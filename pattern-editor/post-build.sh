#!/bin/bash

GAME_NAME=$1;
OS_BUILD_TYPE=$2;
RELEASE_BUILD_TYPE=$3

# Paths
ROOT_BUILD_DIR="./final-builds";
BUILD_DIR="$OS_BUILD_TYPE";
FULL_BUILD_DIR="$ROOT_BUILD_DIR/$BUILD_DIR";

# Working dir: ./build
# Back to project root dir
cd ..;

# Copy compiled binaries files
if [[ "$OS_BUILD_TYPE" == "Windows" ]]; then
   
    cp "./build/$GAME_NAME.exe" "$FULL_BUILD_DIR/";

elif [[ "$OS_BUILD_TYPE" == "Linux" ]]; then

    cp "./build/$GAME_NAME" "$FULL_BUILD_DIR/";

elif [[ "$OS_BUILD_TYPE" == "Web" ]]; then

    cp "./build/$GAME_NAME.html" "$FULL_BUILD_DIR/index.html";
    cp "./build/$GAME_NAME.js" "$FULL_BUILD_DIR/";
    cp "./build/$GAME_NAME.wasm" "$FULL_BUILD_DIR/";
    cp "./build/$GAME_NAME.data" "$FULL_BUILD_DIR/";

    # The .data file will have all assets already, remove the duplicated asset files
    rm -rf "$FULL_BUILD_DIR/assets";

    # Case Web and Release build, copy to gh-pages dir
    if [[ "$RELEASE_BUILD_TYPE" == "Release" ]]; then

        cp "./build/$GAME_NAME.html" "$FULL_BUILD_DIR/../../docs/index.html";
        cp "./build/$GAME_NAME.js" "$FULL_BUILD_DIR/../../docs/";
        cp "./build/$GAME_NAME.wasm" "$FULL_BUILD_DIR/../../docs/";
        cp "./build/$GAME_NAME.data" "$FULL_BUILD_DIR/../../docs/";

    fi

fi