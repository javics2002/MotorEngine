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
set "project=BULLET_PHYSICS" 
set "src=Bullet" 
set "target=Bullet3Collision"


rem Build  
if not exist "build/%project%.sln" (

    mkdir build

    rem Build del proyecto usando CMake
    %cmake% -DCMAKE_CONFIGURATION_TYPES:STRING="Debug;Release;" ^
    -DBUILD_CPU_DEMOS:BOOL="0" -DBUILD_OPENGL3_DEMOS:BOOL="0"  ^
    -DBUILD_BULLET2_DEMOS:BOOL="0" -DUSE_MSVC_RUNTIME_LIBRARY_DLL:BOOL="1" ^
    -DBUILD_UNIT_TESTS:BOOL="0" ^
    -S ./src -B ./build 

    echo: && echo "> La build %src% ha sido creada." && echo: 
) else (
    echo: && echo "> La build %src% ya existe." && echo: 
)
if /i "%pause_option%"=="S" ( pause )



rem Release
if not exist "build\lib\Release\%target%.lib" ( 

    rem Compilación en modo Release
    msbuild build\%project%.sln /t:ALL_BUILD /p:Configuration=Release /p:Platform=x64 /p:PlatformToolset=v143 

    echo: && echo "> Build %project% solucion en modo release compilada." && echo: 
) else (
    echo: && echo "> Build %project% solucion en modo release ya existe." && echo: 
)
if /i "%pause_option%"=="S" ( pause ) 



rem Debug
if not exist "build\lib\Debug\%target%_Debug.lib" ( 

    rem Compilación en modo Debug
    msbuild build\%project%.sln /t:ALL_BUILD /p:Configuration=Debug /p:Platform=x64 /p:PlatformToolset=v143 

    echo: && echo "> Build %project% solucion en modo debug compilada." && echo: 
) else (
    echo: && echo "> Build %project% solucion en modo debug ya existe." && echo: 
)
if /i "%pause_option%"=="S" ( pause ) 


rem pause 
endlocal