
#include "FailOver.hh"

#include "umlrtobjectclass.hh"
#include "umlrtoutsignal.hh"
struct UMLRTCommsPort;

static UMLRTObject_field fields_IAmAlive[] = 
{
    {
        "ServerName",
        &UMLRTType_charptr,
        0,
        1,
        0
    }
};

static UMLRTObject payload_IAmAlive = 
{
    sizeof( char * ),
    1,
    fields_IAmAlive
};

FailOver::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal FailOver::Base::IAmAlive( char * ServerName ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "IAmAlive", signal_IAmAlive, srcPort, &payload_IAmAlive, &ServerName );
    return signal;
}

FailOver::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal FailOver::Conj::IAmAlive( char * ServerName ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "IAmAlive", signal_IAmAlive, srcPort, &payload_IAmAlive, &ServerName );
    return signal;
}


