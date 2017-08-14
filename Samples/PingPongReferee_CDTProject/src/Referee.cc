
#include "Referee.hh"

#include "ExtInterface.hh"
#include "endProtocol.hh"
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

Capsule_Referee::Capsule_Referee( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, endPort( borderPorts[borderport_endPort] )
, extComm( internalPorts[internalport_extComm] )
, refereeTimer( internalPorts[internalport_refereeTimer] )
, startPort( borderPorts[borderport_startPort] )
, round( 0 )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[Debug__C__Initial] = "Debug__C__Initial";
    stateNames[Debug__C__endRound] = "Debug__C__endRound";
    stateNames[Debug__C__startRound] = "Debug__C__startRound";
    stateNames[Debug__C__Initial__Debug__A__Ac__Initial] = "Debug__C__Initial__Debug__A__Ac__Initial";
    stateNames[Debug__C__Initial__Debug__A__En__Initial] = "Debug__C__Initial__Debug__A__En__Initial";
    stateNames[Debug__C__Initial__Debug__B__Ac__Initial] = "Debug__C__Initial__Debug__B__Ac__Initial";
    stateNames[Debug__C__Initial__boundary] = "Debug__C__Initial__boundary";
    stateNames[Debug__C__endRound__Debug__A__Ac__endRound] = "Debug__C__endRound__Debug__A__Ac__endRound";
    stateNames[Debug__C__endRound__Debug__A__En__STARTING_ROUND] = "Debug__C__endRound__Debug__A__En__STARTING_ROUND";
    stateNames[Debug__C__endRound__Debug__B__Ac__endRound] = "Debug__C__endRound__Debug__B__Ac__endRound";
    stateNames[Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND] = "Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND";
    stateNames[Debug__C__endRound__boundary] = "Debug__C__endRound__boundary";
    stateNames[Debug__C__startRound__Debug__A__Ac__startRound] = "Debug__C__startRound__Debug__A__Ac__startRound";
    stateNames[Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND] = "Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND";
    stateNames[Debug__C__startRound__Debug__B__Ac__startRound] = "Debug__C__startRound__Debug__B__Ac__startRound";
    stateNames[Debug__C__startRound__Debug__B__Ex__STARTING_ROUND] = "Debug__C__startRound__Debug__B__Ex__STARTING_ROUND";
    stateNames[Debug__C__startRound__boundary] = "Debug__C__startRound__boundary";
    stateNames[Debug__InitState] = "Debug__InitState";
    stateNames[STARTING_ROUND] = "STARTING_ROUND";
    stateNames[WAITING_FOR_END_OF_ROUND] = "WAITING_FOR_END_OF_ROUND";
    stateNames[SPECIAL_INTERNAL_STATE_TOP] = "<top>";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
    int i = 0;
    while( i < 3 )
        history[i++] = SPECIAL_INTERNAL_STATE_UNVISITED;
}










void Capsule_Referee::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_endPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_endPort, index, true );
            break;
        case borderport_startPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_startPort, index, true );
            break;
        }
}

void Capsule_Referee::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_endPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_endPort, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_endPort], index );
            break;
        case borderport_startPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_startPort, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_startPort], index );
            break;
        }
}






void Capsule_Referee::Debug__recallAllMsg()
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee operation Debug__recallAllMsg */
    endPort.recallAll();
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_Referee::Debug__variablesView()
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee operation Debug__variablesView */
    std::string tempS="";
    tempS.append("round,");
    tempS.append("Integer,");
    if(round!=0){
    char tempR[10];
    sprintf(tempR,"%d",round);
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

bool Capsule_Referee::Debug__variablesChange( char * varName, char * varValue )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee operation Debug__variablesChange */
    std::string tempVarName="";
    tempVarName.append(varName);
    if ("round"==tempVarName){
    round=atoi(varValue);
    return true;
    }else 
    return false;
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_Referee::Debug__sendEvent( debugEvents::EVENTSOURCEKIND eventSourceKind, debugEvents::EVENTTYPE eventType, const char * instanceName, int capsuleIndex, const char * signalName, const char * capsuleName, char * sourceName, char * reserve1, char * reserve2, const char * reserve3, const char * reserve4 )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee operation Debug__sendEvent */
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

void Capsule_Referee::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case STARTING_ROUND:
        currentState = state_____STARTING_ROUND( &message );
        break;
    case WAITING_FOR_END_OF_ROUND:
        currentState = state_____WAITING_FOR_END_OF_ROUND( &message );
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
    case Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND:
        currentState = state_____Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND( &message );
        break;
    case Debug__C__endRound__Debug__B__Ac__endRound:
        currentState = state_____Debug__C__endRound__Debug__B__Ac__endRound( &message );
        break;
    case Debug__C__endRound__Debug__A__Ac__endRound:
        currentState = state_____Debug__C__endRound__Debug__A__Ac__endRound( &message );
        break;
    case Debug__C__endRound__Debug__A__En__STARTING_ROUND:
        currentState = state_____Debug__C__endRound__Debug__A__En__STARTING_ROUND( &message );
        break;
    case Debug__C__endRound__boundary:
        currentState = state_____Debug__C__endRound__boundary( &message );
        break;
    case Debug__C__startRound__Debug__B__Ex__STARTING_ROUND:
        currentState = state_____Debug__C__startRound__Debug__B__Ex__STARTING_ROUND( &message );
        break;
    case Debug__C__startRound__Debug__B__Ac__startRound:
        currentState = state_____Debug__C__startRound__Debug__B__Ac__startRound( &message );
        break;
    case Debug__C__startRound__Debug__A__Ac__startRound:
        currentState = state_____Debug__C__startRound__Debug__A__Ac__startRound( &message );
        break;
    case Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND:
        currentState = state_____Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND( &message );
        break;
    case Debug__C__startRound__boundary:
        currentState = state_____Debug__C__startRound__boundary( &message );
        break;
    default:
        break;
    }
}

void Capsule_Referee::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Debug__InitDebug( &message );
    currentState = Debug__InitState;
}

const char * Capsule_Referee::getCurrentStateString() const
{
    return stateNames[currentState];
}





void Capsule_Referee::save_history( Capsule_Referee::State compositeState, Capsule_Referee::State subState )
{
    history[compositeState] = subState;
}

bool Capsule_Referee::check_history( Capsule_Referee::State compositeState, Capsule_Referee::State subState )
{
    return history[compositeState] == subState;
}

void Capsule_Referee::update_state( Capsule_Referee::State newState )
{
    currentState = newState;
}

