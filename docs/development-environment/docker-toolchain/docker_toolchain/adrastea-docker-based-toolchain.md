# Importing a Docker-Based Toolchain Without Using a Registry

## Table of Contents
1. [Overview](#overview)
2. [Importing a Docker Image](#importing-a-docker-image)
   - [Example](#example)
3. [Verifying the Imported Image](#verifying-the-imported-image)
   - [Expected Output](#expected-output)
4. [Running the Imported Image](#running-the-imported-image)
5. [Setting Up Your Environment Variables](#setting-up-your-environment-variables)
   - [Windows](#windows)
   - [Linux](#linux)

## Overview
This guide explains how to import a Docker image from a file without using a registry. This is useful when transferring images between systems without internet access or when working with private images locally.

## Importing a Docker Image

First, download the Würth eiSos-specific Docker image from the following [link](https://www.we-online.com/res/wco/Adrastea/adrastea-gcc-arm-none-eabi-7-2018-q2-update-linux.tar
 ) and load it into Docker on your host machine.

```sh
docker load -i <my_image>.tar
```

### Example:
```sh
docker load -i adrastea-gcc-arm-none-eabi-7-2018-q2-update-linux.tar
```
This command loads the Docker image into the local Docker environment.

## Verifying the Imported Image
After importing, verify that the image is available by running:
```sh
docker images
```

### Expected Output:
```
REPOSITORY                                              TAG       IMAGE ID          CREATED      SIZE
adrastea-gcc-arm-none-eabi-7-2018-q2-update-linux     latest     <unique_image_id>   2 hours ago   780MB
```

## Running the Imported Image
To run a container from the imported image, use the following command:
```sh
docker run -d --name adrastea-gcc-arm-none-eabi-7-2018-q2-update-linux adrastea-gcc-arm-none-eabi-7-2018-q2-update-linux:latest
```

## Setting Up Your Environment Variables

### Windows
To configure your workspace environment variables, navigate to:
**docker\windows\gcc-arm-none-eabi-7-2018-q2-update-linux\env.cmd**

```cmd
@echo off

REM The name of the image
set DOCKER_IMAGE_TAG=adrastea-gcc-arm-none-eabi-7-2018-q2-update-linux
set DOCKER_IMAGE_VERSION=latest

exit /b
```

### Linux
For Linux, navigate to:
**docker/unix/gcc-arm-none-eabi-7-2018-q2-update-linux/env.sh**

```sh
#!/bin/bash

# The name of the image
docker_image_tag="gcc-arm-none-eabi-7-2018-q2-update-linux"
docker_image_version="latest"
```


