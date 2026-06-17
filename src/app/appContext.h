#pragma once

#include "app/appContext.h"
#include "app/serviceProvider.h"
#include "app/repositoryProvider.h"

#include "eventHandler.h"


class AppContext {
public:
    RepositoryProvider repositories;
    ServiceProvider services;
    EventHandler event;

    AppContext():
        repositories(),
        services(repositories),
        event(services)
    {}
};
