
#include "Pinger.hh"

#include "ExtInterface.hh"
#include "PingPongProtocol.hh"
#include "StartProtocol.hh"
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

Capsule_Pinger::Capsule_Pinger( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, extComm( internalPorts[internalport_extComm] )
, pingPort( borderPorts[borderport_pingPort] )
, pingerTimer( internalPorts[internalport_pingerTimer] )
, startPort( borderPorts[borderport_startPort] )
, pingsSent( 0 )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[Debug__C__Initial] = "Debug__C__Initial";
    stateNames[Debug__C__endOfRound] = "Debug__C__endOfRound";
    stateNames[Debug__C__keepPlaying] = "Debug__C__keepPlaying";
    stateNames[Debug__C__onPong] = "Debug__C__onPong";
    stateNames[Debug__C__startSignal] = "Debug__C__startSignal";
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
    stateNames[Debug__C__onPong__Debug__A__Ac__onPong] = "Debug__C__onPong__Debug__A__Ac__onPong";
    stateNames[Debug__C__onPong__Debug__B__Ac__onPong] = "Debug__C__onPong__Debug__B__Ac__onPong";
    stateNames[Debug__C__onPong__Debug__B__Ex__PLAYING] = "Debug__C__onPong__Debug__B__Ex__PLAYING";
    stateNames[Debug__C__onPong__boundary] = "Debug__C__onPong__boundary";
    stateNames[Debug__C__startSignal__Debug__A__Ac__startSignal] = "Debug__C__startSignal__Debug__A__Ac__startSignal";
    stateNames[Debug__C__startSignal__Debug__A__En__PLAYING] = "Debug__C__startSignal__Debug__A__En__PLAYING";
    stateNames[Debug__C__startSignal__Debug__B__Ac__startSignal] = "Debug__C__startSignal__Debug__B__Ac__startSignal";
    stateNames[Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START] = "Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START";
    stateNames[Debug__C__startSignal__boundary] = "Debug__C__startSignal__boundary";
    stateNames[Debug__C__timeout__Debug__A__Ac__timeout] = "Debug__C__timeout__Debug__A__Ac__timeout";
    stateNames[Debug__C__timeout__Debug__A__En__PLAYING] = "Debug__C__timeout__Debug__A__En__PLAYING";
    stateNames[Debug__C__timeout__Debug__B__Ac__timeout] = "Debug__C__timeout__Debug__B__Ac__timeout";
    stateNames[Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER] = "Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER";
    stateNames[Debug__C__timeout__boundary] = "Debug__C__timeout__boundary";
    stateNames[Debug__InitState] = "Debug__InitState";
    stateNames[PLAYING] = "PLAYING";
    stateNames[WAITING_FOR_TIMER] = "WAITING_FOR_TIMER";
    stateNames[WAITING_TO_START] = "WAITING_TO_START";
    stateNames[SPECIAL_INTERNAL_STATE_TOP] = "<top>";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
    int i = 0;
    while( i < 6 )
        history[i++] = SPECIAL_INTERNAL_STATE_UNVISITED;
}










void Capsule_Pinger::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_pingPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_pingPort, index, true );
            break;
        case borderport_startPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_startPort, index, true );
            break;
        }
}

void Capsule_Pinger::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_pingPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_pingPort, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_pingPort], index );
            break;
        case borderport_startPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_startPort, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_startPort], index );
            break;
        }
}






void Capsule_Pinger::Debug__recallAllMsg()
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger operation Debug__recallAllMsg */
    pingPort.recallAll();
    startPort.recallAll();
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_Pinger::Debug__variablesView()
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger operation Debug__variablesView */
    std::string tempS="";
    tempS.append("pingsSent,");
    tempS.append("Integer,");
    if(pingsSent!=0){
    char tempR[10];
    sprintf(tempR,"%d",pingsSent);
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

bool Capsule_Pinger::Debug__variablesChange( char * varName, char * varValue )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger operation Debug__variablesChange */
    std::string tempVarName="";
    tempVarName.append(varName);
    if ("pingsSent"==tempVarName){
    pingsSent=atoi(varValue);
    return true;
    }else 
    return false;
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_Pinger::Debug__sendEvent( debugEvents::EVENTSOURCEKIND eventSourceKind, debugEvents::EVENTTYPE eventType, const char * instanceName, int capsuleIndex, const char * signalName, const char * capsuleName, char * sourceName, char * reserve1, char * reserve2, const char * reserve3, const char * reserve4 )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger operation Debug__sendEvent */
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

void Capsule_Pinger::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case PLAYING:
        currentState = state_____PLAYING( &message );
        break;
    case WAITING_TO_START:
        currentState = state_____WAITING_TO_START( &message );
        break;
    case WAITING_FOR_TIMER:
        currentState = state_____WAITING_FOR_TIMER( &message );
        break;
    case Debug__InitState:
        currentState = state_____Debug__InitState( &message );
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
    case Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER:
        currentState = state_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( &message );
        break;
    case Debug__C__timeout__Debug__B__Ac__timeout:
        currentState = state_____Debug__C__timeout__Debug__B__Ac__timeout( &message );
        break;
    case Debug__C__timeout__Debug__A__Ac__timeout:
        currentState = state_____Debug__C__timeout__Debug__A__Ac__timeout( &message );
        break;
    case Debug__C__timeout__Debug__A__En__PLAYING:
        currentState = state_____Debug__C__timeout__Debug__A__En__PLAYING( &message );
        break;
    case Debug__C__timeout__boundary:
        currentState = state_____Debug__C__timeout__boundary( &message );
        break;
    case Debug__C__onPong__Debug__B__Ex__PLAYING:
        currentState = state_____Debug__C__onPong__Debug__B__Ex__PLAYING( &message );
        break;
    case Debug__C__onPong__Debug__B__Ac__onPong:
        currentState = state_____Debug__C__onPong__Debug__B__Ac__onPong( &message );
        break;
    case Debug__C__onPong__Debug__A__Ac__onPong:
        currentState = state_____Debug__C__onPong__Debug__A__Ac__onPong( &message );
        break;
    case Debug__C__onPong__boundary:
        currentState = state_____Debug__C__onPong__boundary( &message );
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
    case Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START:
        currentState = state_____Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START( &message );
        break;
    case Debug__C__startSignal__Debug__B__Ac__startSignal:
        currentState = state_____Debug__C__startSignal__Debug__B__Ac__startSignal( &message );
        break;
    case Debug__C__startSignal__Debug__A__Ac__startSignal:
        currentState = state_____Debug__C__startSignal__Debug__A__Ac__startSignal( &message );
        break;
    case Debug__C__startSignal__Debug__A__En__PLAYING:
        currentState = state_____Debug__C__startSignal__Debug__A__En__PLAYING( &message );
        break;
    case Debug__C__startSignal__boundary:
        currentState = state_____Debug__C__startSignal__boundary( &message );
        break;
    default:
        break;
    }
}

void Capsule_Pinger::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Debug__InitDebug( &message );
    currentState = Debug__InitState;
}

const char * Capsule_Pinger::getCurrentStateString() const
{
    return stateNames[currentState];
}





void Capsule_Pinger::save_history( Capsule_Pinger::State compositeState, Capsule_Pinger::State subState )
{
    history[compositeState] = subState;
}

bool Capsule_Pinger::check_history( Capsule_Pinger::State compositeState, Capsule_Pinger::State subState )
{
    return history[compositeState] == subState;
}

void Capsule_Pinger::update_state( Capsule_Pinger::State newState )
{
    currentState = newState;
}

