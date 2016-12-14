#ifndef CRELATIONP_H
#define CRELATIONP_H

#include <QDialog>

namespace Ui {
class CrelationP;
}

class CrelationP : public QDialog
{
    Q_OBJECT

public:
    explicit CrelationP(QWidget *parent = 0);
    ~CrelationP();

private:
    Ui::CrelationP *ui;
};

#endif // CRELATIONP_H
