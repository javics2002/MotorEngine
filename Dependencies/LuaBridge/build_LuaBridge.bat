@echo off
setlocal


rem Configuración de paradas
if /I "%1"=="" (

    set /p pause_option="> Quieres que se generen pausas? [S/N]: "

) else ( set "pause_option=%1" )


rem Ruta actual y herramienta cmake
set "RootDirectory=%CD%"
set "cmake=..\CMake\bin\cmake.exe"


rem Herramientas necesarias:
rem 1. git          -- Descargar repositorios
rem 2. cmake        -- Generar builds configuradas
rem 3. msbuild      -- Compilar usando las herramientas de visual studio



rem Búsqueda y ejecución del shell Developer command prompt for Visual Studio 2022 más actualizado
call "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath > "%temp%\VSWhereOutput.txt"

set /p VS_PATH=<"%temp%\VSWhereOutput.txt"
del "%temp%\VSWhereOutput.txt"

call "%VS_PATH%\Common7\Tools\VsDevCmd.bat"



rem Parámetros de instalación
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

    rem Build del proyecto usando CMake
    %cmake% -DCMAKE_CONFIGURATION_TYPES:STRING="Debug;Release;" ^
    -S ./src -B ./build 

    echo: && echo "> La build %src% ha sido creada." && echo: 
) else (
    echo: && echo "> La build %src% ya existe." && echo: 
)
if /i "%pause_option%"=="S" ( pause )



rem Release
if not exist "build\Tests\Release\%project%.lib" ( 
    
    rem Compilación en modo Release
    msbuild build\Tests\%project%.vcxproj /t:Build /p:Configuration=Release /p:Platform=x64 /p:PlatformToolset=v143 

    echo: && echo "> Biblioteca %project% release compilada." && echo: 
) else (
    echo: && echo "> La biblioteca %project% release ya existe." && echo: 
)
if /i "%pause_option%"=="S" ( pause )



rem Debug
if not exist "build\Tests\Debug\%project%.lib" ( 
    
    rem Compilación en modo Debug
    msbuild build\Tests\%project%.vcxproj /t:Build /p:Configuration=Debug /p:Platform=x64 /p:PlatformToolset=v143 
    
    echo: && echo "> Biblioteca %project% debug compilada." && echo: 
) else (
    echo: && echo "> La biblioteca %project% debug ya existe." && echo: 
)
if /i "%pause_option%"=="S" ( pause ) 


rem pause 
endlocal