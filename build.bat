@echo off
if not exist "bin" mkdir "bin"
if not exist "bin\tools" mkdir "bin\tools"
if not exist "bin\config" mkdir "bin\config"
if not exist "bin\assets" mkdir "bin\assets"

echo 1.0.0 > bin\config\version

g++ src/main.cpp -o bin/kefp.exe -std=c++17 -Wl,-subsystem,console
g++ src/updater.cpp -o bin/updater.exe -std=c++17 -Wl,-subsystem,console
g++ src/uninstall.cpp -o bin/uninstall.exe -std=c++17 -Wl,-subsystem,console

g++ src/encrypt.cpp -o bin/tools/encrypt.exe -std=c++17 -Wl,-subsystem,console
g++ src/decrypt.cpp -o bin/tools/decrypt.exe -std=c++17 -Wl,-subsystem,console
g++ src/extra.cpp -o bin/tools/extra.exe -std=c++17 -Wl,-subsystem,console

g++ src/installer.cpp -o kefp-installer.exe -std=c++17 -static 

:: installer is optional, and also this file is made for users to easily build the project themselves, so you guys dont want to struggle to find the compling command

copy /y LICENSE.md bin\assets\LICENSE.md
echo [SUCCESS] KiddoZ Tiered Suite Built.
pause