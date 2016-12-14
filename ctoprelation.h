#ifndef CTOPRELATION_H
#define CTOPRELATION_H

#include <QDialog>

namespace Ui {
class CToPRelation;
}

class CToPRelation : public QDialog
{
    Q_OBJECT

public:
    explicit CToPRelation(QWidget *parent = 0);
    ~CToPRelation();

private:
    Ui::CToPRelation *ui;
};

#endif // CTOPRELATION_H
