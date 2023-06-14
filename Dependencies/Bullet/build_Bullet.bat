@echo off

rem Ruta actual y herramienta cmake
set "RootDirectory=%CD%"
set "cmake=..\CMake\bin\cmake.exe"

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



rem Release
if not exist "build\lib\Release\%target%.lib" ( 

    rem Compilación en modo Release
    msbuild build\%project%.sln /t:ALL_BUILD /p:Configuration=Release /p:Platform=x64 /p:PlatformToolset=v143 

    echo: && echo "> Build %project% solucion en modo release compilada." && echo: 
) else (
    echo: && echo "> Build %project% solucion en modo release ya existe." && echo: 
)



rem Debug
if not exist "build\lib\Debug\%target%_Debug.lib" ( 

    rem Compilación en modo Debug
    msbuild build\%project%.sln /t:ALL_BUILD /p:Configuration=Debug /p:Platform=x64 /p:PlatformToolset=v143 

    echo: && echo "> Build %project% solucion en modo debug compilada." && echo: 
) else (
    echo: && echo "> Build %project% solucion en modo debug ya existe." && echo: 
)

:end