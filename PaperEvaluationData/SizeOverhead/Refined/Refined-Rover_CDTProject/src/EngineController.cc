
#include "EngineController.hh"

#include "Engine.hh"
#include "ExtInterface.hh"
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
, extComm( borderPorts[borderport_extComm] )
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
    stateNames[Debug__C__init] = "Debug__C__init";
    stateNames[Debug__C__move_backwards] = "Debug__C__move_backwards";
    stateNames[Debug__C__move_forward] = "Debug__C__move_forward";
    stateNames[Debug__C__stop_moving_backwards] = "Debug__C__stop_moving_backwards";
    stateNames[Debug__C__stop_moving_forward] = "Debug__C__stop_moving_forward";
    stateNames[Debug__C__stop_turning_left] = "Debug__C__stop_turning_left";
    stateNames[Debug__C__stop_turning_right] = "Debug__C__stop_turning_right";
    stateNames[Debug__C__turn_left] = "Debug__C__turn_left";
    stateNames[Debug__C__turn_right] = "Debug__C__turn_right";
    stateNames[Debug__C__init__Debug__A__Ac__init] = "Debug__C__init__Debug__A__Ac__init";
    stateNames[Debug__C__init__Debug__A__En__init] = "Debug__C__init__Debug__A__En__init";
    stateNames[Debug__C__init__Debug__B__Ac__init] = "Debug__C__init__Debug__B__Ac__init";
    stateNames[Debug__C__init__boundary] = "Debug__C__init__boundary";
    stateNames[Debug__C__move_backwards__Debug__A__Ac__move_backwards] = "Debug__C__move_backwards__Debug__A__Ac__move_backwards";
    stateNames[Debug__C__move_backwards__Debug__A__En__MOVING_BACKWARDS] = "Debug__C__move_backwards__Debug__A__En__MOVING_BACKWARDS";
    stateNames[Debug__C__move_backwards__Debug__B__Ac__move_backwards] = "Debug__C__move_backwards__Debug__B__Ac__move_backwards";
    stateNames[Debug__C__move_backwards__Debug__B__Ex__IDLE] = "Debug__C__move_backwards__Debug__B__Ex__IDLE";
    stateNames[Debug__C__move_backwards__boundary] = "Debug__C__move_backwards__boundary";
    stateNames[Debug__C__move_forward__Debug__A__Ac__move_forward] = "Debug__C__move_forward__Debug__A__Ac__move_forward";
    stateNames[Debug__C__move_forward__Debug__A__En__MOVING_FORWARD] = "Debug__C__move_forward__Debug__A__En__MOVING_FORWARD";
    stateNames[Debug__C__move_forward__Debug__B__Ac__move_forward] = "Debug__C__move_forward__Debug__B__Ac__move_forward";
    stateNames[Debug__C__move_forward__Debug__B__Ex__IDLE] = "Debug__C__move_forward__Debug__B__Ex__IDLE";
    stateNames[Debug__C__move_forward__boundary] = "Debug__C__move_forward__boundary";
    stateNames[Debug__C__stop_moving_backwards__Debug__A__Ac__stop_moving_backwards] = "Debug__C__stop_moving_backwards__Debug__A__Ac__stop_moving_backwards";
    stateNames[Debug__C__stop_moving_backwards__Debug__A__En__IDLE] = "Debug__C__stop_moving_backwards__Debug__A__En__IDLE";
    stateNames[Debug__C__stop_moving_backwards__Debug__B__Ac__stop_moving_backwards] = "Debug__C__stop_moving_backwards__Debug__B__Ac__stop_moving_backwards";
    stateNames[Debug__C__stop_moving_backwards__Debug__B__Ex__MOVING_BACKWARDS] = "Debug__C__stop_moving_backwards__Debug__B__Ex__MOVING_BACKWARDS";
    stateNames[Debug__C__stop_moving_backwards__boundary] = "Debug__C__stop_moving_backwards__boundary";
    stateNames[Debug__C__stop_moving_forward__Debug__A__Ac__stop_moving_forward] = "Debug__C__stop_moving_forward__Debug__A__Ac__stop_moving_forward";
    stateNames[Debug__C__stop_moving_forward__Debug__A__En__IDLE] = "Debug__C__stop_moving_forward__Debug__A__En__IDLE";
    stateNames[Debug__C__stop_moving_forward__Debug__B__Ac__stop_moving_forward] = "Debug__C__stop_moving_forward__Debug__B__Ac__stop_moving_forward";
    stateNames[Debug__C__stop_moving_forward__Debug__B__Ex__MOVING_FORWARD] = "Debug__C__stop_moving_forward__Debug__B__Ex__MOVING_FORWARD";
    stateNames[Debug__C__stop_moving_forward__boundary] = "Debug__C__stop_moving_forward__boundary";
    stateNames[Debug__C__stop_turning_left__Debug__A__Ac__stop_turning_left] = "Debug__C__stop_turning_left__Debug__A__Ac__stop_turning_left";
    stateNames[Debug__C__stop_turning_left__Debug__A__En__IDLE] = "Debug__C__stop_turning_left__Debug__A__En__IDLE";
    stateNames[Debug__C__stop_turning_left__Debug__B__Ac__stop_turning_left] = "Debug__C__stop_turning_left__Debug__B__Ac__stop_turning_left";
    stateNames[Debug__C__stop_turning_left__Debug__B__Ex__TURNING_LEFT] = "Debug__C__stop_turning_left__Debug__B__Ex__TURNING_LEFT";
    stateNames[Debug__C__stop_turning_left__boundary] = "Debug__C__stop_turning_left__boundary";
    stateNames[Debug__C__stop_turning_right__Debug__A__Ac__stop_turning_right] = "Debug__C__stop_turning_right__Debug__A__Ac__stop_turning_right";
    stateNames[Debug__C__stop_turning_right__Debug__A__En__IDLE] = "Debug__C__stop_turning_right__Debug__A__En__IDLE";
    stateNames[Debug__C__stop_turning_right__Debug__B__Ac__stop_turning_right] = "Debug__C__stop_turning_right__Debug__B__Ac__stop_turning_right";
    stateNames[Debug__C__stop_turning_right__Debug__B__Ex__TURNING_RIGHT] = "Debug__C__stop_turning_right__Debug__B__Ex__TURNING_RIGHT";
    stateNames[Debug__C__stop_turning_right__boundary] = "Debug__C__stop_turning_right__boundary";
    stateNames[Debug__C__turn_left__Debug__A__Ac__turn_left] = "Debug__C__turn_left__Debug__A__Ac__turn_left";
    stateNames[Debug__C__turn_left__Debug__A__En__TURNING_LEFT] = "Debug__C__turn_left__Debug__A__En__TURNING_LEFT";
    stateNames[Debug__C__turn_left__Debug__B__Ac__turn_left] = "Debug__C__turn_left__Debug__B__Ac__turn_left";
    stateNames[Debug__C__turn_left__Debug__B__Ex__IDLE] = "Debug__C__turn_left__Debug__B__Ex__IDLE";
    stateNames[Debug__C__turn_left__boundary] = "Debug__C__turn_left__boundary";
    stateNames[Debug__C__turn_right__Debug__A__Ac__turn_right] = "Debug__C__turn_right__Debug__A__Ac__turn_right";
    stateNames[Debug__C__turn_right__Debug__A__En__TURNING_RIGHT] = "Debug__C__turn_right__Debug__A__En__TURNING_RIGHT";
    stateNames[Debug__C__turn_right__Debug__B__Ac__turn_right] = "Debug__C__turn_right__Debug__B__Ac__turn_right";
    stateNames[Debug__C__turn_right__Debug__B__Ex__IDLE] = "Debug__C__turn_right__Debug__B__Ex__IDLE";
    stateNames[Debug__C__turn_right__boundary] = "Debug__C__turn_right__boundary";
    stateNames[Debug__InitState] = "Debug__InitState";
    stateNames[IDLE] = "IDLE";
    stateNames[MOVING_BACKWARDS] = "MOVING_BACKWARDS";
    stateNames[MOVING_FORWARD] = "MOVING_FORWARD";
    stateNames[TURNING_LEFT] = "TURNING_LEFT";
    stateNames[TURNING_RIGHT] = "TURNING_RIGHT";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
    int i = 0;
    while( i < 9 )
        history[i++] = SPECIAL_INTERNAL_STATE_UNVISITED;
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










void Capsule_EngineController::Debug__variablesView()
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::EngineController operation Debug__variablesView */
    std::string tempS="";
    if (Debug__variablesData==NULL)
    Debug__variablesData=(char *)malloc(strlen(tempS.c_str())+1);
    else if (strlen(Debug__variablesData)<strlen(tempS.c_str()))
    Debug__variablesData=(char *) realloc(Debug__variablesData,strlen(tempS.c_str())+1);
    strcpy(Debug__variablesData,tempS.c_str());
    /* UMLRTGEN-USERREGION-END */
}

bool Capsule_EngineController::Debug__variablesChange( char * varName, char * varValue )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::EngineController operation Debug__variablesChange */
    std::string tempVarName="";
    tempVarName.append(varName);
    return false;
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_EngineController::Debug__sendEvent( debugEvents::EVENTSOURCEKIND eventSourceKind, debugEvents::EVENTTYPE eventType, const char * instanceName, int capsuleIndex, const char * signalName, char * capsuleName, char * sourceName, char * reserve1, char * reserve2, char * reserve3 )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::EngineController operation Debug__sendEvent */
    this->Debug__variablesView();
    this->Debug__event.clearEventPayload();
    this->Debug__event.generateEventID();
    this->Debug__event.setCpuTik();
    this->Debug__event.setTimePointToNow();
    this->Debug__event.setEventSourceKind(eventSourceKind);
    this->Debug__event.setEventType(eventType);
    this->Debug__event.setCapsuleName(capsuleName);
    this->Debug__event.setCapsuleInstance(instanceName);
    this->Debug__event.setCapsuleIndex(capsuleIndex);
    this->Debug__event.setSourceName(sourceName);
    this->Debug__event.setVariableData(this->Debug__variablesData);
    if (eventSourceKind==debugEvents::TRANISTION){
    this->Debug__event.setPayloadField("Source",reserve1);
    this->Debug__event.setPayloadField("Target",reserve2);
    this->Debug__event.setPayloadField("Signal",signalName);
    }
    std::string tempS=this->Debug__event.serialize();
    char eventStr[tempS.length()+1];
    strcpy(eventStr,tempS.c_str());
    extComm.event(eventStr).send();
    /* UMLRTGEN-USERREGION-END */
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
    case Debug__InitState:
        currentState = state_____Debug__InitState( &message );
        break;
    case Debug__C__turn_left__Debug__B__Ex__IDLE:
        currentState = state_____Debug__C__turn_left__Debug__B__Ex__IDLE( &message );
        break;
    case Debug__C__turn_left__Debug__B__Ac__turn_left:
        currentState = state_____Debug__C__turn_left__Debug__B__Ac__turn_left( &message );
        break;
    case Debug__C__turn_left__Debug__A__Ac__turn_left:
        currentState = state_____Debug__C__turn_left__Debug__A__Ac__turn_left( &message );
        break;
    case Debug__C__turn_left__Debug__A__En__TURNING_LEFT:
        currentState = state_____Debug__C__turn_left__Debug__A__En__TURNING_LEFT( &message );
        break;
    case Debug__C__turn_left__boundary:
        currentState = state_____Debug__C__turn_left__boundary( &message );
        break;
    case Debug__C__stop_turning_right__Debug__B__Ex__TURNING_RIGHT:
        currentState = state_____Debug__C__stop_turning_right__Debug__B__Ex__TURNING_RIGHT( &message );
        break;
    case Debug__C__stop_turning_right__Debug__B__Ac__stop_turning_right:
        currentState = state_____Debug__C__stop_turning_right__Debug__B__Ac__stop_turning_right( &message );
        break;
    case Debug__C__stop_turning_right__Debug__A__Ac__stop_turning_right:
        currentState = state_____Debug__C__stop_turning_right__Debug__A__Ac__stop_turning_right( &message );
        break;
    case Debug__C__stop_turning_right__Debug__A__En__IDLE:
        currentState = state_____Debug__C__stop_turning_right__Debug__A__En__IDLE( &message );
        break;
    case Debug__C__stop_turning_right__boundary:
        currentState = state_____Debug__C__stop_turning_right__boundary( &message );
        break;
    case Debug__C__stop_moving_forward__Debug__B__Ex__MOVING_FORWARD:
        currentState = state_____Debug__C__stop_moving_forward__Debug__B__Ex__MOVING_FORWARD( &message );
        break;
    case Debug__C__stop_moving_forward__Debug__B__Ac__stop_moving_forward:
        currentState = state_____Debug__C__stop_moving_forward__Debug__B__Ac__stop_moving_forward( &message );
        break;
    case Debug__C__stop_moving_forward__Debug__A__Ac__stop_moving_forward:
        currentState = state_____Debug__C__stop_moving_forward__Debug__A__Ac__stop_moving_forward( &message );
        break;
    case Debug__C__stop_moving_forward__Debug__A__En__IDLE:
        currentState = state_____Debug__C__stop_moving_forward__Debug__A__En__IDLE( &message );
        break;
    case Debug__C__stop_moving_forward__boundary:
        currentState = state_____Debug__C__stop_moving_forward__boundary( &message );
        break;
    case Debug__C__move_forward__Debug__B__Ex__IDLE:
        currentState = state_____Debug__C__move_forward__Debug__B__Ex__IDLE( &message );
        break;
    case Debug__C__move_forward__Debug__B__Ac__move_forward:
        currentState = state_____Debug__C__move_forward__Debug__B__Ac__move_forward( &message );
        break;
    case Debug__C__move_forward__Debug__A__Ac__move_forward:
        currentState = state_____Debug__C__move_forward__Debug__A__Ac__move_forward( &message );
        break;
    case Debug__C__move_forward__Debug__A__En__MOVING_FORWARD:
        currentState = state_____Debug__C__move_forward__Debug__A__En__MOVING_FORWARD( &message );
        break;
    case Debug__C__move_forward__boundary:
        currentState = state_____Debug__C__move_forward__boundary( &message );
        break;
    case Debug__C__stop_moving_backwards__Debug__B__Ex__MOVING_BACKWARDS:
        currentState = state_____Debug__C__stop_moving_backwards__Debug__B__Ex__MOVING_BACKWARDS( &message );
        break;
    case Debug__C__stop_moving_backwards__Debug__B__Ac__stop_moving_backwards:
        currentState = state_____Debug__C__stop_moving_backwards__Debug__B__Ac__stop_moving_backwards( &message );
        break;
    case Debug__C__stop_moving_backwards__Debug__A__Ac__stop_moving_backwards:
        currentState = state_____Debug__C__stop_moving_backwards__Debug__A__Ac__stop_moving_backwards( &message );
        break;
    case Debug__C__stop_moving_backwards__Debug__A__En__IDLE:
        currentState = state_____Debug__C__stop_moving_backwards__Debug__A__En__IDLE( &message );
        break;
    case Debug__C__stop_moving_backwards__boundary:
        currentState = state_____Debug__C__stop_moving_backwards__boundary( &message );
        break;
    case Debug__C__stop_turning_left__Debug__B__Ex__TURNING_LEFT:
        currentState = state_____Debug__C__stop_turning_left__Debug__B__Ex__TURNING_LEFT( &message );
        break;
    case Debug__C__stop_turning_left__Debug__B__Ac__stop_turning_left:
        currentState = state_____Debug__C__stop_turning_left__Debug__B__Ac__stop_turning_left( &message );
        break;
    case Debug__C__stop_turning_left__Debug__A__Ac__stop_turning_left:
        currentState = state_____Debug__C__stop_turning_left__Debug__A__Ac__stop_turning_left( &message );
        break;
    case Debug__C__stop_turning_left__Debug__A__En__IDLE:
        currentState = state_____Debug__C__stop_turning_left__Debug__A__En__IDLE( &message );
        break;
    case Debug__C__stop_turning_left__boundary:
        currentState = state_____Debug__C__stop_turning_left__boundary( &message );
        break;
    case Debug__C__init__Debug__B__Ac__init:
        currentState = state_____Debug__C__init__Debug__B__Ac__init( &message );
        break;
    case Debug__C__init__Debug__A__Ac__init:
        currentState = state_____Debug__C__init__Debug__A__Ac__init( &message );
        break;
    case Debug__C__init__Debug__A__En__init:
        currentState = state_____Debug__C__init__Debug__A__En__init( &message );
        break;
    case Debug__C__init__boundary:
        currentState = state_____Debug__C__init__boundary( &message );
        break;
    case Debug__C__turn_right__Debug__B__Ex__IDLE:
        currentState = state_____Debug__C__turn_right__Debug__B__Ex__IDLE( &message );
        break;
    case Debug__C__turn_right__Debug__B__Ac__turn_right:
        currentState = state_____Debug__C__turn_right__Debug__B__Ac__turn_right( &message );
        break;
    case Debug__C__turn_right__Debug__A__Ac__turn_right:
        currentState = state_____Debug__C__turn_right__Debug__A__Ac__turn_right( &message );
        break;
    case Debug__C__turn_right__Debug__A__En__TURNING_RIGHT:
        currentState = state_____Debug__C__turn_right__Debug__A__En__TURNING_RIGHT( &message );
        break;
    case Debug__C__turn_right__boundary:
        currentState = state_____Debug__C__turn_right__boundary( &message );
        break;
    case Debug__C__move_backwards__Debug__B__Ex__IDLE:
        currentState = state_____Debug__C__move_backwards__Debug__B__Ex__IDLE( &message );
        break;
    case Debug__C__move_backwards__Debug__B__Ac__move_backwards:
        currentState = state_____Debug__C__move_backwards__Debug__B__Ac__move_backwards( &message );
        break;
    case Debug__C__move_backwards__Debug__A__Ac__move_backwards:
        currentState = state_____Debug__C__move_backwards__Debug__A__Ac__move_backwards( &message );
        break;
    case Debug__C__move_backwards__Debug__A__En__MOVING_BACKWARDS:
        currentState = state_____Debug__C__move_backwards__Debug__A__En__MOVING_BACKWARDS( &message );
        break;
    case Debug__C__move_backwards__boundary:
        currentState = state_____Debug__C__move_backwards__boundary( &message );
        break;
    default:
        break;
    }
}

