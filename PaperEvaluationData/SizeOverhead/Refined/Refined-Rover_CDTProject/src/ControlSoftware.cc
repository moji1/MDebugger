
#include "ControlSoftware.hh"

#include "Detection.hh"
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

Capsule_ControlSoftware::Capsule_ControlSoftware( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, detection( borderPorts[borderport_detection] )
, engine( borderPorts[borderport_engine] )
, extComm( borderPorts[borderport_extComm] )
, temperature( borderPorts[borderport_temperature] )
, timer( borderPorts[borderport_timer] )
, threshold( 30.0 )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[Debug__C__init] = "Debug__C__init";
    stateNames[Debug__C__lowerThanThreshold] = "Debug__C__lowerThanThreshold";
    stateNames[Debug__C__moving_forward] = "Debug__C__moving_forward";
    stateNames[Debug__C__stopped] = "Debug__C__stopped";
    stateNames[Debug__C__stopped_moving_backwards] = "Debug__C__stopped_moving_backwards";
    stateNames[Debug__C__timeout] = "Debug__C__timeout";
    stateNames[Debug__C__turnedRight] = "Debug__C__turnedRight";
    stateNames[Debug__C__greaterThan] = "Debug__C__greaterThan";
    stateNames[Debug__C__init__Debug__A__Ac__init] = "Debug__C__init__Debug__A__Ac__init";
    stateNames[Debug__C__init__Debug__A__En__init] = "Debug__C__init__Debug__A__En__init";
    stateNames[Debug__C__init__Debug__B__Ac__init] = "Debug__C__init__Debug__B__Ac__init";
    stateNames[Debug__C__init__boundary] = "Debug__C__init__boundary";
    stateNames[Debug__C__lowerThanThreshold__Debug__A__Ac__lowerThanThreshold] = "Debug__C__lowerThanThreshold__Debug__A__Ac__lowerThanThreshold";
    stateNames[Debug__C__lowerThanThreshold__Debug__A__En__STOPPING_MOVING_FORWARD] = "Debug__C__lowerThanThreshold__Debug__A__En__STOPPING_MOVING_FORWARD";
    stateNames[Debug__C__lowerThanThreshold__Debug__B__Ac__lowerThanThreshold] = "Debug__C__lowerThanThreshold__Debug__B__Ac__lowerThanThreshold";
    stateNames[Debug__C__lowerThanThreshold__Debug__B__Ex__MOVING_FORWARD] = "Debug__C__lowerThanThreshold__Debug__B__Ex__MOVING_FORWARD";
    stateNames[Debug__C__lowerThanThreshold__boundary] = "Debug__C__lowerThanThreshold__boundary";
    stateNames[Debug__C__moving_forward__Debug__A__Ac__moving_forward] = "Debug__C__moving_forward__Debug__A__Ac__moving_forward";
    stateNames[Debug__C__moving_forward__Debug__A__En__MOVING_FORWARD] = "Debug__C__moving_forward__Debug__A__En__MOVING_FORWARD";
    stateNames[Debug__C__moving_forward__Debug__B__Ac__moving_forward] = "Debug__C__moving_forward__Debug__B__Ac__moving_forward";
    stateNames[Debug__C__moving_forward__Debug__B__Ex__STANDBY] = "Debug__C__moving_forward__Debug__B__Ex__STANDBY";
    stateNames[Debug__C__moving_forward__boundary] = "Debug__C__moving_forward__boundary";
    stateNames[Debug__C__stopped_moving_backwards__Debug__A__Ac__stopped_moving_backwards] = "Debug__C__stopped_moving_backwards__Debug__A__Ac__stopped_moving_backwards";
    stateNames[Debug__C__stopped_moving_backwards__Debug__A__En__ROTATING] = "Debug__C__stopped_moving_backwards__Debug__A__En__ROTATING";
    stateNames[Debug__C__stopped_moving_backwards__Debug__B__Ac__stopped_moving_backwards] = "Debug__C__stopped_moving_backwards__Debug__B__Ac__stopped_moving_backwards";
    stateNames[Debug__C__stopped_moving_backwards__Debug__B__Ex__STOPPING_MOVING_BACKWARDS] = "Debug__C__stopped_moving_backwards__Debug__B__Ex__STOPPING_MOVING_BACKWARDS";
    stateNames[Debug__C__stopped_moving_backwards__boundary] = "Debug__C__stopped_moving_backwards__boundary";
    stateNames[Debug__C__stopped__Debug__A__Ac__stopped] = "Debug__C__stopped__Debug__A__Ac__stopped";
    stateNames[Debug__C__stopped__Debug__A__En__MOVING_BACKWARDS] = "Debug__C__stopped__Debug__A__En__MOVING_BACKWARDS";
    stateNames[Debug__C__stopped__Debug__B__Ac__stopped] = "Debug__C__stopped__Debug__B__Ac__stopped";
    stateNames[Debug__C__stopped__Debug__B__Ex__STOPPING_MOVING_FORWARD] = "Debug__C__stopped__Debug__B__Ex__STOPPING_MOVING_FORWARD";
    stateNames[Debug__C__stopped__boundary] = "Debug__C__stopped__boundary";
    stateNames[Debug__C__timeout__Debug__A__Ac__timeout] = "Debug__C__timeout__Debug__A__Ac__timeout";
    stateNames[Debug__C__timeout__Debug__A__En__STOPPING_MOVING_BACKWARDS] = "Debug__C__timeout__Debug__A__En__STOPPING_MOVING_BACKWARDS";
    stateNames[Debug__C__timeout__Debug__B__Ac__timeout] = "Debug__C__timeout__Debug__B__Ac__timeout";
    stateNames[Debug__C__timeout__Debug__B__Ex__MOVING_BACKWARDS] = "Debug__C__timeout__Debug__B__Ex__MOVING_BACKWARDS";
    stateNames[Debug__C__timeout__boundary] = "Debug__C__timeout__boundary";
    stateNames[Debug__C__turnedRight__Debug__A__Ac__turnedRight] = "Debug__C__turnedRight__Debug__A__Ac__turnedRight";
    stateNames[Debug__C__turnedRight__Debug__A__En__MOVING_FORWARD] = "Debug__C__turnedRight__Debug__A__En__MOVING_FORWARD";
    stateNames[Debug__C__turnedRight__Debug__B__Ac__turnedRight] = "Debug__C__turnedRight__Debug__B__Ac__turnedRight";
    stateNames[Debug__C__turnedRight__Debug__B__Ex__ROTATING] = "Debug__C__turnedRight__Debug__B__Ex__ROTATING";
    stateNames[Debug__C__turnedRight__boundary] = "Debug__C__turnedRight__boundary";
    stateNames[Debug__InitState] = "Debug__InitState";
    stateNames[MOVING_BACKWARDS] = "MOVING_BACKWARDS";
    stateNames[MOVING_FORWARD] = "MOVING_FORWARD";
    stateNames[ROTATING] = "ROTATING";
    stateNames[STANDBY] = "STANDBY";
    stateNames[STOPPING_MOVING_BACKWARDS] = "STOPPING_MOVING_BACKWARDS";
    stateNames[STOPPING_MOVING_FORWARD] = "STOPPING_MOVING_FORWARD";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
    int i = 0;
    while( i < 7 )
        history[i++] = SPECIAL_INTERNAL_STATE_UNVISITED;
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






void Capsule_ControlSoftware::Debug__variablesView()
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware operation Debug__variablesView */
    std::string tempS="";
    tempS.append("threshold,");
    tempS.append("Real,");
    if(threshold!=0){
    char tempR[20];
    sprintf(tempR,"%lf",threshold);
    tempS.append(tempR);
    tempS.append("\n");
    }else{
    tempS.append("0");
    tempS.append("\n");
    }
    if (Debug__variablesData==NULL)
    Debug__variablesData=(char *)malloc(strlen(tempS.c_str())+1);
    else if (strlen(Debug__variablesData)<strlen(tempS.c_str()))
    Debug__variablesData=(char *) realloc(Debug__variablesData,strlen(tempS.c_str())+1);
    strcpy(Debug__variablesData,tempS.c_str());
    /* UMLRTGEN-USERREGION-END */
}

bool Capsule_ControlSoftware::Debug__variablesChange( char * varName, char * varValue )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware operation Debug__variablesChange */
    std::string tempVarName="";
    tempVarName.append(varName);
    if ("threshold"==tempVarName){
    threshold=atof(varValue);
    return true;
    }else 
    return false;
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_ControlSoftware::Debug__sendEvent( debugEvents::EVENTSOURCEKIND eventSourceKind, debugEvents::EVENTTYPE eventType, const char * instanceName, int capsuleIndex, const char * signalName, char * capsuleName, char * sourceName, char * reserve1, char * reserve2, char * reserve3 )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware operation Debug__sendEvent */
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
    case Debug__C__greaterThan:
        currentState = state_____Debug__C__greaterThan( &message );
        break;
    case Debug__InitState:
        currentState = state_____Debug__InitState( &message );
        break;
    case Debug__C__stopped__Debug__B__Ex__STOPPING_MOVING_FORWARD:
        currentState = state_____Debug__C__stopped__Debug__B__Ex__STOPPING_MOVING_FORWARD( &message );
        break;
    case Debug__C__stopped__Debug__B__Ac__stopped:
        currentState = state_____Debug__C__stopped__Debug__B__Ac__stopped( &message );
        break;
    case Debug__C__stopped__Debug__A__Ac__stopped:
        currentState = state_____Debug__C__stopped__Debug__A__Ac__stopped( &message );
        break;
    case Debug__C__stopped__Debug__A__En__MOVING_BACKWARDS:
        currentState = state_____Debug__C__stopped__Debug__A__En__MOVING_BACKWARDS( &message );
        break;
    case Debug__C__stopped__boundary:
        currentState = state_____Debug__C__stopped__boundary( &message );
        break;
    case Debug__C__stopped_moving_backwards__Debug__B__Ex__STOPPING_MOVING_BACKWARDS:
        currentState = state_____Debug__C__stopped_moving_backwards__Debug__B__Ex__STOPPING_MOVING_BACKWARDS( &message );
        break;
    case Debug__C__stopped_moving_backwards__Debug__B__Ac__stopped_moving_backwards:
        currentState = state_____Debug__C__stopped_moving_backwards__Debug__B__Ac__stopped_moving_backwards( &message );
        break;
    case Debug__C__stopped_moving_backwards__Debug__A__Ac__stopped_moving_backwards:
        currentState = state_____Debug__C__stopped_moving_backwards__Debug__A__Ac__stopped_moving_backwards( &message );
        break;
    case Debug__C__stopped_moving_backwards__Debug__A__En__ROTATING:
        currentState = state_____Debug__C__stopped_moving_backwards__Debug__A__En__ROTATING( &message );
        break;
    case Debug__C__stopped_moving_backwards__boundary:
        currentState = state_____Debug__C__stopped_moving_backwards__boundary( &message );
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
    case Debug__C__lowerThanThreshold__Debug__B__Ex__MOVING_FORWARD:
        currentState = state_____Debug__C__lowerThanThreshold__Debug__B__Ex__MOVING_FORWARD( &message );
        break;
    case Debug__C__lowerThanThreshold__Debug__B__Ac__lowerThanThreshold:
        currentState = state_____Debug__C__lowerThanThreshold__Debug__B__Ac__lowerThanThreshold( &message );
        break;
    case Debug__C__lowerThanThreshold__Debug__A__Ac__lowerThanThreshold:
        currentState = state_____Debug__C__lowerThanThreshold__Debug__A__Ac__lowerThanThreshold( &message );
        break;
    case Debug__C__lowerThanThreshold__Debug__A__En__STOPPING_MOVING_FORWARD:
        currentState = state_____Debug__C__lowerThanThreshold__Debug__A__En__STOPPING_MOVING_FORWARD( &message );
        break;
    case Debug__C__lowerThanThreshold__boundary:
        currentState = state_____Debug__C__lowerThanThreshold__boundary( &message );
        break;
    case Debug__C__timeout__Debug__B__Ex__MOVING_BACKWARDS:
        currentState = state_____Debug__C__timeout__Debug__B__Ex__MOVING_BACKWARDS( &message );
        break;
    case Debug__C__timeout__Debug__B__Ac__timeout:
        currentState = state_____Debug__C__timeout__Debug__B__Ac__timeout( &message );
        break;
    case Debug__C__timeout__Debug__A__Ac__timeout:
        currentState = state_____Debug__C__timeout__Debug__A__Ac__timeout( &message );
        break;
    case Debug__C__timeout__Debug__A__En__STOPPING_MOVING_BACKWARDS:
        currentState = state_____Debug__C__timeout__Debug__A__En__STOPPING_MOVING_BACKWARDS( &message );
        break;
    case Debug__C__timeout__boundary:
        currentState = state_____Debug__C__timeout__boundary( &message );
        break;
    case Debug__C__turnedRight__Debug__B__Ex__ROTATING:
        currentState = state_____Debug__C__turnedRight__Debug__B__Ex__ROTATING( &message );
        break;
    case Debug__C__turnedRight__Debug__B__Ac__turnedRight:
        currentState = state_____Debug__C__turnedRight__Debug__B__Ac__turnedRight( &message );
        break;
    case Debug__C__turnedRight__Debug__A__Ac__turnedRight:
        currentState = state_____Debug__C__turnedRight__Debug__A__Ac__turnedRight( &message );
        break;
    case Debug__C__turnedRight__Debug__A__En__MOVING_FORWARD:
        currentState = state_____Debug__C__turnedRight__Debug__A__En__MOVING_FORWARD( &message );
        break;
    case Debug__C__turnedRight__boundary:
        currentState = state_____Debug__C__turnedRight__boundary( &message );
        break;
    case Debug__C__moving_forward__Debug__B__Ex__STANDBY:
        currentState = state_____Debug__C__moving_forward__Debug__B__Ex__STANDBY( &message );
        break;
    case Debug__C__moving_forward__Debug__B__Ac__moving_forward:
        currentState = state_____Debug__C__moving_forward__Debug__B__Ac__moving_forward( &message );
        break;
    case Debug__C__moving_forward__Debug__A__Ac__moving_forward:
        currentState = state_____Debug__C__moving_forward__Debug__A__Ac__moving_forward( &message );
        break;
    case Debug__C__moving_forward__Debug__A__En__MOVING_FORWARD:
        currentState = state_____Debug__C__moving_forward__Debug__A__En__MOVING_FORWARD( &message );
        break;
    case Debug__C__moving_forward__boundary:
        currentState = state_____Debug__C__moving_forward__boundary( &message );
        break;
    default:
        break;
    }
}

