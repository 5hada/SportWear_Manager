cmake_minimum_required(VERSION 3.16)

project(SportWear_Manager VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

add_subdirectory(external/ElaWidgetTools)

set(PROJECT_SOURCES
        src/main.cpp

        src/app/appContext.h
        src/app/repositoryProvider.h
        src/app/serviceProvider.h

        src/database/databaseManager.h
        src/database/databaseManager.cpp
        src/database/repository/cartRepository.h
        src/database/repository/cartRepository.cpp
        src/database/repository/productRepository.h
        src/database/repository/productRepository.cpp
        src/database/repository/reviewRepository.h
        src/database/repository/reviewRepository.cpp
        src/database/repository/userRepository.h
        src/database/repository/userRepository.cpp
        src/database/repository/wishRepository.h
        src/database/repository/wishRepository.cpp

        src/model/product/category.h
        src/model/product/category.cpp
        src/model/product/cart.h
        src/model/product/cart.cpp
        src/model/product/cartAction.h
        src/model/product/cartItem.h
        src/model/product/item.h
        src/model/product/product.h
        src/model/product/product.cpp
        src/model/product/productItem.h
        src/model/product/receipt.h
        src/model/product/receipt.cpp
        src/model/review.h
        src/model/review.cpp
        src/model/user/userBase.h
        src/model/user/userBase.cpp
        src/model/user/user.h
        src/model/user/user.cpp
        src/model/user/sessionInfo.h

        src/service/cartService.h
        src/service/cartService.cpp
        src/service/accountService.h
        src/service/accountService.cpp
        src/service/orderService.h
        src/service/orderService.cpp
        src/service/productService.h
        src/service/productService.cpp
        src/service/reviewService.h
        src/service/reviewService.cpp
        src/service/wishService.h
        src/service/wishService.cpp

        src/ui/mainwindow.h
        src/ui/mainwindow.cpp
        src/ui/page/loginPage.h
        src/ui/page/loginPage.cpp
        src/ui/page/productDetailPage.h
        src/ui/page/productDetailPage.cpp
        src/ui/page/productGridPage.h
        src/ui/page/productGridPage.cpp
        src/ui/page/receiptPage.h
        src/ui/page/receiptPage.cpp
        src/ui/page/wishPage.h
        src/ui/page/wishPage.cpp
        src/ui/page/profilePanel.h
        src/ui/page/profilePanel.cpp
        src/ui/page/cart/cartList.h
        src/ui/page/cart/cartWidget.h
        src/ui/page/cart/cartWidget.cpp
        src/ui/page/profile/formPanelWidget.h
        src/ui/page/profile/formPanelWidget.cpp
        src/ui/page/alertDialog.h
        src/ui/page/alertDialog.cpp

        external/sqlite3/sqlite3.c
        external/sqlite3/sqlite3.h
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/database/schema.sql
    ${CMAKE_CURRENT_BINARY_DIR}/schema.sql
    COPYONLY
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SportWear_Manager
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SportWear_Manager APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SportWear_Manager SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SportWear_Manager
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SportWear_Manager PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    ElaWidgetTools
    )
target_include_directories(SportWear_Manager PRIVATE
    src
    external/ElaWidgetTools
    external/sqlite3
)
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.SportWear_Manager)
endif()
set_target_properties(SportWear_Manager PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS SportWear_Manager
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SportWear_Manager)
endif()
