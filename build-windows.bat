@echo off

set BUILD_TYPE=Release
if "%1"=="--debug" (
    set BUILD_TYPE=Debug
)

echo -- Build type: %BUILD_TYPE%

if not exist build (
    mkdir build
)
cd build

cmake -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ..
cmake --build .

echo ============ Running CocCoc-HomeTest ============
.\CocCoc-HomeTest
