#pragma once

#ifndef __MAINWINDOW_HPP__
#define __MAINWINDOW_HPP__

#include "wxDefs.hpp"
#include "Robotarium.hpp"

#include "CameraFrame.hpp"
#include "CameraDialog.hpp"
#include "SceneNodeDialog.hpp"
#include "GraphicNodeDialog.hpp"
#include "NodeViewer.hpp"
#include "PropertyGrid.hpp"

using namespace Robotarium;
using namespace graphic;

class MainWindow: public wxFrame
{
public:
 
    MainWindow(const wxString& title, 
           const wxPoint& pos, const wxSize& size);
	~MainWindow();

    //wxTreeListCtrl* mTree;
	NodeViewer* mTree;
	PropertyGrid* mProperties;
	//wxTreeItemId mTreeRoot;

	void OnQuit(wxCommandEvent& event);

    void OnAbout(wxCommandEvent& event);

	void OnStart(wxCommandEvent& event);

	void OnOpenWin(wxCommandEvent& event);

	void OnInsertCamera(wxCommandEvent& event);

	void OnInsertSceneNode(wxCommandEvent& event);

	void OnInsertGraphicNode(wxCommandEvent& event);

	void OnInsertRigidBodyNode(wxCommandEvent& event);

	void OnLoadScene(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
private:
    wxAuiManager m_mgr;
};

enum
{
    ID_Quit = 1,
    ID_About,
	ID_Start,
	ID_OpenWin,
	ID_InsertCamera,
	ID_InsertSceneNode,
	ID_InsertGraphicNode,
	ID_InsertRigidBodyNode,
	ID_LoadScene,
};
 

#endif