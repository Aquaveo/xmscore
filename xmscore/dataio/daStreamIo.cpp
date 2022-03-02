//------------------------------------------------------------------------------
/// \file
/// \ingroup dataio
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My header
#include <xmscore/dataio/daStreamIo.h>

// 3. Standard Library Headers
#include <fstream>
#include <sstream>

// 4. External Library Headers
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/unordered_map.hpp>
#include <zlib.h>

// 5. Shared Headers
#include <xmscore/locale/locale.h>
#include <xmscore/misc/StringUtil.h>
#include <xmscore/misc/XmError.h>
#include <xmscore/misc/XmLog.h>

//----- Forward declarations ---------------------------------------------------

//----- External globals -------------------------------------------------------

//----- Namespace declaration --------------------------------------------------

namespace xms
{
//----- Constants / Enumerations -----------------------------------------------

//----- Classes / Structs ------------------------------------------------------

//----- Class / Function definitions -------------------------------------------

namespace
{
const int MAX_BLOCK_SIZE = 1024 * 32;
}

////////////////////////////////////////////////////////////////////////////////
/// Implementation for DaStreamReader.
////////////////////////////////////////////////////////////////////////////////
class DaStreamReader::Impl
{
public:
  /// Constructor
  /// \param a_inStream The input stream.
  /// \param a_binaryArrays Were binary arrays written?
  Impl(std::istream& a_inStream, bool a_binaryArrays)
  : m_inStream(a_inStream)
  , m_binaryArrays(a_binaryArrays)
  {
  }

  std::istream& m_inStream; ///< The input stream.
  bool m_binaryArrays;      ///< Should binary arrays be read?
};

////////////////////////////////////////////////////////////////////////////////
/// Implementation for DaStreamWriter.
////////////////////////////////////////////////////////////////////////////////
class DaStreamWriter::Impl
{
public:
  /// Constructor
  /// \param a_outStream The input stream.
  /// \param a_binaryArrays Should binary arrays be written?
  Impl(std::ostream& a_outStream, bool a_binaryArrays)
  : m_outStream(a_outStream)
  , m_binaryArrays(a_binaryArrays)
  {
  }

