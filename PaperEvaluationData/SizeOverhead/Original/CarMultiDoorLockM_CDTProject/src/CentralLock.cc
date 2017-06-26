
#include "CentralLock.hh"

#include "Locking.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include "umlrttimerprotocol.hh"
#include <cstddef>
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_CentralLock::Capsule_CentralLock( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, lockPort( borderPorts[borderport_lockPort] )
, startupTimer( borderPorts[borderport_startupTimer] )
, tmpInt( 0 )
, locksCount( 4 )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[StartingUp] = "StartingUp";
    stateNames[WaitAllDoorBeClosed] = "WaitAllDoorBeClosed";
    stateNames[WaitAllDoorBeOpened] = "WaitAllDoorBeOpened";
    stateNames[doorsClosed] = "doorsClosed";
    stateNames[doorsOpen] = "doorsOpen";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}






void Capsule_CentralLock::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_lockPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_lockPort, index, true );
            break;
        }
}

void Capsule_CentralLock::unbindPort( bool isBorder, int portId, int index )
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



void Capsule_CentralLock::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case doorsOpen:
        currentState = state_____doorsOpen( &message );
        break;
    case doorsClosed:
        currentState = state_____doorsClosed( &message );
        break;
    case WaitAllDoorBeClosed:
        currentState = state_____WaitAllDoorBeClosed( &message );
        break;
    case WaitAllDoorBeOpened:
        currentState = state_____WaitAllDoorBeOpened( &message );
        break;
    case StartingUp:
        currentState = state_____StartingUp( &message );
        break;
    default:
        break;
    }
}

void Capsule_CentralLock::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____TransitionAction0( &message );
    currentState = StartingUp;
}

