#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief Reader/writer classes and free functions for the XMS named-line stream format.
/// \ingroup dataio
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aquaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
// 3. Standard Library Headers
#include <sstream>

// 4. External Library Headers

// 5. Shared Headers
#include <xmscore/misc/base_macros.h>
#include <xmscore/misc/boost_defines.h>
#include <xmscore/stl/vector.h>

// 6. Non-shared Headers

//----- Forward declarations ---------------------------------------------------

//----- Namespace declaration --------------------------------------------------

namespace xms
{
//----- Constants / Enumerations -----------------------------------------------

//----- Forward declarations ---------------------------------------------------

//----- Structs / Classes ------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// \class DaStreamReader
/// \brief Reads the XMS named-line stream format from a std::istream.
///
/// Each Read* call expects the next non-blank line to begin with the supplied
/// name token. Vector reads can use either a textual or binary block depending
/// on the flag passed at construction.
class DaStreamReader
{
public:
  /// \brief Construct a reader bound to a_inStream; set a_binaryArrays to read array payloads as raw bytes.
  explicit DaStreamReader(std::istream& a_inStream, bool a_binaryArrays = false);
  ~DaStreamReader();

  /// \brief Returns true if vector payloads are read as binary blocks rather than text.
  bool IsBinary() const;

  /// \brief Advance past a header line consisting only of the given name token.
  bool ReadNamedLine(const char* a_name);
  /// \brief Read the next line of the stream into a_line.
  bool ReadLine(std::string& a_line);
  /// \brief Read a "name value" line and return the value as a string.
  bool ReadStringLine(const char* a_name, std::string& a_val);
  /// \brief Read a "name value" line and return the value as an int.
  bool ReadIntLine(const char* a_name, int& a_val);
  /// \brief Read a "name value" line and return the value as a double.
  bool ReadDoubleLine(const char* a_name, double& a_val);

  /// \brief Read a named vector of ints (text or binary depending on IsBinary()).
  bool ReadVecInt(const char* a_name, VecInt& a_vec);
  /// \brief Read a named vector of doubles (text or binary depending on IsBinary()).
  bool ReadVecDbl(const char* a_name, VecDbl& a_vec);
  /// \brief Read a named vector of 3D points (text or binary depending on IsBinary()).
  bool ReadVecPt3d(const char* a_name, VecPt3d& a_vec);

  /// \brief Read a "name v1 v2" line of two strings.
  bool Read2StringLine(const char* a_name, std::string& a_val1, std::string& a_val2);
  /// \brief Read a "name v1 v2 v3" line of three strings.
  bool Read3StringLine(const char* a_name,
                       std::string& a_val1,
                       std::string& a_val2,
                       std::string& a_val3);
  /// \brief Read a "name v1 v2 v3" line of three doubles.
  bool Read3DoubleLine(const char* a_name, double& a_val1, double& a_val2, double& a_val3);

  /// \brief Pop the leading whitespace-separated token from a_line and parse it as an int.
  static bool ReadIntFromLine(std::string& a_line, int& a_val);
  /// \brief Pop the leading whitespace-separated token from a_line as a string.
  static bool ReadStringFromLine(std::string& a_line, std::string& a_val);
  /// \brief Pop the leading whitespace-separated token from a_line and parse it as a double.
  static bool ReadDoubleFromLine(std::string& a_line, double& a_val);

  /// \brief Read a single whitespace-separated string token from the stream.
  bool ReadString(std::string& a_val);
  /// \brief Read a single whitespace-separated int token from the stream.
  bool ReadInt(int& a_val);
  /// \brief Advance the underlying stream to the start of the next line.
  bool NextLine();

  /// \brief Read a_destLength raw bytes from the binary section of the stream.
  bool ReadBinaryBytes(char* a_dest, long long a_destLength);

