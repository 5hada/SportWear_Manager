#pragma once

#include "app/appContext.h"
#include "app/eventProvider.h"
#include "app/serviceProvider.h"
#include "app/repositoryProvider.h"

#include "controller/adminController.h"
#include "controller/authController.h"
#include "controller/cartController.h"
#include "controller/orderController.h"
#include "controller/productController.h"


class AppContext {
public:
    EventProvider events;
    RepositoryProvider repositories;
    ServiceProvider services;
    
    AdminController adminController;
    AuthController authController;
    CartController cartController;
    OrderController orderController;
    ProductController productController;

    AppContext(): repositories(), services(repositories), events() {}
};
