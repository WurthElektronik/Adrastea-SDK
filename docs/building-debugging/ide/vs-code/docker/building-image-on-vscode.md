# Adrastea-I – Firmware Build Guide Using Docker Toolchain with Visual Studio Code

This repository contains a set of predefined tasks for automating common development and deployment workflows using Docker and shell scripts. The tasks are defined in the `tasks.json` file and can be executed within a development environment.

## Table of Contents
- [Overview](#overview)
- [Task Categories](#task-categories)
  - [Docker Tasks](#docker-tasks)
  - [Local Development Tasks](#local-development-tasks)
- [How to Use](#how-to-use)
- [Task Descriptions](#task-descriptions)

## Overview
The tasks in this repository enable developers to easily execute commands for building, cleaning, debugging, and deploying applications using both local shell scripts and Docker-based workflows.

## Task Categories

### Docker Tasks
These tasks are executed within Docker containers so **you are supposed to set the Docker environment first**
- **Docker-Start_Docker** - Starts the Docker environment.
- **Docker-Clean_build** - Cleans and builds the project using Docker.
- **Docker-Source_analyze** - Runs source code analysis within a Docker container.
- **Docker-Grafana-Dashboard** - Starts a Grafana dashboard.
- **Docker-Build** - Builds the project inside a Docker container.
- **Docker-Create_doxygen_docs** - Generates Doxygen documentation using Docker.
- **Docker-Clean** - Cleans up build folder.
- **Docker-Flash_mcu** - Flashes the MCU using Docker.


## How to Use
To run any of these tasks, use your development environment's task execution feature. If using VS Code, you can run tasks via:

1. Open the Command Palette (`Ctrl+Shift+P` ).
2. Select **Run Task**.
3. Choose the desired task from the list.

Alternatively, you can manually execute the corresponding shell script or Docker command from the terminal.

## Task Descriptions
For more details, refer to the `tasks.json` file in the project.

