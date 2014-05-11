#include "MainWindow.hpp"

using namespace Robotarium;
using namespace graphic;

MainWindow::MainWindow(const wxString& title, 
	const wxPoint& pos, const wxSize& size)
	: wxFrame((wxFrame *)NULL, -1, title, pos, size,wxDEFAULT_FRAME_STYLE)
{
	wxMenu *menuFile = new wxMenu;
	//menuFile->AppendSeparator();
	menuFile->Append( ID_Quit, "E&xit" );


	wxMenu *menuInsert = new wxMenu;
	menuInsert->Append( ID_InsertCamera, "&Camera" );
	menuInsert->Append( ID_InsertSceneNode, "&Scene Node" );
	menuInsert->Append( ID_InsertGraphicNode, "&Graphic Node" );
	menuInsert->Append( ID_InsertRigidBodyNode, "&RigidBody Node" );

		
	wxMenu *menuSimulation = new wxMenu;
	menuSimulation->Append( ID_OpenWin, "&Open Window" );
	menuSimulation->AppendSeparator();
	menuSimulation->Append( ID_LoadScene, "&Load Scene" );
	menuSimulation->Append( ID_Start, "&Start" );


	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append( ID_About, "&About" );

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append( menuFile, "&File" );
	menuBar->Append( menuInsert, "&Insert" );
	menuBar->Append( menuSimulation, "&Simulation" );
	menuBar->Append( menuHelp, "&Help" );

	SetMenuBar( menuBar );

	// notify wxAUI which frame to use
	m_mgr.SetManagedWindow(this);

	// create several text controls
	//wxTextCtrl* text1 = new wxTextCtrl(this, -1, _("Scene Graph goes here."),
	//	wxDefaultPosition, wxSize(200,150),
	//	wxNO_BORDER | wxTE_MULTILINE);

	wxTextCtrl* text2 = new wxTextCtrl(this, -1, _("Status goes here."),
		wxDefaultPosition, wxSize(200,150),
		wxNO_BORDER | wxTE_MULTILINE);

	wxTextCtrl* text3 = new wxTextCtrl(this, -1, _("Main content window"),
		wxDefaultPosition, wxSize(200,150),
		wxNO_BORDER | wxTE_MULTILINE);


	mProperties = new PropertyGrid(this);

	mTree = new NodeViewer(this, mProperties, wxID_ANY,
		wxDefaultPosition, wxSize(250,150));

	wxFontInfo* mFontInfo = new wxFontInfo(8);
	mFontInfo->AntiAliased(TRUE);
	this->SetFont(*mFontInfo);

	mTree->SetFont(*mFontInfo);
	mTree->Fit();
	//mTreeRoot = mTree->GetRootItem();


	// add the panes to the manager
	m_mgr.AddPane(mTree, wxLEFT, wxT("SceneGraph"));
	m_mgr.AddPane(mProperties, wxRIGHT, wxT("Properties"));
	m_mgr.AddPane(text2, wxBOTTOM, wxT("Status"));
	m_mgr.AddPane(text3, wxCENTER);

	// tell the manager to "commit" all the changes just made
	m_mgr.Update();
	//CreateStatusBar();
	//SetStatusText( "Welcome to the Robotarium." );
}

MainWindow::~MainWindow()
{
	m_mgr.UnInit();
}

void MainWindow::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	RenderEngine::GetSingleton()->Terminate();
	Close(TRUE);
}

void MainWindow::OnAbout(wxCommandEvent& WXUNUSED(event))
{

	wxMessageBox("This is Robotarium, a simulation engine for robotics research developed at KNTU.",
		"About Robotarium", wxOK | wxICON_INFORMATION, this);

}

void MainWindow::OnStart(wxCommandEvent& WXUNUSED(event))
{
	RenderEngine::GetSingleton()->GetOgreRoot()->startRendering();
}

void MainWindow::OnOpenWin(wxCommandEvent& WXUNUSED(event))
{
	RenderEngine::GetSingleton()->Load();

	RenderEngine::GetSingleton()->Init();
	
	RenderEngine::GetSingleton()->GetScene()->Load();

	RenderEngine::GetSingleton()->GetScene()->GetOgreSceneMgr()->setAmbientLight(Ogre::ColourValue(0.75, 0.75, 0.75));

		// Create a light
	Ogre::Light* light = RenderEngine::GetSingleton()->GetScene()->GetOgreSceneMgr()->createLight("MainLight");

	light->setPosition(10,8,10);

	mTree->UpdateFromNode(boost::static_pointer_cast<Node>(RenderEngine::GetSingleton()->GetScene()->GetRootSceneNode()));
	
	RenderEngine::GetSingleton()->RunRenderLoop();

}

