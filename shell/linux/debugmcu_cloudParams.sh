#!/bin/bash

# List available serial ports (excluding Bluetooth devices)
echo "Available serial ports:"
for device in /dev/ttyUSB* /dev/ttyACM*; do
    if [[ -e "$device" ]]; then
        echo "$device"
    fi
done

# Select the desired COM port
read -p "Enter the desired serial port (e.g., /dev/ttyUSB0): " COM_PORT


shell/utils/debugmcu_cloudParams -L "$COM_PORT" -B 115200 -F none \
    --IMG <binary_name_path> \
    --CLOUD_SETTINGS <config_json_path> \
    --DEVICE_CERTIFICATE <device_cert_path> \
    --PRIVATE_KEY <private_key_path> \
    --ROOT_CERT <root_cert_path>