  std::ostream& m_outStream;        ///< The output stream.
  bool m_binaryArrays;              ///< Should binary arrays be written?
  int m_blockSize = MAX_BLOCK_SIZE; ///< The block size for binary arrays.
};

namespace
{
//------------------------------------------------------------------------------
/// \brief Compresses bytes of given length using zlib compress.
/// \param a_source The bytes to compress.
/// \param a_sourceLength The number of bytes to compress.
/// \param a_dest The destination for the compressed bytes.
/// \param a_destLength The maximum destination length.
/// \return The length of the compressed bytes or -1 on failure.
//------------------------------------------------------------------------------
int32_t iCompress(const char* a_source, int32_t a_sourceLength, char* a_dest, int32_t a_destLength)
{
  auto compressedLength = static_cast<uLong>(a_destLength);
  auto result = compress2(reinterpret_cast<Bytef*>(a_dest), &compressedLength,
                          reinterpret_cast<const Bytef*>(a_source),
                          static_cast<uLong>(a_sourceLength), Z_BEST_SPEED);
  if (result != Z_OK)
  {
    XM_LOG(xmlog::error, _("Unable to write file. Compression failed."));
    return -1;
  }

  return static_cast<int32_t>(compressedLength);
} // iCompress
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
bool iUncompress(const char* a_source, int32_t a_sourceLength, char* a_dest, int32_t a_destLength)
{
  auto uncompressedLength = static_cast<uLong>(a_destLength);
  bool success = uncompress(reinterpret_cast<Bytef*>(a_dest), &uncompressedLength,
                            reinterpret_cast<const Bytef*>(a_source),
                            static_cast<uLong>(a_sourceLength)) == Z_OK;
  success = success && static_cast<int32_t>(uncompressedLength) == a_destLength;
  if (!success)
  {
    XM_LOG(xmlog::error, _("Unable to read file. Unable to uncompress data."));
    return false;
  }

  return true;
} // iCompress
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
int32_t iBase64EncodeSize(int32_t a_sourceLength)
{
  unsigned long length = ((4U * static_cast<unsigned long>(a_sourceLength) / 3U) + 3U) & ~3U;
  return static_cast<int32_t>(length);
} // iBase64EncodeSize
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
int32_t iBase64Encode(const char* a_source, int32_t a_sourceLength, char* a_dest)
{
  using namespace boost::archive::iterators;
  typedef base64_from_binary<transform_width<const char*, 6, 8>> base64_text;

  const char* srcBegin = a_source;
  const char* srcEnd = srcBegin + a_sourceLength;
  char* destBegin = a_dest;
  char* destIterator = a_dest;
  for (auto it = base64_text(srcBegin); it != base64_text(srcEnd); ++it)
    *destIterator++ = *it;
  *destIterator = 0;

  auto encodedLength = int32_t(destIterator - destBegin);
  return encodedLength;
} // iBase64Encode
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
int32_t iBase64Decode(const char* a_source, int32_t a_sourceLength, char* a_dest)
{
  using namespace boost::archive::iterators;
  typedef transform_width<binary_from_base64<const char*>, 8, 6> base64_dec;

  int32_t size = a_sourceLength;
  if (size && a_source[size - 1] == '=')
  {
    --size;
    if (size && a_source[size - 1] == '=')
      --size;
  }

  if (size != 0)
  {
    char* destBegin = a_dest;
    char* destIterator = a_dest;
    auto base64Begin = base64_dec(a_source);
    auto base64End = base64_dec(a_source + size);
    for (auto it = base64Begin; it != base64End; ++it)
      *destIterator++ = *it;

    auto decodedLength = int32_t(destIterator - destBegin);
    return decodedLength;
  }

  return 0;
} // iBase64Decode
//------------------------------------------------------------------------------
/// \brief Read a line into a std::stringstream.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_ss The std::stringstream to write to.
/// \return True on success.
//------------------------------------------------------------------------------
bool iReadLineToSStream(std::istream& a_inStream, const char* a_name, std::stringstream& a_ss)
{
  std::string line;
  if (!daReadLine(a_inStream, line))
    return false;

  auto position = line.find(a_name);
  if (position == std::string::npos)
    return false;
  else
  {
    for (size_t i = 0; i < position; ++i)
    {
      if (!isspace(line[i]))
        return false;
    }
  }

  a_ss.clear();
  std::replace(line.begin(), line.end(), ',', ' ');
  a_ss.str(line.substr(position));
  return !a_ss.fail();
} // iReadLineToSStream
//------------------------------------------------------------------------------
/// \brief Read a single value from a line.
/// \param a_inStream The stream to read from.
/// \param a_val The value to read.
/// \return True on success.
//------------------------------------------------------------------------------
template <typename _T>
bool iReadLineValue(std::istream& a_inStream, _T& a_val)
{
  std::string line;
  if (!daReadLine(a_inStream, line))
    return false;
  std::stringstream ss;
  ss.str(line);
  ss >> a_val;
  return !ss.fail();
} // iReadLineValue
//------------------------------------------------------------------------------
/// \brief Read named vector of values from multiple lines.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_vec The vector of values.
/// \return True on success.
//------------------------------------------------------------------------------
template <typename _T>
bool iReadVector(std::istream& a_inStream, const char* a_name, std::vector<_T>& a_vec)
{
  a_vec.clear();
  int size;
  if (!daReadIntLine(a_inStream, a_name, size))
    return false;
  for (int ii = 0; ii < size; ++ii)
  {
    _T val;
    if (!iReadLineValue(a_inStream, val))
      return false;
    a_vec.push_back(val);
  }
  return true;
} // iReadVector
//------------------------------------------------------------------------------
/// \brief Read a named data value from a line.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_d1 The data value.
/// \return True on success.
//------------------------------------------------------------------------------
template <typename _T>
bool iReadValue(std::istream& a_inStream, const char* a_name, _T& a_d1)
{
  std::stringstream ss;
  if (!iReadLineToSStream(a_inStream, a_name, ss))
    return false;
  std::string name;
  ss >> name;
  ss >> a_d1;
  return !ss.fail();
} // iReadValue
//------------------------------------------------------------------------------
/// \brief Read a named triplet of data values from a line.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param d1 The first value.
/// \param d2 The second value.
/// \param d3 The third value.
/// \return True on success.
//------------------------------------------------------------------------------
template <typename _T>
bool iRead3Values(std::istream& a_inStream, const char* a_name, _T& d1, _T& d2, _T& d3)
{
  std::stringstream ss;
  if (!iReadLineToSStream(a_inStream, a_name, ss))
    return false;
  std::string name;
  ss >> name;
  ss >> d1;
  ss >> d2;
  ss >> d3;
  return !ss.fail();
} // iRead3Values
//------------------------------------------------------------------------------
/// \brief Read a named pair of data values from a line.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param d1 The first value.
/// \param d2 The second value.
/// \return True on success.
//------------------------------------------------------------------------------
template <typename _T>
bool iRead2Values(std::istream& a_inStream, const char* a_name, _T& d1, _T& d2)
{
  std::stringstream ss;
  if (!iReadLineToSStream(a_inStream, a_name, ss))
    return false;
  std::string name;
  ss >> name;
  ss >> d1;
  ss >> d2;
  return !ss.fail();
} // iRead2Values
//------------------------------------------------------------------------------
/// \brief Read an integer value from a string. Return the remaining string.
/// \param a_line The string to read from. Returns the remaining string.
/// \param a_val The value to read.
/// \return True if no errors.
//------------------------------------------------------------------------------
template <typename _T>
bool iReadValueFromLine(std::string& a_line, _T& a_val)
{
  std::string line = a_line;
  std::string stringValue;
  if (!daReadStringFromLine(line, stringValue))
    return false;

  std::istringstream inStream(stringValue);
  _T tempVal;
  inStream >> tempVal;
  if (inStream.fail() || !inStream.eof())
    return false;
  a_val = tempVal;
  a_line = line;
  return true;
} // iReadValueFromLine

} // namespace

////////////////////////////////////////////////////////////////////////////////
/// \class DaStreamReader
/// \brief Class for reading ASCII files with named card fields. Also includes
/// the ability to embed non-portable compressed binary for integer and Pt3d
/// arrays.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Constructor.
/// \param a_inStream The input stream.
/// \param a_binaryArrays Should binary arrays be written?
//------------------------------------------------------------------------------
DaStreamReader::DaStreamReader(std::istream& a_inStream, bool a_binaryArrays /*= false*/)
: m_impl(new Impl(a_inStream, a_binaryArrays))
{
} // DaStreamReader::DaStreamReader
//------------------------------------------------------------------------------
/// \brief Destructor.
//------------------------------------------------------------------------------
DaStreamReader::~DaStreamReader()
{
} // DaStreamReader::~DaStreamReader
//------------------------------------------------------------------------------
/// \brief Are array values read as binary?
/// \return If the array values will be read as binary.
//------------------------------------------------------------------------------
bool DaStreamReader::IsBinary() const
{
  return m_impl->m_binaryArrays;
} // DaStreamReader::IsBinary
//------------------------------------------------------------------------------
/// \brief Read a line that begins with a name.
/// \param a_name The expected name before the value.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadNamedLine(const char* a_name)
{
  std::stringstream ss;
  return iReadLineToSStream(m_impl->m_inStream, a_name, ss);
} // DaStreamReader::ReadNamedLine
//------------------------------------------------------------------------------
/// \brief Read a line from a stream with the following line endings: CR LF, LF,
/// CR, or none.
/// \param a_line The line that was read.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadLine(std::string& a_line)
{
  a_line.clear();

  // The characters in the stream are read one-by-one using a std::streambuf.
  // That is faster than reading them one-by-one using the std::istream.
  // Code that uses streambuf this way must be guarded by a sentry object.
  // The sentry object performs various tasks,
  // such as thread synchronization and updating the stream state.

  std::istream::sentry se(m_impl->m_inStream, true);
  std::streambuf* sb = m_impl->m_inStream.rdbuf();

  for (;;)
  {
    int c = sb->sbumpc();
    if (c == '\n')
    {
      return !!m_impl->m_inStream;
    }

    if (c == '\r')
    {
      if (sb->sgetc() == '\n')
        sb->sbumpc();
      return !!m_impl->m_inStream;
    }

    if (c == std::streambuf::traits_type::eof())
    {
      // Also handle the case when the last line has no line ending
      if (a_line.empty())
        m_impl->m_inStream.setstate(std::ios::eofbit);
      return !!m_impl->m_inStream;
    }

    a_line += static_cast<char>(c);
  }
} // DaStreamReader::ReadLine
//------------------------------------------------------------------------------
/// \brief Read a named integer value from a line.
/// \param a_name The expected name before the value.
/// \param a_val The integer value.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadIntLine(const char* a_name, int& a_val)
{
  return iReadValue(m_impl->m_inStream, a_name, a_val);
} // DaStreamReader::ReadIntLine
//------------------------------------------------------------------------------
/// \brief Read a named double value from a line.
/// \param a_name The expected name before the value.
/// \param a_val The double value.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadDoubleLine(const char* a_name, double& a_val)
{
  return iReadValue(m_impl->m_inStream, a_name, a_val);
} // DaStreamReader::ReadDoubleLine
//------------------------------------------------------------------------------
/// \brief Read a named string value from a line.
/// \param a_name The expected name before the value.
/// \param a_val The string value.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadStringLine(const char* a_name, std::string& a_val)
{
  return iReadValue(m_impl->m_inStream, a_name, a_val);
} // DaStreamReader::ReadStringLine
//------------------------------------------------------------------------------
/// \brief Read named vector of integers from multiple lines.
/// \param a_name The expected name before the value.
/// \param a_vec The vector of integers.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadVecInt(const char* a_name, VecInt& a_vec)
{
  if (IsBinary())
  {
    int size;
    if (!ReadIntLine(a_name, size))
      return false;

    a_vec.resize(size);
    if (size != 0)
      ReadBinaryBytes(reinterpret_cast<char*>(&a_vec[0]), size * sizeof(VecInt::value_type));
    return true;
  }

  return iReadVector(m_impl->m_inStream, a_name, a_vec);
} // DaStreamReader::ReadVecInt
//------------------------------------------------------------------------------
/// \brief Read named vector of doubles from multiple lines.
/// \param a_name The expected name before the value.
/// \param a_vec The vector of doubles.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadVecDbl(const char* a_name, VecDbl& a_vec)
{
  if (IsBinary())
  {
    int size;
    if (!ReadIntLine(a_name, size))
      return false;

    a_vec.resize(size);
    if (size != 0)
      ReadBinaryBytes(reinterpret_cast<char*>(&a_vec[0]), size * sizeof(VecDbl::value_type));
    return true;
  }

  return iReadVector(m_impl->m_inStream, a_name, a_vec);
} // DaStreamReader::ReadVecDbl
//------------------------------------------------------------------------------
/// \brief Read named vector of Pt3d from multiple lines.
/// \param a_name The expected name before the value.
/// \param a_vec The vector of Pt3d.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadVecPt3d(const char* a_name, VecPt3d& a_vec)
{
  int size;
  if (!daReadIntLine(m_impl->m_inStream, a_name, size))
    return false;

  if (IsBinary())
  {
    a_vec.resize(size);
    if (size != 0)
      ReadBinaryBytes(reinterpret_cast<char*>(&a_vec[0]), size * sizeof(VecPt3d::value_type));
  }
  else
  {
    a_vec.resize(0);
    a_vec.reserve(size);
    std::string pointLine;
    std::string pointValue;
    for (int i = 0; i < size; ++i)
    {
      if (!daReadLine(m_impl->m_inStream, pointLine))
        return false;

      bool success = daReadStringFromLine(pointLine, pointValue);
      success = success && pointValue == N_("POINT");
      int readPointIdx = -1;
      success = success && daReadIntFromLine(pointLine, readPointIdx);
      success = success && readPointIdx == static_cast<int>(i);
      Pt3d pt;
      success = success && daReadDoubleFromLine(pointLine, pt.x);
      success = success && daReadDoubleFromLine(pointLine, pt.y);
      success = success && daReadDoubleFromLine(pointLine, pt.z);
      if (!success)
        return false;
      a_vec.push_back(pt);
    }
  }

  return true;
} // DaStreamReader::ReadVecPt3d
//------------------------------------------------------------------------------
/// \brief Read a named pair of words from a line.
/// \param a_name The expected name before the value.
/// \param a_val1 The first word.
/// \param a_val2 The second word.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::Read2StringLine(const char* a_name, std::string& a_val1, std::string& a_val2)
{
  return iRead2Values(m_impl->m_inStream, a_name, a_val1, a_val2);
} // DaStreamReader::Read2StringLine
//------------------------------------------------------------------------------
/// \brief Read a named triplet of words from a line.
/// \param a_name The expected name before the value.
/// \param a_val1 The first word.
/// \param a_val2 The second word.
/// \param a_val3 The third word.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::Read3StringLine(const char* a_name,
                                     std::string& a_val1,
                                     std::string& a_val2,
                                     std::string& a_val3)
{
  return iRead3Values(m_impl->m_inStream, a_name, a_val1, a_val2, a_val3);
} // DaStreamReader::Read3StringLine
//------------------------------------------------------------------------------
/// \brief Read a named triplet of doubles from a line.
/// \param a_name The expected name before the value.
/// \param a_val1 The first double.
/// \param a_val2 The second double.
/// \param a_val3 The third double.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::Read3DoubleLine(const char* a_name,
                                     double& a_val1,
                                     double& a_val2,
                                     double& a_val3)
{
  return iRead3Values(m_impl->m_inStream, a_name, a_val1, a_val2, a_val3);
} // DaStreamReader::Read3DoubleLine
//------------------------------------------------------------------------------
/// \brief Read an integer value from a string. Return the remaining string.
/// \param a_line The string to read from. Returns the remaining string.
/// \param a_val The value to read.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadIntFromLine(std::string& a_line, int& a_val)
{
  return iReadValueFromLine(a_line, a_val);
} // DaStreamReader::ReadIntFromLine
//------------------------------------------------------------------------------
/// \brief Read a string value from a string. Return the remaining string.
/// \param a_line The string to read from. Returns the remaining string.
/// \param a_val The value to read.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadStringFromLine(std::string& a_line, std::string& a_val)
{
  std::istringstream inStream(a_line);
  inStream >> a_val;
  if (inStream.fail())
  {
    return false;
  }
  size_t position = inStream.tellg();
  if (position != std::string::npos)
  {
    a_line = inStream.str().substr(position);
  }
  else
  {
    a_line = "";
  }
  return true;
} // DaStreamReader::ReadStringFromLine
//------------------------------------------------------------------------------
/// \brief Read a double value from a string. Return the remaining string.
/// \param a_line The string to read from. Returns the remaining string.
/// \param a_val The value to read.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadDoubleFromLine(std::string& a_line, double& a_val)
{
  return iReadValueFromLine(a_line, a_val);
} // DaStreamReader::ReadDoubleFromLine
//------------------------------------------------------------------------------
/// \brief Read a white space separated string.
/// \param a_val The value read.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadString(std::string& a_val)
{
  m_impl->m_inStream >> a_val;
  return !m_impl->m_inStream.fail();
} // DaStreamReader::ReadString
//------------------------------------------------------------------------------
/// \brief Read an integer value.
/// \param a_val The value read.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadInt(int& a_val)
{
  m_impl->m_inStream >> a_val;
  return !m_impl->m_inStream.fail();
} // DaStreamReader::ReadInt
//------------------------------------------------------------------------------
/// \brief Go to the next line in the stream.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::NextLine()
{
  std::string line;
  ReadLine(line);
  return !m_impl->m_inStream.fail();
} // DaStreamReader::NextLine
//------------------------------------------------------------------------------
/// \brief Read binary bytes of a given length from a file.
/// \param a_dest The byte array to read to.
/// \param a_destLength The length of bytes to be read.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadBinaryBytes(char* a_dest, long long a_destLength)
{
  auto maxCompressedLength = static_cast<int32_t>(compressBound(MAX_BLOCK_SIZE));
  int32_t maxEncodeLength = iBase64EncodeSize(maxCompressedLength);
  std::unique_ptr<char[]> compressed(new char[maxCompressedLength]);
  std::unique_ptr<char[]> encoded(new char[maxEncodeLength + 1]);

  while (a_destLength > 0)
  {
    // read block info
    std::string blockString;
    int32_t encodedLength;
    int32_t blockLength;
    ReadString(blockString);
    ReadInt(encodedLength);
    ReadInt(blockLength);
    NextLine();

    // read and decode
    m_impl->m_inStream.read(encoded.get(), encodedLength);
    NextLine();

    auto compressedLength = iBase64Decode(encoded.get(), encodedLength, compressed.get());

    // decompress data
    if (!iUncompress(compressed.get(), compressedLength, a_dest, blockLength))
      return false;

    a_dest += blockLength;
    a_destLength -= blockLength;
  }

  return true;
} // DaStreamReader::ReadBinaryBytes
//------------------------------------------------------------------------------
/// \brief Determines if next line read will begin given text.
/// \param a_text The text to check for.
/// \return True if next line begins with given string.
//------------------------------------------------------------------------------
bool DaStreamReader::LineBeginsWith(const char* a_text)
{
  return daLineBeginsWith(m_impl->m_inStream, a_text);
} // DaStreamReader::LineBeginsWith

