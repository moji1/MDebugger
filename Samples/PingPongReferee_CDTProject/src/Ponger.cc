
#include "Ponger.hh"

#include "ExtInterface.hh"
#include "PingPongProtocol.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtsignal.hh"
#include "umlrtslot.hh"
#include "umlrttimerprotocol.hh"
#include <cstddef>
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_Ponger::Capsule_Ponger( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, endPort( borderPorts[borderport_endPort] )
, extComm( internalPorts[internalport_extComm] )
, pongPort( borderPorts[borderport_pongPort] )
, pongerTimer( internalPorts[internalport_pongerTimer] )
, pongsSent( 0 )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[Debug__C__Initial] = "Debug__C__Initial";
    stateNames[Debug__C__endOfRound] = "Debug__C__endOfRound";
    stateNames[Debug__C__keepPlaying] = "Debug__C__keepPlaying";
    stateNames[Debug__C__onPing] = "Debug__C__onPing";
    stateNames[Debug__C__timeout] = "Debug__C__timeout";
    stateNames[Debug__C__Initial__Debug__A__Ac__Initial] = "Debug__C__Initial__Debug__A__Ac__Initial";
    stateNames[Debug__C__Initial__Debug__A__En__Initial] = "Debug__C__Initial__Debug__A__En__Initial";
    stateNames[Debug__C__Initial__Debug__B__Ac__Initial] = "Debug__C__Initial__Debug__B__Ac__Initial";
    stateNames[Debug__C__Initial__boundary] = "Debug__C__Initial__boundary";
    stateNames[Debug__C__endOfRound__Debug__A__Ac__endOfRound] = "Debug__C__endOfRound__Debug__A__Ac__endOfRound";
    stateNames[Debug__C__endOfRound__Debug__A__En__endOfRound] = "Debug__C__endOfRound__Debug__A__En__endOfRound";
    stateNames[Debug__C__endOfRound__Debug__B__Ac__endOfRound] = "Debug__C__endOfRound__Debug__B__Ac__endOfRound";
    stateNames[Debug__C__endOfRound__boundary] = "Debug__C__endOfRound__boundary";
    stateNames[Debug__C__keepPlaying__Debug__A__Ac__keepPlaying] = "Debug__C__keepPlaying__Debug__A__Ac__keepPlaying";
    stateNames[Debug__C__keepPlaying__Debug__A__En__keepPlaying] = "Debug__C__keepPlaying__Debug__A__En__keepPlaying";
    stateNames[Debug__C__keepPlaying__Debug__B__Ac__keepPlaying] = "Debug__C__keepPlaying__Debug__B__Ac__keepPlaying";
    stateNames[Debug__C__keepPlaying__boundary] = "Debug__C__keepPlaying__boundary";
    stateNames[Debug__C__onPing__Debug__A__Ac__onPing] = "Debug__C__onPing__Debug__A__Ac__onPing";
    stateNames[Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER] = "Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER";
    stateNames[Debug__C__onPing__Debug__B__Ac__onPing] = "Debug__C__onPing__Debug__B__Ac__onPing";
    stateNames[Debug__C__onPing__Debug__B__Ex__PLAYING] = "Debug__C__onPing__Debug__B__Ex__PLAYING";
    stateNames[Debug__C__onPing__boundary] = "Debug__C__onPing__boundary";
    stateNames[Debug__C__timeout__Debug__A__Ac__timeout] = "Debug__C__timeout__Debug__A__Ac__timeout";
    stateNames[Debug__C__timeout__Debug__B__Ac__timeout] = "Debug__C__timeout__Debug__B__Ac__timeout";
    stateNames[Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER] = "Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER";
    stateNames[Debug__C__timeout__boundary] = "Debug__C__timeout__boundary";
    stateNames[Debug__InitState] = "Debug__InitState";
    stateNames[PLAYING] = "PLAYING";
    stateNames[WAITING_FOR_TIMER] = "WAITING_FOR_TIMER";
    stateNames[SPECIAL_INTERNAL_STATE_TOP] = "<top>";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
    int i = 0;
    while( i < 5 )
        history[i++] = SPECIAL_INTERNAL_STATE_UNVISITED;
}










void Capsule_Ponger::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_endPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_endPort, index, true );
            break;
        case borderport_pongPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_pongPort, index, true );
            break;
        }
}

void Capsule_Ponger::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_endPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_endPort, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_endPort], index );
            break;
        case borderport_pongPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_pongPort, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_pongPort], index );
            break;
        }
}






void Capsule_Ponger::Debug__recallAllMsg()
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger operation Debug__recallAllMsg */
    pongPort.recallAll();
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_Ponger::Debug__variablesView()
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger operation Debug__variablesView */
    std::string tempS="";
    tempS.append("pongsSent,");
    tempS.append("Integer,");
    if(pongsSent!=0){
    char tempR[10];
    sprintf(tempR,"%d",pongsSent);
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

bool Capsule_Ponger::Debug__variablesChange( char * varName, char * varValue )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger operation Debug__variablesChange */
    std::string tempVarName="";
    tempVarName.append(varName);
    if ("pongsSent"==tempVarName){
    pongsSent=atoi(varValue);
    return true;
    }else 
    return false;
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_Ponger::Debug__sendEvent( debugEvents::EVENTSOURCEKIND eventSourceKind, debugEvents::EVENTTYPE eventType, const char * instanceName, int capsuleIndex, const char * signalName, const char * capsuleName, char * sourceName, char * reserve1, char * reserve2, const char * reserve3, const char * reserve4 )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger operation Debug__sendEvent */
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
    this->Debug__event.setPayloadField("Status",this->Debug__SRO.getStatusStr());
    if (eventSourceKind==debugEvents::TRANISTION){
    this->Debug__event.setPayloadField("Source",reserve1);
    this->Debug__event.setPayloadField("Target",reserve2);
    this->Debug__event.setPayloadField("Signal",signalName);
    this->Debug__event.setPayloadField("SenderCapsule",reserve3);
    this->Debug__event.setPayloadField("Port",reserve4);
    }
    std::string tempS=this->Debug__event.serialize();
    char eventStr[tempS.length()+1];
    strcpy(eventStr,tempS.c_str());
    extComm.event(eventStr).send();
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_Ponger::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case PLAYING:
        currentState = state_____PLAYING( &message );
        break;
    case WAITING_FOR_TIMER:
        currentState = state_____WAITING_FOR_TIMER( &message );
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
    case Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER:
        currentState = state_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( &message );
        break;
    case Debug__C__timeout__Debug__B__Ac__timeout:
        currentState = state_____Debug__C__timeout__Debug__B__Ac__timeout( &message );
        break;
    case Debug__C__timeout__Debug__A__Ac__timeout:
        currentState = state_____Debug__C__timeout__Debug__A__Ac__timeout( &message );
        break;
    case Debug__C__timeout__boundary:
        currentState = state_____Debug__C__timeout__boundary( &message );
        break;
    case Debug__C__keepPlaying__Debug__B__Ac__keepPlaying:
        currentState = state_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( &message );
        break;
    case Debug__C__keepPlaying__Debug__A__Ac__keepPlaying:
        currentState = state_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( &message );
        break;
    case Debug__C__keepPlaying__Debug__A__En__keepPlaying:
        currentState = state_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( &message );
        break;
    case Debug__C__keepPlaying__boundary:
        currentState = state_____Debug__C__keepPlaying__boundary( &message );
        break;
    case Debug__C__onPing__Debug__B__Ex__PLAYING:
        currentState = state_____Debug__C__onPing__Debug__B__Ex__PLAYING( &message );
        break;
    case Debug__C__onPing__Debug__B__Ac__onPing:
        currentState = state_____Debug__C__onPing__Debug__B__Ac__onPing( &message );
        break;
    case Debug__C__onPing__Debug__A__Ac__onPing:
        currentState = state_____Debug__C__onPing__Debug__A__Ac__onPing( &message );
        break;
    case Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER:
        currentState = state_____Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER( &message );
        break;
    case Debug__C__onPing__boundary:
        currentState = state_____Debug__C__onPing__boundary( &message );
        break;
    case Debug__C__endOfRound__Debug__B__Ac__endOfRound:
        currentState = state_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( &message );
        break;
    case Debug__C__endOfRound__Debug__A__Ac__endOfRound:
        currentState = state_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( &message );
        break;
    case Debug__C__endOfRound__Debug__A__En__endOfRound:
        currentState = state_____Debug__C__endOfRound__Debug__A__En__endOfRound( &message );
        break;
    case Debug__C__endOfRound__boundary:
        currentState = state_____Debug__C__endOfRound__boundary( &message );
        break;
    default:
        break;
    }
}

void Capsule_Ponger::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Debug__InitDebug( &message );
    currentState = Debug__InitState;
}

const char * Capsule_Ponger::getCurrentStateString() const
{
    return stateNames[currentState];
}





void Capsule_Ponger::save_history( Capsule_Ponger::State compositeState, Capsule_Ponger::State subState )
{
    history[compositeState] = subState;
}

bool Capsule_Ponger::check_history( Capsule_Ponger::State compositeState, Capsule_Ponger::State subState )
{
    return history[compositeState] == subState;
}

void Capsule_Ponger::update_state( Capsule_Ponger::State newState )
{
    currentState = newState;
}

