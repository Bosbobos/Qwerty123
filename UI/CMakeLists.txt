cmake_minimum_required(VERSION 3.5)

project(UI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core5Compat)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        loginwindow.cpp
        loginwindow.h
        loginwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(UI
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            registrationwindow.h registrationwindow.cpp registrationwindow.ui
            resources.qrc
            mainwindow.h mainwindow.cpp mainwindow.ui
            addeditdialog.h addeditdialog.cpp addeditdialog.ui
    )
else()
    if(ANDROID)
        add_library(UI SHARED
                ${PROJECT_SOURCES}
        )
    else()
        add_executable(UI
                ${PROJECT_SOURCES}
        )
    endif()
endif()

# Add project dependencies
if (NOT TARGET dbManager)
    add_subdirectory(../dbManager ${CMAKE_BINARY_DIR}/dbManager)
endif()

if (NOT TARGET cryptography)
    add_subdirectory(../cryptography ${CMAKE_BINARY_DIR}/cryptography)
endif()

if (NOT TARGET Configs)
    add_subdirectory(../Configs ${CMAKE_BINARY_DIR}/Configs)
endif()

# Assuming dbManager already includes the Entities library
target_include_directories(UI PUBLIC ../Entities ../dbManager ../cryptography ../Configs)
target_link_libraries(UI PUBLIC dbManager cryptography Configs)
target_link_libraries(UI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_include_directories(UI PRIVATE ${PQXX_INCLUDE_DIRS})
target_link_libraries(UI PRIVATE ${PQXX_LIBRARIES})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.UI)
endif()

set_target_properties(UI PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS UI
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(UI)
endif()