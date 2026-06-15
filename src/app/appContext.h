#pragma once

#include "app/serviceProvider.h"
#include "app/repositoryProvider.h"




class AppContext {
public:
    RepositoryProvider repositories;
    ServiceProvider services;

    AppContext(): repositories(), services(repositories) {}
};
