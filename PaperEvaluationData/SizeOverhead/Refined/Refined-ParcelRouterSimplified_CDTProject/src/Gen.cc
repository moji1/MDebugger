
#include "Gen.hh"

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

Capsule_Gen::Capsule_Gen( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, enter( borderPorts[borderport_enter] )
, extComm( borderPorts[borderport_extComm] )
, timer( borderPorts[borderport_timer] )
, delay( 8 )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[Debug__C__GENERATING__GENERATING__3] = "Debug__C__GENERATING__GENERATING__3";
    stateNames[Debug__C__Initial] = "Debug__C__Initial";
    stateNames[Debug__C__GENERATING__GENERATING__3__Debug__A__Ac__GENERATING__GENERATING__3] = "Debug__C__GENERATING__GENERATING__3__Debug__A__Ac__GENERATING__GENERATING__3";
    stateNames[Debug__C__GENERATING__GENERATING__3__Debug__A__En__GENERATING] = "Debug__C__GENERATING__GENERATING__3__Debug__A__En__GENERATING";
    stateNames[Debug__C__GENERATING__GENERATING__3__Debug__B__Ac__GENERATING__GENERATING__3] = "Debug__C__GENERATING__GENERATING__3__Debug__B__Ac__GENERATING__GENERATING__3";
    stateNames[Debug__C__GENERATING__GENERATING__3__Debug__B__Ex__GENERATING] = "Debug__C__GENERATING__GENERATING__3__Debug__B__Ex__GENERATING";
    stateNames[Debug__C__GENERATING__GENERATING__3__boundary] = "Debug__C__GENERATING__GENERATING__3__boundary";
    stateNames[Debug__C__Initial__Debug__A__Ac__Initial] = "Debug__C__Initial__Debug__A__Ac__Initial";
    stateNames[Debug__C__Initial__Debug__A__En__Initial] = "Debug__C__Initial__Debug__A__En__Initial";
    stateNames[Debug__C__Initial__Debug__B__Ac__Initial] = "Debug__C__Initial__Debug__B__Ac__Initial";
    stateNames[Debug__C__Initial__boundary] = "Debug__C__Initial__boundary";
    stateNames[Debug__InitState] = "Debug__InitState";
    stateNames[GENERATING] = "GENERATING";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
    int i = 0;
    while( i < 2 )
        history[i++] = SPECIAL_INTERNAL_STATE_UNVISITED;
}








void Capsule_Gen::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_enter:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_enter, index, true );
            break;
        }
}

void Capsule_Gen::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_enter:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_enter, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_enter], index );
            break;
        }
}







void Capsule_Gen::Debug__variablesView()
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen operation Debug__variablesView */
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

bool Capsule_Gen::Debug__variablesChange( char * varName, char * varValue )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen operation Debug__variablesChange */
    std::string tempVarName="";
    tempVarName.append(varName);
    if ("delay"==tempVarName){
    delay=atoi(varValue);
    return true;
    }else 
    return false;
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_Gen::Debug__sendEvent( debugEvents::EVENTSOURCEKIND eventSourceKind, debugEvents::EVENTTYPE eventType, const char * instanceName, int capsuleIndex, const char * signalName, char * capsuleName, char * sourceName, char * reserve1, char * reserve2, char * reserve3 )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen operation Debug__sendEvent */
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

void Capsule_Gen::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case GENERATING:
        currentState = state_____GENERATING( &message );
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
    case Debug__C__GENERATING__GENERATING__3__Debug__B__Ex__GENERATING:
        currentState = state_____Debug__C__GENERATING__GENERATING__3__Debug__B__Ex__GENERATING( &message );
        break;
    case Debug__C__GENERATING__GENERATING__3__Debug__B__Ac__GENERATING__GENERATING__3:
        currentState = state_____Debug__C__GENERATING__GENERATING__3__Debug__B__Ac__GENERATING__GENERATING__3( &message );
        break;
    case Debug__C__GENERATING__GENERATING__3__Debug__A__Ac__GENERATING__GENERATING__3:
        currentState = state_____Debug__C__GENERATING__GENERATING__3__Debug__A__Ac__GENERATING__GENERATING__3( &message );
        break;
    case Debug__C__GENERATING__GENERATING__3__Debug__A__En__GENERATING:
        currentState = state_____Debug__C__GENERATING__GENERATING__3__Debug__A__En__GENERATING( &message );
        break;
    case Debug__C__GENERATING__GENERATING__3__boundary:
        currentState = state_____Debug__C__GENERATING__GENERATING__3__boundary( &message );
        break;
    default:
        break;
    }
}