void Capsule_ControlSoftware::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Debug__InitDebug( &message );
    currentState = Debug__InitState;
}

const char * Capsule_ControlSoftware::getCurrentStateString() const
{
    return stateNames[currentState];
}





void Capsule_ControlSoftware::save_history( Capsule_ControlSoftware::State compositeState, Capsule_ControlSoftware::State subState )
{
    history[compositeState] = subState;
}

bool Capsule_ControlSoftware::check_history( Capsule_ControlSoftware::State compositeState, Capsule_ControlSoftware::State subState )
{
    return history[compositeState] == subState;
}

void Capsule_ControlSoftware::entryaction_____Debug__C__greaterThan( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__greaterThan entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__init::Debug__A__Ac__init entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__init::Region1::Debug__A__Ac__init",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("init","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("STANDBY","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__init::Debug__A__En__init entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__init::Region1::Debug__A__En__init",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("STANDBY","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__init::Debug__B__Ac__init entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__init::Region1::Debug__B__Ac__init",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("init","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__init__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__lowerThanThreshold__Debug__A__Ac__lowerThanThreshold( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__lowerThanThreshold::Debug__A__Ac__lowerThanThreshold entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__lowerThanThreshold::Region1::Debug__A__Ac__lowerThanThreshold",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("lowerThanThreshold","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("STOPPING_MOVING_FORWARD","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__lowerThanThreshold__Debug__A__En__STOPPING_MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__lowerThanThreshold::Debug__A__En__STOPPING_MOVING_FORWARD entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__lowerThanThreshold::Region1::Debug__A__En__STOPPING_MOVING_FORWARD",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("STOPPING_MOVING_FORWARD","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__lowerThanThreshold__Debug__B__Ac__lowerThanThreshold( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__lowerThanThreshold::Debug__B__Ac__lowerThanThreshold entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__lowerThanThreshold::Region1::Debug__B__Ac__lowerThanThreshold",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("MOVING_FORWARD","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("lowerThanThreshold","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__lowerThanThreshold__Debug__B__Ex__MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__lowerThanThreshold::Debug__B__Ex__MOVING_FORWARD entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__lowerThanThreshold::Region1::Debug__B__Ex__MOVING_FORWARD",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("MOVING_FORWARD","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__lowerThanThreshold__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__moving_forward__Debug__A__Ac__moving_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__moving forward::Debug__A__Ac__moving forward entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__moving forward::Region1::Debug__A__Ac__moving forward",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("moving forward","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("MOVING_FORWARD","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__moving_forward__Debug__A__En__MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__moving forward::Debug__A__En__MOVING_FORWARD entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__moving forward::Region1::Debug__A__En__MOVING_FORWARD",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("MOVING_FORWARD","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__moving_forward__Debug__B__Ac__moving_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__moving forward::Debug__B__Ac__moving forward entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__moving forward::Region1::Debug__B__Ac__moving forward",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("STANDBY","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("moving forward","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__moving_forward__Debug__B__Ex__STANDBY( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__moving forward::Debug__B__Ex__STANDBY entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__moving forward::Region1::Debug__B__Ex__STANDBY",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("STANDBY","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__moving_forward__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__stopped__Debug__A__Ac__stopped( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped::Debug__A__Ac__stopped entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped::Region1::Debug__A__Ac__stopped",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("stopped","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("MOVING_BACKWARDS","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__stopped__Debug__A__En__MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped::Debug__A__En__MOVING_BACKWARDS entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped::Region1::Debug__A__En__MOVING_BACKWARDS",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("MOVING_BACKWARDS","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__stopped__Debug__B__Ac__stopped( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped::Debug__B__Ac__stopped entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped::Region1::Debug__B__Ac__stopped",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("STOPPING_MOVING_FORWARD","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("stopped","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__stopped__Debug__B__Ex__STOPPING_MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped::Debug__B__Ex__STOPPING_MOVING_FORWARD entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped::Region1::Debug__B__Ex__STOPPING_MOVING_FORWARD",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("STOPPING_MOVING_FORWARD","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__stopped__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__stopped_moving_backwards__Debug__A__Ac__stopped_moving_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped moving backwards::Debug__A__Ac__stopped moving backwards entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped moving backwards::Region1::Debug__A__Ac__stopped moving backwards",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("stopped moving backwards","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("ROTATING","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__stopped_moving_backwards__Debug__A__En__ROTATING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped moving backwards::Debug__A__En__ROTATING entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped moving backwards::Region1::Debug__A__En__ROTATING",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("ROTATING","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__stopped_moving_backwards__Debug__B__Ac__stopped_moving_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped moving backwards::Debug__B__Ac__stopped moving backwards entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped moving backwards::Region1::Debug__B__Ac__stopped moving backwards",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("STOPPING_MOVING_BACKWARDS","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("stopped moving backwards","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__stopped_moving_backwards__Debug__B__Ex__STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped moving backwards::Debug__B__Ex__STOPPING_MOVING_BACKWARDS entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped moving backwards::Region1::Debug__B__Ex__STOPPING_MOVING_BACKWARDS",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("STOPPING_MOVING_BACKWARDS","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__stopped_moving_backwards__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__timeout__Debug__A__Ac__timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__timeout::Debug__A__Ac__timeout entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__timeout::Region1::Debug__A__Ac__timeout",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("timeout","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("STOPPING_MOVING_BACKWARDS","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__timeout__Debug__A__En__STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__timeout::Debug__A__En__STOPPING_MOVING_BACKWARDS entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__timeout::Region1::Debug__A__En__STOPPING_MOVING_BACKWARDS",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("STOPPING_MOVING_BACKWARDS","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__timeout__Debug__B__Ac__timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__timeout::Debug__B__Ac__timeout entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__timeout::Region1::Debug__B__Ac__timeout",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("MOVING_BACKWARDS","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("timeout","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__timeout__Debug__B__Ex__MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__timeout::Debug__B__Ex__MOVING_BACKWARDS entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__timeout::Region1::Debug__B__Ex__MOVING_BACKWARDS",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("MOVING_BACKWARDS","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__timeout__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__turnedRight__Debug__A__Ac__turnedRight( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__turnedRight::Debug__A__Ac__turnedRight entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__turnedRight::Region1::Debug__A__Ac__turnedRight",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("turnedRight","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("MOVING_FORWARD","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__turnedRight__Debug__A__En__MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__turnedRight::Debug__A__En__MOVING_FORWARD entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__turnedRight::Region1::Debug__A__En__MOVING_FORWARD",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("MOVING_FORWARD","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__turnedRight__Debug__B__Ac__turnedRight( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__turnedRight::Debug__B__Ac__turnedRight entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__turnedRight::Region1::Debug__B__Ac__turnedRight",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("ROTATING","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("turnedRight","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__turnedRight__Debug__B__Ex__ROTATING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__turnedRight::Debug__B__Ex__ROTATING entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__turnedRight::Region1::Debug__B__Ex__ROTATING",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("ROTATING","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__C__turnedRight__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__InitState entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::MOVING_BACKWARDS entry  */
    if( not Debug__SRO.checkDebug("MOVING_BACKWARDS",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::MOVING_BACKWARDS",(char *)"",(char *)"",(char *)"");
    log.log("moving bacwards");
    engine.moveBackwards().send();
    timer.informIn(UMLRTTimespec(1,0));}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::MOVING_FORWARD entry  */
    if( not Debug__SRO.checkDebug("MOVING_FORWARD",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::MOVING_FORWARD",(char *)"",(char *)"",(char *)"");
    log.log ("moving forward");
    engine.moveForward().send();
    detection.startDetection().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____ROTATING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::ROTATING entry  */
    if( not Debug__SRO.checkDebug("ROTATING",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::ROTATING",(char *)"",(char *)"",(char *)"");
    log.log("rotating");
    engine.turnRight(138).send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____STANDBY( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::STANDBY entry  */
    if( not Debug__SRO.checkDebug("STANDBY",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::STANDBY",(char *)"",(char *)"",(char *)"");
    timer.informIn(UMLRTTimespec(4,0));
    log.log ("ControlSoftware standing by");}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::STOPPING_MOVING_BACKWARDS entry  */
    if( not Debug__SRO.checkDebug("STOPPING_MOVING_BACKWARDS",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::STOPPING_MOVING_BACKWARDS",(char *)"",(char *)"",(char *)"");
    log.log("stopping moving backwards");
    engine.stop().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::entryaction_____STOPPING_MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::STOPPING_MOVING_FORWARD entry  */
    if( not Debug__SRO.checkDebug("STOPPING_MOVING_FORWARD",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::STOPPING_MOVING_FORWARD",(char *)"",(char *)"",(char *)"");
    log.log("Stopping moving forwards");
    engine.stop().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__greaterThan( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__greaterThan exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__init::Debug__A__Ac__init exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__init::Region1::Debug__A__Ac__init",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__init::Debug__A__En__init exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__init::Region1::Debug__A__En__init",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__init::Debug__B__Ac__init exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__init::Region1::Debug__B__Ac__init",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__init__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__lowerThanThreshold__Debug__A__Ac__lowerThanThreshold( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__lowerThanThreshold::Debug__A__Ac__lowerThanThreshold exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__lowerThanThreshold::Region1::Debug__A__Ac__lowerThanThreshold",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__lowerThanThreshold__Debug__A__En__STOPPING_MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__lowerThanThreshold::Debug__A__En__STOPPING_MOVING_FORWARD exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__lowerThanThreshold::Region1::Debug__A__En__STOPPING_MOVING_FORWARD",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__lowerThanThreshold__Debug__B__Ac__lowerThanThreshold( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__lowerThanThreshold::Debug__B__Ac__lowerThanThreshold exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__lowerThanThreshold::Region1::Debug__B__Ac__lowerThanThreshold",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__lowerThanThreshold__Debug__B__Ex__MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__lowerThanThreshold::Debug__B__Ex__MOVING_FORWARD exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__lowerThanThreshold::Region1::Debug__B__Ex__MOVING_FORWARD",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__lowerThanThreshold__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__moving_forward__Debug__A__Ac__moving_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__moving forward::Debug__A__Ac__moving forward exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__moving forward::Region1::Debug__A__Ac__moving forward",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__moving_forward__Debug__A__En__MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__moving forward::Debug__A__En__MOVING_FORWARD exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__moving forward::Region1::Debug__A__En__MOVING_FORWARD",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__moving_forward__Debug__B__Ac__moving_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__moving forward::Debug__B__Ac__moving forward exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__moving forward::Region1::Debug__B__Ac__moving forward",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__moving_forward__Debug__B__Ex__STANDBY( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__moving forward::Debug__B__Ex__STANDBY exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__moving forward::Region1::Debug__B__Ex__STANDBY",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__moving_forward__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__stopped__Debug__A__Ac__stopped( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped::Debug__A__Ac__stopped exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped::Region1::Debug__A__Ac__stopped",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__stopped__Debug__A__En__MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped::Debug__A__En__MOVING_BACKWARDS exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped::Region1::Debug__A__En__MOVING_BACKWARDS",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__stopped__Debug__B__Ac__stopped( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped::Debug__B__Ac__stopped exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped::Region1::Debug__B__Ac__stopped",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__stopped__Debug__B__Ex__STOPPING_MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped::Debug__B__Ex__STOPPING_MOVING_FORWARD exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped::Region1::Debug__B__Ex__STOPPING_MOVING_FORWARD",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__stopped__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__stopped_moving_backwards__Debug__A__Ac__stopped_moving_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped moving backwards::Debug__A__Ac__stopped moving backwards exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped moving backwards::Region1::Debug__A__Ac__stopped moving backwards",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__stopped_moving_backwards__Debug__A__En__ROTATING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped moving backwards::Debug__A__En__ROTATING exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped moving backwards::Region1::Debug__A__En__ROTATING",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__stopped_moving_backwards__Debug__B__Ac__stopped_moving_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped moving backwards::Debug__B__Ac__stopped moving backwards exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped moving backwards::Region1::Debug__B__Ac__stopped moving backwards",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__stopped_moving_backwards__Debug__B__Ex__STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped moving backwards::Debug__B__Ex__STOPPING_MOVING_BACKWARDS exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped moving backwards::Region1::Debug__B__Ex__STOPPING_MOVING_BACKWARDS",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__stopped_moving_backwards__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__timeout__Debug__A__Ac__timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__timeout::Debug__A__Ac__timeout exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__timeout::Region1::Debug__A__Ac__timeout",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__timeout__Debug__A__En__STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__timeout::Debug__A__En__STOPPING_MOVING_BACKWARDS exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__timeout::Region1::Debug__A__En__STOPPING_MOVING_BACKWARDS",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__timeout__Debug__B__Ac__timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__timeout::Debug__B__Ac__timeout exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__timeout::Region1::Debug__B__Ac__timeout",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__timeout__Debug__B__Ex__MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__timeout::Debug__B__Ex__MOVING_BACKWARDS exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__timeout::Region1::Debug__B__Ex__MOVING_BACKWARDS",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__timeout__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__turnedRight__Debug__A__Ac__turnedRight( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__turnedRight::Debug__A__Ac__turnedRight exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__turnedRight::Region1::Debug__A__Ac__turnedRight",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__turnedRight__Debug__A__En__MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__turnedRight::Debug__A__En__MOVING_FORWARD exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__turnedRight::Region1::Debug__A__En__MOVING_FORWARD",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__turnedRight__Debug__B__Ac__turnedRight( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__turnedRight::Debug__B__Ac__turnedRight exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__turnedRight::Region1::Debug__B__Ac__turnedRight",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__turnedRight__Debug__B__Ex__ROTATING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__turnedRight::Debug__B__Ex__ROTATING exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__turnedRight::Region1::Debug__B__Ex__ROTATING",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__C__turnedRight__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__InitState exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::MOVING_BACKWARDS exit  */
    if( not Debug__SRO.checkDebug("MOVING_BACKWARDS",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::MOVING_BACKWARDS",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define umlrtparam_distance ( *(double *)msg->getParam( 0 ) )
    #define rtdata ( (double *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::MOVING_FORWARD exit  */
    if( not Debug__SRO.checkDebug("MOVING_FORWARD",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::MOVING_FORWARD",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_distance
}

void Capsule_ControlSoftware::exitaction_____ROTATING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::ROTATING exit  */
    if( not Debug__SRO.checkDebug("ROTATING",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::ROTATING",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____STANDBY( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::STANDBY exit  */
    if( not Debug__SRO.checkDebug("STANDBY",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::STANDBY",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::STOPPING_MOVING_BACKWARDS exit  */
    if( not Debug__SRO.checkDebug("STOPPING_MOVING_BACKWARDS",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::STOPPING_MOVING_BACKWARDS",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::exitaction_____STOPPING_MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::STOPPING_MOVING_FORWARD exit  */
    if( not Debug__SRO.checkDebug("STOPPING_MOVING_FORWARD",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::STOPPING_MOVING_FORWARD",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__init__Debug__Ac__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__init transition Debug__C__init::Debug__B__Ac__init,Debug__C__init::Debug__A__Ac__init,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__init::Region1::Debug__Ac__init",(char *)"Debug__B__Ac__init",(char *)"Debug__A__Ac__init",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__init__Debug__En__STANDBY( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__init transition Debug__C__init::Debug__A__Ac__init,Debug__C__init::Debug__A__En__init,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__init::Region1::Debug__En__STANDBY",(char *)"Debug__A__Ac__init",(char *)"Debug__A__En__init",(char *)"");
    timer.informIn(UMLRTTimespec(4,0));
    log.log ("ControlSoftware standing by");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__init__Debug__end__trans__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__init transition Debug__C__init::Debug__A__En__init,Debug__C__init::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__init::Region1::Debug__end__trans__init",(char *)"Debug__A__En__init",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__init__Debug__init__trans__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__init transition Debug__C__init::en,Debug__C__init::Debug__B__Ac__init */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__init::Region1::Debug__init__trans__init",(char *)"en",(char *)"Debug__B__Ac__init",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__lowerThanThreshold__Debug__AC__lowerThanThreshold( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #define umlrtparam_distance ( *(double *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__lowerThanThreshold transition Debug__C__lowerThanThreshold::Debug__B__Ac__lowerThanThreshold,Debug__C__lowerThanThreshold::Debug__A__Ac__lowerThanThreshold,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__lowerThanThreshold::Region1::Debug__AC__lowerThanThreshold",(char *)"Debug__B__Ac__lowerThanThreshold",(char *)"Debug__A__Ac__lowerThanThreshold",(char *)"");
    log.log ("distance less than threshold: %f < %f", umlrtparam_distance, threshold);
    detection.stopDetection().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__lowerThanThreshold__Debug__En__STOPPING_MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__lowerThanThreshold transition Debug__C__lowerThanThreshold::Debug__A__Ac__lowerThanThreshold,Debug__C__lowerThanThreshold::Debug__A__En__STOPPING_MOVING_FORWARD,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__lowerThanThreshold::Region1::Debug__En__STOPPING_MOVING_FORWARD",(char *)"Debug__A__Ac__lowerThanThreshold",(char *)"Debug__A__En__STOPPING_MOVING_FORWARD",(char *)"");
    log.log("Stopping moving forwards");
    engine.stop().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__lowerThanThreshold__Debug__Ex__MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__lowerThanThreshold transition Debug__C__lowerThanThreshold::Debug__B__Ex__MOVING_FORWARD,Debug__C__lowerThanThreshold::Debug__B__Ac__lowerThanThreshold,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__lowerThanThreshold::Region1::Debug__Ex__MOVING_FORWARD",(char *)"Debug__B__Ex__MOVING_FORWARD",(char *)"Debug__B__Ac__lowerThanThreshold",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__lowerThanThreshold__Debug__end__trans__lowerThanThreshold( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__lowerThanThreshold transition Debug__C__lowerThanThreshold::Debug__A__En__STOPPING_MOVING_FORWARD,Debug__C__lowerThanThreshold::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__lowerThanThreshold::Region1::Debug__end__trans__lowerThanThreshold",(char *)"Debug__A__En__STOPPING_MOVING_FORWARD",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__lowerThanThreshold__Debug__init__trans__lowerThanThreshold( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__lowerThanThreshold transition Debug__C__lowerThanThreshold::en,Debug__C__lowerThanThreshold::Debug__B__Ex__MOVING_FORWARD */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__lowerThanThreshold::Region1::Debug__init__trans__lowerThanThreshold",(char *)"en",(char *)"Debug__B__Ex__MOVING_FORWARD",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__moving_forward__Debug__AC__moving_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__moving forward transition Debug__C__moving forward::Debug__B__Ac__moving forward,Debug__C__moving forward::Debug__A__Ac__moving forward,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__moving forward::Region1::Debug__AC__moving forward",(char *)"Debug__B__Ac__moving forward",(char *)"Debug__A__Ac__moving forward",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__moving_forward__Debug__En__MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__moving forward transition Debug__C__moving forward::Debug__A__Ac__moving forward,Debug__C__moving forward::Debug__A__En__MOVING_FORWARD,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__moving forward::Region1::Debug__En__MOVING_FORWARD",(char *)"Debug__A__Ac__moving forward",(char *)"Debug__A__En__MOVING_FORWARD",(char *)"");
    log.log ("moving forward");
    engine.moveForward().send();
    detection.startDetection().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__moving_forward__Debug__Ex__STANDBY( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__moving forward transition Debug__C__moving forward::Debug__B__Ex__STANDBY,Debug__C__moving forward::Debug__B__Ac__moving forward,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__moving forward::Region1::Debug__Ex__STANDBY",(char *)"Debug__B__Ex__STANDBY",(char *)"Debug__B__Ac__moving forward",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__moving_forward__Debug__end__trans__moving_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__moving forward transition Debug__C__moving forward::Debug__A__En__MOVING_FORWARD,Debug__C__moving forward::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__moving forward::Region1::Debug__end__trans__moving forward",(char *)"Debug__A__En__MOVING_FORWARD",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__moving_forward__Debug__init__trans__moving_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__moving forward transition Debug__C__moving forward::en,Debug__C__moving forward::Debug__B__Ex__STANDBY */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__moving forward::Region1::Debug__init__trans__moving forward",(char *)"en",(char *)"Debug__B__Ex__STANDBY",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__stopped__Debug__AC__stopped( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped transition Debug__C__stopped::Debug__B__Ac__stopped,Debug__C__stopped::Debug__A__Ac__stopped,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped::Region1::Debug__AC__stopped",(char *)"Debug__B__Ac__stopped",(char *)"Debug__A__Ac__stopped",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__stopped__Debug__En__MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped transition Debug__C__stopped::Debug__A__Ac__stopped,Debug__C__stopped::Debug__A__En__MOVING_BACKWARDS,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped::Region1::Debug__En__MOVING_BACKWARDS",(char *)"Debug__A__Ac__stopped",(char *)"Debug__A__En__MOVING_BACKWARDS",(char *)"");
    log.log("moving bacwards");
    engine.moveBackwards().send();
    timer.informIn(UMLRTTimespec(1,0));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__stopped__Debug__Ex__STOPPING_MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped transition Debug__C__stopped::Debug__B__Ex__STOPPING_MOVING_FORWARD,Debug__C__stopped::Debug__B__Ac__stopped,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped::Region1::Debug__Ex__STOPPING_MOVING_FORWARD",(char *)"Debug__B__Ex__STOPPING_MOVING_FORWARD",(char *)"Debug__B__Ac__stopped",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__stopped__Debug__end__trans__stopped( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped transition Debug__C__stopped::Debug__A__En__MOVING_BACKWARDS,Debug__C__stopped::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped::Region1::Debug__end__trans__stopped",(char *)"Debug__A__En__MOVING_BACKWARDS",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__stopped__Debug__init__trans__stopped( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped transition Debug__C__stopped::en,Debug__C__stopped::Debug__B__Ex__STOPPING_MOVING_FORWARD */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped::Region1::Debug__init__trans__stopped",(char *)"en",(char *)"Debug__B__Ex__STOPPING_MOVING_FORWARD",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__stopped_moving_backwards__Debug__AC__stopped_moving_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped moving backwards transition Debug__C__stopped moving backwards::Debug__B__Ac__stopped moving backwards,Debug__C__stopped moving backwards::Debug__A__Ac__stopped moving backwards,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped moving backwards::Region1::Debug__AC__stopped moving backwards",(char *)"Debug__B__Ac__stopped moving backwards",(char *)"Debug__A__Ac__stopped moving backwards",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__stopped_moving_backwards__Debug__En__ROTATING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped moving backwards transition Debug__C__stopped moving backwards::Debug__A__Ac__stopped moving backwards,Debug__C__stopped moving backwards::Debug__A__En__ROTATING,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped moving backwards::Region1::Debug__En__ROTATING",(char *)"Debug__A__Ac__stopped moving backwards",(char *)"Debug__A__En__ROTATING",(char *)"");
    log.log("rotating");
    engine.turnRight(138).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__stopped_moving_backwards__Debug__Ex__STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped moving backwards transition Debug__C__stopped moving backwards::Debug__B__Ex__STOPPING_MOVING_BACKWARDS,Debug__C__stopped moving backwards::Debug__B__Ac__stopped moving backwards,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped moving backwards::Region1::Debug__Ex__STOPPING_MOVING_BACKWARDS",(char *)"Debug__B__Ex__STOPPING_MOVING_BACKWARDS",(char *)"Debug__B__Ac__stopped moving backwards",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__stopped_moving_backwards__Debug__end__trans__stopped_moving_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped moving backwards transition Debug__C__stopped moving backwards::Debug__A__En__ROTATING,Debug__C__stopped moving backwards::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped moving backwards::Region1::Debug__end__trans__stopped moving backwards",(char *)"Debug__A__En__ROTATING",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__stopped_moving_backwards__Debug__init__trans__stopped_moving_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__stopped moving backwards transition Debug__C__stopped moving backwards::en,Debug__C__stopped moving backwards::Debug__B__Ex__STOPPING_MOVING_BACKWARDS */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__stopped moving backwards::Region1::Debug__init__trans__stopped moving backwards",(char *)"en",(char *)"Debug__B__Ex__STOPPING_MOVING_BACKWARDS",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__timeout__Debug__AC__timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__timeout transition Debug__C__timeout::Debug__B__Ac__timeout,Debug__C__timeout::Debug__A__Ac__timeout,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__timeout::Region1::Debug__AC__timeout",(char *)"Debug__B__Ac__timeout",(char *)"Debug__A__Ac__timeout",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__timeout__Debug__En__STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__timeout transition Debug__C__timeout::Debug__A__Ac__timeout,Debug__C__timeout::Debug__A__En__STOPPING_MOVING_BACKWARDS,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__timeout::Region1::Debug__En__STOPPING_MOVING_BACKWARDS",(char *)"Debug__A__Ac__timeout",(char *)"Debug__A__En__STOPPING_MOVING_BACKWARDS",(char *)"");
    log.log("stopping moving backwards");
    engine.stop().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__timeout__Debug__Ex__MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__timeout transition Debug__C__timeout::Debug__B__Ex__MOVING_BACKWARDS,Debug__C__timeout::Debug__B__Ac__timeout,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__timeout::Region1::Debug__Ex__MOVING_BACKWARDS",(char *)"Debug__B__Ex__MOVING_BACKWARDS",(char *)"Debug__B__Ac__timeout",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__timeout__Debug__end__trans__timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__timeout transition Debug__C__timeout::Debug__A__En__STOPPING_MOVING_BACKWARDS,Debug__C__timeout::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__timeout::Region1::Debug__end__trans__timeout",(char *)"Debug__A__En__STOPPING_MOVING_BACKWARDS",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__timeout__Debug__init__trans__timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__timeout transition Debug__C__timeout::en,Debug__C__timeout::Debug__B__Ex__MOVING_BACKWARDS */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__timeout::Region1::Debug__init__trans__timeout",(char *)"en",(char *)"Debug__B__Ex__MOVING_BACKWARDS",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__turnedRight__Debug__AC__turnedRight( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__turnedRight transition Debug__C__turnedRight::Debug__B__Ac__turnedRight,Debug__C__turnedRight::Debug__A__Ac__turnedRight,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__turnedRight::Region1::Debug__AC__turnedRight",(char *)"Debug__B__Ac__turnedRight",(char *)"Debug__A__Ac__turnedRight",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__turnedRight__Debug__En__MOVING_FORWARD( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__turnedRight transition Debug__C__turnedRight::Debug__A__Ac__turnedRight,Debug__C__turnedRight::Debug__A__En__MOVING_FORWARD,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__turnedRight::Region1::Debug__En__MOVING_FORWARD",(char *)"Debug__A__Ac__turnedRight",(char *)"Debug__A__En__MOVING_FORWARD",(char *)"");
    log.log ("moving forward");
    engine.moveForward().send();
    detection.startDetection().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__turnedRight__Debug__Ex__ROTATING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__turnedRight transition Debug__C__turnedRight::Debug__B__Ex__ROTATING,Debug__C__turnedRight::Debug__B__Ac__turnedRight,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__turnedRight::Region1::Debug__Ex__ROTATING",(char *)"Debug__B__Ex__ROTATING",(char *)"Debug__B__Ac__turnedRight",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__turnedRight__Debug__end__trans__turnedRight( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__turnedRight transition Debug__C__turnedRight::Debug__A__En__MOVING_FORWARD,Debug__C__turnedRight::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__turnedRight::Region1::Debug__end__trans__turnedRight",(char *)"Debug__A__En__MOVING_FORWARD",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__C__turnedRight__Debug__init__trans__turnedRight( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware::Debug__C__turnedRight transition Debug__C__turnedRight::en,Debug__C__turnedRight::Debug__B__Ex__ROTATING */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__C__turnedRight::Region1::Debug__init__trans__turnedRight",(char *)"en",(char *)"Debug__B__Ex__ROTATING",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__InitDebug( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Pseudo1,Debug__InitState */
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

void Capsule_ControlSoftware::transitionaction_____Debug__greaterThan( const UMLRTMessage * msg )
{
    #define umlrtparam_distance ( *(double *)msg->getParam( 0 ) )
    #define rtdata ( (double *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition MOVING_FORWARD,Debug__Path__greaterThan,obstacleDetected:detection */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__greaterThan",(char *)"MOVING_FORWARD",(char *)"Debug__Path__greaterThan",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_distance
}

void Capsule_ControlSoftware::transitionaction_____Debug__greaterThan__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__C__greaterThan,MOVING_FORWARD */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__greaterThan__E",(char *)"ex",(char *)"MOVING_FORWARD",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__greaterThan__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__Path__greaterThan,Debug__C__greaterThan */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__greaterThan__S",(char *)"Debug__Path__greaterThan",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__greaterThan__dbg( const UMLRTMessage * msg )
{
    #define umlrtparam_varName ( *(const char * *)msg->getParam( 0 ) )
    #define umlrtparam_varValue ( *(const char * *)msg->getParam( 1 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__C__greaterThan,Debug__C__greaterThan,dbgVarChange:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__greaterThan__dbg",(char *)"Debug__C__greaterThan",(char *)"Debug__C__greaterThan",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_varValue
    #undef umlrtparam_varName
}

void Capsule_ControlSoftware::transitionaction_____Debug__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__InitState,Debug__Path__init,null:extComm */
    if (this->Debug__SRO.getExecMode()==Stepping){
    Debug__SRO.addTransitionsFromState("MOVING_FORWARD","greaterThan","MOVING_FORWARD","obstacleDetected","Detection");
    Debug__SRO.addTransitionsFromState("ROTATING","turnedRight","MOVING_FORWARD","turnedRight","Engine");
    Debug__SRO.addTransitionsFromState("MOVING_BACKWARDS","timeout","STOPPING_MOVING_BACKWARDS","timeout","Timing");
    Debug__SRO.addTransitionsFromState("STANDBY","moving forward","MOVING_FORWARD","timeout","Timing");
    Debug__SRO.addTransitionsFromState("STOPPING_MOVING_FORWARD","stopped","MOVING_BACKWARDS","stopped","Engine");
    Debug__SRO.addTransitionsFromState("STOPPING_MOVING_BACKWARDS","stopped moving backwards","ROTATING","stopped","Engine");
    Debug__SRO.addTransitionsFromState("MOVING_FORWARD","lowerThanThreshold","STOPPING_MOVING_FORWARD","obstacleDetected","Detection");
    Debug__SRO.addTransitionsFromState("","init","STANDBY","","");
    std::cout<<this->getName()<<": Connection with debugger is in progress\n";
    char  tempS[256];
    sprintf(tempS,"%s%d",this->getName(),(int)this->getIndex());
    extComm.registerToControl(tempS).send();
    Debug__sendEvent(debugEvents::DEBUG,debugEvents::REGISTER,this->getName(),this->getIndex(),msg->getSignalName(),(char *) "",(char *) "",(char *) "",(char *)"",(char *) "");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__init__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__C__init::ex,STANDBY */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__init__E",(char *)"ex",(char *)"STANDBY",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__init__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__Path__init,Debug__C__init::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__init__S",(char *)"Debug__Path__init",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__init__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__C__init::new_exitpoint_3,Debug__C__init */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__init__dbg",(char *)"Debug__C__init",(char *)"Debug__C__init",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__lowerThanThreshold( const UMLRTMessage * msg )
{
    #define umlrtparam_distance ( *(double *)msg->getParam( 0 ) )
    #define rtdata ( (double *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition MOVING_FORWARD,Debug__Path__lowerThanThreshold,obstacleDetected:detection */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__lowerThanThreshold",(char *)"MOVING_FORWARD",(char *)"Debug__Path__lowerThanThreshold",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_distance
}

void Capsule_ControlSoftware::transitionaction_____Debug__lowerThanThreshold__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__C__lowerThanThreshold::ex,STOPPING_MOVING_FORWARD */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__lowerThanThreshold__E",(char *)"ex",(char *)"STOPPING_MOVING_FORWARD",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__lowerThanThreshold__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__Path__lowerThanThreshold,Debug__C__lowerThanThreshold::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__lowerThanThreshold__S",(char *)"Debug__Path__lowerThanThreshold",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__lowerThanThreshold__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__C__lowerThanThreshold::new_exitpoint_4,Debug__C__lowerThanThreshold */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__lowerThanThreshold__dbg",(char *)"Debug__C__lowerThanThreshold",(char *)"Debug__C__lowerThanThreshold",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__moving_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition STANDBY,Debug__Path__moving forward,timeout:timer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__moving forward",(char *)"STANDBY",(char *)"Debug__Path__moving forward",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__moving_forward__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__C__moving forward::ex,MOVING_FORWARD */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__moving forward__E",(char *)"ex",(char *)"MOVING_FORWARD",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__moving_forward__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__Path__moving forward,Debug__C__moving forward::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__moving forward__S",(char *)"Debug__Path__moving forward",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__moving_forward__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__C__moving forward::new_exitpoint_7,Debug__C__moving forward */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__moving forward__dbg",(char *)"Debug__C__moving forward",(char *)"Debug__C__moving forward",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__stopped( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition STOPPING_MOVING_FORWARD,Debug__Path__stopped,stopped:engine */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__stopped",(char *)"STOPPING_MOVING_FORWARD",(char *)"Debug__Path__stopped",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__stopped__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__C__stopped::ex,MOVING_BACKWARDS */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__stopped__E",(char *)"ex",(char *)"MOVING_BACKWARDS",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__stopped__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__Path__stopped,Debug__C__stopped::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__stopped__S",(char *)"Debug__Path__stopped",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__stopped__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__C__stopped::new_exitpoint_1,Debug__C__stopped */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__stopped__dbg",(char *)"Debug__C__stopped",(char *)"Debug__C__stopped",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__stopped_moving_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition STOPPING_MOVING_BACKWARDS,Debug__Path__stopped moving backwards,stopped:engine */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__stopped moving backwards",(char *)"STOPPING_MOVING_BACKWARDS",(char *)"Debug__Path__stopped moving backwards",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__stopped_moving_backwards__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__C__stopped moving backwards::ex,ROTATING */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__stopped moving backwards__E",(char *)"ex",(char *)"ROTATING",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__stopped_moving_backwards__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__Path__stopped moving backwards,Debug__C__stopped moving backwards::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__stopped moving backwards__S",(char *)"Debug__Path__stopped moving backwards",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__stopped_moving_backwards__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__C__stopped moving backwards::new_exitpoint_2,Debug__C__stopped moving backwards */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__stopped moving backwards__dbg",(char *)"Debug__C__stopped moving backwards",(char *)"Debug__C__stopped moving backwards",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition MOVING_BACKWARDS,Debug__Path__timeout,timeout:timer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__timeout",(char *)"MOVING_BACKWARDS",(char *)"Debug__Path__timeout",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__timeout__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__C__timeout::ex,STOPPING_MOVING_BACKWARDS */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__timeout__E",(char *)"ex",(char *)"STOPPING_MOVING_BACKWARDS",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__timeout__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__Path__timeout,Debug__C__timeout::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__timeout__S",(char *)"Debug__Path__timeout",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__timeout__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__C__timeout::new_exitpoint_5,Debug__C__timeout */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__timeout__dbg",(char *)"Debug__C__timeout",(char *)"Debug__C__timeout",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__turnedRight( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition ROTATING,Debug__Path__turnedRight,turnedRight:engine */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__turnedRight",(char *)"ROTATING",(char *)"Debug__Path__turnedRight",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__turnedRight__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__C__turnedRight::ex,MOVING_FORWARD */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__turnedRight__E",(char *)"ex",(char *)"MOVING_FORWARD",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__turnedRight__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__Path__turnedRight,Debug__C__turnedRight::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__turnedRight__S",(char *)"Debug__Path__turnedRight",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____Debug__turnedRight__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__C__turnedRight::new_exitpoint_6,Debug__C__turnedRight */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::Debug__turnedRight__dbg",(char *)"Debug__C__turnedRight",(char *)"Debug__C__turnedRight",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____greaterThan( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #define umlrtparam_distance ( *(double *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__Path__greaterThan,MOVING_FORWARD */
    log.log ("distance greater than threshold: %f > %f", umlrtparam_distance, threshold);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__Path__init,STANDBY */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::init",(char *)"Debug__Path__init",(char *)"STANDBY",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____lowerThanThreshold( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #define umlrtparam_distance ( *(double *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__Path__lowerThanThreshold,STOPPING_MOVING_FORWARD */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::lowerThanThreshold",(char *)"Debug__Path__lowerThanThreshold",(char *)"STOPPING_MOVING_FORWARD",(char *)"");
    log.log ("distance less than threshold: %f < %f", umlrtparam_distance, threshold);
    detection.stopDetection().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____moving_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__Path__moving forward,MOVING_FORWARD */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::moving forward",(char *)"Debug__Path__moving forward",(char *)"MOVING_FORWARD",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____stopped( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__Path__stopped,MOVING_BACKWARDS */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::stopped",(char *)"Debug__Path__stopped",(char *)"MOVING_BACKWARDS",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____stopped_moving_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__Path__stopped moving backwards,ROTATING */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::stopped moving backwards",(char *)"Debug__Path__stopped moving backwards",(char *)"ROTATING",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__Path__timeout,STOPPING_MOVING_BACKWARDS */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::timeout",(char *)"Debug__Path__timeout",(char *)"STOPPING_MOVING_BACKWARDS",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::transitionaction_____turnedRight( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware transition Debug__Path__turnedRight,MOVING_FORWARD */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"rover::ControlSoftware::ControlSoftwareStateMachine::Region::turnedRight",(char *)"Debug__Path__turnedRight",(char *)"MOVING_FORWARD",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_ControlSoftware::action_____Debug__greaterThan__S__Debug__GuardgreaterThan( const UMLRTMessage * msg )
{
    #define umlrtparam_distance ( *(double *)msg->getParam( 0 ) )
    #define rtdata ( (double *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware guard Debug__Path__greaterThan,Debug__C__greaterThan */
    return Debug__SRO.checkDebug("MOVING_FORWARD",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_distance
}

bool Capsule_ControlSoftware::action_____Debug__greaterThan__greaterThanThreshold( const UMLRTMessage * msg )
{
    #define umlrtparam_distance ( *(double *)msg->getParam( 0 ) )
    #define rtdata ( (double *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware guard MOVING_FORWARD,Debug__Path__greaterThan,obstacleDetected:detection */
    return (umlrtparam_distance > threshold) || (umlrtparam_distance < 0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_distance
}

bool Capsule_ControlSoftware::action_____Debug__init__S__Debug__Guardinit( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware guard Debug__Path__init,Debug__C__init::en */
    return Debug__SRO.checkDebug("Pseudo1","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_ControlSoftware::action_____Debug__lowerThanThreshold__S__Debug__GuardlowerThanThreshold( const UMLRTMessage * msg )
{
    #define umlrtparam_distance ( *(double *)msg->getParam( 0 ) )
    #define rtdata ( (double *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware guard Debug__Path__lowerThanThreshold,Debug__C__lowerThanThreshold::en */
    return Debug__SRO.checkDebug("MOVING_FORWARD",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_distance
}

bool Capsule_ControlSoftware::action_____Debug__lowerThanThreshold__lessThanThreshold( const UMLRTMessage * msg )
{
    #define umlrtparam_distance ( *(double *)msg->getParam( 0 ) )
    #define rtdata ( (double *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware guard MOVING_FORWARD,Debug__Path__lowerThanThreshold,obstacleDetected:detection */
    return (umlrtparam_distance < threshold) && (umlrtparam_distance >= 0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_distance
}

bool Capsule_ControlSoftware::action_____Debug__moving_forward__S__Debug__Guardmoving_forward( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware guard Debug__Path__moving forward,Debug__C__moving forward::en */
    return Debug__SRO.checkDebug("STANDBY",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_ControlSoftware::action_____Debug__stopped__S__Debug__Guardstopped( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware guard Debug__Path__stopped,Debug__C__stopped::en */
    return Debug__SRO.checkDebug("STOPPING_MOVING_FORWARD",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_ControlSoftware::action_____Debug__stopped_moving_backwards__S__Debug__Guardstopped_moving_backwards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware guard Debug__Path__stopped moving backwards,Debug__C__stopped moving backwards::en */
    return Debug__SRO.checkDebug("STOPPING_MOVING_BACKWARDS",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_ControlSoftware::action_____Debug__timeout__S__Debug__Guardtimeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware guard Debug__Path__timeout,Debug__C__timeout::en */
    return Debug__SRO.checkDebug("MOVING_BACKWARDS",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_ControlSoftware::action_____Debug__turnedRight__S__Debug__GuardturnedRight( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Rover/rover.uml rover::ControlSoftware guard Debug__Path__turnedRight,Debug__C__turnedRight::en */
    return Debug__SRO.checkDebug("ROTATING",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ControlSoftware::actionchain_____Debug__C__init__Debug__Ac__init( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__B__Ac__init( msg );
    transitionaction_____Debug__C__init__Debug__Ac__init( msg );
    entryaction_____Debug__C__init__Debug__A__Ac__init( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__init__Debug__En__STANDBY( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__A__Ac__init( msg );
    transitionaction_____Debug__C__init__Debug__En__STANDBY( msg );
    entryaction_____Debug__C__init__Debug__A__En__init( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__init__Debug__end__trans__init( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__A__En__init( msg );
    transitionaction_____Debug__C__init__Debug__end__trans__init( msg );
    save_history( Debug__C__init, Debug__C__init__Debug__A__En__init );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__init__Debug__init__trans__init( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__init__Debug__init__trans__init( msg );
    entryaction_____Debug__C__init__Debug__B__Ac__init( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__init__new_transition_21( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__Debug__B__Ac__init( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__init__new_transition_22( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__Debug__A__Ac__init( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__init__new_transition_23( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__Debug__A__En__init( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__init__new_transition_24_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__boundary( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__init__new_transition_25( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__B__Ac__init( msg );
    save_history( Debug__C__init, Debug__C__init__Debug__B__Ac__init );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__init__new_transition_26( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__A__Ac__init( msg );
    save_history( Debug__C__init, Debug__C__init__Debug__A__Ac__init );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__init__new_transition_27( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__A__En__init( msg );
    save_history( Debug__C__init, Debug__C__init__Debug__A__En__init );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__init__new_transition_28( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__boundary( msg );
    save_history( Debug__C__init, Debug__C__init__boundary );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__lowerThanThreshold__Debug__AC__lowerThanThreshold( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__lowerThanThreshold__Debug__B__Ac__lowerThanThreshold( msg );
    transitionaction_____Debug__C__lowerThanThreshold__Debug__AC__lowerThanThreshold( msg );
    entryaction_____Debug__C__lowerThanThreshold__Debug__A__Ac__lowerThanThreshold( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__lowerThanThreshold__Debug__En__STOPPING_MOVING_FORWARD( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__lowerThanThreshold__Debug__A__Ac__lowerThanThreshold( msg );
    transitionaction_____Debug__C__lowerThanThreshold__Debug__En__STOPPING_MOVING_FORWARD( msg );
    entryaction_____Debug__C__lowerThanThreshold__Debug__A__En__STOPPING_MOVING_FORWARD( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__lowerThanThreshold__Debug__Ex__MOVING_FORWARD( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__lowerThanThreshold__Debug__B__Ex__MOVING_FORWARD( msg );
    transitionaction_____Debug__C__lowerThanThreshold__Debug__Ex__MOVING_FORWARD( msg );
    entryaction_____Debug__C__lowerThanThreshold__Debug__B__Ac__lowerThanThreshold( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__lowerThanThreshold__Debug__end__trans__lowerThanThreshold( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__lowerThanThreshold__Debug__A__En__STOPPING_MOVING_FORWARD( msg );
    transitionaction_____Debug__C__lowerThanThreshold__Debug__end__trans__lowerThanThreshold( msg );
    save_history( Debug__C__lowerThanThreshold, Debug__C__lowerThanThreshold__Debug__A__En__STOPPING_MOVING_FORWARD );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__lowerThanThreshold__Debug__init__trans__lowerThanThreshold( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__lowerThanThreshold__Debug__init__trans__lowerThanThreshold( msg );
    entryaction_____Debug__C__lowerThanThreshold__Debug__B__Ex__MOVING_FORWARD( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__lowerThanThreshold__new_transition_29( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__lowerThanThreshold__Debug__B__Ex__MOVING_FORWARD( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__lowerThanThreshold__new_transition_30( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__lowerThanThreshold__Debug__B__Ac__lowerThanThreshold( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__lowerThanThreshold__new_transition_31( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__lowerThanThreshold__Debug__A__Ac__lowerThanThreshold( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__lowerThanThreshold__new_transition_32( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__lowerThanThreshold__Debug__A__En__STOPPING_MOVING_FORWARD( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__lowerThanThreshold__new_transition_33_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__lowerThanThreshold__boundary( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__lowerThanThreshold__new_transition_34( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__lowerThanThreshold__Debug__B__Ex__MOVING_FORWARD( msg );
    save_history( Debug__C__lowerThanThreshold, Debug__C__lowerThanThreshold__Debug__B__Ex__MOVING_FORWARD );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__lowerThanThreshold__new_transition_35( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__lowerThanThreshold__Debug__B__Ac__lowerThanThreshold( msg );
    save_history( Debug__C__lowerThanThreshold, Debug__C__lowerThanThreshold__Debug__B__Ac__lowerThanThreshold );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__lowerThanThreshold__new_transition_36( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__lowerThanThreshold__Debug__A__Ac__lowerThanThreshold( msg );
    save_history( Debug__C__lowerThanThreshold, Debug__C__lowerThanThreshold__Debug__A__Ac__lowerThanThreshold );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__lowerThanThreshold__new_transition_37( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__lowerThanThreshold__Debug__A__En__STOPPING_MOVING_FORWARD( msg );
    save_history( Debug__C__lowerThanThreshold, Debug__C__lowerThanThreshold__Debug__A__En__STOPPING_MOVING_FORWARD );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__lowerThanThreshold__new_transition_38( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__lowerThanThreshold__boundary( msg );
    save_history( Debug__C__lowerThanThreshold, Debug__C__lowerThanThreshold__boundary );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__moving_forward__Debug__AC__moving_forward( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__moving_forward__Debug__B__Ac__moving_forward( msg );
    transitionaction_____Debug__C__moving_forward__Debug__AC__moving_forward( msg );
    entryaction_____Debug__C__moving_forward__Debug__A__Ac__moving_forward( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__moving_forward__Debug__En__MOVING_FORWARD( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__moving_forward__Debug__A__Ac__moving_forward( msg );
    transitionaction_____Debug__C__moving_forward__Debug__En__MOVING_FORWARD( msg );
    entryaction_____Debug__C__moving_forward__Debug__A__En__MOVING_FORWARD( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__moving_forward__Debug__Ex__STANDBY( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__moving_forward__Debug__B__Ex__STANDBY( msg );
    transitionaction_____Debug__C__moving_forward__Debug__Ex__STANDBY( msg );
    entryaction_____Debug__C__moving_forward__Debug__B__Ac__moving_forward( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__moving_forward__Debug__end__trans__moving_forward( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__moving_forward__Debug__A__En__MOVING_FORWARD( msg );
    transitionaction_____Debug__C__moving_forward__Debug__end__trans__moving_forward( msg );
    save_history( Debug__C__moving_forward, Debug__C__moving_forward__Debug__A__En__MOVING_FORWARD );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__moving_forward__Debug__init__trans__moving_forward( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__moving_forward__Debug__init__trans__moving_forward( msg );
    entryaction_____Debug__C__moving_forward__Debug__B__Ex__STANDBY( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__moving_forward__new_transition_59( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__moving_forward__Debug__B__Ex__STANDBY( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__moving_forward__new_transition_60( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__moving_forward__Debug__B__Ac__moving_forward( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__moving_forward__new_transition_61( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__moving_forward__Debug__A__Ac__moving_forward( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__moving_forward__new_transition_62( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__moving_forward__Debug__A__En__MOVING_FORWARD( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__moving_forward__new_transition_63_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__moving_forward__boundary( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__moving_forward__new_transition_64( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__moving_forward__Debug__B__Ex__STANDBY( msg );
    save_history( Debug__C__moving_forward, Debug__C__moving_forward__Debug__B__Ex__STANDBY );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__moving_forward__new_transition_65( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__moving_forward__Debug__B__Ac__moving_forward( msg );
    save_history( Debug__C__moving_forward, Debug__C__moving_forward__Debug__B__Ac__moving_forward );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__moving_forward__new_transition_66( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__moving_forward__Debug__A__Ac__moving_forward( msg );
    save_history( Debug__C__moving_forward, Debug__C__moving_forward__Debug__A__Ac__moving_forward );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__moving_forward__new_transition_67( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__moving_forward__Debug__A__En__MOVING_FORWARD( msg );
    save_history( Debug__C__moving_forward, Debug__C__moving_forward__Debug__A__En__MOVING_FORWARD );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__moving_forward__new_transition_68( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__moving_forward__boundary( msg );
    save_history( Debug__C__moving_forward, Debug__C__moving_forward__boundary );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped__Debug__AC__stopped( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stopped__Debug__B__Ac__stopped( msg );
    transitionaction_____Debug__C__stopped__Debug__AC__stopped( msg );
    entryaction_____Debug__C__stopped__Debug__A__Ac__stopped( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped__Debug__En__MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stopped__Debug__A__Ac__stopped( msg );
    transitionaction_____Debug__C__stopped__Debug__En__MOVING_BACKWARDS( msg );
    entryaction_____Debug__C__stopped__Debug__A__En__MOVING_BACKWARDS( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped__Debug__Ex__STOPPING_MOVING_FORWARD( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stopped__Debug__B__Ex__STOPPING_MOVING_FORWARD( msg );
    transitionaction_____Debug__C__stopped__Debug__Ex__STOPPING_MOVING_FORWARD( msg );
    entryaction_____Debug__C__stopped__Debug__B__Ac__stopped( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped__Debug__end__trans__stopped( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stopped__Debug__A__En__MOVING_BACKWARDS( msg );
    transitionaction_____Debug__C__stopped__Debug__end__trans__stopped( msg );
    save_history( Debug__C__stopped, Debug__C__stopped__Debug__A__En__MOVING_BACKWARDS );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped__Debug__init__trans__stopped( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__stopped__Debug__init__trans__stopped( msg );
    entryaction_____Debug__C__stopped__Debug__B__Ex__STOPPING_MOVING_FORWARD( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped__new_transition_1( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stopped__Debug__B__Ex__STOPPING_MOVING_FORWARD( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped__new_transition_10( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stopped__boundary( msg );
    save_history( Debug__C__stopped, Debug__C__stopped__boundary );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped__new_transition_2( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stopped__Debug__B__Ac__stopped( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped__new_transition_3( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stopped__Debug__A__Ac__stopped( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped__new_transition_4( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stopped__Debug__A__En__MOVING_BACKWARDS( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped__new_transition_5_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stopped__boundary( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped__new_transition_6( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stopped__Debug__B__Ex__STOPPING_MOVING_FORWARD( msg );
    save_history( Debug__C__stopped, Debug__C__stopped__Debug__B__Ex__STOPPING_MOVING_FORWARD );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped__new_transition_7( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stopped__Debug__B__Ac__stopped( msg );
    save_history( Debug__C__stopped, Debug__C__stopped__Debug__B__Ac__stopped );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped__new_transition_8( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stopped__Debug__A__Ac__stopped( msg );
    save_history( Debug__C__stopped, Debug__C__stopped__Debug__A__Ac__stopped );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped__new_transition_9( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stopped__Debug__A__En__MOVING_BACKWARDS( msg );
    save_history( Debug__C__stopped, Debug__C__stopped__Debug__A__En__MOVING_BACKWARDS );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped_moving_backwards__Debug__AC__stopped_moving_backwards( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stopped_moving_backwards__Debug__B__Ac__stopped_moving_backwards( msg );
    transitionaction_____Debug__C__stopped_moving_backwards__Debug__AC__stopped_moving_backwards( msg );
    entryaction_____Debug__C__stopped_moving_backwards__Debug__A__Ac__stopped_moving_backwards( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped_moving_backwards__Debug__En__ROTATING( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stopped_moving_backwards__Debug__A__Ac__stopped_moving_backwards( msg );
    transitionaction_____Debug__C__stopped_moving_backwards__Debug__En__ROTATING( msg );
    entryaction_____Debug__C__stopped_moving_backwards__Debug__A__En__ROTATING( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped_moving_backwards__Debug__Ex__STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stopped_moving_backwards__Debug__B__Ex__STOPPING_MOVING_BACKWARDS( msg );
    transitionaction_____Debug__C__stopped_moving_backwards__Debug__Ex__STOPPING_MOVING_BACKWARDS( msg );
    entryaction_____Debug__C__stopped_moving_backwards__Debug__B__Ac__stopped_moving_backwards( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped_moving_backwards__Debug__end__trans__stopped_moving_backwards( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stopped_moving_backwards__Debug__A__En__ROTATING( msg );
    transitionaction_____Debug__C__stopped_moving_backwards__Debug__end__trans__stopped_moving_backwards( msg );
    save_history( Debug__C__stopped_moving_backwards, Debug__C__stopped_moving_backwards__Debug__A__En__ROTATING );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped_moving_backwards__Debug__init__trans__stopped_moving_backwards( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__stopped_moving_backwards__Debug__init__trans__stopped_moving_backwards( msg );
    entryaction_____Debug__C__stopped_moving_backwards__Debug__B__Ex__STOPPING_MOVING_BACKWARDS( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped_moving_backwards__new_transition_11( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stopped_moving_backwards__Debug__B__Ex__STOPPING_MOVING_BACKWARDS( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped_moving_backwards__new_transition_12( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stopped_moving_backwards__Debug__B__Ac__stopped_moving_backwards( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped_moving_backwards__new_transition_13( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stopped_moving_backwards__Debug__A__Ac__stopped_moving_backwards( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped_moving_backwards__new_transition_14( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stopped_moving_backwards__Debug__A__En__ROTATING( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped_moving_backwards__new_transition_15_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__stopped_moving_backwards__boundary( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped_moving_backwards__new_transition_16( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stopped_moving_backwards__Debug__B__Ex__STOPPING_MOVING_BACKWARDS( msg );
    save_history( Debug__C__stopped_moving_backwards, Debug__C__stopped_moving_backwards__Debug__B__Ex__STOPPING_MOVING_BACKWARDS );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped_moving_backwards__new_transition_17( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stopped_moving_backwards__Debug__B__Ac__stopped_moving_backwards( msg );
    save_history( Debug__C__stopped_moving_backwards, Debug__C__stopped_moving_backwards__Debug__B__Ac__stopped_moving_backwards );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped_moving_backwards__new_transition_18( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stopped_moving_backwards__Debug__A__Ac__stopped_moving_backwards( msg );
    save_history( Debug__C__stopped_moving_backwards, Debug__C__stopped_moving_backwards__Debug__A__Ac__stopped_moving_backwards );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped_moving_backwards__new_transition_19( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stopped_moving_backwards__Debug__A__En__ROTATING( msg );
    save_history( Debug__C__stopped_moving_backwards, Debug__C__stopped_moving_backwards__Debug__A__En__ROTATING );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__stopped_moving_backwards__new_transition_20( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stopped_moving_backwards__boundary( msg );
    save_history( Debug__C__stopped_moving_backwards, Debug__C__stopped_moving_backwards__boundary );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__timeout__Debug__AC__timeout( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ac__timeout( msg );
    transitionaction_____Debug__C__timeout__Debug__AC__timeout( msg );
    entryaction_____Debug__C__timeout__Debug__A__Ac__timeout( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__timeout__Debug__En__STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__Ac__timeout( msg );
    transitionaction_____Debug__C__timeout__Debug__En__STOPPING_MOVING_BACKWARDS( msg );
    entryaction_____Debug__C__timeout__Debug__A__En__STOPPING_MOVING_BACKWARDS( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__timeout__Debug__Ex__MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ex__MOVING_BACKWARDS( msg );
    transitionaction_____Debug__C__timeout__Debug__Ex__MOVING_BACKWARDS( msg );
    entryaction_____Debug__C__timeout__Debug__B__Ac__timeout( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__timeout__Debug__end__trans__timeout( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__En__STOPPING_MOVING_BACKWARDS( msg );
    transitionaction_____Debug__C__timeout__Debug__end__trans__timeout( msg );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__A__En__STOPPING_MOVING_BACKWARDS );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__timeout__Debug__init__trans__timeout( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__timeout__Debug__init__trans__timeout( msg );
    entryaction_____Debug__C__timeout__Debug__B__Ex__MOVING_BACKWARDS( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__timeout__new_transition_39( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__timeout__Debug__B__Ex__MOVING_BACKWARDS( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__timeout__new_transition_40( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__timeout__Debug__B__Ac__timeout( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__timeout__new_transition_41( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__timeout__Debug__A__Ac__timeout( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__timeout__new_transition_42( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__timeout__Debug__A__En__STOPPING_MOVING_BACKWARDS( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__timeout__new_transition_43_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__timeout__boundary( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__timeout__new_transition_44( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ex__MOVING_BACKWARDS( msg );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ex__MOVING_BACKWARDS );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__timeout__new_transition_45( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ac__timeout( msg );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ac__timeout );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__timeout__new_transition_46( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__Ac__timeout( msg );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__A__Ac__timeout );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__timeout__new_transition_47( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__En__STOPPING_MOVING_BACKWARDS( msg );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__A__En__STOPPING_MOVING_BACKWARDS );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__timeout__new_transition_48( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__boundary( msg );
    save_history( Debug__C__timeout, Debug__C__timeout__boundary );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__turnedRight__Debug__AC__turnedRight( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turnedRight__Debug__B__Ac__turnedRight( msg );
    transitionaction_____Debug__C__turnedRight__Debug__AC__turnedRight( msg );
    entryaction_____Debug__C__turnedRight__Debug__A__Ac__turnedRight( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__turnedRight__Debug__En__MOVING_FORWARD( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turnedRight__Debug__A__Ac__turnedRight( msg );
    transitionaction_____Debug__C__turnedRight__Debug__En__MOVING_FORWARD( msg );
    entryaction_____Debug__C__turnedRight__Debug__A__En__MOVING_FORWARD( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__turnedRight__Debug__Ex__ROTATING( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turnedRight__Debug__B__Ex__ROTATING( msg );
    transitionaction_____Debug__C__turnedRight__Debug__Ex__ROTATING( msg );
    entryaction_____Debug__C__turnedRight__Debug__B__Ac__turnedRight( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__turnedRight__Debug__end__trans__turnedRight( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turnedRight__Debug__A__En__MOVING_FORWARD( msg );
    transitionaction_____Debug__C__turnedRight__Debug__end__trans__turnedRight( msg );
    save_history( Debug__C__turnedRight, Debug__C__turnedRight__Debug__A__En__MOVING_FORWARD );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__turnedRight__Debug__init__trans__turnedRight( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__turnedRight__Debug__init__trans__turnedRight( msg );
    entryaction_____Debug__C__turnedRight__Debug__B__Ex__ROTATING( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__turnedRight__new_transition_49( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__turnedRight__Debug__B__Ex__ROTATING( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__turnedRight__new_transition_50( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__turnedRight__Debug__B__Ac__turnedRight( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__turnedRight__new_transition_51( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__turnedRight__Debug__A__Ac__turnedRight( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__turnedRight__new_transition_52( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__turnedRight__Debug__A__En__MOVING_FORWARD( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__turnedRight__new_transition_53_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__turnedRight__boundary( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__turnedRight__new_transition_54( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turnedRight__Debug__B__Ex__ROTATING( msg );
    save_history( Debug__C__turnedRight, Debug__C__turnedRight__Debug__B__Ex__ROTATING );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__turnedRight__new_transition_55( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turnedRight__Debug__B__Ac__turnedRight( msg );
    save_history( Debug__C__turnedRight, Debug__C__turnedRight__Debug__B__Ac__turnedRight );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__turnedRight__new_transition_56( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turnedRight__Debug__A__Ac__turnedRight( msg );
    save_history( Debug__C__turnedRight, Debug__C__turnedRight__Debug__A__Ac__turnedRight );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__turnedRight__new_transition_57( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turnedRight__Debug__A__En__MOVING_FORWARD( msg );
    save_history( Debug__C__turnedRight, Debug__C__turnedRight__Debug__A__En__MOVING_FORWARD );
}

void Capsule_ControlSoftware::actionchain_____Debug__C__turnedRight__new_transition_58( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turnedRight__boundary( msg );
    save_history( Debug__C__turnedRight, Debug__C__turnedRight__boundary );
}

void Capsule_ControlSoftware::actionchain_____Debug__InitDebug( const UMLRTMessage * msg )
{
    transitionaction_____Debug__InitDebug( msg );
    entryaction_____Debug__InitState( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__greaterThan( const UMLRTMessage * msg )
{
    exitaction_____MOVING_FORWARD( msg );
    transitionaction_____Debug__greaterThan( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__greaterThan__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__greaterThan( msg );
    transitionaction_____Debug__greaterThan__E( msg );
    entryaction_____MOVING_FORWARD( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__greaterThan__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__greaterThan__S( msg );
    entryaction_____Debug__C__greaterThan( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__greaterThan__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__greaterThan( msg );
    transitionaction_____Debug__greaterThan__dbg( msg );
    entryaction_____Debug__C__greaterThan( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__init( const UMLRTMessage * msg )
{
    exitaction_____Debug__InitState( msg );
    transitionaction_____Debug__init( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__init__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__boundary( msg );
    transitionaction_____Debug__init__E( msg );
    entryaction_____STANDBY( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__init__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__init__S( msg );
    entryaction_____Debug__C__init__boundary( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__init__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__boundary( msg );
    transitionaction_____Debug__init__dbg( msg );
    entryaction_____Debug__C__init__boundary( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__lowerThanThreshold( const UMLRTMessage * msg )
{
    exitaction_____MOVING_FORWARD( msg );
    transitionaction_____Debug__lowerThanThreshold( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__lowerThanThreshold__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__lowerThanThreshold__boundary( msg );
    transitionaction_____Debug__lowerThanThreshold__E( msg );
    entryaction_____STOPPING_MOVING_FORWARD( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__lowerThanThreshold__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__lowerThanThreshold__S( msg );
    entryaction_____Debug__C__lowerThanThreshold__boundary( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__lowerThanThreshold__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__lowerThanThreshold__boundary( msg );
    transitionaction_____Debug__lowerThanThreshold__dbg( msg );
    entryaction_____Debug__C__lowerThanThreshold__boundary( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__moving_forward( const UMLRTMessage * msg )
{
    exitaction_____STANDBY( msg );
    transitionaction_____Debug__moving_forward( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__moving_forward__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__moving_forward__boundary( msg );
    transitionaction_____Debug__moving_forward__E( msg );
    entryaction_____MOVING_FORWARD( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__moving_forward__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__moving_forward__S( msg );
    entryaction_____Debug__C__moving_forward__boundary( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__moving_forward__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__moving_forward__boundary( msg );
    transitionaction_____Debug__moving_forward__dbg( msg );
    entryaction_____Debug__C__moving_forward__boundary( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__stopped( const UMLRTMessage * msg )
{
    exitaction_____STOPPING_MOVING_FORWARD( msg );
    transitionaction_____Debug__stopped( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__stopped__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stopped__boundary( msg );
    transitionaction_____Debug__stopped__E( msg );
    entryaction_____MOVING_BACKWARDS( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__stopped__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__stopped__S( msg );
    entryaction_____Debug__C__stopped__boundary( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__stopped__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stopped__boundary( msg );
    transitionaction_____Debug__stopped__dbg( msg );
    entryaction_____Debug__C__stopped__boundary( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__stopped_moving_backwards( const UMLRTMessage * msg )
{
    exitaction_____STOPPING_MOVING_BACKWARDS( msg );
    transitionaction_____Debug__stopped_moving_backwards( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__stopped_moving_backwards__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stopped_moving_backwards__boundary( msg );
    transitionaction_____Debug__stopped_moving_backwards__E( msg );
    entryaction_____ROTATING( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__stopped_moving_backwards__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__stopped_moving_backwards__S( msg );
    entryaction_____Debug__C__stopped_moving_backwards__boundary( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__stopped_moving_backwards__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__stopped_moving_backwards__boundary( msg );
    transitionaction_____Debug__stopped_moving_backwards__dbg( msg );
    entryaction_____Debug__C__stopped_moving_backwards__boundary( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__timeout( const UMLRTMessage * msg )
{
    exitaction_____MOVING_BACKWARDS( msg );
    transitionaction_____Debug__timeout( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__timeout__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__boundary( msg );
    transitionaction_____Debug__timeout__E( msg );
    entryaction_____STOPPING_MOVING_BACKWARDS( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__timeout__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__timeout__S( msg );
    entryaction_____Debug__C__timeout__boundary( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__timeout__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__boundary( msg );
    transitionaction_____Debug__timeout__dbg( msg );
    entryaction_____Debug__C__timeout__boundary( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__turnedRight( const UMLRTMessage * msg )
{
    exitaction_____ROTATING( msg );
    transitionaction_____Debug__turnedRight( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__turnedRight__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turnedRight__boundary( msg );
    transitionaction_____Debug__turnedRight__E( msg );
    entryaction_____MOVING_FORWARD( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__turnedRight__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__turnedRight__S( msg );
    entryaction_____Debug__C__turnedRight__boundary( msg );
}

void Capsule_ControlSoftware::actionchain_____Debug__turnedRight__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__turnedRight__boundary( msg );
    transitionaction_____Debug__turnedRight__dbg( msg );
    entryaction_____Debug__C__turnedRight__boundary( msg );
}

void Capsule_ControlSoftware::actionchain_____greaterThan( const UMLRTMessage * msg )
{
    transitionaction_____greaterThan( msg );
}

void Capsule_ControlSoftware::actionchain_____init( const UMLRTMessage * msg )
{
    transitionaction_____init( msg );
    entryaction_____STANDBY( msg );
}

void Capsule_ControlSoftware::actionchain_____lowerThanThreshold( const UMLRTMessage * msg )
{
    transitionaction_____lowerThanThreshold( msg );
    entryaction_____STOPPING_MOVING_FORWARD( msg );
}

void Capsule_ControlSoftware::actionchain_____moving_forward( const UMLRTMessage * msg )
{
    transitionaction_____moving_forward( msg );
    entryaction_____MOVING_FORWARD( msg );
}

void Capsule_ControlSoftware::actionchain_____stopped( const UMLRTMessage * msg )
{
    transitionaction_____stopped( msg );
    entryaction_____MOVING_BACKWARDS( msg );
}

void Capsule_ControlSoftware::actionchain_____stopped_moving_backwards( const UMLRTMessage * msg )
{
    transitionaction_____stopped_moving_backwards( msg );
    entryaction_____ROTATING( msg );
}

void Capsule_ControlSoftware::actionchain_____timeout( const UMLRTMessage * msg )
{
    transitionaction_____timeout( msg );
    entryaction_____STOPPING_MOVING_BACKWARDS( msg );
}

void Capsule_ControlSoftware::actionchain_____turnedRight( const UMLRTMessage * msg )
{
    transitionaction_____turnedRight( msg );
    entryaction_____MOVING_FORWARD( msg );
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::junction_____Debug__C__init__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__init__Debug__init__trans__init( msg );
    return Debug__C__init__Debug__B__Ac__init;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::junction_____Debug__C__init__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__init__E( msg );
    return STANDBY;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::junction_____Debug__C__init__new_exitpoint_3( const UMLRTMessage * msg )
{
    actionchain_____Debug__init__dbg( msg );
    return choice_____Debug__C__init__deephistory( msg );
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::junction_____Debug__C__lowerThanThreshold__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__lowerThanThreshold__Debug__init__trans__lowerThanThreshold( msg );
    return Debug__C__lowerThanThreshold__Debug__B__Ex__MOVING_FORWARD;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::junction_____Debug__C__lowerThanThreshold__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__lowerThanThreshold__E( msg );
    return STOPPING_MOVING_FORWARD;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::junction_____Debug__C__lowerThanThreshold__new_exitpoint_4( const UMLRTMessage * msg )
{
    actionchain_____Debug__lowerThanThreshold__dbg( msg );
    return choice_____Debug__C__lowerThanThreshold__deephistory( msg );
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::junction_____Debug__C__moving_forward__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__moving_forward__Debug__init__trans__moving_forward( msg );
    return Debug__C__moving_forward__Debug__B__Ex__STANDBY;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::junction_____Debug__C__moving_forward__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__moving_forward__E( msg );
    return MOVING_FORWARD;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::junction_____Debug__C__moving_forward__new_exitpoint_7( const UMLRTMessage * msg )
{
    actionchain_____Debug__moving_forward__dbg( msg );
    return choice_____Debug__C__moving_forward__deephistory( msg );
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::junction_____Debug__C__stopped__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__stopped__Debug__init__trans__stopped( msg );
    return Debug__C__stopped__Debug__B__Ex__STOPPING_MOVING_FORWARD;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::junction_____Debug__C__stopped__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__stopped__E( msg );
    return MOVING_BACKWARDS;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::junction_____Debug__C__stopped__new_exitpoint_1( const UMLRTMessage * msg )
{
    actionchain_____Debug__stopped__dbg( msg );
    return choice_____Debug__C__stopped__deephistory( msg );
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::junction_____Debug__C__stopped_moving_backwards__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__stopped_moving_backwards__Debug__init__trans__stopped_moving_backwards( msg );
    return Debug__C__stopped_moving_backwards__Debug__B__Ex__STOPPING_MOVING_BACKWARDS;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::junction_____Debug__C__stopped_moving_backwards__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__stopped_moving_backwards__E( msg );
    return ROTATING;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::junction_____Debug__C__stopped_moving_backwards__new_exitpoint_2( const UMLRTMessage * msg )
{
    actionchain_____Debug__stopped_moving_backwards__dbg( msg );
    return choice_____Debug__C__stopped_moving_backwards__deephistory( msg );
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::junction_____Debug__C__timeout__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__timeout__Debug__init__trans__timeout( msg );
    return Debug__C__timeout__Debug__B__Ex__MOVING_BACKWARDS;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::junction_____Debug__C__timeout__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__timeout__E( msg );
    return STOPPING_MOVING_BACKWARDS;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::junction_____Debug__C__timeout__new_exitpoint_5( const UMLRTMessage * msg )
{
    actionchain_____Debug__timeout__dbg( msg );
    return choice_____Debug__C__timeout__deephistory( msg );
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::junction_____Debug__C__turnedRight__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__turnedRight__Debug__init__trans__turnedRight( msg );
    return Debug__C__turnedRight__Debug__B__Ex__ROTATING;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::junction_____Debug__C__turnedRight__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__turnedRight__E( msg );
    return MOVING_FORWARD;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::junction_____Debug__C__turnedRight__new_exitpoint_6( const UMLRTMessage * msg )
{
    actionchain_____Debug__turnedRight__dbg( msg );
    return choice_____Debug__C__turnedRight__deephistory( msg );
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::choice_____Debug__C__init__deephistory( const UMLRTMessage * msg )
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::choice_____Debug__C__lowerThanThreshold__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__lowerThanThreshold, Debug__C__lowerThanThreshold__Debug__B__Ex__MOVING_FORWARD ) )
    {
        actionchain_____Debug__C__lowerThanThreshold__new_transition_29( msg );
        return Debug__C__lowerThanThreshold__Debug__B__Ex__MOVING_FORWARD;
    }
    else if( check_history( Debug__C__lowerThanThreshold, Debug__C__lowerThanThreshold__Debug__B__Ac__lowerThanThreshold ) )
    {
        actionchain_____Debug__C__lowerThanThreshold__new_transition_30( msg );
        return Debug__C__lowerThanThreshold__Debug__B__Ac__lowerThanThreshold;
    }
    else if( check_history( Debug__C__lowerThanThreshold, Debug__C__lowerThanThreshold__Debug__A__Ac__lowerThanThreshold ) )
    {
        actionchain_____Debug__C__lowerThanThreshold__new_transition_31( msg );
        return Debug__C__lowerThanThreshold__Debug__A__Ac__lowerThanThreshold;
    }
    else if( check_history( Debug__C__lowerThanThreshold, Debug__C__lowerThanThreshold__Debug__A__En__STOPPING_MOVING_FORWARD ) )
    {
        actionchain_____Debug__C__lowerThanThreshold__new_transition_32( msg );
        return Debug__C__lowerThanThreshold__Debug__A__En__STOPPING_MOVING_FORWARD;
    }
    else if( check_history( Debug__C__lowerThanThreshold, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__lowerThanThreshold__new_transition_33_to_boundary( msg );
        return Debug__C__lowerThanThreshold__boundary;
    }
    return currentState;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::choice_____Debug__C__moving_forward__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__moving_forward, Debug__C__moving_forward__Debug__B__Ex__STANDBY ) )
    {
        actionchain_____Debug__C__moving_forward__new_transition_59( msg );
        return Debug__C__moving_forward__Debug__B__Ex__STANDBY;
    }
    else if( check_history( Debug__C__moving_forward, Debug__C__moving_forward__Debug__B__Ac__moving_forward ) )
    {
        actionchain_____Debug__C__moving_forward__new_transition_60( msg );
        return Debug__C__moving_forward__Debug__B__Ac__moving_forward;
    }
    else if( check_history( Debug__C__moving_forward, Debug__C__moving_forward__Debug__A__Ac__moving_forward ) )
    {
        actionchain_____Debug__C__moving_forward__new_transition_61( msg );
        return Debug__C__moving_forward__Debug__A__Ac__moving_forward;
    }
    else if( check_history( Debug__C__moving_forward, Debug__C__moving_forward__Debug__A__En__MOVING_FORWARD ) )
    {
        actionchain_____Debug__C__moving_forward__new_transition_62( msg );
        return Debug__C__moving_forward__Debug__A__En__MOVING_FORWARD;
    }
    else if( check_history( Debug__C__moving_forward, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__moving_forward__new_transition_63_to_boundary( msg );
        return Debug__C__moving_forward__boundary;
    }
    return currentState;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::choice_____Debug__C__stopped__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__stopped, Debug__C__stopped__Debug__B__Ex__STOPPING_MOVING_FORWARD ) )
    {
        actionchain_____Debug__C__stopped__new_transition_1( msg );
        return Debug__C__stopped__Debug__B__Ex__STOPPING_MOVING_FORWARD;
    }
    else if( check_history( Debug__C__stopped, Debug__C__stopped__Debug__B__Ac__stopped ) )
    {
        actionchain_____Debug__C__stopped__new_transition_2( msg );
        return Debug__C__stopped__Debug__B__Ac__stopped;
    }
    else if( check_history( Debug__C__stopped, Debug__C__stopped__Debug__A__Ac__stopped ) )
    {
        actionchain_____Debug__C__stopped__new_transition_3( msg );
        return Debug__C__stopped__Debug__A__Ac__stopped;
    }
    else if( check_history( Debug__C__stopped, Debug__C__stopped__Debug__A__En__MOVING_BACKWARDS ) )
    {
        actionchain_____Debug__C__stopped__new_transition_4( msg );
        return Debug__C__stopped__Debug__A__En__MOVING_BACKWARDS;
    }
    else if( check_history( Debug__C__stopped, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__stopped__new_transition_5_to_boundary( msg );
        return Debug__C__stopped__boundary;
    }
    return currentState;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::choice_____Debug__C__stopped_moving_backwards__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__stopped_moving_backwards, Debug__C__stopped_moving_backwards__Debug__B__Ex__STOPPING_MOVING_BACKWARDS ) )
    {
        actionchain_____Debug__C__stopped_moving_backwards__new_transition_11( msg );
        return Debug__C__stopped_moving_backwards__Debug__B__Ex__STOPPING_MOVING_BACKWARDS;
    }
    else if( check_history( Debug__C__stopped_moving_backwards, Debug__C__stopped_moving_backwards__Debug__B__Ac__stopped_moving_backwards ) )
    {
        actionchain_____Debug__C__stopped_moving_backwards__new_transition_12( msg );
        return Debug__C__stopped_moving_backwards__Debug__B__Ac__stopped_moving_backwards;
    }
    else if( check_history( Debug__C__stopped_moving_backwards, Debug__C__stopped_moving_backwards__Debug__A__Ac__stopped_moving_backwards ) )
    {
        actionchain_____Debug__C__stopped_moving_backwards__new_transition_13( msg );
        return Debug__C__stopped_moving_backwards__Debug__A__Ac__stopped_moving_backwards;
    }
    else if( check_history( Debug__C__stopped_moving_backwards, Debug__C__stopped_moving_backwards__Debug__A__En__ROTATING ) )
    {
        actionchain_____Debug__C__stopped_moving_backwards__new_transition_14( msg );
        return Debug__C__stopped_moving_backwards__Debug__A__En__ROTATING;
    }
    else if( check_history( Debug__C__stopped_moving_backwards, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__stopped_moving_backwards__new_transition_15_to_boundary( msg );
        return Debug__C__stopped_moving_backwards__boundary;
    }
    return currentState;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::choice_____Debug__C__timeout__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ex__MOVING_BACKWARDS ) )
    {
        actionchain_____Debug__C__timeout__new_transition_39( msg );
        return Debug__C__timeout__Debug__B__Ex__MOVING_BACKWARDS;
    }
    else if( check_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ac__timeout ) )
    {
        actionchain_____Debug__C__timeout__new_transition_40( msg );
        return Debug__C__timeout__Debug__B__Ac__timeout;
    }
    else if( check_history( Debug__C__timeout, Debug__C__timeout__Debug__A__Ac__timeout ) )
    {
        actionchain_____Debug__C__timeout__new_transition_41( msg );
        return Debug__C__timeout__Debug__A__Ac__timeout;
    }
    else if( check_history( Debug__C__timeout, Debug__C__timeout__Debug__A__En__STOPPING_MOVING_BACKWARDS ) )
    {
        actionchain_____Debug__C__timeout__new_transition_42( msg );
        return Debug__C__timeout__Debug__A__En__STOPPING_MOVING_BACKWARDS;
    }
    else if( check_history( Debug__C__timeout, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__timeout__new_transition_43_to_boundary( msg );
        return Debug__C__timeout__boundary;
    }
    return currentState;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::choice_____Debug__C__turnedRight__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__turnedRight, Debug__C__turnedRight__Debug__B__Ex__ROTATING ) )
    {
        actionchain_____Debug__C__turnedRight__new_transition_49( msg );
        return Debug__C__turnedRight__Debug__B__Ex__ROTATING;
    }
    else if( check_history( Debug__C__turnedRight, Debug__C__turnedRight__Debug__B__Ac__turnedRight ) )
    {
        actionchain_____Debug__C__turnedRight__new_transition_50( msg );
        return Debug__C__turnedRight__Debug__B__Ac__turnedRight;
    }
    else if( check_history( Debug__C__turnedRight, Debug__C__turnedRight__Debug__A__Ac__turnedRight ) )
    {
        actionchain_____Debug__C__turnedRight__new_transition_51( msg );
        return Debug__C__turnedRight__Debug__A__Ac__turnedRight;
    }
    else if( check_history( Debug__C__turnedRight, Debug__C__turnedRight__Debug__A__En__MOVING_FORWARD ) )
    {
        actionchain_____Debug__C__turnedRight__new_transition_52( msg );
        return Debug__C__turnedRight__Debug__A__En__MOVING_FORWARD;
    }
    else if( check_history( Debug__C__turnedRight, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__turnedRight__new_transition_53_to_boundary( msg );
        return Debug__C__turnedRight__boundary;
    }
    return currentState;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::choice_____Debug__Path__greaterThan( const UMLRTMessage * msg )
{
    if( action_____Debug__greaterThan__S__Debug__GuardgreaterThan( msg ) )
    {
        actionchain_____Debug__greaterThan__S( msg );
        return Debug__C__greaterThan;
    }
    else
    {
        actionchain_____greaterThan( msg );
        return MOVING_FORWARD;
    }
    return currentState;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::choice_____Debug__Path__init( const UMLRTMessage * msg )
{
    if( action_____Debug__init__S__Debug__Guardinit( msg ) )
    {
        actionchain_____Debug__init__S( msg );
        return junction_____Debug__C__init__en( msg );
    }
    else
    {
        actionchain_____init( msg );
        return STANDBY;
    }
    return currentState;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::choice_____Debug__Path__lowerThanThreshold( const UMLRTMessage * msg )
{
    if( action_____Debug__lowerThanThreshold__S__Debug__GuardlowerThanThreshold( msg ) )
    {
        actionchain_____Debug__lowerThanThreshold__S( msg );
        return junction_____Debug__C__lowerThanThreshold__en( msg );
    }
    else
    {
        actionchain_____lowerThanThreshold( msg );
        return STOPPING_MOVING_FORWARD;
    }
    return currentState;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::choice_____Debug__Path__moving_forward( const UMLRTMessage * msg )
{
    if( action_____Debug__moving_forward__S__Debug__Guardmoving_forward( msg ) )
    {
        actionchain_____Debug__moving_forward__S( msg );
        return junction_____Debug__C__moving_forward__en( msg );
    }
    else
    {
        actionchain_____moving_forward( msg );
        return MOVING_FORWARD;
    }
    return currentState;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::choice_____Debug__Path__stopped( const UMLRTMessage * msg )
{
    if( action_____Debug__stopped__S__Debug__Guardstopped( msg ) )
    {
        actionchain_____Debug__stopped__S( msg );
        return junction_____Debug__C__stopped__en( msg );
    }
    else
    {
        actionchain_____stopped( msg );
        return MOVING_BACKWARDS;
    }
    return currentState;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::choice_____Debug__Path__stopped_moving_backwards( const UMLRTMessage * msg )
{
    if( action_____Debug__stopped_moving_backwards__S__Debug__Guardstopped_moving_backwards( msg ) )
    {
        actionchain_____Debug__stopped_moving_backwards__S( msg );
        return junction_____Debug__C__stopped_moving_backwards__en( msg );
    }
    else
    {
        actionchain_____stopped_moving_backwards( msg );
        return ROTATING;
    }
    return currentState;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::choice_____Debug__Path__timeout( const UMLRTMessage * msg )
{
    if( action_____Debug__timeout__S__Debug__Guardtimeout( msg ) )
    {
        actionchain_____Debug__timeout__S( msg );
        return junction_____Debug__C__timeout__en( msg );
    }
    else
    {
        actionchain_____timeout( msg );
        return STOPPING_MOVING_BACKWARDS;
    }
    return currentState;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::choice_____Debug__Path__turnedRight( const UMLRTMessage * msg )
{
    if( action_____Debug__turnedRight__S__Debug__GuardturnedRight( msg ) )
    {
        actionchain_____Debug__turnedRight__S( msg );
        return junction_____Debug__C__turnedRight__en( msg );
    }
    else
    {
        actionchain_____turnedRight( msg );
        return MOVING_FORWARD;
    }
    return currentState;
}

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__greaterThan( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__greaterThan__dbg( msg );
            return Debug__C__greaterThan;
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__init__Debug__En__STANDBY( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg )
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg )
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__init__boundary( const UMLRTMessage * msg )
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__lowerThanThreshold__Debug__A__Ac__lowerThanThreshold( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__lowerThanThreshold__Debug__En__STOPPING_MOVING_FORWARD( msg );
            return Debug__C__lowerThanThreshold__Debug__A__En__STOPPING_MOVING_FORWARD;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__lowerThanThreshold__new_transition_36( msg );
            return junction_____Debug__C__lowerThanThreshold__new_exitpoint_4( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__lowerThanThreshold__Debug__A__En__STOPPING_MOVING_FORWARD( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__lowerThanThreshold__Debug__end__trans__lowerThanThreshold( msg );
            return junction_____Debug__C__lowerThanThreshold__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__lowerThanThreshold__new_transition_37( msg );
            return junction_____Debug__C__lowerThanThreshold__new_exitpoint_4( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__lowerThanThreshold__Debug__B__Ac__lowerThanThreshold( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__lowerThanThreshold__Debug__AC__lowerThanThreshold( msg );
            return Debug__C__lowerThanThreshold__Debug__A__Ac__lowerThanThreshold;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__lowerThanThreshold__new_transition_35( msg );
            return junction_____Debug__C__lowerThanThreshold__new_exitpoint_4( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__lowerThanThreshold__Debug__B__Ex__MOVING_FORWARD( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__lowerThanThreshold__Debug__Ex__MOVING_FORWARD( msg );
            return Debug__C__lowerThanThreshold__Debug__B__Ac__lowerThanThreshold;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__lowerThanThreshold__new_transition_34( msg );
            return junction_____Debug__C__lowerThanThreshold__new_exitpoint_4( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__lowerThanThreshold__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__lowerThanThreshold__new_transition_38( msg );
            return junction_____Debug__C__lowerThanThreshold__new_exitpoint_4( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__moving_forward__Debug__A__Ac__moving_forward( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__moving_forward__Debug__En__MOVING_FORWARD( msg );
            return Debug__C__moving_forward__Debug__A__En__MOVING_FORWARD;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__moving_forward__new_transition_66( msg );
            return junction_____Debug__C__moving_forward__new_exitpoint_7( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__moving_forward__Debug__A__En__MOVING_FORWARD( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__moving_forward__Debug__end__trans__moving_forward( msg );
            return junction_____Debug__C__moving_forward__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__moving_forward__new_transition_67( msg );
            return junction_____Debug__C__moving_forward__new_exitpoint_7( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__moving_forward__Debug__B__Ac__moving_forward( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__moving_forward__Debug__AC__moving_forward( msg );
            return Debug__C__moving_forward__Debug__A__Ac__moving_forward;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__moving_forward__new_transition_65( msg );
            return junction_____Debug__C__moving_forward__new_exitpoint_7( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__moving_forward__Debug__B__Ex__STANDBY( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__moving_forward__Debug__Ex__STANDBY( msg );
            return Debug__C__moving_forward__Debug__B__Ac__moving_forward;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__moving_forward__new_transition_64( msg );
            return junction_____Debug__C__moving_forward__new_exitpoint_7( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__moving_forward__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__moving_forward__new_transition_68( msg );
            return junction_____Debug__C__moving_forward__new_exitpoint_7( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__stopped__Debug__A__Ac__stopped( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stopped__Debug__En__MOVING_BACKWARDS( msg );
            return Debug__C__stopped__Debug__A__En__MOVING_BACKWARDS;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stopped__new_transition_8( msg );
            return junction_____Debug__C__stopped__new_exitpoint_1( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__stopped__Debug__A__En__MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stopped__Debug__end__trans__stopped( msg );
            return junction_____Debug__C__stopped__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stopped__new_transition_9( msg );
            return junction_____Debug__C__stopped__new_exitpoint_1( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__stopped__Debug__B__Ac__stopped( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stopped__Debug__AC__stopped( msg );
            return Debug__C__stopped__Debug__A__Ac__stopped;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stopped__new_transition_7( msg );
            return junction_____Debug__C__stopped__new_exitpoint_1( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__stopped__Debug__B__Ex__STOPPING_MOVING_FORWARD( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stopped__Debug__Ex__STOPPING_MOVING_FORWARD( msg );
            return Debug__C__stopped__Debug__B__Ac__stopped;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stopped__new_transition_6( msg );
            return junction_____Debug__C__stopped__new_exitpoint_1( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__stopped__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stopped__new_transition_10( msg );
            return junction_____Debug__C__stopped__new_exitpoint_1( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__stopped_moving_backwards__Debug__A__Ac__stopped_moving_backwards( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stopped_moving_backwards__Debug__En__ROTATING( msg );
            return Debug__C__stopped_moving_backwards__Debug__A__En__ROTATING;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stopped_moving_backwards__new_transition_18( msg );
            return junction_____Debug__C__stopped_moving_backwards__new_exitpoint_2( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__stopped_moving_backwards__Debug__A__En__ROTATING( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stopped_moving_backwards__Debug__end__trans__stopped_moving_backwards( msg );
            return junction_____Debug__C__stopped_moving_backwards__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stopped_moving_backwards__new_transition_19( msg );
            return junction_____Debug__C__stopped_moving_backwards__new_exitpoint_2( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__stopped_moving_backwards__Debug__B__Ac__stopped_moving_backwards( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stopped_moving_backwards__Debug__AC__stopped_moving_backwards( msg );
            return Debug__C__stopped_moving_backwards__Debug__A__Ac__stopped_moving_backwards;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stopped_moving_backwards__new_transition_17( msg );
            return junction_____Debug__C__stopped_moving_backwards__new_exitpoint_2( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__stopped_moving_backwards__Debug__B__Ex__STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__stopped_moving_backwards__Debug__Ex__STOPPING_MOVING_BACKWARDS( msg );
            return Debug__C__stopped_moving_backwards__Debug__B__Ac__stopped_moving_backwards;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stopped_moving_backwards__new_transition_16( msg );
            return junction_____Debug__C__stopped_moving_backwards__new_exitpoint_2( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__stopped_moving_backwards__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__stopped_moving_backwards__new_transition_20( msg );
            return junction_____Debug__C__stopped_moving_backwards__new_exitpoint_2( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__timeout__Debug__A__Ac__timeout( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__timeout__Debug__En__STOPPING_MOVING_BACKWARDS( msg );
            return Debug__C__timeout__Debug__A__En__STOPPING_MOVING_BACKWARDS;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__timeout__new_transition_46( msg );
            return junction_____Debug__C__timeout__new_exitpoint_5( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__timeout__Debug__A__En__STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__timeout__Debug__end__trans__timeout( msg );
            return junction_____Debug__C__timeout__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__timeout__new_transition_47( msg );
            return junction_____Debug__C__timeout__new_exitpoint_5( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__timeout__Debug__B__Ac__timeout( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__timeout__Debug__AC__timeout( msg );
            return Debug__C__timeout__Debug__A__Ac__timeout;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__timeout__new_transition_45( msg );
            return junction_____Debug__C__timeout__new_exitpoint_5( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__timeout__Debug__B__Ex__MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__timeout__Debug__Ex__MOVING_BACKWARDS( msg );
            return Debug__C__timeout__Debug__B__Ac__timeout;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__timeout__new_transition_44( msg );
            return junction_____Debug__C__timeout__new_exitpoint_5( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__timeout__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__timeout__new_transition_48( msg );
            return junction_____Debug__C__timeout__new_exitpoint_5( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__turnedRight__Debug__A__Ac__turnedRight( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__turnedRight__Debug__En__MOVING_FORWARD( msg );
            return Debug__C__turnedRight__Debug__A__En__MOVING_FORWARD;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__turnedRight__new_transition_56( msg );
            return junction_____Debug__C__turnedRight__new_exitpoint_6( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__turnedRight__Debug__A__En__MOVING_FORWARD( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__turnedRight__Debug__end__trans__turnedRight( msg );
            return junction_____Debug__C__turnedRight__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__turnedRight__new_transition_57( msg );
            return junction_____Debug__C__turnedRight__new_exitpoint_6( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__turnedRight__Debug__B__Ac__turnedRight( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__turnedRight__Debug__AC__turnedRight( msg );
            return Debug__C__turnedRight__Debug__A__Ac__turnedRight;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__turnedRight__new_transition_55( msg );
            return junction_____Debug__C__turnedRight__new_exitpoint_6( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__turnedRight__Debug__B__Ex__ROTATING( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__turnedRight__Debug__Ex__ROTATING( msg );
            return Debug__C__turnedRight__Debug__B__Ac__turnedRight;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__turnedRight__new_transition_54( msg );
            return junction_____Debug__C__turnedRight__new_exitpoint_6( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__C__turnedRight__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__turnedRight__new_transition_58( msg );
            return junction_____Debug__C__turnedRight__new_exitpoint_6( msg );
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____Debug__InitState( const UMLRTMessage * msg )
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

Capsule_ControlSoftware::State Capsule_ControlSoftware::state_____MOVING_BACKWARDS( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____Debug__timeout( msg );
            return choice_____Debug__Path__timeout( msg );
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
            if( action_____Debug__greaterThan__greaterThanThreshold( msg ) )
            {
                actionchain_____Debug__greaterThan( msg );
                return choice_____Debug__Path__greaterThan( msg );
            }
            else if( action_____Debug__lowerThanThreshold__lessThanThreshold( msg ) )
            {
                actionchain_____Debug__lowerThanThreshold( msg );
                return choice_____Debug__Path__lowerThanThreshold( msg );
            }
            return currentState;
            if( action_____Debug__greaterThan__greaterThanThreshold( msg ) )
            {
                actionchain_____Debug__greaterThan( msg );
                return choice_____Debug__Path__greaterThan( msg );
            }
            else if( action_____Debug__lowerThanThreshold__lessThanThreshold( msg ) )
            {
                actionchain_____Debug__lowerThanThreshold( msg );
                return choice_____Debug__Path__lowerThanThreshold( msg );
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
            actionchain_____Debug__turnedRight( msg );
            return choice_____Debug__Path__turnedRight( msg );
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
            actionchain_____Debug__moving_forward( msg );
            return choice_____Debug__Path__moving_forward( msg );
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
            actionchain_____Debug__stopped_moving_backwards( msg );
            return choice_____Debug__Path__stopped_moving_backwards( msg );
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
            actionchain_____Debug__stopped( msg );
            return choice_____Debug__Path__stopped( msg );
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
        Capsule_ControlSoftware::port_extComm,
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
    6,
    portroles_border,
    0,
    NULL
};

