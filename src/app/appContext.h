#include "app/serviceProvider.h"
#include "app/repositoryProvider.h"




class AppContext{
public:
    RepositoryProvider repositories;
    ServiceProvider services;

    int currentUserId = 0;

    AppContext(): repositories(), services(repositories) {}
};