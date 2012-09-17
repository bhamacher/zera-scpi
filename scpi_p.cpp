#include <QObject>
#include <QModelIndex>
#include <QDomDocument>
#include <QDomDocumentType>
#include <QDomElement>
#include <QList>
#include "scpi_p.h"
#include "scpinode.h"
#include "scpi.h"


cSCPIPrivate::cSCPIPrivate(QString sDevice)
    :m_sDeviceName(sDevice)
{
    m_SCPIModel.clear();
}


cSCPIPrivate::~cSCPIPrivate()
{
}


void cSCPIPrivate::genSCPICmd(const QStringList& parentnodeNames, cSCPIObject *pSCPIObject)
{
    QStringList::const_iterator it;
    QStandardItem *parentItem;
    QStandardItem *childItem;
    QModelIndex childModelIndex;

    parentItem = m_SCPIModel.invisibleRootItem();

    if (parentnodeNames.count() > 0 )
    for (it = parentnodeNames.begin(); it != parentnodeNames.end(); ++it)
    {
            childItem = 0;
            quint32 nrows = parentItem->rowCount();

            if (nrows > 0)
                for (quint32 i = 0; i < nrows; i++)
                {
                    childItem = parentItem->child(i);
                    if (childItem->data(Qt::DisplayRole).toString() == *it)
                        break;
                    else
                        childItem = 0;
                }

            if (!childItem)
            {
                cSCPINode *c = new cSCPINode(*it, SCPI::isNode, 0);
                // childItem  = new cSCPINode(*it, SCPI::isNode, 0);
                childItem = c;
                parentItem->appendRow(childItem);
            }

            parentItem = childItem;
    }

    cSCPINode *c = new cSCPINode(pSCPIObject->getName(),pSCPIObject->getType(), pSCPIObject);
    // childItem = new cSCPINode(pSCPIObject->getName(),pSCPIObject->getType(), pSCPIObject);
    childItem = c;
    parentItem->appendRow(childItem);

}


void cSCPIPrivate::genSCPICmd(const QStringList&  parentnodeNames, cSCPINode* pSCPINode)
{
    QStringList::const_iterator it;
    QStandardItem *parentItem;
    QStandardItem *childItem;
    QModelIndex childModelIndex;

    parentItem = m_SCPIModel.invisibleRootItem();

    for (it = parentnodeNames.begin(); it != parentnodeNames.end(); ++it)
    {
            childItem = 0;
            quint32 nrows = parentItem->rowCount();

            if (nrows > 0)
                for (quint32 i = 0; i < nrows; i++)
                {
                    childItem = parentItem->child(i);
                    if (childItem->data(Qt::DisplayRole) == *it)
                        break;
                    else
                        childItem = 0;
                }

            if (!childItem)
            {
                childItem  = new cSCPINode(*it, SCPI::isNode, 0);
                parentItem->appendRow(childItem);
            }

            parentItem = childItem;
    }

    parentItem->appendRow(pSCPINode);
}


void cSCPIPrivate::genSCPICmd(QMap<QString, QList<cSCPIObject*> > SCPIObjectMap)
{
    QMap<QString, QList<cSCPIObject*> >::const_iterator it1;
    QList<cSCPIObject*>::const_iterator it2;
    QList<cSCPIObject*> list;

    QStringList nl;
    for (it1 = SCPIObjectMap.begin(); it1 != SCPIObjectMap.end(); ++it1)
    {
        nl.clear();
        nl << it1.key();
        list = it1.value();
        for (it2 = list.begin(); it2 != list.end(); ++it2)
            genSCPICmd(nl, *it2 );
    }
}


void cSCPIPrivate::genSCPICmd(QMap<QString, QMap<QString, QList<cSCPIObject *> > > SCPIObjectMap)
{
    QMap<QString, QMap<QString, QList<cSCPIObject *> > >::const_iterator it1;
    QMap<QString, QList<cSCPIObject*> >::const_iterator it2;
    QList<cSCPIObject*>::const_iterator it3;
    QList<cSCPIObject*> list;

    QStringList nl;
    QString lKey1;
    for (it1 = SCPIObjectMap.begin(); it1 != SCPIObjectMap.end(); ++it1)
    {
        lKey1 = it1.key();
        for (it2 = it1->begin();it2 != it1->end(); ++it2)
        {
            nl.clear();
            nl << lKey1 << it2.key();
            list = it2.value();
            for (it3 = list.begin(); it3 != list.end(); ++it3)
                genSCPICmd(nl, *it3);
        }
    }
}


