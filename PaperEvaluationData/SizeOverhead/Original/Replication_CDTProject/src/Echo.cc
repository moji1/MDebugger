
#include "Echo.hh"

#include "umlrtobjectclass.hh"
#include "umlrtoutsignal.hh"
struct UMLRTCommsPort;

static UMLRTObject_field fields_Echo[] = 
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

static UMLRTObject payload_Echo = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_Echo
};

Echo::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal Echo::Base::Echo() const
{
    UMLRTOutSignal signal;
    signal.initialize( "Echo", signal_Echo, srcPort, &payload_Echo );
    return signal;
}

Echo::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal Echo::Conj::Echo() const
{
    UMLRTOutSignal signal;
    signal.initialize( "Echo", signal_Echo, srcPort, &payload_Echo );
    return signal;
}


