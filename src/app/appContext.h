#pragma once

#include "app/appContext.h"
#include "app/serviceProvider.h"
#include "app/repositoryProvider.h"

#include "eventHandler.h"


class AppContext {
public:
    EventHandler event;
    RepositoryProvider repositories;
    ServiceProvider services;

    AppContext():
        repositories(),
        services(repositories),
        event(services)
    {}
};
