@echo off
setlocal

if not exist build (
    mkdir build
)
cd build

cmake ..
if errorlevel 1 exit /b %errorlevel%

cmake --build .
if errorlevel 1 exit /b %errorlevel%

echo.
echo ============ Running CocCoc ============
CocCoc.exe
exit /b 0