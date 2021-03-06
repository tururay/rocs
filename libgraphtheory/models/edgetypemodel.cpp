/*
 *  Copyright 2014-2015  Andreas Cord-Landwehr <cordlandwehr@kde.org>
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

#include "edgetypemodel.h"
#include "graphdocument.h"
#include "edgetypestyle.h"
#include "logging_p.h"

#include <KLocalizedString>
#include <QSignalMapper>

using namespace GraphTheory;

class GraphTheory::EdgeTypeModelPrivate {
public:
    EdgeTypeModelPrivate()
        : m_signalMapper(new QSignalMapper)
    {
    }

    ~EdgeTypeModelPrivate()
    {
        m_signalMapper->deleteLater();
    }

    void updateMappings()
    {
        int types = m_document->edgeTypes().count();
        for (int i = 0; i < types; ++i) {
            m_signalMapper->setMapping(m_document->edgeTypes().at(i).data(), i);
        }
    }

    GraphDocumentPtr m_document;
    QSignalMapper *m_signalMapper;
};

EdgeTypeModel::EdgeTypeModel(QObject *parent)
    : QAbstractListModel(parent)
    , d(new EdgeTypeModelPrivate)
{
    connect(d->m_signalMapper, static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
        this, &EdgeTypeModel::emitEdgeTypeChanged);
}

EdgeTypeModel::~EdgeTypeModel()
{

}

QHash< int, QByteArray > EdgeTypeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[TitleRole] = "titleRole";
    roles[DataRole] = "dataRole";

    return roles;
}

void EdgeTypeModel::setDocument(GraphDocumentPtr document)
{
    if (d->m_document == document) {
        return;
    }

    beginResetModel();
    if (d->m_document) {
        d->m_document.data()->disconnect(this);
    }
    d->m_document = document;
    if (d->m_document) {
        connect(d->m_document.data(), &GraphDocument::edgeTypeAboutToBeAdded,
            this, &EdgeTypeModel::onEdgeTypeAboutToBeAdded);
        connect(d->m_document.data(), &GraphDocument::edgeTypeAdded,
            this, &EdgeTypeModel::onEdgeTypeAdded);
        connect(d->m_document.data(), &GraphDocument::edgeTypesAboutToBeRemoved,
            this, &EdgeTypeModel::onEdgeTypesAboutToBeRemoved);
        connect(d->m_document.data(), &GraphDocument::edgeTypesRemoved,
            this, &EdgeTypeModel::onEdgeTypesRemoved);
    }
    endResetModel();
}

EdgeTypePtr EdgeTypeModel::type(int index) const
{
    return d->m_document->edgeTypes().at(index);
}

QVariant EdgeTypeModel::data(const QModelIndex &index, int role) const
{
    Q_ASSERT(d->m_document);

    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() >= d->m_document->edgeTypes().count()) {
        return QVariant();
    }

    EdgeTypePtr const type = d->m_document->edgeTypes().at(index.row());

    switch(role)
    {
    case IdRole:
        return type->id();
    case TitleRole:
        return type->name();
    case ColorRole:
        return type->style()->color();
    case DirectionRole:
        return type->direction();
    case DataRole:
        return QVariant::fromValue<QObject*>(type.data());
    default:
        return QVariant();
    }
}

bool EdgeTypeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        qCWarning(GRAPHTHEORY_GENERAL) << "Index not valid, aborting";
        return false;
    }
    Q_ASSERT(d->m_document);

    if (index.row() >= d->m_document->edgeTypes().count()) {
        return false;
    }

    EdgeTypePtr const type = d->m_document->edgeTypes().at(index.row());
    switch(role)
    {
    case IdRole:
        type->setId(value.toInt());
        break;
    case TitleRole:
        type->setName(value.toString());
        break;
    case ColorRole:
        type->style()->setColor(value.value<QColor>());
        break;
    case DirectionRole:
        type->setDirection(static_cast<EdgeType::Direction>(value.toInt()));
        break;
    default:
        return false;
    }
    dataChanged(index, index);
    return true;
}

int EdgeTypeModel::rowCount(const QModelIndex &parent) const
{
    if (!d->m_document) {
        return 0;
    }

    if (parent.isValid()) {
        return 0;
    }

    return d->m_document->edgeTypes().count();
}

void EdgeTypeModel::onEdgeTypeAboutToBeAdded(EdgeTypePtr type, int index)
{
    beginInsertRows(QModelIndex(), index, index);
    connect(type.data(), &EdgeType::idChanged,
        d->m_signalMapper, static_cast<void (QSignalMapper::*)(void)>(&QSignalMapper::map));
    connect(type.data(), &EdgeType::nameChanged,
        d->m_signalMapper, static_cast<void (QSignalMapper::*)(void)>(&QSignalMapper::map));
    connect(type->style(), &EdgeTypeStyle::colorChanged,
        d->m_signalMapper, static_cast<void (QSignalMapper::*)(void)>(&QSignalMapper::map));
}

void EdgeTypeModel::onEdgeTypeAdded()
{
    d->updateMappings();
    endInsertRows();
}

void EdgeTypeModel::onEdgeTypesAboutToBeRemoved(int first, int last)
{
    beginRemoveRows(QModelIndex(), first, last);
}

void EdgeTypeModel::onEdgeTypesRemoved()
{
    endRemoveRows();
}

void EdgeTypeModel::emitEdgeTypeChanged(int row)
{
    emit edgeChanged(row);
    emit dataChanged(index(row, 0), index(row, 0));
}

QVariant EdgeTypeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    if (orientation == Qt::Vertical) {
        return QVariant(section + 1);
    }
    return QVariant(i18nc("@title:column", "Edge Type"));
}
