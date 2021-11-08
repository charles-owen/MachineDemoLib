/**
 * @file MachineView.h
 * @author Charles Owen
 *
 * The view for our machine
 */

#ifndef CANADIANEXPERIENCE_MACHINEVIEW_H
#define CANADIANEXPERIENCE_MACHINEVIEW_H

class MachineDemoMainFrame;
class IMachineIsolator;

/**
 * The view for our machine
 */
class MachineView final : public wxScrolledCanvas {
private:
    void OnPaint(wxPaintEvent& event);

    /// First time we draw
    bool mFirstDraw = true;

    /// The machine we are displaying
    std::shared_ptr<IMachineIsolator> mMachineIsolator;

    /// Current machine frame
    int mFrame = 0;

    /// Machine speed
    double mSpeed = 1.0;

    /// Zoom factor
    double mZoom = 1.0;

    /// Frame rate
    int mFrameRate = 30;

public:
    explicit MachineView(MachineDemoMainFrame *mainFrame, std::shared_ptr<IMachineIsolator> machineIsolator, std::wstring imagesDir);

    void DrawAxis(std::shared_ptr<wxGraphicsContext> graphics);

    double SetFrame(int frame);

    void SetSpeed(double speed);

    void SetZoom(double zoom);

    /**
     * Get the machine we are viewing, as
     * protected by the isolator.
     * @return Machine in an isolator object
     */
    auto GetMachineIsolator() {return mMachineIsolator;}

    double GetMachineTime();

    void SetupMachine();

    /**
     * Get the frame rate
     * @return Frame rate in frames per second
     */
    auto GetFrameRate() const {return mFrameRate;}

};

#endif //CANADIANEXPERIENCE_MACHINEVIEW_H
