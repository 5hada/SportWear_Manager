#pragma once

#include "app/repositoryProvider.h"

#include "service/accountService.h"
#include "service/cartService.h"
#include "service/orderService.h"
#include "service/pointService.h"
#include "service/productService.h"
#include "service/searchService.h"
#include "service/reviewService.h"
#include "service/wishService.h"

class ServiceProvider {
public:
    AccountService account{nullptr};
    CartService cart;
    OrderService order;
    PointService point;
    ProductService product;
    ReviewService review;
    SearchService search;
    WishService wish;

    explicit ServiceProvider(RepositoryProvider& repo):
        account(&repo.user),
        cart(&repo.cart, &repo.product),
        order(&repo.receipt, &repo.order, &repo.cart, &repo.product),
        point(&repo.user),
        product(&repo.product),
        review(&repo.review),
        search(),
        wish(&repo.wish, &repo.product)
    {
        order.setPointService(&point);
        search.setProductService(&product);
    }
};
