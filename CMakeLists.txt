cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD d0edc3af-4c50-42ea-a356-e2862fe7a444)

#set(CMAKE_BUILD_TYPE Release)

project(vtr C CXX)

find_package(CURL 8.12.0 REQUIRED)
find_package(PROJ REQUIRED CONFIG)
find_package(ZLIB REQUIRED)
find_package(Protobuf REQUIRED)

file(GLOB VTR_MODULES CONFIGURE_DEPENDS
	core/*.ixx
	formats/mvt/*.ixx
	formats/geojson/*.ixx
	geo/*.ixx
	images/*.ixx
	io/*.ixx
	rendering/*.ixx
	unicode/*.ixx
)

file(GLOB VTR_SOURCES CONFIGURE_DEPENDS
	core/*.cpp
	external/json.hpp
	external/sqlite3.c
	formats/mvt/*.cpp
	formats/geojson/*.cpp
	geo/*.cpp
	images/*.cpp
	io/*.cpp
	rendering/*.cpp
	unicode/*.cpp
)

add_library(vtr-core STATIC external/sqlite3.c)

target_sources(vtr-core
	PRIVATE
		${VTR_SOURCES}
	PUBLIC
		FILE_SET cxx_modules
		TYPE CXX_MODULES
		FILES ${VTR_MODULES}
)

set(PROTO_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")

protobuf_generate(
		TARGET vtr-core
		LANGUAGE cpp
		PROTOS  "${CMAKE_CURRENT_SOURCE_DIR}/formats/mvt/vector_tile.proto"
				"${CMAKE_CURRENT_SOURCE_DIR}/formats/mvt/glyphs.proto"
		PROTOC_OUT_DIR "${PROTO_BINARY_DIR}"
		APPEND_PATH
)

target_include_directories(vtr-core
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
		${CMAKE_CURRENT_SOURCE_DIR}/external
		"${PROTO_BINARY_DIR}"
)

target_link_libraries(vtr-core PRIVATE CURL::libcurl)
target_link_libraries(vtr-core PRIVATE PROJ::proj)
target_link_libraries(vtr-core PRIVATE ZLIB::ZLIB)
target_link_libraries(vtr-core PRIVATE protobuf::libprotobuf)


add_subdirectory(apps/qt)

#foreach(module IN LISTS VTR_MODULES)
#	message(STATUS " ${module}")
#endforeach()

#message(${VTR_SOURCES})

#add_executable(vtr)
