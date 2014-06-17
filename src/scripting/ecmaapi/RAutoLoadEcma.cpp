#include <QDebug>
#include "RAutoLoadEcma.h"

QStringList RAutoLoadEcma::autoLoadFiles;

void RAutoLoadEcma::addAutoLoadFile(const QString& file) {
    autoLoadFiles.append(file);
}

QStringList RAutoLoadEcma::getAutoLoadFiles() {
    return autoLoadFiles;
}
