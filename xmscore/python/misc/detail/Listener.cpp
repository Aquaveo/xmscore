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

// 4. External library headers

// 5. Shared code headers
#include <xmscore/misc/XmError.h>

// 6. Non-shared code headers
#include <xmscore/python/misc/PublicProgressListener.h>

//----- Forward declarations ---------------------------------------------------

//----- External globals -------------------------------------------------------

//----- Namespace declaration --------------------------------------------------
namespace xms
{
//----- Constants / Enumerations -----------------------------------------------

//----- Classes / Structs ------------------------------------------------------

//----- Internal functions -----------------------------------------------------

//----- Class / Function definitions -------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// \class Listener
/// \brief Implementation of the ProgressListener class. This is used in the
/// python interface.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Constructor
/// \param[in] a_parent: the parent class
//------------------------------------------------------------------------------
Listener::Listener(PublicProgressListener *a_)
: m_parent(a_),
  m_stackIndex(-1)
{
} // Listener::Listener
//------------------------------------------------------------------------------
/// \brief Destructor
//------------------------------------------------------------------------------
Listener::~Listener()
{
} // Listener::~Listener
//------------------------------------------------------------------------------
/// \brief Listen to progress status
/// \param[in] a_stackIndex: the ID for progress stack (0 for first)
/// \param[in] a_fractionComplete: amount complete from 0.0 to 1.0
//------------------------------------------------------------------------------
void Listener::OnProgressStatus(int a_stackIndex, double a_fractionComplete)
{
  m_parent->on_progress_status(a_stackIndex, a_fractionComplete);
} // Listener::OnProgressStatus
//------------------------------------------------------------------------------
/// \brief Listen to when operation begins
/// \param[in] a_operation: the name of the operation
/// \return the ID for progress stack (0 for first)
//------------------------------------------------------------------------------
int Listener::OnBeginOperationString(const std::string& a_operation)
{
  m_stackIndex++;
  m_parent->on_begin_operation_string(a_operation);
  return m_stackIndex;
} // Listener::OnBeginOperationString
//------------------------------------------------------------------------------
/// \brief Listen to when operation ends
/// \param[in] a_stackIndex: the ID for progress stack (0 for first)
//------------------------------------------------------------------------------
void Listener::OnEndOperation(int a_stackIndex)
{
  m_parent->on_end_operation(a_stackIndex);
  if (m_stackIndex > 0)
    m_stackIndex--;
} // Listener::OnEndOperation
//------------------------------------------------------------------------------
/// \brief Listen to when operation ends
/// \param[in] a_stackIndex: the ID for progress stack (0 for first)
/// \param[in] a_message: the new message for an operation
//------------------------------------------------------------------------------
void Listener::OnUpdateMessage(int a_stackIndex, const std::string& a_message)
{
  m_parent->on_update_message(a_stackIndex, a_message);
} // Listener::OnUpdateMessage

} // namespace xms