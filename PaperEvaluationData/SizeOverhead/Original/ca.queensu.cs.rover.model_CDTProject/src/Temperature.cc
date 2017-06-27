
#include "Temperature.hh"

#include "umlrtobjectclass.hh"
#include "umlrtoutsignal.hh"
struct UMLRTCommsPort;

static UMLRTObject_field fields_dataCollected[] = 
{
    {
        "value",
        &UMLRTType_ptr,
        0,
        1,
        0
    }
};

static UMLRTObject payload_dataCollected = 
{
    sizeof( void * ),
    1,
    fields_dataCollected
};

static UMLRTObject_field fields_startCollecting[] = 
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

static UMLRTObject payload_startCollecting = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_startCollecting
};

static UMLRTObject_field fields_stopCollecting[] = 
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

static UMLRTObject payload_stopCollecting = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_stopCollecting
};

Temperature::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal Temperature::Base::startCollecting() const
{
    UMLRTOutSignal signal;
    signal.initialize( "startCollecting", signal_startCollecting, srcPort, &payload_startCollecting );
    return signal;
}

UMLRTOutSignal Temperature::Base::stopCollecting() const
{
    UMLRTOutSignal signal;
    signal.initialize( "stopCollecting", signal_stopCollecting, srcPort, &payload_stopCollecting );
    return signal;
}

Temperature::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal Temperature::Conj::dataCollected( void * value ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "dataCollected", signal_dataCollected, srcPort, &payload_dataCollected, &value );
    return signal;
}


