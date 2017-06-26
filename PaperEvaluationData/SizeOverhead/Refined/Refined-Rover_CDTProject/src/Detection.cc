
#include "Detection.hh"

#include "umlrtobjectclass.hh"
#include "umlrtoutsignal.hh"
struct UMLRTCommsPort;

static UMLRTObject_field fields_obstacleDetected[] = 
{
    {
        "distance",
        &UMLRTType_double,
        0,
        1,
        0
    }
};

static UMLRTObject payload_obstacleDetected = 
{
    sizeof( double ),
    1,
    fields_obstacleDetected
};

static UMLRTObject_field fields_startDetection[] = 
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

static UMLRTObject payload_startDetection = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_startDetection
};

static UMLRTObject_field fields_stopDetection[] = 
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

static UMLRTObject payload_stopDetection = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_stopDetection
};

Detection::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal Detection::Base::startDetection() const
{
    UMLRTOutSignal signal;
    signal.initialize( "startDetection", signal_startDetection, srcPort, &payload_startDetection );
    return signal;
}

UMLRTOutSignal Detection::Base::stopDetection() const
{
    UMLRTOutSignal signal;
    signal.initialize( "stopDetection", signal_stopDetection, srcPort, &payload_stopDetection );
    return signal;
}

Detection::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal Detection::Conj::obstacleDetected( double distance ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "obstacleDetected", signal_obstacleDetected, srcPort, &payload_obstacleDetected, &distance );
    return signal;
}


