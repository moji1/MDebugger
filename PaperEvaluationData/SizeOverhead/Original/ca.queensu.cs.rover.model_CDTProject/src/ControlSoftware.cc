
#include "ControlSoftware.hh"

#include "Detection.hh"
#include "Engine.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include "umlrttimerprotocol.hh"
#include <cstddef>
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_ControlSoftware::Capsule_ControlSoftware( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, detection( borderPorts[borderport_detection] )
, engine( borderPorts[borderport_engine] )
, temperature( borderPorts[borderport_temperature] )
, timer( borderPorts[borderport_timer] )
, threshold( 30.0 )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[MOVING_BACKWARDS] = "MOVING_BACKWARDS";
    stateNames[MOVING_FORWARD] = "MOVING_FORWARD";
    stateNames[ROTATING] = "ROTATING";
    stateNames[STANDBY] = "STANDBY";
    stateNames[STOPPING_MOVING_BACKWARDS] = "STOPPING_MOVING_BACKWARDS";
    stateNames[STOPPING_MOVING_FORWARD] = "STOPPING_MOVING_FORWARD";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}









void Capsule_ControlSoftware::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_detection:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_detection, index, true );
            break;
        case borderport_engine:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_engine, index, true );
            break;
        case borderport_log:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_log, index, true );
            break;
        case borderport_temperature:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_temperature, index, true );
            break;
        case borderport_timer:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_timer, index, true );
            break;
        }
}

void Capsule_ControlSoftware::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_detection:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_detection, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_detection], index );
            break;
        case borderport_engine:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_engine, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_engine], index );
            break;
        case borderport_log:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_log, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_log], index );
            break;
        case borderport_temperature:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_temperature, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_temperature], index );
            break;
        case borderport_timer:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_timer, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_timer], index );
            break;
        }
}


void Capsule_ControlSoftware::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case MOVING_FORWARD:
        currentState = state_____MOVING_FORWARD( &message );
        break;
    case STANDBY:
        currentState = state_____STANDBY( &message );
        break;
    case STOPPING_MOVING_FORWARD:
        currentState = state_____STOPPING_MOVING_FORWARD( &message );
        break;
    case MOVING_BACKWARDS:
        currentState = state_____MOVING_BACKWARDS( &message );
        break;
    case ROTATING:
        currentState = state_____ROTATING( &message );
        break;
    case STOPPING_MOVING_BACKWARDS:
        currentState = state_____STOPPING_MOVING_BACKWARDS( &message );
        break;
    default:
        break;
    }
}

void Capsule_ControlSoftware::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____init( &message );
    currentState = STANDBY;
}

const char * Capsule_ControlSoftware::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_ControlSoftware::entryaction_____MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::ControlSoftware::MOVING_BACKWARDS entry  */
    log.log("moving bacwards");
    engine.moveBackwards().send();
    timer.informIn(UMLRTTimespec(1,0));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::ControlSoftware::MOVING_FORWARD entry  */
    log.log ("moving forward");
    engine.moveForward().send();
    detection.startDetection().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____ROTATING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::ControlSoftware::ROTATING entry  */
    log.log("rotating");
    engine.turnRight(138).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____STANDBY( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::ControlSoftware::STANDBY entry  */
    timer.informIn(UMLRTTimespec(4,0));
    log.log ("ControlSoftware standing by");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::ControlSoftware::STOPPING_MOVING_BACKWARDS entry  */
    log.log("stopping moving backwards");
    engine.stop().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____STOPPING_MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define umlrtparam_distance ( *(double *)msg->getParam( 0 ) )
    #define rtdata ( (double *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::ControlSoftware::STOPPING_MOVING_FORWARD entry  */
    log.log("Stopping moving forwards");
    engine.stop().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_distance
}

void Capsule_ControlSoftware::exitaction_____MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::ControlSoftware::MOVING_BACKWARDS exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define umlrtparam_distance ( *(double *)msg->getParam( 0 ) )
    #define rtdata ( (double *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::ControlSoftware::MOVING_FORWARD exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_distance
}

