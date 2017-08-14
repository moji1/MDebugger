
#include "PingPongProtocol.hh"

#include "umlrtobjectclass.hh"
#include "umlrtoutsignal.hh"
struct UMLRTCommsPort;

static UMLRTObject_field fields_ping[] = 
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

static UMLRTObject payload_ping = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_ping
};

static UMLRTObject_field fields_pong[] = 
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

static UMLRTObject payload_pong = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_pong
};

PingPongProtocol::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal PingPongProtocol::Base::pong() const
{
    UMLRTOutSignal signal;
    signal.initialize( "pong", signal_pong, srcPort, &payload_pong );
    return signal;
}

PingPongProtocol::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal PingPongProtocol::Conj::ping() const
{
    UMLRTOutSignal signal;
    signal.initialize( "ping", signal_ping, srcPort, &payload_ping );
    return signal;
}


