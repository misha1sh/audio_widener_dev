# Install script for directory: D:/data/progr/audio_widener/stereo_plugin/JUCE

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/A_STEREO_PLUGIN")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-6.0.5" TYPE FILE FILES
    "D:/data/progr/audio_widener/stereo_plugin/cmake-build-debug/JUCE/tools/JUCEConfigVersion.cmake"
    "D:/data/progr/audio_widener/stereo_plugin/cmake-build-debug/JUCE/tools/JUCEConfig.cmake"
    "D:/data/progr/audio_widener/stereo_plugin/JUCE/extras/Build/CMake/JUCEHelperTargets.cmake"
    "D:/data/progr/audio_widener/stereo_plugin/JUCE/extras/Build/CMake/JUCECheckAtomic.cmake"
    "D:/data/progr/audio_widener/stereo_plugin/JUCE/extras/Build/CMake/JUCEUtils.cmake"
    "D:/data/progr/audio_widener/stereo_plugin/JUCE/extras/Build/CMake/LaunchScreen.storyboard"
    "D:/data/progr/audio_widener/stereo_plugin/JUCE/extras/Build/CMake/PIPAudioProcessor.cpp.in"
    "D:/data/progr/audio_widener/stereo_plugin/JUCE/extras/Build/CMake/PIPComponent.cpp.in"
    "D:/data/progr/audio_widener/stereo_plugin/JUCE/extras/Build/CMake/PIPConsole.cpp.in"
    "D:/data/progr/audio_widener/stereo_plugin/JUCE/extras/Build/CMake/RecentFilesMenuTemplate.nib"
    "D:/data/progr/audio_widener/stereo_plugin/JUCE/extras/Build/CMake/UnityPluginGUIScript.cs.in"
    "D:/data/progr/audio_widener/stereo_plugin/JUCE/extras/Build/CMake/copyDir.cmake"
    "D:/data/progr/audio_widener/stereo_plugin/JUCE/extras/Build/CMake/juce_runtime_arch_detection.cpp"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/data/progr/audio_widener/stereo_plugin/cmake-build-debug/JUCE/tools/modules/cmake_install.cmake")
  include("D:/data/progr/audio_widener/stereo_plugin/cmake-build-debug/JUCE/tools/extras/Build/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "D:/data/progr/audio_widener/stereo_plugin/cmake-build-debug/JUCE/tools/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
