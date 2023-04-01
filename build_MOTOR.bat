@echo off
setlocal


rem Pregunta si generar paradas de comprobación entre cada paso
set /p pause_option="> Quieres que se generen pausas? [S/N]: "


rem Fecha inicio: 
set start_time=%time%


rem Elimina si existe el anterior registro
if exist "./build_Output.txt" (

    del "./build_Output.txt"

)


rem Establece las dependencias a tener en cuenta
set deps=Bullet CEGUI FMOD LuaBridge Ogre SDL

rem Borra los registros genereados en las dependencias
for %%i in (%deps%) do (

    if exist ".\%%i\build_Output.txt" ( 
        
        rem Elimina el anterior registro
        del ".\%%i\build_Output.txt"
        
    )

)



rem Establece el tipo de configuración para la ejecución global 
:loop
set /p exec_option="> Quieres que se ejecute en serie o en paralelo? [S/P]: " 

rem Comprueba si ha elegido bien la opción de buildeo: 
if /i "%exec_option%"=="S" ( 

    echo: && echo "> COMENZANDO EN SERIE!!" && echo:

) else if /i "%exec_option%"=="P" (

    echo: && echo "> COMENZANDO EN PARALELO!!" && echo:

) else ( 

    echo: && echo "La opcion %exec_option% no es valida. Prueba otra vez." && echo:
    goto loop

)
if /i "%pause_option%"=="S" ( pause ) 



rem Plataforma destino: 
set "platform=x64"



echo: && echo "> Buscando la version mas actualizada de Visual Studio DCP..." && echo:

rem Búsqueda y guardado de la ruta al shell Developer command prompt for Visual Studio 2022 más actualizado
call "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath > "%temp%\VSWhereOutput.txt"
set /p VS_PATH=<"%temp%\VSWhereOutput.txt"

if /i "%pause_option%"=="S" ( pause )



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



rem Espera hasta que finalicen los scripts 
echo: && echo "> Espere a que finalicen los scripts..." && echo: 

rem Comprueba si han terminado todas las build's, se ejecuta hasta que terminan!
cd .\Dependencies

:check
for %%i in (%deps%) do (

    if not exist ".\%%i\build_Output.txt" ( 
        
        rem Esperar 1 segundo antes de volver a comprobar
        timeout /t 1 /nobreak > nul
        goto check 
        
    )

)

cd ..

rem Continuar con el archivo por lotes 
echo: && echo "> Todos los scripts han terminado!!" && echo: 



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



rem LLamada al DCP: Developer Command Prompt
call "%VS_PATH%\Common7\Tools\VsDevCmd.bat"
del "%temp%\VSWhereOutput.txt"



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


rem Fecha final: 
set end_time=%time%


echo:
echo ----------------------------
echo Fecha inicio: %start_time% 
echo Fecha final: %end_time% 
echo:


rem Check final
echo "> Build %project% finalizada [ inicio: %start_time% // finalizado: %end_time% ]" > "./build_Output.txt"

pause
endlocal