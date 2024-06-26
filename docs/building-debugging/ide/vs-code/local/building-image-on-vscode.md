# Adrastea-I Building an Image Using Visual Studio Code

This repository provides predefined tasks to automate common development and deployment workflows using Docker and shell scripts. The tasks are defined in the `tasks.json` file and can be executed within a development environment.

## Table of Contents
- [Adrastea-I Building an Image Using Visual Studio Code](#adrastea-i-building-an-image-using-visual-studio-code)
  - [Table of Contents](#table-of-contents)
  - [Prerequisite](#prerequisite)
  - [Overview](#overview)
  - [Task Categories](#task-categories)
    - [Local Development Tasks](#local-development-tasks)
  - [How to Use](#how-to-use)

## Prerequisite

> [!WARNING] ⚠️
> Assuming the steps in the official Sony Altair Standard Toolchain Installation were successfully completed, add your toolchain paths to your settings.json file by replacing all occurrences marked as "<Path_to_your>" in the JSON.


```json
{

    "toolchains.mcu_build_tools": "<Path_to_your_mcu_build_tools>",
    "toolchains.arm_toolchain": "<Path_of_arm_toolchain>",
    "terminal.integrated.env.windows": {
        "cortex-debug.JLinkGDBServerPath": "<Path_to_your>\\JLinkGDBServer.exe",
        "cortex-debug.armToolchainPath": "<Path_to_your>\\gcc-arm-none-eabi-10.3-2021.07\\bin",
        "cortex-debug.armGdbPath": "<Path_to_your>\\gcc-arm-none-eabi-10.3-2021.07\\bin",
        "cortex-debug.openocdPath": "<Path_to_your>\\gnu-mcu-eclipse-openocd-0.10.0-8-20180512-1921-win64\\GNU MCU Eclipse\\OpenOCD\\0.10.0-8-20180512-1921\\bin",
        "cortex-debug.showDevDebugOutput": "true"
    },
    
    "terminal.integrated.env.linux": {
        "cortex-debug.JLinkGDBServerPath": "<Path_to_your>/JLinkGDBServer",
        "cortex-debug.armToolchainPath": "<Path_to_your>/gcc-arm-none-eabi",
        "cortex-debug.openocdPath": "<Path_to_your>/openocd",
        "cortex-debug.showDevDebugOutput": "true"
    },
    
    "editor.folding": true,
    "editor.foldingStrategy": "auto",
    "editor.foldImports": true,
    "python.defaultInterpreterPath": "<python2.7_path>"
    
}


```

## Overview
The tasks in this repository allow developers to streamline the process of building, cleaning, debugging, and deploying applications using local shell scripts and Docker.

## Task Categories

### Local Development Tasks
These tasks facilitate compiling, cleaning, and debugging the application using local shell scripts:
- **Local-Clean** - Removes temporary and build files from the local environment.
- **Local-Build** - Compiles and builds the application locally.
- **Local-Flash_Cloud_Config** - Flashes the cloud configuration to the MCU.
- **Local-Flash_MCU** - Uploads the compiled firmware to the MCU.

## How to Use
To execute any of these tasks, utilize your development environment's task execution feature. In Visual Studio Code, follow these steps:

1. Open the Command Palette (`Ctrl+Shift+P`).
2. Select **Run Task**.
3. Choose the desired task from the list.

Alternatively, you can manually execute the corresponding shell script or Docker command via the terminal.
