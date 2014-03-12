/*
    This file is part of Rocs.
    Copyright 2008-2011  Tomaz Canabrava <tomaz.canabrava@gmail.com>
    Copyright 2008       Ugo Sangiori <ugorox@gmail.com>
    Copyright 2010       Wagner Reck <wagner.reck@gmail.com>


    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QApplication>
#include <KAboutData>
#include <KLocalizedString>

#include "rocsversion.h"
#include "Ui/MainWindow.h"
#include <DataStructureBackendManager.h>


int main(int argc, char *argv[])
{
    KAboutData aboutData("rocs",
                         "rocs",
                         ki18nc("@title Displayed program name", "Rocs").toString(),
                         ROCS_VERSION_STRING,
                         ki18nc("@title KAboutData: short program description", "Graph Theory Tool").toString(),
                         KAboutData::License_GPL,
                         ki18nc("@info:credit", "(c) 2009-2013 Rocs Developers").toString(),
                         ki18nc("@title Short program description", "Rocs - Data Structure Analysis").toString()
                        );

    aboutData.addAuthor(ki18nc("@info:credit Developer name", "Tomaz Canabrava").toString(),
                        ki18nc("@info:credit Role", "Developer").toString(),
                        "tcanabrava@kde.org",
                        "http://liveblue.wordpress.com");

    aboutData.addAuthor(ki18nc("@info:credit Developer name", "Wagner Reck").toString(),
                        ki18nc("@info:credit Role", "Developer").toString(),
                        "wagner.reck@gmail.com",
                        "http://wiglot.wordpress.com");

    aboutData.addAuthor(ki18nc("@info:credit Developer name", "Andreas Cord-Landwehr").toString(),
                        ki18nc("@info:credit Role", "Developer").toString(),
                        "cordlandwehr@kde.org",
                        "http://cordlandwehr.wordpress.com");
    /**
     * first init the app
     */
    QApplication app(argc, argv);
    KAboutData::setApplicationData(aboutData);

    if (DataStructureBackendManager::self().backends().count() == 0) {
        KMessageBox::detailedError(0,
                                   i18n("No Data Structure plugins found on your system. Exiting."),
                                   i18n("Rocs needs at least one data structure plugin to continue.\n"
                                        "Try running kbuildsycoca4 from a console and after execute Rocs again."));

    } else {
        MainWindow *window = new MainWindow();
        window->show();
        return app.exec();
    }
    return 0;
}
