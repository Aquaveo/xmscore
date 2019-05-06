//------------------------------------------------------------------------------
// \file
// \copyright (C) Copyright Aquaveo 2019.
//------------------------------------------------------------------------------
#pragma once

//----- Included files ---------------------------------------------------------
// 3. Standard Library Headers

// 4. External Library Headers
#include <cxxtest/TestSuite.h>

// 5. Shared Headers

// 6. Non-shared Headers

//----- Namespace declaration --------------------------------------------------

//----- Forward declarations ---------------------------------------------------

//----- Structs / Classes ------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
class CoUtilsIoUnitTests : public CxxTest::TestSuite
{
public:
  void testReadWriteLine();
  void testReadWriteStringLine();
  void testReadWrite2StringLine();
  void testReadWrite3StringLine();
  void testReadWriteIntLine();
  void testReadWriteDoubleLine();
  void testReadWrite3DoubleLine();
  void testReadWriteVecInt();
  void testReadWriteVecDbl();
  void testReadWriteVecPt3d();
}; // CoQuadtreeGridUnitTests
