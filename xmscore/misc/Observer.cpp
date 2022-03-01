//------------------------------------------------------------------------------
/// \file
/// \ingroup misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmscore/misc/Observer.h>

// 3. Standard library headers

// 4. External library headers
#pragma warning(push)
#pragma warning(disable : 4103)
#include <boost/timer/timer.hpp>
#pragma warning(pop)

// 5. Shared code headers
#include <xmscore/locale/locale.h>

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
/// \brief Implementation of the observer class
class Observer::impl
{
public:
  impl()
  : m_percentComplete(0)
  {
  }
  ~impl() {}

  void BeginOperationString();
  void EndOperation();
  double ElapsedTimeInSeconds();
  double EstimatedTimeRemainingInSec(double a_percentComplete, double a_elapsedTime);

  boost::timer::cpu_timer m_timer; ///< timer to get elapsed time
  double m_percentComplete;        ///< percent complete
};

//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
Observer::Observer()
: m_p(new Observer::impl())
{
}
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
Observer::~Observer()
{
}
//------------------------------------------------------------------------------
/// \brief Method to publish the progress status
/// \param a_percentComplete The percentage complete for the current operation
/// \return returns whether the ProgressBar actually updates.
//------------------------------------------------------------------------------
bool Observer::ProgressStatus(double a_percentComplete)
{
  if (a_percentComplete > m_p->m_percentComplete + .02)
  {
    double elapsedTime = m_p->ElapsedTimeInSeconds();
    m_p->m_percentComplete = a_percentComplete;
    OnProgressStatus(a_percentComplete);

    TimeElapsedInSeconds(elapsedTime);
    double rem = m_p->EstimatedTimeRemainingInSec(a_percentComplete, elapsedTime);
    TimeRemainingInSeconds(rem);
    return true;
  }
  return false;
} // Observer::ProgressStatus
//------------------------------------------------------------------------------
/// \brief Virtual method to publish the time remaining
/// \param a_remainingSeconds: The time remaining for the current operation
/// that the class is observing.
//------------------------------------------------------------------------------
void Observer::TimeRemainingInSeconds(double a_remainingSeconds)
{
  (void)a_remainingSeconds;
} // Observer::TimeRemainingInSeconds
//------------------------------------------------------------------------------
/// \brief Virtual method to publish the elasped time
/// \param a_elapsedSeconds: The elapsed time since the operation began.
//------------------------------------------------------------------------------
void Observer::TimeElapsedInSeconds(double a_elapsedSeconds)
{
  (void)a_elapsedSeconds;
} // Observer::TimeElapsedInSeconds
//------------------------------------------------------------------------------
/// \brief Publishes the name of the operation and starts the timing of
/// the operation.
/// \param a_operation String identifying the name of the operation that is
/// being observed by this class.
//------------------------------------------------------------------------------
void Observer::BeginOperationString(const std::string& a_operation)
{
  m_p->BeginOperationString();
  OnBeginOperationString(a_operation);
  ProgressStatus(0.0);
} // Observer::BeginOperationString
//------------------------------------------------------------------------------
/// \brief Ends the operation.
//------------------------------------------------------------------------------
void Observer::EndOperation()
{
  m_p->EndOperation();
  OnEndOperation();
  ProgressStatus(0.0);
} // Observer::EndOperation
//------------------------------------------------------------------------------
/// \brief Updates the message but not the percent complete.
/// \param[in] a_message: The new message.
//------------------------------------------------------------------------------
void Observer::UpdateMessage(const std::string& a_message)
{
  OnUpdateMessage(a_message);
}
//------------------------------------------------------------------------------
/// \brief Virtual function for derived class to get the operation string.
/// \param a_operation String identifying the name of the operation that is
/// being observed by this class.
//------------------------------------------------------------------------------
void Observer::OnBeginOperationString(const std::string& a_operation)
{
  (void)a_operation;
} // Observer::OnBeginOperationString
//------------------------------------------------------------------------------
/// \brief Virtual function for derived class to get end operation event.
//------------------------------------------------------------------------------
void Observer::OnEndOperation()
{
} // Observer::OnEndOperation
//------------------------------------------------------------------------------
/// virtual function to be notified that the message has been set
/// \param[in] a_message: The new message.
//------------------------------------------------------------------------------
void Observer::OnUpdateMessage(const std::string& a_message)
{
  (void)a_message; // For Doxygen
} // Observer::OnUpdateMessage
//------------------------------------------------------------------------------
/// \brief Starts the timer to know the elapsed time for the operation and
/// to estimate the time remaining.
//------------------------------------------------------------------------------
void Observer::impl::BeginOperationString()
{
  m_timer.start();
  m_percentComplete = 0;
} // Observer::impl::BeginOperationString
//------------------------------------------------------------------------------
/// \brief Stops the timer.
//------------------------------------------------------------------------------
void Observer::impl::EndOperation()
{
  m_timer.stop();
} // Observer::impl::EndOperation
//------------------------------------------------------------------------------
/// \brief Returns the elapsed time for the operation being observed.
/// \return Elapsed time in seconds.
//------------------------------------------------------------------------------
double Observer::impl::ElapsedTimeInSeconds()
{
  boost::timer::cpu_times const elapsed_times(m_timer.elapsed());
  boost::timer::nanosecond_type time = elapsed_times.wall;
  const double NANO_PER_SEC = 1e9;
  double seconds = time / NANO_PER_SEC;
  return seconds;
} // Observer::impl::ElapsedTimeInSeconds
//------------------------------------------------------------------------------
/// \brief Returns the elapsed time for the operation being observed.
/// \param a_percentComplete: The percent complete between 0.0 and 1.0.
/// \param a_elapsedTime: ???
/// \return Elapsed time in seconds.
//------------------------------------------------------------------------------
double Observer::impl::EstimatedTimeRemainingInSec(double a_percentComplete, double a_elapsedTime)
{
  if (a_percentComplete < .01)
    return 60;

  double percentRemaining = 1 - a_percentComplete;
  double timeRemaining = (a_elapsedTime * percentRemaining) / a_percentComplete;
  return timeRemaining;
} // Observer::impl::EstimatedTimeRemainingInSec

} // namespace xms

