@echo off

title DeleteDependencies

rem Variables de directorio
set OGRE_BUILD_DIR=.\Dependencies\Ogre\build\
set BULLET_BUILD_DIR=.\Dependencies\Bullet\build\
set LUA_BUILD_DIR=.\Dependencies\Lua\Src\lib\
set LUA_TEMPS_DIR=.\Dependencies\Lua\Src\Temp\
set FMOD_BUILD_DIR=.\Dependencies\FMOD\bin\
set SDL_BUILD_DIR=.\Dependencies\SDL\build\

set OGRE_BIN_DIR=.\Dependencies\Ogre\bin\
set SDL_BIN_DIR=.\Dependencies\SDL\bin\

set EXES_DIR=.\Exe\
set LIBS_DIR=.\Lib\
set TEMP_DIR=.\Temp\

echo Borrando build de OGRE...
if exist %OGRE_BUILD_DIR% rmdir /s /q %OGRE_BUILD_DIR%
echo Build de OGRE borradas.

echo Borrando bin de OGRE...
if exist %OGRE_BIN_DIR% rmdir /s /q %OGRE_BIN_DIR%
echo Bin de OGRE borradas.

echo Borrando build de SDL...
if exist %SDL_BUILD_DIR% rmdir /s /q %SDL_BUILD_DIR%
echo Build de SDL borradas.

echo Borrando bin de SDL...
if exist %SDL_BIN_DIR% rmdir /s /q %SDL_BIN_DIR%
echo Bin de SDL borradas.

echo Borrando build de Bullet...
if exist %BULLET_BUILD_DIR% rmdir /s /q %BULLET_BUILD_DIR%
echo Build de Bullet borrada.

echo Borrando build de FMOD...
if exist %FMOD_BUILD_DIR% rmdir /s /q %FMOD_BUILD_DIR%
echo Build de FMOD borrada.

echo Borrando build de Lua...
if exist %LUA_BUILD_DIR% rmdir /s /q %LUA_BUILD_DIR%
echo Build de Lua borrada.

echo Borrando temps de Lua...
if exist %LUA_TEMPS_DIR% rmdir /s /q %LUA_TEMPS_DIR%
echo Temps de Lua borrada.

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