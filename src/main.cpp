/*
 * hworld.cpp
 * Hello world sample by Robert Roebling
 */
 
#include "wx/wx.h" 
#include "common/Application.h" 

class MyApp: public wxApp
{
    virtual bool OnInit();
};

class CamFrame: public wxFrame
{
public:
 
    CamFrame(const wxString& title, 
           const wxPoint& pos, const wxSize& size);
};

class MyFrame: public wxFrame
{
public:
 
    MyFrame(const wxString& title, 
           const wxPoint& pos, const wxSize& size);

    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
	void OnCommence(wxCommandEvent& event);
	void OnOpenWin(wxCommandEvent& event);
    DECLARE_EVENT_TABLE()
};

enum
{
    ID_Quit = 1,
    ID_About,
	ID_Commence,
	ID_OpenWin,
};
 
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Quit, MyFrame::OnQuit)
    EVT_MENU(ID_About, MyFrame::OnAbout)
	EVT_MENU(ID_Commence, MyFrame::OnCommence)
	EVT_MENU(ID_OpenWin, MyFrame::OnOpenWin)
END_EVENT_TABLE()
 
IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( "Robotarium",
         wxPoint(50,50), wxSize(800,600) );
    frame->Show(TRUE);
    SetTopWindow(frame);
    return TRUE;
} 
 
MyFrame::MyFrame(const wxString& title, 
       const wxPoint& pos, const wxSize& size)
: wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;
	menuFile->Append( ID_Commence, "&Start" );
	menuFile->Append( ID_OpenWin, "&Open Window" );
	menuFile->AppendSeparator();
    menuFile->Append( ID_About, "&About..." );
    menuFile->AppendSeparator();
    menuFile->Append( ID_Quit, "E&xit" );
 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
 
    SetMenuBar( menuBar );

    CreateStatusBar();
    SetStatusText( "Welcome to the Robotarium." );
}

CamFrame::CamFrame(const wxString& title, 
       const wxPoint& pos, const wxSize& size)
: wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
	Ogre::String handle;
	handle = Ogre::StringConverter::toString((size_t)((HWND)GetHandle()));
	CreateStatusBar();
	SetStatusText( handle );
}

 
void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(TRUE);
}
 
void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{

    wxMessageBox("This is Robotarium, a simulation engine for robotics research developed at KNTU.",
        "About Robotarium", wxOK | wxICON_INFORMATION, this);
}

void MyFrame::OnCommence(wxCommandEvent& WXUNUSED(event))
{
	cApplication app;
	app.commence();
}

void MyFrame::OnOpenWin(wxCommandEvent& WXUNUSED(event))
{
	CamFrame *frame = new CamFrame( "Camera_1",
         wxPoint(100,100), wxSize(640,480) );
	
    frame->Show(TRUE);
}