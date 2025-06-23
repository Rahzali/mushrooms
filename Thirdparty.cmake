include(FetchContent)

set(BUILD_STATIC ON)

FetchContent_Declare(
        mysqlcpp
        GIT_REPOSITORY https://github.com/mysql/mysql-connector-cpp.git
        GIT_TAG        9.3.0
)

FetchContent_MakeAvailable(mysqlcpp)

include_directories(
        ${mysqlcpp_SOURCE_DIR}/include
        ${OPENSSL_INCLUDE_DIR}
        ${mysqlcpp_SOURCE_DIR}/common
)