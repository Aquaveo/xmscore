//------------------------------------------------------------------------------
/// \file
/// \ingroup misc/detail
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmscore/python/misc/PublicProgressListener.h>

// 3. Standard library headers

// 4. External library headers

// 5. Shared code headers
#include <xmscore/misc/XmError.h>

// 6. Non-shared code headers
#include <xmscore/misc/Progress.h>
#include <xmscore/python/misc/detail/Listener.h>

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
/// \class PublicProgressListener::impl
/// \brief Implementation of the ProgressListener class. This is used in the
/// python interface.
////////////////////////////////////////////////////////////////////////////////
class PublicProgressListener::impl
{
public:
  impl(PublicProgressListener *a_) :
    m_child(new Listener(a_))
  {
    ProgressListener::SetListener(m_child);
  }

  BSHP<Listener> m_child;
};

////////////////////////////////////////////////////////////////////////////////
/// \class PublicProgressListener
/// \brief Implementation of the ProgressListener class. This is used in the
/// python interface.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Constructor
/// \param[in] a_parent: the parent class
//------------------------------------------------------------------------------
PublicProgressListener::PublicProgressListener() :
  m_p(new PublicProgressListener::impl(this))
{
} // Listener::Listener
//------------------------------------------------------------------------------
/// \brief Destructor
//------------------------------------------------------------------------------
PublicProgressListener::~PublicProgressListener()
{
  try
  {
    if (m_p)
      delete(m_p);
    m_p = nullptr;
  }
  catch (...) {}
} // PublicProgressListener::~PublicProgressListener

} // namespace xms