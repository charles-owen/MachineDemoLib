/**
 * @file ControlPanel.cpp
 * @author Charles Owen
 */

#include "pch.h"

#include <wx/xrc/xmlres.h>

#include "ControlPanel.h"
#include "MachineDemoMainFrame.h"
#include "MachineView.h"

#include "IMachineIsolator.h"

/// Maximum frame we play to
const int MaxFrame = 300;

/// Maximum possible speed
const double MaxSpeed = 2.0;

/// Minimum possible zoom factor
const double MinZoom = 0.5;

/// Maximum possible zoom factor
const double MaxZoom = 4.0;

/**
 * Constructor
 * @param mainFrame Parent window
 */
ControlPanel::ControlPanel(MachineDemoMainFrame* mainFrame)
{
    mMachineView = mainFrame->GetMachineView();
    auto machine = mMachineView->GetMachineIsolator();

    wxXmlResource::Get()->LoadPanel(this, mainFrame, L"ControlPanel");

    //
    // Frame choice slider
    //
    mFrameSlider = XRCCTRL(*this, "FrameSlider", wxSlider);
    mFrameNumberCtrl = XRCCTRL(*this, "FrameNumber", wxStaticText);
    mFrameSlider->SetMax(MaxFrame);

    Bind(wxEVT_SLIDER, &ControlPanel::OnFrameSliderChanged, this, XRCID("FrameSlider"));

    mMachineView->SetFrame(mFrameSlider->GetValue());

    //
    // Speed slider
    //
    mSpeedSlider = XRCCTRL(*this, "SpeedSlider", wxSlider);
    mSpeedSlider->SetMax(200);
    mSpeedSlider->SetValue(100);

    Bind(wxEVT_SLIDER, &ControlPanel::OnSpeedSliderChanged, this, XRCID("SpeedSlider"));

    mMachineView->SetSpeed(mSpeedSlider->GetValue() * MaxSpeed / mSpeedSlider->GetMax());

    //
    // Zoom slider
    //
    mZoomSlider = XRCCTRL(*this, "ZoomSlider", wxSlider);
    mZoomSlider->SetMax(200);
    mZoomSlider->SetValue((1.0 - MinZoom) * 200 / (MaxZoom - MinZoom));

    Bind(wxEVT_SLIDER, &ControlPanel::OnZoomSliderChanged, this, XRCID("ZoomSlider"));

    //
    // Machine selection
    //
    mMachineNumberCtrl = XRCCTRL(*this, "MachineNumber", wxStaticText);
    mMachineNumberCtrl->SetLabel(wxString::Format(wxT("%i"), machine->GetMachineNumber()));

    Bind(wxEVT_BUTTON, &ControlPanel::OnSelectMachine, this, XRCID("SelectMachine"));

    //
    // Time
    //
    mMachineTimeCtrl = XRCCTRL(*this, "MachineTime", wxStaticText);
    mMachineTimeCtrl->SetLabel(wxString::Format(wxT("%0.2f"),machine->GetMachineTime()));

    //
    // Playback
    //
    Bind(wxEVT_BUTTON, &ControlPanel::OnRewind, this, XRCID("Rewind"));
    Bind(wxEVT_BUTTON, &ControlPanel::OnPlay, this, XRCID("Play"));
    Bind(wxEVT_BUTTON, &ControlPanel::OnStop, this, XRCID("Stop"));
    Bind(wxEVT_TIMER, &ControlPanel::OnTimer, this);

    mTimer.SetOwner(this);
    mStopWatch.Start(0);
    mStopWatch.Pause();
}




/**
 * Handle changes to the frame slider
 * @param event Command event for slider value change
 */
void ControlPanel::OnFrameSliderChanged(wxCommandEvent &event)
{
    auto frame = mFrameSlider->GetValue();
    SetMachineFrame(frame);
    Stop();
}

/**
 * Set the current frame in the machine
 * Sets the machine frame and the current frame and tiem controls
 * @param frame Frame to set
 */
void ControlPanel::SetMachineFrame(int frame)
{
    auto time = mMachineView->SetFrame(frame);
    mFrameNumberCtrl->SetLabel(wxString::Format(wxT("%i"),frame));
    mMachineTimeCtrl->SetLabel(wxString::Format(wxT("%0.2f"), time));
}


/**
 * Handle changes to the frame slider
 * @param event Command event for slider value change
 */
void ControlPanel::OnSpeedSliderChanged(wxCommandEvent &event)
{
    mMachineView->SetSpeed(mSpeedSlider->GetValue() * MaxSpeed / mSpeedSlider->GetMax());
}

/**
 * Handle changes to the frame slider
 * @param event Command event for slider value change
 */
void ControlPanel::OnZoomSliderChanged(wxCommandEvent &event)
{
    mMachineView->SetZoom(MinZoom + mZoomSlider->GetValue() *(MaxZoom - MinZoom) / mZoomSlider->GetMax());
}

/**
 * Handle a Select Machine button press
 * @param event Button press command event
 */
void ControlPanel::OnSelectMachine(wxCommandEvent& event)
{
    auto machine = mMachineView->GetMachineIsolator();
    if(machine->DoDialog(this->GetParent()))
    {
        mMachineNumberCtrl->SetLabel(wxString::Format(wxT("%i"), machine->GetMachineNumber()));
        mMachineView->SetupMachine();
    }
}

/**
 * Handle a rewind button event.
 *
 * Stop any playing that may be active and reset the frame to zero
 *
 * @param event Button event
 */
void ControlPanel::OnRewind(wxCommandEvent& event)
{
    Stop();
    mFrameSlider->SetValue(0);
    SetMachineFrame(0);
}

/**
 * Handle a play button press
 * @param event Button event
 */
void ControlPanel::OnPlay(wxCommandEvent& event)
{
    if(mPlaying)
    {
        // If already playing
        return;
    }

    auto frameRate = mMachineView->GetFrameRate();
    auto time = mMachineView->GetMachineTime();

    mStopWatch.Start(lround(time * 1000));
    mTimer.Start(1000 / frameRate);
}

/**
 * Handle a Stop button press
 * @param event Button event
 */
void ControlPanel::OnStop(wxCommandEvent& event)
{
    Stop();
}

/**
 * Stop any playback animation
 */
void ControlPanel::Stop()
{
    mPlaying = false;
    mTimer.Stop();
    mStopWatch.Pause();
}

/**
 * Handle timer events
 * @param event timer event
 */
void ControlPanel::OnTimer(wxTimerEvent& event)
{
    auto newTime = mStopWatch.Time();
    auto frameRate = mMachineView->GetFrameRate();

    int frame = (int)lround(newTime / 1000.0 * frameRate);
    if(frame >= MaxFrame)
    {
        frame = MaxFrame;
        Stop();
    }

    mFrameSlider->SetValue(frame);
    SetMachineFrame(frame);
}

void ControlPanel::SetFrame(int frame)
{
    mFrameSlider->SetValue(frame);
    SetMachineFrame(frame);
}
