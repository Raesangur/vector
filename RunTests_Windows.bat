goto start

:msvcError
@echo MSVC Compilation Error!
@pause


:start
MSBuild "build/VS2019/vectors.vcxproj"
@if errorlevel 1 goto msvcError

@echo No compilation errors :D
@pause