void Capsule_Ponger::entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__Initial::Debug__A__Ac__Initial entry  */
    if (not(Debug__SRO.checkDebug("Initial","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("PLAYING","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__Initial::Region1::Debug__A__Ac__Initial",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::entryaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__Initial::Debug__A__En__Initial entry  */
    if (not(Debug__SRO.checkDebug("PLAYING","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__Initial::Region1::Debug__A__En__Initial",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__Initial::Debug__B__Ac__Initial entry  */
    if (not(Debug__SRO.checkDebug("Initial","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__Initial::Region1::Debug__B__Ac__Initial",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::entryaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__endOfRound::Debug__A__Ac__endOfRound entry  */
    if (not(Debug__SRO.checkDebug("endOfRound","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("PLAYING","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__endOfRound::Region1::Debug__A__Ac__endOfRound",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::entryaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__endOfRound::Debug__A__En__endOfRound entry  */
    if (not(Debug__SRO.checkDebug("PLAYING","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__endOfRound::Region1::Debug__A__En__endOfRound",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::entryaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__endOfRound::Debug__B__Ac__endOfRound entry  */
    if (not(Debug__SRO.checkDebug("endOfRound","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__endOfRound::Region1::Debug__B__Ac__endOfRound",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::entryaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__keepPlaying::Debug__A__Ac__keepPlaying entry  */
    if (not(Debug__SRO.checkDebug("keepPlaying","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("PLAYING","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__keepPlaying::Region1::Debug__A__Ac__keepPlaying",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::entryaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__keepPlaying::Debug__A__En__keepPlaying entry  */
    if (not(Debug__SRO.checkDebug("PLAYING","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__keepPlaying::Region1::Debug__A__En__keepPlaying",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::entryaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__keepPlaying::Debug__B__Ac__keepPlaying entry  */
    if (not(Debug__SRO.checkDebug("keepPlaying","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__keepPlaying::Region1::Debug__B__Ac__keepPlaying",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::entryaction_____Debug__C__onPing__Debug__A__Ac__onPing( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__onPing::Debug__A__Ac__onPing entry  */
    if (not(Debug__SRO.checkDebug("onPing","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("WAITING FOR TIMER","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__onPing::Region1::Debug__A__Ac__onPing",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::entryaction_____Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__onPing::Debug__A__En__WAITING FOR TIMER entry  */
    if (not(Debug__SRO.checkDebug("WAITING FOR TIMER","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__onPing::Region1::Debug__A__En__WAITING FOR TIMER",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::entryaction_____Debug__C__onPing__Debug__B__Ac__onPing( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__onPing::Debug__B__Ac__onPing entry  */
    if (not(Debug__SRO.checkDebug("PLAYING","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("onPing","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__onPing::Region1::Debug__B__Ac__onPing",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::entryaction_____Debug__C__onPing__Debug__B__Ex__PLAYING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__onPing::Debug__B__Ex__PLAYING entry  */
    if (not(Debug__SRO.checkDebug("PLAYING","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__onPing::Region1::Debug__B__Ex__PLAYING",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::entryaction_____Debug__C__timeout__Debug__A__Ac__timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__timeout::Debug__A__Ac__timeout entry  */
    if (not(Debug__SRO.checkDebug("timeout","","",3,TransitionEffectBreakPoint,1))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__timeout::Region1::Debug__A__Ac__timeout",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::entryaction_____Debug__C__timeout__Debug__B__Ac__timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__timeout::Debug__B__Ac__timeout entry  */
    if (not(Debug__SRO.checkDebug("WAITING FOR TIMER","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("timeout","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__timeout::Region1::Debug__B__Ac__timeout",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::entryaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__timeout::Debug__B__Ex__WAITING FOR TIMER entry  */
    if (not(Debug__SRO.checkDebug("WAITING FOR TIMER","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__timeout::Region1::Debug__B__Ex__WAITING FOR TIMER",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::entryaction_____PLAYING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::PLAYING entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::PLAYING",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::entryaction_____WAITING_FOR_TIMER( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::WAITING FOR TIMER entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::WAITING FOR TIMER",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__Initial::Debug__A__Ac__Initial exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__Initial::Region1::Debug__A__Ac__Initial",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::exitaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__Initial::Debug__A__En__Initial exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__Initial::Region1::Debug__A__En__Initial",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__Initial::Debug__B__Ac__Initial exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__Initial::Region1::Debug__B__Ac__Initial",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::exitaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__endOfRound::Debug__A__Ac__endOfRound exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__endOfRound::Region1::Debug__A__Ac__endOfRound",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::exitaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__endOfRound::Debug__A__En__endOfRound exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__endOfRound::Region1::Debug__A__En__endOfRound",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::exitaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__endOfRound::Debug__B__Ac__endOfRound exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__endOfRound::Region1::Debug__B__Ac__endOfRound",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::exitaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__keepPlaying::Debug__A__Ac__keepPlaying exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__keepPlaying::Region1::Debug__A__Ac__keepPlaying",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::exitaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__keepPlaying::Debug__A__En__keepPlaying exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__keepPlaying::Region1::Debug__A__En__keepPlaying",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::exitaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__keepPlaying::Debug__B__Ac__keepPlaying exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__keepPlaying::Region1::Debug__B__Ac__keepPlaying",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::exitaction_____Debug__C__onPing__Debug__A__Ac__onPing( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__onPing::Debug__A__Ac__onPing exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__onPing::Region1::Debug__A__Ac__onPing",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::exitaction_____Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__onPing::Debug__A__En__WAITING FOR TIMER exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__onPing::Region1::Debug__A__En__WAITING FOR TIMER",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::exitaction_____Debug__C__onPing__Debug__B__Ac__onPing( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__onPing::Debug__B__Ac__onPing exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__onPing::Region1::Debug__B__Ac__onPing",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::exitaction_____Debug__C__onPing__Debug__B__Ex__PLAYING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__onPing::Debug__B__Ex__PLAYING exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__onPing::Region1::Debug__B__Ex__PLAYING",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::exitaction_____Debug__C__timeout__Debug__A__Ac__timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__timeout::Debug__A__Ac__timeout exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__timeout::Region1::Debug__A__Ac__timeout",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::exitaction_____Debug__C__timeout__Debug__B__Ac__timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__timeout::Debug__B__Ac__timeout exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__timeout::Region1::Debug__B__Ac__timeout",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::exitaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__timeout::Debug__B__Ex__WAITING FOR TIMER exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__timeout::Region1::Debug__B__Ex__WAITING FOR TIMER",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::exitaction_____PLAYING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::PLAYING exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::PLAYING",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::exitaction_____WAITING_FOR_TIMER( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::WAITING FOR TIMER exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::WAITING FOR TIMER",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__Initial transition Debug__C__Initial::Debug__B__Ac__Initial,Debug__C__Initial::Debug__A__Ac__Initial,dbgExec:extComm */
    log.log("Ponger is ready");
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__Initial::Region1::Debug__Ac__Initial",(char *)"Debug__B__Ac__Initial",(char *)"Debug__A__Ac__Initial",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__C__Initial__Debug__En__PLAYING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__Initial transition Debug__C__Initial::Debug__A__Ac__Initial,Debug__C__Initial::Debug__A__En__Initial,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__Initial::Region1::Debug__En__PLAYING",(char *)"Debug__A__Ac__Initial",(char *)"Debug__A__En__Initial",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__Initial transition Debug__C__Initial::Debug__A__En__Initial,Debug__C__Initial::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__Initial::Region1::Debug__end__trans__Initial",(char *)"Debug__A__En__Initial",(char *)"ex",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__Initial transition Debug__C__Initial::en,Debug__C__Initial::Debug__B__Ac__Initial */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__Initial::Region1::Debug__init__trans__Initial",(char *)"en",(char *)"Debug__B__Ac__Initial",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__C__endOfRound__Debug__Ac__endOfRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__endOfRound transition Debug__C__endOfRound::Debug__B__Ac__endOfRound,Debug__C__endOfRound::Debug__A__Ac__endOfRound,dbgExec:extComm */
    log.show("ending round.\n");
    endPort.end().send();
    this->pongsSent = 0;
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__endOfRound::Region1::Debug__Ac__endOfRound",(char *)"Debug__B__Ac__endOfRound",(char *)"Debug__A__Ac__endOfRound",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__C__endOfRound__Debug__En__PLAYING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__endOfRound transition Debug__C__endOfRound::Debug__A__Ac__endOfRound,Debug__C__endOfRound::Debug__A__En__endOfRound,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__endOfRound::Region1::Debug__En__PLAYING",(char *)"Debug__A__Ac__endOfRound",(char *)"Debug__A__En__endOfRound",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__C__endOfRound__Debug__end__trans__endOfRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__endOfRound transition Debug__C__endOfRound::Debug__A__En__endOfRound,Debug__C__endOfRound::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__endOfRound::Region1::Debug__end__trans__endOfRound",(char *)"Debug__A__En__endOfRound",(char *)"ex",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__C__endOfRound__Debug__init__trans__endOfRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__endOfRound transition Debug__C__endOfRound::en,Debug__C__endOfRound::Debug__B__Ac__endOfRound */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__endOfRound::Region1::Debug__init__trans__endOfRound",(char *)"en",(char *)"Debug__B__Ac__endOfRound",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__C__keepPlaying__Debug__Ac__keepPlaying( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__keepPlaying transition Debug__C__keepPlaying::Debug__B__Ac__keepPlaying,Debug__C__keepPlaying::Debug__A__Ac__keepPlaying,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__keepPlaying::Region1::Debug__Ac__keepPlaying",(char *)"Debug__B__Ac__keepPlaying",(char *)"Debug__A__Ac__keepPlaying",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__C__keepPlaying__Debug__En__PLAYING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__keepPlaying transition Debug__C__keepPlaying::Debug__A__Ac__keepPlaying,Debug__C__keepPlaying::Debug__A__En__keepPlaying,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__keepPlaying::Region1::Debug__En__PLAYING",(char *)"Debug__A__Ac__keepPlaying",(char *)"Debug__A__En__keepPlaying",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__C__keepPlaying__Debug__end__trans__keepPlaying( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__keepPlaying transition Debug__C__keepPlaying::Debug__A__En__keepPlaying,Debug__C__keepPlaying::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__keepPlaying::Region1::Debug__end__trans__keepPlaying",(char *)"Debug__A__En__keepPlaying",(char *)"ex",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__C__keepPlaying__Debug__init__trans__keepPlaying( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__keepPlaying transition Debug__C__keepPlaying::en,Debug__C__keepPlaying::Debug__B__Ac__keepPlaying */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__keepPlaying::Region1::Debug__init__trans__keepPlaying",(char *)"en",(char *)"Debug__B__Ac__keepPlaying",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__C__onPing__Debug__AC__onPing( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__onPing transition Debug__C__onPing::Debug__B__Ac__onPing,Debug__C__onPing::Debug__A__Ac__onPing,dbgExec:extComm */
    log.show("ping received.\n");
    pongerTimer.informIn(UMLRTTimespec(1,0));
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__onPing::Region1::Debug__AC__onPing",(char *)"Debug__B__Ac__onPing",(char *)"Debug__A__Ac__onPing",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__C__onPing__Debug__En__WAITING_FOR_TIMER( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__onPing transition Debug__C__onPing::Debug__A__Ac__onPing,Debug__C__onPing::Debug__A__En__WAITING FOR TIMER,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__onPing::Region1::Debug__En__WAITING FOR TIMER",(char *)"Debug__A__Ac__onPing",(char *)"Debug__A__En__WAITING FOR TIMER",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__C__onPing__Debug__Ex__PLAYING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__onPing transition Debug__C__onPing::Debug__B__Ex__PLAYING,Debug__C__onPing::Debug__B__Ac__onPing,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__onPing::Region1::Debug__Ex__PLAYING",(char *)"Debug__B__Ex__PLAYING",(char *)"Debug__B__Ac__onPing",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__C__onPing__Debug__end__trans__onPing( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__onPing transition Debug__C__onPing::Debug__A__En__WAITING FOR TIMER,Debug__C__onPing::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__onPing::Region1::Debug__end__trans__onPing",(char *)"Debug__A__En__WAITING FOR TIMER",(char *)"ex",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__C__onPing__Debug__init__trans__onPing( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__onPing transition Debug__C__onPing::en,Debug__C__onPing::Debug__B__Ex__PLAYING */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__onPing::Region1::Debug__init__trans__onPing",(char *)"en",(char *)"Debug__B__Ex__PLAYING",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__C__timeout__Debug__AC__timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__timeout transition Debug__C__timeout::Debug__B__Ac__timeout,Debug__C__timeout::Debug__A__Ac__timeout,dbgExec:extComm */
    pongPort.pong().send();
    this->pongsSent++;
    log.show("pong message sent.\n");
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__timeout::Region1::Debug__AC__timeout",(char *)"Debug__B__Ac__timeout",(char *)"Debug__A__Ac__timeout",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__C__timeout__Debug__Ex__WAITING_FOR_TIMER( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__timeout transition Debug__C__timeout::Debug__B__Ex__WAITING FOR TIMER,Debug__C__timeout::Debug__B__Ac__timeout,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__timeout::Region1::Debug__Ex__WAITING FOR TIMER",(char *)"Debug__B__Ex__WAITING FOR TIMER",(char *)"Debug__B__Ac__timeout",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__C__timeout__Debug__end__trans__timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger::Debug__C__timeout transition Debug__C__timeout::Debug__A__Ac__timeout,Debug__C__timeout::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__C__timeout::Region1::Debug__end__trans__timeout",(char *)"Debug__A__Ac__timeout",(char *)"ex",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__InitDebug( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Pseudo2,Debug__InitState */
    std::cout<<this->getName()<<" : is Starting\n";
    this->Debug__SRO.setExecMode(Stepping);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__InitState,Debug__Path__Initial,rtBound:extComm */
    if (this->Debug__SRO.getExecMode()==Stepping){
    Debug__SRO.addTransitionsFromState("","Initial","PLAYING","","");
    Debug__SRO.addTransitionsFromState("PLAYING","onPing","WAITING FOR TIMER","ping","PingPongProtocol");
    Debug__SRO.addTransitionsFromState("ThreePongsSent?","keepPlaying","PLAYING","","");
    Debug__SRO.addTransitionsFromState("STARTING ROUND","startRound","WAITING FOR END OF ROUND","timeout","Timing");
    Debug__SRO.addTransitionsFromState("ThreePongsSent?","endOfRound","PLAYING","","");
    Debug__SRO.addTransitionsFromState("WAITING FOR END OF ROUND","endRound","STARTING ROUND","end","endProtocol");
    Debug__SRO.addTransitionsFromState("","Initial","STARTING ROUND","","");
    Debug__SRO.addTransitionsFromState("WAITING FOR TIMER","timeout","ThreePongsSent?","timeout","Timing");
    std::cout<<this->getName()<<": Connection with debugger is in progress\n";
    char  tempS[256];
    sprintf(tempS,"%s%d",this->getName(),(int)this->getIndex());
    extComm.registerToControl(tempS).send();
    Debug__sendEvent(debugEvents::DEBUG,debugEvents::REGISTER,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"",(char *)"",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__Initial__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__Initial::ex,PLAYING */
    this->Debug__recallAllMsg();
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__Initial__E",(char *)"ex",(char *)"PLAYING",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__Initial__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__Path__Initial,Debug__C__Initial::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__Initial__S",(char *)"Debug__Path__Initial",(char *)"en",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__Initial__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__Initial::new_exitpoint_6,Debug__C__Initial */
    msg->defer();
    std::cout<<"A message defered"<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__Initial__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__Initial::new_exitpoint_5,Debug__C__Initial */
    this->Debug__SRO.setExecMode((ExecMode)( *(int *)msg->getParam( 0 ) ));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__Initial__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__Initial::new_exitpoint_3,Debug__C__Initial */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.remBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__Initial__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__Initial::new_exitpoint_2,Debug__C__Initial */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.addBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__Initial__dbg__varChange( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__Initial::new_exitpoint_1,Debug__C__Initial */
    char varName1[256];
    char varValue1[1024];
    sprintf(varName1,"%s",(*(const char * *)msg->getParam( 0 )));
    sprintf(varValue1,"%s",(*(const char * *)msg->getParam( 1 )));
    this->Debug__variablesChange(varName1,varValue1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__Initial__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__Initial::new_exitpoint_4,Debug__C__Initial */
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__endOfRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition ThreePongsSent?,Debug__Path__endOfRound */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__endOfRound",(char *)"ThreePongsSent?",(char *)"Debug__Path__endOfRound",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__endOfRound__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__endOfRound::ex,PLAYING */
    this->Debug__recallAllMsg();
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__endOfRound__E",(char *)"ex",(char *)"PLAYING",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__endOfRound__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__Path__endOfRound,Debug__C__endOfRound::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__endOfRound__S",(char *)"Debug__Path__endOfRound",(char *)"en",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__endOfRound__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__endOfRound::new_exitpoint_30,Debug__C__endOfRound */
    msg->defer();
    std::cout<<"A message defered"<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__endOfRound__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__endOfRound::new_exitpoint_29,Debug__C__endOfRound */
    this->Debug__SRO.setExecMode((ExecMode)( *(int *)msg->getParam( 0 ) ));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__endOfRound__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__endOfRound::new_exitpoint_27,Debug__C__endOfRound */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.remBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__endOfRound__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__endOfRound::new_exitpoint_26,Debug__C__endOfRound */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.addBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__endOfRound__dbg__varChange( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__endOfRound::new_exitpoint_25,Debug__C__endOfRound */
    char varName1[256];
    char varValue1[1024];
    sprintf(varName1,"%s",(*(const char * *)msg->getParam( 0 )));
    sprintf(varValue1,"%s",(*(const char * *)msg->getParam( 1 )));
    this->Debug__variablesChange(varName1,varValue1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__endOfRound__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__endOfRound::new_exitpoint_28,Debug__C__endOfRound */
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__keepPlaying( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition ThreePongsSent?,Debug__Path__keepPlaying */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__keepPlaying",(char *)"ThreePongsSent?",(char *)"Debug__Path__keepPlaying",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__keepPlaying__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__keepPlaying::ex,PLAYING */
    this->Debug__recallAllMsg();
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__keepPlaying__E",(char *)"ex",(char *)"PLAYING",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__keepPlaying__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__Path__keepPlaying,Debug__C__keepPlaying::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__keepPlaying__S",(char *)"Debug__Path__keepPlaying",(char *)"en",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__keepPlaying__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__keepPlaying::new_exitpoint_18,Debug__C__keepPlaying */
    msg->defer();
    std::cout<<"A message defered"<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__keepPlaying__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__keepPlaying::new_exitpoint_17,Debug__C__keepPlaying */
    this->Debug__SRO.setExecMode((ExecMode)( *(int *)msg->getParam( 0 ) ));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__keepPlaying__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__keepPlaying::new_exitpoint_15,Debug__C__keepPlaying */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.remBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__keepPlaying__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__keepPlaying::new_exitpoint_14,Debug__C__keepPlaying */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.addBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__keepPlaying__dbg__varChange( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__keepPlaying::new_exitpoint_13,Debug__C__keepPlaying */
    char varName1[256];
    char varValue1[1024];
    sprintf(varName1,"%s",(*(const char * *)msg->getParam( 0 )));
    sprintf(varValue1,"%s",(*(const char * *)msg->getParam( 1 )));
    this->Debug__variablesChange(varName1,varValue1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__keepPlaying__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__keepPlaying::new_exitpoint_16,Debug__C__keepPlaying */
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__onPing( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition PLAYING,Debug__Path__onPing,ping:pongPort */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__onPing",(char *)"PLAYING",(char *)"Debug__Path__onPing",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__onPing__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__onPing::ex,WAITING FOR TIMER */
    this->Debug__recallAllMsg();
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__onPing__E",(char *)"ex",(char *)"WAITING FOR TIMER",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__onPing__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__Path__onPing,Debug__C__onPing::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__onPing__S",(char *)"Debug__Path__onPing",(char *)"en",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__onPing__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__onPing::new_exitpoint_24,Debug__C__onPing */
    msg->defer();
    std::cout<<"A message defered"<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__onPing__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__onPing::new_exitpoint_23,Debug__C__onPing */
    this->Debug__SRO.setExecMode((ExecMode)( *(int *)msg->getParam( 0 ) ));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__onPing__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__onPing::new_exitpoint_21,Debug__C__onPing */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.remBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__onPing__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__onPing::new_exitpoint_20,Debug__C__onPing */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.addBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__onPing__dbg__varChange( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__onPing::new_exitpoint_19,Debug__C__onPing */
    char varName1[256];
    char varValue1[1024];
    sprintf(varName1,"%s",(*(const char * *)msg->getParam( 0 )));
    sprintf(varValue1,"%s",(*(const char * *)msg->getParam( 1 )));
    this->Debug__variablesChange(varName1,varValue1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__onPing__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__onPing::new_exitpoint_22,Debug__C__onPing */
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition WAITING FOR TIMER,Debug__Path__timeout,timeout:pongerTimer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__timeout",(char *)"WAITING FOR TIMER",(char *)"Debug__Path__timeout",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__timeout__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__timeout::ex,ThreePongsSent? */
    this->Debug__recallAllMsg();
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__timeout__E",(char *)"ex",(char *)"ThreePongsSent?",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__timeout__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__Path__timeout,Debug__C__timeout::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Debug__timeout__S",(char *)"Debug__Path__timeout",(char *)"en",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__timeout__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__timeout::new_exitpoint_12,Debug__C__timeout */
    msg->defer();
    std::cout<<"A message defered"<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__timeout__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__timeout::new_exitpoint_11,Debug__C__timeout */
    this->Debug__SRO.setExecMode((ExecMode)( *(int *)msg->getParam( 0 ) ));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__timeout__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__timeout::new_exitpoint_9,Debug__C__timeout */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.remBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__timeout__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__timeout::new_exitpoint_8,Debug__C__timeout */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.addBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__timeout__dbg__varChange( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__timeout::new_exitpoint_7,Debug__C__timeout */
    char varName1[256];
    char varValue1[1024];
    sprintf(varName1,"%s",(*(const char * *)msg->getParam( 0 )));
    sprintf(varValue1,"%s",(*(const char * *)msg->getParam( 1 )));
    this->Debug__variablesChange(varName1,varValue1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Debug__timeout__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__C__timeout::new_exitpoint_10,Debug__C__timeout */
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__Path__Initial,PLAYING */
    log.log("Ponger is ready");
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::Initial",(char *)"Debug__Path__Initial",(char *)"PLAYING",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____endOfRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__Path__endOfRound,PLAYING */
    log.show("ending round.\n");
    endPort.end().send();
    this->pongsSent = 0;
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::endOfRound",(char *)"Debug__Path__endOfRound",(char *)"PLAYING",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____keepPlaying( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__Path__keepPlaying,PLAYING */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::keepPlaying",(char *)"Debug__Path__keepPlaying",(char *)"PLAYING",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____onPing( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__Path__onPing,WAITING FOR TIMER */
    log.show("ping received.\n");
    pongerTimer.informIn(UMLRTTimespec(1,0));
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::onPing",(char *)"Debug__Path__onPing",(char *)"WAITING FOR TIMER",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::transitionaction_____timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger transition Debug__Path__timeout,ThreePongsSent? */
    pongPort.pong().send();
    this->pongsSent++;
    log.show("pong message sent.\n");
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Ponger::StateMachine::Region::timeout",(char *)"Debug__Path__timeout",(char *)"ThreePongsSent?",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Ponger::guard_____Debug__Initial__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger guard Debug__Path__Initial,Debug__C__Initial::en */
    return Debug__SRO.checkDebug("Pseudo2","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Ponger::guard_____Debug__endOfRound__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger guard Debug__Path__endOfRound,Debug__C__endOfRound::en */
    return Debug__SRO.checkDebug("ThreePongsSent?","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Ponger::guard_____Debug__keepPlaying( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger guard ThreePongsSent?,Debug__Path__keepPlaying */
    bool sendMorePongs = this->pongsSent < 3;
    return sendMorePongs;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Ponger::guard_____Debug__keepPlaying__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger guard Debug__Path__keepPlaying,Debug__C__keepPlaying::en */
    return Debug__SRO.checkDebug("ThreePongsSent?","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Ponger::guard_____Debug__onPing__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger guard Debug__Path__onPing,Debug__C__onPing::en */
    return Debug__SRO.checkDebug("PLAYING",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Ponger::guard_____Debug__timeout__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Ponger guard Debug__Path__timeout,Debug__C__timeout::en */
    return Debug__SRO.checkDebug("WAITING FOR TIMER",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    transitionaction_____Debug__C__Initial__Debug__Ac__Initial( msg );
    update_state( Debug__C__Initial__Debug__A__Ac__Initial );
    entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__Debug__En__PLAYING( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    transitionaction_____Debug__C__Initial__Debug__En__PLAYING( msg );
    update_state( Debug__C__Initial__Debug__A__En__Initial );
    entryaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    update_state( Debug__C__Initial );
    transitionaction_____Debug__C__Initial__Debug__end__trans__Initial( msg );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__Initial__Debug__init__trans__Initial( msg );
    update_state( Debug__C__Initial__Debug__B__Ac__Initial );
    entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_1( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial__Debug__B__Ac__Initial );
    entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_10( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_11( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_12( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_13( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_14( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_15( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_16( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_17( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_18( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_19( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_2( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial__Debug__A__Ac__Initial );
    entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_20( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_21( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_22( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_23( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_24( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_25( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_26( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_27( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_28( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_29( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_3( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial__Debug__A__En__Initial );
    entryaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_4_to_unvisited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_5_to_visited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_6( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_7( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_8( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Ponger::actionchain_____Debug__C__Initial__new_transition_9( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__Debug__Ac__endOfRound( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    transitionaction_____Debug__C__endOfRound__Debug__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound__Debug__A__Ac__endOfRound );
    entryaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__Debug__En__PLAYING( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    transitionaction_____Debug__C__endOfRound__Debug__En__PLAYING( msg );
    update_state( Debug__C__endOfRound__Debug__A__En__endOfRound );
    entryaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__Debug__end__trans__endOfRound( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    transitionaction_____Debug__C__endOfRound__Debug__end__trans__endOfRound( msg );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__En__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__Debug__init__trans__endOfRound( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__endOfRound__Debug__init__trans__endOfRound( msg );
    update_state( Debug__C__endOfRound__Debug__B__Ac__endOfRound );
    entryaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_124( const UMLRTMessage * msg )
{
    update_state( Debug__C__endOfRound__Debug__B__Ac__endOfRound );
    entryaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_125( const UMLRTMessage * msg )
{
    update_state( Debug__C__endOfRound__Debug__A__Ac__endOfRound );
    entryaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_126( const UMLRTMessage * msg )
{
    update_state( Debug__C__endOfRound__Debug__A__En__endOfRound );
    entryaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_127_to_unvisited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__endOfRound__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_128_to_visited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__endOfRound__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_129( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__B__Ac__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_130( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__Ac__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_131( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__En__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_132( const UMLRTMessage * msg )
{
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_133( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__B__Ac__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_134( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__Ac__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_135( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__En__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_136( const UMLRTMessage * msg )
{
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_137( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__B__Ac__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_138( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__Ac__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_139( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__En__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_140( const UMLRTMessage * msg )
{
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_141( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__B__Ac__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_142( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__Ac__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_143( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__En__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_144( const UMLRTMessage * msg )
{
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_145( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__B__Ac__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_146( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__Ac__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_147( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__En__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_148( const UMLRTMessage * msg )
{
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_149( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__B__Ac__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_150( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__Ac__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_151( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__En__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__C__endOfRound__new_transition_152( const UMLRTMessage * msg )
{
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__Debug__Ac__keepPlaying( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    transitionaction_____Debug__C__keepPlaying__Debug__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying__Debug__A__Ac__keepPlaying );
    entryaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__Debug__En__PLAYING( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    transitionaction_____Debug__C__keepPlaying__Debug__En__PLAYING( msg );
    update_state( Debug__C__keepPlaying__Debug__A__En__keepPlaying );
    entryaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__Debug__end__trans__keepPlaying( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    transitionaction_____Debug__C__keepPlaying__Debug__end__trans__keepPlaying( msg );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__En__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__Debug__init__trans__keepPlaying( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__keepPlaying__Debug__init__trans__keepPlaying( msg );
    update_state( Debug__C__keepPlaying__Debug__B__Ac__keepPlaying );
    entryaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_59( const UMLRTMessage * msg )
{
    update_state( Debug__C__keepPlaying__Debug__B__Ac__keepPlaying );
    entryaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_60( const UMLRTMessage * msg )
{
    update_state( Debug__C__keepPlaying__Debug__A__Ac__keepPlaying );
    entryaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_61( const UMLRTMessage * msg )
{
    update_state( Debug__C__keepPlaying__Debug__A__En__keepPlaying );
    entryaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_62_to_unvisited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__keepPlaying__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_63_to_visited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__keepPlaying__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_64( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__B__Ac__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_65( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__Ac__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_66( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__En__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_67( const UMLRTMessage * msg )
{
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_68( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__B__Ac__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_69( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__Ac__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_70( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__En__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_71( const UMLRTMessage * msg )
{
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_72( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__B__Ac__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_73( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__Ac__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_74( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__En__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_75( const UMLRTMessage * msg )
{
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_76( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__B__Ac__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_77( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__Ac__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_78( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__En__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_79( const UMLRTMessage * msg )
{
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_80( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__B__Ac__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_81( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__Ac__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_82( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__En__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_83( const UMLRTMessage * msg )
{
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_84( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__B__Ac__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_85( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__Ac__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_86( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__En__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__C__keepPlaying__new_transition_87( const UMLRTMessage * msg )
{
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__Debug__AC__onPing( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__B__Ac__onPing( msg );
    update_state( Debug__C__onPing );
    transitionaction_____Debug__C__onPing__Debug__AC__onPing( msg );
    update_state( Debug__C__onPing__Debug__A__Ac__onPing );
    entryaction_____Debug__C__onPing__Debug__A__Ac__onPing( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__Debug__En__WAITING_FOR_TIMER( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__A__Ac__onPing( msg );
    update_state( Debug__C__onPing );
    transitionaction_____Debug__C__onPing__Debug__En__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER );
    entryaction_____Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__Debug__Ex__PLAYING( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__B__Ex__PLAYING( msg );
    update_state( Debug__C__onPing );
    transitionaction_____Debug__C__onPing__Debug__Ex__PLAYING( msg );
    update_state( Debug__C__onPing__Debug__B__Ac__onPing );
    entryaction_____Debug__C__onPing__Debug__B__Ac__onPing( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__Debug__end__trans__onPing( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__onPing );
    transitionaction_____Debug__C__onPing__Debug__end__trans__onPing( msg );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__Debug__init__trans__onPing( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__onPing__Debug__init__trans__onPing( msg );
    update_state( Debug__C__onPing__Debug__B__Ex__PLAYING );
    entryaction_____Debug__C__onPing__Debug__B__Ex__PLAYING( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_100( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__B__Ac__onPing( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__B__Ac__onPing );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_101( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__A__Ac__onPing( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__A__Ac__onPing );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_102( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_103( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_104( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__B__Ex__PLAYING( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__B__Ex__PLAYING );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_105( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__B__Ac__onPing( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__B__Ac__onPing );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_106( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__A__Ac__onPing( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__A__Ac__onPing );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_107( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_108( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_109( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__B__Ex__PLAYING( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__B__Ex__PLAYING );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_110( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__B__Ac__onPing( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__B__Ac__onPing );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_111( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__A__Ac__onPing( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__A__Ac__onPing );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_112( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_113( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_114( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__B__Ex__PLAYING( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__B__Ex__PLAYING );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_115( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__B__Ac__onPing( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__B__Ac__onPing );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_116( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__A__Ac__onPing( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__A__Ac__onPing );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_117( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_118( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_119( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__B__Ex__PLAYING( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__B__Ex__PLAYING );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_120( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__B__Ac__onPing( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__B__Ac__onPing );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_121( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__A__Ac__onPing( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__A__Ac__onPing );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_122( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_123( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_88( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPing__Debug__B__Ex__PLAYING );
    entryaction_____Debug__C__onPing__Debug__B__Ex__PLAYING( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_89( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPing__Debug__B__Ac__onPing );
    entryaction_____Debug__C__onPing__Debug__B__Ac__onPing( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_90( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPing__Debug__A__Ac__onPing );
    entryaction_____Debug__C__onPing__Debug__A__Ac__onPing( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_91( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER );
    entryaction_____Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_92_to_unvisited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPing__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_93_to_visited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPing__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_94( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__B__Ex__PLAYING( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__B__Ex__PLAYING );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_95( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__B__Ac__onPing( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__B__Ac__onPing );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_96( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__A__Ac__onPing( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__A__Ac__onPing );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_97( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_98( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__onPing__new_transition_99( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPing__Debug__B__Ex__PLAYING( msg );
    update_state( Debug__C__onPing );
    save_history( Debug__C__onPing, Debug__C__onPing__Debug__B__Ex__PLAYING );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__Debug__AC__timeout( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    transitionaction_____Debug__C__timeout__Debug__AC__timeout( msg );
    update_state( Debug__C__timeout__Debug__A__Ac__timeout );
    entryaction_____Debug__C__timeout__Debug__A__Ac__timeout( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__Debug__Ex__WAITING_FOR_TIMER( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__timeout );
    transitionaction_____Debug__C__timeout__Debug__Ex__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__timeout__Debug__B__Ac__timeout );
    entryaction_____Debug__C__timeout__Debug__B__Ac__timeout( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__Debug__end__trans__timeout( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    transitionaction_____Debug__C__timeout__Debug__end__trans__timeout( msg );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__A__Ac__timeout );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__Debug__init__trans__timeout( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER );
    entryaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_30( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER );
    entryaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_31( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout__Debug__B__Ac__timeout );
    entryaction_____Debug__C__timeout__Debug__B__Ac__timeout( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_32( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout__Debug__A__Ac__timeout );
    entryaction_____Debug__C__timeout__Debug__A__Ac__timeout( msg );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_33_to_unvisited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_34_to_visited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_35( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_36( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ac__timeout );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_37( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__A__Ac__timeout );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_38( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_39( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_40( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ac__timeout );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_41( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__A__Ac__timeout );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_42( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_43( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_44( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ac__timeout );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_45( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__A__Ac__timeout );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_46( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_47( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_48( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ac__timeout );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_49( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__A__Ac__timeout );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_50( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_51( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_52( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ac__timeout );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_53( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__A__Ac__timeout );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_54( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__boundary );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_55( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_56( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ac__timeout );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_57( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__A__Ac__timeout );
}

void Capsule_Ponger::actionchain_____Debug__C__timeout__new_transition_58( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__boundary );
}

void Capsule_Ponger::actionchain_____Debug__InitDebug( const UMLRTMessage * msg )
{
    transitionaction_____Debug__InitDebug( msg );
    update_state( Debug__InitState );
}

void Capsule_Ponger::actionchain_____Debug__Initial( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial( msg );
}

void Capsule_Ponger::actionchain_____Debug__Initial__E( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial__E( msg );
    update_state( PLAYING );
    entryaction_____PLAYING( msg );
}

void Capsule_Ponger::actionchain_____Debug__Initial__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__Initial__S( msg );
    update_state( Debug__C__Initial );
}

void Capsule_Ponger::actionchain_____Debug__Initial__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial__dbg__dbgDeferMsg( msg );
    update_state( Debug__C__Initial );
}

void Capsule_Ponger::actionchain_____Debug__Initial__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial__dbg__dbgSetExecMode( msg );
    update_state( Debug__C__Initial );
}

void Capsule_Ponger::actionchain_____Debug__Initial__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial__dbg__remBreakPoint( msg );
    update_state( Debug__C__Initial );
}

void Capsule_Ponger::actionchain_____Debug__Initial__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial__dbg__setBreakPoint( msg );
    update_state( Debug__C__Initial );
}

void Capsule_Ponger::actionchain_____Debug__Initial__dbg__varChange( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial__dbg__varChange( msg );
    update_state( Debug__C__Initial );
}

void Capsule_Ponger::actionchain_____Debug__Initial__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial__dbg__viewBreakPoints( msg );
    update_state( Debug__C__Initial );
}

void Capsule_Ponger::actionchain_____Debug__endOfRound( const UMLRTMessage * msg )
{
    transitionaction_____Debug__endOfRound( msg );
}

void Capsule_Ponger::actionchain_____Debug__endOfRound__E( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__endOfRound__E( msg );
    update_state( PLAYING );
    entryaction_____PLAYING( msg );
}

void Capsule_Ponger::actionchain_____Debug__endOfRound__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__endOfRound__S( msg );
    update_state( Debug__C__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__endOfRound__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__endOfRound__dbg__dbgDeferMsg( msg );
    update_state( Debug__C__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__endOfRound__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__endOfRound__dbg__dbgSetExecMode( msg );
    update_state( Debug__C__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__endOfRound__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__endOfRound__dbg__remBreakPoint( msg );
    update_state( Debug__C__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__endOfRound__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__endOfRound__dbg__setBreakPoint( msg );
    update_state( Debug__C__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__endOfRound__dbg__varChange( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__endOfRound__dbg__varChange( msg );
    update_state( Debug__C__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__endOfRound__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__endOfRound__dbg__viewBreakPoints( msg );
    update_state( Debug__C__endOfRound );
}

void Capsule_Ponger::actionchain_____Debug__keepPlaying( const UMLRTMessage * msg )
{
    transitionaction_____Debug__keepPlaying( msg );
}

void Capsule_Ponger::actionchain_____Debug__keepPlaying__E( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__keepPlaying__E( msg );
    update_state( PLAYING );
    entryaction_____PLAYING( msg );
}

void Capsule_Ponger::actionchain_____Debug__keepPlaying__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__keepPlaying__S( msg );
    update_state( Debug__C__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__keepPlaying__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__keepPlaying__dbg__dbgDeferMsg( msg );
    update_state( Debug__C__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__keepPlaying__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__keepPlaying__dbg__dbgSetExecMode( msg );
    update_state( Debug__C__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__keepPlaying__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__keepPlaying__dbg__remBreakPoint( msg );
    update_state( Debug__C__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__keepPlaying__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__keepPlaying__dbg__setBreakPoint( msg );
    update_state( Debug__C__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__keepPlaying__dbg__varChange( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__keepPlaying__dbg__varChange( msg );
    update_state( Debug__C__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__keepPlaying__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__keepPlaying__dbg__viewBreakPoints( msg );
    update_state( Debug__C__keepPlaying );
}

void Capsule_Ponger::actionchain_____Debug__onPing( const UMLRTMessage * msg )
{
    exitaction_____PLAYING( msg );
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__onPing( msg );
}

void Capsule_Ponger::actionchain_____Debug__onPing__E( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__onPing__E( msg );
    update_state( WAITING_FOR_TIMER );
    entryaction_____WAITING_FOR_TIMER( msg );
}

void Capsule_Ponger::actionchain_____Debug__onPing__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__onPing__S( msg );
    update_state( Debug__C__onPing );
}

void Capsule_Ponger::actionchain_____Debug__onPing__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__onPing__dbg__dbgDeferMsg( msg );
    update_state( Debug__C__onPing );
}

void Capsule_Ponger::actionchain_____Debug__onPing__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__onPing__dbg__dbgSetExecMode( msg );
    update_state( Debug__C__onPing );
}

void Capsule_Ponger::actionchain_____Debug__onPing__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__onPing__dbg__remBreakPoint( msg );
    update_state( Debug__C__onPing );
}

void Capsule_Ponger::actionchain_____Debug__onPing__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__onPing__dbg__setBreakPoint( msg );
    update_state( Debug__C__onPing );
}

void Capsule_Ponger::actionchain_____Debug__onPing__dbg__varChange( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__onPing__dbg__varChange( msg );
    update_state( Debug__C__onPing );
}

void Capsule_Ponger::actionchain_____Debug__onPing__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__onPing__dbg__viewBreakPoints( msg );
    update_state( Debug__C__onPing );
}

void Capsule_Ponger::actionchain_____Debug__timeout( const UMLRTMessage * msg )
{
    exitaction_____WAITING_FOR_TIMER( msg );
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__timeout( msg );
}

void Capsule_Ponger::actionchain_____Debug__timeout__E( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__timeout__E( msg );
}

void Capsule_Ponger::actionchain_____Debug__timeout__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__timeout__S( msg );
    update_state( Debug__C__timeout );
}

void Capsule_Ponger::actionchain_____Debug__timeout__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__timeout__dbg__dbgDeferMsg( msg );
    update_state( Debug__C__timeout );
}

void Capsule_Ponger::actionchain_____Debug__timeout__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__timeout__dbg__dbgSetExecMode( msg );
    update_state( Debug__C__timeout );
}

void Capsule_Ponger::actionchain_____Debug__timeout__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__timeout__dbg__remBreakPoint( msg );
    update_state( Debug__C__timeout );
}

void Capsule_Ponger::actionchain_____Debug__timeout__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__timeout__dbg__setBreakPoint( msg );
    update_state( Debug__C__timeout );
}

void Capsule_Ponger::actionchain_____Debug__timeout__dbg__varChange( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__timeout__dbg__varChange( msg );
    update_state( Debug__C__timeout );
}

void Capsule_Ponger::actionchain_____Debug__timeout__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__timeout__dbg__viewBreakPoints( msg );
    update_state( Debug__C__timeout );
}

void Capsule_Ponger::actionchain_____Initial( const UMLRTMessage * msg )
{
    transitionaction_____Initial( msg );
    update_state( PLAYING );
    entryaction_____PLAYING( msg );
}

void Capsule_Ponger::actionchain_____endOfRound( const UMLRTMessage * msg )
{
    transitionaction_____endOfRound( msg );
    update_state( PLAYING );
    entryaction_____PLAYING( msg );
}

void Capsule_Ponger::actionchain_____keepPlaying( const UMLRTMessage * msg )
{
    transitionaction_____keepPlaying( msg );
    update_state( PLAYING );
    entryaction_____PLAYING( msg );
}

void Capsule_Ponger::actionchain_____onPing( const UMLRTMessage * msg )
{
    transitionaction_____onPing( msg );
    update_state( WAITING_FOR_TIMER );
    entryaction_____WAITING_FOR_TIMER( msg );
}

void Capsule_Ponger::actionchain_____timeout( const UMLRTMessage * msg )
{
    transitionaction_____timeout( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__Initial__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__Initial__Debug__init__trans__Initial( msg );
    return Debug__C__Initial__Debug__B__Ac__Initial;
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__Initial__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__E( msg );
    return PLAYING;
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__Initial__new_exitpoint_1( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__dbg__varChange( msg );
    return choice_____Debug__C__Initial__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__Initial__new_exitpoint_2( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__dbg__setBreakPoint( msg );
    return choice_____Debug__C__Initial__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__Initial__new_exitpoint_3( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__dbg__remBreakPoint( msg );
    return choice_____Debug__C__Initial__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__Initial__new_exitpoint_4( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__dbg__viewBreakPoints( msg );
    return choice_____Debug__C__Initial__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__Initial__new_exitpoint_5( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__dbg__dbgSetExecMode( msg );
    return choice_____Debug__C__Initial__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__Initial__new_exitpoint_6( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__dbg__dbgDeferMsg( msg );
    return choice_____Debug__C__Initial__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__endOfRound__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__endOfRound__Debug__init__trans__endOfRound( msg );
    return Debug__C__endOfRound__Debug__B__Ac__endOfRound;
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__endOfRound__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__endOfRound__E( msg );
    return PLAYING;
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__endOfRound__new_exitpoint_25( const UMLRTMessage * msg )
{
    actionchain_____Debug__endOfRound__dbg__varChange( msg );
    return choice_____Debug__C__endOfRound__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__endOfRound__new_exitpoint_26( const UMLRTMessage * msg )
{
    actionchain_____Debug__endOfRound__dbg__setBreakPoint( msg );
    return choice_____Debug__C__endOfRound__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__endOfRound__new_exitpoint_27( const UMLRTMessage * msg )
{
    actionchain_____Debug__endOfRound__dbg__remBreakPoint( msg );
    return choice_____Debug__C__endOfRound__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__endOfRound__new_exitpoint_28( const UMLRTMessage * msg )
{
    actionchain_____Debug__endOfRound__dbg__viewBreakPoints( msg );
    return choice_____Debug__C__endOfRound__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__endOfRound__new_exitpoint_29( const UMLRTMessage * msg )
{
    actionchain_____Debug__endOfRound__dbg__dbgSetExecMode( msg );
    return choice_____Debug__C__endOfRound__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__endOfRound__new_exitpoint_30( const UMLRTMessage * msg )
{
    actionchain_____Debug__endOfRound__dbg__dbgDeferMsg( msg );
    return choice_____Debug__C__endOfRound__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__keepPlaying__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__keepPlaying__Debug__init__trans__keepPlaying( msg );
    return Debug__C__keepPlaying__Debug__B__Ac__keepPlaying;
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__keepPlaying__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__keepPlaying__E( msg );
    return PLAYING;
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__keepPlaying__new_exitpoint_13( const UMLRTMessage * msg )
{
    actionchain_____Debug__keepPlaying__dbg__varChange( msg );
    return choice_____Debug__C__keepPlaying__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__keepPlaying__new_exitpoint_14( const UMLRTMessage * msg )
{
    actionchain_____Debug__keepPlaying__dbg__setBreakPoint( msg );
    return choice_____Debug__C__keepPlaying__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__keepPlaying__new_exitpoint_15( const UMLRTMessage * msg )
{
    actionchain_____Debug__keepPlaying__dbg__remBreakPoint( msg );
    return choice_____Debug__C__keepPlaying__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__keepPlaying__new_exitpoint_16( const UMLRTMessage * msg )
{
    actionchain_____Debug__keepPlaying__dbg__viewBreakPoints( msg );
    return choice_____Debug__C__keepPlaying__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__keepPlaying__new_exitpoint_17( const UMLRTMessage * msg )
{
    actionchain_____Debug__keepPlaying__dbg__dbgSetExecMode( msg );
    return choice_____Debug__C__keepPlaying__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__keepPlaying__new_exitpoint_18( const UMLRTMessage * msg )
{
    actionchain_____Debug__keepPlaying__dbg__dbgDeferMsg( msg );
    return choice_____Debug__C__keepPlaying__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__onPing__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__onPing__Debug__init__trans__onPing( msg );
    return Debug__C__onPing__Debug__B__Ex__PLAYING;
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__onPing__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__onPing__E( msg );
    return WAITING_FOR_TIMER;
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__onPing__new_exitpoint_19( const UMLRTMessage * msg )
{
    actionchain_____Debug__onPing__dbg__varChange( msg );
    return choice_____Debug__C__onPing__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__onPing__new_exitpoint_20( const UMLRTMessage * msg )
{
    actionchain_____Debug__onPing__dbg__setBreakPoint( msg );
    return choice_____Debug__C__onPing__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__onPing__new_exitpoint_21( const UMLRTMessage * msg )
{
    actionchain_____Debug__onPing__dbg__remBreakPoint( msg );
    return choice_____Debug__C__onPing__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__onPing__new_exitpoint_22( const UMLRTMessage * msg )
{
    actionchain_____Debug__onPing__dbg__viewBreakPoints( msg );
    return choice_____Debug__C__onPing__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__onPing__new_exitpoint_23( const UMLRTMessage * msg )
{
    actionchain_____Debug__onPing__dbg__dbgSetExecMode( msg );
    return choice_____Debug__C__onPing__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__onPing__new_exitpoint_24( const UMLRTMessage * msg )
{
    actionchain_____Debug__onPing__dbg__dbgDeferMsg( msg );
    return choice_____Debug__C__onPing__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__timeout__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__timeout__Debug__init__trans__timeout( msg );
    return Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER;
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__timeout__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__timeout__E( msg );
    return choice_____ThreePongsSent_( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__timeout__new_exitpoint_10( const UMLRTMessage * msg )
{
    actionchain_____Debug__timeout__dbg__viewBreakPoints( msg );
    return choice_____Debug__C__timeout__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__timeout__new_exitpoint_11( const UMLRTMessage * msg )
{
    actionchain_____Debug__timeout__dbg__dbgSetExecMode( msg );
    return choice_____Debug__C__timeout__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__timeout__new_exitpoint_12( const UMLRTMessage * msg )
{
    actionchain_____Debug__timeout__dbg__dbgDeferMsg( msg );
    return choice_____Debug__C__timeout__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__timeout__new_exitpoint_7( const UMLRTMessage * msg )
{
    actionchain_____Debug__timeout__dbg__varChange( msg );
    return choice_____Debug__C__timeout__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__timeout__new_exitpoint_8( const UMLRTMessage * msg )
{
    actionchain_____Debug__timeout__dbg__setBreakPoint( msg );
    return choice_____Debug__C__timeout__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::junction_____Debug__C__timeout__new_exitpoint_9( const UMLRTMessage * msg )
{
    actionchain_____Debug__timeout__dbg__remBreakPoint( msg );
    return choice_____Debug__C__timeout__deephistory( msg );
}

Capsule_Ponger::State Capsule_Ponger::choice_____Debug__C__Initial__deephistory( const UMLRTMessage * msg )
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
        actionchain_____Debug__C__Initial__new_transition_4_to_unvisited_boundary( msg );
        return Debug__C__Initial__boundary;
    }
    else if( check_history( Debug__C__Initial, Debug__C__Initial__boundary ) )
    {
        actionchain_____Debug__C__Initial__new_transition_5_to_visited_boundary( msg );
        return Debug__C__Initial__boundary;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::choice_____Debug__C__endOfRound__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__B__Ac__endOfRound ) )
    {
        actionchain_____Debug__C__endOfRound__new_transition_124( msg );
        return Debug__C__endOfRound__Debug__B__Ac__endOfRound;
    }
    else if( check_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__Ac__endOfRound ) )
    {
        actionchain_____Debug__C__endOfRound__new_transition_125( msg );
        return Debug__C__endOfRound__Debug__A__Ac__endOfRound;
    }
    else if( check_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__En__endOfRound ) )
    {
        actionchain_____Debug__C__endOfRound__new_transition_126( msg );
        return Debug__C__endOfRound__Debug__A__En__endOfRound;
    }
    else if( check_history( Debug__C__endOfRound, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__endOfRound__new_transition_127_to_unvisited_boundary( msg );
        return Debug__C__endOfRound__boundary;
    }
    else if( check_history( Debug__C__endOfRound, Debug__C__endOfRound__boundary ) )
    {
        actionchain_____Debug__C__endOfRound__new_transition_128_to_visited_boundary( msg );
        return Debug__C__endOfRound__boundary;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::choice_____Debug__C__keepPlaying__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__B__Ac__keepPlaying ) )
    {
        actionchain_____Debug__C__keepPlaying__new_transition_59( msg );
        return Debug__C__keepPlaying__Debug__B__Ac__keepPlaying;
    }
    else if( check_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__Ac__keepPlaying ) )
    {
        actionchain_____Debug__C__keepPlaying__new_transition_60( msg );
        return Debug__C__keepPlaying__Debug__A__Ac__keepPlaying;
    }
    else if( check_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__En__keepPlaying ) )
    {
        actionchain_____Debug__C__keepPlaying__new_transition_61( msg );
        return Debug__C__keepPlaying__Debug__A__En__keepPlaying;
    }
    else if( check_history( Debug__C__keepPlaying, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__keepPlaying__new_transition_62_to_unvisited_boundary( msg );
        return Debug__C__keepPlaying__boundary;
    }
    else if( check_history( Debug__C__keepPlaying, Debug__C__keepPlaying__boundary ) )
    {
        actionchain_____Debug__C__keepPlaying__new_transition_63_to_visited_boundary( msg );
        return Debug__C__keepPlaying__boundary;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::choice_____Debug__C__onPing__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__onPing, Debug__C__onPing__Debug__B__Ex__PLAYING ) )
    {
        actionchain_____Debug__C__onPing__new_transition_88( msg );
        return Debug__C__onPing__Debug__B__Ex__PLAYING;
    }
    else if( check_history( Debug__C__onPing, Debug__C__onPing__Debug__B__Ac__onPing ) )
    {
        actionchain_____Debug__C__onPing__new_transition_89( msg );
        return Debug__C__onPing__Debug__B__Ac__onPing;
    }
    else if( check_history( Debug__C__onPing, Debug__C__onPing__Debug__A__Ac__onPing ) )
    {
        actionchain_____Debug__C__onPing__new_transition_90( msg );
        return Debug__C__onPing__Debug__A__Ac__onPing;
    }
    else if( check_history( Debug__C__onPing, Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER ) )
    {
        actionchain_____Debug__C__onPing__new_transition_91( msg );
        return Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER;
    }
    else if( check_history( Debug__C__onPing, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__onPing__new_transition_92_to_unvisited_boundary( msg );
        return Debug__C__onPing__boundary;
    }
    else if( check_history( Debug__C__onPing, Debug__C__onPing__boundary ) )
    {
        actionchain_____Debug__C__onPing__new_transition_93_to_visited_boundary( msg );
        return Debug__C__onPing__boundary;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::choice_____Debug__C__timeout__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER ) )
    {
        actionchain_____Debug__C__timeout__new_transition_30( msg );
        return Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER;
    }
    else if( check_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ac__timeout ) )
    {
        actionchain_____Debug__C__timeout__new_transition_31( msg );
        return Debug__C__timeout__Debug__B__Ac__timeout;
    }
    else if( check_history( Debug__C__timeout, Debug__C__timeout__Debug__A__Ac__timeout ) )
    {
        actionchain_____Debug__C__timeout__new_transition_32( msg );
        return Debug__C__timeout__Debug__A__Ac__timeout;
    }
    else if( check_history( Debug__C__timeout, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__timeout__new_transition_33_to_unvisited_boundary( msg );
        return Debug__C__timeout__boundary;
    }
    else if( check_history( Debug__C__timeout, Debug__C__timeout__boundary ) )
    {
        actionchain_____Debug__C__timeout__new_transition_34_to_visited_boundary( msg );
        return Debug__C__timeout__boundary;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::choice_____Debug__Path__Initial( const UMLRTMessage * msg )
{
    if( guard_____Debug__Initial__S( msg ) )
    {
        actionchain_____Debug__Initial__S( msg );
        return junction_____Debug__C__Initial__en( msg );
    }
    else
    {
        actionchain_____Initial( msg );
        return PLAYING;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::choice_____Debug__Path__endOfRound( const UMLRTMessage * msg )
{
    if( guard_____Debug__endOfRound__S( msg ) )
    {
        actionchain_____Debug__endOfRound__S( msg );
        return junction_____Debug__C__endOfRound__en( msg );
    }
    else
    {
        actionchain_____endOfRound( msg );
        return PLAYING;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::choice_____Debug__Path__keepPlaying( const UMLRTMessage * msg )
{
    if( guard_____Debug__keepPlaying__S( msg ) )
    {
        actionchain_____Debug__keepPlaying__S( msg );
        return junction_____Debug__C__keepPlaying__en( msg );
    }
    else
    {
        actionchain_____keepPlaying( msg );
        return PLAYING;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::choice_____Debug__Path__onPing( const UMLRTMessage * msg )
{
    if( guard_____Debug__onPing__S( msg ) )
    {
        actionchain_____Debug__onPing__S( msg );
        return junction_____Debug__C__onPing__en( msg );
    }
    else
    {
        actionchain_____onPing( msg );
        return WAITING_FOR_TIMER;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::choice_____Debug__Path__timeout( const UMLRTMessage * msg )
{
    if( guard_____Debug__timeout__S( msg ) )
    {
        actionchain_____Debug__timeout__S( msg );
        return junction_____Debug__C__timeout__en( msg );
    }
    else
    {
        actionchain_____timeout( msg );
        return choice_____ThreePongsSent_( msg );
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::choice_____ThreePongsSent_( const UMLRTMessage * msg )
{
    if( guard_____Debug__keepPlaying( msg ) )
    {
        actionchain_____Debug__keepPlaying( msg );
        return choice_____Debug__Path__keepPlaying( msg );
    }
    else
    {
        actionchain_____Debug__endOfRound( msg );
        return choice_____Debug__Path__endOfRound( msg );
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::state_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Initial__Debug__En__PLAYING( msg );
            return Debug__C__Initial__Debug__A__En__Initial;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Initial__new_transition_7( msg );
            return junction_____Debug__C__Initial__new_exitpoint_1( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__Initial__new_transition_11( msg );
            return junction_____Debug__C__Initial__new_exitpoint_2( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__Initial__new_transition_15( msg );
            return junction_____Debug__C__Initial__new_exitpoint_3( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__Initial__new_transition_19( msg );
            return junction_____Debug__C__Initial__new_exitpoint_4( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__Initial__new_transition_23( msg );
            return junction_____Debug__C__Initial__new_exitpoint_5( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pongPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__Initial__new_transition_27( msg );
            return junction_____Debug__C__Initial__new_exitpoint_6( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::state_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg )
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
            actionchain_____Debug__C__Initial__new_transition_8( msg );
            return junction_____Debug__C__Initial__new_exitpoint_1( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__Initial__new_transition_12( msg );
            return junction_____Debug__C__Initial__new_exitpoint_2( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__Initial__new_transition_16( msg );
            return junction_____Debug__C__Initial__new_exitpoint_3( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__Initial__new_transition_20( msg );
            return junction_____Debug__C__Initial__new_exitpoint_4( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__Initial__new_transition_24( msg );
            return junction_____Debug__C__Initial__new_exitpoint_5( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pongPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__Initial__new_transition_28( msg );
            return junction_____Debug__C__Initial__new_exitpoint_6( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::state_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg )
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
            actionchain_____Debug__C__Initial__new_transition_6( msg );
            return junction_____Debug__C__Initial__new_exitpoint_1( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__Initial__new_transition_10( msg );
            return junction_____Debug__C__Initial__new_exitpoint_2( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__Initial__new_transition_14( msg );
            return junction_____Debug__C__Initial__new_exitpoint_3( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__Initial__new_transition_18( msg );
            return junction_____Debug__C__Initial__new_exitpoint_4( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__Initial__new_transition_22( msg );
            return junction_____Debug__C__Initial__new_exitpoint_5( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pongPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__Initial__new_transition_26( msg );
            return junction_____Debug__C__Initial__new_exitpoint_6( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::state_____Debug__C__Initial__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Initial__new_transition_9( msg );
            return junction_____Debug__C__Initial__new_exitpoint_1( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__Initial__new_transition_13( msg );
            return junction_____Debug__C__Initial__new_exitpoint_2( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__Initial__new_transition_17( msg );
            return junction_____Debug__C__Initial__new_exitpoint_3( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__Initial__new_transition_21( msg );
            return junction_____Debug__C__Initial__new_exitpoint_4( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__Initial__new_transition_25( msg );
            return junction_____Debug__C__Initial__new_exitpoint_5( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pongPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__Initial__new_transition_29( msg );
            return junction_____Debug__C__Initial__new_exitpoint_6( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::state_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__endOfRound__Debug__En__PLAYING( msg );
            return Debug__C__endOfRound__Debug__A__En__endOfRound;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__endOfRound__new_transition_130( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_25( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__endOfRound__new_transition_134( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_26( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__endOfRound__new_transition_138( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_27( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__endOfRound__new_transition_142( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_28( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__endOfRound__new_transition_146( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_29( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pongPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__endOfRound__new_transition_150( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_30( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::state_____Debug__C__endOfRound__Debug__A__En__endOfRound( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__endOfRound__Debug__end__trans__endOfRound( msg );
            return junction_____Debug__C__endOfRound__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__endOfRound__new_transition_131( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_25( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__endOfRound__new_transition_135( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_26( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__endOfRound__new_transition_139( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_27( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__endOfRound__new_transition_143( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_28( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__endOfRound__new_transition_147( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_29( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pongPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__endOfRound__new_transition_151( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_30( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::state_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__endOfRound__Debug__Ac__endOfRound( msg );
            return Debug__C__endOfRound__Debug__A__Ac__endOfRound;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__endOfRound__new_transition_129( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_25( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__endOfRound__new_transition_133( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_26( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__endOfRound__new_transition_137( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_27( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__endOfRound__new_transition_141( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_28( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__endOfRound__new_transition_145( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_29( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pongPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__endOfRound__new_transition_149( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_30( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::state_____Debug__C__endOfRound__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__endOfRound__new_transition_132( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_25( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__endOfRound__new_transition_136( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_26( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__endOfRound__new_transition_140( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_27( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__endOfRound__new_transition_144( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_28( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__endOfRound__new_transition_148( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_29( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pongPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__endOfRound__new_transition_152( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_30( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::state_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__keepPlaying__Debug__En__PLAYING( msg );
            return Debug__C__keepPlaying__Debug__A__En__keepPlaying;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__keepPlaying__new_transition_65( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_13( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__keepPlaying__new_transition_69( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_14( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__keepPlaying__new_transition_73( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_15( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__keepPlaying__new_transition_77( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_16( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__keepPlaying__new_transition_81( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_17( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pongPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__keepPlaying__new_transition_85( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_18( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::state_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__keepPlaying__Debug__end__trans__keepPlaying( msg );
            return junction_____Debug__C__keepPlaying__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__keepPlaying__new_transition_66( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_13( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__keepPlaying__new_transition_70( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_14( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__keepPlaying__new_transition_74( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_15( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__keepPlaying__new_transition_78( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_16( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__keepPlaying__new_transition_82( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_17( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pongPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__keepPlaying__new_transition_86( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_18( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::state_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__keepPlaying__Debug__Ac__keepPlaying( msg );
            return Debug__C__keepPlaying__Debug__A__Ac__keepPlaying;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__keepPlaying__new_transition_64( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_13( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__keepPlaying__new_transition_68( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_14( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__keepPlaying__new_transition_72( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_15( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__keepPlaying__new_transition_76( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_16( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__keepPlaying__new_transition_80( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_17( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pongPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__keepPlaying__new_transition_84( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_18( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::state_____Debug__C__keepPlaying__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__keepPlaying__new_transition_67( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_13( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__keepPlaying__new_transition_71( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_14( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__keepPlaying__new_transition_75( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_15( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__keepPlaying__new_transition_79( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_16( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__keepPlaying__new_transition_83( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_17( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pongPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__keepPlaying__new_transition_87( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_18( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::state_____Debug__C__onPing__Debug__A__Ac__onPing( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__onPing__Debug__En__WAITING_FOR_TIMER( msg );
            return Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__onPing__new_transition_96( msg );
            return junction_____Debug__C__onPing__new_exitpoint_19( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__onPing__new_transition_101( msg );
            return junction_____Debug__C__onPing__new_exitpoint_20( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__onPing__new_transition_106( msg );
            return junction_____Debug__C__onPing__new_exitpoint_21( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__onPing__new_transition_111( msg );
            return junction_____Debug__C__onPing__new_exitpoint_22( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__onPing__new_transition_116( msg );
            return junction_____Debug__C__onPing__new_exitpoint_23( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pongPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__onPing__new_transition_121( msg );
            return junction_____Debug__C__onPing__new_exitpoint_24( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::state_____Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__onPing__Debug__end__trans__onPing( msg );
            return junction_____Debug__C__onPing__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__onPing__new_transition_97( msg );
            return junction_____Debug__C__onPing__new_exitpoint_19( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__onPing__new_transition_102( msg );
            return junction_____Debug__C__onPing__new_exitpoint_20( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__onPing__new_transition_107( msg );
            return junction_____Debug__C__onPing__new_exitpoint_21( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__onPing__new_transition_112( msg );
            return junction_____Debug__C__onPing__new_exitpoint_22( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__onPing__new_transition_117( msg );
            return junction_____Debug__C__onPing__new_exitpoint_23( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pongPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__onPing__new_transition_122( msg );
            return junction_____Debug__C__onPing__new_exitpoint_24( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::state_____Debug__C__onPing__Debug__B__Ac__onPing( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__onPing__Debug__AC__onPing( msg );
            return Debug__C__onPing__Debug__A__Ac__onPing;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__onPing__new_transition_95( msg );
            return junction_____Debug__C__onPing__new_exitpoint_19( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__onPing__new_transition_100( msg );
            return junction_____Debug__C__onPing__new_exitpoint_20( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__onPing__new_transition_105( msg );
            return junction_____Debug__C__onPing__new_exitpoint_21( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__onPing__new_transition_110( msg );
            return junction_____Debug__C__onPing__new_exitpoint_22( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__onPing__new_transition_115( msg );
            return junction_____Debug__C__onPing__new_exitpoint_23( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pongPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__onPing__new_transition_120( msg );
            return junction_____Debug__C__onPing__new_exitpoint_24( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::state_____Debug__C__onPing__Debug__B__Ex__PLAYING( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__onPing__Debug__Ex__PLAYING( msg );
            return Debug__C__onPing__Debug__B__Ac__onPing;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__onPing__new_transition_94( msg );
            return junction_____Debug__C__onPing__new_exitpoint_19( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__onPing__new_transition_99( msg );
            return junction_____Debug__C__onPing__new_exitpoint_20( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__onPing__new_transition_104( msg );
            return junction_____Debug__C__onPing__new_exitpoint_21( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__onPing__new_transition_109( msg );
            return junction_____Debug__C__onPing__new_exitpoint_22( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__onPing__new_transition_114( msg );
            return junction_____Debug__C__onPing__new_exitpoint_23( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pongPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__onPing__new_transition_119( msg );
            return junction_____Debug__C__onPing__new_exitpoint_24( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::state_____Debug__C__onPing__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__onPing__new_transition_98( msg );
            return junction_____Debug__C__onPing__new_exitpoint_19( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__onPing__new_transition_103( msg );
            return junction_____Debug__C__onPing__new_exitpoint_20( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__onPing__new_transition_108( msg );
            return junction_____Debug__C__onPing__new_exitpoint_21( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__onPing__new_transition_113( msg );
            return junction_____Debug__C__onPing__new_exitpoint_22( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__onPing__new_transition_118( msg );
            return junction_____Debug__C__onPing__new_exitpoint_23( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pongPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__onPing__new_transition_123( msg );
            return junction_____Debug__C__onPing__new_exitpoint_24( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::state_____Debug__C__timeout__Debug__A__Ac__timeout( const UMLRTMessage * msg )
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
            actionchain_____Debug__C__timeout__new_transition_37( msg );
            return junction_____Debug__C__timeout__new_exitpoint_7( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__timeout__new_transition_41( msg );
            return junction_____Debug__C__timeout__new_exitpoint_8( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__timeout__new_transition_45( msg );
            return junction_____Debug__C__timeout__new_exitpoint_9( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__timeout__new_transition_49( msg );
            return junction_____Debug__C__timeout__new_exitpoint_10( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__timeout__new_transition_53( msg );
            return junction_____Debug__C__timeout__new_exitpoint_11( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pongPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__timeout__new_transition_57( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::state_____Debug__C__timeout__Debug__B__Ac__timeout( const UMLRTMessage * msg )
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
            actionchain_____Debug__C__timeout__new_transition_36( msg );
            return junction_____Debug__C__timeout__new_exitpoint_7( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__timeout__new_transition_40( msg );
            return junction_____Debug__C__timeout__new_exitpoint_8( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__timeout__new_transition_44( msg );
            return junction_____Debug__C__timeout__new_exitpoint_9( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__timeout__new_transition_48( msg );
            return junction_____Debug__C__timeout__new_exitpoint_10( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__timeout__new_transition_52( msg );
            return junction_____Debug__C__timeout__new_exitpoint_11( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pongPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__timeout__new_transition_56( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::state_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__timeout__Debug__Ex__WAITING_FOR_TIMER( msg );
            return Debug__C__timeout__Debug__B__Ac__timeout;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__timeout__new_transition_35( msg );
            return junction_____Debug__C__timeout__new_exitpoint_7( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__timeout__new_transition_39( msg );
            return junction_____Debug__C__timeout__new_exitpoint_8( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__timeout__new_transition_43( msg );
            return junction_____Debug__C__timeout__new_exitpoint_9( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__timeout__new_transition_47( msg );
            return junction_____Debug__C__timeout__new_exitpoint_10( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__timeout__new_transition_51( msg );
            return junction_____Debug__C__timeout__new_exitpoint_11( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pongPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__timeout__new_transition_55( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::state_____Debug__C__timeout__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__timeout__new_transition_38( msg );
            return junction_____Debug__C__timeout__new_exitpoint_7( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__timeout__new_transition_42( msg );
            return junction_____Debug__C__timeout__new_exitpoint_8( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__timeout__new_transition_46( msg );
            return junction_____Debug__C__timeout__new_exitpoint_9( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__timeout__new_transition_50( msg );
            return junction_____Debug__C__timeout__new_exitpoint_10( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__timeout__new_transition_54( msg );
            return junction_____Debug__C__timeout__new_exitpoint_11( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pongPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__timeout__new_transition_58( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Ponger::State Capsule_Ponger::state_____Debug__InitState( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case UMLRTSignal::rtBound:
            actionchain_____Debug__Initial( msg );
            return choice_____Debug__Path__Initial( msg );
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

Capsule_Ponger::State Capsule_Ponger::state_____PLAYING( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_pongPort:
        switch( msg->getSignalId() )
        {
        case PingPongProtocol::signal_ping:
            actionchain_____Debug__onPing( msg );
            return choice_____Debug__Path__onPing( msg );
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

Capsule_Ponger::State Capsule_Ponger::state_____WAITING_FOR_TIMER( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_pongerTimer:
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


static const UMLRTCommsPortRole portroles_border[] = 
{
    {
        Capsule_Ponger::port_endPort,
        "endProtocol",
        "endPort",
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
        Capsule_Ponger::port_pongPort,
        "PingPongProtocol",
        "pongPort",
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

static const UMLRTCommsPortRole portroles_internal[] = 
{
    {
        Capsule_Ponger::port_extComm,
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
        Capsule_Ponger::port_pongerTimer,
        "Timing",
        "pongerTimer",
        "",
        0,
        false,
        false,
        false,
        false,
        true,
        false,
        false
    },
    {
        Capsule_Ponger::port_log,
        "Log",
        "log",
        "",
        0,
        false,
        false,
        false,
        false,
        true,
        false,
        false
    }
};

static void instantiate_Ponger( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    const UMLRTCommsPort * * internalPorts = UMLRTFrameService::createInternalPorts( slot, &Ponger );
    slot->capsule = new Capsule_Ponger( &Ponger, slot, borderPorts, internalPorts, false );
}

const UMLRTCapsuleClass Ponger = 
{
    "Ponger",
    NULL,
    instantiate_Ponger,
    0,
    NULL,
    2,
    portroles_border,
    3,
    portroles_internal
};

