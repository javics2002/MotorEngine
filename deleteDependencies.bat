@echo off

title DeleteDependencies

rem Variables de directorio
set OGRE_BUILD_DIR=.\Dependencies\Ogre\build\
set BULLET_BUILD_DIR=.\Dependencies\Bullet\build\
set LUABRIDGE_BUILD_DIR=.\Dependencies\LuaBridge\build\
set FMOD_BUILD_DIR=.\Dependencies\FMOD\bin\
set SDL_BUILD_DIR=.\Dependencies\SDL\build\

set EXES_DIR=.\Exe\
set LIBS_DIR=.\Lib\
set TEMP_DIR=.\Temp\

echo Borrando build de OGRE...
if exist %OGRE_BUILD_DIR% rmdir /s /q %OGRE_BUILD_DIR%
echo Build de OGRE borradas.

echo Borrando build de SDL...
if exist %SDL_BUILD_DIR% rmdir /s /q %SDL_BUILD_DIR%
echo Build de SDL borradas.

echo Borrando build de Bullet...
if exist %BULLET_BUILD_DIR% rmdir /s /q %BULLET_BUILD_DIR%
echo Build de Bullet borrada.

echo Borrando build de FMOD...
if exist %FMOD_BUILD_DIR% rmdir /s /q %FMOD_BUILD_DIR%
echo Build de FMOD borrada.

echo Borrando build de LuaBridge...
if exist %LUABRIDGE_BUILD_DIR% rmdir /s /q %LUABRIDGE_BUILD_DIR%
echo Build de LuaBridge borrada.


echo Borrando la carpeta Lib
if exist %LIBS_DIR% rmdir /s /q %LIBS_DIR%
echo Directorio Lib borrado.

echo Borrando la carpeta Exe
if exist %EXES_DIR% rmdir /s /q %EXES_DIR%
echo Directorio Exe borrado.

echo Borrando la carpeta Temp
if exist %TEMP_DIR% rmdir /s /q %TEMP_DIR%
echo Directorio Temp borrado.


echo Borrado completado.