/**
 * @file MachineDemoMainFrame.cpp
 * @author Charles Owen
 */

#include "pch.h"

#include <wx/xrc/xmlres.h>
#include <wx/stdpaths.h>

#include "MachineDemoMainFrame.h"
#include "ControlPanel.h"
#include "MachineView.h"
#include "AboutDialog.h"

/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";


/**
 * Constructor
 */
MachineDemoMainFrame::MachineDemoMainFrame(std::shared_ptr<IMachineIsolator> machineIsolator)
{
    wxXmlResource::Get()->LoadFrame(this, nullptr, L"MainFrame");

    // Where do the images come from?
    auto standardPaths = wxStandardPaths::Get();
    auto imagesDir = standardPaths.GetResourcesDir().ToStdWstring() + ImagesDirectory;

    auto sizer = new wxBoxSizer( wxVERTICAL );

    mMachineView = new MachineView(this, machineIsolator, imagesDir);
    mControlPanel = new ControlPanel(this);

    sizer->Add(mMachineView, 1, wxEXPAND | wxALL);
    sizer->Add(mControlPanel, 0, wxEXPAND | wxALL);

    SetSizer( sizer );
    Layout();

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MachineDemoMainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MachineDemoMainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_CLOSE_WINDOW, &MachineDemoMainFrame::OnClose, this);
}


void MachineDemoMainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}


void MachineDemoMainFrame::OnAbout(wxCommandEvent& event)
{
    AboutDialog aboutDlg(this);
    aboutDlg.ShowModal();
}


void MachineDemoMainFrame::OnClose(wxCloseEvent& event)
{
    mControlPanel->Stop();
    Destroy();
}





