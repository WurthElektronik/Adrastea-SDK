@echo off


REM The name of the image
@echo setting off the dashboard parameters

set ECLIPSE_MOSQUITTO_DOCKER_IMAGE_TAG=eclipse-mosquitto
set ECLIPSE_MOSQUITTO_DOCKER_IMAGE_VERSION=latest

set INFLUXDB_DOCKER_IMAGE_TAG=influxdb
set INFLUXDB_DOCKER_IMAGE_VERSION=1.8

set TELEGRAF_DOCKER_IMAGE_TAG=telegraf
set TELEGRAF_DOCKER_IMAGE_VERSION=latest

set GRAFANA_DOCKER_IMAGE_TAG=grafana/grafana
set GRAFANA_DOCKER_IMAGE_VERSION=latest

exit /b