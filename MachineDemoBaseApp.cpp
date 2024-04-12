/**
 * @file MachineDemoBaseApp.cpp
 * @author Charles Owen
 */

#include "pch.h"

#include <wx/xrc/xmlres.h>
#include <wx/stdpaths.h>
#include <wx/cmdline.h>

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
    auto machine = CreateMachineIsolator(resourcesDir, nullptr);

    auto frame = new MachineDemoMainFrame(machine, &mController);
    frame->Show(true);

    mController.Execute();
    return true;
}

/**
 * Handle exit from application
 * @return Any exit code
 */
int MachineDemoBaseApp::OnExit()
{
    return wxAppBase::OnExit();
}

/**
 * Handle a passed-in command line
 * @param parser The command line parser object
 */
void MachineDemoBaseApp::OnInitCmdLine(wxCmdLineParser& parser)
{
    wxAppBase::OnInitCmdLine(parser);
    mController.OnInitCmdLine(parser);
}

/**
 * Indicate that the command line arguments have been parsed
 * @param parser The command line parser object
 * @return true if successful
 */
bool MachineDemoBaseApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
    if(!mController.OnCmdLineParsed(parser))
    {
        return false;
    }

    return wxAppBase::OnCmdLineParsed(parser);
}
