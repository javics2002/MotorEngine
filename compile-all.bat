@echo off

title CompileAll

rem Variables de batch
set ENGINE_ROOT_DIR=%cd%

set OGRE_COMPILE_DIR=.\Dependencies\Ogre\
set SDL_COMPILE_DIR=.\Dependencies\SDL\
set BULLET_COMPILE_DIR=.\Dependencies\Bullet\
set LUA_COMPILE_DIR=.\Dependencies\Lua\
set FMOD_COMPILE_DIR=.\Dependencies\FMOD\

set EXE_DIR=.\Exe\

set MOTOR_ENGINE_SLN=.\MotorEngine.sln

if not exist %EXE_DIR% mkdir %EXE_DIR%

cd %ENGINE_ROOT_DIR%/%OGRE_COMPILE_DIR%

rem Compilacion y copia de dlls de OGRE
call build_OGRE.bat

cd %ENGINE_ROOT_DIR%/%SDL_COMPILE_DIR%

rem Compilacion y copia de dlls de SDL
call build_SDL.bat

cd %ENGINE_ROOT_DIR%/%BULLET_COMPILE_DIR%

rem Compilacion de Bullet
call build_Bullet.bat

cd %ENGINE_ROOT_DIR%/%LUA_COMPILE_DIR%

rem Compilacion de Lua
call build_Lua.bat

cd %ENGINE_ROOT_DIR%/%FMOD_COMPILE_DIR%

rem Copia de dlls de FMOD
call build_FMOD.bat

cd %ENGINE_ROOT_DIR%

rem Copia de los dlls de bin a Exe
set "ORIGEN=.\Dependencies\*" 
set "DESTINO_RELEASE=.\Exe\Main\x64\Release\" 

for /d %%d in (%origen%) do (
    if exist "%%d\bin\Release" (
        robocopy /NJH "%%d\bin\Release" %DESTINO_RELEASE% *.dll
    )    
)

cd %ENGINE_ROOT_DIR%

rem ( OGRE .cfg ) actualiza los ficheros de configuración de Ogre
set "ORIGEN=.\Dependencies\Ogre\" 

rem Copia para ejecutar directamente 
echo: && echo "> Copiando ficheros necesarios del motor de renderizado de MotorEngine para: build final." && echo: 
robocopy /NJH %origen% %DESTINO_RELEASE% *.cfg 

cd %ENGINE_ROOT_DIR%

rem Compilacion de la solucion del motor
msbuild %MOTOR_ENGINE_SLN% /p:configuration=Release /p:Platform=x64