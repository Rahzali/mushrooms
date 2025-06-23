# mushroomApp

## Building

You may need to set DCMAKE_PREFIX_PATH option with path to Qt6.9.0 cmake dir and/or openssl dir

On windows with mingw you may experience issues with zlib adding `/wd4996` flag.
You may need to delete this line then _deps/mysqlcpp-src/cdk/extra/zlib/CMakeLists.txt:30
I'm too lazy to find workaround but feel free.