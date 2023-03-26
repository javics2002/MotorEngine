@echo off
rem Hace el script más limpio y fácil de leer

rem Pregunta si se desea generar pausas para una instalación supervisada
set /p pause_option="> Quieres que se generen pausas? [S/N]: "

rem Guardar la ruta actual en una variable
set "RootDirectory=%CD%"

rem Búsqueda y ejecución del shell Developer command prompt for Visual Studio 2022 más actualizado
call "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath > "%temp%\VSWhereOutput.txt"

set /p VS_PATH=<"%temp%\VSWhereOutput.txt"
del "%temp%\VSWhereOutput.txt"

call "%VS_PATH%\Common7\Tools\VsDevCmd.bat"

rem Installation settings parameters
set "project=Lua54" 
set "src=LuaBridge" 
set "repo=https://github.com/vinniefalco/LuaBridge"

rem Download  
if not exist "src/" (

    git clone --recursive %repo%
    rmdir /s /q "%src%\.git"

    echo: && echo "> El codigo fuente %src% ha sido creado." && echo: 
    ren %src% src
) else (
    echo: && echo "> El codigo %src% fuente ya existe." && echo: 
)
if /i "%pause_option%"=="S" ( pause )

rem Build  
if not exist "build/" (

    mkdir build
    cd build
    cmake ..\src -G "Visual Studio 17 2022"

    echo: && echo "> La build %src% ha sido creada." && echo: 
) else (
    echo: && echo "> La build %src% ya existe." && echo: 
)
if /i "%pause_option%"=="S" ( pause )

cd %RootDirectory%
echo: && echo "> Directorio actual: %CD%"

mkdir bin
mkdir bin\Release
mkdir bin\Debug

rem Compilación en modo Release
if not exist "bin\Release\%project%.lib" ( 
    
    msbuild build\Tests\%project%.vcxproj /t:Build /p:Configuration=Release /p:Platform=x64 /p:OutDir=..\..\bin\Release\ /p:TargetName=%project% 

    echo: && echo "> Biblioteca %project% release generada." && echo: 
) else (
    echo: && echo "> La biblioteca %project% release ya existe." && echo: 
)
if /i "%pause_option%"=="S" ( pause )

rem Compilación en modo Debug
if not exist "bin\Debug\%project%_d.lib" ( 
    
    msbuild build\Tests\%project%.vcxproj /t:Build /p:Configuration=Debug /p:Platform=x64 /p:OutDir=..\..\bin\Debug\ /p:TargetName=%project%_d 
    
    echo: && echo "> Biblioteca %project% debug generada." && echo: 
) else (
    echo: && echo "> La biblioteca %project% debug ya existe." && echo: 
)
if /i "%pause_option%"=="S" ( pause )
