#include "database/repository/cartRepository.h"
#include "database/repository/orderRepository.h"
#include "database/repository/paymentRepository.h"
#include "database/repository/productRepository.h"
#include "database/repository/reviewRepository.h"
#include "database/repository/userRepository.h"

class RepositoryProvider{
public:
    UserRepository user;
    ProductRepository product;
    CartRepository cart;
    OrderRepository order;
    PaymentRepository payment;
    ReviewRepository review;
};