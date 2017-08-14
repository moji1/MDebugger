
#include "StartProtocol.hh"

#include "umlrtobjectclass.hh"
#include "umlrtoutsignal.hh"
struct UMLRTCommsPort;

static UMLRTObject_field fields_start[] = 
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

static UMLRTObject payload_start = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_start
};

StartProtocol::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

StartProtocol::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal StartProtocol::Base::start() const
{
    UMLRTOutSignal signal;
    signal.initialize( "start", signal_start, srcPort, &payload_start );
    return signal;
}


