
#include "EngineController.hh"

#include "Engine.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include "umlrttimerprotocol.hh"
#include <cstddef>
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

#include "GPIOClass.hh"

Capsule_EngineController::Capsule_EngineController( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, engine( borderPorts[borderport_engine] )
, timer( borderPorts[borderport_timer] )
, leftMotorForward( GPIOClass("22") )
, rightMotorForward( GPIOClass("6") )
, rightMotorBackwards( GPIOClass("5") )
, leftMotorBackwards( GPIOClass("27") )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    leftMotorForward = ( GPIOClass("22") );
    rightMotorForward = ( GPIOClass("6") );
    rightMotorBackwards = ( GPIOClass("5") );
    leftMotorBackwards = ( GPIOClass("27") );
    stateNames[IDLE] = "IDLE";
    stateNames[MOVING_BACKWARDS] = "MOVING_BACKWARDS";
    stateNames[MOVING_FORWARD] = "MOVING_FORWARD";
    stateNames[TURNING_LEFT] = "TURNING_LEFT";
    stateNames[TURNING_RIGHT] = "TURNING_RIGHT";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}







void Capsule_EngineController::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_engine:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_engine, index, true );
            break;
        case borderport_log:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_log, index, true );
            break;
        case borderport_timer:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_timer, index, true );
            break;
        }
}

void Capsule_EngineController::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_engine:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_engine, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_engine], index );
            break;
        case borderport_log:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_log, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_log], index );
            break;
        case borderport_timer:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_timer, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_timer], index );
            break;
        }
}






void Capsule_EngineController::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case IDLE:
        currentState = state_____IDLE( &message );
        break;
    case MOVING_BACKWARDS:
        currentState = state_____MOVING_BACKWARDS( &message );
        break;
    case MOVING_FORWARD:
        currentState = state_____MOVING_FORWARD( &message );
        break;
    case TURNING_RIGHT:
        currentState = state_____TURNING_RIGHT( &message );
        break;
    case TURNING_LEFT:
        currentState = state_____TURNING_LEFT( &message );
        break;
    default:
        break;
    }
}

void Capsule_EngineController::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____init( &message );
    currentState = IDLE;
}

const char * Capsule_EngineController::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_EngineController::entryaction_____IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::EngineController::IDLE entry  */
    log.log("Engine is idle");
    leftMotorForward.setval_gpio("0");
    leftMotorBackwards.setval_gpio("0");
    rightMotorForward.setval_gpio("0");
    rightMotorBackwards.setval_gpio("0");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::EngineController::MOVING_BACKWARDS entry  */
    log.log("Engine is moving backwards");
    leftMotorBackwards.setval_gpio("1");
    rightMotorBackwards.setval_gpio("1");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::EngineController::MOVING_FORWARD entry  */
    log.log("Engine is moving forward");
    leftMotorForward.setval_gpio("1");
    rightMotorForward.setval_gpio("1");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____TURNING_LEFT( const UMLRTMessage * msg )
{
    #define umlrtparam_angle ( *(int *)msg->getParam( 0 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::EngineController::TURNING_LEFT entry  */
    log.log("Engine is turning left");
    leftMotorBackwards.setval_gpio("1");
    rightMotorForward.setval_gpio("1");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_angle
}

void Capsule_EngineController::entryaction_____TURNING_RIGHT( const UMLRTMessage * msg )
{
    #define umlrtparam_angle ( *(int *)msg->getParam( 0 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::EngineController::TURNING_RIGHT entry  */
    log.log("Engine is turning right");
    leftMotorForward.setval_gpio("1");
    rightMotorBackwards.setval_gpio("1");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_angle
}

void Capsule_EngineController::exitaction_____IDLE( const UMLRTMessage * msg )
{
    #define umlrtparam_angle ( *(int *)msg->getParam( 0 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::EngineController::IDLE exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_angle
}

