#ifndef PTOCRELATION_H
#define PTOCRELATION_H

#include <QDialog>

namespace Ui {
class PToCRelation;
}

class PToCRelation : public QDialog
{
    Q_OBJECT

public:
    explicit PToCRelation(QWidget *parent = 0);
    ~PToCRelation();

private:
    Ui::PToCRelation *ui;
};

#endif // PTOCRELATION_H