const char * Capsule_CentralLock::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_CentralLock::entryaction_____StartingUp( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::StartingUp entry  */
    startupTimer.informIn(UMLRTTimespec(3,0));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____WaitAllDoorBeClosed( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::WaitAllDoorBeClosed entry  */
    tmpInt++;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

void Capsule_CentralLock::entryaction_____WaitAllDoorBeOpened( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::WaitAllDoorBeOpened entry  */
    tmpInt++;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

void Capsule_CentralLock::entryaction_____doorsClosed( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::doorsClosed entry  */
    std::cout<<"Doors are closed"<<std::endl;
    std::cout<<"Press any key to open doors"<<std::endl;
    getchar();
    std::cout<<"Sending UnLock message to doors\n"<<std::endl;
    /// send message to first door
    lockPort.unlock().send(4);
    tmpInt=1;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____doorsOpen( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::doorsOpen entry  */
    std::cout<<"Doors are open"<<std::endl;
    std::cout<<"Press any key to close doors"<<std::endl;
    getchar();
    std::cout<<"Sending Lock message to doors\n"<<std::endl;
    /// send message to first door
    lockPort.lock().send(4);
    tmpInt=1;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____StartingUp( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::StartingUp exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____WaitAllDoorBeClosed( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::WaitAllDoorBeClosed exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

void Capsule_CentralLock::exitaction_____WaitAllDoorBeOpened( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::WaitAllDoorBeOpened exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

void Capsule_CentralLock::exitaction_____doorsClosed( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::doorsClosed exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

void Capsule_CentralLock::exitaction_____doorsOpen( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::doorsOpen exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

bool Capsule_CentralLock::action_____TransitionAction5__null( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock guard AllDoorClosed,doorsClosed */
    return tmpInt==locksCount;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

bool Capsule_CentralLock::action_____TransitionAction8__null( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock guard Choice1,doorsOpen */
    return tmpInt==locksCount;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

void Capsule_CentralLock::actionchain_____TransitionAction0( const UMLRTMessage * msg )
{
    entryaction_____StartingUp( msg );
}

void Capsule_CentralLock::actionchain_____TransitionAction1( const UMLRTMessage * msg )
{
    exitaction_____doorsOpen( msg );
    entryaction_____WaitAllDoorBeClosed( msg );
}

void Capsule_CentralLock::actionchain_____TransitionAction2( const UMLRTMessage * msg )
{
    exitaction_____WaitAllDoorBeOpened( msg );
}

void Capsule_CentralLock::actionchain_____TransitionAction3( const UMLRTMessage * msg )
{
    exitaction_____StartingUp( msg );
    entryaction_____doorsOpen( msg );
}

void Capsule_CentralLock::actionchain_____TransitionAction4( const UMLRTMessage * msg )
{
    exitaction_____WaitAllDoorBeClosed( msg );
}

void Capsule_CentralLock::actionchain_____TransitionAction5( const UMLRTMessage * msg )
{
    entryaction_____doorsClosed( msg );
}

void Capsule_CentralLock::actionchain_____TransitionAction6( const UMLRTMessage * msg )
{
    entryaction_____WaitAllDoorBeClosed( msg );
}

void Capsule_CentralLock::actionchain_____TransitionAction7( const UMLRTMessage * msg )
{
    exitaction_____doorsClosed( msg );
    entryaction_____WaitAllDoorBeOpened( msg );
}

void Capsule_CentralLock::actionchain_____TransitionAction8( const UMLRTMessage * msg )
{
    entryaction_____doorsOpen( msg );
}

void Capsule_CentralLock::actionchain_____TransitionAction9( const UMLRTMessage * msg )
{
    entryaction_____WaitAllDoorBeOpened( msg );
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____AllDoorClosed( const UMLRTMessage * msg )
{
    if( action_____TransitionAction5__null( msg ) )
    {
        actionchain_____TransitionAction5( msg );
        return doorsClosed;
    }
    else
    {
        actionchain_____TransitionAction6( msg );
        return WaitAllDoorBeClosed;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____Choice1( const UMLRTMessage * msg )
{
    if( action_____TransitionAction8__null( msg ) )
    {
        actionchain_____TransitionAction8( msg );
        return doorsOpen;
    }
    else
    {
        actionchain_____TransitionAction9( msg );
        return WaitAllDoorBeOpened;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____StartingUp( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_startupTimer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____TransitionAction3( msg );
            return doorsOpen;
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

Capsule_CentralLock::State Capsule_CentralLock::state_____WaitAllDoorBeClosed( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_lockPort:
        switch( msg->getSignalId() )
        {
        case Locking::signal_lockStatus:
            actionchain_____TransitionAction4( msg );
            return choice_____AllDoorClosed( msg );
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

Capsule_CentralLock::State Capsule_CentralLock::state_____WaitAllDoorBeOpened( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_lockPort:
        switch( msg->getSignalId() )
        {
        case Locking::signal_lockStatus:
            actionchain_____TransitionAction2( msg );
            return choice_____Choice1( msg );
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

Capsule_CentralLock::State Capsule_CentralLock::state_____doorsClosed( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_lockPort:
        switch( msg->getSignalId() )
        {
        case Locking::signal_lockStatus:
            actionchain_____TransitionAction7( msg );
            return WaitAllDoorBeOpened;
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

Capsule_CentralLock::State Capsule_CentralLock::state_____doorsOpen( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_lockPort:
        switch( msg->getSignalId() )
        {
        case Locking::signal_lockStatus:
            actionchain_____TransitionAction1( msg );
            return WaitAllDoorBeClosed;
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
        Capsule_CentralLock::port_lockPort,
        "Locking",
        "lockPort",
        "",
        4,
        true,
        true,
        false,
        false,
        false,
        false,
        true
    },
    {
        Capsule_CentralLock::port_startupTimer,
        "Timing",
        "startupTimer",
        "",
        1,
        true,
        false,
        false,
        false,
        true,
        false,
        false
    }
};

static void instantiate_CentralLock( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_CentralLock( &CentralLock, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass CentralLock = 
{
    "CentralLock",
    NULL,
    instantiate_CentralLock,
    0,
    NULL,
    2,
    portroles_border,
    0,
    NULL
};

