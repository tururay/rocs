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

#include "documentwrapper.h"
#include "nodewrapper.h"
#include "edgewrapper.h"
#include "graphdocument.h"
#include "nodetype.h"
#include "edge.h"

#include <QDebug>

using namespace GraphTheory;

DocumentWrapper::DocumentWrapper(GraphDocumentPtr document, QScriptEngine *engine)
    : m_document(document)
    , m_engine(engine)
{
    foreach (NodePtr node, document->nodes()) {
        registerWrapper(node);
    }
    foreach (EdgePtr edge, document->edges()) {
        registerWrapper(edge);
    }

    connect(document.data(), SIGNAL(nodeAboutToBeAdded(NodePtr,int)), this, SLOT(registerWrapper(NodePtr)));
    connect(document.data(), SIGNAL(edgeAboutToBeAdded(EdgePtr,int)), this, SLOT(registerWrapper(EdgePtr)));
}

DocumentWrapper::~DocumentWrapper()
{
    qDeleteAll(m_edgeMap);
    qDeleteAll(m_nodeMap);
}

void DocumentWrapper::registerWrapper(NodePtr node)
{
    if (m_nodeMap.contains(node)) {
        return;
    }
    NodeWrapper *wrapper = new NodeWrapper(node, this);
    m_nodeMap.insert(node, wrapper);
    return;
}

void DocumentWrapper::registerWrapper(EdgePtr edge)
{
    if (m_edgeMap.contains(edge)) {
        return;
    }
    EdgeWrapper *wrapper = new EdgeWrapper(edge, this);
    m_edgeMap.insert(edge, wrapper);
    return;
}

NodeWrapper * DocumentWrapper::nodeWrapper(NodePtr node) const
{
    Q_ASSERT(m_nodeMap.contains(node));
    return m_nodeMap.value(node);
}

EdgeWrapper * DocumentWrapper::edgeWrapper(EdgePtr edge) const
{
    Q_ASSERT(m_edgeMap.contains(edge));
    return m_edgeMap.value(edge);
}

QScriptValue DocumentWrapper::nodes() const
{
    NodeList nodes = m_document->nodes();
    QScriptValue array = m_engine->newArray(nodes.length());
    for (int i = 0; i < nodes.length(); ++i) {
        QScriptValue nodeScriptValue = m_engine->newQObject(nodeWrapper(nodes.at(i)),
                                                            QScriptEngine::AutoOwnership,
                                                            QScriptEngine::AutoCreateDynamicProperties);
        array.setProperty(i, nodeScriptValue);
    }
    return array;
}

QScriptValue DocumentWrapper::nodes(int type) const
{
    NodeTypePtr typePtr;
    foreach (NodeTypePtr typeTest, m_document->nodeTypes()) {
        if (typeTest->id() == type) {
            typePtr = typeTest;
            break;
        }
    }
    if (!typePtr) {
        qCritical() << "Node type with ID" << type << "is not registered at document.";
        // TODO present error message in UI
        return m_engine->newArray();
    }
    NodeList nodes = m_document->nodes(typePtr);
    QScriptValue array = m_engine->newArray(nodes.length());
    for (int i = 0; i < nodes.length(); ++i) {
        QScriptValue nodeScriptValue = m_engine->newQObject(nodeWrapper(nodes.at(i)),
                                                            QScriptEngine::AutoOwnership,
                                                            QScriptEngine::AutoCreateDynamicProperties);
        array.setProperty(i, nodeScriptValue);
    }
    return array;
}

QScriptValue DocumentWrapper::edges() const
{
    EdgeList edges = m_document->edges();
    QScriptValue array = m_engine->newArray(edges.length());
    for (int i = 0; i < edges.length(); ++i) {
        QScriptValue edgeScriptValue = m_engine->newQObject(edgeWrapper(edges.at(i)),
                                                            QScriptEngine::AutoOwnership,
                                                            QScriptEngine::AutoCreateDynamicProperties);
        array.setProperty(i, edgeScriptValue);
    }
    return array;
}

QScriptValue DocumentWrapper::edges(int type) const
{
    EdgeTypePtr typePtr;
    foreach (EdgeTypePtr typeTest, m_document->edgeTypes()) {
        if (typeTest->id() == type) {
            typePtr = typeTest;
            break;
        }
    }
    if (!typePtr) {
        qCritical() << "Edge type with ID" << type << "is not registered at document.";
        // TODO present error message in UI
        return m_engine->newArray();
    }
    EdgeList edges = m_document->edges(typePtr);
    QScriptValue array = m_engine->newArray(edges.length());
    for (int i = 0; i < edges.length(); ++i) {
        QScriptValue edgeScriptValue = m_engine->newQObject(edgeWrapper(edges.at(i)),
                                                            QScriptEngine::AutoOwnership,
                                                            QScriptEngine::AutoCreateDynamicProperties);
        array.setProperty(i, edgeScriptValue);
    }
    return array;
}
