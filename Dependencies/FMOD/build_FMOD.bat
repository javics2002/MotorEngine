@echo off

set /p pause_option="> Quieres que se generen pausas? [S/N]: "
set "project=FMOD Studio API Windows"
set "src=FMOD_Src"
set "platform=x64"

rem Herramientas necesarias:
rem 1. start        -- Ejecutar un proceso en segundo plano
rem 2. robocopy     -- Copiar de forma efectiva varios ficheros
rem 3. xcopy        -- Copiar ficheros concretos


rem Instala el software con sigilo
if not exist "src/uninstall.exe" (

    start /wait fmodstudioapi20213win-installer.exe /S 
    ren "%project%" src

    echo: && echo "> El codigo fuente %src% ha sido creado." && echo: 
    
) else (
    echo: && echo "> El codigo %src% fuente ya existe." && echo: 
)
if /i "%pause_option%"=="S" ( pause ) 

rem Copia el contenido de FMOD_Src a src para tratar todas las depencias por igual
if exist "./%src%/" (
    md "src" 2>nul 
    robocopy "%src%" .\src\ /E
)



set "origen=.\src\api\core\lib\%platform%\" 
set "destino=.\bin\" 

if not exist "bin/" (

    md "bin" 2>nul     

    rem Copia los binarios de configuración Debug
    md "%destino%\Debug" 2>nul
    xcopy "%origen%\*L.dll" "%destino%\Debug\" /Y
    xcopy "%origen%\*L_vc.lib" "%destino%\Debug\" /Y

    rem Copia los binarios de configuración Release
    md "%destino%\Release" 2>nul
    xcopy "%origen%\fmod.dll" "%destino%\Release\" /Y
    xcopy "%origen%\fmod_vc.lib" "%destino%\Release\" /Y

    echo: && echo "> Los binarios de %target% has sido reservados." && echo:     
) else (
    echo: && echo "> Los binarios de %target% ya estaban reservados." && echo: 
)
if /i "%pause_option%"=="S" ( pause ) 