#include"model/product/cart.h"
#include"model/product/orderItem.h"
#include <map>
#include <vector>
class ReceiptRepository;

class OrderService{
    ReceiptRepository* receipt{nullptr};
    std::vector<OrderItem>* currentOrder;
    int totalPrice;

    
    void addPoint(int userId, int totalPrice, int rate = 5);
    std::vector<OrderItem> getOrderItems(Cart cartItems);
public:
    OrderService(ReceiptRepository* receiptRepo):receipt(receiptRepo){}

    std::map<int, std::vector<OrderItem>> makeOrder(int userId);
    bool confirmOrder(int userId, int userPoint);
    bool order(int userId, Cart cartItems,int totalPrice, int usedPoint);
    bool refund(int id);
};