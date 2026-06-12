#pragma once

#include "app/repositoryProvider.h"
#include "service/cartService.h"
#include "service/loginService.h"
#include "service/productService.h"
#include "service/reviewService.h"
#include "service/wishService.h"

class ServiceProvider
{
public:
    LoginService login;
    ProductService product;
    CartService cart;
    ReviewService review;
    WishService wish;

    explicit ServiceProvider(RepositoryProvider& repo)
        : login(&repo.user),
          product(&repo.product),
          cart(&repo.cart, &repo.product),
          review(&repo.review),
          wish(&repo.wish)
    {
    }
};
