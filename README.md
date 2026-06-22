protoc installed with 'winget install protoc'

protoc --cpp_out=. vector_tile.proto


vcpkg installed via:

https://learn.microsoft.com/en-us/vcpkg/get_started/get-started-msbuild?pivots=shell-cmd

protobuf installed via:

vcpkg install protobuf:x64-windows


vcpkg install zlib

vcpkg install curl


To set up a temporary web server for serving data files:

python -m http.server 8000

