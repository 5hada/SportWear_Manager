#pragma once

#include "app/repositoryProvider.h"
#include "service/cartService.h"
#include "service/productService.h"
#include "service/reviewService.h"
#include "service/wishService.h"
#include "service/accountService.h"

class ServiceProvider {
public:
    AccountService account{nullptr};
    ProductService product;
    CartService cart;
    ReviewService review;
    WishService wish;

    explicit ServiceProvider(RepositoryProvider& repo)
        : account(&repo.user),
          product(&repo.product),
          cart(&repo.cart, &repo.product),
          review(&repo.review),
          wish(&repo.wish)
    {
    }
};
