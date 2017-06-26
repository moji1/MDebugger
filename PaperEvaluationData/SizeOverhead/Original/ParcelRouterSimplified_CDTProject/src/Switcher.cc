
#include "Switcher.hh"

#include "switchProtocol.hh"
#include "transmission.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include "umlrttimerprotocol.hh"
#include <cstddef>
#include "Parcel.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_Switcher::Capsule_Switcher( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, enter( borderPorts[borderport_enter] )
, left( borderPorts[borderport_left] )
, right( borderPorts[borderport_right] )
, switchProtocol( borderPorts[borderport_switchProtocol] )
, timer( borderPorts[borderport_timer] )
, delay( 1 )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[IDLE] = "IDLE";
    stateNames[OCCUPIED] = "OCCUPIED";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}










void Capsule_Switcher::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_enter:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_enter, index, true );
            break;
        case borderport_left:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_left, index, true );
            break;
        case borderport_right:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_right, index, true );
            break;
        case borderport_switchProtocol:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_switchProtocol, index, true );
            break;
        }
}

void Capsule_Switcher::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_enter:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_enter, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_enter], index );
            break;
        case borderport_left:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_left, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_left], index );
            break;
        case borderport_right:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_right, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_right], index );
            break;
        case borderport_switchProtocol:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_switchProtocol, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_switchProtocol], index );
            break;
        }
}




void Capsule_Switcher::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case IDLE:
        currentState = state_____IDLE( &message );
        break;
    case OCCUPIED:
        currentState = state_____OCCUPIED( &message );
        break;
    default:
        break;
    }
}

void Capsule_Switcher::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Initial( &message );
    currentState = IDLE;
}

const char * Capsule_Switcher::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_Switcher::entryaction_____IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouterSimplified/model.uml RootElement::Switcher::IDLE entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Switcher::entryaction_____OCCUPIED( const UMLRTMessage * msg )
{
    #define umlrtparam_p ( *(const Parcel * )msg->getParam( 0 ) )
    #define rtdata ( (const Parcel * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouterSimplified/model.uml RootElement::Switcher::OCCUPIED entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_p
}

void Capsule_Switcher::exitaction_____IDLE( const UMLRTMessage * msg )
{
    #define umlrtparam_c ( *(int *)msg->getParam( 0 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouterSimplified/model.uml RootElement::Switcher::IDLE exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_c
}

void Capsule_Switcher::exitaction_____OCCUPIED( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouterSimplified/model.uml RootElement::Switcher::OCCUPIED exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Switcher::transitionaction_____TransitionAction1( const UMLRTMessage * msg )
{
    #define umlrtparam_c ( *(int *)msg->getParam( 0 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouterSimplified/model.uml RootElement::Switcher transition IDLE,IDLE,setSwitch:switchProtocol */
    this->choice = umlrtparam_c;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_c
}

void Capsule_Switcher::transitionaction_____TransitionAction4( const UMLRTMessage * msg )
{
    #define umlrtparam_c ( *(int *)msg->getParam( 0 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouterSimplified/model.uml RootElement::Switcher transition OCCUPIED,OCCUPIED,setSwitch:switchProtocol */
    log.show("Impossible to activate the switch of %s: the switch gate is obstructed by a parcel\n", this->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_c
}

void Capsule_Switcher::transitionaction_____reception( const UMLRTMessage * msg )
{
    #define umlrtparam_p ( *(const Parcel * )msg->getParam( 0 ) )
    #define rtdata ( (const Parcel * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouterSimplified/model.uml RootElement::Switcher transition IDLE,OCCUPIED,transmit:enter */
    this->parcel = Parcel();
    this->parcel.number = umlrtparam_p.number;
    this->parcel.level = umlrtparam_p.level;
    this->parcel.stage = umlrtparam_p.stage;
    log.show("Switcher %s of stage %d becomes occupied\n", this->getName(), umlrtparam_p.stage);
    timer.informIn(UMLRTTimespec(this->delay,0));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_p
}

void Capsule_Switcher::transitionaction_____transmission( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouterSimplified/model.uml RootElement::Switcher transition OCCUPIED,IDLE,timeout:timer */
    this->parcel.level--;
    log.show("Switcher %s of stage %d is now free\n", this->getName(), this->parcel.stage);
    if (choice == 0) {
    this->parcel.stage = 1;
    left.transmit(this->parcel).send();
    }
    else {
    this->parcel.stage = 2;
    right.transmit(this->parcel).send();
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Switcher::actionchain_____Initial( const UMLRTMessage * msg )
{
    entryaction_____IDLE( msg );
}

void Capsule_Switcher::actionchain_____TransitionAction1( const UMLRTMessage * msg )
{
    exitaction_____IDLE( msg );
    transitionaction_____TransitionAction1( msg );
    entryaction_____IDLE( msg );
}

void Capsule_Switcher::actionchain_____TransitionAction4( const UMLRTMessage * msg )
{
    exitaction_____OCCUPIED( msg );
    transitionaction_____TransitionAction4( msg );
    entryaction_____OCCUPIED( msg );
}

void Capsule_Switcher::actionchain_____reception( const UMLRTMessage * msg )
{
    exitaction_____IDLE( msg );
    transitionaction_____reception( msg );
    entryaction_____OCCUPIED( msg );
}

void Capsule_Switcher::actionchain_____transmission( const UMLRTMessage * msg )
{
    exitaction_____OCCUPIED( msg );
    transitionaction_____transmission( msg );
    entryaction_____IDLE( msg );
}

Capsule_Switcher::State Capsule_Switcher::state_____IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_switchProtocol:
        switch( msg->getSignalId() )
        {
        case switchProtocol::signal_setSwitch:
            actionchain_____TransitionAction1( msg );
            return IDLE;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_enter:
        switch( msg->getSignalId() )
        {
        case transmission::signal_transmit:
            actionchain_____reception( msg );
            return OCCUPIED;
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

Capsule_Switcher::State Capsule_Switcher::state_____OCCUPIED( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____transmission( msg );
            return IDLE;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_switchProtocol:
        switch( msg->getSignalId() )
        {
        case switchProtocol::signal_setSwitch:
            actionchain_____TransitionAction4( msg );
            return OCCUPIED;
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
        Capsule_Switcher::port_left,
        "transmission",
        "left",
        "",
        1,
        true,
        false,
        false,
        false,
        false,
        false,
        true
    },
    {
        Capsule_Switcher::port_right,
        "transmission",
        "right",
        "",
        1,
        true,
        false,
        false,
        false,
        false,
        false,
        true
    },
    {
        Capsule_Switcher::port_enter,
        "transmission",
        "enter",
        "",
        1,
        true,
        true,
        false,
        false,
        false,
        false,
        true
    },
    {
        Capsule_Switcher::port_switchProtocol,
        "switchProtocol",
        "switchProtocol",
        "",
        1,
        true,
        true,
        false,
        false,
        false,
        false,
        true
    },
    {
        Capsule_Switcher::port_timer,
        "Timing",
        "timer",
        "",
        1,
        true,
        false,
        false,
        false,
        true,
        false,
        false
    },
    {
        Capsule_Switcher::port_log,
        "Log",
        "log",
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

static void instantiate_Switcher( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_Switcher( &Switcher, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Switcher = 
{
    "Switcher",
    NULL,
    instantiate_Switcher,
    0,
    NULL,
    6,
    portroles_border,
    0,
    NULL
};