////////////////////////////////////////////////////////////////////////////////
/// \class DaStreamWriter
/// \brief Class for writing ASCII files with named card fields. Also includes
/// the ability to embed non-portable compressed binary for integer and Pt3d
/// arrays.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Constructor.
/// \param a_outStream The output stream.
/// \param a_binaryArrays Should binary arrays be written?
//------------------------------------------------------------------------------
DaStreamWriter::DaStreamWriter(std::ostream& a_outStream, bool a_binaryArrays /*= false*/)
: m_impl(new Impl(a_outStream, a_binaryArrays))
{
} // DaStreamWriter::DaStreamWriter
//------------------------------------------------------------------------------
/// \brief Destructor.
//------------------------------------------------------------------------------
DaStreamWriter::~DaStreamWriter()
{
} // DaStreamWriter::~DaStreamWriter
//------------------------------------------------------------------------------
/// \brief Are array values written as binary?
/// \return If the array values will be written as binary.
//------------------------------------------------------------------------------
bool DaStreamWriter::IsBinary() const
{
  return m_impl->m_binaryArrays;
} // DaStreamWriter::IsBinary
//------------------------------------------------------------------------------
/// \brief Write a given line to a stream.
/// \param a_line The line of text to be written.
//------------------------------------------------------------------------------
void DaStreamWriter::WriteLine(const std::string& a_line)
{
  daWriteLine(m_impl->m_outStream, a_line);
} // DaStreamWriter::WriteLine
//------------------------------------------------------------------------------
/// \brief Write a named word line.
/// \param a_name The name to be written before the value.
/// \param a_val The word.
//------------------------------------------------------------------------------
void DaStreamWriter::WriteStringLine(const char* a_name, const std::string& a_val)
{
  daWriteStringLine(m_impl->m_outStream, a_name, a_val);
} // DaStreamWriter::WriteStringLine
//------------------------------------------------------------------------------
/// \brief Write a named integer value to a line.
/// \param a_name The name to be written before the value.
/// \param a_val The integer value.
//------------------------------------------------------------------------------
void DaStreamWriter::WriteIntLine(const char* a_name, int a_val)
{
  daWriteIntLine(m_impl->m_outStream, a_name, a_val);
} // DaStreamWriter::WriteIntLine
//------------------------------------------------------------------------------
/// \brief Write a named double line value.
/// \param a_name The name to be written before the value.
/// \param a_val The double value to write.
//------------------------------------------------------------------------------
void DaStreamWriter::WriteDoubleLine(const char* a_name, double a_val)
{
  daWriteDoubleLine(m_impl->m_outStream, a_name, a_val);
} // DaStreamWriter::WriteDoubleLine
//------------------------------------------------------------------------------
/// \brief Write a named vector of integers to several lines.
/// \param a_name The name to be written before the value.
/// \param a_vec The vector of integers.
//------------------------------------------------------------------------------
void DaStreamWriter::WriteVecInt(const char* a_name, const VecInt& a_vec)
{
  if (IsBinary())
  {
    m_impl->m_outStream << a_name << ' ' << a_vec.size() << '\n';
    if (!a_vec.empty())
      WriteBinaryBytes(reinterpret_cast<const char*>(&a_vec[0]),
                       a_vec.size() * sizeof(VecInt::value_type));
  }
  else
  {
    daWriteVecInt(m_impl->m_outStream, a_name, a_vec);
  }
} // DaStreamWriter::WriteVecInt
//------------------------------------------------------------------------------
/// \brief Write a named vector of doubles to multiple lines.
/// \param a_name The name to be written before the value.
/// \param a_vec The vector of doubles.
//------------------------------------------------------------------------------
void DaStreamWriter::WriteVecDbl(const char* a_name, const VecDbl& a_vec)
{
  if (IsBinary())
  {
    m_impl->m_outStream << a_name << ' ' << a_vec.size() << '\n';
    if (!a_vec.empty())
      WriteBinaryBytes(reinterpret_cast<const char*>(&a_vec[0]),
                       a_vec.size() * sizeof(VecDbl::value_type));
  }
  else
  {
    daWriteVecDbl(m_impl->m_outStream, a_name, a_vec);
  }
} // DaStreamWriter::WriteVecDbl
//------------------------------------------------------------------------------
/// \brief Write a named vector of Pt3d to multiple lines.
/// \param a_name The name to be written before the value.
/// \param a_points The vector of Pt3d.
//------------------------------------------------------------------------------
void DaStreamWriter::WriteVecPt3d(const char* a_name, const VecPt3d& a_points)
{
  if (IsBinary())
  {
    m_impl->m_outStream << a_name << ' ' << a_points.size() << '\n';
    if (!a_points.empty())
      WriteBinaryBytes(reinterpret_cast<const char*>(&a_points[0]),
                       a_points.size() * sizeof(VecPt3d::value_type));
  }
  else
  {
    daWriteVecPt3d(m_impl->m_outStream, a_name, a_points);
  }
} // DaStreamWriter::WriteVecPt3d
//------------------------------------------------------------------------------
/// \brief Write a named pair of words to a line.
/// \param a_name The name to be written before the value.
/// \param a_val1 The first word.
/// \param a_val2 The second word.
//------------------------------------------------------------------------------
void DaStreamWriter::Write2StringLine(const char* a_name,
                                      const std::string& a_val1,
                                      const std::string& a_val2)
{
  daWrite2StringLine(m_impl->m_outStream, a_name, a_val1, a_val2);
} // DaStreamWriter::Write2StringLine
//------------------------------------------------------------------------------
/// \brief Write a named triplet of words to a line.
/// \param a_name The name to be written before the value.
/// \param a_val1 The first word.
/// \param a_val2 The second word.
/// \param a_val3 The third word.
//------------------------------------------------------------------------------
void DaStreamWriter::Write3StringLine(const char* a_name,
                                      const std::string& a_val1,
                                      const std::string& a_val2,
                                      const std::string& a_val3)
{
  daWrite3StringLine(m_impl->m_outStream, a_name, a_val1, a_val2, a_val3);
} // DaStreamWriter::Write3StringLine
//------------------------------------------------------------------------------
/// \brief Write a named triplet of doubles to a line.
/// \param a_name The name to be written before the value.
/// \param a_val1 The first double.
/// \param a_val2 The second double.
/// \param a_val3 The third double.
//------------------------------------------------------------------------------
void DaStreamWriter::Write3DoubleLine(const char* a_name,
                                      const double& a_val1,
                                      const double& a_val2,
                                      const double& a_val3)
{
  daWrite3DoubleLine(m_impl->m_outStream, a_name, a_val1, a_val2, a_val3);
} // DaStreamWriter::Write3DoubleLine
//------------------------------------------------------------------------------
/// \brief Write a string value to the stream.
/// \param a_string
//------------------------------------------------------------------------------
void DaStreamWriter::WriteString(const char* a_string)
{
  m_impl->m_outStream << a_string;
} // DaStreamWriter::WriteString
//------------------------------------------------------------------------------
/// \brief Append an integer value to the end of a line of text.
/// \param a_val The integer value.
//------------------------------------------------------------------------------
void DaStreamWriter::AppendInt(int a_val)
{
  m_impl->m_outStream << ' ' << a_val;
} // DaStreamWriter::AppendInt
//------------------------------------------------------------------------------
/// \brief Append a list of integer values to the end of a line of text.
/// \param a_values A pointer to the integer values.
/// \param a_numValues The number of integer values.
//------------------------------------------------------------------------------
void DaStreamWriter::AppendInts(const int* a_values, int a_numValues)
{
  for (int i = 0; i < a_numValues; ++i)
    m_impl->m_outStream << ' ' << *a_values++;
} // DaStreamWriter::AppendInts
//------------------------------------------------------------------------------
/// \brief Append a string to the end of a line of text.
/// \param a_val The string to append.
//------------------------------------------------------------------------------
void DaStreamWriter::AppendString(const std::string& a_val)
{
  m_impl->m_outStream << ' ' << a_val;
} // DaStreamWriter::AppendString
//------------------------------------------------------------------------------
/// \brief Add return to move to the next line of text.
//------------------------------------------------------------------------------
void DaStreamWriter::EndLine()
{
  m_impl->m_outStream << '\n';
} // DaStreamWriter::EndLine
//------------------------------------------------------------------------------
/// \brief Write binary bytes of a given length to the stream.
/// \param a_source The bytes to be written.
/// \param a_sourceLength The number of bytes to be written.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamWriter::WriteBinaryBytes(const char* a_source, long long a_sourceLength)
{
  auto maxCompressedLength = static_cast<int32_t>(compressBound(m_impl->m_blockSize));
  int32_t maxEncodeLength = iBase64EncodeSize(maxCompressedLength);
  std::unique_ptr<char[]> compressed(new char[maxCompressedLength]);
  std::unique_ptr<char[]> encoded(new char[maxEncodeLength + 1]);

  while (a_sourceLength > 0)
  {
    // compress a block
    int32_t blockLength = a_sourceLength < m_impl->m_blockSize
                            ? static_cast<int32_t>(a_sourceLength)
                            : m_impl->m_blockSize;
    int32_t compressedLength =
      iCompress(a_source, blockLength, compressed.get(), maxCompressedLength);
    if (compressedLength < 0)
      return false;
    a_sourceLength -= blockLength;
    a_source += blockLength;

    // encode a block
    int32_t encodedLength = iBase64Encode(compressed.get(), compressedLength, encoded.get());

    // write block info
    WriteString(N_("BINARY_BLOCK"));
    AppendInt(encodedLength);
    AppendInt(blockLength);
    EndLine();
    m_impl->m_outStream.write(encoded.get(), encodedLength);
    EndLine();
  }

  return true;
} // DaStreamWriter::WriteBinaryBytes
//------------------------------------------------------------------------------
/// \brief Set the block size to use when writing binary arrays.
/// \param a_blockSize The block size.
//------------------------------------------------------------------------------
void DaStreamWriter::SetBinaryBlockSize(int a_blockSize)
{
  m_impl->m_blockSize = a_blockSize > MAX_BLOCK_SIZE ? MAX_BLOCK_SIZE : a_blockSize;
} // DaStreamWriter::SetBinaryBlockSize

