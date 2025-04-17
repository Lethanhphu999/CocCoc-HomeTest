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
echo ============ CocCoc-HomeTest ============
CocCoc-HomeTest.exe
exit /b 0