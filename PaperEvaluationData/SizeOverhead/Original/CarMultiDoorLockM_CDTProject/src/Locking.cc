
#include "Locking.hh"

#include "umlrtobjectclass.hh"
#include "umlrtoutsignal.hh"
struct UMLRTCommsPort;

static UMLRTObject_field fields_lock[] = 
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

static UMLRTObject payload_lock = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_lock
};

static UMLRTObject_field fields_unlock[] = 
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

static UMLRTObject payload_unlock = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_unlock
};

static UMLRTObject_field fields_lockStatus[] = 
{
    {
        "locked",
        &UMLRTType_bool,
        0,
        1,
        0
    }
};

static UMLRTObject payload_lockStatus = 
{
    sizeof( bool ),
    1,
    fields_lockStatus
};

Locking::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal Locking::Base::lockStatus( bool locked ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "lockStatus", signal_lockStatus, srcPort, &payload_lockStatus, &locked );
    return signal;
}

Locking::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal Locking::Conj::lock() const
{
    UMLRTOutSignal signal;
    signal.initialize( "lock", signal_lock, srcPort, &payload_lock );
    return signal;
}

UMLRTOutSignal Locking::Conj::unlock() const
{
    UMLRTOutSignal signal;
    signal.initialize( "unlock", signal_unlock, srcPort, &payload_unlock );
    return signal;
}


