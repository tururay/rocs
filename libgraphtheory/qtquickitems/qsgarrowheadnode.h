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

#ifndef QSGARROWHEADNODE_H
#define QSGARROWHEADNODE_H

#include "graphtheory_export.h"
#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>

class QColor;

namespace GraphTheory
{
class QSGArrowHeadNode : public QSGGeometryNode
{

public:
    explicit QSGArrowHeadNode();
    virtual ~QSGArrowHeadNode();
    void setArrow(const QPointF &from, const QPointF &to);
    void setColor(const QColor &color);

private:
    QSGGeometry m_geometry;
    QSGFlatColorMaterial m_material;
};
}

#endif
