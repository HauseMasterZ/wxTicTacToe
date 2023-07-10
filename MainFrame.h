#pragma once

#include <wx/wx.h>
class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	wxDECLARE_EVENT_TABLE();
	void OnLabelClicked(wxMouseEvent& event);
	void OnPaint(wxPaintEvent& event);
	void OnResetClicked(wxCommandEvent& event);
	void DrawWinLines(int first, int third);
	bool CheckWin(int ID);
	wxStaticText* labels[9];
	wxStaticText* Result;
	int currentPlayer;
	bool Done;
	wxPanel* panel;


};

