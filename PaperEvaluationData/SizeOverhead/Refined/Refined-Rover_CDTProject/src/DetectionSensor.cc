
#include "DetectionSensor.hh"

#include "Detection.hh"
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

Capsule_DetectionSensor::Capsule_DetectionSensor( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, detection( borderPorts[borderport_detection] )
, extComm( borderPorts[borderport_extComm] )
, timer( borderPorts[borderport_timer] )
, pinTrig( GPIOClass("23") )
, pinEcho( GPIOClass("24") )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    pinTrig = ( GPIOClass("23") );
    pinEcho = ( GPIOClass("24") );
    stateNames[Debug__C__init] = "Debug__C__init";
    stateNames[Debug__C__start_detecting] = "Debug__C__start_detecting";
    stateNames[Debug__C__stop_detecting] = "Debug__C__stop_detecting";
    stateNames[DETECTING] = "DETECTING";
    stateNames[Debug__C__detecting] = "Debug__C__detecting";
    stateNames[Debug__C__init__Debug__A__Ac__init] = "Debug__C__init__Debug__A__Ac__init";
    stateNames[Debug__C__init__Debug__A__En__init] = "Debug__C__init__Debug__A__En__init";
    stateNames[Debug__C__init__Debug__B__Ac__init] = "Debug__C__init__Debug__B__Ac__init";
    stateNames[Debug__C__init__boundary] = "Debug__C__init__boundary";
    stateNames[Debug__C__start_detecting__Debug__A__Ac__start_detecting] = "Debug__C__start_detecting__Debug__A__Ac__start_detecting";
    stateNames[Debug__C__start_detecting__Debug__A__En__DETECTING] = "Debug__C__start_detecting__Debug__A__En__DETECTING";
    stateNames[Debug__C__start_detecting__Debug__B__Ac__start_detecting] = "Debug__C__start_detecting__Debug__B__Ac__start_detecting";
    stateNames[Debug__C__start_detecting__Debug__B__Ex__IDLE] = "Debug__C__start_detecting__Debug__B__Ex__IDLE";
    stateNames[Debug__C__start_detecting__boundary] = "Debug__C__start_detecting__boundary";
    stateNames[Debug__C__stop_detecting__Debug__A__Ac__stop_detecting] = "Debug__C__stop_detecting__Debug__A__Ac__stop_detecting";
    stateNames[Debug__C__stop_detecting__Debug__A__En__IDLE] = "Debug__C__stop_detecting__Debug__A__En__IDLE";
    stateNames[Debug__C__stop_detecting__Debug__B__Ac__stop_detecting] = "Debug__C__stop_detecting__Debug__B__Ac__stop_detecting";
    stateNames[Debug__C__stop_detecting__Debug__B__Ex__DETECTING] = "Debug__C__stop_detecting__Debug__B__Ex__DETECTING";
    stateNames[Debug__C__stop_detecting__boundary] = "Debug__C__stop_detecting__boundary";
    stateNames[Debug__InitState] = "Debug__InitState";
    stateNames[IDLE] = "IDLE";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
    int i = 0;
    while( i < 3 )
        history[i++] = SPECIAL_INTERNAL_STATE_UNVISITED;
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








void Capsule_DetectionSensor::Debug__variablesView()
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::DetectionSensor operation Debug__variablesView */
    std::string tempS="";
    if (Debug__variablesData==NULL)
    Debug__variablesData=(char *)malloc(strlen(tempS.c_str())+1);
    else if (strlen(Debug__variablesData)<strlen(tempS.c_str()))
    Debug__variablesData=(char *) realloc(Debug__variablesData,strlen(tempS.c_str())+1);
    strcpy(Debug__variablesData,tempS.c_str());
    /* UMLRTGEN-USERREGION-END */
}

bool Capsule_DetectionSensor::Debug__variablesChange( char * varName, char * varValue )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::DetectionSensor operation Debug__variablesChange */
    std::string tempVarName="";
    tempVarName.append(varName);
    return false;
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_DetectionSensor::Debug__sendEvent( debugEvents::EVENTSOURCEKIND eventSourceKind, debugEvents::EVENTTYPE eventType, const char * instanceName, int capsuleIndex, const char * signalName, char * capsuleName, char * sourceName, char * reserve1, char * reserve2, char * reserve3 )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::DetectionSensor operation Debug__sendEvent */
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
    case Debug__C__detecting:
        currentState = state_____Debug__C__detecting( &message );
        break;
    case Debug__InitState:
        currentState = state_____Debug__InitState( &message );
        break;
    case Debug__C__start_detecting__Debug__B__Ex__IDLE:
        currentState = state_____Debug__C__start_detecting__Debug__B__Ex__IDLE( &message );
        break;
    case Debug__C__start_detecting__Debug__B__Ac__start_detecting:
        currentState = state_____Debug__C__start_detecting__Debug__B__Ac__start_detecting( &message );
        break;
    case Debug__C__start_detecting__Debug__A__Ac__start_detecting:
        currentState = state_____Debug__C__start_detecting__Debug__A__Ac__start_detecting( &message );
        break;
    case Debug__C__start_detecting__Debug__A__En__DETECTING:
        currentState = state_____Debug__C__start_detecting__Debug__A__En__DETECTING( &message );
        break;
    case Debug__C__start_detecting__boundary:
        currentState = state_____Debug__C__start_detecting__boundary( &message );
        break;
    case Debug__C__stop_detecting__Debug__B__Ex__DETECTING:
        currentState = state_____Debug__C__stop_detecting__Debug__B__Ex__DETECTING( &message );
        break;
    case Debug__C__stop_detecting__Debug__B__Ac__stop_detecting:
        currentState = state_____Debug__C__stop_detecting__Debug__B__Ac__stop_detecting( &message );
        break;
    case Debug__C__stop_detecting__Debug__A__Ac__stop_detecting:
        currentState = state_____Debug__C__stop_detecting__Debug__A__Ac__stop_detecting( &message );
        break;
    case Debug__C__stop_detecting__Debug__A__En__IDLE:
        currentState = state_____Debug__C__stop_detecting__Debug__A__En__IDLE( &message );
        break;
    case Debug__C__stop_detecting__boundary:
        currentState = state_____Debug__C__stop_detecting__boundary( &message );
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
    default:
        break;
    }
}

