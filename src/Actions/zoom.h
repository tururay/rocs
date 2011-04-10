/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef ZOOM_H
#define ZOOM_H

#include <AbstractAction.h>
#include <QRectF>
#include <QPointF>

class QGraphicsRectItem;
class QGraphicsView;
class QKeyEvent;
class QGraphicsSceneWheelEvent;

class ZoomAction : public AbstractAction
{

public:
    ZoomAction(GraphScene* scene, QObject* parent);
    bool executePress(QPointF pos);
    bool executeMove(QPointF pos);
    bool executeRelease(QPointF pos);
    bool executeDoubleClick(QPointF pos);
    bool executeKeyPress(QKeyEvent* keyEvent);
    bool executeKeyRelease(QKeyEvent* keyEvent);
    bool executeWellEvent(QGraphicsSceneWheelEvent *wEvent);    
private:
    QRectF m_zoomArea;
    qreal m_currentZoomFactor;
    QGraphicsView *m_view;
    QGraphicsRectItem *m_zoomRectItem;
    QPointF m_beginZoom;
    QPointF m_endZoom;
};

#endif // ZOOM_H
