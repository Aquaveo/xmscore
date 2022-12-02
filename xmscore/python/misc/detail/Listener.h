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
#include <xmscore/misc/Progress.h>

// 5. Shared Headers

// 6. Non-shared Headers


//----- Namespace declaration --------------------------------------------------
namespace xms
{

class PublicProgressListener;

class Listener : public xms::ProgressListener
{
public:
  explicit Listener(PublicProgressListener* a_parent, int a_updateDelaySeconds=3);
  virtual ~Listener();

  void SetUpdateDelaySeconds(int a_delay);

  void OnProgressStatus(int a_stackIndex, double a_percentComplete) override;
  int OnBeginOperationString(const std::string& a_operation) override;
  void OnEndOperation(int a_stackIndex) override;
  void OnUpdateMessage(int a_stackIndex, const std::string& a_message) override;

private:
  class impl;
  impl* m_p;
};

} // namespace xms