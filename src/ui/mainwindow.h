#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "database/repository/cartRepository.h"
#include "database/repository/orderRepository.h"
#include "database/repository/paymentRepository.h"
#include "database/repository/productRepository.h"
#include "database/repository/reviewRepository.h"
#include "database/repository/userRepository.h"
#include "service/cartService.h"
#include "service/loginService.h"
#include "service/orderService.h"
#include "service/productService.h"
#include "service/reviewService.h"

#include <QMainWindow>

class QLabel;
class QLineEdit;
class QListWidget;
class QPushButton;
class QSpinBox;
class QTabWidget;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void buildInterface();
    void refreshProducts();
    void refreshCart();
    void refreshOrders();
    void refreshReviews();
    int selectedProductId() const;
    bool requireLogin();

    Ui::MainWindow *ui;

    UserRepository userRepository_;
    ProductRepository productRepository_;
    CartRepository cartRepository_;
    OrderRepository orderRepository_;
    PaymentRepository paymentRepository_;
    ReviewRepository reviewRepository_;

    LoginService loginService_;
    ProductService productService_;
    CartService cartService_;
    OrderService orderService_;
    ReviewService reviewService_;

    int currentUserId_ = 0;

    QTabWidget *tabs_ = nullptr;
    QLabel *sessionLabel_ = nullptr;
    QLineEdit *usernameEdit_ = nullptr;
    QLineEdit *passwordEdit_ = nullptr;
    QListWidget *productList_ = nullptr;
    QSpinBox *quantitySpin_ = nullptr;
    QListWidget *cartList_ = nullptr;
    QLabel *cartTotalLabel_ = nullptr;
    QLineEdit *addressEdit_ = nullptr;
    QListWidget *orderList_ = nullptr;
    QSpinBox *reviewRatingSpin_ = nullptr;
    QLineEdit *reviewCommentEdit_ = nullptr;
    QListWidget *reviewList_ = nullptr;
};
#endif // MAINWINDOW_H
