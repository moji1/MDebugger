
#include "ENV.hh"

#include "Config.hh"
#include "ExtInterface.hh"
#include "FailOver.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include "umlrttimerprotocol.hh"
#include <cstddef>
class UMLRTRtsInterface;
struct UMLRTCommsPort;

#include<iostream>

Capsule_ENV::Capsule_ENV( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, AnnouncmentServer1( borderPorts[borderport_AnnouncmentServer1] )
, AnnouncmentServer2( borderPorts[borderport_AnnouncmentServer2] )
, BITTimer( borderPorts[borderport_BITTimer] )
, ConfigComm( borderPorts[borderport_ConfigComm] )
, FailureTimer( borderPorts[borderport_FailureTimer] )
, GeneralTimer( borderPorts[borderport_GeneralTimer] )
, configTimer( borderPorts[borderport_configTimer] )
, extComm( borderPorts[borderport_extComm] )
, AnnouncmentServerTimeout( 6 )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[Debug__C__ConfigNOK] = "Debug__C__ConfigNOK";
    stateNames[Debug__C__Init__ReadConfig__8] = "Debug__C__Init__ReadConfig__8";
    stateNames[Debug__C__MasterAnnouncment] = "Debug__C__MasterAnnouncment";
    stateNames[Debug__C__QueryConfig] = "Debug__C__QueryConfig";
    stateNames[Debug__C__RetryConfig] = "Debug__C__RetryConfig";
    stateNames[Debug__C__Server1Failure] = "Debug__C__Server1Failure";
    stateNames[Debug__C__configLoaded] = "Debug__C__configLoaded";
    stateNames[Debug__C__configOK] = "Debug__C__configOK";
    stateNames[Debug__C__server2Failure] = "Debug__C__server2Failure";
    stateNames[ConfigFailure] = "ConfigFailure";
    stateNames[Debug__C__ConfigNOK__Debug__A__Ac__ConfigNOK] = "Debug__C__ConfigNOK__Debug__A__Ac__ConfigNOK";
    stateNames[Debug__C__ConfigNOK__Debug__A__En__ConfigNOK] = "Debug__C__ConfigNOK__Debug__A__En__ConfigNOK";
    stateNames[Debug__C__ConfigNOK__Debug__B__Ac__ConfigNOK] = "Debug__C__ConfigNOK__Debug__B__Ac__ConfigNOK";
    stateNames[Debug__C__ConfigNOK__boundary] = "Debug__C__ConfigNOK__boundary";
    stateNames[Debug__C__Init__ReadConfig__8__Debug__A__Ac__Init__ReadConfig__8] = "Debug__C__Init__ReadConfig__8__Debug__A__Ac__Init__ReadConfig__8";
    stateNames[Debug__C__Init__ReadConfig__8__Debug__A__En__Init__ReadConfig__8] = "Debug__C__Init__ReadConfig__8__Debug__A__En__Init__ReadConfig__8";
    stateNames[Debug__C__Init__ReadConfig__8__Debug__B__Ac__Init__ReadConfig__8] = "Debug__C__Init__ReadConfig__8__Debug__B__Ac__Init__ReadConfig__8";
    stateNames[Debug__C__Init__ReadConfig__8__boundary] = "Debug__C__Init__ReadConfig__8__boundary";
    stateNames[Debug__C__MasterAnnouncment__Debug__A__Ac__MasterAnnouncment] = "Debug__C__MasterAnnouncment__Debug__A__Ac__MasterAnnouncment";
    stateNames[Debug__C__MasterAnnouncment__Debug__A__En__Running] = "Debug__C__MasterAnnouncment__Debug__A__En__Running";
    stateNames[Debug__C__MasterAnnouncment__Debug__B__Ac__MasterAnnouncment] = "Debug__C__MasterAnnouncment__Debug__B__Ac__MasterAnnouncment";
    stateNames[Debug__C__MasterAnnouncment__Debug__B__Ex__Running] = "Debug__C__MasterAnnouncment__Debug__B__Ex__Running";
    stateNames[Debug__C__MasterAnnouncment__boundary] = "Debug__C__MasterAnnouncment__boundary";
    stateNames[Debug__C__QueryConfig__Debug__A__Ac__QueryConfig] = "Debug__C__QueryConfig__Debug__A__Ac__QueryConfig";
    stateNames[Debug__C__QueryConfig__Debug__A__En__Running] = "Debug__C__QueryConfig__Debug__A__En__Running";
    stateNames[Debug__C__QueryConfig__Debug__B__Ac__QueryConfig] = "Debug__C__QueryConfig__Debug__B__Ac__QueryConfig";
    stateNames[Debug__C__QueryConfig__Debug__B__Ex__Running] = "Debug__C__QueryConfig__Debug__B__Ex__Running";
    stateNames[Debug__C__QueryConfig__boundary] = "Debug__C__QueryConfig__boundary";
    stateNames[Debug__C__RetryConfig__Debug__A__Ac__RetryConfig] = "Debug__C__RetryConfig__Debug__A__Ac__RetryConfig";
    stateNames[Debug__C__RetryConfig__Debug__A__En__ReadConfig] = "Debug__C__RetryConfig__Debug__A__En__ReadConfig";
    stateNames[Debug__C__RetryConfig__Debug__B__Ac__RetryConfig] = "Debug__C__RetryConfig__Debug__B__Ac__RetryConfig";
    stateNames[Debug__C__RetryConfig__Debug__B__Ex__ConfigFailure] = "Debug__C__RetryConfig__Debug__B__Ex__ConfigFailure";
    stateNames[Debug__C__RetryConfig__boundary] = "Debug__C__RetryConfig__boundary";
    stateNames[Debug__C__Server1Failure__Debug__A__Ac__Server1Failure] = "Debug__C__Server1Failure__Debug__A__Ac__Server1Failure";
    stateNames[Debug__C__Server1Failure__Debug__A__En__Running] = "Debug__C__Server1Failure__Debug__A__En__Running";
    stateNames[Debug__C__Server1Failure__Debug__B__Ac__Server1Failure] = "Debug__C__Server1Failure__Debug__B__Ac__Server1Failure";
    stateNames[Debug__C__Server1Failure__Debug__B__Ex__Running] = "Debug__C__Server1Failure__Debug__B__Ex__Running";
    stateNames[Debug__C__Server1Failure__boundary] = "Debug__C__Server1Failure__boundary";
    stateNames[Debug__C__configLoaded__Debug__A__Ac__configLoaded] = "Debug__C__configLoaded__Debug__A__Ac__configLoaded";
    stateNames[Debug__C__configLoaded__Debug__B__Ac__configLoaded] = "Debug__C__configLoaded__Debug__B__Ac__configLoaded";
    stateNames[Debug__C__configLoaded__Debug__B__Ex__ReadConfig] = "Debug__C__configLoaded__Debug__B__Ex__ReadConfig";
    stateNames[Debug__C__configLoaded__boundary] = "Debug__C__configLoaded__boundary";
    stateNames[Debug__C__configOK__Debug__A__Ac__configOK] = "Debug__C__configOK__Debug__A__Ac__configOK";
    stateNames[Debug__C__configOK__Debug__A__En__configOK] = "Debug__C__configOK__Debug__A__En__configOK";
    stateNames[Debug__C__configOK__Debug__B__Ac__configOK] = "Debug__C__configOK__Debug__B__Ac__configOK";
    stateNames[Debug__C__configOK__boundary] = "Debug__C__configOK__boundary";
    stateNames[Debug__C__server2Failure__Debug__A__Ac__server2Failure] = "Debug__C__server2Failure__Debug__A__Ac__server2Failure";
    stateNames[Debug__C__server2Failure__Debug__A__En__Running] = "Debug__C__server2Failure__Debug__A__En__Running";
    stateNames[Debug__C__server2Failure__Debug__B__Ac__server2Failure] = "Debug__C__server2Failure__Debug__B__Ac__server2Failure";
    stateNames[Debug__C__server2Failure__Debug__B__Ex__Running] = "Debug__C__server2Failure__Debug__B__Ex__Running";
    stateNames[Debug__C__server2Failure__boundary] = "Debug__C__server2Failure__boundary";
    stateNames[Debug__InitState] = "Debug__InitState";
    stateNames[ReadConfig] = "ReadConfig";
    stateNames[Running] = "Running";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
    int i = 0;
    while( i < 9 )
        history[i++] = SPECIAL_INTERNAL_STATE_UNVISITED;
}












void Capsule_ENV::bindPort( bool isBorder, int portId, int index )
{
}

void Capsule_ENV::unbindPort( bool isBorder, int portId, int index )
{
}










void Capsule_ENV::Debug__variablesView()
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV operation Debug__variablesView */
    std::string tempS="";
    //tempS.append(config->variablesData);
    tempS.append("AnnouncmentServerTimeout,");
    tempS.append("Integer,");
    if(AnnouncmentServerTimeout!=0){
    char tempR[10];
    sprintf(tempR,"%d",AnnouncmentServerTimeout);
    tempS.append(tempR);
    tempS.append("\n");
    }else {
    tempS.append("0");
    tempS.append("\n");
    };
    //tempS.append(configuration->variablesData);
    if (Debug__variablesData==NULL)
    Debug__variablesData=(char *)malloc(strlen(tempS.c_str())+1);
    else if (strlen(Debug__variablesData)<strlen(tempS.c_str()))
    Debug__variablesData=(char *) realloc(Debug__variablesData,strlen(tempS.c_str())+1);
    strcpy(Debug__variablesData,tempS.c_str());
    /* UMLRTGEN-USERREGION-END */
}

bool Capsule_ENV::Debug__variablesChange( char * varName, char * varValue )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV operation Debug__variablesChange */
    std::string tempVarName="";
    tempVarName.append(varName);
    if ("AnnouncmentServerTimeout"==tempVarName){
    AnnouncmentServerTimeout=atoi(varValue);
    return true;
    }else 
    return false;
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_ENV::Debug__sendEvent( debugEvents::EVENTSOURCEKIND eventSourceKind, debugEvents::EVENTTYPE eventType, const char * instanceName, int capsuleIndex, const char * signalName, char * capsuleName, char * sourceName, char * reserve1, char * reserve2, char * reserve3 )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV operation Debug__sendEvent */
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

void Capsule_ENV::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case ReadConfig:
        currentState = state_____ReadConfig( &message );
        break;
    case Running:
        currentState = state_____Running( &message );
        break;
    case ConfigFailure:
        currentState = state_____ConfigFailure( &message );
        break;
    case Debug__InitState:
        currentState = state_____Debug__InitState( &message );
        break;
    case Debug__C__MasterAnnouncment__Debug__B__Ex__Running:
        currentState = state_____Debug__C__MasterAnnouncment__Debug__B__Ex__Running( &message );
        break;
    case Debug__C__MasterAnnouncment__Debug__B__Ac__MasterAnnouncment:
        currentState = state_____Debug__C__MasterAnnouncment__Debug__B__Ac__MasterAnnouncment( &message );
        break;
    case Debug__C__MasterAnnouncment__Debug__A__Ac__MasterAnnouncment:
        currentState = state_____Debug__C__MasterAnnouncment__Debug__A__Ac__MasterAnnouncment( &message );
        break;
    case Debug__C__MasterAnnouncment__Debug__A__En__Running:
        currentState = state_____Debug__C__MasterAnnouncment__Debug__A__En__Running( &message );
        break;
    case Debug__C__MasterAnnouncment__boundary:
        currentState = state_____Debug__C__MasterAnnouncment__boundary( &message );
        break;
    case Debug__C__Init__ReadConfig__8__Debug__B__Ac__Init__ReadConfig__8:
        currentState = state_____Debug__C__Init__ReadConfig__8__Debug__B__Ac__Init__ReadConfig__8( &message );
        break;
    case Debug__C__Init__ReadConfig__8__Debug__A__Ac__Init__ReadConfig__8:
        currentState = state_____Debug__C__Init__ReadConfig__8__Debug__A__Ac__Init__ReadConfig__8( &message );
        break;
    case Debug__C__Init__ReadConfig__8__Debug__A__En__Init__ReadConfig__8:
        currentState = state_____Debug__C__Init__ReadConfig__8__Debug__A__En__Init__ReadConfig__8( &message );
        break;
    case Debug__C__Init__ReadConfig__8__boundary:
        currentState = state_____Debug__C__Init__ReadConfig__8__boundary( &message );
        break;
    case Debug__C__RetryConfig__Debug__B__Ex__ConfigFailure:
        currentState = state_____Debug__C__RetryConfig__Debug__B__Ex__ConfigFailure( &message );
        break;
    case Debug__C__RetryConfig__Debug__B__Ac__RetryConfig:
        currentState = state_____Debug__C__RetryConfig__Debug__B__Ac__RetryConfig( &message );
        break;
    case Debug__C__RetryConfig__Debug__A__Ac__RetryConfig:
        currentState = state_____Debug__C__RetryConfig__Debug__A__Ac__RetryConfig( &message );
        break;
    case Debug__C__RetryConfig__Debug__A__En__ReadConfig:
        currentState = state_____Debug__C__RetryConfig__Debug__A__En__ReadConfig( &message );
        break;
    case Debug__C__RetryConfig__boundary:
        currentState = state_____Debug__C__RetryConfig__boundary( &message );
        break;
    case Debug__C__server2Failure__Debug__B__Ex__Running:
        currentState = state_____Debug__C__server2Failure__Debug__B__Ex__Running( &message );
        break;
    case Debug__C__server2Failure__Debug__B__Ac__server2Failure:
        currentState = state_____Debug__C__server2Failure__Debug__B__Ac__server2Failure( &message );
        break;
    case Debug__C__server2Failure__Debug__A__Ac__server2Failure:
        currentState = state_____Debug__C__server2Failure__Debug__A__Ac__server2Failure( &message );
        break;
    case Debug__C__server2Failure__Debug__A__En__Running:
        currentState = state_____Debug__C__server2Failure__Debug__A__En__Running( &message );
        break;
    case Debug__C__server2Failure__boundary:
        currentState = state_____Debug__C__server2Failure__boundary( &message );
        break;
    case Debug__C__configOK__Debug__B__Ac__configOK:
        currentState = state_____Debug__C__configOK__Debug__B__Ac__configOK( &message );
        break;
    case Debug__C__configOK__Debug__A__Ac__configOK:
        currentState = state_____Debug__C__configOK__Debug__A__Ac__configOK( &message );
        break;
    case Debug__C__configOK__Debug__A__En__configOK:
        currentState = state_____Debug__C__configOK__Debug__A__En__configOK( &message );
        break;
    case Debug__C__configOK__boundary:
        currentState = state_____Debug__C__configOK__boundary( &message );
        break;
    case Debug__C__configLoaded__Debug__B__Ex__ReadConfig:
        currentState = state_____Debug__C__configLoaded__Debug__B__Ex__ReadConfig( &message );
        break;
    case Debug__C__configLoaded__Debug__B__Ac__configLoaded:
        currentState = state_____Debug__C__configLoaded__Debug__B__Ac__configLoaded( &message );
        break;
    case Debug__C__configLoaded__Debug__A__Ac__configLoaded:
        currentState = state_____Debug__C__configLoaded__Debug__A__Ac__configLoaded( &message );
        break;
    case Debug__C__configLoaded__boundary:
        currentState = state_____Debug__C__configLoaded__boundary( &message );
        break;
    case Debug__C__ConfigNOK__Debug__B__Ac__ConfigNOK:
        currentState = state_____Debug__C__ConfigNOK__Debug__B__Ac__ConfigNOK( &message );
        break;
    case Debug__C__ConfigNOK__Debug__A__Ac__ConfigNOK:
        currentState = state_____Debug__C__ConfigNOK__Debug__A__Ac__ConfigNOK( &message );
        break;
    case Debug__C__ConfigNOK__Debug__A__En__ConfigNOK:
        currentState = state_____Debug__C__ConfigNOK__Debug__A__En__ConfigNOK( &message );
        break;
    case Debug__C__ConfigNOK__boundary:
        currentState = state_____Debug__C__ConfigNOK__boundary( &message );
        break;
    case Debug__C__QueryConfig__Debug__B__Ex__Running:
        currentState = state_____Debug__C__QueryConfig__Debug__B__Ex__Running( &message );
        break;
    case Debug__C__QueryConfig__Debug__B__Ac__QueryConfig:
        currentState = state_____Debug__C__QueryConfig__Debug__B__Ac__QueryConfig( &message );
        break;
    case Debug__C__QueryConfig__Debug__A__Ac__QueryConfig:
        currentState = state_____Debug__C__QueryConfig__Debug__A__Ac__QueryConfig( &message );
        break;
    case Debug__C__QueryConfig__Debug__A__En__Running:
        currentState = state_____Debug__C__QueryConfig__Debug__A__En__Running( &message );
        break;
    case Debug__C__QueryConfig__boundary:
        currentState = state_____Debug__C__QueryConfig__boundary( &message );
        break;
    case Debug__C__Server1Failure__Debug__B__Ex__Running:
        currentState = state_____Debug__C__Server1Failure__Debug__B__Ex__Running( &message );
        break;
    case Debug__C__Server1Failure__Debug__B__Ac__Server1Failure:
        currentState = state_____Debug__C__Server1Failure__Debug__B__Ac__Server1Failure( &message );
        break;
    case Debug__C__Server1Failure__Debug__A__Ac__Server1Failure:
        currentState = state_____Debug__C__Server1Failure__Debug__A__Ac__Server1Failure( &message );
        break;
    case Debug__C__Server1Failure__Debug__A__En__Running:
        currentState = state_____Debug__C__Server1Failure__Debug__A__En__Running( &message );
        break;
    case Debug__C__Server1Failure__boundary:
        currentState = state_____Debug__C__Server1Failure__boundary( &message );
        break;
    default:
        break;
    }
}

void Capsule_ENV::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Debug__InitDebug( &message );
    currentState = Debug__InitState;
}

