@echo off

set /p pause_option="> Quieres que se generen pausas? [S/N]: "
set "RootDirectory=%CD%"

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
set "project=Tests\Lua54" 
set "target=Lua_54"
set "src=LuaBridge" 
set "repo=https://github.com/vinniefalco/LuaBridge" 



rem Download  
if not exist "src/CMakeLists.txt" (

    rem Descarga recursiva del repositorio y los posibles submódulos
    git clone --recursive %repo%

    ren "%src%" src
    rmdir /s /q "src\.git"

    echo: && echo "> El codigo fuente %src% ha sido creado." && echo:     
) else (
    echo: && echo "> El codigo %src% fuente ya existe." && echo: 
)
if /i "%pause_option%"=="S" ( pause )



rem Build  
if not exist "build/%src%.sln" (

    mkdir build
    cd build

    rem Build del proyecto usando CMake
    cmake ..\src -G "Visual Studio 17 2022"

    echo: && echo "> La build %src% ha sido creada." && echo: 
) else (
    echo: && echo "> La build %src% ya existe." && echo: 
)
if /i "%pause_option%"=="S" ( pause )



rem Muestra la ubicación actual
cd %RootDirectory%
echo: && echo "> Directorio actual: %CD%\" && echo: 
if /i "%pause_option%"=="S" ( pause )


rem Prepara los directorios finales
mkdir bin
mkdir bin\Release
mkdir bin\Debug



if not exist "bin\Release\%target%.lib" ( 
    
    rem Compilación en modo Release
    msbuild build\%project%.vcxproj /t:Build /p:Configuration=Release /p:Platform=x64 /p:OutDir=..\..\bin\Release\ /p:TargetName=%target% 

    echo: && echo "> Biblioteca %target% release generada." && echo: 
) else (
    echo: && echo "> La biblioteca %target% release ya existe." && echo: 
)
if /i "%pause_option%"=="S" ( pause )



if not exist "bin\Debug\%target%_d.lib" ( 
    
    rem Compilación en modo Debug
    msbuild build\%project%.vcxproj /t:Build /p:Configuration=Debug /p:Platform=x64 /p:OutDir=..\..\bin\Debug\ /p:TargetName=%target%_d 
    
    echo: && echo "> Biblioteca %target% debug generada." && echo: 
) else (
    echo: && echo "> La biblioteca %target% debug ya existe." && echo: 
)
if /i "%pause_option%"=="S" ( pause )