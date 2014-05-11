#pragma once
#ifndef __SCENE_NODE_DIALOG__
#define __SCENE_NODE_DIALOG__

#include <boost/shared_ptr.hpp>
#include <boost/pointer_cast.hpp>

#include "wxDefs.hpp"
#include "common/Types.hpp"
#include "graphic/SceneNode.hpp"
#include "Robotarium.hpp"

using namespace Robotarium;

class SceneNodeDialog : public wxDialog
{
public:
	SceneNodeDialog(wxFrame* parent, Robotarium::graphic::SceneNodePtr*,const std::string title, DlgType dlgType);
	
	void LoadSceneTree2Combo(wxComboBox * cmbo, Robotarium::graphic::SceneNodePtr& startingNode);

	String name;
	Vec3 position;
	Quat rotation;
	UInt32 retID;
	Robotarium::graphic::SceneNodePtr parent;
	Robotarium::graphic::SceneNodePtr& mParent;
	std::vector<Robotarium::NodePtr> listOfNodes;
};

#endif