//------------------------------------------------------------------------------
/// \brief Read a line that begins with a name.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daReadNamedLine(std::istream& a_inStream, const char* a_name)
{
  std::stringstream ss;
  return iReadLineToSStream(a_inStream, a_name, ss);
} // daReadNamedLine
//------------------------------------------------------------------------------
/// \brief Read a line from a stream with the following line endings: CR LF, LF,
/// CR, or none.
/// \param a_inStream The stream to read from.
/// \param a_line The line that was read.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daReadLine(std::istream& a_inStream, std::string& a_line)
{
  a_line.clear();

  // The characters in the stream are read one-by-one using a std::streambuf.
  // That is faster than reading them one-by-one using the std::istream.
  // Code that uses streambuf this way must be guarded by a sentry object.
  // The sentry object performs various tasks,
  // such as thread synchronization and updating the stream state.

  std::istream::sentry se(a_inStream, true);
  std::streambuf* sb = a_inStream.rdbuf();

  for (;;)
  {
    int c = sb->sbumpc();
    if (c == '\n')
    {
      return !!a_inStream;
    }

    if (c == '\r')
    {
      if (sb->sgetc() == '\n')
        sb->sbumpc();
      return !!a_inStream;
    }

    if (c == std::streambuf::traits_type::eof())
    {
      // Also handle the case when the last line has no line ending
      if (a_line.empty())
        a_inStream.setstate(std::ios::eofbit);
      return !!a_inStream;
    }

    a_line += (char)c;
  }
} // daReadLine
//------------------------------------------------------------------------------
/// \brief Read a named integer value from a line.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_val The integer value.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daReadIntLine(std::istream& a_inStream, const char* a_name, int& a_val)
{
  return iReadValue(a_inStream, a_name, a_val);
} // daReadIntLine
//------------------------------------------------------------------------------
/// \brief Read a named double value from a line.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_val The double value.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daReadDoubleLine(std::istream& a_inStream, const char* a_name, double& a_val)
{
  return iReadValue(a_inStream, a_name, a_val);
} // daReadDoubleLine
//------------------------------------------------------------------------------
/// \brief Read a named string value from a line.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_val The string value.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daReadStringLine(std::istream& a_inStream, const char* a_name, std::string& a_val)
{
  return iReadValue(a_inStream, a_name, a_val);
} // daReadStringLine
//------------------------------------------------------------------------------
/// \brief Read named vector of integers from multiple lines.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_vec The vector of integers.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daReadVecInt(std::istream& a_inStream, const char* a_name, VecInt& a_vec)
{
  return iReadVector(a_inStream, a_name, a_vec);
} // daReadVecInt
//------------------------------------------------------------------------------
/// \brief Read named vector of doubles from multiple lines.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_vec The vector of doubles.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daReadVecDbl(std::istream& a_inStream, const char* a_name, VecDbl& a_vec)
{
  return iReadVector(a_inStream, a_name, a_vec);
} // daReadVecDbl
//------------------------------------------------------------------------------
/// \brief Read named vector of Pt3d from multiple lines.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_vec The vector of Pt3d.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daReadVecPt3d(std::istream& a_inStream, const char* a_name, VecPt3d& a_vec)
{
  int size;
  if (!daReadIntLine(a_inStream, a_name, size))
    return false;

  a_vec.resize(0);
  a_vec.reserve(size);
  std::string pointLine;
  std::string pointValue;
  for (int i = 0; i < size; ++i)
  {
    if (!daReadLine(a_inStream, pointLine))
      return false;

    bool success = daReadStringFromLine(pointLine, pointValue);
    success = success && pointValue == N_("POINT");
    int readPointIdx = -1;
    success = success && daReadIntFromLine(pointLine, readPointIdx);
    success = success && readPointIdx == (int)i;
    Pt3d pt;
    success = success && daReadDoubleFromLine(pointLine, pt.x);
    success = success && daReadDoubleFromLine(pointLine, pt.y);
    success = success && daReadDoubleFromLine(pointLine, pt.z);
    if (!success)
      return false;
    a_vec.push_back(pt);
  }

  return true;
} // daReadVecPt3d
//------------------------------------------------------------------------------
/// \brief Read a named pair of words from a line.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_val1 The first word.
/// \param a_val2 The second word.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daRead2StringLine(std::istream& a_inStream,
                       const char* a_name,
                       std::string& a_val1,
                       std::string& a_val2)
{
  return iRead2Values(a_inStream, a_name, a_val1, a_val2);
} // daRead2StringLine
//------------------------------------------------------------------------------
/// \brief Read a named triplet of words from a line.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_val1 The first word.
/// \param a_val2 The second word.
/// \param a_val3 The third word.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daRead3StringLine(std::istream& a_inStream,
                       const char* a_name,
                       std::string& a_val1,
                       std::string& a_val2,
                       std::string& a_val3)
{
  return iRead3Values(a_inStream, a_name, a_val1, a_val2, a_val3);
} // daRead3StringLine
//------------------------------------------------------------------------------
/// \brief Read a named triplet of doubles from a line.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_val1 The first double.
/// \param a_val2 The second double.
/// \param a_val3 The third double.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daRead3DoubleLine(std::istream& a_inStream,
                       const char* a_name,
                       double& a_val1,
                       double& a_val2,
                       double& a_val3)
{
  return iRead3Values(a_inStream, a_name, a_val1, a_val2, a_val3);
} // daRead3DoubleLine
//------------------------------------------------------------------------------
/// \brief Read an integer value from a string. Return the remaining string.
/// \param a_line The string to read from. Returns the remaining string.
/// \param a_val The value to read.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daReadIntFromLine(std::string& a_line, int& a_val)
{
  return iReadValueFromLine(a_line, a_val);
} // daReadIntFromLine
//------------------------------------------------------------------------------
/// \brief Read a string value from a string. Return the remaining string.
/// \param a_line The string to read from. Returns the remaining string.
/// \param a_val The value to read.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daReadStringFromLine(std::string& a_line, std::string& a_val)
{
  std::istringstream inStream(a_line);
  inStream >> a_val;
  if (inStream.fail())
  {
    return false;
  }
  size_t position = inStream.tellg();
  if (position != std::string::npos)
  {
    a_line = inStream.str().substr(position);
  }
  else
  {
    a_line = "";
  }
  return true;
} // daReadStringFromLine
//------------------------------------------------------------------------------
/// \brief Read a double value from a string. Return the remaining string.
/// \param a_line The string to read from. Returns the remaining string.
/// \param a_val The value to read.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool daReadDoubleFromLine(std::string& a_line, double& a_val)
{
  return iReadValueFromLine(a_line, a_val);
} // daReadDoubleFromLine
//------------------------------------------------------------------------------
/// \brief Determines if next line read will begin given text.
/// \param a_inStream The stream to read from.
/// \param a_text The text to check for.
/// \return True if next line begins with given string.
//------------------------------------------------------------------------------
bool daLineBeginsWith(std::istream& a_inStream, const std::string& a_text)
{
  auto streamPosition = a_inStream.tellg();
  bool foundText = false;
  std::string line;
  if (daReadLine(a_inStream, line))
  {
    foundText = line.find(a_text) == 0;
  }

  a_inStream.seekg(streamPosition);
  return foundText;
} // daLineBeginsWith
//------------------------------------------------------------------------------
/// \brief Write a given line to a stream.
/// \param a_outStream The stream to write too.
/// \param a_name The line of text to be written.
//------------------------------------------------------------------------------
void daWriteNamedLine(std::ostream& a_outStream, const char* a_name)
{
  a_outStream << a_name << '\n';
} // daWriteNamedLine
  //------------------------------------------------------------------------------
  /// \brief Write a given line to a stream.
  /// \param a_outStream The stream to write too.
  /// \param a_line The line of text to be written.
  //------------------------------------------------------------------------------
void daWriteLine(std::ostream& a_outStream, const std::string& a_line)
{
  a_outStream << a_line << '\n';
} // daWriteLine
//------------------------------------------------------------------------------
/// \brief Write a named double line value.
/// \param a_outStream The stream to write too.
/// \param a_name The name to be written before the value.
/// \param a_val The double value to write.
//------------------------------------------------------------------------------
void daWriteDoubleLine(std::ostream& a_outStream, const char* a_name, double a_val)
{
  StTemp2DigitExponents temp2DigitExponents;
  a_outStream << a_name << ' ' << STRstd(a_val) << '\n';
} // daWriteDoubleLine
//------------------------------------------------------------------------------
/// \brief Write a named word line.
/// \param a_outStream The stream to write too.
/// \param a_name The name to be written before the value.
/// \param a_val The word.
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void daWriteStringLine(std::ostream& a_outStream, const char* a_name, const std::string& a_val)
{
  a_outStream << a_name << ' ' << a_val << '\n';
} // daWriteStringLine
//------------------------------------------------------------------------------
/// \brief Write a named vector of integers to several lines.
/// \param a_outStream The stream to write too.
/// \param a_name The name to be written before the value.
/// \param a_vec The vector of integers.
//------------------------------------------------------------------------------
void daWriteVecInt(std::ostream& a_outStream, const char* a_name, const VecInt& a_vec)
{
  size_t size = a_vec.size();
  a_outStream << a_name << ' ' << size << '\n';
  for (auto val : a_vec)
  {
    a_outStream << N_("  ") << val << '\n';
  }
} // daWriteVecInt
//------------------------------------------------------------------------------
/// \brief Write a named pair of words to a line.
/// \param a_outStream The stream to write too.
/// \param a_name The name to be written before the value.
/// \param a_val1 The first word.
/// \param a_val2 The second word.
//------------------------------------------------------------------------------
void daWrite2StringLine(std::ostream& a_outStream,
                        const char* a_name,
                        const std::string& a_val1,
                        const std::string& a_val2)
{
  a_outStream << a_name << ' ' << a_val1 << ' ' << a_val2 << '\n';
} // daWrite2StringLine
//------------------------------------------------------------------------------
/// \brief Write a named triplet of words to a line.
/// \param a_outStream The stream to write too.
/// \param a_name The name to be written before the value.
/// \param a_val1 The first word.
/// \param a_val2 The second word.
/// \param a_val3 The third word.
//------------------------------------------------------------------------------
void daWrite3StringLine(std::ostream& a_outStream,
                        const char* a_name,
                        const std::string& a_val1,
                        const std::string& a_val2,
                        const std::string& a_val3)
{
  a_outStream << a_name << ' ' << a_val1 << ' ' << a_val2 << ' ' << a_val3 << '\n';
} // daWrite3StringLine
//------------------------------------------------------------------------------
/// \brief Write a named triplet of doubles to a line.
/// \param a_outStream The stream to write too.
/// \param a_name The name to be written before the value.
/// \param a_val1 The first double.
/// \param a_val2 The second double.
/// \param a_val3 The third double.
//------------------------------------------------------------------------------
void daWrite3DoubleLine(std::ostream& a_outStream,
                        const char* a_name,
                        const double& a_val1,
                        const double& a_val2,
                        const double& a_val3)
{
  a_outStream << a_name << ' ' << STRstd(a_val1) << ' ' << STRstd(a_val2) << ' ' << STRstd(a_val3)
              << '\n';
} // daWrite3DoubleLine
//------------------------------------------------------------------------------
/// \brief Write a named integer value to a line.
/// \param a_outStream The stream to write too.
/// \param a_name The name to be written before the value.
/// \param a_val The integer value.
//------------------------------------------------------------------------------
void daWriteIntLine(std::ostream& a_outStream, const char* a_name, int a_val)
{
  a_outStream << a_name << ' ' << a_val << '\n';
} // daWriteIntLine
//------------------------------------------------------------------------------
/// \brief Write a named vector of doubles to multiple lines.
/// \param a_outStream The stream to write too.
/// \param a_name The name to be written before the value.
/// \param a_vec The vector of doubles.
//------------------------------------------------------------------------------
void daWriteVecDbl(std::ostream& a_outStream, const char* a_name, const VecDbl& a_vec)
{
  StTemp2DigitExponents temp2DigitExponents;
  size_t size = a_vec.size();
  a_outStream << a_name << ' ' << size << '\n';
  for (auto val : a_vec)
  {
    a_outStream << N_("  ") << STRstd(val) << '\n';
  }
} // daWriteVecDbl
//------------------------------------------------------------------------------
/// \brief Write a named vector of Pt3d to multiple lines.
/// \param a_outStream The stream to write too.
/// \param a_name The name to be written before the value.
/// \param a_points The vector of Pt3d.
//------------------------------------------------------------------------------
void daWriteVecPt3d(std::ostream& a_outStream, const char* a_name, const VecPt3d& a_points)
{
  // write name and size of vector
  a_outStream << a_name << ' ' << a_points.size() << '\n';

  // write each indented point and XYZ (why not remove POINT text?)
  StTemp2DigitExponents use2DigitExponents;
  for (size_t i = 0; i < a_points.size(); ++i)
  {
    const Pt3d& point = a_points[i];
    std::string sx(STRstd(point.x));
    std::string sy(STRstd(point.y));
    std::string sz(STRstd(point.z));
    a_outStream << N_("  POINT ") << i << ' ' << sx << ' ' << sy << ' ' << sz << '\n';
  }
} // daWriteVecPt3d

} // namespace xms

#if CXX_TEST
///////////////////////////////////////////////////////////////////////////////
// TESTS
///////////////////////////////////////////////////////////////////////////////

#include <xmscore/dataio/daStreamIo.t.h>

#include <numeric>

using namespace xms;