const char * Capsule_ENV::getCurrentStateString() const
{
    return stateNames[currentState];
}





void Capsule_ENV::save_history( Capsule_ENV::State compositeState, Capsule_ENV::State subState )
{
    history[compositeState] = subState;
}

bool Capsule_ENV::check_history( Capsule_ENV::State compositeState, Capsule_ENV::State subState )
{
    return history[compositeState] == subState;
}

void Capsule_ENV::entryaction_____ConfigFailure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::ConfigFailure entry  */
    if( not Debug__SRO.checkDebug("ConfigFailure",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::ConfigFailure",(char *)"",(char *)"",(char *)"");
    std::cout<<"ENV: The system is in Failure State, try to reload the config after 10 second\n";
    FailureTimer.informIn(UMLRTTimespec(10,0),4);
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__ConfigNOK__Debug__A__Ac__ConfigNOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__ConfigNOK::Debug__A__Ac__ConfigNOK entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__ConfigNOK::Region1::Debug__A__Ac__ConfigNOK",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("ConfigNOK","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("ConfigFailure","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__ConfigNOK__Debug__A__En__ConfigNOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__ConfigNOK::Debug__A__En__ConfigNOK entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__ConfigNOK::Region1::Debug__A__En__ConfigNOK",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("ConfigFailure","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__ConfigNOK__Debug__B__Ac__ConfigNOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__ConfigNOK::Debug__B__Ac__ConfigNOK entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__ConfigNOK::Region1::Debug__B__Ac__ConfigNOK",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("ConfigNOK","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__ConfigNOK__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__Init__ReadConfig__8__Debug__A__Ac__Init__ReadConfig__8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__Init__ReadConfig__8::Debug__A__Ac__Init__ReadConfig__8 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__Init__ReadConfig__8::Region1::Debug__A__Ac__Init__ReadConfig__8",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Init__ReadConfig__8","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("ReadConfig","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__Init__ReadConfig__8__Debug__A__En__Init__ReadConfig__8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__Init__ReadConfig__8::Debug__A__En__Init__ReadConfig__8 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__Init__ReadConfig__8::Region1::Debug__A__En__Init__ReadConfig__8",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("ReadConfig","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__Init__ReadConfig__8__Debug__B__Ac__Init__ReadConfig__8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__Init__ReadConfig__8::Debug__B__Ac__Init__ReadConfig__8 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__Init__ReadConfig__8::Region1::Debug__B__Ac__Init__ReadConfig__8",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Init__ReadConfig__8","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__Init__ReadConfig__8__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__MasterAnnouncment__Debug__A__Ac__MasterAnnouncment( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__MasterAnnouncment::Debug__A__Ac__MasterAnnouncment entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__MasterAnnouncment::Region1::Debug__A__Ac__MasterAnnouncment",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("MasterAnnouncment","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("Running","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__MasterAnnouncment__Debug__A__En__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__MasterAnnouncment::Debug__A__En__Running entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__MasterAnnouncment::Region1::Debug__A__En__Running",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Running","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__MasterAnnouncment__Debug__B__Ac__MasterAnnouncment( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__MasterAnnouncment::Debug__B__Ac__MasterAnnouncment entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__MasterAnnouncment::Region1::Debug__B__Ac__MasterAnnouncment",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Running","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("MasterAnnouncment","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__MasterAnnouncment__Debug__B__Ex__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__MasterAnnouncment::Debug__B__Ex__Running entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__MasterAnnouncment::Region1::Debug__B__Ex__Running",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Running","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__MasterAnnouncment__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__QueryConfig__Debug__A__Ac__QueryConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__QueryConfig::Debug__A__Ac__QueryConfig entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__QueryConfig::Region1::Debug__A__Ac__QueryConfig",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("QueryConfig","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("Running","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__QueryConfig__Debug__A__En__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__QueryConfig::Debug__A__En__Running entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__QueryConfig::Region1::Debug__A__En__Running",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Running","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__QueryConfig__Debug__B__Ac__QueryConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__QueryConfig::Debug__B__Ac__QueryConfig entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__QueryConfig::Region1::Debug__B__Ac__QueryConfig",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Running","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("QueryConfig","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__QueryConfig__Debug__B__Ex__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__QueryConfig::Debug__B__Ex__Running entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__QueryConfig::Region1::Debug__B__Ex__Running",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Running","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__QueryConfig__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__RetryConfig__Debug__A__Ac__RetryConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__RetryConfig::Debug__A__Ac__RetryConfig entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__RetryConfig::Region1::Debug__A__Ac__RetryConfig",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("RetryConfig","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("ReadConfig","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__RetryConfig__Debug__A__En__ReadConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__RetryConfig::Debug__A__En__ReadConfig entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__RetryConfig::Region1::Debug__A__En__ReadConfig",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("ReadConfig","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__RetryConfig__Debug__B__Ac__RetryConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__RetryConfig::Debug__B__Ac__RetryConfig entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__RetryConfig::Region1::Debug__B__Ac__RetryConfig",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("ConfigFailure","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("RetryConfig","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__RetryConfig__Debug__B__Ex__ConfigFailure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__RetryConfig::Debug__B__Ex__ConfigFailure entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__RetryConfig::Region1::Debug__B__Ex__ConfigFailure",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("ConfigFailure","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__RetryConfig__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__Server1Failure__Debug__A__Ac__Server1Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__Server1Failure::Debug__A__Ac__Server1Failure entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__Server1Failure::Region1::Debug__A__Ac__Server1Failure",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Server1Failure","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("Running","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__Server1Failure__Debug__A__En__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__Server1Failure::Debug__A__En__Running entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__Server1Failure::Region1::Debug__A__En__Running",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Running","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__Server1Failure__Debug__B__Ac__Server1Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__Server1Failure::Debug__B__Ac__Server1Failure entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__Server1Failure::Region1::Debug__B__Ac__Server1Failure",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Running","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("Server1Failure","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__Server1Failure__Debug__B__Ex__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__Server1Failure::Debug__B__Ex__Running entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__Server1Failure::Region1::Debug__B__Ex__Running",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Running","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__Server1Failure__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__configLoaded__Debug__A__Ac__configLoaded( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__configLoaded::Debug__A__Ac__configLoaded entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__configLoaded::Region1::Debug__A__Ac__configLoaded",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("configLoaded","","",3,TransitionEffectBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__configLoaded__Debug__B__Ac__configLoaded( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__configLoaded::Debug__B__Ac__configLoaded entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__configLoaded::Region1::Debug__B__Ac__configLoaded",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("ReadConfig","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("configLoaded","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__configLoaded__Debug__B__Ex__ReadConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__configLoaded::Debug__B__Ex__ReadConfig entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__configLoaded::Region1::Debug__B__Ex__ReadConfig",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("ReadConfig","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__configLoaded__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__configOK__Debug__A__Ac__configOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__configOK::Debug__A__Ac__configOK entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__configOK::Region1::Debug__A__Ac__configOK",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("configOK","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("Running","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__configOK__Debug__A__En__configOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__configOK::Debug__A__En__configOK entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__configOK::Region1::Debug__A__En__configOK",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Running","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__configOK__Debug__B__Ac__configOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__configOK::Debug__B__Ac__configOK entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__configOK::Region1::Debug__B__Ac__configOK",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("configOK","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__configOK__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__server2Failure__Debug__A__Ac__server2Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__server2Failure::Debug__A__Ac__server2Failure entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__server2Failure::Region1::Debug__A__Ac__server2Failure",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("server2Failure","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("Running","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__server2Failure__Debug__A__En__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__server2Failure::Debug__A__En__Running entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__server2Failure::Region1::Debug__A__En__Running",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Running","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__server2Failure__Debug__B__Ac__server2Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__server2Failure::Debug__B__Ac__server2Failure entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__server2Failure::Region1::Debug__B__Ac__server2Failure",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Running","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("server2Failure","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__server2Failure__Debug__B__Ex__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__server2Failure::Debug__B__Ex__Running entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__server2Failure::Region1::Debug__B__Ex__Running",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Running","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__C__server2Failure__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ENV::entryaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__InitState entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____ReadConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::ReadConfig entry  */
    if( not Debug__SRO.checkDebug("ReadConfig",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::ReadConfig",(char *)"",(char *)"",(char *)"");
    std::cout<<"ENV: Reading the configuration \n";
    configTimer.informIn(UMLRTTimespec(3,0));
    config.loadConfig();
    std::cout<<"ENV: Reading the configuration was done\n";
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Running entry  */
    if( not Debug__SRO.checkDebug("Running",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Running",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____ConfigFailure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::ConfigFailure exit  */
    if( not Debug__SRO.checkDebug("ConfigFailure",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::ConfigFailure",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__ConfigNOK__Debug__A__Ac__ConfigNOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__ConfigNOK::Debug__A__Ac__ConfigNOK exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__ConfigNOK::Region1::Debug__A__Ac__ConfigNOK",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__ConfigNOK__Debug__A__En__ConfigNOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__ConfigNOK::Debug__A__En__ConfigNOK exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__ConfigNOK::Region1::Debug__A__En__ConfigNOK",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__ConfigNOK__Debug__B__Ac__ConfigNOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__ConfigNOK::Debug__B__Ac__ConfigNOK exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__ConfigNOK::Region1::Debug__B__Ac__ConfigNOK",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__ConfigNOK__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__Init__ReadConfig__8__Debug__A__Ac__Init__ReadConfig__8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__Init__ReadConfig__8::Debug__A__Ac__Init__ReadConfig__8 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__Init__ReadConfig__8::Region1::Debug__A__Ac__Init__ReadConfig__8",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__Init__ReadConfig__8__Debug__A__En__Init__ReadConfig__8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__Init__ReadConfig__8::Debug__A__En__Init__ReadConfig__8 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__Init__ReadConfig__8::Region1::Debug__A__En__Init__ReadConfig__8",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__Init__ReadConfig__8__Debug__B__Ac__Init__ReadConfig__8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__Init__ReadConfig__8::Debug__B__Ac__Init__ReadConfig__8 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__Init__ReadConfig__8::Region1::Debug__B__Ac__Init__ReadConfig__8",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__Init__ReadConfig__8__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__MasterAnnouncment__Debug__A__Ac__MasterAnnouncment( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__MasterAnnouncment::Debug__A__Ac__MasterAnnouncment exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__MasterAnnouncment::Region1::Debug__A__Ac__MasterAnnouncment",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__MasterAnnouncment__Debug__A__En__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__MasterAnnouncment::Debug__A__En__Running exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__MasterAnnouncment::Region1::Debug__A__En__Running",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__MasterAnnouncment__Debug__B__Ac__MasterAnnouncment( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__MasterAnnouncment::Debug__B__Ac__MasterAnnouncment exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__MasterAnnouncment::Region1::Debug__B__Ac__MasterAnnouncment",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__MasterAnnouncment__Debug__B__Ex__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__MasterAnnouncment::Debug__B__Ex__Running exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__MasterAnnouncment::Region1::Debug__B__Ex__Running",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__MasterAnnouncment__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__QueryConfig__Debug__A__Ac__QueryConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__QueryConfig::Debug__A__Ac__QueryConfig exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__QueryConfig::Region1::Debug__A__Ac__QueryConfig",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__QueryConfig__Debug__A__En__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__QueryConfig::Debug__A__En__Running exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__QueryConfig::Region1::Debug__A__En__Running",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__QueryConfig__Debug__B__Ac__QueryConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__QueryConfig::Debug__B__Ac__QueryConfig exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__QueryConfig::Region1::Debug__B__Ac__QueryConfig",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__QueryConfig__Debug__B__Ex__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__QueryConfig::Debug__B__Ex__Running exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__QueryConfig::Region1::Debug__B__Ex__Running",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__QueryConfig__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__RetryConfig__Debug__A__Ac__RetryConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__RetryConfig::Debug__A__Ac__RetryConfig exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__RetryConfig::Region1::Debug__A__Ac__RetryConfig",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__RetryConfig__Debug__A__En__ReadConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__RetryConfig::Debug__A__En__ReadConfig exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__RetryConfig::Region1::Debug__A__En__ReadConfig",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__RetryConfig__Debug__B__Ac__RetryConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__RetryConfig::Debug__B__Ac__RetryConfig exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__RetryConfig::Region1::Debug__B__Ac__RetryConfig",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__RetryConfig__Debug__B__Ex__ConfigFailure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__RetryConfig::Debug__B__Ex__ConfigFailure exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__RetryConfig::Region1::Debug__B__Ex__ConfigFailure",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__RetryConfig__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__Server1Failure__Debug__A__Ac__Server1Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__Server1Failure::Debug__A__Ac__Server1Failure exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__Server1Failure::Region1::Debug__A__Ac__Server1Failure",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__Server1Failure__Debug__A__En__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__Server1Failure::Debug__A__En__Running exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__Server1Failure::Region1::Debug__A__En__Running",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__Server1Failure__Debug__B__Ac__Server1Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__Server1Failure::Debug__B__Ac__Server1Failure exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__Server1Failure::Region1::Debug__B__Ac__Server1Failure",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__Server1Failure__Debug__B__Ex__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__Server1Failure::Debug__B__Ex__Running exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__Server1Failure::Region1::Debug__B__Ex__Running",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__Server1Failure__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__configLoaded__Debug__A__Ac__configLoaded( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__configLoaded::Debug__A__Ac__configLoaded exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__configLoaded::Region1::Debug__A__Ac__configLoaded",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__configLoaded__Debug__B__Ac__configLoaded( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__configLoaded::Debug__B__Ac__configLoaded exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__configLoaded::Region1::Debug__B__Ac__configLoaded",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__configLoaded__Debug__B__Ex__ReadConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__configLoaded::Debug__B__Ex__ReadConfig exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__configLoaded::Region1::Debug__B__Ex__ReadConfig",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__configLoaded__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__configOK__Debug__A__Ac__configOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__configOK::Debug__A__Ac__configOK exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__configOK::Region1::Debug__A__Ac__configOK",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__configOK__Debug__A__En__configOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__configOK::Debug__A__En__configOK exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__configOK::Region1::Debug__A__En__configOK",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__configOK__Debug__B__Ac__configOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__configOK::Debug__B__Ac__configOK exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__configOK::Region1::Debug__B__Ac__configOK",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__configOK__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__server2Failure__Debug__A__Ac__server2Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__server2Failure::Debug__A__Ac__server2Failure exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__server2Failure::Region1::Debug__A__Ac__server2Failure",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__server2Failure__Debug__A__En__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__server2Failure::Debug__A__En__Running exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__server2Failure::Region1::Debug__A__En__Running",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__server2Failure__Debug__B__Ac__server2Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__server2Failure::Debug__B__Ac__server2Failure exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__server2Failure::Region1::Debug__B__Ac__server2Failure",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__server2Failure__Debug__B__Ex__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__server2Failure::Debug__B__Ex__Running exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__server2Failure::Region1::Debug__B__Ex__Running",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__C__server2Failure__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_ENV::exitaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__InitState exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____ReadConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::ReadConfig exit  */
    if( not Debug__SRO.checkDebug("ReadConfig",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::ReadConfig",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Running( const UMLRTMessage * msg )
{
    #define umlrtparam_MasterName ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Running exit  */
    if( not Debug__SRO.checkDebug("Running",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Running",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_MasterName
}

void Capsule_ENV::transitionaction_____ConfigNOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__Path__ConfigNOK,ConfigFailure */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::ConfigNOK",(char *)"Debug__Path__ConfigNOK",(char *)"ConfigFailure",(char *)"");
    std::cout<<"ENV: The configuration is not OK, the transition configCheck-> ConfigFailure was taken\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__ConfigNOK__Debug__Ac__ConfigNOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__ConfigNOK transition Debug__C__ConfigNOK::Debug__B__Ac__ConfigNOK,Debug__C__ConfigNOK::Debug__A__Ac__ConfigNOK,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__ConfigNOK::Region1::Debug__Ac__ConfigNOK",(char *)"Debug__B__Ac__ConfigNOK",(char *)"Debug__A__Ac__ConfigNOK",(char *)"");
    std::cout<<"ENV: The configuration is not OK, the transition configCheck-> ConfigFailure was taken\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__ConfigNOK__Debug__En__ConfigFailure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__ConfigNOK transition Debug__C__ConfigNOK::Debug__A__Ac__ConfigNOK,Debug__C__ConfigNOK::Debug__A__En__ConfigNOK,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__ConfigNOK::Region1::Debug__En__ConfigFailure",(char *)"Debug__A__Ac__ConfigNOK",(char *)"Debug__A__En__ConfigNOK",(char *)"");
    std::cout<<"ENV: The system is in Failure State, try to reload the config after 10 second\n";
    FailureTimer.informIn(UMLRTTimespec(10,0),4);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__ConfigNOK__Debug__end__trans__ConfigNOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__ConfigNOK transition Debug__C__ConfigNOK::Debug__A__En__ConfigNOK,Debug__C__ConfigNOK::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__ConfigNOK::Region1::Debug__end__trans__ConfigNOK",(char *)"Debug__A__En__ConfigNOK",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__ConfigNOK__Debug__init__trans__ConfigNOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__ConfigNOK transition Debug__C__ConfigNOK::en,Debug__C__ConfigNOK::Debug__B__Ac__ConfigNOK */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__ConfigNOK::Region1::Debug__init__trans__ConfigNOK",(char *)"en",(char *)"Debug__B__Ac__ConfigNOK",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__Init__ReadConfig__8__Debug__Ac__Init__ReadConfig__8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__Init__ReadConfig__8 transition Debug__C__Init__ReadConfig__8::Debug__B__Ac__Init__ReadConfig__8,Debug__C__Init__ReadConfig__8::Debug__A__Ac__Init__ReadConfig__8,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__Init__ReadConfig__8::Region1::Debug__Ac__Init__ReadConfig__8",(char *)"Debug__B__Ac__Init__ReadConfig__8",(char *)"Debug__A__Ac__Init__ReadConfig__8",(char *)"");
    std::cout<<"ENV: Intialization\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__Init__ReadConfig__8__Debug__En__ReadConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__Init__ReadConfig__8 transition Debug__C__Init__ReadConfig__8::Debug__A__Ac__Init__ReadConfig__8,Debug__C__Init__ReadConfig__8::Debug__A__En__Init__ReadConfig__8,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__Init__ReadConfig__8::Region1::Debug__En__ReadConfig",(char *)"Debug__A__Ac__Init__ReadConfig__8",(char *)"Debug__A__En__Init__ReadConfig__8",(char *)"");
    std::cout<<"ENV: Reading the configuration \n";
    configTimer.informIn(UMLRTTimespec(3,0));
    config.loadConfig();
    std::cout<<"ENV: Reading the configuration was done\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__Init__ReadConfig__8__Debug__end__trans__Init__ReadConfig__8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__Init__ReadConfig__8 transition Debug__C__Init__ReadConfig__8::Debug__A__En__Init__ReadConfig__8,Debug__C__Init__ReadConfig__8::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__Init__ReadConfig__8::Region1::Debug__end__trans__Init__ReadConfig__8",(char *)"Debug__A__En__Init__ReadConfig__8",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__Init__ReadConfig__8__Debug__init__trans__Init__ReadConfig__8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__Init__ReadConfig__8 transition Debug__C__Init__ReadConfig__8::en,Debug__C__Init__ReadConfig__8::Debug__B__Ac__Init__ReadConfig__8 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__Init__ReadConfig__8::Region1::Debug__init__trans__Init__ReadConfig__8",(char *)"en",(char *)"Debug__B__Ac__Init__ReadConfig__8",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__MasterAnnouncment__Debug__AC__MasterAnnouncment( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #define umlrtparam_MasterName ( *(const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__MasterAnnouncment transition Debug__C__MasterAnnouncment::Debug__B__Ac__MasterAnnouncment,Debug__C__MasterAnnouncment::Debug__A__Ac__MasterAnnouncment,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__MasterAnnouncment::Region1::Debug__AC__MasterAnnouncment",(char *)"Debug__B__Ac__MasterAnnouncment",(char *)"Debug__A__Ac__MasterAnnouncment",(char *)"");
    std::cout<<this->getName()<<": Master Annoucment from "<< umlrtparam_MasterName<<"\n";
    if (strcmp((char *)umlrtparam_MasterName,"server1")==0)
    {
    config.MasterList[0]=true;
    if (AnnouncementServer1Id.isValid())
    AnnouncmentServer1.cancelTimer(AnnouncementServer1Id);
    AnnouncementServer1Id=AnnouncmentServer1.informEvery(UMLRTTimespec(AnnouncmentServerTimeout,0),4);
    }
    else if (strcmp((char *)umlrtparam_MasterName,"server2")==0)
    {
    config.MasterList[1]=true;
    if (AnnouncementServer2Id.isValid())
    AnnouncmentServer2.cancelTimer(AnnouncementServer2Id);
    AnnouncementServer2Id=AnnouncmentServer2.informEvery(UMLRTTimespec(AnnouncmentServerTimeout,0),4);
    }
    // the following code has been generated
    if ((config.RunningMode==1)&& (config.MasterList[0] ) && (config.MasterList[1]))
    std::cout<<this->getName()<<": Violation, there are 2 master in passive mode\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__MasterAnnouncment__Debug__En__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__MasterAnnouncment transition Debug__C__MasterAnnouncment::Debug__A__Ac__MasterAnnouncment,Debug__C__MasterAnnouncment::Debug__A__En__Running,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__MasterAnnouncment::Region1::Debug__En__Running",(char *)"Debug__A__Ac__MasterAnnouncment",(char *)"Debug__A__En__Running",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__MasterAnnouncment__Debug__Ex__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__MasterAnnouncment transition Debug__C__MasterAnnouncment::Debug__B__Ex__Running,Debug__C__MasterAnnouncment::Debug__B__Ac__MasterAnnouncment,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__MasterAnnouncment::Region1::Debug__Ex__Running",(char *)"Debug__B__Ex__Running",(char *)"Debug__B__Ac__MasterAnnouncment",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__MasterAnnouncment__Debug__end__trans__MasterAnnouncment( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__MasterAnnouncment transition Debug__C__MasterAnnouncment::Debug__A__En__Running,Debug__C__MasterAnnouncment::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__MasterAnnouncment::Region1::Debug__end__trans__MasterAnnouncment",(char *)"Debug__A__En__Running",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__MasterAnnouncment__Debug__init__trans__MasterAnnouncment( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__MasterAnnouncment transition Debug__C__MasterAnnouncment::en,Debug__C__MasterAnnouncment::Debug__B__Ex__Running */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__MasterAnnouncment::Region1::Debug__init__trans__MasterAnnouncment",(char *)"en",(char *)"Debug__B__Ex__Running",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__QueryConfig__Debug__AC__QueryConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__QueryConfig transition Debug__C__QueryConfig::Debug__B__Ac__QueryConfig,Debug__C__QueryConfig::Debug__A__Ac__QueryConfig,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__QueryConfig::Region1::Debug__AC__QueryConfig",(char *)"Debug__B__Ac__QueryConfig",(char *)"Debug__A__Ac__QueryConfig",(char *)"");
    std::cout<<"ENV: The Config request replied at index" << msg->sapIndex0_<< "\n";
    int tempid=msg->sapIndex0_;
    ConfigComm.ReplyConfig(config).sendAt(tempid);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__QueryConfig__Debug__En__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__QueryConfig transition Debug__C__QueryConfig::Debug__A__Ac__QueryConfig,Debug__C__QueryConfig::Debug__A__En__Running,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__QueryConfig::Region1::Debug__En__Running",(char *)"Debug__A__Ac__QueryConfig",(char *)"Debug__A__En__Running",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__QueryConfig__Debug__Ex__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__QueryConfig transition Debug__C__QueryConfig::Debug__B__Ex__Running,Debug__C__QueryConfig::Debug__B__Ac__QueryConfig,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__QueryConfig::Region1::Debug__Ex__Running",(char *)"Debug__B__Ex__Running",(char *)"Debug__B__Ac__QueryConfig",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__QueryConfig__Debug__end__trans__QueryConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__QueryConfig transition Debug__C__QueryConfig::Debug__A__En__Running,Debug__C__QueryConfig::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__QueryConfig::Region1::Debug__end__trans__QueryConfig",(char *)"Debug__A__En__Running",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__QueryConfig__Debug__init__trans__QueryConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__QueryConfig transition Debug__C__QueryConfig::en,Debug__C__QueryConfig::Debug__B__Ex__Running */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__QueryConfig::Region1::Debug__init__trans__QueryConfig",(char *)"en",(char *)"Debug__B__Ex__Running",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__RetryConfig__Debug__AC__RetryConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__RetryConfig transition Debug__C__RetryConfig::Debug__B__Ac__RetryConfig,Debug__C__RetryConfig::Debug__A__Ac__RetryConfig,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__RetryConfig::Region1::Debug__AC__RetryConfig",(char *)"Debug__B__Ac__RetryConfig",(char *)"Debug__A__Ac__RetryConfig",(char *)"");
    std::cout<<"ENV: retrying configuation, The transtion Failure -> readConfig was taken \n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__RetryConfig__Debug__En__ReadConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__RetryConfig transition Debug__C__RetryConfig::Debug__A__Ac__RetryConfig,Debug__C__RetryConfig::Debug__A__En__ReadConfig,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__RetryConfig::Region1::Debug__En__ReadConfig",(char *)"Debug__A__Ac__RetryConfig",(char *)"Debug__A__En__ReadConfig",(char *)"");
    std::cout<<"ENV: Reading the configuration \n";
    configTimer.informIn(UMLRTTimespec(3,0));
    config.loadConfig();
    std::cout<<"ENV: Reading the configuration was done\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__RetryConfig__Debug__Ex__ConfigFailure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__RetryConfig transition Debug__C__RetryConfig::Debug__B__Ex__ConfigFailure,Debug__C__RetryConfig::Debug__B__Ac__RetryConfig,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__RetryConfig::Region1::Debug__Ex__ConfigFailure",(char *)"Debug__B__Ex__ConfigFailure",(char *)"Debug__B__Ac__RetryConfig",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__RetryConfig__Debug__end__trans__RetryConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__RetryConfig transition Debug__C__RetryConfig::Debug__A__En__ReadConfig,Debug__C__RetryConfig::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__RetryConfig::Region1::Debug__end__trans__RetryConfig",(char *)"Debug__A__En__ReadConfig",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__RetryConfig__Debug__init__trans__RetryConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__RetryConfig transition Debug__C__RetryConfig::en,Debug__C__RetryConfig::Debug__B__Ex__ConfigFailure */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__RetryConfig::Region1::Debug__init__trans__RetryConfig",(char *)"en",(char *)"Debug__B__Ex__ConfigFailure",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__Server1Failure__Debug__AC__Server1Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__Server1Failure transition Debug__C__Server1Failure::Debug__B__Ac__Server1Failure,Debug__C__Server1Failure::Debug__A__Ac__Server1Failure,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__Server1Failure::Region1::Debug__AC__Server1Failure",(char *)"Debug__B__Ac__Server1Failure",(char *)"Debug__A__Ac__Server1Failure",(char *)"");
    std::cout<<"ENV: No announcment from server1, remove server1 from masters list\n";
    config.MasterList[0]=false;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__Server1Failure__Debug__En__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__Server1Failure transition Debug__C__Server1Failure::Debug__A__Ac__Server1Failure,Debug__C__Server1Failure::Debug__A__En__Running,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__Server1Failure::Region1::Debug__En__Running",(char *)"Debug__A__Ac__Server1Failure",(char *)"Debug__A__En__Running",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__Server1Failure__Debug__Ex__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__Server1Failure transition Debug__C__Server1Failure::Debug__B__Ex__Running,Debug__C__Server1Failure::Debug__B__Ac__Server1Failure,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__Server1Failure::Region1::Debug__Ex__Running",(char *)"Debug__B__Ex__Running",(char *)"Debug__B__Ac__Server1Failure",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__Server1Failure__Debug__end__trans__Server1Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__Server1Failure transition Debug__C__Server1Failure::Debug__A__En__Running,Debug__C__Server1Failure::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__Server1Failure::Region1::Debug__end__trans__Server1Failure",(char *)"Debug__A__En__Running",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__Server1Failure__Debug__init__trans__Server1Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__Server1Failure transition Debug__C__Server1Failure::en,Debug__C__Server1Failure::Debug__B__Ex__Running */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__Server1Failure::Region1::Debug__init__trans__Server1Failure",(char *)"en",(char *)"Debug__B__Ex__Running",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__configLoaded__Debug__AC__configLoaded( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__configLoaded transition Debug__C__configLoaded::Debug__B__Ac__configLoaded,Debug__C__configLoaded::Debug__A__Ac__configLoaded,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__configLoaded::Region1::Debug__AC__configLoaded",(char *)"Debug__B__Ac__configLoaded",(char *)"Debug__A__Ac__configLoaded",(char *)"");
    std::cout<<"ENV: The transition from ReadConfig -> Config was taken\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__configLoaded__Debug__Ex__ReadConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__configLoaded transition Debug__C__configLoaded::Debug__B__Ex__ReadConfig,Debug__C__configLoaded::Debug__B__Ac__configLoaded,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__configLoaded::Region1::Debug__Ex__ReadConfig",(char *)"Debug__B__Ex__ReadConfig",(char *)"Debug__B__Ac__configLoaded",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__configLoaded__Debug__end__trans__configLoaded( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__configLoaded transition Debug__C__configLoaded::Debug__A__Ac__configLoaded,Debug__C__configLoaded::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__configLoaded::Region1::Debug__end__trans__configLoaded",(char *)"Debug__A__Ac__configLoaded",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__configOK__Debug__Ac__configOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__configOK transition Debug__C__configOK::Debug__B__Ac__configOK,Debug__C__configOK::Debug__A__Ac__configOK,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__configOK::Region1::Debug__Ac__configOK",(char *)"Debug__B__Ac__configOK",(char *)"Debug__A__Ac__configOK",(char *)"");
    std::cout<<"ENV: The configuration is OK, the transition config-> Running was taken, sending signal to servers and clients \n";
    ConfigComm.StartUp(this->config).send();
    std::cout<<"ENV: ENV is in  Running State\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__configOK__Debug__En__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__configOK transition Debug__C__configOK::Debug__A__Ac__configOK,Debug__C__configOK::Debug__A__En__configOK,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__configOK::Region1::Debug__En__Running",(char *)"Debug__A__Ac__configOK",(char *)"Debug__A__En__configOK",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__configOK__Debug__end__trans__configOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__configOK transition Debug__C__configOK::Debug__A__En__configOK,Debug__C__configOK::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__configOK::Region1::Debug__end__trans__configOK",(char *)"Debug__A__En__configOK",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__configOK__Debug__init__trans__configOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__configOK transition Debug__C__configOK::en,Debug__C__configOK::Debug__B__Ac__configOK */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__configOK::Region1::Debug__init__trans__configOK",(char *)"en",(char *)"Debug__B__Ac__configOK",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__server2Failure__Debug__AC__server2Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__server2Failure transition Debug__C__server2Failure::Debug__B__Ac__server2Failure,Debug__C__server2Failure::Debug__A__Ac__server2Failure,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__server2Failure::Region1::Debug__AC__server2Failure",(char *)"Debug__B__Ac__server2Failure",(char *)"Debug__A__Ac__server2Failure",(char *)"");
    std::cout<<"ENV: No announcment from server2, remove Server2 from masters list\n";
    config.MasterList[1]=false;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__server2Failure__Debug__En__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__server2Failure transition Debug__C__server2Failure::Debug__A__Ac__server2Failure,Debug__C__server2Failure::Debug__A__En__Running,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__server2Failure::Region1::Debug__En__Running",(char *)"Debug__A__Ac__server2Failure",(char *)"Debug__A__En__Running",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__server2Failure__Debug__Ex__Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__server2Failure transition Debug__C__server2Failure::Debug__B__Ex__Running,Debug__C__server2Failure::Debug__B__Ac__server2Failure,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__server2Failure::Region1::Debug__Ex__Running",(char *)"Debug__B__Ex__Running",(char *)"Debug__B__Ac__server2Failure",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__server2Failure__Debug__end__trans__server2Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__server2Failure transition Debug__C__server2Failure::Debug__A__En__Running,Debug__C__server2Failure::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__server2Failure::Region1::Debug__end__trans__server2Failure",(char *)"Debug__A__En__Running",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__C__server2Failure__Debug__init__trans__server2Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV::Debug__C__server2Failure transition Debug__C__server2Failure::en,Debug__C__server2Failure::Debug__B__Ex__Running */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__C__server2Failure::Region1::Debug__init__trans__server2Failure",(char *)"en",(char *)"Debug__B__Ex__Running",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__ConfigNOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Config,Debug__Path__ConfigNOK */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__ConfigNOK",(char *)"Config",(char *)"Debug__Path__ConfigNOK",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__ConfigNOK__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__C__ConfigNOK::ex,ConfigFailure */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__ConfigNOK__E",(char *)"ex",(char *)"ConfigFailure",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__ConfigNOK__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__Path__ConfigNOK,Debug__C__ConfigNOK::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__ConfigNOK__S",(char *)"Debug__Path__ConfigNOK",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__ConfigNOK__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__C__ConfigNOK::new_exitpoint_7,Debug__C__ConfigNOK */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__ConfigNOK__dbg",(char *)"Debug__C__ConfigNOK",(char *)"Debug__C__ConfigNOK",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__InitDebug( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Init,Debug__InitState */
    std::cout<<this->getName()<<" : is Starting\n";
    std::string tempS;
    std::cout<<"Enter 1 for running in debug mode, any other key for normal model\n";
    std::cin>> tempS;
    if (tempS=="1")
    this->Debug__SRO.setExecMode(Stepping);
    else
    this->Debug__SRO.setExecMode((ExecMode)2);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__Init__ReadConfig__8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__InitState,Debug__Path__Init__ReadConfig__8,null:extComm */
    if (this->Debug__SRO.getExecMode()==Stepping){
    Debug__SRO.addTransitionsFromState("RunAsSlave","NokeepAlive","TryBeMaster","timeout","Timing");
    Debug__SRO.addTransitionsFromState("RunAsMaster","KeepAlive","RunAsMaster","timeout","Timing");
    Debug__SRO.addTransitionsFromState("WaitingForReply","ServiceResult","ProcessResponse","Reply","Services");
    Debug__SRO.addTransitionsFromState("Slave","backtoslave","RunAsSlave","","");
    Debug__SRO.addTransitionsFromState("RunAsMaster","ServerFaliure","Failure","timeout","Timing");
    Debug__SRO.addTransitionsFromState("BeMaster","BeingMaster","RunAsMaster","","");
    Debug__SRO.addTransitionsFromState("Running","MasterAnnouncment","Running","IAMMaster","Config");
    Debug__SRO.addTransitionsFromState("Init","","StandBy","","");
    Debug__SRO.addTransitionsFromState("checkConfig","NoMaster","Retry","","");
    Debug__SRO.addTransitionsFromState("init","","WaitForEcho","","");
    Debug__SRO.addTransitionsFromState("Ready","reqFlowInit","getMasterName","timeout","Timing");
    Debug__SRO.addTransitionsFromState("Running","server2Failure","Running","IAmAlive","Timing");
    Debug__SRO.addTransitionsFromState("Running","Server1Failure","Running","IAmAlive","Timing");
    Debug__SRO.addTransitionsFromState("Initial1","","RunAsSlave","","");
    Debug__SRO.addTransitionsFromState("ReadConfig","configLoaded","Config","timeout","Timing");
    Debug__SRO.addTransitionsFromState("CheckConfig","BeSlave","Backup","","");
    Debug__SRO.addTransitionsFromState("WaitingForReply","NoResponseFromServer","Ready","timeout","Timing");
    Debug__SRO.addTransitionsFromState("Retry","Retry","getMasterName","timeout","Timing");
    Debug__SRO.addTransitionsFromState("Choice1","ActiveMode","BeMaster","","");
    Debug__SRO.addTransitionsFromState("getMasterName","","checkConfig","ReplyConfig","Config");
    Debug__SRO.addTransitionsFromState("StandBY","StarupTransition","Ready","StartUp","Config");
    Debug__SRO.addTransitionsFromState("ExitPoint1","","BeMaster","","");
    Debug__SRO.addTransitionsFromState("RunAsSlave","KeepAliveMsg","RunAsSlave","IAmAlive","FailOver");
    Debug__SRO.addTransitionsFromState("StandBy","","CheckConfig","StartUp","Config");
    Debug__SRO.addTransitionsFromState("Running","QueryConfig","Running","QueryConfig","Config");
    Debug__SRO.addTransitionsFromState("Config","ConfigNOK","ConfigFailure","","");
    Debug__SRO.addTransitionsFromState("TryBeMaster","ReplyConfig","Choice2","ReplyConfig","Config");
    Debug__SRO.addTransitionsFromState("Choice1","PassiveMode","Backup","","");
    Debug__SRO.addTransitionsFromState("init","","StandBY","","");
    Debug__SRO.addTransitionsFromState("CheckConfig","initTimer","RunAsMaster","","");
    Debug__SRO.addTransitionsFromState("Failure","purgeotherMessage","Failure","*","Services");
    Debug__SRO.addTransitionsFromState("Failure","purgeotherMessage","Failure","*","FailOver");
    Debug__SRO.addTransitionsFromState("RunAsMaster","MasterAnnounce","RunAsMaster","timeout","Timing");
    Debug__SRO.addTransitionsFromState("Failure","Recover","Choice1","timeout","Timing");
    Debug__SRO.addTransitionsFromState("ConfigFailure","RetryConfig","ReadConfig","timeout","Timing");
    Debug__SRO.addTransitionsFromState("Choice2","CheckNoMaster","ExitPoint1","","");
    Debug__SRO.addTransitionsFromState("checkConfig","reqService","WaitingForReply","","");
    Debug__SRO.addTransitionsFromState("Config","configOK","Running","","");
    Debug__SRO.addTransitionsFromState("WaitForEcho","DoEcho","WaitForEcho","Echo","Echo");
    Debug__SRO.addTransitionsFromState("Init","","ReadConfig","","");
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

void Capsule_ENV::transitionaction_____Debug__Init__ReadConfig__8__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__C__Init__ReadConfig__8::ex,ReadConfig */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__Init__ReadConfig__8__E",(char *)"ex",(char *)"ReadConfig",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__Init__ReadConfig__8__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__Path__Init__ReadConfig__8,Debug__C__Init__ReadConfig__8::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__Init__ReadConfig__8__S",(char *)"Debug__Path__Init__ReadConfig__8",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__Init__ReadConfig__8__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__C__Init__ReadConfig__8::new_exitpoint_2,Debug__C__Init__ReadConfig__8 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__Init__ReadConfig__8__dbg",(char *)"Debug__C__Init__ReadConfig__8",(char *)"Debug__C__Init__ReadConfig__8",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__MasterAnnouncment( const UMLRTMessage * msg )
{
    #define umlrtparam_MasterName ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Running,Debug__Path__MasterAnnouncment,IAMMaster:ConfigComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__MasterAnnouncment",(char *)"Running",(char *)"Debug__Path__MasterAnnouncment",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_MasterName
}

void Capsule_ENV::transitionaction_____Debug__MasterAnnouncment__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__C__MasterAnnouncment::ex,Running */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__MasterAnnouncment__E",(char *)"ex",(char *)"Running",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__MasterAnnouncment__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__Path__MasterAnnouncment,Debug__C__MasterAnnouncment::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__MasterAnnouncment__S",(char *)"Debug__Path__MasterAnnouncment",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__MasterAnnouncment__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__C__MasterAnnouncment::new_exitpoint_1,Debug__C__MasterAnnouncment */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__MasterAnnouncment__dbg",(char *)"Debug__C__MasterAnnouncment",(char *)"Debug__C__MasterAnnouncment",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__QueryConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Running,Debug__Path__QueryConfig,QueryConfig:ConfigComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__QueryConfig",(char *)"Running",(char *)"Debug__Path__QueryConfig",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__QueryConfig__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__C__QueryConfig::ex,Running */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__QueryConfig__E",(char *)"ex",(char *)"Running",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__QueryConfig__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__Path__QueryConfig,Debug__C__QueryConfig::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__QueryConfig__S",(char *)"Debug__Path__QueryConfig",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__QueryConfig__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__C__QueryConfig::new_exitpoint_8,Debug__C__QueryConfig */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__QueryConfig__dbg",(char *)"Debug__C__QueryConfig",(char *)"Debug__C__QueryConfig",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__RetryConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition ConfigFailure,Debug__Path__RetryConfig,timeout:FailureTimer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__RetryConfig",(char *)"ConfigFailure",(char *)"Debug__Path__RetryConfig",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__RetryConfig__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__C__RetryConfig::ex,ReadConfig */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__RetryConfig__E",(char *)"ex",(char *)"ReadConfig",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__RetryConfig__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__Path__RetryConfig,Debug__C__RetryConfig::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__RetryConfig__S",(char *)"Debug__Path__RetryConfig",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__RetryConfig__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__C__RetryConfig::new_exitpoint_3,Debug__C__RetryConfig */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__RetryConfig__dbg",(char *)"Debug__C__RetryConfig",(char *)"Debug__C__RetryConfig",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__Server1Failure( const UMLRTMessage * msg )
{
    #define umlrtparam_ServerName ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Running,Debug__Path__Server1Failure,IAmAlive:AnnouncmentServer1 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__Server1Failure",(char *)"Running",(char *)"Debug__Path__Server1Failure",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_ServerName
}

void Capsule_ENV::transitionaction_____Debug__Server1Failure__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__C__Server1Failure::ex,Running */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__Server1Failure__E",(char *)"ex",(char *)"Running",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__Server1Failure__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__Path__Server1Failure,Debug__C__Server1Failure::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__Server1Failure__S",(char *)"Debug__Path__Server1Failure",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__Server1Failure__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__C__Server1Failure::new_exitpoint_9,Debug__C__Server1Failure */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__Server1Failure__dbg",(char *)"Debug__C__Server1Failure",(char *)"Debug__C__Server1Failure",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__configLoaded( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition ReadConfig,Debug__Path__configLoaded,timeout:configTimer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__configLoaded",(char *)"ReadConfig",(char *)"Debug__Path__configLoaded",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__configLoaded__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__C__configLoaded::ex,Config */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__configLoaded__E",(char *)"ex",(char *)"Config",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__configLoaded__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__Path__configLoaded,Debug__C__configLoaded::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__configLoaded__S",(char *)"Debug__Path__configLoaded",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__configLoaded__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__C__configLoaded::new_exitpoint_6,Debug__C__configLoaded */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__configLoaded__dbg",(char *)"Debug__C__configLoaded",(char *)"Debug__C__configLoaded",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__configOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Config,Debug__Path__configOK */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__configOK",(char *)"Config",(char *)"Debug__Path__configOK",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__configOK__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__C__configOK::ex,Running */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__configOK__E",(char *)"ex",(char *)"Running",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__configOK__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__Path__configOK,Debug__C__configOK::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__configOK__S",(char *)"Debug__Path__configOK",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__configOK__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__C__configOK::new_exitpoint_5,Debug__C__configOK */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__configOK__dbg",(char *)"Debug__C__configOK",(char *)"Debug__C__configOK",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__server2Failure( const UMLRTMessage * msg )
{
    #define umlrtparam_ServerName ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Running,Debug__Path__server2Failure,IAmAlive:AnnouncmentServer2 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__server2Failure",(char *)"Running",(char *)"Debug__Path__server2Failure",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_ServerName
}

void Capsule_ENV::transitionaction_____Debug__server2Failure__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__C__server2Failure::ex,Running */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__server2Failure__E",(char *)"ex",(char *)"Running",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__server2Failure__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__Path__server2Failure,Debug__C__server2Failure::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__server2Failure__S",(char *)"Debug__Path__server2Failure",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Debug__server2Failure__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__C__server2Failure::new_exitpoint_4,Debug__C__server2Failure */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Debug__server2Failure__dbg",(char *)"Debug__C__server2Failure",(char *)"Debug__C__server2Failure",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Init__ReadConfig__8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__Path__Init__ReadConfig__8,ReadConfig */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Init__ReadConfig__8",(char *)"Debug__Path__Init__ReadConfig__8",(char *)"ReadConfig",(char *)"");
    std::cout<<"ENV: Intialization\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____MasterAnnouncment( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #define umlrtparam_MasterName ( *(const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__Path__MasterAnnouncment,Running */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::MasterAnnouncment",(char *)"Debug__Path__MasterAnnouncment",(char *)"Running",(char *)"");
    std::cout<<this->getName()<<": Master Annoucment from "<< umlrtparam_MasterName<<"\n";
    if (strcmp((char *)umlrtparam_MasterName,"server1")==0)
    {
    config.MasterList[0]=true;
    if (AnnouncementServer1Id.isValid())
    AnnouncmentServer1.cancelTimer(AnnouncementServer1Id);
    AnnouncementServer1Id=AnnouncmentServer1.informEvery(UMLRTTimespec(AnnouncmentServerTimeout,0),4);
    }
    else if (strcmp((char *)umlrtparam_MasterName,"server2")==0)
    {
    config.MasterList[1]=true;
    if (AnnouncementServer2Id.isValid())
    AnnouncmentServer2.cancelTimer(AnnouncementServer2Id);
    AnnouncementServer2Id=AnnouncmentServer2.informEvery(UMLRTTimespec(AnnouncmentServerTimeout,0),4);
    }
    // the following code has been generated
    if ((config.RunningMode==1)&& (config.MasterList[0] ) && (config.MasterList[1]))
    std::cout<<this->getName()<<": Violation, there are 2 master in passive mode\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____QueryConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__Path__QueryConfig,Running */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::QueryConfig",(char *)"Debug__Path__QueryConfig",(char *)"Running",(char *)"");
    std::cout<<"ENV: The Config request replied at index" << msg->sapIndex0_<< "\n";
    int tempid=msg->sapIndex0_;
    ConfigComm.ReplyConfig(config).sendAt(tempid);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____RetryConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__Path__RetryConfig,ReadConfig */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::RetryConfig",(char *)"Debug__Path__RetryConfig",(char *)"ReadConfig",(char *)"");
    std::cout<<"ENV: retrying configuation, The transtion Failure -> readConfig was taken \n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Server1Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__Path__Server1Failure,Running */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::Server1Failure",(char *)"Debug__Path__Server1Failure",(char *)"Running",(char *)"");
    std::cout<<"ENV: No announcment from server1, remove server1 from masters list\n";
    config.MasterList[0]=false;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____configLoaded( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__Path__configLoaded,Config */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::configLoaded",(char *)"Debug__Path__configLoaded",(char *)"Config",(char *)"");
    std::cout<<"ENV: The transition from ReadConfig -> Config was taken\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____configOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__Path__configOK,Running */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::configOK",(char *)"Debug__Path__configOK",(char *)"Running",(char *)"");
    std::cout<<"ENV: The configuration is OK, the transition config-> Running was taken, sending signal to servers and clients \n";
    ConfigComm.StartUp(this->config).send();
    std::cout<<"ENV: ENV is in  Running State\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____server2Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV transition Debug__Path__server2Failure,Running */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::ENV::ENV::StateMachine1::Region1::server2Failure",(char *)"Debug__Path__server2Failure",(char *)"Running",(char *)"");
    std::cout<<"ENV: No announcment from server2, remove Server2 from masters list\n";
    config.MasterList[1]=false;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_ENV::action_____Debug__ConfigNOK__S__Debug__GuardConfigNOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV guard Debug__Path__ConfigNOK,Debug__C__ConfigNOK::en */
    return Debug__SRO.checkDebug("Config","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_ENV::action_____Debug__Init__ReadConfig__8__S__Debug__GuardInit__ReadConfig__8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV guard Debug__Path__Init__ReadConfig__8,Debug__C__Init__ReadConfig__8::en */
    return Debug__SRO.checkDebug("Init","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_ENV::action_____Debug__MasterAnnouncment__S__Debug__GuardMasterAnnouncment( const UMLRTMessage * msg )
{
    #define umlrtparam_MasterName ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV guard Debug__Path__MasterAnnouncment,Debug__C__MasterAnnouncment::en */
    return Debug__SRO.checkDebug("Running",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_MasterName
}

bool Capsule_ENV::action_____Debug__QueryConfig__S__Debug__GuardQueryConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV guard Debug__Path__QueryConfig,Debug__C__QueryConfig::en */
    return Debug__SRO.checkDebug("Running",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_ENV::action_____Debug__RetryConfig__S__Debug__GuardRetryConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV guard Debug__Path__RetryConfig,Debug__C__RetryConfig::en */
    return Debug__SRO.checkDebug("ConfigFailure",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_ENV::action_____Debug__Server1Failure__S__Debug__GuardServer1Failure( const UMLRTMessage * msg )
{
    #define umlrtparam_ServerName ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV guard Debug__Path__Server1Failure,Debug__C__Server1Failure::en */
    return Debug__SRO.checkDebug("Running",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_ServerName
}

bool Capsule_ENV::action_____Debug__configLoaded__S__Debug__GuardconfigLoaded( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV guard Debug__Path__configLoaded,Debug__C__configLoaded::en */
    return Debug__SRO.checkDebug("ReadConfig",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_ENV::action_____Debug__configOK__S__Debug__GuardconfigOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV guard Debug__Path__configOK,Debug__C__configOK::en */
    return Debug__SRO.checkDebug("Config","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_ENV::action_____Debug__configOK__checkConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV guard Config,Debug__Path__configOK */
    return config.ConfigOK;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_ENV::action_____Debug__server2Failure__S__Debug__Guardserver2Failure( const UMLRTMessage * msg )
{
    #define umlrtparam_ServerName ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::ENV::ENV guard Debug__Path__server2Failure,Debug__C__server2Failure::en */
    return Debug__SRO.checkDebug("Running",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_ServerName
}

void Capsule_ENV::actionchain_____ConfigNOK( const UMLRTMessage * msg )
{
    transitionaction_____ConfigNOK( msg );
    entryaction_____ConfigFailure( msg );
}

void Capsule_ENV::actionchain_____Debug__C__ConfigNOK__Debug__Ac__ConfigNOK( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ConfigNOK__Debug__B__Ac__ConfigNOK( msg );
    transitionaction_____Debug__C__ConfigNOK__Debug__Ac__ConfigNOK( msg );
    entryaction_____Debug__C__ConfigNOK__Debug__A__Ac__ConfigNOK( msg );
}

void Capsule_ENV::actionchain_____Debug__C__ConfigNOK__Debug__En__ConfigFailure( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ConfigNOK__Debug__A__Ac__ConfigNOK( msg );
    transitionaction_____Debug__C__ConfigNOK__Debug__En__ConfigFailure( msg );
    entryaction_____Debug__C__ConfigNOK__Debug__A__En__ConfigNOK( msg );
}

void Capsule_ENV::actionchain_____Debug__C__ConfigNOK__Debug__end__trans__ConfigNOK( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ConfigNOK__Debug__A__En__ConfigNOK( msg );
    transitionaction_____Debug__C__ConfigNOK__Debug__end__trans__ConfigNOK( msg );
    save_history( Debug__C__ConfigNOK, Debug__C__ConfigNOK__Debug__A__En__ConfigNOK );
}

void Capsule_ENV::actionchain_____Debug__C__ConfigNOK__Debug__init__trans__ConfigNOK( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__ConfigNOK__Debug__init__trans__ConfigNOK( msg );
    entryaction_____Debug__C__ConfigNOK__Debug__B__Ac__ConfigNOK( msg );
}

void Capsule_ENV::actionchain_____Debug__C__ConfigNOK__new_transition_55( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ConfigNOK__Debug__B__Ac__ConfigNOK( msg );
}

void Capsule_ENV::actionchain_____Debug__C__ConfigNOK__new_transition_56( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ConfigNOK__Debug__A__Ac__ConfigNOK( msg );
}

void Capsule_ENV::actionchain_____Debug__C__ConfigNOK__new_transition_57( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ConfigNOK__Debug__A__En__ConfigNOK( msg );
}

void Capsule_ENV::actionchain_____Debug__C__ConfigNOK__new_transition_58_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ConfigNOK__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__C__ConfigNOK__new_transition_59( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ConfigNOK__Debug__B__Ac__ConfigNOK( msg );
    save_history( Debug__C__ConfigNOK, Debug__C__ConfigNOK__Debug__B__Ac__ConfigNOK );
}

void Capsule_ENV::actionchain_____Debug__C__ConfigNOK__new_transition_60( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ConfigNOK__Debug__A__Ac__ConfigNOK( msg );
    save_history( Debug__C__ConfigNOK, Debug__C__ConfigNOK__Debug__A__Ac__ConfigNOK );
}

void Capsule_ENV::actionchain_____Debug__C__ConfigNOK__new_transition_61( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ConfigNOK__Debug__A__En__ConfigNOK( msg );
    save_history( Debug__C__ConfigNOK, Debug__C__ConfigNOK__Debug__A__En__ConfigNOK );
}

void Capsule_ENV::actionchain_____Debug__C__ConfigNOK__new_transition_62( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ConfigNOK__boundary( msg );
    save_history( Debug__C__ConfigNOK, Debug__C__ConfigNOK__boundary );
}

void Capsule_ENV::actionchain_____Debug__C__Init__ReadConfig__8__Debug__Ac__Init__ReadConfig__8( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Init__ReadConfig__8__Debug__B__Ac__Init__ReadConfig__8( msg );
    transitionaction_____Debug__C__Init__ReadConfig__8__Debug__Ac__Init__ReadConfig__8( msg );
    entryaction_____Debug__C__Init__ReadConfig__8__Debug__A__Ac__Init__ReadConfig__8( msg );
}

void Capsule_ENV::actionchain_____Debug__C__Init__ReadConfig__8__Debug__En__ReadConfig( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Init__ReadConfig__8__Debug__A__Ac__Init__ReadConfig__8( msg );
    transitionaction_____Debug__C__Init__ReadConfig__8__Debug__En__ReadConfig( msg );
    entryaction_____Debug__C__Init__ReadConfig__8__Debug__A__En__Init__ReadConfig__8( msg );
}

void Capsule_ENV::actionchain_____Debug__C__Init__ReadConfig__8__Debug__end__trans__Init__ReadConfig__8( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Init__ReadConfig__8__Debug__A__En__Init__ReadConfig__8( msg );
    transitionaction_____Debug__C__Init__ReadConfig__8__Debug__end__trans__Init__ReadConfig__8( msg );
    save_history( Debug__C__Init__ReadConfig__8, Debug__C__Init__ReadConfig__8__Debug__A__En__Init__ReadConfig__8 );
}

void Capsule_ENV::actionchain_____Debug__C__Init__ReadConfig__8__Debug__init__trans__Init__ReadConfig__8( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__Init__ReadConfig__8__Debug__init__trans__Init__ReadConfig__8( msg );
    entryaction_____Debug__C__Init__ReadConfig__8__Debug__B__Ac__Init__ReadConfig__8( msg );
}

void Capsule_ENV::actionchain_____Debug__C__Init__ReadConfig__8__new_transition_11( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Init__ReadConfig__8__Debug__B__Ac__Init__ReadConfig__8( msg );
}

void Capsule_ENV::actionchain_____Debug__C__Init__ReadConfig__8__new_transition_12( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Init__ReadConfig__8__Debug__A__Ac__Init__ReadConfig__8( msg );
}

void Capsule_ENV::actionchain_____Debug__C__Init__ReadConfig__8__new_transition_13( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Init__ReadConfig__8__Debug__A__En__Init__ReadConfig__8( msg );
}

void Capsule_ENV::actionchain_____Debug__C__Init__ReadConfig__8__new_transition_14_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Init__ReadConfig__8__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__C__Init__ReadConfig__8__new_transition_15( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Init__ReadConfig__8__Debug__B__Ac__Init__ReadConfig__8( msg );
    save_history( Debug__C__Init__ReadConfig__8, Debug__C__Init__ReadConfig__8__Debug__B__Ac__Init__ReadConfig__8 );
}

void Capsule_ENV::actionchain_____Debug__C__Init__ReadConfig__8__new_transition_16( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Init__ReadConfig__8__Debug__A__Ac__Init__ReadConfig__8( msg );
    save_history( Debug__C__Init__ReadConfig__8, Debug__C__Init__ReadConfig__8__Debug__A__Ac__Init__ReadConfig__8 );
}

void Capsule_ENV::actionchain_____Debug__C__Init__ReadConfig__8__new_transition_17( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Init__ReadConfig__8__Debug__A__En__Init__ReadConfig__8( msg );
    save_history( Debug__C__Init__ReadConfig__8, Debug__C__Init__ReadConfig__8__Debug__A__En__Init__ReadConfig__8 );
}

void Capsule_ENV::actionchain_____Debug__C__Init__ReadConfig__8__new_transition_18( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Init__ReadConfig__8__boundary( msg );
    save_history( Debug__C__Init__ReadConfig__8, Debug__C__Init__ReadConfig__8__boundary );
}

void Capsule_ENV::actionchain_____Debug__C__MasterAnnouncment__Debug__AC__MasterAnnouncment( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__MasterAnnouncment__Debug__B__Ac__MasterAnnouncment( msg );
    transitionaction_____Debug__C__MasterAnnouncment__Debug__AC__MasterAnnouncment( msg );
    entryaction_____Debug__C__MasterAnnouncment__Debug__A__Ac__MasterAnnouncment( msg );
}

void Capsule_ENV::actionchain_____Debug__C__MasterAnnouncment__Debug__En__Running( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__MasterAnnouncment__Debug__A__Ac__MasterAnnouncment( msg );
    transitionaction_____Debug__C__MasterAnnouncment__Debug__En__Running( msg );
    entryaction_____Debug__C__MasterAnnouncment__Debug__A__En__Running( msg );
}

void Capsule_ENV::actionchain_____Debug__C__MasterAnnouncment__Debug__Ex__Running( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__MasterAnnouncment__Debug__B__Ex__Running( msg );
    transitionaction_____Debug__C__MasterAnnouncment__Debug__Ex__Running( msg );
    entryaction_____Debug__C__MasterAnnouncment__Debug__B__Ac__MasterAnnouncment( msg );
}

void Capsule_ENV::actionchain_____Debug__C__MasterAnnouncment__Debug__end__trans__MasterAnnouncment( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__MasterAnnouncment__Debug__A__En__Running( msg );
    transitionaction_____Debug__C__MasterAnnouncment__Debug__end__trans__MasterAnnouncment( msg );
    save_history( Debug__C__MasterAnnouncment, Debug__C__MasterAnnouncment__Debug__A__En__Running );
}

void Capsule_ENV::actionchain_____Debug__C__MasterAnnouncment__Debug__init__trans__MasterAnnouncment( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__MasterAnnouncment__Debug__init__trans__MasterAnnouncment( msg );
    entryaction_____Debug__C__MasterAnnouncment__Debug__B__Ex__Running( msg );
}

void Capsule_ENV::actionchain_____Debug__C__MasterAnnouncment__new_transition_1( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__MasterAnnouncment__Debug__B__Ex__Running( msg );
}

void Capsule_ENV::actionchain_____Debug__C__MasterAnnouncment__new_transition_10( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__MasterAnnouncment__boundary( msg );
    save_history( Debug__C__MasterAnnouncment, Debug__C__MasterAnnouncment__boundary );
}

void Capsule_ENV::actionchain_____Debug__C__MasterAnnouncment__new_transition_2( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__MasterAnnouncment__Debug__B__Ac__MasterAnnouncment( msg );
}

void Capsule_ENV::actionchain_____Debug__C__MasterAnnouncment__new_transition_3( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__MasterAnnouncment__Debug__A__Ac__MasterAnnouncment( msg );
}

void Capsule_ENV::actionchain_____Debug__C__MasterAnnouncment__new_transition_4( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__MasterAnnouncment__Debug__A__En__Running( msg );
}

void Capsule_ENV::actionchain_____Debug__C__MasterAnnouncment__new_transition_5_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__MasterAnnouncment__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__C__MasterAnnouncment__new_transition_6( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__MasterAnnouncment__Debug__B__Ex__Running( msg );
    save_history( Debug__C__MasterAnnouncment, Debug__C__MasterAnnouncment__Debug__B__Ex__Running );
}

void Capsule_ENV::actionchain_____Debug__C__MasterAnnouncment__new_transition_7( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__MasterAnnouncment__Debug__B__Ac__MasterAnnouncment( msg );
    save_history( Debug__C__MasterAnnouncment, Debug__C__MasterAnnouncment__Debug__B__Ac__MasterAnnouncment );
}

void Capsule_ENV::actionchain_____Debug__C__MasterAnnouncment__new_transition_8( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__MasterAnnouncment__Debug__A__Ac__MasterAnnouncment( msg );
    save_history( Debug__C__MasterAnnouncment, Debug__C__MasterAnnouncment__Debug__A__Ac__MasterAnnouncment );
}

void Capsule_ENV::actionchain_____Debug__C__MasterAnnouncment__new_transition_9( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__MasterAnnouncment__Debug__A__En__Running( msg );
    save_history( Debug__C__MasterAnnouncment, Debug__C__MasterAnnouncment__Debug__A__En__Running );
}

void Capsule_ENV::actionchain_____Debug__C__QueryConfig__Debug__AC__QueryConfig( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__QueryConfig__Debug__B__Ac__QueryConfig( msg );
    transitionaction_____Debug__C__QueryConfig__Debug__AC__QueryConfig( msg );
    entryaction_____Debug__C__QueryConfig__Debug__A__Ac__QueryConfig( msg );
}

void Capsule_ENV::actionchain_____Debug__C__QueryConfig__Debug__En__Running( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__QueryConfig__Debug__A__Ac__QueryConfig( msg );
    transitionaction_____Debug__C__QueryConfig__Debug__En__Running( msg );
    entryaction_____Debug__C__QueryConfig__Debug__A__En__Running( msg );
}

void Capsule_ENV::actionchain_____Debug__C__QueryConfig__Debug__Ex__Running( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__QueryConfig__Debug__B__Ex__Running( msg );
    transitionaction_____Debug__C__QueryConfig__Debug__Ex__Running( msg );
    entryaction_____Debug__C__QueryConfig__Debug__B__Ac__QueryConfig( msg );
}

void Capsule_ENV::actionchain_____Debug__C__QueryConfig__Debug__end__trans__QueryConfig( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__QueryConfig__Debug__A__En__Running( msg );
    transitionaction_____Debug__C__QueryConfig__Debug__end__trans__QueryConfig( msg );
    save_history( Debug__C__QueryConfig, Debug__C__QueryConfig__Debug__A__En__Running );
}

void Capsule_ENV::actionchain_____Debug__C__QueryConfig__Debug__init__trans__QueryConfig( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__QueryConfig__Debug__init__trans__QueryConfig( msg );
    entryaction_____Debug__C__QueryConfig__Debug__B__Ex__Running( msg );
}

void Capsule_ENV::actionchain_____Debug__C__QueryConfig__new_transition_63( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__QueryConfig__Debug__B__Ex__Running( msg );
}

void Capsule_ENV::actionchain_____Debug__C__QueryConfig__new_transition_64( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__QueryConfig__Debug__B__Ac__QueryConfig( msg );
}

void Capsule_ENV::actionchain_____Debug__C__QueryConfig__new_transition_65( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__QueryConfig__Debug__A__Ac__QueryConfig( msg );
}

void Capsule_ENV::actionchain_____Debug__C__QueryConfig__new_transition_66( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__QueryConfig__Debug__A__En__Running( msg );
}

void Capsule_ENV::actionchain_____Debug__C__QueryConfig__new_transition_67_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__QueryConfig__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__C__QueryConfig__new_transition_68( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__QueryConfig__Debug__B__Ex__Running( msg );
    save_history( Debug__C__QueryConfig, Debug__C__QueryConfig__Debug__B__Ex__Running );
}

void Capsule_ENV::actionchain_____Debug__C__QueryConfig__new_transition_69( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__QueryConfig__Debug__B__Ac__QueryConfig( msg );
    save_history( Debug__C__QueryConfig, Debug__C__QueryConfig__Debug__B__Ac__QueryConfig );
}

void Capsule_ENV::actionchain_____Debug__C__QueryConfig__new_transition_70( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__QueryConfig__Debug__A__Ac__QueryConfig( msg );
    save_history( Debug__C__QueryConfig, Debug__C__QueryConfig__Debug__A__Ac__QueryConfig );
}

void Capsule_ENV::actionchain_____Debug__C__QueryConfig__new_transition_71( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__QueryConfig__Debug__A__En__Running( msg );
    save_history( Debug__C__QueryConfig, Debug__C__QueryConfig__Debug__A__En__Running );
}

void Capsule_ENV::actionchain_____Debug__C__QueryConfig__new_transition_72( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__QueryConfig__boundary( msg );
    save_history( Debug__C__QueryConfig, Debug__C__QueryConfig__boundary );
}

void Capsule_ENV::actionchain_____Debug__C__RetryConfig__Debug__AC__RetryConfig( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__RetryConfig__Debug__B__Ac__RetryConfig( msg );
    transitionaction_____Debug__C__RetryConfig__Debug__AC__RetryConfig( msg );
    entryaction_____Debug__C__RetryConfig__Debug__A__Ac__RetryConfig( msg );
}

void Capsule_ENV::actionchain_____Debug__C__RetryConfig__Debug__En__ReadConfig( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__RetryConfig__Debug__A__Ac__RetryConfig( msg );
    transitionaction_____Debug__C__RetryConfig__Debug__En__ReadConfig( msg );
    entryaction_____Debug__C__RetryConfig__Debug__A__En__ReadConfig( msg );
}

void Capsule_ENV::actionchain_____Debug__C__RetryConfig__Debug__Ex__ConfigFailure( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__RetryConfig__Debug__B__Ex__ConfigFailure( msg );
    transitionaction_____Debug__C__RetryConfig__Debug__Ex__ConfigFailure( msg );
    entryaction_____Debug__C__RetryConfig__Debug__B__Ac__RetryConfig( msg );
}

void Capsule_ENV::actionchain_____Debug__C__RetryConfig__Debug__end__trans__RetryConfig( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__RetryConfig__Debug__A__En__ReadConfig( msg );
    transitionaction_____Debug__C__RetryConfig__Debug__end__trans__RetryConfig( msg );
    save_history( Debug__C__RetryConfig, Debug__C__RetryConfig__Debug__A__En__ReadConfig );
}

void Capsule_ENV::actionchain_____Debug__C__RetryConfig__Debug__init__trans__RetryConfig( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__RetryConfig__Debug__init__trans__RetryConfig( msg );
    entryaction_____Debug__C__RetryConfig__Debug__B__Ex__ConfigFailure( msg );
}

void Capsule_ENV::actionchain_____Debug__C__RetryConfig__new_transition_19( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__RetryConfig__Debug__B__Ex__ConfigFailure( msg );
}

void Capsule_ENV::actionchain_____Debug__C__RetryConfig__new_transition_20( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__RetryConfig__Debug__B__Ac__RetryConfig( msg );
}

void Capsule_ENV::actionchain_____Debug__C__RetryConfig__new_transition_21( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__RetryConfig__Debug__A__Ac__RetryConfig( msg );
}

void Capsule_ENV::actionchain_____Debug__C__RetryConfig__new_transition_22( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__RetryConfig__Debug__A__En__ReadConfig( msg );
}

void Capsule_ENV::actionchain_____Debug__C__RetryConfig__new_transition_23_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__RetryConfig__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__C__RetryConfig__new_transition_24( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__RetryConfig__Debug__B__Ex__ConfigFailure( msg );
    save_history( Debug__C__RetryConfig, Debug__C__RetryConfig__Debug__B__Ex__ConfigFailure );
}

void Capsule_ENV::actionchain_____Debug__C__RetryConfig__new_transition_25( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__RetryConfig__Debug__B__Ac__RetryConfig( msg );
    save_history( Debug__C__RetryConfig, Debug__C__RetryConfig__Debug__B__Ac__RetryConfig );
}

void Capsule_ENV::actionchain_____Debug__C__RetryConfig__new_transition_26( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__RetryConfig__Debug__A__Ac__RetryConfig( msg );
    save_history( Debug__C__RetryConfig, Debug__C__RetryConfig__Debug__A__Ac__RetryConfig );
}

void Capsule_ENV::actionchain_____Debug__C__RetryConfig__new_transition_27( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__RetryConfig__Debug__A__En__ReadConfig( msg );
    save_history( Debug__C__RetryConfig, Debug__C__RetryConfig__Debug__A__En__ReadConfig );
}

void Capsule_ENV::actionchain_____Debug__C__RetryConfig__new_transition_28( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__RetryConfig__boundary( msg );
    save_history( Debug__C__RetryConfig, Debug__C__RetryConfig__boundary );
}

void Capsule_ENV::actionchain_____Debug__C__Server1Failure__Debug__AC__Server1Failure( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Server1Failure__Debug__B__Ac__Server1Failure( msg );
    transitionaction_____Debug__C__Server1Failure__Debug__AC__Server1Failure( msg );
    entryaction_____Debug__C__Server1Failure__Debug__A__Ac__Server1Failure( msg );
}

void Capsule_ENV::actionchain_____Debug__C__Server1Failure__Debug__En__Running( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Server1Failure__Debug__A__Ac__Server1Failure( msg );
    transitionaction_____Debug__C__Server1Failure__Debug__En__Running( msg );
    entryaction_____Debug__C__Server1Failure__Debug__A__En__Running( msg );
}

void Capsule_ENV::actionchain_____Debug__C__Server1Failure__Debug__Ex__Running( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Server1Failure__Debug__B__Ex__Running( msg );
    transitionaction_____Debug__C__Server1Failure__Debug__Ex__Running( msg );
    entryaction_____Debug__C__Server1Failure__Debug__B__Ac__Server1Failure( msg );
}

void Capsule_ENV::actionchain_____Debug__C__Server1Failure__Debug__end__trans__Server1Failure( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Server1Failure__Debug__A__En__Running( msg );
    transitionaction_____Debug__C__Server1Failure__Debug__end__trans__Server1Failure( msg );
    save_history( Debug__C__Server1Failure, Debug__C__Server1Failure__Debug__A__En__Running );
}

void Capsule_ENV::actionchain_____Debug__C__Server1Failure__Debug__init__trans__Server1Failure( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__Server1Failure__Debug__init__trans__Server1Failure( msg );
    entryaction_____Debug__C__Server1Failure__Debug__B__Ex__Running( msg );
}

void Capsule_ENV::actionchain_____Debug__C__Server1Failure__new_transition_73( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Server1Failure__Debug__B__Ex__Running( msg );
}

void Capsule_ENV::actionchain_____Debug__C__Server1Failure__new_transition_74( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Server1Failure__Debug__B__Ac__Server1Failure( msg );
}

void Capsule_ENV::actionchain_____Debug__C__Server1Failure__new_transition_75( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Server1Failure__Debug__A__Ac__Server1Failure( msg );
}

void Capsule_ENV::actionchain_____Debug__C__Server1Failure__new_transition_76( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Server1Failure__Debug__A__En__Running( msg );
}

void Capsule_ENV::actionchain_____Debug__C__Server1Failure__new_transition_77_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Server1Failure__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__C__Server1Failure__new_transition_78( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Server1Failure__Debug__B__Ex__Running( msg );
    save_history( Debug__C__Server1Failure, Debug__C__Server1Failure__Debug__B__Ex__Running );
}

void Capsule_ENV::actionchain_____Debug__C__Server1Failure__new_transition_79( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Server1Failure__Debug__B__Ac__Server1Failure( msg );
    save_history( Debug__C__Server1Failure, Debug__C__Server1Failure__Debug__B__Ac__Server1Failure );
}

void Capsule_ENV::actionchain_____Debug__C__Server1Failure__new_transition_80( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Server1Failure__Debug__A__Ac__Server1Failure( msg );
    save_history( Debug__C__Server1Failure, Debug__C__Server1Failure__Debug__A__Ac__Server1Failure );
}

void Capsule_ENV::actionchain_____Debug__C__Server1Failure__new_transition_81( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Server1Failure__Debug__A__En__Running( msg );
    save_history( Debug__C__Server1Failure, Debug__C__Server1Failure__Debug__A__En__Running );
}

void Capsule_ENV::actionchain_____Debug__C__Server1Failure__new_transition_82( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Server1Failure__boundary( msg );
    save_history( Debug__C__Server1Failure, Debug__C__Server1Failure__boundary );
}

void Capsule_ENV::actionchain_____Debug__C__configLoaded__Debug__AC__configLoaded( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__configLoaded__Debug__B__Ac__configLoaded( msg );
    transitionaction_____Debug__C__configLoaded__Debug__AC__configLoaded( msg );
    entryaction_____Debug__C__configLoaded__Debug__A__Ac__configLoaded( msg );
}

void Capsule_ENV::actionchain_____Debug__C__configLoaded__Debug__Ex__ReadConfig( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__configLoaded__Debug__B__Ex__ReadConfig( msg );
    transitionaction_____Debug__C__configLoaded__Debug__Ex__ReadConfig( msg );
    entryaction_____Debug__C__configLoaded__Debug__B__Ac__configLoaded( msg );
}

void Capsule_ENV::actionchain_____Debug__C__configLoaded__Debug__end__trans__configLoaded( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__configLoaded__Debug__A__Ac__configLoaded( msg );
    transitionaction_____Debug__C__configLoaded__Debug__end__trans__configLoaded( msg );
    save_history( Debug__C__configLoaded, Debug__C__configLoaded__Debug__A__Ac__configLoaded );
}

void Capsule_ENV::actionchain_____Debug__C__configLoaded__Debug__init__trans__configLoaded( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__configLoaded__Debug__B__Ex__ReadConfig( msg );
}

void Capsule_ENV::actionchain_____Debug__C__configLoaded__new_transition_47( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__configLoaded__Debug__B__Ex__ReadConfig( msg );
}

void Capsule_ENV::actionchain_____Debug__C__configLoaded__new_transition_48( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__configLoaded__Debug__B__Ac__configLoaded( msg );
}

void Capsule_ENV::actionchain_____Debug__C__configLoaded__new_transition_49( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__configLoaded__Debug__A__Ac__configLoaded( msg );
}

void Capsule_ENV::actionchain_____Debug__C__configLoaded__new_transition_50_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__configLoaded__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__C__configLoaded__new_transition_51( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__configLoaded__Debug__B__Ex__ReadConfig( msg );
    save_history( Debug__C__configLoaded, Debug__C__configLoaded__Debug__B__Ex__ReadConfig );
}

void Capsule_ENV::actionchain_____Debug__C__configLoaded__new_transition_52( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__configLoaded__Debug__B__Ac__configLoaded( msg );
    save_history( Debug__C__configLoaded, Debug__C__configLoaded__Debug__B__Ac__configLoaded );
}

void Capsule_ENV::actionchain_____Debug__C__configLoaded__new_transition_53( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__configLoaded__Debug__A__Ac__configLoaded( msg );
    save_history( Debug__C__configLoaded, Debug__C__configLoaded__Debug__A__Ac__configLoaded );
}

void Capsule_ENV::actionchain_____Debug__C__configLoaded__new_transition_54( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__configLoaded__boundary( msg );
    save_history( Debug__C__configLoaded, Debug__C__configLoaded__boundary );
}

void Capsule_ENV::actionchain_____Debug__C__configOK__Debug__Ac__configOK( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__configOK__Debug__B__Ac__configOK( msg );
    transitionaction_____Debug__C__configOK__Debug__Ac__configOK( msg );
    entryaction_____Debug__C__configOK__Debug__A__Ac__configOK( msg );
}

void Capsule_ENV::actionchain_____Debug__C__configOK__Debug__En__Running( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__configOK__Debug__A__Ac__configOK( msg );
    transitionaction_____Debug__C__configOK__Debug__En__Running( msg );
    entryaction_____Debug__C__configOK__Debug__A__En__configOK( msg );
}

void Capsule_ENV::actionchain_____Debug__C__configOK__Debug__end__trans__configOK( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__configOK__Debug__A__En__configOK( msg );
    transitionaction_____Debug__C__configOK__Debug__end__trans__configOK( msg );
    save_history( Debug__C__configOK, Debug__C__configOK__Debug__A__En__configOK );
}

void Capsule_ENV::actionchain_____Debug__C__configOK__Debug__init__trans__configOK( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__configOK__Debug__init__trans__configOK( msg );
    entryaction_____Debug__C__configOK__Debug__B__Ac__configOK( msg );
}

void Capsule_ENV::actionchain_____Debug__C__configOK__new_transition_39( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__configOK__Debug__B__Ac__configOK( msg );
}

void Capsule_ENV::actionchain_____Debug__C__configOK__new_transition_40( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__configOK__Debug__A__Ac__configOK( msg );
}

void Capsule_ENV::actionchain_____Debug__C__configOK__new_transition_41( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__configOK__Debug__A__En__configOK( msg );
}

void Capsule_ENV::actionchain_____Debug__C__configOK__new_transition_42_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__configOK__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__C__configOK__new_transition_43( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__configOK__Debug__B__Ac__configOK( msg );
    save_history( Debug__C__configOK, Debug__C__configOK__Debug__B__Ac__configOK );
}

void Capsule_ENV::actionchain_____Debug__C__configOK__new_transition_44( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__configOK__Debug__A__Ac__configOK( msg );
    save_history( Debug__C__configOK, Debug__C__configOK__Debug__A__Ac__configOK );
}

void Capsule_ENV::actionchain_____Debug__C__configOK__new_transition_45( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__configOK__Debug__A__En__configOK( msg );
    save_history( Debug__C__configOK, Debug__C__configOK__Debug__A__En__configOK );
}

void Capsule_ENV::actionchain_____Debug__C__configOK__new_transition_46( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__configOK__boundary( msg );
    save_history( Debug__C__configOK, Debug__C__configOK__boundary );
}

void Capsule_ENV::actionchain_____Debug__C__server2Failure__Debug__AC__server2Failure( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__server2Failure__Debug__B__Ac__server2Failure( msg );
    transitionaction_____Debug__C__server2Failure__Debug__AC__server2Failure( msg );
    entryaction_____Debug__C__server2Failure__Debug__A__Ac__server2Failure( msg );
}

void Capsule_ENV::actionchain_____Debug__C__server2Failure__Debug__En__Running( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__server2Failure__Debug__A__Ac__server2Failure( msg );
    transitionaction_____Debug__C__server2Failure__Debug__En__Running( msg );
    entryaction_____Debug__C__server2Failure__Debug__A__En__Running( msg );
}

void Capsule_ENV::actionchain_____Debug__C__server2Failure__Debug__Ex__Running( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__server2Failure__Debug__B__Ex__Running( msg );
    transitionaction_____Debug__C__server2Failure__Debug__Ex__Running( msg );
    entryaction_____Debug__C__server2Failure__Debug__B__Ac__server2Failure( msg );
}

void Capsule_ENV::actionchain_____Debug__C__server2Failure__Debug__end__trans__server2Failure( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__server2Failure__Debug__A__En__Running( msg );
    transitionaction_____Debug__C__server2Failure__Debug__end__trans__server2Failure( msg );
    save_history( Debug__C__server2Failure, Debug__C__server2Failure__Debug__A__En__Running );
}

void Capsule_ENV::actionchain_____Debug__C__server2Failure__Debug__init__trans__server2Failure( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__server2Failure__Debug__init__trans__server2Failure( msg );
    entryaction_____Debug__C__server2Failure__Debug__B__Ex__Running( msg );
}

void Capsule_ENV::actionchain_____Debug__C__server2Failure__new_transition_29( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__server2Failure__Debug__B__Ex__Running( msg );
}

void Capsule_ENV::actionchain_____Debug__C__server2Failure__new_transition_30( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__server2Failure__Debug__B__Ac__server2Failure( msg );
}

void Capsule_ENV::actionchain_____Debug__C__server2Failure__new_transition_31( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__server2Failure__Debug__A__Ac__server2Failure( msg );
}

void Capsule_ENV::actionchain_____Debug__C__server2Failure__new_transition_32( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__server2Failure__Debug__A__En__Running( msg );
}

void Capsule_ENV::actionchain_____Debug__C__server2Failure__new_transition_33_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__server2Failure__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__C__server2Failure__new_transition_34( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__server2Failure__Debug__B__Ex__Running( msg );
    save_history( Debug__C__server2Failure, Debug__C__server2Failure__Debug__B__Ex__Running );
}

void Capsule_ENV::actionchain_____Debug__C__server2Failure__new_transition_35( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__server2Failure__Debug__B__Ac__server2Failure( msg );
    save_history( Debug__C__server2Failure, Debug__C__server2Failure__Debug__B__Ac__server2Failure );
}

void Capsule_ENV::actionchain_____Debug__C__server2Failure__new_transition_36( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__server2Failure__Debug__A__Ac__server2Failure( msg );
    save_history( Debug__C__server2Failure, Debug__C__server2Failure__Debug__A__Ac__server2Failure );
}

void Capsule_ENV::actionchain_____Debug__C__server2Failure__new_transition_37( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__server2Failure__Debug__A__En__Running( msg );
    save_history( Debug__C__server2Failure, Debug__C__server2Failure__Debug__A__En__Running );
}

void Capsule_ENV::actionchain_____Debug__C__server2Failure__new_transition_38( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__server2Failure__boundary( msg );
    save_history( Debug__C__server2Failure, Debug__C__server2Failure__boundary );
}

void Capsule_ENV::actionchain_____Debug__ConfigNOK( const UMLRTMessage * msg )
{
    transitionaction_____Debug__ConfigNOK( msg );
}

void Capsule_ENV::actionchain_____Debug__ConfigNOK__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ConfigNOK__boundary( msg );
    transitionaction_____Debug__ConfigNOK__E( msg );
    entryaction_____ConfigFailure( msg );
}

void Capsule_ENV::actionchain_____Debug__ConfigNOK__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__ConfigNOK__S( msg );
    entryaction_____Debug__C__ConfigNOK__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__ConfigNOK__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ConfigNOK__boundary( msg );
    transitionaction_____Debug__ConfigNOK__dbg( msg );
    entryaction_____Debug__C__ConfigNOK__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__InitDebug( const UMLRTMessage * msg )
{
    transitionaction_____Debug__InitDebug( msg );
    entryaction_____Debug__InitState( msg );
}

void Capsule_ENV::actionchain_____Debug__Init__ReadConfig__8( const UMLRTMessage * msg )
{
    exitaction_____Debug__InitState( msg );
    transitionaction_____Debug__Init__ReadConfig__8( msg );
}

void Capsule_ENV::actionchain_____Debug__Init__ReadConfig__8__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Init__ReadConfig__8__boundary( msg );
    transitionaction_____Debug__Init__ReadConfig__8__E( msg );
    entryaction_____ReadConfig( msg );
}

void Capsule_ENV::actionchain_____Debug__Init__ReadConfig__8__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__Init__ReadConfig__8__S( msg );
    entryaction_____Debug__C__Init__ReadConfig__8__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__Init__ReadConfig__8__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Init__ReadConfig__8__boundary( msg );
    transitionaction_____Debug__Init__ReadConfig__8__dbg( msg );
    entryaction_____Debug__C__Init__ReadConfig__8__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__MasterAnnouncment( const UMLRTMessage * msg )
{
    exitaction_____Running( msg );
    transitionaction_____Debug__MasterAnnouncment( msg );
}

void Capsule_ENV::actionchain_____Debug__MasterAnnouncment__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__MasterAnnouncment__boundary( msg );
    transitionaction_____Debug__MasterAnnouncment__E( msg );
    entryaction_____Running( msg );
}

void Capsule_ENV::actionchain_____Debug__MasterAnnouncment__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__MasterAnnouncment__S( msg );
    entryaction_____Debug__C__MasterAnnouncment__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__MasterAnnouncment__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__MasterAnnouncment__boundary( msg );
    transitionaction_____Debug__MasterAnnouncment__dbg( msg );
    entryaction_____Debug__C__MasterAnnouncment__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__QueryConfig( const UMLRTMessage * msg )
{
    exitaction_____Running( msg );
    transitionaction_____Debug__QueryConfig( msg );
}

void Capsule_ENV::actionchain_____Debug__QueryConfig__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__QueryConfig__boundary( msg );
    transitionaction_____Debug__QueryConfig__E( msg );
    entryaction_____Running( msg );
}

void Capsule_ENV::actionchain_____Debug__QueryConfig__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__QueryConfig__S( msg );
    entryaction_____Debug__C__QueryConfig__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__QueryConfig__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__QueryConfig__boundary( msg );
    transitionaction_____Debug__QueryConfig__dbg( msg );
    entryaction_____Debug__C__QueryConfig__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__RetryConfig( const UMLRTMessage * msg )
{
    exitaction_____ConfigFailure( msg );
    transitionaction_____Debug__RetryConfig( msg );
}

void Capsule_ENV::actionchain_____Debug__RetryConfig__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__RetryConfig__boundary( msg );
    transitionaction_____Debug__RetryConfig__E( msg );
    entryaction_____ReadConfig( msg );
}

void Capsule_ENV::actionchain_____Debug__RetryConfig__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__RetryConfig__S( msg );
    entryaction_____Debug__C__RetryConfig__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__RetryConfig__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__RetryConfig__boundary( msg );
    transitionaction_____Debug__RetryConfig__dbg( msg );
    entryaction_____Debug__C__RetryConfig__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__Server1Failure( const UMLRTMessage * msg )
{
    exitaction_____Running( msg );
    transitionaction_____Debug__Server1Failure( msg );
}

void Capsule_ENV::actionchain_____Debug__Server1Failure__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Server1Failure__boundary( msg );
    transitionaction_____Debug__Server1Failure__E( msg );
    entryaction_____Running( msg );
}

void Capsule_ENV::actionchain_____Debug__Server1Failure__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__Server1Failure__S( msg );
    entryaction_____Debug__C__Server1Failure__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__Server1Failure__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Server1Failure__boundary( msg );
    transitionaction_____Debug__Server1Failure__dbg( msg );
    entryaction_____Debug__C__Server1Failure__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__configLoaded( const UMLRTMessage * msg )
{
    exitaction_____ReadConfig( msg );
    transitionaction_____Debug__configLoaded( msg );
}

void Capsule_ENV::actionchain_____Debug__configLoaded__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__configLoaded__boundary( msg );
    transitionaction_____Debug__configLoaded__E( msg );
}

void Capsule_ENV::actionchain_____Debug__configLoaded__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__configLoaded__S( msg );
    entryaction_____Debug__C__configLoaded__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__configLoaded__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__configLoaded__boundary( msg );
    transitionaction_____Debug__configLoaded__dbg( msg );
    entryaction_____Debug__C__configLoaded__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__configOK( const UMLRTMessage * msg )
{
    transitionaction_____Debug__configOK( msg );
}

void Capsule_ENV::actionchain_____Debug__configOK__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__configOK__boundary( msg );
    transitionaction_____Debug__configOK__E( msg );
    entryaction_____Running( msg );
}

void Capsule_ENV::actionchain_____Debug__configOK__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__configOK__S( msg );
    entryaction_____Debug__C__configOK__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__configOK__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__configOK__boundary( msg );
    transitionaction_____Debug__configOK__dbg( msg );
    entryaction_____Debug__C__configOK__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__server2Failure( const UMLRTMessage * msg )
{
    exitaction_____Running( msg );
    transitionaction_____Debug__server2Failure( msg );
}

void Capsule_ENV::actionchain_____Debug__server2Failure__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__server2Failure__boundary( msg );
    transitionaction_____Debug__server2Failure__E( msg );
    entryaction_____Running( msg );
}

void Capsule_ENV::actionchain_____Debug__server2Failure__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__server2Failure__S( msg );
    entryaction_____Debug__C__server2Failure__boundary( msg );
}

void Capsule_ENV::actionchain_____Debug__server2Failure__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__server2Failure__boundary( msg );
    transitionaction_____Debug__server2Failure__dbg( msg );
    entryaction_____Debug__C__server2Failure__boundary( msg );
}

void Capsule_ENV::actionchain_____Init__ReadConfig__8( const UMLRTMessage * msg )
{
    transitionaction_____Init__ReadConfig__8( msg );
    entryaction_____ReadConfig( msg );
}

void Capsule_ENV::actionchain_____MasterAnnouncment( const UMLRTMessage * msg )
{
    transitionaction_____MasterAnnouncment( msg );
    entryaction_____Running( msg );
}

void Capsule_ENV::actionchain_____QueryConfig( const UMLRTMessage * msg )
{
    transitionaction_____QueryConfig( msg );
    entryaction_____Running( msg );
}

void Capsule_ENV::actionchain_____RetryConfig( const UMLRTMessage * msg )
{
    transitionaction_____RetryConfig( msg );
    entryaction_____ReadConfig( msg );
}

void Capsule_ENV::actionchain_____Server1Failure( const UMLRTMessage * msg )
{
    transitionaction_____Server1Failure( msg );
    entryaction_____Running( msg );
}

void Capsule_ENV::actionchain_____configLoaded( const UMLRTMessage * msg )
{
    transitionaction_____configLoaded( msg );
}

void Capsule_ENV::actionchain_____configOK( const UMLRTMessage * msg )
{
    transitionaction_____configOK( msg );
    entryaction_____Running( msg );
}

void Capsule_ENV::actionchain_____server2Failure( const UMLRTMessage * msg )
{
    transitionaction_____server2Failure( msg );
    entryaction_____Running( msg );
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__ConfigNOK__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__ConfigNOK__Debug__init__trans__ConfigNOK( msg );
    return Debug__C__ConfigNOK__Debug__B__Ac__ConfigNOK;
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__ConfigNOK__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__ConfigNOK__E( msg );
    return ConfigFailure;
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__ConfigNOK__new_exitpoint_7( const UMLRTMessage * msg )
{
    actionchain_____Debug__ConfigNOK__dbg( msg );
    return choice_____Debug__C__ConfigNOK__deephistory( msg );
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__Init__ReadConfig__8__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__Init__ReadConfig__8__Debug__init__trans__Init__ReadConfig__8( msg );
    return Debug__C__Init__ReadConfig__8__Debug__B__Ac__Init__ReadConfig__8;
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__Init__ReadConfig__8__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__Init__ReadConfig__8__E( msg );
    return ReadConfig;
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__Init__ReadConfig__8__new_exitpoint_2( const UMLRTMessage * msg )
{
    actionchain_____Debug__Init__ReadConfig__8__dbg( msg );
    return choice_____Debug__C__Init__ReadConfig__8__deephistory( msg );
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__MasterAnnouncment__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__MasterAnnouncment__Debug__init__trans__MasterAnnouncment( msg );
    return Debug__C__MasterAnnouncment__Debug__B__Ex__Running;
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__MasterAnnouncment__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__MasterAnnouncment__E( msg );
    return Running;
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__MasterAnnouncment__new_exitpoint_1( const UMLRTMessage * msg )
{
    actionchain_____Debug__MasterAnnouncment__dbg( msg );
    return choice_____Debug__C__MasterAnnouncment__deephistory( msg );
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__QueryConfig__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__QueryConfig__Debug__init__trans__QueryConfig( msg );
    return Debug__C__QueryConfig__Debug__B__Ex__Running;
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__QueryConfig__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__QueryConfig__E( msg );
    return Running;
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__QueryConfig__new_exitpoint_8( const UMLRTMessage * msg )
{
    actionchain_____Debug__QueryConfig__dbg( msg );
    return choice_____Debug__C__QueryConfig__deephistory( msg );
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__RetryConfig__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__RetryConfig__Debug__init__trans__RetryConfig( msg );
    return Debug__C__RetryConfig__Debug__B__Ex__ConfigFailure;
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__RetryConfig__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__RetryConfig__E( msg );
    return ReadConfig;
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__RetryConfig__new_exitpoint_3( const UMLRTMessage * msg )
{
    actionchain_____Debug__RetryConfig__dbg( msg );
    return choice_____Debug__C__RetryConfig__deephistory( msg );
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__Server1Failure__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__Server1Failure__Debug__init__trans__Server1Failure( msg );
    return Debug__C__Server1Failure__Debug__B__Ex__Running;
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__Server1Failure__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__Server1Failure__E( msg );
    return Running;
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__Server1Failure__new_exitpoint_9( const UMLRTMessage * msg )
{
    actionchain_____Debug__Server1Failure__dbg( msg );
    return choice_____Debug__C__Server1Failure__deephistory( msg );
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__configLoaded__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__configLoaded__Debug__init__trans__configLoaded( msg );
    return Debug__C__configLoaded__Debug__B__Ex__ReadConfig;
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__configLoaded__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__configLoaded__E( msg );
    return choice_____Config( msg );
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__configLoaded__new_exitpoint_6( const UMLRTMessage * msg )
{
    actionchain_____Debug__configLoaded__dbg( msg );
    return choice_____Debug__C__configLoaded__deephistory( msg );
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__configOK__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__configOK__Debug__init__trans__configOK( msg );
    return Debug__C__configOK__Debug__B__Ac__configOK;
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__configOK__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__configOK__E( msg );
    return Running;
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__configOK__new_exitpoint_5( const UMLRTMessage * msg )
{
    actionchain_____Debug__configOK__dbg( msg );
    return choice_____Debug__C__configOK__deephistory( msg );
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__server2Failure__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__server2Failure__Debug__init__trans__server2Failure( msg );
    return Debug__C__server2Failure__Debug__B__Ex__Running;
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__server2Failure__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__server2Failure__E( msg );
    return Running;
}

Capsule_ENV::State Capsule_ENV::junction_____Debug__C__server2Failure__new_exitpoint_4( const UMLRTMessage * msg )
{
    actionchain_____Debug__server2Failure__dbg( msg );
    return choice_____Debug__C__server2Failure__deephistory( msg );
}

Capsule_ENV::State Capsule_ENV::choice_____Config( const UMLRTMessage * msg )
{
    if( action_____Debug__configOK__checkConfig( msg ) )
    {
        actionchain_____Debug__configOK( msg );
        return choice_____Debug__Path__configOK( msg );
    }
    else
    {
        actionchain_____Debug__ConfigNOK( msg );
        return choice_____Debug__Path__ConfigNOK( msg );
    }
    return currentState;
}

Capsule_ENV::State Capsule_ENV::choice_____Debug__C__ConfigNOK__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__ConfigNOK, Debug__C__ConfigNOK__Debug__B__Ac__ConfigNOK ) )
    {
        actionchain_____Debug__C__ConfigNOK__new_transition_55( msg );
        return Debug__C__ConfigNOK__Debug__B__Ac__ConfigNOK;
    }
    else if( check_history( Debug__C__ConfigNOK, Debug__C__ConfigNOK__Debug__A__Ac__ConfigNOK ) )
    {
        actionchain_____Debug__C__ConfigNOK__new_transition_56( msg );
        return Debug__C__ConfigNOK__Debug__A__Ac__ConfigNOK;
    }
    else if( check_history( Debug__C__ConfigNOK, Debug__C__ConfigNOK__Debug__A__En__ConfigNOK ) )
    {
        actionchain_____Debug__C__ConfigNOK__new_transition_57( msg );
        return Debug__C__ConfigNOK__Debug__A__En__ConfigNOK;
    }
    else if( check_history( Debug__C__ConfigNOK, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__ConfigNOK__new_transition_58_to_boundary( msg );
        return Debug__C__ConfigNOK__boundary;
    }
    return currentState;
}

Capsule_ENV::State Capsule_ENV::choice_____Debug__C__Init__ReadConfig__8__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__Init__ReadConfig__8, Debug__C__Init__ReadConfig__8__Debug__B__Ac__Init__ReadConfig__8 ) )
    {
        actionchain_____Debug__C__Init__ReadConfig__8__new_transition_11( msg );
        return Debug__C__Init__ReadConfig__8__Debug__B__Ac__Init__ReadConfig__8;
    }
    else if( check_history( Debug__C__Init__ReadConfig__8, Debug__C__Init__ReadConfig__8__Debug__A__Ac__Init__ReadConfig__8 ) )
    {
        actionchain_____Debug__C__Init__ReadConfig__8__new_transition_12( msg );
        return Debug__C__Init__ReadConfig__8__Debug__A__Ac__Init__ReadConfig__8;
    }
    else if( check_history( Debug__C__Init__ReadConfig__8, Debug__C__Init__ReadConfig__8__Debug__A__En__Init__ReadConfig__8 ) )
    {
        actionchain_____Debug__C__Init__ReadConfig__8__new_transition_13( msg );
        return Debug__C__Init__ReadConfig__8__Debug__A__En__Init__ReadConfig__8;
    }
    else if( check_history( Debug__C__Init__ReadConfig__8, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__Init__ReadConfig__8__new_transition_14_to_boundary( msg );
        return Debug__C__Init__ReadConfig__8__boundary;
    }
    return currentState;
}

Capsule_ENV::State Capsule_ENV::choice_____Debug__C__MasterAnnouncment__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__MasterAnnouncment, Debug__C__MasterAnnouncment__Debug__B__Ex__Running ) )
    {
        actionchain_____Debug__C__MasterAnnouncment__new_transition_1( msg );
        return Debug__C__MasterAnnouncment__Debug__B__Ex__Running;
    }
    else if( check_history( Debug__C__MasterAnnouncment, Debug__C__MasterAnnouncment__Debug__B__Ac__MasterAnnouncment ) )
    {
        actionchain_____Debug__C__MasterAnnouncment__new_transition_2( msg );
        return Debug__C__MasterAnnouncment__Debug__B__Ac__MasterAnnouncment;
    }
    else if( check_history( Debug__C__MasterAnnouncment, Debug__C__MasterAnnouncment__Debug__A__Ac__MasterAnnouncment ) )
    {
        actionchain_____Debug__C__MasterAnnouncment__new_transition_3( msg );
        return Debug__C__MasterAnnouncment__Debug__A__Ac__MasterAnnouncment;
    }
    else if( check_history( Debug__C__MasterAnnouncment, Debug__C__MasterAnnouncment__Debug__A__En__Running ) )
    {
        actionchain_____Debug__C__MasterAnnouncment__new_transition_4( msg );
        return Debug__C__MasterAnnouncment__Debug__A__En__Running;
    }
    else if( check_history( Debug__C__MasterAnnouncment, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__MasterAnnouncment__new_transition_5_to_boundary( msg );
        return Debug__C__MasterAnnouncment__boundary;
    }
    return currentState;
}

Capsule_ENV::State Capsule_ENV::choice_____Debug__C__QueryConfig__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__QueryConfig, Debug__C__QueryConfig__Debug__B__Ex__Running ) )
    {
        actionchain_____Debug__C__QueryConfig__new_transition_63( msg );
        return Debug__C__QueryConfig__Debug__B__Ex__Running;
    }
    else if( check_history( Debug__C__QueryConfig, Debug__C__QueryConfig__Debug__B__Ac__QueryConfig ) )
    {
        actionchain_____Debug__C__QueryConfig__new_transition_64( msg );
        return Debug__C__QueryConfig__Debug__B__Ac__QueryConfig;
    }
    else if( check_history( Debug__C__QueryConfig, Debug__C__QueryConfig__Debug__A__Ac__QueryConfig ) )
    {
        actionchain_____Debug__C__QueryConfig__new_transition_65( msg );
        return Debug__C__QueryConfig__Debug__A__Ac__QueryConfig;
    }
    else if( check_history( Debug__C__QueryConfig, Debug__C__QueryConfig__Debug__A__En__Running ) )
    {
        actionchain_____Debug__C__QueryConfig__new_transition_66( msg );
        return Debug__C__QueryConfig__Debug__A__En__Running;
    }
    else if( check_history( Debug__C__QueryConfig, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__QueryConfig__new_transition_67_to_boundary( msg );
        return Debug__C__QueryConfig__boundary;
    }
    return currentState;
}

Capsule_ENV::State Capsule_ENV::choice_____Debug__C__RetryConfig__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__RetryConfig, Debug__C__RetryConfig__Debug__B__Ex__ConfigFailure ) )
    {
        actionchain_____Debug__C__RetryConfig__new_transition_19( msg );
        return Debug__C__RetryConfig__Debug__B__Ex__ConfigFailure;
    }
    else if( check_history( Debug__C__RetryConfig, Debug__C__RetryConfig__Debug__B__Ac__RetryConfig ) )
    {
        actionchain_____Debug__C__RetryConfig__new_transition_20( msg );
        return Debug__C__RetryConfig__Debug__B__Ac__RetryConfig;
    }
    else if( check_history( Debug__C__RetryConfig, Debug__C__RetryConfig__Debug__A__Ac__RetryConfig ) )
    {
        actionchain_____Debug__C__RetryConfig__new_transition_21( msg );
        return Debug__C__RetryConfig__Debug__A__Ac__RetryConfig;
    }
    else if( check_history( Debug__C__RetryConfig, Debug__C__RetryConfig__Debug__A__En__ReadConfig ) )
    {
        actionchain_____Debug__C__RetryConfig__new_transition_22( msg );
        return Debug__C__RetryConfig__Debug__A__En__ReadConfig;
    }
    else if( check_history( Debug__C__RetryConfig, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__RetryConfig__new_transition_23_to_boundary( msg );
        return Debug__C__RetryConfig__boundary;
    }
    return currentState;
}

Capsule_ENV::State Capsule_ENV::choice_____Debug__C__Server1Failure__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__Server1Failure, Debug__C__Server1Failure__Debug__B__Ex__Running ) )
    {
        actionchain_____Debug__C__Server1Failure__new_transition_73( msg );
        return Debug__C__Server1Failure__Debug__B__Ex__Running;
    }
    else if( check_history( Debug__C__Server1Failure, Debug__C__Server1Failure__Debug__B__Ac__Server1Failure ) )
    {
        actionchain_____Debug__C__Server1Failure__new_transition_74( msg );
        return Debug__C__Server1Failure__Debug__B__Ac__Server1Failure;
    }
    else if( check_history( Debug__C__Server1Failure, Debug__C__Server1Failure__Debug__A__Ac__Server1Failure ) )
    {
        actionchain_____Debug__C__Server1Failure__new_transition_75( msg );
        return Debug__C__Server1Failure__Debug__A__Ac__Server1Failure;
    }
    else if( check_history( Debug__C__Server1Failure, Debug__C__Server1Failure__Debug__A__En__Running ) )
    {
        actionchain_____Debug__C__Server1Failure__new_transition_76( msg );
        return Debug__C__Server1Failure__Debug__A__En__Running;
    }
    else if( check_history( Debug__C__Server1Failure, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__Server1Failure__new_transition_77_to_boundary( msg );
        return Debug__C__Server1Failure__boundary;
    }
    return currentState;
}

Capsule_ENV::State Capsule_ENV::choice_____Debug__C__configLoaded__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__configLoaded, Debug__C__configLoaded__Debug__B__Ex__ReadConfig ) )
    {
        actionchain_____Debug__C__configLoaded__new_transition_47( msg );
        return Debug__C__configLoaded__Debug__B__Ex__ReadConfig;
    }
    else if( check_history( Debug__C__configLoaded, Debug__C__configLoaded__Debug__B__Ac__configLoaded ) )
    {
        actionchain_____Debug__C__configLoaded__new_transition_48( msg );
        return Debug__C__configLoaded__Debug__B__Ac__configLoaded;
    }
    else if( check_history( Debug__C__configLoaded, Debug__C__configLoaded__Debug__A__Ac__configLoaded ) )
    {
        actionchain_____Debug__C__configLoaded__new_transition_49( msg );
        return Debug__C__configLoaded__Debug__A__Ac__configLoaded;
    }
    else if( check_history( Debug__C__configLoaded, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__configLoaded__new_transition_50_to_boundary( msg );
        return Debug__C__configLoaded__boundary;
    }
    return currentState;
}

Capsule_ENV::State Capsule_ENV::choice_____Debug__C__configOK__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__configOK, Debug__C__configOK__Debug__B__Ac__configOK ) )
    {
        actionchain_____Debug__C__configOK__new_transition_39( msg );
        return Debug__C__configOK__Debug__B__Ac__configOK;
    }
    else if( check_history( Debug__C__configOK, Debug__C__configOK__Debug__A__Ac__configOK ) )
    {
        actionchain_____Debug__C__configOK__new_transition_40( msg );
        return Debug__C__configOK__Debug__A__Ac__configOK;
    }
    else if( check_history( Debug__C__configOK, Debug__C__configOK__Debug__A__En__configOK ) )
    {
        actionchain_____Debug__C__configOK__new_transition_41( msg );
        return Debug__C__configOK__Debug__A__En__configOK;
    }
    else if( check_history( Debug__C__configOK, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__configOK__new_transition_42_to_boundary( msg );
        return Debug__C__configOK__boundary;
    }
    return currentState;
}

Capsule_ENV::State Capsule_ENV::choice_____Debug__C__server2Failure__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__server2Failure, Debug__C__server2Failure__Debug__B__Ex__Running ) )
    {
        actionchain_____Debug__C__server2Failure__new_transition_29( msg );
        return Debug__C__server2Failure__Debug__B__Ex__Running;
    }
    else if( check_history( Debug__C__server2Failure, Debug__C__server2Failure__Debug__B__Ac__server2Failure ) )
    {
        actionchain_____Debug__C__server2Failure__new_transition_30( msg );
        return Debug__C__server2Failure__Debug__B__Ac__server2Failure;
    }
    else if( check_history( Debug__C__server2Failure, Debug__C__server2Failure__Debug__A__Ac__server2Failure ) )
    {
        actionchain_____Debug__C__server2Failure__new_transition_31( msg );
        return Debug__C__server2Failure__Debug__A__Ac__server2Failure;
    }
    else if( check_history( Debug__C__server2Failure, Debug__C__server2Failure__Debug__A__En__Running ) )
    {
        actionchain_____Debug__C__server2Failure__new_transition_32( msg );
        return Debug__C__server2Failure__Debug__A__En__Running;
    }
    else if( check_history( Debug__C__server2Failure, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__server2Failure__new_transition_33_to_boundary( msg );
        return Debug__C__server2Failure__boundary;
    }
    return currentState;
}

Capsule_ENV::State Capsule_ENV::choice_____Debug__Path__ConfigNOK( const UMLRTMessage * msg )
{
    if( action_____Debug__ConfigNOK__S__Debug__GuardConfigNOK( msg ) )
    {
        actionchain_____Debug__ConfigNOK__S( msg );
        return junction_____Debug__C__ConfigNOK__en( msg );
    }
    else
    {
        actionchain_____ConfigNOK( msg );
        return ConfigFailure;
    }
    return currentState;
}

Capsule_ENV::State Capsule_ENV::choice_____Debug__Path__Init__ReadConfig__8( const UMLRTMessage * msg )
{
    if( action_____Debug__Init__ReadConfig__8__S__Debug__GuardInit__ReadConfig__8( msg ) )
    {
        actionchain_____Debug__Init__ReadConfig__8__S( msg );
        return junction_____Debug__C__Init__ReadConfig__8__en( msg );
    }
    else
    {
        actionchain_____Init__ReadConfig__8( msg );
        return ReadConfig;
    }
    return currentState;
}

Capsule_ENV::State Capsule_ENV::choice_____Debug__Path__MasterAnnouncment( const UMLRTMessage * msg )
{
    if( action_____Debug__MasterAnnouncment__S__Debug__GuardMasterAnnouncment( msg ) )
    {
        actionchain_____Debug__MasterAnnouncment__S( msg );
        return junction_____Debug__C__MasterAnnouncment__en( msg );
    }
    else
    {
        actionchain_____MasterAnnouncment( msg );
        return Running;
    }
    return currentState;
}

Capsule_ENV::State Capsule_ENV::choice_____Debug__Path__QueryConfig( const UMLRTMessage * msg )
{
    if( action_____Debug__QueryConfig__S__Debug__GuardQueryConfig( msg ) )
    {
        actionchain_____Debug__QueryConfig__S( msg );
        return junction_____Debug__C__QueryConfig__en( msg );
    }
    else
    {
        actionchain_____QueryConfig( msg );
        return Running;
    }
    return currentState;
}

Capsule_ENV::State Capsule_ENV::choice_____Debug__Path__RetryConfig( const UMLRTMessage * msg )
{
    if( action_____Debug__RetryConfig__S__Debug__GuardRetryConfig( msg ) )
    {
        actionchain_____Debug__RetryConfig__S( msg );
        return junction_____Debug__C__RetryConfig__en( msg );
    }
    else
    {
        actionchain_____RetryConfig( msg );
        return ReadConfig;
    }
    return currentState;
}

Capsule_ENV::State Capsule_ENV::choice_____Debug__Path__Server1Failure( const UMLRTMessage * msg )
{
    if( action_____Debug__Server1Failure__S__Debug__GuardServer1Failure( msg ) )
    {
        actionchain_____Debug__Server1Failure__S( msg );
        return junction_____Debug__C__Server1Failure__en( msg );
    }
    else
    {
        actionchain_____Server1Failure( msg );
        return Running;
    }
    return currentState;
}

Capsule_ENV::State Capsule_ENV::choice_____Debug__Path__configLoaded( const UMLRTMessage * msg )
{
    if( action_____Debug__configLoaded__S__Debug__GuardconfigLoaded( msg ) )
    {
        actionchain_____Debug__configLoaded__S( msg );
        return junction_____Debug__C__configLoaded__en( msg );
    }
    else
    {
        actionchain_____configLoaded( msg );
        return choice_____Config( msg );
    }
    return currentState;
}

Capsule_ENV::State Capsule_ENV::choice_____Debug__Path__configOK( const UMLRTMessage * msg )
{
    if( action_____Debug__configOK__S__Debug__GuardconfigOK( msg ) )
    {
        actionchain_____Debug__configOK__S( msg );
        return junction_____Debug__C__configOK__en( msg );
    }
    else
    {
        actionchain_____configOK( msg );
        return Running;
    }
    return currentState;
}

Capsule_ENV::State Capsule_ENV::choice_____Debug__Path__server2Failure( const UMLRTMessage * msg )
{
    if( action_____Debug__server2Failure__S__Debug__Guardserver2Failure( msg ) )
    {
        actionchain_____Debug__server2Failure__S( msg );
        return junction_____Debug__C__server2Failure__en( msg );
    }
    else
    {
        actionchain_____server2Failure( msg );
        return Running;
    }
    return currentState;
}

Capsule_ENV::State Capsule_ENV::state_____ConfigFailure( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_FailureTimer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____Debug__RetryConfig( msg );
            return choice_____Debug__Path__RetryConfig( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__ConfigNOK__Debug__A__Ac__ConfigNOK( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__ConfigNOK__Debug__En__ConfigFailure( msg );
            return Debug__C__ConfigNOK__Debug__A__En__ConfigNOK;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ConfigNOK__new_transition_60( msg );
            return junction_____Debug__C__ConfigNOK__new_exitpoint_7( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__ConfigNOK__Debug__A__En__ConfigNOK( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__ConfigNOK__Debug__end__trans__ConfigNOK( msg );
            return junction_____Debug__C__ConfigNOK__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ConfigNOK__new_transition_61( msg );
            return junction_____Debug__C__ConfigNOK__new_exitpoint_7( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__ConfigNOK__Debug__B__Ac__ConfigNOK( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__ConfigNOK__Debug__Ac__ConfigNOK( msg );
            return Debug__C__ConfigNOK__Debug__A__Ac__ConfigNOK;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ConfigNOK__new_transition_59( msg );
            return junction_____Debug__C__ConfigNOK__new_exitpoint_7( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__ConfigNOK__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ConfigNOK__new_transition_62( msg );
            return junction_____Debug__C__ConfigNOK__new_exitpoint_7( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__Init__ReadConfig__8__Debug__A__Ac__Init__ReadConfig__8( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Init__ReadConfig__8__Debug__En__ReadConfig( msg );
            return Debug__C__Init__ReadConfig__8__Debug__A__En__Init__ReadConfig__8;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Init__ReadConfig__8__new_transition_16( msg );
            return junction_____Debug__C__Init__ReadConfig__8__new_exitpoint_2( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__Init__ReadConfig__8__Debug__A__En__Init__ReadConfig__8( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Init__ReadConfig__8__Debug__end__trans__Init__ReadConfig__8( msg );
            return junction_____Debug__C__Init__ReadConfig__8__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Init__ReadConfig__8__new_transition_17( msg );
            return junction_____Debug__C__Init__ReadConfig__8__new_exitpoint_2( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__Init__ReadConfig__8__Debug__B__Ac__Init__ReadConfig__8( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Init__ReadConfig__8__Debug__Ac__Init__ReadConfig__8( msg );
            return Debug__C__Init__ReadConfig__8__Debug__A__Ac__Init__ReadConfig__8;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Init__ReadConfig__8__new_transition_15( msg );
            return junction_____Debug__C__Init__ReadConfig__8__new_exitpoint_2( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__Init__ReadConfig__8__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Init__ReadConfig__8__new_transition_18( msg );
            return junction_____Debug__C__Init__ReadConfig__8__new_exitpoint_2( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__MasterAnnouncment__Debug__A__Ac__MasterAnnouncment( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__MasterAnnouncment__Debug__En__Running( msg );
            return Debug__C__MasterAnnouncment__Debug__A__En__Running;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__MasterAnnouncment__new_transition_8( msg );
            return junction_____Debug__C__MasterAnnouncment__new_exitpoint_1( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__MasterAnnouncment__Debug__A__En__Running( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__MasterAnnouncment__Debug__end__trans__MasterAnnouncment( msg );
            return junction_____Debug__C__MasterAnnouncment__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__MasterAnnouncment__new_transition_9( msg );
            return junction_____Debug__C__MasterAnnouncment__new_exitpoint_1( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__MasterAnnouncment__Debug__B__Ac__MasterAnnouncment( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__MasterAnnouncment__Debug__AC__MasterAnnouncment( msg );
            return Debug__C__MasterAnnouncment__Debug__A__Ac__MasterAnnouncment;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__MasterAnnouncment__new_transition_7( msg );
            return junction_____Debug__C__MasterAnnouncment__new_exitpoint_1( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__MasterAnnouncment__Debug__B__Ex__Running( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__MasterAnnouncment__Debug__Ex__Running( msg );
            return Debug__C__MasterAnnouncment__Debug__B__Ac__MasterAnnouncment;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__MasterAnnouncment__new_transition_6( msg );
            return junction_____Debug__C__MasterAnnouncment__new_exitpoint_1( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__MasterAnnouncment__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__MasterAnnouncment__new_transition_10( msg );
            return junction_____Debug__C__MasterAnnouncment__new_exitpoint_1( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__QueryConfig__Debug__A__Ac__QueryConfig( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__QueryConfig__Debug__En__Running( msg );
            return Debug__C__QueryConfig__Debug__A__En__Running;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__QueryConfig__new_transition_70( msg );
            return junction_____Debug__C__QueryConfig__new_exitpoint_8( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__QueryConfig__Debug__A__En__Running( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__QueryConfig__Debug__end__trans__QueryConfig( msg );
            return junction_____Debug__C__QueryConfig__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__QueryConfig__new_transition_71( msg );
            return junction_____Debug__C__QueryConfig__new_exitpoint_8( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__QueryConfig__Debug__B__Ac__QueryConfig( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__QueryConfig__Debug__AC__QueryConfig( msg );
            return Debug__C__QueryConfig__Debug__A__Ac__QueryConfig;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__QueryConfig__new_transition_69( msg );
            return junction_____Debug__C__QueryConfig__new_exitpoint_8( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__QueryConfig__Debug__B__Ex__Running( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__QueryConfig__Debug__Ex__Running( msg );
            return Debug__C__QueryConfig__Debug__B__Ac__QueryConfig;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__QueryConfig__new_transition_68( msg );
            return junction_____Debug__C__QueryConfig__new_exitpoint_8( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__QueryConfig__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__QueryConfig__new_transition_72( msg );
            return junction_____Debug__C__QueryConfig__new_exitpoint_8( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__RetryConfig__Debug__A__Ac__RetryConfig( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__RetryConfig__Debug__En__ReadConfig( msg );
            return Debug__C__RetryConfig__Debug__A__En__ReadConfig;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__RetryConfig__new_transition_26( msg );
            return junction_____Debug__C__RetryConfig__new_exitpoint_3( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__RetryConfig__Debug__A__En__ReadConfig( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__RetryConfig__Debug__end__trans__RetryConfig( msg );
            return junction_____Debug__C__RetryConfig__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__RetryConfig__new_transition_27( msg );
            return junction_____Debug__C__RetryConfig__new_exitpoint_3( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__RetryConfig__Debug__B__Ac__RetryConfig( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__RetryConfig__Debug__AC__RetryConfig( msg );
            return Debug__C__RetryConfig__Debug__A__Ac__RetryConfig;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__RetryConfig__new_transition_25( msg );
            return junction_____Debug__C__RetryConfig__new_exitpoint_3( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__RetryConfig__Debug__B__Ex__ConfigFailure( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__RetryConfig__Debug__Ex__ConfigFailure( msg );
            return Debug__C__RetryConfig__Debug__B__Ac__RetryConfig;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__RetryConfig__new_transition_24( msg );
            return junction_____Debug__C__RetryConfig__new_exitpoint_3( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__RetryConfig__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__RetryConfig__new_transition_28( msg );
            return junction_____Debug__C__RetryConfig__new_exitpoint_3( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__Server1Failure__Debug__A__Ac__Server1Failure( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Server1Failure__Debug__En__Running( msg );
            return Debug__C__Server1Failure__Debug__A__En__Running;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Server1Failure__new_transition_80( msg );
            return junction_____Debug__C__Server1Failure__new_exitpoint_9( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__Server1Failure__Debug__A__En__Running( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Server1Failure__Debug__end__trans__Server1Failure( msg );
            return junction_____Debug__C__Server1Failure__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Server1Failure__new_transition_81( msg );
            return junction_____Debug__C__Server1Failure__new_exitpoint_9( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__Server1Failure__Debug__B__Ac__Server1Failure( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Server1Failure__Debug__AC__Server1Failure( msg );
            return Debug__C__Server1Failure__Debug__A__Ac__Server1Failure;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Server1Failure__new_transition_79( msg );
            return junction_____Debug__C__Server1Failure__new_exitpoint_9( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__Server1Failure__Debug__B__Ex__Running( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Server1Failure__Debug__Ex__Running( msg );
            return Debug__C__Server1Failure__Debug__B__Ac__Server1Failure;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Server1Failure__new_transition_78( msg );
            return junction_____Debug__C__Server1Failure__new_exitpoint_9( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__Server1Failure__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Server1Failure__new_transition_82( msg );
            return junction_____Debug__C__Server1Failure__new_exitpoint_9( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__configLoaded__Debug__A__Ac__configLoaded( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__configLoaded__Debug__end__trans__configLoaded( msg );
            return junction_____Debug__C__configLoaded__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__configLoaded__new_transition_53( msg );
            return junction_____Debug__C__configLoaded__new_exitpoint_6( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__configLoaded__Debug__B__Ac__configLoaded( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__configLoaded__Debug__AC__configLoaded( msg );
            return Debug__C__configLoaded__Debug__A__Ac__configLoaded;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__configLoaded__new_transition_52( msg );
            return junction_____Debug__C__configLoaded__new_exitpoint_6( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__configLoaded__Debug__B__Ex__ReadConfig( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__configLoaded__Debug__Ex__ReadConfig( msg );
            return Debug__C__configLoaded__Debug__B__Ac__configLoaded;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__configLoaded__new_transition_51( msg );
            return junction_____Debug__C__configLoaded__new_exitpoint_6( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__configLoaded__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__configLoaded__new_transition_54( msg );
            return junction_____Debug__C__configLoaded__new_exitpoint_6( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__configOK__Debug__A__Ac__configOK( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__configOK__Debug__En__Running( msg );
            return Debug__C__configOK__Debug__A__En__configOK;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__configOK__new_transition_44( msg );
            return junction_____Debug__C__configOK__new_exitpoint_5( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__configOK__Debug__A__En__configOK( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__configOK__Debug__end__trans__configOK( msg );
            return junction_____Debug__C__configOK__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__configOK__new_transition_45( msg );
            return junction_____Debug__C__configOK__new_exitpoint_5( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__configOK__Debug__B__Ac__configOK( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__configOK__Debug__Ac__configOK( msg );
            return Debug__C__configOK__Debug__A__Ac__configOK;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__configOK__new_transition_43( msg );
            return junction_____Debug__C__configOK__new_exitpoint_5( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__configOK__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__configOK__new_transition_46( msg );
            return junction_____Debug__C__configOK__new_exitpoint_5( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__server2Failure__Debug__A__Ac__server2Failure( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__server2Failure__Debug__En__Running( msg );
            return Debug__C__server2Failure__Debug__A__En__Running;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__server2Failure__new_transition_36( msg );
            return junction_____Debug__C__server2Failure__new_exitpoint_4( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__server2Failure__Debug__A__En__Running( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__server2Failure__Debug__end__trans__server2Failure( msg );
            return junction_____Debug__C__server2Failure__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__server2Failure__new_transition_37( msg );
            return junction_____Debug__C__server2Failure__new_exitpoint_4( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__server2Failure__Debug__B__Ac__server2Failure( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__server2Failure__Debug__AC__server2Failure( msg );
            return Debug__C__server2Failure__Debug__A__Ac__server2Failure;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__server2Failure__new_transition_35( msg );
            return junction_____Debug__C__server2Failure__new_exitpoint_4( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__server2Failure__Debug__B__Ex__Running( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__server2Failure__Debug__Ex__Running( msg );
            return Debug__C__server2Failure__Debug__B__Ac__server2Failure;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__server2Failure__new_transition_34( msg );
            return junction_____Debug__C__server2Failure__new_exitpoint_4( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__C__server2Failure__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__server2Failure__new_transition_38( msg );
            return junction_____Debug__C__server2Failure__new_exitpoint_4( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Debug__InitState( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__Init__ReadConfig__8( msg );
            return choice_____Debug__Path__Init__ReadConfig__8( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_ENV::State Capsule_ENV::state_____ReadConfig( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_configTimer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____Debug__configLoaded( msg );
            return choice_____Debug__Path__configLoaded( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Running( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_ConfigComm:
        switch( msg->getSignalId() )
        {
        case Config::signal_IAMMaster:
            actionchain_____Debug__MasterAnnouncment( msg );
            return choice_____Debug__Path__MasterAnnouncment( msg );
        case Config::signal_QueryConfig:
            actionchain_____Debug__QueryConfig( msg );
            return choice_____Debug__Path__QueryConfig( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_AnnouncmentServer2:
        switch( msg->getSignalId() )
        {
        case FailOver::signal_IAmAlive:
            actionchain_____Debug__server2Failure( msg );
            return choice_____Debug__Path__server2Failure( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_AnnouncmentServer1:
        switch( msg->getSignalId() )
        {
        case FailOver::signal_IAmAlive:
            actionchain_____Debug__Server1Failure( msg );
            return choice_____Debug__Path__Server1Failure( msg );
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
        Capsule_ENV::port_AnnouncmentServer1,
        "Timing",
        "AnnouncmentServer1",
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
        Capsule_ENV::port_AnnouncmentServer2,
        "Timing",
        "AnnouncmentServer2",
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
        Capsule_ENV::port_BITTimer,
        "Timing",
        "BITTimer",
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
        Capsule_ENV::port_ConfigComm,
        "Config",
        "ConfigComm",
        "",
        7,
        true,
        true,
        false,
        false,
        false,
        true,
        false
    },
    {
        Capsule_ENV::port_FailureTimer,
        "Timing",
        "FailureTimer",
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
        Capsule_ENV::port_GeneralTimer,
        "Timing",
        "GeneralTimer",
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
        Capsule_ENV::port_configTimer,
        "Timing",
        "configTimer",
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
        Capsule_ENV::port_extComm,
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

static void instantiate_ENV( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_ENV( &ENV, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass ENV = 
{
    "ENV",
    NULL,
    instantiate_ENV,
    0,
    NULL,
    8,
    portroles_border,
    0,
    NULL
};

