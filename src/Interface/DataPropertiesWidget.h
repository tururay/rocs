/*
    This file is part of Rocs.
    Copyright 2008-2011  Tomaz Canabrava <tomaz.canabrava@gmail.com>
    Copyright 2008       Ugo Sangiori <ugorox@gmail.com>

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

#ifndef SUI_DATAPROPERTIESWIDGET_H
#define SUI_DATAPROPERTIESWIDGET_H

#include <QWidget>
#include "Rocs_Typedefs.h"
#include "ui_DataPropertiesWidget.h"

class Data;
class MainWindow;
class DataItem;
#include <QPointF>
#include <QPointer>
/*! \brief Properties Area. */
class DataPropertiesWidget : public QWidget, public Ui::DataPropertiesWidget
{
    Q_OBJECT
public:
    DataPropertiesWidget(MainWindow* parent = 0);
    void setData(DataItem *n, QPointF pos);

public slots:
    /** shows the widget; this is a wrapper for \see setActive(true) **/
    void show() {
        setActive(true);
    };

private slots:
    void on__color_activated(const QColor& c);
    void on__images_activated(const QString& s);
    void reflectAttributes();
    void setUseColor(bool b); //! Temporary fix because of the string-freeze. remove this for 4.8
//     void updateAutomateAttributes(bool b);
    void on__addProperty_clicked();

private:
    void setActive(bool active);

    DataPtr  _data;
    MainWindow *_mainWindow;
    DataItem *_item;
    QString _svgFile;
    QString _oldDataStructurePlugin;

};
#endif