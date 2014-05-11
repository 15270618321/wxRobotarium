#include "CameraDialog.hpp"

void CameraDialog::LoadSceneTree2Combo(wxComboBox * cmbo, Robotarium::graphic::SceneNodePtr& startingNode)
{
	//Robotarium::graphic::RenderEngine::GetSingleton()->GetScene()->GetRootSceneNode();
	Robotarium::NodeMapPtr& childNodeMap = startingNode->GetChildNodeMap();

	Robotarium::NodeMap::const_iterator nodeIterator = childNodeMap->begin();
	Robotarium::NodeMap::const_iterator nodeIteratorEnd = childNodeMap->end();

	for(;nodeIterator != nodeIteratorEnd ; ++nodeIterator)
	{
		if (nodeIterator->second->GetNodeType() == Robotarium::SCENE_NODE_TYPE)
		{
			cmbo->Append(nodeIterator->second->GetName());
			this->listOfNodes.push_back(nodeIterator->second);
			LoadSceneTree2Combo(cmbo, boost::static_pointer_cast<Robotarium::graphic::SceneNode>(nodeIterator->second));
		}
	}

}

CameraDialog::CameraDialog(wxFrame* _parent, Robotarium::graphic::SceneNodePtr* _parentSceneNode, const std::string title, DlgType dlgType)
	: wxDialog(_parent, wxID_ANY, title, wxDefaultPosition),
		mParent(*_parentSceneNode), parent(nullptr)
{
	wxPanel *pnlPositions = new wxPanel(this, -1);
	wxPanel *pnlParent = new wxPanel(this, -1);
	wxPanel *pnlName = new wxPanel(this, -1);

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

	wxTextCtrl *txtName;
	if (dlgType == WILL_CREATE_NEW)
	{
		wxStaticBox *stbName = new wxStaticBox(pnlName, -1, wxT("Name"), 
		wxPoint(0, 0), wxSize(240, 60));

		wxStaticText *lblName = new wxStaticText(pnlName, -1, wxT("Name"), 
			wxPoint(15, 30), wxSize(50, -1), wxALIGN_RIGHT);
		txtName = new wxTextCtrl(pnlName, -1, wxT("Camera"), 
			wxPoint(75, 30), wxSize(130,20),0, wxTextValidator(wxFILTER_ALPHANUMERIC));

	}
	wxStaticBox *stbPosition = new wxStaticBox(pnlPositions, -1, wxT("Position"), 
		wxPoint(0, 0), wxSize(240, 85));

	
	wxStaticText *posText1  = new wxStaticText(pnlPositions, -1, wxT("Camera"), 
		wxPoint(15, 30), wxSize(50, -1), wxALIGN_RIGHT);

	wxTextCtrl *camPos_x = new wxTextCtrl(pnlPositions, -1, wxT("0"), wxPoint(75, 30), wxSize(40,20),0, wxTextValidator(wxFILTER_NUMERIC));
	wxTextCtrl *camPos_y = new wxTextCtrl(pnlPositions, -1, wxT("0"), wxPoint(120, 30), wxSize(40,20),0, wxTextValidator(wxFILTER_NUMERIC));
	wxTextCtrl *camPos_z = new wxTextCtrl(pnlPositions, -1, wxT("0"), wxPoint(165, 30), wxSize(40,20),0, wxTextValidator(wxFILTER_NUMERIC));


	wxStaticText *posText2  = new wxStaticText(pnlPositions, -1, wxT("Look at point"), 
		wxPoint(15, 55), wxSize(50, -1), wxALIGN_RIGHT);

	wxTextCtrl *lapPos_x = new wxTextCtrl(pnlPositions, -1, wxT("1"), wxPoint(75, 55), wxSize(40,20),0, wxTextValidator(wxFILTER_NUMERIC));
	wxTextCtrl *lapPos_y = new wxTextCtrl(pnlPositions, -1, wxT("0"), wxPoint(120, 55), wxSize(40,20),0, wxTextValidator(wxFILTER_NUMERIC));
	wxTextCtrl *lapPos_z = new wxTextCtrl(pnlPositions, -1, wxT("0"), wxPoint(165, 55), wxSize(40,20),0, wxTextValidator(wxFILTER_NUMERIC));



	wxPanel *pnlViewportSettings = new wxPanel(this, -1);

	wxStaticBox *stbViewportSettings = new wxStaticBox(pnlViewportSettings, -1, wxT("Viewport Settings"), 
		wxPoint(0, 0), wxSize(240, 60));

	
	wxStaticText *lblViewportSize  = new wxStaticText(pnlViewportSettings, -1, wxT("Size"), 
		wxPoint(15, 30), wxSize(50, -1), wxALIGN_RIGHT);

	wxTextCtrl *txtSizeX = new wxTextCtrl(pnlViewportSettings, -1, wxT("800"), 
		wxPoint(75, 30), wxSize(62,20),0, wxTextValidator(wxFILTER_NUMERIC));
	
	wxTextCtrl *txtSizeY = new wxTextCtrl(pnlViewportSettings, -1, wxT("600"), 
		wxPoint(142, 30), wxSize(63,20),0, wxTextValidator(wxFILTER_NUMERIC));

		wxStaticBox *stbParent = new wxStaticBox(pnlParent, -1, wxT("Parent Scene Node"), 
		wxPoint(0, 0), wxSize(240, 60));

	wxStaticText *lblParent = new wxStaticText(pnlParent, -1, wxT("Parent"), 
		wxPoint(15, 30), wxSize(50, -1), wxALIGN_RIGHT);

	wxComboBox *nodeList = new wxComboBox(pnlParent,  -1, "", 
		wxPoint(75, 25), wxSize(130, 20), 0, 0, wxCB_READONLY);

	nodeList->Append(Robotarium::graphic::RenderEngine::GetSingleton()->GetScene()->GetRootSceneNode()->GetName());
	nodeList->SetSelection(0);
	listOfNodes.push_back(Robotarium::graphic::RenderEngine::GetSingleton()->GetScene()->GetRootSceneNode());
	LoadSceneTree2Combo(nodeList, mParent);



	wxButton *okButton = new wxButton(this, wxID_OK, wxT("Ok"), 
		wxDefaultPosition, wxSize(70, 25));
	wxButton *closeButton = new wxButton(this, wxID_CANCEL, wxT("Close"), 
		wxDefaultPosition, wxSize(70, 25));

	hbox->Add(okButton, 1);
	hbox->Add(closeButton, 1, wxLEFT, 5);

	if (dlgType == WILL_CREATE_NEW)
	{
		vbox->Add(pnlName, 0, wxLEFT | wxTOP | wxRIGHT, 10);
	}
	vbox->Add(pnlPositions, 0, wxLEFT | wxTOP | wxRIGHT, 10);
	vbox->Add(pnlViewportSettings, 0, wxLEFT | wxTOP | wxRIGHT, 10);
	vbox->Add(pnlParent, 0, wxLEFT | wxTOP | wxRIGHT, 10);
	vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
	vbox->AddSpacer(10);

	this->SetSizerAndFit(vbox);
	Centre();

	//okButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CameraDialog::OnOK, this);

	retID = ShowModal();
	if(retID == wxID_OK)
	{
		if (dlgType == WILL_CREATE_NEW)
		{
			name = txtName->GetValue().ToStdString();
		}

		this->viewportSize.x = Ogre::StringConverter::parseInt(txtSizeX->GetValue().ToStdString());
		this->viewportSize.y = Ogre::StringConverter::parseInt(txtSizeY->GetValue().ToStdString());

		this->camPosition.x = Ogre::StringConverter::parseInt(camPos_x->GetValue().ToStdString());
		this->camPosition.y = Ogre::StringConverter::parseInt(camPos_y->GetValue().ToStdString());
		this->camPosition.z = Ogre::StringConverter::parseInt(camPos_z->GetValue().ToStdString());

		this->lapPosition.x = Ogre::StringConverter::parseInt(lapPos_x->GetValue().ToStdString());
		this->lapPosition.y = Ogre::StringConverter::parseInt(lapPos_y->GetValue().ToStdString());
		this->lapPosition.z = Ogre::StringConverter::parseInt(lapPos_z->GetValue().ToStdString());

		parent = boost::static_pointer_cast<Robotarium::graphic::SceneNode>(listOfNodes.at(nodeList->GetSelection()));
	}

	//Destroy();
}

//void CameraDialog::OnOK(wxCommandEvent& event)
//{
//	CamFrame* mCamFrame = new CamFrame(this, "Camera_1",
//		wxPoint(100,100), 500, 500);
//	mCamFrame->Show(TRUE);
//}