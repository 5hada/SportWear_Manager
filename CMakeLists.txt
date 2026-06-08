cmake_minimum_required(VERSION 3.16)

project(SportWear_Manager VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(PROJECT_SOURCES
        src/main.cpp

        src/database/repository/orderRepository.h
        src/database/repository/orderRepository.cpp
        src/database/repository/productRepository.h
        src/database/repository/productRepository.cpp
        src/database/repository/userRepository.h
        src/database/repository/userRepository.cpp
        src/database/repository/cartRepository.h
        src/database/repository/cartRepository.cpp
        src/database/repository/inventoryRepository.h
        src/database/repository/inventoryRepository.cpp
        src/database/repository/paymentRepository.h
        src/database/repository/paymentRepository.cpp
        src/database/repository/reviewRepository.h
        src/database/repository/reviewRepository.cpp
        src/database/repository/wishlistRepository.h
        src/database/repository/wishlistRepository.cpp
        src/database/databaseManager.h
        src/database/databaseManager.cpp

        src/model/cart/cart.h
        src/model/cart/cart.cpp
        src/model/cart/cartItem.h
        src/model/cart/cartItem.cpp
        src/model/order/delivery.h
        src/model/order/delivery.cpp
        src/model/order/order.h
        src/model/order/order.cpp
        src/model/order/orderItem.h
        src/model/order/orderItem.cpp
        src/model/order/receipt.h
        src/model/order/receipt.cpp
        src/model/product/category.h
        src/model/product/category.cpp
        src/model/product/inventory.h
        src/model/product/inventory.cpp
        src/model/product/product.h
        src/model/product/product.cpp
        src/model/review.h
        src/model/review.cpp
        src/model/user/admin.h
        src/model/user/admin.cpp
        src/model/user/guest.h
        src/model/user/guest.cpp
        src/model/user/user.h
        src/model/user/user.cpp
        src/model/user/userBase.h
        src/model/user/userBase.cpp

        src/service/cartService.h
        src/service/cartService.cpp
        src/service/inventoryService.h
        src/service/inventoryService.cpp
        src/service/loginService.h
        src/service/loginService.cpp
        src/service/orderService.h
        src/service/orderService.cpp
        src/service/pointService.h
        src/service/pointService.cpp
        src/service/productService.h
        src/service/productService.cpp
        src/service/refundService.h
        src/service/refundService.cpp
        src/service/reviewService.h
        src/service/reviewService.cpp
        src/service/wishlistService.h
        src/service/wishlistService.cpp

        src/ui/mainwindow.cpp
        src/ui/mainwindow.h
        src/ui/mainwindow.ui
        src/ui/page/cartPage.h
        src/ui/page/cartPage.cpp
        src/ui/page/loginPage.h
        src/ui/page/loginPage.cpp
        src/ui/page/orderPage.h
        src/ui/page/orderPage.cpp
        src/ui/page/productPage.h
        src/ui/page/productPage.cpp
        src/ui/page/reviewPage.h
        src/ui/page/reviewPage.cpp

        sqlite3/sqlite3.c
        sqlite3/sqlite3.h
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

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
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

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(SportWear_Manager PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(SportWear_Manager PRIVATE
    src
    sqlite3
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
