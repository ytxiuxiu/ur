#include "file.h"

std::string File::readFile(QString filename)
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return NULL;
    }
    QTextStream in(&file);
    return in.readAll().toUtf8().constData();
}
