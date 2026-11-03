#cmake_minimum_required(VERSION 3.30)

#project(vtr-qt LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui OpenGL OpenGLWidgets Widgets)

qt_standard_project_setup()


file(GLOB APP_FILES CONFIGURE_DEPENDS *.ixx *.cpp *.h)

# Append Qt-specific RenderTarget subclass.
file(GLOB QT_RT_FILES CONFIGURE_DEPENDS
	${PROJECT_SOURCE_DIR}/rendering/qt/*.ixx
	${PROJECT_SOURCE_DIR}/rendering/qt/*.cpp
)

list(APPEND APP_FILES ${QT_RT_FILES})

set(APP_MODULES ${APP_FILES})
list(FILTER APP_MODULES INCLUDE REGEX "\\.ixx$")
set(APP_SOURCES ${APP_FILES})
list(FILTER APP_SOURCES EXCLUDE REGEX "\\.ixx$")

#add_executable(vtr-qt)

message("APP_SOURCES:")
message(${APP_SOURCES})

qt_add_executable(vtr-qt)

target_sources(vtr-qt PRIVATE ${APP_SOURCES})

target_sources(vtr-qt
	PRIVATE
		FILE_SET modules TYPE CXX_MODULES
		BASE_DIRS ${PROJECT_SOURCE_DIR}
		FILES ${APP_MODULES}
)

#target_include_directories(vtr-qt PRIVATE ${PROJECT_SOURCE_DIR})

target_link_libraries(vtr-qt
    PRIVATE
		vtr-core
        Qt6::Core Qt6::Gui Qt6::OpenGL Qt6::OpenGLWidgets Qt6::Widgets
)



