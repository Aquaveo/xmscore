//------------------------------------------------------------------------------
/// \file
/// \ingroup misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmscore/misc/DynBitset.h>

// 3. Standard library headers

// 4. External library headers

// 5. Shared code headers

// 6. Non-shared code headers

//----- Forward declarations ---------------------------------------------------

//----- External globals -------------------------------------------------------

//----- Namespace declaration --------------------------------------------------
namespace xms
{
//----- Constants / Enumerations -----------------------------------------------

//----- Classes / Structs ------------------------------------------------------

//----- Internal functions -----------------------------------------------------

//----- Class / Function definitions -------------------------------------------

//------------------------------------------------------------------------------
/// \brief Convert from a VecBoolean to a DynBitset.
/// \param[in]  a_from: VecBoolean array in.
/// \param[out] a_to: DynBitset out.
//------------------------------------------------------------------------------
void VecBooleanToDynBitset(const std::vector<unsigned char>& a_from, DynBitset& a_to)
{
  a_to.resize(a_from.size());
  for (size_t i = 0; i < a_from.size(); ++i)
  {
    a_to[i] = a_from[i] != 0;
  }
} // VecBooleanToDynBitset
//------------------------------------------------------------------------------
/// \brief Convert from a DynBitset to a VecBoolean.
/// \param[in]  a_from: DynBitset array in.
/// \param[out] a_to: VecBoolean out.
//------------------------------------------------------------------------------
void DynBitsetToVecBoolean(const DynBitset& a_from, std::vector<unsigned char>& a_to)
{
  a_to.clear();
  a_to.reserve(a_from.size());
  for (size_t i = 0; i < a_from.size(); ++i)
  {
    a_to.push_back(a_from[i]);
  }
} // DynBitsetToVecBoolean

} // namespace xms

#if CXX_TEST
////////////////////////////////////////////////////////////////////////////////
// TESTS
////////////////////////////////////////////////////////////////////////////////

#include <xmscore/misc/DynBitset.t.h>

using namespace xms;

////////////////////////////////////////////////////////////////////////////////
/// \class DynBitsetUnitTests
/// \brief Unit tests for the DynBitset conversion free functions.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Verify VecBooleanToDynBitset copies values and treats any
///        non-zero byte as ``true`` while exactly-zero stays ``false``.
//------------------------------------------------------------------------------
void DynBitsetUnitTests::testVecBooleanToDynBitset()
{
  // Empty input round-trips to an empty bitset (covers the size==0 branch).
  {
    std::vector<unsigned char> empty;
    DynBitset bs;
    VecBooleanToDynBitset(empty, bs);
    TS_ASSERT_EQUALS(0u, bs.size());
  }
  // Mixed input: 0 stays false; both 1 and 255 are coerced to true.
  {
    std::vector<unsigned char> in = {0, 1, 0, 255, 2};
    DynBitset bs;
    VecBooleanToDynBitset(in, bs);
    TS_ASSERT_EQUALS(5u, bs.size());
    TS_ASSERT(!bs[0]);
    TS_ASSERT(bs[1]);
    TS_ASSERT(!bs[2]);
    TS_ASSERT(bs[3]);
    TS_ASSERT(bs[4]);
  }
  // A pre-sized DynBitset is resized to match the input length.
  {
    std::vector<unsigned char> in = {1, 0};
    DynBitset bs(10);
    VecBooleanToDynBitset(in, bs);
    TS_ASSERT_EQUALS(2u, bs.size());
    TS_ASSERT(bs[0]);
    TS_ASSERT(!bs[1]);
  }
} // DynBitsetUnitTests::testVecBooleanToDynBitset
//------------------------------------------------------------------------------
/// \brief Verify DynBitsetToVecBoolean produces a vector matching the
///        bitset's contents and clears any pre-existing destination data.
//------------------------------------------------------------------------------
void DynBitsetUnitTests::testDynBitsetToVecBoolean()
{
  // Empty bitset produces an empty vector.
  {
    DynBitset bs;
    std::vector<unsigned char> out;
    DynBitsetToVecBoolean(bs, out);
    TS_ASSERT_EQUALS(0u, out.size());
  }
  // Populated bitset produces a vector of 0/1 bytes in order.
  {
    DynBitset bs(4);
    bs[0] = true;
    bs[1] = false;
    bs[2] = true;
    bs[3] = true;
    std::vector<unsigned char> out;
    DynBitsetToVecBoolean(bs, out);
    std::vector<unsigned char> expected = {1, 0, 1, 1};
    TS_ASSERT_EQUALS(expected, out);
  }
  // Pre-populated destination is cleared before being filled.
  {
    DynBitset bs(2);
    bs[0] = false;
    bs[1] = true;
    std::vector<unsigned char> out = {42, 42, 42, 42};
    DynBitsetToVecBoolean(bs, out);
    std::vector<unsigned char> expected = {0, 1};
    TS_ASSERT_EQUALS(expected, out);
  }
} // DynBitsetUnitTests::testDynBitsetToVecBoolean
//------------------------------------------------------------------------------
/// \brief Round-trip the two functions to confirm they are inverses on
///        canonical (0/1) inputs.
//------------------------------------------------------------------------------
void DynBitsetUnitTests::testRoundTrip()
{
  std::vector<unsigned char> original = {0, 1, 1, 0, 1, 0, 0, 1};
  DynBitset bs;
  VecBooleanToDynBitset(original, bs);
  std::vector<unsigned char> result;
  DynBitsetToVecBoolean(bs, result);
  TS_ASSERT_EQUALS(original, result);
} // DynBitsetUnitTests::testRoundTrip

#endif

