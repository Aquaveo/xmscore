#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief an Observer class with public virtual methods.
///
///        This is necessary for the Python bindings. Python isn't able to
///        override methods that aren't public.
/// \ingroup
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

// 3. Standard Library Headers

// 4. External Library Headers
#include <xmscore/misc/boost_defines.h>
#include <xmscore/misc/Progress.h>

// 5. Shared Headers

// 6. Non-shared Headers

//----- Namespace declaration --------------------------------------------------
namespace xms
{

class PublicProgressListener
{
public:
  PublicProgressListener();
  virtual ~PublicProgressListener();

  /* Virtual methods called by overrides of Observer virtual methods */
  virtual void on_progress_status(int a_stackIndex, double a_percentComplete) {}
  virtual int on_begin_operation_string(const std::string& a_operation) { return 0; }
  virtual void on_end_operation(int a_stackIndex) {}
  virtual void on_update_message(int a_stackIndex, const std::string& a_message) {}

private:
  class impl;
  impl *m_p;
};

} // namespace xms