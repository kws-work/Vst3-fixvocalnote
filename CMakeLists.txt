cmake_minimum_required(VERSION 3.22)
project(FixVocalNote VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(FIXVOCALNOTE_JUCE_VERSION "8.0.7" CACHE STRING "JUCE version used when auto-fetching")
set(FIXVOCALNOTE_JUCE_ARCHIVE "" CACHE FILEPATH "Local JUCE source archive (.tar.gz/.zip) used for offline builds")

if(DEFINED JUCE_DIR)
  message(STATUS "Using JUCE_DIR=${JUCE_DIR}")
  add_subdirectory(${JUCE_DIR} JUCE)
elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/third_party/JUCE/CMakeLists.txt")
  message(STATUS "Using vendored JUCE at third_party/JUCE")
  add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/third_party/JUCE" JUCE)
elseif(FIXVOCALNOTE_JUCE_ARCHIVE)
  message(STATUS "Using local JUCE archive: ${FIXVOCALNOTE_JUCE_ARCHIVE}")
  FetchContent_Declare(
    juce
    URL ${FIXVOCALNOTE_JUCE_ARCHIVE}
  )
  FetchContent_MakeAvailable(juce)
else()
  message(STATUS "JUCE_DIR not set, fetching JUCE ${FIXVOCALNOTE_JUCE_VERSION} from GitHub")
  message(STATUS "Hint: if your network blocks github.com, pass -DJUCE_DIR=/path/to/JUCE or -DFIXVOCALNOTE_JUCE_ARCHIVE=/path/to/JUCE.tar.gz")
  FetchContent_Declare(
    juce
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG ${FIXVOCALNOTE_JUCE_VERSION}
    GIT_SHALLOW TRUE
  )
  FetchContent_MakeAvailable(juce)
endif()

juce_add_plugin(FixVocalNote
  COMPANY_NAME "CodexLab"
  BUNDLE_ID com.codexlab.fixvocalnote
  IS_SYNTH FALSE
  NEEDS_MIDI_INPUT FALSE
  NEEDS_MIDI_OUTPUT FALSE
  IS_MIDI_EFFECT FALSE
  EDITOR_WANTS_KEYBOARD_FOCUS FALSE
  COPY_PLUGIN_AFTER_BUILD FALSE
  PLUGIN_MANUFACTURER_CODE Cdex
  PLUGIN_CODE FvNt
  FORMATS VST3
  PRODUCT_NAME "FixVocalNote"
)

target_sources(FixVocalNote
  PRIVATE
    source/PluginProcessor.cpp
    source/PluginProcessor.h
    source/PluginEditor.cpp
    source/PluginEditor.h
)

target_compile_definitions(FixVocalNote
  PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
)

target_link_libraries(FixVocalNote
  PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
  PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)
