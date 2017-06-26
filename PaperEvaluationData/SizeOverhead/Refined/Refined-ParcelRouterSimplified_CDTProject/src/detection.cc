
#include "detection.hh"

#include "Parcel.hh"
#include "umlrtobjectclass.hh"
#include "umlrtoutsignal.hh"
struct UMLRTCommsPort;

static UMLRTObject_field fields_detect[] = 
{
    {
        "p",
        &UMLRTType_Parcel,
        0,
        1,
        0
    }
};

static UMLRTObject payload_detect = 
{
    sizeof( Parcel ),
    1,
    fields_detect
};

detection::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal detection::Base::detect( const Parcel & p ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "detect", signal_detect, srcPort, &payload_detect, &p );
    return signal;
}

detection::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}


