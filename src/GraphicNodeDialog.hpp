#pragma once
#ifndef __GRAPHIC_NODE_DIALOG__
#define __GRAPHIC_NODE_DIALOG__

#include <boost/shared_ptr.hpp>
#include <boost/pointer_cast.hpp>

#include "wxDefs.hpp"
#include "common/Types.hpp"
#include "graphic/SceneNode.hpp"
#include "graphic/GraphicNode.hpp"
#include "Robotarium.hpp"

using namespace Robotarium;

class GraphicNodeDialog : public wxDialog
{
public:
	GraphicNodeDialog(wxFrame*, Robotarium::graphic::SceneNodePtr*,const std::string, DlgType dlgType);
	
	void LoadSceneTree2Combo(wxComboBox * cmbo, Robotarium::graphic::SceneNodePtr& startingNode);

	String name;
	String meshName;
	UInt32 retID;
	Robotarium::graphic::SceneNodePtr parent;
	Robotarium::graphic::SceneNodePtr& mParent;
	std::vector<Robotarium::NodePtr> listOfNodes;
};

#endif