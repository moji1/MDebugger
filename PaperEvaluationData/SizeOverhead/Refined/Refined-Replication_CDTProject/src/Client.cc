
#include "Client.hh"

#include "Config.hh"
#include "ExtInterface.hh"
#include "Host.hh"
#include "Services.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include "umlrttimerprotocol.hh"
#include <cstddef>
#include "Configuration.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

#include <iostream>
#include <cstdlib>

Capsule_Client::Capsule_Client( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: Capsule_Host( cd, st, border, internal, isStat )
, ConfigComm( borderPorts[borderport_ConfigComm] )
, ConfigTimer( borderPorts[borderport_ConfigTimer] )
, RequestTimer( borderPorts[borderport_RequestTimer] )
, ResponseTimer( borderPorts[borderport_ResponseTimer] )
, Server1Comm( borderPorts[borderport_Server1Comm] )
, Server2Comm( borderPorts[borderport_Server2Comm] )
, Timer( borderPorts[borderport_Timer] )
, extComm( borderPorts[borderport_extComm] )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[Debug__C__NoMaster] = "Debug__C__NoMaster";
    stateNames[Debug__C__NoResponseFromServer] = "Debug__C__NoResponseFromServer";
    stateNames[Debug__C__ReqFlowDone] = "Debug__C__ReqFlowDone";
    stateNames[Debug__C__Retry] = "Debug__C__Retry";
    stateNames[Debug__C__ServiceResult] = "Debug__C__ServiceResult";
    stateNames[Debug__C__StarupTransition] = "Debug__C__StarupTransition";
    stateNames[Debug__C__getMasterName__checkConfig__7] = "Debug__C__getMasterName__checkConfig__7";
    stateNames[Debug__C__init__StandBY__6] = "Debug__C__init__StandBY__6";
    stateNames[Debug__C__reqFlowInit] = "Debug__C__reqFlowInit";
    stateNames[Debug__C__reqService] = "Debug__C__reqService";
    stateNames[Debug__C__NoMaster__Debug__A__Ac__NoMaster] = "Debug__C__NoMaster__Debug__A__Ac__NoMaster";
    stateNames[Debug__C__NoMaster__Debug__A__En__NoMaster] = "Debug__C__NoMaster__Debug__A__En__NoMaster";
    stateNames[Debug__C__NoMaster__Debug__B__Ac__NoMaster] = "Debug__C__NoMaster__Debug__B__Ac__NoMaster";
    stateNames[Debug__C__NoMaster__boundary] = "Debug__C__NoMaster__boundary";
    stateNames[Debug__C__NoResponseFromServer__Debug__A__Ac__NoResponseFromServer] = "Debug__C__NoResponseFromServer__Debug__A__Ac__NoResponseFromServer";
    stateNames[Debug__C__NoResponseFromServer__Debug__A__En__Ready] = "Debug__C__NoResponseFromServer__Debug__A__En__Ready";
    stateNames[Debug__C__NoResponseFromServer__Debug__B__Ac__NoResponseFromServer] = "Debug__C__NoResponseFromServer__Debug__B__Ac__NoResponseFromServer";
    stateNames[Debug__C__NoResponseFromServer__Debug__B__Ex__WaitingForReply] = "Debug__C__NoResponseFromServer__Debug__B__Ex__WaitingForReply";
    stateNames[Debug__C__NoResponseFromServer__boundary] = "Debug__C__NoResponseFromServer__boundary";
    stateNames[Debug__C__ReqFlowDone__Debug__A__Ac__ReqFlowDone] = "Debug__C__ReqFlowDone__Debug__A__Ac__ReqFlowDone";
    stateNames[Debug__C__ReqFlowDone__Debug__A__En__Ready] = "Debug__C__ReqFlowDone__Debug__A__En__Ready";
    stateNames[Debug__C__ReqFlowDone__Debug__B__Ac__ReqFlowDone] = "Debug__C__ReqFlowDone__Debug__B__Ac__ReqFlowDone";
    stateNames[Debug__C__ReqFlowDone__Debug__B__Ex__ProcessResponse] = "Debug__C__ReqFlowDone__Debug__B__Ex__ProcessResponse";
    stateNames[Debug__C__ReqFlowDone__boundary] = "Debug__C__ReqFlowDone__boundary";
    stateNames[Debug__C__Retry__Debug__A__Ac__Retry] = "Debug__C__Retry__Debug__A__Ac__Retry";
    stateNames[Debug__C__Retry__Debug__A__En__getMasterName] = "Debug__C__Retry__Debug__A__En__getMasterName";
    stateNames[Debug__C__Retry__Debug__B__Ac__Retry] = "Debug__C__Retry__Debug__B__Ac__Retry";
    stateNames[Debug__C__Retry__Debug__B__Ex__Retry] = "Debug__C__Retry__Debug__B__Ex__Retry";
    stateNames[Debug__C__Retry__boundary] = "Debug__C__Retry__boundary";
    stateNames[Debug__C__ServiceResult__Debug__A__Ac__ServiceResult] = "Debug__C__ServiceResult__Debug__A__Ac__ServiceResult";
    stateNames[Debug__C__ServiceResult__Debug__A__En__ProcessResponse] = "Debug__C__ServiceResult__Debug__A__En__ProcessResponse";
    stateNames[Debug__C__ServiceResult__Debug__B__Ac__ServiceResult] = "Debug__C__ServiceResult__Debug__B__Ac__ServiceResult";
    stateNames[Debug__C__ServiceResult__Debug__B__Ex__WaitingForReply] = "Debug__C__ServiceResult__Debug__B__Ex__WaitingForReply";
    stateNames[Debug__C__ServiceResult__boundary] = "Debug__C__ServiceResult__boundary";
    stateNames[Debug__C__StarupTransition__Debug__A__Ac__StarupTransition] = "Debug__C__StarupTransition__Debug__A__Ac__StarupTransition";
    stateNames[Debug__C__StarupTransition__Debug__A__En__Ready] = "Debug__C__StarupTransition__Debug__A__En__Ready";
    stateNames[Debug__C__StarupTransition__Debug__B__Ac__StarupTransition] = "Debug__C__StarupTransition__Debug__B__Ac__StarupTransition";
    stateNames[Debug__C__StarupTransition__Debug__B__Ex__StandBY] = "Debug__C__StarupTransition__Debug__B__Ex__StandBY";
    stateNames[Debug__C__StarupTransition__boundary] = "Debug__C__StarupTransition__boundary";
    stateNames[Debug__C__getMasterName__checkConfig__7__Debug__A__Ac__getMasterName__checkConfig__7] = "Debug__C__getMasterName__checkConfig__7__Debug__A__Ac__getMasterName__checkConfig__7";
    stateNames[Debug__C__getMasterName__checkConfig__7__Debug__B__Ac__getMasterName__checkConfig__7] = "Debug__C__getMasterName__checkConfig__7__Debug__B__Ac__getMasterName__checkConfig__7";
    stateNames[Debug__C__getMasterName__checkConfig__7__Debug__B__Ex__getMasterName] = "Debug__C__getMasterName__checkConfig__7__Debug__B__Ex__getMasterName";
    stateNames[Debug__C__getMasterName__checkConfig__7__boundary] = "Debug__C__getMasterName__checkConfig__7__boundary";
    stateNames[Debug__C__init__StandBY__6__Debug__A__Ac__init__StandBY__6] = "Debug__C__init__StandBY__6__Debug__A__Ac__init__StandBY__6";
    stateNames[Debug__C__init__StandBY__6__Debug__A__En__init__StandBY__6] = "Debug__C__init__StandBY__6__Debug__A__En__init__StandBY__6";
    stateNames[Debug__C__init__StandBY__6__Debug__B__Ac__init__StandBY__6] = "Debug__C__init__StandBY__6__Debug__B__Ac__init__StandBY__6";
    stateNames[Debug__C__init__StandBY__6__boundary] = "Debug__C__init__StandBY__6__boundary";
    stateNames[Debug__C__reqFlowInit__Debug__A__Ac__reqFlowInit] = "Debug__C__reqFlowInit__Debug__A__Ac__reqFlowInit";
    stateNames[Debug__C__reqFlowInit__Debug__A__En__getMasterName] = "Debug__C__reqFlowInit__Debug__A__En__getMasterName";
    stateNames[Debug__C__reqFlowInit__Debug__B__Ac__reqFlowInit] = "Debug__C__reqFlowInit__Debug__B__Ac__reqFlowInit";
    stateNames[Debug__C__reqFlowInit__Debug__B__Ex__Ready] = "Debug__C__reqFlowInit__Debug__B__Ex__Ready";
    stateNames[Debug__C__reqFlowInit__boundary] = "Debug__C__reqFlowInit__boundary";
    stateNames[Debug__C__reqService__Debug__A__Ac__reqService] = "Debug__C__reqService__Debug__A__Ac__reqService";
    stateNames[Debug__C__reqService__Debug__A__En__reqService] = "Debug__C__reqService__Debug__A__En__reqService";
    stateNames[Debug__C__reqService__Debug__B__Ac__reqService] = "Debug__C__reqService__Debug__B__Ac__reqService";
    stateNames[Debug__C__reqService__boundary] = "Debug__C__reqService__boundary";
    stateNames[Debug__InitState] = "Debug__InitState";
    stateNames[ProcessResponse] = "ProcessResponse";
    stateNames[Ready] = "Ready";
    stateNames[Retry] = "Retry";
    stateNames[StandBY] = "StandBY";
    stateNames[WaitingForReply] = "WaitingForReply";
    stateNames[getMasterName] = "getMasterName";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
    int i = 0;
    while( i < 10 )
        history[i++] = SPECIAL_INTERNAL_STATE_UNVISITED;
}












void Capsule_Client::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_Server1Comm:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_Server1Comm, index, true );
            break;
        case borderport_Server2Comm:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_Server2Comm, index, true );
            break;
        }
}

void Capsule_Client::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_Server1Comm:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_Server1Comm, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_Server1Comm], index );
            break;
        case borderport_Server2Comm:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_Server2Comm, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_Server2Comm], index );
            break;
        }
}





void Capsule_Client::Debug__variablesView()
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Client operation Debug__variablesView */
    std::string tempS="";
    if (Debug__variablesData==NULL)
    Debug__variablesData=(char *)malloc(strlen(tempS.c_str())+1);
    else if (strlen(Debug__variablesData)<strlen(tempS.c_str()))
    Debug__variablesData=(char *) realloc(Debug__variablesData,strlen(tempS.c_str())+1);
    strcpy(Debug__variablesData,tempS.c_str());
    /* UMLRTGEN-USERREGION-END */
}

bool Capsule_Client::Debug__variablesChange( char * varName, char * varValue )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Client operation Debug__variablesChange */
    std::string tempVarName="";
    tempVarName.append(varName);
    return false;
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_Client::Debug__sendEvent( debugEvents::EVENTSOURCEKIND eventSourceKind, debugEvents::EVENTTYPE eventType, const char * instanceName, int capsuleIndex, const char * signalName, char * capsuleName, char * sourceName, char * reserve1, char * reserve2, char * reserve3 )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Client operation Debug__sendEvent */
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

void Capsule_Client::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case StandBY:
        currentState = state_____StandBY( &message );
        break;
    case Ready:
        currentState = state_____Ready( &message );
        break;
    case getMasterName:
        currentState = state_____getMasterName( &message );
        break;
    case WaitingForReply:
        currentState = state_____WaitingForReply( &message );
        break;
    case ProcessResponse:
        currentState = state_____ProcessResponse( &message );
        break;
    case Retry:
        currentState = state_____Retry( &message );
        break;
    case Debug__InitState:
        currentState = state_____Debug__InitState( &message );
        break;
    case Debug__C__StarupTransition__Debug__B__Ex__StandBY:
        currentState = state_____Debug__C__StarupTransition__Debug__B__Ex__StandBY( &message );
        break;
    case Debug__C__StarupTransition__Debug__B__Ac__StarupTransition:
        currentState = state_____Debug__C__StarupTransition__Debug__B__Ac__StarupTransition( &message );
        break;
    case Debug__C__StarupTransition__Debug__A__Ac__StarupTransition:
        currentState = state_____Debug__C__StarupTransition__Debug__A__Ac__StarupTransition( &message );
        break;
    case Debug__C__StarupTransition__Debug__A__En__Ready:
        currentState = state_____Debug__C__StarupTransition__Debug__A__En__Ready( &message );
        break;
    case Debug__C__StarupTransition__boundary:
        currentState = state_____Debug__C__StarupTransition__boundary( &message );
        break;
    case Debug__C__Retry__Debug__B__Ex__Retry:
        currentState = state_____Debug__C__Retry__Debug__B__Ex__Retry( &message );
        break;
    case Debug__C__Retry__Debug__B__Ac__Retry:
        currentState = state_____Debug__C__Retry__Debug__B__Ac__Retry( &message );
        break;
    case Debug__C__Retry__Debug__A__Ac__Retry:
        currentState = state_____Debug__C__Retry__Debug__A__Ac__Retry( &message );
        break;
    case Debug__C__Retry__Debug__A__En__getMasterName:
        currentState = state_____Debug__C__Retry__Debug__A__En__getMasterName( &message );
        break;
    case Debug__C__Retry__boundary:
        currentState = state_____Debug__C__Retry__boundary( &message );
        break;
    case Debug__C__NoMaster__Debug__B__Ac__NoMaster:
        currentState = state_____Debug__C__NoMaster__Debug__B__Ac__NoMaster( &message );
        break;
    case Debug__C__NoMaster__Debug__A__Ac__NoMaster:
        currentState = state_____Debug__C__NoMaster__Debug__A__Ac__NoMaster( &message );
        break;
    case Debug__C__NoMaster__Debug__A__En__NoMaster:
        currentState = state_____Debug__C__NoMaster__Debug__A__En__NoMaster( &message );
        break;
    case Debug__C__NoMaster__boundary:
        currentState = state_____Debug__C__NoMaster__boundary( &message );
        break;
    case Debug__C__NoResponseFromServer__Debug__B__Ex__WaitingForReply:
        currentState = state_____Debug__C__NoResponseFromServer__Debug__B__Ex__WaitingForReply( &message );
        break;
    case Debug__C__NoResponseFromServer__Debug__B__Ac__NoResponseFromServer:
        currentState = state_____Debug__C__NoResponseFromServer__Debug__B__Ac__NoResponseFromServer( &message );
        break;
    case Debug__C__NoResponseFromServer__Debug__A__Ac__NoResponseFromServer:
        currentState = state_____Debug__C__NoResponseFromServer__Debug__A__Ac__NoResponseFromServer( &message );
        break;
    case Debug__C__NoResponseFromServer__Debug__A__En__Ready:
        currentState = state_____Debug__C__NoResponseFromServer__Debug__A__En__Ready( &message );
        break;
    case Debug__C__NoResponseFromServer__boundary:
        currentState = state_____Debug__C__NoResponseFromServer__boundary( &message );
        break;
    case Debug__C__ReqFlowDone__Debug__B__Ex__ProcessResponse:
        currentState = state_____Debug__C__ReqFlowDone__Debug__B__Ex__ProcessResponse( &message );
        break;
    case Debug__C__ReqFlowDone__Debug__B__Ac__ReqFlowDone:
        currentState = state_____Debug__C__ReqFlowDone__Debug__B__Ac__ReqFlowDone( &message );
        break;
    case Debug__C__ReqFlowDone__Debug__A__Ac__ReqFlowDone:
        currentState = state_____Debug__C__ReqFlowDone__Debug__A__Ac__ReqFlowDone( &message );
        break;
    case Debug__C__ReqFlowDone__Debug__A__En__Ready:
        currentState = state_____Debug__C__ReqFlowDone__Debug__A__En__Ready( &message );
        break;
    case Debug__C__ReqFlowDone__boundary:
        currentState = state_____Debug__C__ReqFlowDone__boundary( &message );
        break;
    case Debug__C__init__StandBY__6__Debug__B__Ac__init__StandBY__6:
        currentState = state_____Debug__C__init__StandBY__6__Debug__B__Ac__init__StandBY__6( &message );
        break;
    case Debug__C__init__StandBY__6__Debug__A__Ac__init__StandBY__6:
        currentState = state_____Debug__C__init__StandBY__6__Debug__A__Ac__init__StandBY__6( &message );
        break;
    case Debug__C__init__StandBY__6__Debug__A__En__init__StandBY__6:
        currentState = state_____Debug__C__init__StandBY__6__Debug__A__En__init__StandBY__6( &message );
        break;
    case Debug__C__init__StandBY__6__boundary:
        currentState = state_____Debug__C__init__StandBY__6__boundary( &message );
        break;
    case Debug__C__getMasterName__checkConfig__7__Debug__B__Ex__getMasterName:
        currentState = state_____Debug__C__getMasterName__checkConfig__7__Debug__B__Ex__getMasterName( &message );
        break;
    case Debug__C__getMasterName__checkConfig__7__Debug__B__Ac__getMasterName__checkConfig__7:
        currentState = state_____Debug__C__getMasterName__checkConfig__7__Debug__B__Ac__getMasterName__checkConfig__7( &message );
        break;
    case Debug__C__getMasterName__checkConfig__7__Debug__A__Ac__getMasterName__checkConfig__7:
        currentState = state_____Debug__C__getMasterName__checkConfig__7__Debug__A__Ac__getMasterName__checkConfig__7( &message );
        break;
    case Debug__C__getMasterName__checkConfig__7__boundary:
        currentState = state_____Debug__C__getMasterName__checkConfig__7__boundary( &message );
        break;
    case Debug__C__reqFlowInit__Debug__B__Ex__Ready:
        currentState = state_____Debug__C__reqFlowInit__Debug__B__Ex__Ready( &message );
        break;
    case Debug__C__reqFlowInit__Debug__B__Ac__reqFlowInit:
        currentState = state_____Debug__C__reqFlowInit__Debug__B__Ac__reqFlowInit( &message );
        break;
    case Debug__C__reqFlowInit__Debug__A__Ac__reqFlowInit:
        currentState = state_____Debug__C__reqFlowInit__Debug__A__Ac__reqFlowInit( &message );
        break;
    case Debug__C__reqFlowInit__Debug__A__En__getMasterName:
        currentState = state_____Debug__C__reqFlowInit__Debug__A__En__getMasterName( &message );
        break;
    case Debug__C__reqFlowInit__boundary:
        currentState = state_____Debug__C__reqFlowInit__boundary( &message );
        break;
    case Debug__C__ServiceResult__Debug__B__Ex__WaitingForReply:
        currentState = state_____Debug__C__ServiceResult__Debug__B__Ex__WaitingForReply( &message );
        break;
    case Debug__C__ServiceResult__Debug__B__Ac__ServiceResult:
        currentState = state_____Debug__C__ServiceResult__Debug__B__Ac__ServiceResult( &message );
        break;
    case Debug__C__ServiceResult__Debug__A__Ac__ServiceResult:
        currentState = state_____Debug__C__ServiceResult__Debug__A__Ac__ServiceResult( &message );
        break;
    case Debug__C__ServiceResult__Debug__A__En__ProcessResponse:
        currentState = state_____Debug__C__ServiceResult__Debug__A__En__ProcessResponse( &message );
        break;
    case Debug__C__ServiceResult__boundary:
        currentState = state_____Debug__C__ServiceResult__boundary( &message );
        break;
    case Debug__C__reqService__Debug__B__Ac__reqService:
        currentState = state_____Debug__C__reqService__Debug__B__Ac__reqService( &message );
        break;
    case Debug__C__reqService__Debug__A__Ac__reqService:
        currentState = state_____Debug__C__reqService__Debug__A__Ac__reqService( &message );
        break;
    case Debug__C__reqService__Debug__A__En__reqService:
        currentState = state_____Debug__C__reqService__Debug__A__En__reqService( &message );
        break;
    case Debug__C__reqService__boundary:
        currentState = state_____Debug__C__reqService__boundary( &message );
        break;
    default:
        break;
    }
}

