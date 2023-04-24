@echo off
setlocal


rem Fecha inicio: 
set start_time=%time% 



rem Parámetros de instalación
set "project=MotorEngine" 
set "platform=x64" 
set "deps=Bullet FMOD LuaBridge Ogre SDL" 



rem Formatea la salida de Configuration para el binario final 
if /I "%Configuration%"=="Debug" ( 

    set "target=%project%_d" 

) else if /I "%Configuration%"=="Release" ( 

    set "target=%project%" 

) 



rem Muestra las variables de la configuración del entorno antes de continuar:
echo:
echo      VARIABLES DE ENTORNO PARA LA INSTALACION
echo  ------------------------------------------------ 
echo   GameMachine: %project% 
echo   Dependencies: %deps% 
echo  ------------------------------------------------ 
echo   Platform: %platform% 
echo   Configuration: %Configuration% 
echo  ------------------------------------------------ 
echo   target: %target%.dll 
echo  ------------------------------------------------ 
echo: && pause 



rem Configuración de paradas
if /I "%1"=="" (

    set /p pause_option="> Quieres que se generen pausas? [S/N]: "

) else ( set "pause_option=%1" ) 



rem Elimina si existe el anterior registro
if exist "./build_Output.txt" (

    del "./build_Output.txt" 

)


rem Borra los registros genereados en las dependencias
for %%i in (%deps%) do (

    if exist ".\%%i\build_Output.txt" ( 
        
        rem Elimina el anterior registro
        del ".\%%i\build_Output.txt"
        
    )

) 



:loop
rem Configuración para la ejecución global de los procesos 
if /i "%exec_option%"=="P" (

    echo: && echo "> COMENZANDO EN PARALELO!!" && echo:

) else if /i "%exec_option%"=="S" (  
    
    echo: && echo "> COMENZANDO EN SERIE!!" && echo:

) else (

    set /p exec_option="> Quieres que se ejecute en serie o en paralelo? [S/P]: " 
    goto loop

)
if /i "%pause_option%"=="S" ( pause ) 


rem ----------------------------------------------------------------------------------------------- 


rem Configuración del shell de Visual Studio 
if not exist "%temp%\VSWhereOutput.txt" (

    echo: && echo "> Buscando la version mas actualizada de Visual Studio DCP..." && echo:

    rem Búsqueda y ejecución del shell Developer command prompt for Visual Studio 2022 más actualizado
    call "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath > "%temp%\VSWhereOutput.txt"

) else ( echo: && echo "> Arranque instantaneo!!" && echo: )

set /p VS_PATH=<"%temp%\VSWhereOutput.txt" 

if /i "%pause_option%"=="S" ( pause )



rem Llamadas a la automatización de cada dependencia: 
cd .\Dependencies

cd .\FMOD
echo: && echo "> Instalando: FMOD" && echo: 
if /i "%exec_option%"=="S" ( call .\build_FMOD.bat %pause_option% ) else if /i "%exec_option%"=="P" ( start .\build_FMOD.bat %pause_option% ) 
cd ..

cd .\SDL
echo: && echo "> Instalando: SDL" && echo: 
if /i "%exec_option%"=="S" ( call .\build_SDL.bat %pause_option% ) else if /i "%exec_option%"=="P" ( start .\build_SDL.bat %pause_option% ) 
cd ..

cd .\LuaBridge
echo: && echo "> Instalando: LUA" && echo: 
if /i "%exec_option%"=="S" ( call .\build_LuaBridge.bat %pause_option% ) else if /i "%exec_option%"=="P" ( start .\build_LuaBridge.bat %pause_option% ) 
cd ..

cd .\Ogre
echo: && echo "> Instalando: OGRE" && echo: 
if /i "%exec_option%"=="S" ( call .\build_OGRE.bat %pause_option% ) else if /i "%exec_option%"=="P" ( start .\build_OGRE.bat %pause_option% ) 
cd ..

cd .\Bullet
echo: && echo "> Instalando: BULLET" && echo: 
if /i "%exec_option%"=="S" ( call .\build_BULLET.bat %pause_option% ) else if /i "%exec_option%"=="P" ( start .\build_BULLET.bat %pause_option% ) 
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
        robocopy /NJH "%%d\bin\Debug" "%destino%\Debug" "*.dll"
        if /i "%pause_option%"=="S" ( pause )
    )

    if exist "%%d\bin\Release" (
        robocopy /NJH "%%d\bin\Release" "%destino%\Release" "*.dll"
        if /i "%pause_option%"=="S" ( pause )
    )    
)



rem ( OGRE .cfg ) actualiza los ficheros de configuración de Ogre
set "origen=.\Dependencies\Ogre\" 

rem Copia para ejecutar desde Visual Studio 
echo: && echo "> Copiando ficheros necesarios del motor de renderizado de MotorEngine para: desarrollador." && echo: 
set "destino=.\Projects\Main\" 
robocopy /NJH %origen% %destino% *.cfg 

if /i "%pause_option%"=="S" ( pause ) 

rem Copia para ejecutar directamente 
echo: && echo "> Copiando ficheros necesarios del motor de renderizado de MotorEngine para: build final." && echo: 
set "destino=.\Exe\Main\%platform%\Debug\" 
robocopy /NJH %origen% %destino% *.cfg 
set "destino=.\Exe\Main\%platform%\Release\" 
robocopy /NJH %origen% %destino% *.cfg 

if /i "%pause_option%"=="S" ( pause ) 



rem Llamada al DCP: Developer Command Prompt
call "%VS_PATH%\Common7\Tools\VsDevCmd.bat"
del "%temp%\VSWhereOutput.txt" 


rem Instalación del motor 
echo: && echo "> Instalando: %project%" && echo: 

set "instalar-motor=false" 
if not exist ".\Exe\Main\%platform%\%Configuration%\%target%.dll" ( set "instalar-motor=true" ) 
if /i "%recompile-motor%"=="true" ( set "instalar-motor=true" ) 

if /i "%instalar-motor%"=="true" ( 

    rem Compilación del motor 
    msbuild %project%.sln /t:Main /p:Configuration=%Configuration% /p:Platform=%platform% /p:PlatformToolset=v143 

    echo: && echo "> Instalación de %project% en modo %platform%_%Configuration% completada!" && echo: 
) else (
    echo: && echo "> El motor de videojuegos %GameMachine% en modo %platform%_%Configuration% ya se encontraba instalado." && echo: 
)
if /i "%pause_option%"=="S" ( pause ) 


rem ----------------------------------------------------------------------------------------------- 


rem Fecha final: 
set end_time=%time%


echo:
echo ----------------------------
echo Fecha inicio: %start_time% 
echo Fecha final: %end_time% 
echo:


rem Check final
echo "> Build %project% finalizada [ inicio: %start_time% // finalizado: %end_time% ]" > "./build_Output.txt"

rem pause 
endlocal 
exit 