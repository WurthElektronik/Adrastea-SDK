
@echo off

setlocal enabledelayedexpansion

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


shell\\utils\\flashmcu.exe -L %COM_PORT% -B 115200 -F none --IMG <binary_path>
