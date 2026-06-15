
#include "model/product/order.h"
class ReceiptRepository;
class OrderRepository;
class CartRepository;
class ProductRepository;

class OrderService{
    ReceiptRepository* receiptRepo{nullptr};
    OrderRepository* orderRepo{nullptr};
    CartRepository* cartRepo{nullptr};
    ProductRepository* productRepo{nullptr};
    Order* currentOrder{nullptr};

    
    void addPoint(int userId, int totalPrice, int rate = 5);
public:
    OrderService(ReceiptRepository* receiptRepo):receiptRepo(receiptRepo){}

    Order& makeOrder(int userId);
    bool confirmOrder(int userId, int userPoint);
    bool refund(int id);

    void clear();
};