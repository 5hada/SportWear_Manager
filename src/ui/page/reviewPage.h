#include "app/appContext.h"
#include <QWidget>
#include <QListWidget>
#include <QSpinBox>
#include <QLineEdit>

class ReviewPage : public QWidget {
    AppContext app;

    QTabWidget *tab = nullptr;
    QListWidget *reviewList = nullptr;
    QSpinBox *reviewRatingSpin = nullptr;
    QLineEdit *reviewCommentEdit = nullptr;

public:
    explicit ReviewPage(QWidget *parent = nullptr);
    
    void buildInterface();
    void refreshReviews();
};
