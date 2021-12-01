/**
 * @file Controller.h
 * @author Charles Owen
 *
 * This class supports the control of the
 * application using the command line.
 */

#ifndef CANADIANEXPERIENCE_CONTROLLER_H
#define CANADIANEXPERIENCE_CONTROLLER_H

class MachineDemoMainFrame;
class MachineView;
class ControlPanel;

/**
 * This class supports the control of the
 * application using the command line.
 */
class Controller final {
private:
    /// The MainFrame window
    MachineDemoMainFrame* mMainFrame;

    /// The Machine view
    MachineView* mMachineView;

    /// The control panel
    ControlPanel* mControlPanel;

public:
    Controller(MachineDemoMainFrame* mainFrame, MachineView* machineView, ControlPanel* controlPanel);

};

#endif //CANADIANEXPERIENCE_CONTROLLER_H
