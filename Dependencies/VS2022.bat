@echo off

set "RootDirectory=%CD%" 
set "zip=.\7zip\7za.exe"

rem Búsqueda y ejecución del shell VS más actualizado
call "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath > "%temp%\VSWhereOutput.txt"

set /p VS_PATH=<"%temp%\VSWhereOutput.txt"
del "%temp%\VSWhereOutput.txt"

rem Apertura del developer command prompt for VS 2022 (con final abierto)
cmd /k call "%VS_PATH%\Common7\Tools\VsDevCmd.bat"