#pragma once

#include "app/eventProvider.h"
#include "app/serviceProvider.h"
#include "app/repositoryProvider.h"




class AppContext {
public:
    EventProvider events;
    RepositoryProvider repositories;
    ServiceProvider services;

    AppContext(): repositories(), services(repositories), events() {}
};
