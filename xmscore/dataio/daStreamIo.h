#pragma once
//------------------------------------------------------------------------------
/// \file
/// \ingroup dataio
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
// 3. Standard Library Headers
#include <sstream>

// 4. External Library Headers

// 5. Shared Headers
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

//----- Function prototypes ----------------------------------------------------

bool daReadNamedLine(std::istream& a_inStream, const char* a_name);
bool daReadLine(std::istream& a_inStream, std::string& a_line);
bool daReadIntLine(std::istream& a_inStream, const char* a_name, int& a_val);
bool daReadIntFromLine(std::string& a_line, int& a_val);
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

void daWriteVecInt(std::ostream& a_outStream, const char* a_name, const VecInt& a_vec);
void daWriteVecDbl(std::ostream& a_outStream, const char* a_name, const VecDbl& a_vec);
void daWriteVecPt3d(std::ostream& a_outStream, const char* a_name, const VecPt3d& a_vec);

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
