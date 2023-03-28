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
set "project=cegui" 
set "src=CEGUI" 
set "target=CEGUIBase-0" 



rem Build  
if not exist "build/" (

    mkdir build

    rem Build del proyecto usando CMake
    %cmake% -DCEGUI_SAMPLES_ENABLE_EFFECTS_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_TEXT_DEMO:BOOL="0" ^
    -DCEGUI_SAMPLES_ENABLE_WIDGET_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_LOOKNFEELOVERVIEW_DEMO:BOOL="0" ^
    -DCEGUI_SAMPLES_ENABLE_SCROLLABLEPANE_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_EDITBOX_VALIDATION_DEMO:BOOL="0" ^
    -DCEGUI_BUILD_RENDERER_DIRECT3D11:BOOL="1" -DCEGUI_SAMPLES_ENABLE_COMMON_DIALOGUES_DEMO:BOOL="0" ^
    -DCEGUI_SAMPLES_ENABLE_DEMO6:BOOL="0" -DCEGUI_SAMPLES_ENABLE_DRAGDROP_DEMO:BOOL="0" ^
    -DCMAKE_CONFIGURATION_TYPES:STRING="Debug;Release;" -DCEGUI_SAMPLES_ENABLE_MINESWEEPER_DEMO:BOOL="0" ^
    -DCEGUI_SAMPLES_ENABLE_TREE_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_FONT_DEMO:BOOL="1" ^
    -DCEGUI_SAMPLES_ENABLE_INVENTORY_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_TABCONTROL_DEMO:BOOL="0" ^
    -S ./src -B ./build 

    echo: && echo "> La build %src% ha sido creada." && echo: 
) else (
    echo: && echo "> La build %src% ya existe." && echo: 
)
if /i "%pause_option%"=="S" ( pause )



set "origen=.\build\bin\" 
set "destino=.\bin\Release\" 

rem Release
if not exist "bin\Release\%target%.dll" (


    if not exist "build\bin\%target%.dll" ( 
    
        rem Compilación en modo Release
        msbuild build\%project%.sln /t:ALL_BUILD /p:Configuration=Release /p:Platform=x64 /p:PlatformToolset=v143 

        echo: && echo "> Biblioteca %src% release compilada." && echo: 
    ) else (
        echo: && echo "> La biblioteca %src% release ya existe." && echo: 
    )
    if /i "%pause_option%"=="S" ( pause )


    rem Copia los binarios .dll
    robocopy %origen% %destino% *.dll /XF "*_d.dll"

    echo: && echo "> Los binarios (.dll) de %src% en modo release han sido copiados." && echo: 
) else (
    echo: && echo "> Los binarios (.dll) de %src% en modo release ya estaban copiados." && echo: 
)
if /i "%pause_option%"=="S" ( pause ) 



set "origen=.\build\bin\" 
set "destino=.\bin\Debug\" 

rem Debug
if not exist "bin\Debug\%target%_d.dll" (


    if not exist "build\bin\%target%_d.dll" ( 
    
        rem Compilación en modo Debug
        msbuild build\%project%.sln /t:ALL_BUILD /p:Configuration=Debug /p:Platform=x64 /p:PlatformToolset=v143 
        
        echo: && echo "> Biblioteca %src% debug compilada." && echo: 
    ) else (
        echo: && echo "> La biblioteca %src% debug ya existe." && echo: 
    )
    if /i "%pause_option%"=="S" ( pause )


    rem Copia los binarios .dll
    robocopy %origen% %destino% *_d.dll 

    echo: && echo "> Los binarios (.dll) de %src% en modo debug han sido copiados." && echo: 
) else (
    echo: && echo "> Los binarios (.dll) de %src% en modo debug ya estaban copiados." && echo: 
)
if /i "%pause_option%"=="S" ( pause ) 


rem pause
endlocal 