//------------------------------------------------------------------------------
/// \file
/// \ingroup misc/detail
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmscore/python/misc/detail/Listener.h>

// 3. Standard library headers
#include <chrono>

// 4. External library headers

// 5. Shared code headers
#include <xmscore/misc/XmError.h>

// 6. Non-shared code headers
#include <xmscore/python/misc/PublicProgressListener.h>
#include <xmscore/stl/vector.h>

//----- Forward declarations ---------------------------------------------------

//----- External globals -------------------------------------------------------

//----- Namespace declaration --------------------------------------------------
namespace xms
{
//----- Constants / Enumerations -----------------------------------------------

//----- Classes / Structs ------------------------------------------------------

//----- Internal functions -----------------------------------------------------

//----- Class / Function definitions -------------------------------------------

using namespace std::chrono;

////////////////////////////////////////////////////////////////////////////////
/// \class Listener::impl
/// \brief Implementation of the ProgressListener class. This is used in the
/// python interface.
////////////////////////////////////////////////////////////////////////////////
class Listener::impl
{
public:
  impl(PublicProgressListener* a_, int a_updateDelaySeconds)
  : m_parent(a_)
  , m_delay(a_updateDelaySeconds){}

  PublicProgressListener* m_parent; ///< parent class that holds this instance
  int m_delay;                      ///< time to delay messages in seconds
  VecStr m_operations;              ///< vector of the "begin operation" strings
  ///< time used for delaying messages so we are not so chatty
  steady_clock::time_point m_lastMsgTime;
};

////////////////////////////////////////////////////////////////////////////////
/// \class Listener
/// \brief Implementation of the ProgressListener class. This is used in the
/// python interface.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Constructor
/// \param[in] a_parent: the parent class
/// \param[in] a_updateDelaySeconds: time for delay in updating
//------------------------------------------------------------------------------
Listener::Listener(PublicProgressListener *a_, int a_updateDelaySeconds /*3*/)
: m_p(new Listener::impl(a_, a_updateDelaySeconds))
{
} // Listener::Listener
//------------------------------------------------------------------------------
/// \brief Destructor
//------------------------------------------------------------------------------
Listener::~Listener()
{
  try
  {
    delete(m_p);
    m_p = nullptr;
  }
  catch (...)
  {
  }
} // Listener::~Listener
//------------------------------------------------------------------------------
/// \brief Set the update delay
/// \param[in] a_delay: time for delay in message updating
//------------------------------------------------------------------------------
void Listener::SetUpdateDelaySeconds(int a_delay)
{
  m_p->m_delay = a_delay;
} // Listener::SetUpdateDelaySeconds
//------------------------------------------------------------------------------
/// \brief Listen to progress status
/// \param[in] a_stackIndex: the ID for progress stack (0 for first)
/// \param[in] a_fractionComplete: amount complete from 0.0 to 1.0
//------------------------------------------------------------------------------
void Listener::OnProgressStatus(int a_stackIndex, double a_fractionComplete)
{
  auto t = steady_clock::now();
  int elapsed = (int)duration_cast<seconds>(t - m_p->m_lastMsgTime).count();
  if (elapsed >= m_p->m_delay)
  {
    m_p->m_parent->on_progress_status(a_stackIndex, a_fractionComplete);
    m_p->m_lastMsgTime = t;
  }
} // Listener::OnProgressStatus
//------------------------------------------------------------------------------
/// \brief Listen to when operation begins
/// \param[in] a_operation: the name of the operation
/// \return the ID for progress stack (0 for first)
//------------------------------------------------------------------------------
int Listener::OnBeginOperationString(const std::string& a_operation)
{
  m_p->m_lastMsgTime = steady_clock::now();
  m_p->m_operations.push_back(a_operation);
  m_p->m_parent->on_begin_operation_string(a_operation);
  return static_cast<int>(m_p->m_operations.size());
} // Listener::OnBeginOperationString
//------------------------------------------------------------------------------
/// \brief Listen to when operation ends
/// \param[in] a_stackIndex: the ID for progress stack (0 for first)
//------------------------------------------------------------------------------
void Listener::OnEndOperation(int a_stackIndex)
{
  m_p->m_lastMsgTime = steady_clock::now();
  m_p->m_parent->on_end_operation(a_stackIndex);
  if (!m_p->m_operations.empty())
    m_p->m_operations.pop_back();
} // Listener::OnEndOperation
//------------------------------------------------------------------------------
/// \brief Listen to when operation ends
/// \param[in] a_stackIndex: the ID for progress stack (0 for first)
/// \param[in] a_message: the new message for an operation
//------------------------------------------------------------------------------
void Listener::OnUpdateMessage(int a_stackIndex, const std::string& a_message)
{
  auto t = steady_clock::now();
  int elapsed = (int)duration_cast<seconds>(t - m_p->m_lastMsgTime).count();
  if (elapsed >= m_p->m_delay)
  {
    m_p->m_parent->on_update_message(a_stackIndex, a_message);
    m_p->m_lastMsgTime = t;
  }
} // Listener::OnUpdateMessage

} // namespace xms