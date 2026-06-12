#include "database/repository/orderRepository.h"
#include "database/repository/paymentRepository.h"

class RefundService {
    OrderRepository *orders_ = nullptr;
    PaymentRepository *payments_ = nullptr;
    
public:
    RefundService(OrderRepository *orders, PaymentRepository *payments);

    bool refund(int orderId);
};
