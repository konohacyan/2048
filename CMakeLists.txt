cmake_minimum_required(VERSION 3.10)
project(2048Game)
set(CMAKE_CXX_STANDARD 17)

# 自动处理MOC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# 检测编译器
if(MSVC)
    message(STATUS "Building with MSVC")
    add_compile_options(/utf-8)
elseif(MINGW)
    message(STATUS "Building with MinGW")
    add_definitions(-DMINGW)
endif()

# 设置Qt的qmake可执行文件路径
if(UNIX)
    # 如果是Unix系统，设置Qt的qmake可执行文件路径
    set(QT_QMAKE_EXECUTABLE "/opt/Qt5.12.0/5.12.0/gcc_64/bin/qmake")
    set(Qt5_DIR "/opt/Qt5.12.0/5.12.0/gcc_64/lib/cmake/Qt5")
    set(CMAKE_PREFIX_PATH "/opt/Qt5.12.0/5.12.0/gcc_64")
elseif(WIN32)
    # 如果是Windows系统，设置Qt的qmake可执行文件路径
    if(DEFINED ENV{QtPath} AND MSVC)
        message(STATUS "Using MSVC, Using Qt ENV QtPath: $ENV{QtPath}")
        set(QT_BIN_DIR "$ENV{QtPath}/msvc2017_64/bin")
        set(Qt5_DIR "$ENV{QtPath}/msvc2017_64/lib/cmake/Qt5")
        set(CMAKE_PREFIX_PATH "$ENV{QtPath}/msvc2017_64")
        set(QT_QMAKE_EXECUTABLE "${QT_BIN_DIR}/qmake.exe")
        # file(COPY 
        #     "${QT_BIN_DIR}/Qt5Gui.dll"
        #     "${QT_BIN_DIR}/Qt5Core.dll"
        #     "${QT_BIN_DIR}/Qt5Widgets.dll"
        #     DESTINATION ${CMAKE_BINARY_DIR})
    else()
        message(STATUS "Using MinGW, Default Qt Path")
        set(QT_QMAKE_EXECUTABLE "D:/Qt/Qt5.0.12/5.12.0/mingw73_64/bin/qmake.exe")
        set(Qt5_DIR "D:/Qt/Qt5.12.0/5.12.0/mingw73_64/lib/cmake/Qt5")
        set(CMAKE_PREFIX_PATH "D:/Qt/Qt5.12.0/5.12.0/mingw73_64")
    endif()
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

find_package(Qt5 COMPONENTS Core Gui Sql Widgets  REQUIRED)


# 生成对应的头文件
qt5_wrap_ui(UI_HEADERS ${UI_FILES})

add_executable(2048Game main.cpp Game.cpp
        public_func.h
        public_func.cpp
        public_def.h
        public_def.cpp)

# Windows 下用 windeployqt 部署 DLL
if(WIN32 AND MSVC)
    find_program(WINDEPLOYQT_EXECUTABLE NAMES windeployqt HINTS "${QT_BIN_DIR}")
    if(WINDEPLOYQT_EXECUTABLE)
        # 定义部署参数：Debug 用 --debug，Release 用 --release
        set(WINDEPLOYQT_MODE "$<$<CONFIG:Debug>:--debug>$<$<CONFIG:Release>:--release>")
        
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${WINDEPLOYQT_EXECUTABLE} 
                --no-translations 
                ${WINDEPLOYQT_MODE} 
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
            COMMENT "Deploying Qt libraries (${CMAKE_BUILD_TYPE}) with windeployqt"
        )
    else()
        message(WARNING "windeployqt not found! Manual DLL deployment required.")
    endif()
endif()

# 设置可执行文件的运行时路径
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    INSTALL_RPATH ${QT_BIN_DIR}
    INSTALL_RPATH_USE_LINK_PATH TRUE
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Sql
    Qt5::Widgets
)

if(MSVC)

elseif(MINGW)
    target_link_options(${PROJECT_NAME} PRIVATE "-Wl,--subsystem,console")
endif()