  /// \brief Returns true if the next non-blank line begins with a_text.
  bool LineBeginsWith(const char* a_text);

private:
  XM_DISALLOW_COPY_AND_ASSIGN(DaStreamReader)
  class Impl;
  std::unique_ptr<Impl> m_impl; ///< Implementation.
};

////////////////////////////////////////////////////////////////////////////////
/// \class DaStreamWriter
/// \brief Writes the XMS named-line stream format to a std::ostream.
///
/// Mirrors the readers in DaStreamReader: each Write* method emits a single
/// "name value(s)" line. Array payloads are written either as text or as a
/// binary block depending on the flag passed at construction.
class DaStreamWriter
{
public:
  /// \brief Construct a writer bound to a_outStream; set a_binaryArrays to emit array payloads as raw bytes.
  explicit DaStreamWriter(std::ostream& a_outStream, bool a_binaryArrays = false);
  ~DaStreamWriter();

  /// \brief Returns true if vector payloads are emitted as binary blocks rather than text.
  bool IsBinary() const;

  /// \brief Write a single line verbatim, followed by a newline.
  void WriteLine(const std::string& a_line);
  /// \brief Write a "name value" line for a string value.
  void WriteStringLine(const char* a_name, const std::string& a_val);
  /// \brief Write a "name value" line for an int value.
  void WriteIntLine(const char* a_name, int a_val);
  /// \brief Write a "name value" line for a double value.
  void WriteDoubleLine(const char* a_name, double a_val);

  /// \brief Write a named vector of ints (text or binary depending on IsBinary()).
  void WriteVecInt(const char* a_name, const VecInt& a_vec);
  /// \brief Write a named vector of doubles (text or binary depending on IsBinary()).
  void WriteVecDbl(const char* a_name, const VecDbl& a_vec);
  /// \brief Write a named vector of 3D points (text or binary depending on IsBinary()).
  void WriteVecPt3d(const char* a_name, const VecPt3d& a_points);

  /// \brief Write a "name v1 v2" line of two strings.
  void Write2StringLine(const char* a_name, const std::string& a_val1, const std::string& a_val2);
  /// \brief Write a "name v1 v2 v3" line of three strings.
  void Write3StringLine(const char* a_name,
                        const std::string& a_val1,
                        const std::string& a_val2,
                        const std::string& a_val3);
  /// \brief Write a "name v1 v2 v3" line of three doubles.
  void Write3DoubleLine(const char* a_name,
                        const double& a_val1,
                        const double& a_val2,
                        const double& a_val3);

  /// \brief Append a string token to the current line without ending it.
  void WriteString(const char* a_string);
  /// \brief Append an int token to the current line without ending it.
  void AppendInt(int a_val);
  /// \brief Append a_numVals int tokens to the current line without ending it.
  void AppendInts(const int* a_vals, int a_numVals);
  /// \brief Append a string token to the current line without ending it.
  void AppendString(const std::string& a_val);
  /// \brief Terminate the current line.
  void EndLine();

