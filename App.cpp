#include "App.h"
#include <wx/wx.h>
#include "MainFrame.h"
wxIMPLEMENT_APP(App);
bool App::OnInit() {
	MainFrame* mainFrame = new MainFrame("TicTacToe Gui C++");
	mainFrame->SetClientSize(600, 600);
	mainFrame->Center();
	mainFrame->Show();
	return true;
}
