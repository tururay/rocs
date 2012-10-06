/*
    This file is part of Rocs.
    Copyright 2012       Andreas Cord-Landwehr <cola@uni-paderborn.de>

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

#ifndef SCRIPTOUTPUTWIDGET_H
#define SCRIPTOUTPUTWIDGET_H

#include <QtGui/QWidget>
#include "ui_ScriptOutputWidget.h"

class QtScriptBackend;

/**
 * \class ScriptOutputWidget
 *
 * This widget displays output and debug messages from a QtScriptBackend.
 * Add this widget to your UI and set the corresponding QtScriptBackend with \see setEngine(...).
 * The widget listens for the QtScriptBackend::sendDebug(const QString& s) and
 * QtScriptBackend::sendOutput(const QString& s) signals. If a debug message is emitted by
 * the engine, the debug output is shown automatically.
 */
class ScriptOutputWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScriptOutputWidget(QWidget *parent = 0);
    void setEngine(QtScriptBackend* engine);

public slots:
    void showDebugOutput(bool show = true);
    void appendOutput(const QString& string);
    void appendDebugOutput(const QString& string);
    void clear();

private:
    QtScriptBackend* _engine;
    Ui::ScriptOutputWidget* ui;
};

#endif