void Capsule_Gen::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Debug__InitDebug( &message );
    currentState = Debug__InitState;
}

const char * Capsule_Gen::getCurrentStateString() const
{
    return stateNames[currentState];
}





void Capsule_Gen::save_history( Capsule_Gen::State compositeState, Capsule_Gen::State subState )
{
    history[compositeState] = subState;
}

bool Capsule_Gen::check_history( Capsule_Gen::State compositeState, Capsule_Gen::State subState )
{
    return history[compositeState] == subState;
}

void Capsule_Gen::entryaction_____Debug__C__GENERATING__GENERATING__3__Debug__A__Ac__GENERATING__GENERATING__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__C__GENERATING__GENERATING__3::Debug__A__Ac__GENERATING__GENERATING__3 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__C__GENERATING__GENERATING__3::Region1::Debug__A__Ac__GENERATING__GENERATING__3",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("GENERATING__GENERATING__3","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("GENERATING","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::entryaction_____Debug__C__GENERATING__GENERATING__3__Debug__A__En__GENERATING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__C__GENERATING__GENERATING__3::Debug__A__En__GENERATING entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__C__GENERATING__GENERATING__3::Region1::Debug__A__En__GENERATING",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("GENERATING","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::entryaction_____Debug__C__GENERATING__GENERATING__3__Debug__B__Ac__GENERATING__GENERATING__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__C__GENERATING__GENERATING__3::Debug__B__Ac__GENERATING__GENERATING__3 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__C__GENERATING__GENERATING__3::Region1::Debug__B__Ac__GENERATING__GENERATING__3",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("GENERATING","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("GENERATING__GENERATING__3","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::entryaction_____Debug__C__GENERATING__GENERATING__3__Debug__B__Ex__GENERATING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__C__GENERATING__GENERATING__3::Debug__B__Ex__GENERATING entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__C__GENERATING__GENERATING__3::Region1::Debug__B__Ex__GENERATING",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("GENERATING","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::entryaction_____Debug__C__GENERATING__GENERATING__3__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Gen::entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__C__Initial::Debug__A__Ac__Initial entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__C__Initial::Region1::Debug__A__Ac__Initial",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Initial","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("GENERATING","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::entryaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__C__Initial::Debug__A__En__Initial entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__C__Initial::Region1::Debug__A__En__Initial",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("GENERATING","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__C__Initial::Debug__B__Ac__Initial entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__C__Initial::Region1::Debug__B__Ac__Initial",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Initial","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::entryaction_____Debug__C__Initial__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Gen::entryaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__InitState entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::entryaction_____GENERATING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::GENERATING entry  */
    if( not Debug__SRO.checkDebug("GENERATING",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::GENERATING",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::exitaction_____Debug__C__GENERATING__GENERATING__3__Debug__A__Ac__GENERATING__GENERATING__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__C__GENERATING__GENERATING__3::Debug__A__Ac__GENERATING__GENERATING__3 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__C__GENERATING__GENERATING__3::Region1::Debug__A__Ac__GENERATING__GENERATING__3",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::exitaction_____Debug__C__GENERATING__GENERATING__3__Debug__A__En__GENERATING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__C__GENERATING__GENERATING__3::Debug__A__En__GENERATING exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__C__GENERATING__GENERATING__3::Region1::Debug__A__En__GENERATING",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::exitaction_____Debug__C__GENERATING__GENERATING__3__Debug__B__Ac__GENERATING__GENERATING__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__C__GENERATING__GENERATING__3::Debug__B__Ac__GENERATING__GENERATING__3 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__C__GENERATING__GENERATING__3::Region1::Debug__B__Ac__GENERATING__GENERATING__3",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::exitaction_____Debug__C__GENERATING__GENERATING__3__Debug__B__Ex__GENERATING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__C__GENERATING__GENERATING__3::Debug__B__Ex__GENERATING exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__C__GENERATING__GENERATING__3::Region1::Debug__B__Ex__GENERATING",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::exitaction_____Debug__C__GENERATING__GENERATING__3__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Gen::exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__C__Initial::Debug__A__Ac__Initial exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__C__Initial::Region1::Debug__A__Ac__Initial",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::exitaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__C__Initial::Debug__A__En__Initial exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__C__Initial::Region1::Debug__A__En__Initial",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__C__Initial::Debug__B__Ac__Initial exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__C__Initial::Region1::Debug__B__Ac__Initial",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::exitaction_____Debug__C__Initial__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Gen::exitaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__InitState exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::exitaction_____GENERATING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::GENERATING exit  */
    if( not Debug__SRO.checkDebug("GENERATING",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::GENERATING",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::transitionaction_____Debug__C__GENERATING__GENERATING__3__Debug__AC__GENERATING__GENERATING__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__C__GENERATING__GENERATING__3 transition Debug__C__GENERATING__GENERATING__3::Debug__B__Ac__GENERATING__GENERATING__3,Debug__C__GENERATING__GENERATING__3::Debug__A__Ac__GENERATING__GENERATING__3,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__C__GENERATING__GENERATING__3::Region1::Debug__AC__GENERATING__GENERATING__3",(char *)"Debug__B__Ac__GENERATING__GENERATING__3",(char *)"Debug__A__Ac__GENERATING__GENERATING__3",(char *)"");
    int random = rand() % 4;
    parcel = Parcel();
    parcel.number = random;
    parcel.stage = 0; // 0 for "top", 1 for "left", 2 for "right"
    parcel.level = 2;
    enter.transmit(parcel).send();
    log.show("generating a parcel %d on stage %d\n", random, parcel.stage);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::transitionaction_____Debug__C__GENERATING__GENERATING__3__Debug__En__GENERATING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__C__GENERATING__GENERATING__3 transition Debug__C__GENERATING__GENERATING__3::Debug__A__Ac__GENERATING__GENERATING__3,Debug__C__GENERATING__GENERATING__3::Debug__A__En__GENERATING,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__C__GENERATING__GENERATING__3::Region1::Debug__En__GENERATING",(char *)"Debug__A__Ac__GENERATING__GENERATING__3",(char *)"Debug__A__En__GENERATING",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::transitionaction_____Debug__C__GENERATING__GENERATING__3__Debug__Ex__GENERATING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__C__GENERATING__GENERATING__3 transition Debug__C__GENERATING__GENERATING__3::Debug__B__Ex__GENERATING,Debug__C__GENERATING__GENERATING__3::Debug__B__Ac__GENERATING__GENERATING__3,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__C__GENERATING__GENERATING__3::Region1::Debug__Ex__GENERATING",(char *)"Debug__B__Ex__GENERATING",(char *)"Debug__B__Ac__GENERATING__GENERATING__3",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::transitionaction_____Debug__C__GENERATING__GENERATING__3__Debug__end__trans__GENERATING__GENERATING__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__C__GENERATING__GENERATING__3 transition Debug__C__GENERATING__GENERATING__3::Debug__A__En__GENERATING,Debug__C__GENERATING__GENERATING__3::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__C__GENERATING__GENERATING__3::Region1::Debug__end__trans__GENERATING__GENERATING__3",(char *)"Debug__A__En__GENERATING",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::transitionaction_____Debug__C__GENERATING__GENERATING__3__Debug__init__trans__GENERATING__GENERATING__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__C__GENERATING__GENERATING__3 transition Debug__C__GENERATING__GENERATING__3::en,Debug__C__GENERATING__GENERATING__3::Debug__B__Ex__GENERATING */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__C__GENERATING__GENERATING__3::Region1::Debug__init__trans__GENERATING__GENERATING__3",(char *)"en",(char *)"Debug__B__Ex__GENERATING",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::transitionaction_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__C__Initial transition Debug__C__Initial::Debug__B__Ac__Initial,Debug__C__Initial::Debug__A__Ac__Initial,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__C__Initial::Region1::Debug__Ac__Initial",(char *)"Debug__B__Ac__Initial",(char *)"Debug__A__Ac__Initial",(char *)"");
    srand(time(0));
    timer.informEvery(UMLRTTimespec(4,0));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::transitionaction_____Debug__C__Initial__Debug__En__GENERATING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__C__Initial transition Debug__C__Initial::Debug__A__Ac__Initial,Debug__C__Initial::Debug__A__En__Initial,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__C__Initial::Region1::Debug__En__GENERATING",(char *)"Debug__A__Ac__Initial",(char *)"Debug__A__En__Initial",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::transitionaction_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__C__Initial transition Debug__C__Initial::Debug__A__En__Initial,Debug__C__Initial::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__C__Initial::Region1::Debug__end__trans__Initial",(char *)"Debug__A__En__Initial",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::transitionaction_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen::Debug__C__Initial transition Debug__C__Initial::en,Debug__C__Initial::Debug__B__Ac__Initial */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__C__Initial::Region1::Debug__init__trans__Initial",(char *)"en",(char *)"Debug__B__Ac__Initial",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::transitionaction_____Debug__GENERATING__GENERATING__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen transition GENERATING,Debug__Path__GENERATING__GENERATING__3,timeout:timer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__GENERATING__GENERATING__3",(char *)"GENERATING",(char *)"Debug__Path__GENERATING__GENERATING__3",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::transitionaction_____Debug__GENERATING__GENERATING__3__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen transition Debug__C__GENERATING__GENERATING__3::ex,GENERATING */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__GENERATING__GENERATING__3__E",(char *)"ex",(char *)"GENERATING",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::transitionaction_____Debug__GENERATING__GENERATING__3__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen transition Debug__Path__GENERATING__GENERATING__3,Debug__C__GENERATING__GENERATING__3::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__GENERATING__GENERATING__3__S",(char *)"Debug__Path__GENERATING__GENERATING__3",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::transitionaction_____Debug__GENERATING__GENERATING__3__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen transition Debug__C__GENERATING__GENERATING__3::new_exitpoint_2,Debug__C__GENERATING__GENERATING__3 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__GENERATING__GENERATING__3__dbg",(char *)"Debug__C__GENERATING__GENERATING__3",(char *)"Debug__C__GENERATING__GENERATING__3",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::transitionaction_____Debug__InitDebug( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen transition Pseudo2,Debug__InitState */
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

void Capsule_Gen::transitionaction_____Debug__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen transition Debug__InitState,Debug__Path__Initial,null:extComm */
    if (this->Debug__SRO.getExecMode()==Stepping){
    Debug__SRO.addTransitionsFromState("GENERATING","","GENERATING","timeout","Timing");
    Debug__SRO.addTransitionsFromState("IDLE","reception","OCCUPIED","transmit","transmission");
    Debug__SRO.addTransitionsFromState("OCCUPIED","transmission","IDLE","timeout","Timing");
    Debug__SRO.addTransitionsFromState("","Initial","IDLE","","");
    Debug__SRO.addTransitionsFromState("","Initial","GENERATING","","");
    std::cout<<this->getName()<<": Connection with debugger is in progress\n";
    char  tempS[256];
    sprintf(tempS,"%s%d",this->getName(),(int)this->getIndex());
    extComm.registerToControl(tempS).send();
    Debug__sendEvent(debugEvents::DEBUG,debugEvents::REGISTER,this->getName(),this->getIndex(),msg->getSignalName(),(char *) "",(char *) "",(char *) "",(char *)"",(char *) "");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::transitionaction_____Debug__Initial__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen transition Debug__C__Initial::ex,GENERATING */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__Initial__E",(char *)"ex",(char *)"GENERATING",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::transitionaction_____Debug__Initial__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen transition Debug__Path__Initial,Debug__C__Initial::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__Initial__S",(char *)"Debug__Path__Initial",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::transitionaction_____Debug__Initial__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen transition Debug__C__Initial::new_exitpoint_1,Debug__C__Initial */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Debug__Initial__dbg",(char *)"Debug__C__Initial",(char *)"Debug__C__Initial",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::transitionaction_____GENERATING__GENERATING__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen transition Debug__Path__GENERATING__GENERATING__3,GENERATING */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::GENERATING__GENERATING__3",(char *)"Debug__Path__GENERATING__GENERATING__3",(char *)"GENERATING",(char *)"");
    int random = rand() % 4;
    parcel = Parcel();
    parcel.number = random;
    parcel.stage = 0; // 0 for "top", 1 for "left", 2 for "right"
    parcel.level = 2;
    enter.transmit(parcel).send();
    log.show("generating a parcel %d on stage %d\n", random, parcel.stage);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::transitionaction_____Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen transition Debug__Path__Initial,GENERATING */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Gen::GenStateMachine::Region::Initial",(char *)"Debug__Path__Initial",(char *)"GENERATING",(char *)"");
    srand(time(0));
    timer.informEvery(UMLRTTimespec(4,0));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Gen::action_____Debug__GENERATING__GENERATING__3__S__Debug__GuardGENERATING__GENERATING__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen guard Debug__Path__GENERATING__GENERATING__3,Debug__C__GENERATING__GENERATING__3::en */
    return Debug__SRO.checkDebug("GENERATING",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Gen::action_____Debug__Initial__S__Debug__GuardInitial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Gen guard Debug__Path__Initial,Debug__C__Initial::en */
    return Debug__SRO.checkDebug("Pseudo2","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::actionchain_____Debug__C__GENERATING__GENERATING__3__Debug__AC__GENERATING__GENERATING__3( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__GENERATING__GENERATING__3__Debug__B__Ac__GENERATING__GENERATING__3( msg );
    transitionaction_____Debug__C__GENERATING__GENERATING__3__Debug__AC__GENERATING__GENERATING__3( msg );
    entryaction_____Debug__C__GENERATING__GENERATING__3__Debug__A__Ac__GENERATING__GENERATING__3( msg );
}

void Capsule_Gen::actionchain_____Debug__C__GENERATING__GENERATING__3__Debug__En__GENERATING( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__GENERATING__GENERATING__3__Debug__A__Ac__GENERATING__GENERATING__3( msg );
    transitionaction_____Debug__C__GENERATING__GENERATING__3__Debug__En__GENERATING( msg );
    entryaction_____Debug__C__GENERATING__GENERATING__3__Debug__A__En__GENERATING( msg );
}

void Capsule_Gen::actionchain_____Debug__C__GENERATING__GENERATING__3__Debug__Ex__GENERATING( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__GENERATING__GENERATING__3__Debug__B__Ex__GENERATING( msg );
    transitionaction_____Debug__C__GENERATING__GENERATING__3__Debug__Ex__GENERATING( msg );
    entryaction_____Debug__C__GENERATING__GENERATING__3__Debug__B__Ac__GENERATING__GENERATING__3( msg );
}

void Capsule_Gen::actionchain_____Debug__C__GENERATING__GENERATING__3__Debug__end__trans__GENERATING__GENERATING__3( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__GENERATING__GENERATING__3__Debug__A__En__GENERATING( msg );
    transitionaction_____Debug__C__GENERATING__GENERATING__3__Debug__end__trans__GENERATING__GENERATING__3( msg );
    save_history( Debug__C__GENERATING__GENERATING__3, Debug__C__GENERATING__GENERATING__3__Debug__A__En__GENERATING );
}

void Capsule_Gen::actionchain_____Debug__C__GENERATING__GENERATING__3__Debug__init__trans__GENERATING__GENERATING__3( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__GENERATING__GENERATING__3__Debug__init__trans__GENERATING__GENERATING__3( msg );
    entryaction_____Debug__C__GENERATING__GENERATING__3__Debug__B__Ex__GENERATING( msg );
}

void Capsule_Gen::actionchain_____Debug__C__GENERATING__GENERATING__3__new_transition_10( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__GENERATING__GENERATING__3__Debug__B__Ac__GENERATING__GENERATING__3( msg );
}

void Capsule_Gen::actionchain_____Debug__C__GENERATING__GENERATING__3__new_transition_11( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__GENERATING__GENERATING__3__Debug__A__Ac__GENERATING__GENERATING__3( msg );
}

void Capsule_Gen::actionchain_____Debug__C__GENERATING__GENERATING__3__new_transition_12( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__GENERATING__GENERATING__3__Debug__A__En__GENERATING( msg );
}

void Capsule_Gen::actionchain_____Debug__C__GENERATING__GENERATING__3__new_transition_13_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__GENERATING__GENERATING__3__boundary( msg );
}

void Capsule_Gen::actionchain_____Debug__C__GENERATING__GENERATING__3__new_transition_14( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__GENERATING__GENERATING__3__Debug__B__Ex__GENERATING( msg );
    save_history( Debug__C__GENERATING__GENERATING__3, Debug__C__GENERATING__GENERATING__3__Debug__B__Ex__GENERATING );
}

void Capsule_Gen::actionchain_____Debug__C__GENERATING__GENERATING__3__new_transition_15( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__GENERATING__GENERATING__3__Debug__B__Ac__GENERATING__GENERATING__3( msg );
    save_history( Debug__C__GENERATING__GENERATING__3, Debug__C__GENERATING__GENERATING__3__Debug__B__Ac__GENERATING__GENERATING__3 );
}

void Capsule_Gen::actionchain_____Debug__C__GENERATING__GENERATING__3__new_transition_16( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__GENERATING__GENERATING__3__Debug__A__Ac__GENERATING__GENERATING__3( msg );
    save_history( Debug__C__GENERATING__GENERATING__3, Debug__C__GENERATING__GENERATING__3__Debug__A__Ac__GENERATING__GENERATING__3 );
}

void Capsule_Gen::actionchain_____Debug__C__GENERATING__GENERATING__3__new_transition_17( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__GENERATING__GENERATING__3__Debug__A__En__GENERATING( msg );
    save_history( Debug__C__GENERATING__GENERATING__3, Debug__C__GENERATING__GENERATING__3__Debug__A__En__GENERATING );
}

void Capsule_Gen::actionchain_____Debug__C__GENERATING__GENERATING__3__new_transition_18( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__GENERATING__GENERATING__3__boundary( msg );
    save_history( Debug__C__GENERATING__GENERATING__3, Debug__C__GENERATING__GENERATING__3__boundary );
}

void Capsule_Gen::actionchain_____Debug__C__GENERATING__GENERATING__3__new_transition_9( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__GENERATING__GENERATING__3__Debug__B__Ex__GENERATING( msg );
}

void Capsule_Gen::actionchain_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    transitionaction_____Debug__C__Initial__Debug__Ac__Initial( msg );
    entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
}

void Capsule_Gen::actionchain_____Debug__C__Initial__Debug__En__GENERATING( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    transitionaction_____Debug__C__Initial__Debug__En__GENERATING( msg );
    entryaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
}

void Capsule_Gen::actionchain_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    transitionaction_____Debug__C__Initial__Debug__end__trans__Initial( msg );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Gen::actionchain_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__Initial__Debug__init__trans__Initial( msg );
    entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
}

void Capsule_Gen::actionchain_____Debug__C__Initial__new_transition_1( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
}

void Capsule_Gen::actionchain_____Debug__C__Initial__new_transition_2( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
}

void Capsule_Gen::actionchain_____Debug__C__Initial__new_transition_3( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
}

void Capsule_Gen::actionchain_____Debug__C__Initial__new_transition_4_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Initial__boundary( msg );
}

void Capsule_Gen::actionchain_____Debug__C__Initial__new_transition_5( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial );
}

void Capsule_Gen::actionchain_____Debug__C__Initial__new_transition_6( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial );
}

void Capsule_Gen::actionchain_____Debug__C__Initial__new_transition_7( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Gen::actionchain_____Debug__C__Initial__new_transition_8( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__boundary( msg );
    save_history( Debug__C__Initial, Debug__C__Initial__boundary );
}

void Capsule_Gen::actionchain_____Debug__GENERATING__GENERATING__3( const UMLRTMessage * msg )
{
    exitaction_____GENERATING( msg );
    transitionaction_____Debug__GENERATING__GENERATING__3( msg );
}

void Capsule_Gen::actionchain_____Debug__GENERATING__GENERATING__3__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__GENERATING__GENERATING__3__boundary( msg );
    transitionaction_____Debug__GENERATING__GENERATING__3__E( msg );
    entryaction_____GENERATING( msg );
}

void Capsule_Gen::actionchain_____Debug__GENERATING__GENERATING__3__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__GENERATING__GENERATING__3__S( msg );
    entryaction_____Debug__C__GENERATING__GENERATING__3__boundary( msg );
}

