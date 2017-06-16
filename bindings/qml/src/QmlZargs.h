/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
*/

#ifndef QML_ZARGS_H
#define QML_ZARGS_H

#include <QtQml>

#include <czmq.h>
#include "qml_czmq_plugin.h"


class QmlZargs : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isNULL READ isNULL)
    
public:
    zargs_t *self;
    
    QmlZargs() { self = NULL; }
    bool isNULL() { return self == NULL; }
    
    static QObject* qmlAttachedProperties(QObject* object); // defined in QmlZargs.cpp
    
public slots:
    //  Return program name (argv[0])
    const QString progname ();

    //  Return number of positional arguments
    size_t arguments ();

    //  Return first positional argument or NULL
    const QString first ();

    //  Return next positional argument or NULL
    const QString next ();

    //  Return first named parameter value, or NULL if there are no named   
    //  parameters, or value for which zargs_param_empty (arg) returns true.
    const QString paramFirst ();

    //  Return next named parameter value, or NULL if there are no named    
    //  parameters, or value for which zargs_param_empty (arg) returns true.
    const QString paramNext ();

    //  Return current parameter name, or NULL if there are no named
    //  parameters.                                                 
    const QString paramName ();

    //  Return value of named parameter, NULL if no given parameter has
    //  been specified, or special value for wich zargs_param_empty () 
    //  returns true.                                                  
    const QString paramLookup (const QString &keys);

    //  Return value of named parameter(s), NULL if no given parameter has
    //  been specified, or special value for wich zargs_param_empty ()    
    //  returns true.                                                     
    const QString paramLookupx (const QString &keys);

    //  Returns true if there are --help -h arguments
    bool hasHelp ();

    //  Print an instance of zargs.
    void print ();
};

class QmlZargsAttached : public QObject
{
    Q_OBJECT
    QObject* m_attached;
    
public:
    QmlZargsAttached (QObject* attached) {
        Q_UNUSED (attached);
    };
    
public slots:
    //  Returns true if parameter did not have a value
    bool paramEmpty (const QString &arg);

    //  Self test of this class.
    void test (bool verbose);

    //  Create a new zargs from command line arguments.
    QmlZargs *construct (int argc, QString argv);

    //  Destroy zargs instance.
    void destruct (QmlZargs *qmlSelf);
};


QML_DECLARE_TYPEINFO(QmlZargs, QML_HAS_ATTACHED_PROPERTIES)

#endif
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
*/
