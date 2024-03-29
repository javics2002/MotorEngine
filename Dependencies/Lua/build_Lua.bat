@echo off

set "origen=.\Src\lib\" 
set "destino=.\bin" 

cd .\Src

msbuild "lua.sln" /p:configuration=Debug
msbuild "lua.sln" /p:configuration=Release

cd..

rem Copia los binarios .dll
robocopy /NJH %origen%\Debug\ %destino%\Debug\ *.dll
robocopy /NJH %origen%\Release\ %destino%\Release\ *.dll