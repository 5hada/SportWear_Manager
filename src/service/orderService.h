
#include "model/product/order.h"
#include "model/product/receipt.h"
class ReceiptRepository;
class OrderRepository;
class CartRepository;
class ProductRepository;
class PointService;

class OrderService{
    ReceiptRepository* receiptRepo{nullptr};
    OrderRepository* orderRepo{nullptr};
    CartRepository* cartRepo{nullptr};
    ProductRepository* productRepo{nullptr};

    PointService* pointService{nullptr};

    Order* currentOrder{nullptr};

public:
    OrderService(
        ReceiptRepository* receiptRepo,
        OrderRepository* orderRepo,
        CartRepository* cartRepo,
        ProductRepository* productRepo
    ):
        receiptRepo(receiptRepo),
        orderRepo(orderRepo),
        cartRepo(cartRepo),
        productRepo(productRepo)
    {}

    void setPointService(PointService* pointService) {this->pointService = pointService;}


    Receipts getReceipts(int userId);

    Order& makeOrder(int userId);
    bool confirmOrder(int userId, int userPoint);
    bool refund(int id);

    void clear();
};