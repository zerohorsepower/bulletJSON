#!/bin/bash

GAME_NAME=$1;
OS_BUILD_TYPE=$2;

# Paths
ROOT_BUILD_DIR="./final-builds";
BUILD_DIR="$OS_BUILD_TYPE";
FULL_BUILD_DIR="$ROOT_BUILD_DIR/$BUILD_DIR";

# Working dir: ./build
# Back to project root dir
cd ..;

################# Clean files

# Clean last build
if [[ -d "$FULL_BUILD_DIR" ]]; then
    rm -rf "$FULL_BUILD_DIR";
fi

# Clean executables from ./build dir
if [[ -d "./build/" ]]; then
    if [[ "$OS_BUILD_TYPE" == "Windows" ]]; then
    
        if [[ -e "./build/$GAME_NAME.exe" ]]; then
            rm "./build/$GAME_NAME.exe";
        fi

    elif [[ "$OS_BUILD_TYPE" == "Linux" ]]; then

        if [[ -e "./build/$GAME_NAME" ]]; then
            rm "./build/$GAME_NAME";
        fi

    elif [[ "$OS_BUILD_TYPE" == "Web" ]]; then

        if [[ -e "./build/$GAME_NAME.html" ]]; then
            rm "./build/$GAME_NAME.html";
            rm "./build/$GAME_NAME.js";
            rm "./build/$GAME_NAME.wasm";
            rm "./build/$GAME_NAME.data";
        fi

    fi
fi

################# Creating new build files

# Create new build dir
if [[ ! -d "$ROOT_BUILD_DIR" ]]; then
    mkdir "$ROOT_BUILD_DIR";
fi
mkdir "$FULL_BUILD_DIR";

# Copy static game assets
mkdir "$FULL_BUILD_DIR/assets";
cp "./assets/texture.png" "$FULL_BUILD_DIR/assets/";
