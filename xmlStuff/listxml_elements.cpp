//Gets a document, tag and attribute and displays the attibute value.
//CHS 24/10/2015

#include "listxml_elements.h"


QStringList ListXmlElements(QDomDocument doc, QString tagname, QString attribute)
{
    QDomNodeList items = doc.elementsByTagName(tagname);
    qDebug() << "Total items = " << items.count();
    QStringList sList;

    for (int i = 0; i!=items.count(); i++)
    {
        QDomNode itemnode = items.at(i);

        // convert to element
        if (itemnode.isElement())
        {
            QDomElement element_i = itemnode.toElement();
            QString str = element_i.attribute(attribute);
            sList.push_back(element_i.attribute(attribute));
            //qDebug() << element_i.attribute(attribute);
        }
    }
    return sList;
}
