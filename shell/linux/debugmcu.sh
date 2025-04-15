#!/bin/bash

echo "Available serial ports (excluding Bluetooth):"

# List serial devices (typically /dev/ttyUSB* or /dev/ttyACM*)
for device in /dev/ttyUSB* /dev/ttyACM*; do
    if [[ -e "$device" ]]; then
        # Skip known Bluetooth devices if needed
        if [[ "$device" != *"rfcomm"* ]]; then
            echo "$device"
        fi
    fi
done

read -p "Enter the desired serial port (e.g., /dev/ttyUSB0): " COM_PORT


if [[ ! -e "$COM_PORT" ]]; then
    echo "Error: $COM_PORT does not exist!"
    exit 1
fi

# Run the tool (adjust binary name and path)
./shell/utils/debugmcu -L "$COM_PORT" -B 115200 -F none <binary_name_path>
