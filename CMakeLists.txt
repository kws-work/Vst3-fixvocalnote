cmake_minimum_required(VERSION 3.22)
project(FixVocalNote VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(FIXVOCALNOTE_JUCE_VERSION "8.0.7" CACHE STRING "JUCE version used when auto-fetching")

if(DEFINED JUCE_DIR)
  message(STATUS "Using JUCE_DIR=${JUCE_DIR}")
  add_subdirectory(${JUCE_DIR} JUCE)
else()
  message(STATUS "JUCE_DIR not set, fetching JUCE ${FIXVOCALNOTE_JUCE_VERSION} from GitHub")
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
