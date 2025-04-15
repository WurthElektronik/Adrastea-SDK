
@echo off


setlocal enabledelayedexpansion

rem Query the registry for serial ports
for /f "tokens=3" %%a in ('reg query HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM 2^>nul') do (
    set device=%%a
    rem Skip Bluetooth COM ports
    echo !device! | findstr /i "BthModem" > nul
    if errorlevel 1 (
        rem Output COM port if it's not Bluetooth
        echo !device!
    )
)

endlocal

set /p COM_PORT="Enter the desired COM port: "

shell\\utils\\debugmcu_cloudParams.exe -L %COM_PORT% -B 115200 -F none --IMG  <binary_name> ^
--CLOUD_SETTINGS <config_json_path> ^
--DEVICE_CERTIFICATE <device_cert_path> ^
--PRIVATE_KEY <private_key_path>  ^
--ROOT_CERT <root_cert_path>
