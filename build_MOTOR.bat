@echo off
setlocal


set start_time=%time%


:loop
set /p pause_option="> Quieres que se generen pausas? [S/N]: " 
set /p exec_option="> Quieres que se ejecute en serie o en paralelo? [S/P]: " 

rem Comprueba si ha elegido bien la opción de buildeo: 
if /i "%exec_option%"=="S" ( 
    echo: && echo "> COMENZANDO EN SERIE!!" && echo:
) else if /i "%exec_option%"=="P" (
    echo: && echo "> COMENZANDO EN PARALELO!!" && echo:
) else ( 
    echo "La opcion %exec_option% no es valida. Prueba otra vez."
)
if /i "%pause_option%"=="S" ( pause ) 

rem Plataforma destino: 
set "platform=x64"


rem Llamadas a la automatización de cada dependencia: 

cd .\Dependencies

cd .\FMOD
echo: && echo "> Instalando _FMOD_" && echo: 
if /i "%exec_option%"=="S" ( call .\build_FMOD.bat %pause_option% ) else if /i "%exec_option%"=="P" ( start .\build_FMOD.bat %pause_option% ) 
cd ..

cd .\SDL
echo: && echo "> Instalando _SDL_" && echo: 
if /i "%exec_option%"=="S" ( call .\build_SDL.bat %pause_option% ) else if /i "%exec_option%"=="P" ( start .\build_SDL.bat %pause_option% ) 
cd ..

cd .\LuaBridge
echo: && echo "> Instalando _LUA_" && echo: 
if /i "%exec_option%"=="S" ( call .\build_LuaBridge.bat %pause_option% ) else if /i "%exec_option%"=="P" ( start .\build_LuaBridge.bat %pause_option% ) 
cd ..

cd .\Ogre
echo: && echo "> Instalando _OGRE_" && echo: 
if /i "%exec_option%"=="S" ( call .\build_OGRE.bat %pause_option% ) else if /i "%exec_option%"=="P" ( start .\build_OGRE.bat %pause_option% ) 
cd ..

cd .\Bullet
echo: && echo "> Instalando _BULLET_" && echo: 
if /i "%exec_option%"=="S" ( call .\build_BULLET.bat %pause_option% ) else if /i "%exec_option%"=="P" ( start .\build_BULLET.bat %pause_option% ) 
cd ..

cd .\CEGUI
echo: && echo "> Instalando _CEGUI_" && echo: 
if /i "%exec_option%"=="S" ( call .\build_CEGUI.bat %pause_option% ) else if /i "%exec_option%"=="P" ( start .\build_CEGUI.bat %pause_option% ) 
cd ..

cd ..


rem Copia iterativa de las .dll's a través del directorio .\Dependencies y sus subdirectorios: 

set "origen=.\Dependencies\*" 
set "destino=.\Exe\Main\%platform%" 

for /d %%d in (%origen%) do (

    if exist "%%d\bin\Debug" (
        robocopy "%%d\bin\Debug" "%destino%\Debug" "*.dll"
        if /i "%pause_option%"=="S" ( pause )
    )

    if exist "%%d\bin\Release" (
        robocopy "%%d\bin\Release" "%destino%\Release" "*.dll"
        if /i "%pause_option%"=="S" ( pause )
    )    

)



rem Búsqueda y ejecución del shell Developer command prompt for Visual Studio 2022 más actualizado
call "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath > "%temp%\VSWhereOutput.txt"

set /p VS_PATH=<"%temp%\VSWhereOutput.txt"
del "%temp%\VSWhereOutput.txt"

call "%VS_PATH%\Common7\Tools\VsDevCmd.bat"



rem Parámetros de instalación
set "project=MotorEngine" 
set "target=MotorEngine"


rem Release
if not exist "Exe\Main\x64\Release\%target%.dll" ( 

    rem Compilación en modo Release
    msbuild %project%.sln /t:Main /p:Configuration=Release /p:Platform=x64 /p:PlatformToolset=v143 

    echo: && echo "> Build %project% solucion en modo release compilada." && echo: 
) else (
    echo: && echo "> Build %project% solucion en modo release ya existe." && echo: 
)
if /i "%pause_option%"=="S" ( pause ) 



rem Debug
if not exist "Exe\Main\x64\Debug\%target%_d.dll" ( 

    rem Compilación en modo Debug
    msbuild %project%.sln /t:Main /p:Configuration=Debug /p:Platform=x64 /p:PlatformToolset=v143 

    echo: && echo "> Build %project% solucion en modo debug compilada." && echo: 
) else (
    echo: && echo "> Build %project% solucion en modo debug ya existe." && echo: 
)
if /i "%pause_option%"=="S" ( pause ) 


set end_time=%time%


rem Convierte las cadenas en objetos de tiempo
for /f "tokens=1-3 delims=:" %%a in ("%start_time%") do (
    set /a "start_seconds=(((%%a*60)+%%b)*60)+%%c"
)
for /f "tokens=1-3 delims=:" %%a in ("%end_time%") do (
    set /a "end_seconds=(((%%a*60)+%%b)*60)+%%c"
)

rem Calcula la diferencia de tiempo
set /a "elapsed_seconds=%end_seconds%-%start_seconds%"

rem Convierte los segundos en minutos y segundos
set /a "elapsed_minutes=%elapsed_seconds%/60"
set /a "elapsed_seconds=%elapsed_seconds%%%60"

echo ----------------------------
echo Fecha inicio: %start_time% 
echo Fecha final: %end_time%
echo Tiempo transcurrido: %elapsed_minutes% minutos y %elapsed_seconds% segundos.
echo Tiempo de ejecucion: %start_time% - %end_time% = %elapsed_minutes% minutos y %elapsed_seconds% segundos. > building-time.log

pause
endlocal