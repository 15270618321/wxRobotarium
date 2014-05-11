#pragma once
#ifndef __PROPERTY_GRID_HPP__
#define __PROPERTY_GRID_HPP__

#include "wx/propgrid/propgrid.h"
#include "wxDefs.hpp"
#include "Robotarium.hpp"
#include <math.h>

class PropertyGrid: public  wxPropertyGrid
{
public:
	PropertyGrid(wxWindow* parent);
	~PropertyGrid();
	void ShowProperties(Robotarium::NodePtr& obj2show);

	Robotarium::NodePtr mCurrentNode;
};
#endif