void Capsule_Gen::actionchain_____Debug__GENERATING__GENERATING__3__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__GENERATING__GENERATING__3__boundary( msg );
    transitionaction_____Debug__GENERATING__GENERATING__3__dbg( msg );
    entryaction_____Debug__C__GENERATING__GENERATING__3__boundary( msg );
}

void Capsule_Gen::actionchain_____Debug__InitDebug( const UMLRTMessage * msg )
{
    transitionaction_____Debug__InitDebug( msg );
    entryaction_____Debug__InitState( msg );
}

void Capsule_Gen::actionchain_____Debug__Initial( const UMLRTMessage * msg )
{
    exitaction_____Debug__InitState( msg );
    transitionaction_____Debug__Initial( msg );
}

void Capsule_Gen::actionchain_____Debug__Initial__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__boundary( msg );
    transitionaction_____Debug__Initial__E( msg );
    entryaction_____GENERATING( msg );
}

void Capsule_Gen::actionchain_____Debug__Initial__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__Initial__S( msg );
    entryaction_____Debug__C__Initial__boundary( msg );
}

void Capsule_Gen::actionchain_____Debug__Initial__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__boundary( msg );
    transitionaction_____Debug__Initial__dbg( msg );
    entryaction_____Debug__C__Initial__boundary( msg );
}

