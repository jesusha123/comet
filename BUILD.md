# Build

### macOS

- Install macOS developer tools
  - `xcode-select --install`
- Install Qt 6 SDK via Qt Online Installer
- Install CMake
- Install vcpkg
  - `git clone https://github.com/microsoft/vcpkg`
  - `./vcpkg/bootstrap-vcpkg.sh`
- Add the following line to `arm64-osx-dynamic.cmake` and `x64-osx-dynamic.cmake` files under `vcpkg/triplets/community:
  - `set(VCPKG_BUILD_TYPE release)`
- Generate Makefile
```sh
# macOS arm64
cmake . -DCMAKE_PREFIX_PATH="/Users/max/Qt/6.6.2/macos/lib/cmake/Qt6" -DCMAKE_OSX_ARCHITECTURES="arm64" -DCMAKE_TOOLCHAIN_FILE=/Users/max/dev/misc/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=arm64-osx-dynamic

# macOS x86_64
cmake . -DCMAKE_PREFIX_PATH="/Users/max/Qt/6.6.2/macos/lib/cmake/Qt6" -DCMAKE_OSX_ARCHITECTURES="x86_64" -DCMAKE_TOOLCHAIN_FILE=/Users/max/dev/misc/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-osx-dynamic
```
- Make application
```sh
make
```
- Run application
```sh
open ./Comet.app
```

### Windows

- Install Visual Studio 2022 Community Edition 
- Install Qt 6 SDK via Qt Online Installer
- Install CMake
  - `winget install -e --id Kitware.CMake`
- Install vcpkg
  - `git clone https://github.com/microsoft/vcpkg` 
  - `.\vcpkg\bootstrap-vcpkg.bat`
- Use Qt MSVC terminal to run the next commands
- Prepare MSVC environment
  - `"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64`
- Generate Makefile
```sh
cmake . -DCMAKE_TOOLCHAIN_FILE="C:\Users\chuy_\dev\vcpkg\scripts\buildsystems\vcpkg.cmake" -DCMAKE_OSX_ARCHITECTURES="x86_64" -DVCPKG_TARGET_TRIPLET=x64-windows-release
```
- Build
  - `msbuild Comet.sln /property:Configuration=Release`
