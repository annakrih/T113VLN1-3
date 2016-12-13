#ifndef PERSONINFO_H
#define PERSONINFO_H

#include <QDialog>

namespace Ui {
class personInfo;
}

class personInfo : public QDialog
{
    Q_OBJECT

public:
    explicit personInfo(QWidget *parent = 0);
    ~personInfo();

private:
    Ui::personInfo *ui;
};

#endif // PERSONINFO_H
