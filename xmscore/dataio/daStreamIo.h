#pragma once
//------------------------------------------------------------------------------
/// \file
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
class DaStreamReader
{
public:
  explicit DaStreamReader(std::istream& a_inStream, bool a_binaryArrays = false);
  ~DaStreamReader();

  bool IsBinary() const;

  bool ReadNamedLine(const char* a_name);
  bool ReadLine(std::string& a_line);
  bool ReadStringLine(const char* a_name, std::string& a_val);
  bool ReadIntLine(const char* a_name, int& a_val);
  bool ReadDoubleLine(const char* a_name, double& a_val);

  bool ReadVecInt(const char* a_name, VecInt& a_vec);
  bool ReadVecDbl(const char* a_name, VecDbl& a_vec);
  bool ReadVecPt3d(const char* a_name, VecPt3d& a_vec);

  bool Read2StringLine(const char* a_name, std::string& a_val1, std::string& a_val2);
  bool Read3StringLine(const char* a_name,
                       std::string& a_val1,
                       std::string& a_val2,
                       std::string& a_val3);
  bool Read3DoubleLine(const char* a_name, double& a_val1, double& a_val2, double& a_val3);

  static bool ReadIntFromLine(std::string& a_line, int& a_val);
  static bool ReadStringFromLine(std::string& a_line, std::string& a_val);
  static bool ReadDoubleFromLine(std::string& a_line, double& a_val);

  bool ReadString(std::string& a_val);
  bool ReadInt(int& a_val);
  bool NextLine();

  bool ReadBinaryBytes(char* a_dest, long long a_destLength);

  bool LineBeginsWith(const char* a_text);

private:
  XM_DISALLOW_COPY_AND_ASSIGN(DaStreamReader)
  class Impl;
  std::unique_ptr<Impl> m_impl; ///< Implementation.
};

////////////////////////////////////////////////////////////////////////////////
class DaStreamWriter
{
public:
  explicit DaStreamWriter(std::ostream& a_outStream, bool a_binaryArrays = false);
  ~DaStreamWriter();

  bool IsBinary() const;

  void WriteLine(const std::string& a_line);
  void WriteStringLine(const char* a_name, const std::string& a_val);
  void WriteIntLine(const char* a_name, int a_val);
  void WriteDoubleLine(const char* a_name, double a_val);

  void WriteVecInt(const char* a_name, const VecInt& a_vec);
  void WriteVecDbl(const char* a_name, const VecDbl& a_vec);
  void WriteVecPt3d(const char* a_name, const VecPt3d& a_points);

  void Write2StringLine(const char* a_name, const std::string& a_val1, const std::string& a_val2);
  void Write3StringLine(const char* a_name,
                        const std::string& a_val1,
                        const std::string& a_val2,
                        const std::string& a_val3);
  void Write3DoubleLine(const char* a_name,
                        const double& a_val1,
                        const double& a_val2,
                        const double& a_val3);

  void WriteString(const char* a_string);
  void AppendInt(int a_val);
  void AppendInts(const int* a_vals, int a_numVals);
  void AppendString(const std::string& a_val);
  void EndLine();

  bool WriteBinaryBytes(const char* a_source, long long a_sourceLength);
  void SetBinaryBlockSize(int a_blockSize);

private:
  XM_DISALLOW_COPY_AND_ASSIGN(DaStreamWriter)
  class Impl;
  std::unique_ptr<Impl> m_impl; ///< Implementation.
};

//----- Function prototypes ----------------------------------------------------

bool daReadNamedLine(std::istream& a_inStream, const char* a_name);
bool daReadLine(std::istream& a_inStream, std::string& a_line);
bool daReadIntLine(std::istream& a_inStream, const char* a_name, int& a_val);
bool daReadDoubleLine(std::istream& a_inStream, const char* a_name, double& a_val);
bool daReadStringLine(std::istream& a_inStream, const char* a_name, std::string& a_val);
bool daReadVecInt(std::istream& a_inStream, const char* a_name, VecInt& a_vec);
bool daReadVecDbl(std::istream& a_inStream, const char* a_name, VecDbl& a_vec);
bool daReadVecPt3d(std::istream& a_inStream, const char* a_name, VecPt3d& a_vec);
bool daRead2StringLine(std::istream& a_inStream,
                       const char* a_name,
                       std::string& a_val1,
                       std::string& a_val2);
bool daRead3StringLine(std::istream& a_inStream,
                       const char* a_name,
                       std::string& a_val1,
                       std::string& a_val2,
                       std::string& a_val3);
bool daRead3DoubleLine(std::istream& a_inStream,
                       const char* a_name,
                       double& a_val1,
                       double& a_val2,
                       double& a_val3);

bool daReadIntFromLine(std::string& a_line, int& a_val);
bool daReadStringFromLine(std::string& a_line, std::string& a_val);
bool daReadDoubleFromLine(std::string& a_line, double& a_val);

void daWriteVecInt(std::ostream& a_outStream, const char* a_name, const VecInt& a_vec);
void daWriteVecDbl(std::ostream& a_outStream, const char* a_name, const VecDbl& a_vec);
void daWriteVecPt3d(std::ostream& a_outStream, const char* a_name, const VecPt3d& a_points);

void daWriteIntLine(std::ostream& a_outStream, const char* a_name, int a_val);

void daWriteDoubleLine(std::ostream& a_outStream, const char* a_name, double a_val);
void daWrite3DoubleLine(std::ostream& a_outStream,
                        const char* a_name,
                        const double& a_val1,
                        const double& a_val2,
                        const double& a_val3);

void daWriteLine(std::ostream& a_outStream, const std::string& a_line);
void daWriteStringLine(std::ostream& a_outStream, const char* a_name, const std::string& a_val);
void daWrite2StringLine(std::ostream& a_outStream,
                        const char* a_name,
                        const std::string& a_val1,
                        const std::string& a_val2);
void daWrite3StringLine(std::ostream& a_outStream,
                        const char* a_name,
                        const std::string& a_val1,
                        const std::string& a_val2,
                        const std::string& a_val3);

} // namespace xms
