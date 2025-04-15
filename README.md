# Adrastea-I SDK

![Alt text](docs/general/images/image.png)
- [Adrastea-I SDK](#adrastea-i-sdk)
- [About](#about)
- [Features Used by This SDK](#features-used-by-this-sdk)
- [Prerequisites](#prerequisites)
  - [Prerequisite: Access to the Sony Altair SDK](#prerequisite-access-to-the-sony-altair-sdk)
  - [Prerequisite: Must-Have](#prerequisite-must-have)
  - [Quick Start Guide](#quick-start-guide)
  - [Sony Altair ALT125X – Standard Toolchain Installation Guide](#sony-altair-alt125x--standard-toolchain-installation-guide)
    - [Sony Altair ALT125X – Firmware Build Guide with Eclipse](#sony-altair-alt125x--firmware-build-guide-with-eclipse)
    - [Sony Altair ALT125X – Firmware Debugging Guide with Eclipse](#sony-altair-alt125x--firmware-debugging-guide-with-eclipse)
  - [Adrastea-I – Standard Toolchain Installation Guide with Visual Studio Code](#adrastea-i--standard-toolchain-installation-guide-with-visual-studio-code)
    - [Adrastea-I – Firmware Build Guide with Visual Studio Code](#adrastea-i--firmware-build-guide-with-visual-studio-code)
    - [Adrastea-I – Firmware Debugging Guide with Visual Studio Code](#adrastea-i--firmware-debugging-guide-with-visual-studio-code)
  - [Adrastea-I Docker-Based Toolchain and Utilities](#adrastea-i-docker-based-toolchain-and-utilities)
    - [Prerequisites](#prerequisites-1)
    - [Adrastea-I – Docker-Based Toolchain Installation](#adrastea-i--docker-based-toolchain-installation)
    - [Adrastea-I – Firmware Build Guide Using Docker Toolchain with Eclipse](#adrastea-i--firmware-build-guide-using-docker-toolchain-with-eclipse)
    - [Adrastea-I – Firmware Build Guide Using Docker Toolchain with Visual Studio Code](#adrastea-i--firmware-build-guide-using-docker-toolchain-with-visual-studio-code)
- [Telemetry and Dashboarding via Grafana through Docker](#telemetry-and-dashboarding-via-grafana-through-docker)
- [SW Modules / SBOM Overview](#sw-modules--sbom-overview)
- [Common Error Cases](#common-error-cases)
- [Legal Disclaimer](#legal-disclaimer)



# About

This repository contains the Software development kit for the [Adrastea-I Cellular module](https://www.we-online.com/en/components/products/ADRASTEA-I). It guides you the process of installing the tool chain, the IDE and provides the example source code for developing embedded applications on the Adrastea-I platform.

The Adrastea-I module is a compact LTE-M/NB-IoT cellular module with integrated GNSS, an ARM Cortex-M4, and 1MB Flash memory for customer-developed applications. Based on the Sony Altair ALT1250 chipset, the Adrastea-I module provides AT-command-based multi-band configurability, enabling international, multi-regional coverage in LTE Cat M1 / NB1 radio access technologies.

Adrastea-I includes a fully integrated global navigation satellite system solution that supports GPS and GLONASS positioning systems.

> [!NOTE]  
> This repository is intended for use by embedded software developers for developing applications on the Adrastea-I module.
> 

> [!NOTE]  
> **Quick start for the Adrastea-I FeatherWing Kit:**
> 
>A [separate repository](https://github.com/WurthElektronik/Adrastea-FeatherWing-Kit) which step by step instructions to take Adrastea-I FeatherWing kit into operation can be found under, 
> https://github.com/WurthElektronik/Adrastea-FeatherWing-Kit

# Features Used by This SDK

This SDK enables customers to develop applications for Adrastea, allowing them to take advantage of Würth eiSos Sensor SDK capabilities.

- ✅ Modular and scalable IoT architecture  
- ✅ Support for multiple sensors  
- ✅ Secure communication (TLS, MQTT, etc.)  
- ✅ Integration with cloud platforms (AWS IoT, Azure IoT Hub, KaaIoT, Mosquitto)  
- ✅ Docker-based toolchain for easy development and Docker-based Grafana and telemetry for dashboarding.

# Prerequisites

## Prerequisite: Access to the Sony Altair SDK

To use the Sony Altair SDK, you must first obtain access. Please register and follow the enrollment process by visiting the link below. Once enrolled, you will be able to download the necessary tools and documentation. It may take 3–5 working days.

[Sign Up for Sony Altair SDK](https://developer.sony.com/sign-up)

> ⚠️ It may take 3–5 working days.  
> ⚠️ Please note that the following steps require access to the Sony GitHub repository. You cannot proceed further without this access. You will also need local admin rights, and certain ports must not be blocked by your company's firewall or GPOs.

## Prerequisite: Must-Have

> ℹ️ Hardware Requirements for Docker Engine:
> - Minimum 16GB RAM (32GB recommended)  
> - At least 4 logical CPU cores

> ℹ️ User Knowledge Requirements:
> - Proficiency in C, C++, JSON, YAML, Python, and Bash/Shell script execution
> - Experience with Docker, VS Code, or Eclipse
> - Familiarity with cloud platforms (e.g., AWS, Azure, Mosquitto)

> ℹ️ Access and Credentials:
> - Required credentials for cloud platforms (AWS, Azure, etc.)

> ℹ️ Cellular Connectivity Setup:
> - Ensure proper configuration ([Adrastea Module User Manual](https://www.we-online.com/components/products/manual/2615011136000_Manual-um-adrastea-i-2615011136000-v1-0_rev1.4.pdf))

> ℹ️ SIM card insertion, PIN setup, APN server configuration, etc.

> ℹ️ SIM Card Compatibility:
> - A CAT-M / NB-IoT capable SIM card must be present

## Quick Start Guide

Before starting the SDK installation, you must configure your Adrastea Featherwing module, which comes with the default firmware. After completing these steps, you can proceed to the next stages of the toolchain.

[Adrastea-I FeatherWing Kit ](https://github.com/WurthElektronik/Adrastea-FeatherWing-Kit).

## Sony Altair ALT125X – Standard Toolchain Installation Guide

The official installation instructions for the Sony Altair ALT125X SDK can be found on the [Sony Website](https://developer.sony.com/cellular-iot/developer-docs/).

[Sony Altair ALT125X Development Environment Setup](https://developer.sony.com/cellular-iot/developer-docs)

### Sony Altair ALT125X – Firmware Build Guide with Eclipse

[Sony ALT125X MCU Building Guide on Eclipse](https://developer.sony.com/cellular-iot/developer-docs)

### Sony Altair ALT125X – Firmware Debugging Guide with Eclipse

[Sony ALT125X MCU Debugging Guide on Eclipse](https://developer.sony.com/cellular-iot/developer-docs)

## Adrastea-I – Standard Toolchain Installation Guide with Visual Studio Code

### Adrastea-I – Firmware Build Guide with Visual Studio Code

> ⚠️ The standard MCU Build Guide is already available on [Sony Altair ALT125X Development Environment Setup](https://developer.sony.com/cellular-iot/developer-docs).  
> ⚠️ After completing that step, follow the guide below.

[Adrastea-I - Sony Altair ALT125X MCU Build Guide on VSCode](docs/building-debugging/ide/vs-code/local/building-image-on-vscode.md)

### Adrastea-I – Firmware Debugging Guide with Visual Studio Code

[Adrastea-I - Sony Altair ALT125X MCU Debugging Guide on VSCode](docs/building-debugging/ide/vs-code/local/debugging-on-vscode.md)

## Adrastea-I Docker-Based Toolchain and Utilities 

### Prerequisites

To use the Docker toolchain, you need to set up the Docker Engine on your host machine. Please follow the instructions below.

[Install Docker Engine on Windows and Linux](docs/development-environment/docker-toolchain/docker_toolchain/docker-engine-installation.md)

### Adrastea-I – Docker-Based Toolchain Installation

The Adrastea Docker-Based Toolchain Guide provides step-by-step instructions on setting up and using a Docker-powered development environment. It covers installing Docker, configuring the toolchain, managing dependencies, and running builds within isolated containers. This guide ensures a consistent and efficient workflow across different systems, making development, testing, and deployment more reliable and reproducible.

> ⚠️ Set the minimum memory and CPU parameters in the `<your_workspace>\docker\build_targets\build.yml` file. Increase the values based on your local hardware capabilities (e.g., set memory to 16GB and CPUs to 4.0). The minimum configuration uses 8GB of memory and 1.0 CPU.

[Adrastea Docker-Based Toolchain Guide](docs/development-environment/docker-toolchain/docker_toolchain/adrastea-docker-based-toolchain.md)

### Adrastea-I – Firmware Build Guide Using Docker Toolchain with Eclipse

[Firmware Build Guide Using Docker Toolchain with Eclipse](docs/building-debugging/ide/eclipse/docker/building-image-on-eclipse.md)

### Adrastea-I – Firmware Build Guide Using Docker Toolchain with Visual Studio Code

[Firmware Build Guide Using Docker Toolchain with Visual Studio Code](docs/building-debugging/ide/vs-code/docker/building-image-on-vscode.md)



# Telemetry and Dashboarding via Grafana through Docker

[Adrastea-I Guide for Docker-based Telemetry and Dashboard Tools](docs/docker-telemetry-dashboarding/configuration-grafana-telegraf-influxdb.md)

[Visualizing IoT Data on Grafana](docs/docker-telemetry-dashboarding/visualizing-data.md)

[Grafana Dashboard through Eclipse](docs/building-debugging/ide/eclipse/docker/grafana-dashboarding.md)



# SW Modules / SBOM Overview

Refer to the software modules and their detailed descriptions here: [See SW Modules / SBOM - Sofware Bill of Materials](docs/general/sw-modules.md)

# Common Error Cases

| Error Case                            | Possible Causes and Solutions                                                                                   |
|--------------------------------------|------------------------------------------------------------------------------------------------------------------|
| 🚩 **Git clone does not work**        | ✅ Ensure you have internet access and authorization to access the Sony SDK.                                |
|                                      | ✅ Check firewall settings to ensure Git can connect.                                                      |
|                                      | ✅ Verify that necessary Git ports are open and not blocked.                                               |
| 🚩 **No data uploaded to the cloud** | ✅ Check cellular network quality. Ensure a stable and strong signal.                                      |
|                                      | ✅ Verify that your antenna connection is secure and functional.                                           |


# Legal Disclaimer

THE SOFTWARE AND ITS SOURCE CODE IS PROVIDED "AS IS." YOU ACKNOWLEDGE
THAT WÜRTH ELEKTRONIK EISOS MAKES NO REPRESENTATIONS AND WARRANTIES
OF ANY KIND, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT OF THIRD
PARTY INTELLECTUAL PROPERTY RIGHTS OR THE MERCHANTABILITY OR FITNESS
FOR YOUR INTENDED PURPOSE. WÜRTH ELEKTRONIK EISOS DOES NOT WARRANT
OR REPRESENT THAT ANY LICENSE, EXPRESS OR IMPLIED, IS GRANTED UNDER ANY
PATENT RIGHT, COPYRIGHT, MASK WORK RIGHT, OR OTHER INTELLECTUAL
PROPERTY RIGHT RELATING TO ANY COMBINATION, MACHINE, OR PROCESS IN WHICH
THE WÜRTH ELEKTRONIK EISOS PRODUCT WITH THE INCORPORATED SOFTWARE IS USED.
INFORMATION PUBLISHED BY WÜRTH ELEKTRONIK EISOS REGARDING THIRD-PARTY PRODUCTS OR SERVICES
DOES NOT CONSTITUTE A LICENSE FROM WÜRTH ELEKTRONIK EISOS TO USE SUCH PRODUCTS OR SERVICES,
NOR A WARRANTY OR ENDORSEMENT THEREOF.
