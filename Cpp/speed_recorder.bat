@echo off

echo "Running...."

set "Directory=Recordings"
md "%Directory%" 2>nul
if not exist "%Directory%\*" (
    echo Failed to create directory "%Directory%"
    pause
    goto :EOF
)

RMServer.exe | filter.exe