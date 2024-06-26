# Adrastea-I Guide for Docker-based Telemetry and Dashboard Tools

This guide provides step-by-step instructions for configuring a monitoring dashboard using Docker-based services, including Mosquitto, InfluxDB, Telegraf, and Grafana. The setup includes scripts for Unix and Windows environments to define Docker image tags and versions for each service.

## Table of Contents
- [Overview](#overview)
- [Supported Services](#supported-services)
- [Configuration](#configuration)
  - [Unix (Linux/macOS)](#unix-linuxmacos)
  - [Windows](#windows)
- [Mosquitto and MQTT Broker Configuration](#mosquitto-and-mqtt-broker-configuration)
  - [Mosquitto Settings](#mosquitto-settings)
  - [Default MQTT Broker Settings](#default-mqtt-broker-settings)

## Overview
The Adrastea-I Dashboard Tool Configuration simplifies the setup of a robust monitoring system. By leveraging Docker, developers can easily deploy and manage their MQTT-based telemetry data pipeline, ensuring seamless data collection, storage, and visualization.

## Supported Services
The setup configures the following services:

- **Eclipse Mosquitto** - An MQTT broker for message transmission.
- **InfluxDB** - A time-series database optimized for storing high-frequency telemetry data.
- **Telegraf** - A plugin-driven agent for collecting and sending metrics.
- **Grafana** - A data visualization platform for creating interactive dashboards.

## Configuration
The configuration process involves setting environment variables for Docker images and versions. Separate scripts are provided for Unix-based systems and Windows.

### Unix (Linux)
To configure the environment variables, navigate to:

```
<workspace>/docker/unix/dashboard/env.sh
```

Modify the following script as needed:

```bash
#!/bin/bash

ECLIPSE_MOSQUITTO_DOCKER_IMAGE_TAG="eclipse-mosquitto"
ECLIPSE_MOSQUITTO_DOCKER_IMAGE_VERSION="latest"

INFLUXDB_DOCKER_IMAGE_TAG="influxdb"
INFLUXDB_DOCKER_IMAGE_VERSION="1.8"

TELEGRAF_DOCKER_IMAGE_TAG="telegraf"
TELEGRAF_DOCKER_IMAGE_VERSION="latest"

GRAFANA_DOCKER_IMAGE_TAG="grafana/grafana"
GRAFANA_DOCKER_IMAGE_VERSION="latest"
```

### Windows
To configure the environment variables, navigate to:

```
<workspace>\docker\windows\dashboard\env.cmd
```

Modify the following script as needed:

```bash
@echo off

REM Setting up dashboard parameters
set ECLIPSE_MOSQUITTO_DOCKER_IMAGE_TAG=eclipse-mosquitto
set ECLIPSE_MOSQUITTO_DOCKER_IMAGE_VERSION=latest

set INFLUXDB_DOCKER_IMAGE_TAG=influxdb
set INFLUXDB_DOCKER_IMAGE_VERSION=1.8

set TELEGRAF_DOCKER_IMAGE_TAG=telegraf
set TELEGRAF_DOCKER_IMAGE_VERSION=latest

set GRAFANA_DOCKER_IMAGE_TAG=grafana/grafana
set GRAFANA_DOCKER_IMAGE_VERSION=latest

exit /b
```

## Mosquitto and MQTT Broker Configuration
Properly configuring Mosquitto and MQTT Broker ensures smooth data transmission and telemetry collection.

### Mosquitto Settings
Navigate to:

```
<workspace>/docker/dashboard_configurations/mosquitto.conf
```

Modify the settings as needed:

```bash
persistence true
persistence_location /mosquitto/data/
listener 1883
allow_anonymous true
```

### Default MQTT Broker Settings
Navigate to:

```
<workspace>/docker/dashboard_configurations/telegraf.conf
```

Modify the settings as needed:

```bash
[agent]
interval = "1s"
#flush_interval = "10s"

[[outputs.influxdb]]
urls = ["http://influxdb:<influxdb_port>"]
database = "mqtt_data"
username="<user_name>"
password="<password>"

# Mosquitto Broker
[[inputs.mqtt_consumer]]
servers = ["tcp://<broker_url>:<port-number>"]
topics = []
client_id = ""
data_format = "json"

# Local Mosquitto Broker
[[inputs.mqtt_consumer]]
servers = ["tcp://mosquitto:<port_number>"]
topics = [""]
client_id = "<your_default_client_id>"
data_format = "json"
```



