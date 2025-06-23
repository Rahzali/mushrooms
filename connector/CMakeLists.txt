cmake_minimum_required(VERSION 3.15)
project(test)

set(CMAKE_CXX_STANDARD 20)
set(OPENSSL_ROOT_DIR "C:/Program Files/OpenSSL-Win64")
set(OPENSSL_INCLUDE_DIR "C:/Program Files/OpenSSL-Win64/include")
set(OPENSSL_CRYPTO_LIBRARY "C:/Program Files/OpenSSL-Win64/lib/libcrypto.lib")
set(OPENSSL_SSL_LIBRARY "C:/Program Files/OpenSSL-Win64/lib/libssl.lib")

include(FetchContent)

FetchContent_Declare(
        mysqlcpp
        GIT_REPOSITORY https://github.com/mysql/mysql-connector-cpp.git
        GIT_TAG        9.3.0
)

FetchContent_MakeAvailable(mysqlcpp)

add_executable(test main.cpp)
include_directories("C:/Program Files/MySQL/mysql-connector-c++-9.3.0-winx64/include")
target_link_libraries(test
        mysqlcppconnx
)
