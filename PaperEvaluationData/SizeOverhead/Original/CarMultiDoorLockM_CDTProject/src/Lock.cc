
#include "Lock.hh"

#include "Locking.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_Lock::Capsule_Lock( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, lockPort( borderPorts[borderport_lockPort] )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[locked] = "locked";
    stateNames[unlocked] = "unlocked";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}





void Capsule_Lock::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_lockPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_lockPort, index, true );
            break;
        }
}

void Capsule_Lock::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_lockPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_lockPort, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_lockPort], index );
            break;
        }
}

void Capsule_Lock::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case unlocked:
        currentState = state_____unlocked( &message );
        break;
    case locked:
        currentState = state_____locked( &message );
        break;
    default:
        break;
    }
}

void Capsule_Lock::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____init( &message );
    currentState = unlocked;
}

const char * Capsule_Lock::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_Lock::entryaction_____locked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::locked entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::entryaction_____unlocked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::unlocked entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____locked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::locked exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____unlocked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::unlocked exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition Initial1,unlocked */
    std::cout<<"The Lock "<<this->borderPorts[0]->slotName()<<"  is unlocked"<<std::endl;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____lock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition unlocked,locked,lock:lockPort */
    std::cout<<"The Lock "<<this->borderPorts[0]->slotName()<<"  is locked"<<std::endl;
    lockPort.lockStatus(true).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____twiceLock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition locked,locked,lock:lockPort */
    std::cout<<"The Lock   "<<this->borderPorts[0]->slotName()<<"  is already unlocked"<<std::endl;
    lockPort.lockStatus(false).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____twiceUnlock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition unlocked,unlocked,unlock:lockPort */
    std::cout<<"The Lock   "<<this->borderPorts[0]->slotName()<<"  is already unlocked"<<std::endl;
    lockPort.lockStatus(true).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____unlock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition locked,unlocked,unlock:lockPort */
    std::cout<<"The Lock "<<this->borderPorts[0]->slotName()<<"  is unlocked"<<std::endl;
    lockPort.lockStatus(false).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::actionchain_____init( const UMLRTMessage * msg )
{
    transitionaction_____init( msg );
    entryaction_____unlocked( msg );
}

void Capsule_Lock::actionchain_____lock( const UMLRTMessage * msg )
{
    exitaction_____unlocked( msg );
    transitionaction_____lock( msg );
    entryaction_____locked( msg );
}

void Capsule_Lock::actionchain_____twiceLock( const UMLRTMessage * msg )
{
    exitaction_____locked( msg );
    transitionaction_____twiceLock( msg );
    entryaction_____locked( msg );
}

void Capsule_Lock::actionchain_____twiceUnlock( const UMLRTMessage * msg )
{
    exitaction_____unlocked( msg );
    transitionaction_____twiceUnlock( msg );
    entryaction_____unlocked( msg );
}

void Capsule_Lock::actionchain_____unlock( const UMLRTMessage * msg )
{
    exitaction_____locked( msg );
    transitionaction_____unlock( msg );
    entryaction_____unlocked( msg );
}

Capsule_Lock::State Capsule_Lock::state_____locked( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_lockPort:
        switch( msg->getSignalId() )
        {
        case Locking::signal_unlock:
            actionchain_____unlock( msg );
            return unlocked;
        case Locking::signal_lock:
            actionchain_____twiceLock( msg );
            return locked;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____unlocked( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_lockPort:
        switch( msg->getSignalId() )
        {
        case Locking::signal_lock:
            actionchain_____lock( msg );
            return locked;
        case Locking::signal_unlock:
            actionchain_____twiceUnlock( msg );
            return unlocked;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}


static const UMLRTCommsPortRole portroles_border[] = 
{
    {
        Capsule_Lock::port_lockPort,
        "Locking",
        "lockPort",
        "",
        1,
        true,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static void instantiate_Lock( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_Lock( &Lock, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Lock = 
{
    "Lock",
    NULL,
    instantiate_Lock,
    0,
    NULL,
    1,
    portroles_border,
    0,
    NULL
};

