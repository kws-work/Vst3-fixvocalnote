#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="${ROOT_DIR}/build"
JUCE_VERSION="8.0.7"

echo "[FixVocalNote] build root: ${ROOT_DIR}"

cmake_args=("-S" "${ROOT_DIR}" "-B" "${BUILD_DIR}" "-DCMAKE_BUILD_TYPE=Release")

if [[ -n "${JUCE_DIR:-}" ]]; then
  echo "[FixVocalNote] using JUCE_DIR from environment: ${JUCE_DIR}"
  cmake_args+=("-DJUCE_DIR=${JUCE_DIR}")
elif [[ -f "${ROOT_DIR}/third_party/JUCE/CMakeLists.txt" ]]; then
  echo "[FixVocalNote] using vendored JUCE at third_party/JUCE"
elif [[ -f "${ROOT_DIR}/third_party/JUCE-${JUCE_VERSION}.tar.gz" ]]; then
  echo "[FixVocalNote] using local JUCE archive third_party/JUCE-${JUCE_VERSION}.tar.gz"
  cmake_args+=("-DFIXVOCALNOTE_JUCE_ARCHIVE=${ROOT_DIR}/third_party/JUCE-${JUCE_VERSION}.tar.gz")
else
  echo "[FixVocalNote] no local JUCE found; CMake will try fetching from GitHub"
  echo "[FixVocalNote] if this fails with proxy/403, provide one of:"
  echo "  1) JUCE_DIR=/absolute/path/to/JUCE"
  echo "  2) third_party/JUCE/ (vendored source)"
  echo "  3) third_party/JUCE-${JUCE_VERSION}.tar.gz"
fi

cmake "${cmake_args[@]}"
cmake --build "${BUILD_DIR}" --config Release -j

echo "[FixVocalNote] done"
echo "[FixVocalNote] expected artifact: ${BUILD_DIR}/FixVocalNote_artefacts/Release/VST3/FixVocalNote.vst3"
