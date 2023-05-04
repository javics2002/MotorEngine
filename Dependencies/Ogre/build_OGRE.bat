@echo off

rem Fecha inicio: 
set start_time=%time%

rem Ruta actual y herramienta cmake
set "RootDirectory=%CD%"
set "cmake=..\CMake\bin\cmake.exe"


rem Herramientas necesarias:
rem 1. curl             -- Parecido a powershell Invoke-Request, solicitar una descarga web
rem 2.a. unzip          -- Descompresor de ficheros .zip más eficiente (no logro generar la build) 
rem 2.b. 7zip           -- Descompresor de ficheros .zip y .tar muy eficiente! 
rem 2.c. powershell     -- Uso de la herramienta Expand-Archive, descomprimir ficheros .zip 
rem 3. cmake            -- Generar builds configuradas
rem 4. msbuild          -- Compilar usando las herramientas de visual studio



rem Configuración del shell de Visual Studio 
if not exist "%temp%\VSWhereOutput.txt" (

    echo: && echo "> Buscando la version mas actualizada de Visual Studio DCP..." && echo:

    rem Búsqueda y ejecución del shell Developer command prompt for Visual Studio 2022 más actualizado
    call "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath > "%temp%\VSWhereOutput.txt"

) else ( echo: && echo "> Arranque instantaneo!!" && echo: )

set /p VS_PATH=<"%temp%\VSWhereOutput.txt"
call "%VS_PATH%\Common7\Tools\VsDevCmd.bat"



rem Parámetros de instalación
set "project=OGRE" 
set "target=OgreMain" 


rem Build  
if not exist "build/" (

    mkdir build

    rem Build del proyecto usando CMake
    %cmake% -DOGRE_INSTALL_SAMPLES:BOOL="0" -DOGRE_BUILD_RENDERSYSTEM_D3D9:BOOL="0" -DCMAKE_CONFIGURATION_TYPES:STRING="Debug;Release;" ^
    -DOGRE_BUILD_PLUGIN_PCZ:BOOL="0" -DOGRE_INSTALL_DEPENDENCIES:BOOL="0" -DOGRE_BUILD_TOOLS:BOOL="0" ^
    -DOGRE_BUILD_COMPONENT_BITES:BOOL="0" -DOGRE_INSTALL_TOOLS:BOOL="0" -DOGRE_BUILD_RENDERSYSTEM_GLES2:BOOL="0" ^
    -DOGRE_BUILD_SAMPLES:BOOL="0" -DOGRE_INSTALL_DOCS:BOOL="0" -DOGRE_INSTALL_PDB:BOOL="0" -DOGRE_BUILD_DEPENDENCIES:BOOL="1" ^
    -DOGRE_BUILD_COMPONENT_BULLET:BOOL="0" -DOGRE_BUILD_RENDERSYSTEM_GL:BOOL="0" -DOGRE_BUILD_RENDERSYSTEM_GL3PLUS:BOOL="0" ^
    -S ./src -B ./build 

    echo: && echo "> La build %project% ha sido creada." && echo: 
) else (
    echo: && echo "> La build %project% ya existe." && echo: 
)



set "origen=.\build\bin\release\" 
set "destino=.\bin\Release\" 

rem Release
if not exist "bin\Release\%target%.dll" (


    if not exist "build\bin\release\%target%.dll" ( 
        
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


set "origen=.\build\bin\debug\" 
set "destino=.\bin\Debug\" 

rem Debug
if not exist "bin\Debug\%target%_d.dll" (


    if not exist "build\bin\debug\%target%_d.dll" ( 
    
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