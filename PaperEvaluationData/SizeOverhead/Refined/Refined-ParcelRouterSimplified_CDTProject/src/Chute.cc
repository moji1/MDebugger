
#include "Chute.hh"

#include "ExtInterface.hh"
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
, extComm( borderPorts[borderport_extComm] )
, timer( borderPorts[borderport_timer] )
, delay( 1 )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[Debug__C__Initial] = "Debug__C__Initial";
    stateNames[Debug__C__reception] = "Debug__C__reception";
    stateNames[Debug__C__transmission] = "Debug__C__transmission";
    stateNames[Debug__C__Initial__Debug__A__Ac__Initial] = "Debug__C__Initial__Debug__A__Ac__Initial";
    stateNames[Debug__C__Initial__Debug__A__En__Initial] = "Debug__C__Initial__Debug__A__En__Initial";
    stateNames[Debug__C__Initial__Debug__B__Ac__Initial] = "Debug__C__Initial__Debug__B__Ac__Initial";
    stateNames[Debug__C__Initial__boundary] = "Debug__C__Initial__boundary";
    stateNames[Debug__C__reception__Debug__A__Ac__reception] = "Debug__C__reception__Debug__A__Ac__reception";
    stateNames[Debug__C__reception__Debug__A__En__OCCUPIED] = "Debug__C__reception__Debug__A__En__OCCUPIED";
    stateNames[Debug__C__reception__Debug__B__Ac__reception] = "Debug__C__reception__Debug__B__Ac__reception";
    stateNames[Debug__C__reception__Debug__B__Ex__IDLE] = "Debug__C__reception__Debug__B__Ex__IDLE";
    stateNames[Debug__C__reception__boundary] = "Debug__C__reception__boundary";
    stateNames[Debug__C__transmission__Debug__A__Ac__transmission] = "Debug__C__transmission__Debug__A__Ac__transmission";
    stateNames[Debug__C__transmission__Debug__A__En__IDLE] = "Debug__C__transmission__Debug__A__En__IDLE";
    stateNames[Debug__C__transmission__Debug__B__Ac__transmission] = "Debug__C__transmission__Debug__B__Ac__transmission";
    stateNames[Debug__C__transmission__Debug__B__Ex__OCCUPIED] = "Debug__C__transmission__Debug__B__Ex__OCCUPIED";
    stateNames[Debug__C__transmission__boundary] = "Debug__C__transmission__boundary";
    stateNames[Debug__InitState] = "Debug__InitState";
    stateNames[IDLE] = "IDLE";
    stateNames[OCCUPIED] = "OCCUPIED";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
    int i = 0;
    while( i < 3 )
        history[i++] = SPECIAL_INTERNAL_STATE_UNVISITED;
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







void Capsule_Chute::Debug__variablesView()
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute operation Debug__variablesView */
    std::string tempS="";
    tempS.append("delay,");
    tempS.append("Integer,");
    if(delay!=0){
    char tempR[10];
    sprintf(tempR,"%d",delay);
    tempS.append(tempR);
    tempS.append("\n");
    }else {
    tempS.append("0");
    tempS.append("\n");
    };
    if (Debug__variablesData==NULL)
    Debug__variablesData=(char *)malloc(strlen(tempS.c_str())+1);
    else if (strlen(Debug__variablesData)<strlen(tempS.c_str()))
    Debug__variablesData=(char *) realloc(Debug__variablesData,strlen(tempS.c_str())+1);
    strcpy(Debug__variablesData,tempS.c_str());
    /* UMLRTGEN-USERREGION-END */
}

bool Capsule_Chute::Debug__variablesChange( char * varName, char * varValue )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute operation Debug__variablesChange */
    std::string tempVarName="";
    tempVarName.append(varName);
    if ("delay"==tempVarName){
    delay=atoi(varValue);
    return true;
    }else 
    return false;
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_Chute::Debug__sendEvent( debugEvents::EVENTSOURCEKIND eventSourceKind, debugEvents::EVENTTYPE eventType, const char * instanceName, int capsuleIndex, const char * signalName, char * capsuleName, char * sourceName, char * reserve1, char * reserve2, char * reserve3 )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute operation Debug__sendEvent */
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
    case Debug__InitState:
        currentState = state_____Debug__InitState( &message );
        break;
    case Debug__C__Initial__Debug__B__Ac__Initial:
        currentState = state_____Debug__C__Initial__Debug__B__Ac__Initial( &message );
        break;
    case Debug__C__Initial__Debug__A__Ac__Initial:
        currentState = state_____Debug__C__Initial__Debug__A__Ac__Initial( &message );
        break;
    case Debug__C__Initial__Debug__A__En__Initial:
        currentState = state_____Debug__C__Initial__Debug__A__En__Initial( &message );
        break;
    case Debug__C__Initial__boundary:
        currentState = state_____Debug__C__Initial__boundary( &message );
        break;
    case Debug__C__reception__Debug__B__Ex__IDLE:
        currentState = state_____Debug__C__reception__Debug__B__Ex__IDLE( &message );
        break;
    case Debug__C__reception__Debug__B__Ac__reception:
        currentState = state_____Debug__C__reception__Debug__B__Ac__reception( &message );
        break;
    case Debug__C__reception__Debug__A__Ac__reception:
        currentState = state_____Debug__C__reception__Debug__A__Ac__reception( &message );
        break;
    case Debug__C__reception__Debug__A__En__OCCUPIED:
        currentState = state_____Debug__C__reception__Debug__A__En__OCCUPIED( &message );
        break;
    case Debug__C__reception__boundary:
        currentState = state_____Debug__C__reception__boundary( &message );
        break;
    case Debug__C__transmission__Debug__B__Ex__OCCUPIED:
        currentState = state_____Debug__C__transmission__Debug__B__Ex__OCCUPIED( &message );
        break;
    case Debug__C__transmission__Debug__B__Ac__transmission:
        currentState = state_____Debug__C__transmission__Debug__B__Ac__transmission( &message );
        break;
    case Debug__C__transmission__Debug__A__Ac__transmission:
        currentState = state_____Debug__C__transmission__Debug__A__Ac__transmission( &message );
        break;
    case Debug__C__transmission__Debug__A__En__IDLE:
        currentState = state_____Debug__C__transmission__Debug__A__En__IDLE( &message );
        break;
    case Debug__C__transmission__boundary:
        currentState = state_____Debug__C__transmission__boundary( &message );
        break;
    default:
        break;
    }
}

