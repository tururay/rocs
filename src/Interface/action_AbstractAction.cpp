
/* This file is part of Rocs,
   Copyright (C) 2008 by:
   Tomaz Canabrava <tomaz.canabrava@gmail.com>
   Ugo Sangiori <ugorox@gmail.com>

   Rocs is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   Rocs is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Step; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "action_AbstractAction.h"
#include "SUI_GraphScene.h"
#include "graph.h"
#include "graphDocument.h"
#include <QPointF>
#include <KDebug>

AbstractAction::AbstractAction(GraphScene *scene, QObject *parent) : KAction(parent)
{
  _graphDocument = 0;
  _graph = 0;
  _graphScene = scene;
  setCheckable ( true );
  setChecked ( false );
  connect(this, SIGNAL(triggered()), this, SLOT( sendExecuteBit() ));
}

void AbstractAction::setGraphDocument(  GraphDocument *graphDocument)
{
  kDebug() << "Document Setted";
  _graphDocument = graphDocument;
}

void AbstractAction::setGraph( Graph *graph){
  kDebug() << "Graph Setted";
  _graph = graph;
}

void AbstractAction::sendExecuteBit()
{
  _graphScene -> setAction ( this );
}

void AbstractAction::executePress(QPointF){ return; }
void AbstractAction::executeMove(QPointF){ return; }
void AbstractAction::executeRelease(QPointF) { return; }
void AbstractAction::executeKeyPress(QKeyEvent*){ return;  }
void AbstractAction::executeKeyRelease(QKeyEvent*){ return; }