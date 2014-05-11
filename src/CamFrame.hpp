#ifndef __CAMFRAME_HPP__
#define __CAMFRAME_HPP__

#include "wx/wx.h" 
#include "Robotarium.hpp"

using namespace Robotarium;
using namespace graphic;

class CamFrame: public wxFrame
{
public:
 
    CamFrame(wxWindow* parent, const wxString& title, 
           const wxPoint& pos, uint32_t width, uint32_t height);
	
	Robotarium::graphic::CameraPtr mCamera;
};

#endif