@echo off

set "current_directory=%~dp0"

call %current_directory%\env.cmd

goto :main

:main


docker-compose -f %current_directory%\docker-compose.yml up -d



