 
#include "wxDefs.hpp" 
#include "Robotarium.hpp"

#include "CameraFrame.hpp"
#include "MainWindow.hpp"


class MyApp: public wxApp
{
    virtual bool OnInit();
};


BEGIN_EVENT_TABLE(MainWindow, wxFrame)
    EVT_MENU(ID_Quit, MainWindow::OnQuit)
    EVT_MENU(ID_About, MainWindow::OnAbout)
	EVT_MENU(ID_Start, MainWindow::OnStart)
	EVT_MENU(ID_OpenWin, MainWindow::OnOpenWin)
	EVT_MENU(ID_InsertCamera, MainWindow::OnInsertCamera)
	EVT_MENU(ID_InsertSceneNode, MainWindow::OnInsertSceneNode)
	EVT_MENU(ID_InsertGraphicNode, MainWindow::OnInsertGraphicNode)
	EVT_MENU(ID_InsertRigidBodyNode, MainWindow::OnInsertRigidBodyNode)
	EVT_MENU(ID_LoadScene, MainWindow::OnLoadScene)
END_EVENT_TABLE()
 
IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MainWindow *frame = new MainWindow( "Robotarium",
         wxPoint(50,50), wxSize(800,600) );
	SetTopWindow(frame);
    frame->Show();
    return TRUE;
}