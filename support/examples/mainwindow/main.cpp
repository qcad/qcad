#include <QApplication>
#include <QDir>
#include <QDebug>

#include "MainWindow.h"

#include "RDebug.h"
#include "RFontList.h"
#include "RPatternListImperial.h"
#include "RPatternListMetric.h"
#include "RPluginLoader.h"
#include "RSettings.h"

int main(int argc, char **argv)
{
    QApplication* app = new QApplication(argc, argv);

    // set current working directory:
    QDir::setCurrent(RSettings::getApplicationPath());

    // only use plugins dir of QCAD, none of the default plugin dirs of Qt self:
    app->setLibraryPaths(QStringList() << RSettings::getPluginPath());

    // compile font list from 'fonts' dir:
    RFontList::init();

    // compile hatch pattern lists from 'patterns' dir:
    RPatternListMetric::init();
    RPatternListImperial::init();

    // load plugins (DWG support, etc.):
    RPluginLoader::loadPlugins(true);

    // show main window:
    MainWindow* window = new MainWindow();
    window->show();

    // exec:
    int ret = app->exec();

    // uninit:
    RFontList::uninit();
    RPatternListMetric::uninit();
    RPatternListImperial::uninit();

    return ret;
}
