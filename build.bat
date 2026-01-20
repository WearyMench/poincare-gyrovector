@echo off
REM Build script for Poincaré Ball Gyrovector Algebra Library (Windows)

echo Building Poincaré Ball Gyrovector Algebra Library...
echo.

REM Check if CMake is available and find it
set CMAKE_CMD=
where cmake >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    set CMAKE_CMD=cmake
    echo Found CMake in PATH.
    goto :found_cmake
)

REM Try Program Files location
if exist "C:\Program Files\CMake\bin\cmake.exe" (
    set CMAKE_CMD=C:\Program Files\CMake\bin\cmake.exe
    echo Found CMake at: C:\Program Files\CMake\bin
    goto :found_cmake
)

REM Try Program Files (x86) location  
if exist "C:\Program Files (x86)\CMake\bin\cmake.exe" (
    set CMAKE_CMD=C:\Program Files (x86)\CMake\bin\cmake.exe
    echo Found CMake at: C:\Program Files (x86)\CMake\bin
    goto :found_cmake
)

REM CMake not found
echo ERROR: CMake is not installed or not in your PATH.
echo.
echo Please install CMake using one of the following methods:
echo.
echo Option 1: Install via Chocolatey (recommended)
echo   choco install cmake
echo.
echo Option 2: Install via winget
echo   winget install Kitware.CMake
echo.
echo Option 3: Download from official website
echo   https://cmake.org/download/
echo   Make sure to add CMake to PATH during installation.
echo.
echo Option 4: Install via Visual Studio Installer
echo   Open Visual Studio Installer, modify your installation,
echo   and add "Desktop development with C++" workload.
echo.
echo After installing CMake, restart your terminal and try again.
exit /b 1

:found_cmake
REM Check CMake version
echo Checking CMake version...
"%CMAKE_CMD%" --version
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to run CMake.
    exit /b 1
)
echo.

REM Create build directory
if not exist build mkdir build
cd build

REM Configure with CMake
echo Configuring with CMake...
"%CMAKE_CMD%" ..
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: CMake configuration failed.
    echo Please check the error messages above.
    cd ..
    exit /b 1
)

REM Build
echo.
echo Building...
"%CMAKE_CMD%" --build . --config Release
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: Build failed.
    echo Please check the error messages above.
    cd ..
    exit /b 1
)

echo.
echo Build complete!
echo.
echo To run C++ example:
echo   build\examples\Release\example_cpp.exe
echo.
echo To run Python example:
echo   python examples\example.py

cd ..
