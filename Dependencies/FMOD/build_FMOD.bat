@echo off
setlocal


rem Fecha inicio: 
set start_time=%time%


rem Elimina si existe el anterior registro
if exist "./build_Output.txt" (

    del "./build_Output.txt"

)


rem Configuración de paradas
if /I "%1"=="" (

    set /p pause_option="> Quieres que se generen pausas? [S/N]: "

) else ( set "pause_option=%1" )


rem Plataforma utilizada
set "platform=x64"
set "target=FMOD"


rem Herramientas necesarias:
rem 1. xcopy        -- Copiar ficheros concretos


set "origen=.\src\api\core\lib\%platform%\" 
set "origenstudio=.\src\api\studio\lib\%platform%\" 
set "destino=.\bin\" 


if not exist "bin/" (

    md "bin" 2>nul

    rem Copia los binarios de configuración Debug
    md "%destino%\Debug" 2>nul
    xcopy "%origen%\fmodL.dll" "%destino%\Debug\" /Y
    xcopy "%origenstudio%\fmodstudioL.dll" "%destino%\Debug\" /Y

    rem Copia los binarios de configuración Release
    md "%destino%\Release" 2>nul
    xcopy "%origen%\fmod.dll" "%destino%\Release\" /Y
    xcopy "%origenstudio%\fmodstudio.dll" "%destino%\Release\" /Y

    echo: && echo "> Los binarios (.dll) de %target% han sido copiados." && echo:     
) else (
    echo: && echo "> Los binarios (.dll) de %target% ya estaban copiados." && echo: 
)
if /i "%pause_option%"=="S" ( pause ) 


rem Fecha final: 
set end_time=%time%


echo:
echo ----------------------------
echo Fecha inicio: %start_time% 
echo Fecha final: %end_time% 
echo:


rem Check final
echo "> Build %target% finalizada [ inicio: %start_time% // finalizado: %end_time% ]" > "./build_Output.txt"


rem pause 
endlocal