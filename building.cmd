@echo off
Setlocal EnableDelayedExpansion

chcp 1251 > nul

for /F "delims=" %%a in ('echo %cd%') do set HOME_DIR=%%a
set EXIT_STATUS=0

for /F "delims=" %%P in ('WHERE /R .\ CMakeLists.txt') do (
    set MY_PATH=%%P
    set MY_PATH=!MY_PATH:CMakeLists.txt=!
    echo Building !MY_PATH!...
    cd !MY_PATH!
    rd /s/q build 2> nul
    cmake -H. -Bbuild > nul
    (cmake --build build --config Debug && color 02 && echo Build completed) || (set EXIT_STATUS=!1! && color 04 && echo Build failed)
    echo.
)

exit !EXIT_STATUS!