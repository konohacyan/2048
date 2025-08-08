cmake_minimum_required(VERSION 3.10)
project(2048Game)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
if(MSVC)
    add_compile_options(/utf-8)
endif()

# 设置Qt的qmake可执行文件路径
if(UNIX)
    # 如果是Unix系统，设置Qt的qmake可执行文件路径
    set(QT_QMAKE_EXECUTABLE "/opt/Qt5.12.0/5.12.0/gcc_64/bin/qmake")
    set(Qt5_DIR "/opt/Qt5.12.0/5.12.0/gcc_64/lib/cmake/Qt5")
    set(CMAKE_PREFIX_PATH "/opt/Qt5.12.0/5.12.0/gcc_64")
elseif(WIN32)
    # 如果是Windows系统，设置Qt的qmake可执行文件路径
    set(QT_QMAKE_EXECUTABLE "D:/Qt/Qt5.0.12/5.12.0/mingw73_64/bin/qmake.exe")
    set(Qt5_DIR "D:/Qt/Qt5.12.0/5.12.0/mingw73_64/lib/cmake/Qt5")
    set(CMAKE_PREFIX_PATH "D:/Qt/Qt5.12.0/5.12.0/mingw73_64")
endif()

find_package(Qt5 COMPONENTS Core Gui Sql Widgets REQUIRED)


# 生成对应的头文件
qt5_wrap_ui(UI_HEADERS ${UI_FILES})

add_executable(2048Game main.cpp Game.cpp
        public_func.h
        public_func.cpp
        public_def.h
        public_def.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Sql
    Qt5::Widgets
)
