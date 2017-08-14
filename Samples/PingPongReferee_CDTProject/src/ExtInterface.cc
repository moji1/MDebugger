
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

struct params_dbgRemBreakPoint
{
    char * location;
    int breakPointType;
    int place;
};

static UMLRTObject_field fields_dbgRemBreakPoint[] = 
{
    {
        "location",
        &UMLRTType_charptr,
        offsetof( params_dbgRemBreakPoint, location ),
        1,
        0
    },
    {
        "breakPointType",
        &UMLRTType_int,
        offsetof( params_dbgRemBreakPoint, breakPointType ),
        1,
        0
    },
    {
        "place",
        &UMLRTType_int,
        offsetof( params_dbgRemBreakPoint, place ),
        1,
        0
    }
};

static UMLRTObject payload_dbgRemBreakPoint = 
{
    sizeof( params_dbgRemBreakPoint ),
    3,
    fields_dbgRemBreakPoint
};

struct params_dbgSetBreakPoint
{
    char * location;
    int breakPointType;
    int place;
};

static UMLRTObject_field fields_dbgSetBreakPoint[] = 
{
    {
        "location",
        &UMLRTType_charptr,
        offsetof( params_dbgSetBreakPoint, location ),
        1,
        0
    },
    {
        "breakPointType",
        &UMLRTType_int,
        offsetof( params_dbgSetBreakPoint, breakPointType ),
        1,
        0
    },
    {
        "place",
        &UMLRTType_int,
        offsetof( params_dbgSetBreakPoint, place ),
        1,
        0
    }
};

static UMLRTObject payload_dbgSetBreakPoint = 
{
    sizeof( params_dbgSetBreakPoint ),
    3,
    fields_dbgSetBreakPoint
};

static UMLRTObject_field fields_dbgSetExecMode[] = 
{
    {
        "execMode",
        &UMLRTType_int,
        0,
        1,
        0
    }
};

static UMLRTObject payload_dbgSetExecMode = 
{
    sizeof( int ),
    1,
    fields_dbgSetExecMode
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

static UMLRTObject_field fields_dbgViewBreakPoints[] = 
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

static UMLRTObject payload_dbgViewBreakPoints = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_dbgViewBreakPoints
};

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

UMLRTOutSignal ExtInterface::Base::dbgRemBreakPoint( char * location, int breakPointType, int place ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "dbgRemBreakPoint", signal_dbgRemBreakPoint, srcPort, &payload_dbgRemBreakPoint, &location, &breakPointType, &place );
    return signal;
}

UMLRTOutSignal ExtInterface::Base::dbgSetBreakPoint( char * location, int breakPointType, int place ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "dbgSetBreakPoint", signal_dbgSetBreakPoint, srcPort, &payload_dbgSetBreakPoint, &location, &breakPointType, &place );
    return signal;
}

UMLRTOutSignal ExtInterface::Base::dbgSetExecMode( int execMode ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "dbgSetExecMode", signal_dbgSetExecMode, srcPort, &payload_dbgSetExecMode, &execMode );
    return signal;
}

UMLRTOutSignal ExtInterface::Base::dbgVarChange( char * varName, char * varValue ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "dbgVarChange", signal_dbgVarChange, srcPort, &payload_dbgVarChange, &varName, &varValue );
    return signal;
}

UMLRTOutSignal ExtInterface::Base::dbgViewBreakPoints() const
{
    UMLRTOutSignal signal;
    signal.initialize( "dbgViewBreakPoints", signal_dbgViewBreakPoints, srcPort, &payload_dbgViewBreakPoints );
    return signal;
}


