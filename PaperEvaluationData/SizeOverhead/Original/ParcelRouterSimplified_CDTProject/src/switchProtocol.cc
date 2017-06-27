
#include "switchProtocol.hh"

#include "umlrtobjectclass.hh"
#include "umlrtoutsignal.hh"
struct UMLRTCommsPort;

static UMLRTObject_field fields_setSwitch[] = 
{
    {
        "c",
        &UMLRTType_int,
        0,
        1,
        0
    }
};

static UMLRTObject payload_setSwitch = 
{
    sizeof( int ),
    1,
    fields_setSwitch
};

switchProtocol::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

switchProtocol::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal switchProtocol::Base::setSwitch( int c ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "setSwitch", signal_setSwitch, srcPort, &payload_setSwitch, &c );
    return signal;
}


