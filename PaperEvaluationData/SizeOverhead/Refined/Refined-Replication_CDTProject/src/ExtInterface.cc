
#include "ExtInterface.hh"

#include "COMMANDS.hh"
#include "umlrtobjectclass.hh"
#include "umlrtoutsignal.hh"
#include <cstddef>
struct UMLRTCommsPort;

static UMLRTObject_field fields_event[] = 
{
    {
        "eventInfo",
        &UMLRTType_charptr,
        0,
        1,
        0
    }
};

static UMLRTObject payload_event = 
{
    sizeof( char * ),
    1,
    fields_event
};

static UMLRTObject_field fields_registerToControl[] = 
{
    {
        "capsuleInstanceName",
        &UMLRTType_charptr,
        0,
        1,
        0
    }
};

static UMLRTObject payload_registerToControl = 
{
    sizeof( char * ),
    1,
    fields_registerToControl
};

static UMLRTObject_field fields_selfExec[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_selfExec = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_selfExec
};

static UMLRTObject_field fields_dbgCommand[] = 
{
    {
        "data",
        &UMLRTType_int,
        0,
        1,
        0
    }
};

static UMLRTObject payload_dbgCommand = 
{
    sizeof( COMMANDS ),
    1,
    fields_dbgCommand
};

static UMLRTObject_field fields_dbgExec[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_dbgExec = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_dbgExec
};

struct params_dbgVarChange
{
    char * varName;
    char * varValue;
};

static UMLRTObject_field fields_dbgVarChange[] = 
{
    {
        "varName",
        &UMLRTType_charptr,
        offsetof( params_dbgVarChange, varName ),
        1,
        0
    },
    {
        "varValue",
        &UMLRTType_charptr,
        offsetof( params_dbgVarChange, varValue ),
        1,
        0
    }
};

static UMLRTObject payload_dbgVarChange = 
{
    sizeof( params_dbgVarChange ),
    2,
    fields_dbgVarChange
};

ExtInterface::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal ExtInterface::Base::dbgCommand( const COMMANDS & data ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "dbgCommand", signal_dbgCommand, srcPort, &payload_dbgCommand, &data );
    return signal;
}

UMLRTOutSignal ExtInterface::Base::dbgExec() const
{
    UMLRTOutSignal signal;
    signal.initialize( "dbgExec", signal_dbgExec, srcPort, &payload_dbgExec );
    return signal;
}

UMLRTOutSignal ExtInterface::Base::dbgVarChange( char * varName, char * varValue ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "dbgVarChange", signal_dbgVarChange, srcPort, &payload_dbgVarChange, &varName, &varValue );
    return signal;
}

ExtInterface::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal ExtInterface::Conj::event( char * eventInfo ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "event", signal_event, srcPort, &payload_event, &eventInfo );
    return signal;
}

UMLRTOutSignal ExtInterface::Conj::registerToControl( char * capsuleInstanceName ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "registerToControl", signal_registerToControl, srcPort, &payload_registerToControl, &capsuleInstanceName );
    return signal;
}

UMLRTOutSignal ExtInterface::Conj::selfExec() const
{
    UMLRTOutSignal signal;
    signal.initialize( "selfExec", signal_selfExec, srcPort, &payload_selfExec );
    return signal;
}


