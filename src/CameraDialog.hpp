#pragma once
#ifndef __CAMERADIALOG_HPP__
#define __CAMERADIALOG_HPP__

#include "wx/wx.h"
#include "wxDefs.hpp"
#include "CameraFrame.hpp"
//#include "MainWindow.hpp"
#include "common/Types.hpp"
#include "Robotarium.hpp"

using namespace Robotarium;

class CameraDialog : public wxDialog
{
public:
	CameraDialog(wxFrame*, Robotarium::graphic::SceneNodePtr*, const std::string title, DlgType dlgType);

public: void LoadSceneTree2Combo(wxComboBox * cmbo, Robotarium::graphic::SceneNodePtr& startingNode);

	String name;
	Vec2 viewportSize;
	Vec3 camPosition;
	Vec3 lapPosition;
	UInt32 retID;
	std::vector<Robotarium::NodePtr> listOfNodes;
	
	Robotarium::graphic::SceneNodePtr parent;
	Robotarium::graphic::SceneNodePtr& mParent;
};

#endif