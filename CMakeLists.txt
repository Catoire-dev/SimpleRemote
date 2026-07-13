cmake_minimum_required(VERSION 3.20)

project(SimpleRemote)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(SimpleRemote
    src/main.cpp
    src/http/HttpClient.cpp
)

target_link_libraries(SimpleRemote PRIVATE
    CURL::libcurl
    nlohmann_json::nlohmann_json
)