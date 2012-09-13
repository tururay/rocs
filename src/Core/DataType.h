/*
    This file is part of Rocs.
    Copyright 2012  Andreas Cord-Landwehr <cola@uni-paderborn.de>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef DATATYPE_H
#define DATATYPE_H

#include <QString>
#include <QColor>
#include <KIcon>

#include "rocslib_export.h"
#include "Rocs_Typedefs.h"

class Data;
class DataTypePrivate;
class DataStructure;
class Document;

/**
* \class DataType
*
* A data type groups a set of data elements and gives them a common appearance. Each data type is
* associated to a document and must get an unique identifier on creation. To create a data type,
* use the static \see create(document, identifier) method.
*/
class ROCSLIB_EXPORT DataType : public QObject
{
    Q_OBJECT
public:
    /**
     * Create data type objects.
     *
     * \param document is graph document for that the data type is created
     * \param identifier is unique identifier of the data type within the document
     * \return the created data type
     */
    static DataTypePtr create(Document* document, int identifier);

    /**
     * Destructor.
     */
    ~DataType();

    /**
     * \return name of data type
     */
    const QString& name() const;

    /**
     * \return data type icon identifier for iconPackage
     */
    const QString& iconName() const;

    /**
     * Generates KIcon for data type at run time. This icon is not cached.
     *
     * \return icon according to current iconPackage and iconName
     */
    KIcon icon() const;

    /**
     * \return unique identifier of data type
     */
    int identifier() const;

    /**
     * \return default color for data elements of this data type
     */
    const QColor& defaultColor() const;

public slots:
    /**
     * Set name of the data type.
     *
     * \param name of the data type
     */
    void setName(QString name);

    /**
     * Set icon of data elements of this type.
     * "rocs_" prefix of icon identifier must be removed before setting this.
     *
     * \param icon identifier in current icon package
     */
    void setIcon(QString icon);

    /**
     * Set default color value for this data type.
     *
     * \param color is the default color to be set
     */
    void setDefaultColor(QColor color);

    /**
     * Unregister data type from graph document.
     */
    void remove();

signals:
    /**
     * Emitted when default color was changed.
     */
    void defaultColorChanged(QColor color);

    /**
     * Emitted when icon was changed.
     */
    void iconChanged(const QString& icon);

    /**
     * Emitted when name was changed.
     */
    void nameChanged(const QString& name);

protected:
    /**
     * \internal
     * Default constructor. To create DataType elements use \see DataType::create(...).
     *
     * \param document is graph document for that the data type is created
     * \param identifier is unique identifier of the data type within the document
     */
    DataType(Document* document, int identifier);

private:
    boost::shared_ptr<DataTypePrivate> const d;
};

#endif // DATATYPE_H