void Capsule_Gen::actionchain_____GENERATING__GENERATING__3( const UMLRTMessage * msg )
{
    transitionaction_____GENERATING__GENERATING__3( msg );
    entryaction_____GENERATING( msg );
}

void Capsule_Gen::actionchain_____Initial( const UMLRTMessage * msg )
{
    transitionaction_____Initial( msg );
    entryaction_____GENERATING( msg );
}

Capsule_Gen::State Capsule_Gen::junction_____Debug__C__GENERATING__GENERATING__3__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__GENERATING__GENERATING__3__Debug__init__trans__GENERATING__GENERATING__3( msg );
    return Debug__C__GENERATING__GENERATING__3__Debug__B__Ex__GENERATING;
}

Capsule_Gen::State Capsule_Gen::junction_____Debug__C__GENERATING__GENERATING__3__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__GENERATING__GENERATING__3__E( msg );
    return GENERATING;
}

Capsule_Gen::State Capsule_Gen::junction_____Debug__C__GENERATING__GENERATING__3__new_exitpoint_2( const UMLRTMessage * msg )
{
    actionchain_____Debug__GENERATING__GENERATING__3__dbg( msg );
    return choice_____Debug__C__GENERATING__GENERATING__3__deephistory( msg );
}

Capsule_Gen::State Capsule_Gen::junction_____Debug__C__Initial__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__Initial__Debug__init__trans__Initial( msg );
    return Debug__C__Initial__Debug__B__Ac__Initial;
}

