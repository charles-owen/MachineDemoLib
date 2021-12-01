/**
 * @file Controller.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "Controller.h"

#include <wx/cmdline.h>

Controller::Controller(MachineDemoMainFrame* mainFrame, MachineView* machineView, ControlPanel* controlPanel) :
    mMainFrame(mainFrame), mMachineView(machineView), mControlPanel(controlPanel)
{
    wxCmdLineParser parser(wxTheApp->argc, wxTheApp->argv);


}
