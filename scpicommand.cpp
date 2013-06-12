#include "scpicommand.h"
#include "scpicommand_p.h"


cSCPICommand::cSCPICommand()
    :d_ptr(new cSCPICommandPrivate)
{
}


cSCPICommand::cSCPICommand(const QString& str)
    :d_ptr(new cSCPICommandPrivate(str))
{
}


cSCPICommand::~cSCPICommand()
{
    delete d_ptr;
}


cSCPICommand& cSCPICommand::operator = (const QString& str)
{
    *d_ptr = str;
    return *this;
}


QTextStream& operator >> (QTextStream& ts, cSCPICommand& cmd)
{
    return ts >> *(cmd.d_ptr);
}


const QString& cSCPICommand::getCommand()
{
    return d_ptr->m_sCommand;
}


const QString &cSCPICommand::getCommandStr()
{
    return d_ptr->m_sCommandStr;
}


quint32 cSCPICommand::getParamCount()
{
    return d_ptr->m_sParamList.count();
}


QString& cSCPICommand::getParam(quint32 pos)
{
    return d_ptr->m_sParamList[pos];
}

bool cSCPICommand::isQuery()
{
    return d_ptr->isQuery();
}

bool cSCPICommand::isCommand(quint8 anzParameter)
{
    return d_ptr->isCommand(anzParameter);
}
