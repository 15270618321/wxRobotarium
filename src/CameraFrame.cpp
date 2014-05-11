#include "CameraFrame.hpp"

using namespace Robotarium;
using namespace graphic;

CamFrame::CamFrame(wxWindow* parent, String name, Vec2 viewportsize)
	: wxFrame((wxWindow*)parent, -1, name, wxDefaultPosition, wxDefaultSize, 
			wxFRAME_FLOAT_ON_PARENT | wxCAPTION | wxMINIMIZE_BOX & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	
	wxControl* renderTarget = new wxControl(this, -1, wxDefaultPosition, wxSize(viewportsize.x, viewportsize.y));

	renderTarget->SetBackgroundColour(wxColor(200, 200, 210));

	wxBoxSizer *szrCenter = new wxBoxSizer(wxVERTICAL);

	szrCenter->Add(renderTarget);

	this->SetSizerAndFit(szrCenter);

	this->handle = Ogre::StringConverter::toString((size_t)((HWND)renderTarget->GetHandle()));
	
	renderTarget->Show(TRUE);
	

	CreateStatusBar();
	
	SetStatusText( handle );
	
	//mCamera = boost::make_shared<Camera>(name, handle, viewportsize, camposition, lookatpoint);

}
