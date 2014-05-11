#ifndef __CAMFRAME_HPP__
#define __CAMFRAME_HPP__

#include "wx/wx.h" 
#include "Robotarium.hpp"

using namespace Robotarium;
using namespace graphic;

class CamFrame: public wxFrame
{
public:
 
    CamFrame(wxWindow* parent, String name, Vec2 viewportsize);

	String handle;
	
	Robotarium::graphic::CameraPtr mCamera;
	
	Robotarium::graphic::CameraSceneNodePtr mCameraSceneNode;

};

#endif