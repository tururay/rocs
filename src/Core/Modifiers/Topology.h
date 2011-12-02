/*
    This file is part of Rocs.
    Copyright (C) 2011  Andreas Cord-Landwehr <phoenixx@uni-paderborn.de>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include <QtCore/QVector>
#include <QtCore/QPair>

#include <boost/graph/fruchterman_reingold.hpp>
#include <boost/graph/random_layout.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topology.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/random/linear_congruential.hpp>

#include "rocslib_export.h"
#include "Rocs_Typedefs.h"

/** \brief this class provides topology modifiers for data structures
 * 
 * Methods of this class either can be applied to data structures to 
 * make unique changes or connected to specific re-format signals to
 * apply a given topology after every change of the structure.
 */
class ROCSLIB_EXPORT Topology
{
    typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS,
        boost::property<boost::vertex_name_t, std::string> >
        Graph;
    typedef boost::rectangle_topology<> topology_type;
    typedef topology_type::point_type point_type;
    typedef QVector<point_type> PositionVec;
    typedef boost::iterator_property_map<PositionVec::iterator,
        boost::property_map<Graph, boost::vertex_index_t>::type> 
        PositionMap;
    typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
    typedef QPair<int, int> Edge;

public:
    Topology();
    virtual ~Topology();
 
    /** \brief applies Fruchterman-Reingold cut minimization
     * 
     * For the given data set this algorithm applies the Boost implementation
     * of the Frutherman-Reingold force directed layout algorithm to minimize
     * crossing edges. Data must be element of the same data structure. The 
     * crossings of all present edges contained in this data structure are
     * minimized. This method directly modifies the data.
     * \param dataList is the list of data
     * \return void
     */
    void applyMinCutTreeAlignment(DataList dataList);

    /** \brief applies Circle topology to data set
     * 
     * For the given data set this algorithm applies the Boost implementation
     * to create a circle layout.
     * \param dataList is the list of data
     * \return void
     */
    void applyCircleAlignment(DataList dataList);

};

#endif // TOPOLOGY_H
