/**
 * @file MachineDemoApp.h
 * @author Charles Owen
 *
 * Base class for the MachineDemo application class
 */

#ifndef CANADIANEXPERIENCE_MACHINEDEMOBASEAPP_H
#define CANADIANEXPERIENCE_MACHINEDEMOBASEAPP_H

class IMachineIsolator;

/**
 * Base class for the MachineDemo application class
 * This ia an abstract class.
 */
class MachineDemoBaseApp : public wxApp {
public:
    bool OnInit() override;

    virtual std::shared_ptr<IMachineIsolator> CreateMachineIsolator(std::wstring imagesDir) = 0;
};

#endif //CANADIANEXPERIENCE_MACHINEDEMOBASEAPP_H
