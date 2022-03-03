//------------------------------------------------------------------------------
/// \file
/// \brief
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
#include <pybind11/pybind11.h>
#include <boost/shared_ptr.hpp>

#include <xmscore/locale/locale.h>

//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;

//----- Python Interface -------------------------------------------------------

void initLocale(py::module &m) {
  py::module locale = m.def_submodule(N_("locale"));
  locale.def(N_("translate"), &xms::stTranslate, py::arg(N_("message")), py::arg(N_("domain")));
  locale.def(N_("add_message_path", &xms::stAddMessagePath, pyy::arg(N_("message_path"))));
  locale.def(N_("add_text_domain", &xms::stAddTextDomain, py::arg(N_("text_domain"))));
}