void Capsule_Client::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Debug__InitDebug( &message );
    currentState = Debug__InitState;
}

const char * Capsule_Client::getCurrentStateString() const
{
    return stateNames[currentState];
}





void Capsule_Client::save_history( Capsule_Client::State compositeState, Capsule_Client::State subState )
{
    history[compositeState] = subState;
}

bool Capsule_Client::check_history( Capsule_Client::State compositeState, Capsule_Client::State subState )
{
    return history[compositeState] == subState;
}

void Capsule_Client::entryaction_____Debug__C__NoMaster__Debug__A__Ac__NoMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__NoMaster::Debug__A__Ac__NoMaster entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__NoMaster::Region1::Debug__A__Ac__NoMaster",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("NoMaster","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("Retry","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__NoMaster__Debug__A__En__NoMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__NoMaster::Debug__A__En__NoMaster entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__NoMaster::Region1::Debug__A__En__NoMaster",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Retry","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__NoMaster__Debug__B__Ac__NoMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__NoMaster::Debug__B__Ac__NoMaster entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__NoMaster::Region1::Debug__B__Ac__NoMaster",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("NoMaster","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__NoMaster__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__NoResponseFromServer__Debug__A__Ac__NoResponseFromServer( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__NoResponseFromServer::Debug__A__Ac__NoResponseFromServer entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__NoResponseFromServer::Region1::Debug__A__Ac__NoResponseFromServer",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("NoResponseFromServer","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("Ready","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__NoResponseFromServer__Debug__A__En__Ready( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__NoResponseFromServer::Debug__A__En__Ready entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__NoResponseFromServer::Region1::Debug__A__En__Ready",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Ready","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__NoResponseFromServer__Debug__B__Ac__NoResponseFromServer( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__NoResponseFromServer::Debug__B__Ac__NoResponseFromServer entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__NoResponseFromServer::Region1::Debug__B__Ac__NoResponseFromServer",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("WaitingForReply","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("NoResponseFromServer","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__NoResponseFromServer__Debug__B__Ex__WaitingForReply( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__NoResponseFromServer::Debug__B__Ex__WaitingForReply entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__NoResponseFromServer::Region1::Debug__B__Ex__WaitingForReply",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("WaitingForReply","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__NoResponseFromServer__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__ReqFlowDone__Debug__A__Ac__ReqFlowDone( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ReqFlowDone::Debug__A__Ac__ReqFlowDone entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ReqFlowDone::Region1::Debug__A__Ac__ReqFlowDone",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("ReqFlowDone","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("Ready","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__ReqFlowDone__Debug__A__En__Ready( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ReqFlowDone::Debug__A__En__Ready entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ReqFlowDone::Region1::Debug__A__En__Ready",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Ready","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__ReqFlowDone__Debug__B__Ac__ReqFlowDone( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ReqFlowDone::Debug__B__Ac__ReqFlowDone entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ReqFlowDone::Region1::Debug__B__Ac__ReqFlowDone",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("ProcessResponse","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("ReqFlowDone","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__ReqFlowDone__Debug__B__Ex__ProcessResponse( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ReqFlowDone::Debug__B__Ex__ProcessResponse entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ReqFlowDone::Region1::Debug__B__Ex__ProcessResponse",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("ProcessResponse","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__ReqFlowDone__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__Retry__Debug__A__Ac__Retry( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__Retry::Debug__A__Ac__Retry entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__Retry::Region1::Debug__A__Ac__Retry",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Retry","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("getMasterName","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__Retry__Debug__A__En__getMasterName( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__Retry::Debug__A__En__getMasterName entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__Retry::Region1::Debug__A__En__getMasterName",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("getMasterName","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__Retry__Debug__B__Ac__Retry( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__Retry::Debug__B__Ac__Retry entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__Retry::Region1::Debug__B__Ac__Retry",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Retry","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("Retry","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__Retry__Debug__B__Ex__Retry( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__Retry::Debug__B__Ex__Retry entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__Retry::Region1::Debug__B__Ex__Retry",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Retry","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__Retry__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__ServiceResult__Debug__A__Ac__ServiceResult( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ServiceResult::Debug__A__Ac__ServiceResult entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ServiceResult::Region1::Debug__A__Ac__ServiceResult",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("ServiceResult","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("ProcessResponse","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__ServiceResult__Debug__A__En__ProcessResponse( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ServiceResult::Debug__A__En__ProcessResponse entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ServiceResult::Region1::Debug__A__En__ProcessResponse",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("ProcessResponse","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__ServiceResult__Debug__B__Ac__ServiceResult( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ServiceResult::Debug__B__Ac__ServiceResult entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ServiceResult::Region1::Debug__B__Ac__ServiceResult",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("WaitingForReply","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("ServiceResult","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__ServiceResult__Debug__B__Ex__WaitingForReply( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ServiceResult::Debug__B__Ex__WaitingForReply entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ServiceResult::Region1::Debug__B__Ex__WaitingForReply",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("WaitingForReply","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__ServiceResult__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__StarupTransition__Debug__A__Ac__StarupTransition( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__StarupTransition::Debug__A__Ac__StarupTransition entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__StarupTransition::Region1::Debug__A__Ac__StarupTransition",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("StarupTransition","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("Ready","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__StarupTransition__Debug__A__En__Ready( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__StarupTransition::Debug__A__En__Ready entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__StarupTransition::Region1::Debug__A__En__Ready",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Ready","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__StarupTransition__Debug__B__Ac__StarupTransition( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__StarupTransition::Debug__B__Ac__StarupTransition entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__StarupTransition::Region1::Debug__B__Ac__StarupTransition",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("StandBY","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("StarupTransition","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__StarupTransition__Debug__B__Ex__StandBY( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__StarupTransition::Debug__B__Ex__StandBY entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__StarupTransition::Region1::Debug__B__Ex__StandBY",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("StandBY","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__StarupTransition__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__getMasterName__checkConfig__7__Debug__A__Ac__getMasterName__checkConfig__7( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__getMasterName__checkConfig__7::Debug__A__Ac__getMasterName__checkConfig__7 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__getMasterName__checkConfig__7::Region1::Debug__A__Ac__getMasterName__checkConfig__7",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("getMasterName__checkConfig__7","","",3,TransitionEffectBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__getMasterName__checkConfig__7__Debug__B__Ac__getMasterName__checkConfig__7( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__getMasterName__checkConfig__7::Debug__B__Ac__getMasterName__checkConfig__7 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__getMasterName__checkConfig__7::Region1::Debug__B__Ac__getMasterName__checkConfig__7",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("getMasterName","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("getMasterName__checkConfig__7","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__getMasterName__checkConfig__7__Debug__B__Ex__getMasterName( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__getMasterName__checkConfig__7::Debug__B__Ex__getMasterName entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__getMasterName__checkConfig__7::Region1::Debug__B__Ex__getMasterName",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("getMasterName","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__getMasterName__checkConfig__7__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__init__StandBY__6__Debug__A__Ac__init__StandBY__6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__init__StandBY__6::Debug__A__Ac__init__StandBY__6 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__init__StandBY__6::Region1::Debug__A__Ac__init__StandBY__6",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("init__StandBY__6","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("StandBY","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__init__StandBY__6__Debug__A__En__init__StandBY__6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__init__StandBY__6::Debug__A__En__init__StandBY__6 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__init__StandBY__6::Region1::Debug__A__En__init__StandBY__6",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("StandBY","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__init__StandBY__6__Debug__B__Ac__init__StandBY__6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__init__StandBY__6::Debug__B__Ac__init__StandBY__6 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__init__StandBY__6::Region1::Debug__B__Ac__init__StandBY__6",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("init__StandBY__6","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__init__StandBY__6__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__reqFlowInit__Debug__A__Ac__reqFlowInit( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__reqFlowInit::Debug__A__Ac__reqFlowInit entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__reqFlowInit::Region1::Debug__A__Ac__reqFlowInit",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("reqFlowInit","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("getMasterName","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__reqFlowInit__Debug__A__En__getMasterName( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__reqFlowInit::Debug__A__En__getMasterName entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__reqFlowInit::Region1::Debug__A__En__getMasterName",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("getMasterName","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__reqFlowInit__Debug__B__Ac__reqFlowInit( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__reqFlowInit::Debug__B__Ac__reqFlowInit entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__reqFlowInit::Region1::Debug__B__Ac__reqFlowInit",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Ready","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("reqFlowInit","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__reqFlowInit__Debug__B__Ex__Ready( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__reqFlowInit::Debug__B__Ex__Ready entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__reqFlowInit::Region1::Debug__B__Ex__Ready",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Ready","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__reqFlowInit__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__reqService__Debug__A__Ac__reqService( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__reqService::Debug__A__Ac__reqService entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__reqService::Region1::Debug__A__Ac__reqService",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("reqService","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("WaitingForReply","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__reqService__Debug__A__En__reqService( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__reqService::Debug__A__En__reqService entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__reqService::Region1::Debug__A__En__reqService",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("WaitingForReply","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__reqService__Debug__B__Ac__reqService( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__reqService::Debug__B__Ac__reqService entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__reqService::Region1::Debug__B__Ac__reqService",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("reqService","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__C__reqService__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Client::entryaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__InitState entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____ProcessResponse( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::ProcessResponse entry  */
    if( not Debug__SRO.checkDebug("ProcessResponse",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::ProcessResponse",(char *)"",(char *)"",(char *)"");
    std::cout<<this->getName()<<this->getIndex()<<" : Processing Response .....\n";
    int r=rand()%10;
    Timer.informIn(UMLRTTimespec(r,0),4);
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Ready( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Ready entry  */
    if( not Debug__SRO.checkDebug("Ready",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Ready",(char *)"",(char *)"",(char *)"");
    std::cout<<this->getName()<<this->getIndex()<<": is in Ready State\n";
    int r=rand()%11;
    RequestTimer.informIn(UMLRTTimespec(r,0),4);
    std::cout<<this->getName()<<this->getIndex()<<": will try to request service after "<< r<<" second \n";
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____Retry( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Retry entry  */
    if( not Debug__SRO.checkDebug("Retry",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Retry",(char *)"",(char *)"",(char *)"");
    int r=rand()%5;
    std::cout<<this->getName()<<this->getIndex()<<": The master is not available, retry in "<<r<< " second\n";
    Timer.informIn(UMLRTTimespec(r,0),4);
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____StandBY( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::StandBY entry  */
    if( not Debug__SRO.checkDebug("StandBY",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::StandBY",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____WaitingForReply( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::WaitingForReply entry  */
    if( not Debug__SRO.checkDebug("WaitingForReply",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::WaitingForReply",(char *)"",(char *)"",(char *)"");
    std::cout<<this->getName()<<this->getIndex()<<": Waiting for Response, The timeout is 60 Second\n";
    TimerId=ResponseTimer.informIn(UMLRTTimespec(60,0),4);
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____getMasterName( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::getMasterName entry  */
    if( not Debug__SRO.checkDebug("getMasterName",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::getMasterName",(char *)"",(char *)"",(char *)"");
    std::cout<<this->getName()<<this->getIndex()<<":  Request Master Information from ENV\n";
    ConfigComm.QueryConfig().send();
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__NoMaster__Debug__A__Ac__NoMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__NoMaster::Debug__A__Ac__NoMaster exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__NoMaster::Region1::Debug__A__Ac__NoMaster",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__NoMaster__Debug__A__En__NoMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__NoMaster::Debug__A__En__NoMaster exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__NoMaster::Region1::Debug__A__En__NoMaster",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__NoMaster__Debug__B__Ac__NoMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__NoMaster::Debug__B__Ac__NoMaster exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__NoMaster::Region1::Debug__B__Ac__NoMaster",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__NoMaster__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__NoResponseFromServer__Debug__A__Ac__NoResponseFromServer( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__NoResponseFromServer::Debug__A__Ac__NoResponseFromServer exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__NoResponseFromServer::Region1::Debug__A__Ac__NoResponseFromServer",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__NoResponseFromServer__Debug__A__En__Ready( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__NoResponseFromServer::Debug__A__En__Ready exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__NoResponseFromServer::Region1::Debug__A__En__Ready",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__NoResponseFromServer__Debug__B__Ac__NoResponseFromServer( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__NoResponseFromServer::Debug__B__Ac__NoResponseFromServer exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__NoResponseFromServer::Region1::Debug__B__Ac__NoResponseFromServer",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__NoResponseFromServer__Debug__B__Ex__WaitingForReply( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__NoResponseFromServer::Debug__B__Ex__WaitingForReply exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__NoResponseFromServer::Region1::Debug__B__Ex__WaitingForReply",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__NoResponseFromServer__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__ReqFlowDone__Debug__A__Ac__ReqFlowDone( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ReqFlowDone::Debug__A__Ac__ReqFlowDone exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ReqFlowDone::Region1::Debug__A__Ac__ReqFlowDone",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__ReqFlowDone__Debug__A__En__Ready( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ReqFlowDone::Debug__A__En__Ready exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ReqFlowDone::Region1::Debug__A__En__Ready",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__ReqFlowDone__Debug__B__Ac__ReqFlowDone( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ReqFlowDone::Debug__B__Ac__ReqFlowDone exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ReqFlowDone::Region1::Debug__B__Ac__ReqFlowDone",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__ReqFlowDone__Debug__B__Ex__ProcessResponse( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ReqFlowDone::Debug__B__Ex__ProcessResponse exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ReqFlowDone::Region1::Debug__B__Ex__ProcessResponse",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__ReqFlowDone__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__Retry__Debug__A__Ac__Retry( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__Retry::Debug__A__Ac__Retry exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__Retry::Region1::Debug__A__Ac__Retry",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__Retry__Debug__A__En__getMasterName( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__Retry::Debug__A__En__getMasterName exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__Retry::Region1::Debug__A__En__getMasterName",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__Retry__Debug__B__Ac__Retry( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__Retry::Debug__B__Ac__Retry exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__Retry::Region1::Debug__B__Ac__Retry",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__Retry__Debug__B__Ex__Retry( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__Retry::Debug__B__Ex__Retry exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__Retry::Region1::Debug__B__Ex__Retry",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__Retry__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__ServiceResult__Debug__A__Ac__ServiceResult( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ServiceResult::Debug__A__Ac__ServiceResult exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ServiceResult::Region1::Debug__A__Ac__ServiceResult",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__ServiceResult__Debug__A__En__ProcessResponse( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ServiceResult::Debug__A__En__ProcessResponse exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ServiceResult::Region1::Debug__A__En__ProcessResponse",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__ServiceResult__Debug__B__Ac__ServiceResult( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ServiceResult::Debug__B__Ac__ServiceResult exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ServiceResult::Region1::Debug__B__Ac__ServiceResult",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__ServiceResult__Debug__B__Ex__WaitingForReply( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ServiceResult::Debug__B__Ex__WaitingForReply exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ServiceResult::Region1::Debug__B__Ex__WaitingForReply",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__ServiceResult__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__StarupTransition__Debug__A__Ac__StarupTransition( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__StarupTransition::Debug__A__Ac__StarupTransition exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__StarupTransition::Region1::Debug__A__Ac__StarupTransition",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__StarupTransition__Debug__A__En__Ready( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__StarupTransition::Debug__A__En__Ready exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__StarupTransition::Region1::Debug__A__En__Ready",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__StarupTransition__Debug__B__Ac__StarupTransition( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__StarupTransition::Debug__B__Ac__StarupTransition exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__StarupTransition::Region1::Debug__B__Ac__StarupTransition",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__StarupTransition__Debug__B__Ex__StandBY( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__StarupTransition::Debug__B__Ex__StandBY exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__StarupTransition::Region1::Debug__B__Ex__StandBY",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__StarupTransition__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__getMasterName__checkConfig__7__Debug__A__Ac__getMasterName__checkConfig__7( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__getMasterName__checkConfig__7::Debug__A__Ac__getMasterName__checkConfig__7 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__getMasterName__checkConfig__7::Region1::Debug__A__Ac__getMasterName__checkConfig__7",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__getMasterName__checkConfig__7__Debug__B__Ac__getMasterName__checkConfig__7( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__getMasterName__checkConfig__7::Debug__B__Ac__getMasterName__checkConfig__7 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__getMasterName__checkConfig__7::Region1::Debug__B__Ac__getMasterName__checkConfig__7",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__getMasterName__checkConfig__7__Debug__B__Ex__getMasterName( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__getMasterName__checkConfig__7::Debug__B__Ex__getMasterName exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__getMasterName__checkConfig__7::Region1::Debug__B__Ex__getMasterName",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__getMasterName__checkConfig__7__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__init__StandBY__6__Debug__A__Ac__init__StandBY__6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__init__StandBY__6::Debug__A__Ac__init__StandBY__6 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__init__StandBY__6::Region1::Debug__A__Ac__init__StandBY__6",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__init__StandBY__6__Debug__A__En__init__StandBY__6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__init__StandBY__6::Debug__A__En__init__StandBY__6 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__init__StandBY__6::Region1::Debug__A__En__init__StandBY__6",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__init__StandBY__6__Debug__B__Ac__init__StandBY__6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__init__StandBY__6::Debug__B__Ac__init__StandBY__6 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__init__StandBY__6::Region1::Debug__B__Ac__init__StandBY__6",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__init__StandBY__6__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__reqFlowInit__Debug__A__Ac__reqFlowInit( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__reqFlowInit::Debug__A__Ac__reqFlowInit exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__reqFlowInit::Region1::Debug__A__Ac__reqFlowInit",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__reqFlowInit__Debug__A__En__getMasterName( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__reqFlowInit::Debug__A__En__getMasterName exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__reqFlowInit::Region1::Debug__A__En__getMasterName",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__reqFlowInit__Debug__B__Ac__reqFlowInit( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__reqFlowInit::Debug__B__Ac__reqFlowInit exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__reqFlowInit::Region1::Debug__B__Ac__reqFlowInit",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__reqFlowInit__Debug__B__Ex__Ready( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__reqFlowInit::Debug__B__Ex__Ready exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__reqFlowInit::Region1::Debug__B__Ex__Ready",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__reqFlowInit__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__reqService__Debug__A__Ac__reqService( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__reqService::Debug__A__Ac__reqService exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__reqService::Region1::Debug__A__Ac__reqService",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__reqService__Debug__A__En__reqService( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__reqService::Debug__A__En__reqService exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__reqService::Region1::Debug__A__En__reqService",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__reqService__Debug__B__Ac__reqService( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__reqService::Debug__B__Ac__reqService exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__reqService::Region1::Debug__B__Ac__reqService",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__C__reqService__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Client::exitaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__InitState exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____ProcessResponse( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::ProcessResponse exit  */
    if( not Debug__SRO.checkDebug("ProcessResponse",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::ProcessResponse",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Ready( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Ready exit  */
    if( not Debug__SRO.checkDebug("Ready",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Ready",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Retry( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Retry exit  */
    if( not Debug__SRO.checkDebug("Retry",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Retry",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____StandBY( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    #define rtdata ( (const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::StandBY exit  */
    if( not Debug__SRO.checkDebug("StandBY",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::StandBY",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

void Capsule_Client::exitaction_____WaitingForReply( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::WaitingForReply exit  */
    if( not Debug__SRO.checkDebug("WaitingForReply",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::WaitingForReply",(char *)"",(char *)"",(char *)"");
    ResponseTimer.cancelTimer(TimerId);
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____getMasterName( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    #define rtdata ( (const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::getMasterName exit  */
    if( not Debug__SRO.checkDebug("getMasterName",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::getMasterName",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

void Capsule_Client::transitionaction_____Debug__C__NoMaster__Debug__Ac__NoMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__NoMaster transition Debug__C__NoMaster::Debug__B__Ac__NoMaster,Debug__C__NoMaster::Debug__A__Ac__NoMaster,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__NoMaster::Region1::Debug__Ac__NoMaster",(char *)"Debug__B__Ac__NoMaster",(char *)"Debug__A__Ac__NoMaster",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__NoMaster__Debug__En__Retry( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__NoMaster transition Debug__C__NoMaster::Debug__A__Ac__NoMaster,Debug__C__NoMaster::Debug__A__En__NoMaster,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__NoMaster::Region1::Debug__En__Retry",(char *)"Debug__A__Ac__NoMaster",(char *)"Debug__A__En__NoMaster",(char *)"");
    int r=rand()%5;
    std::cout<<this->getName()<<this->getIndex()<<": The master is not available, retry in "<<r<< " second\n";
    Timer.informIn(UMLRTTimespec(r,0),4);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__NoMaster__Debug__end__trans__NoMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__NoMaster transition Debug__C__NoMaster::Debug__A__En__NoMaster,Debug__C__NoMaster::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__NoMaster::Region1::Debug__end__trans__NoMaster",(char *)"Debug__A__En__NoMaster",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__NoMaster__Debug__init__trans__NoMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__NoMaster transition Debug__C__NoMaster::en,Debug__C__NoMaster::Debug__B__Ac__NoMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__NoMaster::Region1::Debug__init__trans__NoMaster",(char *)"en",(char *)"Debug__B__Ac__NoMaster",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__NoResponseFromServer__Debug__AC__NoResponseFromServer( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__NoResponseFromServer transition Debug__C__NoResponseFromServer::Debug__B__Ac__NoResponseFromServer,Debug__C__NoResponseFromServer::Debug__A__Ac__NoResponseFromServer,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__NoResponseFromServer::Region1::Debug__AC__NoResponseFromServer",(char *)"Debug__B__Ac__NoResponseFromServer",(char *)"Debug__A__Ac__NoResponseFromServer",(char *)"");
    std::cout<<this->getName()<<this->getIndex()<<": Service Failur.....\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__NoResponseFromServer__Debug__En__Ready( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__NoResponseFromServer transition Debug__C__NoResponseFromServer::Debug__A__Ac__NoResponseFromServer,Debug__C__NoResponseFromServer::Debug__A__En__Ready,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__NoResponseFromServer::Region1::Debug__En__Ready",(char *)"Debug__A__Ac__NoResponseFromServer",(char *)"Debug__A__En__Ready",(char *)"");
    std::cout<<this->getName()<<this->getIndex()<<": is in Ready State\n";
    int r=rand()%11;
    RequestTimer.informIn(UMLRTTimespec(r,0),4);
    std::cout<<this->getName()<<this->getIndex()<<": will try to request service after "<< r<<" second \n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__NoResponseFromServer__Debug__Ex__WaitingForReply( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__NoResponseFromServer transition Debug__C__NoResponseFromServer::Debug__B__Ex__WaitingForReply,Debug__C__NoResponseFromServer::Debug__B__Ac__NoResponseFromServer,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__NoResponseFromServer::Region1::Debug__Ex__WaitingForReply",(char *)"Debug__B__Ex__WaitingForReply",(char *)"Debug__B__Ac__NoResponseFromServer",(char *)"");
    ResponseTimer.cancelTimer(TimerId);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__NoResponseFromServer__Debug__end__trans__NoResponseFromServer( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__NoResponseFromServer transition Debug__C__NoResponseFromServer::Debug__A__En__Ready,Debug__C__NoResponseFromServer::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__NoResponseFromServer::Region1::Debug__end__trans__NoResponseFromServer",(char *)"Debug__A__En__Ready",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__NoResponseFromServer__Debug__init__trans__NoResponseFromServer( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__NoResponseFromServer transition Debug__C__NoResponseFromServer::en,Debug__C__NoResponseFromServer::Debug__B__Ex__WaitingForReply */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__NoResponseFromServer::Region1::Debug__init__trans__NoResponseFromServer",(char *)"en",(char *)"Debug__B__Ex__WaitingForReply",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__ReqFlowDone__Debug__AC__ReqFlowDone( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ReqFlowDone transition Debug__C__ReqFlowDone::Debug__B__Ac__ReqFlowDone,Debug__C__ReqFlowDone::Debug__A__Ac__ReqFlowDone,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ReqFlowDone::Region1::Debug__AC__ReqFlowDone",(char *)"Debug__B__Ac__ReqFlowDone",(char *)"Debug__A__Ac__ReqFlowDone",(char *)"");
    std::cout<<this->getName()<<this->getIndex()<<": The service Request has been done sucessfully\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__ReqFlowDone__Debug__En__Ready( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ReqFlowDone transition Debug__C__ReqFlowDone::Debug__A__Ac__ReqFlowDone,Debug__C__ReqFlowDone::Debug__A__En__Ready,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ReqFlowDone::Region1::Debug__En__Ready",(char *)"Debug__A__Ac__ReqFlowDone",(char *)"Debug__A__En__Ready",(char *)"");
    std::cout<<this->getName()<<this->getIndex()<<": is in Ready State\n";
    int r=rand()%11;
    RequestTimer.informIn(UMLRTTimespec(r,0),4);
    std::cout<<this->getName()<<this->getIndex()<<": will try to request service after "<< r<<" second \n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__ReqFlowDone__Debug__Ex__ProcessResponse( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ReqFlowDone transition Debug__C__ReqFlowDone::Debug__B__Ex__ProcessResponse,Debug__C__ReqFlowDone::Debug__B__Ac__ReqFlowDone,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ReqFlowDone::Region1::Debug__Ex__ProcessResponse",(char *)"Debug__B__Ex__ProcessResponse",(char *)"Debug__B__Ac__ReqFlowDone",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__ReqFlowDone__Debug__end__trans__ReqFlowDone( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ReqFlowDone transition Debug__C__ReqFlowDone::Debug__A__En__Ready,Debug__C__ReqFlowDone::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ReqFlowDone::Region1::Debug__end__trans__ReqFlowDone",(char *)"Debug__A__En__Ready",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__ReqFlowDone__Debug__init__trans__ReqFlowDone( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ReqFlowDone transition Debug__C__ReqFlowDone::en,Debug__C__ReqFlowDone::Debug__B__Ex__ProcessResponse */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ReqFlowDone::Region1::Debug__init__trans__ReqFlowDone",(char *)"en",(char *)"Debug__B__Ex__ProcessResponse",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__Retry__Debug__AC__Retry( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__Retry transition Debug__C__Retry::Debug__B__Ac__Retry,Debug__C__Retry::Debug__A__Ac__Retry,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__Retry::Region1::Debug__AC__Retry",(char *)"Debug__B__Ac__Retry",(char *)"Debug__A__Ac__Retry",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__Retry__Debug__En__getMasterName( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__Retry transition Debug__C__Retry::Debug__A__Ac__Retry,Debug__C__Retry::Debug__A__En__getMasterName,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__Retry::Region1::Debug__En__getMasterName",(char *)"Debug__A__Ac__Retry",(char *)"Debug__A__En__getMasterName",(char *)"");
    std::cout<<this->getName()<<this->getIndex()<<":  Request Master Information from ENV\n";
    ConfigComm.QueryConfig().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__Retry__Debug__Ex__Retry( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__Retry transition Debug__C__Retry::Debug__B__Ex__Retry,Debug__C__Retry::Debug__B__Ac__Retry,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__Retry::Region1::Debug__Ex__Retry",(char *)"Debug__B__Ex__Retry",(char *)"Debug__B__Ac__Retry",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__Retry__Debug__end__trans__Retry( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__Retry transition Debug__C__Retry::Debug__A__En__getMasterName,Debug__C__Retry::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__Retry::Region1::Debug__end__trans__Retry",(char *)"Debug__A__En__getMasterName",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__Retry__Debug__init__trans__Retry( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__Retry transition Debug__C__Retry::en,Debug__C__Retry::Debug__B__Ex__Retry */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__Retry::Region1::Debug__init__trans__Retry",(char *)"en",(char *)"Debug__B__Ex__Retry",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__ServiceResult__Debug__AC__ServiceResult( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ServiceResult transition Debug__C__ServiceResult::Debug__B__Ac__ServiceResult,Debug__C__ServiceResult::Debug__A__Ac__ServiceResult,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ServiceResult::Region1::Debug__AC__ServiceResult",(char *)"Debug__B__Ac__ServiceResult",(char *)"Debug__A__Ac__ServiceResult",(char *)"");
    std::cout<<this->getName()<<this->getIndex()<<": got reponse from server, go to process response state\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__ServiceResult__Debug__En__ProcessResponse( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ServiceResult transition Debug__C__ServiceResult::Debug__A__Ac__ServiceResult,Debug__C__ServiceResult::Debug__A__En__ProcessResponse,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ServiceResult::Region1::Debug__En__ProcessResponse",(char *)"Debug__A__Ac__ServiceResult",(char *)"Debug__A__En__ProcessResponse",(char *)"");
    std::cout<<this->getName()<<this->getIndex()<<" : Processing Response .....\n";
    int r=rand()%10;
    Timer.informIn(UMLRTTimespec(r,0),4);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__ServiceResult__Debug__Ex__WaitingForReply( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ServiceResult transition Debug__C__ServiceResult::Debug__B__Ex__WaitingForReply,Debug__C__ServiceResult::Debug__B__Ac__ServiceResult,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ServiceResult::Region1::Debug__Ex__WaitingForReply",(char *)"Debug__B__Ex__WaitingForReply",(char *)"Debug__B__Ac__ServiceResult",(char *)"");
    ResponseTimer.cancelTimer(TimerId);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__ServiceResult__Debug__end__trans__ServiceResult( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ServiceResult transition Debug__C__ServiceResult::Debug__A__En__ProcessResponse,Debug__C__ServiceResult::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ServiceResult::Region1::Debug__end__trans__ServiceResult",(char *)"Debug__A__En__ProcessResponse",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__ServiceResult__Debug__init__trans__ServiceResult( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__ServiceResult transition Debug__C__ServiceResult::en,Debug__C__ServiceResult::Debug__B__Ex__WaitingForReply */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__ServiceResult::Region1::Debug__init__trans__ServiceResult",(char *)"en",(char *)"Debug__B__Ex__WaitingForReply",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__StarupTransition__Debug__AC__StarupTransition( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__StarupTransition transition Debug__C__StarupTransition::Debug__B__Ac__StarupTransition,Debug__C__StarupTransition::Debug__A__Ac__StarupTransition,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__StarupTransition::Region1::Debug__AC__StarupTransition",(char *)"Debug__B__Ac__StarupTransition",(char *)"Debug__A__Ac__StarupTransition",(char *)"");
    std::cout<<this->getName()<<this->getIndex()<<" Client is startingUP \n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__StarupTransition__Debug__En__Ready( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__StarupTransition transition Debug__C__StarupTransition::Debug__A__Ac__StarupTransition,Debug__C__StarupTransition::Debug__A__En__Ready,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__StarupTransition::Region1::Debug__En__Ready",(char *)"Debug__A__Ac__StarupTransition",(char *)"Debug__A__En__Ready",(char *)"");
    std::cout<<this->getName()<<this->getIndex()<<": is in Ready State\n";
    int r=rand()%11;
    RequestTimer.informIn(UMLRTTimespec(r,0),4);
    std::cout<<this->getName()<<this->getIndex()<<": will try to request service after "<< r<<" second \n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__StarupTransition__Debug__Ex__StandBY( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__StarupTransition transition Debug__C__StarupTransition::Debug__B__Ex__StandBY,Debug__C__StarupTransition::Debug__B__Ac__StarupTransition,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__StarupTransition::Region1::Debug__Ex__StandBY",(char *)"Debug__B__Ex__StandBY",(char *)"Debug__B__Ac__StarupTransition",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__StarupTransition__Debug__end__trans__StarupTransition( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__StarupTransition transition Debug__C__StarupTransition::Debug__A__En__Ready,Debug__C__StarupTransition::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__StarupTransition::Region1::Debug__end__trans__StarupTransition",(char *)"Debug__A__En__Ready",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__StarupTransition__Debug__init__trans__StarupTransition( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__StarupTransition transition Debug__C__StarupTransition::en,Debug__C__StarupTransition::Debug__B__Ex__StandBY */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__StarupTransition::Region1::Debug__init__trans__StarupTransition",(char *)"en",(char *)"Debug__B__Ex__StandBY",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__getMasterName__checkConfig__7__Debug__AC__getMasterName__checkConfig__7( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__getMasterName__checkConfig__7 transition Debug__C__getMasterName__checkConfig__7::Debug__B__Ac__getMasterName__checkConfig__7,Debug__C__getMasterName__checkConfig__7::Debug__A__Ac__getMasterName__checkConfig__7,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__getMasterName__checkConfig__7::Region1::Debug__AC__getMasterName__checkConfig__7",(char *)"Debug__B__Ac__getMasterName__checkConfig__7",(char *)"Debug__A__Ac__getMasterName__checkConfig__7",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__getMasterName__checkConfig__7__Debug__Ex__getMasterName( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__getMasterName__checkConfig__7 transition Debug__C__getMasterName__checkConfig__7::Debug__B__Ex__getMasterName,Debug__C__getMasterName__checkConfig__7::Debug__B__Ac__getMasterName__checkConfig__7,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__getMasterName__checkConfig__7::Region1::Debug__Ex__getMasterName",(char *)"Debug__B__Ex__getMasterName",(char *)"Debug__B__Ac__getMasterName__checkConfig__7",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__getMasterName__checkConfig__7__Debug__end__trans__getMasterName__checkConfig__7( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__getMasterName__checkConfig__7 transition Debug__C__getMasterName__checkConfig__7::Debug__A__Ac__getMasterName__checkConfig__7,Debug__C__getMasterName__checkConfig__7::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__getMasterName__checkConfig__7::Region1::Debug__end__trans__getMasterName__checkConfig__7",(char *)"Debug__A__Ac__getMasterName__checkConfig__7",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__init__StandBY__6__Debug__Ac__init__StandBY__6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__init__StandBY__6 transition Debug__C__init__StandBY__6::Debug__B__Ac__init__StandBY__6,Debug__C__init__StandBY__6::Debug__A__Ac__init__StandBY__6,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__init__StandBY__6::Region1::Debug__Ac__init__StandBY__6",(char *)"Debug__B__Ac__init__StandBY__6",(char *)"Debug__A__Ac__init__StandBY__6",(char *)"");
    std::cout<<this->getName()<<this->getIndex()<<": Intialization\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__init__StandBY__6__Debug__En__StandBY( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__init__StandBY__6 transition Debug__C__init__StandBY__6::Debug__A__Ac__init__StandBY__6,Debug__C__init__StandBY__6::Debug__A__En__init__StandBY__6,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__init__StandBY__6::Region1::Debug__En__StandBY",(char *)"Debug__A__Ac__init__StandBY__6",(char *)"Debug__A__En__init__StandBY__6",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__init__StandBY__6__Debug__end__trans__init__StandBY__6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__init__StandBY__6 transition Debug__C__init__StandBY__6::Debug__A__En__init__StandBY__6,Debug__C__init__StandBY__6::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__init__StandBY__6::Region1::Debug__end__trans__init__StandBY__6",(char *)"Debug__A__En__init__StandBY__6",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__init__StandBY__6__Debug__init__trans__init__StandBY__6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__init__StandBY__6 transition Debug__C__init__StandBY__6::en,Debug__C__init__StandBY__6::Debug__B__Ac__init__StandBY__6 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__init__StandBY__6::Region1::Debug__init__trans__init__StandBY__6",(char *)"en",(char *)"Debug__B__Ac__init__StandBY__6",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__reqFlowInit__Debug__AC__reqFlowInit( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__reqFlowInit transition Debug__C__reqFlowInit::Debug__B__Ac__reqFlowInit,Debug__C__reqFlowInit::Debug__A__Ac__reqFlowInit,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__reqFlowInit::Region1::Debug__AC__reqFlowInit",(char *)"Debug__B__Ac__reqFlowInit",(char *)"Debug__A__Ac__reqFlowInit",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__reqFlowInit__Debug__En__getMasterName( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__reqFlowInit transition Debug__C__reqFlowInit::Debug__A__Ac__reqFlowInit,Debug__C__reqFlowInit::Debug__A__En__getMasterName,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__reqFlowInit::Region1::Debug__En__getMasterName",(char *)"Debug__A__Ac__reqFlowInit",(char *)"Debug__A__En__getMasterName",(char *)"");
    std::cout<<this->getName()<<this->getIndex()<<":  Request Master Information from ENV\n";
    ConfigComm.QueryConfig().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__reqFlowInit__Debug__Ex__Ready( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__reqFlowInit transition Debug__C__reqFlowInit::Debug__B__Ex__Ready,Debug__C__reqFlowInit::Debug__B__Ac__reqFlowInit,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__reqFlowInit::Region1::Debug__Ex__Ready",(char *)"Debug__B__Ex__Ready",(char *)"Debug__B__Ac__reqFlowInit",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__reqFlowInit__Debug__end__trans__reqFlowInit( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__reqFlowInit transition Debug__C__reqFlowInit::Debug__A__En__getMasterName,Debug__C__reqFlowInit::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__reqFlowInit::Region1::Debug__end__trans__reqFlowInit",(char *)"Debug__A__En__getMasterName",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__reqFlowInit__Debug__init__trans__reqFlowInit( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__reqFlowInit transition Debug__C__reqFlowInit::en,Debug__C__reqFlowInit::Debug__B__Ex__Ready */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__reqFlowInit::Region1::Debug__init__trans__reqFlowInit",(char *)"en",(char *)"Debug__B__Ex__Ready",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__reqService__Debug__Ac__reqService( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__reqService transition Debug__C__reqService::Debug__B__Ac__reqService,Debug__C__reqService::Debug__A__Ac__reqService,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__reqService::Region1::Debug__Ac__reqService",(char *)"Debug__B__Ac__reqService",(char *)"Debug__A__Ac__reqService",(char *)"");
    if (config.MasterList[0] && config.MasterList[1])
    {
    int r=rand()%2;
    if (r==0)
    {
    Server1Comm.Request(0).send();
    std::cout<<this->getName()<<this->getIndex()<<": sending Request to Server1\n";
    }
    else{
    Server2Comm.Request(0).send();
    std::cout<<this->getName()<<this->getIndex()<<": sending Request to Server2\n";
    }
    }
    else if (config.MasterList[0]){
    Server1Comm.Request(0).send();
    std::cout<<this->getName()<<this->getIndex()<<": sending Request to Server1\n";
    }
    else
    {
    Server2Comm.Request(0).send();
    std::cout<<this->getName()<<this->getIndex()<<": sending Request to Server2\n";
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__reqService__Debug__En__WaitingForReply( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__reqService transition Debug__C__reqService::Debug__A__Ac__reqService,Debug__C__reqService::Debug__A__En__reqService,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__reqService::Region1::Debug__En__WaitingForReply",(char *)"Debug__A__Ac__reqService",(char *)"Debug__A__En__reqService",(char *)"");
    std::cout<<this->getName()<<this->getIndex()<<": Waiting for Response, The timeout is 60 Second\n";
    TimerId=ResponseTimer.informIn(UMLRTTimespec(60,0),4);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__reqService__Debug__end__trans__reqService( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__reqService transition Debug__C__reqService::Debug__A__En__reqService,Debug__C__reqService::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__reqService::Region1::Debug__end__trans__reqService",(char *)"Debug__A__En__reqService",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__C__reqService__Debug__init__trans__reqService( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client::Debug__C__reqService transition Debug__C__reqService::en,Debug__C__reqService::Debug__B__Ac__reqService */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__C__reqService::Region1::Debug__init__trans__reqService",(char *)"en",(char *)"Debug__B__Ac__reqService",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__InitDebug( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition init,Debug__InitState */
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

void Capsule_Client::transitionaction_____Debug__NoMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition checkConfig,Debug__Path__NoMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__NoMaster",(char *)"checkConfig",(char *)"Debug__Path__NoMaster",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__NoMaster__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__C__NoMaster::ex,Retry */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__NoMaster__E",(char *)"ex",(char *)"Retry",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__NoMaster__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__Path__NoMaster,Debug__C__NoMaster::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__NoMaster__S",(char *)"Debug__Path__NoMaster",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__NoMaster__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__C__NoMaster::new_exitpoint_3,Debug__C__NoMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__NoMaster__dbg",(char *)"Debug__C__NoMaster",(char *)"Debug__C__NoMaster",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__NoResponseFromServer( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition WaitingForReply,Debug__Path__NoResponseFromServer,timeout:ResponseTimer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__NoResponseFromServer",(char *)"WaitingForReply",(char *)"Debug__Path__NoResponseFromServer",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__NoResponseFromServer__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__C__NoResponseFromServer::ex,Ready */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__NoResponseFromServer__E",(char *)"ex",(char *)"Ready",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__NoResponseFromServer__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__Path__NoResponseFromServer,Debug__C__NoResponseFromServer::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__NoResponseFromServer__S",(char *)"Debug__Path__NoResponseFromServer",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__NoResponseFromServer__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__C__NoResponseFromServer::new_exitpoint_4,Debug__C__NoResponseFromServer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__NoResponseFromServer__dbg",(char *)"Debug__C__NoResponseFromServer",(char *)"Debug__C__NoResponseFromServer",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__ReqFlowDone( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition ProcessResponse,Debug__Path__ReqFlowDone,timeout:Timer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__ReqFlowDone",(char *)"ProcessResponse",(char *)"Debug__Path__ReqFlowDone",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__ReqFlowDone__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__C__ReqFlowDone::ex,Ready */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__ReqFlowDone__E",(char *)"ex",(char *)"Ready",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__ReqFlowDone__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__Path__ReqFlowDone,Debug__C__ReqFlowDone::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__ReqFlowDone__S",(char *)"Debug__Path__ReqFlowDone",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__ReqFlowDone__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__C__ReqFlowDone::new_exitpoint_5,Debug__C__ReqFlowDone */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__ReqFlowDone__dbg",(char *)"Debug__C__ReqFlowDone",(char *)"Debug__C__ReqFlowDone",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__Retry( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Retry,Debug__Path__Retry,timeout:Timer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__Retry",(char *)"Retry",(char *)"Debug__Path__Retry",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__Retry__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__C__Retry::ex,getMasterName */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__Retry__E",(char *)"ex",(char *)"getMasterName",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__Retry__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__Path__Retry,Debug__C__Retry::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__Retry__S",(char *)"Debug__Path__Retry",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__Retry__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__C__Retry::new_exitpoint_2,Debug__C__Retry */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__Retry__dbg",(char *)"Debug__C__Retry",(char *)"Debug__C__Retry",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__ServiceResult( const UMLRTMessage * msg )
{
    #define umlrtparam_Result ( *(int *)msg->getParam( 0 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition WaitingForReply,Debug__Path__ServiceResult,Reply:Server1Comm:Server2Comm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__ServiceResult",(char *)"WaitingForReply",(char *)"Debug__Path__ServiceResult",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_Result
}

void Capsule_Client::transitionaction_____Debug__ServiceResult__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__C__ServiceResult::ex,ProcessResponse */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__ServiceResult__E",(char *)"ex",(char *)"ProcessResponse",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__ServiceResult__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__Path__ServiceResult,Debug__C__ServiceResult::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__ServiceResult__S",(char *)"Debug__Path__ServiceResult",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__ServiceResult__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__C__ServiceResult::new_exitpoint_9,Debug__C__ServiceResult */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__ServiceResult__dbg",(char *)"Debug__C__ServiceResult",(char *)"Debug__C__ServiceResult",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__StarupTransition( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    #define rtdata ( (const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition StandBY,Debug__Path__StarupTransition,StartUp:ConfigComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__StarupTransition",(char *)"StandBY",(char *)"Debug__Path__StarupTransition",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

void Capsule_Client::transitionaction_____Debug__StarupTransition__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__C__StarupTransition::ex,Ready */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__StarupTransition__E",(char *)"ex",(char *)"Ready",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__StarupTransition__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__Path__StarupTransition,Debug__C__StarupTransition::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__StarupTransition__S",(char *)"Debug__Path__StarupTransition",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__StarupTransition__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__C__StarupTransition::new_exitpoint_1,Debug__C__StarupTransition */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__StarupTransition__dbg",(char *)"Debug__C__StarupTransition",(char *)"Debug__C__StarupTransition",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__getMasterName__checkConfig__7( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    #define rtdata ( (const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition getMasterName,Debug__Path__getMasterName__checkConfig__7,ReplyConfig:ConfigComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__getMasterName__checkConfig__7",(char *)"getMasterName",(char *)"Debug__Path__getMasterName__checkConfig__7",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

void Capsule_Client::transitionaction_____Debug__getMasterName__checkConfig__7__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__C__getMasterName__checkConfig__7::ex,checkConfig */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__getMasterName__checkConfig__7__E",(char *)"ex",(char *)"checkConfig",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__getMasterName__checkConfig__7__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__Path__getMasterName__checkConfig__7,Debug__C__getMasterName__checkConfig__7::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__getMasterName__checkConfig__7__S",(char *)"Debug__Path__getMasterName__checkConfig__7",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__getMasterName__checkConfig__7__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__C__getMasterName__checkConfig__7::new_exitpoint_7,Debug__C__getMasterName__checkConfig__7 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__getMasterName__checkConfig__7__dbg",(char *)"Debug__C__getMasterName__checkConfig__7",(char *)"Debug__C__getMasterName__checkConfig__7",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__init__StandBY__6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__InitState,Debug__Path__init__StandBY__6,null:extComm */
    if (this->Debug__SRO.getExecMode()==Stepping){
    Debug__SRO.addTransitionsFromState("RunAsSlave","NokeepAlive","TryBeMaster","timeout","Timing");
    Debug__SRO.addTransitionsFromState("RunAsMaster","KeepAlive","RunAsMaster","timeout","Timing");
    Debug__SRO.addTransitionsFromState("WaitingForReply","ServiceResult","ProcessResponse","Reply","Services");
    Debug__SRO.addTransitionsFromState("Slave","backtoslave","RunAsSlave","","");
    Debug__SRO.addTransitionsFromState("RunAsMaster","ServerFaliure","Failure","timeout","Timing");
    Debug__SRO.addTransitionsFromState("BeMaster","BeingMaster","RunAsMaster","","");
    Debug__SRO.addTransitionsFromState("Init","","StandBy","","");
    Debug__SRO.addTransitionsFromState("checkConfig","NoMaster","Retry","","");
    Debug__SRO.addTransitionsFromState("init","","WaitForEcho","","");
    Debug__SRO.addTransitionsFromState("Ready","reqFlowInit","getMasterName","timeout","Timing");
    Debug__SRO.addTransitionsFromState("Initial1","","RunAsSlave","","");
    Debug__SRO.addTransitionsFromState("CheckConfig","BeSlave","Backup","","");
    Debug__SRO.addTransitionsFromState("WaitingForReply","NoResponseFromServer","Ready","timeout","Timing");
    Debug__SRO.addTransitionsFromState("Retry","Retry","getMasterName","timeout","Timing");
    Debug__SRO.addTransitionsFromState("Choice1","ActiveMode","BeMaster","","");
    Debug__SRO.addTransitionsFromState("getMasterName","","checkConfig","ReplyConfig","Config");
    Debug__SRO.addTransitionsFromState("StandBY","StarupTransition","Ready","StartUp","Config");
    Debug__SRO.addTransitionsFromState("ExitPoint1","","BeMaster","","");
    Debug__SRO.addTransitionsFromState("RunAsSlave","KeepAliveMsg","RunAsSlave","IAmAlive","FailOver");
    Debug__SRO.addTransitionsFromState("StandBy","","CheckConfig","StartUp","Config");
    Debug__SRO.addTransitionsFromState("TryBeMaster","ReplyConfig","Choice2","ReplyConfig","Config");
    Debug__SRO.addTransitionsFromState("Choice1","PassiveMode","Backup","","");
    Debug__SRO.addTransitionsFromState("init","","StandBY","","");
    Debug__SRO.addTransitionsFromState("CheckConfig","initTimer","RunAsMaster","","");
    Debug__SRO.addTransitionsFromState("Failure","purgeotherMessage","Failure","*","Services");
    Debug__SRO.addTransitionsFromState("Failure","purgeotherMessage","Failure","*","FailOver");
    Debug__SRO.addTransitionsFromState("RunAsMaster","MasterAnnounce","RunAsMaster","timeout","Timing");
    Debug__SRO.addTransitionsFromState("Failure","Recover","Choice1","timeout","Timing");
    Debug__SRO.addTransitionsFromState("Choice2","CheckNoMaster","ExitPoint1","","");
    Debug__SRO.addTransitionsFromState("checkConfig","reqService","WaitingForReply","","");
    Debug__SRO.addTransitionsFromState("WaitForEcho","DoEcho","WaitForEcho","Echo","Echo");
    Debug__SRO.addTransitionsFromState("RunAsMaster","ServiceRequest","RunAsMaster","Request","Services");
    Debug__SRO.addTransitionsFromState("Choice2","backtoslave1","Slave","","");
    Debug__SRO.addTransitionsFromState("ProcessResponse","ReqFlowDone","Ready","timeout","Timing");
    std::cout<<this->getName()<<": Connection with debugger is in progress\n";
    char  tempS[256];
    sprintf(tempS,"%s%d",this->getName(),(int)this->getIndex());
    extComm.registerToControl(tempS).send();
    Debug__sendEvent(debugEvents::DEBUG,debugEvents::REGISTER,this->getName(),this->getIndex(),msg->getSignalName(),(char *) "",(char *) "",(char *) "",(char *)"",(char *) "");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__init__StandBY__6__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__C__init__StandBY__6::ex,StandBY */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__init__StandBY__6__E",(char *)"ex",(char *)"StandBY",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__init__StandBY__6__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__Path__init__StandBY__6,Debug__C__init__StandBY__6::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__init__StandBY__6__S",(char *)"Debug__Path__init__StandBY__6",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__init__StandBY__6__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__C__init__StandBY__6::new_exitpoint_6,Debug__C__init__StandBY__6 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__init__StandBY__6__dbg",(char *)"Debug__C__init__StandBY__6",(char *)"Debug__C__init__StandBY__6",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__reqFlowInit( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Ready,Debug__Path__reqFlowInit,timeout:RequestTimer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__reqFlowInit",(char *)"Ready",(char *)"Debug__Path__reqFlowInit",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__reqFlowInit__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__C__reqFlowInit::ex,getMasterName */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__reqFlowInit__E",(char *)"ex",(char *)"getMasterName",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__reqFlowInit__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__Path__reqFlowInit,Debug__C__reqFlowInit::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__reqFlowInit__S",(char *)"Debug__Path__reqFlowInit",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__reqFlowInit__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__C__reqFlowInit::new_exitpoint_8,Debug__C__reqFlowInit */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__reqFlowInit__dbg",(char *)"Debug__C__reqFlowInit",(char *)"Debug__C__reqFlowInit",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__reqService( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition checkConfig,Debug__Path__reqService */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__reqService",(char *)"checkConfig",(char *)"Debug__Path__reqService",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__reqService__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__C__reqService::ex,WaitingForReply */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__reqService__E",(char *)"ex",(char *)"WaitingForReply",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__reqService__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__Path__reqService,Debug__C__reqService::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__reqService__S",(char *)"Debug__Path__reqService",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Debug__reqService__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__C__reqService::new_exitpoint_10,Debug__C__reqService */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Debug__reqService__dbg",(char *)"Debug__C__reqService",(char *)"Debug__C__reqService",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____NoMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__Path__NoMaster,Retry */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::NoMaster",(char *)"Debug__Path__NoMaster",(char *)"Retry",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____NoResponseFromServer( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__Path__NoResponseFromServer,Ready */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::NoResponseFromServer",(char *)"Debug__Path__NoResponseFromServer",(char *)"Ready",(char *)"");
    std::cout<<this->getName()<<this->getIndex()<<": Service Failur.....\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____ReqFlowDone( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__Path__ReqFlowDone,Ready */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::ReqFlowDone",(char *)"Debug__Path__ReqFlowDone",(char *)"Ready",(char *)"");
    std::cout<<this->getName()<<this->getIndex()<<": The service Request has been done sucessfully\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____Retry( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__Path__Retry,getMasterName */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::Retry",(char *)"Debug__Path__Retry",(char *)"getMasterName",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____ServiceResult( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__Path__ServiceResult,ProcessResponse */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::ServiceResult",(char *)"Debug__Path__ServiceResult",(char *)"ProcessResponse",(char *)"");
    std::cout<<this->getName()<<this->getIndex()<<": got reponse from server, go to process response state\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____StarupTransition( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__Path__StarupTransition,Ready */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::StarupTransition",(char *)"Debug__Path__StarupTransition",(char *)"Ready",(char *)"");
    std::cout<<this->getName()<<this->getIndex()<<" Client is startingUP \n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____getMasterName__checkConfig__7( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__Path__getMasterName__checkConfig__7,checkConfig */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::getMasterName__checkConfig__7",(char *)"Debug__Path__getMasterName__checkConfig__7",(char *)"checkConfig",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____init__StandBY__6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__Path__init__StandBY__6,StandBY */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::init__StandBY__6",(char *)"Debug__Path__init__StandBY__6",(char *)"StandBY",(char *)"");
    std::cout<<this->getName()<<this->getIndex()<<": Intialization\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____reqFlowInit( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__Path__reqFlowInit,getMasterName */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::reqFlowInit",(char *)"Debug__Path__reqFlowInit",(char *)"getMasterName",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____reqService( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client transition Debug__Path__reqService,WaitingForReply */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Client::ClientStateMachine::Region1::reqService",(char *)"Debug__Path__reqService",(char *)"WaitingForReply",(char *)"");
    if (config.MasterList[0] && config.MasterList[1])
    {
    int r=rand()%2;
    if (r==0)
    {
    Server1Comm.Request(0).send();
    std::cout<<this->getName()<<this->getIndex()<<": sending Request to Server1\n";
    }
    else{
    Server2Comm.Request(0).send();
    std::cout<<this->getName()<<this->getIndex()<<": sending Request to Server2\n";
    }
    }
    else if (config.MasterList[0]){
    Server1Comm.Request(0).send();
    std::cout<<this->getName()<<this->getIndex()<<": sending Request to Server1\n";
    }
    else
    {
    Server2Comm.Request(0).send();
    std::cout<<this->getName()<<this->getIndex()<<": sending Request to Server2\n";
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Client::action_____Debug__NoMaster__S__Debug__GuardNoMaster( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    #define rtdata ( (const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client guard Debug__Path__NoMaster,Debug__C__NoMaster::en */
    return Debug__SRO.checkDebug("checkConfig","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

bool Capsule_Client::action_____Debug__NoResponseFromServer__S__Debug__GuardNoResponseFromServer( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client guard Debug__Path__NoResponseFromServer,Debug__C__NoResponseFromServer::en */
    return Debug__SRO.checkDebug("WaitingForReply",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Client::action_____Debug__ReqFlowDone__S__Debug__GuardReqFlowDone( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client guard Debug__Path__ReqFlowDone,Debug__C__ReqFlowDone::en */
    return Debug__SRO.checkDebug("ProcessResponse",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Client::action_____Debug__Retry__S__Debug__GuardRetry( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client guard Debug__Path__Retry,Debug__C__Retry::en */
    return Debug__SRO.checkDebug("Retry",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Client::action_____Debug__ServiceResult__S__Debug__GuardServiceResult( const UMLRTMessage * msg )
{
    #define umlrtparam_Result ( *(int *)msg->getParam( 0 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client guard Debug__Path__ServiceResult,Debug__C__ServiceResult::en */
    return Debug__SRO.checkDebug("WaitingForReply",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_Result
}

bool Capsule_Client::action_____Debug__StarupTransition__S__Debug__GuardStarupTransition( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    #define rtdata ( (const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client guard Debug__Path__StarupTransition,Debug__C__StarupTransition::en */
    return Debug__SRO.checkDebug("StandBY",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

bool Capsule_Client::action_____Debug__getMasterName__checkConfig__7__S__Debug__GuardgetMasterName__checkConfig__7( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    #define rtdata ( (const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client guard Debug__Path__getMasterName__checkConfig__7,Debug__C__getMasterName__checkConfig__7::en */
    return Debug__SRO.checkDebug("getMasterName",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

bool Capsule_Client::action_____Debug__init__StandBY__6__S__Debug__Guardinit__StandBY__6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client guard Debug__Path__init__StandBY__6,Debug__C__init__StandBY__6::en */
    return Debug__SRO.checkDebug("init","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Client::action_____Debug__reqFlowInit__S__Debug__GuardreqFlowInit( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client guard Debug__Path__reqFlowInit,Debug__C__reqFlowInit::en */
    return Debug__SRO.checkDebug("Ready",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Client::action_____Debug__reqService__MasterIsAvailable( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    #define rtdata ( (const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client guard checkConfig,Debug__Path__reqService */
    config=umlrtparam_config;
    if (config.MasterList[0] || config.MasterList[1])
    return true;
    else 
    return false;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

bool Capsule_Client::action_____Debug__reqService__S__Debug__GuardreqService( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    #define rtdata ( (const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Client guard Debug__Path__reqService,Debug__C__reqService::en */
    return Debug__SRO.checkDebug("checkConfig","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

void Capsule_Client::actionchain_____Debug__C__NoMaster__Debug__Ac__NoMaster( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__NoMaster__Debug__B__Ac__NoMaster( msg );
    transitionaction_____Debug__C__NoMaster__Debug__Ac__NoMaster( msg );
    entryaction_____Debug__C__NoMaster__Debug__A__Ac__NoMaster( msg );
}

void Capsule_Client::actionchain_____Debug__C__NoMaster__Debug__En__Retry( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__NoMaster__Debug__A__Ac__NoMaster( msg );
    transitionaction_____Debug__C__NoMaster__Debug__En__Retry( msg );
    entryaction_____Debug__C__NoMaster__Debug__A__En__NoMaster( msg );
}

void Capsule_Client::actionchain_____Debug__C__NoMaster__Debug__end__trans__NoMaster( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__NoMaster__Debug__A__En__NoMaster( msg );
    transitionaction_____Debug__C__NoMaster__Debug__end__trans__NoMaster( msg );
    save_history( Debug__C__NoMaster, Debug__C__NoMaster__Debug__A__En__NoMaster );
}

void Capsule_Client::actionchain_____Debug__C__NoMaster__Debug__init__trans__NoMaster( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__NoMaster__Debug__init__trans__NoMaster( msg );
    entryaction_____Debug__C__NoMaster__Debug__B__Ac__NoMaster( msg );
}

void Capsule_Client::actionchain_____Debug__C__NoMaster__new_transition_21( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__NoMaster__Debug__B__Ac__NoMaster( msg );
}

void Capsule_Client::actionchain_____Debug__C__NoMaster__new_transition_22( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__NoMaster__Debug__A__Ac__NoMaster( msg );
}

void Capsule_Client::actionchain_____Debug__C__NoMaster__new_transition_23( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__NoMaster__Debug__A__En__NoMaster( msg );
}

void Capsule_Client::actionchain_____Debug__C__NoMaster__new_transition_24_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__NoMaster__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__C__NoMaster__new_transition_25( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__NoMaster__Debug__B__Ac__NoMaster( msg );
    save_history( Debug__C__NoMaster, Debug__C__NoMaster__Debug__B__Ac__NoMaster );
}

void Capsule_Client::actionchain_____Debug__C__NoMaster__new_transition_26( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__NoMaster__Debug__A__Ac__NoMaster( msg );
    save_history( Debug__C__NoMaster, Debug__C__NoMaster__Debug__A__Ac__NoMaster );
}

void Capsule_Client::actionchain_____Debug__C__NoMaster__new_transition_27( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__NoMaster__Debug__A__En__NoMaster( msg );
    save_history( Debug__C__NoMaster, Debug__C__NoMaster__Debug__A__En__NoMaster );
}

void Capsule_Client::actionchain_____Debug__C__NoMaster__new_transition_28( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__NoMaster__boundary( msg );
    save_history( Debug__C__NoMaster, Debug__C__NoMaster__boundary );
}

void Capsule_Client::actionchain_____Debug__C__NoResponseFromServer__Debug__AC__NoResponseFromServer( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__NoResponseFromServer__Debug__B__Ac__NoResponseFromServer( msg );
    transitionaction_____Debug__C__NoResponseFromServer__Debug__AC__NoResponseFromServer( msg );
    entryaction_____Debug__C__NoResponseFromServer__Debug__A__Ac__NoResponseFromServer( msg );
}

void Capsule_Client::actionchain_____Debug__C__NoResponseFromServer__Debug__En__Ready( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__NoResponseFromServer__Debug__A__Ac__NoResponseFromServer( msg );
    transitionaction_____Debug__C__NoResponseFromServer__Debug__En__Ready( msg );
    entryaction_____Debug__C__NoResponseFromServer__Debug__A__En__Ready( msg );
}

void Capsule_Client::actionchain_____Debug__C__NoResponseFromServer__Debug__Ex__WaitingForReply( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__NoResponseFromServer__Debug__B__Ex__WaitingForReply( msg );
    transitionaction_____Debug__C__NoResponseFromServer__Debug__Ex__WaitingForReply( msg );
    entryaction_____Debug__C__NoResponseFromServer__Debug__B__Ac__NoResponseFromServer( msg );
}

void Capsule_Client::actionchain_____Debug__C__NoResponseFromServer__Debug__end__trans__NoResponseFromServer( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__NoResponseFromServer__Debug__A__En__Ready( msg );
    transitionaction_____Debug__C__NoResponseFromServer__Debug__end__trans__NoResponseFromServer( msg );
    save_history( Debug__C__NoResponseFromServer, Debug__C__NoResponseFromServer__Debug__A__En__Ready );
}

void Capsule_Client::actionchain_____Debug__C__NoResponseFromServer__Debug__init__trans__NoResponseFromServer( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__NoResponseFromServer__Debug__init__trans__NoResponseFromServer( msg );
    entryaction_____Debug__C__NoResponseFromServer__Debug__B__Ex__WaitingForReply( msg );
}

void Capsule_Client::actionchain_____Debug__C__NoResponseFromServer__new_transition_29( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__NoResponseFromServer__Debug__B__Ex__WaitingForReply( msg );
}

void Capsule_Client::actionchain_____Debug__C__NoResponseFromServer__new_transition_30( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__NoResponseFromServer__Debug__B__Ac__NoResponseFromServer( msg );
}

void Capsule_Client::actionchain_____Debug__C__NoResponseFromServer__new_transition_31( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__NoResponseFromServer__Debug__A__Ac__NoResponseFromServer( msg );
}

void Capsule_Client::actionchain_____Debug__C__NoResponseFromServer__new_transition_32( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__NoResponseFromServer__Debug__A__En__Ready( msg );
}

void Capsule_Client::actionchain_____Debug__C__NoResponseFromServer__new_transition_33_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__NoResponseFromServer__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__C__NoResponseFromServer__new_transition_34( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__NoResponseFromServer__Debug__B__Ex__WaitingForReply( msg );
    save_history( Debug__C__NoResponseFromServer, Debug__C__NoResponseFromServer__Debug__B__Ex__WaitingForReply );
}

void Capsule_Client::actionchain_____Debug__C__NoResponseFromServer__new_transition_35( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__NoResponseFromServer__Debug__B__Ac__NoResponseFromServer( msg );
    save_history( Debug__C__NoResponseFromServer, Debug__C__NoResponseFromServer__Debug__B__Ac__NoResponseFromServer );
}

void Capsule_Client::actionchain_____Debug__C__NoResponseFromServer__new_transition_36( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__NoResponseFromServer__Debug__A__Ac__NoResponseFromServer( msg );
    save_history( Debug__C__NoResponseFromServer, Debug__C__NoResponseFromServer__Debug__A__Ac__NoResponseFromServer );
}

void Capsule_Client::actionchain_____Debug__C__NoResponseFromServer__new_transition_37( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__NoResponseFromServer__Debug__A__En__Ready( msg );
    save_history( Debug__C__NoResponseFromServer, Debug__C__NoResponseFromServer__Debug__A__En__Ready );
}

void Capsule_Client::actionchain_____Debug__C__NoResponseFromServer__new_transition_38( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__NoResponseFromServer__boundary( msg );
    save_history( Debug__C__NoResponseFromServer, Debug__C__NoResponseFromServer__boundary );
}

void Capsule_Client::actionchain_____Debug__C__ReqFlowDone__Debug__AC__ReqFlowDone( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ReqFlowDone__Debug__B__Ac__ReqFlowDone( msg );
    transitionaction_____Debug__C__ReqFlowDone__Debug__AC__ReqFlowDone( msg );
    entryaction_____Debug__C__ReqFlowDone__Debug__A__Ac__ReqFlowDone( msg );
}

void Capsule_Client::actionchain_____Debug__C__ReqFlowDone__Debug__En__Ready( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ReqFlowDone__Debug__A__Ac__ReqFlowDone( msg );
    transitionaction_____Debug__C__ReqFlowDone__Debug__En__Ready( msg );
    entryaction_____Debug__C__ReqFlowDone__Debug__A__En__Ready( msg );
}

void Capsule_Client::actionchain_____Debug__C__ReqFlowDone__Debug__Ex__ProcessResponse( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ReqFlowDone__Debug__B__Ex__ProcessResponse( msg );
    transitionaction_____Debug__C__ReqFlowDone__Debug__Ex__ProcessResponse( msg );
    entryaction_____Debug__C__ReqFlowDone__Debug__B__Ac__ReqFlowDone( msg );
}

void Capsule_Client::actionchain_____Debug__C__ReqFlowDone__Debug__end__trans__ReqFlowDone( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ReqFlowDone__Debug__A__En__Ready( msg );
    transitionaction_____Debug__C__ReqFlowDone__Debug__end__trans__ReqFlowDone( msg );
    save_history( Debug__C__ReqFlowDone, Debug__C__ReqFlowDone__Debug__A__En__Ready );
}

void Capsule_Client::actionchain_____Debug__C__ReqFlowDone__Debug__init__trans__ReqFlowDone( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__ReqFlowDone__Debug__init__trans__ReqFlowDone( msg );
    entryaction_____Debug__C__ReqFlowDone__Debug__B__Ex__ProcessResponse( msg );
}

void Capsule_Client::actionchain_____Debug__C__ReqFlowDone__new_transition_39( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ReqFlowDone__Debug__B__Ex__ProcessResponse( msg );
}

void Capsule_Client::actionchain_____Debug__C__ReqFlowDone__new_transition_40( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ReqFlowDone__Debug__B__Ac__ReqFlowDone( msg );
}

void Capsule_Client::actionchain_____Debug__C__ReqFlowDone__new_transition_41( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ReqFlowDone__Debug__A__Ac__ReqFlowDone( msg );
}

void Capsule_Client::actionchain_____Debug__C__ReqFlowDone__new_transition_42( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ReqFlowDone__Debug__A__En__Ready( msg );
}

void Capsule_Client::actionchain_____Debug__C__ReqFlowDone__new_transition_43_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ReqFlowDone__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__C__ReqFlowDone__new_transition_44( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ReqFlowDone__Debug__B__Ex__ProcessResponse( msg );
    save_history( Debug__C__ReqFlowDone, Debug__C__ReqFlowDone__Debug__B__Ex__ProcessResponse );
}

void Capsule_Client::actionchain_____Debug__C__ReqFlowDone__new_transition_45( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ReqFlowDone__Debug__B__Ac__ReqFlowDone( msg );
    save_history( Debug__C__ReqFlowDone, Debug__C__ReqFlowDone__Debug__B__Ac__ReqFlowDone );
}

void Capsule_Client::actionchain_____Debug__C__ReqFlowDone__new_transition_46( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ReqFlowDone__Debug__A__Ac__ReqFlowDone( msg );
    save_history( Debug__C__ReqFlowDone, Debug__C__ReqFlowDone__Debug__A__Ac__ReqFlowDone );
}

void Capsule_Client::actionchain_____Debug__C__ReqFlowDone__new_transition_47( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ReqFlowDone__Debug__A__En__Ready( msg );
    save_history( Debug__C__ReqFlowDone, Debug__C__ReqFlowDone__Debug__A__En__Ready );
}

void Capsule_Client::actionchain_____Debug__C__ReqFlowDone__new_transition_48( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ReqFlowDone__boundary( msg );
    save_history( Debug__C__ReqFlowDone, Debug__C__ReqFlowDone__boundary );
}

void Capsule_Client::actionchain_____Debug__C__Retry__Debug__AC__Retry( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Retry__Debug__B__Ac__Retry( msg );
    transitionaction_____Debug__C__Retry__Debug__AC__Retry( msg );
    entryaction_____Debug__C__Retry__Debug__A__Ac__Retry( msg );
}

void Capsule_Client::actionchain_____Debug__C__Retry__Debug__En__getMasterName( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Retry__Debug__A__Ac__Retry( msg );
    transitionaction_____Debug__C__Retry__Debug__En__getMasterName( msg );
    entryaction_____Debug__C__Retry__Debug__A__En__getMasterName( msg );
}

void Capsule_Client::actionchain_____Debug__C__Retry__Debug__Ex__Retry( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Retry__Debug__B__Ex__Retry( msg );
    transitionaction_____Debug__C__Retry__Debug__Ex__Retry( msg );
    entryaction_____Debug__C__Retry__Debug__B__Ac__Retry( msg );
}

void Capsule_Client::actionchain_____Debug__C__Retry__Debug__end__trans__Retry( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Retry__Debug__A__En__getMasterName( msg );
    transitionaction_____Debug__C__Retry__Debug__end__trans__Retry( msg );
    save_history( Debug__C__Retry, Debug__C__Retry__Debug__A__En__getMasterName );
}

void Capsule_Client::actionchain_____Debug__C__Retry__Debug__init__trans__Retry( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__Retry__Debug__init__trans__Retry( msg );
    entryaction_____Debug__C__Retry__Debug__B__Ex__Retry( msg );
}

void Capsule_Client::actionchain_____Debug__C__Retry__new_transition_11( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Retry__Debug__B__Ex__Retry( msg );
}

void Capsule_Client::actionchain_____Debug__C__Retry__new_transition_12( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Retry__Debug__B__Ac__Retry( msg );
}

void Capsule_Client::actionchain_____Debug__C__Retry__new_transition_13( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Retry__Debug__A__Ac__Retry( msg );
}

void Capsule_Client::actionchain_____Debug__C__Retry__new_transition_14( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Retry__Debug__A__En__getMasterName( msg );
}

void Capsule_Client::actionchain_____Debug__C__Retry__new_transition_15_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Retry__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__C__Retry__new_transition_16( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Retry__Debug__B__Ex__Retry( msg );
    save_history( Debug__C__Retry, Debug__C__Retry__Debug__B__Ex__Retry );
}

void Capsule_Client::actionchain_____Debug__C__Retry__new_transition_17( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Retry__Debug__B__Ac__Retry( msg );
    save_history( Debug__C__Retry, Debug__C__Retry__Debug__B__Ac__Retry );
}

void Capsule_Client::actionchain_____Debug__C__Retry__new_transition_18( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Retry__Debug__A__Ac__Retry( msg );
    save_history( Debug__C__Retry, Debug__C__Retry__Debug__A__Ac__Retry );
}

void Capsule_Client::actionchain_____Debug__C__Retry__new_transition_19( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Retry__Debug__A__En__getMasterName( msg );
    save_history( Debug__C__Retry, Debug__C__Retry__Debug__A__En__getMasterName );
}

void Capsule_Client::actionchain_____Debug__C__Retry__new_transition_20( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Retry__boundary( msg );
    save_history( Debug__C__Retry, Debug__C__Retry__boundary );
}

void Capsule_Client::actionchain_____Debug__C__ServiceResult__Debug__AC__ServiceResult( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServiceResult__Debug__B__Ac__ServiceResult( msg );
    transitionaction_____Debug__C__ServiceResult__Debug__AC__ServiceResult( msg );
    entryaction_____Debug__C__ServiceResult__Debug__A__Ac__ServiceResult( msg );
}

void Capsule_Client::actionchain_____Debug__C__ServiceResult__Debug__En__ProcessResponse( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServiceResult__Debug__A__Ac__ServiceResult( msg );
    transitionaction_____Debug__C__ServiceResult__Debug__En__ProcessResponse( msg );
    entryaction_____Debug__C__ServiceResult__Debug__A__En__ProcessResponse( msg );
}

void Capsule_Client::actionchain_____Debug__C__ServiceResult__Debug__Ex__WaitingForReply( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServiceResult__Debug__B__Ex__WaitingForReply( msg );
    transitionaction_____Debug__C__ServiceResult__Debug__Ex__WaitingForReply( msg );
    entryaction_____Debug__C__ServiceResult__Debug__B__Ac__ServiceResult( msg );
}

void Capsule_Client::actionchain_____Debug__C__ServiceResult__Debug__end__trans__ServiceResult( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServiceResult__Debug__A__En__ProcessResponse( msg );
    transitionaction_____Debug__C__ServiceResult__Debug__end__trans__ServiceResult( msg );
    save_history( Debug__C__ServiceResult, Debug__C__ServiceResult__Debug__A__En__ProcessResponse );
}

void Capsule_Client::actionchain_____Debug__C__ServiceResult__Debug__init__trans__ServiceResult( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__ServiceResult__Debug__init__trans__ServiceResult( msg );
    entryaction_____Debug__C__ServiceResult__Debug__B__Ex__WaitingForReply( msg );
}

void Capsule_Client::actionchain_____Debug__C__ServiceResult__new_transition_75( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ServiceResult__Debug__B__Ex__WaitingForReply( msg );
}

void Capsule_Client::actionchain_____Debug__C__ServiceResult__new_transition_76( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ServiceResult__Debug__B__Ac__ServiceResult( msg );
}

void Capsule_Client::actionchain_____Debug__C__ServiceResult__new_transition_77( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ServiceResult__Debug__A__Ac__ServiceResult( msg );
}

void Capsule_Client::actionchain_____Debug__C__ServiceResult__new_transition_78( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ServiceResult__Debug__A__En__ProcessResponse( msg );
}

void Capsule_Client::actionchain_____Debug__C__ServiceResult__new_transition_79_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ServiceResult__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__C__ServiceResult__new_transition_80( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServiceResult__Debug__B__Ex__WaitingForReply( msg );
    save_history( Debug__C__ServiceResult, Debug__C__ServiceResult__Debug__B__Ex__WaitingForReply );
}

void Capsule_Client::actionchain_____Debug__C__ServiceResult__new_transition_81( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServiceResult__Debug__B__Ac__ServiceResult( msg );
    save_history( Debug__C__ServiceResult, Debug__C__ServiceResult__Debug__B__Ac__ServiceResult );
}

void Capsule_Client::actionchain_____Debug__C__ServiceResult__new_transition_82( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServiceResult__Debug__A__Ac__ServiceResult( msg );
    save_history( Debug__C__ServiceResult, Debug__C__ServiceResult__Debug__A__Ac__ServiceResult );
}

void Capsule_Client::actionchain_____Debug__C__ServiceResult__new_transition_83( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServiceResult__Debug__A__En__ProcessResponse( msg );
    save_history( Debug__C__ServiceResult, Debug__C__ServiceResult__Debug__A__En__ProcessResponse );
}

void Capsule_Client::actionchain_____Debug__C__ServiceResult__new_transition_84( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServiceResult__boundary( msg );
    save_history( Debug__C__ServiceResult, Debug__C__ServiceResult__boundary );
}

void Capsule_Client::actionchain_____Debug__C__StarupTransition__Debug__AC__StarupTransition( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StarupTransition__Debug__B__Ac__StarupTransition( msg );
    transitionaction_____Debug__C__StarupTransition__Debug__AC__StarupTransition( msg );
    entryaction_____Debug__C__StarupTransition__Debug__A__Ac__StarupTransition( msg );
}

void Capsule_Client::actionchain_____Debug__C__StarupTransition__Debug__En__Ready( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StarupTransition__Debug__A__Ac__StarupTransition( msg );
    transitionaction_____Debug__C__StarupTransition__Debug__En__Ready( msg );
    entryaction_____Debug__C__StarupTransition__Debug__A__En__Ready( msg );
}

void Capsule_Client::actionchain_____Debug__C__StarupTransition__Debug__Ex__StandBY( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StarupTransition__Debug__B__Ex__StandBY( msg );
    transitionaction_____Debug__C__StarupTransition__Debug__Ex__StandBY( msg );
    entryaction_____Debug__C__StarupTransition__Debug__B__Ac__StarupTransition( msg );
}

void Capsule_Client::actionchain_____Debug__C__StarupTransition__Debug__end__trans__StarupTransition( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StarupTransition__Debug__A__En__Ready( msg );
    transitionaction_____Debug__C__StarupTransition__Debug__end__trans__StarupTransition( msg );
    save_history( Debug__C__StarupTransition, Debug__C__StarupTransition__Debug__A__En__Ready );
}

void Capsule_Client::actionchain_____Debug__C__StarupTransition__Debug__init__trans__StarupTransition( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__StarupTransition__Debug__init__trans__StarupTransition( msg );
    entryaction_____Debug__C__StarupTransition__Debug__B__Ex__StandBY( msg );
}

void Capsule_Client::actionchain_____Debug__C__StarupTransition__new_transition_1( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__StarupTransition__Debug__B__Ex__StandBY( msg );
}

void Capsule_Client::actionchain_____Debug__C__StarupTransition__new_transition_10( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StarupTransition__boundary( msg );
    save_history( Debug__C__StarupTransition, Debug__C__StarupTransition__boundary );
}

void Capsule_Client::actionchain_____Debug__C__StarupTransition__new_transition_2( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__StarupTransition__Debug__B__Ac__StarupTransition( msg );
}

void Capsule_Client::actionchain_____Debug__C__StarupTransition__new_transition_3( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__StarupTransition__Debug__A__Ac__StarupTransition( msg );
}

void Capsule_Client::actionchain_____Debug__C__StarupTransition__new_transition_4( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__StarupTransition__Debug__A__En__Ready( msg );
}

void Capsule_Client::actionchain_____Debug__C__StarupTransition__new_transition_5_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__StarupTransition__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__C__StarupTransition__new_transition_6( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StarupTransition__Debug__B__Ex__StandBY( msg );
    save_history( Debug__C__StarupTransition, Debug__C__StarupTransition__Debug__B__Ex__StandBY );
}

void Capsule_Client::actionchain_____Debug__C__StarupTransition__new_transition_7( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StarupTransition__Debug__B__Ac__StarupTransition( msg );
    save_history( Debug__C__StarupTransition, Debug__C__StarupTransition__Debug__B__Ac__StarupTransition );
}

void Capsule_Client::actionchain_____Debug__C__StarupTransition__new_transition_8( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StarupTransition__Debug__A__Ac__StarupTransition( msg );
    save_history( Debug__C__StarupTransition, Debug__C__StarupTransition__Debug__A__Ac__StarupTransition );
}

void Capsule_Client::actionchain_____Debug__C__StarupTransition__new_transition_9( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StarupTransition__Debug__A__En__Ready( msg );
    save_history( Debug__C__StarupTransition, Debug__C__StarupTransition__Debug__A__En__Ready );
}

void Capsule_Client::actionchain_____Debug__C__getMasterName__checkConfig__7__Debug__AC__getMasterName__checkConfig__7( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__getMasterName__checkConfig__7__Debug__B__Ac__getMasterName__checkConfig__7( msg );
    transitionaction_____Debug__C__getMasterName__checkConfig__7__Debug__AC__getMasterName__checkConfig__7( msg );
    entryaction_____Debug__C__getMasterName__checkConfig__7__Debug__A__Ac__getMasterName__checkConfig__7( msg );
}

void Capsule_Client::actionchain_____Debug__C__getMasterName__checkConfig__7__Debug__Ex__getMasterName( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__getMasterName__checkConfig__7__Debug__B__Ex__getMasterName( msg );
    transitionaction_____Debug__C__getMasterName__checkConfig__7__Debug__Ex__getMasterName( msg );
    entryaction_____Debug__C__getMasterName__checkConfig__7__Debug__B__Ac__getMasterName__checkConfig__7( msg );
}

void Capsule_Client::actionchain_____Debug__C__getMasterName__checkConfig__7__Debug__end__trans__getMasterName__checkConfig__7( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__getMasterName__checkConfig__7__Debug__A__Ac__getMasterName__checkConfig__7( msg );
    transitionaction_____Debug__C__getMasterName__checkConfig__7__Debug__end__trans__getMasterName__checkConfig__7( msg );
    save_history( Debug__C__getMasterName__checkConfig__7, Debug__C__getMasterName__checkConfig__7__Debug__A__Ac__getMasterName__checkConfig__7 );
}

void Capsule_Client::actionchain_____Debug__C__getMasterName__checkConfig__7__Debug__init__trans__getMasterName__checkConfig__7( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__getMasterName__checkConfig__7__Debug__B__Ex__getMasterName( msg );
}

void Capsule_Client::actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_57( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__getMasterName__checkConfig__7__Debug__B__Ex__getMasterName( msg );
}

void Capsule_Client::actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_58( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__getMasterName__checkConfig__7__Debug__B__Ac__getMasterName__checkConfig__7( msg );
}

void Capsule_Client::actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_59( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__getMasterName__checkConfig__7__Debug__A__Ac__getMasterName__checkConfig__7( msg );
}

void Capsule_Client::actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_60_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__getMasterName__checkConfig__7__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_61( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__getMasterName__checkConfig__7__Debug__B__Ex__getMasterName( msg );
    save_history( Debug__C__getMasterName__checkConfig__7, Debug__C__getMasterName__checkConfig__7__Debug__B__Ex__getMasterName );
}

void Capsule_Client::actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_62( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__getMasterName__checkConfig__7__Debug__B__Ac__getMasterName__checkConfig__7( msg );
    save_history( Debug__C__getMasterName__checkConfig__7, Debug__C__getMasterName__checkConfig__7__Debug__B__Ac__getMasterName__checkConfig__7 );
}

void Capsule_Client::actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_63( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__getMasterName__checkConfig__7__Debug__A__Ac__getMasterName__checkConfig__7( msg );
    save_history( Debug__C__getMasterName__checkConfig__7, Debug__C__getMasterName__checkConfig__7__Debug__A__Ac__getMasterName__checkConfig__7 );
}

void Capsule_Client::actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_64( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__getMasterName__checkConfig__7__boundary( msg );
    save_history( Debug__C__getMasterName__checkConfig__7, Debug__C__getMasterName__checkConfig__7__boundary );
}

void Capsule_Client::actionchain_____Debug__C__init__StandBY__6__Debug__Ac__init__StandBY__6( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__StandBY__6__Debug__B__Ac__init__StandBY__6( msg );
    transitionaction_____Debug__C__init__StandBY__6__Debug__Ac__init__StandBY__6( msg );
    entryaction_____Debug__C__init__StandBY__6__Debug__A__Ac__init__StandBY__6( msg );
}

void Capsule_Client::actionchain_____Debug__C__init__StandBY__6__Debug__En__StandBY( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__StandBY__6__Debug__A__Ac__init__StandBY__6( msg );
    transitionaction_____Debug__C__init__StandBY__6__Debug__En__StandBY( msg );
    entryaction_____Debug__C__init__StandBY__6__Debug__A__En__init__StandBY__6( msg );
}

void Capsule_Client::actionchain_____Debug__C__init__StandBY__6__Debug__end__trans__init__StandBY__6( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__StandBY__6__Debug__A__En__init__StandBY__6( msg );
    transitionaction_____Debug__C__init__StandBY__6__Debug__end__trans__init__StandBY__6( msg );
    save_history( Debug__C__init__StandBY__6, Debug__C__init__StandBY__6__Debug__A__En__init__StandBY__6 );
}

void Capsule_Client::actionchain_____Debug__C__init__StandBY__6__Debug__init__trans__init__StandBY__6( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__init__StandBY__6__Debug__init__trans__init__StandBY__6( msg );
    entryaction_____Debug__C__init__StandBY__6__Debug__B__Ac__init__StandBY__6( msg );
}

void Capsule_Client::actionchain_____Debug__C__init__StandBY__6__new_transition_49( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__StandBY__6__Debug__B__Ac__init__StandBY__6( msg );
}

void Capsule_Client::actionchain_____Debug__C__init__StandBY__6__new_transition_50( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__StandBY__6__Debug__A__Ac__init__StandBY__6( msg );
}

void Capsule_Client::actionchain_____Debug__C__init__StandBY__6__new_transition_51( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__StandBY__6__Debug__A__En__init__StandBY__6( msg );
}

void Capsule_Client::actionchain_____Debug__C__init__StandBY__6__new_transition_52_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__StandBY__6__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__C__init__StandBY__6__new_transition_53( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__StandBY__6__Debug__B__Ac__init__StandBY__6( msg );
    save_history( Debug__C__init__StandBY__6, Debug__C__init__StandBY__6__Debug__B__Ac__init__StandBY__6 );
}

void Capsule_Client::actionchain_____Debug__C__init__StandBY__6__new_transition_54( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__StandBY__6__Debug__A__Ac__init__StandBY__6( msg );
    save_history( Debug__C__init__StandBY__6, Debug__C__init__StandBY__6__Debug__A__Ac__init__StandBY__6 );
}

void Capsule_Client::actionchain_____Debug__C__init__StandBY__6__new_transition_55( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__StandBY__6__Debug__A__En__init__StandBY__6( msg );
    save_history( Debug__C__init__StandBY__6, Debug__C__init__StandBY__6__Debug__A__En__init__StandBY__6 );
}

void Capsule_Client::actionchain_____Debug__C__init__StandBY__6__new_transition_56( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__StandBY__6__boundary( msg );
    save_history( Debug__C__init__StandBY__6, Debug__C__init__StandBY__6__boundary );
}

void Capsule_Client::actionchain_____Debug__C__reqFlowInit__Debug__AC__reqFlowInit( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reqFlowInit__Debug__B__Ac__reqFlowInit( msg );
    transitionaction_____Debug__C__reqFlowInit__Debug__AC__reqFlowInit( msg );
    entryaction_____Debug__C__reqFlowInit__Debug__A__Ac__reqFlowInit( msg );
}

void Capsule_Client::actionchain_____Debug__C__reqFlowInit__Debug__En__getMasterName( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reqFlowInit__Debug__A__Ac__reqFlowInit( msg );
    transitionaction_____Debug__C__reqFlowInit__Debug__En__getMasterName( msg );
    entryaction_____Debug__C__reqFlowInit__Debug__A__En__getMasterName( msg );
}

void Capsule_Client::actionchain_____Debug__C__reqFlowInit__Debug__Ex__Ready( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reqFlowInit__Debug__B__Ex__Ready( msg );
    transitionaction_____Debug__C__reqFlowInit__Debug__Ex__Ready( msg );
    entryaction_____Debug__C__reqFlowInit__Debug__B__Ac__reqFlowInit( msg );
}

void Capsule_Client::actionchain_____Debug__C__reqFlowInit__Debug__end__trans__reqFlowInit( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reqFlowInit__Debug__A__En__getMasterName( msg );
    transitionaction_____Debug__C__reqFlowInit__Debug__end__trans__reqFlowInit( msg );
    save_history( Debug__C__reqFlowInit, Debug__C__reqFlowInit__Debug__A__En__getMasterName );
}

void Capsule_Client::actionchain_____Debug__C__reqFlowInit__Debug__init__trans__reqFlowInit( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__reqFlowInit__Debug__init__trans__reqFlowInit( msg );
    entryaction_____Debug__C__reqFlowInit__Debug__B__Ex__Ready( msg );
}

void Capsule_Client::actionchain_____Debug__C__reqFlowInit__new_transition_65( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__reqFlowInit__Debug__B__Ex__Ready( msg );
}

void Capsule_Client::actionchain_____Debug__C__reqFlowInit__new_transition_66( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__reqFlowInit__Debug__B__Ac__reqFlowInit( msg );
}

void Capsule_Client::actionchain_____Debug__C__reqFlowInit__new_transition_67( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__reqFlowInit__Debug__A__Ac__reqFlowInit( msg );
}

void Capsule_Client::actionchain_____Debug__C__reqFlowInit__new_transition_68( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__reqFlowInit__Debug__A__En__getMasterName( msg );
}

void Capsule_Client::actionchain_____Debug__C__reqFlowInit__new_transition_69_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__reqFlowInit__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__C__reqFlowInit__new_transition_70( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reqFlowInit__Debug__B__Ex__Ready( msg );
    save_history( Debug__C__reqFlowInit, Debug__C__reqFlowInit__Debug__B__Ex__Ready );
}

void Capsule_Client::actionchain_____Debug__C__reqFlowInit__new_transition_71( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reqFlowInit__Debug__B__Ac__reqFlowInit( msg );
    save_history( Debug__C__reqFlowInit, Debug__C__reqFlowInit__Debug__B__Ac__reqFlowInit );
}

void Capsule_Client::actionchain_____Debug__C__reqFlowInit__new_transition_72( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reqFlowInit__Debug__A__Ac__reqFlowInit( msg );
    save_history( Debug__C__reqFlowInit, Debug__C__reqFlowInit__Debug__A__Ac__reqFlowInit );
}

void Capsule_Client::actionchain_____Debug__C__reqFlowInit__new_transition_73( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reqFlowInit__Debug__A__En__getMasterName( msg );
    save_history( Debug__C__reqFlowInit, Debug__C__reqFlowInit__Debug__A__En__getMasterName );
}

void Capsule_Client::actionchain_____Debug__C__reqFlowInit__new_transition_74( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reqFlowInit__boundary( msg );
    save_history( Debug__C__reqFlowInit, Debug__C__reqFlowInit__boundary );
}

void Capsule_Client::actionchain_____Debug__C__reqService__Debug__Ac__reqService( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reqService__Debug__B__Ac__reqService( msg );
    transitionaction_____Debug__C__reqService__Debug__Ac__reqService( msg );
    entryaction_____Debug__C__reqService__Debug__A__Ac__reqService( msg );
}

void Capsule_Client::actionchain_____Debug__C__reqService__Debug__En__WaitingForReply( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reqService__Debug__A__Ac__reqService( msg );
    transitionaction_____Debug__C__reqService__Debug__En__WaitingForReply( msg );
    entryaction_____Debug__C__reqService__Debug__A__En__reqService( msg );
}

void Capsule_Client::actionchain_____Debug__C__reqService__Debug__end__trans__reqService( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reqService__Debug__A__En__reqService( msg );
    transitionaction_____Debug__C__reqService__Debug__end__trans__reqService( msg );
    save_history( Debug__C__reqService, Debug__C__reqService__Debug__A__En__reqService );
}

void Capsule_Client::actionchain_____Debug__C__reqService__Debug__init__trans__reqService( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__reqService__Debug__init__trans__reqService( msg );
    entryaction_____Debug__C__reqService__Debug__B__Ac__reqService( msg );
}

void Capsule_Client::actionchain_____Debug__C__reqService__new_transition_85( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__reqService__Debug__B__Ac__reqService( msg );
}

void Capsule_Client::actionchain_____Debug__C__reqService__new_transition_86( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__reqService__Debug__A__Ac__reqService( msg );
}

void Capsule_Client::actionchain_____Debug__C__reqService__new_transition_87( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__reqService__Debug__A__En__reqService( msg );
}

void Capsule_Client::actionchain_____Debug__C__reqService__new_transition_88_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__reqService__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__C__reqService__new_transition_89( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reqService__Debug__B__Ac__reqService( msg );
    save_history( Debug__C__reqService, Debug__C__reqService__Debug__B__Ac__reqService );
}

void Capsule_Client::actionchain_____Debug__C__reqService__new_transition_90( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reqService__Debug__A__Ac__reqService( msg );
    save_history( Debug__C__reqService, Debug__C__reqService__Debug__A__Ac__reqService );
}

void Capsule_Client::actionchain_____Debug__C__reqService__new_transition_91( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reqService__Debug__A__En__reqService( msg );
    save_history( Debug__C__reqService, Debug__C__reqService__Debug__A__En__reqService );
}

void Capsule_Client::actionchain_____Debug__C__reqService__new_transition_92( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reqService__boundary( msg );
    save_history( Debug__C__reqService, Debug__C__reqService__boundary );
}

void Capsule_Client::actionchain_____Debug__InitDebug( const UMLRTMessage * msg )
{
    transitionaction_____Debug__InitDebug( msg );
    entryaction_____Debug__InitState( msg );
}

void Capsule_Client::actionchain_____Debug__NoMaster( const UMLRTMessage * msg )
{
    transitionaction_____Debug__NoMaster( msg );
}

void Capsule_Client::actionchain_____Debug__NoMaster__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__NoMaster__boundary( msg );
    transitionaction_____Debug__NoMaster__E( msg );
    entryaction_____Retry( msg );
}

void Capsule_Client::actionchain_____Debug__NoMaster__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__NoMaster__S( msg );
    entryaction_____Debug__C__NoMaster__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__NoMaster__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__NoMaster__boundary( msg );
    transitionaction_____Debug__NoMaster__dbg( msg );
    entryaction_____Debug__C__NoMaster__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__NoResponseFromServer( const UMLRTMessage * msg )
{
    exitaction_____WaitingForReply( msg );
    transitionaction_____Debug__NoResponseFromServer( msg );
}

void Capsule_Client::actionchain_____Debug__NoResponseFromServer__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__NoResponseFromServer__boundary( msg );
    transitionaction_____Debug__NoResponseFromServer__E( msg );
    entryaction_____Ready( msg );
}

void Capsule_Client::actionchain_____Debug__NoResponseFromServer__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__NoResponseFromServer__S( msg );
    entryaction_____Debug__C__NoResponseFromServer__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__NoResponseFromServer__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__NoResponseFromServer__boundary( msg );
    transitionaction_____Debug__NoResponseFromServer__dbg( msg );
    entryaction_____Debug__C__NoResponseFromServer__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__ReqFlowDone( const UMLRTMessage * msg )
{
    exitaction_____ProcessResponse( msg );
    transitionaction_____Debug__ReqFlowDone( msg );
}

void Capsule_Client::actionchain_____Debug__ReqFlowDone__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ReqFlowDone__boundary( msg );
    transitionaction_____Debug__ReqFlowDone__E( msg );
    entryaction_____Ready( msg );
}

void Capsule_Client::actionchain_____Debug__ReqFlowDone__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__ReqFlowDone__S( msg );
    entryaction_____Debug__C__ReqFlowDone__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__ReqFlowDone__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ReqFlowDone__boundary( msg );
    transitionaction_____Debug__ReqFlowDone__dbg( msg );
    entryaction_____Debug__C__ReqFlowDone__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__Retry( const UMLRTMessage * msg )
{
    exitaction_____Retry( msg );
    transitionaction_____Debug__Retry( msg );
}

void Capsule_Client::actionchain_____Debug__Retry__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Retry__boundary( msg );
    transitionaction_____Debug__Retry__E( msg );
    entryaction_____getMasterName( msg );
}

void Capsule_Client::actionchain_____Debug__Retry__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__Retry__S( msg );
    entryaction_____Debug__C__Retry__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__Retry__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Retry__boundary( msg );
    transitionaction_____Debug__Retry__dbg( msg );
    entryaction_____Debug__C__Retry__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__ServiceResult( const UMLRTMessage * msg )
{
    exitaction_____WaitingForReply( msg );
    transitionaction_____Debug__ServiceResult( msg );
}

void Capsule_Client::actionchain_____Debug__ServiceResult__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServiceResult__boundary( msg );
    transitionaction_____Debug__ServiceResult__E( msg );
    entryaction_____ProcessResponse( msg );
}

void Capsule_Client::actionchain_____Debug__ServiceResult__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__ServiceResult__S( msg );
    entryaction_____Debug__C__ServiceResult__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__ServiceResult__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServiceResult__boundary( msg );
    transitionaction_____Debug__ServiceResult__dbg( msg );
    entryaction_____Debug__C__ServiceResult__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__StarupTransition( const UMLRTMessage * msg )
{
    exitaction_____StandBY( msg );
    transitionaction_____Debug__StarupTransition( msg );
}

void Capsule_Client::actionchain_____Debug__StarupTransition__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StarupTransition__boundary( msg );
    transitionaction_____Debug__StarupTransition__E( msg );
    entryaction_____Ready( msg );
}

void Capsule_Client::actionchain_____Debug__StarupTransition__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__StarupTransition__S( msg );
    entryaction_____Debug__C__StarupTransition__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__StarupTransition__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StarupTransition__boundary( msg );
    transitionaction_____Debug__StarupTransition__dbg( msg );
    entryaction_____Debug__C__StarupTransition__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__getMasterName__checkConfig__7( const UMLRTMessage * msg )
{
    exitaction_____getMasterName( msg );
    transitionaction_____Debug__getMasterName__checkConfig__7( msg );
}

void Capsule_Client::actionchain_____Debug__getMasterName__checkConfig__7__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__getMasterName__checkConfig__7__boundary( msg );
    transitionaction_____Debug__getMasterName__checkConfig__7__E( msg );
}

void Capsule_Client::actionchain_____Debug__getMasterName__checkConfig__7__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__getMasterName__checkConfig__7__S( msg );
    entryaction_____Debug__C__getMasterName__checkConfig__7__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__getMasterName__checkConfig__7__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__getMasterName__checkConfig__7__boundary( msg );
    transitionaction_____Debug__getMasterName__checkConfig__7__dbg( msg );
    entryaction_____Debug__C__getMasterName__checkConfig__7__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__init__StandBY__6( const UMLRTMessage * msg )
{
    exitaction_____Debug__InitState( msg );
    transitionaction_____Debug__init__StandBY__6( msg );
}

void Capsule_Client::actionchain_____Debug__init__StandBY__6__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__StandBY__6__boundary( msg );
    transitionaction_____Debug__init__StandBY__6__E( msg );
    entryaction_____StandBY( msg );
}

void Capsule_Client::actionchain_____Debug__init__StandBY__6__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__init__StandBY__6__S( msg );
    entryaction_____Debug__C__init__StandBY__6__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__init__StandBY__6__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__StandBY__6__boundary( msg );
    transitionaction_____Debug__init__StandBY__6__dbg( msg );
    entryaction_____Debug__C__init__StandBY__6__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__reqFlowInit( const UMLRTMessage * msg )
{
    exitaction_____Ready( msg );
    transitionaction_____Debug__reqFlowInit( msg );
}

void Capsule_Client::actionchain_____Debug__reqFlowInit__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reqFlowInit__boundary( msg );
    transitionaction_____Debug__reqFlowInit__E( msg );
    entryaction_____getMasterName( msg );
}

void Capsule_Client::actionchain_____Debug__reqFlowInit__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__reqFlowInit__S( msg );
    entryaction_____Debug__C__reqFlowInit__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__reqFlowInit__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reqFlowInit__boundary( msg );
    transitionaction_____Debug__reqFlowInit__dbg( msg );
    entryaction_____Debug__C__reqFlowInit__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__reqService( const UMLRTMessage * msg )
{
    transitionaction_____Debug__reqService( msg );
}

void Capsule_Client::actionchain_____Debug__reqService__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reqService__boundary( msg );
    transitionaction_____Debug__reqService__E( msg );
    entryaction_____WaitingForReply( msg );
}

void Capsule_Client::actionchain_____Debug__reqService__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__reqService__S( msg );
    entryaction_____Debug__C__reqService__boundary( msg );
}

void Capsule_Client::actionchain_____Debug__reqService__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__reqService__boundary( msg );
    transitionaction_____Debug__reqService__dbg( msg );
    entryaction_____Debug__C__reqService__boundary( msg );
}

void Capsule_Client::actionchain_____NoMaster( const UMLRTMessage * msg )
{
    transitionaction_____NoMaster( msg );
    entryaction_____Retry( msg );
}

void Capsule_Client::actionchain_____NoResponseFromServer( const UMLRTMessage * msg )
{
    transitionaction_____NoResponseFromServer( msg );
    entryaction_____Ready( msg );
}

void Capsule_Client::actionchain_____ReqFlowDone( const UMLRTMessage * msg )
{
    transitionaction_____ReqFlowDone( msg );
    entryaction_____Ready( msg );
}

void Capsule_Client::actionchain_____Retry( const UMLRTMessage * msg )
{
    transitionaction_____Retry( msg );
    entryaction_____getMasterName( msg );
}

void Capsule_Client::actionchain_____ServiceResult( const UMLRTMessage * msg )
{
    transitionaction_____ServiceResult( msg );
    entryaction_____ProcessResponse( msg );
}

void Capsule_Client::actionchain_____StarupTransition( const UMLRTMessage * msg )
{
    transitionaction_____StarupTransition( msg );
    entryaction_____Ready( msg );
}

void Capsule_Client::actionchain_____getMasterName__checkConfig__7( const UMLRTMessage * msg )
{
    transitionaction_____getMasterName__checkConfig__7( msg );
}

void Capsule_Client::actionchain_____init__StandBY__6( const UMLRTMessage * msg )
{
    transitionaction_____init__StandBY__6( msg );
    entryaction_____StandBY( msg );
}

void Capsule_Client::actionchain_____reqFlowInit( const UMLRTMessage * msg )
{
    transitionaction_____reqFlowInit( msg );
    entryaction_____getMasterName( msg );
}

void Capsule_Client::actionchain_____reqService( const UMLRTMessage * msg )
{
    transitionaction_____reqService( msg );
    entryaction_____WaitingForReply( msg );
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__NoMaster__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__NoMaster__Debug__init__trans__NoMaster( msg );
    return Debug__C__NoMaster__Debug__B__Ac__NoMaster;
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__NoMaster__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__NoMaster__E( msg );
    return Retry;
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__NoMaster__new_exitpoint_3( const UMLRTMessage * msg )
{
    actionchain_____Debug__NoMaster__dbg( msg );
    return choice_____Debug__C__NoMaster__deephistory( msg );
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__NoResponseFromServer__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__NoResponseFromServer__Debug__init__trans__NoResponseFromServer( msg );
    return Debug__C__NoResponseFromServer__Debug__B__Ex__WaitingForReply;
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__NoResponseFromServer__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__NoResponseFromServer__E( msg );
    return Ready;
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__NoResponseFromServer__new_exitpoint_4( const UMLRTMessage * msg )
{
    actionchain_____Debug__NoResponseFromServer__dbg( msg );
    return choice_____Debug__C__NoResponseFromServer__deephistory( msg );
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__ReqFlowDone__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__ReqFlowDone__Debug__init__trans__ReqFlowDone( msg );
    return Debug__C__ReqFlowDone__Debug__B__Ex__ProcessResponse;
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__ReqFlowDone__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__ReqFlowDone__E( msg );
    return Ready;
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__ReqFlowDone__new_exitpoint_5( const UMLRTMessage * msg )
{
    actionchain_____Debug__ReqFlowDone__dbg( msg );
    return choice_____Debug__C__ReqFlowDone__deephistory( msg );
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__Retry__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__Retry__Debug__init__trans__Retry( msg );
    return Debug__C__Retry__Debug__B__Ex__Retry;
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__Retry__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__Retry__E( msg );
    return getMasterName;
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__Retry__new_exitpoint_2( const UMLRTMessage * msg )
{
    actionchain_____Debug__Retry__dbg( msg );
    return choice_____Debug__C__Retry__deephistory( msg );
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__ServiceResult__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__ServiceResult__Debug__init__trans__ServiceResult( msg );
    return Debug__C__ServiceResult__Debug__B__Ex__WaitingForReply;
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__ServiceResult__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__ServiceResult__E( msg );
    return ProcessResponse;
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__ServiceResult__new_exitpoint_9( const UMLRTMessage * msg )
{
    actionchain_____Debug__ServiceResult__dbg( msg );
    return choice_____Debug__C__ServiceResult__deephistory( msg );
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__StarupTransition__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__StarupTransition__Debug__init__trans__StarupTransition( msg );
    return Debug__C__StarupTransition__Debug__B__Ex__StandBY;
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__StarupTransition__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__StarupTransition__E( msg );
    return Ready;
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__StarupTransition__new_exitpoint_1( const UMLRTMessage * msg )
{
    actionchain_____Debug__StarupTransition__dbg( msg );
    return choice_____Debug__C__StarupTransition__deephistory( msg );
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__getMasterName__checkConfig__7__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__getMasterName__checkConfig__7__Debug__init__trans__getMasterName__checkConfig__7( msg );
    return Debug__C__getMasterName__checkConfig__7__Debug__B__Ex__getMasterName;
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__getMasterName__checkConfig__7__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__getMasterName__checkConfig__7__E( msg );
    return choice_____checkConfig( msg );
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__getMasterName__checkConfig__7__new_exitpoint_7( const UMLRTMessage * msg )
{
    actionchain_____Debug__getMasterName__checkConfig__7__dbg( msg );
    return choice_____Debug__C__getMasterName__checkConfig__7__deephistory( msg );
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__init__StandBY__6__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__init__StandBY__6__Debug__init__trans__init__StandBY__6( msg );
    return Debug__C__init__StandBY__6__Debug__B__Ac__init__StandBY__6;
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__init__StandBY__6__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__init__StandBY__6__E( msg );
    return StandBY;
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__init__StandBY__6__new_exitpoint_6( const UMLRTMessage * msg )
{
    actionchain_____Debug__init__StandBY__6__dbg( msg );
    return choice_____Debug__C__init__StandBY__6__deephistory( msg );
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__reqFlowInit__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__reqFlowInit__Debug__init__trans__reqFlowInit( msg );
    return Debug__C__reqFlowInit__Debug__B__Ex__Ready;
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__reqFlowInit__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__reqFlowInit__E( msg );
    return getMasterName;
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__reqFlowInit__new_exitpoint_8( const UMLRTMessage * msg )
{
    actionchain_____Debug__reqFlowInit__dbg( msg );
    return choice_____Debug__C__reqFlowInit__deephistory( msg );
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__reqService__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__reqService__Debug__init__trans__reqService( msg );
    return Debug__C__reqService__Debug__B__Ac__reqService;
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__reqService__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__reqService__E( msg );
    return WaitingForReply;
}

Capsule_Client::State Capsule_Client::junction_____Debug__C__reqService__new_exitpoint_10( const UMLRTMessage * msg )
{
    actionchain_____Debug__reqService__dbg( msg );
    return choice_____Debug__C__reqService__deephistory( msg );
}

Capsule_Client::State Capsule_Client::choice_____Debug__C__NoMaster__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__NoMaster, Debug__C__NoMaster__Debug__B__Ac__NoMaster ) )
    {
        actionchain_____Debug__C__NoMaster__new_transition_21( msg );
        return Debug__C__NoMaster__Debug__B__Ac__NoMaster;
    }
    else if( check_history( Debug__C__NoMaster, Debug__C__NoMaster__Debug__A__Ac__NoMaster ) )
    {
        actionchain_____Debug__C__NoMaster__new_transition_22( msg );
        return Debug__C__NoMaster__Debug__A__Ac__NoMaster;
    }
    else if( check_history( Debug__C__NoMaster, Debug__C__NoMaster__Debug__A__En__NoMaster ) )
    {
        actionchain_____Debug__C__NoMaster__new_transition_23( msg );
        return Debug__C__NoMaster__Debug__A__En__NoMaster;
    }
    else if( check_history( Debug__C__NoMaster, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__NoMaster__new_transition_24_to_boundary( msg );
        return Debug__C__NoMaster__boundary;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::choice_____Debug__C__NoResponseFromServer__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__NoResponseFromServer, Debug__C__NoResponseFromServer__Debug__B__Ex__WaitingForReply ) )
    {
        actionchain_____Debug__C__NoResponseFromServer__new_transition_29( msg );
        return Debug__C__NoResponseFromServer__Debug__B__Ex__WaitingForReply;
    }
    else if( check_history( Debug__C__NoResponseFromServer, Debug__C__NoResponseFromServer__Debug__B__Ac__NoResponseFromServer ) )
    {
        actionchain_____Debug__C__NoResponseFromServer__new_transition_30( msg );
        return Debug__C__NoResponseFromServer__Debug__B__Ac__NoResponseFromServer;
    }
    else if( check_history( Debug__C__NoResponseFromServer, Debug__C__NoResponseFromServer__Debug__A__Ac__NoResponseFromServer ) )
    {
        actionchain_____Debug__C__NoResponseFromServer__new_transition_31( msg );
        return Debug__C__NoResponseFromServer__Debug__A__Ac__NoResponseFromServer;
    }
    else if( check_history( Debug__C__NoResponseFromServer, Debug__C__NoResponseFromServer__Debug__A__En__Ready ) )
    {
        actionchain_____Debug__C__NoResponseFromServer__new_transition_32( msg );
        return Debug__C__NoResponseFromServer__Debug__A__En__Ready;
    }
    else if( check_history( Debug__C__NoResponseFromServer, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__NoResponseFromServer__new_transition_33_to_boundary( msg );
        return Debug__C__NoResponseFromServer__boundary;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::choice_____Debug__C__ReqFlowDone__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__ReqFlowDone, Debug__C__ReqFlowDone__Debug__B__Ex__ProcessResponse ) )
    {
        actionchain_____Debug__C__ReqFlowDone__new_transition_39( msg );
        return Debug__C__ReqFlowDone__Debug__B__Ex__ProcessResponse;
    }
    else if( check_history( Debug__C__ReqFlowDone, Debug__C__ReqFlowDone__Debug__B__Ac__ReqFlowDone ) )
    {
        actionchain_____Debug__C__ReqFlowDone__new_transition_40( msg );
        return Debug__C__ReqFlowDone__Debug__B__Ac__ReqFlowDone;
    }
    else if( check_history( Debug__C__ReqFlowDone, Debug__C__ReqFlowDone__Debug__A__Ac__ReqFlowDone ) )
    {
        actionchain_____Debug__C__ReqFlowDone__new_transition_41( msg );
        return Debug__C__ReqFlowDone__Debug__A__Ac__ReqFlowDone;
    }
    else if( check_history( Debug__C__ReqFlowDone, Debug__C__ReqFlowDone__Debug__A__En__Ready ) )
    {
        actionchain_____Debug__C__ReqFlowDone__new_transition_42( msg );
        return Debug__C__ReqFlowDone__Debug__A__En__Ready;
    }
    else if( check_history( Debug__C__ReqFlowDone, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__ReqFlowDone__new_transition_43_to_boundary( msg );
        return Debug__C__ReqFlowDone__boundary;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::choice_____Debug__C__Retry__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__Retry, Debug__C__Retry__Debug__B__Ex__Retry ) )
    {
        actionchain_____Debug__C__Retry__new_transition_11( msg );
        return Debug__C__Retry__Debug__B__Ex__Retry;
    }
    else if( check_history( Debug__C__Retry, Debug__C__Retry__Debug__B__Ac__Retry ) )
    {
        actionchain_____Debug__C__Retry__new_transition_12( msg );
        return Debug__C__Retry__Debug__B__Ac__Retry;
    }
    else if( check_history( Debug__C__Retry, Debug__C__Retry__Debug__A__Ac__Retry ) )
    {
        actionchain_____Debug__C__Retry__new_transition_13( msg );
        return Debug__C__Retry__Debug__A__Ac__Retry;
    }
    else if( check_history( Debug__C__Retry, Debug__C__Retry__Debug__A__En__getMasterName ) )
    {
        actionchain_____Debug__C__Retry__new_transition_14( msg );
        return Debug__C__Retry__Debug__A__En__getMasterName;
    }
    else if( check_history( Debug__C__Retry, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__Retry__new_transition_15_to_boundary( msg );
        return Debug__C__Retry__boundary;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::choice_____Debug__C__ServiceResult__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__ServiceResult, Debug__C__ServiceResult__Debug__B__Ex__WaitingForReply ) )
    {
        actionchain_____Debug__C__ServiceResult__new_transition_75( msg );
        return Debug__C__ServiceResult__Debug__B__Ex__WaitingForReply;
    }
    else if( check_history( Debug__C__ServiceResult, Debug__C__ServiceResult__Debug__B__Ac__ServiceResult ) )
    {
        actionchain_____Debug__C__ServiceResult__new_transition_76( msg );
        return Debug__C__ServiceResult__Debug__B__Ac__ServiceResult;
    }
    else if( check_history( Debug__C__ServiceResult, Debug__C__ServiceResult__Debug__A__Ac__ServiceResult ) )
    {
        actionchain_____Debug__C__ServiceResult__new_transition_77( msg );
        return Debug__C__ServiceResult__Debug__A__Ac__ServiceResult;
    }
    else if( check_history( Debug__C__ServiceResult, Debug__C__ServiceResult__Debug__A__En__ProcessResponse ) )
    {
        actionchain_____Debug__C__ServiceResult__new_transition_78( msg );
        return Debug__C__ServiceResult__Debug__A__En__ProcessResponse;
    }
    else if( check_history( Debug__C__ServiceResult, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__ServiceResult__new_transition_79_to_boundary( msg );
        return Debug__C__ServiceResult__boundary;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::choice_____Debug__C__StarupTransition__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__StarupTransition, Debug__C__StarupTransition__Debug__B__Ex__StandBY ) )
    {
        actionchain_____Debug__C__StarupTransition__new_transition_1( msg );
        return Debug__C__StarupTransition__Debug__B__Ex__StandBY;
    }
    else if( check_history( Debug__C__StarupTransition, Debug__C__StarupTransition__Debug__B__Ac__StarupTransition ) )
    {
        actionchain_____Debug__C__StarupTransition__new_transition_2( msg );
        return Debug__C__StarupTransition__Debug__B__Ac__StarupTransition;
    }
    else if( check_history( Debug__C__StarupTransition, Debug__C__StarupTransition__Debug__A__Ac__StarupTransition ) )
    {
        actionchain_____Debug__C__StarupTransition__new_transition_3( msg );
        return Debug__C__StarupTransition__Debug__A__Ac__StarupTransition;
    }
    else if( check_history( Debug__C__StarupTransition, Debug__C__StarupTransition__Debug__A__En__Ready ) )
    {
        actionchain_____Debug__C__StarupTransition__new_transition_4( msg );
        return Debug__C__StarupTransition__Debug__A__En__Ready;
    }
    else if( check_history( Debug__C__StarupTransition, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__StarupTransition__new_transition_5_to_boundary( msg );
        return Debug__C__StarupTransition__boundary;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::choice_____Debug__C__getMasterName__checkConfig__7__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__getMasterName__checkConfig__7, Debug__C__getMasterName__checkConfig__7__Debug__B__Ex__getMasterName ) )
    {
        actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_57( msg );
        return Debug__C__getMasterName__checkConfig__7__Debug__B__Ex__getMasterName;
    }
    else if( check_history( Debug__C__getMasterName__checkConfig__7, Debug__C__getMasterName__checkConfig__7__Debug__B__Ac__getMasterName__checkConfig__7 ) )
    {
        actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_58( msg );
        return Debug__C__getMasterName__checkConfig__7__Debug__B__Ac__getMasterName__checkConfig__7;
    }
    else if( check_history( Debug__C__getMasterName__checkConfig__7, Debug__C__getMasterName__checkConfig__7__Debug__A__Ac__getMasterName__checkConfig__7 ) )
    {
        actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_59( msg );
        return Debug__C__getMasterName__checkConfig__7__Debug__A__Ac__getMasterName__checkConfig__7;
    }
    else if( check_history( Debug__C__getMasterName__checkConfig__7, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_60_to_boundary( msg );
        return Debug__C__getMasterName__checkConfig__7__boundary;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::choice_____Debug__C__init__StandBY__6__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__init__StandBY__6, Debug__C__init__StandBY__6__Debug__B__Ac__init__StandBY__6 ) )
    {
        actionchain_____Debug__C__init__StandBY__6__new_transition_49( msg );
        return Debug__C__init__StandBY__6__Debug__B__Ac__init__StandBY__6;
    }
    else if( check_history( Debug__C__init__StandBY__6, Debug__C__init__StandBY__6__Debug__A__Ac__init__StandBY__6 ) )
    {
        actionchain_____Debug__C__init__StandBY__6__new_transition_50( msg );
        return Debug__C__init__StandBY__6__Debug__A__Ac__init__StandBY__6;
    }
    else if( check_history( Debug__C__init__StandBY__6, Debug__C__init__StandBY__6__Debug__A__En__init__StandBY__6 ) )
    {
        actionchain_____Debug__C__init__StandBY__6__new_transition_51( msg );
        return Debug__C__init__StandBY__6__Debug__A__En__init__StandBY__6;
    }
    else if( check_history( Debug__C__init__StandBY__6, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__init__StandBY__6__new_transition_52_to_boundary( msg );
        return Debug__C__init__StandBY__6__boundary;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::choice_____Debug__C__reqFlowInit__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__reqFlowInit, Debug__C__reqFlowInit__Debug__B__Ex__Ready ) )
    {
        actionchain_____Debug__C__reqFlowInit__new_transition_65( msg );
        return Debug__C__reqFlowInit__Debug__B__Ex__Ready;
    }
    else if( check_history( Debug__C__reqFlowInit, Debug__C__reqFlowInit__Debug__B__Ac__reqFlowInit ) )
    {
        actionchain_____Debug__C__reqFlowInit__new_transition_66( msg );
        return Debug__C__reqFlowInit__Debug__B__Ac__reqFlowInit;
    }
    else if( check_history( Debug__C__reqFlowInit, Debug__C__reqFlowInit__Debug__A__Ac__reqFlowInit ) )
    {
        actionchain_____Debug__C__reqFlowInit__new_transition_67( msg );
        return Debug__C__reqFlowInit__Debug__A__Ac__reqFlowInit;
    }
    else if( check_history( Debug__C__reqFlowInit, Debug__C__reqFlowInit__Debug__A__En__getMasterName ) )
    {
        actionchain_____Debug__C__reqFlowInit__new_transition_68( msg );
        return Debug__C__reqFlowInit__Debug__A__En__getMasterName;
    }
    else if( check_history( Debug__C__reqFlowInit, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__reqFlowInit__new_transition_69_to_boundary( msg );
        return Debug__C__reqFlowInit__boundary;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::choice_____Debug__C__reqService__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__reqService, Debug__C__reqService__Debug__B__Ac__reqService ) )
    {
        actionchain_____Debug__C__reqService__new_transition_85( msg );
        return Debug__C__reqService__Debug__B__Ac__reqService;
    }
    else if( check_history( Debug__C__reqService, Debug__C__reqService__Debug__A__Ac__reqService ) )
    {
        actionchain_____Debug__C__reqService__new_transition_86( msg );
        return Debug__C__reqService__Debug__A__Ac__reqService;
    }
    else if( check_history( Debug__C__reqService, Debug__C__reqService__Debug__A__En__reqService ) )
    {
        actionchain_____Debug__C__reqService__new_transition_87( msg );
        return Debug__C__reqService__Debug__A__En__reqService;
    }
    else if( check_history( Debug__C__reqService, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__reqService__new_transition_88_to_boundary( msg );
        return Debug__C__reqService__boundary;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::choice_____Debug__Path__NoMaster( const UMLRTMessage * msg )
{
    if( action_____Debug__NoMaster__S__Debug__GuardNoMaster( msg ) )
    {
        actionchain_____Debug__NoMaster__S( msg );
        return junction_____Debug__C__NoMaster__en( msg );
    }
    else
    {
        actionchain_____NoMaster( msg );
        return Retry;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::choice_____Debug__Path__NoResponseFromServer( const UMLRTMessage * msg )
{
    if( action_____Debug__NoResponseFromServer__S__Debug__GuardNoResponseFromServer( msg ) )
    {
        actionchain_____Debug__NoResponseFromServer__S( msg );
        return junction_____Debug__C__NoResponseFromServer__en( msg );
    }
    else
    {
        actionchain_____NoResponseFromServer( msg );
        return Ready;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::choice_____Debug__Path__ReqFlowDone( const UMLRTMessage * msg )
{
    if( action_____Debug__ReqFlowDone__S__Debug__GuardReqFlowDone( msg ) )
    {
        actionchain_____Debug__ReqFlowDone__S( msg );
        return junction_____Debug__C__ReqFlowDone__en( msg );
    }
    else
    {
        actionchain_____ReqFlowDone( msg );
        return Ready;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::choice_____Debug__Path__Retry( const UMLRTMessage * msg )
{
    if( action_____Debug__Retry__S__Debug__GuardRetry( msg ) )
    {
        actionchain_____Debug__Retry__S( msg );
        return junction_____Debug__C__Retry__en( msg );
    }
    else
    {
        actionchain_____Retry( msg );
        return getMasterName;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::choice_____Debug__Path__ServiceResult( const UMLRTMessage * msg )
{
    if( action_____Debug__ServiceResult__S__Debug__GuardServiceResult( msg ) )
    {
        actionchain_____Debug__ServiceResult__S( msg );
        return junction_____Debug__C__ServiceResult__en( msg );
    }
    else
    {
        actionchain_____ServiceResult( msg );
        return ProcessResponse;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::choice_____Debug__Path__StarupTransition( const UMLRTMessage * msg )
{
    if( action_____Debug__StarupTransition__S__Debug__GuardStarupTransition( msg ) )
    {
        actionchain_____Debug__StarupTransition__S( msg );
        return junction_____Debug__C__StarupTransition__en( msg );
    }
    else
    {
        actionchain_____StarupTransition( msg );
        return Ready;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::choice_____Debug__Path__getMasterName__checkConfig__7( const UMLRTMessage * msg )
{
    if( action_____Debug__getMasterName__checkConfig__7__S__Debug__GuardgetMasterName__checkConfig__7( msg ) )
    {
        actionchain_____Debug__getMasterName__checkConfig__7__S( msg );
        return junction_____Debug__C__getMasterName__checkConfig__7__en( msg );
    }
    else
    {
        actionchain_____getMasterName__checkConfig__7( msg );
        return choice_____checkConfig( msg );
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::choice_____Debug__Path__init__StandBY__6( const UMLRTMessage * msg )
{
    if( action_____Debug__init__StandBY__6__S__Debug__Guardinit__StandBY__6( msg ) )
    {
        actionchain_____Debug__init__StandBY__6__S( msg );
        return junction_____Debug__C__init__StandBY__6__en( msg );
    }
    else
    {
        actionchain_____init__StandBY__6( msg );
        return StandBY;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::choice_____Debug__Path__reqFlowInit( const UMLRTMessage * msg )
{
    if( action_____Debug__reqFlowInit__S__Debug__GuardreqFlowInit( msg ) )
    {
        actionchain_____Debug__reqFlowInit__S( msg );
        return junction_____Debug__C__reqFlowInit__en( msg );
    }
    else
    {
        actionchain_____reqFlowInit( msg );
        return getMasterName;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::choice_____Debug__Path__reqService( const UMLRTMessage * msg )
{
    if( action_____Debug__reqService__S__Debug__GuardreqService( msg ) )
    {
        actionchain_____Debug__reqService__S( msg );
        return junction_____Debug__C__reqService__en( msg );
    }
    else
    {
        actionchain_____reqService( msg );
        return WaitingForReply;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::choice_____checkConfig( const UMLRTMessage * msg )
{
    if( action_____Debug__reqService__MasterIsAvailable( msg ) )
    {
        actionchain_____Debug__reqService( msg );
        return choice_____Debug__Path__reqService( msg );
    }
    else
    {
        actionchain_____Debug__NoMaster( msg );
        return choice_____Debug__Path__NoMaster( msg );
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::state_____Debug__C__NoMaster__Debug__A__Ac__NoMaster( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__NoMaster__Debug__En__Retry( msg );
            return Debug__C__NoMaster__Debug__A__En__NoMaster;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__NoMaster__new_transition_26( msg );
            return junction_____Debug__C__NoMaster__new_exitpoint_3( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__NoMaster__Debug__A__En__NoMaster( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__NoMaster__Debug__end__trans__NoMaster( msg );
            return junction_____Debug__C__NoMaster__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__NoMaster__new_transition_27( msg );
            return junction_____Debug__C__NoMaster__new_exitpoint_3( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__NoMaster__Debug__B__Ac__NoMaster( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__NoMaster__Debug__Ac__NoMaster( msg );
            return Debug__C__NoMaster__Debug__A__Ac__NoMaster;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__NoMaster__new_transition_25( msg );
            return junction_____Debug__C__NoMaster__new_exitpoint_3( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__NoMaster__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__NoMaster__new_transition_28( msg );
            return junction_____Debug__C__NoMaster__new_exitpoint_3( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__NoResponseFromServer__Debug__A__Ac__NoResponseFromServer( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__NoResponseFromServer__Debug__En__Ready( msg );
            return Debug__C__NoResponseFromServer__Debug__A__En__Ready;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__NoResponseFromServer__new_transition_36( msg );
            return junction_____Debug__C__NoResponseFromServer__new_exitpoint_4( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__NoResponseFromServer__Debug__A__En__Ready( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__NoResponseFromServer__Debug__end__trans__NoResponseFromServer( msg );
            return junction_____Debug__C__NoResponseFromServer__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__NoResponseFromServer__new_transition_37( msg );
            return junction_____Debug__C__NoResponseFromServer__new_exitpoint_4( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__NoResponseFromServer__Debug__B__Ac__NoResponseFromServer( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__NoResponseFromServer__Debug__AC__NoResponseFromServer( msg );
            return Debug__C__NoResponseFromServer__Debug__A__Ac__NoResponseFromServer;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__NoResponseFromServer__new_transition_35( msg );
            return junction_____Debug__C__NoResponseFromServer__new_exitpoint_4( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__NoResponseFromServer__Debug__B__Ex__WaitingForReply( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__NoResponseFromServer__Debug__Ex__WaitingForReply( msg );
            return Debug__C__NoResponseFromServer__Debug__B__Ac__NoResponseFromServer;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__NoResponseFromServer__new_transition_34( msg );
            return junction_____Debug__C__NoResponseFromServer__new_exitpoint_4( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__NoResponseFromServer__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__NoResponseFromServer__new_transition_38( msg );
            return junction_____Debug__C__NoResponseFromServer__new_exitpoint_4( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__ReqFlowDone__Debug__A__Ac__ReqFlowDone( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__ReqFlowDone__Debug__En__Ready( msg );
            return Debug__C__ReqFlowDone__Debug__A__En__Ready;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ReqFlowDone__new_transition_46( msg );
            return junction_____Debug__C__ReqFlowDone__new_exitpoint_5( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__ReqFlowDone__Debug__A__En__Ready( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__ReqFlowDone__Debug__end__trans__ReqFlowDone( msg );
            return junction_____Debug__C__ReqFlowDone__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ReqFlowDone__new_transition_47( msg );
            return junction_____Debug__C__ReqFlowDone__new_exitpoint_5( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__ReqFlowDone__Debug__B__Ac__ReqFlowDone( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__ReqFlowDone__Debug__AC__ReqFlowDone( msg );
            return Debug__C__ReqFlowDone__Debug__A__Ac__ReqFlowDone;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ReqFlowDone__new_transition_45( msg );
            return junction_____Debug__C__ReqFlowDone__new_exitpoint_5( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__ReqFlowDone__Debug__B__Ex__ProcessResponse( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__ReqFlowDone__Debug__Ex__ProcessResponse( msg );
            return Debug__C__ReqFlowDone__Debug__B__Ac__ReqFlowDone;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ReqFlowDone__new_transition_44( msg );
            return junction_____Debug__C__ReqFlowDone__new_exitpoint_5( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__ReqFlowDone__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ReqFlowDone__new_transition_48( msg );
            return junction_____Debug__C__ReqFlowDone__new_exitpoint_5( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__Retry__Debug__A__Ac__Retry( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Retry__Debug__En__getMasterName( msg );
            return Debug__C__Retry__Debug__A__En__getMasterName;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Retry__new_transition_18( msg );
            return junction_____Debug__C__Retry__new_exitpoint_2( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__Retry__Debug__A__En__getMasterName( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Retry__Debug__end__trans__Retry( msg );
            return junction_____Debug__C__Retry__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Retry__new_transition_19( msg );
            return junction_____Debug__C__Retry__new_exitpoint_2( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__Retry__Debug__B__Ac__Retry( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Retry__Debug__AC__Retry( msg );
            return Debug__C__Retry__Debug__A__Ac__Retry;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Retry__new_transition_17( msg );
            return junction_____Debug__C__Retry__new_exitpoint_2( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__Retry__Debug__B__Ex__Retry( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Retry__Debug__Ex__Retry( msg );
            return Debug__C__Retry__Debug__B__Ac__Retry;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Retry__new_transition_16( msg );
            return junction_____Debug__C__Retry__new_exitpoint_2( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__Retry__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Retry__new_transition_20( msg );
            return junction_____Debug__C__Retry__new_exitpoint_2( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__ServiceResult__Debug__A__Ac__ServiceResult( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__ServiceResult__Debug__En__ProcessResponse( msg );
            return Debug__C__ServiceResult__Debug__A__En__ProcessResponse;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ServiceResult__new_transition_82( msg );
            return junction_____Debug__C__ServiceResult__new_exitpoint_9( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__ServiceResult__Debug__A__En__ProcessResponse( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__ServiceResult__Debug__end__trans__ServiceResult( msg );
            return junction_____Debug__C__ServiceResult__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ServiceResult__new_transition_83( msg );
            return junction_____Debug__C__ServiceResult__new_exitpoint_9( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__ServiceResult__Debug__B__Ac__ServiceResult( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__ServiceResult__Debug__AC__ServiceResult( msg );
            return Debug__C__ServiceResult__Debug__A__Ac__ServiceResult;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ServiceResult__new_transition_81( msg );
            return junction_____Debug__C__ServiceResult__new_exitpoint_9( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__ServiceResult__Debug__B__Ex__WaitingForReply( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__ServiceResult__Debug__Ex__WaitingForReply( msg );
            return Debug__C__ServiceResult__Debug__B__Ac__ServiceResult;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ServiceResult__new_transition_80( msg );
            return junction_____Debug__C__ServiceResult__new_exitpoint_9( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__ServiceResult__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ServiceResult__new_transition_84( msg );
            return junction_____Debug__C__ServiceResult__new_exitpoint_9( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__StarupTransition__Debug__A__Ac__StarupTransition( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__StarupTransition__Debug__En__Ready( msg );
            return Debug__C__StarupTransition__Debug__A__En__Ready;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__StarupTransition__new_transition_8( msg );
            return junction_____Debug__C__StarupTransition__new_exitpoint_1( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__StarupTransition__Debug__A__En__Ready( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__StarupTransition__Debug__end__trans__StarupTransition( msg );
            return junction_____Debug__C__StarupTransition__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__StarupTransition__new_transition_9( msg );
            return junction_____Debug__C__StarupTransition__new_exitpoint_1( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__StarupTransition__Debug__B__Ac__StarupTransition( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__StarupTransition__Debug__AC__StarupTransition( msg );
            return Debug__C__StarupTransition__Debug__A__Ac__StarupTransition;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__StarupTransition__new_transition_7( msg );
            return junction_____Debug__C__StarupTransition__new_exitpoint_1( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__StarupTransition__Debug__B__Ex__StandBY( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__StarupTransition__Debug__Ex__StandBY( msg );
            return Debug__C__StarupTransition__Debug__B__Ac__StarupTransition;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__StarupTransition__new_transition_6( msg );
            return junction_____Debug__C__StarupTransition__new_exitpoint_1( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__StarupTransition__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__StarupTransition__new_transition_10( msg );
            return junction_____Debug__C__StarupTransition__new_exitpoint_1( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__getMasterName__checkConfig__7__Debug__A__Ac__getMasterName__checkConfig__7( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__getMasterName__checkConfig__7__Debug__end__trans__getMasterName__checkConfig__7( msg );
            return junction_____Debug__C__getMasterName__checkConfig__7__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_63( msg );
            return junction_____Debug__C__getMasterName__checkConfig__7__new_exitpoint_7( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__getMasterName__checkConfig__7__Debug__B__Ac__getMasterName__checkConfig__7( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__getMasterName__checkConfig__7__Debug__AC__getMasterName__checkConfig__7( msg );
            return Debug__C__getMasterName__checkConfig__7__Debug__A__Ac__getMasterName__checkConfig__7;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_62( msg );
            return junction_____Debug__C__getMasterName__checkConfig__7__new_exitpoint_7( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__getMasterName__checkConfig__7__Debug__B__Ex__getMasterName( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__getMasterName__checkConfig__7__Debug__Ex__getMasterName( msg );
            return Debug__C__getMasterName__checkConfig__7__Debug__B__Ac__getMasterName__checkConfig__7;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_61( msg );
            return junction_____Debug__C__getMasterName__checkConfig__7__new_exitpoint_7( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__getMasterName__checkConfig__7__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_64( msg );
            return junction_____Debug__C__getMasterName__checkConfig__7__new_exitpoint_7( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__init__StandBY__6__Debug__A__Ac__init__StandBY__6( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__init__StandBY__6__Debug__En__StandBY( msg );
            return Debug__C__init__StandBY__6__Debug__A__En__init__StandBY__6;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__init__StandBY__6__new_transition_54( msg );
            return junction_____Debug__C__init__StandBY__6__new_exitpoint_6( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__init__StandBY__6__Debug__A__En__init__StandBY__6( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__init__StandBY__6__Debug__end__trans__init__StandBY__6( msg );
            return junction_____Debug__C__init__StandBY__6__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__init__StandBY__6__new_transition_55( msg );
            return junction_____Debug__C__init__StandBY__6__new_exitpoint_6( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__init__StandBY__6__Debug__B__Ac__init__StandBY__6( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__init__StandBY__6__Debug__Ac__init__StandBY__6( msg );
            return Debug__C__init__StandBY__6__Debug__A__Ac__init__StandBY__6;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__init__StandBY__6__new_transition_53( msg );
            return junction_____Debug__C__init__StandBY__6__new_exitpoint_6( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__init__StandBY__6__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__init__StandBY__6__new_transition_56( msg );
            return junction_____Debug__C__init__StandBY__6__new_exitpoint_6( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__reqFlowInit__Debug__A__Ac__reqFlowInit( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__reqFlowInit__Debug__En__getMasterName( msg );
            return Debug__C__reqFlowInit__Debug__A__En__getMasterName;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__reqFlowInit__new_transition_72( msg );
            return junction_____Debug__C__reqFlowInit__new_exitpoint_8( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__reqFlowInit__Debug__A__En__getMasterName( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__reqFlowInit__Debug__end__trans__reqFlowInit( msg );
            return junction_____Debug__C__reqFlowInit__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__reqFlowInit__new_transition_73( msg );
            return junction_____Debug__C__reqFlowInit__new_exitpoint_8( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__reqFlowInit__Debug__B__Ac__reqFlowInit( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__reqFlowInit__Debug__AC__reqFlowInit( msg );
            return Debug__C__reqFlowInit__Debug__A__Ac__reqFlowInit;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__reqFlowInit__new_transition_71( msg );
            return junction_____Debug__C__reqFlowInit__new_exitpoint_8( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__reqFlowInit__Debug__B__Ex__Ready( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__reqFlowInit__Debug__Ex__Ready( msg );
            return Debug__C__reqFlowInit__Debug__B__Ac__reqFlowInit;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__reqFlowInit__new_transition_70( msg );
            return junction_____Debug__C__reqFlowInit__new_exitpoint_8( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__reqFlowInit__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__reqFlowInit__new_transition_74( msg );
            return junction_____Debug__C__reqFlowInit__new_exitpoint_8( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__reqService__Debug__A__Ac__reqService( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__reqService__Debug__En__WaitingForReply( msg );
            return Debug__C__reqService__Debug__A__En__reqService;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__reqService__new_transition_90( msg );
            return junction_____Debug__C__reqService__new_exitpoint_10( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__reqService__Debug__A__En__reqService( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__reqService__Debug__end__trans__reqService( msg );
            return junction_____Debug__C__reqService__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__reqService__new_transition_91( msg );
            return junction_____Debug__C__reqService__new_exitpoint_10( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__reqService__Debug__B__Ac__reqService( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__reqService__Debug__Ac__reqService( msg );
            return Debug__C__reqService__Debug__A__Ac__reqService;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__reqService__new_transition_89( msg );
            return junction_____Debug__C__reqService__new_exitpoint_10( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__C__reqService__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__reqService__new_transition_92( msg );
            return junction_____Debug__C__reqService__new_exitpoint_10( msg );
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

Capsule_Client::State Capsule_Client::state_____Debug__InitState( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__init__StandBY__6( msg );
            return choice_____Debug__Path__init__StandBY__6( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::state_____ProcessResponse( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_Timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____Debug__ReqFlowDone( msg );
            return choice_____Debug__Path__ReqFlowDone( msg );
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

Capsule_Client::State Capsule_Client::state_____Ready( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_RequestTimer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____Debug__reqFlowInit( msg );
            return choice_____Debug__Path__reqFlowInit( msg );
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

Capsule_Client::State Capsule_Client::state_____Retry( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_Timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____Debug__Retry( msg );
            return choice_____Debug__Path__Retry( msg );
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

Capsule_Client::State Capsule_Client::state_____StandBY( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_ConfigComm:
        switch( msg->getSignalId() )
        {
        case Config::signal_StartUp:
            actionchain_____Debug__StarupTransition( msg );
            return choice_____Debug__Path__StarupTransition( msg );
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

Capsule_Client::State Capsule_Client::state_____WaitingForReply( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_ResponseTimer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____Debug__NoResponseFromServer( msg );
            return choice_____Debug__Path__NoResponseFromServer( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_Server1Comm:
        switch( msg->getSignalId() )
        {
        case Services::signal_Reply:
            actionchain_____Debug__ServiceResult( msg );
            return choice_____Debug__Path__ServiceResult( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_Server2Comm:
        switch( msg->getSignalId() )
        {
        case Services::signal_Reply:
            actionchain_____Debug__ServiceResult( msg );
            return choice_____Debug__Path__ServiceResult( msg );
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

Capsule_Client::State Capsule_Client::state_____getMasterName( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_ConfigComm:
        switch( msg->getSignalId() )
        {
        case Config::signal_ReplyConfig:
            actionchain_____Debug__getMasterName__checkConfig__7( msg );
            return choice_____Debug__Path__getMasterName__checkConfig__7( msg );
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
        Capsule_Client::port_ConfigComm,
        "Config",
        "ConfigComm",
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
        Capsule_Client::port_ConfigTimer,
        "Timing",
        "ConfigTimer",
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
        Capsule_Client::port_RequestTimer,
        "Timing",
        "RequestTimer",
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
        Capsule_Client::port_ResponseTimer,
        "Timing",
        "ResponseTimer",
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
        Capsule_Client::port_Server1Comm,
        "Services",
        "Server1Comm",
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
        Capsule_Client::port_Server2Comm,
        "Services",
        "Server2Comm",
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
        Capsule_Client::port_Timer,
        "Timing",
        "Timer",
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
        Capsule_Client::port_extComm,
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
    }
};

static void instantiate_Client( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_Client( &Client, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Client = 
{
    "Client",
    &Host,
    instantiate_Client,
    0,
    NULL,
    8,
    portroles_border,
    0,
    NULL
};

