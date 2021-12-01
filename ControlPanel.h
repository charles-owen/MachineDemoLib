/**
 * @file ControlPanel.h
 * @author Charles Owen
 *
 * The machine demonstrator control panel
 */

#ifndef CANADIANEXPERIENCE_CONTROLPANEL_H
#define CANADIANEXPERIENCE_CONTROLPANEL_H

class MachineDemoMainFrame;
class MachineView;


/**
 * The machine demonstrator control panel
 */
class ControlPanel final : public wxPanel {
private:
    void OnFrameSliderChanged(wxCommandEvent& event);
    void OnSpeedSliderChanged(wxCommandEvent& event);
    void OnZoomSliderChanged(wxCommandEvent& event);
    void OnSelectMachine(wxCommandEvent& event);
    void OnRewind(wxCommandEvent& event);
    void OnPlay(wxCommandEvent& event);
    void OnStop(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);

    void SetMachineFrame(int frame);

    /// Pointer to the machine view
    MachineView *mMachineView;

    /// The frame choice slider
    wxSlider *mFrameSlider;

    /// The static control that displays the current frame
    wxStaticText *mFrameNumberCtrl;

    /// The speed selection slider
    wxSlider *mSpeedSlider;

    /// The zoom slider
    wxSlider *mZoomSlider;

    /// The static control that displays the machine number
    wxStaticText *mMachineNumberCtrl;

    /// Machine time control
    wxStaticText *mMachineTimeCtrl;

    /// The timer that allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// Are we playing?
    bool mPlaying = false;

public:
    ControlPanel(MachineDemoMainFrame *mainFrame);

    void Stop();

    void SetFrame(int frame);
};

#endif //CANADIANEXPERIENCE_CONTROLPANEL_H