void Capsule_ControlSoftware::exitaction_____ROTATING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::ControlSoftware::ROTATING exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____STANDBY( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::ControlSoftware::STANDBY exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::ControlSoftware::STOPPING_MOVING_BACKWARDS exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____STOPPING_MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::ControlSoftware::STOPPING_MOVING_FORWARD exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____greaterThan( const UMLRTMessage * msg )
{
    #define umlrtparam_distance ( *(double *)msg->getParam( 0 ) )
    #define rtdata ( (double *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::ControlSoftware transition MOVING_FORWARD,MOVING_FORWARD,obstacleDetected:detection */
    log.log ("distance greater than threshold: %f > %f", umlrtparam_distance, threshold);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_distance
}

void Capsule_ControlSoftware::transitionaction_____lowerThanThreshold( const UMLRTMessage * msg )
{
    #define umlrtparam_distance ( *(double *)msg->getParam( 0 ) )
    #define rtdata ( (double *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::ControlSoftware transition MOVING_FORWARD,STOPPING_MOVING_FORWARD,obstacleDetected:detection */
    log.log ("distance less than threshold: %f < %f", umlrtparam_distance, threshold);
    detection.stopDetection().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_distance
}

bool Capsule_ControlSoftware::action_____greaterThan__greaterThanThreshold( const UMLRTMessage * msg )
{
    #define umlrtparam_distance ( *(double *)msg->getParam( 0 ) )
    #define rtdata ( (double *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::ControlSoftware guard MOVING_FORWARD,MOVING_FORWARD,obstacleDetected:detection */
    return (umlrtparam_distance > threshold) || (umlrtparam_distance < 0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_distance
}

bool Capsule_ControlSoftware::action_____lowerThanThreshold__lessThanThreshold( const UMLRTMessage * msg )
{
    #define umlrtparam_distance ( *(double *)msg->getParam( 0 ) )
    #define rtdata ( (double *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::ControlSoftware guard MOVING_FORWARD,STOPPING_MOVING_FORWARD,obstacleDetected:detection */
    return (umlrtparam_distance < threshold) && (umlrtparam_distance >= 0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_distance
}

void Capsule_ControlSoftware::actionchain_____greaterThan( const UMLRTMessage * msg )
{
    transitionaction_____greaterThan( msg );
}

void Capsule_ControlSoftware::actionchain_____init( const UMLRTMessage * msg )
{
    entryaction_____STANDBY( msg );
}

void Capsule_ControlSoftware::actionchain_____lowerThanThreshold( const UMLRTMessage * msg )
{
    exitaction_____MOVING_FORWARD( msg );
    transitionaction_____lowerThanThreshold( msg );
    entryaction_____STOPPING_MOVING_FORWARD( msg );
}

void Capsule_ControlSoftware::actionchain_____moving_forward( const UMLRTMessage * msg )
{
    exitaction_____STANDBY( msg );
    entryaction_____MOVING_FORWARD( msg );
}

void Capsule_ControlSoftware::actionchain_____stopped( const UMLRTMessage * msg )
{
    exitaction_____STOPPING_MOVING_FORWARD( msg );
    entryaction_____MOVING_BACKWARDS( msg );
}

void Capsule_ControlSoftware::actionchain_____stopped_moving_backwards( const UMLRTMessage * msg )
{
    exitaction_____STOPPING_MOVING_BACKWARDS( msg );
    entryaction_____ROTATING( msg );
}

void Capsule_ControlSoftware::actionchain_____timeout( const UMLRTMessage * msg )
{
    exitaction_____MOVING_BACKWARDS( msg );
    entryaction_____STOPPING_MOVING_BACKWARDS( msg );
}

void Capsule_ControlSoftware::actionchain_____turnedRight( const UMLRTMessage * msg )
{
    exitaction_____ROTATING( msg );
    entryaction_____MOVING_FORWARD( msg );
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____timeout( msg );
            return STOPPING_MOVING_BACKWARDS;
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____MOVING_FORWARD( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_detection:
        switch( msg->getSignalId() )
        {
        case Detection::signal_obstacleDetected:
            if( action_____lowerThanThreshold__lessThanThreshold( msg ) )
            {
                actionchain_____lowerThanThreshold( msg );
                return STOPPING_MOVING_FORWARD;
            }
            else if( action_____greaterThan__greaterThanThreshold( msg ) )
            {
                actionchain_____greaterThan( msg );
                return MOVING_FORWARD;
            }
            return currentState;
            if( action_____lowerThanThreshold__lessThanThreshold( msg ) )
            {
                actionchain_____lowerThanThreshold( msg );
                return STOPPING_MOVING_FORWARD;
            }
            else if( action_____greaterThan__greaterThanThreshold( msg ) )
            {
                actionchain_____greaterThan( msg );
                return MOVING_FORWARD;
            }
            return currentState;
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____ROTATING( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_engine:
        switch( msg->getSignalId() )
        {
        case Engine::signal_turnedRight:
            actionchain_____turnedRight( msg );
            return MOVING_FORWARD;
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____STANDBY( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____moving_forward( msg );
            return MOVING_FORWARD;
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_engine:
        switch( msg->getSignalId() )
        {
        case Engine::signal_stopped:
            actionchain_____stopped_moving_backwards( msg );
            return ROTATING;
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____STOPPING_MOVING_FORWARD( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_engine:
        switch( msg->getSignalId() )
        {
        case Engine::signal_stopped:
            actionchain_____stopped( msg );
            return MOVING_BACKWARDS;
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
        Capsule_ControlSoftware::port_detection,
        "Detection",
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
        Capsule_ControlSoftware::port_engine,
        "Engine",
        "engine",
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
        Capsule_ControlSoftware::port_temperature,
        "Temperature",
        "temperature",
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
        Capsule_ControlSoftware::port_timer,
        "Timing",
        "timer",
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
        Capsule_ControlSoftware::port_log,
        "Log",
        "log",
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

static void instantiate_ControlSoftware( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_ControlSoftware( &ControlSoftware, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass ControlSoftware = 
{
    "ControlSoftware",
    NULL,
    instantiate_ControlSoftware,
    0,
    NULL,
    5,
    portroles_border,
    0,
    NULL
};

