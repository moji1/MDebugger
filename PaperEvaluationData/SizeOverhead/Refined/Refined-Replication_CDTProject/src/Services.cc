
#include "Services.hh"

#include "umlrtobjectclass.hh"
#include "umlrtoutsignal.hh"
struct UMLRTCommsPort;

static UMLRTObject_field fields_Reply[] = 
{
    {
        "Result",
        &UMLRTType_int,
        0,
        1,
        0
    }
};

static UMLRTObject payload_Reply = 
{
    sizeof( int ),
    1,
    fields_Reply
};

static UMLRTObject_field fields_Request[] = 
{
    {
        "ServiceID",
        &UMLRTType_int,
        0,
        1,
        0
    }
};

static UMLRTObject payload_Request = 
{
    sizeof( int ),
    1,
    fields_Request
};

Services::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal Services::Conj::Reply( int Result ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "Reply", signal_Reply, srcPort, &payload_Reply, &Result );
    return signal;
}

Services::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal Services::Base::Request( int ServiceID ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "Request", signal_Request, srcPort, &payload_Request, &ServiceID );
    return signal;
}


