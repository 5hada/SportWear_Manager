class Inventory {
    int productId_ = 0;
    int quantity_ = 0;

public:
    Inventory() = default;
    Inventory(int productId, int quantity);

    int productId() const;
    int quantity() const;

    void setQuantity(int quantity);
    void add(int quantity);

    bool remove(int quantity);
};