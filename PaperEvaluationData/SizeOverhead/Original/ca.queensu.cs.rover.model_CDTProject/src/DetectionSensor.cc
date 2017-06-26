
#include "DetectionSensor.hh"

#include "Detection.hh"
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

Capsule_DetectionSensor::Capsule_DetectionSensor( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, detection( borderPorts[borderport_detection] )
, timer( borderPorts[borderport_timer] )
, pinTrig( GPIOClass("23") )
, pinEcho( GPIOClass("24") )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    pinTrig = ( GPIOClass("23") );
    pinEcho = ( GPIOClass("24") );
    stateNames[DETECTING] = "DETECTING";
    stateNames[IDLE] = "IDLE";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}







void Capsule_DetectionSensor::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_detection:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_detection, index, true );
            break;
        case borderport_log:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_log, index, true );
            break;
        case borderport_timer:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_timer, index, true );
            break;
        }
}

void Capsule_DetectionSensor::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_detection:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_detection, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_detection], index );
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




void Capsule_DetectionSensor::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case IDLE:
        currentState = state_____IDLE( &message );
        break;
    case DETECTING:
        currentState = state_____DETECTING( &message );
        break;
    default:
        break;
    }
}

void Capsule_DetectionSensor::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____init( &message );
    currentState = IDLE;
}

const char * Capsule_DetectionSensor::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_DetectionSensor::entryaction_____DETECTING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::DetectionSensor::DETECTING entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::entryaction_____IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::DetectionSensor::IDLE entry  */
    pinTrig.setval_gpio("0");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::exitaction_____DETECTING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::DetectionSensor::DETECTING exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::exitaction_____IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::DetectionSensor::IDLE exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::DetectionSensor transition DETECTING,DETECTING,timeout:timer */
    pinTrig.setval_gpio("0");
    clock_t pulse_start;
    clock_t pulse_end;
    double pulse_duration;
    while(true) {
    string inputstate;
    pinEcho.getval_gpio(inputstate);
    int value = atoi(inputstate.c_str());
    if (value == 0) {
    pulse_start = clock();
    } else {
    break;
    }
    }
    while(true) {
    string inputstate;
    pinEcho.getval_gpio(inputstate);
    int value = atoi(inputstate.c_str());
    if (value == 1) {
    pulse_end = clock();
    } else {
    break;
    }
    }
    pulse_duration = (pulse_end - pulse_start) / (double)(CLOCKS_PER_SEC);
    // log.log ("pulse duration is %f", pulse_duration);
    double distance = pulse_duration *17150;
    //log.log ("distance is %f", distance);
    detection.obstacleDetected(distance).send();
    pinTrig.setval_gpio("1");
    timerId = timer.informIn(UMLRTTimespec(0,10000));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::DetectionSensor transition initial,IDLE */
    pinTrig.export_gpio();
    pinEcho.export_gpio();
    pinTrig.setdir_gpio("out");
    pinEcho.setdir_gpio("in");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____start_detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::DetectionSensor transition IDLE,DETECTING,startDetection:detection */
    pinTrig.setval_gpio("1");
    timerId = timer.informIn(UMLRTTimespec(0,10000));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____stop_detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ca.queensu.cs.rover.model/rover.uml rover::UMLRT-Rover::DetectionSensor transition DETECTING,IDLE,stopDetection:detection */
    timer.cancelTimer(timerId);
    log.log("stop detecting");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::actionchain_____detecting( const UMLRTMessage * msg )
{
    transitionaction_____detecting( msg );
}

void Capsule_DetectionSensor::actionchain_____init( const UMLRTMessage * msg )
{
    transitionaction_____init( msg );
    entryaction_____IDLE( msg );
}

void Capsule_DetectionSensor::actionchain_____start_detecting( const UMLRTMessage * msg )
{
    exitaction_____IDLE( msg );
    transitionaction_____start_detecting( msg );
    entryaction_____DETECTING( msg );
}

void Capsule_DetectionSensor::actionchain_____stop_detecting( const UMLRTMessage * msg )
{
    exitaction_____DETECTING( msg );
    transitionaction_____stop_detecting( msg );
    entryaction_____IDLE( msg );
}

Capsule_DetectionSensor::State Capsule_DetectionSensor::state_____DETECTING( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_detection:
        switch( msg->getSignalId() )
        {
        case Detection::signal_stopDetection:
            actionchain_____stop_detecting( msg );
            return IDLE;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____detecting( msg );
            return DETECTING;
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

Capsule_DetectionSensor::State Capsule_DetectionSensor::state_____IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_detection:
        switch( msg->getSignalId() )
        {
        case Detection::signal_startDetection:
            actionchain_____start_detecting( msg );
            return DETECTING;
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
        Capsule_DetectionSensor::port_detection,
        "Detection",
        "detection",
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
        Capsule_DetectionSensor::port_timer,
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
        Capsule_DetectionSensor::port_log,
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

static void instantiate_DetectionSensor( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_DetectionSensor( &DetectionSensor, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass DetectionSensor = 
{
    "DetectionSensor",
    NULL,
    instantiate_DetectionSensor,
    0,
    NULL,
    3,
    portroles_border,
    0,
    NULL
};

