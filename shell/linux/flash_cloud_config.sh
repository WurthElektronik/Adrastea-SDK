#!/bin/bash

echo "Available serial ports (excluding Bluetooth):"

for device in /dev/ttyUSB* /dev/ttyACM*; do
    if [[ -e "$device" && "$device" != *"rfcomm"* ]]; then
        echo "$device"
    fi
done

read -p "Enter the desired serial port (e.g., /dev/ttyUSB0): " COM_PORT

# Check if the input device exists
if [[ ! -e "$COM_PORT" ]]; then
    echo "Error: Serial port '$COM_PORT' does not exist."
    exit 1
fi

./shell/utils/flashcloudconfig -L "$COM_PORT" -B 115200 -F none --CLOUD_SETTINGS <config_file_path>
