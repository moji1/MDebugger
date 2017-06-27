
#include "Config.hh"

#include "Configuration.hh"
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
        &UMLRTType_Configuration,
        0,
        1,
        0
    }
};

static UMLRTObject payload_ReplyConfig = 
{
    sizeof( Configuration ),
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
        &UMLRTType_Configuration,
        0,
        1,
        0
    }
};

static UMLRTObject payload_StartUp = 
{
    sizeof( Configuration ),
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

Config::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal Config::Base::IAMMaster( char * MasterName ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "IAMMaster", signal_IAMMaster, srcPort, &payload_IAMMaster, &MasterName );
    return signal;
}

UMLRTOutSignal Config::Base::QueryConfig() const
{
    UMLRTOutSignal signal;
    signal.initialize( "QueryConfig", signal_QueryConfig, srcPort, &payload_QueryConfig );
    return signal;
}

UMLRTOutSignal Config::Base::QueryMasterId() const
{
    UMLRTOutSignal signal;
    signal.initialize( "QueryMasterId", signal_QueryMasterId, srcPort, &payload_QueryMasterId );
    return signal;
}

UMLRTOutSignal Config::Base::QueryReplicationMode() const
{
    UMLRTOutSignal signal;
    signal.initialize( "QueryReplicationMode", signal_QueryReplicationMode, srcPort, &payload_QueryReplicationMode );
    return signal;
}

UMLRTOutSignal Config::Base::QueryServerRole( char * ServerName ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "QueryServerRole", signal_QueryServerRole, srcPort, &payload_QueryServerRole, &ServerName );
    return signal;
}

Config::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal Config::Conj::BIT() const
{
    UMLRTOutSignal signal;
    signal.initialize( "BIT", signal_BIT, srcPort, &payload_BIT );
    return signal;
}

UMLRTOutSignal Config::Conj::ReplyConfig( const Configuration & config ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "ReplyConfig", signal_ReplyConfig, srcPort, &payload_ReplyConfig, &config );
    return signal;
}

UMLRTOutSignal Config::Conj::ReplyMasterId( int MasterId ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "ReplyMasterId", signal_ReplyMasterId, srcPort, &payload_ReplyMasterId, &MasterId );
    return signal;
}

UMLRTOutSignal Config::Conj::ReplyReplicationMode( int RunningMode ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "ReplyReplicationMode", signal_ReplyReplicationMode, srcPort, &payload_ReplyReplicationMode, &RunningMode );
    return signal;
}

UMLRTOutSignal Config::Conj::ReplyServerRole( int ServerRole ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "ReplyServerRole", signal_ReplyServerRole, srcPort, &payload_ReplyServerRole, &ServerRole );
    return signal;
}

UMLRTOutSignal Config::Conj::Shutdown() const
{
    UMLRTOutSignal signal;
    signal.initialize( "Shutdown", signal_Shutdown, srcPort, &payload_Shutdown );
    return signal;
}

UMLRTOutSignal Config::Conj::StartUp( const Configuration & config ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "StartUp", signal_StartUp, srcPort, &payload_StartUp, &config );
    return signal;
}


