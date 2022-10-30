/**
 * @file MachineDemoBaseApp.h
 * @author Charles Owen
 *
 * Base class for the MachineDemo application class
 */

#ifndef CANADIANEXPERIENCE_MACHINEDEMOBASEAPP_H
#define CANADIANEXPERIENCE_MACHINEDEMOBASEAPP_H

#include "Controller.h"
#include <miniaudio.h>

class IMachineIsolator;


/**
 * Base class for the MachineDemo application class
 * This ia an abstract class.
 */
class MachineDemoBaseApp : public wxApp {
private:
    /// The application command-line-based controller
    Controller mController;

    /// The audio engine for miniaudio
    ma_engine mAudioEngine;

public:
    bool OnInit() override;
    int OnExit() override;

    /**
     * Create the machine isolator, which contains the machine we are displaying.
     * @param resourcesDir Directory containing the resources for the program
     * @param audioEngine The miniaudio engine
     * @return MachineIsolator object
     */
    virtual std::shared_ptr<IMachineIsolator> CreateMachineIsolator(std::wstring resourcesDir, ma_engine *audioEngine) = 0;

    bool OnCmdLineParsed(wxCmdLineParser & 	parser) override;

    void OnInitCmdLine(wxCmdLineParser& parser) override;
};

#endif //CANADIANEXPERIENCE_MACHINEDEMOBASEAPP_H