void MainWindow::OnInsertCamera(wxCommandEvent& WXUNUSED(event))
{
	CameraDialog* CameraDlg = new CameraDialog(this, 
		&RenderEngine::GetSingleton()->GetScene()->GetRootSceneNode(), "Insert Camera...", WILL_CREATE_NEW);

	CameraDlg->Show();

	if (CameraDlg->retID == wxID_OK)
	{

		CamFrame* camFrame = new CamFrame(this, CameraDlg->name, CameraDlg->viewportSize);
		
		camFrame->Show(TRUE);

		//camFrame->mCamera->Load();

		CameraSceneNodePtr temp(new CameraSceneNode(CameraDlg->parent, 
			CameraDlg->name, CameraDlg->parent->GetNodeMapSize() + 1,
			camFrame->handle, CameraDlg->viewportSize, CameraDlg->camPosition, CameraDlg->lapPosition));

		CameraDlg->parent->AddNode(temp);

		temp->Load(CameraDlg->parent);

		mTree->UpdateFromNode(boost::static_pointer_cast<Node>(RenderEngine::GetSingleton()->GetScene()->GetRootSceneNode()));
		mProperties->ShowProperties(boost::static_pointer_cast<Node>(temp));

	}

	Ogre::WindowEventUtilities::messagePump();

	CameraDlg->Destroy();
}

void MainWindow::OnInsertSceneNode(wxCommandEvent& WXUNUSED(event))
{
	SceneNodeDialog* SceneNodeDlg = new SceneNodeDialog(this, 
		&RenderEngine::GetSingleton()->GetScene()->GetRootSceneNode(),"Insert Scene Node...", WILL_CREATE_NEW);

	SceneNodeDlg->Show();

	if (SceneNodeDlg->retID == wxID_OK)
	{
		SceneNodePtr temp(new SceneNode(SceneNodeDlg->name, SceneNodeDlg->parent->GetNodeMapSize() + 1));

		SceneNodeDlg->parent->AddNode(temp);

		temp->Load();

		temp->SetPosition(SceneNodeDlg->position);
		temp->SetOrientation(SceneNodeDlg->rotation);

		mTree->UpdateFromNode(boost::static_pointer_cast<Node>(RenderEngine::GetSingleton()->GetScene()->GetRootSceneNode()));
		mProperties->ShowProperties(boost::static_pointer_cast<Node>(temp));
	}

	SceneNodeDlg->Destroy();
}

void MainWindow::OnInsertGraphicNode(wxCommandEvent& WXUNUSED(event))
{
	GraphicNodeDialog* GraphicNodeDlg = new GraphicNodeDialog(this, 
		&RenderEngine::GetSingleton()->GetScene()->GetRootSceneNode(),"Insert Graphic Node...", WILL_CREATE_NEW);

	GraphicNodeDlg->Show();

	if (GraphicNodeDlg->retID == wxID_OK)
	{
		GraphicNodePtr temp(new GraphicNode(GraphicNodeDlg->parent, GraphicNodeDlg->name, GraphicNodeDlg->meshName));

		GraphicNodeDlg->parent->AddNode(temp);

		temp->Load(GraphicNodeDlg->parent);

		mTree->UpdateFromNode(boost::static_pointer_cast<Node>(RenderEngine::GetSingleton()->GetScene()->GetRootSceneNode()));
		mProperties->ShowProperties(boost::static_pointer_cast<Node>(temp));
	}

	GraphicNodeDlg->Destroy();
}

void MainWindow::OnInsertRigidBodyNode(wxCommandEvent& WXUNUSED(event))
{

}

void MainWindow::OnLoadScene(wxCommandEvent& WXUNUSED(event))
{
		
	//SceneNodePtr rootNode = RenderEngine::GetSingleton()->GetScene()->GetRootSceneNode();

	//SceneNodePtr Node1(new SceneNode(rootNode, "Node_1", 1));
	//rootNode->AddNode(Node1);
	//
	//Ogre::LogManager::getSingleton().logMessage(Ogre::StringConverter::toString(rootNode->GetNodeMapSize()));
	//
	//GraphicNodePtr base(new GraphicNode(Node1, "Graphic_Node_1_1", "resBase.mesh"));
	//Node1->AddNode(base);

	//wxTreeListItem wxRootNode = mTree->AppendItem(mTree->GetRootItem(), "Root");
	//mTree->SetItemText(wxRootNode, 1, "SceneNode");

	//wxTreeListItem n_1 = mTree->AppendItem(wxRootNode, Node1->GetName());
	//mTree->SetItemText(n_1, 1, "SceneNode");

	//wxTreeListItem n_1_1 = mTree->AppendItem(n_1, base->GetName());
	//mTree->SetItemText(n_1_1, 1, "GraphicNode");

	//Ogre::LogManager::getSingleton().logMessage(" Loading Cameras.");
	//RenderEngine::GetSingleton()->GetScene()->LoadAllCameras();
	//Ogre::LogManager::getSingleton().logMessage(" Loading Scene.");
	//RenderEngine::GetSingleton()->GetScene()->Load();
}

