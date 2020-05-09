goto start

:msvcError
@echo MSVC Compilation Error!
@pause


:start
MSBuild "build/vectors.vcxproj"
@if errorlevel 1 goto msvcError

@echo No compilation errors :D
@pause