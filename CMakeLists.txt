cmake_minimum_required(VERSION 3.5)

project(JsonCpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    data_structures/ByteBuffer.cpp
    data_structures/GenericParser.cpp
    data_structures/Json.cpp
    data_structures/String.cpp
    data_structures/StringView.cpp
    main.cpp)

set(HEADERS
    data_structures/ByteBuffer.h
    data_structures/GenericParser.h
    data_structures/HashTable.h
    data_structures/Json.h
    data_structures/LinkedList.h
    data_structures/String.h
    data_structures/StringView.h)

add_executable(JsonCpp ${SOURCES} ${HEADERS})
