
#include <QHBoxLayout>

class ElaText;
class ElaLineEdit;

class IndexNavigation: public QHBoxLayout {
    Q_OBJECT

    ElaText* pageIndex;
    ElaLineEdit* pageIndexInput{nullptr};
    ElaLineEdit* searchEdit{nullptr};
    int currentIndex;
    int maxIndex;

    void init();

    void updateText();
public:
    IndexNavigation(QWidget* parent = nullptr);

    void setIndex(int maxIndex, int currentIndex = 0);
Q_SIGNALS:
    void indexChanged(int newIndex);
};