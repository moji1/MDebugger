
#include "Engine.hh"

#include "umlrtobjectclass.hh"
#include "umlrtoutsignal.hh"
struct UMLRTCommsPort;

static UMLRTObject_field fields_stopped[] = 
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

static UMLRTObject payload_stopped = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_stopped
};

static UMLRTObject_field fields_turnedLeft[] = 
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

static UMLRTObject payload_turnedLeft = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_turnedLeft
};

static UMLRTObject_field fields_turnedRight[] = 
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

static UMLRTObject payload_turnedRight = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_turnedRight
};

static UMLRTObject_field fields_moveBackwards[] = 
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

static UMLRTObject payload_moveBackwards = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_moveBackwards
};

static UMLRTObject_field fields_moveForward[] = 
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

static UMLRTObject payload_moveForward = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_moveForward
};

static UMLRTObject_field fields_stop[] = 
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

static UMLRTObject payload_stop = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_stop
};

static UMLRTObject_field fields_turnLeft[] = 
{
    {
        "angle",
        &UMLRTType_int,
        0,
        1,
        0
    }
};

static UMLRTObject payload_turnLeft = 
{
    sizeof( int ),
    1,
    fields_turnLeft
};

static UMLRTObject_field fields_turnRight[] = 
{
    {
        "angle",
        &UMLRTType_int,
        0,
        1,
        0
    }
};

static UMLRTObject payload_turnRight = 
{
    sizeof( int ),
    1,
    fields_turnRight
};

Engine::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal Engine::Base::moveBackwards() const
{
    UMLRTOutSignal signal;
    signal.initialize( "moveBackwards", signal_moveBackwards, srcPort, &payload_moveBackwards );
    return signal;
}

UMLRTOutSignal Engine::Base::moveForward() const
{
    UMLRTOutSignal signal;
    signal.initialize( "moveForward", signal_moveForward, srcPort, &payload_moveForward );
    return signal;
}

UMLRTOutSignal Engine::Base::stop() const
{
    UMLRTOutSignal signal;
    signal.initialize( "stop", signal_stop, srcPort, &payload_stop );
    return signal;
}

UMLRTOutSignal Engine::Base::turnLeft( int angle ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "turnLeft", signal_turnLeft, srcPort, &payload_turnLeft, &angle );
    return signal;
}

UMLRTOutSignal Engine::Base::turnRight( int angle ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "turnRight", signal_turnRight, srcPort, &payload_turnRight, &angle );
    return signal;
}

Engine::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal Engine::Conj::stopped() const
{
    UMLRTOutSignal signal;
    signal.initialize( "stopped", signal_stopped, srcPort, &payload_stopped );
    return signal;
}

UMLRTOutSignal Engine::Conj::turnedLeft() const
{
    UMLRTOutSignal signal;
    signal.initialize( "turnedLeft", signal_turnedLeft, srcPort, &payload_turnedLeft );
    return signal;
}

UMLRTOutSignal Engine::Conj::turnedRight() const
{
    UMLRTOutSignal signal;
    signal.initialize( "turnedRight", signal_turnedRight, srcPort, &payload_turnedRight );
    return signal;
}


