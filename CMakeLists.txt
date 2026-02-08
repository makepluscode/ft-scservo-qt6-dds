cmake_minimum_required(VERSION 3.16)
project(ft_scservo_qt6_dds VERSION 1.0.0 LANGUAGES CXX)

# C++17 표준 사용
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/utf-8 /W4)
endif()

# =============================================================================
# RTI Connext DDS 설정
# =============================================================================
set(CONNEXTDDS_DIR "C:/Program Files/rti_connext_dds-7.5.0")
list(APPEND CMAKE_MODULE_PATH "${CONNEXTDDS_DIR}/resource/cmake")

set(CONNEXTDDS_ARCH "x64Win64VS2017")
find_package(RTIConnextDDS REQUIRED)

# =============================================================================
# Qt6 설정
# =============================================================================
find_package(Qt6 REQUIRED COMPONENTS Gui Qml Quick)
qt_standard_project_setup()

# =============================================================================
# IDL 생성 코드
# =============================================================================
set(GEN_SOURCES
    gen/scservo.cxx
    gen/scservoPlugin.cxx
)

include_directories(gen)

# =============================================================================
# ServoDaemon 빌드 설정
# =============================================================================
add_executable(ServoDaemon 
    daemon/main.cpp
    daemon/ServoDaemon.cpp
    daemon/SerialPort.cpp
    daemon/servo/scserial.cpp
    ${GEN_SOURCES}
)

target_link_libraries(ServoDaemon 
    RTIConnextDDS::cpp2_api
    advapi32
)

target_include_directories(ServoDaemon PRIVATE 
    daemon
    daemon/servo
)

# =============================================================================
# ServoGUI 빌드 설정
# =============================================================================
qt_add_executable(ServoGUI 
    gui/main.cpp 
    gui/DdsManager.cpp 
    gui/DdsManager.hpp
    ${GEN_SOURCES}
)

qt_add_qml_module(ServoGUI
    URI scservo
    VERSION 1.0
    QML_FILES Main.qml
)

target_include_directories(ServoGUI PRIVATE 
    gui
)

target_link_libraries(ServoGUI PRIVATE 
    Qt6::Gui 
    Qt6::Qml 
    Qt6::Quick
    RTIConnextDDS::cpp2_api
)

# =============================================================================
# QoS 프로파일
# =============================================================================
file(COPY USER_QOS_PROFILES.xml DESTINATION ${CMAKE_BINARY_DIR})
