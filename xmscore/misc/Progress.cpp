//------------------------------------------------------------------------------
/// \file
/// \ingroup misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmscore/misc/Progress.h>

// 3. Standard library headers

// 4. External library headers

// 5. Shared code headers
#include <xmscore/misc/XmError.h>

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
/// \brief Get the current ProgressListener
/// \return the current ProgressListener
//------------------------------------------------------------------------------
BSHP<ProgressListener>& iListener()
{
  static BSHP<ProgressListener> fg_listener;
  return fg_listener;
} // iListener

////////////////////////////////////////////////////////////////////////////////
/// \class Progress
/// \brief Stack based class to give notification of progress for a long task.
///        Progress can be stacked by making multiple instances of Progress
///        going down the call chain.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Constructor
/// \param[in] a_message: the new message for an operation
//------------------------------------------------------------------------------
Progress::Progress(const std::string& a_message)
: m_stackIndex(0)
, m_itemCount(0)
{
  if (iListener())
  {
    m_stackIndex = iListener()->OnBeginOperationString(a_message);
  }
} // Progress::Progress
//------------------------------------------------------------------------------
/// \brief Destructor
//------------------------------------------------------------------------------
Progress::~Progress()
{
  if (iListener())
  {
    iListener()->OnEndOperation(m_stackIndex);
  }
} // Progress::~Progress
//------------------------------------------------------------------------------
/// \brief Update the current progress message.
/// \param[in] a_message: the new message for an operation
//------------------------------------------------------------------------------
void Progress::UpdateMessage(const std::string& a_message)
{
  if (iListener())
  {
    iListener()->OnUpdateMessage(m_stackIndex, a_message);
  }
} // Progress::UpdateMessage
//------------------------------------------------------------------------------
/// \brief Set the number of items to be processed. Used with CurrentItem.
/// \param[in] a_count: the number of items to be processed
//------------------------------------------------------------------------------
void Progress::SetItemCount(long long a_count)
{
  m_itemCount = a_count;
} // Progress::SetItemCount
//------------------------------------------------------------------------------
/// \brief Give notification for the number of items completed. Used with
///        SetItemCount.
/// \param[in] a_item: the current item being processed
//------------------------------------------------------------------------------
void Progress::CurrentItem(long long a_item)
{
  XM_ASSERT(m_itemCount != 0);
  if (iListener() && m_itemCount)
  {
    if (a_item < m_itemCount)
      ++a_item;
    iListener()->OnProgressStatus(m_stackIndex, (double)a_item / m_itemCount);
  }
} // Progress::CurrentItem
//------------------------------------------------------------------------------
/// \brief Give notification for the progress percent complete.
/// \param[in] a_fractionComplete: amount complete from 0.0 to 1.0
//------------------------------------------------------------------------------
void Progress::ProgressStatus(double a_fractionComplete)
{
  // should use either this alone or SetItemCount/CurrentItem
  XM_ASSERT(m_itemCount == 0);

  if (iListener())
  {
    iListener()->OnProgressStatus(m_stackIndex, a_fractionComplete);
  }
} // Progress::ProgressStatus

//------------------------------------------------------------------------------
/// \brief Destructor
//------------------------------------------------------------------------------
ProgressListener::~ProgressListener()
{
} // ProgressListener::~ProgressListener
//------------------------------------------------------------------------------
/// \brief Set the current progress listener.
/// \param[in] a_listener: the listener progress notifications sent to.
//------------------------------------------------------------------------------
void ProgressListener::SetListener(BSHP<ProgressListener> a_listener)
{
  iListener() = a_listener;
} // ProgressListener::SetListener
//------------------------------------------------------------------------------
/// \brief Get the current progress listener.
/// \return the current progress listener
//------------------------------------------------------------------------------
BSHP<ProgressListener> ProgressListener::GetListener()
{
  return iListener();
} // ProgressListener::GetListener

} // namespace xms

#ifdef CXX_TEST
#include <xmscore/misc/Progress.t.h>
#include <sstream>

using namespace xms;

