
#include "Chute.hh"

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

Capsule_Chute::Capsule_Chute( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, detection( borderPorts[borderport_detection] )
, enter( borderPorts[borderport_enter] )
, exit( borderPorts[borderport_exit] )
, timer( borderPorts[borderport_timer] )
, delay( 1 )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[IDLE] = "IDLE";
    stateNames[OCCUPIED] = "OCCUPIED";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}









void Capsule_Chute::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_detection:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_detection, index, true );
            break;
        case borderport_enter:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_enter, index, true );
            break;
        case borderport_exit:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_exit, index, true );
            break;
        }
}

void Capsule_Chute::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_detection:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_detection, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_detection], index );
            break;
        case borderport_enter:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_enter, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_enter], index );
            break;
        case borderport_exit:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_exit, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_exit], index );
            break;
        }
}




void Capsule_Chute::inject( const UMLRTMessage & message )
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

void Capsule_Chute::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Initial( &message );
    currentState = IDLE;
}

const char * Capsule_Chute::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_Chute::entryaction_____IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouter/model.uml RootElement::Chute::IDLE entry  */
    enter.setFree(true).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::entryaction_____OCCUPIED( const UMLRTMessage * msg )
{
    #define umlrtparam_p ( *(const Parcel * )msg->getParam( 0 ) )
    #define rtdata ( (const Parcel * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouter/model.uml RootElement::Chute::OCCUPIED entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_p
}

void Capsule_Chute::exitaction_____IDLE( const UMLRTMessage * msg )
{
    #define umlrtparam_p ( *(const Parcel * )msg->getParam( 0 ) )
    #define rtdata ( (const Parcel * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouter/model.uml RootElement::Chute::IDLE exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_p
}

void Capsule_Chute::exitaction_____OCCUPIED( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouter/model.uml RootElement::Chute::OCCUPIED exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____TransitionAction2( const UMLRTMessage * msg )
{
    #define umlrtparam_free ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouter/model.uml RootElement::Chute transition IDLE,IDLE,setFree:exit */
    this->successorFree = umlrtparam_free;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_free
}

void Capsule_Chute::transitionaction_____TransitionAction4( const UMLRTMessage * msg )
{
    #define umlrtparam_free ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouter/model.uml RootElement::Chute transition OCCUPIED,OCCUPIED,setFree:exit */
    this->successorFree = umlrtparam_free;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_free
}

void Capsule_Chute::transitionaction_____TransitionAction5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouter/model.uml RootElement::Chute transition jam ?,IDLE */
    detection.detect(this->parcel).send();
    exit.transmit(this->parcel).send();
    this->successorFree = false;
    log.show("Chute %s of stage %d is now free\n", this->getName(), this->parcel.stage);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____TransitionAction6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouter/model.uml RootElement::Chute transition jam ?,OCCUPIED */
    log.show("JAM detected in %s of stage %d\n", this->getName(), this->parcel.level-1);
    timer.informIn(UMLRTTimespec(this->delay,0));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____reception( const UMLRTMessage * msg )
{
    #define umlrtparam_p ( *(const Parcel * )msg->getParam( 0 ) )
    #define rtdata ( (const Parcel * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouter/model.uml RootElement::Chute transition IDLE,OCCUPIED,transmit:enter */
    this->parcel = Parcel();
    this->parcel.number = umlrtparam_p.number;
    this->parcel.level = umlrtparam_p.level;
    this->parcel.stage = umlrtparam_p.stage;
    log.show("Chute %s of stage %d becomes occupied\n", this->getName(), umlrtparam_p.stage);
    timer.informIn(UMLRTTimespec(this->delay,0));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_p
}

bool Capsule_Chute::action_____TransitionAction5__null( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouter/model.uml RootElement::Chute guard jam ?,IDLE */
    return this->successorFree;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Chute::action_____TransitionAction6__null( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouter/model.uml RootElement::Chute guard jam ?,OCCUPIED */
    return !this->successorFree;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::actionchain_____Initial( const UMLRTMessage * msg )
{
    entryaction_____IDLE( msg );
}

void Capsule_Chute::actionchain_____TransitionAction2( const UMLRTMessage * msg )
{
    exitaction_____IDLE( msg );
    transitionaction_____TransitionAction2( msg );
    entryaction_____IDLE( msg );
}

void Capsule_Chute::actionchain_____TransitionAction4( const UMLRTMessage * msg )
{
    exitaction_____OCCUPIED( msg );
    transitionaction_____TransitionAction4( msg );
    entryaction_____OCCUPIED( msg );
}

void Capsule_Chute::actionchain_____TransitionAction5( const UMLRTMessage * msg )
{
    transitionaction_____TransitionAction5( msg );
    entryaction_____IDLE( msg );
}

void Capsule_Chute::actionchain_____TransitionAction6( const UMLRTMessage * msg )
{
    transitionaction_____TransitionAction6( msg );
    entryaction_____OCCUPIED( msg );
}

void Capsule_Chute::actionchain_____reception( const UMLRTMessage * msg )
{
    exitaction_____IDLE( msg );
    transitionaction_____reception( msg );
    entryaction_____OCCUPIED( msg );
}

void Capsule_Chute::actionchain_____transmission( const UMLRTMessage * msg )
{
    exitaction_____OCCUPIED( msg );
}

Capsule_Chute::State Capsule_Chute::choice_____jam__( const UMLRTMessage * msg )
{
    if( action_____TransitionAction5__null( msg ) )
    {
        actionchain_____TransitionAction5( msg );
        return IDLE;
    }
    else if( action_____TransitionAction6__null( msg ) )
    {
        actionchain_____TransitionAction6( msg );
        return OCCUPIED;
    }
    return currentState;
}

Capsule_Chute::State Capsule_Chute::state_____IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
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
    case port_exit:
        switch( msg->getSignalId() )
        {
        case transmission::signal_setFree:
            actionchain_____TransitionAction2( msg );
            return IDLE;
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

Capsule_Chute::State Capsule_Chute::state_____OCCUPIED( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____transmission( msg );
            return choice_____jam__( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_exit:
        switch( msg->getSignalId() )
        {
        case transmission::signal_setFree:
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
        Capsule_Chute::port_enter,
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
        Capsule_Chute::port_detection,
        "detection",
        "detection",
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
        Capsule_Chute::port_exit,
        "transmission",
        "exit",
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
        Capsule_Chute::port_timer,
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
        Capsule_Chute::port_log,
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

static void instantiate_Chute( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_Chute( &Chute, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Chute = 
{
    "Chute",
    NULL,
    instantiate_Chute,
    0,
    NULL,
    5,
    portroles_border,
    0,
    NULL
};

