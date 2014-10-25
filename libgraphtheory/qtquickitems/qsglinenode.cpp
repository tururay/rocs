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

#include "qsglinenode.h"
#include "qsgarrowheadnode.h"
#include <QSGGeometry>
#include <QSGFlatColorMaterial>
#include <QColor>

using namespace GraphTheory;

QSGLineNode::QSGLineNode()
    : m_geometry(QSGGeometry::defaultAttributes_Point2D(), 2)
    , m_arrowHead(new QSGArrowHeadNode)
{
    m_material.setColor(QColor(0, 0, 0));
    setMaterial(&m_material);

    setGeometry(&m_geometry);
    m_geometry.setDrawingMode(GL_LINES);
    m_geometry.setLineWidth(3);

    // initialization of end points
    m_geometry.vertexDataAsPoint2D()[0].set(0, 0);
    m_geometry.vertexDataAsPoint2D()[1].set(0, 0);

    appendChildNode(m_arrowHead);
}

QSGLineNode::~QSGLineNode()
{
    delete m_arrowHead;
}

void QSGLineNode::setLine(const QPointF &from, const QPointF &to)
{
    m_geometry.vertexDataAsPoint2D()[0].set(from.x(), from.y());
    m_geometry.vertexDataAsPoint2D()[1].set(to.x(), to.y());
    m_arrowHead->setArrow(from, to);
    markDirty(QSGNode::DirtyGeometry);
}

void QSGLineNode::setColor(const QColor& color)
{
    QSGFlatColorMaterial *m = static_cast<QSGFlatColorMaterial*>(material());
    m->setColor(color);
    m_arrowHead->setColor(color);
    markDirty(QSGNode::DirtyMaterial);
}
