@echo off
REM ############################################################################

goto start

REM ############################################################################

:help
echo Usage: %0 (x86^|armeabi-v7a)
echo Build  Protean3D Android for x86/armeabi-v7a
echo.
exit /b

REM ############################################################################

:start
setlocal EnableDelayedExpansion

set ANDROID_API_VERSION=android-21
set ANDROID_SDK_ROOT=c:\android\sdk
set ANDROID_TARGET_ARCH=%1
set ANDROID_BUILD_TOOLS_REVISION=21.1.2
set ANDROID_NDK_PATH=c:\android\ndk\10d
set ANDROID_TOOLCHAIN_VERSION=4.9
set ANDROID_NDK_HOST=windows-x86_64
set MSYSSHELL=v:\mingw\msys\bin\sh.exe


if "%GNUWIN32%"=="" (
  set GNUWIN32=v:\bin\gnuwin32
)
set GNUWIN32BIN=%GNUWIN32%\bin

if "%1"=="" goto help
if "%1"=="/?" goto help
if "%1"=="help" goto help
if "%1"=="-help" goto help
if "%1"=="--help" goto help


pushd %CD%

cd ..
set BUILD_DIR=build-creator
test -d %BUILD_DIR% || mkdir %BUILD_DIR%

cd %BUILD_DIR%

echo %BUILD_DIR%
echo %PWD%

cmake -G"MinGW Makefiles" ^
      -DCMAKE_TOOLCHAIN_FILE=../src/cmake/android.toolchain.cmake ^
      -DANDROID_NDK=%ANDROID_NDK_PATH% ^
      -DCMAKE_BUILD_TYPE=Debug ^
      -DANDROID_ABI=%1 ^
      -DCMAKE_MAKE_PROGRAM="v:/mingw/mingw64/bin/mingw32-make.exe" ^
      ../src
REM cmake --build .

popd

REM qtdesigner (and other?) needs this structure
REM %GNUWIN32BIN%\cp -rv %INSTALL_DIR%\plugins\platforms %INSTALL_DIR%\bin
REM %GNUWIN32BIN%\rm -rf .\src