@echo off

set /p filename="Enter filename to save to: "
echo saving to %filename%.csv

set "Directory=Recordings"
md "%Directory%" 2>nul
if not exist "%Directory%\*" (
    echo Failed to create directory "%Directory%"
    pause
    goto :EOF
)

RMServer.exe | filter.exe >> Recordings/%filename%.csv