Capsule_Gen::State Capsule_Gen::junction_____Debug__C__Initial__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__E( msg );
    return GENERATING;
}

Capsule_Gen::State Capsule_Gen::junction_____Debug__C__Initial__new_exitpoint_1( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__dbg( msg );
    return choice_____Debug__C__Initial__deephistory( msg );
}

Capsule_Gen::State Capsule_Gen::choice_____Debug__C__GENERATING__GENERATING__3__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__GENERATING__GENERATING__3, Debug__C__GENERATING__GENERATING__3__Debug__B__Ex__GENERATING ) )
    {
        actionchain_____Debug__C__GENERATING__GENERATING__3__new_transition_9( msg );
        return Debug__C__GENERATING__GENERATING__3__Debug__B__Ex__GENERATING;
    }
    else if( check_history( Debug__C__GENERATING__GENERATING__3, Debug__C__GENERATING__GENERATING__3__Debug__B__Ac__GENERATING__GENERATING__3 ) )
    {
        actionchain_____Debug__C__GENERATING__GENERATING__3__new_transition_10( msg );
        return Debug__C__GENERATING__GENERATING__3__Debug__B__Ac__GENERATING__GENERATING__3;
    }
    else if( check_history( Debug__C__GENERATING__GENERATING__3, Debug__C__GENERATING__GENERATING__3__Debug__A__Ac__GENERATING__GENERATING__3 ) )
    {
        actionchain_____Debug__C__GENERATING__GENERATING__3__new_transition_11( msg );
        return Debug__C__GENERATING__GENERATING__3__Debug__A__Ac__GENERATING__GENERATING__3;
    }
    else if( check_history( Debug__C__GENERATING__GENERATING__3, Debug__C__GENERATING__GENERATING__3__Debug__A__En__GENERATING ) )
    {
        actionchain_____Debug__C__GENERATING__GENERATING__3__new_transition_12( msg );
        return Debug__C__GENERATING__GENERATING__3__Debug__A__En__GENERATING;
    }
    else if( check_history( Debug__C__GENERATING__GENERATING__3, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__GENERATING__GENERATING__3__new_transition_13_to_boundary( msg );
        return Debug__C__GENERATING__GENERATING__3__boundary;
    }
    return currentState;
}

