project(MachineDemoLib VERSION 2.02.00)
configure_file(Config.h.in Config.h)

# Request the required wxWidgets libs
# Turn off wxWidgets own precompiled header system, since
# it doesn't seem to work. The CMake version works much better.
set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

# Include the wxWidgets use file to initialize various settings
include(${wxWidgets_USE_FILE})

# Define a variable containing a list of source files for the project
set(SOURCE_FILES pch.h IMachineSystemIsolator.h
        MachineDemoBaseApp.h MachineDemoBaseApp.cpp
        MachineDemoMainFrame.cpp MachineDemoMainFrame.h
        ControlPanel.cpp ControlPanel.h
        MachineView.cpp MachineView.h
        AboutDialog.cpp AboutDialog.h
        Controller.cpp Controller.h)

# Fetch miniaudio from Github
include(FetchContent)
FetchContent_Declare(
        miniaudio
        GIT_REPOSITORY https://github.com/mackron/miniaudio.git
        GIT_TAG 1778a5e839514f35f41d31449f3573e3adffc51a # Version 0.11.10
)

FetchContent_MakeAvailable(miniaudio)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}" "${miniaudio_SOURCE_DIR}")
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)