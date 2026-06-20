#pragma once

#include "serviceProvider.h"
#include "repositoryProvider.h"
#include "eventHandler.h"


class AppContext {
public:
    RepositoryProvider repositories;
    ServiceProvider services;
    EventHandler event;

    AppContext(): repositories(), services(repositories), event(services) {}
};
