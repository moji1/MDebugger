
#include "transmission.hh"

#include "Parcel.hh"
#include "umlrtobjectclass.hh"
#include "umlrtoutsignal.hh"
struct UMLRTCommsPort;

static UMLRTObject_field fields_transmit[] = 
{
    {
        "p",
        &UMLRTType_Parcel,
        0,
        1,
        0
    }
};

static UMLRTObject payload_transmit = 
{
    sizeof( Parcel ),
    1,
    fields_transmit
};

transmission::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal transmission::Base::transmit( const Parcel & p ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "transmit", signal_transmit, srcPort, &payload_transmit, &p );
    return signal;
}

transmission::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}


