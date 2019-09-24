/*
    This file is part of Rocs.
    Copyright 2019       Thiago Ururay <tufa.araujo@kde.org>

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

#include "graphmodel.h"
#include "libgraphtheory/adjacencymatrix.h"
#include "libgraphtheory/graphdocument.h"
#include <QtGlobal>

using namespace GraphTheory;

GraphModel::GraphModel(QObject *parent) : QAbstractTableModel(parent)
{
}

void GraphModel::setGraph(GraphTheory::GraphDocumentPtr graph)
{
    beginResetModel();

    if (m_graph) {
        m_graph->disconnect(this);
    }

    m_graph = graph;
    this->generateMatrix();

    connect(graph, QOverload<>::of(&GraphTheory::GraphDocument::nodeAdded),
        this, &GraphModel::generateMatrix);
    // connect(graph, QOverload<>::of(&GraphTheory::GraphDocument::nodesRemoved),
    //     this, &GraphModel::generateMatrix);
    // connect(graph, QOverload<>::of(&GraphTheory::GraphDocument::edgeAdded),
    //     this, &GraphModel::generateMatrix);
    // connect(graph, QOverload<>::of(&GraphTheory::GraphDocument::edgesRemoved),
    //     this, &GraphModel::generateMatrix);

    endResetModel();

    return;
}

int GraphModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_graph->nodes().size();
}

int GraphModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_graph->nodes().size();
}


QVariant GraphModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return {};
    }

    return m_matrix->getValue(index.row(), index.column());
}

QVariant GraphModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation);
    if (role == Qt::DisplayRole) {
        return m_graph->nodes().at(section)->id();
    }
    return QVariant();
}

void GraphModel::generateMatrix()
{
    if (m_matrix) {
        m_matrix->destroy();
    }

    m_matrix = new AdjacencyMatrix(m_graph);
    m_matrix->create();
    m_matrix->calculate();
}
