
mkdir x86\release
cd x86\release
conan install ..\..\.. -s compiler="Visual Studio" -s arch="x86" -s arch_build="x86" -s compiler.version="12" -s build_type="Release"
cmake -DBUILD_TESTING=1 -G "Visual Studio 12 2013" ..\..\..
cd ..\..

mkdir x86\debug
cd x86\debug
conan install ..\..\.. -s compiler="Visual Studio" -s arch="x86" -s arch_build="x86" -s compiler.version="12" -s build_type="Debug"
cmake -DBUILD_TESTING=1 -G "Visual Studio 12 2013" ..\..\..
cd ..\..


mkdir x64\release
cd x64\release
conan install ..\..\.. -s compiler="Visual Studio" -s arch="x86_64" -s arch_build="x86_64" -s compiler.version="12" -s build_type="Release"
cmake -DBUILD_TESTING=1 -G "Visual Studio 12 2013 Win64" ..\..\..
cd ..\..

mkdir x64\debug
cd x64\debug
conan install ..\..\.. -s compiler="Visual Studio" -s arch="x86_64" -s arch_build="x86_64" -s compiler.version="12" -s build_type="Debug"
cmake -DBUILD_TESTING=1 -G "Visual Studio 12 2013 Win64" ..\..\..
cd ..\..