void Capsule_EngineController::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Debug__InitDebug( &message );
    currentState = Debug__InitState;
}

const char * Capsule_EngineController::getCurrentStateString() const
{
    return stateNames[currentState];
}





void Capsule_EngineController::save_history( Capsule_EngineController::State compositeState, Capsule_EngineController::State subState )
{
    history[compositeState] = subState;
}

bool Capsule_EngineController::check_history( Capsule_EngineController::State compositeState, Capsule_EngineController::State subState )
{
    return history[compositeState] == subState;
}

void Capsule_EngineController::entryaction_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__init::Debug__A__Ac__init entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__init::Region1::Debug__A__Ac__init",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("init","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("IDLE","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__init::Debug__A__En__init entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__init::Region1::Debug__A__En__init",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__init::Debug__B__Ac__init entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__init::Region1::Debug__B__Ac__init",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("init","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__init__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__move_backwards__Debug__A__Ac__move_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move backwards::Debug__A__Ac__move backwards entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move backwards::Region1::Debug__A__Ac__move backwards",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("move backwards","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("MOVING_BACKWARDS","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__move_backwards__Debug__A__En__MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move backwards::Debug__A__En__MOVING_BACKWARDS entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move backwards::Region1::Debug__A__En__MOVING_BACKWARDS",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("MOVING_BACKWARDS","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__move_backwards__Debug__B__Ac__move_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move backwards::Debug__B__Ac__move backwards entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move backwards::Region1::Debug__B__Ac__move backwards",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("move backwards","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__move_backwards__Debug__B__Ex__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move backwards::Debug__B__Ex__IDLE entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move backwards::Region1::Debug__B__Ex__IDLE",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__move_backwards__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__move_forward__Debug__A__Ac__move_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move forward::Debug__A__Ac__move forward entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move forward::Region1::Debug__A__Ac__move forward",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("move forward","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("MOVING_FORWARD","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__move_forward__Debug__A__En__MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move forward::Debug__A__En__MOVING_FORWARD entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move forward::Region1::Debug__A__En__MOVING_FORWARD",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("MOVING_FORWARD","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__move_forward__Debug__B__Ac__move_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move forward::Debug__B__Ac__move forward entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move forward::Region1::Debug__B__Ac__move forward",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("move forward","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__move_forward__Debug__B__Ex__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move forward::Debug__B__Ex__IDLE entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move forward::Region1::Debug__B__Ex__IDLE",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__move_forward__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__stop_moving_backwards__Debug__A__Ac__stop_moving_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving backwards::Debug__A__Ac__stop moving backwards entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving backwards::Region1::Debug__A__Ac__stop moving backwards",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("stop moving backwards","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("IDLE","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__stop_moving_backwards__Debug__A__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving backwards::Debug__A__En__IDLE entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving backwards::Region1::Debug__A__En__IDLE",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__stop_moving_backwards__Debug__B__Ac__stop_moving_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving backwards::Debug__B__Ac__stop moving backwards entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving backwards::Region1::Debug__B__Ac__stop moving backwards",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("MOVING_BACKWARDS","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("stop moving backwards","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__stop_moving_backwards__Debug__B__Ex__MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving backwards::Debug__B__Ex__MOVING_BACKWARDS entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving backwards::Region1::Debug__B__Ex__MOVING_BACKWARDS",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("MOVING_BACKWARDS","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__stop_moving_backwards__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__stop_moving_forward__Debug__A__Ac__stop_moving_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving forward::Debug__A__Ac__stop moving forward entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving forward::Region1::Debug__A__Ac__stop moving forward",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("stop moving forward","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("IDLE","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__stop_moving_forward__Debug__A__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving forward::Debug__A__En__IDLE entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving forward::Region1::Debug__A__En__IDLE",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__stop_moving_forward__Debug__B__Ac__stop_moving_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving forward::Debug__B__Ac__stop moving forward entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving forward::Region1::Debug__B__Ac__stop moving forward",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("MOVING_FORWARD","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("stop moving forward","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__stop_moving_forward__Debug__B__Ex__MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving forward::Debug__B__Ex__MOVING_FORWARD entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving forward::Region1::Debug__B__Ex__MOVING_FORWARD",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("MOVING_FORWARD","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__stop_moving_forward__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__stop_turning_left__Debug__A__Ac__stop_turning_left( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning left::Debug__A__Ac__stop turning left entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning left::Region1::Debug__A__Ac__stop turning left",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("stop turning left","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("IDLE","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__stop_turning_left__Debug__A__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning left::Debug__A__En__IDLE entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning left::Region1::Debug__A__En__IDLE",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__stop_turning_left__Debug__B__Ac__stop_turning_left( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning left::Debug__B__Ac__stop turning left entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning left::Region1::Debug__B__Ac__stop turning left",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("TURNING_LEFT","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("stop turning left","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__stop_turning_left__Debug__B__Ex__TURNING_LEFT( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning left::Debug__B__Ex__TURNING_LEFT entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning left::Region1::Debug__B__Ex__TURNING_LEFT",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("TURNING_LEFT","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__stop_turning_left__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__stop_turning_right__Debug__A__Ac__stop_turning_right( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning right::Debug__A__Ac__stop turning right entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning right::Region1::Debug__A__Ac__stop turning right",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("stop turning right","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("IDLE","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__stop_turning_right__Debug__A__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning right::Debug__A__En__IDLE entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning right::Region1::Debug__A__En__IDLE",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__stop_turning_right__Debug__B__Ac__stop_turning_right( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning right::Debug__B__Ac__stop turning right entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning right::Region1::Debug__B__Ac__stop turning right",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("TURNING_RIGHT","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("stop turning right","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__stop_turning_right__Debug__B__Ex__TURNING_RIGHT( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning right::Debug__B__Ex__TURNING_RIGHT entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning right::Region1::Debug__B__Ex__TURNING_RIGHT",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("TURNING_RIGHT","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__stop_turning_right__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__turn_left__Debug__A__Ac__turn_left( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn left::Debug__A__Ac__turn left entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn left::Region1::Debug__A__Ac__turn left",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("turn left","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("TURNING_LEFT","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__turn_left__Debug__A__En__TURNING_LEFT( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn left::Debug__A__En__TURNING_LEFT entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn left::Region1::Debug__A__En__TURNING_LEFT",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("TURNING_LEFT","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__turn_left__Debug__B__Ac__turn_left( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn left::Debug__B__Ac__turn left entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn left::Region1::Debug__B__Ac__turn left",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("turn left","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__turn_left__Debug__B__Ex__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn left::Debug__B__Ex__IDLE entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn left::Region1::Debug__B__Ex__IDLE",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__turn_left__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__turn_right__Debug__A__Ac__turn_right( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn right::Debug__A__Ac__turn right entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn right::Region1::Debug__A__Ac__turn right",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("turn right","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("TURNING_RIGHT","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__turn_right__Debug__A__En__TURNING_RIGHT( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn right::Debug__A__En__TURNING_RIGHT entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn right::Region1::Debug__A__En__TURNING_RIGHT",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("TURNING_RIGHT","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__turn_right__Debug__B__Ac__turn_right( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn right::Debug__B__Ac__turn right entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn right::Region1::Debug__B__Ac__turn right",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("turn right","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__turn_right__Debug__B__Ex__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn right::Debug__B__Ex__IDLE entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn right::Region1::Debug__B__Ex__IDLE",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__C__turn_right__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_EngineController::entryaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__InitState entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::IDLE entry  */
    if( not Debug__SRO.checkDebug("IDLE",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::IDLE",(char *)"",(char *)"",(char *)"");
    log.log("Engine is idle");
    leftMotorForward.setval_gpio("0");
    leftMotorBackwards.setval_gpio("0");
    rightMotorForward.setval_gpio("0");
    rightMotorBackwards.setval_gpio("0");}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::MOVING_BACKWARDS entry  */
    if( not Debug__SRO.checkDebug("MOVING_BACKWARDS",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::MOVING_BACKWARDS",(char *)"",(char *)"",(char *)"");
    log.log("Engine is moving backwards");
    leftMotorBackwards.setval_gpio("1");
    rightMotorBackwards.setval_gpio("1");}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::MOVING_FORWARD entry  */
    if( not Debug__SRO.checkDebug("MOVING_FORWARD",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::MOVING_FORWARD",(char *)"",(char *)"",(char *)"");
    log.log("Engine is moving forward");
    leftMotorForward.setval_gpio("1");
    rightMotorForward.setval_gpio("1");}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____TURNING_LEFT( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::TURNING_LEFT entry  */
    if( not Debug__SRO.checkDebug("TURNING_LEFT",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::TURNING_LEFT",(char *)"",(char *)"",(char *)"");
    log.log("Engine is turning left");
    leftMotorBackwards.setval_gpio("1");
    rightMotorForward.setval_gpio("1");}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::entryaction_____TURNING_RIGHT( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::TURNING_RIGHT entry  */
    if( not Debug__SRO.checkDebug("TURNING_RIGHT",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::TURNING_RIGHT",(char *)"",(char *)"",(char *)"");
    log.log("Engine is turning right");
    leftMotorForward.setval_gpio("1");
    rightMotorBackwards.setval_gpio("1");}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__init::Debug__A__Ac__init exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__init::Region1::Debug__A__Ac__init",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__init::Debug__A__En__init exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__init::Region1::Debug__A__En__init",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__init::Debug__B__Ac__init exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__init::Region1::Debug__B__Ac__init",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__init__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__move_backwards__Debug__A__Ac__move_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move backwards::Debug__A__Ac__move backwards exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move backwards::Region1::Debug__A__Ac__move backwards",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__move_backwards__Debug__A__En__MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move backwards::Debug__A__En__MOVING_BACKWARDS exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move backwards::Region1::Debug__A__En__MOVING_BACKWARDS",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__move_backwards__Debug__B__Ac__move_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move backwards::Debug__B__Ac__move backwards exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move backwards::Region1::Debug__B__Ac__move backwards",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__move_backwards__Debug__B__Ex__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move backwards::Debug__B__Ex__IDLE exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move backwards::Region1::Debug__B__Ex__IDLE",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__move_backwards__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__move_forward__Debug__A__Ac__move_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move forward::Debug__A__Ac__move forward exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move forward::Region1::Debug__A__Ac__move forward",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__move_forward__Debug__A__En__MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move forward::Debug__A__En__MOVING_FORWARD exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move forward::Region1::Debug__A__En__MOVING_FORWARD",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__move_forward__Debug__B__Ac__move_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move forward::Debug__B__Ac__move forward exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move forward::Region1::Debug__B__Ac__move forward",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__move_forward__Debug__B__Ex__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move forward::Debug__B__Ex__IDLE exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move forward::Region1::Debug__B__Ex__IDLE",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__move_forward__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__stop_moving_backwards__Debug__A__Ac__stop_moving_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving backwards::Debug__A__Ac__stop moving backwards exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving backwards::Region1::Debug__A__Ac__stop moving backwards",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__stop_moving_backwards__Debug__A__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving backwards::Debug__A__En__IDLE exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving backwards::Region1::Debug__A__En__IDLE",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__stop_moving_backwards__Debug__B__Ac__stop_moving_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving backwards::Debug__B__Ac__stop moving backwards exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving backwards::Region1::Debug__B__Ac__stop moving backwards",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__stop_moving_backwards__Debug__B__Ex__MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving backwards::Debug__B__Ex__MOVING_BACKWARDS exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving backwards::Region1::Debug__B__Ex__MOVING_BACKWARDS",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__stop_moving_backwards__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__stop_moving_forward__Debug__A__Ac__stop_moving_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving forward::Debug__A__Ac__stop moving forward exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving forward::Region1::Debug__A__Ac__stop moving forward",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__stop_moving_forward__Debug__A__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving forward::Debug__A__En__IDLE exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving forward::Region1::Debug__A__En__IDLE",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__stop_moving_forward__Debug__B__Ac__stop_moving_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving forward::Debug__B__Ac__stop moving forward exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving forward::Region1::Debug__B__Ac__stop moving forward",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__stop_moving_forward__Debug__B__Ex__MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving forward::Debug__B__Ex__MOVING_FORWARD exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving forward::Region1::Debug__B__Ex__MOVING_FORWARD",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__stop_moving_forward__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__stop_turning_left__Debug__A__Ac__stop_turning_left( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning left::Debug__A__Ac__stop turning left exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning left::Region1::Debug__A__Ac__stop turning left",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__stop_turning_left__Debug__A__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning left::Debug__A__En__IDLE exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning left::Region1::Debug__A__En__IDLE",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__stop_turning_left__Debug__B__Ac__stop_turning_left( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning left::Debug__B__Ac__stop turning left exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning left::Region1::Debug__B__Ac__stop turning left",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__stop_turning_left__Debug__B__Ex__TURNING_LEFT( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning left::Debug__B__Ex__TURNING_LEFT exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning left::Region1::Debug__B__Ex__TURNING_LEFT",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__stop_turning_left__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__stop_turning_right__Debug__A__Ac__stop_turning_right( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning right::Debug__A__Ac__stop turning right exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning right::Region1::Debug__A__Ac__stop turning right",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__stop_turning_right__Debug__A__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning right::Debug__A__En__IDLE exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning right::Region1::Debug__A__En__IDLE",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__stop_turning_right__Debug__B__Ac__stop_turning_right( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning right::Debug__B__Ac__stop turning right exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning right::Region1::Debug__B__Ac__stop turning right",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__stop_turning_right__Debug__B__Ex__TURNING_RIGHT( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning right::Debug__B__Ex__TURNING_RIGHT exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning right::Region1::Debug__B__Ex__TURNING_RIGHT",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__stop_turning_right__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__turn_left__Debug__A__Ac__turn_left( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn left::Debug__A__Ac__turn left exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn left::Region1::Debug__A__Ac__turn left",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__turn_left__Debug__A__En__TURNING_LEFT( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn left::Debug__A__En__TURNING_LEFT exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn left::Region1::Debug__A__En__TURNING_LEFT",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__turn_left__Debug__B__Ac__turn_left( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn left::Debug__B__Ac__turn left exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn left::Region1::Debug__B__Ac__turn left",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__turn_left__Debug__B__Ex__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn left::Debug__B__Ex__IDLE exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn left::Region1::Debug__B__Ex__IDLE",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__turn_left__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__turn_right__Debug__A__Ac__turn_right( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn right::Debug__A__Ac__turn right exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn right::Region1::Debug__A__Ac__turn right",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__turn_right__Debug__A__En__TURNING_RIGHT( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn right::Debug__A__En__TURNING_RIGHT exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn right::Region1::Debug__A__En__TURNING_RIGHT",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__turn_right__Debug__B__Ac__turn_right( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn right::Debug__B__Ac__turn right exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn right::Region1::Debug__B__Ac__turn right",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__turn_right__Debug__B__Ex__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn right::Debug__B__Ex__IDLE exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn right::Region1::Debug__B__Ex__IDLE",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__C__turn_right__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_EngineController::exitaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__InitState exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____IDLE( const UMLRTMessage * msg )
{
    #define umlrtparam_angle ( *(int *)msg->getParam( 0 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::IDLE exit  */
    if( not Debug__SRO.checkDebug("IDLE",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::IDLE",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_angle
}

void Capsule_EngineController::exitaction_____MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::MOVING_BACKWARDS exit  */
    if( not Debug__SRO.checkDebug("MOVING_BACKWARDS",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::MOVING_BACKWARDS",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::MOVING_FORWARD exit  */
    if( not Debug__SRO.checkDebug("MOVING_FORWARD",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::MOVING_FORWARD",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____TURNING_LEFT( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::TURNING_LEFT exit  */
    if( not Debug__SRO.checkDebug("TURNING_LEFT",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::TURNING_LEFT",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::exitaction_____TURNING_RIGHT( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::TURNING_RIGHT exit  */
    if( not Debug__SRO.checkDebug("TURNING_RIGHT",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::TURNING_RIGHT",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__init__Debug__Ac__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__init transition Debug__C__init::Debug__B__Ac__init,Debug__C__init::Debug__A__Ac__init,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__init::Region1::Debug__Ac__init",(char *)"Debug__B__Ac__init",(char *)"Debug__A__Ac__init",(char *)"");
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

void Capsule_EngineController::transitionaction_____Debug__C__init__Debug__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__init transition Debug__C__init::Debug__A__Ac__init,Debug__C__init::Debug__A__En__init,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__init::Region1::Debug__En__IDLE",(char *)"Debug__A__Ac__init",(char *)"Debug__A__En__init",(char *)"");
    log.log("Engine is idle");
    leftMotorForward.setval_gpio("0");
    leftMotorBackwards.setval_gpio("0");
    rightMotorForward.setval_gpio("0");
    rightMotorBackwards.setval_gpio("0");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__init__Debug__end__trans__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__init transition Debug__C__init::Debug__A__En__init,Debug__C__init::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__init::Region1::Debug__end__trans__init",(char *)"Debug__A__En__init",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__init__Debug__init__trans__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__init transition Debug__C__init::en,Debug__C__init::Debug__B__Ac__init */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__init::Region1::Debug__init__trans__init",(char *)"en",(char *)"Debug__B__Ac__init",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__move_backwards__Debug__AC__move_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move backwards transition Debug__C__move backwards::Debug__B__Ac__move backwards,Debug__C__move backwards::Debug__A__Ac__move backwards,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move backwards::Region1::Debug__AC__move backwards",(char *)"Debug__B__Ac__move backwards",(char *)"Debug__A__Ac__move backwards",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__move_backwards__Debug__En__MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move backwards transition Debug__C__move backwards::Debug__A__Ac__move backwards,Debug__C__move backwards::Debug__A__En__MOVING_BACKWARDS,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move backwards::Region1::Debug__En__MOVING_BACKWARDS",(char *)"Debug__A__Ac__move backwards",(char *)"Debug__A__En__MOVING_BACKWARDS",(char *)"");
    log.log("Engine is moving backwards");
    leftMotorBackwards.setval_gpio("1");
    rightMotorBackwards.setval_gpio("1");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__move_backwards__Debug__Ex__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move backwards transition Debug__C__move backwards::Debug__B__Ex__IDLE,Debug__C__move backwards::Debug__B__Ac__move backwards,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move backwards::Region1::Debug__Ex__IDLE",(char *)"Debug__B__Ex__IDLE",(char *)"Debug__B__Ac__move backwards",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__move_backwards__Debug__end__trans__move_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move backwards transition Debug__C__move backwards::Debug__A__En__MOVING_BACKWARDS,Debug__C__move backwards::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move backwards::Region1::Debug__end__trans__move backwards",(char *)"Debug__A__En__MOVING_BACKWARDS",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__move_backwards__Debug__init__trans__move_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move backwards transition Debug__C__move backwards::en,Debug__C__move backwards::Debug__B__Ex__IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move backwards::Region1::Debug__init__trans__move backwards",(char *)"en",(char *)"Debug__B__Ex__IDLE",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__move_forward__Debug__AC__move_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move forward transition Debug__C__move forward::Debug__B__Ac__move forward,Debug__C__move forward::Debug__A__Ac__move forward,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move forward::Region1::Debug__AC__move forward",(char *)"Debug__B__Ac__move forward",(char *)"Debug__A__Ac__move forward",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__move_forward__Debug__En__MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move forward transition Debug__C__move forward::Debug__A__Ac__move forward,Debug__C__move forward::Debug__A__En__MOVING_FORWARD,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move forward::Region1::Debug__En__MOVING_FORWARD",(char *)"Debug__A__Ac__move forward",(char *)"Debug__A__En__MOVING_FORWARD",(char *)"");
    log.log("Engine is moving forward");
    leftMotorForward.setval_gpio("1");
    rightMotorForward.setval_gpio("1");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__move_forward__Debug__Ex__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move forward transition Debug__C__move forward::Debug__B__Ex__IDLE,Debug__C__move forward::Debug__B__Ac__move forward,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move forward::Region1::Debug__Ex__IDLE",(char *)"Debug__B__Ex__IDLE",(char *)"Debug__B__Ac__move forward",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__move_forward__Debug__end__trans__move_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move forward transition Debug__C__move forward::Debug__A__En__MOVING_FORWARD,Debug__C__move forward::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move forward::Region1::Debug__end__trans__move forward",(char *)"Debug__A__En__MOVING_FORWARD",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__move_forward__Debug__init__trans__move_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__move forward transition Debug__C__move forward::en,Debug__C__move forward::Debug__B__Ex__IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__move forward::Region1::Debug__init__trans__move forward",(char *)"en",(char *)"Debug__B__Ex__IDLE",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__stop_moving_backwards__Debug__AC__stop_moving_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving backwards transition Debug__C__stop moving backwards::Debug__B__Ac__stop moving backwards,Debug__C__stop moving backwards::Debug__A__Ac__stop moving backwards,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving backwards::Region1::Debug__AC__stop moving backwards",(char *)"Debug__B__Ac__stop moving backwards",(char *)"Debug__A__Ac__stop moving backwards",(char *)"");
    engine.stopped().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__stop_moving_backwards__Debug__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving backwards transition Debug__C__stop moving backwards::Debug__A__Ac__stop moving backwards,Debug__C__stop moving backwards::Debug__A__En__IDLE,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving backwards::Region1::Debug__En__IDLE",(char *)"Debug__A__Ac__stop moving backwards",(char *)"Debug__A__En__IDLE",(char *)"");
    log.log("Engine is idle");
    leftMotorForward.setval_gpio("0");
    leftMotorBackwards.setval_gpio("0");
    rightMotorForward.setval_gpio("0");
    rightMotorBackwards.setval_gpio("0");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__stop_moving_backwards__Debug__Ex__MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving backwards transition Debug__C__stop moving backwards::Debug__B__Ex__MOVING_BACKWARDS,Debug__C__stop moving backwards::Debug__B__Ac__stop moving backwards,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving backwards::Region1::Debug__Ex__MOVING_BACKWARDS",(char *)"Debug__B__Ex__MOVING_BACKWARDS",(char *)"Debug__B__Ac__stop moving backwards",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__stop_moving_backwards__Debug__end__trans__stop_moving_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving backwards transition Debug__C__stop moving backwards::Debug__A__En__IDLE,Debug__C__stop moving backwards::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving backwards::Region1::Debug__end__trans__stop moving backwards",(char *)"Debug__A__En__IDLE",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__stop_moving_backwards__Debug__init__trans__stop_moving_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving backwards transition Debug__C__stop moving backwards::en,Debug__C__stop moving backwards::Debug__B__Ex__MOVING_BACKWARDS */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving backwards::Region1::Debug__init__trans__stop moving backwards",(char *)"en",(char *)"Debug__B__Ex__MOVING_BACKWARDS",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__stop_moving_forward__Debug__AC__stop_moving_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving forward transition Debug__C__stop moving forward::Debug__B__Ac__stop moving forward,Debug__C__stop moving forward::Debug__A__Ac__stop moving forward,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving forward::Region1::Debug__AC__stop moving forward",(char *)"Debug__B__Ac__stop moving forward",(char *)"Debug__A__Ac__stop moving forward",(char *)"");
    engine.stopped().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__stop_moving_forward__Debug__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving forward transition Debug__C__stop moving forward::Debug__A__Ac__stop moving forward,Debug__C__stop moving forward::Debug__A__En__IDLE,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving forward::Region1::Debug__En__IDLE",(char *)"Debug__A__Ac__stop moving forward",(char *)"Debug__A__En__IDLE",(char *)"");
    log.log("Engine is idle");
    leftMotorForward.setval_gpio("0");
    leftMotorBackwards.setval_gpio("0");
    rightMotorForward.setval_gpio("0");
    rightMotorBackwards.setval_gpio("0");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__stop_moving_forward__Debug__Ex__MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving forward transition Debug__C__stop moving forward::Debug__B__Ex__MOVING_FORWARD,Debug__C__stop moving forward::Debug__B__Ac__stop moving forward,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving forward::Region1::Debug__Ex__MOVING_FORWARD",(char *)"Debug__B__Ex__MOVING_FORWARD",(char *)"Debug__B__Ac__stop moving forward",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__stop_moving_forward__Debug__end__trans__stop_moving_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving forward transition Debug__C__stop moving forward::Debug__A__En__IDLE,Debug__C__stop moving forward::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving forward::Region1::Debug__end__trans__stop moving forward",(char *)"Debug__A__En__IDLE",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__stop_moving_forward__Debug__init__trans__stop_moving_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop moving forward transition Debug__C__stop moving forward::en,Debug__C__stop moving forward::Debug__B__Ex__MOVING_FORWARD */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop moving forward::Region1::Debug__init__trans__stop moving forward",(char *)"en",(char *)"Debug__B__Ex__MOVING_FORWARD",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__stop_turning_left__Debug__AC__stop_turning_left( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning left transition Debug__C__stop turning left::Debug__B__Ac__stop turning left,Debug__C__stop turning left::Debug__A__Ac__stop turning left,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning left::Region1::Debug__AC__stop turning left",(char *)"Debug__B__Ac__stop turning left",(char *)"Debug__A__Ac__stop turning left",(char *)"");
    engine.turnedRight().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__stop_turning_left__Debug__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning left transition Debug__C__stop turning left::Debug__A__Ac__stop turning left,Debug__C__stop turning left::Debug__A__En__IDLE,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning left::Region1::Debug__En__IDLE",(char *)"Debug__A__Ac__stop turning left",(char *)"Debug__A__En__IDLE",(char *)"");
    log.log("Engine is idle");
    leftMotorForward.setval_gpio("0");
    leftMotorBackwards.setval_gpio("0");
    rightMotorForward.setval_gpio("0");
    rightMotorBackwards.setval_gpio("0");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__stop_turning_left__Debug__Ex__TURNING_LEFT( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning left transition Debug__C__stop turning left::Debug__B__Ex__TURNING_LEFT,Debug__C__stop turning left::Debug__B__Ac__stop turning left,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning left::Region1::Debug__Ex__TURNING_LEFT",(char *)"Debug__B__Ex__TURNING_LEFT",(char *)"Debug__B__Ac__stop turning left",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__stop_turning_left__Debug__end__trans__stop_turning_left( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning left transition Debug__C__stop turning left::Debug__A__En__IDLE,Debug__C__stop turning left::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning left::Region1::Debug__end__trans__stop turning left",(char *)"Debug__A__En__IDLE",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__stop_turning_left__Debug__init__trans__stop_turning_left( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning left transition Debug__C__stop turning left::en,Debug__C__stop turning left::Debug__B__Ex__TURNING_LEFT */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning left::Region1::Debug__init__trans__stop turning left",(char *)"en",(char *)"Debug__B__Ex__TURNING_LEFT",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__stop_turning_right__Debug__AC__stop_turning_right( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning right transition Debug__C__stop turning right::Debug__B__Ac__stop turning right,Debug__C__stop turning right::Debug__A__Ac__stop turning right,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning right::Region1::Debug__AC__stop turning right",(char *)"Debug__B__Ac__stop turning right",(char *)"Debug__A__Ac__stop turning right",(char *)"");
    engine.turnedRight().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__stop_turning_right__Debug__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning right transition Debug__C__stop turning right::Debug__A__Ac__stop turning right,Debug__C__stop turning right::Debug__A__En__IDLE,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning right::Region1::Debug__En__IDLE",(char *)"Debug__A__Ac__stop turning right",(char *)"Debug__A__En__IDLE",(char *)"");
    log.log("Engine is idle");
    leftMotorForward.setval_gpio("0");
    leftMotorBackwards.setval_gpio("0");
    rightMotorForward.setval_gpio("0");
    rightMotorBackwards.setval_gpio("0");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__stop_turning_right__Debug__Ex__TURNING_RIGHT( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning right transition Debug__C__stop turning right::Debug__B__Ex__TURNING_RIGHT,Debug__C__stop turning right::Debug__B__Ac__stop turning right,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning right::Region1::Debug__Ex__TURNING_RIGHT",(char *)"Debug__B__Ex__TURNING_RIGHT",(char *)"Debug__B__Ac__stop turning right",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__stop_turning_right__Debug__end__trans__stop_turning_right( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning right transition Debug__C__stop turning right::Debug__A__En__IDLE,Debug__C__stop turning right::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning right::Region1::Debug__end__trans__stop turning right",(char *)"Debug__A__En__IDLE",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__stop_turning_right__Debug__init__trans__stop_turning_right( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__stop turning right transition Debug__C__stop turning right::en,Debug__C__stop turning right::Debug__B__Ex__TURNING_RIGHT */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__stop turning right::Region1::Debug__init__trans__stop turning right",(char *)"en",(char *)"Debug__B__Ex__TURNING_RIGHT",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__turn_left__Debug__AC__turn_left( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn left transition Debug__C__turn left::Debug__B__Ac__turn left,Debug__C__turn left::Debug__A__Ac__turn left,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn left::Region1::Debug__AC__turn left",(char *)"Debug__B__Ac__turn left",(char *)"Debug__A__Ac__turn left",(char *)"");
    timerId = timer.informIn(UMLRTTimespec(0, (10 / 360) * 1000000000));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__turn_left__Debug__En__TURNING_LEFT( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn left transition Debug__C__turn left::Debug__A__Ac__turn left,Debug__C__turn left::Debug__A__En__TURNING_LEFT,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn left::Region1::Debug__En__TURNING_LEFT",(char *)"Debug__A__Ac__turn left",(char *)"Debug__A__En__TURNING_LEFT",(char *)"");
    log.log("Engine is turning left");
    leftMotorBackwards.setval_gpio("1");
    rightMotorForward.setval_gpio("1");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__turn_left__Debug__Ex__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn left transition Debug__C__turn left::Debug__B__Ex__IDLE,Debug__C__turn left::Debug__B__Ac__turn left,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn left::Region1::Debug__Ex__IDLE",(char *)"Debug__B__Ex__IDLE",(char *)"Debug__B__Ac__turn left",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__turn_left__Debug__end__trans__turn_left( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn left transition Debug__C__turn left::Debug__A__En__TURNING_LEFT,Debug__C__turn left::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn left::Region1::Debug__end__trans__turn left",(char *)"Debug__A__En__TURNING_LEFT",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__turn_left__Debug__init__trans__turn_left( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn left transition Debug__C__turn left::en,Debug__C__turn left::Debug__B__Ex__IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn left::Region1::Debug__init__trans__turn left",(char *)"en",(char *)"Debug__B__Ex__IDLE",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__turn_right__Debug__AC__turn_right( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn right transition Debug__C__turn right::Debug__B__Ac__turn right,Debug__C__turn right::Debug__A__Ac__turn right,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn right::Region1::Debug__AC__turn right",(char *)"Debug__B__Ac__turn right",(char *)"Debug__A__Ac__turn right",(char *)"");
    timerId = timer.informIn(UMLRTTimespec(0, (160 / 360) * 1000000000));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__turn_right__Debug__En__TURNING_RIGHT( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn right transition Debug__C__turn right::Debug__A__Ac__turn right,Debug__C__turn right::Debug__A__En__TURNING_RIGHT,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn right::Region1::Debug__En__TURNING_RIGHT",(char *)"Debug__A__Ac__turn right",(char *)"Debug__A__En__TURNING_RIGHT",(char *)"");
    log.log("Engine is turning right");
    leftMotorForward.setval_gpio("1");
    rightMotorBackwards.setval_gpio("1");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__turn_right__Debug__Ex__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn right transition Debug__C__turn right::Debug__B__Ex__IDLE,Debug__C__turn right::Debug__B__Ac__turn right,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn right::Region1::Debug__Ex__IDLE",(char *)"Debug__B__Ex__IDLE",(char *)"Debug__B__Ac__turn right",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__turn_right__Debug__end__trans__turn_right( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn right transition Debug__C__turn right::Debug__A__En__TURNING_RIGHT,Debug__C__turn right::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn right::Region1::Debug__end__trans__turn right",(char *)"Debug__A__En__TURNING_RIGHT",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__C__turn_right__Debug__init__trans__turn_right( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController::Debug__C__turn right transition Debug__C__turn right::en,Debug__C__turn right::Debug__B__Ex__IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__C__turn right::Region1::Debug__init__trans__turn right",(char *)"en",(char *)"Debug__B__Ex__IDLE",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__InitDebug( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Pseudo2,Debug__InitState */
    std::cout<<this->getName()<<" : is Starting\n";
    std::string tempS;
    std::cout<<"Enter 1 for running in debug mode, any other key for normal model\n";
    std::cin>> tempS;
    if (tempS=="1")
    this->Debug__SRO.setExecMode(Stepping);
    else
    this->Debug__SRO.setExecMode(Running);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__InitState,Debug__Path__init,null:extComm */
    if (this->Debug__SRO.getExecMode()==Stepping){
    Debug__SRO.addTransitionsFromState("IDLE","move forward","MOVING_FORWARD","moveForward","Engine");
    Debug__SRO.addTransitionsFromState("IDLE","move backwards","MOVING_BACKWARDS","moveBackwards","Engine");
    Debug__SRO.addTransitionsFromState("IDLE","turn left","TURNING_LEFT","turnLeft","Engine");
    Debug__SRO.addTransitionsFromState("TURNING_LEFT","stop turning left","IDLE","timeout","Timing");
    Debug__SRO.addTransitionsFromState("MOVING_FORWARD","stop moving forward","IDLE","stop","Engine");
    Debug__SRO.addTransitionsFromState("","init","IDLE","","");
    Debug__SRO.addTransitionsFromState("IDLE","turn right","TURNING_RIGHT","turnRight","Engine");
    Debug__SRO.addTransitionsFromState("STOPPING_MOVING_BACKWARDS","stopped moving backwards","ROTATING","stopped","Engine");
    Debug__SRO.addTransitionsFromState("MOVING_FORWARD","lowerThanThreshold","STOPPING_MOVING_FORWARD","obstacleDetected","Detection");
    Debug__SRO.addTransitionsFromState("MOVING_BACKWARDS","stop moving backwards","IDLE","stop","Engine");
    Debug__SRO.addTransitionsFromState("","init","STANDBY","","");
    Debug__SRO.addTransitionsFromState("MOVING_FORWARD","greaterThan","MOVING_FORWARD","obstacleDetected","Detection");
    Debug__SRO.addTransitionsFromState("ROTATING","turnedRight","MOVING_FORWARD","turnedRight","Engine");
    Debug__SRO.addTransitionsFromState("TURNING_RIGHT","stop turning right","IDLE","timeout","Timing");
    Debug__SRO.addTransitionsFromState("MOVING_BACKWARDS","timeout","STOPPING_MOVING_BACKWARDS","timeout","Timing");
    Debug__SRO.addTransitionsFromState("STANDBY","moving forward","MOVING_FORWARD","timeout","Timing");
    Debug__SRO.addTransitionsFromState("STOPPING_MOVING_FORWARD","stopped","MOVING_BACKWARDS","stopped","Engine");
    std::cout<<this->getName()<<": Connection with debugger is in progress\n";
    char  tempS[256];
    sprintf(tempS,"%s%d",this->getName(),(int)this->getIndex());
    extComm.registerToControl(tempS).send();
    Debug__sendEvent(debugEvents::DEBUG,debugEvents::REGISTER,this->getName(),this->getIndex(),msg->getSignalName(),(char *) "",(char *) "",(char *) "",(char *)"",(char *) "");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__init__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__C__init::ex,IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__init__E",(char *)"ex",(char *)"IDLE",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__init__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__Path__init,Debug__C__init::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__init__S",(char *)"Debug__Path__init",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__init__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__C__init::new_exitpoint_7,Debug__C__init */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__init__dbg",(char *)"Debug__C__init",(char *)"Debug__C__init",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__move_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition IDLE,Debug__Path__move backwards,moveBackwards:engine */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__move backwards",(char *)"IDLE",(char *)"Debug__Path__move backwards",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__move_backwards__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__C__move backwards::ex,MOVING_BACKWARDS */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__move backwards__E",(char *)"ex",(char *)"MOVING_BACKWARDS",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__move_backwards__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__Path__move backwards,Debug__C__move backwards::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__move backwards__S",(char *)"Debug__Path__move backwards",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__move_backwards__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__C__move backwards::new_exitpoint_9,Debug__C__move backwards */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__move backwards__dbg",(char *)"Debug__C__move backwards",(char *)"Debug__C__move backwards",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__move_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition IDLE,Debug__Path__move forward,moveForward:engine */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__move forward",(char *)"IDLE",(char *)"Debug__Path__move forward",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__move_forward__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__C__move forward::ex,MOVING_FORWARD */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__move forward__E",(char *)"ex",(char *)"MOVING_FORWARD",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__move_forward__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__Path__move forward,Debug__C__move forward::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__move forward__S",(char *)"Debug__Path__move forward",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__move_forward__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__C__move forward::new_exitpoint_4,Debug__C__move forward */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__move forward__dbg",(char *)"Debug__C__move forward",(char *)"Debug__C__move forward",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__stop_moving_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition MOVING_BACKWARDS,Debug__Path__stop moving backwards,stop:engine */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__stop moving backwards",(char *)"MOVING_BACKWARDS",(char *)"Debug__Path__stop moving backwards",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__stop_moving_backwards__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__C__stop moving backwards::ex,IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__stop moving backwards__E",(char *)"ex",(char *)"IDLE",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__stop_moving_backwards__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__Path__stop moving backwards,Debug__C__stop moving backwards::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__stop moving backwards__S",(char *)"Debug__Path__stop moving backwards",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__stop_moving_backwards__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__C__stop moving backwards::new_exitpoint_5,Debug__C__stop moving backwards */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__stop moving backwards__dbg",(char *)"Debug__C__stop moving backwards",(char *)"Debug__C__stop moving backwards",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__stop_moving_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition MOVING_FORWARD,Debug__Path__stop moving forward,stop:engine */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__stop moving forward",(char *)"MOVING_FORWARD",(char *)"Debug__Path__stop moving forward",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__stop_moving_forward__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__C__stop moving forward::ex,IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__stop moving forward__E",(char *)"ex",(char *)"IDLE",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__stop_moving_forward__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__Path__stop moving forward,Debug__C__stop moving forward::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__stop moving forward__S",(char *)"Debug__Path__stop moving forward",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__stop_moving_forward__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__C__stop moving forward::new_exitpoint_3,Debug__C__stop moving forward */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__stop moving forward__dbg",(char *)"Debug__C__stop moving forward",(char *)"Debug__C__stop moving forward",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__stop_turning_left( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition TURNING_LEFT,Debug__Path__stop turning left,timeout:timer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__stop turning left",(char *)"TURNING_LEFT",(char *)"Debug__Path__stop turning left",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__stop_turning_left__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__C__stop turning left::ex,IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__stop turning left__E",(char *)"ex",(char *)"IDLE",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__stop_turning_left__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__Path__stop turning left,Debug__C__stop turning left::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__stop turning left__S",(char *)"Debug__Path__stop turning left",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__stop_turning_left__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__C__stop turning left::new_exitpoint_6,Debug__C__stop turning left */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__stop turning left__dbg",(char *)"Debug__C__stop turning left",(char *)"Debug__C__stop turning left",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__stop_turning_right( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition TURNING_RIGHT,Debug__Path__stop turning right,timeout:timer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__stop turning right",(char *)"TURNING_RIGHT",(char *)"Debug__Path__stop turning right",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__stop_turning_right__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__C__stop turning right::ex,IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__stop turning right__E",(char *)"ex",(char *)"IDLE",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__stop_turning_right__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__Path__stop turning right,Debug__C__stop turning right::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__stop turning right__S",(char *)"Debug__Path__stop turning right",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__stop_turning_right__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__C__stop turning right::new_exitpoint_2,Debug__C__stop turning right */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__stop turning right__dbg",(char *)"Debug__C__stop turning right",(char *)"Debug__C__stop turning right",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__turn_left( const UMLRTMessage * msg )
{
    #define umlrtparam_angle ( *(int *)msg->getParam( 0 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition IDLE,Debug__Path__turn left,turnLeft:engine */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__turn left",(char *)"IDLE",(char *)"Debug__Path__turn left",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_angle
}

void Capsule_EngineController::transitionaction_____Debug__turn_left__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__C__turn left::ex,TURNING_LEFT */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__turn left__E",(char *)"ex",(char *)"TURNING_LEFT",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__turn_left__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__Path__turn left,Debug__C__turn left::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__turn left__S",(char *)"Debug__Path__turn left",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__turn_left__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__C__turn left::new_exitpoint_1,Debug__C__turn left */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__turn left__dbg",(char *)"Debug__C__turn left",(char *)"Debug__C__turn left",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__turn_right( const UMLRTMessage * msg )
{
    #define umlrtparam_angle ( *(int *)msg->getParam( 0 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition IDLE,Debug__Path__turn right,turnRight:engine */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__turn right",(char *)"IDLE",(char *)"Debug__Path__turn right",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_angle
}

void Capsule_EngineController::transitionaction_____Debug__turn_right__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__C__turn right::ex,TURNING_RIGHT */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__turn right__E",(char *)"ex",(char *)"TURNING_RIGHT",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__turn_right__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__Path__turn right,Debug__C__turn right::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__turn right__S",(char *)"Debug__Path__turn right",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____Debug__turn_right__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__C__turn right::new_exitpoint_8,Debug__C__turn right */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::Debug__turn right__dbg",(char *)"Debug__C__turn right",(char *)"Debug__C__turn right",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__Path__init,IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::init",(char *)"Debug__Path__init",(char *)"IDLE",(char *)"");
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

void Capsule_EngineController::transitionaction_____move_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__Path__move backwards,MOVING_BACKWARDS */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::move backwards",(char *)"Debug__Path__move backwards",(char *)"MOVING_BACKWARDS",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____move_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__Path__move forward,MOVING_FORWARD */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::move forward",(char *)"Debug__Path__move forward",(char *)"MOVING_FORWARD",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____stop_moving_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__Path__stop moving backwards,IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::stop moving backwards",(char *)"Debug__Path__stop moving backwards",(char *)"IDLE",(char *)"");
    engine.stopped().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____stop_moving_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__Path__stop moving forward,IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::stop moving forward",(char *)"Debug__Path__stop moving forward",(char *)"IDLE",(char *)"");
    engine.stopped().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____stop_turning_left( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__Path__stop turning left,IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::stop turning left",(char *)"Debug__Path__stop turning left",(char *)"IDLE",(char *)"");
    engine.turnedRight().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____stop_turning_right( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__Path__stop turning right,IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::stop turning right",(char *)"Debug__Path__stop turning right",(char *)"IDLE",(char *)"");
    engine.turnedRight().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____turn_left( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__Path__turn left,TURNING_LEFT */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::turn left",(char *)"Debug__Path__turn left",(char *)"TURNING_LEFT",(char *)"");
    timerId = timer.informIn(UMLRTTimespec(0, (100 / 360) * 1000000000));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EngineController::transitionaction_____turn_right( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController transition Debug__Path__turn right,TURNING_RIGHT */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::EngineController::EngineControllerStateMachine::Region::turn right",(char *)"Debug__Path__turn right",(char *)"TURNING_RIGHT",(char *)"");
    timerId = timer.informIn(UMLRTTimespec(0, (50 / 360) * 1000000000));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_EngineController::action_____Debug__init__S__Debug__Guardinit( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController guard Debug__Path__init,Debug__C__init::en */
    return Debug__SRO.checkDebug("Pseudo2","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_EngineController::action_____Debug__move_backwards__S__Debug__Guardmove_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController guard Debug__Path__move backwards,Debug__C__move backwards::en */
    return Debug__SRO.checkDebug("IDLE",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_EngineController::action_____Debug__move_forward__S__Debug__Guardmove_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController guard Debug__Path__move forward,Debug__C__move forward::en */
    return Debug__SRO.checkDebug("IDLE",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_EngineController::action_____Debug__stop_moving_backwards__S__Debug__Guardstop_moving_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController guard Debug__Path__stop moving backwards,Debug__C__stop moving backwards::en */
    return Debug__SRO.checkDebug("MOVING_BACKWARDS",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_EngineController::action_____Debug__stop_moving_forward__S__Debug__Guardstop_moving_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController guard Debug__Path__stop moving forward,Debug__C__stop moving forward::en */
    return Debug__SRO.checkDebug("MOVING_FORWARD",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_EngineController::action_____Debug__stop_turning_left__S__Debug__Guardstop_turning_left( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController guard Debug__Path__stop turning left,Debug__C__stop turning left::en */
    return Debug__SRO.checkDebug("TURNING_LEFT",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_EngineController::action_____Debug__stop_turning_right__S__Debug__Guardstop_turning_right( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController guard Debug__Path__stop turning right,Debug__C__stop turning right::en */
    return Debug__SRO.checkDebug("TURNING_RIGHT",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_EngineController::action_____Debug__turn_left__S__Debug__Guardturn_left( const UMLRTMessage * msg )
{
    #define umlrtparam_angle ( *(int *)msg->getParam( 0 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController guard Debug__Path__turn left,Debug__C__turn left::en */
    return Debug__SRO.checkDebug("IDLE",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_angle
}

bool Capsule_EngineController::action_____Debug__turn_right__S__Debug__Guardturn_right( const UMLRTMessage * msg )
{
    #define umlrtparam_angle ( *(int *)msg->getParam( 0 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::EngineController guard Debug__Path__turn right,Debug__C__turn right::en */
    return Debug__SRO.checkDebug("IDLE",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_angle
}

void Capsule_EngineController::actionchain_____Debug__C__init__Debug__Ac__init( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__B__Ac__init( msg );
    transitionaction_____Debug__C__init__Debug__Ac__init( msg );
    entryaction_____Debug__C__init__Debug__A__Ac__init( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__init__Debug__En__IDLE( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__A__Ac__init( msg );
    transitionaction_____Debug__C__init__Debug__En__IDLE( msg );
    entryaction_____Debug__C__init__Debug__A__En__init( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__init__Debug__end__trans__init( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__A__En__init( msg );
    transitionaction_____Debug__C__init__Debug__end__trans__init( msg );
    save_history( Debug__C__init, Debug__C__init__Debug__A__En__init );
}

void Capsule_EngineController::actionchain_____Debug__C__init__Debug__init__trans__init( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__init__Debug__init__trans__init( msg );
    entryaction_____Debug__C__init__Debug__B__Ac__init( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__init__new_transition_61( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__Debug__B__Ac__init( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__init__new_transition_62( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__Debug__A__Ac__init( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__init__new_transition_63( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__Debug__A__En__init( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__init__new_transition_64_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__init__new_transition_65( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__B__Ac__init( msg );
    save_history( Debug__C__init, Debug__C__init__Debug__B__Ac__init );
}

void Capsule_EngineController::actionchain_____Debug__C__init__new_transition_66( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__A__Ac__init( msg );
    save_history( Debug__C__init, Debug__C__init__Debug__A__Ac__init );
}

void Capsule_EngineController::actionchain_____Debug__C__init__new_transition_67( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__A__En__init( msg );
    save_history( Debug__C__init, Debug__C__init__Debug__A__En__init );
}

void Capsule_EngineController::actionchain_____Debug__C__init__new_transition_68( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__boundary( msg );
    save_history( Debug__C__init, Debug__C__init__boundary );
}

void Capsule_EngineController::actionchain_____Debug__C__move_backwards__Debug__AC__move_backwards( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__move_backwards__Debug__B__Ac__move_backwards( msg );
    transitionaction_____Debug__C__move_backwards__Debug__AC__move_backwards( msg );
    entryaction_____Debug__C__move_backwards__Debug__A__Ac__move_backwards( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__move_backwards__Debug__En__MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__move_backwards__Debug__A__Ac__move_backwards( msg );
    transitionaction_____Debug__C__move_backwards__Debug__En__MOVING_BACKWARDS( msg );
    entryaction_____Debug__C__move_backwards__Debug__A__En__MOVING_BACKWARDS( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__move_backwards__Debug__Ex__IDLE( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__move_backwards__Debug__B__Ex__IDLE( msg );
    transitionaction_____Debug__C__move_backwards__Debug__Ex__IDLE( msg );
    entryaction_____Debug__C__move_backwards__Debug__B__Ac__move_backwards( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__move_backwards__Debug__end__trans__move_backwards( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__move_backwards__Debug__A__En__MOVING_BACKWARDS( msg );
    transitionaction_____Debug__C__move_backwards__Debug__end__trans__move_backwards( msg );
    save_history( Debug__C__move_backwards, Debug__C__move_backwards__Debug__A__En__MOVING_BACKWARDS );
}

void Capsule_EngineController::actionchain_____Debug__C__move_backwards__Debug__init__trans__move_backwards( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__move_backwards__Debug__init__trans__move_backwards( msg );
    entryaction_____Debug__C__move_backwards__Debug__B__Ex__IDLE( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__move_backwards__new_transition_79( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__move_backwards__Debug__B__Ex__IDLE( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__move_backwards__new_transition_80( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__move_backwards__Debug__B__Ac__move_backwards( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__move_backwards__new_transition_81( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__move_backwards__Debug__A__Ac__move_backwards( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__move_backwards__new_transition_82( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__move_backwards__Debug__A__En__MOVING_BACKWARDS( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__move_backwards__new_transition_83_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__move_backwards__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__move_backwards__new_transition_84( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__move_backwards__Debug__B__Ex__IDLE( msg );
    save_history( Debug__C__move_backwards, Debug__C__move_backwards__Debug__B__Ex__IDLE );
}

void Capsule_EngineController::actionchain_____Debug__C__move_backwards__new_transition_85( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__move_backwards__Debug__B__Ac__move_backwards( msg );
    save_history( Debug__C__move_backwards, Debug__C__move_backwards__Debug__B__Ac__move_backwards );
}

void Capsule_EngineController::actionchain_____Debug__C__move_backwards__new_transition_86( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__move_backwards__Debug__A__Ac__move_backwards( msg );
    save_history( Debug__C__move_backwards, Debug__C__move_backwards__Debug__A__Ac__move_backwards );
}

void Capsule_EngineController::actionchain_____Debug__C__move_backwards__new_transition_87( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__move_backwards__Debug__A__En__MOVING_BACKWARDS( msg );
    save_history( Debug__C__move_backwards, Debug__C__move_backwards__Debug__A__En__MOVING_BACKWARDS );
}

void Capsule_EngineController::actionchain_____Debug__C__move_backwards__new_transition_88( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__move_backwards__boundary( msg );
    save_history( Debug__C__move_backwards, Debug__C__move_backwards__boundary );
}

void Capsule_EngineController::actionchain_____Debug__C__move_forward__Debug__AC__move_forward( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__move_forward__Debug__B__Ac__move_forward( msg );
    transitionaction_____Debug__C__move_forward__Debug__AC__move_forward( msg );
    entryaction_____Debug__C__move_forward__Debug__A__Ac__move_forward( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__move_forward__Debug__En__MOVING_FORWARD( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__move_forward__Debug__A__Ac__move_forward( msg );
    transitionaction_____Debug__C__move_forward__Debug__En__MOVING_FORWARD( msg );
    entryaction_____Debug__C__move_forward__Debug__A__En__MOVING_FORWARD( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__move_forward__Debug__Ex__IDLE( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__move_forward__Debug__B__Ex__IDLE( msg );
    transitionaction_____Debug__C__move_forward__Debug__Ex__IDLE( msg );
    entryaction_____Debug__C__move_forward__Debug__B__Ac__move_forward( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__move_forward__Debug__end__trans__move_forward( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__move_forward__Debug__A__En__MOVING_FORWARD( msg );
    transitionaction_____Debug__C__move_forward__Debug__end__trans__move_forward( msg );
    save_history( Debug__C__move_forward, Debug__C__move_forward__Debug__A__En__MOVING_FORWARD );
}

void Capsule_EngineController::actionchain_____Debug__C__move_forward__Debug__init__trans__move_forward( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__move_forward__Debug__init__trans__move_forward( msg );
    entryaction_____Debug__C__move_forward__Debug__B__Ex__IDLE( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__move_forward__new_transition_31( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__move_forward__Debug__B__Ex__IDLE( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__move_forward__new_transition_32( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__move_forward__Debug__B__Ac__move_forward( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__move_forward__new_transition_33( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__move_forward__Debug__A__Ac__move_forward( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__move_forward__new_transition_34( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__move_forward__Debug__A__En__MOVING_FORWARD( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__move_forward__new_transition_35_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__move_forward__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__move_forward__new_transition_36( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__move_forward__Debug__B__Ex__IDLE( msg );
    save_history( Debug__C__move_forward, Debug__C__move_forward__Debug__B__Ex__IDLE );
}

void Capsule_EngineController::actionchain_____Debug__C__move_forward__new_transition_37( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__move_forward__Debug__B__Ac__move_forward( msg );
    save_history( Debug__C__move_forward, Debug__C__move_forward__Debug__B__Ac__move_forward );
}

void Capsule_EngineController::actionchain_____Debug__C__move_forward__new_transition_38( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__move_forward__Debug__A__Ac__move_forward( msg );
    save_history( Debug__C__move_forward, Debug__C__move_forward__Debug__A__Ac__move_forward );
}

void Capsule_EngineController::actionchain_____Debug__C__move_forward__new_transition_39( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__move_forward__Debug__A__En__MOVING_FORWARD( msg );
    save_history( Debug__C__move_forward, Debug__C__move_forward__Debug__A__En__MOVING_FORWARD );
}

void Capsule_EngineController::actionchain_____Debug__C__move_forward__new_transition_40( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__move_forward__boundary( msg );
    save_history( Debug__C__move_forward, Debug__C__move_forward__boundary );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_backwards__Debug__AC__stop_moving_backwards( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_moving_backwards__Debug__B__Ac__stop_moving_backwards( msg );
    transitionaction_____Debug__C__stop_moving_backwards__Debug__AC__stop_moving_backwards( msg );
    entryaction_____Debug__C__stop_moving_backwards__Debug__A__Ac__stop_moving_backwards( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_backwards__Debug__En__IDLE( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_moving_backwards__Debug__A__Ac__stop_moving_backwards( msg );
    transitionaction_____Debug__C__stop_moving_backwards__Debug__En__IDLE( msg );
    entryaction_____Debug__C__stop_moving_backwards__Debug__A__En__IDLE( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_backwards__Debug__Ex__MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_moving_backwards__Debug__B__Ex__MOVING_BACKWARDS( msg );
    transitionaction_____Debug__C__stop_moving_backwards__Debug__Ex__MOVING_BACKWARDS( msg );
    entryaction_____Debug__C__stop_moving_backwards__Debug__B__Ac__stop_moving_backwards( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_backwards__Debug__end__trans__stop_moving_backwards( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_moving_backwards__Debug__A__En__IDLE( msg );
    transitionaction_____Debug__C__stop_moving_backwards__Debug__end__trans__stop_moving_backwards( msg );
    save_history( Debug__C__stop_moving_backwards, Debug__C__stop_moving_backwards__Debug__A__En__IDLE );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_backwards__Debug__init__trans__stop_moving_backwards( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__stop_moving_backwards__Debug__init__trans__stop_moving_backwards( msg );
    entryaction_____Debug__C__stop_moving_backwards__Debug__B__Ex__MOVING_BACKWARDS( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_backwards__new_transition_41( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_moving_backwards__Debug__B__Ex__MOVING_BACKWARDS( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_backwards__new_transition_42( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_moving_backwards__Debug__B__Ac__stop_moving_backwards( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_backwards__new_transition_43( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_moving_backwards__Debug__A__Ac__stop_moving_backwards( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_backwards__new_transition_44( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_moving_backwards__Debug__A__En__IDLE( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_backwards__new_transition_45_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_moving_backwards__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_backwards__new_transition_46( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_moving_backwards__Debug__B__Ex__MOVING_BACKWARDS( msg );
    save_history( Debug__C__stop_moving_backwards, Debug__C__stop_moving_backwards__Debug__B__Ex__MOVING_BACKWARDS );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_backwards__new_transition_47( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_moving_backwards__Debug__B__Ac__stop_moving_backwards( msg );
    save_history( Debug__C__stop_moving_backwards, Debug__C__stop_moving_backwards__Debug__B__Ac__stop_moving_backwards );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_backwards__new_transition_48( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_moving_backwards__Debug__A__Ac__stop_moving_backwards( msg );
    save_history( Debug__C__stop_moving_backwards, Debug__C__stop_moving_backwards__Debug__A__Ac__stop_moving_backwards );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_backwards__new_transition_49( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_moving_backwards__Debug__A__En__IDLE( msg );
    save_history( Debug__C__stop_moving_backwards, Debug__C__stop_moving_backwards__Debug__A__En__IDLE );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_backwards__new_transition_50( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_moving_backwards__boundary( msg );
    save_history( Debug__C__stop_moving_backwards, Debug__C__stop_moving_backwards__boundary );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_forward__Debug__AC__stop_moving_forward( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_moving_forward__Debug__B__Ac__stop_moving_forward( msg );
    transitionaction_____Debug__C__stop_moving_forward__Debug__AC__stop_moving_forward( msg );
    entryaction_____Debug__C__stop_moving_forward__Debug__A__Ac__stop_moving_forward( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_forward__Debug__En__IDLE( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_moving_forward__Debug__A__Ac__stop_moving_forward( msg );
    transitionaction_____Debug__C__stop_moving_forward__Debug__En__IDLE( msg );
    entryaction_____Debug__C__stop_moving_forward__Debug__A__En__IDLE( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_forward__Debug__Ex__MOVING_FORWARD( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_moving_forward__Debug__B__Ex__MOVING_FORWARD( msg );
    transitionaction_____Debug__C__stop_moving_forward__Debug__Ex__MOVING_FORWARD( msg );
    entryaction_____Debug__C__stop_moving_forward__Debug__B__Ac__stop_moving_forward( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_forward__Debug__end__trans__stop_moving_forward( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_moving_forward__Debug__A__En__IDLE( msg );
    transitionaction_____Debug__C__stop_moving_forward__Debug__end__trans__stop_moving_forward( msg );
    save_history( Debug__C__stop_moving_forward, Debug__C__stop_moving_forward__Debug__A__En__IDLE );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_forward__Debug__init__trans__stop_moving_forward( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__stop_moving_forward__Debug__init__trans__stop_moving_forward( msg );
    entryaction_____Debug__C__stop_moving_forward__Debug__B__Ex__MOVING_FORWARD( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_forward__new_transition_21( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_moving_forward__Debug__B__Ex__MOVING_FORWARD( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_forward__new_transition_22( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_moving_forward__Debug__B__Ac__stop_moving_forward( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_forward__new_transition_23( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_moving_forward__Debug__A__Ac__stop_moving_forward( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_forward__new_transition_24( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_moving_forward__Debug__A__En__IDLE( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_forward__new_transition_25_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_moving_forward__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_forward__new_transition_26( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_moving_forward__Debug__B__Ex__MOVING_FORWARD( msg );
    save_history( Debug__C__stop_moving_forward, Debug__C__stop_moving_forward__Debug__B__Ex__MOVING_FORWARD );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_forward__new_transition_27( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_moving_forward__Debug__B__Ac__stop_moving_forward( msg );
    save_history( Debug__C__stop_moving_forward, Debug__C__stop_moving_forward__Debug__B__Ac__stop_moving_forward );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_forward__new_transition_28( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_moving_forward__Debug__A__Ac__stop_moving_forward( msg );
    save_history( Debug__C__stop_moving_forward, Debug__C__stop_moving_forward__Debug__A__Ac__stop_moving_forward );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_forward__new_transition_29( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_moving_forward__Debug__A__En__IDLE( msg );
    save_history( Debug__C__stop_moving_forward, Debug__C__stop_moving_forward__Debug__A__En__IDLE );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_moving_forward__new_transition_30( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_moving_forward__boundary( msg );
    save_history( Debug__C__stop_moving_forward, Debug__C__stop_moving_forward__boundary );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_left__Debug__AC__stop_turning_left( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_turning_left__Debug__B__Ac__stop_turning_left( msg );
    transitionaction_____Debug__C__stop_turning_left__Debug__AC__stop_turning_left( msg );
    entryaction_____Debug__C__stop_turning_left__Debug__A__Ac__stop_turning_left( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_left__Debug__En__IDLE( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_turning_left__Debug__A__Ac__stop_turning_left( msg );
    transitionaction_____Debug__C__stop_turning_left__Debug__En__IDLE( msg );
    entryaction_____Debug__C__stop_turning_left__Debug__A__En__IDLE( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_left__Debug__Ex__TURNING_LEFT( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_turning_left__Debug__B__Ex__TURNING_LEFT( msg );
    transitionaction_____Debug__C__stop_turning_left__Debug__Ex__TURNING_LEFT( msg );
    entryaction_____Debug__C__stop_turning_left__Debug__B__Ac__stop_turning_left( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_left__Debug__end__trans__stop_turning_left( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_turning_left__Debug__A__En__IDLE( msg );
    transitionaction_____Debug__C__stop_turning_left__Debug__end__trans__stop_turning_left( msg );
    save_history( Debug__C__stop_turning_left, Debug__C__stop_turning_left__Debug__A__En__IDLE );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_left__Debug__init__trans__stop_turning_left( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__stop_turning_left__Debug__init__trans__stop_turning_left( msg );
    entryaction_____Debug__C__stop_turning_left__Debug__B__Ex__TURNING_LEFT( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_left__new_transition_51( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_turning_left__Debug__B__Ex__TURNING_LEFT( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_left__new_transition_52( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_turning_left__Debug__B__Ac__stop_turning_left( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_left__new_transition_53( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_turning_left__Debug__A__Ac__stop_turning_left( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_left__new_transition_54( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_turning_left__Debug__A__En__IDLE( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_left__new_transition_55_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_turning_left__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_left__new_transition_56( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_turning_left__Debug__B__Ex__TURNING_LEFT( msg );
    save_history( Debug__C__stop_turning_left, Debug__C__stop_turning_left__Debug__B__Ex__TURNING_LEFT );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_left__new_transition_57( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_turning_left__Debug__B__Ac__stop_turning_left( msg );
    save_history( Debug__C__stop_turning_left, Debug__C__stop_turning_left__Debug__B__Ac__stop_turning_left );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_left__new_transition_58( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_turning_left__Debug__A__Ac__stop_turning_left( msg );
    save_history( Debug__C__stop_turning_left, Debug__C__stop_turning_left__Debug__A__Ac__stop_turning_left );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_left__new_transition_59( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_turning_left__Debug__A__En__IDLE( msg );
    save_history( Debug__C__stop_turning_left, Debug__C__stop_turning_left__Debug__A__En__IDLE );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_left__new_transition_60( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_turning_left__boundary( msg );
    save_history( Debug__C__stop_turning_left, Debug__C__stop_turning_left__boundary );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_right__Debug__AC__stop_turning_right( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_turning_right__Debug__B__Ac__stop_turning_right( msg );
    transitionaction_____Debug__C__stop_turning_right__Debug__AC__stop_turning_right( msg );
    entryaction_____Debug__C__stop_turning_right__Debug__A__Ac__stop_turning_right( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_right__Debug__En__IDLE( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_turning_right__Debug__A__Ac__stop_turning_right( msg );
    transitionaction_____Debug__C__stop_turning_right__Debug__En__IDLE( msg );
    entryaction_____Debug__C__stop_turning_right__Debug__A__En__IDLE( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_right__Debug__Ex__TURNING_RIGHT( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_turning_right__Debug__B__Ex__TURNING_RIGHT( msg );
    transitionaction_____Debug__C__stop_turning_right__Debug__Ex__TURNING_RIGHT( msg );
    entryaction_____Debug__C__stop_turning_right__Debug__B__Ac__stop_turning_right( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_right__Debug__end__trans__stop_turning_right( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_turning_right__Debug__A__En__IDLE( msg );
    transitionaction_____Debug__C__stop_turning_right__Debug__end__trans__stop_turning_right( msg );
    save_history( Debug__C__stop_turning_right, Debug__C__stop_turning_right__Debug__A__En__IDLE );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_right__Debug__init__trans__stop_turning_right( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__stop_turning_right__Debug__init__trans__stop_turning_right( msg );
    entryaction_____Debug__C__stop_turning_right__Debug__B__Ex__TURNING_RIGHT( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_right__new_transition_11( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_turning_right__Debug__B__Ex__TURNING_RIGHT( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_right__new_transition_12( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_turning_right__Debug__B__Ac__stop_turning_right( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_right__new_transition_13( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_turning_right__Debug__A__Ac__stop_turning_right( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_right__new_transition_14( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_turning_right__Debug__A__En__IDLE( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_right__new_transition_15_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_turning_right__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_right__new_transition_16( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_turning_right__Debug__B__Ex__TURNING_RIGHT( msg );
    save_history( Debug__C__stop_turning_right, Debug__C__stop_turning_right__Debug__B__Ex__TURNING_RIGHT );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_right__new_transition_17( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_turning_right__Debug__B__Ac__stop_turning_right( msg );
    save_history( Debug__C__stop_turning_right, Debug__C__stop_turning_right__Debug__B__Ac__stop_turning_right );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_right__new_transition_18( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_turning_right__Debug__A__Ac__stop_turning_right( msg );
    save_history( Debug__C__stop_turning_right, Debug__C__stop_turning_right__Debug__A__Ac__stop_turning_right );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_right__new_transition_19( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_turning_right__Debug__A__En__IDLE( msg );
    save_history( Debug__C__stop_turning_right, Debug__C__stop_turning_right__Debug__A__En__IDLE );
}

void Capsule_EngineController::actionchain_____Debug__C__stop_turning_right__new_transition_20( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_turning_right__boundary( msg );
    save_history( Debug__C__stop_turning_right, Debug__C__stop_turning_right__boundary );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_left__Debug__AC__turn_left( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turn_left__Debug__B__Ac__turn_left( msg );
    transitionaction_____Debug__C__turn_left__Debug__AC__turn_left( msg );
    entryaction_____Debug__C__turn_left__Debug__A__Ac__turn_left( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_left__Debug__En__TURNING_LEFT( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turn_left__Debug__A__Ac__turn_left( msg );
    transitionaction_____Debug__C__turn_left__Debug__En__TURNING_LEFT( msg );
    entryaction_____Debug__C__turn_left__Debug__A__En__TURNING_LEFT( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_left__Debug__Ex__IDLE( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turn_left__Debug__B__Ex__IDLE( msg );
    transitionaction_____Debug__C__turn_left__Debug__Ex__IDLE( msg );
    entryaction_____Debug__C__turn_left__Debug__B__Ac__turn_left( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_left__Debug__end__trans__turn_left( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turn_left__Debug__A__En__TURNING_LEFT( msg );
    transitionaction_____Debug__C__turn_left__Debug__end__trans__turn_left( msg );
    save_history( Debug__C__turn_left, Debug__C__turn_left__Debug__A__En__TURNING_LEFT );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_left__Debug__init__trans__turn_left( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__turn_left__Debug__init__trans__turn_left( msg );
    entryaction_____Debug__C__turn_left__Debug__B__Ex__IDLE( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_left__new_transition_1( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__turn_left__Debug__B__Ex__IDLE( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_left__new_transition_10( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turn_left__boundary( msg );
    save_history( Debug__C__turn_left, Debug__C__turn_left__boundary );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_left__new_transition_2( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__turn_left__Debug__B__Ac__turn_left( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_left__new_transition_3( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__turn_left__Debug__A__Ac__turn_left( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_left__new_transition_4( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__turn_left__Debug__A__En__TURNING_LEFT( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_left__new_transition_5_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__turn_left__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_left__new_transition_6( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turn_left__Debug__B__Ex__IDLE( msg );
    save_history( Debug__C__turn_left, Debug__C__turn_left__Debug__B__Ex__IDLE );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_left__new_transition_7( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turn_left__Debug__B__Ac__turn_left( msg );
    save_history( Debug__C__turn_left, Debug__C__turn_left__Debug__B__Ac__turn_left );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_left__new_transition_8( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turn_left__Debug__A__Ac__turn_left( msg );
    save_history( Debug__C__turn_left, Debug__C__turn_left__Debug__A__Ac__turn_left );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_left__new_transition_9( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turn_left__Debug__A__En__TURNING_LEFT( msg );
    save_history( Debug__C__turn_left, Debug__C__turn_left__Debug__A__En__TURNING_LEFT );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_right__Debug__AC__turn_right( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turn_right__Debug__B__Ac__turn_right( msg );
    transitionaction_____Debug__C__turn_right__Debug__AC__turn_right( msg );
    entryaction_____Debug__C__turn_right__Debug__A__Ac__turn_right( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_right__Debug__En__TURNING_RIGHT( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turn_right__Debug__A__Ac__turn_right( msg );
    transitionaction_____Debug__C__turn_right__Debug__En__TURNING_RIGHT( msg );
    entryaction_____Debug__C__turn_right__Debug__A__En__TURNING_RIGHT( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_right__Debug__Ex__IDLE( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turn_right__Debug__B__Ex__IDLE( msg );
    transitionaction_____Debug__C__turn_right__Debug__Ex__IDLE( msg );
    entryaction_____Debug__C__turn_right__Debug__B__Ac__turn_right( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_right__Debug__end__trans__turn_right( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turn_right__Debug__A__En__TURNING_RIGHT( msg );
    transitionaction_____Debug__C__turn_right__Debug__end__trans__turn_right( msg );
    save_history( Debug__C__turn_right, Debug__C__turn_right__Debug__A__En__TURNING_RIGHT );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_right__Debug__init__trans__turn_right( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__turn_right__Debug__init__trans__turn_right( msg );
    entryaction_____Debug__C__turn_right__Debug__B__Ex__IDLE( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_right__new_transition_69( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__turn_right__Debug__B__Ex__IDLE( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_right__new_transition_70( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__turn_right__Debug__B__Ac__turn_right( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_right__new_transition_71( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__turn_right__Debug__A__Ac__turn_right( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_right__new_transition_72( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__turn_right__Debug__A__En__TURNING_RIGHT( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_right__new_transition_73_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__turn_right__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_right__new_transition_74( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turn_right__Debug__B__Ex__IDLE( msg );
    save_history( Debug__C__turn_right, Debug__C__turn_right__Debug__B__Ex__IDLE );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_right__new_transition_75( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turn_right__Debug__B__Ac__turn_right( msg );
    save_history( Debug__C__turn_right, Debug__C__turn_right__Debug__B__Ac__turn_right );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_right__new_transition_76( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turn_right__Debug__A__Ac__turn_right( msg );
    save_history( Debug__C__turn_right, Debug__C__turn_right__Debug__A__Ac__turn_right );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_right__new_transition_77( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turn_right__Debug__A__En__TURNING_RIGHT( msg );
    save_history( Debug__C__turn_right, Debug__C__turn_right__Debug__A__En__TURNING_RIGHT );
}

void Capsule_EngineController::actionchain_____Debug__C__turn_right__new_transition_78( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turn_right__boundary( msg );
    save_history( Debug__C__turn_right, Debug__C__turn_right__boundary );
}

void Capsule_EngineController::actionchain_____Debug__InitDebug( const UMLRTMessage * msg )
{
    transitionaction_____Debug__InitDebug( msg );
    entryaction_____Debug__InitState( msg );
}

void Capsule_EngineController::actionchain_____Debug__init( const UMLRTMessage * msg )
{
    exitaction_____Debug__InitState( msg );
    transitionaction_____Debug__init( msg );
}

void Capsule_EngineController::actionchain_____Debug__init__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__boundary( msg );
    transitionaction_____Debug__init__E( msg );
    entryaction_____IDLE( msg );
}

void Capsule_EngineController::actionchain_____Debug__init__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__init__S( msg );
    entryaction_____Debug__C__init__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__init__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__boundary( msg );
    transitionaction_____Debug__init__dbg( msg );
    entryaction_____Debug__C__init__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__move_backwards( const UMLRTMessage * msg )
{
    exitaction_____IDLE( msg );
    transitionaction_____Debug__move_backwards( msg );
}

void Capsule_EngineController::actionchain_____Debug__move_backwards__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__move_backwards__boundary( msg );
    transitionaction_____Debug__move_backwards__E( msg );
    entryaction_____MOVING_BACKWARDS( msg );
}

void Capsule_EngineController::actionchain_____Debug__move_backwards__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__move_backwards__S( msg );
    entryaction_____Debug__C__move_backwards__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__move_backwards__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__move_backwards__boundary( msg );
    transitionaction_____Debug__move_backwards__dbg( msg );
    entryaction_____Debug__C__move_backwards__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__move_forward( const UMLRTMessage * msg )
{
    exitaction_____IDLE( msg );
    transitionaction_____Debug__move_forward( msg );
}

void Capsule_EngineController::actionchain_____Debug__move_forward__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__move_forward__boundary( msg );
    transitionaction_____Debug__move_forward__E( msg );
    entryaction_____MOVING_FORWARD( msg );
}

void Capsule_EngineController::actionchain_____Debug__move_forward__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__move_forward__S( msg );
    entryaction_____Debug__C__move_forward__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__move_forward__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__move_forward__boundary( msg );
    transitionaction_____Debug__move_forward__dbg( msg );
    entryaction_____Debug__C__move_forward__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__stop_moving_backwards( const UMLRTMessage * msg )
{
    exitaction_____MOVING_BACKWARDS( msg );
    transitionaction_____Debug__stop_moving_backwards( msg );
}

void Capsule_EngineController::actionchain_____Debug__stop_moving_backwards__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_moving_backwards__boundary( msg );
    transitionaction_____Debug__stop_moving_backwards__E( msg );
    entryaction_____IDLE( msg );
}

void Capsule_EngineController::actionchain_____Debug__stop_moving_backwards__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__stop_moving_backwards__S( msg );
    entryaction_____Debug__C__stop_moving_backwards__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__stop_moving_backwards__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_moving_backwards__boundary( msg );
    transitionaction_____Debug__stop_moving_backwards__dbg( msg );
    entryaction_____Debug__C__stop_moving_backwards__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__stop_moving_forward( const UMLRTMessage * msg )
{
    exitaction_____MOVING_FORWARD( msg );
    transitionaction_____Debug__stop_moving_forward( msg );
}

void Capsule_EngineController::actionchain_____Debug__stop_moving_forward__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_moving_forward__boundary( msg );
    transitionaction_____Debug__stop_moving_forward__E( msg );
    entryaction_____IDLE( msg );
}

void Capsule_EngineController::actionchain_____Debug__stop_moving_forward__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__stop_moving_forward__S( msg );
    entryaction_____Debug__C__stop_moving_forward__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__stop_moving_forward__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_moving_forward__boundary( msg );
    transitionaction_____Debug__stop_moving_forward__dbg( msg );
    entryaction_____Debug__C__stop_moving_forward__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__stop_turning_left( const UMLRTMessage * msg )
{
    exitaction_____TURNING_LEFT( msg );
    transitionaction_____Debug__stop_turning_left( msg );
}

void Capsule_EngineController::actionchain_____Debug__stop_turning_left__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_turning_left__boundary( msg );
    transitionaction_____Debug__stop_turning_left__E( msg );
    entryaction_____IDLE( msg );
}

void Capsule_EngineController::actionchain_____Debug__stop_turning_left__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__stop_turning_left__S( msg );
    entryaction_____Debug__C__stop_turning_left__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__stop_turning_left__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_turning_left__boundary( msg );
    transitionaction_____Debug__stop_turning_left__dbg( msg );
    entryaction_____Debug__C__stop_turning_left__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__stop_turning_right( const UMLRTMessage * msg )
{
    exitaction_____TURNING_RIGHT( msg );
    transitionaction_____Debug__stop_turning_right( msg );
}

void Capsule_EngineController::actionchain_____Debug__stop_turning_right__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_turning_right__boundary( msg );
    transitionaction_____Debug__stop_turning_right__E( msg );
    entryaction_____IDLE( msg );
}

void Capsule_EngineController::actionchain_____Debug__stop_turning_right__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__stop_turning_right__S( msg );
    entryaction_____Debug__C__stop_turning_right__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__stop_turning_right__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_turning_right__boundary( msg );
    transitionaction_____Debug__stop_turning_right__dbg( msg );
    entryaction_____Debug__C__stop_turning_right__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__turn_left( const UMLRTMessage * msg )
{
    exitaction_____IDLE( msg );
    transitionaction_____Debug__turn_left( msg );
}

void Capsule_EngineController::actionchain_____Debug__turn_left__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turn_left__boundary( msg );
    transitionaction_____Debug__turn_left__E( msg );
    entryaction_____TURNING_LEFT( msg );
}

void Capsule_EngineController::actionchain_____Debug__turn_left__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__turn_left__S( msg );
    entryaction_____Debug__C__turn_left__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__turn_left__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turn_left__boundary( msg );
    transitionaction_____Debug__turn_left__dbg( msg );
    entryaction_____Debug__C__turn_left__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__turn_right( const UMLRTMessage * msg )
{
    exitaction_____IDLE( msg );
    transitionaction_____Debug__turn_right( msg );
}

void Capsule_EngineController::actionchain_____Debug__turn_right__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turn_right__boundary( msg );
    transitionaction_____Debug__turn_right__E( msg );
    entryaction_____TURNING_RIGHT( msg );
}

void Capsule_EngineController::actionchain_____Debug__turn_right__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__turn_right__S( msg );
    entryaction_____Debug__C__turn_right__boundary( msg );
}

void Capsule_EngineController::actionchain_____Debug__turn_right__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turn_right__boundary( msg );
    transitionaction_____Debug__turn_right__dbg( msg );
    entryaction_____Debug__C__turn_right__boundary( msg );
}

void Capsule_EngineController::actionchain_____init( const UMLRTMessage * msg )
{
    transitionaction_____init( msg );
    entryaction_____IDLE( msg );
}

void Capsule_EngineController::actionchain_____move_backwards( const UMLRTMessage * msg )
{
    transitionaction_____move_backwards( msg );
    entryaction_____MOVING_BACKWARDS( msg );
}

void Capsule_EngineController::actionchain_____move_forward( const UMLRTMessage * msg )
{
    transitionaction_____move_forward( msg );
    entryaction_____MOVING_FORWARD( msg );
}

void Capsule_EngineController::actionchain_____stop_moving_backwards( const UMLRTMessage * msg )
{
    transitionaction_____stop_moving_backwards( msg );
    entryaction_____IDLE( msg );
}

void Capsule_EngineController::actionchain_____stop_moving_forward( const UMLRTMessage * msg )
{
    transitionaction_____stop_moving_forward( msg );
    entryaction_____IDLE( msg );
}

void Capsule_EngineController::actionchain_____stop_turning_left( const UMLRTMessage * msg )
{
    transitionaction_____stop_turning_left( msg );
    entryaction_____IDLE( msg );
}

void Capsule_EngineController::actionchain_____stop_turning_right( const UMLRTMessage * msg )
{
    transitionaction_____stop_turning_right( msg );
    entryaction_____IDLE( msg );
}

void Capsule_EngineController::actionchain_____turn_left( const UMLRTMessage * msg )
{
    transitionaction_____turn_left( msg );
    entryaction_____TURNING_LEFT( msg );
}

void Capsule_EngineController::actionchain_____turn_right( const UMLRTMessage * msg )
{
    transitionaction_____turn_right( msg );
    entryaction_____TURNING_RIGHT( msg );
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__init__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__init__Debug__init__trans__init( msg );
    return Debug__C__init__Debug__B__Ac__init;
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__init__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__init__E( msg );
    return IDLE;
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__init__new_exitpoint_7( const UMLRTMessage * msg )
{
    actionchain_____Debug__init__dbg( msg );
    return choice_____Debug__C__init__deephistory( msg );
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__move_backwards__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__move_backwards__Debug__init__trans__move_backwards( msg );
    return Debug__C__move_backwards__Debug__B__Ex__IDLE;
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__move_backwards__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__move_backwards__E( msg );
    return MOVING_BACKWARDS;
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__move_backwards__new_exitpoint_9( const UMLRTMessage * msg )
{
    actionchain_____Debug__move_backwards__dbg( msg );
    return choice_____Debug__C__move_backwards__deephistory( msg );
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__move_forward__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__move_forward__Debug__init__trans__move_forward( msg );
    return Debug__C__move_forward__Debug__B__Ex__IDLE;
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__move_forward__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__move_forward__E( msg );
    return MOVING_FORWARD;
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__move_forward__new_exitpoint_4( const UMLRTMessage * msg )
{
    actionchain_____Debug__move_forward__dbg( msg );
    return choice_____Debug__C__move_forward__deephistory( msg );
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__stop_moving_backwards__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__stop_moving_backwards__Debug__init__trans__stop_moving_backwards( msg );
    return Debug__C__stop_moving_backwards__Debug__B__Ex__MOVING_BACKWARDS;
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__stop_moving_backwards__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__stop_moving_backwards__E( msg );
    return IDLE;
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__stop_moving_backwards__new_exitpoint_5( const UMLRTMessage * msg )
{
    actionchain_____Debug__stop_moving_backwards__dbg( msg );
    return choice_____Debug__C__stop_moving_backwards__deephistory( msg );
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__stop_moving_forward__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__stop_moving_forward__Debug__init__trans__stop_moving_forward( msg );
    return Debug__C__stop_moving_forward__Debug__B__Ex__MOVING_FORWARD;
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__stop_moving_forward__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__stop_moving_forward__E( msg );
    return IDLE;
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__stop_moving_forward__new_exitpoint_3( const UMLRTMessage * msg )
{
    actionchain_____Debug__stop_moving_forward__dbg( msg );
    return choice_____Debug__C__stop_moving_forward__deephistory( msg );
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__stop_turning_left__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__stop_turning_left__Debug__init__trans__stop_turning_left( msg );
    return Debug__C__stop_turning_left__Debug__B__Ex__TURNING_LEFT;
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__stop_turning_left__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__stop_turning_left__E( msg );
    return IDLE;
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__stop_turning_left__new_exitpoint_6( const UMLRTMessage * msg )
{
    actionchain_____Debug__stop_turning_left__dbg( msg );
    return choice_____Debug__C__stop_turning_left__deephistory( msg );
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__stop_turning_right__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__stop_turning_right__Debug__init__trans__stop_turning_right( msg );
    return Debug__C__stop_turning_right__Debug__B__Ex__TURNING_RIGHT;
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__stop_turning_right__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__stop_turning_right__E( msg );
    return IDLE;
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__stop_turning_right__new_exitpoint_2( const UMLRTMessage * msg )
{
    actionchain_____Debug__stop_turning_right__dbg( msg );
    return choice_____Debug__C__stop_turning_right__deephistory( msg );
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__turn_left__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__turn_left__Debug__init__trans__turn_left( msg );
    return Debug__C__turn_left__Debug__B__Ex__IDLE;
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__turn_left__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__turn_left__E( msg );
    return TURNING_LEFT;
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__turn_left__new_exitpoint_1( const UMLRTMessage * msg )
{
    actionchain_____Debug__turn_left__dbg( msg );
    return choice_____Debug__C__turn_left__deephistory( msg );
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__turn_right__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__turn_right__Debug__init__trans__turn_right( msg );
    return Debug__C__turn_right__Debug__B__Ex__IDLE;
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__turn_right__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__turn_right__E( msg );
    return TURNING_RIGHT;
}

Capsule_EngineController::State Capsule_EngineController::junction_____Debug__C__turn_right__new_exitpoint_8( const UMLRTMessage * msg )
{
    actionchain_____Debug__turn_right__dbg( msg );
    return choice_____Debug__C__turn_right__deephistory( msg );
}

Capsule_EngineController::State Capsule_EngineController::choice_____Debug__C__init__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__init, Debug__C__init__Debug__B__Ac__init ) )
    {
        actionchain_____Debug__C__init__new_transition_61( msg );
        return Debug__C__init__Debug__B__Ac__init;
    }
    else if( check_history( Debug__C__init, Debug__C__init__Debug__A__Ac__init ) )
    {
        actionchain_____Debug__C__init__new_transition_62( msg );
        return Debug__C__init__Debug__A__Ac__init;
    }
    else if( check_history( Debug__C__init, Debug__C__init__Debug__A__En__init ) )
    {
        actionchain_____Debug__C__init__new_transition_63( msg );
        return Debug__C__init__Debug__A__En__init;
    }
    else if( check_history( Debug__C__init, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__init__new_transition_64_to_boundary( msg );
        return Debug__C__init__boundary;
    }
    return currentState;
}

Capsule_EngineController::State Capsule_EngineController::choice_____Debug__C__move_backwards__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__move_backwards, Debug__C__move_backwards__Debug__B__Ex__IDLE ) )
    {
        actionchain_____Debug__C__move_backwards__new_transition_79( msg );
        return Debug__C__move_backwards__Debug__B__Ex__IDLE;
    }
    else if( check_history( Debug__C__move_backwards, Debug__C__move_backwards__Debug__B__Ac__move_backwards ) )
    {
        actionchain_____Debug__C__move_backwards__new_transition_80( msg );
        return Debug__C__move_backwards__Debug__B__Ac__move_backwards;
    }
    else if( check_history( Debug__C__move_backwards, Debug__C__move_backwards__Debug__A__Ac__move_backwards ) )
    {
        actionchain_____Debug__C__move_backwards__new_transition_81( msg );
        return Debug__C__move_backwards__Debug__A__Ac__move_backwards;
    }
    else if( check_history( Debug__C__move_backwards, Debug__C__move_backwards__Debug__A__En__MOVING_BACKWARDS ) )
    {
        actionchain_____Debug__C__move_backwards__new_transition_82( msg );
        return Debug__C__move_backwards__Debug__A__En__MOVING_BACKWARDS;
    }
    else if( check_history( Debug__C__move_backwards, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__move_backwards__new_transition_83_to_boundary( msg );
        return Debug__C__move_backwards__boundary;
    }
    return currentState;
}

Capsule_EngineController::State Capsule_EngineController::choice_____Debug__C__move_forward__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__move_forward, Debug__C__move_forward__Debug__B__Ex__IDLE ) )
    {
        actionchain_____Debug__C__move_forward__new_transition_31( msg );
        return Debug__C__move_forward__Debug__B__Ex__IDLE;
    }
    else if( check_history( Debug__C__move_forward, Debug__C__move_forward__Debug__B__Ac__move_forward ) )
    {
        actionchain_____Debug__C__move_forward__new_transition_32( msg );
        return Debug__C__move_forward__Debug__B__Ac__move_forward;
    }
    else if( check_history( Debug__C__move_forward, Debug__C__move_forward__Debug__A__Ac__move_forward ) )
    {
        actionchain_____Debug__C__move_forward__new_transition_33( msg );
        return Debug__C__move_forward__Debug__A__Ac__move_forward;
    }
    else if( check_history( Debug__C__move_forward, Debug__C__move_forward__Debug__A__En__MOVING_FORWARD ) )
    {
        actionchain_____Debug__C__move_forward__new_transition_34( msg );
        return Debug__C__move_forward__Debug__A__En__MOVING_FORWARD;
    }
    else if( check_history( Debug__C__move_forward, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__move_forward__new_transition_35_to_boundary( msg );
        return Debug__C__move_forward__boundary;
    }
    return currentState;
}

Capsule_EngineController::State Capsule_EngineController::choice_____Debug__C__stop_moving_backwards__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__stop_moving_backwards, Debug__C__stop_moving_backwards__Debug__B__Ex__MOVING_BACKWARDS ) )
    {
        actionchain_____Debug__C__stop_moving_backwards__new_transition_41( msg );
        return Debug__C__stop_moving_backwards__Debug__B__Ex__MOVING_BACKWARDS;
    }
    else if( check_history( Debug__C__stop_moving_backwards, Debug__C__stop_moving_backwards__Debug__B__Ac__stop_moving_backwards ) )
    {
        actionchain_____Debug__C__stop_moving_backwards__new_transition_42( msg );
        return Debug__C__stop_moving_backwards__Debug__B__Ac__stop_moving_backwards;
    }
    else if( check_history( Debug__C__stop_moving_backwards, Debug__C__stop_moving_backwards__Debug__A__Ac__stop_moving_backwards ) )
    {
        actionchain_____Debug__C__stop_moving_backwards__new_transition_43( msg );
        return Debug__C__stop_moving_backwards__Debug__A__Ac__stop_moving_backwards;
    }
    else if( check_history( Debug__C__stop_moving_backwards, Debug__C__stop_moving_backwards__Debug__A__En__IDLE ) )
    {
        actionchain_____Debug__C__stop_moving_backwards__new_transition_44( msg );
        return Debug__C__stop_moving_backwards__Debug__A__En__IDLE;
    }
    else if( check_history( Debug__C__stop_moving_backwards, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__stop_moving_backwards__new_transition_45_to_boundary( msg );
        return Debug__C__stop_moving_backwards__boundary;
    }
    return currentState;
}

Capsule_EngineController::State Capsule_EngineController::choice_____Debug__C__stop_moving_forward__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__stop_moving_forward, Debug__C__stop_moving_forward__Debug__B__Ex__MOVING_FORWARD ) )
    {
        actionchain_____Debug__C__stop_moving_forward__new_transition_21( msg );
        return Debug__C__stop_moving_forward__Debug__B__Ex__MOVING_FORWARD;
    }
    else if( check_history( Debug__C__stop_moving_forward, Debug__C__stop_moving_forward__Debug__B__Ac__stop_moving_forward ) )
    {
        actionchain_____Debug__C__stop_moving_forward__new_transition_22( msg );
        return Debug__C__stop_moving_forward__Debug__B__Ac__stop_moving_forward;
    }
    else if( check_history( Debug__C__stop_moving_forward, Debug__C__stop_moving_forward__Debug__A__Ac__stop_moving_forward ) )
    {
        actionchain_____Debug__C__stop_moving_forward__new_transition_23( msg );
        return Debug__C__stop_moving_forward__Debug__A__Ac__stop_moving_forward;
    }
    else if( check_history( Debug__C__stop_moving_forward, Debug__C__stop_moving_forward__Debug__A__En__IDLE ) )
    {
        actionchain_____Debug__C__stop_moving_forward__new_transition_24( msg );
        return Debug__C__stop_moving_forward__Debug__A__En__IDLE;
    }
    else if( check_history( Debug__C__stop_moving_forward, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__stop_moving_forward__new_transition_25_to_boundary( msg );
        return Debug__C__stop_moving_forward__boundary;
    }
    return currentState;
}

Capsule_EngineController::State Capsule_EngineController::choice_____Debug__C__stop_turning_left__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__stop_turning_left, Debug__C__stop_turning_left__Debug__B__Ex__TURNING_LEFT ) )
    {
        actionchain_____Debug__C__stop_turning_left__new_transition_51( msg );
        return Debug__C__stop_turning_left__Debug__B__Ex__TURNING_LEFT;
    }
    else if( check_history( Debug__C__stop_turning_left, Debug__C__stop_turning_left__Debug__B__Ac__stop_turning_left ) )
    {
        actionchain_____Debug__C__stop_turning_left__new_transition_52( msg );
        return Debug__C__stop_turning_left__Debug__B__Ac__stop_turning_left;
    }
    else if( check_history( Debug__C__stop_turning_left, Debug__C__stop_turning_left__Debug__A__Ac__stop_turning_left ) )
    {
        actionchain_____Debug__C__stop_turning_left__new_transition_53( msg );
        return Debug__C__stop_turning_left__Debug__A__Ac__stop_turning_left;
    }
    else if( check_history( Debug__C__stop_turning_left, Debug__C__stop_turning_left__Debug__A__En__IDLE ) )
    {
        actionchain_____Debug__C__stop_turning_left__new_transition_54( msg );
        return Debug__C__stop_turning_left__Debug__A__En__IDLE;
    }
    else if( check_history( Debug__C__stop_turning_left, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__stop_turning_left__new_transition_55_to_boundary( msg );
        return Debug__C__stop_turning_left__boundary;
    }
    return currentState;
}

Capsule_EngineController::State Capsule_EngineController::choice_____Debug__C__stop_turning_right__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__stop_turning_right, Debug__C__stop_turning_right__Debug__B__Ex__TURNING_RIGHT ) )
    {
        actionchain_____Debug__C__stop_turning_right__new_transition_11( msg );
        return Debug__C__stop_turning_right__Debug__B__Ex__TURNING_RIGHT;
    }
    else if( check_history( Debug__C__stop_turning_right, Debug__C__stop_turning_right__Debug__B__Ac__stop_turning_right ) )
    {
        actionchain_____Debug__C__stop_turning_right__new_transition_12( msg );
        return Debug__C__stop_turning_right__Debug__B__Ac__stop_turning_right;
    }
    else if( check_history( Debug__C__stop_turning_right, Debug__C__stop_turning_right__Debug__A__Ac__stop_turning_right ) )
    {
        actionchain_____Debug__C__stop_turning_right__new_transition_13( msg );
        return Debug__C__stop_turning_right__Debug__A__Ac__stop_turning_right;
    }
    else if( check_history( Debug__C__stop_turning_right, Debug__C__stop_turning_right__Debug__A__En__IDLE ) )
    {
        actionchain_____Debug__C__stop_turning_right__new_transition_14( msg );
        return Debug__C__stop_turning_right__Debug__A__En__IDLE;
    }
    else if( check_history( Debug__C__stop_turning_right, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__stop_turning_right__new_transition_15_to_boundary( msg );
        return Debug__C__stop_turning_right__boundary;
    }
    return currentState;
}

Capsule_EngineController::State Capsule_EngineController::choice_____Debug__C__turn_left__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__turn_left, Debug__C__turn_left__Debug__B__Ex__IDLE ) )
    {
        actionchain_____Debug__C__turn_left__new_transition_1( msg );
        return Debug__C__turn_left__Debug__B__Ex__IDLE;
    }
    else if( check_history( Debug__C__turn_left, Debug__C__turn_left__Debug__B__Ac__turn_left ) )
    {
        actionchain_____Debug__C__turn_left__new_transition_2( msg );
        return Debug__C__turn_left__Debug__B__Ac__turn_left;
    }
    else if( check_history( Debug__C__turn_left, Debug__C__turn_left__Debug__A__Ac__turn_left ) )
    {
        actionchain_____Debug__C__turn_left__new_transition_3( msg );
        return Debug__C__turn_left__Debug__A__Ac__turn_left;
    }
    else if( check_history( Debug__C__turn_left, Debug__C__turn_left__Debug__A__En__TURNING_LEFT ) )
    {
        actionchain_____Debug__C__turn_left__new_transition_4( msg );
        return Debug__C__turn_left__Debug__A__En__TURNING_LEFT;
    }
    else if( check_history( Debug__C__turn_left, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__turn_left__new_transition_5_to_boundary( msg );
        return Debug__C__turn_left__boundary;
    }
    return currentState;
}

Capsule_EngineController::State Capsule_EngineController::choice_____Debug__C__turn_right__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__turn_right, Debug__C__turn_right__Debug__B__Ex__IDLE ) )
    {
        actionchain_____Debug__C__turn_right__new_transition_69( msg );
        return Debug__C__turn_right__Debug__B__Ex__IDLE;
    }
    else if( check_history( Debug__C__turn_right, Debug__C__turn_right__Debug__B__Ac__turn_right ) )
    {
        actionchain_____Debug__C__turn_right__new_transition_70( msg );
        return Debug__C__turn_right__Debug__B__Ac__turn_right;
    }
    else if( check_history( Debug__C__turn_right, Debug__C__turn_right__Debug__A__Ac__turn_right ) )
    {
        actionchain_____Debug__C__turn_right__new_transition_71( msg );
        return Debug__C__turn_right__Debug__A__Ac__turn_right;
    }
    else if( check_history( Debug__C__turn_right, Debug__C__turn_right__Debug__A__En__TURNING_RIGHT ) )
    {
        actionchain_____Debug__C__turn_right__new_transition_72( msg );
        return Debug__C__turn_right__Debug__A__En__TURNING_RIGHT;
    }
    else if( check_history( Debug__C__turn_right, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__turn_right__new_transition_73_to_boundary( msg );
        return Debug__C__turn_right__boundary;
    }
    return currentState;
}

Capsule_EngineController::State Capsule_EngineController::choice_____Debug__Path__init( const UMLRTMessage * msg )
{
    if( action_____Debug__init__S__Debug__Guardinit( msg ) )
    {
        actionchain_____Debug__init__S( msg );
        return junction_____Debug__C__init__en( msg );
    }
    else
    {
        actionchain_____init( msg );
        return IDLE;
    }
    return currentState;
}

Capsule_EngineController::State Capsule_EngineController::choice_____Debug__Path__move_backwards( const UMLRTMessage * msg )
{
    if( action_____Debug__move_backwards__S__Debug__Guardmove_backwards( msg ) )
    {
        actionchain_____Debug__move_backwards__S( msg );
        return junction_____Debug__C__move_backwards__en( msg );
    }
    else
    {
        actionchain_____move_backwards( msg );
        return MOVING_BACKWARDS;
    }
    return currentState;
}

Capsule_EngineController::State Capsule_EngineController::choice_____Debug__Path__move_forward( const UMLRTMessage * msg )
{
    if( action_____Debug__move_forward__S__Debug__Guardmove_forward( msg ) )
    {
        actionchain_____Debug__move_forward__S( msg );
        return junction_____Debug__C__move_forward__en( msg );
    }
    else
    {
        actionchain_____move_forward( msg );
        return MOVING_FORWARD;
    }
    return currentState;
}

Capsule_EngineController::State Capsule_EngineController::choice_____Debug__Path__stop_moving_backwards( const UMLRTMessage * msg )
{
    if( action_____Debug__stop_moving_backwards__S__Debug__Guardstop_moving_backwards( msg ) )
    {
        actionchain_____Debug__stop_moving_backwards__S( msg );
        return junction_____Debug__C__stop_moving_backwards__en( msg );
    }
    else
    {
        actionchain_____stop_moving_backwards( msg );
        return IDLE;
    }
    return currentState;
}

Capsule_EngineController::State Capsule_EngineController::choice_____Debug__Path__stop_moving_forward( const UMLRTMessage * msg )
{
    if( action_____Debug__stop_moving_forward__S__Debug__Guardstop_moving_forward( msg ) )
    {
        actionchain_____Debug__stop_moving_forward__S( msg );
        return junction_____Debug__C__stop_moving_forward__en( msg );
    }
    else
    {
        actionchain_____stop_moving_forward( msg );
        return IDLE;
    }
    return currentState;
}

Capsule_EngineController::State Capsule_EngineController::choice_____Debug__Path__stop_turning_left( const UMLRTMessage * msg )
{
    if( action_____Debug__stop_turning_left__S__Debug__Guardstop_turning_left( msg ) )
    {
        actionchain_____Debug__stop_turning_left__S( msg );
        return junction_____Debug__C__stop_turning_left__en( msg );
    }
    else
    {
        actionchain_____stop_turning_left( msg );
        return IDLE;
    }
    return currentState;
}

Capsule_EngineController::State Capsule_EngineController::choice_____Debug__Path__stop_turning_right( const UMLRTMessage * msg )
{
    if( action_____Debug__stop_turning_right__S__Debug__Guardstop_turning_right( msg ) )
    {
        actionchain_____Debug__stop_turning_right__S( msg );
        return junction_____Debug__C__stop_turning_right__en( msg );
    }
    else
    {
        actionchain_____stop_turning_right( msg );
        return IDLE;
    }
    return currentState;
}

Capsule_EngineController::State Capsule_EngineController::choice_____Debug__Path__turn_left( const UMLRTMessage * msg )
{
    if( action_____Debug__turn_left__S__Debug__Guardturn_left( msg ) )
    {
        actionchain_____Debug__turn_left__S( msg );
        return junction_____Debug__C__turn_left__en( msg );
    }
    else
    {
        actionchain_____turn_left( msg );
        return TURNING_LEFT;
    }
    return currentState;
}

Capsule_EngineController::State Capsule_EngineController::choice_____Debug__Path__turn_right( const UMLRTMessage * msg )
{
    if( action_____Debug__turn_right__S__Debug__Guardturn_right( msg ) )
    {
        actionchain_____Debug__turn_right__S( msg );
        return junction_____Debug__C__turn_right__en( msg );
    }
    else
    {
        actionchain_____turn_right( msg );
        return TURNING_RIGHT;
    }
    return currentState;
}

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__init__Debug__En__IDLE( msg );
            return Debug__C__init__Debug__A__En__init;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__init__new_transition_66( msg );
            return junction_____Debug__C__init__new_exitpoint_7( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__init__Debug__end__trans__init( msg );
            return junction_____Debug__C__init__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__init__new_transition_67( msg );
            return junction_____Debug__C__init__new_exitpoint_7( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__init__Debug__Ac__init( msg );
            return Debug__C__init__Debug__A__Ac__init;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__init__new_transition_65( msg );
            return junction_____Debug__C__init__new_exitpoint_7( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__init__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__init__new_transition_68( msg );
            return junction_____Debug__C__init__new_exitpoint_7( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__move_backwards__Debug__A__Ac__move_backwards( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__move_backwards__Debug__En__MOVING_BACKWARDS( msg );
            return Debug__C__move_backwards__Debug__A__En__MOVING_BACKWARDS;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__move_backwards__new_transition_86( msg );
            return junction_____Debug__C__move_backwards__new_exitpoint_9( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__move_backwards__Debug__A__En__MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__move_backwards__Debug__end__trans__move_backwards( msg );
            return junction_____Debug__C__move_backwards__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__move_backwards__new_transition_87( msg );
            return junction_____Debug__C__move_backwards__new_exitpoint_9( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__move_backwards__Debug__B__Ac__move_backwards( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__move_backwards__Debug__AC__move_backwards( msg );
            return Debug__C__move_backwards__Debug__A__Ac__move_backwards;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__move_backwards__new_transition_85( msg );
            return junction_____Debug__C__move_backwards__new_exitpoint_9( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__move_backwards__Debug__B__Ex__IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__move_backwards__Debug__Ex__IDLE( msg );
            return Debug__C__move_backwards__Debug__B__Ac__move_backwards;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__move_backwards__new_transition_84( msg );
            return junction_____Debug__C__move_backwards__new_exitpoint_9( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__move_backwards__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__move_backwards__new_transition_88( msg );
            return junction_____Debug__C__move_backwards__new_exitpoint_9( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__move_forward__Debug__A__Ac__move_forward( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__move_forward__Debug__En__MOVING_FORWARD( msg );
            return Debug__C__move_forward__Debug__A__En__MOVING_FORWARD;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__move_forward__new_transition_38( msg );
            return junction_____Debug__C__move_forward__new_exitpoint_4( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__move_forward__Debug__A__En__MOVING_FORWARD( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__move_forward__Debug__end__trans__move_forward( msg );
            return junction_____Debug__C__move_forward__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__move_forward__new_transition_39( msg );
            return junction_____Debug__C__move_forward__new_exitpoint_4( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__move_forward__Debug__B__Ac__move_forward( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__move_forward__Debug__AC__move_forward( msg );
            return Debug__C__move_forward__Debug__A__Ac__move_forward;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__move_forward__new_transition_37( msg );
            return junction_____Debug__C__move_forward__new_exitpoint_4( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__move_forward__Debug__B__Ex__IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__move_forward__Debug__Ex__IDLE( msg );
            return Debug__C__move_forward__Debug__B__Ac__move_forward;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__move_forward__new_transition_36( msg );
            return junction_____Debug__C__move_forward__new_exitpoint_4( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__move_forward__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__move_forward__new_transition_40( msg );
            return junction_____Debug__C__move_forward__new_exitpoint_4( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__stop_moving_backwards__Debug__A__Ac__stop_moving_backwards( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stop_moving_backwards__Debug__En__IDLE( msg );
            return Debug__C__stop_moving_backwards__Debug__A__En__IDLE;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_moving_backwards__new_transition_48( msg );
            return junction_____Debug__C__stop_moving_backwards__new_exitpoint_5( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__stop_moving_backwards__Debug__A__En__IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stop_moving_backwards__Debug__end__trans__stop_moving_backwards( msg );
            return junction_____Debug__C__stop_moving_backwards__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_moving_backwards__new_transition_49( msg );
            return junction_____Debug__C__stop_moving_backwards__new_exitpoint_5( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__stop_moving_backwards__Debug__B__Ac__stop_moving_backwards( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stop_moving_backwards__Debug__AC__stop_moving_backwards( msg );
            return Debug__C__stop_moving_backwards__Debug__A__Ac__stop_moving_backwards;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_moving_backwards__new_transition_47( msg );
            return junction_____Debug__C__stop_moving_backwards__new_exitpoint_5( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__stop_moving_backwards__Debug__B__Ex__MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stop_moving_backwards__Debug__Ex__MOVING_BACKWARDS( msg );
            return Debug__C__stop_moving_backwards__Debug__B__Ac__stop_moving_backwards;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_moving_backwards__new_transition_46( msg );
            return junction_____Debug__C__stop_moving_backwards__new_exitpoint_5( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__stop_moving_backwards__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_moving_backwards__new_transition_50( msg );
            return junction_____Debug__C__stop_moving_backwards__new_exitpoint_5( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__stop_moving_forward__Debug__A__Ac__stop_moving_forward( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stop_moving_forward__Debug__En__IDLE( msg );
            return Debug__C__stop_moving_forward__Debug__A__En__IDLE;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_moving_forward__new_transition_28( msg );
            return junction_____Debug__C__stop_moving_forward__new_exitpoint_3( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__stop_moving_forward__Debug__A__En__IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stop_moving_forward__Debug__end__trans__stop_moving_forward( msg );
            return junction_____Debug__C__stop_moving_forward__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_moving_forward__new_transition_29( msg );
            return junction_____Debug__C__stop_moving_forward__new_exitpoint_3( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__stop_moving_forward__Debug__B__Ac__stop_moving_forward( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stop_moving_forward__Debug__AC__stop_moving_forward( msg );
            return Debug__C__stop_moving_forward__Debug__A__Ac__stop_moving_forward;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_moving_forward__new_transition_27( msg );
            return junction_____Debug__C__stop_moving_forward__new_exitpoint_3( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__stop_moving_forward__Debug__B__Ex__MOVING_FORWARD( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stop_moving_forward__Debug__Ex__MOVING_FORWARD( msg );
            return Debug__C__stop_moving_forward__Debug__B__Ac__stop_moving_forward;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_moving_forward__new_transition_26( msg );
            return junction_____Debug__C__stop_moving_forward__new_exitpoint_3( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__stop_moving_forward__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_moving_forward__new_transition_30( msg );
            return junction_____Debug__C__stop_moving_forward__new_exitpoint_3( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__stop_turning_left__Debug__A__Ac__stop_turning_left( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stop_turning_left__Debug__En__IDLE( msg );
            return Debug__C__stop_turning_left__Debug__A__En__IDLE;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_turning_left__new_transition_58( msg );
            return junction_____Debug__C__stop_turning_left__new_exitpoint_6( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__stop_turning_left__Debug__A__En__IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stop_turning_left__Debug__end__trans__stop_turning_left( msg );
            return junction_____Debug__C__stop_turning_left__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_turning_left__new_transition_59( msg );
            return junction_____Debug__C__stop_turning_left__new_exitpoint_6( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__stop_turning_left__Debug__B__Ac__stop_turning_left( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stop_turning_left__Debug__AC__stop_turning_left( msg );
            return Debug__C__stop_turning_left__Debug__A__Ac__stop_turning_left;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_turning_left__new_transition_57( msg );
            return junction_____Debug__C__stop_turning_left__new_exitpoint_6( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__stop_turning_left__Debug__B__Ex__TURNING_LEFT( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stop_turning_left__Debug__Ex__TURNING_LEFT( msg );
            return Debug__C__stop_turning_left__Debug__B__Ac__stop_turning_left;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_turning_left__new_transition_56( msg );
            return junction_____Debug__C__stop_turning_left__new_exitpoint_6( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__stop_turning_left__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_turning_left__new_transition_60( msg );
            return junction_____Debug__C__stop_turning_left__new_exitpoint_6( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__stop_turning_right__Debug__A__Ac__stop_turning_right( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stop_turning_right__Debug__En__IDLE( msg );
            return Debug__C__stop_turning_right__Debug__A__En__IDLE;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_turning_right__new_transition_18( msg );
            return junction_____Debug__C__stop_turning_right__new_exitpoint_2( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__stop_turning_right__Debug__A__En__IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stop_turning_right__Debug__end__trans__stop_turning_right( msg );
            return junction_____Debug__C__stop_turning_right__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_turning_right__new_transition_19( msg );
            return junction_____Debug__C__stop_turning_right__new_exitpoint_2( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__stop_turning_right__Debug__B__Ac__stop_turning_right( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stop_turning_right__Debug__AC__stop_turning_right( msg );
            return Debug__C__stop_turning_right__Debug__A__Ac__stop_turning_right;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_turning_right__new_transition_17( msg );
            return junction_____Debug__C__stop_turning_right__new_exitpoint_2( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__stop_turning_right__Debug__B__Ex__TURNING_RIGHT( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stop_turning_right__Debug__Ex__TURNING_RIGHT( msg );
            return Debug__C__stop_turning_right__Debug__B__Ac__stop_turning_right;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_turning_right__new_transition_16( msg );
            return junction_____Debug__C__stop_turning_right__new_exitpoint_2( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__stop_turning_right__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_turning_right__new_transition_20( msg );
            return junction_____Debug__C__stop_turning_right__new_exitpoint_2( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__turn_left__Debug__A__Ac__turn_left( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__turn_left__Debug__En__TURNING_LEFT( msg );
            return Debug__C__turn_left__Debug__A__En__TURNING_LEFT;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__turn_left__new_transition_8( msg );
            return junction_____Debug__C__turn_left__new_exitpoint_1( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__turn_left__Debug__A__En__TURNING_LEFT( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__turn_left__Debug__end__trans__turn_left( msg );
            return junction_____Debug__C__turn_left__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__turn_left__new_transition_9( msg );
            return junction_____Debug__C__turn_left__new_exitpoint_1( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__turn_left__Debug__B__Ac__turn_left( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__turn_left__Debug__AC__turn_left( msg );
            return Debug__C__turn_left__Debug__A__Ac__turn_left;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__turn_left__new_transition_7( msg );
            return junction_____Debug__C__turn_left__new_exitpoint_1( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__turn_left__Debug__B__Ex__IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__turn_left__Debug__Ex__IDLE( msg );
            return Debug__C__turn_left__Debug__B__Ac__turn_left;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__turn_left__new_transition_6( msg );
            return junction_____Debug__C__turn_left__new_exitpoint_1( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__turn_left__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__turn_left__new_transition_10( msg );
            return junction_____Debug__C__turn_left__new_exitpoint_1( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__turn_right__Debug__A__Ac__turn_right( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__turn_right__Debug__En__TURNING_RIGHT( msg );
            return Debug__C__turn_right__Debug__A__En__TURNING_RIGHT;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__turn_right__new_transition_76( msg );
            return junction_____Debug__C__turn_right__new_exitpoint_8( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__turn_right__Debug__A__En__TURNING_RIGHT( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__turn_right__Debug__end__trans__turn_right( msg );
            return junction_____Debug__C__turn_right__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__turn_right__new_transition_77( msg );
            return junction_____Debug__C__turn_right__new_exitpoint_8( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__turn_right__Debug__B__Ac__turn_right( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__turn_right__Debug__AC__turn_right( msg );
            return Debug__C__turn_right__Debug__A__Ac__turn_right;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__turn_right__new_transition_75( msg );
            return junction_____Debug__C__turn_right__new_exitpoint_8( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__turn_right__Debug__B__Ex__IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__turn_right__Debug__Ex__IDLE( msg );
            return Debug__C__turn_right__Debug__B__Ac__turn_right;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__turn_right__new_transition_74( msg );
            return junction_____Debug__C__turn_right__new_exitpoint_8( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__C__turn_right__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__turn_right__new_transition_78( msg );
            return junction_____Debug__C__turn_right__new_exitpoint_8( msg );
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

Capsule_EngineController::State Capsule_EngineController::state_____Debug__InitState( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__init( msg );
            return choice_____Debug__Path__init( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_EngineController::State Capsule_EngineController::state_____IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_engine:
        switch( msg->getSignalId() )
        {
        case Engine::signal_turnLeft:
            actionchain_____Debug__turn_left( msg );
            return choice_____Debug__Path__turn_left( msg );
        case Engine::signal_moveForward:
            actionchain_____Debug__move_forward( msg );
            return choice_____Debug__Path__move_forward( msg );
        case Engine::signal_turnRight:
            actionchain_____Debug__turn_right( msg );
            return choice_____Debug__Path__turn_right( msg );
        case Engine::signal_moveBackwards:
            actionchain_____Debug__move_backwards( msg );
            return choice_____Debug__Path__move_backwards( msg );
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
            actionchain_____Debug__stop_moving_backwards( msg );
            return choice_____Debug__Path__stop_moving_backwards( msg );
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
            actionchain_____Debug__stop_moving_forward( msg );
            return choice_____Debug__Path__stop_moving_forward( msg );
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
            actionchain_____Debug__stop_turning_left( msg );
            return choice_____Debug__Path__stop_turning_left( msg );
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
            actionchain_____Debug__stop_turning_right( msg );
            return choice_____Debug__Path__stop_turning_right( msg );
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
        Capsule_EngineController::port_extComm,
        "ExtInterface",
        "extComm",
        "",
        1,
        true,
        true,
        false,
        true,
        true,
        false,
        false
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
    4,
    portroles_border,
    0,
    NULL
};

