cmake_minimum_required(VERSION 3.16)
project(StereoPlugin)

set (CMAKE_CXX_STANDARD 17)

#including CPM.cmake, a package manager:
#https://github.com/TheLartians/CPM.cmake
include(CMake/CPM.cmake)

#Compile commands, useful for some IDEs like VS-Code
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

#Minimum MacOS target, set globally
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Minimum OS X deployment version" FORCE)

option(UniversalBinary "Build universal binary for mac" OFF)

if (UniversalBinary)
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE INTERNAL "")
endif()

#static linking in Windows
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

#Adds all the module sources so they appear correctly in the IDE
set_property(GLOBAL PROPERTY USE_FOLDERS YES)
option(JUCE_ENABLE_MODULE_SOURCE_GROUPS "Enable Module Source Groups" ON)

#Fetching JUCE from git
#IF you want to instead point it to a local version, you can invoke CMake with
#-DCPM_JUCE_SOURCE="Path_To_JUCE"
CPMAddPackage(
        NAME JUCE
        GITHUB_REPOSITORY juce-framework/JUCE
        GIT_TAG origin/develop)

set (BaseTargetName StereoPlugin)
juce_add_plugin("${BaseTargetName}"
        VERSION 0.0.1                               # Set this if the plugin version is different to the project version
        # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
        # ICON_SMALL ...
        COMPANY_NAME "MyCompany"
        IS_SYNTH FALSE
        NEEDS_MIDI_INPUT TRUE
        NEEDS_MIDI_OUTPUT FALSE
        IS_MIDI_EFFECT FALSE
        EDITOR_WANTS_KEYBOARD_FOCUS FALSE
        COPY_PLUGIN_AFTER_BUILD TRUE
        PLUGIN_MANUFACTURER_CODE Juce
        PLUGIN_CODE MIpl
        FORMATS AU VST3 Standalone
        VST3_COPY_DIR "C:\\Program Files\\Common Files\\VST3"
        PRODUCT_NAME "Minimal Plugin Template")
juce_generate_juce_header("${BaseTargetName}")

file(GLOB_RECURSE SUB_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "Source/*.cpp")

target_sources(${BaseTargetName} PRIVATE
        ${SUB_SOURCES})

target_compile_definitions(${BaseTargetName}
        PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)


target_link_libraries(${BaseTargetName} PRIVATE
        juce_audio_formats
        juce_audio_plugin_client
        juce_audio_processors
        juce_audio_utils
        juce_data_structures
        juce_dsp
        juce_graphics
        juce_gui_basics
        juce_gui_extra
        juce_opengl
        juce_recommended_config_flags
        juce_recommended_lto_flags
        juce_recommended_warning_flags
        )