#ifdef CXX_TEST
#include <xmscore/misc/Observer.t.h>

#include <boost/thread/thread.hpp>

#include <xmscore/math/math.h>
#include <xmscore/testing/TestTools.h>

////////////////////////////////////////////////////////////////////////////////
/// \brief Derived class used for testing use of Observer class
class MockObserver : public xms::Observer
{
public:
  double m_percentComplete, ///< percent complete
    m_remainingSeconds,     ///< seconds remaining
    m_elapsedSeconds;       ///< seconds elapsed
  std::stringstream m_info; ///< string info captured by the class

private:
  //------------------------------------------------------------------------------
  /// \brief captures the progress of an operation
  /// \param a_percentComplete: The percent complete.
  //------------------------------------------------------------------------------
  virtual void OnProgressStatus(double a_percentComplete) override
  {
    m_percentComplete = a_percentComplete;
    int i = (int)(xms::Round(m_percentComplete * 100));
    std::string message = N_( "Percent complete: {1}%.\n");
    m_info << xms::stCFormat(message, i);
  }
  //------------------------------------------------------------------------------
  /// \param a_operation name of the operation being monitored
  //------------------------------------------------------------------------------
  virtual void OnBeginOperationString(const std::string& a_operation) override
  {
    if (!m_info.str().empty())
    {
      m_info << '\n';
    }
    std::string message = N_("Begin operation: {1}.\n");
    m_info << xms::stCFormat(message, a_operation);
  }
  //------------------------------------------------------------------------------
  /// \param a_elapsedSeconds The elapsed time since the operation began.
  //------------------------------------------------------------------------------
  virtual void TimeElapsedInSeconds(double a_elapsedSeconds) override
  {
    m_elapsedSeconds = a_elapsedSeconds;
    int i = (int)(xms::Round(m_elapsedSeconds * 10));
    std::string message = N_("Elapsed seconds: 0.{1}.\n");
    m_info << xms::stCFormat(message, i);
  }

  //------------------------------------------------------------------------------
  /// \param a_secondsRemaining The time remaining for the current operation
  /// that the class is observing.
  //------------------------------------------------------------------------------
  virtual void TimeRemainingInSeconds(double a_secondsRemaining) override
  {
    m_remainingSeconds = a_secondsRemaining;
    int i = (int)(xms::Round(m_remainingSeconds * 10));
    std::string message = N_("Time remaining (seconds): 0.{1}.\n");
    m_info << xms::stCFormat(message, i);
  }
};
/// \brief mock meshing class to show how the observer works
class MockMesher
{
public:
  MockMesher() {}
  ~MockMesher() {}

