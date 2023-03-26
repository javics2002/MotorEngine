@echo off

set /p pause_option="> Quieres que se generen pausas? [S/N]: "

set "platform=x64"

rem Herramientas necesarias:
rem 1. start        -- Ejecutar un proceso en segundo plano
rem 2. robocopy     -- Copiar de forma efectiva varios ficheros
rem 3. xcopy        -- Copiar ficheros concretos


set "origen=.\src\api\core\lib\%platform%\" 
set "origenstudio=.\src\api\studio\lib\%platform%\" 
set "destino=.\bin\" 

if not exist "bin/" (

    md "bin" 2>nul     

    rem Copia los binarios de configuración Debug
    md "%destino%\Debug" 2>nul
    xcopy "%origen%\*L.dll" "%destino%\Debug\" /Y
    xcopy "%origen%\*L_vc.lib" "%destino%\Debug\" /Y
    xcopy "%origenstudio%\*L.dll" "%destino%\Debug\" /Y
    xcopy "%origenstudio%\*L_vc.lib" "%destino%\Debug\" /Y

    rem Copia los binarios de configuración Release
    md "%destino%\Release" 2>nul
    xcopy "%origen%\fmod.dll" "%destino%\Release\" /Y
    xcopy "%origen%\fmod_vc.lib" "%destino%\Release\" /Y
    xcopy "%origenstudio%\fmodstudio.dll" "%destino%\Release\" /Y
    xcopy "%origenstudio%\fmodstudio_vc.lib" "%destino%\Release\" /Y

    echo: && echo "> Los binarios de %target% has sido reservados." && echo:     
) else (
    echo: && echo "> Los binarios de %target% ya estaban reservados." && echo: 
)
if /i "%pause_option%"=="S" ( pause ) 