
#include "ConfigProtocol.hh"

#include "SystemConfig.hh"
#include "umlrtobjectclass.hh"
#include "umlrtoutsignal.hh"
struct UMLRTCommsPort;

static UMLRTObject_field fields_BIT[] = 
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

static UMLRTObject payload_BIT = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_BIT
};

static UMLRTObject_field fields_ReplyConfig[] = 
{
    {
        "config",
        &UMLRTType_SystemConfig,
        0,
        1,
        0
    }
};

static UMLRTObject payload_ReplyConfig = 
{
    sizeof( SystemConfig ),
    1,
    fields_ReplyConfig
};

static UMLRTObject_field fields_ReplyMasterId[] = 
{
    {
        "MasterId",
        &UMLRTType_int,
        0,
        1,
        0
    }
};

static UMLRTObject payload_ReplyMasterId = 
{
    sizeof( int ),
    1,
    fields_ReplyMasterId
};

static UMLRTObject_field fields_ReplyReplicationMode[] = 
{
    {
        "RunningMode",
        &UMLRTType_int,
        0,
        1,
        0
    }
};

static UMLRTObject payload_ReplyReplicationMode = 
{
    sizeof( int ),
    1,
    fields_ReplyReplicationMode
};

static UMLRTObject_field fields_ReplyServerRole[] = 
{
    {
        "ServerRole",
        &UMLRTType_int,
        0,
        1,
        0
    }
};

static UMLRTObject payload_ReplyServerRole = 
{
    sizeof( int ),
    1,
    fields_ReplyServerRole
};

static UMLRTObject_field fields_Shutdown[] = 
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

static UMLRTObject payload_Shutdown = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_Shutdown
};

static UMLRTObject_field fields_StartUp[] = 
{
    {
        "config",
        &UMLRTType_SystemConfig,
        0,
        1,
        0
    }
};

static UMLRTObject payload_StartUp = 
{
    sizeof( SystemConfig ),
    1,
    fields_StartUp
};

static UMLRTObject_field fields_IAMMaster[] = 
{
    {
        "MasterName",
        &UMLRTType_charptr,
        0,
        1,
        0
    }
};

static UMLRTObject payload_IAMMaster = 
{
    sizeof( char * ),
    1,
    fields_IAMMaster
};

static UMLRTObject_field fields_QueryConfig[] = 
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

static UMLRTObject payload_QueryConfig = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_QueryConfig
};

static UMLRTObject_field fields_QueryMasterId[] = 
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

static UMLRTObject payload_QueryMasterId = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_QueryMasterId
};

static UMLRTObject_field fields_QueryReplicationMode[] = 
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

static UMLRTObject payload_QueryReplicationMode = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_QueryReplicationMode
};

static UMLRTObject_field fields_QueryServerRole[] = 
{
    {
        "ServerName",
        &UMLRTType_charptr,
        0,
        1,
        0
    }
};

static UMLRTObject payload_QueryServerRole = 
{
    sizeof( char * ),
    1,
    fields_QueryServerRole
};

ConfigProtocol::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal ConfigProtocol::Base::IAMMaster( char * MasterName ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "IAMMaster", signal_IAMMaster, srcPort, &payload_IAMMaster, &MasterName );
    return signal;
}

UMLRTOutSignal ConfigProtocol::Base::QueryConfig() const
{
    UMLRTOutSignal signal;
    signal.initialize( "QueryConfig", signal_QueryConfig, srcPort, &payload_QueryConfig );
    return signal;
}

UMLRTOutSignal ConfigProtocol::Base::QueryMasterId() const
{
    UMLRTOutSignal signal;
    signal.initialize( "QueryMasterId", signal_QueryMasterId, srcPort, &payload_QueryMasterId );
    return signal;
}

UMLRTOutSignal ConfigProtocol::Base::QueryReplicationMode() const
{
    UMLRTOutSignal signal;
    signal.initialize( "QueryReplicationMode", signal_QueryReplicationMode, srcPort, &payload_QueryReplicationMode );
    return signal;
}

UMLRTOutSignal ConfigProtocol::Base::QueryServerRole( char * ServerName ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "QueryServerRole", signal_QueryServerRole, srcPort, &payload_QueryServerRole, &ServerName );
    return signal;
}

ConfigProtocol::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal ConfigProtocol::Conj::BIT() const
{
    UMLRTOutSignal signal;
    signal.initialize( "BIT", signal_BIT, srcPort, &payload_BIT );
    return signal;
}

UMLRTOutSignal ConfigProtocol::Conj::ReplyConfig( const SystemConfig & config ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "ReplyConfig", signal_ReplyConfig, srcPort, &payload_ReplyConfig, &config );
    return signal;
}

UMLRTOutSignal ConfigProtocol::Conj::ReplyMasterId( int MasterId ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "ReplyMasterId", signal_ReplyMasterId, srcPort, &payload_ReplyMasterId, &MasterId );
    return signal;
}

UMLRTOutSignal ConfigProtocol::Conj::ReplyReplicationMode( int RunningMode ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "ReplyReplicationMode", signal_ReplyReplicationMode, srcPort, &payload_ReplyReplicationMode, &RunningMode );
    return signal;
}

UMLRTOutSignal ConfigProtocol::Conj::ReplyServerRole( int ServerRole ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "ReplyServerRole", signal_ReplyServerRole, srcPort, &payload_ReplyServerRole, &ServerRole );
    return signal;
}

UMLRTOutSignal ConfigProtocol::Conj::Shutdown() const
{
    UMLRTOutSignal signal;
    signal.initialize( "Shutdown", signal_Shutdown, srcPort, &payload_Shutdown );
    return signal;
}

UMLRTOutSignal ConfigProtocol::Conj::StartUp( const SystemConfig & config ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "StartUp", signal_StartUp, srcPort, &payload_StartUp, &config );
    return signal;
}


