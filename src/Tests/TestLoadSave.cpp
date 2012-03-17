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

#include "TestLoadSave.h"
#include "DataStructure.h"
#include "Data.h"
#include "Pointer.h"
#include <qtest_kde.h>

#include <Document.h>
#include <DataStructurePluginManager.h>
#include <DocumentManager.h>

TestLoadSave::TestLoadSave()
{
    DocumentManager::self()->addDocument(new Document("test"));;
}


void TestLoadSave::serializeUnserializeTest()
{
    QMap<QString, DataPtr> dataList;
    // Creates a simple Graph with 5 data elements and connect them with pointers.
    DataStructurePtr ds = DocumentManager::self()->activeDocument()->activeDataStructure();

    ds->setProperty( "name", "Graph1" );
    dataList.insert( "a", ds->addData( "a" ) );
    dataList.insert( "b", ds->addData( "b" ) );
    dataList.insert( "c", ds->addData( "c" ) );
    dataList.insert( "d", ds->addData( "d" ) );
    dataList.insert( "e", ds->addData( "e" ) );

    ds->addPointer( dataList["a"], dataList["b"] );
    ds->addPointer( dataList["b"], dataList["c"] );
    ds->addPointer( dataList["c"], dataList["d"] );
    ds->addPointer( dataList["d"], dataList["e"] );
    ds->addPointer( dataList["e"], dataList["a"] );

    // serialize into file "serializetest.graph"
    DocumentManager::self()->activeDocument()->saveAsInternalFormat("serializetest");
    DocumentManager::self()->removeDocument(DocumentManager::self()->activeDocument());
    Document* testDoc = new Document("testDoc");

    // unserialize and test properties
    DocumentManager::self()->addDocument(testDoc);
    DocumentManager::self()->changeDocument(testDoc);
    DocumentManager::self()->activeDocument()->loadFromInternalFormat("serializetest.graph");

    // default data structure also present
    QVERIFY2 (DocumentManager::self()->activeDocument()->dataStructures().count() == 2, "ERROR: DataStructure not loaded");

    ds = DocumentManager::self()->activeDocument()->dataStructures().at(1);
    QVERIFY2( ds->dataList().size() == 5, "ERROR: Number of data is not 5 " );
    QVERIFY2( ds->pointers().size() == 5, "ERROR: Number of pointers is not 5 " );

    foreach( DataPtr n, ds->dataList() ) {
        QVERIFY2( n->out_pointers().size() == 1, "ERROR: Number of out pointers is not 1" );
        QVERIFY2( n->in_pointers().size() == 1, "ERROR: Number of in pointers is not 1" );
        QVERIFY2( n->adjacent_data().size() == 2, "ERROR: Number of Adjacent Nodes is not 2" );
        QVERIFY2( n->adjacent_pointers().size() == 2, "ERROR: Number of adjacent pointers is not 2" );
    }

}



/*
   void TestDataStructure::saveTestFile() {
    createPentagon();
    _graphDocument->saveAsInternalFormat("pentagono");
   }

   void  TestDataStructure::loadTestFile() {
    _graphDocument->loadFromInternalFormat("pentagono.datatype");

    QVERIFY2 (_graphDocument->dataStructures().count() == 1, "ERROR: DataStructure not loaded");

    QVERIFY2( ds->dataList().size() == 5, "ERROR: Number of data is not 5 ");
    QVERIFY2( ds->pointers().size() == 5, "ERROR: Number of pointers is not 5 ");

    foreach( DataPtr n, ds->dataList() ) {
        QVERIFY2( n->out_pointers().size() == 1, "ERROR: Number of out pointers is not 1");
        QVERIFY2( n->in_pointers().size() == 1, "ERROR: Number of in pointers is not 1");
        QVERIFY2( n->adjacent_data().size() == 2, "ERROR: Number of Adjacent Nodes is not 2");
        QVERIFY2( n->adjacent_pointers().size() == 2, "ERROR: Number of adjacent pointers is not 2");
    }

    // sort out what is A,B,I


    QVERIFY2( _data["a"]->out_pointers().size()  == 1, "ERROR: Number of pointers is not 1 ");
    QVERIFY2( _data["a"]->in_pointers().size()   == 1, "ERROR: Number of pointers is not 1 ");
    QVERIFY2( _data["a"]->self_pointers().size() == 0, "ERROR: Number of pointers is not 0 ");
    QVERIFY2( _data["a"]->adjacent_data().size() == 2, "ERROR: Number of Adjacent Nodes is not 2");
    QVERIFY2( _data["a"]->adjacent_pointers().size() == 2, "ERROR: Number of adjacent pointers is not 2");

    QVERIFY2( _data["b"]->out_pointers().size() == 1, "ERROR: Number of pointers is not 1 ");
    QVERIFY2( _data["b"]->in_pointers().size() == 2, "ERROR: Number of pointers is not 1 ");
    QVERIFY2( _data["b"]->self_pointers().size() == 0, "ERROR: Number of pointers is not 0 ");
    QVERIFY2( _data["b"]->adjacent_data().size() == 3, "ERROR: Number of Adjacent Nodes is not 2");
    QVERIFY2( _data["b"]->adjacent_pointers().size() == 3, "ERROR: Number of adjacent pointers is not 2");

    QVERIFY2( _data["i"]->out_pointers().size() == 4, "ERROR: Number of pointers is not 1 ");
    QVERIFY2( _data["i"]->in_pointers().size() == 0, "ERROR: Number of pointers is not 1 ");
    QVERIFY2( _data["i"]->self_pointers().size() == 0, "ERROR: Number of pointers is not 0 ");
    QVERIFY2( _data["i"]->adjacent_data().size() == 4, "ERROR: Number of Adjacent Nodes is not 2");
    QVERIFY2( _data["i"]->adjacent_pointers().size() == 4, "ERROR: Number of adjacent pointers is not 2");

    DataPtr n = _data["i"];
    qDebug() << n->property("name");
    ds->remove(n);

    QVERIFY2( _data["a"]->out_pointers().size()  == 1, "ERROR: Number of pointers is not 1 ");
    QVERIFY2( _data["a"]->in_pointers().size()   == 1, "ERROR: Number of pointers is not 1 ");
    QVERIFY2( _data["a"]->self_pointers().size() == 0, "ERROR: Number of pointers is not 0 ");
    QVERIFY2( _data["a"]->adjacent_data().size() == 2, "ERROR: Number of Adjacent Nodes is not 2");
    QVERIFY2( _data["a"]->adjacent_pointers().size() == 2, "ERROR: Number of adjacent pointers is not 2");

    QVERIFY2( _data["b"]->out_pointers().size() == 1, "ERROR: Number of pointer is not 1 ");
    QVERIFY2( _data["b"]->in_pointers().size() == 1, "ERROR: Number of pointers is not 1 ");
    QVERIFY2( _data["b"]->self_pointers().size() == 0, "ERROR: Number of pointer is not 0 ");
    QVERIFY2( _data["b"]->adjacent_data().size() == 2, "ERROR: Number of Adjacent Nodes is not 2");
    QVERIFY2( _data["b"]->adjacent_pointers().size() == 2, "ERROR: Number of adjacent pointers is not 2");

    QVERIFY2( _data["i"] == 0, "ERROR: Node  'i'  was not removed. ");
   }*/

QTEST_KDEMAIN_CORE(TestLoadSave)