  //------------------------------------------------------------------------------
  /// \brief set the observer class
  /// \param a_ The observer
  //------------------------------------------------------------------------------
  void SetObserver(BSHP<xms::Observer> a_) { m_prog = a_; }
  //------------------------------------------------------------------------------
  /// \brief wait until next tenth second passed
  /// \param a_timer Timer to track elapsed time
  /// \param a_count Number of tenths of a second that should have elapsed
  //------------------------------------------------------------------------------
  void WaitForNextTenthSecond(boost::timer::cpu_timer& a_timer, int& a_count)
  {
    ++a_count;
    const long long tenth_second = 100000000LL;
    while (a_timer.elapsed().wall < tenth_second * a_count)
    {
    }
    // boost::this_thread::sleep(boost::posix_time::millisec(100));
  }
  /// mock meshing method
  //------------------------------------------------------------------------------
  /// \brief
  //------------------------------------------------------------------------------
  void PretendMeshing()
  {
    if (!m_prog)
      return;

    boost::timer::cpu_timer timer;
    int count = 0;

    m_prog->BeginOperationString(N_("Generating mesh points"));
    for (int i = 0; i < 4; ++i)
    {
      WaitForNextTenthSecond(timer, count);
      m_prog->ProgressStatus((double)(i + 1) / 4);
    }

    m_prog->BeginOperationString(N_("Triangulating"));
    for (int i = 0; i < 5; ++i)
    {
      WaitForNextTenthSecond(timer, count);
      m_prog->ProgressStatus((double)(i + 1) / 5);
    }

    m_prog->BeginOperationString(N_("Generating unstructured grid"));
    for (int i = 0; i < 3; ++i)
    {
      WaitForNextTenthSecond(timer, count);
      m_prog->ProgressStatus((double)(i + 1) / 3);
    }
  }

  BSHP<xms::Observer> m_prog; ///< observer class to report progress
};
////////////////////////////////////////////////////////////////////////////////
/// \class ObserverIntermediateTests
/// \brief Tests for Observer.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief    Defines the test group.
/// \return CxxTest::TestGroup reference.
//------------------------------------------------------------------------------
#ifndef CXXTEST4
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
const CxxTest::TestGroup& ObserverIntermediateTests::group()
{
  return *CxxTest::TestGroup::GetGroup(CxxTest::TG_INTERMEDIATE);
  // return CxxTest::TestSuite::group();
} // ObserverIntermediateTests::group
#endif
//------------------------------------------------------------------------------
/// \brief tests the estimated time remaining
//------------------------------------------------------------------------------
void ObserverIntermediateTests::testTimeRemaining()
{
  MockObserver o;
  o.BeginOperationString(N_("Test Operation"));
  boost::this_thread::sleep(boost::posix_time::millisec(100));
  o.ProgressStatus(.2);
  double remaining = (o.m_elapsedSeconds * .8) / .2;
  const double DELTA = 1e-5;
  TS_ASSERT_DELTA(remaining, o.m_remainingSeconds, DELTA);
} // ObserverIntermediateTests::testTimeRemaining
//! [snip_test_Example_Observer]
//------------------------------------------------------------------------------
/// \brief tests an example observer implementation
//------------------------------------------------------------------------------
void ObserverIntermediateTests::testMockObserver()
{
  // create an object derived off of Observer
  BSHP<MockObserver> p(new MockObserver());
  // create a mock meshing class
  MockMesher m;
  // set the observer on the mesher
  m.SetObserver(p);
  // execute the mesher
  m.PretendMeshing();
  // capture the output from the observer class and verify it
  std::string outStr(p->m_info.str());
  std::string baseStr = N_(
    "Begin operation: Generating mesh points.\n"
    "Percent complete: 25%.\n"
    "Elapsed seconds: 0.1.\n"
    "Time remaining (seconds): 0.3.\n"
    "Percent complete: 50%.\n"
    "Elapsed seconds: 0.2.\n"
    "Time remaining (seconds): 0.2.\n"
    "Percent complete: 75%.\n"
    "Elapsed seconds: 0.3.\n"
    "Time remaining (seconds): 0.1.\n"
    "Percent complete: 100%.\n"
    "Elapsed seconds: 0.4.\n"
    "Time remaining (seconds): 0.0.\n"
    "\n"
    "Begin operation: Triangulating.\n"
    "Percent complete: 20%.\n"
    "Elapsed seconds: 0.1.\n"
    "Time remaining (seconds): 0.4.\n"
    "Percent complete: 40%.\n"
    "Elapsed seconds: 0.2.\n"
    "Time remaining (seconds): 0.3.\n"
    "Percent complete: 60%.\n"
    "Elapsed seconds: 0.3.\n"
    "Time remaining (seconds): 0.2.\n"
    "Percent complete: 80%.\n"
    "Elapsed seconds: 0.4.\n"
    "Time remaining (seconds): 0.1.\n"
    "Percent complete: 100%.\n"
    "Elapsed seconds: 0.5.\n"
    "Time remaining (seconds): 0.0.\n"
    "\n"
    "Begin operation: Generating unstructured grid.\n"
    "Percent complete: 33%.\n"
    "Elapsed seconds: 0.1.\n"
    "Time remaining (seconds): 0.2.\n"
    "Percent complete: 67%.\n"
    "Elapsed seconds: 0.2.\n"
    "Time remaining (seconds): 0.1.\n"
    "Percent complete: 100%.\n"
    "Elapsed seconds: 0.3.\n"
    "Time remaining (seconds): 0.0.\n");
  TS_ASSERT_EQUALS(baseStr, outStr);
} // ObserverIntermediateTests::testMockObserver
  //! [snip_test_Example_Observer]

#endif