  /// \brief Write a_sourceLength raw bytes into the binary section of the stream.
  bool WriteBinaryBytes(const char* a_source, long long a_sourceLength);
  /// \brief Set the maximum number of bytes per binary block.
  void SetBinaryBlockSize(int a_blockSize);

private:
  XM_DISALLOW_COPY_AND_ASSIGN(DaStreamWriter)
  class Impl;
  std::unique_ptr<Impl> m_impl; ///< Implementation.
};

//----- Function prototypes ----------------------------------------------------

/// \brief Free-function form of DaStreamReader::ReadNamedLine.
bool daReadNamedLine(std::istream& a_inStream, const char* a_name);
/// \brief Free-function form of DaStreamReader::ReadLine.
bool daReadLine(std::istream& a_inStream, std::string& a_line);
/// \brief Free-function form of DaStreamReader::ReadIntLine.
bool daReadIntLine(std::istream& a_inStream, const char* a_name, int& a_val);
/// \brief Free-function form of DaStreamReader::ReadDoubleLine.
bool daReadDoubleLine(std::istream& a_inStream, const char* a_name, double& a_val);
/// \brief Free-function form of DaStreamReader::ReadStringLine.
bool daReadStringLine(std::istream& a_inStream, const char* a_name, std::string& a_val);
/// \brief Free-function form of DaStreamReader::ReadVecInt (text format only).
bool daReadVecInt(std::istream& a_inStream, const char* a_name, VecInt& a_vec);
/// \brief Free-function form of DaStreamReader::ReadVecDbl (text format only).
bool daReadVecDbl(std::istream& a_inStream, const char* a_name, VecDbl& a_vec);
/// \brief Free-function form of DaStreamReader::ReadVecPt3d (text format only).
bool daReadVecPt3d(std::istream& a_inStream, const char* a_name, VecPt3d& a_vec);
/// \brief Free-function form of DaStreamReader::Read2StringLine.
bool daRead2StringLine(std::istream& a_inStream,
                       const char* a_name,
                       std::string& a_val1,
                       std::string& a_val2);
/// \brief Free-function form of DaStreamReader::Read3StringLine.
bool daRead3StringLine(std::istream& a_inStream,
                       const char* a_name,
                       std::string& a_val1,
                       std::string& a_val2,
                       std::string& a_val3);
/// \brief Free-function form of DaStreamReader::Read3DoubleLine.
bool daRead3DoubleLine(std::istream& a_inStream,
                       const char* a_name,
                       double& a_val1,
                       double& a_val2,
                       double& a_val3);

/// \brief Pop the leading token from a_line and parse it as an int.
bool daReadIntFromLine(std::string& a_line, int& a_val);
/// \brief Pop the leading token from a_line as a string.
bool daReadStringFromLine(std::string& a_line, std::string& a_val);
/// \brief Pop the leading token from a_line and parse it as a double.
bool daReadDoubleFromLine(std::string& a_line, double& a_val);

/// \brief Returns true if the next non-blank line in a_inStream begins with a_text.
bool daLineBeginsWith(std::istream& a_inStream, const std::string& a_text);

/// \brief Free-function form of DaStreamWriter::WriteVecInt (text format only).
void daWriteVecInt(std::ostream& a_outStream, const char* a_name, const VecInt& a_vec);
/// \brief Free-function form of DaStreamWriter::WriteVecDbl (text format only).
void daWriteVecDbl(std::ostream& a_outStream, const char* a_name, const VecDbl& a_vec);
/// \brief Free-function form of DaStreamWriter::WriteVecPt3d (text format only).
void daWriteVecPt3d(std::ostream& a_outStream, const char* a_name, const VecPt3d& a_points);

/// \brief Free-function form of DaStreamWriter::WriteIntLine.
void daWriteIntLine(std::ostream& a_outStream, const char* a_name, int a_val);

/// \brief Free-function form of DaStreamWriter::WriteDoubleLine.
void daWriteDoubleLine(std::ostream& a_outStream, const char* a_name, double a_val);
/// \brief Free-function form of DaStreamWriter::Write3DoubleLine.
void daWrite3DoubleLine(std::ostream& a_outStream,
                        const char* a_name,
                        const double& a_val1,
                        const double& a_val2,
                        const double& a_val3);

/// \brief Free-function form of DaStreamWriter::WriteLine.
void daWriteLine(std::ostream& a_outStream, const std::string& a_line);
/// \brief Free-function form of DaStreamWriter::WriteStringLine.
void daWriteStringLine(std::ostream& a_outStream, const char* a_name, const std::string& a_val);
/// \brief Free-function form of DaStreamWriter::Write2StringLine.
void daWrite2StringLine(std::ostream& a_outStream,
                        const char* a_name,
                        const std::string& a_val1,
                        const std::string& a_val2);
/// \brief Free-function form of DaStreamWriter::Write3StringLine.
void daWrite3StringLine(std::ostream& a_outStream,
                        const char* a_name,
                        const std::string& a_val1,
                        const std::string& a_val2,
                        const std::string& a_val3);

} // namespace xms