/// \brief mock class to show how the Progress and ProgressListener
///        classes work
class MockProgressListener : public ProgressListener
{
public:
  MockProgressListener() {}
  ~MockProgressListener() {}

  //------------------------------------------------------------------------------
  /// \brief Listen to progress status
  /// \param[in] a_stackIndex: the ID for progress stack (0 for first)
  /// \param[in] a_fractionComplete: amount complete from 0.0 to 1.0
  //------------------------------------------------------------------------------
  void OnProgressStatus(int a_stackIndex, double a_fractionComplete) override
  {
    std::ostringstream ss;
    ss << "OnProgressStatus " << a_stackIndex << ": " << a_fractionComplete << '\n';
    m_messages += ss.str();
  }
  //------------------------------------------------------------------------------
  /// \brief Listen to when operation begins
  /// \param[in] a_operation: the name of the operation
  /// \return the ID for progress stack (0 for first)
  //------------------------------------------------------------------------------
  int OnBeginOperationString(const std::string& a_operation) override
  {
    ++m_stackIndex;
    std::ostringstream ss;
    ss << "OnBeginOperationString " << a_operation << '\n';
    m_messages += ss.str();
    return m_stackIndex;
  }

  //------------------------------------------------------------------------------
  /// \brief Listen to when operation ends
  /// \param[in] a_stackIndex: the ID for progress stack (0 for first)
  //------------------------------------------------------------------------------
  void OnEndOperation(int a_stackIndex) override
  {
    --m_stackIndex;
    std::ostringstream ss;
    ss << "OnEndOperation " << a_stackIndex << '\n';
    m_messages += ss.str();
  }

  //------------------------------------------------------------------------------
  /// \brief Listen to when operation ends
  /// \param[in] a_stackIndex: the ID for progress stack (0 for first)
  /// \param[in] a_message: the new message for an operation
  //------------------------------------------------------------------------------
  void OnUpdateMessage(int a_stackIndex, const std::string& a_message) override
  {
    std::ostringstream ss;
    ss << "OnUpdateMessage " << a_stackIndex << ": " << a_message << '\n';
    m_messages += ss.str();
  }

  std::string m_messages; ///< stored up messages
  int m_stackIndex = 0;   ///< the size of the progess stack
};
////////////////////////////////////////////////////////////////////////////////
/// \class ProgressUnitTests
/// \brief Tests for Progress.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Test Progress class.
//------------------------------------------------------------------------------
void ProgressUnitTests::testProgress()
{
  BSHP<ProgressListener> old = ProgressListener::GetListener();
  BSHP<MockProgressListener> listener(new MockProgressListener);
  ProgressListener::SetListener(listener);
  {
    Progress p1("First progress");
    p1.ProgressStatus(0.5);
    {
      {
        Progress p2("Second progress");
        p2.ProgressStatus(0.25);
        p2.UpdateMessage("Second progress message 2");
        p2.ProgressStatus(0.75);
      }
      {
        Progress p3("Third progress");
        p3.SetItemCount(4);
        p3.CurrentItem(0);
        p3.CurrentItem(1);
        p3.CurrentItem(2);
        p3.CurrentItem(3);
      }
    }
    p1.ProgressStatus(1.0);
  }

  std::string expected =
    "OnBeginOperationString First progress\n"
    "OnProgressStatus 1: 0.5\n"
    "OnBeginOperationString Second progress\n"
    "OnProgressStatus 2: 0.25\n"
    "OnUpdateMessage 2: Second progress message 2\n"
    "OnProgressStatus 2: 0.75\n"
    "OnEndOperation 2\n"
    "OnBeginOperationString Third progress\n"
    "OnProgressStatus 2: 0.25\n"
    "OnProgressStatus 2: 0.5\n"
    "OnProgressStatus 2: 0.75\n"
    "OnProgressStatus 2: 1\n"
    "OnEndOperation 2\n"
    "OnProgressStatus 1: 1\n"
    "OnEndOperation 1\n";
  TS_ASSERT_EQUALS(expected, listener->m_messages);
  ProgressListener::SetListener(old);
} // ProgressUnitTests::testProgress

#endif
