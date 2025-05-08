#ifndef REST_H
#define REST_H

#include <QWidget>

namespace Ui {
class Rest;
}

class Rest : public QWidget
{
    Q_OBJECT

public:
    explicit Rest(QWidget *parent = nullptr);
    ~Rest();

private:
    Ui::Rest *ui;
};

#endif // REST_H