Capsule_Gen::State Capsule_Gen::choice_____Debug__C__Initial__deephistory( const UMLRTMessage * msg )
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

Capsule_Gen::State Capsule_Gen::choice_____Debug__Path__GENERATING__GENERATING__3( const UMLRTMessage * msg )
{
    if( action_____Debug__GENERATING__GENERATING__3__S__Debug__GuardGENERATING__GENERATING__3( msg ) )
    {
        actionchain_____Debug__GENERATING__GENERATING__3__S( msg );
        return junction_____Debug__C__GENERATING__GENERATING__3__en( msg );
    }
    else
    {
        actionchain_____GENERATING__GENERATING__3( msg );
        return GENERATING;
    }
    return currentState;
}

Capsule_Gen::State Capsule_Gen::choice_____Debug__Path__Initial( const UMLRTMessage * msg )
{
    if( action_____Debug__Initial__S__Debug__GuardInitial( msg ) )
    {
        actionchain_____Debug__Initial__S( msg );
        return junction_____Debug__C__Initial__en( msg );
    }
    else
    {
        actionchain_____Initial( msg );
        return GENERATING;
    }
    return currentState;
}

Capsule_Gen::State Capsule_Gen::state_____Debug__C__GENERATING__GENERATING__3__Debug__A__Ac__GENERATING__GENERATING__3( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__GENERATING__GENERATING__3__Debug__En__GENERATING( msg );
            return Debug__C__GENERATING__GENERATING__3__Debug__A__En__GENERATING;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__GENERATING__GENERATING__3__new_transition_16( msg );
            return junction_____Debug__C__GENERATING__GENERATING__3__new_exitpoint_2( msg );
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

Capsule_Gen::State Capsule_Gen::state_____Debug__C__GENERATING__GENERATING__3__Debug__A__En__GENERATING( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__GENERATING__GENERATING__3__Debug__end__trans__GENERATING__GENERATING__3( msg );
            return junction_____Debug__C__GENERATING__GENERATING__3__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__GENERATING__GENERATING__3__new_transition_17( msg );
            return junction_____Debug__C__GENERATING__GENERATING__3__new_exitpoint_2( msg );
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

Capsule_Gen::State Capsule_Gen::state_____Debug__C__GENERATING__GENERATING__3__Debug__B__Ac__GENERATING__GENERATING__3( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__GENERATING__GENERATING__3__Debug__AC__GENERATING__GENERATING__3( msg );
            return Debug__C__GENERATING__GENERATING__3__Debug__A__Ac__GENERATING__GENERATING__3;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__GENERATING__GENERATING__3__new_transition_15( msg );
            return junction_____Debug__C__GENERATING__GENERATING__3__new_exitpoint_2( msg );
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

Capsule_Gen::State Capsule_Gen::state_____Debug__C__GENERATING__GENERATING__3__Debug__B__Ex__GENERATING( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__GENERATING__GENERATING__3__Debug__Ex__GENERATING( msg );
            return Debug__C__GENERATING__GENERATING__3__Debug__B__Ac__GENERATING__GENERATING__3;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__GENERATING__GENERATING__3__new_transition_14( msg );
            return junction_____Debug__C__GENERATING__GENERATING__3__new_exitpoint_2( msg );
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

Capsule_Gen::State Capsule_Gen::state_____Debug__C__GENERATING__GENERATING__3__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__GENERATING__GENERATING__3__new_transition_18( msg );
            return junction_____Debug__C__GENERATING__GENERATING__3__new_exitpoint_2( msg );
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

Capsule_Gen::State Capsule_Gen::state_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Initial__Debug__En__GENERATING( msg );
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

Capsule_Gen::State Capsule_Gen::state_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg )
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

Capsule_Gen::State Capsule_Gen::state_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg )
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

Capsule_Gen::State Capsule_Gen::state_____Debug__C__Initial__boundary( const UMLRTMessage * msg )
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

Capsule_Gen::State Capsule_Gen::state_____Debug__InitState( const UMLRTMessage * msg )
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

Capsule_Gen::State Capsule_Gen::state_____GENERATING( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____Debug__GENERATING__GENERATING__3( msg );
            return choice_____Debug__Path__GENERATING__GENERATING__3( msg );
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
        Capsule_Gen::port_enter,
        "transmission",
        "enter",
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
        Capsule_Gen::port_extComm,
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
        Capsule_Gen::port_timer,
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
        Capsule_Gen::port_log,
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

static void instantiate_Gen( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_Gen( &Gen, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Gen = 
{
    "Gen",
    NULL,
    instantiate_Gen,
    0,
    NULL,
    4,
    portroles_border,
    0,
    NULL
};

