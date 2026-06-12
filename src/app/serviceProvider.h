#include "service/cartService.h"
#include "service/loginService.h"
#include "service/orderService.h"
#include "service/productService.h"
#include "service/reviewService.h"
#include "app/repositoryProvider.h"

class ServiceProvider{
public: 
    LoginService login;
    ProductService product;
    CartService cart;
    OrderService order;
    ReviewService review;

    explicit ServiceProvider(RepositoryProvider& repo)
        : login(&repo.user),
          product(&repo.product),
          cart(&repo.cart, &repo.product),
          order(&repo.order, &repo.cart, &repo.product, &repo.payment),
          review(&repo.review)
    {}

};