cls
del *.obj
if exist OGL.exe (
    del *.exe

    del *.res
)

for /r src %%f in (*.cpp) do (
    cl.exe /c /EHsc /I "C:\OpenGL\glew\include" "%%f"
)

rc.exe OGL.rc

link.exe *.obj  OGL.res /OUT:OGL.exe /LIBPATH:C:\OpenGL\glew\lib\Release\x64 user32.lib gdi32.lib /subsystem:windows

if exist OGL.exe (
    del *.obj
    OGL.exe
)

