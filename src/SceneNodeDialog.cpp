#include "SceneNodeDialog.hpp"

void SceneNodeDialog::LoadSceneTree2Combo(wxComboBox * cmbo, Robotarium::graphic::SceneNodePtr& startingNode)
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

SceneNodeDialog::SceneNodeDialog(wxFrame* _parent, 
	Robotarium::graphic::SceneNodePtr* _parentSceneNode, 
	const std::string _title, DlgType dlgType)
	: wxDialog(_parent, wxID_ANY, _title, wxDefaultPosition), 
		mParent(*_parentSceneNode), parent(nullptr)
{
	wxPanel *pnlPositions = new wxPanel(this, -1);
	wxPanel *pnlParent = new wxPanel(this, -1);
	wxPanel *pnlName = new wxPanel(this, -1);

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

	wxTextCtrl *txtName;


	wxStaticBox *stbName = new wxStaticBox(pnlName, -1, wxT("Name"), 
		wxPoint(0, 0), wxSize(240, 60));

	wxStaticText *lblName = new wxStaticText(pnlName, -1, wxT("Name"), 
		wxPoint(15, 30), wxSize(50, -1), wxALIGN_RIGHT);
	txtName = new wxTextCtrl(pnlName, -1, wxT("Scene_Node_"), 
		wxPoint(75, 30), wxSize(130,20),0, wxTextValidator(wxFILTER_ALPHANUMERIC));


	wxStaticBox *stbMeshInfo = new wxStaticBox(pnlParent, -1, wxT("Parent Scene Node"), 
		wxPoint(0, 0), wxSize(240, 60));

	wxStaticText *lblParent = new wxStaticText(pnlParent, -1, wxT("Parent"), 
		wxPoint(15, 30), wxSize(50, -1), wxALIGN_RIGHT);

	wxComboBox *nodeList = new wxComboBox(pnlParent,  -1, "", 
		wxPoint(75, 25), wxSize(130, 20), 0, 0, wxCB_READONLY);

	nodeList->Append(Robotarium::graphic::RenderEngine::GetSingleton()->GetScene()->GetRootSceneNode()->GetName());
	nodeList->SetSelection(0);
	listOfNodes.push_back(Robotarium::graphic::RenderEngine::GetSingleton()->GetScene()->GetRootSceneNode());
	LoadSceneTree2Combo(nodeList, mParent);


	wxStaticBox *stbPosition = new wxStaticBox(pnlPositions, -1, wxT("Position"), 
		wxPoint(0, 0), wxSize(240, 85));


	wxStaticText *posText1  = new wxStaticText(pnlPositions, -1, wxT("Position"), 
		wxPoint(15, 30), wxSize(50, -1), wxALIGN_RIGHT);

	wxTextCtrl *pos_x = new wxTextCtrl(pnlPositions, -1, wxT("0"), wxPoint(75, 30), wxSize(40,20),0, wxTextValidator(wxFILTER_NUMERIC));
	wxTextCtrl *pos_y = new wxTextCtrl(pnlPositions, -1, wxT("0"), wxPoint(120, 30), wxSize(40,20),0, wxTextValidator(wxFILTER_NUMERIC));
	wxTextCtrl *pos_z = new wxTextCtrl(pnlPositions, -1, wxT("0"), wxPoint(165, 30), wxSize(40,20),0, wxTextValidator(wxFILTER_NUMERIC));


	wxStaticText *posText2  = new wxStaticText(pnlPositions, -1, wxT("Rotation"), 
		wxPoint(15, 55), wxSize(50, -1), wxALIGN_RIGHT);

	wxTextCtrl *rot_1 = new wxTextCtrl(pnlPositions, -1, wxT("1"), wxPoint(75, 55), wxSize(27,20),0, wxTextValidator(wxFILTER_NUMERIC));
	wxTextCtrl *rot_2 = new wxTextCtrl(pnlPositions, -1, wxT("0"), wxPoint(104, 55), wxSize(27,20),0, wxTextValidator(wxFILTER_NUMERIC));
	wxTextCtrl *rot_3 = new wxTextCtrl(pnlPositions, -1, wxT("0"), wxPoint(133, 55), wxSize(27,20),0, wxTextValidator(wxFILTER_NUMERIC));
	wxTextCtrl *rot_4 = new wxTextCtrl(pnlPositions, -1, wxT("0"), wxPoint(175, 55), wxSize(30,20),0, wxTextValidator(wxFILTER_NUMERIC));


	wxButton *okButton = new wxButton(this, wxID_OK, wxT("Ok"), 
		wxDefaultPosition, wxSize(70, 25));
	wxButton *closeButton = new wxButton(this, wxID_CANCEL, wxT("Close"), 
		wxDefaultPosition, wxSize(70, 25));

	hbox->Add(okButton, 1);
	hbox->Add(closeButton, 1, wxLEFT, 5);

	if (dlgType == WILL_CREATE_NEW)
	{
		vbox->Add(pnlName, 0, wxLEFT | wxTOP | wxRIGHT, 10);
		vbox->Add(pnlParent, 0, wxLEFT | wxTOP | wxRIGHT, 10);
	}

	vbox->Add(pnlPositions, 0, wxLEFT | wxTOP | wxRIGHT, 10);

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

			parent = boost::static_pointer_cast<Robotarium::graphic::SceneNode>(listOfNodes.at(nodeList->GetSelection()));

		}

		this->position.x = Ogre::StringConverter::parseInt(pos_x->GetValue().ToStdString());
		this->position.y = Ogre::StringConverter::parseInt(pos_y->GetValue().ToStdString());
		this->position.z = Ogre::StringConverter::parseInt(pos_z->GetValue().ToStdString());

		Real angle;
		angle = Ogre::StringConverter::parseInt(rot_4->GetValue().ToStdString());

		Vec3 axis;
		axis.x = Ogre::StringConverter::parseInt(pos_x->GetValue().ToStdString());
		axis.y = Ogre::StringConverter::parseInt(pos_y->GetValue().ToStdString());
		axis.z = Ogre::StringConverter::parseInt(pos_z->GetValue().ToStdString());

		this->rotation.FromAngleAxis(Ogre::Radian(angle), axis);
	}

	//Destroy();
}
