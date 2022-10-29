/**
 * @file IMachineIsolator.h
 * @author Charles Owen
 *
 * Interface for a machine isolator.
 */

#ifndef CANADIANEXPERIENCE_IMACHINEISOLATOR_H
#define CANADIANEXPERIENCE_IMACHINEISOLATOR_H

class IMachineIsolator {
public:
    /**
     * Set the position for the root of the machine
     * @param location The x,y location to place the machine
     */
    virtual void SetLocation(wxPoint location) = 0;

    /**
    * Draw the machine at the currently specified location
    * @param graphics Graphics object to render to
    */
    virtual void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) = 0;

    /**
    * Set the current machine animation frame
    * @param frame Frame number
    */
    virtual void SetMachineFrame(int frame) = 0;

    /**
     * Set the expected frame rate in frames per second
     */
    virtual void SetFrameRate(double rate) = 0;

    /**
    * Set the machine number
    * @param machine An integer number. Each number makes a different machine
    */
    virtual void SetMachineNumber(int machine) = 0;

    /**
     * Get the current machine number
     * @return Machine number integer
     */
    virtual int GetMachineNumber() = 0;

    /**
     * Get the current machine time.
     * @return Machine time in seconds
     */
    virtual double GetMachineTime() = 0;

    /**
     * Display the machine selection dialog box
     * @param parent Parent window for the dialog box
     * @return True if OK pressed
     */
    virtual bool DoDialog(wxWindow* parent) = 0;
};

#endif //CANADIANEXPERIENCE_IMACHINEISOLATOR_H