void Capsule_Referee::entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__Initial::Debug__A__Ac__Initial entry  */
    if (not(Debug__SRO.checkDebug("Initial","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("STARTING ROUND","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__Initial::Region1::Debug__A__Ac__Initial",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::entryaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__Initial::Debug__A__En__Initial entry  */
    if (not(Debug__SRO.checkDebug("STARTING ROUND","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__Initial::Region1::Debug__A__En__Initial",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__Initial::Debug__B__Ac__Initial entry  */
    if (not(Debug__SRO.checkDebug("Initial","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__Initial::Region1::Debug__B__Ac__Initial",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::entryaction_____Debug__C__endRound__Debug__A__Ac__endRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__endRound::Debug__A__Ac__endRound entry  */
    if (not(Debug__SRO.checkDebug("endRound","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("STARTING ROUND","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__endRound::Region1::Debug__A__Ac__endRound",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::entryaction_____Debug__C__endRound__Debug__A__En__STARTING_ROUND( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__endRound::Debug__A__En__STARTING ROUND entry  */
    if (not(Debug__SRO.checkDebug("STARTING ROUND","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__endRound::Region1::Debug__A__En__STARTING ROUND",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::entryaction_____Debug__C__endRound__Debug__B__Ac__endRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__endRound::Debug__B__Ac__endRound entry  */
    if (not(Debug__SRO.checkDebug("WAITING FOR END OF ROUND","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("endRound","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__endRound::Region1::Debug__B__Ac__endRound",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::entryaction_____Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__endRound::Debug__B__Ex__WAITING FOR END OF ROUND entry  */
    if (not(Debug__SRO.checkDebug("WAITING FOR END OF ROUND","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__endRound::Region1::Debug__B__Ex__WAITING FOR END OF ROUND",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::entryaction_____Debug__C__startRound__Debug__A__Ac__startRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__startRound::Debug__A__Ac__startRound entry  */
    if (not(Debug__SRO.checkDebug("startRound","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("WAITING FOR END OF ROUND","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__startRound::Region1::Debug__A__Ac__startRound",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::entryaction_____Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__startRound::Debug__A__En__WAITING FOR END OF ROUND entry  */
    if (not(Debug__SRO.checkDebug("WAITING FOR END OF ROUND","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__startRound::Region1::Debug__A__En__WAITING FOR END OF ROUND",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::entryaction_____Debug__C__startRound__Debug__B__Ac__startRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__startRound::Debug__B__Ac__startRound entry  */
    if (not(Debug__SRO.checkDebug("STARTING ROUND","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("startRound","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__startRound::Region1::Debug__B__Ac__startRound",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::entryaction_____Debug__C__startRound__Debug__B__Ex__STARTING_ROUND( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__startRound::Debug__B__Ex__STARTING ROUND entry  */
    if (not(Debug__SRO.checkDebug("STARTING ROUND","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__startRound::Region1::Debug__B__Ex__STARTING ROUND",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::entryaction_____STARTING_ROUND( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::STARTING ROUND entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::STARTING ROUND",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::entryaction_____WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::WAITING FOR END OF ROUND entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::WAITING FOR END OF ROUND",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__Initial::Debug__A__Ac__Initial exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__Initial::Region1::Debug__A__Ac__Initial",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::exitaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__Initial::Debug__A__En__Initial exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__Initial::Region1::Debug__A__En__Initial",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__Initial::Debug__B__Ac__Initial exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__Initial::Region1::Debug__B__Ac__Initial",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::exitaction_____Debug__C__endRound__Debug__A__Ac__endRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__endRound::Debug__A__Ac__endRound exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__endRound::Region1::Debug__A__Ac__endRound",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::exitaction_____Debug__C__endRound__Debug__A__En__STARTING_ROUND( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__endRound::Debug__A__En__STARTING ROUND exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__endRound::Region1::Debug__A__En__STARTING ROUND",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::exitaction_____Debug__C__endRound__Debug__B__Ac__endRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__endRound::Debug__B__Ac__endRound exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__endRound::Region1::Debug__B__Ac__endRound",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::exitaction_____Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__endRound::Debug__B__Ex__WAITING FOR END OF ROUND exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__endRound::Region1::Debug__B__Ex__WAITING FOR END OF ROUND",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::exitaction_____Debug__C__startRound__Debug__A__Ac__startRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__startRound::Debug__A__Ac__startRound exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__startRound::Region1::Debug__A__Ac__startRound",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::exitaction_____Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__startRound::Debug__A__En__WAITING FOR END OF ROUND exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__startRound::Region1::Debug__A__En__WAITING FOR END OF ROUND",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::exitaction_____Debug__C__startRound__Debug__B__Ac__startRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__startRound::Debug__B__Ac__startRound exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__startRound::Region1::Debug__B__Ac__startRound",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::exitaction_____Debug__C__startRound__Debug__B__Ex__STARTING_ROUND( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__startRound::Debug__B__Ex__STARTING ROUND exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__startRound::Region1::Debug__B__Ex__STARTING ROUND",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::exitaction_____STARTING_ROUND( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::STARTING ROUND exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::STARTING ROUND",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::exitaction_____WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::WAITING FOR END OF ROUND exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::WAITING FOR END OF ROUND",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__Initial transition Debug__C__Initial::Debug__B__Ac__Initial,Debug__C__Initial::Debug__A__Ac__Initial,dbgExec:extComm */
    refereeTimer.informIn(UMLRTTimespec(4,0));
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__Initial::Region1::Debug__Ac__Initial",(char *)"Debug__B__Ac__Initial",(char *)"Debug__A__Ac__Initial",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__C__Initial__Debug__En__STARTING_ROUND( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__Initial transition Debug__C__Initial::Debug__A__Ac__Initial,Debug__C__Initial::Debug__A__En__Initial,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__Initial::Region1::Debug__En__STARTING ROUND",(char *)"Debug__A__Ac__Initial",(char *)"Debug__A__En__Initial",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__Initial transition Debug__C__Initial::Debug__A__En__Initial,Debug__C__Initial::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__Initial::Region1::Debug__end__trans__Initial",(char *)"Debug__A__En__Initial",(char *)"ex",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__Initial transition Debug__C__Initial::en,Debug__C__Initial::Debug__B__Ac__Initial */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__Initial::Region1::Debug__init__trans__Initial",(char *)"en",(char *)"Debug__B__Ac__Initial",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__C__endRound__Debug__AC__endRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__endRound transition Debug__C__endRound::Debug__B__Ac__endRound,Debug__C__endRound::Debug__A__Ac__endRound,dbgExec:extComm */
    log.show("round %d finished.\n", this->round);
    this->round++;
    refereeTimer.informIn(UMLRTTimespec(4,0));
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__endRound::Region1::Debug__AC__endRound",(char *)"Debug__B__Ac__endRound",(char *)"Debug__A__Ac__endRound",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__C__endRound__Debug__En__STARTING_ROUND( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__endRound transition Debug__C__endRound::Debug__A__Ac__endRound,Debug__C__endRound::Debug__A__En__STARTING ROUND,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__endRound::Region1::Debug__En__STARTING ROUND",(char *)"Debug__A__Ac__endRound",(char *)"Debug__A__En__STARTING ROUND",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__C__endRound__Debug__Ex__WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__endRound transition Debug__C__endRound::Debug__B__Ex__WAITING FOR END OF ROUND,Debug__C__endRound::Debug__B__Ac__endRound,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__endRound::Region1::Debug__Ex__WAITING FOR END OF ROUND",(char *)"Debug__B__Ex__WAITING FOR END OF ROUND",(char *)"Debug__B__Ac__endRound",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__C__endRound__Debug__end__trans__endRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__endRound transition Debug__C__endRound::Debug__A__En__STARTING ROUND,Debug__C__endRound::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__endRound::Region1::Debug__end__trans__endRound",(char *)"Debug__A__En__STARTING ROUND",(char *)"ex",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__C__endRound__Debug__init__trans__endRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__endRound transition Debug__C__endRound::en,Debug__C__endRound::Debug__B__Ex__WAITING FOR END OF ROUND */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__endRound::Region1::Debug__init__trans__endRound",(char *)"en",(char *)"Debug__B__Ex__WAITING FOR END OF ROUND",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__C__startRound__Debug__AC__startRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__startRound transition Debug__C__startRound::Debug__B__Ac__startRound,Debug__C__startRound::Debug__A__Ac__startRound,dbgExec:extComm */
    log.show("starting round %d.\n", this->round);
    startPort.start().send();
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__startRound::Region1::Debug__AC__startRound",(char *)"Debug__B__Ac__startRound",(char *)"Debug__A__Ac__startRound",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__C__startRound__Debug__En__WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__startRound transition Debug__C__startRound::Debug__A__Ac__startRound,Debug__C__startRound::Debug__A__En__WAITING FOR END OF ROUND,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__startRound::Region1::Debug__En__WAITING FOR END OF ROUND",(char *)"Debug__A__Ac__startRound",(char *)"Debug__A__En__WAITING FOR END OF ROUND",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__C__startRound__Debug__Ex__STARTING_ROUND( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__startRound transition Debug__C__startRound::Debug__B__Ex__STARTING ROUND,Debug__C__startRound::Debug__B__Ac__startRound,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__startRound::Region1::Debug__Ex__STARTING ROUND",(char *)"Debug__B__Ex__STARTING ROUND",(char *)"Debug__B__Ac__startRound",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__C__startRound__Debug__end__trans__startRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__startRound transition Debug__C__startRound::Debug__A__En__WAITING FOR END OF ROUND,Debug__C__startRound::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__startRound::Region1::Debug__end__trans__startRound",(char *)"Debug__A__En__WAITING FOR END OF ROUND",(char *)"ex",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__C__startRound__Debug__init__trans__startRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee::Debug__C__startRound transition Debug__C__startRound::en,Debug__C__startRound::Debug__B__Ex__STARTING ROUND */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__C__startRound::Region1::Debug__init__trans__startRound",(char *)"en",(char *)"Debug__B__Ex__STARTING ROUND",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__InitDebug( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Pseudo1,Debug__InitState */
    std::cout<<this->getName()<<" : is Starting\n";
    this->Debug__SRO.setExecMode(Stepping);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__InitState,Debug__Path__Initial,rtBound:extComm */
    if (this->Debug__SRO.getExecMode()==Stepping){
    Debug__SRO.addTransitionsFromState("STARTING ROUND","startRound","WAITING FOR END OF ROUND","timeout","Timing");
    Debug__SRO.addTransitionsFromState("WAITING FOR END OF ROUND","endRound","STARTING ROUND","end","endProtocol");
    Debug__SRO.addTransitionsFromState("","Initial","STARTING ROUND","","");
    std::cout<<this->getName()<<": Connection with debugger is in progress\n";
    char  tempS[256];
    sprintf(tempS,"%s%d",this->getName(),(int)this->getIndex());
    extComm.registerToControl(tempS).send();
    Debug__sendEvent(debugEvents::DEBUG,debugEvents::REGISTER,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"",(char *)"",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__Initial__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__C__Initial::ex,STARTING ROUND */
    this->Debug__recallAllMsg();
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__Initial__E",(char *)"ex",(char *)"STARTING ROUND",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__Initial__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__Path__Initial,Debug__C__Initial::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__Initial__S",(char *)"Debug__Path__Initial",(char *)"en",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__Initial__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__C__Initial::new_exitpoint_6,Debug__C__Initial */
    msg->defer();
    std::cout<<"A message defered"<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__Initial__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__C__Initial::new_exitpoint_5,Debug__C__Initial */
    this->Debug__SRO.setExecMode((ExecMode)( *(int *)msg->getParam( 0 ) ));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__Initial__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__C__Initial::new_exitpoint_3,Debug__C__Initial */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.remBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__Initial__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__C__Initial::new_exitpoint_2,Debug__C__Initial */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.addBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__Initial__dbg__varChange( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__C__Initial::new_exitpoint_1,Debug__C__Initial */
    char varName1[256];
    char varValue1[1024];
    sprintf(varName1,"%s",(*(const char * *)msg->getParam( 0 )));
    sprintf(varValue1,"%s",(*(const char * *)msg->getParam( 1 )));
    this->Debug__variablesChange(varName1,varValue1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__Initial__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__C__Initial::new_exitpoint_4,Debug__C__Initial */
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__endRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition WAITING FOR END OF ROUND,Debug__Path__endRound,end:endPort */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__endRound",(char *)"WAITING FOR END OF ROUND",(char *)"Debug__Path__endRound",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__endRound__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__C__endRound::ex,STARTING ROUND */
    this->Debug__recallAllMsg();
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__endRound__E",(char *)"ex",(char *)"STARTING ROUND",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__endRound__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__Path__endRound,Debug__C__endRound::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__endRound__S",(char *)"Debug__Path__endRound",(char *)"en",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__endRound__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__C__endRound::new_exitpoint_12,Debug__C__endRound */
    msg->defer();
    std::cout<<"A message defered"<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__endRound__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__C__endRound::new_exitpoint_11,Debug__C__endRound */
    this->Debug__SRO.setExecMode((ExecMode)( *(int *)msg->getParam( 0 ) ));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__endRound__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__C__endRound::new_exitpoint_9,Debug__C__endRound */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.remBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__endRound__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__C__endRound::new_exitpoint_8,Debug__C__endRound */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.addBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__endRound__dbg__varChange( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__C__endRound::new_exitpoint_7,Debug__C__endRound */
    char varName1[256];
    char varValue1[1024];
    sprintf(varName1,"%s",(*(const char * *)msg->getParam( 0 )));
    sprintf(varValue1,"%s",(*(const char * *)msg->getParam( 1 )));
    this->Debug__variablesChange(varName1,varValue1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__endRound__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__C__endRound::new_exitpoint_10,Debug__C__endRound */
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__startRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition STARTING ROUND,Debug__Path__startRound,timeout:refereeTimer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__startRound",(char *)"STARTING ROUND",(char *)"Debug__Path__startRound",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__startRound__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__C__startRound::ex,WAITING FOR END OF ROUND */
    this->Debug__recallAllMsg();
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__startRound__E",(char *)"ex",(char *)"WAITING FOR END OF ROUND",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__startRound__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__Path__startRound,Debug__C__startRound::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Debug__startRound__S",(char *)"Debug__Path__startRound",(char *)"en",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__startRound__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__C__startRound::new_exitpoint_18,Debug__C__startRound */
    msg->defer();
    std::cout<<"A message defered"<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__startRound__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__C__startRound::new_exitpoint_17,Debug__C__startRound */
    this->Debug__SRO.setExecMode((ExecMode)( *(int *)msg->getParam( 0 ) ));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__startRound__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__C__startRound::new_exitpoint_15,Debug__C__startRound */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.remBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__startRound__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__C__startRound::new_exitpoint_14,Debug__C__startRound */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.addBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__startRound__dbg__varChange( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__C__startRound::new_exitpoint_13,Debug__C__startRound */
    char varName1[256];
    char varValue1[1024];
    sprintf(varName1,"%s",(*(const char * *)msg->getParam( 0 )));
    sprintf(varValue1,"%s",(*(const char * *)msg->getParam( 1 )));
    this->Debug__variablesChange(varName1,varValue1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Debug__startRound__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__C__startRound::new_exitpoint_16,Debug__C__startRound */
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__Path__Initial,STARTING ROUND */
    refereeTimer.informIn(UMLRTTimespec(4,0));
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::Initial",(char *)"Debug__Path__Initial",(char *)"STARTING ROUND",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____endRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__Path__endRound,STARTING ROUND */
    log.show("round %d finished.\n", this->round);
    this->round++;
    refereeTimer.informIn(UMLRTTimespec(4,0));
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::endRound",(char *)"Debug__Path__endRound",(char *)"STARTING ROUND",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::transitionaction_____startRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee transition Debug__Path__startRound,WAITING FOR END OF ROUND */
    log.show("starting round %d.\n", this->round);
    startPort.start().send();
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Referee::RefereeStateMachine::Region::startRound",(char *)"Debug__Path__startRound",(char *)"WAITING FOR END OF ROUND",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Referee::guard_____Debug__Initial__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee guard Debug__Path__Initial,Debug__C__Initial::en */
    return Debug__SRO.checkDebug("Pseudo1","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Referee::guard_____Debug__endRound__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee guard Debug__Path__endRound,Debug__C__endRound::en */
    return Debug__SRO.checkDebug("WAITING FOR END OF ROUND",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Referee::guard_____Debug__startRound__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Referee guard Debug__Path__startRound,Debug__C__startRound::en */
    return Debug__SRO.checkDebug("STARTING ROUND",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Referee::actionchain_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    transitionaction_____Debug__C__Initial__Debug__Ac__Initial( msg );
    update_state( Debug__C__Initial__Debug__A__Ac__Initial );
    entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__Debug__En__STARTING_ROUND( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    transitionaction_____Debug__C__Initial__Debug__En__STARTING_ROUND( msg );
    update_state( Debug__C__Initial__Debug__A__En__Initial );
    entryaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    update_state( Debug__C__Initial );
    transitionaction_____Debug__C__Initial__Debug__end__trans__Initial( msg );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__Initial__Debug__init__trans__Initial( msg );
    update_state( Debug__C__Initial__Debug__B__Ac__Initial );
    entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_1( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial__Debug__B__Ac__Initial );
    entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_10( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_11( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_12( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_13( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_14( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_15( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_16( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_17( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_18( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_19( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_2( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial__Debug__A__Ac__Initial );
    entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_20( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_21( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_22( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_23( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_24( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_25( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_26( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_27( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_28( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_29( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_3( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial__Debug__A__En__Initial );
    entryaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_4_to_unvisited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_5_to_visited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_6( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_7( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_8( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Referee::actionchain_____Debug__C__Initial__new_transition_9( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__Debug__AC__endRound( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__B__Ac__endRound( msg );
    update_state( Debug__C__endRound );
    transitionaction_____Debug__C__endRound__Debug__AC__endRound( msg );
    update_state( Debug__C__endRound__Debug__A__Ac__endRound );
    entryaction_____Debug__C__endRound__Debug__A__Ac__endRound( msg );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__Debug__En__STARTING_ROUND( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__A__Ac__endRound( msg );
    update_state( Debug__C__endRound );
    transitionaction_____Debug__C__endRound__Debug__En__STARTING_ROUND( msg );
    update_state( Debug__C__endRound__Debug__A__En__STARTING_ROUND );
    entryaction_____Debug__C__endRound__Debug__A__En__STARTING_ROUND( msg );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__Debug__Ex__WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND( msg );
    update_state( Debug__C__endRound );
    transitionaction_____Debug__C__endRound__Debug__Ex__WAITING_FOR_END_OF_ROUND( msg );
    update_state( Debug__C__endRound__Debug__B__Ac__endRound );
    entryaction_____Debug__C__endRound__Debug__B__Ac__endRound( msg );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__Debug__end__trans__endRound( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__A__En__STARTING_ROUND( msg );
    update_state( Debug__C__endRound );
    transitionaction_____Debug__C__endRound__Debug__end__trans__endRound( msg );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__A__En__STARTING_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__Debug__init__trans__endRound( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__endRound__Debug__init__trans__endRound( msg );
    update_state( Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND );
    entryaction_____Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND( msg );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_30( const UMLRTMessage * msg )
{
    update_state( Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND );
    entryaction_____Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND( msg );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_31( const UMLRTMessage * msg )
{
    update_state( Debug__C__endRound__Debug__B__Ac__endRound );
    entryaction_____Debug__C__endRound__Debug__B__Ac__endRound( msg );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_32( const UMLRTMessage * msg )
{
    update_state( Debug__C__endRound__Debug__A__Ac__endRound );
    entryaction_____Debug__C__endRound__Debug__A__Ac__endRound( msg );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_33( const UMLRTMessage * msg )
{
    update_state( Debug__C__endRound__Debug__A__En__STARTING_ROUND );
    entryaction_____Debug__C__endRound__Debug__A__En__STARTING_ROUND( msg );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_34_to_unvisited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__endRound__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_35_to_visited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__endRound__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_36( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_37( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__B__Ac__endRound( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__B__Ac__endRound );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_38( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__A__Ac__endRound( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__A__Ac__endRound );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_39( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__A__En__STARTING_ROUND( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__A__En__STARTING_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_40( const UMLRTMessage * msg )
{
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_41( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_42( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__B__Ac__endRound( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__B__Ac__endRound );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_43( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__A__Ac__endRound( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__A__Ac__endRound );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_44( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__A__En__STARTING_ROUND( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__A__En__STARTING_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_45( const UMLRTMessage * msg )
{
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_46( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_47( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__B__Ac__endRound( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__B__Ac__endRound );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_48( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__A__Ac__endRound( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__A__Ac__endRound );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_49( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__A__En__STARTING_ROUND( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__A__En__STARTING_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_50( const UMLRTMessage * msg )
{
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_51( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_52( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__B__Ac__endRound( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__B__Ac__endRound );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_53( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__A__Ac__endRound( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__A__Ac__endRound );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_54( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__A__En__STARTING_ROUND( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__A__En__STARTING_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_55( const UMLRTMessage * msg )
{
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_56( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_57( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__B__Ac__endRound( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__B__Ac__endRound );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_58( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__A__Ac__endRound( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__A__Ac__endRound );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_59( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__A__En__STARTING_ROUND( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__A__En__STARTING_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_60( const UMLRTMessage * msg )
{
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_61( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_62( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__B__Ac__endRound( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__B__Ac__endRound );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_63( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__A__Ac__endRound( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__A__Ac__endRound );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_64( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endRound__Debug__A__En__STARTING_ROUND( msg );
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__Debug__A__En__STARTING_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__endRound__new_transition_65( const UMLRTMessage * msg )
{
    update_state( Debug__C__endRound );
    save_history( Debug__C__endRound, Debug__C__endRound__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__Debug__AC__startRound( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__B__Ac__startRound( msg );
    update_state( Debug__C__startRound );
    transitionaction_____Debug__C__startRound__Debug__AC__startRound( msg );
    update_state( Debug__C__startRound__Debug__A__Ac__startRound );
    entryaction_____Debug__C__startRound__Debug__A__Ac__startRound( msg );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__Debug__En__WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__A__Ac__startRound( msg );
    update_state( Debug__C__startRound );
    transitionaction_____Debug__C__startRound__Debug__En__WAITING_FOR_END_OF_ROUND( msg );
    update_state( Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND );
    entryaction_____Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND( msg );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__Debug__Ex__STARTING_ROUND( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__B__Ex__STARTING_ROUND( msg );
    update_state( Debug__C__startRound );
    transitionaction_____Debug__C__startRound__Debug__Ex__STARTING_ROUND( msg );
    update_state( Debug__C__startRound__Debug__B__Ac__startRound );
    entryaction_____Debug__C__startRound__Debug__B__Ac__startRound( msg );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__Debug__end__trans__startRound( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND( msg );
    update_state( Debug__C__startRound );
    transitionaction_____Debug__C__startRound__Debug__end__trans__startRound( msg );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__Debug__init__trans__startRound( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__startRound__Debug__init__trans__startRound( msg );
    update_state( Debug__C__startRound__Debug__B__Ex__STARTING_ROUND );
    entryaction_____Debug__C__startRound__Debug__B__Ex__STARTING_ROUND( msg );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_100( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_101( const UMLRTMessage * msg )
{
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_66( const UMLRTMessage * msg )
{
    update_state( Debug__C__startRound__Debug__B__Ex__STARTING_ROUND );
    entryaction_____Debug__C__startRound__Debug__B__Ex__STARTING_ROUND( msg );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_67( const UMLRTMessage * msg )
{
    update_state( Debug__C__startRound__Debug__B__Ac__startRound );
    entryaction_____Debug__C__startRound__Debug__B__Ac__startRound( msg );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_68( const UMLRTMessage * msg )
{
    update_state( Debug__C__startRound__Debug__A__Ac__startRound );
    entryaction_____Debug__C__startRound__Debug__A__Ac__startRound( msg );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_69( const UMLRTMessage * msg )
{
    update_state( Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND );
    entryaction_____Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND( msg );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_70_to_unvisited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__startRound__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_71_to_visited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__startRound__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_72( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__B__Ex__STARTING_ROUND( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__B__Ex__STARTING_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_73( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__B__Ac__startRound( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__B__Ac__startRound );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_74( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__A__Ac__startRound( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__A__Ac__startRound );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_75( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_76( const UMLRTMessage * msg )
{
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_77( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__B__Ex__STARTING_ROUND( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__B__Ex__STARTING_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_78( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__B__Ac__startRound( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__B__Ac__startRound );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_79( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__A__Ac__startRound( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__A__Ac__startRound );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_80( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_81( const UMLRTMessage * msg )
{
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_82( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__B__Ex__STARTING_ROUND( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__B__Ex__STARTING_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_83( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__B__Ac__startRound( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__B__Ac__startRound );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_84( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__A__Ac__startRound( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__A__Ac__startRound );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_85( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_86( const UMLRTMessage * msg )
{
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_87( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__B__Ex__STARTING_ROUND( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__B__Ex__STARTING_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_88( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__B__Ac__startRound( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__B__Ac__startRound );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_89( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__A__Ac__startRound( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__A__Ac__startRound );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_90( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_91( const UMLRTMessage * msg )
{
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_92( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__B__Ex__STARTING_ROUND( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__B__Ex__STARTING_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_93( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__B__Ac__startRound( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__B__Ac__startRound );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_94( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__A__Ac__startRound( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__A__Ac__startRound );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_95( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_96( const UMLRTMessage * msg )
{
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__boundary );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_97( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__B__Ex__STARTING_ROUND( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__B__Ex__STARTING_ROUND );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_98( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__B__Ac__startRound( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__B__Ac__startRound );
}

void Capsule_Referee::actionchain_____Debug__C__startRound__new_transition_99( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startRound__Debug__A__Ac__startRound( msg );
    update_state( Debug__C__startRound );
    save_history( Debug__C__startRound, Debug__C__startRound__Debug__A__Ac__startRound );
}

void Capsule_Referee::actionchain_____Debug__InitDebug( const UMLRTMessage * msg )
{
    transitionaction_____Debug__InitDebug( msg );
    update_state( Debug__InitState );
}

void Capsule_Referee::actionchain_____Debug__Initial( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial( msg );
}

void Capsule_Referee::actionchain_____Debug__Initial__E( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial__E( msg );
    update_state( STARTING_ROUND );
    entryaction_____STARTING_ROUND( msg );
}

void Capsule_Referee::actionchain_____Debug__Initial__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__Initial__S( msg );
    update_state( Debug__C__Initial );
}

void Capsule_Referee::actionchain_____Debug__Initial__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial__dbg__dbgDeferMsg( msg );
    update_state( Debug__C__Initial );
}

void Capsule_Referee::actionchain_____Debug__Initial__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial__dbg__dbgSetExecMode( msg );
    update_state( Debug__C__Initial );
}

void Capsule_Referee::actionchain_____Debug__Initial__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial__dbg__remBreakPoint( msg );
    update_state( Debug__C__Initial );
}

void Capsule_Referee::actionchain_____Debug__Initial__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial__dbg__setBreakPoint( msg );
    update_state( Debug__C__Initial );
}

void Capsule_Referee::actionchain_____Debug__Initial__dbg__varChange( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial__dbg__varChange( msg );
    update_state( Debug__C__Initial );
}

void Capsule_Referee::actionchain_____Debug__Initial__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial__dbg__viewBreakPoints( msg );
    update_state( Debug__C__Initial );
}

void Capsule_Referee::actionchain_____Debug__endRound( const UMLRTMessage * msg )
{
    exitaction_____WAITING_FOR_END_OF_ROUND( msg );
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__endRound( msg );
}

void Capsule_Referee::actionchain_____Debug__endRound__E( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__endRound__E( msg );
    update_state( STARTING_ROUND );
    entryaction_____STARTING_ROUND( msg );
}

void Capsule_Referee::actionchain_____Debug__endRound__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__endRound__S( msg );
    update_state( Debug__C__endRound );
}

void Capsule_Referee::actionchain_____Debug__endRound__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__endRound__dbg__dbgDeferMsg( msg );
    update_state( Debug__C__endRound );
}

void Capsule_Referee::actionchain_____Debug__endRound__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__endRound__dbg__dbgSetExecMode( msg );
    update_state( Debug__C__endRound );
}

void Capsule_Referee::actionchain_____Debug__endRound__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__endRound__dbg__remBreakPoint( msg );
    update_state( Debug__C__endRound );
}

void Capsule_Referee::actionchain_____Debug__endRound__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__endRound__dbg__setBreakPoint( msg );
    update_state( Debug__C__endRound );
}

void Capsule_Referee::actionchain_____Debug__endRound__dbg__varChange( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__endRound__dbg__varChange( msg );
    update_state( Debug__C__endRound );
}

void Capsule_Referee::actionchain_____Debug__endRound__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__endRound__dbg__viewBreakPoints( msg );
    update_state( Debug__C__endRound );
}

void Capsule_Referee::actionchain_____Debug__startRound( const UMLRTMessage * msg )
{
    exitaction_____STARTING_ROUND( msg );
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__startRound( msg );
}

void Capsule_Referee::actionchain_____Debug__startRound__E( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__startRound__E( msg );
    update_state( WAITING_FOR_END_OF_ROUND );
    entryaction_____WAITING_FOR_END_OF_ROUND( msg );
}

void Capsule_Referee::actionchain_____Debug__startRound__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__startRound__S( msg );
    update_state( Debug__C__startRound );
}

void Capsule_Referee::actionchain_____Debug__startRound__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__startRound__dbg__dbgDeferMsg( msg );
    update_state( Debug__C__startRound );
}

void Capsule_Referee::actionchain_____Debug__startRound__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__startRound__dbg__dbgSetExecMode( msg );
    update_state( Debug__C__startRound );
}

void Capsule_Referee::actionchain_____Debug__startRound__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__startRound__dbg__remBreakPoint( msg );
    update_state( Debug__C__startRound );
}

void Capsule_Referee::actionchain_____Debug__startRound__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__startRound__dbg__setBreakPoint( msg );
    update_state( Debug__C__startRound );
}

void Capsule_Referee::actionchain_____Debug__startRound__dbg__varChange( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__startRound__dbg__varChange( msg );
    update_state( Debug__C__startRound );
}

void Capsule_Referee::actionchain_____Debug__startRound__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__startRound__dbg__viewBreakPoints( msg );
    update_state( Debug__C__startRound );
}

void Capsule_Referee::actionchain_____Initial( const UMLRTMessage * msg )
{
    transitionaction_____Initial( msg );
    update_state( STARTING_ROUND );
    entryaction_____STARTING_ROUND( msg );
}

void Capsule_Referee::actionchain_____endRound( const UMLRTMessage * msg )
{
    transitionaction_____endRound( msg );
    update_state( STARTING_ROUND );
    entryaction_____STARTING_ROUND( msg );
}

void Capsule_Referee::actionchain_____startRound( const UMLRTMessage * msg )
{
    transitionaction_____startRound( msg );
    update_state( WAITING_FOR_END_OF_ROUND );
    entryaction_____WAITING_FOR_END_OF_ROUND( msg );
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__Initial__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__Initial__Debug__init__trans__Initial( msg );
    return Debug__C__Initial__Debug__B__Ac__Initial;
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__Initial__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__E( msg );
    return STARTING_ROUND;
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__Initial__new_exitpoint_1( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__dbg__varChange( msg );
    return choice_____Debug__C__Initial__deephistory( msg );
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__Initial__new_exitpoint_2( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__dbg__setBreakPoint( msg );
    return choice_____Debug__C__Initial__deephistory( msg );
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__Initial__new_exitpoint_3( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__dbg__remBreakPoint( msg );
    return choice_____Debug__C__Initial__deephistory( msg );
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__Initial__new_exitpoint_4( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__dbg__viewBreakPoints( msg );
    return choice_____Debug__C__Initial__deephistory( msg );
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__Initial__new_exitpoint_5( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__dbg__dbgSetExecMode( msg );
    return choice_____Debug__C__Initial__deephistory( msg );
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__Initial__new_exitpoint_6( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__dbg__dbgDeferMsg( msg );
    return choice_____Debug__C__Initial__deephistory( msg );
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__endRound__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__endRound__Debug__init__trans__endRound( msg );
    return Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND;
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__endRound__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__endRound__E( msg );
    return STARTING_ROUND;
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__endRound__new_exitpoint_10( const UMLRTMessage * msg )
{
    actionchain_____Debug__endRound__dbg__viewBreakPoints( msg );
    return choice_____Debug__C__endRound__deephistory( msg );
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__endRound__new_exitpoint_11( const UMLRTMessage * msg )
{
    actionchain_____Debug__endRound__dbg__dbgSetExecMode( msg );
    return choice_____Debug__C__endRound__deephistory( msg );
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__endRound__new_exitpoint_12( const UMLRTMessage * msg )
{
    actionchain_____Debug__endRound__dbg__dbgDeferMsg( msg );
    return choice_____Debug__C__endRound__deephistory( msg );
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__endRound__new_exitpoint_7( const UMLRTMessage * msg )
{
    actionchain_____Debug__endRound__dbg__varChange( msg );
    return choice_____Debug__C__endRound__deephistory( msg );
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__endRound__new_exitpoint_8( const UMLRTMessage * msg )
{
    actionchain_____Debug__endRound__dbg__setBreakPoint( msg );
    return choice_____Debug__C__endRound__deephistory( msg );
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__endRound__new_exitpoint_9( const UMLRTMessage * msg )
{
    actionchain_____Debug__endRound__dbg__remBreakPoint( msg );
    return choice_____Debug__C__endRound__deephistory( msg );
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__startRound__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__startRound__Debug__init__trans__startRound( msg );
    return Debug__C__startRound__Debug__B__Ex__STARTING_ROUND;
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__startRound__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__startRound__E( msg );
    return WAITING_FOR_END_OF_ROUND;
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__startRound__new_exitpoint_13( const UMLRTMessage * msg )
{
    actionchain_____Debug__startRound__dbg__varChange( msg );
    return choice_____Debug__C__startRound__deephistory( msg );
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__startRound__new_exitpoint_14( const UMLRTMessage * msg )
{
    actionchain_____Debug__startRound__dbg__setBreakPoint( msg );
    return choice_____Debug__C__startRound__deephistory( msg );
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__startRound__new_exitpoint_15( const UMLRTMessage * msg )
{
    actionchain_____Debug__startRound__dbg__remBreakPoint( msg );
    return choice_____Debug__C__startRound__deephistory( msg );
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__startRound__new_exitpoint_16( const UMLRTMessage * msg )
{
    actionchain_____Debug__startRound__dbg__viewBreakPoints( msg );
    return choice_____Debug__C__startRound__deephistory( msg );
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__startRound__new_exitpoint_17( const UMLRTMessage * msg )
{
    actionchain_____Debug__startRound__dbg__dbgSetExecMode( msg );
    return choice_____Debug__C__startRound__deephistory( msg );
}

Capsule_Referee::State Capsule_Referee::junction_____Debug__C__startRound__new_exitpoint_18( const UMLRTMessage * msg )
{
    actionchain_____Debug__startRound__dbg__dbgDeferMsg( msg );
    return choice_____Debug__C__startRound__deephistory( msg );
}

Capsule_Referee::State Capsule_Referee::choice_____Debug__C__Initial__deephistory( const UMLRTMessage * msg )
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

Capsule_Referee::State Capsule_Referee::choice_____Debug__C__endRound__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__endRound, Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND ) )
    {
        actionchain_____Debug__C__endRound__new_transition_30( msg );
        return Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND;
    }
    else if( check_history( Debug__C__endRound, Debug__C__endRound__Debug__B__Ac__endRound ) )
    {
        actionchain_____Debug__C__endRound__new_transition_31( msg );
        return Debug__C__endRound__Debug__B__Ac__endRound;
    }
    else if( check_history( Debug__C__endRound, Debug__C__endRound__Debug__A__Ac__endRound ) )
    {
        actionchain_____Debug__C__endRound__new_transition_32( msg );
        return Debug__C__endRound__Debug__A__Ac__endRound;
    }
    else if( check_history( Debug__C__endRound, Debug__C__endRound__Debug__A__En__STARTING_ROUND ) )
    {
        actionchain_____Debug__C__endRound__new_transition_33( msg );
        return Debug__C__endRound__Debug__A__En__STARTING_ROUND;
    }
    else if( check_history( Debug__C__endRound, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__endRound__new_transition_34_to_unvisited_boundary( msg );
        return Debug__C__endRound__boundary;
    }
    else if( check_history( Debug__C__endRound, Debug__C__endRound__boundary ) )
    {
        actionchain_____Debug__C__endRound__new_transition_35_to_visited_boundary( msg );
        return Debug__C__endRound__boundary;
    }
    return currentState;
}

Capsule_Referee::State Capsule_Referee::choice_____Debug__C__startRound__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__startRound, Debug__C__startRound__Debug__B__Ex__STARTING_ROUND ) )
    {
        actionchain_____Debug__C__startRound__new_transition_66( msg );
        return Debug__C__startRound__Debug__B__Ex__STARTING_ROUND;
    }
    else if( check_history( Debug__C__startRound, Debug__C__startRound__Debug__B__Ac__startRound ) )
    {
        actionchain_____Debug__C__startRound__new_transition_67( msg );
        return Debug__C__startRound__Debug__B__Ac__startRound;
    }
    else if( check_history( Debug__C__startRound, Debug__C__startRound__Debug__A__Ac__startRound ) )
    {
        actionchain_____Debug__C__startRound__new_transition_68( msg );
        return Debug__C__startRound__Debug__A__Ac__startRound;
    }
    else if( check_history( Debug__C__startRound, Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND ) )
    {
        actionchain_____Debug__C__startRound__new_transition_69( msg );
        return Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND;
    }
    else if( check_history( Debug__C__startRound, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__startRound__new_transition_70_to_unvisited_boundary( msg );
        return Debug__C__startRound__boundary;
    }
    else if( check_history( Debug__C__startRound, Debug__C__startRound__boundary ) )
    {
        actionchain_____Debug__C__startRound__new_transition_71_to_visited_boundary( msg );
        return Debug__C__startRound__boundary;
    }
    return currentState;
}

Capsule_Referee::State Capsule_Referee::choice_____Debug__Path__Initial( const UMLRTMessage * msg )
{
    if( guard_____Debug__Initial__S( msg ) )
    {
        actionchain_____Debug__Initial__S( msg );
        return junction_____Debug__C__Initial__en( msg );
    }
    else
    {
        actionchain_____Initial( msg );
        return STARTING_ROUND;
    }
    return currentState;
}

Capsule_Referee::State Capsule_Referee::choice_____Debug__Path__endRound( const UMLRTMessage * msg )
{
    if( guard_____Debug__endRound__S( msg ) )
    {
        actionchain_____Debug__endRound__S( msg );
        return junction_____Debug__C__endRound__en( msg );
    }
    else
    {
        actionchain_____endRound( msg );
        return STARTING_ROUND;
    }
    return currentState;
}

Capsule_Referee::State Capsule_Referee::choice_____Debug__Path__startRound( const UMLRTMessage * msg )
{
    if( guard_____Debug__startRound__S( msg ) )
    {
        actionchain_____Debug__startRound__S( msg );
        return junction_____Debug__C__startRound__en( msg );
    }
    else
    {
        actionchain_____startRound( msg );
        return WAITING_FOR_END_OF_ROUND;
    }
    return currentState;
}

Capsule_Referee::State Capsule_Referee::state_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Initial__Debug__En__STARTING_ROUND( msg );
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
    case port_endPort:
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

Capsule_Referee::State Capsule_Referee::state_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg )
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
    case port_endPort:
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

Capsule_Referee::State Capsule_Referee::state_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg )
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
    case port_endPort:
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

Capsule_Referee::State Capsule_Referee::state_____Debug__C__Initial__boundary( const UMLRTMessage * msg )
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
    case port_endPort:
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

Capsule_Referee::State Capsule_Referee::state_____Debug__C__endRound__Debug__A__Ac__endRound( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__endRound__Debug__En__STARTING_ROUND( msg );
            return Debug__C__endRound__Debug__A__En__STARTING_ROUND;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__endRound__new_transition_38( msg );
            return junction_____Debug__C__endRound__new_exitpoint_7( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__endRound__new_transition_43( msg );
            return junction_____Debug__C__endRound__new_exitpoint_8( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__endRound__new_transition_48( msg );
            return junction_____Debug__C__endRound__new_exitpoint_9( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__endRound__new_transition_53( msg );
            return junction_____Debug__C__endRound__new_exitpoint_10( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__endRound__new_transition_58( msg );
            return junction_____Debug__C__endRound__new_exitpoint_11( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_endPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__endRound__new_transition_63( msg );
            return junction_____Debug__C__endRound__new_exitpoint_12( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Referee::State Capsule_Referee::state_____Debug__C__endRound__Debug__A__En__STARTING_ROUND( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__endRound__Debug__end__trans__endRound( msg );
            return junction_____Debug__C__endRound__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__endRound__new_transition_39( msg );
            return junction_____Debug__C__endRound__new_exitpoint_7( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__endRound__new_transition_44( msg );
            return junction_____Debug__C__endRound__new_exitpoint_8( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__endRound__new_transition_49( msg );
            return junction_____Debug__C__endRound__new_exitpoint_9( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__endRound__new_transition_54( msg );
            return junction_____Debug__C__endRound__new_exitpoint_10( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__endRound__new_transition_59( msg );
            return junction_____Debug__C__endRound__new_exitpoint_11( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_endPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__endRound__new_transition_64( msg );
            return junction_____Debug__C__endRound__new_exitpoint_12( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Referee::State Capsule_Referee::state_____Debug__C__endRound__Debug__B__Ac__endRound( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__endRound__Debug__AC__endRound( msg );
            return Debug__C__endRound__Debug__A__Ac__endRound;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__endRound__new_transition_37( msg );
            return junction_____Debug__C__endRound__new_exitpoint_7( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__endRound__new_transition_42( msg );
            return junction_____Debug__C__endRound__new_exitpoint_8( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__endRound__new_transition_47( msg );
            return junction_____Debug__C__endRound__new_exitpoint_9( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__endRound__new_transition_52( msg );
            return junction_____Debug__C__endRound__new_exitpoint_10( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__endRound__new_transition_57( msg );
            return junction_____Debug__C__endRound__new_exitpoint_11( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_endPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__endRound__new_transition_62( msg );
            return junction_____Debug__C__endRound__new_exitpoint_12( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Referee::State Capsule_Referee::state_____Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__endRound__Debug__Ex__WAITING_FOR_END_OF_ROUND( msg );
            return Debug__C__endRound__Debug__B__Ac__endRound;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__endRound__new_transition_36( msg );
            return junction_____Debug__C__endRound__new_exitpoint_7( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__endRound__new_transition_41( msg );
            return junction_____Debug__C__endRound__new_exitpoint_8( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__endRound__new_transition_46( msg );
            return junction_____Debug__C__endRound__new_exitpoint_9( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__endRound__new_transition_51( msg );
            return junction_____Debug__C__endRound__new_exitpoint_10( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__endRound__new_transition_56( msg );
            return junction_____Debug__C__endRound__new_exitpoint_11( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_endPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__endRound__new_transition_61( msg );
            return junction_____Debug__C__endRound__new_exitpoint_12( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Referee::State Capsule_Referee::state_____Debug__C__endRound__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__endRound__new_transition_40( msg );
            return junction_____Debug__C__endRound__new_exitpoint_7( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__endRound__new_transition_45( msg );
            return junction_____Debug__C__endRound__new_exitpoint_8( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__endRound__new_transition_50( msg );
            return junction_____Debug__C__endRound__new_exitpoint_9( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__endRound__new_transition_55( msg );
            return junction_____Debug__C__endRound__new_exitpoint_10( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__endRound__new_transition_60( msg );
            return junction_____Debug__C__endRound__new_exitpoint_11( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_endPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__endRound__new_transition_65( msg );
            return junction_____Debug__C__endRound__new_exitpoint_12( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Referee::State Capsule_Referee::state_____Debug__C__startRound__Debug__A__Ac__startRound( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__startRound__Debug__En__WAITING_FOR_END_OF_ROUND( msg );
            return Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__startRound__new_transition_74( msg );
            return junction_____Debug__C__startRound__new_exitpoint_13( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__startRound__new_transition_79( msg );
            return junction_____Debug__C__startRound__new_exitpoint_14( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__startRound__new_transition_84( msg );
            return junction_____Debug__C__startRound__new_exitpoint_15( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__startRound__new_transition_89( msg );
            return junction_____Debug__C__startRound__new_exitpoint_16( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__startRound__new_transition_94( msg );
            return junction_____Debug__C__startRound__new_exitpoint_17( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_endPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__startRound__new_transition_99( msg );
            return junction_____Debug__C__startRound__new_exitpoint_18( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Referee::State Capsule_Referee::state_____Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__startRound__Debug__end__trans__startRound( msg );
            return junction_____Debug__C__startRound__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__startRound__new_transition_75( msg );
            return junction_____Debug__C__startRound__new_exitpoint_13( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__startRound__new_transition_80( msg );
            return junction_____Debug__C__startRound__new_exitpoint_14( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__startRound__new_transition_85( msg );
            return junction_____Debug__C__startRound__new_exitpoint_15( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__startRound__new_transition_90( msg );
            return junction_____Debug__C__startRound__new_exitpoint_16( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__startRound__new_transition_95( msg );
            return junction_____Debug__C__startRound__new_exitpoint_17( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_endPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__startRound__new_transition_100( msg );
            return junction_____Debug__C__startRound__new_exitpoint_18( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Referee::State Capsule_Referee::state_____Debug__C__startRound__Debug__B__Ac__startRound( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__startRound__Debug__AC__startRound( msg );
            return Debug__C__startRound__Debug__A__Ac__startRound;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__startRound__new_transition_73( msg );
            return junction_____Debug__C__startRound__new_exitpoint_13( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__startRound__new_transition_78( msg );
            return junction_____Debug__C__startRound__new_exitpoint_14( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__startRound__new_transition_83( msg );
            return junction_____Debug__C__startRound__new_exitpoint_15( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__startRound__new_transition_88( msg );
            return junction_____Debug__C__startRound__new_exitpoint_16( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__startRound__new_transition_93( msg );
            return junction_____Debug__C__startRound__new_exitpoint_17( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_endPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__startRound__new_transition_98( msg );
            return junction_____Debug__C__startRound__new_exitpoint_18( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Referee::State Capsule_Referee::state_____Debug__C__startRound__Debug__B__Ex__STARTING_ROUND( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__startRound__Debug__Ex__STARTING_ROUND( msg );
            return Debug__C__startRound__Debug__B__Ac__startRound;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__startRound__new_transition_72( msg );
            return junction_____Debug__C__startRound__new_exitpoint_13( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__startRound__new_transition_77( msg );
            return junction_____Debug__C__startRound__new_exitpoint_14( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__startRound__new_transition_82( msg );
            return junction_____Debug__C__startRound__new_exitpoint_15( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__startRound__new_transition_87( msg );
            return junction_____Debug__C__startRound__new_exitpoint_16( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__startRound__new_transition_92( msg );
            return junction_____Debug__C__startRound__new_exitpoint_17( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_endPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__startRound__new_transition_97( msg );
            return junction_____Debug__C__startRound__new_exitpoint_18( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Referee::State Capsule_Referee::state_____Debug__C__startRound__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__startRound__new_transition_76( msg );
            return junction_____Debug__C__startRound__new_exitpoint_13( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__startRound__new_transition_81( msg );
            return junction_____Debug__C__startRound__new_exitpoint_14( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__startRound__new_transition_86( msg );
            return junction_____Debug__C__startRound__new_exitpoint_15( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__startRound__new_transition_91( msg );
            return junction_____Debug__C__startRound__new_exitpoint_16( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__startRound__new_transition_96( msg );
            return junction_____Debug__C__startRound__new_exitpoint_17( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_endPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__startRound__new_transition_101( msg );
            return junction_____Debug__C__startRound__new_exitpoint_18( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Referee::State Capsule_Referee::state_____Debug__InitState( const UMLRTMessage * msg )
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

Capsule_Referee::State Capsule_Referee::state_____STARTING_ROUND( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_refereeTimer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____Debug__startRound( msg );
            return choice_____Debug__Path__startRound( msg );
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

Capsule_Referee::State Capsule_Referee::state_____WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_endPort:
        switch( msg->getSignalId() )
        {
        case endProtocol::signal_end:
            actionchain_____Debug__endRound( msg );
            return choice_____Debug__Path__endRound( msg );
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
        Capsule_Referee::port_endPort,
        "endProtocol",
        "endPort",
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
        Capsule_Referee::port_startPort,
        "StartProtocol",
        "startPort",
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
        Capsule_Referee::port_extComm,
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
        Capsule_Referee::port_refereeTimer,
        "Timing",
        "refereeTimer",
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
        Capsule_Referee::port_log,
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

static void instantiate_Referee( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    const UMLRTCommsPort * * internalPorts = UMLRTFrameService::createInternalPorts( slot, &Referee );
    slot->capsule = new Capsule_Referee( &Referee, slot, borderPorts, internalPorts, false );
}

const UMLRTCapsuleClass Referee = 
{
    "Referee",
    NULL,
    instantiate_Referee,
    0,
    NULL,
    2,
    portroles_border,
    3,
    portroles_internal
};

