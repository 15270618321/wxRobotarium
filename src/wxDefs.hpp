#pragma once
#ifndef __WX_DEFS__
#define __WX_DEFS__

#include <boost/shared_ptr.hpp>
#include <boost/pointer_cast.hpp>
#include "wx/wxprec.h"
#include "wx/aui/aui.h"
#include "wx/treectrl.h"
#include "wx/propgrid/propgrid.h"
#include "PropertyGrid.hpp"
#include "PropertySet.hpp"
#include "Robotarium.hpp"

enum DlgType{WILL_CREATE_NEW = 1, WILL_EDIT_EXISTING};

#endif