/*
 *  Copyright 2014  Andreas Cord-Landwehr <cordlandwehr@kde.org>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) version 3, or any
 *  later version accepted by the membership of KDE e.V. (or its
 *  successor approved by the membership of KDE e.V.), which shall
 *  act as a proxy defined in Section 6 of version 3 of the license.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EDGEITEM_H
#define EDGEITEM_H

#include "graphtheory_export.h"
#include "edge.h"
#include <QQuickItem>

class QSGNode;

namespace GraphTheory
{
class EdgeItemPrivate;

class EdgeItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(GraphTheory::Edge * edge READ edge WRITE setEdge NOTIFY edgeChanged)
    Q_PROPERTY(QPointF origin READ origin WRITE setOrigin)

public:
    explicit EdgeItem(QQuickItem *parent = 0);
    virtual ~EdgeItem();
    Edge * edge() const;
    void setEdge(Edge *edge);
    /** translation of global origin (0,0) into scene coordinates **/
    QPointF origin() const;
    /** set translation of global origin (0,0) into scene coordinates **/
    void setOrigin(const QPointF &origin);

protected:
    virtual QSGNode * updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data) Q_DECL_OVERRIDE;

Q_SIGNALS:
    void edgeChanged();

private Q_SLOTS:
    void updatePosition();
    void updateColor();
    void updateDirection();
    void updateVisibility();

private:
    Q_DISABLE_COPY(EdgeItem)
    const QScopedPointer<EdgeItemPrivate> d;
};
}

#endif
