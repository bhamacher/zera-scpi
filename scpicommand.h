#ifndef SCPICOMMAND_H
#define SCPICOMMAND_H

#include <QString>
#include <QStringList>
#include <QTextStream>
#include "SCPI_global.h"

class cSCPICommandPrivate;

/**
  @brief
  cSCPICommand is a class to support parsing of scpi commands.

  An entered command is parsed and parameters behind the command are stored in a qstringlist and can be read.
  */
class SCPISHARED_EXPORT cSCPICommand
{
public:
    /**
      @b Generates an empty scpicommand.
      */
    cSCPICommand();
    /**
      @b Generates a scpicommand from str.
      */
    cSCPICommand(const QString& str);
    ~cSCPICommand();
    /**
      @b Sets the scpicommand with str and return a reference to *this.
      */
    cSCPICommand& operator = (const QString& str);
    /**
      @b Sets the scpicommand from a QTextStream and returns a reference to QTextStream.
      */
    friend QTextStream& operator >> (QTextStream& ts, cSCPICommand& cmd);
    /**
      @b Returns the scpicommand.
      */
    const QString& getCommand();
    /**
      @b Returns the number of parameters in the command.
      */
    quint32 getParamCount();
    /**
      @b Returns the parameter from pos.
      */
    QString& getParam(quint32 pos);
    /**
      @b Returns true if the command is a valid query, means only ? and no additional parameters
      */
    bool isQuery();
private:
    /**
      @b D'pointer to the private library internal structure

      this is used to hide the internal structure, and thus make the library ABI safe
      */
    cSCPICommandPrivate *d_ptr;
};

#endif // SCPICOMMAND_H