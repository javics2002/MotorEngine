@echo off

rem Plataforma utilizada
set "platform=x64"
set "target=FMOD"

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


:end