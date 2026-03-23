@echo off
setlocal

echo [CLEANUP] Deleting previous build data...
if exist "bin" rd /s /q "bin"
if exist "kefp-installer.exe" del /f /q "kefp-installer.exe"

echo [PREP] Rebuilding KEFP Structure...
mkdir "bin"
mkdir "bin\tools"
mkdir "bin\config"
mkdir "bin\assets"

echo 1.5.0 > bin\config\version

echo [COMPILING] Building KEFP Engines...
g++ src/main.cpp -o bin/kefp.exe -std=c++17 -Wl,-subsystem,console
g++ src/updater.cpp -o bin/updater.exe -std=c++17 -Wl,-subsystem,console
g++ src/uninstall.cpp -o bin/uninstall.exe -std=c++17 -Wl,-subsystem,console

g++ src/encrypt.cpp -o bin/tools/encrypt.exe -std=c++17 -Wl,-subsystem,console
g++ src/decrypt.cpp -o bin/tools/decrypt.exe -std=c++17 -Wl,-subsystem,console
g++ src/extra.cpp -o bin/tools/extra.exe -std=c++17 -Wl,-subsystem,console

echo [COMPILING] Building The Installer...
g++ src/installer.cpp -o kefp-installer.exe -std=c++17 -static 

copy /y LICENSE.md bin\assets\LICENSE.md

echo.
echo [SUCCESS] KEFP BUILT SUCCESSFULLY!
echo Root: kefp-installer.exe
echo Internal: bin/
pause