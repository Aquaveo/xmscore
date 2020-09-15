#pragma once
//------------------------------------------------------------------------------
/// \file
/// \ingroup misc
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
#include <string>

#include <xmscore/misc/boost_defines.h>

//----- Forward declarations ---------------------------------------------------

//----- Namespace declaration --------------------------------------------------

//----- Constants / Enumerations -----------------------------------------------

//----- Structs / Classes ------------------------------------------------------
namespace xms
{
class Progress
{
public:
  Progress(const std::string& a_message);
  ~Progress();

  void UpdateMessage(const std::string& a_message);

  void SetItemCount(long long a_count);
  void CurrentItem(long long a_item);

  void ProgressStatus(double a_percentComplete);

private:
  int m_stackIndex;      ///< instances index on stack of instances
  long long m_itemCount; ///< number of items to process
};

/// \class ProgressListener
/// \brief Listen to progress reported from Progress class
class ProgressListener
{
public:
  virtual ~ProgressListener();

  /// \brief Listen to progress status
  /// \param[in] a_stackIndex: the ID for progress stack (0 for first)
  /// \param[in] a_fractionComplete: amount complete from 0.0 to 1.0
  virtual void OnProgressStatus(int a_stackIndex, double a_fractionComplete) = 0;

  /// \brief Listen to when operation begins
  /// \param[in] a_operation: the name of the operation
  /// \return the ID for progress stack (0 for first)
  virtual int OnBeginOperationString(const std::string& a_operation) = 0;

  /// \brief Listen to when operation ends
  /// \param[in] a_stackIndex: the ID for progress stack (0 for first)
  virtual void OnEndOperation(int a_stackIndex) = 0;

  /// \brief Listen to when operation ends
  /// \param[in] a_stackIndex: the ID for progress stack (0 for first)
  /// \param[in] a_message: the new message for an operation
  virtual void OnUpdateMessage(int a_stackIndex, const std::string& a_message) = 0;

  static void SetListener(BSHP<ProgressListener> a_listener);
  static BSHP<ProgressListener> GetListener();
};

} // namespace xms

//----- Function prototypes ----------------------------------------------------
