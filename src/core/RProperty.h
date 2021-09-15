#ifndef RPROPERTY_H
#define RPROPERTY_H

#include <QSet>

#include "RObject.h"
#include "RPropertyTypeId.h"

class RDocument;

/**
 * Property with type ID, value and attributes. Used for concurrent property collection.
 *
 * \ingroup core
 */
class RProperty {
public:
    RProperty(const RDocument& document,
              const QSet<RObject::Id>& objectIds,
              const RPropertyTypeId& propertyTypeId,
              bool showOnRequest,
              RS::EntityType entityTypeFilter)
        : document(&document),
          objectIds(&objectIds),
          propertyTypeId(propertyTypeId),
          showOnRequest(showOnRequest),
          entityTypeFilter(entityTypeFilter) { }

    const RDocument* document;
    const QSet<RObject::Id>* objectIds;
    RPropertyTypeId propertyTypeId;
    bool showOnRequest;
    RPropertyAttributes attributes;
    QVariant value;
    RS::EntityType entityTypeFilter;
};

Q_DECLARE_METATYPE(RProperty*)

#endif
