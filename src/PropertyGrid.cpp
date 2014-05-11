#include "PropertyGrid.hpp"


const wxVec3& fromRobotarium(Vec3 _vec)
{
	return wxVec3(_vec.x, _vec.y, _vec.z);
}

const wxScrew& fromRobotarium(Quat _quat)
{
	Robotarium::Radian angle;
	Robotarium::Vec3 axis;
	

   if (_quat.w > 1) _quat.normalise(); // if w>1 acos and sqrt will produce errors, this cant happen if quaternion is normalised
   angle = 2*acos(_quat.w);
   double s = sqrt(1 - _quat.w*_quat.w); // assuming quaternion normalised then w is less than 1, so term always positive.
   if (s < 0.001) { // test to avoid divide by zero, s is always positive due to sqrt
     // if s close to zero then direction of axis not important
     axis.x = _quat.x; // if it is important that axis is normalised then replace with x=1; y=z=0;
     axis.y = _quat.y;
     axis.z = _quat.z;
   } else {
     axis.x = _quat.x / s; // normalise axis
     axis.y = _quat.y / s;
     axis.z = _quat.z / s;
   }
   
   return wxScrew(axis.x, axis.y, axis.z, angle.valueRadians());
}

PropertyGrid::PropertyGrid(wxWindow* parent): wxPropertyGrid(parent, -1, 
        wxDefaultPosition, wxSize(300,0), wxPG_SPLITTER_AUTO_CENTER | wxPG_DEFAULT_STYLE )
{
}

PropertyGrid::~PropertyGrid()
{
}

void PropertyGrid::ShowProperties(Robotarium::NodePtr& node)
{
	this->Clear();
	switch(node->GetNodeType())
	{
	case Robotarium::BASIC_NODE_TYPE :
		Append( new wxPropertyCategory("Node") );
		Append( new wxStringProperty("Name", wxPG_LABEL,node->GetName()));
		mCurrentNode = node;
		break;
	case Robotarium::SCENE_NODE_TYPE :
		Append( new wxPropertyCategory("Node") );
		Append( new wxStringProperty("Name", wxPG_LABEL,node->GetName()));
		Append( new wxPropertyCategory("SceneNode") );
		Append( new Vec3Property("Position", wxPG_LABEL, 
			fromRobotarium(boost::static_pointer_cast<Robotarium::graphic::SceneNode>(node)->GetPosition())));
		Append( new ScrewProperty("Orientation", wxPG_LABEL, 
			fromRobotarium(boost::static_pointer_cast<Robotarium::graphic::SceneNode>(node)->GetOrientation())));
		mCurrentNode = node;
		break;
	case Robotarium::GRAPHIC_NODE_TYPE :
		Append( new wxPropertyCategory("Node") );
		Append( new wxStringProperty("Name", wxPG_LABEL,node->GetName()));
		Append( new wxPropertyCategory("GraphicNode") );
		mCurrentNode = node;
		break;
	case Robotarium::CAMERA_SCENE_NODE_TYPE :
		Append( new wxPropertyCategory("Node") );
		Append( new wxStringProperty("Name", wxPG_LABEL,node->GetName()));
		Append( new wxPropertyCategory("CameraSceneNode") );
		Append( new Vec3Property("Position", wxPG_LABEL, 
			fromRobotarium(boost::static_pointer_cast<Robotarium::graphic::CameraSceneNode>(node)->GetPosition())));
		//Append( new LookAtPointProperty("Look At Point", wxPG_LABEL, 
		//	fromRobotarium(boost::static_pointer_cast<Robotarium::graphic::CameraSceneNode>(node)->GetPosition())));
		Append( new ScrewProperty("Orientation", wxPG_LABEL, 
			fromRobotarium(boost::static_pointer_cast<Robotarium::graphic::SceneNode>(node)->GetOrientation())));

		mCurrentNode = node;
		break;
	}
	
}