////////////////////////////////////////////////////////////////////////////////
/// \class DaStreamIoUnitTests
/// \brief Tests for Stream IO utilities.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Test daReadNamedLine.
//------------------------------------------------------------------------------
void DaStreamIoUnitTests::testReadNamedLine()
{
  // test read with CR LF, LF, CR, and no line endings
  std::string lineEndingsInput =N_(
    "Windows Line\r\n"
    "Unix Line\n"
    "Mac Line\r"
    "Last Line");
  std::istringstream inStream(lineEndingsInput);
  TS_ASSERT(daReadNamedLine(inStream, N_("Windows Line")));
  TS_ASSERT(daReadNamedLine(inStream, N_("Unix Line")));
  TS_ASSERT(daReadNamedLine(inStream, N_("Mac Line")));
  TS_ASSERT(daReadNamedLine(inStream, N_("Last Line")));
} // DaStreamIoUnitTests::testReadNamedLine
//------------------------------------------------------------------------------
/// \brief Test daWriteLine and daReadLine.
//------------------------------------------------------------------------------
void DaStreamIoUnitTests::testReadWriteLine()
{
  std::ostringstream outputStream;
  daWriteLine(outputStream, N_("daWriteLine version 1.0"));
  std::string expected = N_("daWriteLine version 1.0\n");
  std::string found = outputStream.str();
  TS_ASSERT_EQUALS(expected, found);

  std::istringstream inputStream(outputStream.str());
  std::string value;
  daReadLine(inputStream, value);
  expected = N_("daWriteLine version 1.0");
  TS_ASSERT_EQUALS(expected, value);

  // test read with CR LF, LF, CR, and no line endings
  std::string lineEndingsInput =N_(
    "Windows Line\r\n"
    "Unix Line\n"
    "Mac Line\r"
    "Last Line");
  std::istringstream endingsIn(lineEndingsInput);
  daReadLine(endingsIn, value);
  TS_ASSERT_EQUALS(N_("Windows Line"), value);
  daReadLine(endingsIn, value);
  TS_ASSERT_EQUALS(N_("Unix Line"), value);
  daReadLine(endingsIn, value);
  TS_ASSERT_EQUALS(N_("Mac Line"), value);
  daReadLine(endingsIn, value);
  TS_ASSERT_EQUALS(N_("Last Line"), value);
} // DaStreamIoUnitTests::testReadWriteLine
//------------------------------------------------------------------------------
/// \brief Test daWriteStringLine and daReadStringLine.
//------------------------------------------------------------------------------
void DaStreamIoUnitTests::testReadWriteStringLine()
{
  std::ostringstream outputStream;
  const char* name = N_("LINE_NAME");
  std::string expectedValue = N_("VALUE");
  daWriteStringLine(outputStream, name, expectedValue);
  std::string expected = N_("LINE_NAME VALUE\n");
  std::string found = outputStream.str();
  TS_ASSERT_EQUALS(expected, found);

  std::istringstream inputStream(outputStream.str());
  std::string foundValue;
  TS_ASSERT(daReadStringLine(inputStream, name, foundValue));
  TS_ASSERT_EQUALS(expectedValue, foundValue);
} // DaStreamIoUnitTests::testReadWriteStringLine
//------------------------------------------------------------------------------
/// \brief Test daWrite2StringLine and daRead2StringLine.
//------------------------------------------------------------------------------
void DaStreamIoUnitTests::testReadWrite2StringLine()
{
  std::ostringstream outputStream;
  const char* name = N_("LINE_NAME");
  std::string expectedValue1 = N_("VALUE1");
  std::string expectedValue2 = N_("VALUE2");
  daWrite2StringLine(outputStream, name, expectedValue1, expectedValue2);
  std::string expected = N_("LINE_NAME VALUE1 VALUE2\n");
  std::string found = outputStream.str();
  TS_ASSERT_EQUALS(expected, found);

  std::istringstream inputStream(outputStream.str());
  std::string foundValue1;
  std::string foundValue2;
  TS_ASSERT(daRead2StringLine(inputStream, name, foundValue1, foundValue2));
  TS_ASSERT_EQUALS(expectedValue1, foundValue1);
  TS_ASSERT_EQUALS(expectedValue2, foundValue2);
} // DaStreamIoUnitTests::testReadWrite2StringLine
//------------------------------------------------------------------------------
/// \brief Test daWrite3StringLine and daRead3StringLine.
//------------------------------------------------------------------------------
void DaStreamIoUnitTests::testReadWrite3StringLine()
{
  std::ostringstream outputStream;
  const char* name = N_("LINE_NAME");
  std::string expectedValue1 = N_("VALUE1");
  std::string expectedValue2 = N_("VALUE2");
  std::string expectedValue3 = N_("VALUE3");
  daWrite3StringLine(outputStream, name, expectedValue1, expectedValue2, expectedValue3);
  std::string expected = N_("LINE_NAME VALUE1 VALUE2 VALUE3\n");
  std::string found = outputStream.str();
  TS_ASSERT_EQUALS(expected, found);

  std::istringstream inputStream(outputStream.str());
  std::string foundValue1;
  std::string foundValue2;
  std::string foundValue3;
  TS_ASSERT(daRead3StringLine(inputStream, name, foundValue1, foundValue2, foundValue3));
  TS_ASSERT_EQUALS(expectedValue1, foundValue1);
  TS_ASSERT_EQUALS(expectedValue2, foundValue2);
  TS_ASSERT_EQUALS(expectedValue3, foundValue3);
} // DaStreamIoUnitTests::testReadWrite3StringLine
//------------------------------------------------------------------------------
/// \brief Test daReadIntFromLine.
//------------------------------------------------------------------------------
void DaStreamIoUnitTests::testReadIntFromLine()
{
  std::string line;

  // read from front
  int intValue;
  line = N_("1 -1 A 2.0 B 4");
  TS_ASSERT(daReadIntFromLine(line, intValue));
  TS_ASSERT_EQUALS(1, intValue);
  TS_ASSERT_EQUALS(N_(" -1 A 2.0 B 4"), line);

  // read second value (with a space)
  line = N_(" -1 A 2.0 B 4");
  TS_ASSERT(daReadIntFromLine(line, intValue));
  TS_ASSERT_EQUALS(-1, intValue);
  TS_ASSERT_EQUALS(N_(" A 2.0 B 4"), line);

  // fails to read alpha (int value stays the same)
  line = N_(" A 2.0 B 4");
  intValue = -1;
  TS_ASSERT(!daReadIntFromLine(line, intValue));
  TS_ASSERT_EQUALS(-1, intValue);
  TS_ASSERT_EQUALS(N_(" A 2.0 B 4"), line);

  // fails to read double (int value stays the same)
  line = N_(" A 2.0 B 4");
  intValue = -1;
  TS_ASSERT(!daReadIntFromLine(line, intValue));
  TS_ASSERT_EQUALS(-1, intValue);
  TS_ASSERT_EQUALS(N_(" A 2.0 B 4"), line);

  // fails with empty line
  line = N_("");
  intValue = -1;
  TS_ASSERT(!daReadIntFromLine(line, intValue));
  TS_ASSERT_EQUALS(-1, intValue);
  TS_ASSERT_EQUALS(N_(""), line);
} // DaStreamIoUnitTests::testReadIntFromLine
//------------------------------------------------------------------------------
/// \brief Test daReadStringFromLine.
//------------------------------------------------------------------------------
void DaStreamIoUnitTests::testReadStringFromLine()
{
  std::string line;

  // read from front
  std::string stringValue;
  line = N_("value1 value2 3");
  TS_ASSERT(daReadStringFromLine(line, stringValue));
  TS_ASSERT_EQUALS(N_("value1"), stringValue);
  TS_ASSERT_EQUALS(N_(" value2 3"), line);

  // read second value (with a space)
  line = N_(" value2 value3");
  TS_ASSERT(daReadStringFromLine(line, stringValue));
  TS_ASSERT_EQUALS(N_("value2"), stringValue);
  TS_ASSERT_EQUALS(N_(" value3"), line);

  // read last value
  line = N_("3");
  TS_ASSERT(daReadStringFromLine(line, stringValue));
  TS_ASSERT_EQUALS(N_("3"), stringValue);
  TS_ASSERT_EQUALS(N_(""), line);

  // fails with empty line (string value stays the same)
  line = N_("");
  stringValue = N_("3");
  TS_ASSERT(!daReadStringFromLine(line, stringValue));
  TS_ASSERT_EQUALS(N_("3"), stringValue);
  TS_ASSERT_EQUALS(N_(""), line);
} // DaStreamIoUnitTests::testReadStringFromLine
//------------------------------------------------------------------------------
/// \brief Test daReadDoubleFromLine.
//------------------------------------------------------------------------------
void DaStreamIoUnitTests::testReadDoubleFromLine()
{
  std::string line;

  // read from front
  double doubleValue;
  line = N_("1.1 -1.0e-3 3");
  TS_ASSERT(daReadDoubleFromLine(line, doubleValue));
  TS_ASSERT_EQUALS(1.1, doubleValue);
  TS_ASSERT_EQUALS(N_(" -1.0e-3 3"), line);

  // read second value (with a space)
  line = N_(" -1.0e-3 3");
  TS_ASSERT(daReadDoubleFromLine(line, doubleValue));
  TS_ASSERT_EQUALS(-1.0e-3, doubleValue);
  TS_ASSERT_EQUALS(N_(" 3"), line);

  // read last value
  line = N_("3");
  TS_ASSERT(daReadDoubleFromLine(line, doubleValue));
  TS_ASSERT_EQUALS(3, doubleValue);
  TS_ASSERT_EQUALS(N_(""), line);

  // fails with empty line (string value stays the same)
  line = N_("");
  doubleValue = 3;
  TS_ASSERT(!daReadDoubleFromLine(line, doubleValue));
  TS_ASSERT_EQUALS(3, doubleValue);
  TS_ASSERT_EQUALS(N_(""), line);
} // DaStreamIoUnitTests::testReadDoubleFromLine
//------------------------------------------------------------------------------
/// \brief Test daWriteIntLine and daReadIntLine.
//------------------------------------------------------------------------------
void DaStreamIoUnitTests::testReadWriteIntLine()
{
  std::ostringstream outputStream;
  const char* name = N_("LINE_NAME");
  const int expect = 22;
  daWriteIntLine(outputStream, name, expect);
  std::string outputExpected = N_("LINE_NAME 22\n");
  std::string outputFound = outputStream.str();
  TS_ASSERT_EQUALS(outputExpected, outputFound);

  std::istringstream inputStream(outputStream.str());
  int found;
  TS_ASSERT(daReadIntLine(inputStream, name, found));
  TS_ASSERT_EQUALS(expect, found);
} // DaStreamIoUnitTests::testReadWriteIntLine
//------------------------------------------------------------------------------
/// \brief Test daWriteDoubleLine and daReadDoubleLine.
//------------------------------------------------------------------------------
void DaStreamIoUnitTests::testReadWriteDoubleLine()
{
  std::ostringstream outputStream;
  const char* name = N_("LINE_NAME");
  const double expect1 = 1.123e-20;
  const double expect2 = 2.0;
  daWriteDoubleLine(outputStream, name, expect1);
  daWriteDoubleLine(outputStream, name, expect2);
  std::string outputExpected =N_( "LINE_NAME 1.123e-20\nLINE_NAME 2.0\n");
  std::string outputFound = outputStream.str();
  TS_ASSERT_EQUALS(outputExpected, outputFound);

  std::istringstream inputStream(outputStream.str());
  double found;
  TS_ASSERT(daReadDoubleLine(inputStream, name, found));
  TS_ASSERT_EQUALS(expect1, found);
  TS_ASSERT(daReadDoubleLine(inputStream, name, found));
  TS_ASSERT_EQUALS(expect2, found);
} // DaStreamIoUnitTests::testReadWriteDoubleLine
//------------------------------------------------------------------------------
/// \brief Test daWrite3DoubleLine and daRead3DoubleLine.
//------------------------------------------------------------------------------
void DaStreamIoUnitTests::testReadWrite3DoubleLine()
{
  std::ostringstream outputStream;
  const char* name = N_("LINE_NAME");
  const double expect1 = 560770.5;
  const double expect2 = 70055.4;
  const double expect3 = 22.3;
  daWrite3DoubleLine(outputStream, name, expect1, expect2, expect3);
  std::string outputExpected = N_("LINE_NAME 560770.5 70055.4 22.3\n");
  std::string outputFound = outputStream.str();
  TS_ASSERT_EQUALS(outputExpected, outputFound);

  std::istringstream inputStream(outputStream.str());
  double found1;
  double found2;
  double found3;
  TS_ASSERT(daRead3DoubleLine(inputStream, name, found1, found2, found3));
  TS_ASSERT_EQUALS(expect1, found1);
  TS_ASSERT_EQUALS(expect2, found2);
  TS_ASSERT_EQUALS(expect3, found3);
} // DaStreamIoUnitTests::testReadWrite3DoubleLine
//------------------------------------------------------------------------------
/// \brief Test daWriteVecInt and daReadVecInt.
//------------------------------------------------------------------------------
void DaStreamIoUnitTests::testReadWriteVecInt()
{
  std::ostringstream outputStream;
  const char* name = N_("VECTOR_NAME");
  const VecInt expect = {1, 2, 3};
  daWriteVecInt(outputStream, name, expect);
  std::string outputExpected =N_(
    "VECTOR_NAME 3\n"
    "  1\n"
    "  2\n"
    "  3\n");
  std::string outputFound = outputStream.str();
  TS_ASSERT_EQUALS(outputExpected, outputFound);

  std::istringstream inputStream(outputStream.str());
  VecInt found;
  TS_ASSERT(daReadVecInt(inputStream, name, found));
  TS_ASSERT_EQUALS(expect, found);
} // DaStreamIoUnitTests::testReadWriteVecInt
//------------------------------------------------------------------------------
/// \brief Test daWriteVecDbl and daReadVecDbl.
//------------------------------------------------------------------------------
void DaStreamIoUnitTests::testReadWriteVecDbl()
{
  std::ostringstream outputStream;
  const char* name = N_("VECTOR_NAME");
  const VecDbl expect = {1.0, 2.2e-20, 3.3};
  daWriteVecDbl(outputStream, name, expect);
  std::string outputExpected =N_(
    "VECTOR_NAME 3\n"
    "  1.0\n"
    "  2.2e-20\n"
    "  3.3\n");
  std::string outputFound = outputStream.str();
  TS_ASSERT_EQUALS(outputExpected, outputFound);

  std::istringstream inputStream(outputStream.str());
  VecDbl found;
  TS_ASSERT(daReadVecDbl(inputStream, name, found));
  TS_ASSERT_EQUALS(expect, found);
} // DaStreamIoUnitTests::testReadWriteVecDbl
//------------------------------------------------------------------------------
/// \brief Test daWriteVecPt3d and daReadVecPt3d.
//------------------------------------------------------------------------------
void DaStreamIoUnitTests::testReadWriteVecPt3d()
{
  std::ostringstream outputStream;
  const char* name = N_("VECTOR_NAME");
  const VecPt3d expect = {
    {1.0, 1.2, 1.3},
    {2.1, 2.2, 2.3e-20},
  };
  daWriteVecPt3d(outputStream, name, expect);
  std::string outputExpected =N_(
    "VECTOR_NAME 2\n"
    "  POINT 0 1.0 1.2 1.3\n"
    "  POINT 1 2.1 2.2 2.3e-20\n");
  std::string outputFound = outputStream.str();
  TS_ASSERT_EQUALS(outputExpected, outputFound);

  std::istringstream inputStream(outputStream.str());
  VecPt3d found;
  TS_ASSERT(daReadVecPt3d(inputStream, name, found));
  TS_ASSERT_EQUALS(expect, found);
} // DaStreamIoUnitTests::testReadWriteVecPt3d
//------------------------------------------------------------------------------
/// \brief Test DaStreamReader::LineBeginsWith
//------------------------------------------------------------------------------
void DaStreamIoUnitTests::testLineBeginsWith()
{
  const char* inputText =N_(
    "VECTOR_NAME 2\n"
    "  POINT 0 1.1 1.2 1.3\n"
    "  POINT 1 2.1 2.2 2.3\n");
  std::istringstream inputStream(inputText);
  TS_ASSERT(daLineBeginsWith(inputStream, N_("VECTOR_NAME")));
  std::string line;
  TS_ASSERT(daReadLine(inputStream, line));
  TS_ASSERT_EQUALS(N_("VECTOR_NAME 2"), line);
  TS_ASSERT(daLineBeginsWith(inputStream, N_("  POINT")));
  TS_ASSERT(daReadLine(inputStream, line));
  TS_ASSERT_EQUALS(N_("  POINT 0 1.1 1.2 1.3"), line);
  TS_ASSERT(daLineBeginsWith(inputStream, N_("  POINT 1 2.1 2.2 2.3")));
  TS_ASSERT(daReadLine(inputStream, line));
  TS_ASSERT_EQUALS(N_("  POINT 1 2.1 2.2 2.3"), line);
} // DaStreamIoUnitTests::testLineBeginsWith
////////////////////////////////////////////////////////////////////////////////
/// \class DaReaderWriterIoUnitTests
/// \brief Tests for Stream IO utilities.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Test ReadNamedLine.
//------------------------------------------------------------------------------
void DaReaderWriterIoUnitTests::testReadNamedLine()
{
  // test read with CR LF, LF, CR, and no line endings
  std::string lineEndingsInput =N_(
    "Windows Line\r\n"
    "Unix Line\n"
    "Mac Line\r"
    "Last Line");
  std::istringstream inStream(lineEndingsInput);
  DaStreamReader reader(inStream);
  TS_ASSERT(reader.ReadNamedLine(N_("Windows Line")));
  TS_ASSERT(reader.ReadNamedLine(N_("Unix Line")));
  TS_ASSERT(reader.ReadNamedLine(N_("Mac Line")));
  TS_ASSERT(reader.ReadNamedLine(N_("Last Line")));
} // DaReaderWriterIoUnitTests::testReadNamedLine
//------------------------------------------------------------------------------
/// \brief Test WriteLine and ReadLine.
//------------------------------------------------------------------------------
void DaReaderWriterIoUnitTests::testReadWriteLine()
{
  std::ostringstream outputStream;
  DaStreamWriter writer(outputStream);
  writer.WriteLine(N_("daWriteLine version 1.0"));
  std::string expected = N_("daWriteLine version 1.0\n");
  std::string found = outputStream.str();
  TS_ASSERT_EQUALS(expected, found);

  std::istringstream inputStream(outputStream.str());
  DaStreamReader reader(inputStream);
  std::string value;
  reader.ReadLine(value);
  expected = N_("daWriteLine version 1.0");
  TS_ASSERT_EQUALS(expected, value);

  // test read with CR LF, LF, CR, and no line endings
  std::string lineEndingsInput =N_(
    "Windows Line\r\n"
    "Unix Line\n"
    "Mac Line\r"
    "Last Line");
  std::istringstream endingsIn(lineEndingsInput);
  DaStreamReader readerIn(endingsIn);
  readerIn.ReadLine(value);
  TS_ASSERT_EQUALS(N_("Windows Line"), value);
  readerIn.ReadLine(value);
  TS_ASSERT_EQUALS(N_("Unix Line"), value);
  readerIn.ReadLine(value);
  TS_ASSERT_EQUALS(N_("Mac Line"), value);
  readerIn.ReadLine(value);
  TS_ASSERT_EQUALS(N_("Last Line"), value);
} // DaReaderWriterIoUnitTests::testReadWriteLine
//------------------------------------------------------------------------------
/// \brief Test WriteStringLine and ReadStringLine.
//------------------------------------------------------------------------------
void DaReaderWriterIoUnitTests::testReadWriteStringLine()
{
  std::ostringstream outputStream;
  DaStreamWriter writer(outputStream);
  const char* name = N_("LINE_NAME");
  std::string expectedValue = N_("VALUE");
  writer.WriteStringLine(name, expectedValue);
  std::string expected = N_("LINE_NAME VALUE\n");
  std::string found = outputStream.str();
  TS_ASSERT_EQUALS(expected, found);

  std::istringstream inputStream(outputStream.str());
  DaStreamReader reader(inputStream);
  std::string foundValue;
  TS_ASSERT(reader.ReadStringLine(name, foundValue));
  TS_ASSERT_EQUALS(expectedValue, foundValue);
} // DaReaderWriterIoUnitTests::testReadWriteStringLine
//------------------------------------------------------------------------------
/// \brief Test Write2StringLine and Read2StringLine.
//------------------------------------------------------------------------------
void DaReaderWriterIoUnitTests::testReadWrite2StringLine()
{
  std::ostringstream outputStream;
  DaStreamWriter writer(outputStream);
  const char* name = N_("LINE_NAME");
  std::string expectedValue1 = N_("VALUE1");
  std::string expectedValue2 = N_("VALUE2");
  writer.Write2StringLine(name, expectedValue1, expectedValue2);
  std::string expected = N_("LINE_NAME VALUE1 VALUE2\n");
  std::string found = outputStream.str();
  TS_ASSERT_EQUALS(expected, found);

  std::istringstream inputStream(outputStream.str());
  DaStreamReader reader(inputStream);
  std::string foundValue1;
  std::string foundValue2;
  TS_ASSERT(reader.Read2StringLine(name, foundValue1, foundValue2));
  TS_ASSERT_EQUALS(expectedValue1, foundValue1);
  TS_ASSERT_EQUALS(expectedValue2, foundValue2);
} // DaReaderWriterIoUnitTests::testReadWrite2StringLine
//------------------------------------------------------------------------------
/// \brief Test Write3StringLine and Read3StringLine.
//------------------------------------------------------------------------------
void DaReaderWriterIoUnitTests::testReadWrite3StringLine()
{
  std::ostringstream outputStream;
  DaStreamWriter writer(outputStream);
  const char* name = N_("LINE_NAME");
  std::string expectedValue1 = N_("VALUE1");
  std::string expectedValue2 = N_("VALUE2");
  std::string expectedValue3 = N_("VALUE3");
  writer.Write3StringLine(name, expectedValue1, expectedValue2, expectedValue3);
  std::string expected = N_("LINE_NAME VALUE1 VALUE2 VALUE3\n");
  std::string found = outputStream.str();
  TS_ASSERT_EQUALS(expected, found);

  std::istringstream inputStream(outputStream.str());
  DaStreamReader reader(inputStream);
  std::string foundValue1;
  std::string foundValue2;
  std::string foundValue3;
  TS_ASSERT(reader.Read3StringLine(name, foundValue1, foundValue2, foundValue3));
  TS_ASSERT_EQUALS(expectedValue1, foundValue1);
  TS_ASSERT_EQUALS(expectedValue2, foundValue2);
  TS_ASSERT_EQUALS(expectedValue3, foundValue3);
} // DaReaderWriterIoUnitTests::testReadWrite3StringLine
//------------------------------------------------------------------------------
/// \brief Test ReadIntFromLine.
//------------------------------------------------------------------------------
void DaReaderWriterIoUnitTests::testReadIntFromLine()
{
  // read from front
  int intValue;
  std::string line = N_("1 -1 A 2.0 B 4");
  TS_ASSERT(DaStreamReader::ReadIntFromLine(line, intValue));
  TS_ASSERT_EQUALS(1, intValue);
  TS_ASSERT_EQUALS(N_(" -1 A 2.0 B 4"), line);

  // read second value (with a space)
  line = N_(" -1 A 2.0 B 4");
  TS_ASSERT(DaStreamReader::ReadIntFromLine(line, intValue));
  TS_ASSERT_EQUALS(-1, intValue);
  TS_ASSERT_EQUALS(N_(" A 2.0 B 4"), line);

  // fails to read alpha (int value stays the same)
  line = N_(" A 2.0 B 4");
  intValue = -1;
  TS_ASSERT(!DaStreamReader::ReadIntFromLine(line, intValue));
  TS_ASSERT_EQUALS(-1, intValue);
  TS_ASSERT_EQUALS(N_(" A 2.0 B 4"), line);

  // fails to read double (int value stays the same)
  line = N_(" A 2.0 B 4");
  intValue = -1;
  TS_ASSERT(!DaStreamReader::ReadIntFromLine(line, intValue));
  TS_ASSERT_EQUALS(-1, intValue);
  TS_ASSERT_EQUALS(N_(" A 2.0 B 4"), line);

  // fails with empty line
  line = N_("");
  intValue = -1;
  TS_ASSERT(!DaStreamReader::ReadIntFromLine(line, intValue));
  TS_ASSERT_EQUALS(-1, intValue);
  TS_ASSERT_EQUALS(N_(""), line);
} // DaReaderWriterIoUnitTests::testReadIntFromLine
//------------------------------------------------------------------------------
/// \brief Test ReadStringFromLine.
//------------------------------------------------------------------------------
void DaReaderWriterIoUnitTests::testReadStringFromLine()
{
  // read from front
  std::string stringValue;
  std::string line = N_("value1 value2 3");
  TS_ASSERT(DaStreamReader::ReadStringFromLine(line, stringValue));
  TS_ASSERT_EQUALS(N_("value1"), stringValue);
  TS_ASSERT_EQUALS(N_(" value2 3"), line);

  // read second value (with a space)
  line = N_(" value2 value3");
  TS_ASSERT(DaStreamReader::ReadStringFromLine(line, stringValue));
  TS_ASSERT_EQUALS(N_("value2"), stringValue);
  TS_ASSERT_EQUALS(N_(" value3"), line);

  // read last value
  line = N_("3");
  TS_ASSERT(DaStreamReader::ReadStringFromLine(line, stringValue));
  TS_ASSERT_EQUALS(N_("3"), stringValue);
  TS_ASSERT_EQUALS(N_(""), line);

  // fails with empty line (string value stays the same)
  line = N_("");
  stringValue = N_("3");
  TS_ASSERT(!DaStreamReader::ReadStringFromLine(line, stringValue));
  TS_ASSERT_EQUALS(N_("3"), stringValue);
  TS_ASSERT_EQUALS(N_(""), line);
} // DaReaderWriterIoUnitTests::testReadStringFromLine
//------------------------------------------------------------------------------
/// \brief Test ReadDoubleFromLine.
//------------------------------------------------------------------------------
void DaReaderWriterIoUnitTests::testReadDoubleFromLine()
{
  // read from front
  double doubleValue;
  std::string line = N_("1.1 -1.0e-3 3");
  TS_ASSERT(DaStreamReader::ReadDoubleFromLine(line, doubleValue));
  TS_ASSERT_EQUALS(1.1, doubleValue);
  TS_ASSERT_EQUALS(N_(" -1.0e-3 3"), line);

  // read second value (with a space)
  line = N_(" -1.0e-3 3");
  TS_ASSERT(DaStreamReader::ReadDoubleFromLine(line, doubleValue));
  TS_ASSERT_EQUALS(-1.0e-3, doubleValue);
  TS_ASSERT_EQUALS(N_(" 3"), line);

  // read last value
  line = N_("3");
  TS_ASSERT(DaStreamReader::ReadDoubleFromLine(line, doubleValue));
  TS_ASSERT_EQUALS(3, doubleValue);
  TS_ASSERT_EQUALS(N_(""), line);

  // fails with empty line (string value stays the same)
  line = N_("");
  doubleValue = 3;
  TS_ASSERT(!DaStreamReader::ReadDoubleFromLine(line, doubleValue));
  TS_ASSERT_EQUALS(3, doubleValue);
  TS_ASSERT_EQUALS(N_(""), line);
} // DaReaderWriterIoUnitTests::testReadDoubleFromLine
//------------------------------------------------------------------------------
/// \brief Test WriteIntLine and ReadIntLine.
//------------------------------------------------------------------------------
void DaReaderWriterIoUnitTests::testReadWriteIntLine()
{
  std::ostringstream outputStream;
  DaStreamWriter writer(outputStream);
  const char* name = N_("LINE_NAME");
  const int expect = 22;
  writer.WriteIntLine(name, expect);
  std::string outputExpected = N_("LINE_NAME 22\n");
  std::string outputFound = outputStream.str();
  TS_ASSERT_EQUALS(outputExpected, outputFound);

  std::istringstream inputStream(outputStream.str());
  DaStreamReader reader(inputStream);
  int found;
  TS_ASSERT(reader.ReadIntLine(name, found));
  TS_ASSERT_EQUALS(expect, found);
} // DaReaderWriterIoUnitTests::testReadWriteIntLine
//------------------------------------------------------------------------------
/// \brief Test WriteDoubleLine and ReadDoubleLine.
//------------------------------------------------------------------------------
void DaReaderWriterIoUnitTests::testReadWriteDoubleLine()
{
  std::ostringstream outputStream;
  DaStreamWriter writer(outputStream);
  const char* name = N_("LINE_NAME");
  const double expect = 22.1;
  writer.WriteDoubleLine(name, expect);
  std::string outputExpected = N_("LINE_NAME 22.1\n");
  std::string outputFound = outputStream.str();
  TS_ASSERT_EQUALS(outputExpected, outputFound);

  std::istringstream inputStream(outputStream.str());
  DaStreamReader reader(inputStream);
  double found;
  TS_ASSERT(reader.ReadDoubleLine(name, found));
  TS_ASSERT_EQUALS(expect, found);
} // DaReaderWriterIoUnitTests::testReadWriteDoubleLine
//------------------------------------------------------------------------------
/// \brief Test Write3DoubleLine and Read3DoubleLine.
//------------------------------------------------------------------------------
void DaReaderWriterIoUnitTests::testReadWrite3DoubleLine()
{
  std::ostringstream outputStream;
  DaStreamWriter writer(outputStream);
  const char* name = N_("LINE_NAME");
  const double expect1 = 22.1;
  const double expect2 = 22.2;
  const double expect3 = 22.3;
  writer.Write3DoubleLine(name, expect1, expect2, expect3);
  std::string outputExpected = N_("LINE_NAME 22.1 22.2 22.3\n");
  std::string outputFound = outputStream.str();
  TS_ASSERT_EQUALS(outputExpected, outputFound);

  std::istringstream inputStream(outputStream.str());
  DaStreamReader reader(inputStream);
  double found1;
  double found2;
  double found3;
  TS_ASSERT(reader.Read3DoubleLine(name, found1, found2, found3));
  TS_ASSERT_EQUALS(expect1, found1);
  TS_ASSERT_EQUALS(expect2, found2);
  TS_ASSERT_EQUALS(expect3, found3);
} // DaReaderWriterIoUnitTests::testReadWrite3DoubleLine
//------------------------------------------------------------------------------
/// \brief Test WriteVecInt and ReadVecInt.
//------------------------------------------------------------------------------
void DaReaderWriterIoUnitTests::testReadWriteVecInt()
{
  std::ostringstream outputStream;
  DaStreamWriter writer(outputStream);
  const char* name = N_("VECTOR_NAME");
  const VecInt expect = {1, 2, 3};
  writer.WriteVecInt(name, expect);
  std::string outputExpected =N_(
    "VECTOR_NAME 3\n"
    "  1\n"
    "  2\n"
    "  3\n");
  std::string outputFound = outputStream.str();
  TS_ASSERT_EQUALS(outputExpected, outputFound);

  std::istringstream inputStream(outputStream.str());
  DaStreamReader reader(inputStream);
  VecInt found;
  TS_ASSERT(reader.ReadVecInt(name, found));
  TS_ASSERT_EQUALS(expect, found);
} // DaReaderWriterIoUnitTests::testReadWriteVecInt
//------------------------------------------------------------------------------
/// \brief Test WriteVecDbl and ReadVecDbl.
//------------------------------------------------------------------------------
void DaReaderWriterIoUnitTests::testReadWriteVecDbl()
{
  std::ostringstream outputStream;
  DaStreamWriter writer(outputStream);
  const char* name = N_("VECTOR_NAME");
  const VecDbl expect = {1.1, 2.2, 3.3};
  writer.WriteVecDbl(name, expect);
  std::string outputExpected =N_(
    "VECTOR_NAME 3\n"
    "  1.1\n"
    "  2.2\n"
    "  3.3\n");
  std::string outputFound = outputStream.str();
  TS_ASSERT_EQUALS(outputExpected, outputFound);

  std::istringstream inputStream(outputStream.str());
  DaStreamReader reader(inputStream);
  VecDbl found;
  TS_ASSERT(reader.ReadVecDbl(name, found));
  TS_ASSERT_EQUALS(expect, found);
} // DaReaderWriterIoUnitTests::testReadWriteVecDbl
//------------------------------------------------------------------------------
/// \brief Test WriteVecPt3d and ReadVecPt3d.
//------------------------------------------------------------------------------
void DaReaderWriterIoUnitTests::testReadWriteVecPt3d()
{
  std::ostringstream outputStream;
  DaStreamWriter writer(outputStream);
  const char* name = N_("VECTOR_NAME");
  const VecPt3d expect = {
    {1.1, 1.2, 1.3},
    {2.1, 2.2, 2.3},
  };
  writer.WriteVecPt3d(name, expect);
  std::string outputExpected =N_(
    "VECTOR_NAME 2\n"
    "  POINT 0 1.1 1.2 1.3\n"
    "  POINT 1 2.1 2.2 2.3\n");
  std::string outputFound = outputStream.str();
  TS_ASSERT_EQUALS(outputExpected, outputFound);

  std::istringstream inputStream(outputStream.str());
  DaStreamReader reader(inputStream);
  VecPt3d found;
  TS_ASSERT(reader.ReadVecPt3d(name, found));
  TS_ASSERT_EQUALS(expect, found);
} // DaReaderWriterIoUnitTests::testReadWriteVecPt3d
//------------------------------------------------------------------------------
/// \brief Test binary WriteVecInt and binary ReadVecInt.
//------------------------------------------------------------------------------
void DaReaderWriterIoUnitTests::testReadWriteBinaryVecInt()
{
  std::ostringstream outputStream;
  bool useBinaryArrays = true;
  DaStreamWriter writer(outputStream, useBinaryArrays);
  const char* name = N_("VECTOR_NAME");
  VecInt expect(100);
  std::iota(expect.begin(), expect.end(), 0);
  writer.WriteVecInt(name, expect);

  std::istringstream inputStream(outputStream.str());
  DaStreamReader reader(inputStream, useBinaryArrays);
  VecInt found;
  TS_ASSERT(reader.ReadVecInt(name, found));
  TS_ASSERT_EQUALS(expect, found);
} // DaReaderWriterIoUnitTests::testReadWriteBinaryVecInt
//------------------------------------------------------------------------------
/// \brief Test binary WriteVecDbl and binary ReadVecDbl.
//------------------------------------------------------------------------------
void DaReaderWriterIoUnitTests::testReadWriteBinaryVecDbl()
{
  std::ostringstream outputStream;
  bool useBinaryArrays = true;
  DaStreamWriter writer(outputStream, useBinaryArrays);
  const char* name = N_("VECTOR_NAME");
  VecDbl expect(100);
  int count = 0;
  for (auto& e : expect)
    e = ++count;
  writer.WriteVecDbl(name, expect);

  std::istringstream inputStream(outputStream.str());
  DaStreamReader reader(inputStream, useBinaryArrays);
  VecDbl found;
  TS_ASSERT(reader.ReadVecDbl(name, found));
  TS_ASSERT_EQUALS(expect, found);
} // DaReaderWriterIoUnitTests::testReadWriteBinaryVecDbl
//------------------------------------------------------------------------------
/// \brief Test binary WriteVecPt3d and binary ReadVecPt3d.
//------------------------------------------------------------------------------
void DaReaderWriterIoUnitTests::testReadWriteBinaryVecPt3d()
{
  std::ostringstream outputStream;
  bool useBinaryArrays = true;
  DaStreamWriter writer(outputStream, useBinaryArrays);
  const char* name = N_("VECTOR_NAME");
  VecPt3d expect(100);
  int count = 0;
  for (auto& e : expect)
  {
    e = Pt3d(count, count + 1, count + 2);
    ++count;
  }
  writer.WriteVecPt3d(name, expect);

  std::istringstream inputStream(outputStream.str());
  DaStreamReader reader(inputStream, useBinaryArrays);
  VecPt3d found;
  TS_ASSERT(reader.ReadVecPt3d(name, found));
  TS_ASSERT_EQUALS(expect, found);
} // DaReaderWriterIoUnitTests::testReadWriteBinaryVecPt3d
//------------------------------------------------------------------------------
/// \brief Test function that read and write parts of a line.
//------------------------------------------------------------------------------
void DaReaderWriterIoUnitTests::testReadWriteLineParts()
{
  std::ostringstream outputStream;
  DaStreamWriter writer(outputStream);
  writer.WriteString(N_("STRING_ONE"));
  TS_ASSERT_EQUALS(N_("STRING_ONE"), outputStream.str());
  writer.AppendInt(0);
  TS_ASSERT_EQUALS(N_("STRING_ONE 0"), outputStream.str());
  writer.AppendString(N_("STRING_TWO"));
  TS_ASSERT_EQUALS(N_("STRING_ONE 0 STRING_TWO"), outputStream.str());
  int ints[] = {1, 2, 3};
  writer.AppendInts(ints, 3);
  TS_ASSERT_EQUALS(N_("STRING_ONE 0 STRING_TWO 1 2 3"), outputStream.str());
  writer.EndLine();
  TS_ASSERT_EQUALS(N_("STRING_ONE 0 STRING_TWO 1 2 3\n"), outputStream.str());

  std::istringstream inputStream(N_("STRING_ONE 0\n1 STRING_TWO"));
  DaStreamReader reader(inputStream);
  std::string s;
  int i;
  TS_ASSERT(reader.ReadString(s));
  TS_ASSERT_EQUALS(N_("STRING_ONE"), s)
  TS_ASSERT(reader.ReadInt(i));
  TS_ASSERT_EQUALS(0, i);
  TS_ASSERT(reader.NextLine());

  TS_ASSERT(reader.ReadInt(i));
  TS_ASSERT_EQUALS(1, i);
  TS_ASSERT(reader.ReadString(s));
  TS_ASSERT_EQUALS(N_("STRING_TWO"), s)
  TS_ASSERT(!reader.NextLine());
} // DaReaderWriterIoUnitTests::testReadWriteLineParts
//------------------------------------------------------------------------------
/// \brief Test reading and writing a binary array.
//------------------------------------------------------------------------------
void DaReaderWriterIoUnitTests::testReadWriteBinaryArrays()
{
  VecInt outValues(500);
  std::iota(outValues.begin(), outValues.end(), 0);
  long long lengthInBytes = (long long)outValues.size() * sizeof(VecInt::value_type);
  std::ostringstream output;
  DaStreamWriter writer(output);
  writer.SetBinaryBlockSize(120);
  writer.WriteBinaryBytes((char*)&outValues[0], lengthInBytes);
  std::string text = output.str();
  std::string expectedText =N_(
    "BINARY_BLOCK 74 120\n"
    "eAENw4UNwDAAAKDO3d3+f3OQEEIIkbGJqZm5haWVtY2tnb2Do5Ozi6ubu4enl7ePr58/RrQBtA\n"
    "BINARY_BLOCK 78 120\n"
    "eAENw4UNwzAAALBcUuaVGf7/a7bkKIQQm5iamVtYWlnb2Nr5s3dwdHJ2cXVz9/D08vbx9fMPILsFOA\n"
    "BINARY_BLOCK 78 120\n"
    "eAENw4UNwzAAALAcVuaVGf5/ZLbkKIQQm5iamVtYWlnb2Nr5s3dwdHJ2cXVz9/D08vbx9fMP+rMIvA\n"
    "BINARY_BLOCK 76 120\n"
    "eAENw4UNwzAAALDcWeaVGd6fLTkKIcQmpmbmFpZW1ja2dv7sHRydnF1c3dw9PL28fXz9/APUugxA\n"
    "BINARY_BLOCK 76 120\n"
    "eAENw4UNwzAAALCcXeaVGf6dLTkKIcQmpmbmFpZW1ja2dv7sHRydnF1c3dw9PL28fXz9/AOuwQ/E\n"
    "BINARY_BLOCK 78 120\n"
    "eAENw4UNwzAAALD8f0CZV2Z4cLbkKIQQm5iamVtYWlnb2Nr5s3dwdHJ2cXVz9/D08vbx9fMPiMgTSA\n"
    "BINARY_BLOCK 78 120\n"
    "eAENw4UNwzAAALD8f0+ZV2b4aLbkKIQQm5iamVtYWlnb2Nr5s3dwdHJ2cXVz9/D08vbx9fMPYs8WzA\n"
    "BINARY_BLOCK 78 120\n"
    "eAENw4UNwzAAALD8f16ZV2Z4YbbkKIQQm5iamVtYWlnb2Nr5s3dwdHJ2cXVz9/D08vbx9fMPPNYaUA\n"
    "BINARY_BLOCK 74 120\n"
    "eAENw4UNwDAAAKDO/f83524k0IcQBkcnZxdXN3cPTy9vH18/Q4SxiamZuYWllbWNrZ0/dFUP4g\n"
    "BINARY_BLOCK 82 120\n"
    "eAENw4URg0AAALBnAbRIkeJS2H8/krvEUQiJqZm5hR9LK2sbv7Z29g7+HJ2cXVzd3D08vfx7+/gCs5IDdg\n"
    "BINARY_BLOCK 82 120\n"
    "eAENw4URg0AAALBnH7RIkeJS2H8hkrvEUQiJqZm5hR9LK2sbv7Z29g7+HJ2cXVzd3D08vfx7+/gCjZkG+g\n"
    "BINARY_BLOCK 82 120\n"
    "eAENw4URg0AAALBnPbRIkeJS2H8DkrvEUQiJqZm5hR9LK2sbv7Z29g7+HJ2cXVzd3D08vfx7+/gCZ6AKfg\n"
    "BINARY_BLOCK 79 120\n"
    "eAENwwUOg0AAALDjt+iQIcNl8G/apHEUQmJqZm7hx9LK2savrZ29gz9HJ2cXVzd3D08v/94+vkGnDgI\n"
    "BINARY_BLOCK 79 120\n"
    "eAENwwUOg0AAALDj8+iQIcNl8FHapHEUQmJqZm7hx9LK2savrZ29gz9HJ2cXVzd3D08v/94+vhuuEYY\n"
    "BINARY_BLOCK 82 120\n"
    "eAENw4URg0AAALBn/zXQIkWKS2EzkrvEUQiJqZm5hR9LK2sbv7Z29g7+HJ2cXVzd3D08vfx7+/gC9aYVCg\n"
    "BINARY_BLOCK 82 120\n"
    "eAENw4URg0AAALBn/63QIkWKS2EVkrvEUQiJqZm5hR9LK2sbv7Z29g7+HJ2cXVzd3D08vfx7+/gCz60Yjg\n"
    "BINARY_BLOCK 63 80\n"
    "eAENwwESQCAAALD8/5NEkUj0Advd5imExejqZjK7e1g8rV7eNh+7r5/DH/dqElM\n");
  TS_ASSERT_EQUALS(expectedText, text);

  std::istringstream input(expectedText);
  DaStreamReader reader(input);
  VecInt inValues(500);
  TS_ASSERT(reader.ReadBinaryBytes((char*)&inValues[0], lengthInBytes));
  TS_ASSERT_EQUALS(outValues, inValues);
} // DaReaderWriterIoUnitTests::testReadWriteBinaryArrays
//------------------------------------------------------------------------------
/// \brief Test DaStreamReader::LineBeginsWith
//------------------------------------------------------------------------------
void DaReaderWriterIoUnitTests::testLineBeginsWith()
{
  const char* inputText =N_(
    "VECTOR_NAME 2\n"
    "  POINT 0 1.1 1.2 1.3\n"
    "  POINT 1 2.1 2.2 2.3\n");
  std::istringstream inputStream(inputText);
  DaStreamReader reader(inputStream);
  TS_ASSERT(reader.LineBeginsWith(N_("VECTOR_NAME")));
  std::string line;
  TS_ASSERT(reader.ReadLine(line));
  TS_ASSERT_EQUALS(N_("VECTOR_NAME 2"), line);
  TS_ASSERT(reader.LineBeginsWith(N_("  POINT")));
  TS_ASSERT(reader.ReadLine(line));
  TS_ASSERT_EQUALS(N_("  POINT 0 1.1 1.2 1.3"), line);
  TS_ASSERT(reader.LineBeginsWith(N_("  POINT 1 2.1 2.2 2.3")));
  TS_ASSERT(reader.ReadLine(line));
  TS_ASSERT_EQUALS(N_("  POINT 1 2.1 2.2 2.3"), line);
} // DaReaderWriterIoUnitTests::testLineBeginsWith

#endif