void Capsule_EngineController::exitaction_____MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::EngineController::MOVING_BACKWARDS exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::EngineController::MOVING_FORWARD exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____TURNING_LEFT( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::EngineController::TURNING_LEFT exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____TURNING_RIGHT( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::EngineController::TURNING_RIGHT exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::EngineController transition initial,IDLE */
    // exporting GPIOs
    leftMotorForward.export_gpio();
    leftMotorBackwards.export_gpio();
    rightMotorForward.export_gpio();
    rightMotorBackwards.export_gpio();
    // setting the mode for each GPIO
    leftMotorForward.setdir_gpio("out");
    leftMotorBackwards.setdir_gpio("out");
    rightMotorForward.setdir_gpio("out");
    rightMotorBackwards.setdir_gpio("out");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____stop_moving_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::EngineController transition MOVING_BACKWARDS,IDLE,stop:engine */
    engine.stopped().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____stop_moving_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::EngineController transition MOVING_FORWARD,IDLE,stop:engine */
    engine.stopped().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____stop_turning_left( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::EngineController transition TURNING_LEFT,IDLE,timeout:timer */
    engine.turnedRight().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____stop_turning_right( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::EngineController transition TURNING_RIGHT,IDLE,timeout:timer */
    engine.turnedRight().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____turn_left( const UMLRTMessage * msg )
{
    #define umlrtparam_angle ( *(int *)msg->getParam( 0 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::EngineController transition IDLE,TURNING_LEFT,turnLeft:engine */
    timerId = timer.informIn(UMLRTTimespec(0, (umlrtparam_angle / 360) * 1000000000));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_angle
}

void Capsule_EngineController::transitionaction_____turn_right( const UMLRTMessage * msg )
{
    #define umlrtparam_angle ( *(int *)msg->getParam( 0 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::EngineController transition IDLE,TURNING_RIGHT,turnRight:engine */
    timerId = timer.informIn(UMLRTTimespec(0, (umlrtparam_angle / 360) * 1000000000));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_angle
}

void Capsule_EngineController::actionchain_____init( const UMLRTMessage * msg )
{
    transitionaction_____init( msg );
    entryaction_____IDLE( msg );
}

void Capsule_EngineController::actionchain_____move_backwards( const UMLRTMessage * msg )
{
    exitaction_____IDLE( msg );
    entryaction_____MOVING_BACKWARDS( msg );
}

void Capsule_EngineController::actionchain_____move_forward( const UMLRTMessage * msg )
{
    exitaction_____IDLE( msg );
    entryaction_____MOVING_FORWARD( msg );
}

void Capsule_EngineController::actionchain_____stop_moving_backwards( const UMLRTMessage * msg )
{
    exitaction_____MOVING_BACKWARDS( msg );
    transitionaction_____stop_moving_backwards( msg );
    entryaction_____IDLE( msg );
}

void Capsule_EngineController::actionchain_____stop_moving_forward( const UMLRTMessage * msg )
{
    exitaction_____MOVING_FORWARD( msg );
    transitionaction_____stop_moving_forward( msg );
    entryaction_____IDLE( msg );
}

void Capsule_EngineController::actionchain_____stop_turning_left( const UMLRTMessage * msg )
{
    exitaction_____TURNING_LEFT( msg );
    transitionaction_____stop_turning_left( msg );
    entryaction_____IDLE( msg );
}

void Capsule_EngineController::actionchain_____stop_turning_right( const UMLRTMessage * msg )
{
    exitaction_____TURNING_RIGHT( msg );
    transitionaction_____stop_turning_right( msg );
    entryaction_____IDLE( msg );
}

void Capsule_EngineController::actionchain_____turn_left( const UMLRTMessage * msg )
{
    exitaction_____IDLE( msg );
    transitionaction_____turn_left( msg );
    entryaction_____TURNING_LEFT( msg );
}

void Capsule_EngineController::actionchain_____turn_right( const UMLRTMessage * msg )
{
    exitaction_____IDLE( msg );
    transitionaction_____turn_right( msg );
    entryaction_____TURNING_RIGHT( msg );
}

Capsule_EngineController::State Capsule_EngineController::state_____IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_engine:
        switch( msg->getSignalId() )
        {
        case Engine::signal_turnRight:
            actionchain_____turn_right( msg );
            return TURNING_RIGHT;
        case Engine::signal_moveBackwards:
            actionchain_____move_backwards( msg );
            return MOVING_BACKWARDS;
        case Engine::signal_turnLeft:
            actionchain_____turn_left( msg );
            return TURNING_LEFT;
        case Engine::signal_moveForward:
            actionchain_____move_forward( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_engine:
        switch( msg->getSignalId() )
        {
        case Engine::signal_stop:
            actionchain_____stop_moving_backwards( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____MOVING_FORWARD( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_engine:
        switch( msg->getSignalId() )
        {
        case Engine::signal_stop:
            actionchain_____stop_moving_forward( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____TURNING_LEFT( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____stop_turning_left( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____TURNING_RIGHT( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____stop_turning_right( msg );
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


static const UMLRTCommsPortRole portroles_border[] = 
{
    {
        Capsule_EngineController::port_engine,
        "Engine",
        "engine",
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
        Capsule_EngineController::port_timer,
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
        Capsule_EngineController::port_log,
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

static void instantiate_EngineController( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_EngineController( &EngineController, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass EngineController = 
{
    "EngineController",
    NULL,
    instantiate_EngineController,
    0,
    NULL,
    3,
    portroles_border,
    0,
    NULL
};

