@echo off

cd .\Src

msbuild "lua.sln" /p:configuration=Debug
msbuild "lua.sln" /p:configuration=Release
