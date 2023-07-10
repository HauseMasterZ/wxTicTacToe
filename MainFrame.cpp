#include "MainFrame.h"
#include <wx/wx.h>

enum IDs {
    RESET_ID = 1
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(RESET_ID, MainFrame::OnResetClicked) // Event handler for the reset button
wxEND_EVENT_TABLE()

int currentPlayer = 0;

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    // Load the icon file
    wxIcon icon;
    icon.LoadFile("icon.ico", wxBITMAP_TYPE_ICO);
                
    // Set the window's icon
    SetIcon(icon);

    panel = new wxPanel(this); // Create a panel as the main container
    Result = new wxStaticText(panel, wxID_ANY, "Player X Turn...", wxPoint(270, 30), wxDefaultSize, wxALIGN_CENTER); // Display the result text
    wxButton* Reset = new wxButton(panel, RESET_ID, "Reset", wxPoint(30, 20), wxDefaultSize); // Create a reset button
    Done = false; // Flag indicating if the game is finished

    // Create the labels for the game grid
    for (int i = 0; i < 9; i++) {
        labels[i] = new wxStaticText(panel, i + 1, "", wxPoint(100 + (i % 3) * 150, 100 + (i / 3) * 150), wxSize(100, 100), wxALIGN_CENTRE_HORIZONTAL);
        labels[i]->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnLabelClicked, this, labels[i]->GetId()); // Bind the label click event handler
        wxFont font(wxFontInfo(72).Family(wxFONTFAMILY_DEFAULT).FaceName("Arial")); // Set the font for the labels
        labels[i]->SetFont(font);
        labels[i]->SetBackgroundColour(wxNullColour);
    }
    panel->Bind(wxEVT_PAINT, &MainFrame::OnPaint, this); // Bind the paint event handler
}

void MainFrame::OnResetClicked(wxCommandEvent& event) {
    wxWindow::Refresh(); // Refresh the window
    Result->SetLabel("Player X Turn..."); // Reset the result text
    Result->SetBackgroundColour(wxNullColour);
    for (int i = 0; i < 9; i++) {
        labels[i]->SetLabel(""); // Clear the labels
    }
    Done = false; // Reset the game state
    currentPlayer = 0;
}

void MainFrame::OnLabelClicked(wxMouseEvent& event) {
    int labelId = event.GetId();
    wxStaticText* label = dynamic_cast<wxStaticText*>(event.GetEventObject()); // Get the static text control
    if (label) {
        if (Done) {
            return; // Ignore clicks if the game is finished
        }
        if (currentPlayer > 8) {
            Result->SetLabel("It is a Draw!");
            Done = true; // Game ends in a draw
            return;
        }
        wxString currText = label->GetLabel();
        if (currText == "") {
            if (currentPlayer % 2 == 0) {
                label->SetLabel("X"); // Set the label text to "X"
                Result->SetLabel("Player O Turn...");
                if (CheckWin(labelId)) { // Check if the current player has won
                    Result->SetLabel("Player X Won!");
                    Result->SetBackgroundColour(wxColor(10, 255, 10)); // Set the result text background color to green
                    Done = true; // Game ends with a win
                }
            }
            else {
                label->SetLabel("O"); // Set the label text to "O"
                Result->SetLabel("Player X Turn...");
                if (CheckWin(labelId)) { // Check if the current player has won
                    Result->SetLabel("Player O Won!");
                    Result->SetBackgroundColour(wxColor(10, 255, 10)); // Set the result text background color to green
                    Done = true; // Game ends with a win

                }
            }
            currentPlayer++;
        }
    }
    event.Skip();
}

bool MainFrame::CheckWin(int ID) {
    int currId = ID - 1;
    // Define winning combinations
    const int winCombinations[8][3] = {
        { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 }, // rows
        { 0, 3, 6 }, { 1, 4, 7 }, { 2, 5, 8 }, // columns
        { 0, 4, 8 }, { 2, 4, 6 }               // diagonals
    };
    for (int i = 0; i < 8; ++i) {
        int first = winCombinations[i][0];
        int second = winCombinations[i][1];
        int third = winCombinations[i][2];
        if (first == currId || second == currId || third == currId) {
            wxString symbol = labels[first]->GetLabel();
            if (!symbol.IsEmpty() && symbol == labels[second]->GetLabel() && symbol == labels[third]->GetLabel()) {
                DrawWinLines(first, third); // Draw lines to indicate the winning combination
                return true; // Game has been won
            }
        }
    }
    return false; // No winning combination found
}

void MainFrame::DrawWinLines(int first, int third) {
    wxClientDC dc(panel); // Create a device context for drawing on the panel
    dc.SetBackgroundMode(wxBRUSHSTYLE_TRANSPARENT);

    int x1 = 150 + (first % 3) * 150;
    int y1 = 150 + first / 3 * 150;
    int x3 = 0;
    int y3 = 0;

    // Determine the coordinates for drawing the lines based on the winning combination
    if (third == 2 || third == 5) {
        x3 = 525;
        x1 = x1 - 75;
    }
    else {
        if (third == 7) {
            x3 = 300;
        }
        else if (third == 6) {
            x3 = 150;
        }
        else if (third == 8 && first == 6) {
            x3 = 525;
            x1 = x1 - 75;
        }
        else {
            x3 = 450;
        }
    }
    if (third == 6 || third == 7) {
        y3 = 525;
        y1 = y1 - 75;
    }
    else {
        if (third == 2) {
            y3 = 150;
        }
        else if (third == 5) {
            y3 = 300;
        }
        else if (third == 8 && first == 2) {
            y3 = 525;
            y1 = y1 - 75;
        }
        else {
            y3 = 450;
        }
    }
    if (first == 0 && third == 8) {
        x1 = 75;
        y1 = 75;
        x3 = 525;
        y3 = 525;
    }
    else if (first == 2 && third == 6) {
        x1 = 75;
        y1 = 525;
        x3 = 525;
        y3 = 75;
    }
    dc.SetPen(wxPen(*wxGREEN, 2)); // Set the pen color and thickness for drawing the lines
    dc.DrawLine(x1, y1, x3, y3); // Draw the lines
}

void MainFrame::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(dynamic_cast<wxPanel*>(event.GetEventObject())); // Create a device context for painting

    int x1 = 225;
    int x2 = 450;
    int y1 = 60;
    int y2 = 540;
    dc.DrawLine(x1, y1, x1, y2); // Draw vertical grid lines
    dc.DrawLine(y1, x1, y2, x1); // Draw horizontal grid lines
    x1 = 375;
    dc.DrawLine(x1, y1, x1, y2); // Draw vertical grid lines
    dc.DrawLine(y1, x1, y2, x1); // Draw horizontal grid lines
}
