
class WishRepository;
class ProductRepository;

class WishService {
    WishRepository* wishRepo{nullptr};
    ProductRepository* productRepo{nullptr};
    
    bool isRepoValid();
public:
    explicit WishService(WishRepository* wishRepo, ProductRepository* productRepo):
        wishRepo(wishRepo), productRepo(productRepo){}

    bool add(int userId, int productId);
    bool remove(int userId, int productId);
};
