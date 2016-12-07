#include "utils.h"

#include <QStringList>

Utils::Utils()
{

}

QString Utils::capitalizeString(QString string){

    QString text = string, capitalizedText;
    QStringList textList = text.split(" ");
    foreach (QString textPiece, textList){
        textPiece = textPiece.toLower();
        textPiece[0] = textPiece[0].toUpper();
        capitalizedText.append(textPiece + " ");
    }
    return capitalizedText.trimmed();
};
