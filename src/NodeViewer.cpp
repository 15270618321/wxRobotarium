#include "NodeViewer.hpp"
using namespace Robotarium;
using namespace graphic;

UInt32 NodeViewer::LoadNodeTree2TreeCtrl(UInt32 _id, 
	wxTreeItemId& _parent,SceneNodePtr& startingNode)
{
	UInt32 id = _id;

	Ogre::LogManager::getSingleton().logMessage("~ ~ Trying to Append: " + startingNode->GetName());

	wxTreeItemId _new = AppendItem(_parent, (startingNode->GetName()), -1, -1, new NodeViewerItemData(id));

	Ogre::LogManager::getSingleton().logMessage("~ ~ ~ ~ ~ ~ Appended: " + startingNode->GetName());

	mNodeList[id] = startingNode;

	Robotarium::NodeMapPtr& childNodeMap = startingNode->GetChildNodeMap();

	Robotarium::NodeMap::const_iterator nodeIterator = childNodeMap->begin();

	Robotarium::NodeMap::const_iterator nodeIteratorEnd = childNodeMap->end();

	for(;nodeIterator != nodeIteratorEnd ; ++nodeIterator)
	{
		id++;

		id = LoadNodeTree2TreeCtrl(id, _new, boost::static_pointer_cast
			<Robotarium::graphic::SceneNode>(nodeIterator->second));

		switch(nodeIterator->second->GetNodeType())
		{
		case 1:

			//_list->SetItemText(_new, 1, "SceneNode");


			break;
		case 2:

			//_list->SetItemText(_new, 1, "GraphicNode");


			break;
		case 3:

			//_list->SetItemText(_new, 1, "CameraSceneNode");

			break;
		}

	}

	return id;
}

void NodeViewer::OnClick(wxTreeEvent& event) 
{

	wxTreeItemId _item = event.GetItem();
	
	if(! GetItemData(_item))
	{
		return;
	}
	NodeViewerItemData *_item_data = (NodeViewerItemData*)GetItemData(_item);
	int sel = _item_data->GetNodeID();
	
	if (sel != -1) 
	{
		this->mPropGrid->ShowProperties(this->mNodeList[sel]);
	} 

}

NodeViewer::NodeViewer(wxWindow* parent, PropertyGrid* _prop_grid, wxWindowID id, const wxPoint& pos,
	const wxSize& size, long style)
	: wxTreeCtrl( parent, id, pos, size, style), mPropGrid(_prop_grid)
{
	DeleteAllItems();

	//wxTreeItemId rootId = AddRoot(wxT("Root"));

	Bind(wxEVT_COMMAND_TREE_SEL_CHANGED, &NodeViewer::OnClick, this);
}

NodeViewer::~NodeViewer()
{
}

void NodeViewer::UpdateFromNode(Robotarium::NodePtr& node)
{
	//while ( GetFirstChild(GetRootItem()) )
	//{
	//	this->DeleteItem(GetFirstChild(GetRootItem()));
	//}

	Ogre::LogManager::getSingleton().logMessage("~ ~ ~ Updating From:" + node->GetName());
	
	DeleteAllItems();
	
	Ogre::LogManager::getSingleton().logMessage("~ Trying to Add Root!");

	//wxTreeItemId rootId = AddRoot(wxT("Root"));

	Ogre::LogManager::getSingleton().logMessage("~ ~ ~ ~ ~ Root Added!");
	//this->DeleteAllItems();

	////wxTreeListItem _root = AppendItem(GetRootItem(), node->GetName());
	//wxTreeItemId _root = this->AddRoot(node->GetName());
	//Expand(_root);

	//this->SetItemData(_root, 0);

	LoadNodeTree2TreeCtrl(0, GetRootItem(), boost::static_pointer_cast<Robotarium::graphic::SceneNode>(node));

	this->ExpandAll();

}