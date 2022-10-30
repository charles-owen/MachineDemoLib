/**
 * @file MachineDemoBaseApp.cpp
 * @author Charles Owen
 */

#include "pch.h"

#include <wx/xrc/xmlres.h>
#include <wx/stdpaths.h>
#include <wx/cmdline.h>

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "MachineDemoBaseApp.h"
#include "MachineDemoMainFrame.h"

/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";

/**
 * Initialize the application
 * @return True if successful
 */
bool MachineDemoBaseApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    // Initialize the audio engine
    auto result = ma_engine_init(NULL, &mAudioEngine);
    if (result != MA_SUCCESS)
    {
        wxString msg;
        msg.Printf(L"Unable to initialize miniaudio engine - %d", result);
        wxMessageBox( msg, wxT("miniaudio failure"), wxICON_ERROR);
        return false;
    }

    // Get pointer to XML resource system
    auto xmlResource = wxXmlResource::Get();

    // Initialize XRC handlers
    xmlResource->InitAllHandlers();

    // Load all XRC resources from the program resources
    auto standardPaths = wxStandardPaths::Get();
    if (!wxXmlResource::Get()->LoadAllFiles(standardPaths.GetResourcesDir() + "/xrc"))
    {
        return false;
    }

    // Create the machine isolator containing a machine
    auto resourcesDir = standardPaths.GetResourcesDir().ToStdWstring();
    auto machine = CreateMachineIsolator(resourcesDir, &mAudioEngine);

    auto frame = new MachineDemoMainFrame(machine, &mController);
    frame->Show(true);

    mController.Execute();
    return true;
}

/**
 * Handle exit from application
 * @return
 */
int MachineDemoBaseApp::OnExit()
{
    ma_engine_uninit(&mAudioEngine);
    return wxAppBase::OnExit();
}

void MachineDemoBaseApp::OnInitCmdLine(wxCmdLineParser& parser)
{
    wxAppBase::OnInitCmdLine(parser);
    mController.OnInitCmdLine(parser);
}

bool MachineDemoBaseApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
    if(!mController.OnCmdLineParsed(parser))
    {
        return false;
    }

    return wxAppBase::OnCmdLineParsed(parser);
}