void Capsule_Chute::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Debug__InitDebug( &message );
    currentState = Debug__InitState;
}

const char * Capsule_Chute::getCurrentStateString() const
{
    return stateNames[currentState];
}





void Capsule_Chute::save_history( Capsule_Chute::State compositeState, Capsule_Chute::State subState )
{
    history[compositeState] = subState;
}

bool Capsule_Chute::check_history( Capsule_Chute::State compositeState, Capsule_Chute::State subState )
{
    return history[compositeState] == subState;
}

void Capsule_Chute::entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__Initial::Debug__A__Ac__Initial entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__Initial::Region1::Debug__A__Ac__Initial",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Initial","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("IDLE","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::entryaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__Initial::Debug__A__En__Initial entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__Initial::Region1::Debug__A__En__Initial",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__Initial::Debug__B__Ac__Initial entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__Initial::Region1::Debug__B__Ac__Initial",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Initial","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::entryaction_____Debug__C__Initial__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Chute::entryaction_____Debug__C__reception__Debug__A__Ac__reception( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__reception::Debug__A__Ac__reception entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__reception::Region1::Debug__A__Ac__reception",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("reception","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("OCCUPIED","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::entryaction_____Debug__C__reception__Debug__A__En__OCCUPIED( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__reception::Debug__A__En__OCCUPIED entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__reception::Region1::Debug__A__En__OCCUPIED",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("OCCUPIED","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::entryaction_____Debug__C__reception__Debug__B__Ac__reception( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__reception::Debug__B__Ac__reception entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__reception::Region1::Debug__B__Ac__reception",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("reception","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::entryaction_____Debug__C__reception__Debug__B__Ex__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__reception::Debug__B__Ex__IDLE entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__reception::Region1::Debug__B__Ex__IDLE",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::entryaction_____Debug__C__reception__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Chute::entryaction_____Debug__C__transmission__Debug__A__Ac__transmission( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__transmission::Debug__A__Ac__transmission entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__transmission::Region1::Debug__A__Ac__transmission",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("transmission","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("IDLE","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::entryaction_____Debug__C__transmission__Debug__A__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__transmission::Debug__A__En__IDLE entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__transmission::Region1::Debug__A__En__IDLE",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::entryaction_____Debug__C__transmission__Debug__B__Ac__transmission( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__transmission::Debug__B__Ac__transmission entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__transmission::Region1::Debug__B__Ac__transmission",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("OCCUPIED","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("transmission","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::entryaction_____Debug__C__transmission__Debug__B__Ex__OCCUPIED( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__transmission::Debug__B__Ex__OCCUPIED entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__transmission::Region1::Debug__B__Ex__OCCUPIED",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("OCCUPIED","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::entryaction_____Debug__C__transmission__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Chute::entryaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__InitState entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::entryaction_____IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::IDLE entry  */
    if( not Debug__SRO.checkDebug("IDLE",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::IDLE",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::entryaction_____OCCUPIED( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::OCCUPIED entry  */
    if( not Debug__SRO.checkDebug("OCCUPIED",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::OCCUPIED",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__Initial::Debug__A__Ac__Initial exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__Initial::Region1::Debug__A__Ac__Initial",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::exitaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__Initial::Debug__A__En__Initial exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__Initial::Region1::Debug__A__En__Initial",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__Initial::Debug__B__Ac__Initial exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__Initial::Region1::Debug__B__Ac__Initial",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::exitaction_____Debug__C__Initial__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Chute::exitaction_____Debug__C__reception__Debug__A__Ac__reception( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__reception::Debug__A__Ac__reception exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__reception::Region1::Debug__A__Ac__reception",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::exitaction_____Debug__C__reception__Debug__A__En__OCCUPIED( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__reception::Debug__A__En__OCCUPIED exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__reception::Region1::Debug__A__En__OCCUPIED",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::exitaction_____Debug__C__reception__Debug__B__Ac__reception( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__reception::Debug__B__Ac__reception exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__reception::Region1::Debug__B__Ac__reception",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::exitaction_____Debug__C__reception__Debug__B__Ex__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__reception::Debug__B__Ex__IDLE exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__reception::Region1::Debug__B__Ex__IDLE",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::exitaction_____Debug__C__reception__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Chute::exitaction_____Debug__C__transmission__Debug__A__Ac__transmission( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__transmission::Debug__A__Ac__transmission exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__transmission::Region1::Debug__A__Ac__transmission",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::exitaction_____Debug__C__transmission__Debug__A__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__transmission::Debug__A__En__IDLE exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__transmission::Region1::Debug__A__En__IDLE",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::exitaction_____Debug__C__transmission__Debug__B__Ac__transmission( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__transmission::Debug__B__Ac__transmission exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__transmission::Region1::Debug__B__Ac__transmission",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::exitaction_____Debug__C__transmission__Debug__B__Ex__OCCUPIED( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__transmission::Debug__B__Ex__OCCUPIED exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__transmission::Region1::Debug__B__Ex__OCCUPIED",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::exitaction_____Debug__C__transmission__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Chute::exitaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__InitState exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::exitaction_____IDLE( const UMLRTMessage * msg )
{
    #define umlrtparam_p ( *(const Parcel * )msg->getParam( 0 ) )
    #define rtdata ( (const Parcel * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::IDLE exit  */
    if( not Debug__SRO.checkDebug("IDLE",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::IDLE",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_p
}

void Capsule_Chute::exitaction_____OCCUPIED( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::OCCUPIED exit  */
    if( not Debug__SRO.checkDebug("OCCUPIED",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::OCCUPIED",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__Initial transition Debug__C__Initial::Debug__B__Ac__Initial,Debug__C__Initial::Debug__A__Ac__Initial,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__Initial::Region1::Debug__Ac__Initial",(char *)"Debug__B__Ac__Initial",(char *)"Debug__A__Ac__Initial",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__C__Initial__Debug__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__Initial transition Debug__C__Initial::Debug__A__Ac__Initial,Debug__C__Initial::Debug__A__En__Initial,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__Initial::Region1::Debug__En__IDLE",(char *)"Debug__A__Ac__Initial",(char *)"Debug__A__En__Initial",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__Initial transition Debug__C__Initial::Debug__A__En__Initial,Debug__C__Initial::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__Initial::Region1::Debug__end__trans__Initial",(char *)"Debug__A__En__Initial",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__Initial transition Debug__C__Initial::en,Debug__C__Initial::Debug__B__Ac__Initial */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__Initial::Region1::Debug__init__trans__Initial",(char *)"en",(char *)"Debug__B__Ac__Initial",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__C__reception__Debug__AC__reception( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__reception transition Debug__C__reception::Debug__B__Ac__reception,Debug__C__reception::Debug__A__Ac__reception,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__reception::Region1::Debug__AC__reception",(char *)"Debug__B__Ac__reception",(char *)"Debug__A__Ac__reception",(char *)"");
    this->parcel = Parcel();
    this->parcel.number = 1;
    this->parcel.level = 2;
    this->parcel.stage = 3;
    log.show("Chute %s of stage %d becomes occupied\n", this->getName(), 1);
    timer.informIn(UMLRTTimespec(this->delay,0));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__C__reception__Debug__En__OCCUPIED( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__reception transition Debug__C__reception::Debug__A__Ac__reception,Debug__C__reception::Debug__A__En__OCCUPIED,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__reception::Region1::Debug__En__OCCUPIED",(char *)"Debug__A__Ac__reception",(char *)"Debug__A__En__OCCUPIED",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__C__reception__Debug__Ex__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__reception transition Debug__C__reception::Debug__B__Ex__IDLE,Debug__C__reception::Debug__B__Ac__reception,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__reception::Region1::Debug__Ex__IDLE",(char *)"Debug__B__Ex__IDLE",(char *)"Debug__B__Ac__reception",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__C__reception__Debug__end__trans__reception( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__reception transition Debug__C__reception::Debug__A__En__OCCUPIED,Debug__C__reception::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__reception::Region1::Debug__end__trans__reception",(char *)"Debug__A__En__OCCUPIED",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__C__reception__Debug__init__trans__reception( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__reception transition Debug__C__reception::en,Debug__C__reception::Debug__B__Ex__IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__reception::Region1::Debug__init__trans__reception",(char *)"en",(char *)"Debug__B__Ex__IDLE",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__C__transmission__Debug__AC__transmission( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__transmission transition Debug__C__transmission::Debug__B__Ac__transmission,Debug__C__transmission::Debug__A__Ac__transmission,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__transmission::Region1::Debug__AC__transmission",(char *)"Debug__B__Ac__transmission",(char *)"Debug__A__Ac__transmission",(char *)"");
    detection.detect(this->parcel).send();
    exit.transmit(this->parcel).send();
    log.show("Chute %s of stage %d is now free\n", this->getName(), this->parcel.stage);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__C__transmission__Debug__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__transmission transition Debug__C__transmission::Debug__A__Ac__transmission,Debug__C__transmission::Debug__A__En__IDLE,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__transmission::Region1::Debug__En__IDLE",(char *)"Debug__A__Ac__transmission",(char *)"Debug__A__En__IDLE",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__C__transmission__Debug__Ex__OCCUPIED( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__transmission transition Debug__C__transmission::Debug__B__Ex__OCCUPIED,Debug__C__transmission::Debug__B__Ac__transmission,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__transmission::Region1::Debug__Ex__OCCUPIED",(char *)"Debug__B__Ex__OCCUPIED",(char *)"Debug__B__Ac__transmission",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__C__transmission__Debug__end__trans__transmission( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__transmission transition Debug__C__transmission::Debug__A__En__IDLE,Debug__C__transmission::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__transmission::Region1::Debug__end__trans__transmission",(char *)"Debug__A__En__IDLE",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__C__transmission__Debug__init__trans__transmission( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute::Debug__C__transmission transition Debug__C__transmission::en,Debug__C__transmission::Debug__B__Ex__OCCUPIED */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__C__transmission::Region1::Debug__init__trans__transmission",(char *)"en",(char *)"Debug__B__Ex__OCCUPIED",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__InitDebug( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute transition Pseudo1,Debug__InitState */
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

void Capsule_Chute::transitionaction_____Debug__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute transition Debug__InitState,Debug__Path__Initial,null:extComm */
    if (this->Debug__SRO.getExecMode()==Stepping){
    Debug__SRO.addTransitionsFromState("IDLE","reception","OCCUPIED","transmit","transmission");
    Debug__SRO.addTransitionsFromState("OCCUPIED","transmission","IDLE","timeout","Timing");
    Debug__SRO.addTransitionsFromState("","Initial","IDLE","","");
    std::cout<<this->getName()<<": Connection with debugger is in progress\n";
    char  tempS[256];
    sprintf(tempS,"%s%d",this->getName(),(int)this->getIndex());
    extComm.registerToControl(tempS).send();
    Debug__sendEvent(debugEvents::DEBUG,debugEvents::REGISTER,this->getName(),this->getIndex(),msg->getSignalName(),(char *) "",(char *) "",(char *) "",(char *)"",(char *) "");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__Initial__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute transition Debug__C__Initial::ex,IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__Initial__E",(char *)"ex",(char *)"IDLE",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__Initial__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute transition Debug__Path__Initial,Debug__C__Initial::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__Initial__S",(char *)"Debug__Path__Initial",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__Initial__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute transition Debug__C__Initial::new_exitpoint_1,Debug__C__Initial */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__Initial__dbg",(char *)"Debug__C__Initial",(char *)"Debug__C__Initial",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__reception( const UMLRTMessage * msg )
{
    #define umlrtparam_p ( *(const Parcel * )msg->getParam( 0 ) )
    #define rtdata ( (const Parcel * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute transition IDLE,Debug__Path__reception,transmit:enter */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__reception",(char *)"IDLE",(char *)"Debug__Path__reception",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_p
}

void Capsule_Chute::transitionaction_____Debug__reception__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute transition Debug__C__reception::ex,OCCUPIED */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__reception__E",(char *)"ex",(char *)"OCCUPIED",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__reception__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute transition Debug__Path__reception,Debug__C__reception::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__reception__S",(char *)"Debug__Path__reception",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__reception__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute transition Debug__C__reception::new_exitpoint_2,Debug__C__reception */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__reception__dbg",(char *)"Debug__C__reception",(char *)"Debug__C__reception",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__transmission( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute transition OCCUPIED,Debug__Path__transmission,timeout:timer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__transmission",(char *)"OCCUPIED",(char *)"Debug__Path__transmission",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__transmission__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute transition Debug__C__transmission::ex,IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__transmission__E",(char *)"ex",(char *)"IDLE",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__transmission__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute transition Debug__Path__transmission,Debug__C__transmission::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__transmission__S",(char *)"Debug__Path__transmission",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Debug__transmission__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute transition Debug__C__transmission::new_exitpoint_3,Debug__C__transmission */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Debug__transmission__dbg",(char *)"Debug__C__transmission",(char *)"Debug__C__transmission",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute transition Debug__Path__Initial,IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::Initial",(char *)"Debug__Path__Initial",(char *)"IDLE",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____reception( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute transition Debug__Path__reception,OCCUPIED */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::reception",(char *)"Debug__Path__reception",(char *)"OCCUPIED",(char *)"");
    this->parcel = Parcel();
    this->parcel.number = 1;
    this->parcel.level = 2;
    this->parcel.stage = 3;
    log.show("Chute %s of stage %d becomes occupied\n", this->getName(), 4);
    timer.informIn(UMLRTTimespec(this->delay,0));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::transitionaction_____transmission( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute transition Debug__Path__transmission,IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Chute::ChuteStateMachine::Region::transmission",(char *)"Debug__Path__transmission",(char *)"IDLE",(char *)"");
    detection.detect(this->parcel).send();
    exit.transmit(this->parcel).send();
    log.show("Chute %s of stage %d is now free\n", this->getName(), this->parcel.stage);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Chute::action_____Debug__Initial__S__Debug__GuardInitial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute guard Debug__Path__Initial,Debug__C__Initial::en */
    return Debug__SRO.checkDebug("Pseudo1","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Chute::action_____Debug__reception__S__Debug__Guardreception( const UMLRTMessage * msg )
{
    #define umlrtparam_p ( *(const Parcel * )msg->getParam( 0 ) )
    #define rtdata ( (const Parcel * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute guard Debug__Path__reception,Debug__C__reception::en */
    return Debug__SRO.checkDebug("IDLE",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_p
}

bool Capsule_Chute::action_____Debug__transmission__S__Debug__Guardtransmission( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Chute guard Debug__Path__transmission,Debug__C__transmission::en */
    return Debug__SRO.checkDebug("OCCUPIED",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Chute::actionchain_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    transitionaction_____Debug__C__Initial__Debug__Ac__Initial( msg );
    entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
}

void Capsule_Chute::actionchain_____Debug__C__Initial__Debug__En__IDLE( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    transitionaction_____Debug__C__Initial__Debug__En__IDLE( msg );
    entryaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
}

void Capsule_Chute::actionchain_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    transitionaction_____Debug__C__Initial__Debug__end__trans__Initial( msg );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Chute::actionchain_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__Initial__Debug__init__trans__Initial( msg );
    entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
}

void Capsule_Chute::actionchain_____Debug__C__Initial__new_transition_1( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
}

void Capsule_Chute::actionchain_____Debug__C__Initial__new_transition_2( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
}

void Capsule_Chute::actionchain_____Debug__C__Initial__new_transition_3( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
}

void Capsule_Chute::actionchain_____Debug__C__Initial__new_transition_4_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Initial__boundary( msg );
}

void Capsule_Chute::actionchain_____Debug__C__Initial__new_transition_5( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial );
}

void Capsule_Chute::actionchain_____Debug__C__Initial__new_transition_6( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial );
}

void Capsule_Chute::actionchain_____Debug__C__Initial__new_transition_7( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Chute::actionchain_____Debug__C__Initial__new_transition_8( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__boundary( msg );
    save_history( Debug__C__Initial, Debug__C__Initial__boundary );
}

void Capsule_Chute::actionchain_____Debug__C__reception__Debug__AC__reception( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reception__Debug__B__Ac__reception( msg );
    transitionaction_____Debug__C__reception__Debug__AC__reception( msg );
    entryaction_____Debug__C__reception__Debug__A__Ac__reception( msg );
}

void Capsule_Chute::actionchain_____Debug__C__reception__Debug__En__OCCUPIED( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reception__Debug__A__Ac__reception( msg );
    transitionaction_____Debug__C__reception__Debug__En__OCCUPIED( msg );
    entryaction_____Debug__C__reception__Debug__A__En__OCCUPIED( msg );
}

void Capsule_Chute::actionchain_____Debug__C__reception__Debug__Ex__IDLE( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reception__Debug__B__Ex__IDLE( msg );
    transitionaction_____Debug__C__reception__Debug__Ex__IDLE( msg );
    entryaction_____Debug__C__reception__Debug__B__Ac__reception( msg );
}

void Capsule_Chute::actionchain_____Debug__C__reception__Debug__end__trans__reception( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reception__Debug__A__En__OCCUPIED( msg );
    transitionaction_____Debug__C__reception__Debug__end__trans__reception( msg );
    save_history( Debug__C__reception, Debug__C__reception__Debug__A__En__OCCUPIED );
}

void Capsule_Chute::actionchain_____Debug__C__reception__Debug__init__trans__reception( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__reception__Debug__init__trans__reception( msg );
    entryaction_____Debug__C__reception__Debug__B__Ex__IDLE( msg );
}

void Capsule_Chute::actionchain_____Debug__C__reception__new_transition_10( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__reception__Debug__B__Ac__reception( msg );
}

void Capsule_Chute::actionchain_____Debug__C__reception__new_transition_11( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__reception__Debug__A__Ac__reception( msg );
}

void Capsule_Chute::actionchain_____Debug__C__reception__new_transition_12( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__reception__Debug__A__En__OCCUPIED( msg );
}

void Capsule_Chute::actionchain_____Debug__C__reception__new_transition_13_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__reception__boundary( msg );
}

void Capsule_Chute::actionchain_____Debug__C__reception__new_transition_14( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reception__Debug__B__Ex__IDLE( msg );
    save_history( Debug__C__reception, Debug__C__reception__Debug__B__Ex__IDLE );
}

void Capsule_Chute::actionchain_____Debug__C__reception__new_transition_15( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reception__Debug__B__Ac__reception( msg );
    save_history( Debug__C__reception, Debug__C__reception__Debug__B__Ac__reception );
}

void Capsule_Chute::actionchain_____Debug__C__reception__new_transition_16( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reception__Debug__A__Ac__reception( msg );
    save_history( Debug__C__reception, Debug__C__reception__Debug__A__Ac__reception );
}

void Capsule_Chute::actionchain_____Debug__C__reception__new_transition_17( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reception__Debug__A__En__OCCUPIED( msg );
    save_history( Debug__C__reception, Debug__C__reception__Debug__A__En__OCCUPIED );
}

void Capsule_Chute::actionchain_____Debug__C__reception__new_transition_18( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reception__boundary( msg );
    save_history( Debug__C__reception, Debug__C__reception__boundary );
}

void Capsule_Chute::actionchain_____Debug__C__reception__new_transition_9( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__reception__Debug__B__Ex__IDLE( msg );
}

void Capsule_Chute::actionchain_____Debug__C__transmission__Debug__AC__transmission( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__transmission__Debug__B__Ac__transmission( msg );
    transitionaction_____Debug__C__transmission__Debug__AC__transmission( msg );
    entryaction_____Debug__C__transmission__Debug__A__Ac__transmission( msg );
}

void Capsule_Chute::actionchain_____Debug__C__transmission__Debug__En__IDLE( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__transmission__Debug__A__Ac__transmission( msg );
    transitionaction_____Debug__C__transmission__Debug__En__IDLE( msg );
    entryaction_____Debug__C__transmission__Debug__A__En__IDLE( msg );
}

void Capsule_Chute::actionchain_____Debug__C__transmission__Debug__Ex__OCCUPIED( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__transmission__Debug__B__Ex__OCCUPIED( msg );
    transitionaction_____Debug__C__transmission__Debug__Ex__OCCUPIED( msg );
    entryaction_____Debug__C__transmission__Debug__B__Ac__transmission( msg );
}

void Capsule_Chute::actionchain_____Debug__C__transmission__Debug__end__trans__transmission( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__transmission__Debug__A__En__IDLE( msg );
    transitionaction_____Debug__C__transmission__Debug__end__trans__transmission( msg );
    save_history( Debug__C__transmission, Debug__C__transmission__Debug__A__En__IDLE );
}

void Capsule_Chute::actionchain_____Debug__C__transmission__Debug__init__trans__transmission( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__transmission__Debug__init__trans__transmission( msg );
    entryaction_____Debug__C__transmission__Debug__B__Ex__OCCUPIED( msg );
}

void Capsule_Chute::actionchain_____Debug__C__transmission__new_transition_19( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__transmission__Debug__B__Ex__OCCUPIED( msg );
}

void Capsule_Chute::actionchain_____Debug__C__transmission__new_transition_20( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__transmission__Debug__B__Ac__transmission( msg );
}

void Capsule_Chute::actionchain_____Debug__C__transmission__new_transition_21( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__transmission__Debug__A__Ac__transmission( msg );
}

void Capsule_Chute::actionchain_____Debug__C__transmission__new_transition_22( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__transmission__Debug__A__En__IDLE( msg );
}

void Capsule_Chute::actionchain_____Debug__C__transmission__new_transition_23_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__transmission__boundary( msg );
}

void Capsule_Chute::actionchain_____Debug__C__transmission__new_transition_24( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__transmission__Debug__B__Ex__OCCUPIED( msg );
    save_history( Debug__C__transmission, Debug__C__transmission__Debug__B__Ex__OCCUPIED );
}

void Capsule_Chute::actionchain_____Debug__C__transmission__new_transition_25( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__transmission__Debug__B__Ac__transmission( msg );
    save_history( Debug__C__transmission, Debug__C__transmission__Debug__B__Ac__transmission );
}

void Capsule_Chute::actionchain_____Debug__C__transmission__new_transition_26( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__transmission__Debug__A__Ac__transmission( msg );
    save_history( Debug__C__transmission, Debug__C__transmission__Debug__A__Ac__transmission );
}

void Capsule_Chute::actionchain_____Debug__C__transmission__new_transition_27( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__transmission__Debug__A__En__IDLE( msg );
    save_history( Debug__C__transmission, Debug__C__transmission__Debug__A__En__IDLE );
}

void Capsule_Chute::actionchain_____Debug__C__transmission__new_transition_28( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__transmission__boundary( msg );
    save_history( Debug__C__transmission, Debug__C__transmission__boundary );
}

void Capsule_Chute::actionchain_____Debug__InitDebug( const UMLRTMessage * msg )
{
    transitionaction_____Debug__InitDebug( msg );
    entryaction_____Debug__InitState( msg );
}

void Capsule_Chute::actionchain_____Debug__Initial( const UMLRTMessage * msg )
{
    exitaction_____Debug__InitState( msg );
    transitionaction_____Debug__Initial( msg );
}

void Capsule_Chute::actionchain_____Debug__Initial__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__boundary( msg );
    transitionaction_____Debug__Initial__E( msg );
    entryaction_____IDLE( msg );
}

void Capsule_Chute::actionchain_____Debug__Initial__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__Initial__S( msg );
    entryaction_____Debug__C__Initial__boundary( msg );
}

void Capsule_Chute::actionchain_____Debug__Initial__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__boundary( msg );
    transitionaction_____Debug__Initial__dbg( msg );
    entryaction_____Debug__C__Initial__boundary( msg );
}

void Capsule_Chute::actionchain_____Debug__reception( const UMLRTMessage * msg )
{
    exitaction_____IDLE( msg );
    transitionaction_____Debug__reception( msg );
}

void Capsule_Chute::actionchain_____Debug__reception__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reception__boundary( msg );
    transitionaction_____Debug__reception__E( msg );
    entryaction_____OCCUPIED( msg );
}

void Capsule_Chute::actionchain_____Debug__reception__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__reception__S( msg );
    entryaction_____Debug__C__reception__boundary( msg );
}

void Capsule_Chute::actionchain_____Debug__reception__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reception__boundary( msg );
    transitionaction_____Debug__reception__dbg( msg );
    entryaction_____Debug__C__reception__boundary( msg );
}

void Capsule_Chute::actionchain_____Debug__transmission( const UMLRTMessage * msg )
{
    exitaction_____OCCUPIED( msg );
    transitionaction_____Debug__transmission( msg );
}

void Capsule_Chute::actionchain_____Debug__transmission__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__transmission__boundary( msg );
    transitionaction_____Debug__transmission__E( msg );
    entryaction_____IDLE( msg );
}

void Capsule_Chute::actionchain_____Debug__transmission__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__transmission__S( msg );
    entryaction_____Debug__C__transmission__boundary( msg );
}

void Capsule_Chute::actionchain_____Debug__transmission__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__transmission__boundary( msg );
    transitionaction_____Debug__transmission__dbg( msg );
    entryaction_____Debug__C__transmission__boundary( msg );
}

void Capsule_Chute::actionchain_____Initial( const UMLRTMessage * msg )
{
    transitionaction_____Initial( msg );
    entryaction_____IDLE( msg );
}

void Capsule_Chute::actionchain_____reception( const UMLRTMessage * msg )
{
    transitionaction_____reception( msg );
    entryaction_____OCCUPIED( msg );
}

void Capsule_Chute::actionchain_____transmission( const UMLRTMessage * msg )
{
    transitionaction_____transmission( msg );
    entryaction_____IDLE( msg );
}

Capsule_Chute::State Capsule_Chute::junction_____Debug__C__Initial__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__Initial__Debug__init__trans__Initial( msg );
    return Debug__C__Initial__Debug__B__Ac__Initial;
}

Capsule_Chute::State Capsule_Chute::junction_____Debug__C__Initial__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__E( msg );
    return IDLE;
}

Capsule_Chute::State Capsule_Chute::junction_____Debug__C__Initial__new_exitpoint_1( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__dbg( msg );
    return choice_____Debug__C__Initial__deephistory( msg );
}

Capsule_Chute::State Capsule_Chute::junction_____Debug__C__reception__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__reception__Debug__init__trans__reception( msg );
    return Debug__C__reception__Debug__B__Ex__IDLE;
}

Capsule_Chute::State Capsule_Chute::junction_____Debug__C__reception__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__reception__E( msg );
    return OCCUPIED;
}

Capsule_Chute::State Capsule_Chute::junction_____Debug__C__reception__new_exitpoint_2( const UMLRTMessage * msg )
{
    actionchain_____Debug__reception__dbg( msg );
    return choice_____Debug__C__reception__deephistory( msg );
}

Capsule_Chute::State Capsule_Chute::junction_____Debug__C__transmission__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__transmission__Debug__init__trans__transmission( msg );
    return Debug__C__transmission__Debug__B__Ex__OCCUPIED;
}

Capsule_Chute::State Capsule_Chute::junction_____Debug__C__transmission__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__transmission__E( msg );
    return IDLE;
}

Capsule_Chute::State Capsule_Chute::junction_____Debug__C__transmission__new_exitpoint_3( const UMLRTMessage * msg )
{
    actionchain_____Debug__transmission__dbg( msg );
    return choice_____Debug__C__transmission__deephistory( msg );
}

Capsule_Chute::State Capsule_Chute::choice_____Debug__C__Initial__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial ) )
    {
        actionchain_____Debug__C__Initial__new_transition_1( msg );
        return Debug__C__Initial__Debug__B__Ac__Initial;
    }
    else if( check_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial ) )
    {
        actionchain_____Debug__C__Initial__new_transition_2( msg );
        return Debug__C__Initial__Debug__A__Ac__Initial;
    }
    else if( check_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial ) )
    {
        actionchain_____Debug__C__Initial__new_transition_3( msg );
        return Debug__C__Initial__Debug__A__En__Initial;
    }
    else if( check_history( Debug__C__Initial, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__Initial__new_transition_4_to_boundary( msg );
        return Debug__C__Initial__boundary;
    }
    return currentState;
}

Capsule_Chute::State Capsule_Chute::choice_____Debug__C__reception__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__reception, Debug__C__reception__Debug__B__Ex__IDLE ) )
    {
        actionchain_____Debug__C__reception__new_transition_9( msg );
        return Debug__C__reception__Debug__B__Ex__IDLE;
    }
    else if( check_history( Debug__C__reception, Debug__C__reception__Debug__B__Ac__reception ) )
    {
        actionchain_____Debug__C__reception__new_transition_10( msg );
        return Debug__C__reception__Debug__B__Ac__reception;
    }
    else if( check_history( Debug__C__reception, Debug__C__reception__Debug__A__Ac__reception ) )
    {
        actionchain_____Debug__C__reception__new_transition_11( msg );
        return Debug__C__reception__Debug__A__Ac__reception;
    }
    else if( check_history( Debug__C__reception, Debug__C__reception__Debug__A__En__OCCUPIED ) )
    {
        actionchain_____Debug__C__reception__new_transition_12( msg );
        return Debug__C__reception__Debug__A__En__OCCUPIED;
    }
    else if( check_history( Debug__C__reception, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__reception__new_transition_13_to_boundary( msg );
        return Debug__C__reception__boundary;
    }
    return currentState;
}

Capsule_Chute::State Capsule_Chute::choice_____Debug__C__transmission__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__transmission, Debug__C__transmission__Debug__B__Ex__OCCUPIED ) )
    {
        actionchain_____Debug__C__transmission__new_transition_19( msg );
        return Debug__C__transmission__Debug__B__Ex__OCCUPIED;
    }
    else if( check_history( Debug__C__transmission, Debug__C__transmission__Debug__B__Ac__transmission ) )
    {
        actionchain_____Debug__C__transmission__new_transition_20( msg );
        return Debug__C__transmission__Debug__B__Ac__transmission;
    }
    else if( check_history( Debug__C__transmission, Debug__C__transmission__Debug__A__Ac__transmission ) )
    {
        actionchain_____Debug__C__transmission__new_transition_21( msg );
        return Debug__C__transmission__Debug__A__Ac__transmission;
    }
    else if( check_history( Debug__C__transmission, Debug__C__transmission__Debug__A__En__IDLE ) )
    {
        actionchain_____Debug__C__transmission__new_transition_22( msg );
        return Debug__C__transmission__Debug__A__En__IDLE;
    }
    else if( check_history( Debug__C__transmission, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__transmission__new_transition_23_to_boundary( msg );
        return Debug__C__transmission__boundary;
    }
    return currentState;
}

Capsule_Chute::State Capsule_Chute::choice_____Debug__Path__Initial( const UMLRTMessage * msg )
{
    if( action_____Debug__Initial__S__Debug__GuardInitial( msg ) )
    {
        actionchain_____Debug__Initial__S( msg );
        return junction_____Debug__C__Initial__en( msg );
    }
    else
    {
        actionchain_____Initial( msg );
        return IDLE;
    }
    return currentState;
}

Capsule_Chute::State Capsule_Chute::choice_____Debug__Path__reception( const UMLRTMessage * msg )
{
    if( action_____Debug__reception__S__Debug__Guardreception( msg ) )
    {
        actionchain_____Debug__reception__S( msg );
        return junction_____Debug__C__reception__en( msg );
    }
    else
    {
        actionchain_____reception( msg );
        return OCCUPIED;
    }
    return currentState;
}

Capsule_Chute::State Capsule_Chute::choice_____Debug__Path__transmission( const UMLRTMessage * msg )
{
    if( action_____Debug__transmission__S__Debug__Guardtransmission( msg ) )
    {
        actionchain_____Debug__transmission__S( msg );
        return junction_____Debug__C__transmission__en( msg );
    }
    else
    {
        actionchain_____transmission( msg );
        return IDLE;
    }
    return currentState;
}

Capsule_Chute::State Capsule_Chute::state_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Initial__Debug__En__IDLE( msg );
            return Debug__C__Initial__Debug__A__En__Initial;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Initial__new_transition_6( msg );
            return junction_____Debug__C__Initial__new_exitpoint_1( msg );
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

Capsule_Chute::State Capsule_Chute::state_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Initial__Debug__end__trans__Initial( msg );
            return junction_____Debug__C__Initial__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Initial__new_transition_7( msg );
            return junction_____Debug__C__Initial__new_exitpoint_1( msg );
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

Capsule_Chute::State Capsule_Chute::state_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Initial__Debug__Ac__Initial( msg );
            return Debug__C__Initial__Debug__A__Ac__Initial;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Initial__new_transition_5( msg );
            return junction_____Debug__C__Initial__new_exitpoint_1( msg );
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

Capsule_Chute::State Capsule_Chute::state_____Debug__C__Initial__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Initial__new_transition_8( msg );
            return junction_____Debug__C__Initial__new_exitpoint_1( msg );
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

Capsule_Chute::State Capsule_Chute::state_____Debug__C__reception__Debug__A__Ac__reception( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__reception__Debug__En__OCCUPIED( msg );
            return Debug__C__reception__Debug__A__En__OCCUPIED;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__reception__new_transition_16( msg );
            return junction_____Debug__C__reception__new_exitpoint_2( msg );
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

Capsule_Chute::State Capsule_Chute::state_____Debug__C__reception__Debug__A__En__OCCUPIED( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__reception__Debug__end__trans__reception( msg );
            return junction_____Debug__C__reception__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__reception__new_transition_17( msg );
            return junction_____Debug__C__reception__new_exitpoint_2( msg );
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

Capsule_Chute::State Capsule_Chute::state_____Debug__C__reception__Debug__B__Ac__reception( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__reception__Debug__AC__reception( msg );
            return Debug__C__reception__Debug__A__Ac__reception;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__reception__new_transition_15( msg );
            return junction_____Debug__C__reception__new_exitpoint_2( msg );
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

Capsule_Chute::State Capsule_Chute::state_____Debug__C__reception__Debug__B__Ex__IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__reception__Debug__Ex__IDLE( msg );
            return Debug__C__reception__Debug__B__Ac__reception;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__reception__new_transition_14( msg );
            return junction_____Debug__C__reception__new_exitpoint_2( msg );
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

Capsule_Chute::State Capsule_Chute::state_____Debug__C__reception__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__reception__new_transition_18( msg );
            return junction_____Debug__C__reception__new_exitpoint_2( msg );
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

Capsule_Chute::State Capsule_Chute::state_____Debug__C__transmission__Debug__A__Ac__transmission( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__transmission__Debug__En__IDLE( msg );
            return Debug__C__transmission__Debug__A__En__IDLE;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__transmission__new_transition_26( msg );
            return junction_____Debug__C__transmission__new_exitpoint_3( msg );
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

Capsule_Chute::State Capsule_Chute::state_____Debug__C__transmission__Debug__A__En__IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__transmission__Debug__end__trans__transmission( msg );
            return junction_____Debug__C__transmission__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__transmission__new_transition_27( msg );
            return junction_____Debug__C__transmission__new_exitpoint_3( msg );
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

Capsule_Chute::State Capsule_Chute::state_____Debug__C__transmission__Debug__B__Ac__transmission( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__transmission__Debug__AC__transmission( msg );
            return Debug__C__transmission__Debug__A__Ac__transmission;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__transmission__new_transition_25( msg );
            return junction_____Debug__C__transmission__new_exitpoint_3( msg );
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

Capsule_Chute::State Capsule_Chute::state_____Debug__C__transmission__Debug__B__Ex__OCCUPIED( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__transmission__Debug__Ex__OCCUPIED( msg );
            return Debug__C__transmission__Debug__B__Ac__transmission;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__transmission__new_transition_24( msg );
            return junction_____Debug__C__transmission__new_exitpoint_3( msg );
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

Capsule_Chute::State Capsule_Chute::state_____Debug__C__transmission__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__transmission__new_transition_28( msg );
            return junction_____Debug__C__transmission__new_exitpoint_3( msg );
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

Capsule_Chute::State Capsule_Chute::state_____Debug__InitState( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__Initial( msg );
            return choice_____Debug__Path__Initial( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
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
            actionchain_____Debug__reception( msg );
            return choice_____Debug__Path__reception( msg );
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
            actionchain_____Debug__transmission( msg );
            return choice_____Debug__Path__transmission( msg );
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
        Capsule_Chute::port_extComm,
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
    6,
    portroles_border,
    0,
    NULL
};

