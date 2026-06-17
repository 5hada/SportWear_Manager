

class Wish {
    int userId;
    int productId;

public:
    Wish(int userId, int productId): userId(userId), productId(productId) {}

    int getUserId() const {return userId;}
    int getProductId() const {return productId;}

    void setUserId(int userId) {this->userId = userId;}
    void setProductId(int productId) {this->productId = productId;}
};