void Capsule_Pinger::entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__Initial::Debug__A__Ac__Initial entry  */
    if (not(Debug__SRO.checkDebug("Initial","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("WAITING TO START","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__Initial::Region1::Debug__A__Ac__Initial",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::entryaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__Initial::Debug__A__En__Initial entry  */
    if (not(Debug__SRO.checkDebug("WAITING TO START","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__Initial::Region1::Debug__A__En__Initial",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__Initial::Debug__B__Ac__Initial entry  */
    if (not(Debug__SRO.checkDebug("Initial","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__Initial::Region1::Debug__B__Ac__Initial",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::entryaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__endOfRound::Debug__A__Ac__endOfRound entry  */
    if (not(Debug__SRO.checkDebug("endOfRound","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("WAITING TO START","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__endOfRound::Region1::Debug__A__Ac__endOfRound",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::entryaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__endOfRound::Debug__A__En__endOfRound entry  */
    if (not(Debug__SRO.checkDebug("WAITING TO START","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__endOfRound::Region1::Debug__A__En__endOfRound",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::entryaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__endOfRound::Debug__B__Ac__endOfRound entry  */
    if (not(Debug__SRO.checkDebug("endOfRound","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__endOfRound::Region1::Debug__B__Ac__endOfRound",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::entryaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__keepPlaying::Debug__A__Ac__keepPlaying entry  */
    if (not(Debug__SRO.checkDebug("keepPlaying","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("WAITING FOR TIMER","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__keepPlaying::Region1::Debug__A__Ac__keepPlaying",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::entryaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__keepPlaying::Debug__A__En__keepPlaying entry  */
    if (not(Debug__SRO.checkDebug("WAITING FOR TIMER","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__keepPlaying::Region1::Debug__A__En__keepPlaying",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::entryaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__keepPlaying::Debug__B__Ac__keepPlaying entry  */
    if (not(Debug__SRO.checkDebug("keepPlaying","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__keepPlaying::Region1::Debug__B__Ac__keepPlaying",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::entryaction_____Debug__C__onPong__Debug__A__Ac__onPong( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__onPong::Debug__A__Ac__onPong entry  */
    if (not(Debug__SRO.checkDebug("onPong","","",3,TransitionEffectBreakPoint,1))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__onPong::Region1::Debug__A__Ac__onPong",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::entryaction_____Debug__C__onPong__Debug__B__Ac__onPong( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__onPong::Debug__B__Ac__onPong entry  */
    if (not(Debug__SRO.checkDebug("PLAYING","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("onPong","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__onPong::Region1::Debug__B__Ac__onPong",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::entryaction_____Debug__C__onPong__Debug__B__Ex__PLAYING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__onPong::Debug__B__Ex__PLAYING entry  */
    if (not(Debug__SRO.checkDebug("PLAYING","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__onPong::Region1::Debug__B__Ex__PLAYING",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::entryaction_____Debug__C__startSignal__Debug__A__Ac__startSignal( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__startSignal::Debug__A__Ac__startSignal entry  */
    if (not(Debug__SRO.checkDebug("startSignal","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("PLAYING","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__startSignal::Region1::Debug__A__Ac__startSignal",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::entryaction_____Debug__C__startSignal__Debug__A__En__PLAYING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__startSignal::Debug__A__En__PLAYING entry  */
    if (not(Debug__SRO.checkDebug("PLAYING","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__startSignal::Region1::Debug__A__En__PLAYING",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::entryaction_____Debug__C__startSignal__Debug__B__Ac__startSignal( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__startSignal::Debug__B__Ac__startSignal entry  */
    if (not(Debug__SRO.checkDebug("WAITING TO START","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("startSignal","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__startSignal::Region1::Debug__B__Ac__startSignal",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::entryaction_____Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__startSignal::Debug__B__Ex__WAITING TO START entry  */
    if (not(Debug__SRO.checkDebug("WAITING TO START","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__startSignal::Region1::Debug__B__Ex__WAITING TO START",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::entryaction_____Debug__C__timeout__Debug__A__Ac__timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__timeout::Debug__A__Ac__timeout entry  */
    if (not(Debug__SRO.checkDebug("timeout","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("PLAYING","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__timeout::Region1::Debug__A__Ac__timeout",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::entryaction_____Debug__C__timeout__Debug__A__En__PLAYING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__timeout::Debug__A__En__PLAYING entry  */
    if (not(Debug__SRO.checkDebug("PLAYING","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__timeout::Region1::Debug__A__En__PLAYING",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::entryaction_____Debug__C__timeout__Debug__B__Ac__timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__timeout::Debug__B__Ac__timeout entry  */
    if (not(Debug__SRO.checkDebug("WAITING FOR TIMER","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("timeout","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__timeout::Region1::Debug__B__Ac__timeout",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::entryaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__timeout::Debug__B__Ex__WAITING FOR TIMER entry  */
    if (not(Debug__SRO.checkDebug("WAITING FOR TIMER","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__timeout::Region1::Debug__B__Ex__WAITING FOR TIMER",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::entryaction_____PLAYING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::PLAYING entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::PLAYING",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::entryaction_____WAITING_FOR_TIMER( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::WAITING FOR TIMER entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::WAITING FOR TIMER",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::entryaction_____WAITING_TO_START( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::WAITING TO START entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::WAITING TO START",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__Initial::Debug__A__Ac__Initial exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__Initial::Region1::Debug__A__Ac__Initial",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::exitaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__Initial::Debug__A__En__Initial exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__Initial::Region1::Debug__A__En__Initial",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__Initial::Debug__B__Ac__Initial exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__Initial::Region1::Debug__B__Ac__Initial",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::exitaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__endOfRound::Debug__A__Ac__endOfRound exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__endOfRound::Region1::Debug__A__Ac__endOfRound",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::exitaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__endOfRound::Debug__A__En__endOfRound exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__endOfRound::Region1::Debug__A__En__endOfRound",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::exitaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__endOfRound::Debug__B__Ac__endOfRound exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__endOfRound::Region1::Debug__B__Ac__endOfRound",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::exitaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__keepPlaying::Debug__A__Ac__keepPlaying exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__keepPlaying::Region1::Debug__A__Ac__keepPlaying",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::exitaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__keepPlaying::Debug__A__En__keepPlaying exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__keepPlaying::Region1::Debug__A__En__keepPlaying",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::exitaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__keepPlaying::Debug__B__Ac__keepPlaying exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__keepPlaying::Region1::Debug__B__Ac__keepPlaying",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::exitaction_____Debug__C__onPong__Debug__A__Ac__onPong( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__onPong::Debug__A__Ac__onPong exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__onPong::Region1::Debug__A__Ac__onPong",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::exitaction_____Debug__C__onPong__Debug__B__Ac__onPong( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__onPong::Debug__B__Ac__onPong exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__onPong::Region1::Debug__B__Ac__onPong",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::exitaction_____Debug__C__onPong__Debug__B__Ex__PLAYING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__onPong::Debug__B__Ex__PLAYING exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__onPong::Region1::Debug__B__Ex__PLAYING",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::exitaction_____Debug__C__startSignal__Debug__A__Ac__startSignal( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__startSignal::Debug__A__Ac__startSignal exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__startSignal::Region1::Debug__A__Ac__startSignal",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::exitaction_____Debug__C__startSignal__Debug__A__En__PLAYING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__startSignal::Debug__A__En__PLAYING exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__startSignal::Region1::Debug__A__En__PLAYING",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::exitaction_____Debug__C__startSignal__Debug__B__Ac__startSignal( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__startSignal::Debug__B__Ac__startSignal exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__startSignal::Region1::Debug__B__Ac__startSignal",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::exitaction_____Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__startSignal::Debug__B__Ex__WAITING TO START exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__startSignal::Region1::Debug__B__Ex__WAITING TO START",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::exitaction_____Debug__C__timeout__Debug__A__Ac__timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__timeout::Debug__A__Ac__timeout exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__timeout::Region1::Debug__A__Ac__timeout",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::exitaction_____Debug__C__timeout__Debug__A__En__PLAYING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__timeout::Debug__A__En__PLAYING exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__timeout::Region1::Debug__A__En__PLAYING",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::exitaction_____Debug__C__timeout__Debug__B__Ac__timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__timeout::Debug__B__Ac__timeout exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__timeout::Region1::Debug__B__Ac__timeout",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::exitaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__timeout::Debug__B__Ex__WAITING FOR TIMER exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__timeout::Region1::Debug__B__Ex__WAITING FOR TIMER",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::exitaction_____PLAYING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::PLAYING exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::PLAYING",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::exitaction_____WAITING_FOR_TIMER( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::WAITING FOR TIMER exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::WAITING FOR TIMER",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::exitaction_____WAITING_TO_START( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::WAITING TO START exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::WAITING TO START",(char *)"",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__Initial transition Debug__C__Initial::Debug__B__Ac__Initial,Debug__C__Initial::Debug__A__Ac__Initial,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__Initial::Region1::Debug__Ac__Initial",(char *)"Debug__B__Ac__Initial",(char *)"Debug__A__Ac__Initial",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__Initial__Debug__En__WAITING_TO_START( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__Initial transition Debug__C__Initial::Debug__A__Ac__Initial,Debug__C__Initial::Debug__A__En__Initial,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__Initial::Region1::Debug__En__WAITING TO START",(char *)"Debug__A__Ac__Initial",(char *)"Debug__A__En__Initial",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__Initial transition Debug__C__Initial::Debug__A__En__Initial,Debug__C__Initial::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__Initial::Region1::Debug__end__trans__Initial",(char *)"Debug__A__En__Initial",(char *)"ex",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__Initial transition Debug__C__Initial::en,Debug__C__Initial::Debug__B__Ac__Initial */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__Initial::Region1::Debug__init__trans__Initial",(char *)"en",(char *)"Debug__B__Ac__Initial",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__endOfRound__Debug__Ac__endOfRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__endOfRound transition Debug__C__endOfRound::Debug__B__Ac__endOfRound,Debug__C__endOfRound::Debug__A__Ac__endOfRound,dbgExec:extComm */
    this->pingsSent = 0;
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__endOfRound::Region1::Debug__Ac__endOfRound",(char *)"Debug__B__Ac__endOfRound",(char *)"Debug__A__Ac__endOfRound",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__endOfRound__Debug__En__WAITING_TO_START( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__endOfRound transition Debug__C__endOfRound::Debug__A__Ac__endOfRound,Debug__C__endOfRound::Debug__A__En__endOfRound,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__endOfRound::Region1::Debug__En__WAITING TO START",(char *)"Debug__A__Ac__endOfRound",(char *)"Debug__A__En__endOfRound",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__endOfRound__Debug__end__trans__endOfRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__endOfRound transition Debug__C__endOfRound::Debug__A__En__endOfRound,Debug__C__endOfRound::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__endOfRound::Region1::Debug__end__trans__endOfRound",(char *)"Debug__A__En__endOfRound",(char *)"ex",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__endOfRound__Debug__init__trans__endOfRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__endOfRound transition Debug__C__endOfRound::en,Debug__C__endOfRound::Debug__B__Ac__endOfRound */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__endOfRound::Region1::Debug__init__trans__endOfRound",(char *)"en",(char *)"Debug__B__Ac__endOfRound",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__keepPlaying__Debug__Ac__keepPlaying( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__keepPlaying transition Debug__C__keepPlaying::Debug__B__Ac__keepPlaying,Debug__C__keepPlaying::Debug__A__Ac__keepPlaying,dbgExec:extComm */
    pingerTimer.informIn(UMLRTTimespec(1,0));
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__keepPlaying::Region1::Debug__Ac__keepPlaying",(char *)"Debug__B__Ac__keepPlaying",(char *)"Debug__A__Ac__keepPlaying",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__keepPlaying__Debug__En__WAITING_FOR_TIMER( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__keepPlaying transition Debug__C__keepPlaying::Debug__A__Ac__keepPlaying,Debug__C__keepPlaying::Debug__A__En__keepPlaying,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__keepPlaying::Region1::Debug__En__WAITING FOR TIMER",(char *)"Debug__A__Ac__keepPlaying",(char *)"Debug__A__En__keepPlaying",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__keepPlaying__Debug__end__trans__keepPlaying( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__keepPlaying transition Debug__C__keepPlaying::Debug__A__En__keepPlaying,Debug__C__keepPlaying::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__keepPlaying::Region1::Debug__end__trans__keepPlaying",(char *)"Debug__A__En__keepPlaying",(char *)"ex",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__keepPlaying__Debug__init__trans__keepPlaying( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__keepPlaying transition Debug__C__keepPlaying::en,Debug__C__keepPlaying::Debug__B__Ac__keepPlaying */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__keepPlaying::Region1::Debug__init__trans__keepPlaying",(char *)"en",(char *)"Debug__B__Ac__keepPlaying",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__onPong__Debug__AC__onPong( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__onPong transition Debug__C__onPong::Debug__B__Ac__onPong,Debug__C__onPong::Debug__A__Ac__onPong,dbgExec:extComm */
    log.show("pong received.\n");
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__onPong::Region1::Debug__AC__onPong",(char *)"Debug__B__Ac__onPong",(char *)"Debug__A__Ac__onPong",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__onPong__Debug__Ex__PLAYING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__onPong transition Debug__C__onPong::Debug__B__Ex__PLAYING,Debug__C__onPong::Debug__B__Ac__onPong,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__onPong::Region1::Debug__Ex__PLAYING",(char *)"Debug__B__Ex__PLAYING",(char *)"Debug__B__Ac__onPong",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__onPong__Debug__end__trans__onPong( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__onPong transition Debug__C__onPong::Debug__A__Ac__onPong,Debug__C__onPong::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__onPong::Region1::Debug__end__trans__onPong",(char *)"Debug__A__Ac__onPong",(char *)"ex",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__startSignal__Debug__AC__startSignal( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__startSignal transition Debug__C__startSignal::Debug__B__Ac__startSignal,Debug__C__startSignal::Debug__A__Ac__startSignal,dbgExec:extComm */
    pingPort.ping().send();
    this->pingsSent++;
    log.show("ping message sent.\n");
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__startSignal::Region1::Debug__AC__startSignal",(char *)"Debug__B__Ac__startSignal",(char *)"Debug__A__Ac__startSignal",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__startSignal__Debug__En__PLAYING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__startSignal transition Debug__C__startSignal::Debug__A__Ac__startSignal,Debug__C__startSignal::Debug__A__En__PLAYING,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__startSignal::Region1::Debug__En__PLAYING",(char *)"Debug__A__Ac__startSignal",(char *)"Debug__A__En__PLAYING",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__startSignal__Debug__Ex__WAITING_TO_START( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__startSignal transition Debug__C__startSignal::Debug__B__Ex__WAITING TO START,Debug__C__startSignal::Debug__B__Ac__startSignal,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__startSignal::Region1::Debug__Ex__WAITING TO START",(char *)"Debug__B__Ex__WAITING TO START",(char *)"Debug__B__Ac__startSignal",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__startSignal__Debug__end__trans__startSignal( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__startSignal transition Debug__C__startSignal::Debug__A__En__PLAYING,Debug__C__startSignal::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__startSignal::Region1::Debug__end__trans__startSignal",(char *)"Debug__A__En__PLAYING",(char *)"ex",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__startSignal__Debug__init__trans__startSignal( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__startSignal transition Debug__C__startSignal::en,Debug__C__startSignal::Debug__B__Ex__WAITING TO START */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__startSignal::Region1::Debug__init__trans__startSignal",(char *)"en",(char *)"Debug__B__Ex__WAITING TO START",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__timeout__Debug__AC__timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__timeout transition Debug__C__timeout::Debug__B__Ac__timeout,Debug__C__timeout::Debug__A__Ac__timeout,dbgExec:extComm */
    pingPort.ping().send();
    this->pingsSent++;
    log.show("ping message sent.\n");
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__timeout::Region1::Debug__AC__timeout",(char *)"Debug__B__Ac__timeout",(char *)"Debug__A__Ac__timeout",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__timeout__Debug__En__PLAYING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__timeout transition Debug__C__timeout::Debug__A__Ac__timeout,Debug__C__timeout::Debug__A__En__PLAYING,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__timeout::Region1::Debug__En__PLAYING",(char *)"Debug__A__Ac__timeout",(char *)"Debug__A__En__PLAYING",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__timeout__Debug__Ex__WAITING_FOR_TIMER( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__timeout transition Debug__C__timeout::Debug__B__Ex__WAITING FOR TIMER,Debug__C__timeout::Debug__B__Ac__timeout,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__timeout::Region1::Debug__Ex__WAITING FOR TIMER",(char *)"Debug__B__Ex__WAITING FOR TIMER",(char *)"Debug__B__Ac__timeout",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__timeout__Debug__end__trans__timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__timeout transition Debug__C__timeout::Debug__A__En__PLAYING,Debug__C__timeout::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__timeout::Region1::Debug__end__trans__timeout",(char *)"Debug__A__En__PLAYING",(char *)"ex",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__C__timeout__Debug__init__trans__timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger::Debug__C__timeout transition Debug__C__timeout::en,Debug__C__timeout::Debug__B__Ex__WAITING FOR TIMER */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__C__timeout::Region1::Debug__init__trans__timeout",(char *)"en",(char *)"Debug__B__Ex__WAITING FOR TIMER",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__InitDebug( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Pseudo3,Debug__InitState */
    std::cout<<this->getName()<<" : is Starting\n";
    this->Debug__SRO.setExecMode(Stepping);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__InitState,Debug__Path__Initial,rtBound:extComm */
    if (this->Debug__SRO.getExecMode()==Stepping){
    Debug__SRO.addTransitionsFromState("","Initial","PLAYING","","");
    Debug__SRO.addTransitionsFromState("WAITING FOR TIMER","timeout","PLAYING","timeout","Timing");
    Debug__SRO.addTransitionsFromState("PLAYING","onPing","WAITING FOR TIMER","ping","PingPongProtocol");
    Debug__SRO.addTransitionsFromState("WAITING TO START","startSignal","PLAYING","start","StartProtocol");
    Debug__SRO.addTransitionsFromState("STARTING ROUND","startRound","WAITING FOR END OF ROUND","timeout","Timing");
    Debug__SRO.addTransitionsFromState("ThreePongsSent?","endOfRound","PLAYING","","");
    Debug__SRO.addTransitionsFromState("WAITING FOR END OF ROUND","endRound","STARTING ROUND","end","endProtocol");
    Debug__SRO.addTransitionsFromState("","Initial","STARTING ROUND","","");
    Debug__SRO.addTransitionsFromState("ThreePingsSent?","keepPlaying","WAITING FOR TIMER","","");
    Debug__SRO.addTransitionsFromState("PLAYING","onPong","ThreePingsSent?","pong","PingPongProtocol");
    Debug__SRO.addTransitionsFromState("ThreePongsSent?","keepPlaying","PLAYING","","");
    Debug__SRO.addTransitionsFromState("WAITING FOR TIMER","timeout","ThreePongsSent?","timeout","Timing");
    Debug__SRO.addTransitionsFromState("ThreePingsSent?","endOfRound","WAITING TO START","","");
    Debug__SRO.addTransitionsFromState("","Initial","WAITING TO START","","");
    std::cout<<this->getName()<<": Connection with debugger is in progress\n";
    char  tempS[256];
    sprintf(tempS,"%s%d",this->getName(),(int)this->getIndex());
    extComm.registerToControl(tempS).send();
    Debug__sendEvent(debugEvents::DEBUG,debugEvents::REGISTER,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"",(char *)"",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__Initial__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__Initial::ex,WAITING TO START */
    this->Debug__recallAllMsg();
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__Initial__E",(char *)"ex",(char *)"WAITING TO START",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__Initial__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__Path__Initial,Debug__C__Initial::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__Initial__S",(char *)"Debug__Path__Initial",(char *)"en",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__Initial__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__Initial::new_exitpoint_24,Debug__C__Initial */
    msg->defer();
    std::cout<<"A message defered"<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__Initial__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__Initial::new_exitpoint_23,Debug__C__Initial */
    this->Debug__SRO.setExecMode((ExecMode)( *(int *)msg->getParam( 0 ) ));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__Initial__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__Initial::new_exitpoint_21,Debug__C__Initial */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.remBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__Initial__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__Initial::new_exitpoint_20,Debug__C__Initial */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.addBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__Initial__dbg__varChange( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__Initial::new_exitpoint_19,Debug__C__Initial */
    char varName1[256];
    char varValue1[1024];
    sprintf(varName1,"%s",(*(const char * *)msg->getParam( 0 )));
    sprintf(varValue1,"%s",(*(const char * *)msg->getParam( 1 )));
    this->Debug__variablesChange(varName1,varValue1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__Initial__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__Initial::new_exitpoint_22,Debug__C__Initial */
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__endOfRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition ThreePingsSent?,Debug__Path__endOfRound */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__endOfRound",(char *)"ThreePingsSent?",(char *)"Debug__Path__endOfRound",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__endOfRound__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__endOfRound::ex,WAITING TO START */
    this->Debug__recallAllMsg();
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__endOfRound__E",(char *)"ex",(char *)"WAITING TO START",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__endOfRound__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__Path__endOfRound,Debug__C__endOfRound::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__endOfRound__S",(char *)"Debug__Path__endOfRound",(char *)"en",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__endOfRound__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__endOfRound::new_exitpoint_6,Debug__C__endOfRound */
    msg->defer();
    std::cout<<"A message defered"<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__endOfRound__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__endOfRound::new_exitpoint_5,Debug__C__endOfRound */
    this->Debug__SRO.setExecMode((ExecMode)( *(int *)msg->getParam( 0 ) ));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__endOfRound__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__endOfRound::new_exitpoint_3,Debug__C__endOfRound */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.remBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__endOfRound__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__endOfRound::new_exitpoint_2,Debug__C__endOfRound */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.addBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__endOfRound__dbg__varChange( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__endOfRound::new_exitpoint_1,Debug__C__endOfRound */
    char varName1[256];
    char varValue1[1024];
    sprintf(varName1,"%s",(*(const char * *)msg->getParam( 0 )));
    sprintf(varValue1,"%s",(*(const char * *)msg->getParam( 1 )));
    this->Debug__variablesChange(varName1,varValue1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__endOfRound__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__endOfRound::new_exitpoint_4,Debug__C__endOfRound */
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__keepPlaying( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition ThreePingsSent?,Debug__Path__keepPlaying */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__keepPlaying",(char *)"ThreePingsSent?",(char *)"Debug__Path__keepPlaying",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__keepPlaying__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__keepPlaying::ex,WAITING FOR TIMER */
    this->Debug__recallAllMsg();
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__keepPlaying__E",(char *)"ex",(char *)"WAITING FOR TIMER",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__keepPlaying__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__Path__keepPlaying,Debug__C__keepPlaying::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__keepPlaying__S",(char *)"Debug__Path__keepPlaying",(char *)"en",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__keepPlaying__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__keepPlaying::new_exitpoint_30,Debug__C__keepPlaying */
    msg->defer();
    std::cout<<"A message defered"<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__keepPlaying__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__keepPlaying::new_exitpoint_29,Debug__C__keepPlaying */
    this->Debug__SRO.setExecMode((ExecMode)( *(int *)msg->getParam( 0 ) ));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__keepPlaying__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__keepPlaying::new_exitpoint_27,Debug__C__keepPlaying */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.remBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__keepPlaying__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__keepPlaying::new_exitpoint_26,Debug__C__keepPlaying */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.addBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__keepPlaying__dbg__varChange( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__keepPlaying::new_exitpoint_25,Debug__C__keepPlaying */
    char varName1[256];
    char varValue1[1024];
    sprintf(varName1,"%s",(*(const char * *)msg->getParam( 0 )));
    sprintf(varValue1,"%s",(*(const char * *)msg->getParam( 1 )));
    this->Debug__variablesChange(varName1,varValue1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__keepPlaying__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__keepPlaying::new_exitpoint_28,Debug__C__keepPlaying */
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__onPong( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition PLAYING,Debug__Path__onPong,pong:pingPort */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__onPong",(char *)"PLAYING",(char *)"Debug__Path__onPong",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__onPong__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__onPong::ex,ThreePingsSent? */
    this->Debug__recallAllMsg();
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__onPong__E",(char *)"ex",(char *)"ThreePingsSent?",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__onPong__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__Path__onPong,Debug__C__onPong::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__onPong__S",(char *)"Debug__Path__onPong",(char *)"en",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__onPong__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__onPong::new_exitpoint_18,Debug__C__onPong */
    msg->defer();
    std::cout<<"A message defered"<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__onPong__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__onPong::new_exitpoint_17,Debug__C__onPong */
    this->Debug__SRO.setExecMode((ExecMode)( *(int *)msg->getParam( 0 ) ));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__onPong__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__onPong::new_exitpoint_15,Debug__C__onPong */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.remBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__onPong__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__onPong::new_exitpoint_14,Debug__C__onPong */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.addBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__onPong__dbg__varChange( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__onPong::new_exitpoint_13,Debug__C__onPong */
    char varName1[256];
    char varValue1[1024];
    sprintf(varName1,"%s",(*(const char * *)msg->getParam( 0 )));
    sprintf(varValue1,"%s",(*(const char * *)msg->getParam( 1 )));
    this->Debug__variablesChange(varName1,varValue1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__onPong__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__onPong::new_exitpoint_16,Debug__C__onPong */
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__startSignal( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition WAITING TO START,Debug__Path__startSignal,start:startPort */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__startSignal",(char *)"WAITING TO START",(char *)"Debug__Path__startSignal",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__startSignal__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__startSignal::ex,PLAYING */
    this->Debug__recallAllMsg();
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__startSignal__E",(char *)"ex",(char *)"PLAYING",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__startSignal__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__Path__startSignal,Debug__C__startSignal::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__startSignal__S",(char *)"Debug__Path__startSignal",(char *)"en",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__startSignal__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__startSignal::new_exitpoint_36,Debug__C__startSignal */
    msg->defer();
    std::cout<<"A message defered"<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__startSignal__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__startSignal::new_exitpoint_35,Debug__C__startSignal */
    this->Debug__SRO.setExecMode((ExecMode)( *(int *)msg->getParam( 0 ) ));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__startSignal__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__startSignal::new_exitpoint_33,Debug__C__startSignal */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.remBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__startSignal__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__startSignal::new_exitpoint_32,Debug__C__startSignal */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.addBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__startSignal__dbg__varChange( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__startSignal::new_exitpoint_31,Debug__C__startSignal */
    char varName1[256];
    char varValue1[1024];
    sprintf(varName1,"%s",(*(const char * *)msg->getParam( 0 )));
    sprintf(varValue1,"%s",(*(const char * *)msg->getParam( 1 )));
    this->Debug__variablesChange(varName1,varValue1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__startSignal__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__startSignal::new_exitpoint_34,Debug__C__startSignal */
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition WAITING FOR TIMER,Debug__Path__timeout,timeout:pingerTimer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),msg->getSignalName(),this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__timeout",(char *)"WAITING FOR TIMER",(char *)"Debug__Path__timeout",msg->signal.getSrcPort()->containerClass->name,msg->signal.getSrcPort()->getName());
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__timeout__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__timeout::ex,PLAYING */
    this->Debug__recallAllMsg();
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__timeout__E",(char *)"ex",(char *)"PLAYING",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__timeout__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__Path__timeout,Debug__C__timeout::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Debug__timeout__S",(char *)"Debug__Path__timeout",(char *)"en",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__timeout__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__timeout::new_exitpoint_12,Debug__C__timeout */
    msg->defer();
    std::cout<<"A message defered"<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__timeout__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__timeout::new_exitpoint_11,Debug__C__timeout */
    this->Debug__SRO.setExecMode((ExecMode)( *(int *)msg->getParam( 0 ) ));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__timeout__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__timeout::new_exitpoint_9,Debug__C__timeout */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.remBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__timeout__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__timeout::new_exitpoint_8,Debug__C__timeout */
    char loc[1024];
    sprintf(loc,"%s",(*(const char * *)msg->getParam( 0 )));
    this->Debug__SRO.addBreakPoint(loc,(BreakPointType)( *(int *)msg->getParam( 1 ) ),( *(int *)msg->getParam( 2 ) ));
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__timeout__dbg__varChange( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__timeout::new_exitpoint_7,Debug__C__timeout */
    char varName1[256];
    char varValue1[1024];
    sprintf(varName1,"%s",(*(const char * *)msg->getParam( 0 )));
    sprintf(varValue1,"%s",(*(const char * *)msg->getParam( 1 )));
    this->Debug__variablesChange(varName1,varValue1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Debug__timeout__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__C__timeout::new_exitpoint_10,Debug__C__timeout */
    std::cout<<this->Debug__SRO.serializeBreakPoint()<<"n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__Path__Initial,WAITING TO START */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::Initial",(char *)"Debug__Path__Initial",(char *)"WAITING TO START",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____endOfRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__Path__endOfRound,WAITING TO START */
    this->pingsSent = 0;
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::endOfRound",(char *)"Debug__Path__endOfRound",(char *)"WAITING TO START",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____keepPlaying( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__Path__keepPlaying,WAITING FOR TIMER */
    pingerTimer.informIn(UMLRTTimespec(1,0));
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::keepPlaying",(char *)"Debug__Path__keepPlaying",(char *)"WAITING FOR TIMER",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____onPong( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__Path__onPong,ThreePingsSent? */
    log.show("pong received.\n");
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::onPong",(char *)"Debug__Path__onPong",(char *)"ThreePingsSent?",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____startSignal( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__Path__startSignal,PLAYING */
    pingPort.ping().send();
    this->pingsSent++;
    log.show("ping message sent.\n");
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::startSignal",(char *)"Debug__Path__startSignal",(char *)"PLAYING",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::transitionaction_____timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger transition Debug__Path__timeout,PLAYING */
    pingPort.ping().send();
    this->pingsSent++;
    log.show("ping message sent.\n");
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONEND,this->getName(),this->getIndex(),(char *)"",this->getTypeName(),(char *)"PingPong::Pinger::StateMachine::Region::timeout",(char *)"Debug__Path__timeout",(char *)"PLAYING",(char *)"null",(char *)"null");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Pinger::guard_____Debug__Initial__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger guard Debug__Path__Initial,Debug__C__Initial::en */
    return Debug__SRO.checkDebug("Pseudo3","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Pinger::guard_____Debug__endOfRound( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger guard ThreePingsSent?,Debug__Path__endOfRound */
    bool threePingsSent = this->pingsSent > 2;
    return threePingsSent;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Pinger::guard_____Debug__endOfRound__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger guard Debug__Path__endOfRound,Debug__C__endOfRound::en */
    return Debug__SRO.checkDebug("ThreePingsSent?","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Pinger::guard_____Debug__keepPlaying__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger guard Debug__Path__keepPlaying,Debug__C__keepPlaying::en */
    return Debug__SRO.checkDebug("ThreePingsSent?","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Pinger::guard_____Debug__onPong__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger guard Debug__Path__onPong,Debug__C__onPong::en */
    return Debug__SRO.checkDebug("PLAYING",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Pinger::guard_____Debug__startSignal__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger guard Debug__Path__startSignal,Debug__C__startSignal::en */
    return Debug__SRO.checkDebug("WAITING TO START",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Pinger::guard_____Debug__timeout__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PingPongReferee/PingPongRef_debug.uml PingPong::Pinger guard Debug__Path__timeout,Debug__C__timeout::en */
    return Debug__SRO.checkDebug("WAITING FOR TIMER",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    transitionaction_____Debug__C__Initial__Debug__Ac__Initial( msg );
    update_state( Debug__C__Initial__Debug__A__Ac__Initial );
    entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__Debug__En__WAITING_TO_START( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    transitionaction_____Debug__C__Initial__Debug__En__WAITING_TO_START( msg );
    update_state( Debug__C__Initial__Debug__A__En__Initial );
    entryaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    update_state( Debug__C__Initial );
    transitionaction_____Debug__C__Initial__Debug__end__trans__Initial( msg );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__Initial__Debug__init__trans__Initial( msg );
    update_state( Debug__C__Initial__Debug__B__Ac__Initial );
    entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_100( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_101( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_102( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_103( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_104( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_105( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_106( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_107( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_108( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_109( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_110( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_111( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_112( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_113( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_114( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_115( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_116( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_117( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_118( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_119( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_120( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_121( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_122( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_123( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial );
    save_history( Debug__C__Initial, Debug__C__Initial__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_95( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial__Debug__B__Ac__Initial );
    entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_96( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial__Debug__A__Ac__Initial );
    entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_97( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial__Debug__A__En__Initial );
    entryaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_98_to_unvisited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__Initial__new_transition_99_to_visited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__Initial__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__Debug__Ac__endOfRound( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    transitionaction_____Debug__C__endOfRound__Debug__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound__Debug__A__Ac__endOfRound );
    entryaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__Debug__En__WAITING_TO_START( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    transitionaction_____Debug__C__endOfRound__Debug__En__WAITING_TO_START( msg );
    update_state( Debug__C__endOfRound__Debug__A__En__endOfRound );
    entryaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__Debug__end__trans__endOfRound( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    transitionaction_____Debug__C__endOfRound__Debug__end__trans__endOfRound( msg );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__En__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__Debug__init__trans__endOfRound( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__endOfRound__Debug__init__trans__endOfRound( msg );
    update_state( Debug__C__endOfRound__Debug__B__Ac__endOfRound );
    entryaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_1( const UMLRTMessage * msg )
{
    update_state( Debug__C__endOfRound__Debug__B__Ac__endOfRound );
    entryaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_10( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__B__Ac__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_11( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__Ac__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_12( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__En__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_13( const UMLRTMessage * msg )
{
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_14( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__B__Ac__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_15( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__Ac__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_16( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__En__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_17( const UMLRTMessage * msg )
{
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_18( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__B__Ac__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_19( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__Ac__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_2( const UMLRTMessage * msg )
{
    update_state( Debug__C__endOfRound__Debug__A__Ac__endOfRound );
    entryaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_20( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__En__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_21( const UMLRTMessage * msg )
{
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_22( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__B__Ac__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_23( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__Ac__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_24( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__En__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_25( const UMLRTMessage * msg )
{
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_26( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__B__Ac__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_27( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__Ac__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_28( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__En__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_29( const UMLRTMessage * msg )
{
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_3( const UMLRTMessage * msg )
{
    update_state( Debug__C__endOfRound__Debug__A__En__endOfRound );
    entryaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_4_to_unvisited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__endOfRound__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_5_to_visited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__endOfRound__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_6( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__B__Ac__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_7( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__Ac__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_8( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( msg );
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__En__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__C__endOfRound__new_transition_9( const UMLRTMessage * msg )
{
    update_state( Debug__C__endOfRound );
    save_history( Debug__C__endOfRound, Debug__C__endOfRound__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__Debug__Ac__keepPlaying( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    transitionaction_____Debug__C__keepPlaying__Debug__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying__Debug__A__Ac__keepPlaying );
    entryaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__Debug__En__WAITING_FOR_TIMER( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    transitionaction_____Debug__C__keepPlaying__Debug__En__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__keepPlaying__Debug__A__En__keepPlaying );
    entryaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__Debug__end__trans__keepPlaying( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    transitionaction_____Debug__C__keepPlaying__Debug__end__trans__keepPlaying( msg );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__En__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__Debug__init__trans__keepPlaying( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__keepPlaying__Debug__init__trans__keepPlaying( msg );
    update_state( Debug__C__keepPlaying__Debug__B__Ac__keepPlaying );
    entryaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_124( const UMLRTMessage * msg )
{
    update_state( Debug__C__keepPlaying__Debug__B__Ac__keepPlaying );
    entryaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_125( const UMLRTMessage * msg )
{
    update_state( Debug__C__keepPlaying__Debug__A__Ac__keepPlaying );
    entryaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_126( const UMLRTMessage * msg )
{
    update_state( Debug__C__keepPlaying__Debug__A__En__keepPlaying );
    entryaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_127_to_unvisited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__keepPlaying__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_128_to_visited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__keepPlaying__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_129( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__B__Ac__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_130( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__Ac__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_131( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__En__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_132( const UMLRTMessage * msg )
{
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_133( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__B__Ac__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_134( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__Ac__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_135( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__En__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_136( const UMLRTMessage * msg )
{
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_137( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__B__Ac__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_138( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__Ac__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_139( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__En__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_140( const UMLRTMessage * msg )
{
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_141( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__B__Ac__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_142( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__Ac__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_143( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__En__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_144( const UMLRTMessage * msg )
{
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_145( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__B__Ac__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_146( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__Ac__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_147( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__En__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_148( const UMLRTMessage * msg )
{
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_149( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__B__Ac__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_150( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__Ac__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_151( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( msg );
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__En__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__C__keepPlaying__new_transition_152( const UMLRTMessage * msg )
{
    update_state( Debug__C__keepPlaying );
    save_history( Debug__C__keepPlaying, Debug__C__keepPlaying__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__Debug__AC__onPong( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPong__Debug__B__Ac__onPong( msg );
    update_state( Debug__C__onPong );
    transitionaction_____Debug__C__onPong__Debug__AC__onPong( msg );
    update_state( Debug__C__onPong__Debug__A__Ac__onPong );
    entryaction_____Debug__C__onPong__Debug__A__Ac__onPong( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__Debug__Ex__PLAYING( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPong__Debug__B__Ex__PLAYING( msg );
    update_state( Debug__C__onPong );
    transitionaction_____Debug__C__onPong__Debug__Ex__PLAYING( msg );
    update_state( Debug__C__onPong__Debug__B__Ac__onPong );
    entryaction_____Debug__C__onPong__Debug__B__Ac__onPong( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__Debug__end__trans__onPong( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPong__Debug__A__Ac__onPong( msg );
    update_state( Debug__C__onPong );
    transitionaction_____Debug__C__onPong__Debug__end__trans__onPong( msg );
    save_history( Debug__C__onPong, Debug__C__onPong__Debug__A__Ac__onPong );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__Debug__init__trans__onPong( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPong__Debug__B__Ex__PLAYING );
    entryaction_____Debug__C__onPong__Debug__B__Ex__PLAYING( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_66( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPong__Debug__B__Ex__PLAYING );
    entryaction_____Debug__C__onPong__Debug__B__Ex__PLAYING( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_67( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPong__Debug__B__Ac__onPong );
    entryaction_____Debug__C__onPong__Debug__B__Ac__onPong( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_68( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPong__Debug__A__Ac__onPong );
    entryaction_____Debug__C__onPong__Debug__A__Ac__onPong( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_69_to_unvisited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPong__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_70_to_visited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPong__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_71( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPong__Debug__B__Ex__PLAYING( msg );
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__Debug__B__Ex__PLAYING );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_72( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPong__Debug__B__Ac__onPong( msg );
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__Debug__B__Ac__onPong );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_73( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPong__Debug__A__Ac__onPong( msg );
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__Debug__A__Ac__onPong );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_74( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_75( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPong__Debug__B__Ex__PLAYING( msg );
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__Debug__B__Ex__PLAYING );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_76( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPong__Debug__B__Ac__onPong( msg );
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__Debug__B__Ac__onPong );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_77( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPong__Debug__A__Ac__onPong( msg );
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__Debug__A__Ac__onPong );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_78( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_79( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPong__Debug__B__Ex__PLAYING( msg );
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__Debug__B__Ex__PLAYING );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_80( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPong__Debug__B__Ac__onPong( msg );
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__Debug__B__Ac__onPong );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_81( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPong__Debug__A__Ac__onPong( msg );
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__Debug__A__Ac__onPong );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_82( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_83( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPong__Debug__B__Ex__PLAYING( msg );
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__Debug__B__Ex__PLAYING );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_84( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPong__Debug__B__Ac__onPong( msg );
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__Debug__B__Ac__onPong );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_85( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPong__Debug__A__Ac__onPong( msg );
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__Debug__A__Ac__onPong );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_86( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_87( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPong__Debug__B__Ex__PLAYING( msg );
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__Debug__B__Ex__PLAYING );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_88( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPong__Debug__B__Ac__onPong( msg );
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__Debug__B__Ac__onPong );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_89( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPong__Debug__A__Ac__onPong( msg );
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__Debug__A__Ac__onPong );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_90( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_91( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPong__Debug__B__Ex__PLAYING( msg );
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__Debug__B__Ex__PLAYING );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_92( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPong__Debug__B__Ac__onPong( msg );
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__Debug__B__Ac__onPong );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_93( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__onPong__Debug__A__Ac__onPong( msg );
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__Debug__A__Ac__onPong );
}

void Capsule_Pinger::actionchain_____Debug__C__onPong__new_transition_94( const UMLRTMessage * msg )
{
    update_state( Debug__C__onPong );
    save_history( Debug__C__onPong, Debug__C__onPong__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__Debug__AC__startSignal( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__B__Ac__startSignal( msg );
    update_state( Debug__C__startSignal );
    transitionaction_____Debug__C__startSignal__Debug__AC__startSignal( msg );
    update_state( Debug__C__startSignal__Debug__A__Ac__startSignal );
    entryaction_____Debug__C__startSignal__Debug__A__Ac__startSignal( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__Debug__En__PLAYING( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__A__Ac__startSignal( msg );
    update_state( Debug__C__startSignal );
    transitionaction_____Debug__C__startSignal__Debug__En__PLAYING( msg );
    update_state( Debug__C__startSignal__Debug__A__En__PLAYING );
    entryaction_____Debug__C__startSignal__Debug__A__En__PLAYING( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__Debug__Ex__WAITING_TO_START( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START( msg );
    update_state( Debug__C__startSignal );
    transitionaction_____Debug__C__startSignal__Debug__Ex__WAITING_TO_START( msg );
    update_state( Debug__C__startSignal__Debug__B__Ac__startSignal );
    entryaction_____Debug__C__startSignal__Debug__B__Ac__startSignal( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__Debug__end__trans__startSignal( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__A__En__PLAYING( msg );
    update_state( Debug__C__startSignal );
    transitionaction_____Debug__C__startSignal__Debug__end__trans__startSignal( msg );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__A__En__PLAYING );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__Debug__init__trans__startSignal( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__startSignal__Debug__init__trans__startSignal( msg );
    update_state( Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START );
    entryaction_____Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_153( const UMLRTMessage * msg )
{
    update_state( Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START );
    entryaction_____Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_154( const UMLRTMessage * msg )
{
    update_state( Debug__C__startSignal__Debug__B__Ac__startSignal );
    entryaction_____Debug__C__startSignal__Debug__B__Ac__startSignal( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_155( const UMLRTMessage * msg )
{
    update_state( Debug__C__startSignal__Debug__A__Ac__startSignal );
    entryaction_____Debug__C__startSignal__Debug__A__Ac__startSignal( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_156( const UMLRTMessage * msg )
{
    update_state( Debug__C__startSignal__Debug__A__En__PLAYING );
    entryaction_____Debug__C__startSignal__Debug__A__En__PLAYING( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_157_to_unvisited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__startSignal__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_158_to_visited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__startSignal__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_159( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_160( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__B__Ac__startSignal( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__B__Ac__startSignal );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_161( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__A__Ac__startSignal( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__A__Ac__startSignal );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_162( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__A__En__PLAYING( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__A__En__PLAYING );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_163( const UMLRTMessage * msg )
{
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_164( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_165( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__B__Ac__startSignal( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__B__Ac__startSignal );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_166( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__A__Ac__startSignal( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__A__Ac__startSignal );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_167( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__A__En__PLAYING( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__A__En__PLAYING );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_168( const UMLRTMessage * msg )
{
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_169( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_170( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__B__Ac__startSignal( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__B__Ac__startSignal );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_171( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__A__Ac__startSignal( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__A__Ac__startSignal );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_172( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__A__En__PLAYING( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__A__En__PLAYING );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_173( const UMLRTMessage * msg )
{
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_174( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_175( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__B__Ac__startSignal( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__B__Ac__startSignal );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_176( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__A__Ac__startSignal( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__A__Ac__startSignal );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_177( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__A__En__PLAYING( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__A__En__PLAYING );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_178( const UMLRTMessage * msg )
{
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_179( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_180( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__B__Ac__startSignal( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__B__Ac__startSignal );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_181( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__A__Ac__startSignal( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__A__Ac__startSignal );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_182( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__A__En__PLAYING( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__A__En__PLAYING );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_183( const UMLRTMessage * msg )
{
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_184( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_185( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__B__Ac__startSignal( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__B__Ac__startSignal );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_186( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__A__Ac__startSignal( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__A__Ac__startSignal );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_187( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__startSignal__Debug__A__En__PLAYING( msg );
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__Debug__A__En__PLAYING );
}

void Capsule_Pinger::actionchain_____Debug__C__startSignal__new_transition_188( const UMLRTMessage * msg )
{
    update_state( Debug__C__startSignal );
    save_history( Debug__C__startSignal, Debug__C__startSignal__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__Debug__AC__timeout( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    transitionaction_____Debug__C__timeout__Debug__AC__timeout( msg );
    update_state( Debug__C__timeout__Debug__A__Ac__timeout );
    entryaction_____Debug__C__timeout__Debug__A__Ac__timeout( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__Debug__En__PLAYING( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    transitionaction_____Debug__C__timeout__Debug__En__PLAYING( msg );
    update_state( Debug__C__timeout__Debug__A__En__PLAYING );
    entryaction_____Debug__C__timeout__Debug__A__En__PLAYING( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__Debug__Ex__WAITING_FOR_TIMER( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__timeout );
    transitionaction_____Debug__C__timeout__Debug__Ex__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__timeout__Debug__B__Ac__timeout );
    entryaction_____Debug__C__timeout__Debug__B__Ac__timeout( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__Debug__end__trans__timeout( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__En__PLAYING( msg );
    update_state( Debug__C__timeout );
    transitionaction_____Debug__C__timeout__Debug__end__trans__timeout( msg );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__A__En__PLAYING );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__Debug__init__trans__timeout( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__timeout__Debug__init__trans__timeout( msg );
    update_state( Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER );
    entryaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_30( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER );
    entryaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_31( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout__Debug__B__Ac__timeout );
    entryaction_____Debug__C__timeout__Debug__B__Ac__timeout( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_32( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout__Debug__A__Ac__timeout );
    entryaction_____Debug__C__timeout__Debug__A__Ac__timeout( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_33( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout__Debug__A__En__PLAYING );
    entryaction_____Debug__C__timeout__Debug__A__En__PLAYING( msg );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_34_to_unvisited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_35_to_visited_boundary( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_36( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_37( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ac__timeout );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_38( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__A__Ac__timeout );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_39( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__En__PLAYING( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__A__En__PLAYING );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_40( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_41( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_42( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ac__timeout );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_43( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__A__Ac__timeout );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_44( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__En__PLAYING( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__A__En__PLAYING );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_45( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_46( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_47( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ac__timeout );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_48( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__A__Ac__timeout );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_49( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__En__PLAYING( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__A__En__PLAYING );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_50( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_51( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_52( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ac__timeout );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_53( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__A__Ac__timeout );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_54( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__En__PLAYING( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__A__En__PLAYING );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_55( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_56( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_57( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ac__timeout );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_58( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__A__Ac__timeout );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_59( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__En__PLAYING( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__A__En__PLAYING );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_60( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__boundary );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_61( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_62( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__B__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__B__Ac__timeout );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_63( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__Ac__timeout( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__A__Ac__timeout );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_64( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__timeout__Debug__A__En__PLAYING( msg );
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__Debug__A__En__PLAYING );
}

void Capsule_Pinger::actionchain_____Debug__C__timeout__new_transition_65( const UMLRTMessage * msg )
{
    update_state( Debug__C__timeout );
    save_history( Debug__C__timeout, Debug__C__timeout__boundary );
}

void Capsule_Pinger::actionchain_____Debug__InitDebug( const UMLRTMessage * msg )
{
    transitionaction_____Debug__InitDebug( msg );
    update_state( Debug__InitState );
}

void Capsule_Pinger::actionchain_____Debug__Initial( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial( msg );
}

void Capsule_Pinger::actionchain_____Debug__Initial__E( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial__E( msg );
    update_state( WAITING_TO_START );
    entryaction_____WAITING_TO_START( msg );
}

void Capsule_Pinger::actionchain_____Debug__Initial__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__Initial__S( msg );
    update_state( Debug__C__Initial );
}

void Capsule_Pinger::actionchain_____Debug__Initial__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial__dbg__dbgDeferMsg( msg );
    update_state( Debug__C__Initial );
}

void Capsule_Pinger::actionchain_____Debug__Initial__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial__dbg__dbgSetExecMode( msg );
    update_state( Debug__C__Initial );
}

void Capsule_Pinger::actionchain_____Debug__Initial__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial__dbg__remBreakPoint( msg );
    update_state( Debug__C__Initial );
}

void Capsule_Pinger::actionchain_____Debug__Initial__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial__dbg__setBreakPoint( msg );
    update_state( Debug__C__Initial );
}

void Capsule_Pinger::actionchain_____Debug__Initial__dbg__varChange( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial__dbg__varChange( msg );
    update_state( Debug__C__Initial );
}

void Capsule_Pinger::actionchain_____Debug__Initial__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__Initial__dbg__viewBreakPoints( msg );
    update_state( Debug__C__Initial );
}

void Capsule_Pinger::actionchain_____Debug__endOfRound( const UMLRTMessage * msg )
{
    transitionaction_____Debug__endOfRound( msg );
}

void Capsule_Pinger::actionchain_____Debug__endOfRound__E( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__endOfRound__E( msg );
    update_state( WAITING_TO_START );
    entryaction_____WAITING_TO_START( msg );
}

void Capsule_Pinger::actionchain_____Debug__endOfRound__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__endOfRound__S( msg );
    update_state( Debug__C__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__endOfRound__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__endOfRound__dbg__dbgDeferMsg( msg );
    update_state( Debug__C__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__endOfRound__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__endOfRound__dbg__dbgSetExecMode( msg );
    update_state( Debug__C__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__endOfRound__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__endOfRound__dbg__remBreakPoint( msg );
    update_state( Debug__C__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__endOfRound__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__endOfRound__dbg__setBreakPoint( msg );
    update_state( Debug__C__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__endOfRound__dbg__varChange( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__endOfRound__dbg__varChange( msg );
    update_state( Debug__C__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__endOfRound__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__endOfRound__dbg__viewBreakPoints( msg );
    update_state( Debug__C__endOfRound );
}

void Capsule_Pinger::actionchain_____Debug__keepPlaying( const UMLRTMessage * msg )
{
    transitionaction_____Debug__keepPlaying( msg );
}

void Capsule_Pinger::actionchain_____Debug__keepPlaying__E( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__keepPlaying__E( msg );
    update_state( WAITING_FOR_TIMER );
    entryaction_____WAITING_FOR_TIMER( msg );
}

void Capsule_Pinger::actionchain_____Debug__keepPlaying__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__keepPlaying__S( msg );
    update_state( Debug__C__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__keepPlaying__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__keepPlaying__dbg__dbgDeferMsg( msg );
    update_state( Debug__C__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__keepPlaying__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__keepPlaying__dbg__dbgSetExecMode( msg );
    update_state( Debug__C__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__keepPlaying__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__keepPlaying__dbg__remBreakPoint( msg );
    update_state( Debug__C__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__keepPlaying__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__keepPlaying__dbg__setBreakPoint( msg );
    update_state( Debug__C__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__keepPlaying__dbg__varChange( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__keepPlaying__dbg__varChange( msg );
    update_state( Debug__C__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__keepPlaying__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__keepPlaying__dbg__viewBreakPoints( msg );
    update_state( Debug__C__keepPlaying );
}

void Capsule_Pinger::actionchain_____Debug__onPong( const UMLRTMessage * msg )
{
    exitaction_____PLAYING( msg );
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__onPong( msg );
}

void Capsule_Pinger::actionchain_____Debug__onPong__E( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__onPong__E( msg );
}

void Capsule_Pinger::actionchain_____Debug__onPong__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__onPong__S( msg );
    update_state( Debug__C__onPong );
}

void Capsule_Pinger::actionchain_____Debug__onPong__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__onPong__dbg__dbgDeferMsg( msg );
    update_state( Debug__C__onPong );
}

void Capsule_Pinger::actionchain_____Debug__onPong__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__onPong__dbg__dbgSetExecMode( msg );
    update_state( Debug__C__onPong );
}

void Capsule_Pinger::actionchain_____Debug__onPong__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__onPong__dbg__remBreakPoint( msg );
    update_state( Debug__C__onPong );
}

void Capsule_Pinger::actionchain_____Debug__onPong__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__onPong__dbg__setBreakPoint( msg );
    update_state( Debug__C__onPong );
}

void Capsule_Pinger::actionchain_____Debug__onPong__dbg__varChange( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__onPong__dbg__varChange( msg );
    update_state( Debug__C__onPong );
}

void Capsule_Pinger::actionchain_____Debug__onPong__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__onPong__dbg__viewBreakPoints( msg );
    update_state( Debug__C__onPong );
}

void Capsule_Pinger::actionchain_____Debug__startSignal( const UMLRTMessage * msg )
{
    exitaction_____WAITING_TO_START( msg );
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__startSignal( msg );
}

void Capsule_Pinger::actionchain_____Debug__startSignal__E( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__startSignal__E( msg );
    update_state( PLAYING );
    entryaction_____PLAYING( msg );
}

void Capsule_Pinger::actionchain_____Debug__startSignal__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__startSignal__S( msg );
    update_state( Debug__C__startSignal );
}

void Capsule_Pinger::actionchain_____Debug__startSignal__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__startSignal__dbg__dbgDeferMsg( msg );
    update_state( Debug__C__startSignal );
}

void Capsule_Pinger::actionchain_____Debug__startSignal__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__startSignal__dbg__dbgSetExecMode( msg );
    update_state( Debug__C__startSignal );
}

void Capsule_Pinger::actionchain_____Debug__startSignal__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__startSignal__dbg__remBreakPoint( msg );
    update_state( Debug__C__startSignal );
}

void Capsule_Pinger::actionchain_____Debug__startSignal__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__startSignal__dbg__setBreakPoint( msg );
    update_state( Debug__C__startSignal );
}

void Capsule_Pinger::actionchain_____Debug__startSignal__dbg__varChange( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__startSignal__dbg__varChange( msg );
    update_state( Debug__C__startSignal );
}

void Capsule_Pinger::actionchain_____Debug__startSignal__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__startSignal__dbg__viewBreakPoints( msg );
    update_state( Debug__C__startSignal );
}

void Capsule_Pinger::actionchain_____Debug__timeout( const UMLRTMessage * msg )
{
    exitaction_____WAITING_FOR_TIMER( msg );
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__timeout( msg );
}

void Capsule_Pinger::actionchain_____Debug__timeout__E( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__timeout__E( msg );
    update_state( PLAYING );
    entryaction_____PLAYING( msg );
}

void Capsule_Pinger::actionchain_____Debug__timeout__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__timeout__S( msg );
    update_state( Debug__C__timeout );
}

void Capsule_Pinger::actionchain_____Debug__timeout__dbg__dbgDeferMsg( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__timeout__dbg__dbgDeferMsg( msg );
    update_state( Debug__C__timeout );
}

void Capsule_Pinger::actionchain_____Debug__timeout__dbg__dbgSetExecMode( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__timeout__dbg__dbgSetExecMode( msg );
    update_state( Debug__C__timeout );
}

void Capsule_Pinger::actionchain_____Debug__timeout__dbg__remBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__timeout__dbg__remBreakPoint( msg );
    update_state( Debug__C__timeout );
}

void Capsule_Pinger::actionchain_____Debug__timeout__dbg__setBreakPoint( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__timeout__dbg__setBreakPoint( msg );
    update_state( Debug__C__timeout );
}

void Capsule_Pinger::actionchain_____Debug__timeout__dbg__varChange( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__timeout__dbg__varChange( msg );
    update_state( Debug__C__timeout );
}

void Capsule_Pinger::actionchain_____Debug__timeout__dbg__viewBreakPoints( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____Debug__timeout__dbg__viewBreakPoints( msg );
    update_state( Debug__C__timeout );
}

void Capsule_Pinger::actionchain_____Initial( const UMLRTMessage * msg )
{
    transitionaction_____Initial( msg );
    update_state( WAITING_TO_START );
    entryaction_____WAITING_TO_START( msg );
}

void Capsule_Pinger::actionchain_____endOfRound( const UMLRTMessage * msg )
{
    transitionaction_____endOfRound( msg );
    update_state( WAITING_TO_START );
    entryaction_____WAITING_TO_START( msg );
}

void Capsule_Pinger::actionchain_____keepPlaying( const UMLRTMessage * msg )
{
    transitionaction_____keepPlaying( msg );
    update_state( WAITING_FOR_TIMER );
    entryaction_____WAITING_FOR_TIMER( msg );
}

void Capsule_Pinger::actionchain_____onPong( const UMLRTMessage * msg )
{
    transitionaction_____onPong( msg );
}

void Capsule_Pinger::actionchain_____startSignal( const UMLRTMessage * msg )
{
    transitionaction_____startSignal( msg );
    update_state( PLAYING );
    entryaction_____PLAYING( msg );
}

void Capsule_Pinger::actionchain_____timeout( const UMLRTMessage * msg )
{
    transitionaction_____timeout( msg );
    update_state( PLAYING );
    entryaction_____PLAYING( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__Initial__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__Initial__Debug__init__trans__Initial( msg );
    return Debug__C__Initial__Debug__B__Ac__Initial;
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__Initial__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__E( msg );
    return WAITING_TO_START;
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__Initial__new_exitpoint_19( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__dbg__varChange( msg );
    return choice_____Debug__C__Initial__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__Initial__new_exitpoint_20( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__dbg__setBreakPoint( msg );
    return choice_____Debug__C__Initial__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__Initial__new_exitpoint_21( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__dbg__remBreakPoint( msg );
    return choice_____Debug__C__Initial__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__Initial__new_exitpoint_22( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__dbg__viewBreakPoints( msg );
    return choice_____Debug__C__Initial__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__Initial__new_exitpoint_23( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__dbg__dbgSetExecMode( msg );
    return choice_____Debug__C__Initial__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__Initial__new_exitpoint_24( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__dbg__dbgDeferMsg( msg );
    return choice_____Debug__C__Initial__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__endOfRound__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__endOfRound__Debug__init__trans__endOfRound( msg );
    return Debug__C__endOfRound__Debug__B__Ac__endOfRound;
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__endOfRound__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__endOfRound__E( msg );
    return WAITING_TO_START;
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__endOfRound__new_exitpoint_1( const UMLRTMessage * msg )
{
    actionchain_____Debug__endOfRound__dbg__varChange( msg );
    return choice_____Debug__C__endOfRound__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__endOfRound__new_exitpoint_2( const UMLRTMessage * msg )
{
    actionchain_____Debug__endOfRound__dbg__setBreakPoint( msg );
    return choice_____Debug__C__endOfRound__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__endOfRound__new_exitpoint_3( const UMLRTMessage * msg )
{
    actionchain_____Debug__endOfRound__dbg__remBreakPoint( msg );
    return choice_____Debug__C__endOfRound__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__endOfRound__new_exitpoint_4( const UMLRTMessage * msg )
{
    actionchain_____Debug__endOfRound__dbg__viewBreakPoints( msg );
    return choice_____Debug__C__endOfRound__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__endOfRound__new_exitpoint_5( const UMLRTMessage * msg )
{
    actionchain_____Debug__endOfRound__dbg__dbgSetExecMode( msg );
    return choice_____Debug__C__endOfRound__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__endOfRound__new_exitpoint_6( const UMLRTMessage * msg )
{
    actionchain_____Debug__endOfRound__dbg__dbgDeferMsg( msg );
    return choice_____Debug__C__endOfRound__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__keepPlaying__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__keepPlaying__Debug__init__trans__keepPlaying( msg );
    return Debug__C__keepPlaying__Debug__B__Ac__keepPlaying;
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__keepPlaying__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__keepPlaying__E( msg );
    return WAITING_FOR_TIMER;
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__keepPlaying__new_exitpoint_25( const UMLRTMessage * msg )
{
    actionchain_____Debug__keepPlaying__dbg__varChange( msg );
    return choice_____Debug__C__keepPlaying__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__keepPlaying__new_exitpoint_26( const UMLRTMessage * msg )
{
    actionchain_____Debug__keepPlaying__dbg__setBreakPoint( msg );
    return choice_____Debug__C__keepPlaying__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__keepPlaying__new_exitpoint_27( const UMLRTMessage * msg )
{
    actionchain_____Debug__keepPlaying__dbg__remBreakPoint( msg );
    return choice_____Debug__C__keepPlaying__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__keepPlaying__new_exitpoint_28( const UMLRTMessage * msg )
{
    actionchain_____Debug__keepPlaying__dbg__viewBreakPoints( msg );
    return choice_____Debug__C__keepPlaying__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__keepPlaying__new_exitpoint_29( const UMLRTMessage * msg )
{
    actionchain_____Debug__keepPlaying__dbg__dbgSetExecMode( msg );
    return choice_____Debug__C__keepPlaying__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__keepPlaying__new_exitpoint_30( const UMLRTMessage * msg )
{
    actionchain_____Debug__keepPlaying__dbg__dbgDeferMsg( msg );
    return choice_____Debug__C__keepPlaying__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__onPong__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__onPong__Debug__init__trans__onPong( msg );
    return Debug__C__onPong__Debug__B__Ex__PLAYING;
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__onPong__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__onPong__E( msg );
    return choice_____ThreePingsSent_( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__onPong__new_exitpoint_13( const UMLRTMessage * msg )
{
    actionchain_____Debug__onPong__dbg__varChange( msg );
    return choice_____Debug__C__onPong__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__onPong__new_exitpoint_14( const UMLRTMessage * msg )
{
    actionchain_____Debug__onPong__dbg__setBreakPoint( msg );
    return choice_____Debug__C__onPong__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__onPong__new_exitpoint_15( const UMLRTMessage * msg )
{
    actionchain_____Debug__onPong__dbg__remBreakPoint( msg );
    return choice_____Debug__C__onPong__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__onPong__new_exitpoint_16( const UMLRTMessage * msg )
{
    actionchain_____Debug__onPong__dbg__viewBreakPoints( msg );
    return choice_____Debug__C__onPong__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__onPong__new_exitpoint_17( const UMLRTMessage * msg )
{
    actionchain_____Debug__onPong__dbg__dbgSetExecMode( msg );
    return choice_____Debug__C__onPong__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__onPong__new_exitpoint_18( const UMLRTMessage * msg )
{
    actionchain_____Debug__onPong__dbg__dbgDeferMsg( msg );
    return choice_____Debug__C__onPong__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__startSignal__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__startSignal__Debug__init__trans__startSignal( msg );
    return Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START;
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__startSignal__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__startSignal__E( msg );
    return PLAYING;
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__startSignal__new_exitpoint_31( const UMLRTMessage * msg )
{
    actionchain_____Debug__startSignal__dbg__varChange( msg );
    return choice_____Debug__C__startSignal__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__startSignal__new_exitpoint_32( const UMLRTMessage * msg )
{
    actionchain_____Debug__startSignal__dbg__setBreakPoint( msg );
    return choice_____Debug__C__startSignal__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__startSignal__new_exitpoint_33( const UMLRTMessage * msg )
{
    actionchain_____Debug__startSignal__dbg__remBreakPoint( msg );
    return choice_____Debug__C__startSignal__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__startSignal__new_exitpoint_34( const UMLRTMessage * msg )
{
    actionchain_____Debug__startSignal__dbg__viewBreakPoints( msg );
    return choice_____Debug__C__startSignal__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__startSignal__new_exitpoint_35( const UMLRTMessage * msg )
{
    actionchain_____Debug__startSignal__dbg__dbgSetExecMode( msg );
    return choice_____Debug__C__startSignal__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__startSignal__new_exitpoint_36( const UMLRTMessage * msg )
{
    actionchain_____Debug__startSignal__dbg__dbgDeferMsg( msg );
    return choice_____Debug__C__startSignal__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__timeout__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__timeout__Debug__init__trans__timeout( msg );
    return Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER;
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__timeout__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__timeout__E( msg );
    return PLAYING;
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__timeout__new_exitpoint_10( const UMLRTMessage * msg )
{
    actionchain_____Debug__timeout__dbg__viewBreakPoints( msg );
    return choice_____Debug__C__timeout__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__timeout__new_exitpoint_11( const UMLRTMessage * msg )
{
    actionchain_____Debug__timeout__dbg__dbgSetExecMode( msg );
    return choice_____Debug__C__timeout__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__timeout__new_exitpoint_12( const UMLRTMessage * msg )
{
    actionchain_____Debug__timeout__dbg__dbgDeferMsg( msg );
    return choice_____Debug__C__timeout__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__timeout__new_exitpoint_7( const UMLRTMessage * msg )
{
    actionchain_____Debug__timeout__dbg__varChange( msg );
    return choice_____Debug__C__timeout__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__timeout__new_exitpoint_8( const UMLRTMessage * msg )
{
    actionchain_____Debug__timeout__dbg__setBreakPoint( msg );
    return choice_____Debug__C__timeout__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::junction_____Debug__C__timeout__new_exitpoint_9( const UMLRTMessage * msg )
{
    actionchain_____Debug__timeout__dbg__remBreakPoint( msg );
    return choice_____Debug__C__timeout__deephistory( msg );
}

Capsule_Pinger::State Capsule_Pinger::choice_____Debug__C__Initial__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial ) )
    {
        actionchain_____Debug__C__Initial__new_transition_95( msg );
        return Debug__C__Initial__Debug__B__Ac__Initial;
    }
    else if( check_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial ) )
    {
        actionchain_____Debug__C__Initial__new_transition_96( msg );
        return Debug__C__Initial__Debug__A__Ac__Initial;
    }
    else if( check_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial ) )
    {
        actionchain_____Debug__C__Initial__new_transition_97( msg );
        return Debug__C__Initial__Debug__A__En__Initial;
    }
    else if( check_history( Debug__C__Initial, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__Initial__new_transition_98_to_unvisited_boundary( msg );
        return Debug__C__Initial__boundary;
    }
    else if( check_history( Debug__C__Initial, Debug__C__Initial__boundary ) )
    {
        actionchain_____Debug__C__Initial__new_transition_99_to_visited_boundary( msg );
        return Debug__C__Initial__boundary;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::choice_____Debug__C__endOfRound__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__B__Ac__endOfRound ) )
    {
        actionchain_____Debug__C__endOfRound__new_transition_1( msg );
        return Debug__C__endOfRound__Debug__B__Ac__endOfRound;
    }
    else if( check_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__Ac__endOfRound ) )
    {
        actionchain_____Debug__C__endOfRound__new_transition_2( msg );
        return Debug__C__endOfRound__Debug__A__Ac__endOfRound;
    }
    else if( check_history( Debug__C__endOfRound, Debug__C__endOfRound__Debug__A__En__endOfRound ) )
    {
        actionchain_____Debug__C__endOfRound__new_transition_3( msg );
        return Debug__C__endOfRound__Debug__A__En__endOfRound;
    }
    else if( check_history( Debug__C__endOfRound, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__endOfRound__new_transition_4_to_unvisited_boundary( msg );
        return Debug__C__endOfRound__boundary;
    }
    else if( check_history( Debug__C__endOfRound, Debug__C__endOfRound__boundary ) )
    {
        actionchain_____Debug__C__endOfRound__new_transition_5_to_visited_boundary( msg );
        return Debug__C__endOfRound__boundary;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::choice_____Debug__C__keepPlaying__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__B__Ac__keepPlaying ) )
    {
        actionchain_____Debug__C__keepPlaying__new_transition_124( msg );
        return Debug__C__keepPlaying__Debug__B__Ac__keepPlaying;
    }
    else if( check_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__Ac__keepPlaying ) )
    {
        actionchain_____Debug__C__keepPlaying__new_transition_125( msg );
        return Debug__C__keepPlaying__Debug__A__Ac__keepPlaying;
    }
    else if( check_history( Debug__C__keepPlaying, Debug__C__keepPlaying__Debug__A__En__keepPlaying ) )
    {
        actionchain_____Debug__C__keepPlaying__new_transition_126( msg );
        return Debug__C__keepPlaying__Debug__A__En__keepPlaying;
    }
    else if( check_history( Debug__C__keepPlaying, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__keepPlaying__new_transition_127_to_unvisited_boundary( msg );
        return Debug__C__keepPlaying__boundary;
    }
    else if( check_history( Debug__C__keepPlaying, Debug__C__keepPlaying__boundary ) )
    {
        actionchain_____Debug__C__keepPlaying__new_transition_128_to_visited_boundary( msg );
        return Debug__C__keepPlaying__boundary;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::choice_____Debug__C__onPong__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__onPong, Debug__C__onPong__Debug__B__Ex__PLAYING ) )
    {
        actionchain_____Debug__C__onPong__new_transition_66( msg );
        return Debug__C__onPong__Debug__B__Ex__PLAYING;
    }
    else if( check_history( Debug__C__onPong, Debug__C__onPong__Debug__B__Ac__onPong ) )
    {
        actionchain_____Debug__C__onPong__new_transition_67( msg );
        return Debug__C__onPong__Debug__B__Ac__onPong;
    }
    else if( check_history( Debug__C__onPong, Debug__C__onPong__Debug__A__Ac__onPong ) )
    {
        actionchain_____Debug__C__onPong__new_transition_68( msg );
        return Debug__C__onPong__Debug__A__Ac__onPong;
    }
    else if( check_history( Debug__C__onPong, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__onPong__new_transition_69_to_unvisited_boundary( msg );
        return Debug__C__onPong__boundary;
    }
    else if( check_history( Debug__C__onPong, Debug__C__onPong__boundary ) )
    {
        actionchain_____Debug__C__onPong__new_transition_70_to_visited_boundary( msg );
        return Debug__C__onPong__boundary;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::choice_____Debug__C__startSignal__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__startSignal, Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START ) )
    {
        actionchain_____Debug__C__startSignal__new_transition_153( msg );
        return Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START;
    }
    else if( check_history( Debug__C__startSignal, Debug__C__startSignal__Debug__B__Ac__startSignal ) )
    {
        actionchain_____Debug__C__startSignal__new_transition_154( msg );
        return Debug__C__startSignal__Debug__B__Ac__startSignal;
    }
    else if( check_history( Debug__C__startSignal, Debug__C__startSignal__Debug__A__Ac__startSignal ) )
    {
        actionchain_____Debug__C__startSignal__new_transition_155( msg );
        return Debug__C__startSignal__Debug__A__Ac__startSignal;
    }
    else if( check_history( Debug__C__startSignal, Debug__C__startSignal__Debug__A__En__PLAYING ) )
    {
        actionchain_____Debug__C__startSignal__new_transition_156( msg );
        return Debug__C__startSignal__Debug__A__En__PLAYING;
    }
    else if( check_history( Debug__C__startSignal, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__startSignal__new_transition_157_to_unvisited_boundary( msg );
        return Debug__C__startSignal__boundary;
    }
    else if( check_history( Debug__C__startSignal, Debug__C__startSignal__boundary ) )
    {
        actionchain_____Debug__C__startSignal__new_transition_158_to_visited_boundary( msg );
        return Debug__C__startSignal__boundary;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::choice_____Debug__C__timeout__deephistory( const UMLRTMessage * msg )
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
    else if( check_history( Debug__C__timeout, Debug__C__timeout__Debug__A__En__PLAYING ) )
    {
        actionchain_____Debug__C__timeout__new_transition_33( msg );
        return Debug__C__timeout__Debug__A__En__PLAYING;
    }
    else if( check_history( Debug__C__timeout, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__timeout__new_transition_34_to_unvisited_boundary( msg );
        return Debug__C__timeout__boundary;
    }
    else if( check_history( Debug__C__timeout, Debug__C__timeout__boundary ) )
    {
        actionchain_____Debug__C__timeout__new_transition_35_to_visited_boundary( msg );
        return Debug__C__timeout__boundary;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::choice_____Debug__Path__Initial( const UMLRTMessage * msg )
{
    if( guard_____Debug__Initial__S( msg ) )
    {
        actionchain_____Debug__Initial__S( msg );
        return junction_____Debug__C__Initial__en( msg );
    }
    else
    {
        actionchain_____Initial( msg );
        return WAITING_TO_START;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::choice_____Debug__Path__endOfRound( const UMLRTMessage * msg )
{
    if( guard_____Debug__endOfRound__S( msg ) )
    {
        actionchain_____Debug__endOfRound__S( msg );
        return junction_____Debug__C__endOfRound__en( msg );
    }
    else
    {
        actionchain_____endOfRound( msg );
        return WAITING_TO_START;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::choice_____Debug__Path__keepPlaying( const UMLRTMessage * msg )
{
    if( guard_____Debug__keepPlaying__S( msg ) )
    {
        actionchain_____Debug__keepPlaying__S( msg );
        return junction_____Debug__C__keepPlaying__en( msg );
    }
    else
    {
        actionchain_____keepPlaying( msg );
        return WAITING_FOR_TIMER;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::choice_____Debug__Path__onPong( const UMLRTMessage * msg )
{
    if( guard_____Debug__onPong__S( msg ) )
    {
        actionchain_____Debug__onPong__S( msg );
        return junction_____Debug__C__onPong__en( msg );
    }
    else
    {
        actionchain_____onPong( msg );
        return choice_____ThreePingsSent_( msg );
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::choice_____Debug__Path__startSignal( const UMLRTMessage * msg )
{
    if( guard_____Debug__startSignal__S( msg ) )
    {
        actionchain_____Debug__startSignal__S( msg );
        return junction_____Debug__C__startSignal__en( msg );
    }
    else
    {
        actionchain_____startSignal( msg );
        return PLAYING;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::choice_____Debug__Path__timeout( const UMLRTMessage * msg )
{
    if( guard_____Debug__timeout__S( msg ) )
    {
        actionchain_____Debug__timeout__S( msg );
        return junction_____Debug__C__timeout__en( msg );
    }
    else
    {
        actionchain_____timeout( msg );
        return PLAYING;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::choice_____ThreePingsSent_( const UMLRTMessage * msg )
{
    if( guard_____Debug__endOfRound( msg ) )
    {
        actionchain_____Debug__endOfRound( msg );
        return choice_____Debug__Path__endOfRound( msg );
    }
    else
    {
        actionchain_____Debug__keepPlaying( msg );
        return choice_____Debug__Path__keepPlaying( msg );
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Initial__Debug__En__WAITING_TO_START( msg );
            return Debug__C__Initial__Debug__A__En__Initial;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Initial__new_transition_101( msg );
            return junction_____Debug__C__Initial__new_exitpoint_19( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__Initial__new_transition_105( msg );
            return junction_____Debug__C__Initial__new_exitpoint_20( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__Initial__new_transition_109( msg );
            return junction_____Debug__C__Initial__new_exitpoint_21( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__Initial__new_transition_113( msg );
            return junction_____Debug__C__Initial__new_exitpoint_22( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__Initial__new_transition_117( msg );
            return junction_____Debug__C__Initial__new_exitpoint_23( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__Initial__new_transition_121( msg );
            return junction_____Debug__C__Initial__new_exitpoint_24( msg );
            actionchain_____Debug__C__Initial__new_transition_121( msg );
            return junction_____Debug__C__Initial__new_exitpoint_24( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__Initial__new_transition_121( msg );
            return junction_____Debug__C__Initial__new_exitpoint_24( msg );
            actionchain_____Debug__C__Initial__new_transition_121( msg );
            return junction_____Debug__C__Initial__new_exitpoint_24( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg )
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
            actionchain_____Debug__C__Initial__new_transition_102( msg );
            return junction_____Debug__C__Initial__new_exitpoint_19( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__Initial__new_transition_106( msg );
            return junction_____Debug__C__Initial__new_exitpoint_20( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__Initial__new_transition_110( msg );
            return junction_____Debug__C__Initial__new_exitpoint_21( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__Initial__new_transition_114( msg );
            return junction_____Debug__C__Initial__new_exitpoint_22( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__Initial__new_transition_118( msg );
            return junction_____Debug__C__Initial__new_exitpoint_23( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__Initial__new_transition_122( msg );
            return junction_____Debug__C__Initial__new_exitpoint_24( msg );
            actionchain_____Debug__C__Initial__new_transition_122( msg );
            return junction_____Debug__C__Initial__new_exitpoint_24( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__Initial__new_transition_122( msg );
            return junction_____Debug__C__Initial__new_exitpoint_24( msg );
            actionchain_____Debug__C__Initial__new_transition_122( msg );
            return junction_____Debug__C__Initial__new_exitpoint_24( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg )
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
            actionchain_____Debug__C__Initial__new_transition_100( msg );
            return junction_____Debug__C__Initial__new_exitpoint_19( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__Initial__new_transition_104( msg );
            return junction_____Debug__C__Initial__new_exitpoint_20( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__Initial__new_transition_108( msg );
            return junction_____Debug__C__Initial__new_exitpoint_21( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__Initial__new_transition_112( msg );
            return junction_____Debug__C__Initial__new_exitpoint_22( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__Initial__new_transition_116( msg );
            return junction_____Debug__C__Initial__new_exitpoint_23( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__Initial__new_transition_120( msg );
            return junction_____Debug__C__Initial__new_exitpoint_24( msg );
            actionchain_____Debug__C__Initial__new_transition_120( msg );
            return junction_____Debug__C__Initial__new_exitpoint_24( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__Initial__new_transition_120( msg );
            return junction_____Debug__C__Initial__new_exitpoint_24( msg );
            actionchain_____Debug__C__Initial__new_transition_120( msg );
            return junction_____Debug__C__Initial__new_exitpoint_24( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__Initial__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Initial__new_transition_103( msg );
            return junction_____Debug__C__Initial__new_exitpoint_19( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__Initial__new_transition_107( msg );
            return junction_____Debug__C__Initial__new_exitpoint_20( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__Initial__new_transition_111( msg );
            return junction_____Debug__C__Initial__new_exitpoint_21( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__Initial__new_transition_115( msg );
            return junction_____Debug__C__Initial__new_exitpoint_22( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__Initial__new_transition_119( msg );
            return junction_____Debug__C__Initial__new_exitpoint_23( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__Initial__new_transition_123( msg );
            return junction_____Debug__C__Initial__new_exitpoint_24( msg );
            actionchain_____Debug__C__Initial__new_transition_123( msg );
            return junction_____Debug__C__Initial__new_exitpoint_24( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__Initial__new_transition_123( msg );
            return junction_____Debug__C__Initial__new_exitpoint_24( msg );
            actionchain_____Debug__C__Initial__new_transition_123( msg );
            return junction_____Debug__C__Initial__new_exitpoint_24( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__endOfRound__Debug__En__WAITING_TO_START( msg );
            return Debug__C__endOfRound__Debug__A__En__endOfRound;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__endOfRound__new_transition_7( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_1( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__endOfRound__new_transition_11( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_2( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__endOfRound__new_transition_15( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_3( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__endOfRound__new_transition_19( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_4( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__endOfRound__new_transition_23( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_5( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__endOfRound__new_transition_27( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_6( msg );
            actionchain_____Debug__C__endOfRound__new_transition_27( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_6( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__endOfRound__new_transition_27( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_6( msg );
            actionchain_____Debug__C__endOfRound__new_transition_27( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_6( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__endOfRound__Debug__A__En__endOfRound( const UMLRTMessage * msg )
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
            actionchain_____Debug__C__endOfRound__new_transition_8( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_1( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__endOfRound__new_transition_12( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_2( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__endOfRound__new_transition_16( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_3( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__endOfRound__new_transition_20( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_4( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__endOfRound__new_transition_24( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_5( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__endOfRound__new_transition_28( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_6( msg );
            actionchain_____Debug__C__endOfRound__new_transition_28( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_6( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__endOfRound__new_transition_28( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_6( msg );
            actionchain_____Debug__C__endOfRound__new_transition_28( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_6( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( const UMLRTMessage * msg )
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
            actionchain_____Debug__C__endOfRound__new_transition_6( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_1( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__endOfRound__new_transition_10( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_2( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__endOfRound__new_transition_14( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_3( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__endOfRound__new_transition_18( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_4( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__endOfRound__new_transition_22( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_5( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__endOfRound__new_transition_26( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_6( msg );
            actionchain_____Debug__C__endOfRound__new_transition_26( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_6( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__endOfRound__new_transition_26( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_6( msg );
            actionchain_____Debug__C__endOfRound__new_transition_26( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_6( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__endOfRound__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__endOfRound__new_transition_9( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_1( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__endOfRound__new_transition_13( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_2( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__endOfRound__new_transition_17( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_3( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__endOfRound__new_transition_21( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_4( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__endOfRound__new_transition_25( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_5( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__endOfRound__new_transition_29( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_6( msg );
            actionchain_____Debug__C__endOfRound__new_transition_29( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_6( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__endOfRound__new_transition_29( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_6( msg );
            actionchain_____Debug__C__endOfRound__new_transition_29( msg );
            return junction_____Debug__C__endOfRound__new_exitpoint_6( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__keepPlaying__Debug__En__WAITING_FOR_TIMER( msg );
            return Debug__C__keepPlaying__Debug__A__En__keepPlaying;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__keepPlaying__new_transition_130( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_25( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__keepPlaying__new_transition_134( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_26( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__keepPlaying__new_transition_138( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_27( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__keepPlaying__new_transition_142( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_28( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__keepPlaying__new_transition_146( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_29( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__keepPlaying__new_transition_150( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_30( msg );
            actionchain_____Debug__C__keepPlaying__new_transition_150( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_30( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__keepPlaying__new_transition_150( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_30( msg );
            actionchain_____Debug__C__keepPlaying__new_transition_150( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_30( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( const UMLRTMessage * msg )
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
            actionchain_____Debug__C__keepPlaying__new_transition_131( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_25( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__keepPlaying__new_transition_135( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_26( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__keepPlaying__new_transition_139( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_27( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__keepPlaying__new_transition_143( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_28( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__keepPlaying__new_transition_147( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_29( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__keepPlaying__new_transition_151( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_30( msg );
            actionchain_____Debug__C__keepPlaying__new_transition_151( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_30( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__keepPlaying__new_transition_151( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_30( msg );
            actionchain_____Debug__C__keepPlaying__new_transition_151( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_30( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( const UMLRTMessage * msg )
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
            actionchain_____Debug__C__keepPlaying__new_transition_129( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_25( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__keepPlaying__new_transition_133( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_26( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__keepPlaying__new_transition_137( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_27( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__keepPlaying__new_transition_141( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_28( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__keepPlaying__new_transition_145( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_29( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__keepPlaying__new_transition_149( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_30( msg );
            actionchain_____Debug__C__keepPlaying__new_transition_149( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_30( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__keepPlaying__new_transition_149( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_30( msg );
            actionchain_____Debug__C__keepPlaying__new_transition_149( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_30( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__keepPlaying__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__keepPlaying__new_transition_132( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_25( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__keepPlaying__new_transition_136( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_26( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__keepPlaying__new_transition_140( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_27( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__keepPlaying__new_transition_144( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_28( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__keepPlaying__new_transition_148( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_29( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__keepPlaying__new_transition_152( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_30( msg );
            actionchain_____Debug__C__keepPlaying__new_transition_152( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_30( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__keepPlaying__new_transition_152( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_30( msg );
            actionchain_____Debug__C__keepPlaying__new_transition_152( msg );
            return junction_____Debug__C__keepPlaying__new_exitpoint_30( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__onPong__Debug__A__Ac__onPong( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__onPong__Debug__end__trans__onPong( msg );
            return junction_____Debug__C__onPong__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__onPong__new_transition_73( msg );
            return junction_____Debug__C__onPong__new_exitpoint_13( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__onPong__new_transition_77( msg );
            return junction_____Debug__C__onPong__new_exitpoint_14( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__onPong__new_transition_81( msg );
            return junction_____Debug__C__onPong__new_exitpoint_15( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__onPong__new_transition_85( msg );
            return junction_____Debug__C__onPong__new_exitpoint_16( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__onPong__new_transition_89( msg );
            return junction_____Debug__C__onPong__new_exitpoint_17( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__onPong__new_transition_93( msg );
            return junction_____Debug__C__onPong__new_exitpoint_18( msg );
            actionchain_____Debug__C__onPong__new_transition_93( msg );
            return junction_____Debug__C__onPong__new_exitpoint_18( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__onPong__new_transition_93( msg );
            return junction_____Debug__C__onPong__new_exitpoint_18( msg );
            actionchain_____Debug__C__onPong__new_transition_93( msg );
            return junction_____Debug__C__onPong__new_exitpoint_18( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__onPong__Debug__B__Ac__onPong( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__onPong__Debug__AC__onPong( msg );
            return Debug__C__onPong__Debug__A__Ac__onPong;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__onPong__new_transition_72( msg );
            return junction_____Debug__C__onPong__new_exitpoint_13( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__onPong__new_transition_76( msg );
            return junction_____Debug__C__onPong__new_exitpoint_14( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__onPong__new_transition_80( msg );
            return junction_____Debug__C__onPong__new_exitpoint_15( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__onPong__new_transition_84( msg );
            return junction_____Debug__C__onPong__new_exitpoint_16( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__onPong__new_transition_88( msg );
            return junction_____Debug__C__onPong__new_exitpoint_17( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__onPong__new_transition_92( msg );
            return junction_____Debug__C__onPong__new_exitpoint_18( msg );
            actionchain_____Debug__C__onPong__new_transition_92( msg );
            return junction_____Debug__C__onPong__new_exitpoint_18( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__onPong__new_transition_92( msg );
            return junction_____Debug__C__onPong__new_exitpoint_18( msg );
            actionchain_____Debug__C__onPong__new_transition_92( msg );
            return junction_____Debug__C__onPong__new_exitpoint_18( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__onPong__Debug__B__Ex__PLAYING( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__onPong__Debug__Ex__PLAYING( msg );
            return Debug__C__onPong__Debug__B__Ac__onPong;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__onPong__new_transition_71( msg );
            return junction_____Debug__C__onPong__new_exitpoint_13( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__onPong__new_transition_75( msg );
            return junction_____Debug__C__onPong__new_exitpoint_14( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__onPong__new_transition_79( msg );
            return junction_____Debug__C__onPong__new_exitpoint_15( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__onPong__new_transition_83( msg );
            return junction_____Debug__C__onPong__new_exitpoint_16( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__onPong__new_transition_87( msg );
            return junction_____Debug__C__onPong__new_exitpoint_17( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__onPong__new_transition_91( msg );
            return junction_____Debug__C__onPong__new_exitpoint_18( msg );
            actionchain_____Debug__C__onPong__new_transition_91( msg );
            return junction_____Debug__C__onPong__new_exitpoint_18( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__onPong__new_transition_91( msg );
            return junction_____Debug__C__onPong__new_exitpoint_18( msg );
            actionchain_____Debug__C__onPong__new_transition_91( msg );
            return junction_____Debug__C__onPong__new_exitpoint_18( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__onPong__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__onPong__new_transition_74( msg );
            return junction_____Debug__C__onPong__new_exitpoint_13( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__onPong__new_transition_78( msg );
            return junction_____Debug__C__onPong__new_exitpoint_14( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__onPong__new_transition_82( msg );
            return junction_____Debug__C__onPong__new_exitpoint_15( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__onPong__new_transition_86( msg );
            return junction_____Debug__C__onPong__new_exitpoint_16( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__onPong__new_transition_90( msg );
            return junction_____Debug__C__onPong__new_exitpoint_17( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__onPong__new_transition_94( msg );
            return junction_____Debug__C__onPong__new_exitpoint_18( msg );
            actionchain_____Debug__C__onPong__new_transition_94( msg );
            return junction_____Debug__C__onPong__new_exitpoint_18( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__onPong__new_transition_94( msg );
            return junction_____Debug__C__onPong__new_exitpoint_18( msg );
            actionchain_____Debug__C__onPong__new_transition_94( msg );
            return junction_____Debug__C__onPong__new_exitpoint_18( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__startSignal__Debug__A__Ac__startSignal( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__startSignal__Debug__En__PLAYING( msg );
            return Debug__C__startSignal__Debug__A__En__PLAYING;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__startSignal__new_transition_161( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_31( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__startSignal__new_transition_166( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_32( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__startSignal__new_transition_171( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_33( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__startSignal__new_transition_176( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_34( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__startSignal__new_transition_181( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_35( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__startSignal__new_transition_186( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_36( msg );
            actionchain_____Debug__C__startSignal__new_transition_186( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_36( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__startSignal__new_transition_186( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_36( msg );
            actionchain_____Debug__C__startSignal__new_transition_186( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_36( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__startSignal__Debug__A__En__PLAYING( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__startSignal__Debug__end__trans__startSignal( msg );
            return junction_____Debug__C__startSignal__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__startSignal__new_transition_162( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_31( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__startSignal__new_transition_167( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_32( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__startSignal__new_transition_172( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_33( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__startSignal__new_transition_177( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_34( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__startSignal__new_transition_182( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_35( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__startSignal__new_transition_187( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_36( msg );
            actionchain_____Debug__C__startSignal__new_transition_187( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_36( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__startSignal__new_transition_187( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_36( msg );
            actionchain_____Debug__C__startSignal__new_transition_187( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_36( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__startSignal__Debug__B__Ac__startSignal( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__startSignal__Debug__AC__startSignal( msg );
            return Debug__C__startSignal__Debug__A__Ac__startSignal;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__startSignal__new_transition_160( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_31( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__startSignal__new_transition_165( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_32( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__startSignal__new_transition_170( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_33( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__startSignal__new_transition_175( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_34( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__startSignal__new_transition_180( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_35( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__startSignal__new_transition_185( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_36( msg );
            actionchain_____Debug__C__startSignal__new_transition_185( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_36( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__startSignal__new_transition_185( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_36( msg );
            actionchain_____Debug__C__startSignal__new_transition_185( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_36( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__startSignal__Debug__Ex__WAITING_TO_START( msg );
            return Debug__C__startSignal__Debug__B__Ac__startSignal;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__startSignal__new_transition_159( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_31( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__startSignal__new_transition_164( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_32( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__startSignal__new_transition_169( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_33( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__startSignal__new_transition_174( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_34( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__startSignal__new_transition_179( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_35( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__startSignal__new_transition_184( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_36( msg );
            actionchain_____Debug__C__startSignal__new_transition_184( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_36( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__startSignal__new_transition_184( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_36( msg );
            actionchain_____Debug__C__startSignal__new_transition_184( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_36( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__startSignal__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__startSignal__new_transition_163( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_31( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__startSignal__new_transition_168( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_32( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__startSignal__new_transition_173( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_33( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__startSignal__new_transition_178( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_34( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__startSignal__new_transition_183( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_35( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__startSignal__new_transition_188( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_36( msg );
            actionchain_____Debug__C__startSignal__new_transition_188( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_36( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__startSignal__new_transition_188( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_36( msg );
            actionchain_____Debug__C__startSignal__new_transition_188( msg );
            return junction_____Debug__C__startSignal__new_exitpoint_36( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__timeout__Debug__A__Ac__timeout( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__timeout__Debug__En__PLAYING( msg );
            return Debug__C__timeout__Debug__A__En__PLAYING;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__timeout__new_transition_38( msg );
            return junction_____Debug__C__timeout__new_exitpoint_7( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__timeout__new_transition_43( msg );
            return junction_____Debug__C__timeout__new_exitpoint_8( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__timeout__new_transition_48( msg );
            return junction_____Debug__C__timeout__new_exitpoint_9( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__timeout__new_transition_53( msg );
            return junction_____Debug__C__timeout__new_exitpoint_10( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__timeout__new_transition_58( msg );
            return junction_____Debug__C__timeout__new_exitpoint_11( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__timeout__new_transition_63( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
            actionchain_____Debug__C__timeout__new_transition_63( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__timeout__new_transition_63( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
            actionchain_____Debug__C__timeout__new_transition_63( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__timeout__Debug__A__En__PLAYING( const UMLRTMessage * msg )
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
            actionchain_____Debug__C__timeout__new_transition_39( msg );
            return junction_____Debug__C__timeout__new_exitpoint_7( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__timeout__new_transition_44( msg );
            return junction_____Debug__C__timeout__new_exitpoint_8( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__timeout__new_transition_49( msg );
            return junction_____Debug__C__timeout__new_exitpoint_9( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__timeout__new_transition_54( msg );
            return junction_____Debug__C__timeout__new_exitpoint_10( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__timeout__new_transition_59( msg );
            return junction_____Debug__C__timeout__new_exitpoint_11( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__timeout__new_transition_64( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
            actionchain_____Debug__C__timeout__new_transition_64( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__timeout__new_transition_64( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
            actionchain_____Debug__C__timeout__new_transition_64( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__timeout__Debug__B__Ac__timeout( const UMLRTMessage * msg )
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
            actionchain_____Debug__C__timeout__new_transition_37( msg );
            return junction_____Debug__C__timeout__new_exitpoint_7( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__timeout__new_transition_42( msg );
            return junction_____Debug__C__timeout__new_exitpoint_8( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__timeout__new_transition_47( msg );
            return junction_____Debug__C__timeout__new_exitpoint_9( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__timeout__new_transition_52( msg );
            return junction_____Debug__C__timeout__new_exitpoint_10( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__timeout__new_transition_57( msg );
            return junction_____Debug__C__timeout__new_exitpoint_11( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__timeout__new_transition_62( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
            actionchain_____Debug__C__timeout__new_transition_62( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__timeout__new_transition_62( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
            actionchain_____Debug__C__timeout__new_transition_62( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( const UMLRTMessage * msg )
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
            actionchain_____Debug__C__timeout__new_transition_36( msg );
            return junction_____Debug__C__timeout__new_exitpoint_7( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__timeout__new_transition_41( msg );
            return junction_____Debug__C__timeout__new_exitpoint_8( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__timeout__new_transition_46( msg );
            return junction_____Debug__C__timeout__new_exitpoint_9( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__timeout__new_transition_51( msg );
            return junction_____Debug__C__timeout__new_exitpoint_10( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__timeout__new_transition_56( msg );
            return junction_____Debug__C__timeout__new_exitpoint_11( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__timeout__new_transition_61( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
            actionchain_____Debug__C__timeout__new_transition_61( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__timeout__new_transition_61( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
            actionchain_____Debug__C__timeout__new_transition_61( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__C__timeout__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__timeout__new_transition_40( msg );
            return junction_____Debug__C__timeout__new_exitpoint_7( msg );
        case ExtInterface::signal_dbgSetBreakPoint:
            actionchain_____Debug__C__timeout__new_transition_45( msg );
            return junction_____Debug__C__timeout__new_exitpoint_8( msg );
        case ExtInterface::signal_dbgRemBreakPoint:
            actionchain_____Debug__C__timeout__new_transition_50( msg );
            return junction_____Debug__C__timeout__new_exitpoint_9( msg );
        case ExtInterface::signal_dbgViewBreakPoints:
            actionchain_____Debug__C__timeout__new_transition_55( msg );
            return junction_____Debug__C__timeout__new_exitpoint_10( msg );
        case ExtInterface::signal_dbgSetExecMode:
            actionchain_____Debug__C__timeout__new_transition_60( msg );
            return junction_____Debug__C__timeout__new_exitpoint_11( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__timeout__new_transition_65( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
            actionchain_____Debug__C__timeout__new_transition_65( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
        }
        return currentState;
    case port_startPort:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__C__timeout__new_transition_65( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
            actionchain_____Debug__C__timeout__new_transition_65( msg );
            return junction_____Debug__C__timeout__new_exitpoint_12( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Pinger::State Capsule_Pinger::state_____Debug__InitState( const UMLRTMessage * msg )
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

Capsule_Pinger::State Capsule_Pinger::state_____PLAYING( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_pingPort:
        switch( msg->getSignalId() )
        {
        case PingPongProtocol::signal_pong:
            actionchain_____Debug__onPong( msg );
            return choice_____Debug__Path__onPong( msg );
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

Capsule_Pinger::State Capsule_Pinger::state_____WAITING_FOR_TIMER( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_pingerTimer:
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

Capsule_Pinger::State Capsule_Pinger::state_____WAITING_TO_START( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_startPort:
        switch( msg->getSignalId() )
        {
        case StartProtocol::signal_start:
            actionchain_____Debug__startSignal( msg );
            return choice_____Debug__Path__startSignal( msg );
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
        Capsule_Pinger::port_pingPort,
        "PingPongProtocol",
        "pingPort",
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
        Capsule_Pinger::port_startPort,
        "StartProtocol",
        "startPort",
        "",
        1,
        true,
        true,
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
        Capsule_Pinger::port_extComm,
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
        Capsule_Pinger::port_pingerTimer,
        "Timing",
        "pingerTimer",
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
        Capsule_Pinger::port_log,
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

static void instantiate_Pinger( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    const UMLRTCommsPort * * internalPorts = UMLRTFrameService::createInternalPorts( slot, &Pinger );
    slot->capsule = new Capsule_Pinger( &Pinger, slot, borderPorts, internalPorts, false );
}

const UMLRTCapsuleClass Pinger = 
{
    "Pinger",
    NULL,
    instantiate_Pinger,
    0,
    NULL,
    2,
    portroles_border,
    3,
    portroles_internal
};