void cSCPIPrivate::genSCPICmd(QMap<QString, QMap<QString, QMap<QString, QList<cSCPIObject*> > > >SCPIObjectMap)
{
    QMap<QString, QMap<QString, QMap<QString, QList<cSCPIObject*> > > >::const_iterator it1;
    QMap<QString, QMap<QString, QList<cSCPIObject*> > >::const_iterator it2;
    QMap<QString, QList<cSCPIObject*> >::const_iterator it3;
    QList<cSCPIObject*>::const_iterator it4;
    QList<cSCPIObject*> list;

    QStringList nl;
    QString lKey1, lKey2;
    for (it1 = SCPIObjectMap.begin(); it1 != SCPIObjectMap.end(); ++it1)
    {
        lKey1 = it1.key();
        for (it2 = it1->begin();it2 != it1->end(); ++it2)
        {
            lKey2 = it2.key();
            for (it3 = it2->begin();it3 != it2->end(); ++it3)
            {
                nl.clear();
                nl << lKey1 << lKey2 << it3.key();
                list = it3.value();
                for (it4 = list.begin(); it4 != list.end(); ++it4)
                    genSCPICmd(nl, *it4);
            }
        }
    }
}

void cSCPIPrivate::genSCPICmd(QMap<QString, QMap<QString, QMap<QString, QMap<QString, QList<cSCPIObject*> > > > > SCPIObjectMap)
{
    QMap<QString, QMap<QString, QMap<QString, QMap<QString, QList<cSCPIObject*> > > > >::const_iterator it1;
    QMap<QString, QMap<QString, QMap<QString, QList<cSCPIObject*> > > >::const_iterator it2;
    QMap<QString, QMap<QString, QList<cSCPIObject*> > >::const_iterator it3;
    QMap<QString, QList<cSCPIObject*> >::const_iterator it4;
    QList<cSCPIObject*>::const_iterator it5;
    QList<cSCPIObject*> list;

    QStringList nl;
    QString lKey1, lKey2, lKey3;
    for (it1 = SCPIObjectMap.begin(); it1 != SCPIObjectMap.end(); ++it1)
    {
        lKey1 = it1.key();
        for (it2 = it1->begin();it2 != it1->end(); ++it2)
        {
            lKey2 = it2.key();
            for (it3 = it2->begin();it3 != it2->end(); ++it3)
            {
                lKey3 = it3.key();
                for (it4 = it3->begin();it4 != it3->end(); ++it4)
                nl.clear();
                nl << lKey1 << lKey2 << lKey3 << it4.key();
                list = it4.value();
                for (it5 = list.begin(); it5 != list.end(); ++it5)
                    genSCPICmd(nl, *it5);
            }
        }
    }
}

void cSCPIPrivate::genSCPICmd(QMap<QString, QMap<QString, QMap<QString, QMap<QString, QMap<QString, QList<cSCPIObject*> > > > > > SCPIObjectMap)
{
    QMap<QString, QMap<QString, QMap<QString, QMap<QString, QMap<QString, QList<cSCPIObject*> > > > > >::const_iterator it1;
    QMap<QString, QMap<QString, QMap<QString, QMap<QString, QList<cSCPIObject*> > > > >::const_iterator it2;
    QMap<QString, QMap<QString, QMap<QString, QList<cSCPIObject*> > > >::const_iterator it3;
    QMap<QString, QMap<QString, QList<cSCPIObject*> > >::const_iterator it4;
    QMap<QString, QList<cSCPIObject*> >::const_iterator it5;
    QList<cSCPIObject*>::const_iterator it6;
    QList<cSCPIObject*> list;

    QStringList nl;
    QString lKey1, lKey2, lKey3, lKey4;
    for (it1 = SCPIObjectMap.begin(); it1 != SCPIObjectMap.end(); ++it1)
    {
        lKey1 = it1.key();
        for (it2 = it1->begin();it2 != it1->end(); ++it2)
        {
            lKey2 = it2.key();
            for (it3 = it2->begin();it3 != it2->end(); ++it3)
            {
                lKey3 = it3.key();
                for (it4 = it3->begin();it4 != it3->end(); ++it4)
                {
                    lKey4 = it4.key();
                    for (it5 = it4->begin();it5 != it4->end(); ++it5)
                    {
                        nl.clear();
                        nl << lKey1 << lKey2 << lKey3 << lKey4 << it5.key();
                        list = it5.value();
                        for (it6 = list.begin(); it6 != list.end(); ++it6)
                            genSCPICmd(nl, *it6);
                    }
                }
            }
        }
    }
}


void cSCPIPrivate::clearSCPICmdList()
{
    QList<QStandardItem *> itemList;

    itemList = m_SCPIModel.takeColumn (0);
    for (qint32 i = 0; i < itemList.size(); ++i)
        delete itemList.value(i);
}


cSCPIObject* cSCPIPrivate::getSCPIObject(const QString& input, QString &Param)
{
    bool found;
    QChar* pInput;
    QStandardItem *parentItem;
    cSCPINode *childItem;
    found = false;
    pInput = (QChar*) input.data();
    parentItem = m_SCPIModel.invisibleRootItem();

    quint32 nrows;
    while ( (nrows = parentItem->rowCount()) > 0) // keywords in next command level available
    {
        cSCPIString keyw(m_Parser.GetKeyword(&pInput)); // we fetch a new keyword
        for (quint32 i = 0; i < nrows; i++)
        {
            childItem = (cSCPINode*) parentItem->child(i);
            QString s = childItem->data(Qt::DisplayRole).toString();
            if ((found = (keyw == s)))
            {
                parentItem = childItem;
                break;
            }
        }
        if ( (*pInput != ':') || !found) // the command sent is finished ... found or not found
            break;
    }

    Param = QString(pInput);

    if (found)
        return childItem->m_pSCPIObject;
    else
        return NULL;
}