void Capsule_DetectionSensor::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Debug__InitDebug( &message );
    currentState = Debug__InitState;
}

const char * Capsule_DetectionSensor::getCurrentStateString() const
{
    return stateNames[currentState];
}





void Capsule_DetectionSensor::save_history( Capsule_DetectionSensor::State compositeState, Capsule_DetectionSensor::State subState )
{
    history[compositeState] = subState;
}

bool Capsule_DetectionSensor::check_history( Capsule_DetectionSensor::State compositeState, Capsule_DetectionSensor::State subState )
{
    return history[compositeState] == subState;
}

void Capsule_DetectionSensor::entryaction_____DETECTING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::DETECTING entry  */
    if( not Debug__SRO.checkDebug("DETECTING",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::DETECTING",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::entryaction_____Debug__C__detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__detecting entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::entryaction_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__init::Debug__A__Ac__init entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__init::Region1::Debug__A__Ac__init",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("init","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("IDLE","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::entryaction_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__init::Debug__A__En__init entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__init::Region1::Debug__A__En__init",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::entryaction_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__init::Debug__B__Ac__init entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__init::Region1::Debug__B__Ac__init",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("init","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::entryaction_____Debug__C__init__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_DetectionSensor::entryaction_____Debug__C__start_detecting__Debug__A__Ac__start_detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__start detecting::Debug__A__Ac__start detecting entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__start detecting::Region1::Debug__A__Ac__start detecting",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("start detecting","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("DETECTING","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::entryaction_____Debug__C__start_detecting__Debug__A__En__DETECTING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__start detecting::Debug__A__En__DETECTING entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__start detecting::Region1::Debug__A__En__DETECTING",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("DETECTING","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::entryaction_____Debug__C__start_detecting__Debug__B__Ac__start_detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__start detecting::Debug__B__Ac__start detecting entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__start detecting::Region1::Debug__B__Ac__start detecting",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("start detecting","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::entryaction_____Debug__C__start_detecting__Debug__B__Ex__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__start detecting::Debug__B__Ex__IDLE entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__start detecting::Region1::Debug__B__Ex__IDLE",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::entryaction_____Debug__C__start_detecting__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_DetectionSensor::entryaction_____Debug__C__stop_detecting__Debug__A__Ac__stop_detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__stop detecting::Debug__A__Ac__stop detecting entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__stop detecting::Region1::Debug__A__Ac__stop detecting",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("stop detecting","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("IDLE","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::entryaction_____Debug__C__stop_detecting__Debug__A__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__stop detecting::Debug__A__En__IDLE entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__stop detecting::Region1::Debug__A__En__IDLE",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::entryaction_____Debug__C__stop_detecting__Debug__B__Ac__stop_detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__stop detecting::Debug__B__Ac__stop detecting entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__stop detecting::Region1::Debug__B__Ac__stop detecting",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("DETECTING","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("stop detecting","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::entryaction_____Debug__C__stop_detecting__Debug__B__Ex__DETECTING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__stop detecting::Debug__B__Ex__DETECTING entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__stop detecting::Region1::Debug__B__Ex__DETECTING",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("DETECTING","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::entryaction_____Debug__C__stop_detecting__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_DetectionSensor::entryaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__InitState entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::entryaction_____IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::IDLE entry  */
    if( not Debug__SRO.checkDebug("IDLE",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::IDLE",(char *)"",(char *)"",(char *)"");
    pinTrig.setval_gpio("0");}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::exitaction_____DETECTING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::DETECTING exit  */
    if( not Debug__SRO.checkDebug("DETECTING",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::DETECTING",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::exitaction_____Debug__C__detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__detecting exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::exitaction_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__init::Debug__A__Ac__init exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__init::Region1::Debug__A__Ac__init",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::exitaction_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__init::Debug__A__En__init exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__init::Region1::Debug__A__En__init",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::exitaction_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__init::Debug__B__Ac__init exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__init::Region1::Debug__B__Ac__init",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::exitaction_____Debug__C__init__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_DetectionSensor::exitaction_____Debug__C__start_detecting__Debug__A__Ac__start_detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__start detecting::Debug__A__Ac__start detecting exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__start detecting::Region1::Debug__A__Ac__start detecting",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::exitaction_____Debug__C__start_detecting__Debug__A__En__DETECTING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__start detecting::Debug__A__En__DETECTING exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__start detecting::Region1::Debug__A__En__DETECTING",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::exitaction_____Debug__C__start_detecting__Debug__B__Ac__start_detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__start detecting::Debug__B__Ac__start detecting exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__start detecting::Region1::Debug__B__Ac__start detecting",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::exitaction_____Debug__C__start_detecting__Debug__B__Ex__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__start detecting::Debug__B__Ex__IDLE exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__start detecting::Region1::Debug__B__Ex__IDLE",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::exitaction_____Debug__C__start_detecting__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_DetectionSensor::exitaction_____Debug__C__stop_detecting__Debug__A__Ac__stop_detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__stop detecting::Debug__A__Ac__stop detecting exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__stop detecting::Region1::Debug__A__Ac__stop detecting",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::exitaction_____Debug__C__stop_detecting__Debug__A__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__stop detecting::Debug__A__En__IDLE exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__stop detecting::Region1::Debug__A__En__IDLE",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::exitaction_____Debug__C__stop_detecting__Debug__B__Ac__stop_detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__stop detecting::Debug__B__Ac__stop detecting exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__stop detecting::Region1::Debug__B__Ac__stop detecting",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::exitaction_____Debug__C__stop_detecting__Debug__B__Ex__DETECTING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__stop detecting::Debug__B__Ex__DETECTING exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__stop detecting::Region1::Debug__B__Ex__DETECTING",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::exitaction_____Debug__C__stop_detecting__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_DetectionSensor::exitaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__InitState exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::exitaction_____IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::IDLE exit  */
    if( not Debug__SRO.checkDebug("IDLE",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::IDLE",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__C__init__Debug__Ac__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__init transition Debug__C__init::Debug__B__Ac__init,Debug__C__init::Debug__A__Ac__init,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__init::Region1::Debug__Ac__init",(char *)"Debug__B__Ac__init",(char *)"Debug__A__Ac__init",(char *)"");
    pinTrig.export_gpio();
    pinEcho.export_gpio();
    pinTrig.setdir_gpio("out");
    pinEcho.setdir_gpio("in");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__C__init__Debug__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__init transition Debug__C__init::Debug__A__Ac__init,Debug__C__init::Debug__A__En__init,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__init::Region1::Debug__En__IDLE",(char *)"Debug__A__Ac__init",(char *)"Debug__A__En__init",(char *)"");
    pinTrig.setval_gpio("0");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__C__init__Debug__end__trans__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__init transition Debug__C__init::Debug__A__En__init,Debug__C__init::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__init::Region1::Debug__end__trans__init",(char *)"Debug__A__En__init",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__C__init__Debug__init__trans__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__init transition Debug__C__init::en,Debug__C__init::Debug__B__Ac__init */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__init::Region1::Debug__init__trans__init",(char *)"en",(char *)"Debug__B__Ac__init",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__C__start_detecting__Debug__AC__start_detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__start detecting transition Debug__C__start detecting::Debug__B__Ac__start detecting,Debug__C__start detecting::Debug__A__Ac__start detecting,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__start detecting::Region1::Debug__AC__start detecting",(char *)"Debug__B__Ac__start detecting",(char *)"Debug__A__Ac__start detecting",(char *)"");
    pinTrig.setval_gpio("1");
    timerId = timer.informIn(UMLRTTimespec(0,10000));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__C__start_detecting__Debug__En__DETECTING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__start detecting transition Debug__C__start detecting::Debug__A__Ac__start detecting,Debug__C__start detecting::Debug__A__En__DETECTING,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__start detecting::Region1::Debug__En__DETECTING",(char *)"Debug__A__Ac__start detecting",(char *)"Debug__A__En__DETECTING",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__C__start_detecting__Debug__Ex__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__start detecting transition Debug__C__start detecting::Debug__B__Ex__IDLE,Debug__C__start detecting::Debug__B__Ac__start detecting,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__start detecting::Region1::Debug__Ex__IDLE",(char *)"Debug__B__Ex__IDLE",(char *)"Debug__B__Ac__start detecting",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__C__start_detecting__Debug__end__trans__start_detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__start detecting transition Debug__C__start detecting::Debug__A__En__DETECTING,Debug__C__start detecting::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__start detecting::Region1::Debug__end__trans__start detecting",(char *)"Debug__A__En__DETECTING",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__C__start_detecting__Debug__init__trans__start_detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__start detecting transition Debug__C__start detecting::en,Debug__C__start detecting::Debug__B__Ex__IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__start detecting::Region1::Debug__init__trans__start detecting",(char *)"en",(char *)"Debug__B__Ex__IDLE",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__C__stop_detecting__Debug__AC__stop_detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__stop detecting transition Debug__C__stop detecting::Debug__B__Ac__stop detecting,Debug__C__stop detecting::Debug__A__Ac__stop detecting,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__stop detecting::Region1::Debug__AC__stop detecting",(char *)"Debug__B__Ac__stop detecting",(char *)"Debug__A__Ac__stop detecting",(char *)"");
    timer.cancelTimer(timerId);
    log.log("stop detecting");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__C__stop_detecting__Debug__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__stop detecting transition Debug__C__stop detecting::Debug__A__Ac__stop detecting,Debug__C__stop detecting::Debug__A__En__IDLE,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__stop detecting::Region1::Debug__En__IDLE",(char *)"Debug__A__Ac__stop detecting",(char *)"Debug__A__En__IDLE",(char *)"");
    pinTrig.setval_gpio("0");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__C__stop_detecting__Debug__Ex__DETECTING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__stop detecting transition Debug__C__stop detecting::Debug__B__Ex__DETECTING,Debug__C__stop detecting::Debug__B__Ac__stop detecting,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__stop detecting::Region1::Debug__Ex__DETECTING",(char *)"Debug__B__Ex__DETECTING",(char *)"Debug__B__Ac__stop detecting",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__C__stop_detecting__Debug__end__trans__stop_detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__stop detecting transition Debug__C__stop detecting::Debug__A__En__IDLE,Debug__C__stop detecting::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__stop detecting::Region1::Debug__end__trans__stop detecting",(char *)"Debug__A__En__IDLE",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__C__stop_detecting__Debug__init__trans__stop_detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor::Debug__C__stop detecting transition Debug__C__stop detecting::en,Debug__C__stop detecting::Debug__B__Ex__DETECTING */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__C__stop detecting::Region1::Debug__init__trans__stop detecting",(char *)"en",(char *)"Debug__B__Ex__DETECTING",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__InitDebug( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor transition Pseudo3,Debug__InitState */
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

void Capsule_DetectionSensor::transitionaction_____Debug__detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor transition DETECTING,Debug__Path__detecting,timeout:timer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__detecting",(char *)"DETECTING",(char *)"Debug__Path__detecting",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__detecting__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor transition Debug__C__detecting,DETECTING */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__detecting__E",(char *)"ex",(char *)"DETECTING",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__detecting__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor transition Debug__Path__detecting,Debug__C__detecting */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__detecting__S",(char *)"Debug__Path__detecting",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__detecting__dbg( const UMLRTMessage * msg )
{
    #define umlrtparam_varName ( *(const char * *)msg->getParam( 0 ) )
    #define umlrtparam_varValue ( *(const char * *)msg->getParam( 1 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor transition Debug__C__detecting,Debug__C__detecting,dbgVarChange:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__detecting__dbg",(char *)"Debug__C__detecting",(char *)"Debug__C__detecting",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_varValue
    #undef umlrtparam_varName
}

void Capsule_DetectionSensor::transitionaction_____Debug__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor transition Debug__InitState,Debug__Path__init,null:extComm */
    if (this->Debug__SRO.getExecMode()==Stepping){
    Debug__SRO.addTransitionsFromState("IDLE","move forward","MOVING_FORWARD","moveForward","Engine");
    Debug__SRO.addTransitionsFromState("IDLE","move backwards","MOVING_BACKWARDS","moveBackwards","Engine");
    Debug__SRO.addTransitionsFromState("DETECTING","detecting","DETECTING","timeout","Timing");
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
    Debug__SRO.addTransitionsFromState("IDLE","start detecting","DETECTING","startDetection","Detection");
    Debug__SRO.addTransitionsFromState("DETECTING","stop detecting","IDLE","stopDetection","Detection");
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

void Capsule_DetectionSensor::transitionaction_____Debug__init__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor transition Debug__C__init::ex,IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__init__E",(char *)"ex",(char *)"IDLE",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__init__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor transition Debug__Path__init,Debug__C__init::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__init__S",(char *)"Debug__Path__init",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__init__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor transition Debug__C__init::new_exitpoint_3,Debug__C__init */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__init__dbg",(char *)"Debug__C__init",(char *)"Debug__C__init",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__start_detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor transition IDLE,Debug__Path__start detecting,startDetection:detection */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__start detecting",(char *)"IDLE",(char *)"Debug__Path__start detecting",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__start_detecting__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor transition Debug__C__start detecting::ex,DETECTING */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__start detecting__E",(char *)"ex",(char *)"DETECTING",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__start_detecting__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor transition Debug__Path__start detecting,Debug__C__start detecting::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__start detecting__S",(char *)"Debug__Path__start detecting",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__start_detecting__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor transition Debug__C__start detecting::new_exitpoint_1,Debug__C__start detecting */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__start detecting__dbg",(char *)"Debug__C__start detecting",(char *)"Debug__C__start detecting",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__stop_detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor transition DETECTING,Debug__Path__stop detecting,stopDetection:detection */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__stop detecting",(char *)"DETECTING",(char *)"Debug__Path__stop detecting",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__stop_detecting__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor transition Debug__C__stop detecting::ex,IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__stop detecting__E",(char *)"ex",(char *)"IDLE",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__stop_detecting__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor transition Debug__Path__stop detecting,Debug__C__stop detecting::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__stop detecting__S",(char *)"Debug__Path__stop detecting",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____Debug__stop_detecting__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor transition Debug__C__stop detecting::new_exitpoint_2,Debug__C__stop detecting */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::Debug__stop detecting__dbg",(char *)"Debug__C__stop detecting",(char *)"Debug__C__stop detecting",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor transition Debug__Path__detecting,DETECTING */
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
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor transition Debug__Path__init,IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::init",(char *)"Debug__Path__init",(char *)"IDLE",(char *)"");
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
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor transition Debug__Path__start detecting,DETECTING */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::start detecting",(char *)"Debug__Path__start detecting",(char *)"DETECTING",(char *)"");
    pinTrig.setval_gpio("1");
    timerId = timer.informIn(UMLRTTimespec(0,10000));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::transitionaction_____stop_detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor transition Debug__Path__stop detecting,IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::UMLRT-Rover::DetectionSensor::DetectionSensorStateMachine::Region::stop detecting",(char *)"Debug__Path__stop detecting",(char *)"IDLE",(char *)"");
    timer.cancelTimer(timerId);
    log.log("stop detecting");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_DetectionSensor::action_____Debug__detecting__S__Debug__Guarddetecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor guard Debug__Path__detecting,Debug__C__detecting */
    return Debug__SRO.checkDebug("DETECTING",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_DetectionSensor::action_____Debug__init__S__Debug__Guardinit( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor guard Debug__Path__init,Debug__C__init::en */
    return Debug__SRO.checkDebug("Pseudo3","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_DetectionSensor::action_____Debug__start_detecting__S__Debug__Guardstart_detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor guard Debug__Path__start detecting,Debug__C__start detecting::en */
    return Debug__SRO.checkDebug("IDLE",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_DetectionSensor::action_____Debug__stop_detecting__S__Debug__Guardstop_detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::UMLRT-Rover::DetectionSensor guard Debug__Path__stop detecting,Debug__C__stop detecting::en */
    return Debug__SRO.checkDebug("DETECTING",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_DetectionSensor::actionchain_____Debug__C__init__Debug__Ac__init( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__B__Ac__init( msg );
    transitionaction_____Debug__C__init__Debug__Ac__init( msg );
    entryaction_____Debug__C__init__Debug__A__Ac__init( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__init__Debug__En__IDLE( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__A__Ac__init( msg );
    transitionaction_____Debug__C__init__Debug__En__IDLE( msg );
    entryaction_____Debug__C__init__Debug__A__En__init( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__init__Debug__end__trans__init( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__A__En__init( msg );
    transitionaction_____Debug__C__init__Debug__end__trans__init( msg );
    save_history( Debug__C__init, Debug__C__init__Debug__A__En__init );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__init__Debug__init__trans__init( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__init__Debug__init__trans__init( msg );
    entryaction_____Debug__C__init__Debug__B__Ac__init( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__init__new_transition_21( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__Debug__B__Ac__init( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__init__new_transition_22( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__Debug__A__Ac__init( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__init__new_transition_23( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__Debug__A__En__init( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__init__new_transition_24_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__boundary( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__init__new_transition_25( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__B__Ac__init( msg );
    save_history( Debug__C__init, Debug__C__init__Debug__B__Ac__init );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__init__new_transition_26( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__A__Ac__init( msg );
    save_history( Debug__C__init, Debug__C__init__Debug__A__Ac__init );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__init__new_transition_27( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__A__En__init( msg );
    save_history( Debug__C__init, Debug__C__init__Debug__A__En__init );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__init__new_transition_28( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__boundary( msg );
    save_history( Debug__C__init, Debug__C__init__boundary );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__start_detecting__Debug__AC__start_detecting( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__start_detecting__Debug__B__Ac__start_detecting( msg );
    transitionaction_____Debug__C__start_detecting__Debug__AC__start_detecting( msg );
    entryaction_____Debug__C__start_detecting__Debug__A__Ac__start_detecting( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__start_detecting__Debug__En__DETECTING( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__start_detecting__Debug__A__Ac__start_detecting( msg );
    transitionaction_____Debug__C__start_detecting__Debug__En__DETECTING( msg );
    entryaction_____Debug__C__start_detecting__Debug__A__En__DETECTING( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__start_detecting__Debug__Ex__IDLE( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__start_detecting__Debug__B__Ex__IDLE( msg );
    transitionaction_____Debug__C__start_detecting__Debug__Ex__IDLE( msg );
    entryaction_____Debug__C__start_detecting__Debug__B__Ac__start_detecting( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__start_detecting__Debug__end__trans__start_detecting( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__start_detecting__Debug__A__En__DETECTING( msg );
    transitionaction_____Debug__C__start_detecting__Debug__end__trans__start_detecting( msg );
    save_history( Debug__C__start_detecting, Debug__C__start_detecting__Debug__A__En__DETECTING );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__start_detecting__Debug__init__trans__start_detecting( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__start_detecting__Debug__init__trans__start_detecting( msg );
    entryaction_____Debug__C__start_detecting__Debug__B__Ex__IDLE( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__start_detecting__new_transition_1( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__start_detecting__Debug__B__Ex__IDLE( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__start_detecting__new_transition_10( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__start_detecting__boundary( msg );
    save_history( Debug__C__start_detecting, Debug__C__start_detecting__boundary );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__start_detecting__new_transition_2( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__start_detecting__Debug__B__Ac__start_detecting( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__start_detecting__new_transition_3( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__start_detecting__Debug__A__Ac__start_detecting( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__start_detecting__new_transition_4( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__start_detecting__Debug__A__En__DETECTING( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__start_detecting__new_transition_5_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__start_detecting__boundary( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__start_detecting__new_transition_6( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__start_detecting__Debug__B__Ex__IDLE( msg );
    save_history( Debug__C__start_detecting, Debug__C__start_detecting__Debug__B__Ex__IDLE );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__start_detecting__new_transition_7( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__start_detecting__Debug__B__Ac__start_detecting( msg );
    save_history( Debug__C__start_detecting, Debug__C__start_detecting__Debug__B__Ac__start_detecting );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__start_detecting__new_transition_8( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__start_detecting__Debug__A__Ac__start_detecting( msg );
    save_history( Debug__C__start_detecting, Debug__C__start_detecting__Debug__A__Ac__start_detecting );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__start_detecting__new_transition_9( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__start_detecting__Debug__A__En__DETECTING( msg );
    save_history( Debug__C__start_detecting, Debug__C__start_detecting__Debug__A__En__DETECTING );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__stop_detecting__Debug__AC__stop_detecting( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_detecting__Debug__B__Ac__stop_detecting( msg );
    transitionaction_____Debug__C__stop_detecting__Debug__AC__stop_detecting( msg );
    entryaction_____Debug__C__stop_detecting__Debug__A__Ac__stop_detecting( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__stop_detecting__Debug__En__IDLE( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_detecting__Debug__A__Ac__stop_detecting( msg );
    transitionaction_____Debug__C__stop_detecting__Debug__En__IDLE( msg );
    entryaction_____Debug__C__stop_detecting__Debug__A__En__IDLE( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__stop_detecting__Debug__Ex__DETECTING( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_detecting__Debug__B__Ex__DETECTING( msg );
    transitionaction_____Debug__C__stop_detecting__Debug__Ex__DETECTING( msg );
    entryaction_____Debug__C__stop_detecting__Debug__B__Ac__stop_detecting( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__stop_detecting__Debug__end__trans__stop_detecting( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_detecting__Debug__A__En__IDLE( msg );
    transitionaction_____Debug__C__stop_detecting__Debug__end__trans__stop_detecting( msg );
    save_history( Debug__C__stop_detecting, Debug__C__stop_detecting__Debug__A__En__IDLE );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__stop_detecting__Debug__init__trans__stop_detecting( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__stop_detecting__Debug__init__trans__stop_detecting( msg );
    entryaction_____Debug__C__stop_detecting__Debug__B__Ex__DETECTING( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__stop_detecting__new_transition_11( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_detecting__Debug__B__Ex__DETECTING( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__stop_detecting__new_transition_12( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_detecting__Debug__B__Ac__stop_detecting( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__stop_detecting__new_transition_13( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_detecting__Debug__A__Ac__stop_detecting( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__stop_detecting__new_transition_14( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_detecting__Debug__A__En__IDLE( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__stop_detecting__new_transition_15_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stop_detecting__boundary( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__stop_detecting__new_transition_16( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_detecting__Debug__B__Ex__DETECTING( msg );
    save_history( Debug__C__stop_detecting, Debug__C__stop_detecting__Debug__B__Ex__DETECTING );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__stop_detecting__new_transition_17( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_detecting__Debug__B__Ac__stop_detecting( msg );
    save_history( Debug__C__stop_detecting, Debug__C__stop_detecting__Debug__B__Ac__stop_detecting );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__stop_detecting__new_transition_18( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_detecting__Debug__A__Ac__stop_detecting( msg );
    save_history( Debug__C__stop_detecting, Debug__C__stop_detecting__Debug__A__Ac__stop_detecting );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__stop_detecting__new_transition_19( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_detecting__Debug__A__En__IDLE( msg );
    save_history( Debug__C__stop_detecting, Debug__C__stop_detecting__Debug__A__En__IDLE );
}

void Capsule_DetectionSensor::actionchain_____Debug__C__stop_detecting__new_transition_20( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_detecting__boundary( msg );
    save_history( Debug__C__stop_detecting, Debug__C__stop_detecting__boundary );
}

void Capsule_DetectionSensor::actionchain_____Debug__InitDebug( const UMLRTMessage * msg )
{
    transitionaction_____Debug__InitDebug( msg );
    entryaction_____Debug__InitState( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__detecting( const UMLRTMessage * msg )
{
    exitaction_____DETECTING( msg );
    transitionaction_____Debug__detecting( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__detecting__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__detecting( msg );
    transitionaction_____Debug__detecting__E( msg );
    entryaction_____DETECTING( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__detecting__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__detecting__S( msg );
    entryaction_____Debug__C__detecting( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__detecting__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__detecting( msg );
    transitionaction_____Debug__detecting__dbg( msg );
    entryaction_____Debug__C__detecting( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__init( const UMLRTMessage * msg )
{
    exitaction_____Debug__InitState( msg );
    transitionaction_____Debug__init( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__init__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__boundary( msg );
    transitionaction_____Debug__init__E( msg );
    entryaction_____IDLE( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__init__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__init__S( msg );
    entryaction_____Debug__C__init__boundary( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__init__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__boundary( msg );
    transitionaction_____Debug__init__dbg( msg );
    entryaction_____Debug__C__init__boundary( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__start_detecting( const UMLRTMessage * msg )
{
    exitaction_____IDLE( msg );
    transitionaction_____Debug__start_detecting( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__start_detecting__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__start_detecting__boundary( msg );
    transitionaction_____Debug__start_detecting__E( msg );
    entryaction_____DETECTING( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__start_detecting__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__start_detecting__S( msg );
    entryaction_____Debug__C__start_detecting__boundary( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__start_detecting__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__start_detecting__boundary( msg );
    transitionaction_____Debug__start_detecting__dbg( msg );
    entryaction_____Debug__C__start_detecting__boundary( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__stop_detecting( const UMLRTMessage * msg )
{
    exitaction_____DETECTING( msg );
    transitionaction_____Debug__stop_detecting( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__stop_detecting__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_detecting__boundary( msg );
    transitionaction_____Debug__stop_detecting__E( msg );
    entryaction_____IDLE( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__stop_detecting__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__stop_detecting__S( msg );
    entryaction_____Debug__C__stop_detecting__boundary( msg );
}

void Capsule_DetectionSensor::actionchain_____Debug__stop_detecting__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stop_detecting__boundary( msg );
    transitionaction_____Debug__stop_detecting__dbg( msg );
    entryaction_____Debug__C__stop_detecting__boundary( msg );
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
    transitionaction_____start_detecting( msg );
    entryaction_____DETECTING( msg );
}

void Capsule_DetectionSensor::actionchain_____stop_detecting( const UMLRTMessage * msg )
{
    transitionaction_____stop_detecting( msg );
    entryaction_____IDLE( msg );
}

Capsule_DetectionSensor::State Capsule_DetectionSensor::junction_____Debug__C__init__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__init__Debug__init__trans__init( msg );
    return Debug__C__init__Debug__B__Ac__init;
}

Capsule_DetectionSensor::State Capsule_DetectionSensor::junction_____Debug__C__init__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__init__E( msg );
    return IDLE;
}

Capsule_DetectionSensor::State Capsule_DetectionSensor::junction_____Debug__C__init__new_exitpoint_3( const UMLRTMessage * msg )
{
    actionchain_____Debug__init__dbg( msg );
    return choice_____Debug__C__init__deephistory( msg );
}

Capsule_DetectionSensor::State Capsule_DetectionSensor::junction_____Debug__C__start_detecting__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__start_detecting__Debug__init__trans__start_detecting( msg );
    return Debug__C__start_detecting__Debug__B__Ex__IDLE;
}

Capsule_DetectionSensor::State Capsule_DetectionSensor::junction_____Debug__C__start_detecting__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__start_detecting__E( msg );
    return DETECTING;
}

Capsule_DetectionSensor::State Capsule_DetectionSensor::junction_____Debug__C__start_detecting__new_exitpoint_1( const UMLRTMessage * msg )
{
    actionchain_____Debug__start_detecting__dbg( msg );
    return choice_____Debug__C__start_detecting__deephistory( msg );
}

Capsule_DetectionSensor::State Capsule_DetectionSensor::junction_____Debug__C__stop_detecting__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__stop_detecting__Debug__init__trans__stop_detecting( msg );
    return Debug__C__stop_detecting__Debug__B__Ex__DETECTING;
}

Capsule_DetectionSensor::State Capsule_DetectionSensor::junction_____Debug__C__stop_detecting__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__stop_detecting__E( msg );
    return IDLE;
}

Capsule_DetectionSensor::State Capsule_DetectionSensor::junction_____Debug__C__stop_detecting__new_exitpoint_2( const UMLRTMessage * msg )
{
    actionchain_____Debug__stop_detecting__dbg( msg );
    return choice_____Debug__C__stop_detecting__deephistory( msg );
}

Capsule_DetectionSensor::State Capsule_DetectionSensor::choice_____Debug__C__init__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__init, Debug__C__init__Debug__B__Ac__init ) )
    {
        actionchain_____Debug__C__init__new_transition_21( msg );
        return Debug__C__init__Debug__B__Ac__init;
    }
    else if( check_history( Debug__C__init, Debug__C__init__Debug__A__Ac__init ) )
    {
        actionchain_____Debug__C__init__new_transition_22( msg );
        return Debug__C__init__Debug__A__Ac__init;
    }
    else if( check_history( Debug__C__init, Debug__C__init__Debug__A__En__init ) )
    {
        actionchain_____Debug__C__init__new_transition_23( msg );
        return Debug__C__init__Debug__A__En__init;
    }
    else if( check_history( Debug__C__init, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__init__new_transition_24_to_boundary( msg );
        return Debug__C__init__boundary;
    }
    return currentState;
}

Capsule_DetectionSensor::State Capsule_DetectionSensor::choice_____Debug__C__start_detecting__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__start_detecting, Debug__C__start_detecting__Debug__B__Ex__IDLE ) )
    {
        actionchain_____Debug__C__start_detecting__new_transition_1( msg );
        return Debug__C__start_detecting__Debug__B__Ex__IDLE;
    }
    else if( check_history( Debug__C__start_detecting, Debug__C__start_detecting__Debug__B__Ac__start_detecting ) )
    {
        actionchain_____Debug__C__start_detecting__new_transition_2( msg );
        return Debug__C__start_detecting__Debug__B__Ac__start_detecting;
    }
    else if( check_history( Debug__C__start_detecting, Debug__C__start_detecting__Debug__A__Ac__start_detecting ) )
    {
        actionchain_____Debug__C__start_detecting__new_transition_3( msg );
        return Debug__C__start_detecting__Debug__A__Ac__start_detecting;
    }
    else if( check_history( Debug__C__start_detecting, Debug__C__start_detecting__Debug__A__En__DETECTING ) )
    {
        actionchain_____Debug__C__start_detecting__new_transition_4( msg );
        return Debug__C__start_detecting__Debug__A__En__DETECTING;
    }
    else if( check_history( Debug__C__start_detecting, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__start_detecting__new_transition_5_to_boundary( msg );
        return Debug__C__start_detecting__boundary;
    }
    return currentState;
}

Capsule_DetectionSensor::State Capsule_DetectionSensor::choice_____Debug__C__stop_detecting__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__stop_detecting, Debug__C__stop_detecting__Debug__B__Ex__DETECTING ) )
    {
        actionchain_____Debug__C__stop_detecting__new_transition_11( msg );
        return Debug__C__stop_detecting__Debug__B__Ex__DETECTING;
    }
    else if( check_history( Debug__C__stop_detecting, Debug__C__stop_detecting__Debug__B__Ac__stop_detecting ) )
    {
        actionchain_____Debug__C__stop_detecting__new_transition_12( msg );
        return Debug__C__stop_detecting__Debug__B__Ac__stop_detecting;
    }
    else if( check_history( Debug__C__stop_detecting, Debug__C__stop_detecting__Debug__A__Ac__stop_detecting ) )
    {
        actionchain_____Debug__C__stop_detecting__new_transition_13( msg );
        return Debug__C__stop_detecting__Debug__A__Ac__stop_detecting;
    }
    else if( check_history( Debug__C__stop_detecting, Debug__C__stop_detecting__Debug__A__En__IDLE ) )
    {
        actionchain_____Debug__C__stop_detecting__new_transition_14( msg );
        return Debug__C__stop_detecting__Debug__A__En__IDLE;
    }
    else if( check_history( Debug__C__stop_detecting, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__stop_detecting__new_transition_15_to_boundary( msg );
        return Debug__C__stop_detecting__boundary;
    }
    return currentState;
}

Capsule_DetectionSensor::State Capsule_DetectionSensor::choice_____Debug__Path__detecting( const UMLRTMessage * msg )
{
    if( action_____Debug__detecting__S__Debug__Guarddetecting( msg ) )
    {
        actionchain_____Debug__detecting__S( msg );
        return Debug__C__detecting;
    }
    else
    {
        actionchain_____detecting( msg );
        return DETECTING;
    }
    return currentState;
}

Capsule_DetectionSensor::State Capsule_DetectionSensor::choice_____Debug__Path__init( const UMLRTMessage * msg )
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

Capsule_DetectionSensor::State Capsule_DetectionSensor::choice_____Debug__Path__start_detecting( const UMLRTMessage * msg )
{
    if( action_____Debug__start_detecting__S__Debug__Guardstart_detecting( msg ) )
    {
        actionchain_____Debug__start_detecting__S( msg );
        return junction_____Debug__C__start_detecting__en( msg );
    }
    else
    {
        actionchain_____start_detecting( msg );
        return DETECTING;
    }
    return currentState;
}

Capsule_DetectionSensor::State Capsule_DetectionSensor::choice_____Debug__Path__stop_detecting( const UMLRTMessage * msg )
{
    if( action_____Debug__stop_detecting__S__Debug__Guardstop_detecting( msg ) )
    {
        actionchain_____Debug__stop_detecting__S( msg );
        return junction_____Debug__C__stop_detecting__en( msg );
    }
    else
    {
        actionchain_____stop_detecting( msg );
        return IDLE;
    }
    return currentState;
}

Capsule_DetectionSensor::State Capsule_DetectionSensor::state_____DETECTING( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_detection:
        switch( msg->getSignalId() )
        {
        case Detection::signal_stopDetection:
            actionchain_____Debug__stop_detecting( msg );
            return choice_____Debug__Path__stop_detecting( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____Debug__detecting( msg );
            return choice_____Debug__Path__detecting( msg );
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

Capsule_DetectionSensor::State Capsule_DetectionSensor::state_____Debug__C__detecting( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__detecting__dbg( msg );
            return Debug__C__detecting;
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

Capsule_DetectionSensor::State Capsule_DetectionSensor::state_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg )
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
            actionchain_____Debug__C__init__new_transition_26( msg );
            return junction_____Debug__C__init__new_exitpoint_3( msg );
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

Capsule_DetectionSensor::State Capsule_DetectionSensor::state_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg )
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
            actionchain_____Debug__C__init__new_transition_27( msg );
            return junction_____Debug__C__init__new_exitpoint_3( msg );
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

Capsule_DetectionSensor::State Capsule_DetectionSensor::state_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg )
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
            actionchain_____Debug__C__init__new_transition_25( msg );
            return junction_____Debug__C__init__new_exitpoint_3( msg );
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

Capsule_DetectionSensor::State Capsule_DetectionSensor::state_____Debug__C__init__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__init__new_transition_28( msg );
            return junction_____Debug__C__init__new_exitpoint_3( msg );
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

Capsule_DetectionSensor::State Capsule_DetectionSensor::state_____Debug__C__start_detecting__Debug__A__Ac__start_detecting( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__start_detecting__Debug__En__DETECTING( msg );
            return Debug__C__start_detecting__Debug__A__En__DETECTING;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__start_detecting__new_transition_8( msg );
            return junction_____Debug__C__start_detecting__new_exitpoint_1( msg );
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

Capsule_DetectionSensor::State Capsule_DetectionSensor::state_____Debug__C__start_detecting__Debug__A__En__DETECTING( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__start_detecting__Debug__end__trans__start_detecting( msg );
            return junction_____Debug__C__start_detecting__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__start_detecting__new_transition_9( msg );
            return junction_____Debug__C__start_detecting__new_exitpoint_1( msg );
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

Capsule_DetectionSensor::State Capsule_DetectionSensor::state_____Debug__C__start_detecting__Debug__B__Ac__start_detecting( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__start_detecting__Debug__AC__start_detecting( msg );
            return Debug__C__start_detecting__Debug__A__Ac__start_detecting;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__start_detecting__new_transition_7( msg );
            return junction_____Debug__C__start_detecting__new_exitpoint_1( msg );
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

Capsule_DetectionSensor::State Capsule_DetectionSensor::state_____Debug__C__start_detecting__Debug__B__Ex__IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__start_detecting__Debug__Ex__IDLE( msg );
            return Debug__C__start_detecting__Debug__B__Ac__start_detecting;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__start_detecting__new_transition_6( msg );
            return junction_____Debug__C__start_detecting__new_exitpoint_1( msg );
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

Capsule_DetectionSensor::State Capsule_DetectionSensor::state_____Debug__C__start_detecting__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__start_detecting__new_transition_10( msg );
            return junction_____Debug__C__start_detecting__new_exitpoint_1( msg );
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

Capsule_DetectionSensor::State Capsule_DetectionSensor::state_____Debug__C__stop_detecting__Debug__A__Ac__stop_detecting( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stop_detecting__Debug__En__IDLE( msg );
            return Debug__C__stop_detecting__Debug__A__En__IDLE;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_detecting__new_transition_18( msg );
            return junction_____Debug__C__stop_detecting__new_exitpoint_2( msg );
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

Capsule_DetectionSensor::State Capsule_DetectionSensor::state_____Debug__C__stop_detecting__Debug__A__En__IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stop_detecting__Debug__end__trans__stop_detecting( msg );
            return junction_____Debug__C__stop_detecting__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_detecting__new_transition_19( msg );
            return junction_____Debug__C__stop_detecting__new_exitpoint_2( msg );
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

Capsule_DetectionSensor::State Capsule_DetectionSensor::state_____Debug__C__stop_detecting__Debug__B__Ac__stop_detecting( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stop_detecting__Debug__AC__stop_detecting( msg );
            return Debug__C__stop_detecting__Debug__A__Ac__stop_detecting;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_detecting__new_transition_17( msg );
            return junction_____Debug__C__stop_detecting__new_exitpoint_2( msg );
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

Capsule_DetectionSensor::State Capsule_DetectionSensor::state_____Debug__C__stop_detecting__Debug__B__Ex__DETECTING( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stop_detecting__Debug__Ex__DETECTING( msg );
            return Debug__C__stop_detecting__Debug__B__Ac__stop_detecting;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_detecting__new_transition_16( msg );
            return junction_____Debug__C__stop_detecting__new_exitpoint_2( msg );
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

Capsule_DetectionSensor::State Capsule_DetectionSensor::state_____Debug__C__stop_detecting__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stop_detecting__new_transition_20( msg );
            return junction_____Debug__C__stop_detecting__new_exitpoint_2( msg );
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

Capsule_DetectionSensor::State Capsule_DetectionSensor::state_____Debug__InitState( const UMLRTMessage * msg )
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

Capsule_DetectionSensor::State Capsule_DetectionSensor::state_____IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_detection:
        switch( msg->getSignalId() )
        {
        case Detection::signal_startDetection:
            actionchain_____Debug__start_detecting( msg );
            return choice_____Debug__Path__start_detecting( msg );
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
        Capsule_DetectionSensor::port_extComm,
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
    4,
    portroles_border,
    0,
    NULL
};

