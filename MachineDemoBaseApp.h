/**
 * @file MachineDemoBaseApp.h
 * @author Charles Owen
 *
 * Base class for the MachineDemo application class
 */

#ifndef CANADIANEXPERIENCE_MACHINEDEMOBASEAPP_H
#define CANADIANEXPERIENCE_MACHINEDEMOBASEAPP_H

#include "Controller.h"

class IMachineIsolator;


/**
 * Base class for the MachineDemo application class
 * This ia an abstract class.
 */
class MachineDemoBaseApp : public wxApp {
private:
    /// The application command-line-based controller
    Controller mController;

public:
    bool OnInit() override;

    virtual std::shared_ptr<IMachineIsolator> CreateMachineIsolator(std::wstring resourcesDir) = 0;

    bool OnCmdLineParsed(wxCmdLineParser & 	parser) override;

    void OnInitCmdLine(wxCmdLineParser& parser) override;
};

#endif //CANADIANEXPERIENCE_MACHINEDEMOBASEAPP_H