QStandardItemModel* cSCPIPrivate::getSCPIModel()
{
    return &m_SCPIModel;
}


void cSCPIPrivate::appendSCPIRows(QStandardItem *rootItem, QDomDocument& doc,  QDomElement &rootElement, quint32 nlevel)
{
    quint32 nrows;
    cSCPINode *childItem;
    QString s;
    nrows = rootItem->rowCount();
    if (nrows > 0)
    {
        quint32 i;
        for (i = 0; i < nrows; i++)
        {
            childItem = (cSCPINode*) rootItem->child(i);
            s = childItem->data(Qt::DisplayRole).toString();
            QDomElement cmdTag = doc.createElement(s);
            if (nlevel == 0)
                s = "Model,";
            else
                s = "";
            s += childItem->data(Qt::ToolTipRole).toString();
            cmdTag.setAttribute(scpinodeAttributeName, s);
            rootElement.appendChild(cmdTag);
            appendSCPIRows(childItem, doc, cmdTag, ++nlevel);
            --nlevel;
        }
    }
}


void cSCPIPrivate::exportSCPIModelXML(QString& sxml)
{
    QDomDocument modelDoc(scpimodelDocName);

    QDomElement rootTag;
    rootTag = modelDoc.createElement( scpimodelrootName );
    modelDoc.appendChild( rootTag );

    QDomElement deviceTag = modelDoc.createElement( scpimodeldeviceTag );
    rootTag.appendChild( deviceTag );
    QDomText t = modelDoc.createTextNode(m_sDeviceName);
    deviceTag.appendChild( t );

    QDomElement modelsTag = modelDoc.createElement(scpimodelsTag);
    rootTag.appendChild( modelsTag );

    appendSCPIRows(m_SCPIModel.invisibleRootItem(), modelDoc, modelsTag, 0);

    sxml = modelDoc.toString();
}


quint8 cSCPIPrivate::getNodeType(const QString& sAttr)
{
    int t = SCPI::isNode;
    if ( sAttr.contains(SCPI::scpiNodeType[SCPI::Query]) )
        t += SCPI::isQuery;
    if ( sAttr.contains(SCPI::scpiNodeType[SCPI::CmdwP]) )
        t += SCPI::isCmdwP;
    else
    if ( sAttr.contains(SCPI::scpiNodeType[SCPI::Cmd]) )
        t += SCPI::isCmd;

    return t;
}


bool cSCPIPrivate::getcommandInfo( QDomNode rootNode, quint32 nlevel )
{
    static QStringList nodeNames;
    QDomNodeList nl = rootNode.childNodes();

    quint32 n = nl.length();
    if ( n > 0)
    {
        quint32 i;
        for (i=0; i<n ; i++)
        {
            if (nlevel == 0)
                nodeNames.clear(); // for each root cmd we clear the local node name list
            QDomNode node2 = nl.item(i);
            QDomElement e = node2.toElement();
            QString s = e.tagName();
            if (!node2.hasChildNodes())
            {
                quint8 t = getNodeType(e.attribute(scpinodeAttributeName));
                cSCPINode *pSCPINode = new cSCPINode (s , t, NULL); // we have no corresponding cSCPIObject -> NULL
                genSCPICmd(nodeNames, pSCPINode);
            }
            else
            {
                nodeNames.append(s); // we add each node name to the list
                getcommandInfo(node2, ++nlevel); // we look for further levels
                --nlevel;
            }
        }
    }

    if (nlevel > 0)
        nodeNames.pop_back();

    return true;
}


bool cSCPIPrivate::importSCPIModelXML(QIODevice *ioDevice)
{
    clearSCPICmdList();

    QDomDocument modelDoc;
    if ( !modelDoc.setContent(ioDevice) )
        return false;

    QDomDocumentType TheDocType = modelDoc.doctype ();
    if (TheDocType.name() != scpimodelDocName)
        return false;

    QDomElement rootElem = modelDoc.documentElement();
    if (rootElem.tagName() != scpimodelrootName)
        return false;

    QDomNodeList nl=rootElem.childNodes();

    for (quint32 i=0; i<nl.length() ; i++)
    {
        QDomNode n = nl.item(i);
        QDomElement e=n.toElement();

        if (e.tagName() == scpimodeldeviceTag)
            m_sDeviceName = e.text();

        if (e.tagName() == scpimodelsTag) // here the scpi models start
        {
            m_SCPIModel.clear(); // we clear the existing command list
            if (!getcommandInfo( n, 0))
                return false;
        }

    }

    return true;
}


