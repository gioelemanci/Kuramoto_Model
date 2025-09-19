@echo off
setlocal

echo [1] Configuring project...
cmake -S . -B build

echo [2] Building project...
cmake --build build

echo [3] Copying SFML DLLs...
set SFML_DLL_DIR=build\_deps\sfml-build\lib
set BIN_DIR=build\bin

copy "%SFML_DLL_DIR%\sfml-graphics-2.dll" "%BIN_DIR%" >nul
copy "%SFML_DLL_DIR%\sfml-window-2.dll" "%BIN_DIR%" >nul
copy "%SFML_DLL_DIR%\sfml-system-2.dll" "%BIN_DIR%" >nul
copy "%SFML_DLL_DIR%\sfml-audio-2.dll" "%BIN_DIR%" >nul

echo [4] Running simulation...
cd %BIN_DIR%
.\Kuramoto_Model.exe

echo [4.1] Running tests...
.\Kuramoto_Model_tests.exe

endlocal