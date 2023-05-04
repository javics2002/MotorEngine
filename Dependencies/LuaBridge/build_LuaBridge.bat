@echo off

rem Fecha inicio: 
set start_time=%time%

rem Ruta actual y herramienta cmake
set "RootDirectory=%CD%"
set "cmake=..\CMake\bin\cmake.exe"


rem Herramientas necesarias:
rem 1. git          -- Descargar repositorios
rem 2. cmake        -- Generar builds configuradas
rem 3. msbuild      -- Compilar usando las herramientas de visual studio

rem Configuración del shell de Visual Studio 
if not exist "%temp%\VSWhereOutput.txt" (

    echo: && echo "> Buscando la version mas actualizada de Visual Studio DCP..." && echo:

    rem Búsqueda y ejecución del shell Developer command prompt for Visual Studio 2022 más actualizado
    call "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath > "%temp%\VSWhereOutput.txt"

) else ( echo: && echo "> Arranque instantaneo!!" && echo: )

set /p VS_PATH=<"%temp%\VSWhereOutput.txt"
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



rem Build  
if not exist "build/" (

    mkdir build

    rem Build del proyecto usando CMake
    %cmake% -DCMAKE_CONFIGURATION_TYPES:STRING="Debug;Release;" ^
    -DLUABRIDGE_CXX17:BOOL="1" -DBUILD_GMOCK:BOOL="0" -DINSTALL_GTEST:BOOL="0" ^
    -S ./src -B ./build 

    echo: && echo "> La build %src% ha sido creada." && echo: 
) else (
    echo: && echo "> La build %src% ya existe." && echo: 
)



rem Release
if not exist "build\Tests\Release\%project%.lib" ( 
    
    rem Compilación en modo Release
    msbuild build\Tests\%project%.vcxproj /t:Build /p:Configuration=Release /p:Platform=x64 /p:PlatformToolset=v143 

    echo: && echo "> Biblioteca %project% release compilada." && echo: 
) else (
    echo: && echo "> La biblioteca %project% release ya existe." && echo: 
)



rem Debug
if not exist "build\Tests\Debug\%project%.lib" ( 
    
    rem Compilación en modo Debug
    msbuild build\Tests\%project%.vcxproj /t:Build /p:Configuration=Debug /p:Platform=x64 /p:PlatformToolset=v143 
    
    echo: && echo "> Biblioteca %project% debug compilada." && echo: 
) else (
    echo: && echo "> La biblioteca %project% debug ya existe." && echo: 
)


rem Fecha final: 
set end_time=%time%


echo:
echo ----------------------------
echo Fecha inicio: %start_time% 
echo Fecha final: %end_time% 
echo:


rem Check final
echo "> Build %project% finalizada [ inicio: %start_time% // finalizado: %end_time% ]" > "./build_Output.txt"


:end