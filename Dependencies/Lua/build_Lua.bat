@echo off

set "origen=.\Src\lib\Release\" 
set "destino=.\bin\Release\" 

cd .\Src

msbuild "lua.sln" /p:configuration=Debug
msbuild "lua.sln" /p:configuration=Release

cd..

rem Copia los binarios .dll
robocopy /NJH %origen% %destino% *.dll