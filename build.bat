@echo off


call vendor\premake\premake5.exe vs2022
call msbuild -nologo -v:m OpenGL.sln
