//
// C++ Implementation: FilterList
//
// Description:
//
//
// Author: cbro <cbro@semperpax.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "FilterList.h"

#define STRINGIFY(x) XSTRINGIFY(x)
#define XSTRINGIFY(x) #x

FilterItem::FilterItem ()
    : name(""), filter(""), deleted(false)
{
}

FilterItem::FilterItem (QString aName, QString aFilter, bool aDeleted)
    : name(aName), filter(aFilter), deleted(aDeleted)
{
}

void FilterItem::toXml(QDomElement parent)
{
    QDomElement p = parent.ownerDocument().createElement("Filter");
    parent.appendChild(p);
    p.setAttribute("name", name);
    if (deleted)
        p.setAttribute("deleted", "true");

    QDomText t = parent.ownerDocument().createTextNode(filter);
    p.appendChild(t);
}

FilterItem FilterItem::fromXml(QDomElement parent)
{
    FilterItem theFilter;

    if (parent.tagName() == "Filter") {
        theFilter.filter = parent.text().trimmed();
        theFilter.name = parent.attribute("name");
        theFilter.deleted = (parent.attribute("deleted") == "true" ? true : false);
    }

    return theFilter;
}

void FiltersList::add(FiltersList aFilterList)
{
    FilterListIterator it(*(aFilterList.getFilters()));
    while (it.hasNext()) {
        it.next();

        FilterItem anItem = it.value();
        if (!theFilters.contains(anItem.name))
            theFilters.insert(anItem.name, anItem);
    }
}

void FiltersList::addFilter(FilterItem aFilter)
{
    theFilters.insert(aFilter.name, aFilter);
}

FilterItem FiltersList::getFilter(QString name) const
{
    if (theFilters.contains(name))
        return theFilters.value(name);
    else {
        QMapIterator <QString, FilterItem> it(theFilters);
        while (it.hasNext()) {
            it.next();

            if (it.key().contains(name, Qt::CaseInsensitive))
                return it.value();
        }
    }
    return FilterItem();
}

QMap <QString, FilterItem>* FiltersList::getFilters()
{
    return &theFilters;
}

void FiltersList::toXml(QDomElement parent)
{
    QDomElement rt = parent.ownerDocument().createElement("Filters");
    parent.appendChild(rt);
    rt.setAttribute("creator", QString("Merkaartor v%1%2").arg(STRINGIFY(VERSION)).arg(STRINGIFY(REVISION)));

    QMapIterator <QString, FilterItem> it(theFilters);
    while (it.hasNext()) {
        it.next();

        FilterItem i = it.value();
        i.toXml(rt);
    }
}

FiltersList FiltersList::fromXml(QDomElement parent)
{
    FiltersList theFilters;

    if (parent.nodeName() == "Filters") {
        QDomElement c = parent.firstChildElement();
        while(!c.isNull()) {
            if (c.tagName() == "Filter") {
                theFilters.addFilter(FilterItem::fromXml(c));
            }

            c = c.nextSiblingElement();
        }
    }

    return theFilters;
}