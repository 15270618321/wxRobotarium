#pragma once
#ifndef __NODE_VIEWER_HPP__
#define __NODE_VIEWER_HPP__
#include <vector>
#include "wxDefs.hpp"
#include "PropertyGrid.hpp"
#include "Robotarium.hpp"

class NodeViewerItemData : public wxTreeItemData
{
public:
    NodeViewerItemData (const int& id) : mId(id) { }

    const int GetNodeID() const { return mId; }

private:
    int mId;
};

class NodeViewer : public wxTreeCtrl
{

public:		NodeViewer(wxWindow* parent, PropertyGrid* _prop_grid,
				wxWindowID id,
				const wxPoint& pos = wxDefaultPosition,
				const wxSize& size = wxDefaultSize,
				long style = wxTR_HAS_BUTTONS | wxTR_SINGLE);

			~NodeViewer();

			//std::vector<Robotarium::NodePtr> mNodeList;

			std::map<Robotarium::UInt32, Robotarium::NodePtr> mNodeList;

private:	PropertyGrid* mPropGrid;

private:	Robotarium::UInt32 LoadNodeTree2TreeCtrl(Robotarium::UInt32, wxTreeItemId &,Robotarium::graphic::SceneNodePtr& );

public:		void UpdateFromNode(Robotarium::NodePtr&);

public:		void OnClick(wxTreeEvent& event);
};

#endif