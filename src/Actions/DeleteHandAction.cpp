/*  
    This file is part of Rocs.
    Copyright 2008  Tomaz Canabrava <tomaz.canabrava@gmail.com>
    Copyright 2008  Ugo Sangiori <ugorox@gmail.com>
    Copyright 2011  Andreas Cord-Landwehr <cola@uni-paderborn.de>

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

#include "DeleteHandAction.h"

#include <KLocale>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "GraphScene.h"
#include "DataStructure.h"
#include "Data.h"
#include "Pointer.h"
#include "DataItem.h"
#include "PointerItem.h"

DeleteHandAction::DeleteHandAction(GraphScene* scene, QObject* parent): AbstractAction(scene, parent) {
    setText(i18n ( "Delete" ));
    setToolTip ( i18n ( "Delete items by clicking on them." ) );
    setIcon ( KIcon ( "rocsdelete" ) );
    _name = "delete";

    connect (_graphScene, SIGNAL(keyPressed(QKeyEvent*)), this, SLOT(executeKeyRelease(QKeyEvent*)));
}

bool DeleteHandAction::executePress(QPointF pos) {
    QGraphicsItem * item = _graphScene->itemAt(pos);
    if ( DataItem *n  = qgraphicsitem_cast<DataItem*>(item) ) {
        if (n->isSelected()) {
        foreach (QGraphicsItem *selectedItem, _graphScene->selectedItems())
            if (DataItem *dItem = qgraphicsitem_cast<DataItem*>(selectedItem)) {
                dItem->data()->remove();
            }
        }
        else {    
            n->data()->remove();
        }
        return true;
    }
    else if ( PointerItem *e = qgraphicsitem_cast<PointerItem*>(item) ) {
        e->pointer()->remove();
        return true;
    }
    return false;
}

bool DeleteHandAction::executeKeyRelease(QKeyEvent* keyEvent)
{
    if (keyEvent->key() == Qt::Key_Delete) {
        foreach (QGraphicsItem *item, _graphScene->selectedItems()){
            if (DataItem *dItem = qgraphicsitem_cast<DataItem*>(item)){
                _graphScene->removeItem(item);
                dItem->deleteLater();
                dItem->data()->remove();
            }
            if (PointerItem *pItem = qgraphicsitem_cast<PointerItem*>(item)){
                pItem->pointer()->remove();
            }
        }
        return true;
    }
    return false;
}
