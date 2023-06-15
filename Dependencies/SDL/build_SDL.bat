@echo off

rem Ruta actual y herramienta cmake
set "RootDirectory=%CD%"
set "cmake=..\CMake\bin\cmake.exe"

rem Parámetros de instalación
set "project=SDL3" 
set "src=SDL" 

rem Build  
if not exist "build/%project%.sln" (

    mkdir build

    rem Build del proyecto usando CMake
    %cmake% -DCMAKE_CONFIGURATION_TYPES:STRING="Debug;Release;" ^
    -DSDL_TEST:BOOL="0" ^
    -S ./src -B ./build 

    echo: && echo "> La build %src% ha sido creada." && echo: 
) else (
    echo: && echo "> La build %src% ya existe." && echo: 
)


set "origen=.\build\Release\" 
set "destino=.\bin\Release\" 

rem Release
if not exist "bin\Release\%project%.dll" (
    if not exist "build\Release\%project%.dll" ( 
    
        rem Compilación en modo Release
        msbuild build\%project%.sln /t:ALL_BUILD /p:Configuration=Release /p:Platform=x64 /p:PlatformToolset=v143 

        echo: && echo "> Biblioteca %project% release compilada." && echo: 
    ) else (
        echo: && echo "> La biblioteca %project% release ya existe." && echo: 
    )


    rem Copia los binarios .dll
    robocopy /NJH %origen% %destino% *.dll

    echo: && echo "> Los binarios (.dll) de %project% en modo release han sido copiados." && echo: 
) else (
    echo: && echo "> Los binarios (.dll) de %project% en modo release ya estaban copiados." && echo: 
)

set "origen=.\build\Debug\" 
set "destino=.\bin\Debug\" 

rem Debug
if not exist "bin\Debug\%project%.dll" (


    if not exist "build\Debug\%project%.dll" ( 
    
        rem Compilación en modo Debug
        msbuild build\%project%.sln /t:ALL_BUILD /p:Configuration=Debug /p:Platform=x64 /p:PlatformToolset=v143 
        
        echo: && echo "> Biblioteca %project% debug compilada." && echo: 
    ) else (
        echo: && echo "> La biblioteca %project% debug ya existe." && echo: 
    )


    rem Copia los binarios .dll
    robocopy /NJH %origen% %destino% *.dll

    echo: && echo "> Los binarios (.dll) de %project% en modo debug han sido copiados." && echo: 
) else (
    echo: && echo "> Los binarios (.dll) de %project% en modo debug ya estaban copiados." && echo: 
)

:end