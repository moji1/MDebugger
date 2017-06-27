
#include "Server.hh"

#include "Config.hh"
#include "ExtInterface.hh"
#include "FailOver.hh"
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

Capsule_Server::Capsule_Server( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: Capsule_Host( cd, st, border, internal, isStat )
, ConfigComm( borderPorts[borderport_ConfigComm] )
, KeepAliveTimer( borderPorts[borderport_KeepAliveTimer] )
, Master( borderPorts[borderport_Master] )
, MasterAnnounceTimer( borderPorts[borderport_MasterAnnounceTimer] )
, ServerComm( borderPorts[borderport_ServerComm] )
, Slave( borderPorts[borderport_Slave] )
, Timer( borderPorts[borderport_Timer] )
, extComm( borderPorts[borderport_extComm] )
, KeepAliveTimeOut( 5 )
, AnnouncementTimeOut( 4 )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[Backup] = "Backup";
    stateNames[Backup__Debug__C__BackToSlave] = "Backup__Debug__C__BackToSlave";
    stateNames[Backup__Debug__C__CheckNoMaster] = "Backup__Debug__C__CheckNoMaster";
    stateNames[Backup__Debug__C__Initial1__RunAsSlave__2] = "Backup__Debug__C__Initial1__RunAsSlave__2";
    stateNames[Backup__Debug__C__KeepAliveMsg] = "Backup__Debug__C__KeepAliveMsg";
    stateNames[Backup__Debug__C__NokeepAlive] = "Backup__Debug__C__NokeepAlive";
    stateNames[Backup__Debug__C__ReplyConfig] = "Backup__Debug__C__ReplyConfig";
    stateNames[Backup__Debug__C__backtoslave] = "Backup__Debug__C__backtoslave";
    stateNames[Backup__Debug__C__backtoslave1] = "Backup__Debug__C__backtoslave1";
    stateNames[Debug__C__ActiveMode] = "Debug__C__ActiveMode";
    stateNames[Debug__C__BeSlave] = "Debug__C__BeSlave";
    stateNames[Debug__C__BeingMaster] = "Debug__C__BeingMaster";
    stateNames[Debug__C__ExitPoint1__BeMaster__4] = "Debug__C__ExitPoint1__BeMaster__4";
    stateNames[Debug__C__Init__StandBy__3] = "Debug__C__Init__StandBy__3";
    stateNames[Debug__C__KeepAlive] = "Debug__C__KeepAlive";
    stateNames[Debug__C__PassiveMode] = "Debug__C__PassiveMode";
    stateNames[Debug__C__Recover] = "Debug__C__Recover";
    stateNames[Debug__C__ServerFaliure] = "Debug__C__ServerFaliure";
    stateNames[Debug__C__StandBy__CheckConfig__5] = "Debug__C__StandBy__CheckConfig__5";
    stateNames[Debug__C__initTimer] = "Debug__C__initTimer";
    stateNames[Debug__C__purgeotherMessage] = "Debug__C__purgeotherMessage";
    stateNames[Backup__Debug__C__BackToSlave__Debug__A__Ac__BackToSlave] = "Backup__Debug__C__BackToSlave__Debug__A__Ac__BackToSlave";
    stateNames[Backup__Debug__C__BackToSlave__Debug__B__Ac__BackToSlave] = "Backup__Debug__C__BackToSlave__Debug__B__Ac__BackToSlave";
    stateNames[Backup__Debug__C__BackToSlave__Debug__B__Ex__TryBeMaster] = "Backup__Debug__C__BackToSlave__Debug__B__Ex__TryBeMaster";
    stateNames[Backup__Debug__C__BackToSlave__boundary] = "Backup__Debug__C__BackToSlave__boundary";
    stateNames[Backup__Debug__C__CheckNoMaster__Debug__A__Ac__CheckNoMaster] = "Backup__Debug__C__CheckNoMaster__Debug__A__Ac__CheckNoMaster";
    stateNames[Backup__Debug__C__CheckNoMaster__Debug__B__Ac__CheckNoMaster] = "Backup__Debug__C__CheckNoMaster__Debug__B__Ac__CheckNoMaster";
    stateNames[Backup__Debug__C__CheckNoMaster__boundary] = "Backup__Debug__C__CheckNoMaster__boundary";
    stateNames[Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__Ac__Initial1__RunAsSlave__2] = "Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__Ac__Initial1__RunAsSlave__2";
    stateNames[Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__En__Initial1__RunAsSlave__2] = "Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__En__Initial1__RunAsSlave__2";
    stateNames[Backup__Debug__C__Initial1__RunAsSlave__2__Debug__B__Ac__Initial1__RunAsSlave__2] = "Backup__Debug__C__Initial1__RunAsSlave__2__Debug__B__Ac__Initial1__RunAsSlave__2";
    stateNames[Backup__Debug__C__Initial1__RunAsSlave__2__boundary] = "Backup__Debug__C__Initial1__RunAsSlave__2__boundary";
    stateNames[Backup__Debug__C__KeepAliveMsg__Debug__A__Ac__KeepAliveMsg] = "Backup__Debug__C__KeepAliveMsg__Debug__A__Ac__KeepAliveMsg";
    stateNames[Backup__Debug__C__KeepAliveMsg__Debug__A__En__RunAsSlave] = "Backup__Debug__C__KeepAliveMsg__Debug__A__En__RunAsSlave";
    stateNames[Backup__Debug__C__KeepAliveMsg__Debug__B__Ac__KeepAliveMsg] = "Backup__Debug__C__KeepAliveMsg__Debug__B__Ac__KeepAliveMsg";
    stateNames[Backup__Debug__C__KeepAliveMsg__Debug__B__Ex__RunAsSlave] = "Backup__Debug__C__KeepAliveMsg__Debug__B__Ex__RunAsSlave";
    stateNames[Backup__Debug__C__KeepAliveMsg__boundary] = "Backup__Debug__C__KeepAliveMsg__boundary";
    stateNames[Backup__Debug__C__NokeepAlive__Debug__A__Ac__NokeepAlive] = "Backup__Debug__C__NokeepAlive__Debug__A__Ac__NokeepAlive";
    stateNames[Backup__Debug__C__NokeepAlive__Debug__A__En__TryBeMaster] = "Backup__Debug__C__NokeepAlive__Debug__A__En__TryBeMaster";
    stateNames[Backup__Debug__C__NokeepAlive__Debug__B__Ac__NokeepAlive] = "Backup__Debug__C__NokeepAlive__Debug__B__Ac__NokeepAlive";
    stateNames[Backup__Debug__C__NokeepAlive__Debug__B__Ex__RunAsSlave] = "Backup__Debug__C__NokeepAlive__Debug__B__Ex__RunAsSlave";
    stateNames[Backup__Debug__C__NokeepAlive__boundary] = "Backup__Debug__C__NokeepAlive__boundary";
    stateNames[Backup__Debug__C__ReplyConfig__Debug__A__Ac__ReplyConfig] = "Backup__Debug__C__ReplyConfig__Debug__A__Ac__ReplyConfig";
    stateNames[Backup__Debug__C__ReplyConfig__Debug__B__Ac__ReplyConfig] = "Backup__Debug__C__ReplyConfig__Debug__B__Ac__ReplyConfig";
    stateNames[Backup__Debug__C__ReplyConfig__Debug__B__Ex__TryBeMaster] = "Backup__Debug__C__ReplyConfig__Debug__B__Ex__TryBeMaster";
    stateNames[Backup__Debug__C__ReplyConfig__boundary] = "Backup__Debug__C__ReplyConfig__boundary";
    stateNames[Backup__Debug__C__backtoslave1__Debug__A__Ac__backtoslave1] = "Backup__Debug__C__backtoslave1__Debug__A__Ac__backtoslave1";
    stateNames[Backup__Debug__C__backtoslave1__Debug__B__Ac__backtoslave1] = "Backup__Debug__C__backtoslave1__Debug__B__Ac__backtoslave1";
    stateNames[Backup__Debug__C__backtoslave1__boundary] = "Backup__Debug__C__backtoslave1__boundary";
    stateNames[Backup__Debug__C__backtoslave__Debug__A__Ac__backtoslave] = "Backup__Debug__C__backtoslave__Debug__A__Ac__backtoslave";
    stateNames[Backup__Debug__C__backtoslave__Debug__A__En__backtoslave] = "Backup__Debug__C__backtoslave__Debug__A__En__backtoslave";
    stateNames[Backup__Debug__C__backtoslave__Debug__B__Ac__backtoslave] = "Backup__Debug__C__backtoslave__Debug__B__Ac__backtoslave";
    stateNames[Backup__Debug__C__backtoslave__boundary] = "Backup__Debug__C__backtoslave__boundary";
    stateNames[Backup__RunAsSlave] = "Backup__RunAsSlave";
    stateNames[Backup__TryBeMaster] = "Backup__TryBeMaster";
    stateNames[Debug__C__ActiveMode__Debug__A__Ac__ActiveMode] = "Debug__C__ActiveMode__Debug__A__Ac__ActiveMode";
    stateNames[Debug__C__ActiveMode__Debug__B__Ac__ActiveMode] = "Debug__C__ActiveMode__Debug__B__Ac__ActiveMode";
    stateNames[Debug__C__ActiveMode__boundary] = "Debug__C__ActiveMode__boundary";
    stateNames[Debug__C__BeSlave__Debug__A__Ac__BeSlave] = "Debug__C__BeSlave__Debug__A__Ac__BeSlave";
    stateNames[Debug__C__BeSlave__Debug__A__En__BeSlave] = "Debug__C__BeSlave__Debug__A__En__BeSlave";
    stateNames[Debug__C__BeSlave__Debug__B__Ac__BeSlave] = "Debug__C__BeSlave__Debug__B__Ac__BeSlave";
    stateNames[Debug__C__BeSlave__boundary] = "Debug__C__BeSlave__boundary";
    stateNames[Debug__C__BeingMaster__Debug__A__Ac__BeingMaster] = "Debug__C__BeingMaster__Debug__A__Ac__BeingMaster";
    stateNames[Debug__C__BeingMaster__Debug__A__En__BeingMaster] = "Debug__C__BeingMaster__Debug__A__En__BeingMaster";
    stateNames[Debug__C__BeingMaster__Debug__B__Ac__BeingMaster] = "Debug__C__BeingMaster__Debug__B__Ac__BeingMaster";
    stateNames[Debug__C__BeingMaster__boundary] = "Debug__C__BeingMaster__boundary";
    stateNames[Debug__C__ExitPoint1__BeMaster__4__Debug__A__Ac__ExitPoint1__BeMaster__4] = "Debug__C__ExitPoint1__BeMaster__4__Debug__A__Ac__ExitPoint1__BeMaster__4";
    stateNames[Debug__C__ExitPoint1__BeMaster__4__Debug__B__Ac__ExitPoint1__BeMaster__4] = "Debug__C__ExitPoint1__BeMaster__4__Debug__B__Ac__ExitPoint1__BeMaster__4";
    stateNames[Debug__C__ExitPoint1__BeMaster__4__boundary] = "Debug__C__ExitPoint1__BeMaster__4__boundary";
    stateNames[Debug__C__Init__StandBy__3__Debug__A__Ac__Init__StandBy__3] = "Debug__C__Init__StandBy__3__Debug__A__Ac__Init__StandBy__3";
    stateNames[Debug__C__Init__StandBy__3__Debug__A__En__Init__StandBy__3] = "Debug__C__Init__StandBy__3__Debug__A__En__Init__StandBy__3";
    stateNames[Debug__C__Init__StandBy__3__Debug__B__Ac__Init__StandBy__3] = "Debug__C__Init__StandBy__3__Debug__B__Ac__Init__StandBy__3";
    stateNames[Debug__C__Init__StandBy__3__boundary] = "Debug__C__Init__StandBy__3__boundary";
    stateNames[Debug__C__KeepAlive__Debug__A__Ac__KeepAlive] = "Debug__C__KeepAlive__Debug__A__Ac__KeepAlive";
    stateNames[Debug__C__KeepAlive__Debug__A__En__RunAsMaster] = "Debug__C__KeepAlive__Debug__A__En__RunAsMaster";
    stateNames[Debug__C__KeepAlive__Debug__B__Ac__KeepAlive] = "Debug__C__KeepAlive__Debug__B__Ac__KeepAlive";
    stateNames[Debug__C__KeepAlive__Debug__B__Ex__RunAsMaster] = "Debug__C__KeepAlive__Debug__B__Ex__RunAsMaster";
    stateNames[Debug__C__KeepAlive__boundary] = "Debug__C__KeepAlive__boundary";
    stateNames[Debug__C__MasterAnnounce] = "Debug__C__MasterAnnounce";
    stateNames[Debug__C__PassiveMode__Debug__A__Ac__PassiveMode] = "Debug__C__PassiveMode__Debug__A__Ac__PassiveMode";
    stateNames[Debug__C__PassiveMode__Debug__A__En__PassiveMode] = "Debug__C__PassiveMode__Debug__A__En__PassiveMode";
    stateNames[Debug__C__PassiveMode__Debug__B__Ac__PassiveMode] = "Debug__C__PassiveMode__Debug__B__Ac__PassiveMode";
    stateNames[Debug__C__PassiveMode__boundary] = "Debug__C__PassiveMode__boundary";
    stateNames[Debug__C__Recover__Debug__A__Ac__Recover] = "Debug__C__Recover__Debug__A__Ac__Recover";
    stateNames[Debug__C__Recover__Debug__B__Ac__Recover] = "Debug__C__Recover__Debug__B__Ac__Recover";
    stateNames[Debug__C__Recover__Debug__B__Ex__Failure] = "Debug__C__Recover__Debug__B__Ex__Failure";
    stateNames[Debug__C__Recover__boundary] = "Debug__C__Recover__boundary";
    stateNames[Debug__C__ServerFaliure__Debug__A__Ac__ServerFaliure] = "Debug__C__ServerFaliure__Debug__A__Ac__ServerFaliure";
    stateNames[Debug__C__ServerFaliure__Debug__A__En__Failure] = "Debug__C__ServerFaliure__Debug__A__En__Failure";
    stateNames[Debug__C__ServerFaliure__Debug__B__Ac__ServerFaliure] = "Debug__C__ServerFaliure__Debug__B__Ac__ServerFaliure";
    stateNames[Debug__C__ServerFaliure__Debug__B__Ex__RunAsMaster] = "Debug__C__ServerFaliure__Debug__B__Ex__RunAsMaster";
    stateNames[Debug__C__ServerFaliure__boundary] = "Debug__C__ServerFaliure__boundary";
    stateNames[Debug__C__ServiceRequest] = "Debug__C__ServiceRequest";
    stateNames[Debug__C__StandBy__CheckConfig__5__Debug__A__Ac__StandBy__CheckConfig__5] = "Debug__C__StandBy__CheckConfig__5__Debug__A__Ac__StandBy__CheckConfig__5";
    stateNames[Debug__C__StandBy__CheckConfig__5__Debug__B__Ac__StandBy__CheckConfig__5] = "Debug__C__StandBy__CheckConfig__5__Debug__B__Ac__StandBy__CheckConfig__5";
    stateNames[Debug__C__StandBy__CheckConfig__5__Debug__B__Ex__StandBy] = "Debug__C__StandBy__CheckConfig__5__Debug__B__Ex__StandBy";
    stateNames[Debug__C__StandBy__CheckConfig__5__boundary] = "Debug__C__StandBy__CheckConfig__5__boundary";
    stateNames[Debug__C__initTimer__Debug__A__Ac__initTimer] = "Debug__C__initTimer__Debug__A__Ac__initTimer";
    stateNames[Debug__C__initTimer__Debug__A__En__initTimer] = "Debug__C__initTimer__Debug__A__En__initTimer";
    stateNames[Debug__C__initTimer__Debug__B__Ac__initTimer] = "Debug__C__initTimer__Debug__B__Ac__initTimer";
    stateNames[Debug__C__initTimer__boundary] = "Debug__C__initTimer__boundary";
    stateNames[Debug__C__purgeotherMessage__Debug__A__Ac__purgeotherMessage] = "Debug__C__purgeotherMessage__Debug__A__Ac__purgeotherMessage";
    stateNames[Debug__C__purgeotherMessage__Debug__A__En__Failure] = "Debug__C__purgeotherMessage__Debug__A__En__Failure";
    stateNames[Debug__C__purgeotherMessage__Debug__B__Ac__purgeotherMessage] = "Debug__C__purgeotherMessage__Debug__B__Ac__purgeotherMessage";
    stateNames[Debug__C__purgeotherMessage__Debug__B__Ex__Failure] = "Debug__C__purgeotherMessage__Debug__B__Ex__Failure";
    stateNames[Debug__C__purgeotherMessage__boundary] = "Debug__C__purgeotherMessage__boundary";
    stateNames[Debug__InitState] = "Debug__InitState";
    stateNames[Failure] = "Failure";
    stateNames[RunAsMaster] = "RunAsMaster";
    stateNames[StandBy] = "StandBy";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
    int i = 0;
    while( i < 21 )
        history[i++] = SPECIAL_INTERNAL_STATE_UNVISITED;
}












void Capsule_Server::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_Master:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_Master, index, true );
            break;
        case borderport_ServerComm:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_ServerComm, index, true );
            break;
        case borderport_Slave:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_Slave, index, true );
            break;
        }
}

void Capsule_Server::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_Master:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_Master, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_Master], index );
            break;
        case borderport_ServerComm:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_ServerComm, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_ServerComm], index );
            break;
        case borderport_Slave:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_Slave, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_Slave], index );
            break;
        }
}









void Capsule_Server::Debug__variablesView()
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Server operation Debug__variablesView */
    std::string tempS="";
    tempS.append("KeepAliveTimeOut,");
    tempS.append("Integer,");
    if(KeepAliveTimeOut!=0){
    char tempR[10];
    sprintf(tempR,"%d",KeepAliveTimeOut);
    tempS.append(tempR);
    tempS.append("\n");
    }else {
    tempS.append("0");
    tempS.append("\n");
    };
    tempS.append("AnnouncementTimeOut,");
    tempS.append("Integer,");
    if(AnnouncementTimeOut!=0){
    char tempR[10];
    sprintf(tempR,"%d",AnnouncementTimeOut);
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

bool Capsule_Server::Debug__variablesChange( char * varName, char * varValue )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Server operation Debug__variablesChange */
    std::string tempVarName="";
    tempVarName.append(varName);
    if ("AnnouncementTimeOut"==tempVarName){
    AnnouncementTimeOut=atoi(varValue);
    return true;
    }else if ("KeepAliveTimeOut"==tempVarName){
    KeepAliveTimeOut=atoi(varValue);
    return true;
    }else 
    return false;
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_Server::Debug__sendEvent( debugEvents::EVENTSOURCEKIND eventSourceKind, debugEvents::EVENTTYPE eventType, const char * instanceName, int capsuleIndex, const char * signalName, char * capsuleName, char * sourceName, char * reserve1, char * reserve2, char * reserve3 )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Server operation Debug__sendEvent */
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

void Capsule_Server::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case StandBy:
        currentState = state_____StandBy( &message );
        break;
    case RunAsMaster:
        currentState = state_____RunAsMaster( &message );
        break;
    case Failure:
        currentState = state_____Failure( &message );
        break;
    case Debug__C__MasterAnnounce:
        currentState = state_____Debug__C__MasterAnnounce( &message );
        break;
    case Debug__C__ServiceRequest:
        currentState = state_____Debug__C__ServiceRequest( &message );
        break;
    case Debug__InitState:
        currentState = state_____Debug__InitState( &message );
        break;
    case Backup__TryBeMaster:
        currentState = state_____Backup__TryBeMaster( &message );
        break;
    case Backup__RunAsSlave:
        currentState = state_____Backup__RunAsSlave( &message );
        break;
    case Backup__Debug__C__Initial1__RunAsSlave__2__Debug__B__Ac__Initial1__RunAsSlave__2:
        currentState = state_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__B__Ac__Initial1__RunAsSlave__2( &message );
        break;
    case Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__Ac__Initial1__RunAsSlave__2:
        currentState = state_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__Ac__Initial1__RunAsSlave__2( &message );
        break;
    case Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__En__Initial1__RunAsSlave__2:
        currentState = state_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__En__Initial1__RunAsSlave__2( &message );
        break;
    case Backup__Debug__C__Initial1__RunAsSlave__2__boundary:
        currentState = state_____Backup__Debug__C__Initial1__RunAsSlave__2__boundary( &message );
        break;
    case Backup__Debug__C__BackToSlave__Debug__B__Ex__TryBeMaster:
        currentState = state_____Backup__Debug__C__BackToSlave__Debug__B__Ex__TryBeMaster( &message );
        break;
    case Backup__Debug__C__BackToSlave__Debug__B__Ac__BackToSlave:
        currentState = state_____Backup__Debug__C__BackToSlave__Debug__B__Ac__BackToSlave( &message );
        break;
    case Backup__Debug__C__BackToSlave__Debug__A__Ac__BackToSlave:
        currentState = state_____Backup__Debug__C__BackToSlave__Debug__A__Ac__BackToSlave( &message );
        break;
    case Backup__Debug__C__BackToSlave__boundary:
        currentState = state_____Backup__Debug__C__BackToSlave__boundary( &message );
        break;
    case Backup__Debug__C__backtoslave__Debug__B__Ac__backtoslave:
        currentState = state_____Backup__Debug__C__backtoslave__Debug__B__Ac__backtoslave( &message );
        break;
    case Backup__Debug__C__backtoslave__Debug__A__Ac__backtoslave:
        currentState = state_____Backup__Debug__C__backtoslave__Debug__A__Ac__backtoslave( &message );
        break;
    case Backup__Debug__C__backtoslave__Debug__A__En__backtoslave:
        currentState = state_____Backup__Debug__C__backtoslave__Debug__A__En__backtoslave( &message );
        break;
    case Backup__Debug__C__backtoslave__boundary:
        currentState = state_____Backup__Debug__C__backtoslave__boundary( &message );
        break;
    case Backup__Debug__C__ReplyConfig__Debug__B__Ex__TryBeMaster:
        currentState = state_____Backup__Debug__C__ReplyConfig__Debug__B__Ex__TryBeMaster( &message );
        break;
    case Backup__Debug__C__ReplyConfig__Debug__B__Ac__ReplyConfig:
        currentState = state_____Backup__Debug__C__ReplyConfig__Debug__B__Ac__ReplyConfig( &message );
        break;
    case Backup__Debug__C__ReplyConfig__Debug__A__Ac__ReplyConfig:
        currentState = state_____Backup__Debug__C__ReplyConfig__Debug__A__Ac__ReplyConfig( &message );
        break;
    case Backup__Debug__C__ReplyConfig__boundary:
        currentState = state_____Backup__Debug__C__ReplyConfig__boundary( &message );
        break;
    case Backup__Debug__C__backtoslave1__Debug__B__Ac__backtoslave1:
        currentState = state_____Backup__Debug__C__backtoslave1__Debug__B__Ac__backtoslave1( &message );
        break;
    case Backup__Debug__C__backtoslave1__Debug__A__Ac__backtoslave1:
        currentState = state_____Backup__Debug__C__backtoslave1__Debug__A__Ac__backtoslave1( &message );
        break;
    case Backup__Debug__C__backtoslave1__boundary:
        currentState = state_____Backup__Debug__C__backtoslave1__boundary( &message );
        break;
    case Backup__Debug__C__KeepAliveMsg__Debug__B__Ex__RunAsSlave:
        currentState = state_____Backup__Debug__C__KeepAliveMsg__Debug__B__Ex__RunAsSlave( &message );
        break;
    case Backup__Debug__C__KeepAliveMsg__Debug__B__Ac__KeepAliveMsg:
        currentState = state_____Backup__Debug__C__KeepAliveMsg__Debug__B__Ac__KeepAliveMsg( &message );
        break;
    case Backup__Debug__C__KeepAliveMsg__Debug__A__Ac__KeepAliveMsg:
        currentState = state_____Backup__Debug__C__KeepAliveMsg__Debug__A__Ac__KeepAliveMsg( &message );
        break;
    case Backup__Debug__C__KeepAliveMsg__Debug__A__En__RunAsSlave:
        currentState = state_____Backup__Debug__C__KeepAliveMsg__Debug__A__En__RunAsSlave( &message );
        break;
    case Backup__Debug__C__KeepAliveMsg__boundary:
        currentState = state_____Backup__Debug__C__KeepAliveMsg__boundary( &message );
        break;
    case Backup__Debug__C__CheckNoMaster__Debug__B__Ac__CheckNoMaster:
        currentState = state_____Backup__Debug__C__CheckNoMaster__Debug__B__Ac__CheckNoMaster( &message );
        break;
    case Backup__Debug__C__CheckNoMaster__Debug__A__Ac__CheckNoMaster:
        currentState = state_____Backup__Debug__C__CheckNoMaster__Debug__A__Ac__CheckNoMaster( &message );
        break;
    case Backup__Debug__C__CheckNoMaster__boundary:
        currentState = state_____Backup__Debug__C__CheckNoMaster__boundary( &message );
        break;
    case Backup__Debug__C__NokeepAlive__Debug__B__Ex__RunAsSlave:
        currentState = state_____Backup__Debug__C__NokeepAlive__Debug__B__Ex__RunAsSlave( &message );
        break;
    case Backup__Debug__C__NokeepAlive__Debug__B__Ac__NokeepAlive:
        currentState = state_____Backup__Debug__C__NokeepAlive__Debug__B__Ac__NokeepAlive( &message );
        break;
    case Backup__Debug__C__NokeepAlive__Debug__A__Ac__NokeepAlive:
        currentState = state_____Backup__Debug__C__NokeepAlive__Debug__A__Ac__NokeepAlive( &message );
        break;
    case Backup__Debug__C__NokeepAlive__Debug__A__En__TryBeMaster:
        currentState = state_____Backup__Debug__C__NokeepAlive__Debug__A__En__TryBeMaster( &message );
        break;
    case Backup__Debug__C__NokeepAlive__boundary:
        currentState = state_____Backup__Debug__C__NokeepAlive__boundary( &message );
        break;
    case Debug__C__initTimer__Debug__B__Ac__initTimer:
        currentState = state_____Debug__C__initTimer__Debug__B__Ac__initTimer( &message );
        break;
    case Debug__C__initTimer__Debug__A__Ac__initTimer:
        currentState = state_____Debug__C__initTimer__Debug__A__Ac__initTimer( &message );
        break;
    case Debug__C__initTimer__Debug__A__En__initTimer:
        currentState = state_____Debug__C__initTimer__Debug__A__En__initTimer( &message );
        break;
    case Debug__C__initTimer__boundary:
        currentState = state_____Debug__C__initTimer__boundary( &message );
        break;
    case Debug__C__ServerFaliure__Debug__B__Ex__RunAsMaster:
        currentState = state_____Debug__C__ServerFaliure__Debug__B__Ex__RunAsMaster( &message );
        break;
    case Debug__C__ServerFaliure__Debug__B__Ac__ServerFaliure:
        currentState = state_____Debug__C__ServerFaliure__Debug__B__Ac__ServerFaliure( &message );
        break;
    case Debug__C__ServerFaliure__Debug__A__Ac__ServerFaliure:
        currentState = state_____Debug__C__ServerFaliure__Debug__A__Ac__ServerFaliure( &message );
        break;
    case Debug__C__ServerFaliure__Debug__A__En__Failure:
        currentState = state_____Debug__C__ServerFaliure__Debug__A__En__Failure( &message );
        break;
    case Debug__C__ServerFaliure__boundary:
        currentState = state_____Debug__C__ServerFaliure__boundary( &message );
        break;
    case Debug__C__BeSlave__Debug__B__Ac__BeSlave:
        currentState = state_____Debug__C__BeSlave__Debug__B__Ac__BeSlave( &message );
        break;
    case Debug__C__BeSlave__Debug__A__Ac__BeSlave:
        currentState = state_____Debug__C__BeSlave__Debug__A__Ac__BeSlave( &message );
        break;
    case Debug__C__BeSlave__Debug__A__En__BeSlave:
        currentState = state_____Debug__C__BeSlave__Debug__A__En__BeSlave( &message );
        break;
    case Debug__C__BeSlave__boundary:
        currentState = state_____Debug__C__BeSlave__boundary( &message );
        break;
    case Debug__C__Init__StandBy__3__Debug__B__Ac__Init__StandBy__3:
        currentState = state_____Debug__C__Init__StandBy__3__Debug__B__Ac__Init__StandBy__3( &message );
        break;
    case Debug__C__Init__StandBy__3__Debug__A__Ac__Init__StandBy__3:
        currentState = state_____Debug__C__Init__StandBy__3__Debug__A__Ac__Init__StandBy__3( &message );
        break;
    case Debug__C__Init__StandBy__3__Debug__A__En__Init__StandBy__3:
        currentState = state_____Debug__C__Init__StandBy__3__Debug__A__En__Init__StandBy__3( &message );
        break;
    case Debug__C__Init__StandBy__3__boundary:
        currentState = state_____Debug__C__Init__StandBy__3__boundary( &message );
        break;
    case Debug__C__Recover__Debug__B__Ex__Failure:
        currentState = state_____Debug__C__Recover__Debug__B__Ex__Failure( &message );
        break;
    case Debug__C__Recover__Debug__B__Ac__Recover:
        currentState = state_____Debug__C__Recover__Debug__B__Ac__Recover( &message );
        break;
    case Debug__C__Recover__Debug__A__Ac__Recover:
        currentState = state_____Debug__C__Recover__Debug__A__Ac__Recover( &message );
        break;
    case Debug__C__Recover__boundary:
        currentState = state_____Debug__C__Recover__boundary( &message );
        break;
    case Debug__C__ActiveMode__Debug__B__Ac__ActiveMode:
        currentState = state_____Debug__C__ActiveMode__Debug__B__Ac__ActiveMode( &message );
        break;
    case Debug__C__ActiveMode__Debug__A__Ac__ActiveMode:
        currentState = state_____Debug__C__ActiveMode__Debug__A__Ac__ActiveMode( &message );
        break;
    case Debug__C__ActiveMode__boundary:
        currentState = state_____Debug__C__ActiveMode__boundary( &message );
        break;
    case Debug__C__ExitPoint1__BeMaster__4__Debug__B__Ac__ExitPoint1__BeMaster__4:
        currentState = state_____Debug__C__ExitPoint1__BeMaster__4__Debug__B__Ac__ExitPoint1__BeMaster__4( &message );
        break;
    case Debug__C__ExitPoint1__BeMaster__4__Debug__A__Ac__ExitPoint1__BeMaster__4:
        currentState = state_____Debug__C__ExitPoint1__BeMaster__4__Debug__A__Ac__ExitPoint1__BeMaster__4( &message );
        break;
    case Debug__C__ExitPoint1__BeMaster__4__boundary:
        currentState = state_____Debug__C__ExitPoint1__BeMaster__4__boundary( &message );
        break;
    case Debug__C__KeepAlive__Debug__B__Ex__RunAsMaster:
        currentState = state_____Debug__C__KeepAlive__Debug__B__Ex__RunAsMaster( &message );
        break;
    case Debug__C__KeepAlive__Debug__B__Ac__KeepAlive:
        currentState = state_____Debug__C__KeepAlive__Debug__B__Ac__KeepAlive( &message );
        break;
    case Debug__C__KeepAlive__Debug__A__Ac__KeepAlive:
        currentState = state_____Debug__C__KeepAlive__Debug__A__Ac__KeepAlive( &message );
        break;
    case Debug__C__KeepAlive__Debug__A__En__RunAsMaster:
        currentState = state_____Debug__C__KeepAlive__Debug__A__En__RunAsMaster( &message );
        break;
    case Debug__C__KeepAlive__boundary:
        currentState = state_____Debug__C__KeepAlive__boundary( &message );
        break;
    case Debug__C__BeingMaster__Debug__B__Ac__BeingMaster:
        currentState = state_____Debug__C__BeingMaster__Debug__B__Ac__BeingMaster( &message );
        break;
    case Debug__C__BeingMaster__Debug__A__Ac__BeingMaster:
        currentState = state_____Debug__C__BeingMaster__Debug__A__Ac__BeingMaster( &message );
        break;
    case Debug__C__BeingMaster__Debug__A__En__BeingMaster:
        currentState = state_____Debug__C__BeingMaster__Debug__A__En__BeingMaster( &message );
        break;
    case Debug__C__BeingMaster__boundary:
        currentState = state_____Debug__C__BeingMaster__boundary( &message );
        break;
    case Debug__C__purgeotherMessage__Debug__B__Ex__Failure:
        currentState = state_____Debug__C__purgeotherMessage__Debug__B__Ex__Failure( &message );
        break;
    case Debug__C__purgeotherMessage__Debug__B__Ac__purgeotherMessage:
        currentState = state_____Debug__C__purgeotherMessage__Debug__B__Ac__purgeotherMessage( &message );
        break;
    case Debug__C__purgeotherMessage__Debug__A__Ac__purgeotherMessage:
        currentState = state_____Debug__C__purgeotherMessage__Debug__A__Ac__purgeotherMessage( &message );
        break;
    case Debug__C__purgeotherMessage__Debug__A__En__Failure:
        currentState = state_____Debug__C__purgeotherMessage__Debug__A__En__Failure( &message );
        break;
    case Debug__C__purgeotherMessage__boundary:
        currentState = state_____Debug__C__purgeotherMessage__boundary( &message );
        break;
    case Debug__C__StandBy__CheckConfig__5__Debug__B__Ex__StandBy:
        currentState = state_____Debug__C__StandBy__CheckConfig__5__Debug__B__Ex__StandBy( &message );
        break;
    case Debug__C__StandBy__CheckConfig__5__Debug__B__Ac__StandBy__CheckConfig__5:
        currentState = state_____Debug__C__StandBy__CheckConfig__5__Debug__B__Ac__StandBy__CheckConfig__5( &message );
        break;
    case Debug__C__StandBy__CheckConfig__5__Debug__A__Ac__StandBy__CheckConfig__5:
        currentState = state_____Debug__C__StandBy__CheckConfig__5__Debug__A__Ac__StandBy__CheckConfig__5( &message );
        break;
    case Debug__C__StandBy__CheckConfig__5__boundary:
        currentState = state_____Debug__C__StandBy__CheckConfig__5__boundary( &message );
        break;
    case Debug__C__PassiveMode__Debug__B__Ac__PassiveMode:
        currentState = state_____Debug__C__PassiveMode__Debug__B__Ac__PassiveMode( &message );
        break;
    case Debug__C__PassiveMode__Debug__A__Ac__PassiveMode:
        currentState = state_____Debug__C__PassiveMode__Debug__A__Ac__PassiveMode( &message );
        break;
    case Debug__C__PassiveMode__Debug__A__En__PassiveMode:
        currentState = state_____Debug__C__PassiveMode__Debug__A__En__PassiveMode( &message );
        break;
    case Debug__C__PassiveMode__boundary:
        currentState = state_____Debug__C__PassiveMode__boundary( &message );
        break;
    default:
        break;
    }
}

void Capsule_Server::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Debug__InitDebug( &message );
    currentState = Debug__InitState;
}

const char * Capsule_Server::getCurrentStateString() const
{
    return stateNames[currentState];
}





void Capsule_Server::save_history( Capsule_Server::State compositeState, Capsule_Server::State subState )
{
    history[compositeState] = subState;
}

bool Capsule_Server::check_history( Capsule_Server::State compositeState, Capsule_Server::State subState )
{
    return history[compositeState] == subState;
}

void Capsule_Server::entryaction_____Backup( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup entry  */
    if( not Debug__SRO.checkDebug("Backup",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__BackToSlave__Debug__A__Ac__BackToSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__BackToSlave::Debug__A__Ac__BackToSlave entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__BackToSlave::Region1::Debug__A__Ac__BackToSlave",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("BackToSlave","","",3,TransitionEffectBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__BackToSlave__Debug__B__Ac__BackToSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__BackToSlave::Debug__B__Ac__BackToSlave entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__BackToSlave::Region1::Debug__B__Ac__BackToSlave",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("TryBeMaster","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("BackToSlave","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__BackToSlave__Debug__B__Ex__TryBeMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__BackToSlave::Debug__B__Ex__TryBeMaster entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__BackToSlave::Region1::Debug__B__Ex__TryBeMaster",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("TryBeMaster","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__BackToSlave__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__CheckNoMaster__Debug__A__Ac__CheckNoMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__CheckNoMaster::Debug__A__Ac__CheckNoMaster entry  */
    if (not(Debug__SRO.checkDebug("CheckNoMaster","","",3,TransitionEffectBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__CheckNoMaster__Debug__B__Ac__CheckNoMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__CheckNoMaster::Debug__B__Ac__CheckNoMaster entry  */
    if (not(Debug__SRO.checkDebug("CheckNoMaster","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__CheckNoMaster__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__Ac__Initial1__RunAsSlave__2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__Initial1__RunAsSlave__2::Debug__A__Ac__Initial1__RunAsSlave__2 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__Initial1__RunAsSlave__2::Region1::Debug__A__Ac__Initial1__RunAsSlave__2",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Initial1__RunAsSlave__2","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("RunAsSlave","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__En__Initial1__RunAsSlave__2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__Initial1__RunAsSlave__2::Debug__A__En__Initial1__RunAsSlave__2 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__Initial1__RunAsSlave__2::Region1::Debug__A__En__Initial1__RunAsSlave__2",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("RunAsSlave","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__B__Ac__Initial1__RunAsSlave__2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__Initial1__RunAsSlave__2::Debug__B__Ac__Initial1__RunAsSlave__2 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__Initial1__RunAsSlave__2::Region1::Debug__B__Ac__Initial1__RunAsSlave__2",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Initial1__RunAsSlave__2","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__Initial1__RunAsSlave__2__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__KeepAliveMsg__Debug__A__Ac__KeepAliveMsg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__KeepAliveMsg::Debug__A__Ac__KeepAliveMsg entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__KeepAliveMsg::Region1::Debug__A__Ac__KeepAliveMsg",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("KeepAliveMsg","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("RunAsSlave","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__KeepAliveMsg__Debug__A__En__RunAsSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__KeepAliveMsg::Debug__A__En__RunAsSlave entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__KeepAliveMsg::Region1::Debug__A__En__RunAsSlave",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("RunAsSlave","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__KeepAliveMsg__Debug__B__Ac__KeepAliveMsg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__KeepAliveMsg::Debug__B__Ac__KeepAliveMsg entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__KeepAliveMsg::Region1::Debug__B__Ac__KeepAliveMsg",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("RunAsSlave","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("KeepAliveMsg","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__KeepAliveMsg__Debug__B__Ex__RunAsSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__KeepAliveMsg::Debug__B__Ex__RunAsSlave entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__KeepAliveMsg::Region1::Debug__B__Ex__RunAsSlave",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("RunAsSlave","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__KeepAliveMsg__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__NokeepAlive__Debug__A__Ac__NokeepAlive( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__NokeepAlive::Debug__A__Ac__NokeepAlive entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__NokeepAlive::Region1::Debug__A__Ac__NokeepAlive",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("NokeepAlive","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("TryBeMaster","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__NokeepAlive__Debug__A__En__TryBeMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__NokeepAlive::Debug__A__En__TryBeMaster entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__NokeepAlive::Region1::Debug__A__En__TryBeMaster",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("TryBeMaster","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__NokeepAlive__Debug__B__Ac__NokeepAlive( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__NokeepAlive::Debug__B__Ac__NokeepAlive entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__NokeepAlive::Region1::Debug__B__Ac__NokeepAlive",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("RunAsSlave","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("NokeepAlive","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__NokeepAlive__Debug__B__Ex__RunAsSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__NokeepAlive::Debug__B__Ex__RunAsSlave entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__NokeepAlive::Region1::Debug__B__Ex__RunAsSlave",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("RunAsSlave","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__NokeepAlive__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__ReplyConfig__Debug__A__Ac__ReplyConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__ReplyConfig::Debug__A__Ac__ReplyConfig entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__ReplyConfig::Region1::Debug__A__Ac__ReplyConfig",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("ReplyConfig","","",3,TransitionEffectBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__ReplyConfig__Debug__B__Ac__ReplyConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__ReplyConfig::Debug__B__Ac__ReplyConfig entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__ReplyConfig::Region1::Debug__B__Ac__ReplyConfig",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("TryBeMaster","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("ReplyConfig","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__ReplyConfig__Debug__B__Ex__TryBeMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__ReplyConfig::Debug__B__Ex__TryBeMaster entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__ReplyConfig::Region1::Debug__B__Ex__TryBeMaster",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("TryBeMaster","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__ReplyConfig__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__backtoslave1__Debug__A__Ac__backtoslave1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__backtoslave1::Debug__A__Ac__backtoslave1 entry  */
    if (not(Debug__SRO.checkDebug("backtoslave1","","",3,TransitionEffectBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__backtoslave1__Debug__B__Ac__backtoslave1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__backtoslave1::Debug__B__Ac__backtoslave1 entry  */
    if (not(Debug__SRO.checkDebug("backtoslave1","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__backtoslave1__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__backtoslave__Debug__A__Ac__backtoslave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__backtoslave::Debug__A__Ac__backtoslave entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__backtoslave::Region1::Debug__A__Ac__backtoslave",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("backtoslave","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("RunAsSlave","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__backtoslave__Debug__A__En__backtoslave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__backtoslave::Debug__A__En__backtoslave entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__backtoslave::Region1::Debug__A__En__backtoslave",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("RunAsSlave","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__backtoslave__Debug__B__Ac__backtoslave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__backtoslave::Debug__B__Ac__backtoslave entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__backtoslave::Region1::Debug__B__Ac__backtoslave",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("backtoslave","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__Debug__C__backtoslave__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__RunAsSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::RunAsSlave entry  */
    if( not Debug__SRO.checkDebug("RunAsSlave",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::RunAsSlave",(char *)"",(char *)"",(char *)"");
    std::cout<<this->getName()<<": Running as Slave now\n";
    //if (KeepAliveTimerId.isValid())
    //	KeepAliveTimer.cancelTimer(KeepAliveTimerId);
    KeepAliveTimerId=KeepAliveTimer.informIn(UMLRTTimespec(6,0),4);
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__TryBeMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::TryBeMaster entry  */
    if( not Debug__SRO.checkDebug("TryBeMaster",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::TryBeMaster",(char *)"",(char *)"",(char *)"");
    //std::cout<<this->getName()<<": trying to Be Master ------------\n";
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__ActiveMode__Debug__A__Ac__ActiveMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__ActiveMode::Debug__A__Ac__ActiveMode entry  */
    if (not(Debug__SRO.checkDebug("ActiveMode","","",3,TransitionEffectBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__ActiveMode__Debug__B__Ac__ActiveMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__ActiveMode::Debug__B__Ac__ActiveMode entry  */
    if (not(Debug__SRO.checkDebug("ActiveMode","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__ActiveMode__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__BeSlave__Debug__A__Ac__BeSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__BeSlave::Debug__A__Ac__BeSlave entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__BeSlave::Region1::Debug__A__Ac__BeSlave",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("BeSlave","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("Backup","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__BeSlave__Debug__A__En__BeSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__BeSlave::Debug__A__En__BeSlave entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__BeSlave::Region1::Debug__A__En__BeSlave",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Backup","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__BeSlave__Debug__B__Ac__BeSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__BeSlave::Debug__B__Ac__BeSlave entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__BeSlave::Region1::Debug__B__Ac__BeSlave",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("BeSlave","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__BeSlave__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__BeingMaster__Debug__A__Ac__BeingMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__BeingMaster::Debug__A__Ac__BeingMaster entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__BeingMaster::Region1::Debug__A__Ac__BeingMaster",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("BeingMaster","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("RunAsMaster","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__BeingMaster__Debug__A__En__BeingMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__BeingMaster::Debug__A__En__BeingMaster entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__BeingMaster::Region1::Debug__A__En__BeingMaster",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("RunAsMaster","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__BeingMaster__Debug__B__Ac__BeingMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__BeingMaster::Debug__B__Ac__BeingMaster entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__BeingMaster::Region1::Debug__B__Ac__BeingMaster",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("BeingMaster","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__BeingMaster__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__ExitPoint1__BeMaster__4__Debug__A__Ac__ExitPoint1__BeMaster__4( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__ExitPoint1__BeMaster__4::Debug__A__Ac__ExitPoint1__BeMaster__4 entry  */
    if (not(Debug__SRO.checkDebug("ExitPoint1__BeMaster__4","","",3,TransitionEffectBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__ExitPoint1__BeMaster__4__Debug__B__Ac__ExitPoint1__BeMaster__4( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__ExitPoint1__BeMaster__4::Debug__B__Ac__ExitPoint1__BeMaster__4 entry  */
    if (not(Debug__SRO.checkDebug("ExitPoint1__BeMaster__4","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__ExitPoint1__BeMaster__4__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__Init__StandBy__3__Debug__A__Ac__Init__StandBy__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__Init__StandBy__3::Debug__A__Ac__Init__StandBy__3 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__Init__StandBy__3::Region1::Debug__A__Ac__Init__StandBy__3",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Init__StandBy__3","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("StandBy","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__Init__StandBy__3__Debug__A__En__Init__StandBy__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__Init__StandBy__3::Debug__A__En__Init__StandBy__3 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__Init__StandBy__3::Region1::Debug__A__En__Init__StandBy__3",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("StandBy","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__Init__StandBy__3__Debug__B__Ac__Init__StandBy__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__Init__StandBy__3::Debug__B__Ac__Init__StandBy__3 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__Init__StandBy__3::Region1::Debug__B__Ac__Init__StandBy__3",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Init__StandBy__3","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__Init__StandBy__3__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__KeepAlive__Debug__A__Ac__KeepAlive( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__KeepAlive::Debug__A__Ac__KeepAlive entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__KeepAlive::Region1::Debug__A__Ac__KeepAlive",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("KeepAlive","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("RunAsMaster","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__KeepAlive__Debug__A__En__RunAsMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__KeepAlive::Debug__A__En__RunAsMaster entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__KeepAlive::Region1::Debug__A__En__RunAsMaster",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("RunAsMaster","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__KeepAlive__Debug__B__Ac__KeepAlive( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__KeepAlive::Debug__B__Ac__KeepAlive entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__KeepAlive::Region1::Debug__B__Ac__KeepAlive",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("RunAsMaster","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("KeepAlive","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__KeepAlive__Debug__B__Ex__RunAsMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__KeepAlive::Debug__B__Ex__RunAsMaster entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__KeepAlive::Region1::Debug__B__Ex__RunAsMaster",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("RunAsMaster","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__KeepAlive__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__MasterAnnounce( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__MasterAnnounce entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__PassiveMode__Debug__A__Ac__PassiveMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__PassiveMode::Debug__A__Ac__PassiveMode entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__PassiveMode::Region1::Debug__A__Ac__PassiveMode",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("PassiveMode","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("Backup","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__PassiveMode__Debug__A__En__PassiveMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__PassiveMode::Debug__A__En__PassiveMode entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__PassiveMode::Region1::Debug__A__En__PassiveMode",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Backup","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__PassiveMode__Debug__B__Ac__PassiveMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__PassiveMode::Debug__B__Ac__PassiveMode entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__PassiveMode::Region1::Debug__B__Ac__PassiveMode",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("PassiveMode","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__PassiveMode__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__Recover__Debug__A__Ac__Recover( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__Recover::Debug__A__Ac__Recover entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__Recover::Region1::Debug__A__Ac__Recover",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Recover","","",3,TransitionEffectBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__Recover__Debug__B__Ac__Recover( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__Recover::Debug__B__Ac__Recover entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__Recover::Region1::Debug__B__Ac__Recover",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Failure","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("Recover","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__Recover__Debug__B__Ex__Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__Recover::Debug__B__Ex__Failure entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__Recover::Region1::Debug__B__Ex__Failure",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Failure","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__Recover__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__ServerFaliure__Debug__A__Ac__ServerFaliure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__ServerFaliure::Debug__A__Ac__ServerFaliure entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__ServerFaliure::Region1::Debug__A__Ac__ServerFaliure",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("ServerFaliure","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("Failure","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__ServerFaliure__Debug__A__En__Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__ServerFaliure::Debug__A__En__Failure entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__ServerFaliure::Region1::Debug__A__En__Failure",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Failure","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__ServerFaliure__Debug__B__Ac__ServerFaliure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__ServerFaliure::Debug__B__Ac__ServerFaliure entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__ServerFaliure::Region1::Debug__B__Ac__ServerFaliure",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("RunAsMaster","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("ServerFaliure","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__ServerFaliure__Debug__B__Ex__RunAsMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__ServerFaliure::Debug__B__Ex__RunAsMaster entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__ServerFaliure::Region1::Debug__B__Ex__RunAsMaster",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("RunAsMaster","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__ServerFaliure__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__ServiceRequest( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__ServiceRequest entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__StandBy__CheckConfig__5__Debug__A__Ac__StandBy__CheckConfig__5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__StandBy__CheckConfig__5::Debug__A__Ac__StandBy__CheckConfig__5 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__StandBy__CheckConfig__5::Region1::Debug__A__Ac__StandBy__CheckConfig__5",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("StandBy__CheckConfig__5","","",3,TransitionEffectBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__StandBy__CheckConfig__5__Debug__B__Ac__StandBy__CheckConfig__5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__StandBy__CheckConfig__5::Debug__B__Ac__StandBy__CheckConfig__5 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__StandBy__CheckConfig__5::Region1::Debug__B__Ac__StandBy__CheckConfig__5",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("StandBy","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("StandBy__CheckConfig__5","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__StandBy__CheckConfig__5__Debug__B__Ex__StandBy( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__StandBy__CheckConfig__5::Debug__B__Ex__StandBy entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__StandBy__CheckConfig__5::Region1::Debug__B__Ex__StandBy",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("StandBy","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__StandBy__CheckConfig__5__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__initTimer__Debug__A__Ac__initTimer( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__initTimer::Debug__A__Ac__initTimer entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__initTimer::Region1::Debug__A__Ac__initTimer",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("initTimer","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("RunAsMaster","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__initTimer__Debug__A__En__initTimer( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__initTimer::Debug__A__En__initTimer entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__initTimer::Region1::Debug__A__En__initTimer",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("RunAsMaster","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__initTimer__Debug__B__Ac__initTimer( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__initTimer::Debug__B__Ac__initTimer entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__initTimer::Region1::Debug__B__Ac__initTimer",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("initTimer","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__initTimer__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__purgeotherMessage__Debug__A__Ac__purgeotherMessage( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__purgeotherMessage::Debug__A__Ac__purgeotherMessage entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__purgeotherMessage::Region1::Debug__A__Ac__purgeotherMessage",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("purgeotherMessage","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("Failure","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__purgeotherMessage__Debug__A__En__Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__purgeotherMessage::Debug__A__En__Failure entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__purgeotherMessage::Region1::Debug__A__En__Failure",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Failure","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__purgeotherMessage__Debug__B__Ac__purgeotherMessage( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__purgeotherMessage::Debug__B__Ac__purgeotherMessage entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__purgeotherMessage::Region1::Debug__B__Ac__purgeotherMessage",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Failure","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("purgeotherMessage","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__purgeotherMessage__Debug__B__Ex__Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__purgeotherMessage::Debug__B__Ex__Failure entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__purgeotherMessage::Region1::Debug__B__Ex__Failure",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Failure","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__C__purgeotherMessage__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::entryaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__InitState entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Failure entry  */
    if( not Debug__SRO.checkDebug("Failure",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Failure",(char *)"",(char *)"",(char *)"");
    //------
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____RunAsMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::RunAsMaster entry  */
    if( not Debug__SRO.checkDebug("RunAsMaster",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::RunAsMaster",(char *)"",(char *)"",(char *)"");
    std::cout<<this->getName()<<": Run as Master now\n";
    ConfigComm.IAMMaster((char *)this->getName()).send();
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____StandBy( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::StandBy entry  */
    if( not Debug__SRO.checkDebug("StandBy",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::StandBy",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup exit  */
    if( not Debug__SRO.checkDebug("Backup",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__BackToSlave__Debug__A__Ac__BackToSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__BackToSlave::Debug__A__Ac__BackToSlave exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__BackToSlave::Region1::Debug__A__Ac__BackToSlave",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__BackToSlave__Debug__B__Ac__BackToSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__BackToSlave::Debug__B__Ac__BackToSlave exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__BackToSlave::Region1::Debug__B__Ac__BackToSlave",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__BackToSlave__Debug__B__Ex__TryBeMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__BackToSlave::Debug__B__Ex__TryBeMaster exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__BackToSlave::Region1::Debug__B__Ex__TryBeMaster",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__BackToSlave__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__CheckNoMaster__Debug__A__Ac__CheckNoMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__CheckNoMaster::Debug__A__Ac__CheckNoMaster exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__CheckNoMaster__Debug__B__Ac__CheckNoMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__CheckNoMaster::Debug__B__Ac__CheckNoMaster exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__CheckNoMaster__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__Ac__Initial1__RunAsSlave__2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__Initial1__RunAsSlave__2::Debug__A__Ac__Initial1__RunAsSlave__2 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__Initial1__RunAsSlave__2::Region1::Debug__A__Ac__Initial1__RunAsSlave__2",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__En__Initial1__RunAsSlave__2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__Initial1__RunAsSlave__2::Debug__A__En__Initial1__RunAsSlave__2 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__Initial1__RunAsSlave__2::Region1::Debug__A__En__Initial1__RunAsSlave__2",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__B__Ac__Initial1__RunAsSlave__2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__Initial1__RunAsSlave__2::Debug__B__Ac__Initial1__RunAsSlave__2 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__Initial1__RunAsSlave__2::Region1::Debug__B__Ac__Initial1__RunAsSlave__2",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__Initial1__RunAsSlave__2__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__KeepAliveMsg__Debug__A__Ac__KeepAliveMsg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__KeepAliveMsg::Debug__A__Ac__KeepAliveMsg exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__KeepAliveMsg::Region1::Debug__A__Ac__KeepAliveMsg",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__KeepAliveMsg__Debug__A__En__RunAsSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__KeepAliveMsg::Debug__A__En__RunAsSlave exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__KeepAliveMsg::Region1::Debug__A__En__RunAsSlave",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__KeepAliveMsg__Debug__B__Ac__KeepAliveMsg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__KeepAliveMsg::Debug__B__Ac__KeepAliveMsg exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__KeepAliveMsg::Region1::Debug__B__Ac__KeepAliveMsg",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__KeepAliveMsg__Debug__B__Ex__RunAsSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__KeepAliveMsg::Debug__B__Ex__RunAsSlave exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__KeepAliveMsg::Region1::Debug__B__Ex__RunAsSlave",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__KeepAliveMsg__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__NokeepAlive__Debug__A__Ac__NokeepAlive( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__NokeepAlive::Debug__A__Ac__NokeepAlive exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__NokeepAlive::Region1::Debug__A__Ac__NokeepAlive",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__NokeepAlive__Debug__A__En__TryBeMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__NokeepAlive::Debug__A__En__TryBeMaster exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__NokeepAlive::Region1::Debug__A__En__TryBeMaster",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__NokeepAlive__Debug__B__Ac__NokeepAlive( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__NokeepAlive::Debug__B__Ac__NokeepAlive exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__NokeepAlive::Region1::Debug__B__Ac__NokeepAlive",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__NokeepAlive__Debug__B__Ex__RunAsSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__NokeepAlive::Debug__B__Ex__RunAsSlave exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__NokeepAlive::Region1::Debug__B__Ex__RunAsSlave",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__NokeepAlive__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__ReplyConfig__Debug__A__Ac__ReplyConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__ReplyConfig::Debug__A__Ac__ReplyConfig exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__ReplyConfig::Region1::Debug__A__Ac__ReplyConfig",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__ReplyConfig__Debug__B__Ac__ReplyConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__ReplyConfig::Debug__B__Ac__ReplyConfig exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__ReplyConfig::Region1::Debug__B__Ac__ReplyConfig",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__ReplyConfig__Debug__B__Ex__TryBeMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__ReplyConfig::Debug__B__Ex__TryBeMaster exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__ReplyConfig::Region1::Debug__B__Ex__TryBeMaster",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__ReplyConfig__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__backtoslave1__Debug__A__Ac__backtoslave1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__backtoslave1::Debug__A__Ac__backtoslave1 exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__backtoslave1__Debug__B__Ac__backtoslave1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__backtoslave1::Debug__B__Ac__backtoslave1 exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__backtoslave1__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__backtoslave__Debug__A__Ac__backtoslave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__backtoslave::Debug__A__Ac__backtoslave exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__backtoslave::Region1::Debug__A__Ac__backtoslave",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__backtoslave__Debug__A__En__backtoslave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__backtoslave::Debug__A__En__backtoslave exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__backtoslave::Region1::Debug__A__En__backtoslave",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__backtoslave__Debug__B__Ac__backtoslave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__backtoslave::Debug__B__Ac__backtoslave exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__backtoslave::Region1::Debug__B__Ac__backtoslave",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__Debug__C__backtoslave__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__RunAsSlave( const UMLRTMessage * msg )
{
    #define umlrtparam_ServerName ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::RunAsSlave exit  */
    if( not Debug__SRO.checkDebug("RunAsSlave",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::RunAsSlave",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_ServerName
}

void Capsule_Server::exitaction_____Backup__TryBeMaster( const UMLRTMessage * msg )
{
    #define umlrtparam_ServerName ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::TryBeMaster exit  */
    if( not Debug__SRO.checkDebug("TryBeMaster",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::TryBeMaster",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_ServerName
}

void Capsule_Server::exitaction_____Debug__C__ActiveMode__Debug__A__Ac__ActiveMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__ActiveMode::Debug__A__Ac__ActiveMode exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__ActiveMode__Debug__B__Ac__ActiveMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__ActiveMode::Debug__B__Ac__ActiveMode exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__ActiveMode__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__BeSlave__Debug__A__Ac__BeSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__BeSlave::Debug__A__Ac__BeSlave exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__BeSlave::Region1::Debug__A__Ac__BeSlave",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__BeSlave__Debug__A__En__BeSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__BeSlave::Debug__A__En__BeSlave exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__BeSlave::Region1::Debug__A__En__BeSlave",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__BeSlave__Debug__B__Ac__BeSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__BeSlave::Debug__B__Ac__BeSlave exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__BeSlave::Region1::Debug__B__Ac__BeSlave",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__BeSlave__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__BeingMaster__Debug__A__Ac__BeingMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__BeingMaster::Debug__A__Ac__BeingMaster exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__BeingMaster::Region1::Debug__A__Ac__BeingMaster",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__BeingMaster__Debug__A__En__BeingMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__BeingMaster::Debug__A__En__BeingMaster exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__BeingMaster::Region1::Debug__A__En__BeingMaster",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__BeingMaster__Debug__B__Ac__BeingMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__BeingMaster::Debug__B__Ac__BeingMaster exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__BeingMaster::Region1::Debug__B__Ac__BeingMaster",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__BeingMaster__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__ExitPoint1__BeMaster__4__Debug__A__Ac__ExitPoint1__BeMaster__4( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__ExitPoint1__BeMaster__4::Debug__A__Ac__ExitPoint1__BeMaster__4 exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__ExitPoint1__BeMaster__4__Debug__B__Ac__ExitPoint1__BeMaster__4( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__ExitPoint1__BeMaster__4::Debug__B__Ac__ExitPoint1__BeMaster__4 exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__ExitPoint1__BeMaster__4__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__Init__StandBy__3__Debug__A__Ac__Init__StandBy__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__Init__StandBy__3::Debug__A__Ac__Init__StandBy__3 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__Init__StandBy__3::Region1::Debug__A__Ac__Init__StandBy__3",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__Init__StandBy__3__Debug__A__En__Init__StandBy__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__Init__StandBy__3::Debug__A__En__Init__StandBy__3 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__Init__StandBy__3::Region1::Debug__A__En__Init__StandBy__3",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__Init__StandBy__3__Debug__B__Ac__Init__StandBy__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__Init__StandBy__3::Debug__B__Ac__Init__StandBy__3 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__Init__StandBy__3::Region1::Debug__B__Ac__Init__StandBy__3",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__Init__StandBy__3__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__KeepAlive__Debug__A__Ac__KeepAlive( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__KeepAlive::Debug__A__Ac__KeepAlive exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__KeepAlive::Region1::Debug__A__Ac__KeepAlive",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__KeepAlive__Debug__A__En__RunAsMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__KeepAlive::Debug__A__En__RunAsMaster exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__KeepAlive::Region1::Debug__A__En__RunAsMaster",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__KeepAlive__Debug__B__Ac__KeepAlive( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__KeepAlive::Debug__B__Ac__KeepAlive exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__KeepAlive::Region1::Debug__B__Ac__KeepAlive",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__KeepAlive__Debug__B__Ex__RunAsMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__KeepAlive::Debug__B__Ex__RunAsMaster exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__KeepAlive::Region1::Debug__B__Ex__RunAsMaster",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__KeepAlive__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__MasterAnnounce( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__MasterAnnounce exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__PassiveMode__Debug__A__Ac__PassiveMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__PassiveMode::Debug__A__Ac__PassiveMode exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__PassiveMode::Region1::Debug__A__Ac__PassiveMode",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__PassiveMode__Debug__A__En__PassiveMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__PassiveMode::Debug__A__En__PassiveMode exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__PassiveMode::Region1::Debug__A__En__PassiveMode",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__PassiveMode__Debug__B__Ac__PassiveMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__PassiveMode::Debug__B__Ac__PassiveMode exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__PassiveMode::Region1::Debug__B__Ac__PassiveMode",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__PassiveMode__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__Recover__Debug__A__Ac__Recover( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__Recover::Debug__A__Ac__Recover exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__Recover::Region1::Debug__A__Ac__Recover",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__Recover__Debug__B__Ac__Recover( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__Recover::Debug__B__Ac__Recover exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__Recover::Region1::Debug__B__Ac__Recover",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__Recover__Debug__B__Ex__Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__Recover::Debug__B__Ex__Failure exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__Recover::Region1::Debug__B__Ex__Failure",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__Recover__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__ServerFaliure__Debug__A__Ac__ServerFaliure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__ServerFaliure::Debug__A__Ac__ServerFaliure exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__ServerFaliure::Region1::Debug__A__Ac__ServerFaliure",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__ServerFaliure__Debug__A__En__Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__ServerFaliure::Debug__A__En__Failure exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__ServerFaliure::Region1::Debug__A__En__Failure",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__ServerFaliure__Debug__B__Ac__ServerFaliure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__ServerFaliure::Debug__B__Ac__ServerFaliure exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__ServerFaliure::Region1::Debug__B__Ac__ServerFaliure",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__ServerFaliure__Debug__B__Ex__RunAsMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__ServerFaliure::Debug__B__Ex__RunAsMaster exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__ServerFaliure::Region1::Debug__B__Ex__RunAsMaster",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__ServerFaliure__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__ServiceRequest( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__ServiceRequest exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__StandBy__CheckConfig__5__Debug__A__Ac__StandBy__CheckConfig__5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__StandBy__CheckConfig__5::Debug__A__Ac__StandBy__CheckConfig__5 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__StandBy__CheckConfig__5::Region1::Debug__A__Ac__StandBy__CheckConfig__5",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__StandBy__CheckConfig__5__Debug__B__Ac__StandBy__CheckConfig__5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__StandBy__CheckConfig__5::Debug__B__Ac__StandBy__CheckConfig__5 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__StandBy__CheckConfig__5::Region1::Debug__B__Ac__StandBy__CheckConfig__5",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__StandBy__CheckConfig__5__Debug__B__Ex__StandBy( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__StandBy__CheckConfig__5::Debug__B__Ex__StandBy exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__StandBy__CheckConfig__5::Region1::Debug__B__Ex__StandBy",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__StandBy__CheckConfig__5__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__initTimer__Debug__A__Ac__initTimer( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__initTimer::Debug__A__Ac__initTimer exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__initTimer::Region1::Debug__A__Ac__initTimer",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__initTimer__Debug__A__En__initTimer( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__initTimer::Debug__A__En__initTimer exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__initTimer::Region1::Debug__A__En__initTimer",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__initTimer__Debug__B__Ac__initTimer( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__initTimer::Debug__B__Ac__initTimer exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__initTimer::Region1::Debug__B__Ac__initTimer",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__initTimer__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__purgeotherMessage__Debug__A__Ac__purgeotherMessage( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__purgeotherMessage::Debug__A__Ac__purgeotherMessage exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__purgeotherMessage::Region1::Debug__A__Ac__purgeotherMessage",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__purgeotherMessage__Debug__A__En__Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__purgeotherMessage::Debug__A__En__Failure exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__purgeotherMessage::Region1::Debug__A__En__Failure",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__purgeotherMessage__Debug__B__Ac__purgeotherMessage( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__purgeotherMessage::Debug__B__Ac__purgeotherMessage exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__purgeotherMessage::Region1::Debug__B__Ac__purgeotherMessage",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__purgeotherMessage__Debug__B__Ex__Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__purgeotherMessage::Debug__B__Ex__Failure exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__purgeotherMessage::Region1::Debug__B__Ex__Failure",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__C__purgeotherMessage__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Server::exitaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__InitState exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Failure exit  */
    if( not Debug__SRO.checkDebug("Failure",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Failure",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____RunAsMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::RunAsMaster exit  */
    if( not Debug__SRO.checkDebug("RunAsMaster",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::RunAsMaster",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____StandBy( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    #define rtdata ( (const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::StandBy exit  */
    if( not Debug__SRO.checkDebug("StandBy",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::StandBy",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

void Capsule_Server::transitionaction_____ActiveMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__ActiveMode,BeMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::ActiveMode",(char *)"Debug__Path__ActiveMode",(char *)"BeMaster",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__BackToSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__Path__BackToSlave,Backup::Slave */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::BackToSlave",(char *)"Debug__Path__BackToSlave",(char *)"Slave",(char *)"");
    //std::cout<<this->getName()<<": The Master recovered itself, backing to slave mode\n";
    //if (TimerId.isValid())
    //	Timer.cancelTimer(TimerId);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__CheckNoMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__Path__CheckNoMaster,Backup::ExitPoint1 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::CheckNoMaster",(char *)"Debug__Path__CheckNoMaster",(char *)"ExitPoint1",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__BackToSlave( const UMLRTMessage * msg )
{
    #define umlrtparam_ServerName ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::TryBeMaster,Backup::Debug__Path__BackToSlave,IAmAlive */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__BackToSlave",(char *)"TryBeMaster",(char *)"Debug__Path__BackToSlave",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_ServerName
}

void Capsule_Server::transitionaction_____Backup__Debug__BackToSlave__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__C__BackToSlave::ex,Backup::Slave */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__BackToSlave__E",(char *)"ex",(char *)"Slave",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__BackToSlave__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__Path__BackToSlave,Backup::Debug__C__BackToSlave::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__BackToSlave__S",(char *)"Debug__Path__BackToSlave",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__BackToSlave__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__C__BackToSlave::new_exitpoint_2,Backup::Debug__C__BackToSlave */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__BackToSlave__dbg",(char *)"Debug__C__BackToSlave",(char *)"Debug__C__BackToSlave",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__BackToSlave__Debug__AC__BackToSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__BackToSlave transition Backup::Debug__C__BackToSlave::Debug__B__Ac__BackToSlave,Backup::Debug__C__BackToSlave::Debug__A__Ac__BackToSlave,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__BackToSlave::Region1::Debug__AC__BackToSlave",(char *)"Debug__B__Ac__BackToSlave",(char *)"Debug__A__Ac__BackToSlave",(char *)"");
    //std::cout<<this->getName()<<": The Master recovered itself, backing to slave mode\n";
    //if (TimerId.isValid())
    //	Timer.cancelTimer(TimerId);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__BackToSlave__Debug__Ex__TryBeMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__BackToSlave transition Backup::Debug__C__BackToSlave::Debug__B__Ex__TryBeMaster,Backup::Debug__C__BackToSlave::Debug__B__Ac__BackToSlave,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__BackToSlave::Region1::Debug__Ex__TryBeMaster",(char *)"Debug__B__Ex__TryBeMaster",(char *)"Debug__B__Ac__BackToSlave",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__BackToSlave__Debug__end__trans__BackToSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__BackToSlave transition Backup::Debug__C__BackToSlave::Debug__A__Ac__BackToSlave,Backup::Debug__C__BackToSlave::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__BackToSlave::Region1::Debug__end__trans__BackToSlave",(char *)"Debug__A__Ac__BackToSlave",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__Ac__Initial1__RunAsSlave__2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__Initial1__RunAsSlave__2 transition Backup::Debug__C__Initial1__RunAsSlave__2::Debug__B__Ac__Initial1__RunAsSlave__2,Backup::Debug__C__Initial1__RunAsSlave__2::Debug__A__Ac__Initial1__RunAsSlave__2,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__Initial1__RunAsSlave__2::Region1::Debug__Ac__Initial1__RunAsSlave__2",(char *)"Debug__B__Ac__Initial1__RunAsSlave__2",(char *)"Debug__A__Ac__Initial1__RunAsSlave__2",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__En__RunAsSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__Initial1__RunAsSlave__2 transition Backup::Debug__C__Initial1__RunAsSlave__2::Debug__A__Ac__Initial1__RunAsSlave__2,Backup::Debug__C__Initial1__RunAsSlave__2::Debug__A__En__Initial1__RunAsSlave__2,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__Initial1__RunAsSlave__2::Region1::Debug__En__RunAsSlave",(char *)"Debug__A__Ac__Initial1__RunAsSlave__2",(char *)"Debug__A__En__Initial1__RunAsSlave__2",(char *)"");
    std::cout<<this->getName()<<": Running as Slave now\n";
    //if (KeepAliveTimerId.isValid())
    //	KeepAliveTimer.cancelTimer(KeepAliveTimerId);
    KeepAliveTimerId=KeepAliveTimer.informIn(UMLRTTimespec(6,0),4);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__end__trans__Initial1__RunAsSlave__2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__Initial1__RunAsSlave__2 transition Backup::Debug__C__Initial1__RunAsSlave__2::Debug__A__En__Initial1__RunAsSlave__2,Backup::Debug__C__Initial1__RunAsSlave__2::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__Initial1__RunAsSlave__2::Region1::Debug__end__trans__Initial1__RunAsSlave__2",(char *)"Debug__A__En__Initial1__RunAsSlave__2",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__init__trans__Initial1__RunAsSlave__2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__Initial1__RunAsSlave__2 transition Backup::Debug__C__Initial1__RunAsSlave__2::en,Backup::Debug__C__Initial1__RunAsSlave__2::Debug__B__Ac__Initial1__RunAsSlave__2 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__Initial1__RunAsSlave__2::Region1::Debug__init__trans__Initial1__RunAsSlave__2",(char *)"en",(char *)"Debug__B__Ac__Initial1__RunAsSlave__2",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__KeepAliveMsg__Debug__AC__KeepAliveMsg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #define umlrtparam_ServerName ( *(const char * *)msg->getParam( 0 ) ) 
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__KeepAliveMsg transition Backup::Debug__C__KeepAliveMsg::Debug__B__Ac__KeepAliveMsg,Backup::Debug__C__KeepAliveMsg::Debug__A__Ac__KeepAliveMsg,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__KeepAliveMsg::Region1::Debug__AC__KeepAliveMsg",(char *)"Debug__B__Ac__KeepAliveMsg",(char *)"Debug__A__Ac__KeepAliveMsg",(char *)"");
    std::cout<<this->getName()<<": Keep Alive Message from "<< umlrtparam_ServerName<<"\n";
    //if (KeepAliveTimerId.isValid())
    //	KeepAliveTimer.cancelTimer(KeepAliveTimerId);
    //KeepAliveTimerId=KeepAliveTimer.informEvery(UMLRTTimespec(6,0),4);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__KeepAliveMsg__Debug__En__RunAsSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__KeepAliveMsg transition Backup::Debug__C__KeepAliveMsg::Debug__A__Ac__KeepAliveMsg,Backup::Debug__C__KeepAliveMsg::Debug__A__En__RunAsSlave,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__KeepAliveMsg::Region1::Debug__En__RunAsSlave",(char *)"Debug__A__Ac__KeepAliveMsg",(char *)"Debug__A__En__RunAsSlave",(char *)"");
    std::cout<<this->getName()<<": Running as Slave now\n";
    //if (KeepAliveTimerId.isValid())
    //	KeepAliveTimer.cancelTimer(KeepAliveTimerId);
    KeepAliveTimerId=KeepAliveTimer.informIn(UMLRTTimespec(6,0),4);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__KeepAliveMsg__Debug__Ex__RunAsSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__KeepAliveMsg transition Backup::Debug__C__KeepAliveMsg::Debug__B__Ex__RunAsSlave,Backup::Debug__C__KeepAliveMsg::Debug__B__Ac__KeepAliveMsg,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__KeepAliveMsg::Region1::Debug__Ex__RunAsSlave",(char *)"Debug__B__Ex__RunAsSlave",(char *)"Debug__B__Ac__KeepAliveMsg",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__KeepAliveMsg__Debug__end__trans__KeepAliveMsg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__KeepAliveMsg transition Backup::Debug__C__KeepAliveMsg::Debug__A__En__RunAsSlave,Backup::Debug__C__KeepAliveMsg::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__KeepAliveMsg::Region1::Debug__end__trans__KeepAliveMsg",(char *)"Debug__A__En__RunAsSlave",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__KeepAliveMsg__Debug__init__trans__KeepAliveMsg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__KeepAliveMsg transition Backup::Debug__C__KeepAliveMsg::en,Backup::Debug__C__KeepAliveMsg::Debug__B__Ex__RunAsSlave */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__KeepAliveMsg::Region1::Debug__init__trans__KeepAliveMsg",(char *)"en",(char *)"Debug__B__Ex__RunAsSlave",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__NokeepAlive__Debug__AC__NokeepAlive( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__NokeepAlive transition Backup::Debug__C__NokeepAlive::Debug__B__Ac__NokeepAlive,Backup::Debug__C__NokeepAlive::Debug__A__Ac__NokeepAlive,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__NokeepAlive::Region1::Debug__AC__NokeepAlive",(char *)"Debug__B__Ac__NokeepAlive",(char *)"Debug__A__Ac__NokeepAlive",(char *)"");
    //if (KeepAliveTimerId.isValid())
    //	KeepAliveTimer.cancelTimer(KeepAliveTimerId);
    std::cout<<this->getName()<<": No keep Alive message from Master, Try to be Master-------\n";
    //TimerId=Timer.informEvery(UMLRTTimespec(2,0),4);
    ConfigComm.QueryConfig().send();
    //std::cout<<this->getName()<<": trying to be Master\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__NokeepAlive__Debug__En__TryBeMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__NokeepAlive transition Backup::Debug__C__NokeepAlive::Debug__A__Ac__NokeepAlive,Backup::Debug__C__NokeepAlive::Debug__A__En__TryBeMaster,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__NokeepAlive::Region1::Debug__En__TryBeMaster",(char *)"Debug__A__Ac__NokeepAlive",(char *)"Debug__A__En__TryBeMaster",(char *)"");
    //std::cout<<this->getName()<<": trying to Be Master ------------\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__NokeepAlive__Debug__Ex__RunAsSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__NokeepAlive transition Backup::Debug__C__NokeepAlive::Debug__B__Ex__RunAsSlave,Backup::Debug__C__NokeepAlive::Debug__B__Ac__NokeepAlive,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__NokeepAlive::Region1::Debug__Ex__RunAsSlave",(char *)"Debug__B__Ex__RunAsSlave",(char *)"Debug__B__Ac__NokeepAlive",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__NokeepAlive__Debug__end__trans__NokeepAlive( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__NokeepAlive transition Backup::Debug__C__NokeepAlive::Debug__A__En__TryBeMaster,Backup::Debug__C__NokeepAlive::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__NokeepAlive::Region1::Debug__end__trans__NokeepAlive",(char *)"Debug__A__En__TryBeMaster",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__NokeepAlive__Debug__init__trans__NokeepAlive( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__NokeepAlive transition Backup::Debug__C__NokeepAlive::en,Backup::Debug__C__NokeepAlive::Debug__B__Ex__RunAsSlave */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__NokeepAlive::Region1::Debug__init__trans__NokeepAlive",(char *)"en",(char *)"Debug__B__Ex__RunAsSlave",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__ReplyConfig__Debug__AC__ReplyConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__ReplyConfig transition Backup::Debug__C__ReplyConfig::Debug__B__Ac__ReplyConfig,Backup::Debug__C__ReplyConfig::Debug__A__Ac__ReplyConfig,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__ReplyConfig::Region1::Debug__AC__ReplyConfig",(char *)"Debug__B__Ac__ReplyConfig",(char *)"Debug__A__Ac__ReplyConfig",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__ReplyConfig__Debug__Ex__TryBeMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__ReplyConfig transition Backup::Debug__C__ReplyConfig::Debug__B__Ex__TryBeMaster,Backup::Debug__C__ReplyConfig::Debug__B__Ac__ReplyConfig,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__ReplyConfig::Region1::Debug__Ex__TryBeMaster",(char *)"Debug__B__Ex__TryBeMaster",(char *)"Debug__B__Ac__ReplyConfig",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__ReplyConfig__Debug__end__trans__ReplyConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__ReplyConfig transition Backup::Debug__C__ReplyConfig::Debug__A__Ac__ReplyConfig,Backup::Debug__C__ReplyConfig::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__ReplyConfig::Region1::Debug__end__trans__ReplyConfig",(char *)"Debug__A__Ac__ReplyConfig",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__backtoslave__Debug__Ac__backtoslave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__backtoslave transition Backup::Debug__C__backtoslave::Debug__B__Ac__backtoslave,Backup::Debug__C__backtoslave::Debug__A__Ac__backtoslave,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__backtoslave::Region1::Debug__Ac__backtoslave",(char *)"Debug__B__Ac__backtoslave",(char *)"Debug__A__Ac__backtoslave",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__backtoslave__Debug__En__RunAsSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__backtoslave transition Backup::Debug__C__backtoslave::Debug__A__Ac__backtoslave,Backup::Debug__C__backtoslave::Debug__A__En__backtoslave,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__backtoslave::Region1::Debug__En__RunAsSlave",(char *)"Debug__A__Ac__backtoslave",(char *)"Debug__A__En__backtoslave",(char *)"");
    std::cout<<this->getName()<<": Running as Slave now\n";
    //if (KeepAliveTimerId.isValid())
    //	KeepAliveTimer.cancelTimer(KeepAliveTimerId);
    KeepAliveTimerId=KeepAliveTimer.informIn(UMLRTTimespec(6,0),4);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__backtoslave__Debug__end__trans__backtoslave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__backtoslave transition Backup::Debug__C__backtoslave::Debug__A__En__backtoslave,Backup::Debug__C__backtoslave::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__backtoslave::Region1::Debug__end__trans__backtoslave",(char *)"Debug__A__En__backtoslave",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__C__backtoslave__Debug__init__trans__backtoslave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup::Debug__C__backtoslave transition Backup::Debug__C__backtoslave::en,Backup::Debug__C__backtoslave::Debug__B__Ac__backtoslave */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__C__backtoslave::Region1::Debug__init__trans__backtoslave",(char *)"en",(char *)"Debug__B__Ac__backtoslave",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__CheckNoMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Choice2,Backup::Debug__Path__CheckNoMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__CheckNoMaster",(char *)"Choice2",(char *)"Debug__Path__CheckNoMaster",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__CheckNoMaster__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__C__CheckNoMaster::ex,Backup::ExitPoint1 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__CheckNoMaster__E",(char *)"ex",(char *)"ExitPoint1",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__CheckNoMaster__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__Path__CheckNoMaster,Backup::Debug__C__CheckNoMaster::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__CheckNoMaster__S",(char *)"Debug__Path__CheckNoMaster",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__CheckNoMaster__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__C__CheckNoMaster::new_exitpoint_7,Backup::Debug__C__CheckNoMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__CheckNoMaster__dbg",(char *)"Debug__C__CheckNoMaster",(char *)"Debug__C__CheckNoMaster",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__Initial1__RunAsSlave__2__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__C__Initial1__RunAsSlave__2::ex,Backup::RunAsSlave */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__Initial1__RunAsSlave__2__E",(char *)"ex",(char *)"RunAsSlave",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__Initial1__RunAsSlave__2__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__Path__Initial1__RunAsSlave__2,Backup::Debug__C__Initial1__RunAsSlave__2::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__Initial1__RunAsSlave__2__S",(char *)"Debug__Path__Initial1__RunAsSlave__2",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__Initial1__RunAsSlave__2__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__C__Initial1__RunAsSlave__2::new_exitpoint_1,Backup::Debug__C__Initial1__RunAsSlave__2 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__Initial1__RunAsSlave__2__dbg",(char *)"Debug__C__Initial1__RunAsSlave__2",(char *)"Debug__C__Initial1__RunAsSlave__2",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__KeepAliveMsg( const UMLRTMessage * msg )
{
    #define umlrtparam_ServerName ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::RunAsSlave,Backup::Debug__Path__KeepAliveMsg,IAmAlive:Slave */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__KeepAliveMsg",(char *)"RunAsSlave",(char *)"Debug__Path__KeepAliveMsg",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_ServerName
}

void Capsule_Server::transitionaction_____Backup__Debug__KeepAliveMsg__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__C__KeepAliveMsg::ex,Backup::RunAsSlave */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__KeepAliveMsg__E",(char *)"ex",(char *)"RunAsSlave",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__KeepAliveMsg__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__Path__KeepAliveMsg,Backup::Debug__C__KeepAliveMsg::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__KeepAliveMsg__S",(char *)"Debug__Path__KeepAliveMsg",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__KeepAliveMsg__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__C__KeepAliveMsg::new_exitpoint_6,Backup::Debug__C__KeepAliveMsg */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__KeepAliveMsg__dbg",(char *)"Debug__C__KeepAliveMsg",(char *)"Debug__C__KeepAliveMsg",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__NokeepAlive( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::RunAsSlave,Backup::Debug__Path__NokeepAlive,timeout:KeepAliveTimer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__NokeepAlive",(char *)"RunAsSlave",(char *)"Debug__Path__NokeepAlive",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__NokeepAlive__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__C__NokeepAlive::ex,Backup::TryBeMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__NokeepAlive__E",(char *)"ex",(char *)"TryBeMaster",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__NokeepAlive__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__Path__NokeepAlive,Backup::Debug__C__NokeepAlive::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__NokeepAlive__S",(char *)"Debug__Path__NokeepAlive",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__NokeepAlive__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__C__NokeepAlive::new_exitpoint_8,Backup::Debug__C__NokeepAlive */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__NokeepAlive__dbg",(char *)"Debug__C__NokeepAlive",(char *)"Debug__C__NokeepAlive",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__ReplyConfig( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    #define rtdata ( (const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::TryBeMaster,Backup::Debug__Path__ReplyConfig,ReplyConfig:ConfigComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__ReplyConfig",(char *)"TryBeMaster",(char *)"Debug__Path__ReplyConfig",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

void Capsule_Server::transitionaction_____Backup__Debug__ReplyConfig__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__C__ReplyConfig::ex,Backup::Choice2 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__ReplyConfig__E",(char *)"ex",(char *)"Choice2",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__ReplyConfig__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__Path__ReplyConfig,Backup::Debug__C__ReplyConfig::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__ReplyConfig__S",(char *)"Debug__Path__ReplyConfig",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__ReplyConfig__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__C__ReplyConfig::new_exitpoint_4,Backup::Debug__C__ReplyConfig */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__ReplyConfig__dbg",(char *)"Debug__C__ReplyConfig",(char *)"Debug__C__ReplyConfig",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__backtoslave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Slave,Backup::Debug__Path__backtoslave */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__backtoslave",(char *)"Slave",(char *)"Debug__Path__backtoslave",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__backtoslave1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Choice2,Backup::Debug__Path__backtoslave1 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__backtoslave1",(char *)"Choice2",(char *)"Debug__Path__backtoslave1",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__backtoslave1__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__C__backtoslave1::ex,Backup::Slave */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__backtoslave1__E",(char *)"ex",(char *)"Slave",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__backtoslave1__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__Path__backtoslave1,Backup::Debug__C__backtoslave1::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__backtoslave1__S",(char *)"Debug__Path__backtoslave1",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__backtoslave1__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__C__backtoslave1::new_exitpoint_5,Backup::Debug__C__backtoslave1 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__backtoslave1__dbg",(char *)"Debug__C__backtoslave1",(char *)"Debug__C__backtoslave1",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__backtoslave__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__C__backtoslave::ex,Backup::RunAsSlave */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__backtoslave__E",(char *)"ex",(char *)"RunAsSlave",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__backtoslave__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__Path__backtoslave,Backup::Debug__C__backtoslave::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__backtoslave__S",(char *)"Debug__Path__backtoslave",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Debug__backtoslave__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__C__backtoslave::new_exitpoint_3,Backup::Debug__C__backtoslave */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__backtoslave__dbg",(char *)"Debug__C__backtoslave",(char *)"Debug__C__backtoslave",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__Initial1__RunAsSlave__2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__Path__Initial1__RunAsSlave__2,Backup::RunAsSlave */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Initial1__RunAsSlave__2",(char *)"Debug__Path__Initial1__RunAsSlave__2",(char *)"RunAsSlave",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__KeepAliveMsg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
     #define umlrtparam_ServerName ( *(const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__Path__KeepAliveMsg,Backup::RunAsSlave */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::KeepAliveMsg",(char *)"Debug__Path__KeepAliveMsg",(char *)"RunAsSlave",(char *)"");
    std::cout<<this->getName()<<": Keep Alive Message from "<< umlrtparam_ServerName<<"\n";
    //if (KeepAliveTimerId.isValid())
    //	KeepAliveTimer.cancelTimer(KeepAliveTimerId);
    //KeepAliveTimerId=KeepAliveTimer.informEvery(UMLRTTimespec(6,0),4);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__NokeepAlive( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__Path__NokeepAlive,Backup::TryBeMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::NokeepAlive",(char *)"Debug__Path__NokeepAlive",(char *)"TryBeMaster",(char *)"");
    //if (KeepAliveTimerId.isValid())
    //	KeepAliveTimer.cancelTimer(KeepAliveTimerId);
    std::cout<<this->getName()<<": No keep Alive message from Master, Try to be Master-------\n";
    //TimerId=Timer.informEvery(UMLRTTimespec(2,0),4);
    ConfigComm.QueryConfig().send();
    //std::cout<<this->getName()<<": trying to be Master\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__ReplyConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__Path__ReplyConfig,Backup::Choice2 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::ReplyConfig",(char *)"Debug__Path__ReplyConfig",(char *)"Choice2",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__backtoslave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__Path__backtoslave,Backup::RunAsSlave */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::backtoslave",(char *)"Debug__Path__backtoslave",(char *)"RunAsSlave",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__backtoslave1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::Debug__Path__backtoslave1,Backup::Slave */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::backtoslave1",(char *)"Debug__Path__backtoslave1",(char *)"Slave",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Backup__new_transition_11( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup,Backup::Debug__Path__Initial1__RunAsSlave__2 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Backup::Region1::Debug__Initial1__RunAsSlave__2",(char *)"Initial1",(char *)"Debug__Path__Initial1__RunAsSlave__2",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____BeSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__BeSlave,Backup */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::BeSlave",(char *)"Debug__Path__BeSlave",(char *)"Backup",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____BeingMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__BeingMaster,RunAsMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::BeingMaster",(char *)"Debug__Path__BeingMaster",(char *)"RunAsMaster",(char *)"");
    int r=random()%30+5;
    std::cout<<this->getName()<<": will go fail state after "<< r << "second\n";
    TimerId=Timer.informEvery(UMLRTTimespec(r,0),4);
    KeepAliveTimerId=KeepAliveTimer.informEvery(UMLRTTimespec(KeepAliveTimeOut,0),4);
    AnnouncementTimerId=MasterAnnounceTimer.informEvery(UMLRTTimespec(AnnouncementTimeOut,0),4);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__ActiveMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Choice1,Debug__Path__ActiveMode */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__ActiveMode",(char *)"Choice1",(char *)"Debug__Path__ActiveMode",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__ActiveMode__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__ActiveMode::ex,BeMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__ActiveMode__E",(char *)"ex",(char *)"BeMaster",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__ActiveMode__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__ActiveMode,Debug__C__ActiveMode::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__ActiveMode__S",(char *)"Debug__Path__ActiveMode",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__ActiveMode__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__ActiveMode::new_exitpoint_14,Debug__C__ActiveMode */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__ActiveMode__dbg",(char *)"Debug__C__ActiveMode",(char *)"Debug__C__ActiveMode",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__BeSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition CheckConfig,Debug__Path__BeSlave */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__BeSlave",(char *)"CheckConfig",(char *)"Debug__Path__BeSlave",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__BeSlave__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__BeSlave::ex,Backup */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__BeSlave__E",(char *)"ex",(char *)"Backup",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__BeSlave__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__BeSlave,Debug__C__BeSlave::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__BeSlave__S",(char *)"Debug__Path__BeSlave",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__BeSlave__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__BeSlave::new_exitpoint_11,Debug__C__BeSlave */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__BeSlave__dbg",(char *)"Debug__C__BeSlave",(char *)"Debug__C__BeSlave",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__BeingMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition BeMaster,Debug__Path__BeingMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__BeingMaster",(char *)"BeMaster",(char *)"Debug__Path__BeingMaster",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__BeingMaster__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__BeingMaster::ex,RunAsMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__BeingMaster__E",(char *)"ex",(char *)"RunAsMaster",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__BeingMaster__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__BeingMaster,Debug__C__BeingMaster::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__BeingMaster__S",(char *)"Debug__Path__BeingMaster",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__BeingMaster__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__BeingMaster::new_exitpoint_17,Debug__C__BeingMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__BeingMaster__dbg",(char *)"Debug__C__BeingMaster",(char *)"Debug__C__BeingMaster",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__BeSlave__Debug__Ac__BeSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__BeSlave transition Debug__C__BeSlave::Debug__B__Ac__BeSlave,Debug__C__BeSlave::Debug__A__Ac__BeSlave,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__BeSlave::Region1::Debug__Ac__BeSlave",(char *)"Debug__B__Ac__BeSlave",(char *)"Debug__A__Ac__BeSlave",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__BeSlave__Debug__En__Backup( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__BeSlave transition Debug__C__BeSlave::Debug__A__Ac__BeSlave,Debug__C__BeSlave::Debug__A__En__BeSlave,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__BeSlave::Region1::Debug__En__Backup",(char *)"Debug__A__Ac__BeSlave",(char *)"Debug__A__En__BeSlave",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__BeSlave__Debug__end__trans__BeSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__BeSlave transition Debug__C__BeSlave::Debug__A__En__BeSlave,Debug__C__BeSlave::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__BeSlave::Region1::Debug__end__trans__BeSlave",(char *)"Debug__A__En__BeSlave",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__BeSlave__Debug__init__trans__BeSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__BeSlave transition Debug__C__BeSlave::en,Debug__C__BeSlave::Debug__B__Ac__BeSlave */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__BeSlave::Region1::Debug__init__trans__BeSlave",(char *)"en",(char *)"Debug__B__Ac__BeSlave",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__BeingMaster__Debug__Ac__BeingMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__BeingMaster transition Debug__C__BeingMaster::Debug__B__Ac__BeingMaster,Debug__C__BeingMaster::Debug__A__Ac__BeingMaster,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__BeingMaster::Region1::Debug__Ac__BeingMaster",(char *)"Debug__B__Ac__BeingMaster",(char *)"Debug__A__Ac__BeingMaster",(char *)"");
    int r=random()%30+5;
    std::cout<<this->getName()<<": will go fail state after "<< r << "second\n";
    TimerId=Timer.informEvery(UMLRTTimespec(r,0),4);
    KeepAliveTimerId=KeepAliveTimer.informEvery(UMLRTTimespec(KeepAliveTimeOut,0),4);
    AnnouncementTimerId=MasterAnnounceTimer.informEvery(UMLRTTimespec(AnnouncementTimeOut,0),4);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__BeingMaster__Debug__En__RunAsMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__BeingMaster transition Debug__C__BeingMaster::Debug__A__Ac__BeingMaster,Debug__C__BeingMaster::Debug__A__En__BeingMaster,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__BeingMaster::Region1::Debug__En__RunAsMaster",(char *)"Debug__A__Ac__BeingMaster",(char *)"Debug__A__En__BeingMaster",(char *)"");
    std::cout<<this->getName()<<": Run as Master now\n";
    ConfigComm.IAMMaster((char *)this->getName()).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__BeingMaster__Debug__end__trans__BeingMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__BeingMaster transition Debug__C__BeingMaster::Debug__A__En__BeingMaster,Debug__C__BeingMaster::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__BeingMaster::Region1::Debug__end__trans__BeingMaster",(char *)"Debug__A__En__BeingMaster",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__BeingMaster__Debug__init__trans__BeingMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__BeingMaster transition Debug__C__BeingMaster::en,Debug__C__BeingMaster::Debug__B__Ac__BeingMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__BeingMaster::Region1::Debug__init__trans__BeingMaster",(char *)"en",(char *)"Debug__B__Ac__BeingMaster",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__Init__StandBy__3__Debug__Ac__Init__StandBy__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__Init__StandBy__3 transition Debug__C__Init__StandBy__3::Debug__B__Ac__Init__StandBy__3,Debug__C__Init__StandBy__3::Debug__A__Ac__Init__StandBy__3,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__Init__StandBy__3::Region1::Debug__Ac__Init__StandBy__3",(char *)"Debug__B__Ac__Init__StandBy__3",(char *)"Debug__A__Ac__Init__StandBy__3",(char *)"");
    std::cout<<this->getName()<<this->getIndex()<<": Intialization\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__Init__StandBy__3__Debug__En__StandBy( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__Init__StandBy__3 transition Debug__C__Init__StandBy__3::Debug__A__Ac__Init__StandBy__3,Debug__C__Init__StandBy__3::Debug__A__En__Init__StandBy__3,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__Init__StandBy__3::Region1::Debug__En__StandBy",(char *)"Debug__A__Ac__Init__StandBy__3",(char *)"Debug__A__En__Init__StandBy__3",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__Init__StandBy__3__Debug__end__trans__Init__StandBy__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__Init__StandBy__3 transition Debug__C__Init__StandBy__3::Debug__A__En__Init__StandBy__3,Debug__C__Init__StandBy__3::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__Init__StandBy__3::Region1::Debug__end__trans__Init__StandBy__3",(char *)"Debug__A__En__Init__StandBy__3",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__Init__StandBy__3__Debug__init__trans__Init__StandBy__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__Init__StandBy__3 transition Debug__C__Init__StandBy__3::en,Debug__C__Init__StandBy__3::Debug__B__Ac__Init__StandBy__3 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__Init__StandBy__3::Region1::Debug__init__trans__Init__StandBy__3",(char *)"en",(char *)"Debug__B__Ac__Init__StandBy__3",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__KeepAlive__Debug__AC__KeepAlive( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__KeepAlive transition Debug__C__KeepAlive::Debug__B__Ac__KeepAlive,Debug__C__KeepAlive::Debug__A__Ac__KeepAlive,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__KeepAlive::Region1::Debug__AC__KeepAlive",(char *)"Debug__B__Ac__KeepAlive",(char *)"Debug__A__Ac__KeepAlive",(char *)"");
    if (KeepAliveTimerId.isValid())
    KeepAliveTimer.cancelTimer(KeepAliveTimerId);
    KeepAliveTimerId=KeepAliveTimer.informEvery(UMLRTTimespec(KeepAliveTimeOut,0),4);
    if (config.RunningMode==1)
    Master.IAmAlive((char *)this->getName()).send();
    std::cout<<"Master: Keep Alive is sent\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__KeepAlive__Debug__En__RunAsMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__KeepAlive transition Debug__C__KeepAlive::Debug__A__Ac__KeepAlive,Debug__C__KeepAlive::Debug__A__En__RunAsMaster,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__KeepAlive::Region1::Debug__En__RunAsMaster",(char *)"Debug__A__Ac__KeepAlive",(char *)"Debug__A__En__RunAsMaster",(char *)"");
    std::cout<<this->getName()<<": Run as Master now\n";
    ConfigComm.IAMMaster((char *)this->getName()).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__KeepAlive__Debug__Ex__RunAsMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__KeepAlive transition Debug__C__KeepAlive::Debug__B__Ex__RunAsMaster,Debug__C__KeepAlive::Debug__B__Ac__KeepAlive,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__KeepAlive::Region1::Debug__Ex__RunAsMaster",(char *)"Debug__B__Ex__RunAsMaster",(char *)"Debug__B__Ac__KeepAlive",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__KeepAlive__Debug__end__trans__KeepAlive( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__KeepAlive transition Debug__C__KeepAlive::Debug__A__En__RunAsMaster,Debug__C__KeepAlive::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__KeepAlive::Region1::Debug__end__trans__KeepAlive",(char *)"Debug__A__En__RunAsMaster",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__KeepAlive__Debug__init__trans__KeepAlive( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__KeepAlive transition Debug__C__KeepAlive::en,Debug__C__KeepAlive::Debug__B__Ex__RunAsMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__KeepAlive::Region1::Debug__init__trans__KeepAlive",(char *)"en",(char *)"Debug__B__Ex__RunAsMaster",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__PassiveMode__Debug__Ac__PassiveMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__PassiveMode transition Debug__C__PassiveMode::Debug__B__Ac__PassiveMode,Debug__C__PassiveMode::Debug__A__Ac__PassiveMode,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__PassiveMode::Region1::Debug__Ac__PassiveMode",(char *)"Debug__B__Ac__PassiveMode",(char *)"Debug__A__Ac__PassiveMode",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__PassiveMode__Debug__En__Backup( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__PassiveMode transition Debug__C__PassiveMode::Debug__A__Ac__PassiveMode,Debug__C__PassiveMode::Debug__A__En__PassiveMode,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__PassiveMode::Region1::Debug__En__Backup",(char *)"Debug__A__Ac__PassiveMode",(char *)"Debug__A__En__PassiveMode",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__PassiveMode__Debug__end__trans__PassiveMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__PassiveMode transition Debug__C__PassiveMode::Debug__A__En__PassiveMode,Debug__C__PassiveMode::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__PassiveMode::Region1::Debug__end__trans__PassiveMode",(char *)"Debug__A__En__PassiveMode",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__PassiveMode__Debug__init__trans__PassiveMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__PassiveMode transition Debug__C__PassiveMode::en,Debug__C__PassiveMode::Debug__B__Ac__PassiveMode */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__PassiveMode::Region1::Debug__init__trans__PassiveMode",(char *)"en",(char *)"Debug__B__Ac__PassiveMode",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__Recover__Debug__AC__Recover( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__Recover transition Debug__C__Recover::Debug__B__Ac__Recover,Debug__C__Recover::Debug__A__Ac__Recover,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__Recover::Region1::Debug__AC__Recover",(char *)"Debug__B__Ac__Recover",(char *)"Debug__A__Ac__Recover",(char *)"");
    std::cout<<this->getName()<<": is recovering\n";
    if (TimerId.isValid())
    Timer.cancelTimer(TimerId);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__Recover__Debug__Ex__Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__Recover transition Debug__C__Recover::Debug__B__Ex__Failure,Debug__C__Recover::Debug__B__Ac__Recover,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__Recover::Region1::Debug__Ex__Failure",(char *)"Debug__B__Ex__Failure",(char *)"Debug__B__Ac__Recover",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__Recover__Debug__end__trans__Recover( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__Recover transition Debug__C__Recover::Debug__A__Ac__Recover,Debug__C__Recover::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__Recover::Region1::Debug__end__trans__Recover",(char *)"Debug__A__Ac__Recover",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__ServerFaliure__Debug__AC__ServerFaliure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__ServerFaliure transition Debug__C__ServerFaliure::Debug__B__Ac__ServerFaliure,Debug__C__ServerFaliure::Debug__A__Ac__ServerFaliure,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__ServerFaliure::Region1::Debug__AC__ServerFaliure",(char *)"Debug__B__Ac__ServerFaliure",(char *)"Debug__A__Ac__ServerFaliure",(char *)"");
    if (KeepAliveTimerId.isValid())
    KeepAliveTimer.cancelTimer(KeepAliveTimerId);
    if (AnnouncementTimerId.isValid())
    MasterAnnounceTimer.cancelTimer(AnnouncementTimerId);
    if (TimerId.isValid())
    Timer.cancelTimer(TimerId);
    int r=random()%30+5;
    Timer.informEvery(UMLRTTimespec(r,0),4);
    std::cout<<this->getName()<<": Failure,  will recover after " << r << " seconds\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__ServerFaliure__Debug__En__Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__ServerFaliure transition Debug__C__ServerFaliure::Debug__A__Ac__ServerFaliure,Debug__C__ServerFaliure::Debug__A__En__Failure,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__ServerFaliure::Region1::Debug__En__Failure",(char *)"Debug__A__Ac__ServerFaliure",(char *)"Debug__A__En__Failure",(char *)"");
    //------
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__ServerFaliure__Debug__Ex__RunAsMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__ServerFaliure transition Debug__C__ServerFaliure::Debug__B__Ex__RunAsMaster,Debug__C__ServerFaliure::Debug__B__Ac__ServerFaliure,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__ServerFaliure::Region1::Debug__Ex__RunAsMaster",(char *)"Debug__B__Ex__RunAsMaster",(char *)"Debug__B__Ac__ServerFaliure",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__ServerFaliure__Debug__end__trans__ServerFaliure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__ServerFaliure transition Debug__C__ServerFaliure::Debug__A__En__Failure,Debug__C__ServerFaliure::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__ServerFaliure::Region1::Debug__end__trans__ServerFaliure",(char *)"Debug__A__En__Failure",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__ServerFaliure__Debug__init__trans__ServerFaliure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__ServerFaliure transition Debug__C__ServerFaliure::en,Debug__C__ServerFaliure::Debug__B__Ex__RunAsMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__ServerFaliure::Region1::Debug__init__trans__ServerFaliure",(char *)"en",(char *)"Debug__B__Ex__RunAsMaster",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__StandBy__CheckConfig__5__Debug__AC__StandBy__CheckConfig__5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__StandBy__CheckConfig__5 transition Debug__C__StandBy__CheckConfig__5::Debug__B__Ac__StandBy__CheckConfig__5,Debug__C__StandBy__CheckConfig__5::Debug__A__Ac__StandBy__CheckConfig__5,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__StandBy__CheckConfig__5::Region1::Debug__AC__StandBy__CheckConfig__5",(char *)"Debug__B__Ac__StandBy__CheckConfig__5",(char *)"Debug__A__Ac__StandBy__CheckConfig__5",(char *)"");
    std::cout<<this->getName()<<": StartingUp\n";
    this->config=umlrtparam_config;
    std::cout<<this->getName()<<": Configuration is:"<< config.RunningMode<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__StandBy__CheckConfig__5__Debug__Ex__StandBy( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__StandBy__CheckConfig__5 transition Debug__C__StandBy__CheckConfig__5::Debug__B__Ex__StandBy,Debug__C__StandBy__CheckConfig__5::Debug__B__Ac__StandBy__CheckConfig__5,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__StandBy__CheckConfig__5::Region1::Debug__Ex__StandBy",(char *)"Debug__B__Ex__StandBy",(char *)"Debug__B__Ac__StandBy__CheckConfig__5",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__StandBy__CheckConfig__5__Debug__end__trans__StandBy__CheckConfig__5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__StandBy__CheckConfig__5 transition Debug__C__StandBy__CheckConfig__5::Debug__A__Ac__StandBy__CheckConfig__5,Debug__C__StandBy__CheckConfig__5::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__StandBy__CheckConfig__5::Region1::Debug__end__trans__StandBy__CheckConfig__5",(char *)"Debug__A__Ac__StandBy__CheckConfig__5",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__initTimer__Debug__Ac__initTimer( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__initTimer transition Debug__C__initTimer::Debug__B__Ac__initTimer,Debug__C__initTimer::Debug__A__Ac__initTimer,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__initTimer::Region1::Debug__Ac__initTimer",(char *)"Debug__B__Ac__initTimer",(char *)"Debug__A__Ac__initTimer",(char *)"");
    int r=random()%30+5;
    std::cout<<this->getName()<<": will go fail state after "<< r << "second\n";
    TimerId=Timer.informEvery(UMLRTTimespec(r,0),4);
    KeepAliveTimerId=KeepAliveTimer.informEvery(UMLRTTimespec(KeepAliveTimeOut,0),4);
    AnnouncementTimerId=MasterAnnounceTimer.informEvery(UMLRTTimespec(AnnouncementTimeOut,0),4);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__initTimer__Debug__En__RunAsMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__initTimer transition Debug__C__initTimer::Debug__A__Ac__initTimer,Debug__C__initTimer::Debug__A__En__initTimer,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__initTimer::Region1::Debug__En__RunAsMaster",(char *)"Debug__A__Ac__initTimer",(char *)"Debug__A__En__initTimer",(char *)"");
    std::cout<<this->getName()<<": Run as Master now\n";
    ConfigComm.IAMMaster((char *)this->getName()).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__initTimer__Debug__end__trans__initTimer( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__initTimer transition Debug__C__initTimer::Debug__A__En__initTimer,Debug__C__initTimer::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__initTimer::Region1::Debug__end__trans__initTimer",(char *)"Debug__A__En__initTimer",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__initTimer__Debug__init__trans__initTimer( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__initTimer transition Debug__C__initTimer::en,Debug__C__initTimer::Debug__B__Ac__initTimer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__initTimer::Region1::Debug__init__trans__initTimer",(char *)"en",(char *)"Debug__B__Ac__initTimer",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__purgeotherMessage__Debug__AC__purgeotherMessage( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__purgeotherMessage transition Debug__C__purgeotherMessage::Debug__B__Ac__purgeotherMessage,Debug__C__purgeotherMessage::Debug__A__Ac__purgeotherMessage,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__purgeotherMessage::Region1::Debug__AC__purgeotherMessage",(char *)"Debug__B__Ac__purgeotherMessage",(char *)"Debug__A__Ac__purgeotherMessage",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__purgeotherMessage__Debug__En__Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__purgeotherMessage transition Debug__C__purgeotherMessage::Debug__A__Ac__purgeotherMessage,Debug__C__purgeotherMessage::Debug__A__En__Failure,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__purgeotherMessage::Region1::Debug__En__Failure",(char *)"Debug__A__Ac__purgeotherMessage",(char *)"Debug__A__En__Failure",(char *)"");
    //------
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__purgeotherMessage__Debug__Ex__Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__purgeotherMessage transition Debug__C__purgeotherMessage::Debug__B__Ex__Failure,Debug__C__purgeotherMessage::Debug__B__Ac__purgeotherMessage,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__purgeotherMessage::Region1::Debug__Ex__Failure",(char *)"Debug__B__Ex__Failure",(char *)"Debug__B__Ac__purgeotherMessage",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__purgeotherMessage__Debug__end__trans__purgeotherMessage( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__purgeotherMessage transition Debug__C__purgeotherMessage::Debug__A__En__Failure,Debug__C__purgeotherMessage::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__purgeotherMessage::Region1::Debug__end__trans__purgeotherMessage",(char *)"Debug__A__En__Failure",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__C__purgeotherMessage__Debug__init__trans__purgeotherMessage( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Debug__C__purgeotherMessage transition Debug__C__purgeotherMessage::en,Debug__C__purgeotherMessage::Debug__B__Ex__Failure */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__C__purgeotherMessage::Region1::Debug__init__trans__purgeotherMessage",(char *)"en",(char *)"Debug__B__Ex__Failure",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__ExitPoint1__BeMaster__4( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Backup::ExitPoint1,Debug__Path__ExitPoint1__BeMaster__4 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__ExitPoint1__BeMaster__4",(char *)"ExitPoint1",(char *)"Debug__Path__ExitPoint1__BeMaster__4",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__ExitPoint1__BeMaster__4__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__ExitPoint1__BeMaster__4::ex,BeMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__ExitPoint1__BeMaster__4__E",(char *)"ex",(char *)"BeMaster",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__ExitPoint1__BeMaster__4__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__ExitPoint1__BeMaster__4,Debug__C__ExitPoint1__BeMaster__4::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__ExitPoint1__BeMaster__4__S",(char *)"Debug__Path__ExitPoint1__BeMaster__4",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__ExitPoint1__BeMaster__4__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__ExitPoint1__BeMaster__4::new_exitpoint_15,Debug__C__ExitPoint1__BeMaster__4 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__ExitPoint1__BeMaster__4__dbg",(char *)"Debug__C__ExitPoint1__BeMaster__4",(char *)"Debug__C__ExitPoint1__BeMaster__4",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__InitDebug( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Init,Debug__InitState */
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

void Capsule_Server::transitionaction_____Debug__Init__StandBy__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__InitState,Debug__Path__Init__StandBy__3,null:extComm */
    if (this->Debug__SRO.getExecMode()==Stepping){
    Debug__SRO.addTransitionsFromState("Choice1","ActiveMode","BeMaster","","");
    Debug__SRO.addTransitionsFromState("ExitPoint1","","BeMaster","","");
    Debug__SRO.addTransitionsFromState("RunAsSlave","KeepAliveMsg","RunAsSlave","IAmAlive","FailOver");
    Debug__SRO.addTransitionsFromState("RunAsSlave","NokeepAlive","TryBeMaster","timeout","Timing");
    Debug__SRO.addTransitionsFromState("RunAsMaster","KeepAlive","RunAsMaster","timeout","Timing");
    Debug__SRO.addTransitionsFromState("StandBy","","CheckConfig","StartUp","Config");
    Debug__SRO.addTransitionsFromState("TryBeMaster","ReplyConfig","Choice2","ReplyConfig","Config");
    Debug__SRO.addTransitionsFromState("Choice1","PassiveMode","Backup","","");
    Debug__SRO.addTransitionsFromState("Slave","backtoslave","RunAsSlave","","");
    Debug__SRO.addTransitionsFromState("RunAsMaster","ServerFaliure","Failure","timeout","Timing");
    Debug__SRO.addTransitionsFromState("BeMaster","BeingMaster","RunAsMaster","","");
    Debug__SRO.addTransitionsFromState("CheckConfig","initTimer","RunAsMaster","","");
    Debug__SRO.addTransitionsFromState("Failure","purgeotherMessage","Failure","*","Services");
    Debug__SRO.addTransitionsFromState("Failure","purgeotherMessage","Failure","*","FailOver");
    Debug__SRO.addTransitionsFromState("Init","","StandBy","","");
    Debug__SRO.addTransitionsFromState("RunAsMaster","MasterAnnounce","RunAsMaster","timeout","Timing");
    Debug__SRO.addTransitionsFromState("Failure","Recover","Choice1","timeout","Timing");
    Debug__SRO.addTransitionsFromState("Choice2","CheckNoMaster","ExitPoint1","","");
    Debug__SRO.addTransitionsFromState("init","","WaitForEcho","","");
    Debug__SRO.addTransitionsFromState("WaitForEcho","DoEcho","WaitForEcho","Echo","Echo");
    Debug__SRO.addTransitionsFromState("Initial1","","RunAsSlave","","");
    Debug__SRO.addTransitionsFromState("RunAsMaster","ServiceRequest","RunAsMaster","Request","Services");
    Debug__SRO.addTransitionsFromState("Choice2","backtoslave1","Slave","","");
    Debug__SRO.addTransitionsFromState("CheckConfig","BeSlave","Backup","","");
    std::cout<<this->getName()<<": Connection with debugger is in progress\n";
    char  tempS[256];
    sprintf(tempS,"%s%d",this->getName(),(int)this->getIndex());
    extComm.registerToControl(tempS).send();
    Debug__sendEvent(debugEvents::DEBUG,debugEvents::REGISTER,this->getName(),this->getIndex(),msg->getSignalName(),(char *) "",(char *) "",(char *) "",(char *)"",(char *) "");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__Init__StandBy__3__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__Init__StandBy__3::ex,StandBy */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__Init__StandBy__3__E",(char *)"ex",(char *)"StandBy",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__Init__StandBy__3__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__Init__StandBy__3,Debug__C__Init__StandBy__3::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__Init__StandBy__3__S",(char *)"Debug__Path__Init__StandBy__3",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__Init__StandBy__3__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__Init__StandBy__3::new_exitpoint_12,Debug__C__Init__StandBy__3 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__Init__StandBy__3__dbg",(char *)"Debug__C__Init__StandBy__3",(char *)"Debug__C__Init__StandBy__3",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__KeepAlive( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition RunAsMaster,Debug__Path__KeepAlive,timeout:KeepAliveTimer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__KeepAlive",(char *)"RunAsMaster",(char *)"Debug__Path__KeepAlive",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__KeepAlive__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__KeepAlive::ex,RunAsMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__KeepAlive__E",(char *)"ex",(char *)"RunAsMaster",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__KeepAlive__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__KeepAlive,Debug__C__KeepAlive::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__KeepAlive__S",(char *)"Debug__Path__KeepAlive",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__KeepAlive__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__KeepAlive::new_exitpoint_16,Debug__C__KeepAlive */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__KeepAlive__dbg",(char *)"Debug__C__KeepAlive",(char *)"Debug__C__KeepAlive",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__MasterAnnounce( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition RunAsMaster,Debug__Path__MasterAnnounce,timeout:MasterAnnounceTimer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__MasterAnnounce",(char *)"RunAsMaster",(char *)"Debug__Path__MasterAnnounce",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__MasterAnnounce__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__MasterAnnounce,RunAsMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__MasterAnnounce__E",(char *)"ex",(char *)"RunAsMaster",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__MasterAnnounce__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__MasterAnnounce,Debug__C__MasterAnnounce */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__MasterAnnounce__S",(char *)"Debug__Path__MasterAnnounce",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__MasterAnnounce__dbg( const UMLRTMessage * msg )
{
    #define umlrtparam_varName ( *(const char * *)msg->getParam( 0 ) )
    #define umlrtparam_varValue ( *(const char * *)msg->getParam( 1 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__MasterAnnounce,Debug__C__MasterAnnounce,dbgVarChange:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__MasterAnnounce__dbg",(char *)"Debug__C__MasterAnnounce",(char *)"Debug__C__MasterAnnounce",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_varValue
    #undef umlrtparam_varName
}

void Capsule_Server::transitionaction_____Debug__PassiveMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Choice1,Debug__Path__PassiveMode */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__PassiveMode",(char *)"Choice1",(char *)"Debug__Path__PassiveMode",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__PassiveMode__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__PassiveMode::ex,Backup */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__PassiveMode__E",(char *)"ex",(char *)"Backup",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__PassiveMode__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__PassiveMode,Debug__C__PassiveMode::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__PassiveMode__S",(char *)"Debug__Path__PassiveMode",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__PassiveMode__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__PassiveMode::new_exitpoint_20,Debug__C__PassiveMode */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__PassiveMode__dbg",(char *)"Debug__C__PassiveMode",(char *)"Debug__C__PassiveMode",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__Recover( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Failure,Debug__Path__Recover,timeout:Timer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__Recover",(char *)"Failure",(char *)"Debug__Path__Recover",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__Recover__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__Recover::ex,Choice1 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__Recover__E",(char *)"ex",(char *)"Choice1",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__Recover__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__Recover,Debug__C__Recover::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__Recover__S",(char *)"Debug__Path__Recover",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__Recover__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__Recover::new_exitpoint_13,Debug__C__Recover */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__Recover__dbg",(char *)"Debug__C__Recover",(char *)"Debug__C__Recover",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__ServerFaliure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition RunAsMaster,Debug__Path__ServerFaliure,timeout:Timer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__ServerFaliure",(char *)"RunAsMaster",(char *)"Debug__Path__ServerFaliure",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__ServerFaliure__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__ServerFaliure::ex,Failure */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__ServerFaliure__E",(char *)"ex",(char *)"Failure",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__ServerFaliure__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__ServerFaliure,Debug__C__ServerFaliure::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__ServerFaliure__S",(char *)"Debug__Path__ServerFaliure",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__ServerFaliure__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__ServerFaliure::new_exitpoint_10,Debug__C__ServerFaliure */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__ServerFaliure__dbg",(char *)"Debug__C__ServerFaliure",(char *)"Debug__C__ServerFaliure",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__ServiceRequest( const UMLRTMessage * msg )
{
    #define umlrtparam_ServiceID ( *(int *)msg->getParam( 0 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition RunAsMaster,Debug__Path__ServiceRequest,Request:ServerComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__ServiceRequest",(char *)"RunAsMaster",(char *)"Debug__Path__ServiceRequest",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_ServiceID
}

void Capsule_Server::transitionaction_____Debug__ServiceRequest__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__ServiceRequest,RunAsMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__ServiceRequest__E",(char *)"ex",(char *)"RunAsMaster",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__ServiceRequest__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__ServiceRequest,Debug__C__ServiceRequest */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__ServiceRequest__S",(char *)"Debug__Path__ServiceRequest",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__ServiceRequest__dbg( const UMLRTMessage * msg )
{
    #define umlrtparam_varName ( *(const char * *)msg->getParam( 0 ) )
    #define umlrtparam_varValue ( *(const char * *)msg->getParam( 1 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__ServiceRequest,Debug__C__ServiceRequest,dbgVarChange:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__ServiceRequest__dbg",(char *)"Debug__C__ServiceRequest",(char *)"Debug__C__ServiceRequest",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_varValue
    #undef umlrtparam_varName
}

void Capsule_Server::transitionaction_____Debug__StandBy__CheckConfig__5( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    #define rtdata ( (const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition StandBy,Debug__Path__StandBy__CheckConfig__5,StartUp:ConfigComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__StandBy__CheckConfig__5",(char *)"StandBy",(char *)"Debug__Path__StandBy__CheckConfig__5",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

void Capsule_Server::transitionaction_____Debug__StandBy__CheckConfig__5__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__StandBy__CheckConfig__5::ex,CheckConfig */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__StandBy__CheckConfig__5__E",(char *)"ex",(char *)"CheckConfig",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__StandBy__CheckConfig__5__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__StandBy__CheckConfig__5,Debug__C__StandBy__CheckConfig__5::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__StandBy__CheckConfig__5__S",(char *)"Debug__Path__StandBy__CheckConfig__5",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__StandBy__CheckConfig__5__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__StandBy__CheckConfig__5::new_exitpoint_19,Debug__C__StandBy__CheckConfig__5 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__StandBy__CheckConfig__5__dbg",(char *)"Debug__C__StandBy__CheckConfig__5",(char *)"Debug__C__StandBy__CheckConfig__5",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__initTimer( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition CheckConfig,Debug__Path__initTimer,timeout:MasterAnnounceTimer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__initTimer",(char *)"CheckConfig",(char *)"Debug__Path__initTimer",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__initTimer__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__initTimer::ex,RunAsMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__initTimer__E",(char *)"ex",(char *)"RunAsMaster",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__initTimer__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__initTimer,Debug__C__initTimer::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__initTimer__S",(char *)"Debug__Path__initTimer",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__initTimer__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__initTimer::new_exitpoint_9,Debug__C__initTimer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__initTimer__dbg",(char *)"Debug__C__initTimer",(char *)"Debug__C__initTimer",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__purgeotherMessage( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Failure,Debug__Path__purgeotherMessage,null:ServerComm:Master */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__purgeotherMessage",(char *)"Failure",(char *)"Debug__Path__purgeotherMessage",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__purgeotherMessage__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__purgeotherMessage::ex,Failure */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__purgeotherMessage__E",(char *)"ex",(char *)"Failure",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__purgeotherMessage__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__purgeotherMessage,Debug__C__purgeotherMessage::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__purgeotherMessage__S",(char *)"Debug__Path__purgeotherMessage",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Debug__purgeotherMessage__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__C__purgeotherMessage::new_exitpoint_18,Debug__C__purgeotherMessage */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Debug__purgeotherMessage__dbg",(char *)"Debug__C__purgeotherMessage",(char *)"Debug__C__purgeotherMessage",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____ExitPoint1__BeMaster__4( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__ExitPoint1__BeMaster__4,BeMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::ExitPoint1__BeMaster__4",(char *)"Debug__Path__ExitPoint1__BeMaster__4",(char *)"BeMaster",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Init__StandBy__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__Init__StandBy__3,StandBy */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Init__StandBy__3",(char *)"Debug__Path__Init__StandBy__3",(char *)"StandBy",(char *)"");
    std::cout<<this->getName()<<this->getIndex()<<": Intialization\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____KeepAlive( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__KeepAlive,RunAsMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::KeepAlive",(char *)"Debug__Path__KeepAlive",(char *)"RunAsMaster",(char *)"");
    if (KeepAliveTimerId.isValid())
    KeepAliveTimer.cancelTimer(KeepAliveTimerId);
    KeepAliveTimerId=KeepAliveTimer.informEvery(UMLRTTimespec(KeepAliveTimeOut,0),4);
    if (config.RunningMode==1)
    Master.IAmAlive((char *)this->getName()).send();
    std::cout<<"Master: Keep Alive is sent\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____MasterAnnounce( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__MasterAnnounce,RunAsMaster */
    if (AnnouncementTimerId.isValid())
    MasterAnnounceTimer.cancelTimer(AnnouncementTimerId);
    AnnouncementTimerId=MasterAnnounceTimer.informEvery(UMLRTTimespec(AnnouncementTimeOut,0),4);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____PassiveMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__PassiveMode,Backup */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::PassiveMode",(char *)"Debug__Path__PassiveMode",(char *)"Backup",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Recover( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__Recover,Choice1 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::Recover",(char *)"Debug__Path__Recover",(char *)"Choice1",(char *)"");
    std::cout<<this->getName()<<": is recovering\n";
    if (TimerId.isValid())
    Timer.cancelTimer(TimerId);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____ServerFaliure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__ServerFaliure,Failure */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::ServerFaliure",(char *)"Debug__Path__ServerFaliure",(char *)"Failure",(char *)"");
    if (KeepAliveTimerId.isValid())
    KeepAliveTimer.cancelTimer(KeepAliveTimerId);
    if (AnnouncementTimerId.isValid())
    MasterAnnounceTimer.cancelTimer(AnnouncementTimerId);
    if (TimerId.isValid())
    Timer.cancelTimer(TimerId);
    int r=random()%30+5;
    Timer.informEvery(UMLRTTimespec(r,0),4);
    std::cout<<this->getName()<<": Failure,  will recover after " << r << " seconds\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____ServiceRequest( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__ServiceRequest,RunAsMaster */
    std::cout<<this->getName()<<": Message from client replied at index "<<msg->sapIndex0_<<"\n";
    int tempid=msg->sapIndex0_;
    ServerComm.Reply(0).sendAt(tempid);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____StandBy__CheckConfig__5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__StandBy__CheckConfig__5,CheckConfig */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::StandBy__CheckConfig__5",(char *)"Debug__Path__StandBy__CheckConfig__5",(char *)"CheckConfig",(char *)"");
    std::cout<<this->getName()<<": StartingUp\n";
    this->config=umlrtparam_config;
    std::cout<<this->getName()<<": Configuration is:"<< config.RunningMode<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____initTimer( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__initTimer,RunAsMaster */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::initTimer",(char *)"Debug__Path__initTimer",(char *)"RunAsMaster",(char *)"");
    int r=random()%30+5;
    std::cout<<this->getName()<<": will go fail state after "<< r << "second\n";
    TimerId=Timer.informEvery(UMLRTTimespec(r,0),4);
    KeepAliveTimerId=KeepAliveTimer.informEvery(UMLRTTimespec(KeepAliveTimeOut,0),4);
    AnnouncementTimerId=MasterAnnounceTimer.informEvery(UMLRTTimespec(AnnouncementTimeOut,0),4);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____purgeotherMessage( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server transition Debug__Path__purgeotherMessage,Failure */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Hosts::Server::ServerStateMachine::Region1::purgeotherMessage",(char *)"Debug__Path__purgeotherMessage",(char *)"Failure",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Server::action_____Backup__Debug__BackToSlave__S__Debug__GuardBackToSlave( const UMLRTMessage * msg )
{
    #define umlrtparam_ServerName ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup guard Backup::Debug__Path__BackToSlave,Backup::Debug__C__BackToSlave::en */
    return Debug__SRO.checkDebug("TryBeMaster",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_ServerName
}

bool Capsule_Server::action_____Backup__Debug__CheckNoMaster__CheckNoServer( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    #define rtdata ( (const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup guard Backup::Choice2,Backup::Debug__Path__CheckNoMaster */
    std::cout<<"00000----------------------------------------------------000000\n";
    this->config=umlrtparam_config;
    if (!(this->config.MasterList[0] || this->config.MasterList[1]))
    {
    //Echo.Echo().send();
    //Timer.cancelTimer(TimerId);
    std::cout<<this->getName()<<": No one is Master, I am going to Be master\n";
    return true;
    }
    else if ((strcmp((char*)this->getName(),"server1")==0) && (config.MasterList[1]==false))
    {
    //Echo.Echo().send();
    //Timer.cancelTimer(TimerId);
    std::cout<<this->getName()<<": No one is Master, I am going to Be master\n";
    return true;
    }
    else if ((strcmp((char *)this->getName(),"server2"))==0 && (config.MasterList[0]==false))
    {
    //Echo.Echo().send();
    //Timer.cancelTimer(TimerId);
    std::cout<<this->getName()<<": No one is Master, I am going to Be master\n";
    return true;
    }
    std::cout<<"11111111-----------------------------------------111111111111\n";
    return false;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

bool Capsule_Server::action_____Backup__Debug__CheckNoMaster__S__Debug__GuardCheckNoMaster( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    #define rtdata ( (const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup guard Backup::Debug__Path__CheckNoMaster,Backup::Debug__C__CheckNoMaster::en */
    return Debug__SRO.checkDebug("Choice2","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

bool Capsule_Server::action_____Backup__Debug__Initial1__RunAsSlave__2__S__Debug__GuardInitial1__RunAsSlave__2( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    #define rtdata ( (const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup guard Backup::Debug__Path__Initial1__RunAsSlave__2,Backup::Debug__C__Initial1__RunAsSlave__2::en */
    return Debug__SRO.checkDebug("Initial1","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

bool Capsule_Server::action_____Backup__Debug__KeepAliveMsg__S__Debug__GuardKeepAliveMsg( const UMLRTMessage * msg )
{
    #define umlrtparam_ServerName ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup guard Backup::Debug__Path__KeepAliveMsg,Backup::Debug__C__KeepAliveMsg::en */
    return Debug__SRO.checkDebug("RunAsSlave",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_ServerName
}

bool Capsule_Server::action_____Backup__Debug__NokeepAlive__S__Debug__GuardNokeepAlive( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup guard Backup::Debug__Path__NokeepAlive,Backup::Debug__C__NokeepAlive::en */
    return Debug__SRO.checkDebug("RunAsSlave",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Server::action_____Backup__Debug__ReplyConfig__S__Debug__GuardReplyConfig( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    #define rtdata ( (const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup guard Backup::Debug__Path__ReplyConfig,Backup::Debug__C__ReplyConfig::en */
    return Debug__SRO.checkDebug("TryBeMaster",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

bool Capsule_Server::action_____Backup__Debug__backtoslave1__S__Debug__Guardbacktoslave1( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    #define rtdata ( (const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup guard Backup::Debug__Path__backtoslave1,Backup::Debug__C__backtoslave1::en */
    return Debug__SRO.checkDebug("Choice2","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

bool Capsule_Server::action_____Backup__Debug__backtoslave__S__Debug__Guardbacktoslave( const UMLRTMessage * msg )
{
    #define umlrtparam_ServerName ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server::Backup guard Backup::Debug__Path__backtoslave,Backup::Debug__C__backtoslave::en */
    return Debug__SRO.checkDebug("Slave","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_ServerName
}

bool Capsule_Server::action_____Debug__ActiveMode__S__Debug__GuardActiveMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server guard Debug__Path__ActiveMode,Debug__C__ActiveMode::en */
    return Debug__SRO.checkDebug("Choice1","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Server::action_____Debug__ActiveMode__checkConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server guard Choice1,Debug__Path__ActiveMode */
    if (config.RunningMode==0)
    return true;
    else return false;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Server::action_____Debug__BeSlave__S__Debug__GuardBeSlave( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    #define rtdata ( (const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server guard Debug__Path__BeSlave,Debug__C__BeSlave::en */
    return Debug__SRO.checkDebug("CheckConfig","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

bool Capsule_Server::action_____Debug__BeingMaster__S__Debug__GuardBeingMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server guard Debug__Path__BeingMaster,Debug__C__BeingMaster::en */
    return Debug__SRO.checkDebug("BeMaster","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Server::action_____Debug__ExitPoint1__BeMaster__4__S__Debug__GuardExitPoint1__BeMaster__4( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    #define rtdata ( (const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server guard Debug__Path__ExitPoint1__BeMaster__4,Debug__C__ExitPoint1__BeMaster__4::en */
    return Debug__SRO.checkDebug("ExitPoint1","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

bool Capsule_Server::action_____Debug__Init__StandBy__3__S__Debug__GuardInit__StandBy__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server guard Debug__Path__Init__StandBy__3,Debug__C__Init__StandBy__3::en */
    return Debug__SRO.checkDebug("Init","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Server::action_____Debug__KeepAlive__S__Debug__GuardKeepAlive( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server guard Debug__Path__KeepAlive,Debug__C__KeepAlive::en */
    return Debug__SRO.checkDebug("RunAsMaster",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Server::action_____Debug__MasterAnnounce__S__Debug__GuardMasterAnnounce( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server guard Debug__Path__MasterAnnounce,Debug__C__MasterAnnounce */
    return Debug__SRO.checkDebug("RunAsMaster",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Server::action_____Debug__PassiveMode__S__Debug__GuardPassiveMode( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server guard Debug__Path__PassiveMode,Debug__C__PassiveMode::en */
    return Debug__SRO.checkDebug("Choice1","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Server::action_____Debug__Recover__S__Debug__GuardRecover( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server guard Debug__Path__Recover,Debug__C__Recover::en */
    return Debug__SRO.checkDebug("Failure",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Server::action_____Debug__ServerFaliure__S__Debug__GuardServerFaliure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server guard Debug__Path__ServerFaliure,Debug__C__ServerFaliure::en */
    return Debug__SRO.checkDebug("RunAsMaster",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Server::action_____Debug__ServiceRequest__S__Debug__GuardServiceRequest( const UMLRTMessage * msg )
{
    #define umlrtparam_ServiceID ( *(int *)msg->getParam( 0 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server guard Debug__Path__ServiceRequest,Debug__C__ServiceRequest */
    return Debug__SRO.checkDebug("RunAsMaster",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_ServiceID
}

bool Capsule_Server::action_____Debug__StandBy__CheckConfig__5__S__Debug__GuardStandBy__CheckConfig__5( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    #define rtdata ( (const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server guard Debug__Path__StandBy__CheckConfig__5,Debug__C__StandBy__CheckConfig__5::en */
    return Debug__SRO.checkDebug("StandBy",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

bool Capsule_Server::action_____Debug__initTimer__CheckConfig( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    #define rtdata ( (const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server guard CheckConfig,Debug__Path__initTimer,timeout:MasterAnnounceTimer */
    if ((config.RunningMode==0) ||
    ((config.RunningMode==1) && (strcmp(config.MasterName,this->getName())==0)))
    return true;
    else 
    return false;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

bool Capsule_Server::action_____Debug__initTimer__S__Debug__GuardinitTimer( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const Configuration * )msg->getParam( 0 ) )
    #define rtdata ( (const Configuration * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server guard Debug__Path__initTimer,Debug__C__initTimer::en */
    return Debug__SRO.checkDebug("CheckConfig","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

bool Capsule_Server::action_____Debug__purgeotherMessage__S__Debug__GuardpurgeotherMessage( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Hosts::Server guard Debug__Path__purgeotherMessage,Debug__C__purgeotherMessage::en */
    return Debug__SRO.checkDebug("Failure",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::actionchain_____ActiveMode( const UMLRTMessage * msg )
{
    transitionaction_____ActiveMode( msg );
}

void Capsule_Server::actionchain_____Backup__BackToSlave( const UMLRTMessage * msg )
{
    transitionaction_____Backup__BackToSlave( msg );
}

void Capsule_Server::actionchain_____Backup__CheckNoMaster( const UMLRTMessage * msg )
{
    transitionaction_____Backup__CheckNoMaster( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__BackToSlave( const UMLRTMessage * msg )
{
    exitaction_____Backup__TryBeMaster( msg );
    transitionaction_____Backup__Debug__BackToSlave( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__BackToSlave__E( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__BackToSlave__boundary( msg );
    transitionaction_____Backup__Debug__BackToSlave__E( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__BackToSlave__S( const UMLRTMessage * msg )
{
    transitionaction_____Backup__Debug__BackToSlave__S( msg );
    entryaction_____Backup__Debug__C__BackToSlave__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__BackToSlave__dbg( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__BackToSlave__boundary( msg );
    transitionaction_____Backup__Debug__BackToSlave__dbg( msg );
    entryaction_____Backup__Debug__C__BackToSlave__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__BackToSlave__Debug__AC__BackToSlave( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__BackToSlave__Debug__B__Ac__BackToSlave( msg );
    transitionaction_____Backup__Debug__C__BackToSlave__Debug__AC__BackToSlave( msg );
    entryaction_____Backup__Debug__C__BackToSlave__Debug__A__Ac__BackToSlave( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__BackToSlave__Debug__Ex__TryBeMaster( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__BackToSlave__Debug__B__Ex__TryBeMaster( msg );
    transitionaction_____Backup__Debug__C__BackToSlave__Debug__Ex__TryBeMaster( msg );
    entryaction_____Backup__Debug__C__BackToSlave__Debug__B__Ac__BackToSlave( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__BackToSlave__Debug__end__trans__BackToSlave( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__BackToSlave__Debug__A__Ac__BackToSlave( msg );
    transitionaction_____Backup__Debug__C__BackToSlave__Debug__end__trans__BackToSlave( msg );
    save_history( Backup__Debug__C__BackToSlave, Backup__Debug__C__BackToSlave__Debug__A__Ac__BackToSlave );
}

void Capsule_Server::actionchain_____Backup__Debug__C__BackToSlave__Debug__init__trans__BackToSlave( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__BackToSlave__Debug__B__Ex__TryBeMaster( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__BackToSlave__new_transition_20( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__BackToSlave__Debug__B__Ex__TryBeMaster( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__BackToSlave__new_transition_21( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__BackToSlave__Debug__B__Ac__BackToSlave( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__BackToSlave__new_transition_22( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__BackToSlave__Debug__A__Ac__BackToSlave( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__BackToSlave__new_transition_23_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__BackToSlave__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__BackToSlave__new_transition_24( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__BackToSlave__Debug__B__Ex__TryBeMaster( msg );
    save_history( Backup__Debug__C__BackToSlave, Backup__Debug__C__BackToSlave__Debug__B__Ex__TryBeMaster );
}

void Capsule_Server::actionchain_____Backup__Debug__C__BackToSlave__new_transition_25( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__BackToSlave__Debug__B__Ac__BackToSlave( msg );
    save_history( Backup__Debug__C__BackToSlave, Backup__Debug__C__BackToSlave__Debug__B__Ac__BackToSlave );
}

void Capsule_Server::actionchain_____Backup__Debug__C__BackToSlave__new_transition_26( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__BackToSlave__Debug__A__Ac__BackToSlave( msg );
    save_history( Backup__Debug__C__BackToSlave, Backup__Debug__C__BackToSlave__Debug__A__Ac__BackToSlave );
}

void Capsule_Server::actionchain_____Backup__Debug__C__BackToSlave__new_transition_27( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__BackToSlave__boundary( msg );
    save_history( Backup__Debug__C__BackToSlave, Backup__Debug__C__BackToSlave__boundary );
}

void Capsule_Server::actionchain_____Backup__Debug__C__CheckNoMaster__Debug__Ac__CheckNoMaster( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__CheckNoMaster__Debug__B__Ac__CheckNoMaster( msg );
    entryaction_____Backup__Debug__C__CheckNoMaster__Debug__A__Ac__CheckNoMaster( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__CheckNoMaster__Debug__end__trans__CheckNoMaster( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__CheckNoMaster__Debug__A__Ac__CheckNoMaster( msg );
    save_history( Backup__Debug__C__CheckNoMaster, Backup__Debug__C__CheckNoMaster__Debug__A__Ac__CheckNoMaster );
}

void Capsule_Server::actionchain_____Backup__Debug__C__CheckNoMaster__Debug__init__trans__CheckNoMaster( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__CheckNoMaster__Debug__B__Ac__CheckNoMaster( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__CheckNoMaster__new_transition_60( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__CheckNoMaster__Debug__B__Ac__CheckNoMaster( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__CheckNoMaster__new_transition_61( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__CheckNoMaster__Debug__A__Ac__CheckNoMaster( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__CheckNoMaster__new_transition_62_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__CheckNoMaster__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__CheckNoMaster__new_transition_63( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__CheckNoMaster__Debug__B__Ac__CheckNoMaster( msg );
    save_history( Backup__Debug__C__CheckNoMaster, Backup__Debug__C__CheckNoMaster__Debug__B__Ac__CheckNoMaster );
}

void Capsule_Server::actionchain_____Backup__Debug__C__CheckNoMaster__new_transition_64( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__CheckNoMaster__Debug__A__Ac__CheckNoMaster( msg );
    save_history( Backup__Debug__C__CheckNoMaster, Backup__Debug__C__CheckNoMaster__Debug__A__Ac__CheckNoMaster );
}

void Capsule_Server::actionchain_____Backup__Debug__C__CheckNoMaster__new_transition_65( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__CheckNoMaster__boundary( msg );
    save_history( Backup__Debug__C__CheckNoMaster, Backup__Debug__C__CheckNoMaster__boundary );
}

void Capsule_Server::actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__Ac__Initial1__RunAsSlave__2( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__B__Ac__Initial1__RunAsSlave__2( msg );
    transitionaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__Ac__Initial1__RunAsSlave__2( msg );
    entryaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__Ac__Initial1__RunAsSlave__2( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__En__RunAsSlave( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__Ac__Initial1__RunAsSlave__2( msg );
    transitionaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__En__RunAsSlave( msg );
    entryaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__En__Initial1__RunAsSlave__2( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__end__trans__Initial1__RunAsSlave__2( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__En__Initial1__RunAsSlave__2( msg );
    transitionaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__end__trans__Initial1__RunAsSlave__2( msg );
    save_history( Backup__Debug__C__Initial1__RunAsSlave__2, Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__En__Initial1__RunAsSlave__2 );
}

void Capsule_Server::actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__init__trans__Initial1__RunAsSlave__2( const UMLRTMessage * msg )
{
    transitionaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__init__trans__Initial1__RunAsSlave__2( msg );
    entryaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__B__Ac__Initial1__RunAsSlave__2( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_12( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__B__Ac__Initial1__RunAsSlave__2( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_13( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__Ac__Initial1__RunAsSlave__2( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_14( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__En__Initial1__RunAsSlave__2( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_15_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__Initial1__RunAsSlave__2__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_16( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__B__Ac__Initial1__RunAsSlave__2( msg );
    save_history( Backup__Debug__C__Initial1__RunAsSlave__2, Backup__Debug__C__Initial1__RunAsSlave__2__Debug__B__Ac__Initial1__RunAsSlave__2 );
}

void Capsule_Server::actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_17( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__Ac__Initial1__RunAsSlave__2( msg );
    save_history( Backup__Debug__C__Initial1__RunAsSlave__2, Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__Ac__Initial1__RunAsSlave__2 );
}

void Capsule_Server::actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_18( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__En__Initial1__RunAsSlave__2( msg );
    save_history( Backup__Debug__C__Initial1__RunAsSlave__2, Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__En__Initial1__RunAsSlave__2 );
}

void Capsule_Server::actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_19( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__Initial1__RunAsSlave__2__boundary( msg );
    save_history( Backup__Debug__C__Initial1__RunAsSlave__2, Backup__Debug__C__Initial1__RunAsSlave__2__boundary );
}

void Capsule_Server::actionchain_____Backup__Debug__C__KeepAliveMsg__Debug__AC__KeepAliveMsg( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__KeepAliveMsg__Debug__B__Ac__KeepAliveMsg( msg );
    transitionaction_____Backup__Debug__C__KeepAliveMsg__Debug__AC__KeepAliveMsg( msg );
    entryaction_____Backup__Debug__C__KeepAliveMsg__Debug__A__Ac__KeepAliveMsg( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__KeepAliveMsg__Debug__En__RunAsSlave( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__KeepAliveMsg__Debug__A__Ac__KeepAliveMsg( msg );
    transitionaction_____Backup__Debug__C__KeepAliveMsg__Debug__En__RunAsSlave( msg );
    entryaction_____Backup__Debug__C__KeepAliveMsg__Debug__A__En__RunAsSlave( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__KeepAliveMsg__Debug__Ex__RunAsSlave( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__KeepAliveMsg__Debug__B__Ex__RunAsSlave( msg );
    transitionaction_____Backup__Debug__C__KeepAliveMsg__Debug__Ex__RunAsSlave( msg );
    entryaction_____Backup__Debug__C__KeepAliveMsg__Debug__B__Ac__KeepAliveMsg( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__KeepAliveMsg__Debug__end__trans__KeepAliveMsg( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__KeepAliveMsg__Debug__A__En__RunAsSlave( msg );
    transitionaction_____Backup__Debug__C__KeepAliveMsg__Debug__end__trans__KeepAliveMsg( msg );
    save_history( Backup__Debug__C__KeepAliveMsg, Backup__Debug__C__KeepAliveMsg__Debug__A__En__RunAsSlave );
}

void Capsule_Server::actionchain_____Backup__Debug__C__KeepAliveMsg__Debug__init__trans__KeepAliveMsg( const UMLRTMessage * msg )
{
    transitionaction_____Backup__Debug__C__KeepAliveMsg__Debug__init__trans__KeepAliveMsg( msg );
    entryaction_____Backup__Debug__C__KeepAliveMsg__Debug__B__Ex__RunAsSlave( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_50( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__KeepAliveMsg__Debug__B__Ex__RunAsSlave( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_51( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__KeepAliveMsg__Debug__B__Ac__KeepAliveMsg( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_52( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__KeepAliveMsg__Debug__A__Ac__KeepAliveMsg( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_53( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__KeepAliveMsg__Debug__A__En__RunAsSlave( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_54_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__KeepAliveMsg__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_55( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__KeepAliveMsg__Debug__B__Ex__RunAsSlave( msg );
    save_history( Backup__Debug__C__KeepAliveMsg, Backup__Debug__C__KeepAliveMsg__Debug__B__Ex__RunAsSlave );
}

void Capsule_Server::actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_56( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__KeepAliveMsg__Debug__B__Ac__KeepAliveMsg( msg );
    save_history( Backup__Debug__C__KeepAliveMsg, Backup__Debug__C__KeepAliveMsg__Debug__B__Ac__KeepAliveMsg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_57( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__KeepAliveMsg__Debug__A__Ac__KeepAliveMsg( msg );
    save_history( Backup__Debug__C__KeepAliveMsg, Backup__Debug__C__KeepAliveMsg__Debug__A__Ac__KeepAliveMsg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_58( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__KeepAliveMsg__Debug__A__En__RunAsSlave( msg );
    save_history( Backup__Debug__C__KeepAliveMsg, Backup__Debug__C__KeepAliveMsg__Debug__A__En__RunAsSlave );
}

void Capsule_Server::actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_59( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__KeepAliveMsg__boundary( msg );
    save_history( Backup__Debug__C__KeepAliveMsg, Backup__Debug__C__KeepAliveMsg__boundary );
}

void Capsule_Server::actionchain_____Backup__Debug__C__NokeepAlive__Debug__AC__NokeepAlive( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__NokeepAlive__Debug__B__Ac__NokeepAlive( msg );
    transitionaction_____Backup__Debug__C__NokeepAlive__Debug__AC__NokeepAlive( msg );
    entryaction_____Backup__Debug__C__NokeepAlive__Debug__A__Ac__NokeepAlive( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__NokeepAlive__Debug__En__TryBeMaster( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__NokeepAlive__Debug__A__Ac__NokeepAlive( msg );
    transitionaction_____Backup__Debug__C__NokeepAlive__Debug__En__TryBeMaster( msg );
    entryaction_____Backup__Debug__C__NokeepAlive__Debug__A__En__TryBeMaster( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__NokeepAlive__Debug__Ex__RunAsSlave( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__NokeepAlive__Debug__B__Ex__RunAsSlave( msg );
    transitionaction_____Backup__Debug__C__NokeepAlive__Debug__Ex__RunAsSlave( msg );
    entryaction_____Backup__Debug__C__NokeepAlive__Debug__B__Ac__NokeepAlive( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__NokeepAlive__Debug__end__trans__NokeepAlive( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__NokeepAlive__Debug__A__En__TryBeMaster( msg );
    transitionaction_____Backup__Debug__C__NokeepAlive__Debug__end__trans__NokeepAlive( msg );
    save_history( Backup__Debug__C__NokeepAlive, Backup__Debug__C__NokeepAlive__Debug__A__En__TryBeMaster );
}

void Capsule_Server::actionchain_____Backup__Debug__C__NokeepAlive__Debug__init__trans__NokeepAlive( const UMLRTMessage * msg )
{
    transitionaction_____Backup__Debug__C__NokeepAlive__Debug__init__trans__NokeepAlive( msg );
    entryaction_____Backup__Debug__C__NokeepAlive__Debug__B__Ex__RunAsSlave( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__NokeepAlive__new_transition_66( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__NokeepAlive__Debug__B__Ex__RunAsSlave( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__NokeepAlive__new_transition_67( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__NokeepAlive__Debug__B__Ac__NokeepAlive( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__NokeepAlive__new_transition_68( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__NokeepAlive__Debug__A__Ac__NokeepAlive( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__NokeepAlive__new_transition_69( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__NokeepAlive__Debug__A__En__TryBeMaster( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__NokeepAlive__new_transition_70_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__NokeepAlive__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__NokeepAlive__new_transition_71( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__NokeepAlive__Debug__B__Ex__RunAsSlave( msg );
    save_history( Backup__Debug__C__NokeepAlive, Backup__Debug__C__NokeepAlive__Debug__B__Ex__RunAsSlave );
}

void Capsule_Server::actionchain_____Backup__Debug__C__NokeepAlive__new_transition_72( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__NokeepAlive__Debug__B__Ac__NokeepAlive( msg );
    save_history( Backup__Debug__C__NokeepAlive, Backup__Debug__C__NokeepAlive__Debug__B__Ac__NokeepAlive );
}

void Capsule_Server::actionchain_____Backup__Debug__C__NokeepAlive__new_transition_73( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__NokeepAlive__Debug__A__Ac__NokeepAlive( msg );
    save_history( Backup__Debug__C__NokeepAlive, Backup__Debug__C__NokeepAlive__Debug__A__Ac__NokeepAlive );
}

void Capsule_Server::actionchain_____Backup__Debug__C__NokeepAlive__new_transition_74( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__NokeepAlive__Debug__A__En__TryBeMaster( msg );
    save_history( Backup__Debug__C__NokeepAlive, Backup__Debug__C__NokeepAlive__Debug__A__En__TryBeMaster );
}

void Capsule_Server::actionchain_____Backup__Debug__C__NokeepAlive__new_transition_75( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__NokeepAlive__boundary( msg );
    save_history( Backup__Debug__C__NokeepAlive, Backup__Debug__C__NokeepAlive__boundary );
}

void Capsule_Server::actionchain_____Backup__Debug__C__ReplyConfig__Debug__AC__ReplyConfig( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__ReplyConfig__Debug__B__Ac__ReplyConfig( msg );
    transitionaction_____Backup__Debug__C__ReplyConfig__Debug__AC__ReplyConfig( msg );
    entryaction_____Backup__Debug__C__ReplyConfig__Debug__A__Ac__ReplyConfig( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__ReplyConfig__Debug__Ex__TryBeMaster( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__ReplyConfig__Debug__B__Ex__TryBeMaster( msg );
    transitionaction_____Backup__Debug__C__ReplyConfig__Debug__Ex__TryBeMaster( msg );
    entryaction_____Backup__Debug__C__ReplyConfig__Debug__B__Ac__ReplyConfig( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__ReplyConfig__Debug__end__trans__ReplyConfig( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__ReplyConfig__Debug__A__Ac__ReplyConfig( msg );
    transitionaction_____Backup__Debug__C__ReplyConfig__Debug__end__trans__ReplyConfig( msg );
    save_history( Backup__Debug__C__ReplyConfig, Backup__Debug__C__ReplyConfig__Debug__A__Ac__ReplyConfig );
}

void Capsule_Server::actionchain_____Backup__Debug__C__ReplyConfig__Debug__init__trans__ReplyConfig( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__ReplyConfig__Debug__B__Ex__TryBeMaster( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__ReplyConfig__new_transition_36( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__ReplyConfig__Debug__B__Ex__TryBeMaster( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__ReplyConfig__new_transition_37( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__ReplyConfig__Debug__B__Ac__ReplyConfig( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__ReplyConfig__new_transition_38( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__ReplyConfig__Debug__A__Ac__ReplyConfig( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__ReplyConfig__new_transition_39_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__ReplyConfig__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__ReplyConfig__new_transition_40( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__ReplyConfig__Debug__B__Ex__TryBeMaster( msg );
    save_history( Backup__Debug__C__ReplyConfig, Backup__Debug__C__ReplyConfig__Debug__B__Ex__TryBeMaster );
}

void Capsule_Server::actionchain_____Backup__Debug__C__ReplyConfig__new_transition_41( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__ReplyConfig__Debug__B__Ac__ReplyConfig( msg );
    save_history( Backup__Debug__C__ReplyConfig, Backup__Debug__C__ReplyConfig__Debug__B__Ac__ReplyConfig );
}

void Capsule_Server::actionchain_____Backup__Debug__C__ReplyConfig__new_transition_42( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__ReplyConfig__Debug__A__Ac__ReplyConfig( msg );
    save_history( Backup__Debug__C__ReplyConfig, Backup__Debug__C__ReplyConfig__Debug__A__Ac__ReplyConfig );
}

void Capsule_Server::actionchain_____Backup__Debug__C__ReplyConfig__new_transition_43( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__ReplyConfig__boundary( msg );
    save_history( Backup__Debug__C__ReplyConfig, Backup__Debug__C__ReplyConfig__boundary );
}

void Capsule_Server::actionchain_____Backup__Debug__C__backtoslave1__Debug__Ac__backtoslave1( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__backtoslave1__Debug__B__Ac__backtoslave1( msg );
    entryaction_____Backup__Debug__C__backtoslave1__Debug__A__Ac__backtoslave1( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__backtoslave1__Debug__end__trans__backtoslave1( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__backtoslave1__Debug__A__Ac__backtoslave1( msg );
    save_history( Backup__Debug__C__backtoslave1, Backup__Debug__C__backtoslave1__Debug__A__Ac__backtoslave1 );
}

void Capsule_Server::actionchain_____Backup__Debug__C__backtoslave1__Debug__init__trans__backtoslave1( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__backtoslave1__Debug__B__Ac__backtoslave1( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__backtoslave1__new_transition_44( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__backtoslave1__Debug__B__Ac__backtoslave1( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__backtoslave1__new_transition_45( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__backtoslave1__Debug__A__Ac__backtoslave1( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__backtoslave1__new_transition_46_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__backtoslave1__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__backtoslave1__new_transition_47( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__backtoslave1__Debug__B__Ac__backtoslave1( msg );
    save_history( Backup__Debug__C__backtoslave1, Backup__Debug__C__backtoslave1__Debug__B__Ac__backtoslave1 );
}

void Capsule_Server::actionchain_____Backup__Debug__C__backtoslave1__new_transition_48( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__backtoslave1__Debug__A__Ac__backtoslave1( msg );
    save_history( Backup__Debug__C__backtoslave1, Backup__Debug__C__backtoslave1__Debug__A__Ac__backtoslave1 );
}

void Capsule_Server::actionchain_____Backup__Debug__C__backtoslave1__new_transition_49( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__backtoslave1__boundary( msg );
    save_history( Backup__Debug__C__backtoslave1, Backup__Debug__C__backtoslave1__boundary );
}

void Capsule_Server::actionchain_____Backup__Debug__C__backtoslave__Debug__Ac__backtoslave( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__backtoslave__Debug__B__Ac__backtoslave( msg );
    transitionaction_____Backup__Debug__C__backtoslave__Debug__Ac__backtoslave( msg );
    entryaction_____Backup__Debug__C__backtoslave__Debug__A__Ac__backtoslave( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__backtoslave__Debug__En__RunAsSlave( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__backtoslave__Debug__A__Ac__backtoslave( msg );
    transitionaction_____Backup__Debug__C__backtoslave__Debug__En__RunAsSlave( msg );
    entryaction_____Backup__Debug__C__backtoslave__Debug__A__En__backtoslave( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__backtoslave__Debug__end__trans__backtoslave( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__backtoslave__Debug__A__En__backtoslave( msg );
    transitionaction_____Backup__Debug__C__backtoslave__Debug__end__trans__backtoslave( msg );
    save_history( Backup__Debug__C__backtoslave, Backup__Debug__C__backtoslave__Debug__A__En__backtoslave );
}

void Capsule_Server::actionchain_____Backup__Debug__C__backtoslave__Debug__init__trans__backtoslave( const UMLRTMessage * msg )
{
    transitionaction_____Backup__Debug__C__backtoslave__Debug__init__trans__backtoslave( msg );
    entryaction_____Backup__Debug__C__backtoslave__Debug__B__Ac__backtoslave( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__backtoslave__new_transition_28( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__backtoslave__Debug__B__Ac__backtoslave( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__backtoslave__new_transition_29( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__backtoslave__Debug__A__Ac__backtoslave( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__backtoslave__new_transition_30( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__backtoslave__Debug__A__En__backtoslave( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__backtoslave__new_transition_31_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Backup__Debug__C__backtoslave__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__C__backtoslave__new_transition_32( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__backtoslave__Debug__B__Ac__backtoslave( msg );
    save_history( Backup__Debug__C__backtoslave, Backup__Debug__C__backtoslave__Debug__B__Ac__backtoslave );
}

void Capsule_Server::actionchain_____Backup__Debug__C__backtoslave__new_transition_33( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__backtoslave__Debug__A__Ac__backtoslave( msg );
    save_history( Backup__Debug__C__backtoslave, Backup__Debug__C__backtoslave__Debug__A__Ac__backtoslave );
}

void Capsule_Server::actionchain_____Backup__Debug__C__backtoslave__new_transition_34( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__backtoslave__Debug__A__En__backtoslave( msg );
    save_history( Backup__Debug__C__backtoslave, Backup__Debug__C__backtoslave__Debug__A__En__backtoslave );
}

void Capsule_Server::actionchain_____Backup__Debug__C__backtoslave__new_transition_35( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__backtoslave__boundary( msg );
    save_history( Backup__Debug__C__backtoslave, Backup__Debug__C__backtoslave__boundary );
}

void Capsule_Server::actionchain_____Backup__Debug__CheckNoMaster( const UMLRTMessage * msg )
{
    transitionaction_____Backup__Debug__CheckNoMaster( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__CheckNoMaster__E( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__CheckNoMaster__boundary( msg );
    transitionaction_____Backup__Debug__CheckNoMaster__E( msg );
    save_history( Backup, Backup__Debug__C__CheckNoMaster );
}

void Capsule_Server::actionchain_____Backup__Debug__CheckNoMaster__S( const UMLRTMessage * msg )
{
    transitionaction_____Backup__Debug__CheckNoMaster__S( msg );
    entryaction_____Backup__Debug__C__CheckNoMaster__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__CheckNoMaster__dbg( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__CheckNoMaster__boundary( msg );
    transitionaction_____Backup__Debug__CheckNoMaster__dbg( msg );
    entryaction_____Backup__Debug__C__CheckNoMaster__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__Initial1__RunAsSlave__2__E( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__Initial1__RunAsSlave__2__boundary( msg );
    transitionaction_____Backup__Debug__Initial1__RunAsSlave__2__E( msg );
    entryaction_____Backup__RunAsSlave( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__Initial1__RunAsSlave__2__S( const UMLRTMessage * msg )
{
    transitionaction_____Backup__Debug__Initial1__RunAsSlave__2__S( msg );
    entryaction_____Backup__Debug__C__Initial1__RunAsSlave__2__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__Initial1__RunAsSlave__2__dbg( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__Initial1__RunAsSlave__2__boundary( msg );
    transitionaction_____Backup__Debug__Initial1__RunAsSlave__2__dbg( msg );
    entryaction_____Backup__Debug__C__Initial1__RunAsSlave__2__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__KeepAliveMsg( const UMLRTMessage * msg )
{
    exitaction_____Backup__RunAsSlave( msg );
    transitionaction_____Backup__Debug__KeepAliveMsg( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__KeepAliveMsg__E( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__KeepAliveMsg__boundary( msg );
    transitionaction_____Backup__Debug__KeepAliveMsg__E( msg );
    entryaction_____Backup__RunAsSlave( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__KeepAliveMsg__S( const UMLRTMessage * msg )
{
    transitionaction_____Backup__Debug__KeepAliveMsg__S( msg );
    entryaction_____Backup__Debug__C__KeepAliveMsg__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__KeepAliveMsg__dbg( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__KeepAliveMsg__boundary( msg );
    transitionaction_____Backup__Debug__KeepAliveMsg__dbg( msg );
    entryaction_____Backup__Debug__C__KeepAliveMsg__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__NokeepAlive( const UMLRTMessage * msg )
{
    exitaction_____Backup__RunAsSlave( msg );
    transitionaction_____Backup__Debug__NokeepAlive( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__NokeepAlive__E( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__NokeepAlive__boundary( msg );
    transitionaction_____Backup__Debug__NokeepAlive__E( msg );
    entryaction_____Backup__TryBeMaster( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__NokeepAlive__S( const UMLRTMessage * msg )
{
    transitionaction_____Backup__Debug__NokeepAlive__S( msg );
    entryaction_____Backup__Debug__C__NokeepAlive__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__NokeepAlive__dbg( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__NokeepAlive__boundary( msg );
    transitionaction_____Backup__Debug__NokeepAlive__dbg( msg );
    entryaction_____Backup__Debug__C__NokeepAlive__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__ReplyConfig( const UMLRTMessage * msg )
{
    exitaction_____Backup__TryBeMaster( msg );
    transitionaction_____Backup__Debug__ReplyConfig( msg );
    save_history( Backup, Backup__TryBeMaster );
}

void Capsule_Server::actionchain_____Backup__Debug__ReplyConfig__E( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__ReplyConfig__boundary( msg );
    transitionaction_____Backup__Debug__ReplyConfig__E( msg );
    save_history( Backup, Backup__Debug__C__ReplyConfig );
}

void Capsule_Server::actionchain_____Backup__Debug__ReplyConfig__S( const UMLRTMessage * msg )
{
    transitionaction_____Backup__Debug__ReplyConfig__S( msg );
    entryaction_____Backup__Debug__C__ReplyConfig__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__ReplyConfig__dbg( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__ReplyConfig__boundary( msg );
    transitionaction_____Backup__Debug__ReplyConfig__dbg( msg );
    entryaction_____Backup__Debug__C__ReplyConfig__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__backtoslave( const UMLRTMessage * msg )
{
    transitionaction_____Backup__Debug__backtoslave( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__backtoslave1( const UMLRTMessage * msg )
{
    transitionaction_____Backup__Debug__backtoslave1( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__backtoslave1__E( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__backtoslave1__boundary( msg );
    transitionaction_____Backup__Debug__backtoslave1__E( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__backtoslave1__S( const UMLRTMessage * msg )
{
    transitionaction_____Backup__Debug__backtoslave1__S( msg );
    entryaction_____Backup__Debug__C__backtoslave1__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__backtoslave1__dbg( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__backtoslave1__boundary( msg );
    transitionaction_____Backup__Debug__backtoslave1__dbg( msg );
    entryaction_____Backup__Debug__C__backtoslave1__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__backtoslave__E( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__backtoslave__boundary( msg );
    transitionaction_____Backup__Debug__backtoslave__E( msg );
    entryaction_____Backup__RunAsSlave( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__backtoslave__S( const UMLRTMessage * msg )
{
    transitionaction_____Backup__Debug__backtoslave__S( msg );
    entryaction_____Backup__Debug__C__backtoslave__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Debug__backtoslave__dbg( const UMLRTMessage * msg )
{
    exitaction_____Backup__Debug__C__backtoslave__boundary( msg );
    transitionaction_____Backup__Debug__backtoslave__dbg( msg );
    entryaction_____Backup__Debug__C__backtoslave__boundary( msg );
}

void Capsule_Server::actionchain_____Backup__Initial1__RunAsSlave__2( const UMLRTMessage * msg )
{
    transitionaction_____Backup__Initial1__RunAsSlave__2( msg );
    entryaction_____Backup__RunAsSlave( msg );
}

void Capsule_Server::actionchain_____Backup__KeepAliveMsg( const UMLRTMessage * msg )
{
    transitionaction_____Backup__KeepAliveMsg( msg );
    entryaction_____Backup__RunAsSlave( msg );
}

void Capsule_Server::actionchain_____Backup__NokeepAlive( const UMLRTMessage * msg )
{
    transitionaction_____Backup__NokeepAlive( msg );
    entryaction_____Backup__TryBeMaster( msg );
}

void Capsule_Server::actionchain_____Backup__ReplyConfig( const UMLRTMessage * msg )
{
    transitionaction_____Backup__ReplyConfig( msg );
}

void Capsule_Server::actionchain_____Backup__backtoslave( const UMLRTMessage * msg )
{
    transitionaction_____Backup__backtoslave( msg );
    entryaction_____Backup__RunAsSlave( msg );
}

void Capsule_Server::actionchain_____Backup__backtoslave1( const UMLRTMessage * msg )
{
    transitionaction_____Backup__backtoslave1( msg );
}

void Capsule_Server::actionchain_____Backup__new_transition_1( const UMLRTMessage * msg )
{
    entryaction_____Backup__TryBeMaster( msg );
}

void Capsule_Server::actionchain_____Backup__new_transition_11( const UMLRTMessage * msg )
{
    transitionaction_____Backup__new_transition_11( msg );
}

void Capsule_Server::actionchain_____Backup__new_transition_2( const UMLRTMessage * msg )
{
    entryaction_____Backup__RunAsSlave( msg );
}

void Capsule_Server::actionchain_____BeSlave( const UMLRTMessage * msg )
{
    transitionaction_____BeSlave( msg );
    entryaction_____Backup( msg );
}

void Capsule_Server::actionchain_____BeingMaster( const UMLRTMessage * msg )
{
    transitionaction_____BeingMaster( msg );
    entryaction_____RunAsMaster( msg );
}

void Capsule_Server::actionchain_____Debug__ActiveMode( const UMLRTMessage * msg )
{
    transitionaction_____Debug__ActiveMode( msg );
}

void Capsule_Server::actionchain_____Debug__ActiveMode__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ActiveMode__boundary( msg );
    transitionaction_____Debug__ActiveMode__E( msg );
}

void Capsule_Server::actionchain_____Debug__ActiveMode__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__ActiveMode__S( msg );
    entryaction_____Debug__C__ActiveMode__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__ActiveMode__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ActiveMode__boundary( msg );
    transitionaction_____Debug__ActiveMode__dbg( msg );
    entryaction_____Debug__C__ActiveMode__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__BeSlave( const UMLRTMessage * msg )
{
    transitionaction_____Debug__BeSlave( msg );
}

void Capsule_Server::actionchain_____Debug__BeSlave__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__BeSlave__boundary( msg );
    transitionaction_____Debug__BeSlave__E( msg );
    entryaction_____Backup( msg );
}

void Capsule_Server::actionchain_____Debug__BeSlave__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__BeSlave__S( msg );
    entryaction_____Debug__C__BeSlave__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__BeSlave__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__BeSlave__boundary( msg );
    transitionaction_____Debug__BeSlave__dbg( msg );
    entryaction_____Debug__C__BeSlave__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__BeingMaster( const UMLRTMessage * msg )
{
    transitionaction_____Debug__BeingMaster( msg );
}

void Capsule_Server::actionchain_____Debug__BeingMaster__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__BeingMaster__boundary( msg );
    transitionaction_____Debug__BeingMaster__E( msg );
    entryaction_____RunAsMaster( msg );
}

void Capsule_Server::actionchain_____Debug__BeingMaster__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__BeingMaster__S( msg );
    entryaction_____Debug__C__BeingMaster__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__BeingMaster__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__BeingMaster__boundary( msg );
    transitionaction_____Debug__BeingMaster__dbg( msg );
    entryaction_____Debug__C__BeingMaster__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__C__ActiveMode__Debug__Ac__ActiveMode( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ActiveMode__Debug__B__Ac__ActiveMode( msg );
    entryaction_____Debug__C__ActiveMode__Debug__A__Ac__ActiveMode( msg );
}

void Capsule_Server::actionchain_____Debug__C__ActiveMode__Debug__end__trans__ActiveMode( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ActiveMode__Debug__A__Ac__ActiveMode( msg );
    save_history( Debug__C__ActiveMode, Debug__C__ActiveMode__Debug__A__Ac__ActiveMode );
}

void Capsule_Server::actionchain_____Debug__C__ActiveMode__Debug__init__trans__ActiveMode( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ActiveMode__Debug__B__Ac__ActiveMode( msg );
}

void Capsule_Server::actionchain_____Debug__C__ActiveMode__new_transition_118( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ActiveMode__Debug__B__Ac__ActiveMode( msg );
}

void Capsule_Server::actionchain_____Debug__C__ActiveMode__new_transition_119( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ActiveMode__Debug__A__Ac__ActiveMode( msg );
}

void Capsule_Server::actionchain_____Debug__C__ActiveMode__new_transition_120_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ActiveMode__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__C__ActiveMode__new_transition_121( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ActiveMode__Debug__B__Ac__ActiveMode( msg );
    save_history( Debug__C__ActiveMode, Debug__C__ActiveMode__Debug__B__Ac__ActiveMode );
}

void Capsule_Server::actionchain_____Debug__C__ActiveMode__new_transition_122( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ActiveMode__Debug__A__Ac__ActiveMode( msg );
    save_history( Debug__C__ActiveMode, Debug__C__ActiveMode__Debug__A__Ac__ActiveMode );
}

void Capsule_Server::actionchain_____Debug__C__ActiveMode__new_transition_123( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ActiveMode__boundary( msg );
    save_history( Debug__C__ActiveMode, Debug__C__ActiveMode__boundary );
}

void Capsule_Server::actionchain_____Debug__C__BeSlave__Debug__Ac__BeSlave( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__BeSlave__Debug__B__Ac__BeSlave( msg );
    transitionaction_____Debug__C__BeSlave__Debug__Ac__BeSlave( msg );
    entryaction_____Debug__C__BeSlave__Debug__A__Ac__BeSlave( msg );
}

void Capsule_Server::actionchain_____Debug__C__BeSlave__Debug__En__Backup( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__BeSlave__Debug__A__Ac__BeSlave( msg );
    transitionaction_____Debug__C__BeSlave__Debug__En__Backup( msg );
    entryaction_____Debug__C__BeSlave__Debug__A__En__BeSlave( msg );
}

void Capsule_Server::actionchain_____Debug__C__BeSlave__Debug__end__trans__BeSlave( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__BeSlave__Debug__A__En__BeSlave( msg );
    transitionaction_____Debug__C__BeSlave__Debug__end__trans__BeSlave( msg );
    save_history( Debug__C__BeSlave, Debug__C__BeSlave__Debug__A__En__BeSlave );
}

void Capsule_Server::actionchain_____Debug__C__BeSlave__Debug__init__trans__BeSlave( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__BeSlave__Debug__init__trans__BeSlave( msg );
    entryaction_____Debug__C__BeSlave__Debug__B__Ac__BeSlave( msg );
}

void Capsule_Server::actionchain_____Debug__C__BeSlave__new_transition_100( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__BeSlave__Debug__A__En__BeSlave( msg );
    save_history( Debug__C__BeSlave, Debug__C__BeSlave__Debug__A__En__BeSlave );
}

void Capsule_Server::actionchain_____Debug__C__BeSlave__new_transition_101( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__BeSlave__boundary( msg );
    save_history( Debug__C__BeSlave, Debug__C__BeSlave__boundary );
}

void Capsule_Server::actionchain_____Debug__C__BeSlave__new_transition_94( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__BeSlave__Debug__B__Ac__BeSlave( msg );
}

void Capsule_Server::actionchain_____Debug__C__BeSlave__new_transition_95( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__BeSlave__Debug__A__Ac__BeSlave( msg );
}

void Capsule_Server::actionchain_____Debug__C__BeSlave__new_transition_96( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__BeSlave__Debug__A__En__BeSlave( msg );
}

void Capsule_Server::actionchain_____Debug__C__BeSlave__new_transition_97_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__BeSlave__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__C__BeSlave__new_transition_98( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__BeSlave__Debug__B__Ac__BeSlave( msg );
    save_history( Debug__C__BeSlave, Debug__C__BeSlave__Debug__B__Ac__BeSlave );
}

void Capsule_Server::actionchain_____Debug__C__BeSlave__new_transition_99( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__BeSlave__Debug__A__Ac__BeSlave( msg );
    save_history( Debug__C__BeSlave, Debug__C__BeSlave__Debug__A__Ac__BeSlave );
}

void Capsule_Server::actionchain_____Debug__C__BeingMaster__Debug__Ac__BeingMaster( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__BeingMaster__Debug__B__Ac__BeingMaster( msg );
    transitionaction_____Debug__C__BeingMaster__Debug__Ac__BeingMaster( msg );
    entryaction_____Debug__C__BeingMaster__Debug__A__Ac__BeingMaster( msg );
}

void Capsule_Server::actionchain_____Debug__C__BeingMaster__Debug__En__RunAsMaster( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__BeingMaster__Debug__A__Ac__BeingMaster( msg );
    transitionaction_____Debug__C__BeingMaster__Debug__En__RunAsMaster( msg );
    entryaction_____Debug__C__BeingMaster__Debug__A__En__BeingMaster( msg );
}

void Capsule_Server::actionchain_____Debug__C__BeingMaster__Debug__end__trans__BeingMaster( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__BeingMaster__Debug__A__En__BeingMaster( msg );
    transitionaction_____Debug__C__BeingMaster__Debug__end__trans__BeingMaster( msg );
    save_history( Debug__C__BeingMaster, Debug__C__BeingMaster__Debug__A__En__BeingMaster );
}

void Capsule_Server::actionchain_____Debug__C__BeingMaster__Debug__init__trans__BeingMaster( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__BeingMaster__Debug__init__trans__BeingMaster( msg );
    entryaction_____Debug__C__BeingMaster__Debug__B__Ac__BeingMaster( msg );
}

void Capsule_Server::actionchain_____Debug__C__BeingMaster__new_transition_140( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__BeingMaster__Debug__B__Ac__BeingMaster( msg );
}

void Capsule_Server::actionchain_____Debug__C__BeingMaster__new_transition_141( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__BeingMaster__Debug__A__Ac__BeingMaster( msg );
}

void Capsule_Server::actionchain_____Debug__C__BeingMaster__new_transition_142( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__BeingMaster__Debug__A__En__BeingMaster( msg );
}

void Capsule_Server::actionchain_____Debug__C__BeingMaster__new_transition_143_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__BeingMaster__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__C__BeingMaster__new_transition_144( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__BeingMaster__Debug__B__Ac__BeingMaster( msg );
    save_history( Debug__C__BeingMaster, Debug__C__BeingMaster__Debug__B__Ac__BeingMaster );
}

void Capsule_Server::actionchain_____Debug__C__BeingMaster__new_transition_145( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__BeingMaster__Debug__A__Ac__BeingMaster( msg );
    save_history( Debug__C__BeingMaster, Debug__C__BeingMaster__Debug__A__Ac__BeingMaster );
}

void Capsule_Server::actionchain_____Debug__C__BeingMaster__new_transition_146( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__BeingMaster__Debug__A__En__BeingMaster( msg );
    save_history( Debug__C__BeingMaster, Debug__C__BeingMaster__Debug__A__En__BeingMaster );
}

void Capsule_Server::actionchain_____Debug__C__BeingMaster__new_transition_147( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__BeingMaster__boundary( msg );
    save_history( Debug__C__BeingMaster, Debug__C__BeingMaster__boundary );
}

void Capsule_Server::actionchain_____Debug__C__ExitPoint1__BeMaster__4__Debug__Ac__ExitPoint1__BeMaster__4( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ExitPoint1__BeMaster__4__Debug__B__Ac__ExitPoint1__BeMaster__4( msg );
    entryaction_____Debug__C__ExitPoint1__BeMaster__4__Debug__A__Ac__ExitPoint1__BeMaster__4( msg );
}

void Capsule_Server::actionchain_____Debug__C__ExitPoint1__BeMaster__4__Debug__end__trans__ExitPoint1__BeMaster__4( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ExitPoint1__BeMaster__4__Debug__A__Ac__ExitPoint1__BeMaster__4( msg );
    save_history( Debug__C__ExitPoint1__BeMaster__4, Debug__C__ExitPoint1__BeMaster__4__Debug__A__Ac__ExitPoint1__BeMaster__4 );
}

void Capsule_Server::actionchain_____Debug__C__ExitPoint1__BeMaster__4__Debug__init__trans__ExitPoint1__BeMaster__4( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ExitPoint1__BeMaster__4__Debug__B__Ac__ExitPoint1__BeMaster__4( msg );
}

void Capsule_Server::actionchain_____Debug__C__ExitPoint1__BeMaster__4__new_transition_124( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ExitPoint1__BeMaster__4__Debug__B__Ac__ExitPoint1__BeMaster__4( msg );
}

void Capsule_Server::actionchain_____Debug__C__ExitPoint1__BeMaster__4__new_transition_125( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ExitPoint1__BeMaster__4__Debug__A__Ac__ExitPoint1__BeMaster__4( msg );
}

void Capsule_Server::actionchain_____Debug__C__ExitPoint1__BeMaster__4__new_transition_126_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ExitPoint1__BeMaster__4__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__C__ExitPoint1__BeMaster__4__new_transition_127( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ExitPoint1__BeMaster__4__Debug__B__Ac__ExitPoint1__BeMaster__4( msg );
    save_history( Debug__C__ExitPoint1__BeMaster__4, Debug__C__ExitPoint1__BeMaster__4__Debug__B__Ac__ExitPoint1__BeMaster__4 );
}

void Capsule_Server::actionchain_____Debug__C__ExitPoint1__BeMaster__4__new_transition_128( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ExitPoint1__BeMaster__4__Debug__A__Ac__ExitPoint1__BeMaster__4( msg );
    save_history( Debug__C__ExitPoint1__BeMaster__4, Debug__C__ExitPoint1__BeMaster__4__Debug__A__Ac__ExitPoint1__BeMaster__4 );
}

void Capsule_Server::actionchain_____Debug__C__ExitPoint1__BeMaster__4__new_transition_129( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ExitPoint1__BeMaster__4__boundary( msg );
    save_history( Debug__C__ExitPoint1__BeMaster__4, Debug__C__ExitPoint1__BeMaster__4__boundary );
}

void Capsule_Server::actionchain_____Debug__C__Init__StandBy__3__Debug__Ac__Init__StandBy__3( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Init__StandBy__3__Debug__B__Ac__Init__StandBy__3( msg );
    transitionaction_____Debug__C__Init__StandBy__3__Debug__Ac__Init__StandBy__3( msg );
    entryaction_____Debug__C__Init__StandBy__3__Debug__A__Ac__Init__StandBy__3( msg );
}

void Capsule_Server::actionchain_____Debug__C__Init__StandBy__3__Debug__En__StandBy( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Init__StandBy__3__Debug__A__Ac__Init__StandBy__3( msg );
    transitionaction_____Debug__C__Init__StandBy__3__Debug__En__StandBy( msg );
    entryaction_____Debug__C__Init__StandBy__3__Debug__A__En__Init__StandBy__3( msg );
}

void Capsule_Server::actionchain_____Debug__C__Init__StandBy__3__Debug__end__trans__Init__StandBy__3( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Init__StandBy__3__Debug__A__En__Init__StandBy__3( msg );
    transitionaction_____Debug__C__Init__StandBy__3__Debug__end__trans__Init__StandBy__3( msg );
    save_history( Debug__C__Init__StandBy__3, Debug__C__Init__StandBy__3__Debug__A__En__Init__StandBy__3 );
}

void Capsule_Server::actionchain_____Debug__C__Init__StandBy__3__Debug__init__trans__Init__StandBy__3( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__Init__StandBy__3__Debug__init__trans__Init__StandBy__3( msg );
    entryaction_____Debug__C__Init__StandBy__3__Debug__B__Ac__Init__StandBy__3( msg );
}

void Capsule_Server::actionchain_____Debug__C__Init__StandBy__3__new_transition_102( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Init__StandBy__3__Debug__B__Ac__Init__StandBy__3( msg );
}

void Capsule_Server::actionchain_____Debug__C__Init__StandBy__3__new_transition_103( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Init__StandBy__3__Debug__A__Ac__Init__StandBy__3( msg );
}

void Capsule_Server::actionchain_____Debug__C__Init__StandBy__3__new_transition_104( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Init__StandBy__3__Debug__A__En__Init__StandBy__3( msg );
}

void Capsule_Server::actionchain_____Debug__C__Init__StandBy__3__new_transition_105_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Init__StandBy__3__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__C__Init__StandBy__3__new_transition_106( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Init__StandBy__3__Debug__B__Ac__Init__StandBy__3( msg );
    save_history( Debug__C__Init__StandBy__3, Debug__C__Init__StandBy__3__Debug__B__Ac__Init__StandBy__3 );
}

void Capsule_Server::actionchain_____Debug__C__Init__StandBy__3__new_transition_107( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Init__StandBy__3__Debug__A__Ac__Init__StandBy__3( msg );
    save_history( Debug__C__Init__StandBy__3, Debug__C__Init__StandBy__3__Debug__A__Ac__Init__StandBy__3 );
}

void Capsule_Server::actionchain_____Debug__C__Init__StandBy__3__new_transition_108( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Init__StandBy__3__Debug__A__En__Init__StandBy__3( msg );
    save_history( Debug__C__Init__StandBy__3, Debug__C__Init__StandBy__3__Debug__A__En__Init__StandBy__3 );
}

void Capsule_Server::actionchain_____Debug__C__Init__StandBy__3__new_transition_109( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Init__StandBy__3__boundary( msg );
    save_history( Debug__C__Init__StandBy__3, Debug__C__Init__StandBy__3__boundary );
}

void Capsule_Server::actionchain_____Debug__C__KeepAlive__Debug__AC__KeepAlive( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__KeepAlive__Debug__B__Ac__KeepAlive( msg );
    transitionaction_____Debug__C__KeepAlive__Debug__AC__KeepAlive( msg );
    entryaction_____Debug__C__KeepAlive__Debug__A__Ac__KeepAlive( msg );
}

void Capsule_Server::actionchain_____Debug__C__KeepAlive__Debug__En__RunAsMaster( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__KeepAlive__Debug__A__Ac__KeepAlive( msg );
    transitionaction_____Debug__C__KeepAlive__Debug__En__RunAsMaster( msg );
    entryaction_____Debug__C__KeepAlive__Debug__A__En__RunAsMaster( msg );
}

void Capsule_Server::actionchain_____Debug__C__KeepAlive__Debug__Ex__RunAsMaster( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__KeepAlive__Debug__B__Ex__RunAsMaster( msg );
    transitionaction_____Debug__C__KeepAlive__Debug__Ex__RunAsMaster( msg );
    entryaction_____Debug__C__KeepAlive__Debug__B__Ac__KeepAlive( msg );
}

void Capsule_Server::actionchain_____Debug__C__KeepAlive__Debug__end__trans__KeepAlive( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__KeepAlive__Debug__A__En__RunAsMaster( msg );
    transitionaction_____Debug__C__KeepAlive__Debug__end__trans__KeepAlive( msg );
    save_history( Debug__C__KeepAlive, Debug__C__KeepAlive__Debug__A__En__RunAsMaster );
}

void Capsule_Server::actionchain_____Debug__C__KeepAlive__Debug__init__trans__KeepAlive( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__KeepAlive__Debug__init__trans__KeepAlive( msg );
    entryaction_____Debug__C__KeepAlive__Debug__B__Ex__RunAsMaster( msg );
}

void Capsule_Server::actionchain_____Debug__C__KeepAlive__new_transition_130( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__KeepAlive__Debug__B__Ex__RunAsMaster( msg );
}

void Capsule_Server::actionchain_____Debug__C__KeepAlive__new_transition_131( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__KeepAlive__Debug__B__Ac__KeepAlive( msg );
}

void Capsule_Server::actionchain_____Debug__C__KeepAlive__new_transition_132( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__KeepAlive__Debug__A__Ac__KeepAlive( msg );
}

void Capsule_Server::actionchain_____Debug__C__KeepAlive__new_transition_133( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__KeepAlive__Debug__A__En__RunAsMaster( msg );
}

void Capsule_Server::actionchain_____Debug__C__KeepAlive__new_transition_134_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__KeepAlive__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__C__KeepAlive__new_transition_135( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__KeepAlive__Debug__B__Ex__RunAsMaster( msg );
    save_history( Debug__C__KeepAlive, Debug__C__KeepAlive__Debug__B__Ex__RunAsMaster );
}

void Capsule_Server::actionchain_____Debug__C__KeepAlive__new_transition_136( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__KeepAlive__Debug__B__Ac__KeepAlive( msg );
    save_history( Debug__C__KeepAlive, Debug__C__KeepAlive__Debug__B__Ac__KeepAlive );
}

void Capsule_Server::actionchain_____Debug__C__KeepAlive__new_transition_137( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__KeepAlive__Debug__A__Ac__KeepAlive( msg );
    save_history( Debug__C__KeepAlive, Debug__C__KeepAlive__Debug__A__Ac__KeepAlive );
}

void Capsule_Server::actionchain_____Debug__C__KeepAlive__new_transition_138( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__KeepAlive__Debug__A__En__RunAsMaster( msg );
    save_history( Debug__C__KeepAlive, Debug__C__KeepAlive__Debug__A__En__RunAsMaster );
}

void Capsule_Server::actionchain_____Debug__C__KeepAlive__new_transition_139( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__KeepAlive__boundary( msg );
    save_history( Debug__C__KeepAlive, Debug__C__KeepAlive__boundary );
}

void Capsule_Server::actionchain_____Debug__C__PassiveMode__Debug__Ac__PassiveMode( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__PassiveMode__Debug__B__Ac__PassiveMode( msg );
    transitionaction_____Debug__C__PassiveMode__Debug__Ac__PassiveMode( msg );
    entryaction_____Debug__C__PassiveMode__Debug__A__Ac__PassiveMode( msg );
}

void Capsule_Server::actionchain_____Debug__C__PassiveMode__Debug__En__Backup( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__PassiveMode__Debug__A__Ac__PassiveMode( msg );
    transitionaction_____Debug__C__PassiveMode__Debug__En__Backup( msg );
    entryaction_____Debug__C__PassiveMode__Debug__A__En__PassiveMode( msg );
}

void Capsule_Server::actionchain_____Debug__C__PassiveMode__Debug__end__trans__PassiveMode( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__PassiveMode__Debug__A__En__PassiveMode( msg );
    transitionaction_____Debug__C__PassiveMode__Debug__end__trans__PassiveMode( msg );
    save_history( Debug__C__PassiveMode, Debug__C__PassiveMode__Debug__A__En__PassiveMode );
}

void Capsule_Server::actionchain_____Debug__C__PassiveMode__Debug__init__trans__PassiveMode( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__PassiveMode__Debug__init__trans__PassiveMode( msg );
    entryaction_____Debug__C__PassiveMode__Debug__B__Ac__PassiveMode( msg );
}

void Capsule_Server::actionchain_____Debug__C__PassiveMode__new_transition_166( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__PassiveMode__Debug__B__Ac__PassiveMode( msg );
}

void Capsule_Server::actionchain_____Debug__C__PassiveMode__new_transition_167( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__PassiveMode__Debug__A__Ac__PassiveMode( msg );
}

void Capsule_Server::actionchain_____Debug__C__PassiveMode__new_transition_168( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__PassiveMode__Debug__A__En__PassiveMode( msg );
}

void Capsule_Server::actionchain_____Debug__C__PassiveMode__new_transition_169_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__PassiveMode__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__C__PassiveMode__new_transition_170( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__PassiveMode__Debug__B__Ac__PassiveMode( msg );
    save_history( Debug__C__PassiveMode, Debug__C__PassiveMode__Debug__B__Ac__PassiveMode );
}

void Capsule_Server::actionchain_____Debug__C__PassiveMode__new_transition_171( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__PassiveMode__Debug__A__Ac__PassiveMode( msg );
    save_history( Debug__C__PassiveMode, Debug__C__PassiveMode__Debug__A__Ac__PassiveMode );
}

void Capsule_Server::actionchain_____Debug__C__PassiveMode__new_transition_172( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__PassiveMode__Debug__A__En__PassiveMode( msg );
    save_history( Debug__C__PassiveMode, Debug__C__PassiveMode__Debug__A__En__PassiveMode );
}

void Capsule_Server::actionchain_____Debug__C__PassiveMode__new_transition_173( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__PassiveMode__boundary( msg );
    save_history( Debug__C__PassiveMode, Debug__C__PassiveMode__boundary );
}

void Capsule_Server::actionchain_____Debug__C__Recover__Debug__AC__Recover( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Recover__Debug__B__Ac__Recover( msg );
    transitionaction_____Debug__C__Recover__Debug__AC__Recover( msg );
    entryaction_____Debug__C__Recover__Debug__A__Ac__Recover( msg );
}

void Capsule_Server::actionchain_____Debug__C__Recover__Debug__Ex__Failure( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Recover__Debug__B__Ex__Failure( msg );
    transitionaction_____Debug__C__Recover__Debug__Ex__Failure( msg );
    entryaction_____Debug__C__Recover__Debug__B__Ac__Recover( msg );
}

void Capsule_Server::actionchain_____Debug__C__Recover__Debug__end__trans__Recover( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Recover__Debug__A__Ac__Recover( msg );
    transitionaction_____Debug__C__Recover__Debug__end__trans__Recover( msg );
    save_history( Debug__C__Recover, Debug__C__Recover__Debug__A__Ac__Recover );
}

void Capsule_Server::actionchain_____Debug__C__Recover__Debug__init__trans__Recover( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Recover__Debug__B__Ex__Failure( msg );
}

void Capsule_Server::actionchain_____Debug__C__Recover__new_transition_110( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Recover__Debug__B__Ex__Failure( msg );
}

void Capsule_Server::actionchain_____Debug__C__Recover__new_transition_111( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Recover__Debug__B__Ac__Recover( msg );
}

void Capsule_Server::actionchain_____Debug__C__Recover__new_transition_112( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Recover__Debug__A__Ac__Recover( msg );
}

void Capsule_Server::actionchain_____Debug__C__Recover__new_transition_113_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Recover__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__C__Recover__new_transition_114( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Recover__Debug__B__Ex__Failure( msg );
    save_history( Debug__C__Recover, Debug__C__Recover__Debug__B__Ex__Failure );
}

void Capsule_Server::actionchain_____Debug__C__Recover__new_transition_115( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Recover__Debug__B__Ac__Recover( msg );
    save_history( Debug__C__Recover, Debug__C__Recover__Debug__B__Ac__Recover );
}

void Capsule_Server::actionchain_____Debug__C__Recover__new_transition_116( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Recover__Debug__A__Ac__Recover( msg );
    save_history( Debug__C__Recover, Debug__C__Recover__Debug__A__Ac__Recover );
}

void Capsule_Server::actionchain_____Debug__C__Recover__new_transition_117( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Recover__boundary( msg );
    save_history( Debug__C__Recover, Debug__C__Recover__boundary );
}

void Capsule_Server::actionchain_____Debug__C__ServerFaliure__Debug__AC__ServerFaliure( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServerFaliure__Debug__B__Ac__ServerFaliure( msg );
    transitionaction_____Debug__C__ServerFaliure__Debug__AC__ServerFaliure( msg );
    entryaction_____Debug__C__ServerFaliure__Debug__A__Ac__ServerFaliure( msg );
}

void Capsule_Server::actionchain_____Debug__C__ServerFaliure__Debug__En__Failure( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServerFaliure__Debug__A__Ac__ServerFaliure( msg );
    transitionaction_____Debug__C__ServerFaliure__Debug__En__Failure( msg );
    entryaction_____Debug__C__ServerFaliure__Debug__A__En__Failure( msg );
}

void Capsule_Server::actionchain_____Debug__C__ServerFaliure__Debug__Ex__RunAsMaster( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServerFaliure__Debug__B__Ex__RunAsMaster( msg );
    transitionaction_____Debug__C__ServerFaliure__Debug__Ex__RunAsMaster( msg );
    entryaction_____Debug__C__ServerFaliure__Debug__B__Ac__ServerFaliure( msg );
}

void Capsule_Server::actionchain_____Debug__C__ServerFaliure__Debug__end__trans__ServerFaliure( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServerFaliure__Debug__A__En__Failure( msg );
    transitionaction_____Debug__C__ServerFaliure__Debug__end__trans__ServerFaliure( msg );
    save_history( Debug__C__ServerFaliure, Debug__C__ServerFaliure__Debug__A__En__Failure );
}

void Capsule_Server::actionchain_____Debug__C__ServerFaliure__Debug__init__trans__ServerFaliure( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__ServerFaliure__Debug__init__trans__ServerFaliure( msg );
    entryaction_____Debug__C__ServerFaliure__Debug__B__Ex__RunAsMaster( msg );
}

void Capsule_Server::actionchain_____Debug__C__ServerFaliure__new_transition_84( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ServerFaliure__Debug__B__Ex__RunAsMaster( msg );
}

void Capsule_Server::actionchain_____Debug__C__ServerFaliure__new_transition_85( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ServerFaliure__Debug__B__Ac__ServerFaliure( msg );
}

void Capsule_Server::actionchain_____Debug__C__ServerFaliure__new_transition_86( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ServerFaliure__Debug__A__Ac__ServerFaliure( msg );
}

void Capsule_Server::actionchain_____Debug__C__ServerFaliure__new_transition_87( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ServerFaliure__Debug__A__En__Failure( msg );
}

void Capsule_Server::actionchain_____Debug__C__ServerFaliure__new_transition_88_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__ServerFaliure__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__C__ServerFaliure__new_transition_89( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServerFaliure__Debug__B__Ex__RunAsMaster( msg );
    save_history( Debug__C__ServerFaliure, Debug__C__ServerFaliure__Debug__B__Ex__RunAsMaster );
}

void Capsule_Server::actionchain_____Debug__C__ServerFaliure__new_transition_90( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServerFaliure__Debug__B__Ac__ServerFaliure( msg );
    save_history( Debug__C__ServerFaliure, Debug__C__ServerFaliure__Debug__B__Ac__ServerFaliure );
}

void Capsule_Server::actionchain_____Debug__C__ServerFaliure__new_transition_91( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServerFaliure__Debug__A__Ac__ServerFaliure( msg );
    save_history( Debug__C__ServerFaliure, Debug__C__ServerFaliure__Debug__A__Ac__ServerFaliure );
}

void Capsule_Server::actionchain_____Debug__C__ServerFaliure__new_transition_92( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServerFaliure__Debug__A__En__Failure( msg );
    save_history( Debug__C__ServerFaliure, Debug__C__ServerFaliure__Debug__A__En__Failure );
}

void Capsule_Server::actionchain_____Debug__C__ServerFaliure__new_transition_93( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServerFaliure__boundary( msg );
    save_history( Debug__C__ServerFaliure, Debug__C__ServerFaliure__boundary );
}

void Capsule_Server::actionchain_____Debug__C__StandBy__CheckConfig__5__Debug__AC__StandBy__CheckConfig__5( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StandBy__CheckConfig__5__Debug__B__Ac__StandBy__CheckConfig__5( msg );
    transitionaction_____Debug__C__StandBy__CheckConfig__5__Debug__AC__StandBy__CheckConfig__5( msg );
    entryaction_____Debug__C__StandBy__CheckConfig__5__Debug__A__Ac__StandBy__CheckConfig__5( msg );
}

void Capsule_Server::actionchain_____Debug__C__StandBy__CheckConfig__5__Debug__Ex__StandBy( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StandBy__CheckConfig__5__Debug__B__Ex__StandBy( msg );
    transitionaction_____Debug__C__StandBy__CheckConfig__5__Debug__Ex__StandBy( msg );
    entryaction_____Debug__C__StandBy__CheckConfig__5__Debug__B__Ac__StandBy__CheckConfig__5( msg );
}

void Capsule_Server::actionchain_____Debug__C__StandBy__CheckConfig__5__Debug__end__trans__StandBy__CheckConfig__5( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StandBy__CheckConfig__5__Debug__A__Ac__StandBy__CheckConfig__5( msg );
    transitionaction_____Debug__C__StandBy__CheckConfig__5__Debug__end__trans__StandBy__CheckConfig__5( msg );
    save_history( Debug__C__StandBy__CheckConfig__5, Debug__C__StandBy__CheckConfig__5__Debug__A__Ac__StandBy__CheckConfig__5 );
}

void Capsule_Server::actionchain_____Debug__C__StandBy__CheckConfig__5__Debug__init__trans__StandBy__CheckConfig__5( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__StandBy__CheckConfig__5__Debug__B__Ex__StandBy( msg );
}

void Capsule_Server::actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_158( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__StandBy__CheckConfig__5__Debug__B__Ex__StandBy( msg );
}

void Capsule_Server::actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_159( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__StandBy__CheckConfig__5__Debug__B__Ac__StandBy__CheckConfig__5( msg );
}

void Capsule_Server::actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_160( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__StandBy__CheckConfig__5__Debug__A__Ac__StandBy__CheckConfig__5( msg );
}

void Capsule_Server::actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_161_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__StandBy__CheckConfig__5__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_162( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StandBy__CheckConfig__5__Debug__B__Ex__StandBy( msg );
    save_history( Debug__C__StandBy__CheckConfig__5, Debug__C__StandBy__CheckConfig__5__Debug__B__Ex__StandBy );
}

void Capsule_Server::actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_163( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StandBy__CheckConfig__5__Debug__B__Ac__StandBy__CheckConfig__5( msg );
    save_history( Debug__C__StandBy__CheckConfig__5, Debug__C__StandBy__CheckConfig__5__Debug__B__Ac__StandBy__CheckConfig__5 );
}

void Capsule_Server::actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_164( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StandBy__CheckConfig__5__Debug__A__Ac__StandBy__CheckConfig__5( msg );
    save_history( Debug__C__StandBy__CheckConfig__5, Debug__C__StandBy__CheckConfig__5__Debug__A__Ac__StandBy__CheckConfig__5 );
}

void Capsule_Server::actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_165( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StandBy__CheckConfig__5__boundary( msg );
    save_history( Debug__C__StandBy__CheckConfig__5, Debug__C__StandBy__CheckConfig__5__boundary );
}

void Capsule_Server::actionchain_____Debug__C__initTimer__Debug__Ac__initTimer( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__initTimer__Debug__B__Ac__initTimer( msg );
    transitionaction_____Debug__C__initTimer__Debug__Ac__initTimer( msg );
    entryaction_____Debug__C__initTimer__Debug__A__Ac__initTimer( msg );
}

void Capsule_Server::actionchain_____Debug__C__initTimer__Debug__En__RunAsMaster( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__initTimer__Debug__A__Ac__initTimer( msg );
    transitionaction_____Debug__C__initTimer__Debug__En__RunAsMaster( msg );
    entryaction_____Debug__C__initTimer__Debug__A__En__initTimer( msg );
}

void Capsule_Server::actionchain_____Debug__C__initTimer__Debug__end__trans__initTimer( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__initTimer__Debug__A__En__initTimer( msg );
    transitionaction_____Debug__C__initTimer__Debug__end__trans__initTimer( msg );
    save_history( Debug__C__initTimer, Debug__C__initTimer__Debug__A__En__initTimer );
}

void Capsule_Server::actionchain_____Debug__C__initTimer__Debug__init__trans__initTimer( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__initTimer__Debug__init__trans__initTimer( msg );
    entryaction_____Debug__C__initTimer__Debug__B__Ac__initTimer( msg );
}

void Capsule_Server::actionchain_____Debug__C__initTimer__new_transition_76( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__initTimer__Debug__B__Ac__initTimer( msg );
}

void Capsule_Server::actionchain_____Debug__C__initTimer__new_transition_77( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__initTimer__Debug__A__Ac__initTimer( msg );
}

void Capsule_Server::actionchain_____Debug__C__initTimer__new_transition_78( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__initTimer__Debug__A__En__initTimer( msg );
}

void Capsule_Server::actionchain_____Debug__C__initTimer__new_transition_79_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__initTimer__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__C__initTimer__new_transition_80( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__initTimer__Debug__B__Ac__initTimer( msg );
    save_history( Debug__C__initTimer, Debug__C__initTimer__Debug__B__Ac__initTimer );
}

void Capsule_Server::actionchain_____Debug__C__initTimer__new_transition_81( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__initTimer__Debug__A__Ac__initTimer( msg );
    save_history( Debug__C__initTimer, Debug__C__initTimer__Debug__A__Ac__initTimer );
}

void Capsule_Server::actionchain_____Debug__C__initTimer__new_transition_82( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__initTimer__Debug__A__En__initTimer( msg );
    save_history( Debug__C__initTimer, Debug__C__initTimer__Debug__A__En__initTimer );
}

void Capsule_Server::actionchain_____Debug__C__initTimer__new_transition_83( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__initTimer__boundary( msg );
    save_history( Debug__C__initTimer, Debug__C__initTimer__boundary );
}

void Capsule_Server::actionchain_____Debug__C__purgeotherMessage__Debug__AC__purgeotherMessage( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__purgeotherMessage__Debug__B__Ac__purgeotherMessage( msg );
    transitionaction_____Debug__C__purgeotherMessage__Debug__AC__purgeotherMessage( msg );
    entryaction_____Debug__C__purgeotherMessage__Debug__A__Ac__purgeotherMessage( msg );
}

void Capsule_Server::actionchain_____Debug__C__purgeotherMessage__Debug__En__Failure( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__purgeotherMessage__Debug__A__Ac__purgeotherMessage( msg );
    transitionaction_____Debug__C__purgeotherMessage__Debug__En__Failure( msg );
    entryaction_____Debug__C__purgeotherMessage__Debug__A__En__Failure( msg );
}

void Capsule_Server::actionchain_____Debug__C__purgeotherMessage__Debug__Ex__Failure( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__purgeotherMessage__Debug__B__Ex__Failure( msg );
    transitionaction_____Debug__C__purgeotherMessage__Debug__Ex__Failure( msg );
    entryaction_____Debug__C__purgeotherMessage__Debug__B__Ac__purgeotherMessage( msg );
}

void Capsule_Server::actionchain_____Debug__C__purgeotherMessage__Debug__end__trans__purgeotherMessage( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__purgeotherMessage__Debug__A__En__Failure( msg );
    transitionaction_____Debug__C__purgeotherMessage__Debug__end__trans__purgeotherMessage( msg );
    save_history( Debug__C__purgeotherMessage, Debug__C__purgeotherMessage__Debug__A__En__Failure );
}

void Capsule_Server::actionchain_____Debug__C__purgeotherMessage__Debug__init__trans__purgeotherMessage( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__purgeotherMessage__Debug__init__trans__purgeotherMessage( msg );
    entryaction_____Debug__C__purgeotherMessage__Debug__B__Ex__Failure( msg );
}

void Capsule_Server::actionchain_____Debug__C__purgeotherMessage__new_transition_148( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__purgeotherMessage__Debug__B__Ex__Failure( msg );
}

void Capsule_Server::actionchain_____Debug__C__purgeotherMessage__new_transition_149( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__purgeotherMessage__Debug__B__Ac__purgeotherMessage( msg );
}

void Capsule_Server::actionchain_____Debug__C__purgeotherMessage__new_transition_150( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__purgeotherMessage__Debug__A__Ac__purgeotherMessage( msg );
}

void Capsule_Server::actionchain_____Debug__C__purgeotherMessage__new_transition_151( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__purgeotherMessage__Debug__A__En__Failure( msg );
}

void Capsule_Server::actionchain_____Debug__C__purgeotherMessage__new_transition_152_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__purgeotherMessage__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__C__purgeotherMessage__new_transition_153( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__purgeotherMessage__Debug__B__Ex__Failure( msg );
    save_history( Debug__C__purgeotherMessage, Debug__C__purgeotherMessage__Debug__B__Ex__Failure );
}

void Capsule_Server::actionchain_____Debug__C__purgeotherMessage__new_transition_154( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__purgeotherMessage__Debug__B__Ac__purgeotherMessage( msg );
    save_history( Debug__C__purgeotherMessage, Debug__C__purgeotherMessage__Debug__B__Ac__purgeotherMessage );
}

void Capsule_Server::actionchain_____Debug__C__purgeotherMessage__new_transition_155( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__purgeotherMessage__Debug__A__Ac__purgeotherMessage( msg );
    save_history( Debug__C__purgeotherMessage, Debug__C__purgeotherMessage__Debug__A__Ac__purgeotherMessage );
}

void Capsule_Server::actionchain_____Debug__C__purgeotherMessage__new_transition_156( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__purgeotherMessage__Debug__A__En__Failure( msg );
    save_history( Debug__C__purgeotherMessage, Debug__C__purgeotherMessage__Debug__A__En__Failure );
}

void Capsule_Server::actionchain_____Debug__C__purgeotherMessage__new_transition_157( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__purgeotherMessage__boundary( msg );
    save_history( Debug__C__purgeotherMessage, Debug__C__purgeotherMessage__boundary );
}

void Capsule_Server::actionchain_____Debug__ExitPoint1__BeMaster__4( const UMLRTMessage * msg )
{
    exitaction_____Backup( msg );
    transitionaction_____Debug__ExitPoint1__BeMaster__4( msg );
}

void Capsule_Server::actionchain_____Debug__ExitPoint1__BeMaster__4__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ExitPoint1__BeMaster__4__boundary( msg );
    transitionaction_____Debug__ExitPoint1__BeMaster__4__E( msg );
}

void Capsule_Server::actionchain_____Debug__ExitPoint1__BeMaster__4__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__ExitPoint1__BeMaster__4__S( msg );
    entryaction_____Debug__C__ExitPoint1__BeMaster__4__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__ExitPoint1__BeMaster__4__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ExitPoint1__BeMaster__4__boundary( msg );
    transitionaction_____Debug__ExitPoint1__BeMaster__4__dbg( msg );
    entryaction_____Debug__C__ExitPoint1__BeMaster__4__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__InitDebug( const UMLRTMessage * msg )
{
    transitionaction_____Debug__InitDebug( msg );
    entryaction_____Debug__InitState( msg );
}

void Capsule_Server::actionchain_____Debug__Init__StandBy__3( const UMLRTMessage * msg )
{
    exitaction_____Debug__InitState( msg );
    transitionaction_____Debug__Init__StandBy__3( msg );
}

void Capsule_Server::actionchain_____Debug__Init__StandBy__3__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Init__StandBy__3__boundary( msg );
    transitionaction_____Debug__Init__StandBy__3__E( msg );
    entryaction_____StandBy( msg );
}

void Capsule_Server::actionchain_____Debug__Init__StandBy__3__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__Init__StandBy__3__S( msg );
    entryaction_____Debug__C__Init__StandBy__3__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__Init__StandBy__3__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Init__StandBy__3__boundary( msg );
    transitionaction_____Debug__Init__StandBy__3__dbg( msg );
    entryaction_____Debug__C__Init__StandBy__3__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__KeepAlive( const UMLRTMessage * msg )
{
    exitaction_____RunAsMaster( msg );
    transitionaction_____Debug__KeepAlive( msg );
}

void Capsule_Server::actionchain_____Debug__KeepAlive__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__KeepAlive__boundary( msg );
    transitionaction_____Debug__KeepAlive__E( msg );
    entryaction_____RunAsMaster( msg );
}

void Capsule_Server::actionchain_____Debug__KeepAlive__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__KeepAlive__S( msg );
    entryaction_____Debug__C__KeepAlive__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__KeepAlive__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__KeepAlive__boundary( msg );
    transitionaction_____Debug__KeepAlive__dbg( msg );
    entryaction_____Debug__C__KeepAlive__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__MasterAnnounce( const UMLRTMessage * msg )
{
    exitaction_____RunAsMaster( msg );
    transitionaction_____Debug__MasterAnnounce( msg );
}

void Capsule_Server::actionchain_____Debug__MasterAnnounce__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__MasterAnnounce( msg );
    transitionaction_____Debug__MasterAnnounce__E( msg );
    entryaction_____RunAsMaster( msg );
}

void Capsule_Server::actionchain_____Debug__MasterAnnounce__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__MasterAnnounce__S( msg );
    entryaction_____Debug__C__MasterAnnounce( msg );
}

void Capsule_Server::actionchain_____Debug__MasterAnnounce__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__MasterAnnounce( msg );
    transitionaction_____Debug__MasterAnnounce__dbg( msg );
    entryaction_____Debug__C__MasterAnnounce( msg );
}

void Capsule_Server::actionchain_____Debug__PassiveMode( const UMLRTMessage * msg )
{
    transitionaction_____Debug__PassiveMode( msg );
}

void Capsule_Server::actionchain_____Debug__PassiveMode__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__PassiveMode__boundary( msg );
    transitionaction_____Debug__PassiveMode__E( msg );
    entryaction_____Backup( msg );
}

void Capsule_Server::actionchain_____Debug__PassiveMode__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__PassiveMode__S( msg );
    entryaction_____Debug__C__PassiveMode__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__PassiveMode__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__PassiveMode__boundary( msg );
    transitionaction_____Debug__PassiveMode__dbg( msg );
    entryaction_____Debug__C__PassiveMode__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__Recover( const UMLRTMessage * msg )
{
    exitaction_____Failure( msg );
    transitionaction_____Debug__Recover( msg );
}

void Capsule_Server::actionchain_____Debug__Recover__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Recover__boundary( msg );
    transitionaction_____Debug__Recover__E( msg );
}

void Capsule_Server::actionchain_____Debug__Recover__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__Recover__S( msg );
    entryaction_____Debug__C__Recover__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__Recover__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Recover__boundary( msg );
    transitionaction_____Debug__Recover__dbg( msg );
    entryaction_____Debug__C__Recover__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__ServerFaliure( const UMLRTMessage * msg )
{
    exitaction_____RunAsMaster( msg );
    transitionaction_____Debug__ServerFaliure( msg );
}

void Capsule_Server::actionchain_____Debug__ServerFaliure__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServerFaliure__boundary( msg );
    transitionaction_____Debug__ServerFaliure__E( msg );
    entryaction_____Failure( msg );
}

void Capsule_Server::actionchain_____Debug__ServerFaliure__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__ServerFaliure__S( msg );
    entryaction_____Debug__C__ServerFaliure__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__ServerFaliure__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServerFaliure__boundary( msg );
    transitionaction_____Debug__ServerFaliure__dbg( msg );
    entryaction_____Debug__C__ServerFaliure__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__ServiceRequest( const UMLRTMessage * msg )
{
    exitaction_____RunAsMaster( msg );
    transitionaction_____Debug__ServiceRequest( msg );
}

void Capsule_Server::actionchain_____Debug__ServiceRequest__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServiceRequest( msg );
    transitionaction_____Debug__ServiceRequest__E( msg );
    entryaction_____RunAsMaster( msg );
}

void Capsule_Server::actionchain_____Debug__ServiceRequest__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__ServiceRequest__S( msg );
    entryaction_____Debug__C__ServiceRequest( msg );
}

void Capsule_Server::actionchain_____Debug__ServiceRequest__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__ServiceRequest( msg );
    transitionaction_____Debug__ServiceRequest__dbg( msg );
    entryaction_____Debug__C__ServiceRequest( msg );
}

void Capsule_Server::actionchain_____Debug__StandBy__CheckConfig__5( const UMLRTMessage * msg )
{
    exitaction_____StandBy( msg );
    transitionaction_____Debug__StandBy__CheckConfig__5( msg );
}

void Capsule_Server::actionchain_____Debug__StandBy__CheckConfig__5__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StandBy__CheckConfig__5__boundary( msg );
    transitionaction_____Debug__StandBy__CheckConfig__5__E( msg );
}

void Capsule_Server::actionchain_____Debug__StandBy__CheckConfig__5__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__StandBy__CheckConfig__5__S( msg );
    entryaction_____Debug__C__StandBy__CheckConfig__5__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__StandBy__CheckConfig__5__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StandBy__CheckConfig__5__boundary( msg );
    transitionaction_____Debug__StandBy__CheckConfig__5__dbg( msg );
    entryaction_____Debug__C__StandBy__CheckConfig__5__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__initTimer( const UMLRTMessage * msg )
{
    transitionaction_____Debug__initTimer( msg );
}

void Capsule_Server::actionchain_____Debug__initTimer__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__initTimer__boundary( msg );
    transitionaction_____Debug__initTimer__E( msg );
    entryaction_____RunAsMaster( msg );
}

void Capsule_Server::actionchain_____Debug__initTimer__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__initTimer__S( msg );
    entryaction_____Debug__C__initTimer__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__initTimer__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__initTimer__boundary( msg );
    transitionaction_____Debug__initTimer__dbg( msg );
    entryaction_____Debug__C__initTimer__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__purgeotherMessage( const UMLRTMessage * msg )
{
    exitaction_____Failure( msg );
    transitionaction_____Debug__purgeotherMessage( msg );
}

void Capsule_Server::actionchain_____Debug__purgeotherMessage__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__purgeotherMessage__boundary( msg );
    transitionaction_____Debug__purgeotherMessage__E( msg );
    entryaction_____Failure( msg );
}

void Capsule_Server::actionchain_____Debug__purgeotherMessage__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__purgeotherMessage__S( msg );
    entryaction_____Debug__C__purgeotherMessage__boundary( msg );
}

void Capsule_Server::actionchain_____Debug__purgeotherMessage__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__purgeotherMessage__boundary( msg );
    transitionaction_____Debug__purgeotherMessage__dbg( msg );
    entryaction_____Debug__C__purgeotherMessage__boundary( msg );
}

void Capsule_Server::actionchain_____ExitPoint1__BeMaster__4( const UMLRTMessage * msg )
{
    transitionaction_____ExitPoint1__BeMaster__4( msg );
}

void Capsule_Server::actionchain_____Init__StandBy__3( const UMLRTMessage * msg )
{
    transitionaction_____Init__StandBy__3( msg );
    entryaction_____StandBy( msg );
}

void Capsule_Server::actionchain_____KeepAlive( const UMLRTMessage * msg )
{
    transitionaction_____KeepAlive( msg );
    entryaction_____RunAsMaster( msg );
}

void Capsule_Server::actionchain_____MasterAnnounce( const UMLRTMessage * msg )
{
    transitionaction_____MasterAnnounce( msg );
}

void Capsule_Server::actionchain_____PassiveMode( const UMLRTMessage * msg )
{
    transitionaction_____PassiveMode( msg );
    entryaction_____Backup( msg );
}

void Capsule_Server::actionchain_____Recover( const UMLRTMessage * msg )
{
    transitionaction_____Recover( msg );
}

void Capsule_Server::actionchain_____ServerFaliure( const UMLRTMessage * msg )
{
    transitionaction_____ServerFaliure( msg );
    entryaction_____Failure( msg );
}

void Capsule_Server::actionchain_____ServiceRequest( const UMLRTMessage * msg )
{
    transitionaction_____ServiceRequest( msg );
}

void Capsule_Server::actionchain_____StandBy__CheckConfig__5( const UMLRTMessage * msg )
{
    transitionaction_____StandBy__CheckConfig__5( msg );
}

void Capsule_Server::actionchain_____initTimer( const UMLRTMessage * msg )
{
    transitionaction_____initTimer( msg );
    entryaction_____RunAsMaster( msg );
}

void Capsule_Server::actionchain_____purgeotherMessage( const UMLRTMessage * msg )
{
    transitionaction_____purgeotherMessage( msg );
    entryaction_____Failure( msg );
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__BackToSlave__en( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__C__BackToSlave__Debug__init__trans__BackToSlave( msg );
    return Backup__Debug__C__BackToSlave__Debug__B__Ex__TryBeMaster;
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__BackToSlave__ex( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__BackToSlave__E( msg );
    return junction_____Backup__Slave( msg );
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__BackToSlave__new_exitpoint_2( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__BackToSlave__dbg( msg );
    return choice_____Backup__Debug__C__BackToSlave__deephistory( msg );
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__CheckNoMaster__en( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__C__CheckNoMaster__Debug__init__trans__CheckNoMaster( msg );
    return Backup__Debug__C__CheckNoMaster__Debug__B__Ac__CheckNoMaster;
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__CheckNoMaster__ex( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__CheckNoMaster__E( msg );
    return junction_____Backup__ExitPoint1( msg );
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__CheckNoMaster__new_exitpoint_7( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__CheckNoMaster__dbg( msg );
    return choice_____Backup__Debug__C__CheckNoMaster__deephistory( msg );
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__Initial1__RunAsSlave__2__en( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__init__trans__Initial1__RunAsSlave__2( msg );
    return Backup__Debug__C__Initial1__RunAsSlave__2__Debug__B__Ac__Initial1__RunAsSlave__2;
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__Initial1__RunAsSlave__2__ex( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__Initial1__RunAsSlave__2__E( msg );
    return Backup__RunAsSlave;
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__Initial1__RunAsSlave__2__new_exitpoint_1( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__Initial1__RunAsSlave__2__dbg( msg );
    return choice_____Backup__Debug__C__Initial1__RunAsSlave__2__deephistory( msg );
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__KeepAliveMsg__en( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__C__KeepAliveMsg__Debug__init__trans__KeepAliveMsg( msg );
    return Backup__Debug__C__KeepAliveMsg__Debug__B__Ex__RunAsSlave;
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__KeepAliveMsg__ex( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__KeepAliveMsg__E( msg );
    return Backup__RunAsSlave;
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__KeepAliveMsg__new_exitpoint_6( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__KeepAliveMsg__dbg( msg );
    return choice_____Backup__Debug__C__KeepAliveMsg__deephistory( msg );
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__NokeepAlive__en( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__C__NokeepAlive__Debug__init__trans__NokeepAlive( msg );
    return Backup__Debug__C__NokeepAlive__Debug__B__Ex__RunAsSlave;
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__NokeepAlive__ex( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__NokeepAlive__E( msg );
    return Backup__TryBeMaster;
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__NokeepAlive__new_exitpoint_8( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__NokeepAlive__dbg( msg );
    return choice_____Backup__Debug__C__NokeepAlive__deephistory( msg );
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__ReplyConfig__en( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__C__ReplyConfig__Debug__init__trans__ReplyConfig( msg );
    return Backup__Debug__C__ReplyConfig__Debug__B__Ex__TryBeMaster;
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__ReplyConfig__ex( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__ReplyConfig__E( msg );
    return choice_____Backup__Choice2( msg );
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__ReplyConfig__new_exitpoint_4( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__ReplyConfig__dbg( msg );
    return choice_____Backup__Debug__C__ReplyConfig__deephistory( msg );
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__backtoslave1__en( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__C__backtoslave1__Debug__init__trans__backtoslave1( msg );
    return Backup__Debug__C__backtoslave1__Debug__B__Ac__backtoslave1;
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__backtoslave1__ex( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__backtoslave1__E( msg );
    return junction_____Backup__Slave( msg );
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__backtoslave1__new_exitpoint_5( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__backtoslave1__dbg( msg );
    return choice_____Backup__Debug__C__backtoslave1__deephistory( msg );
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__backtoslave__en( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__C__backtoslave__Debug__init__trans__backtoslave( msg );
    return Backup__Debug__C__backtoslave__Debug__B__Ac__backtoslave;
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__backtoslave__ex( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__backtoslave__E( msg );
    return Backup__RunAsSlave;
}

Capsule_Server::State Capsule_Server::junction_____Backup__Debug__C__backtoslave__new_exitpoint_3( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__backtoslave__dbg( msg );
    return choice_____Backup__Debug__C__backtoslave__deephistory( msg );
}

Capsule_Server::State Capsule_Server::junction_____Backup__ExitPoint1( const UMLRTMessage * msg )
{
    actionchain_____Debug__ExitPoint1__BeMaster__4( msg );
    return choice_____Debug__Path__ExitPoint1__BeMaster__4( msg );
}

Capsule_Server::State Capsule_Server::junction_____Backup__Slave( const UMLRTMessage * msg )
{
    actionchain_____Backup__Debug__backtoslave( msg );
    return choice_____Backup__Debug__Path__backtoslave( msg );
}

Capsule_Server::State Capsule_Server::junction_____BeMaster( const UMLRTMessage * msg )
{
    actionchain_____Debug__BeingMaster( msg );
    return choice_____Debug__Path__BeingMaster( msg );
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__ActiveMode__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__ActiveMode__Debug__init__trans__ActiveMode( msg );
    return Debug__C__ActiveMode__Debug__B__Ac__ActiveMode;
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__ActiveMode__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__ActiveMode__E( msg );
    return junction_____BeMaster( msg );
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__ActiveMode__new_exitpoint_14( const UMLRTMessage * msg )
{
    actionchain_____Debug__ActiveMode__dbg( msg );
    return choice_____Debug__C__ActiveMode__deephistory( msg );
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__BeSlave__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__BeSlave__Debug__init__trans__BeSlave( msg );
    return Debug__C__BeSlave__Debug__B__Ac__BeSlave;
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__BeSlave__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__BeSlave__E( msg );
    return choice_____Backup__deephistory( msg );
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__BeSlave__new_exitpoint_11( const UMLRTMessage * msg )
{
    actionchain_____Debug__BeSlave__dbg( msg );
    return choice_____Debug__C__BeSlave__deephistory( msg );
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__BeingMaster__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__BeingMaster__Debug__init__trans__BeingMaster( msg );
    return Debug__C__BeingMaster__Debug__B__Ac__BeingMaster;
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__BeingMaster__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__BeingMaster__E( msg );
    return RunAsMaster;
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__BeingMaster__new_exitpoint_17( const UMLRTMessage * msg )
{
    actionchain_____Debug__BeingMaster__dbg( msg );
    return choice_____Debug__C__BeingMaster__deephistory( msg );
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__ExitPoint1__BeMaster__4__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__ExitPoint1__BeMaster__4__Debug__init__trans__ExitPoint1__BeMaster__4( msg );
    return Debug__C__ExitPoint1__BeMaster__4__Debug__B__Ac__ExitPoint1__BeMaster__4;
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__ExitPoint1__BeMaster__4__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__ExitPoint1__BeMaster__4__E( msg );
    return junction_____BeMaster( msg );
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__ExitPoint1__BeMaster__4__new_exitpoint_15( const UMLRTMessage * msg )
{
    actionchain_____Debug__ExitPoint1__BeMaster__4__dbg( msg );
    return choice_____Debug__C__ExitPoint1__BeMaster__4__deephistory( msg );
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__Init__StandBy__3__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__Init__StandBy__3__Debug__init__trans__Init__StandBy__3( msg );
    return Debug__C__Init__StandBy__3__Debug__B__Ac__Init__StandBy__3;
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__Init__StandBy__3__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__Init__StandBy__3__E( msg );
    return StandBy;
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__Init__StandBy__3__new_exitpoint_12( const UMLRTMessage * msg )
{
    actionchain_____Debug__Init__StandBy__3__dbg( msg );
    return choice_____Debug__C__Init__StandBy__3__deephistory( msg );
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__KeepAlive__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__KeepAlive__Debug__init__trans__KeepAlive( msg );
    return Debug__C__KeepAlive__Debug__B__Ex__RunAsMaster;
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__KeepAlive__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__KeepAlive__E( msg );
    return RunAsMaster;
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__KeepAlive__new_exitpoint_16( const UMLRTMessage * msg )
{
    actionchain_____Debug__KeepAlive__dbg( msg );
    return choice_____Debug__C__KeepAlive__deephistory( msg );
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__PassiveMode__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__PassiveMode__Debug__init__trans__PassiveMode( msg );
    return Debug__C__PassiveMode__Debug__B__Ac__PassiveMode;
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__PassiveMode__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__PassiveMode__E( msg );
    return choice_____Backup__deephistory( msg );
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__PassiveMode__new_exitpoint_20( const UMLRTMessage * msg )
{
    actionchain_____Debug__PassiveMode__dbg( msg );
    return choice_____Debug__C__PassiveMode__deephistory( msg );
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__Recover__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__Recover__Debug__init__trans__Recover( msg );
    return Debug__C__Recover__Debug__B__Ex__Failure;
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__Recover__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__Recover__E( msg );
    return choice_____Choice1( msg );
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__Recover__new_exitpoint_13( const UMLRTMessage * msg )
{
    actionchain_____Debug__Recover__dbg( msg );
    return choice_____Debug__C__Recover__deephistory( msg );
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__ServerFaliure__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__ServerFaliure__Debug__init__trans__ServerFaliure( msg );
    return Debug__C__ServerFaliure__Debug__B__Ex__RunAsMaster;
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__ServerFaliure__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__ServerFaliure__E( msg );
    return Failure;
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__ServerFaliure__new_exitpoint_10( const UMLRTMessage * msg )
{
    actionchain_____Debug__ServerFaliure__dbg( msg );
    return choice_____Debug__C__ServerFaliure__deephistory( msg );
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__StandBy__CheckConfig__5__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__StandBy__CheckConfig__5__Debug__init__trans__StandBy__CheckConfig__5( msg );
    return Debug__C__StandBy__CheckConfig__5__Debug__B__Ex__StandBy;
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__StandBy__CheckConfig__5__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__StandBy__CheckConfig__5__E( msg );
    return choice_____CheckConfig( msg );
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__StandBy__CheckConfig__5__new_exitpoint_19( const UMLRTMessage * msg )
{
    actionchain_____Debug__StandBy__CheckConfig__5__dbg( msg );
    return choice_____Debug__C__StandBy__CheckConfig__5__deephistory( msg );
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__initTimer__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__initTimer__Debug__init__trans__initTimer( msg );
    return Debug__C__initTimer__Debug__B__Ac__initTimer;
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__initTimer__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__initTimer__E( msg );
    return RunAsMaster;
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__initTimer__new_exitpoint_9( const UMLRTMessage * msg )
{
    actionchain_____Debug__initTimer__dbg( msg );
    return choice_____Debug__C__initTimer__deephistory( msg );
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__purgeotherMessage__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__purgeotherMessage__Debug__init__trans__purgeotherMessage( msg );
    return Debug__C__purgeotherMessage__Debug__B__Ex__Failure;
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__purgeotherMessage__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__purgeotherMessage__E( msg );
    return Failure;
}

Capsule_Server::State Capsule_Server::junction_____Debug__C__purgeotherMessage__new_exitpoint_18( const UMLRTMessage * msg )
{
    actionchain_____Debug__purgeotherMessage__dbg( msg );
    return choice_____Debug__C__purgeotherMessage__deephistory( msg );
}

Capsule_Server::State Capsule_Server::choice_____Backup__Choice2( const UMLRTMessage * msg )
{
    if( action_____Backup__Debug__CheckNoMaster__CheckNoServer( msg ) )
    {
        actionchain_____Backup__Debug__CheckNoMaster( msg );
        return choice_____Backup__Debug__Path__CheckNoMaster( msg );
    }
    else
    {
        actionchain_____Backup__Debug__backtoslave1( msg );
        return choice_____Backup__Debug__Path__backtoslave1( msg );
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Backup__Debug__C__BackToSlave__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Backup__Debug__C__BackToSlave, Backup__Debug__C__BackToSlave__Debug__B__Ex__TryBeMaster ) )
    {
        actionchain_____Backup__Debug__C__BackToSlave__new_transition_20( msg );
        return Backup__Debug__C__BackToSlave__Debug__B__Ex__TryBeMaster;
    }
    else if( check_history( Backup__Debug__C__BackToSlave, Backup__Debug__C__BackToSlave__Debug__B__Ac__BackToSlave ) )
    {
        actionchain_____Backup__Debug__C__BackToSlave__new_transition_21( msg );
        return Backup__Debug__C__BackToSlave__Debug__B__Ac__BackToSlave;
    }
    else if( check_history( Backup__Debug__C__BackToSlave, Backup__Debug__C__BackToSlave__Debug__A__Ac__BackToSlave ) )
    {
        actionchain_____Backup__Debug__C__BackToSlave__new_transition_22( msg );
        return Backup__Debug__C__BackToSlave__Debug__A__Ac__BackToSlave;
    }
    else if( check_history( Backup__Debug__C__BackToSlave, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Backup__Debug__C__BackToSlave__new_transition_23_to_boundary( msg );
        return Backup__Debug__C__BackToSlave__boundary;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Backup__Debug__C__CheckNoMaster__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Backup__Debug__C__CheckNoMaster, Backup__Debug__C__CheckNoMaster__Debug__B__Ac__CheckNoMaster ) )
    {
        actionchain_____Backup__Debug__C__CheckNoMaster__new_transition_60( msg );
        return Backup__Debug__C__CheckNoMaster__Debug__B__Ac__CheckNoMaster;
    }
    else if( check_history( Backup__Debug__C__CheckNoMaster, Backup__Debug__C__CheckNoMaster__Debug__A__Ac__CheckNoMaster ) )
    {
        actionchain_____Backup__Debug__C__CheckNoMaster__new_transition_61( msg );
        return Backup__Debug__C__CheckNoMaster__Debug__A__Ac__CheckNoMaster;
    }
    else if( check_history( Backup__Debug__C__CheckNoMaster, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Backup__Debug__C__CheckNoMaster__new_transition_62_to_boundary( msg );
        return Backup__Debug__C__CheckNoMaster__boundary;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Backup__Debug__C__Initial1__RunAsSlave__2__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Backup__Debug__C__Initial1__RunAsSlave__2, Backup__Debug__C__Initial1__RunAsSlave__2__Debug__B__Ac__Initial1__RunAsSlave__2 ) )
    {
        actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_12( msg );
        return Backup__Debug__C__Initial1__RunAsSlave__2__Debug__B__Ac__Initial1__RunAsSlave__2;
    }
    else if( check_history( Backup__Debug__C__Initial1__RunAsSlave__2, Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__Ac__Initial1__RunAsSlave__2 ) )
    {
        actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_13( msg );
        return Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__Ac__Initial1__RunAsSlave__2;
    }
    else if( check_history( Backup__Debug__C__Initial1__RunAsSlave__2, Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__En__Initial1__RunAsSlave__2 ) )
    {
        actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_14( msg );
        return Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__En__Initial1__RunAsSlave__2;
    }
    else if( check_history( Backup__Debug__C__Initial1__RunAsSlave__2, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_15_to_boundary( msg );
        return Backup__Debug__C__Initial1__RunAsSlave__2__boundary;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Backup__Debug__C__KeepAliveMsg__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Backup__Debug__C__KeepAliveMsg, Backup__Debug__C__KeepAliveMsg__Debug__B__Ex__RunAsSlave ) )
    {
        actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_50( msg );
        return Backup__Debug__C__KeepAliveMsg__Debug__B__Ex__RunAsSlave;
    }
    else if( check_history( Backup__Debug__C__KeepAliveMsg, Backup__Debug__C__KeepAliveMsg__Debug__B__Ac__KeepAliveMsg ) )
    {
        actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_51( msg );
        return Backup__Debug__C__KeepAliveMsg__Debug__B__Ac__KeepAliveMsg;
    }
    else if( check_history( Backup__Debug__C__KeepAliveMsg, Backup__Debug__C__KeepAliveMsg__Debug__A__Ac__KeepAliveMsg ) )
    {
        actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_52( msg );
        return Backup__Debug__C__KeepAliveMsg__Debug__A__Ac__KeepAliveMsg;
    }
    else if( check_history( Backup__Debug__C__KeepAliveMsg, Backup__Debug__C__KeepAliveMsg__Debug__A__En__RunAsSlave ) )
    {
        actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_53( msg );
        return Backup__Debug__C__KeepAliveMsg__Debug__A__En__RunAsSlave;
    }
    else if( check_history( Backup__Debug__C__KeepAliveMsg, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_54_to_boundary( msg );
        return Backup__Debug__C__KeepAliveMsg__boundary;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Backup__Debug__C__NokeepAlive__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Backup__Debug__C__NokeepAlive, Backup__Debug__C__NokeepAlive__Debug__B__Ex__RunAsSlave ) )
    {
        actionchain_____Backup__Debug__C__NokeepAlive__new_transition_66( msg );
        return Backup__Debug__C__NokeepAlive__Debug__B__Ex__RunAsSlave;
    }
    else if( check_history( Backup__Debug__C__NokeepAlive, Backup__Debug__C__NokeepAlive__Debug__B__Ac__NokeepAlive ) )
    {
        actionchain_____Backup__Debug__C__NokeepAlive__new_transition_67( msg );
        return Backup__Debug__C__NokeepAlive__Debug__B__Ac__NokeepAlive;
    }
    else if( check_history( Backup__Debug__C__NokeepAlive, Backup__Debug__C__NokeepAlive__Debug__A__Ac__NokeepAlive ) )
    {
        actionchain_____Backup__Debug__C__NokeepAlive__new_transition_68( msg );
        return Backup__Debug__C__NokeepAlive__Debug__A__Ac__NokeepAlive;
    }
    else if( check_history( Backup__Debug__C__NokeepAlive, Backup__Debug__C__NokeepAlive__Debug__A__En__TryBeMaster ) )
    {
        actionchain_____Backup__Debug__C__NokeepAlive__new_transition_69( msg );
        return Backup__Debug__C__NokeepAlive__Debug__A__En__TryBeMaster;
    }
    else if( check_history( Backup__Debug__C__NokeepAlive, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Backup__Debug__C__NokeepAlive__new_transition_70_to_boundary( msg );
        return Backup__Debug__C__NokeepAlive__boundary;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Backup__Debug__C__ReplyConfig__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Backup__Debug__C__ReplyConfig, Backup__Debug__C__ReplyConfig__Debug__B__Ex__TryBeMaster ) )
    {
        actionchain_____Backup__Debug__C__ReplyConfig__new_transition_36( msg );
        return Backup__Debug__C__ReplyConfig__Debug__B__Ex__TryBeMaster;
    }
    else if( check_history( Backup__Debug__C__ReplyConfig, Backup__Debug__C__ReplyConfig__Debug__B__Ac__ReplyConfig ) )
    {
        actionchain_____Backup__Debug__C__ReplyConfig__new_transition_37( msg );
        return Backup__Debug__C__ReplyConfig__Debug__B__Ac__ReplyConfig;
    }
    else if( check_history( Backup__Debug__C__ReplyConfig, Backup__Debug__C__ReplyConfig__Debug__A__Ac__ReplyConfig ) )
    {
        actionchain_____Backup__Debug__C__ReplyConfig__new_transition_38( msg );
        return Backup__Debug__C__ReplyConfig__Debug__A__Ac__ReplyConfig;
    }
    else if( check_history( Backup__Debug__C__ReplyConfig, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Backup__Debug__C__ReplyConfig__new_transition_39_to_boundary( msg );
        return Backup__Debug__C__ReplyConfig__boundary;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Backup__Debug__C__backtoslave1__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Backup__Debug__C__backtoslave1, Backup__Debug__C__backtoslave1__Debug__B__Ac__backtoslave1 ) )
    {
        actionchain_____Backup__Debug__C__backtoslave1__new_transition_44( msg );
        return Backup__Debug__C__backtoslave1__Debug__B__Ac__backtoslave1;
    }
    else if( check_history( Backup__Debug__C__backtoslave1, Backup__Debug__C__backtoslave1__Debug__A__Ac__backtoslave1 ) )
    {
        actionchain_____Backup__Debug__C__backtoslave1__new_transition_45( msg );
        return Backup__Debug__C__backtoslave1__Debug__A__Ac__backtoslave1;
    }
    else if( check_history( Backup__Debug__C__backtoslave1, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Backup__Debug__C__backtoslave1__new_transition_46_to_boundary( msg );
        return Backup__Debug__C__backtoslave1__boundary;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Backup__Debug__C__backtoslave__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Backup__Debug__C__backtoslave, Backup__Debug__C__backtoslave__Debug__B__Ac__backtoslave ) )
    {
        actionchain_____Backup__Debug__C__backtoslave__new_transition_28( msg );
        return Backup__Debug__C__backtoslave__Debug__B__Ac__backtoslave;
    }
    else if( check_history( Backup__Debug__C__backtoslave, Backup__Debug__C__backtoslave__Debug__A__Ac__backtoslave ) )
    {
        actionchain_____Backup__Debug__C__backtoslave__new_transition_29( msg );
        return Backup__Debug__C__backtoslave__Debug__A__Ac__backtoslave;
    }
    else if( check_history( Backup__Debug__C__backtoslave, Backup__Debug__C__backtoslave__Debug__A__En__backtoslave ) )
    {
        actionchain_____Backup__Debug__C__backtoslave__new_transition_30( msg );
        return Backup__Debug__C__backtoslave__Debug__A__En__backtoslave;
    }
    else if( check_history( Backup__Debug__C__backtoslave, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Backup__Debug__C__backtoslave__new_transition_31_to_boundary( msg );
        return Backup__Debug__C__backtoslave__boundary;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Backup__Debug__Path__BackToSlave( const UMLRTMessage * msg )
{
    if( action_____Backup__Debug__BackToSlave__S__Debug__GuardBackToSlave( msg ) )
    {
        actionchain_____Backup__Debug__BackToSlave__S( msg );
        return junction_____Backup__Debug__C__BackToSlave__en( msg );
    }
    else
    {
        actionchain_____Backup__BackToSlave( msg );
        return junction_____Backup__Slave( msg );
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Backup__Debug__Path__CheckNoMaster( const UMLRTMessage * msg )
{
    if( action_____Backup__Debug__CheckNoMaster__S__Debug__GuardCheckNoMaster( msg ) )
    {
        actionchain_____Backup__Debug__CheckNoMaster__S( msg );
        return junction_____Backup__Debug__C__CheckNoMaster__en( msg );
    }
    else
    {
        actionchain_____Backup__CheckNoMaster( msg );
        return junction_____Backup__ExitPoint1( msg );
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Backup__Debug__Path__Initial1__RunAsSlave__2( const UMLRTMessage * msg )
{
    if( action_____Backup__Debug__Initial1__RunAsSlave__2__S__Debug__GuardInitial1__RunAsSlave__2( msg ) )
    {
        actionchain_____Backup__Debug__Initial1__RunAsSlave__2__S( msg );
        return junction_____Backup__Debug__C__Initial1__RunAsSlave__2__en( msg );
    }
    else
    {
        actionchain_____Backup__Initial1__RunAsSlave__2( msg );
        return Backup__RunAsSlave;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Backup__Debug__Path__KeepAliveMsg( const UMLRTMessage * msg )
{
    if( action_____Backup__Debug__KeepAliveMsg__S__Debug__GuardKeepAliveMsg( msg ) )
    {
        actionchain_____Backup__Debug__KeepAliveMsg__S( msg );
        return junction_____Backup__Debug__C__KeepAliveMsg__en( msg );
    }
    else
    {
        actionchain_____Backup__KeepAliveMsg( msg );
        return Backup__RunAsSlave;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Backup__Debug__Path__NokeepAlive( const UMLRTMessage * msg )
{
    if( action_____Backup__Debug__NokeepAlive__S__Debug__GuardNokeepAlive( msg ) )
    {
        actionchain_____Backup__Debug__NokeepAlive__S( msg );
        return junction_____Backup__Debug__C__NokeepAlive__en( msg );
    }
    else
    {
        actionchain_____Backup__NokeepAlive( msg );
        return Backup__TryBeMaster;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Backup__Debug__Path__ReplyConfig( const UMLRTMessage * msg )
{
    if( action_____Backup__Debug__ReplyConfig__S__Debug__GuardReplyConfig( msg ) )
    {
        actionchain_____Backup__Debug__ReplyConfig__S( msg );
        return junction_____Backup__Debug__C__ReplyConfig__en( msg );
    }
    else
    {
        actionchain_____Backup__ReplyConfig( msg );
        return choice_____Backup__Choice2( msg );
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Backup__Debug__Path__backtoslave( const UMLRTMessage * msg )
{
    if( action_____Backup__Debug__backtoslave__S__Debug__Guardbacktoslave( msg ) )
    {
        actionchain_____Backup__Debug__backtoslave__S( msg );
        return junction_____Backup__Debug__C__backtoslave__en( msg );
    }
    else
    {
        actionchain_____Backup__backtoslave( msg );
        return Backup__RunAsSlave;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Backup__Debug__Path__backtoslave1( const UMLRTMessage * msg )
{
    if( action_____Backup__Debug__backtoslave1__S__Debug__Guardbacktoslave1( msg ) )
    {
        actionchain_____Backup__Debug__backtoslave1__S( msg );
        return junction_____Backup__Debug__C__backtoslave1__en( msg );
    }
    else
    {
        actionchain_____Backup__backtoslave1( msg );
        return junction_____Backup__Slave( msg );
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Backup__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Backup, Backup__TryBeMaster ) )
    {
        actionchain_____Backup__new_transition_1( msg );
        return Backup__TryBeMaster;
    }
    else if( check_history( Backup, Backup__RunAsSlave ) )
    {
        actionchain_____Backup__new_transition_2( msg );
        return Backup__RunAsSlave;
    }
    else if( check_history( Backup, Backup__Debug__C__Initial1__RunAsSlave__2 ) )
        return choice_____Backup__Debug__C__Initial1__RunAsSlave__2__deephistory( msg );
    else if( check_history( Backup, Backup__Debug__C__BackToSlave ) )
        return choice_____Backup__Debug__C__BackToSlave__deephistory( msg );
    else if( check_history( Backup, Backup__Debug__C__backtoslave ) )
        return choice_____Backup__Debug__C__backtoslave__deephistory( msg );
    else if( check_history( Backup, Backup__Debug__C__ReplyConfig ) )
        return choice_____Backup__Debug__C__ReplyConfig__deephistory( msg );
    else if( check_history( Backup, Backup__Debug__C__backtoslave1 ) )
        return choice_____Backup__Debug__C__backtoslave1__deephistory( msg );
    else if( check_history( Backup, Backup__Debug__C__KeepAliveMsg ) )
        return choice_____Backup__Debug__C__KeepAliveMsg__deephistory( msg );
    else if( check_history( Backup, Backup__Debug__C__CheckNoMaster ) )
        return choice_____Backup__Debug__C__CheckNoMaster__deephistory( msg );
    else if( check_history( Backup, Backup__Debug__C__NokeepAlive ) )
        return choice_____Backup__Debug__C__NokeepAlive__deephistory( msg );
    else if( check_history( Backup, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Backup__new_transition_11( msg );
        return choice_____Backup__Debug__Path__Initial1__RunAsSlave__2( msg );
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____CheckConfig( const UMLRTMessage * msg )
{
    if( action_____Debug__initTimer__CheckConfig( msg ) )
    {
        actionchain_____Debug__initTimer( msg );
        return choice_____Debug__Path__initTimer( msg );
    }
    else
    {
        actionchain_____Debug__BeSlave( msg );
        return choice_____Debug__Path__BeSlave( msg );
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Choice1( const UMLRTMessage * msg )
{
    if( action_____Debug__ActiveMode__checkConfig( msg ) )
    {
        actionchain_____Debug__ActiveMode( msg );
        return choice_____Debug__Path__ActiveMode( msg );
    }
    else
    {
        actionchain_____Debug__PassiveMode( msg );
        return choice_____Debug__Path__PassiveMode( msg );
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__C__ActiveMode__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__ActiveMode, Debug__C__ActiveMode__Debug__B__Ac__ActiveMode ) )
    {
        actionchain_____Debug__C__ActiveMode__new_transition_118( msg );
        return Debug__C__ActiveMode__Debug__B__Ac__ActiveMode;
    }
    else if( check_history( Debug__C__ActiveMode, Debug__C__ActiveMode__Debug__A__Ac__ActiveMode ) )
    {
        actionchain_____Debug__C__ActiveMode__new_transition_119( msg );
        return Debug__C__ActiveMode__Debug__A__Ac__ActiveMode;
    }
    else if( check_history( Debug__C__ActiveMode, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__ActiveMode__new_transition_120_to_boundary( msg );
        return Debug__C__ActiveMode__boundary;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__C__BeSlave__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__BeSlave, Debug__C__BeSlave__Debug__B__Ac__BeSlave ) )
    {
        actionchain_____Debug__C__BeSlave__new_transition_94( msg );
        return Debug__C__BeSlave__Debug__B__Ac__BeSlave;
    }
    else if( check_history( Debug__C__BeSlave, Debug__C__BeSlave__Debug__A__Ac__BeSlave ) )
    {
        actionchain_____Debug__C__BeSlave__new_transition_95( msg );
        return Debug__C__BeSlave__Debug__A__Ac__BeSlave;
    }
    else if( check_history( Debug__C__BeSlave, Debug__C__BeSlave__Debug__A__En__BeSlave ) )
    {
        actionchain_____Debug__C__BeSlave__new_transition_96( msg );
        return Debug__C__BeSlave__Debug__A__En__BeSlave;
    }
    else if( check_history( Debug__C__BeSlave, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__BeSlave__new_transition_97_to_boundary( msg );
        return Debug__C__BeSlave__boundary;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__C__BeingMaster__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__BeingMaster, Debug__C__BeingMaster__Debug__B__Ac__BeingMaster ) )
    {
        actionchain_____Debug__C__BeingMaster__new_transition_140( msg );
        return Debug__C__BeingMaster__Debug__B__Ac__BeingMaster;
    }
    else if( check_history( Debug__C__BeingMaster, Debug__C__BeingMaster__Debug__A__Ac__BeingMaster ) )
    {
        actionchain_____Debug__C__BeingMaster__new_transition_141( msg );
        return Debug__C__BeingMaster__Debug__A__Ac__BeingMaster;
    }
    else if( check_history( Debug__C__BeingMaster, Debug__C__BeingMaster__Debug__A__En__BeingMaster ) )
    {
        actionchain_____Debug__C__BeingMaster__new_transition_142( msg );
        return Debug__C__BeingMaster__Debug__A__En__BeingMaster;
    }
    else if( check_history( Debug__C__BeingMaster, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__BeingMaster__new_transition_143_to_boundary( msg );
        return Debug__C__BeingMaster__boundary;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__C__ExitPoint1__BeMaster__4__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__ExitPoint1__BeMaster__4, Debug__C__ExitPoint1__BeMaster__4__Debug__B__Ac__ExitPoint1__BeMaster__4 ) )
    {
        actionchain_____Debug__C__ExitPoint1__BeMaster__4__new_transition_124( msg );
        return Debug__C__ExitPoint1__BeMaster__4__Debug__B__Ac__ExitPoint1__BeMaster__4;
    }
    else if( check_history( Debug__C__ExitPoint1__BeMaster__4, Debug__C__ExitPoint1__BeMaster__4__Debug__A__Ac__ExitPoint1__BeMaster__4 ) )
    {
        actionchain_____Debug__C__ExitPoint1__BeMaster__4__new_transition_125( msg );
        return Debug__C__ExitPoint1__BeMaster__4__Debug__A__Ac__ExitPoint1__BeMaster__4;
    }
    else if( check_history( Debug__C__ExitPoint1__BeMaster__4, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__ExitPoint1__BeMaster__4__new_transition_126_to_boundary( msg );
        return Debug__C__ExitPoint1__BeMaster__4__boundary;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__C__Init__StandBy__3__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__Init__StandBy__3, Debug__C__Init__StandBy__3__Debug__B__Ac__Init__StandBy__3 ) )
    {
        actionchain_____Debug__C__Init__StandBy__3__new_transition_102( msg );
        return Debug__C__Init__StandBy__3__Debug__B__Ac__Init__StandBy__3;
    }
    else if( check_history( Debug__C__Init__StandBy__3, Debug__C__Init__StandBy__3__Debug__A__Ac__Init__StandBy__3 ) )
    {
        actionchain_____Debug__C__Init__StandBy__3__new_transition_103( msg );
        return Debug__C__Init__StandBy__3__Debug__A__Ac__Init__StandBy__3;
    }
    else if( check_history( Debug__C__Init__StandBy__3, Debug__C__Init__StandBy__3__Debug__A__En__Init__StandBy__3 ) )
    {
        actionchain_____Debug__C__Init__StandBy__3__new_transition_104( msg );
        return Debug__C__Init__StandBy__3__Debug__A__En__Init__StandBy__3;
    }
    else if( check_history( Debug__C__Init__StandBy__3, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__Init__StandBy__3__new_transition_105_to_boundary( msg );
        return Debug__C__Init__StandBy__3__boundary;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__C__KeepAlive__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__KeepAlive, Debug__C__KeepAlive__Debug__B__Ex__RunAsMaster ) )
    {
        actionchain_____Debug__C__KeepAlive__new_transition_130( msg );
        return Debug__C__KeepAlive__Debug__B__Ex__RunAsMaster;
    }
    else if( check_history( Debug__C__KeepAlive, Debug__C__KeepAlive__Debug__B__Ac__KeepAlive ) )
    {
        actionchain_____Debug__C__KeepAlive__new_transition_131( msg );
        return Debug__C__KeepAlive__Debug__B__Ac__KeepAlive;
    }
    else if( check_history( Debug__C__KeepAlive, Debug__C__KeepAlive__Debug__A__Ac__KeepAlive ) )
    {
        actionchain_____Debug__C__KeepAlive__new_transition_132( msg );
        return Debug__C__KeepAlive__Debug__A__Ac__KeepAlive;
    }
    else if( check_history( Debug__C__KeepAlive, Debug__C__KeepAlive__Debug__A__En__RunAsMaster ) )
    {
        actionchain_____Debug__C__KeepAlive__new_transition_133( msg );
        return Debug__C__KeepAlive__Debug__A__En__RunAsMaster;
    }
    else if( check_history( Debug__C__KeepAlive, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__KeepAlive__new_transition_134_to_boundary( msg );
        return Debug__C__KeepAlive__boundary;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__C__PassiveMode__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__PassiveMode, Debug__C__PassiveMode__Debug__B__Ac__PassiveMode ) )
    {
        actionchain_____Debug__C__PassiveMode__new_transition_166( msg );
        return Debug__C__PassiveMode__Debug__B__Ac__PassiveMode;
    }
    else if( check_history( Debug__C__PassiveMode, Debug__C__PassiveMode__Debug__A__Ac__PassiveMode ) )
    {
        actionchain_____Debug__C__PassiveMode__new_transition_167( msg );
        return Debug__C__PassiveMode__Debug__A__Ac__PassiveMode;
    }
    else if( check_history( Debug__C__PassiveMode, Debug__C__PassiveMode__Debug__A__En__PassiveMode ) )
    {
        actionchain_____Debug__C__PassiveMode__new_transition_168( msg );
        return Debug__C__PassiveMode__Debug__A__En__PassiveMode;
    }
    else if( check_history( Debug__C__PassiveMode, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__PassiveMode__new_transition_169_to_boundary( msg );
        return Debug__C__PassiveMode__boundary;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__C__Recover__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__Recover, Debug__C__Recover__Debug__B__Ex__Failure ) )
    {
        actionchain_____Debug__C__Recover__new_transition_110( msg );
        return Debug__C__Recover__Debug__B__Ex__Failure;
    }
    else if( check_history( Debug__C__Recover, Debug__C__Recover__Debug__B__Ac__Recover ) )
    {
        actionchain_____Debug__C__Recover__new_transition_111( msg );
        return Debug__C__Recover__Debug__B__Ac__Recover;
    }
    else if( check_history( Debug__C__Recover, Debug__C__Recover__Debug__A__Ac__Recover ) )
    {
        actionchain_____Debug__C__Recover__new_transition_112( msg );
        return Debug__C__Recover__Debug__A__Ac__Recover;
    }
    else if( check_history( Debug__C__Recover, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__Recover__new_transition_113_to_boundary( msg );
        return Debug__C__Recover__boundary;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__C__ServerFaliure__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__ServerFaliure, Debug__C__ServerFaliure__Debug__B__Ex__RunAsMaster ) )
    {
        actionchain_____Debug__C__ServerFaliure__new_transition_84( msg );
        return Debug__C__ServerFaliure__Debug__B__Ex__RunAsMaster;
    }
    else if( check_history( Debug__C__ServerFaliure, Debug__C__ServerFaliure__Debug__B__Ac__ServerFaliure ) )
    {
        actionchain_____Debug__C__ServerFaliure__new_transition_85( msg );
        return Debug__C__ServerFaliure__Debug__B__Ac__ServerFaliure;
    }
    else if( check_history( Debug__C__ServerFaliure, Debug__C__ServerFaliure__Debug__A__Ac__ServerFaliure ) )
    {
        actionchain_____Debug__C__ServerFaliure__new_transition_86( msg );
        return Debug__C__ServerFaliure__Debug__A__Ac__ServerFaliure;
    }
    else if( check_history( Debug__C__ServerFaliure, Debug__C__ServerFaliure__Debug__A__En__Failure ) )
    {
        actionchain_____Debug__C__ServerFaliure__new_transition_87( msg );
        return Debug__C__ServerFaliure__Debug__A__En__Failure;
    }
    else if( check_history( Debug__C__ServerFaliure, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__ServerFaliure__new_transition_88_to_boundary( msg );
        return Debug__C__ServerFaliure__boundary;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__C__StandBy__CheckConfig__5__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__StandBy__CheckConfig__5, Debug__C__StandBy__CheckConfig__5__Debug__B__Ex__StandBy ) )
    {
        actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_158( msg );
        return Debug__C__StandBy__CheckConfig__5__Debug__B__Ex__StandBy;
    }
    else if( check_history( Debug__C__StandBy__CheckConfig__5, Debug__C__StandBy__CheckConfig__5__Debug__B__Ac__StandBy__CheckConfig__5 ) )
    {
        actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_159( msg );
        return Debug__C__StandBy__CheckConfig__5__Debug__B__Ac__StandBy__CheckConfig__5;
    }
    else if( check_history( Debug__C__StandBy__CheckConfig__5, Debug__C__StandBy__CheckConfig__5__Debug__A__Ac__StandBy__CheckConfig__5 ) )
    {
        actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_160( msg );
        return Debug__C__StandBy__CheckConfig__5__Debug__A__Ac__StandBy__CheckConfig__5;
    }
    else if( check_history( Debug__C__StandBy__CheckConfig__5, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_161_to_boundary( msg );
        return Debug__C__StandBy__CheckConfig__5__boundary;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__C__initTimer__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__initTimer, Debug__C__initTimer__Debug__B__Ac__initTimer ) )
    {
        actionchain_____Debug__C__initTimer__new_transition_76( msg );
        return Debug__C__initTimer__Debug__B__Ac__initTimer;
    }
    else if( check_history( Debug__C__initTimer, Debug__C__initTimer__Debug__A__Ac__initTimer ) )
    {
        actionchain_____Debug__C__initTimer__new_transition_77( msg );
        return Debug__C__initTimer__Debug__A__Ac__initTimer;
    }
    else if( check_history( Debug__C__initTimer, Debug__C__initTimer__Debug__A__En__initTimer ) )
    {
        actionchain_____Debug__C__initTimer__new_transition_78( msg );
        return Debug__C__initTimer__Debug__A__En__initTimer;
    }
    else if( check_history( Debug__C__initTimer, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__initTimer__new_transition_79_to_boundary( msg );
        return Debug__C__initTimer__boundary;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__C__purgeotherMessage__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__purgeotherMessage, Debug__C__purgeotherMessage__Debug__B__Ex__Failure ) )
    {
        actionchain_____Debug__C__purgeotherMessage__new_transition_148( msg );
        return Debug__C__purgeotherMessage__Debug__B__Ex__Failure;
    }
    else if( check_history( Debug__C__purgeotherMessage, Debug__C__purgeotherMessage__Debug__B__Ac__purgeotherMessage ) )
    {
        actionchain_____Debug__C__purgeotherMessage__new_transition_149( msg );
        return Debug__C__purgeotherMessage__Debug__B__Ac__purgeotherMessage;
    }
    else if( check_history( Debug__C__purgeotherMessage, Debug__C__purgeotherMessage__Debug__A__Ac__purgeotherMessage ) )
    {
        actionchain_____Debug__C__purgeotherMessage__new_transition_150( msg );
        return Debug__C__purgeotherMessage__Debug__A__Ac__purgeotherMessage;
    }
    else if( check_history( Debug__C__purgeotherMessage, Debug__C__purgeotherMessage__Debug__A__En__Failure ) )
    {
        actionchain_____Debug__C__purgeotherMessage__new_transition_151( msg );
        return Debug__C__purgeotherMessage__Debug__A__En__Failure;
    }
    else if( check_history( Debug__C__purgeotherMessage, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__purgeotherMessage__new_transition_152_to_boundary( msg );
        return Debug__C__purgeotherMessage__boundary;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__Path__ActiveMode( const UMLRTMessage * msg )
{
    if( action_____Debug__ActiveMode__S__Debug__GuardActiveMode( msg ) )
    {
        actionchain_____Debug__ActiveMode__S( msg );
        return junction_____Debug__C__ActiveMode__en( msg );
    }
    else
    {
        actionchain_____ActiveMode( msg );
        return junction_____BeMaster( msg );
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__Path__BeSlave( const UMLRTMessage * msg )
{
    if( action_____Debug__BeSlave__S__Debug__GuardBeSlave( msg ) )
    {
        actionchain_____Debug__BeSlave__S( msg );
        return junction_____Debug__C__BeSlave__en( msg );
    }
    else
    {
        actionchain_____BeSlave( msg );
        return choice_____Backup__deephistory( msg );
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__Path__BeingMaster( const UMLRTMessage * msg )
{
    if( action_____Debug__BeingMaster__S__Debug__GuardBeingMaster( msg ) )
    {
        actionchain_____Debug__BeingMaster__S( msg );
        return junction_____Debug__C__BeingMaster__en( msg );
    }
    else
    {
        actionchain_____BeingMaster( msg );
        return RunAsMaster;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__Path__ExitPoint1__BeMaster__4( const UMLRTMessage * msg )
{
    if( action_____Debug__ExitPoint1__BeMaster__4__S__Debug__GuardExitPoint1__BeMaster__4( msg ) )
    {
        actionchain_____Debug__ExitPoint1__BeMaster__4__S( msg );
        return junction_____Debug__C__ExitPoint1__BeMaster__4__en( msg );
    }
    else
    {
        actionchain_____ExitPoint1__BeMaster__4( msg );
        return junction_____BeMaster( msg );
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__Path__Init__StandBy__3( const UMLRTMessage * msg )
{
    if( action_____Debug__Init__StandBy__3__S__Debug__GuardInit__StandBy__3( msg ) )
    {
        actionchain_____Debug__Init__StandBy__3__S( msg );
        return junction_____Debug__C__Init__StandBy__3__en( msg );
    }
    else
    {
        actionchain_____Init__StandBy__3( msg );
        return StandBy;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__Path__KeepAlive( const UMLRTMessage * msg )
{
    if( action_____Debug__KeepAlive__S__Debug__GuardKeepAlive( msg ) )
    {
        actionchain_____Debug__KeepAlive__S( msg );
        return junction_____Debug__C__KeepAlive__en( msg );
    }
    else
    {
        actionchain_____KeepAlive( msg );
        return RunAsMaster;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__Path__MasterAnnounce( const UMLRTMessage * msg )
{
    if( action_____Debug__MasterAnnounce__S__Debug__GuardMasterAnnounce( msg ) )
    {
        actionchain_____Debug__MasterAnnounce__S( msg );
        return Debug__C__MasterAnnounce;
    }
    else
    {
        actionchain_____MasterAnnounce( msg );
        return RunAsMaster;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__Path__PassiveMode( const UMLRTMessage * msg )
{
    if( action_____Debug__PassiveMode__S__Debug__GuardPassiveMode( msg ) )
    {
        actionchain_____Debug__PassiveMode__S( msg );
        return junction_____Debug__C__PassiveMode__en( msg );
    }
    else
    {
        actionchain_____PassiveMode( msg );
        return choice_____Backup__deephistory( msg );
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__Path__Recover( const UMLRTMessage * msg )
{
    if( action_____Debug__Recover__S__Debug__GuardRecover( msg ) )
    {
        actionchain_____Debug__Recover__S( msg );
        return junction_____Debug__C__Recover__en( msg );
    }
    else
    {
        actionchain_____Recover( msg );
        return choice_____Choice1( msg );
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__Path__ServerFaliure( const UMLRTMessage * msg )
{
    if( action_____Debug__ServerFaliure__S__Debug__GuardServerFaliure( msg ) )
    {
        actionchain_____Debug__ServerFaliure__S( msg );
        return junction_____Debug__C__ServerFaliure__en( msg );
    }
    else
    {
        actionchain_____ServerFaliure( msg );
        return Failure;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__Path__ServiceRequest( const UMLRTMessage * msg )
{
    if( action_____Debug__ServiceRequest__S__Debug__GuardServiceRequest( msg ) )
    {
        actionchain_____Debug__ServiceRequest__S( msg );
        return Debug__C__ServiceRequest;
    }
    else
    {
        actionchain_____ServiceRequest( msg );
        return RunAsMaster;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__Path__StandBy__CheckConfig__5( const UMLRTMessage * msg )
{
    if( action_____Debug__StandBy__CheckConfig__5__S__Debug__GuardStandBy__CheckConfig__5( msg ) )
    {
        actionchain_____Debug__StandBy__CheckConfig__5__S( msg );
        return junction_____Debug__C__StandBy__CheckConfig__5__en( msg );
    }
    else
    {
        actionchain_____StandBy__CheckConfig__5( msg );
        return choice_____CheckConfig( msg );
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__Path__initTimer( const UMLRTMessage * msg )
{
    if( action_____Debug__initTimer__S__Debug__GuardinitTimer( msg ) )
    {
        actionchain_____Debug__initTimer__S( msg );
        return junction_____Debug__C__initTimer__en( msg );
    }
    else
    {
        actionchain_____initTimer( msg );
        return RunAsMaster;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Debug__Path__purgeotherMessage( const UMLRTMessage * msg )
{
    if( action_____Debug__purgeotherMessage__S__Debug__GuardpurgeotherMessage( msg ) )
    {
        actionchain_____Debug__purgeotherMessage__S( msg );
        return junction_____Debug__C__purgeotherMessage__en( msg );
    }
    else
    {
        actionchain_____purgeotherMessage( msg );
        return Failure;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__BackToSlave__Debug__A__Ac__BackToSlave( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__BackToSlave__Debug__end__trans__BackToSlave( msg );
            return junction_____Backup__Debug__C__BackToSlave__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__BackToSlave__new_transition_26( msg );
            return junction_____Backup__Debug__C__BackToSlave__new_exitpoint_2( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__BackToSlave__Debug__B__Ac__BackToSlave( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__BackToSlave__Debug__AC__BackToSlave( msg );
            return Backup__Debug__C__BackToSlave__Debug__A__Ac__BackToSlave;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__BackToSlave__new_transition_25( msg );
            return junction_____Backup__Debug__C__BackToSlave__new_exitpoint_2( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__BackToSlave__Debug__B__Ex__TryBeMaster( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__BackToSlave__Debug__Ex__TryBeMaster( msg );
            return Backup__Debug__C__BackToSlave__Debug__B__Ac__BackToSlave;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__BackToSlave__new_transition_24( msg );
            return junction_____Backup__Debug__C__BackToSlave__new_exitpoint_2( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__BackToSlave__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__BackToSlave__new_transition_27( msg );
            return junction_____Backup__Debug__C__BackToSlave__new_exitpoint_2( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__CheckNoMaster__Debug__A__Ac__CheckNoMaster( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__CheckNoMaster__Debug__end__trans__CheckNoMaster( msg );
            return junction_____Backup__Debug__C__CheckNoMaster__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__CheckNoMaster__new_transition_64( msg );
            return junction_____Backup__Debug__C__CheckNoMaster__new_exitpoint_7( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__CheckNoMaster__Debug__B__Ac__CheckNoMaster( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__CheckNoMaster__Debug__Ac__CheckNoMaster( msg );
            return Backup__Debug__C__CheckNoMaster__Debug__A__Ac__CheckNoMaster;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__CheckNoMaster__new_transition_63( msg );
            return junction_____Backup__Debug__C__CheckNoMaster__new_exitpoint_7( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__CheckNoMaster__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__CheckNoMaster__new_transition_65( msg );
            return junction_____Backup__Debug__C__CheckNoMaster__new_exitpoint_7( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__Ac__Initial1__RunAsSlave__2( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__En__RunAsSlave( msg );
            return Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__En__Initial1__RunAsSlave__2;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_17( msg );
            return junction_____Backup__Debug__C__Initial1__RunAsSlave__2__new_exitpoint_1( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__En__Initial1__RunAsSlave__2( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__end__trans__Initial1__RunAsSlave__2( msg );
            return junction_____Backup__Debug__C__Initial1__RunAsSlave__2__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_18( msg );
            return junction_____Backup__Debug__C__Initial1__RunAsSlave__2__new_exitpoint_1( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__B__Ac__Initial1__RunAsSlave__2( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__Ac__Initial1__RunAsSlave__2( msg );
            return Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__Ac__Initial1__RunAsSlave__2;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_16( msg );
            return junction_____Backup__Debug__C__Initial1__RunAsSlave__2__new_exitpoint_1( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__Initial1__RunAsSlave__2__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_19( msg );
            return junction_____Backup__Debug__C__Initial1__RunAsSlave__2__new_exitpoint_1( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__KeepAliveMsg__Debug__A__Ac__KeepAliveMsg( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__KeepAliveMsg__Debug__En__RunAsSlave( msg );
            return Backup__Debug__C__KeepAliveMsg__Debug__A__En__RunAsSlave;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_57( msg );
            return junction_____Backup__Debug__C__KeepAliveMsg__new_exitpoint_6( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__KeepAliveMsg__Debug__A__En__RunAsSlave( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__KeepAliveMsg__Debug__end__trans__KeepAliveMsg( msg );
            return junction_____Backup__Debug__C__KeepAliveMsg__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_58( msg );
            return junction_____Backup__Debug__C__KeepAliveMsg__new_exitpoint_6( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__KeepAliveMsg__Debug__B__Ac__KeepAliveMsg( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__KeepAliveMsg__Debug__AC__KeepAliveMsg( msg );
            return Backup__Debug__C__KeepAliveMsg__Debug__A__Ac__KeepAliveMsg;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_56( msg );
            return junction_____Backup__Debug__C__KeepAliveMsg__new_exitpoint_6( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__KeepAliveMsg__Debug__B__Ex__RunAsSlave( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__KeepAliveMsg__Debug__Ex__RunAsSlave( msg );
            return Backup__Debug__C__KeepAliveMsg__Debug__B__Ac__KeepAliveMsg;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_55( msg );
            return junction_____Backup__Debug__C__KeepAliveMsg__new_exitpoint_6( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__KeepAliveMsg__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_59( msg );
            return junction_____Backup__Debug__C__KeepAliveMsg__new_exitpoint_6( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__NokeepAlive__Debug__A__Ac__NokeepAlive( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__NokeepAlive__Debug__En__TryBeMaster( msg );
            return Backup__Debug__C__NokeepAlive__Debug__A__En__TryBeMaster;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__NokeepAlive__new_transition_73( msg );
            return junction_____Backup__Debug__C__NokeepAlive__new_exitpoint_8( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__NokeepAlive__Debug__A__En__TryBeMaster( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__NokeepAlive__Debug__end__trans__NokeepAlive( msg );
            return junction_____Backup__Debug__C__NokeepAlive__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__NokeepAlive__new_transition_74( msg );
            return junction_____Backup__Debug__C__NokeepAlive__new_exitpoint_8( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__NokeepAlive__Debug__B__Ac__NokeepAlive( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__NokeepAlive__Debug__AC__NokeepAlive( msg );
            return Backup__Debug__C__NokeepAlive__Debug__A__Ac__NokeepAlive;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__NokeepAlive__new_transition_72( msg );
            return junction_____Backup__Debug__C__NokeepAlive__new_exitpoint_8( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__NokeepAlive__Debug__B__Ex__RunAsSlave( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__NokeepAlive__Debug__Ex__RunAsSlave( msg );
            return Backup__Debug__C__NokeepAlive__Debug__B__Ac__NokeepAlive;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__NokeepAlive__new_transition_71( msg );
            return junction_____Backup__Debug__C__NokeepAlive__new_exitpoint_8( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__NokeepAlive__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__NokeepAlive__new_transition_75( msg );
            return junction_____Backup__Debug__C__NokeepAlive__new_exitpoint_8( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__ReplyConfig__Debug__A__Ac__ReplyConfig( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__ReplyConfig__Debug__end__trans__ReplyConfig( msg );
            return junction_____Backup__Debug__C__ReplyConfig__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__ReplyConfig__new_transition_42( msg );
            return junction_____Backup__Debug__C__ReplyConfig__new_exitpoint_4( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__ReplyConfig__Debug__B__Ac__ReplyConfig( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__ReplyConfig__Debug__AC__ReplyConfig( msg );
            return Backup__Debug__C__ReplyConfig__Debug__A__Ac__ReplyConfig;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__ReplyConfig__new_transition_41( msg );
            return junction_____Backup__Debug__C__ReplyConfig__new_exitpoint_4( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__ReplyConfig__Debug__B__Ex__TryBeMaster( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__ReplyConfig__Debug__Ex__TryBeMaster( msg );
            return Backup__Debug__C__ReplyConfig__Debug__B__Ac__ReplyConfig;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__ReplyConfig__new_transition_40( msg );
            return junction_____Backup__Debug__C__ReplyConfig__new_exitpoint_4( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__ReplyConfig__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__ReplyConfig__new_transition_43( msg );
            return junction_____Backup__Debug__C__ReplyConfig__new_exitpoint_4( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__backtoslave1__Debug__A__Ac__backtoslave1( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__backtoslave1__Debug__end__trans__backtoslave1( msg );
            return junction_____Backup__Debug__C__backtoslave1__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__backtoslave1__new_transition_48( msg );
            return junction_____Backup__Debug__C__backtoslave1__new_exitpoint_5( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__backtoslave1__Debug__B__Ac__backtoslave1( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__backtoslave1__Debug__Ac__backtoslave1( msg );
            return Backup__Debug__C__backtoslave1__Debug__A__Ac__backtoslave1;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__backtoslave1__new_transition_47( msg );
            return junction_____Backup__Debug__C__backtoslave1__new_exitpoint_5( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__backtoslave1__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__backtoslave1__new_transition_49( msg );
            return junction_____Backup__Debug__C__backtoslave1__new_exitpoint_5( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__backtoslave__Debug__A__Ac__backtoslave( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__backtoslave__Debug__En__RunAsSlave( msg );
            return Backup__Debug__C__backtoslave__Debug__A__En__backtoslave;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__backtoslave__new_transition_33( msg );
            return junction_____Backup__Debug__C__backtoslave__new_exitpoint_3( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__backtoslave__Debug__A__En__backtoslave( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__backtoslave__Debug__end__trans__backtoslave( msg );
            return junction_____Backup__Debug__C__backtoslave__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__backtoslave__new_transition_34( msg );
            return junction_____Backup__Debug__C__backtoslave__new_exitpoint_3( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__backtoslave__Debug__B__Ac__backtoslave( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Backup__Debug__C__backtoslave__Debug__Ac__backtoslave( msg );
            return Backup__Debug__C__backtoslave__Debug__A__Ac__backtoslave;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__backtoslave__new_transition_32( msg );
            return junction_____Backup__Debug__C__backtoslave__new_exitpoint_3( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__Debug__C__backtoslave__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Backup__Debug__C__backtoslave__new_transition_35( msg );
            return junction_____Backup__Debug__C__backtoslave__new_exitpoint_3( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__RunAsSlave( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_Slave:
        switch( msg->getSignalId() )
        {
        case FailOver::signal_IAmAlive:
            actionchain_____Backup__Debug__KeepAliveMsg( msg );
            return choice_____Backup__Debug__Path__KeepAliveMsg( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_KeepAliveTimer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____Backup__Debug__NokeepAlive( msg );
            return choice_____Backup__Debug__Path__NokeepAlive( msg );
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

Capsule_Server::State Capsule_Server::state_____Backup__TryBeMaster( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_ConfigComm:
        switch( msg->getSignalId() )
        {
        case Config::signal_ReplyConfig:
            actionchain_____Backup__Debug__ReplyConfig( msg );
            return choice_____Backup__Debug__Path__ReplyConfig( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__ActiveMode__Debug__A__Ac__ActiveMode( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__ActiveMode__Debug__end__trans__ActiveMode( msg );
            return junction_____Debug__C__ActiveMode__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ActiveMode__new_transition_122( msg );
            return junction_____Debug__C__ActiveMode__new_exitpoint_14( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__ActiveMode__Debug__B__Ac__ActiveMode( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__ActiveMode__Debug__Ac__ActiveMode( msg );
            return Debug__C__ActiveMode__Debug__A__Ac__ActiveMode;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ActiveMode__new_transition_121( msg );
            return junction_____Debug__C__ActiveMode__new_exitpoint_14( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__ActiveMode__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ActiveMode__new_transition_123( msg );
            return junction_____Debug__C__ActiveMode__new_exitpoint_14( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__BeSlave__Debug__A__Ac__BeSlave( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__BeSlave__Debug__En__Backup( msg );
            return Debug__C__BeSlave__Debug__A__En__BeSlave;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__BeSlave__new_transition_99( msg );
            return junction_____Debug__C__BeSlave__new_exitpoint_11( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__BeSlave__Debug__A__En__BeSlave( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__BeSlave__Debug__end__trans__BeSlave( msg );
            return junction_____Debug__C__BeSlave__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__BeSlave__new_transition_100( msg );
            return junction_____Debug__C__BeSlave__new_exitpoint_11( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__BeSlave__Debug__B__Ac__BeSlave( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__BeSlave__Debug__Ac__BeSlave( msg );
            return Debug__C__BeSlave__Debug__A__Ac__BeSlave;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__BeSlave__new_transition_98( msg );
            return junction_____Debug__C__BeSlave__new_exitpoint_11( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__BeSlave__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__BeSlave__new_transition_101( msg );
            return junction_____Debug__C__BeSlave__new_exitpoint_11( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__BeingMaster__Debug__A__Ac__BeingMaster( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__BeingMaster__Debug__En__RunAsMaster( msg );
            return Debug__C__BeingMaster__Debug__A__En__BeingMaster;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__BeingMaster__new_transition_145( msg );
            return junction_____Debug__C__BeingMaster__new_exitpoint_17( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__BeingMaster__Debug__A__En__BeingMaster( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__BeingMaster__Debug__end__trans__BeingMaster( msg );
            return junction_____Debug__C__BeingMaster__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__BeingMaster__new_transition_146( msg );
            return junction_____Debug__C__BeingMaster__new_exitpoint_17( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__BeingMaster__Debug__B__Ac__BeingMaster( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__BeingMaster__Debug__Ac__BeingMaster( msg );
            return Debug__C__BeingMaster__Debug__A__Ac__BeingMaster;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__BeingMaster__new_transition_144( msg );
            return junction_____Debug__C__BeingMaster__new_exitpoint_17( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__BeingMaster__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__BeingMaster__new_transition_147( msg );
            return junction_____Debug__C__BeingMaster__new_exitpoint_17( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__ExitPoint1__BeMaster__4__Debug__A__Ac__ExitPoint1__BeMaster__4( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__ExitPoint1__BeMaster__4__Debug__end__trans__ExitPoint1__BeMaster__4( msg );
            return junction_____Debug__C__ExitPoint1__BeMaster__4__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ExitPoint1__BeMaster__4__new_transition_128( msg );
            return junction_____Debug__C__ExitPoint1__BeMaster__4__new_exitpoint_15( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__ExitPoint1__BeMaster__4__Debug__B__Ac__ExitPoint1__BeMaster__4( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__ExitPoint1__BeMaster__4__Debug__Ac__ExitPoint1__BeMaster__4( msg );
            return Debug__C__ExitPoint1__BeMaster__4__Debug__A__Ac__ExitPoint1__BeMaster__4;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ExitPoint1__BeMaster__4__new_transition_127( msg );
            return junction_____Debug__C__ExitPoint1__BeMaster__4__new_exitpoint_15( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__ExitPoint1__BeMaster__4__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ExitPoint1__BeMaster__4__new_transition_129( msg );
            return junction_____Debug__C__ExitPoint1__BeMaster__4__new_exitpoint_15( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__Init__StandBy__3__Debug__A__Ac__Init__StandBy__3( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Init__StandBy__3__Debug__En__StandBy( msg );
            return Debug__C__Init__StandBy__3__Debug__A__En__Init__StandBy__3;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Init__StandBy__3__new_transition_107( msg );
            return junction_____Debug__C__Init__StandBy__3__new_exitpoint_12( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__Init__StandBy__3__Debug__A__En__Init__StandBy__3( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Init__StandBy__3__Debug__end__trans__Init__StandBy__3( msg );
            return junction_____Debug__C__Init__StandBy__3__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Init__StandBy__3__new_transition_108( msg );
            return junction_____Debug__C__Init__StandBy__3__new_exitpoint_12( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__Init__StandBy__3__Debug__B__Ac__Init__StandBy__3( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Init__StandBy__3__Debug__Ac__Init__StandBy__3( msg );
            return Debug__C__Init__StandBy__3__Debug__A__Ac__Init__StandBy__3;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Init__StandBy__3__new_transition_106( msg );
            return junction_____Debug__C__Init__StandBy__3__new_exitpoint_12( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__Init__StandBy__3__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Init__StandBy__3__new_transition_109( msg );
            return junction_____Debug__C__Init__StandBy__3__new_exitpoint_12( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__KeepAlive__Debug__A__Ac__KeepAlive( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__KeepAlive__Debug__En__RunAsMaster( msg );
            return Debug__C__KeepAlive__Debug__A__En__RunAsMaster;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__KeepAlive__new_transition_137( msg );
            return junction_____Debug__C__KeepAlive__new_exitpoint_16( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__KeepAlive__Debug__A__En__RunAsMaster( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__KeepAlive__Debug__end__trans__KeepAlive( msg );
            return junction_____Debug__C__KeepAlive__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__KeepAlive__new_transition_138( msg );
            return junction_____Debug__C__KeepAlive__new_exitpoint_16( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__KeepAlive__Debug__B__Ac__KeepAlive( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__KeepAlive__Debug__AC__KeepAlive( msg );
            return Debug__C__KeepAlive__Debug__A__Ac__KeepAlive;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__KeepAlive__new_transition_136( msg );
            return junction_____Debug__C__KeepAlive__new_exitpoint_16( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__KeepAlive__Debug__B__Ex__RunAsMaster( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__KeepAlive__Debug__Ex__RunAsMaster( msg );
            return Debug__C__KeepAlive__Debug__B__Ac__KeepAlive;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__KeepAlive__new_transition_135( msg );
            return junction_____Debug__C__KeepAlive__new_exitpoint_16( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__KeepAlive__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__KeepAlive__new_transition_139( msg );
            return junction_____Debug__C__KeepAlive__new_exitpoint_16( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__MasterAnnounce( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__MasterAnnounce__dbg( msg );
            return Debug__C__MasterAnnounce;
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

Capsule_Server::State Capsule_Server::state_____Debug__C__PassiveMode__Debug__A__Ac__PassiveMode( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__PassiveMode__Debug__En__Backup( msg );
            return Debug__C__PassiveMode__Debug__A__En__PassiveMode;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__PassiveMode__new_transition_171( msg );
            return junction_____Debug__C__PassiveMode__new_exitpoint_20( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__PassiveMode__Debug__A__En__PassiveMode( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__PassiveMode__Debug__end__trans__PassiveMode( msg );
            return junction_____Debug__C__PassiveMode__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__PassiveMode__new_transition_172( msg );
            return junction_____Debug__C__PassiveMode__new_exitpoint_20( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__PassiveMode__Debug__B__Ac__PassiveMode( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__PassiveMode__Debug__Ac__PassiveMode( msg );
            return Debug__C__PassiveMode__Debug__A__Ac__PassiveMode;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__PassiveMode__new_transition_170( msg );
            return junction_____Debug__C__PassiveMode__new_exitpoint_20( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__PassiveMode__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__PassiveMode__new_transition_173( msg );
            return junction_____Debug__C__PassiveMode__new_exitpoint_20( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__Recover__Debug__A__Ac__Recover( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Recover__Debug__end__trans__Recover( msg );
            return junction_____Debug__C__Recover__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Recover__new_transition_116( msg );
            return junction_____Debug__C__Recover__new_exitpoint_13( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__Recover__Debug__B__Ac__Recover( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Recover__Debug__AC__Recover( msg );
            return Debug__C__Recover__Debug__A__Ac__Recover;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Recover__new_transition_115( msg );
            return junction_____Debug__C__Recover__new_exitpoint_13( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__Recover__Debug__B__Ex__Failure( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Recover__Debug__Ex__Failure( msg );
            return Debug__C__Recover__Debug__B__Ac__Recover;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Recover__new_transition_114( msg );
            return junction_____Debug__C__Recover__new_exitpoint_13( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__Recover__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Recover__new_transition_117( msg );
            return junction_____Debug__C__Recover__new_exitpoint_13( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__ServerFaliure__Debug__A__Ac__ServerFaliure( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__ServerFaliure__Debug__En__Failure( msg );
            return Debug__C__ServerFaliure__Debug__A__En__Failure;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ServerFaliure__new_transition_91( msg );
            return junction_____Debug__C__ServerFaliure__new_exitpoint_10( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__ServerFaliure__Debug__A__En__Failure( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__ServerFaliure__Debug__end__trans__ServerFaliure( msg );
            return junction_____Debug__C__ServerFaliure__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ServerFaliure__new_transition_92( msg );
            return junction_____Debug__C__ServerFaliure__new_exitpoint_10( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__ServerFaliure__Debug__B__Ac__ServerFaliure( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__ServerFaliure__Debug__AC__ServerFaliure( msg );
            return Debug__C__ServerFaliure__Debug__A__Ac__ServerFaliure;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ServerFaliure__new_transition_90( msg );
            return junction_____Debug__C__ServerFaliure__new_exitpoint_10( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__ServerFaliure__Debug__B__Ex__RunAsMaster( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__ServerFaliure__Debug__Ex__RunAsMaster( msg );
            return Debug__C__ServerFaliure__Debug__B__Ac__ServerFaliure;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ServerFaliure__new_transition_89( msg );
            return junction_____Debug__C__ServerFaliure__new_exitpoint_10( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__ServerFaliure__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__ServerFaliure__new_transition_93( msg );
            return junction_____Debug__C__ServerFaliure__new_exitpoint_10( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__ServiceRequest( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__ServiceRequest__dbg( msg );
            return Debug__C__ServiceRequest;
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

Capsule_Server::State Capsule_Server::state_____Debug__C__StandBy__CheckConfig__5__Debug__A__Ac__StandBy__CheckConfig__5( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__StandBy__CheckConfig__5__Debug__end__trans__StandBy__CheckConfig__5( msg );
            return junction_____Debug__C__StandBy__CheckConfig__5__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_164( msg );
            return junction_____Debug__C__StandBy__CheckConfig__5__new_exitpoint_19( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__StandBy__CheckConfig__5__Debug__B__Ac__StandBy__CheckConfig__5( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__StandBy__CheckConfig__5__Debug__AC__StandBy__CheckConfig__5( msg );
            return Debug__C__StandBy__CheckConfig__5__Debug__A__Ac__StandBy__CheckConfig__5;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_163( msg );
            return junction_____Debug__C__StandBy__CheckConfig__5__new_exitpoint_19( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__StandBy__CheckConfig__5__Debug__B__Ex__StandBy( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__StandBy__CheckConfig__5__Debug__Ex__StandBy( msg );
            return Debug__C__StandBy__CheckConfig__5__Debug__B__Ac__StandBy__CheckConfig__5;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_162( msg );
            return junction_____Debug__C__StandBy__CheckConfig__5__new_exitpoint_19( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__StandBy__CheckConfig__5__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_165( msg );
            return junction_____Debug__C__StandBy__CheckConfig__5__new_exitpoint_19( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__initTimer__Debug__A__Ac__initTimer( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__initTimer__Debug__En__RunAsMaster( msg );
            return Debug__C__initTimer__Debug__A__En__initTimer;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__initTimer__new_transition_81( msg );
            return junction_____Debug__C__initTimer__new_exitpoint_9( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__initTimer__Debug__A__En__initTimer( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__initTimer__Debug__end__trans__initTimer( msg );
            return junction_____Debug__C__initTimer__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__initTimer__new_transition_82( msg );
            return junction_____Debug__C__initTimer__new_exitpoint_9( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__initTimer__Debug__B__Ac__initTimer( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__initTimer__Debug__Ac__initTimer( msg );
            return Debug__C__initTimer__Debug__A__Ac__initTimer;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__initTimer__new_transition_80( msg );
            return junction_____Debug__C__initTimer__new_exitpoint_9( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__initTimer__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__initTimer__new_transition_83( msg );
            return junction_____Debug__C__initTimer__new_exitpoint_9( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__purgeotherMessage__Debug__A__Ac__purgeotherMessage( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__purgeotherMessage__Debug__En__Failure( msg );
            return Debug__C__purgeotherMessage__Debug__A__En__Failure;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__purgeotherMessage__new_transition_155( msg );
            return junction_____Debug__C__purgeotherMessage__new_exitpoint_18( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__purgeotherMessage__Debug__A__En__Failure( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__purgeotherMessage__Debug__end__trans__purgeotherMessage( msg );
            return junction_____Debug__C__purgeotherMessage__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__purgeotherMessage__new_transition_156( msg );
            return junction_____Debug__C__purgeotherMessage__new_exitpoint_18( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__purgeotherMessage__Debug__B__Ac__purgeotherMessage( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__purgeotherMessage__Debug__AC__purgeotherMessage( msg );
            return Debug__C__purgeotherMessage__Debug__A__Ac__purgeotherMessage;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__purgeotherMessage__new_transition_154( msg );
            return junction_____Debug__C__purgeotherMessage__new_exitpoint_18( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__purgeotherMessage__Debug__B__Ex__Failure( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__purgeotherMessage__Debug__Ex__Failure( msg );
            return Debug__C__purgeotherMessage__Debug__B__Ac__purgeotherMessage;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__purgeotherMessage__new_transition_153( msg );
            return junction_____Debug__C__purgeotherMessage__new_exitpoint_18( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__C__purgeotherMessage__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__purgeotherMessage__new_transition_157( msg );
            return junction_____Debug__C__purgeotherMessage__new_exitpoint_18( msg );
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

Capsule_Server::State Capsule_Server::state_____Debug__InitState( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__Init__StandBy__3( msg );
            return choice_____Debug__Path__Init__StandBy__3( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::state_____Failure( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_Timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____Debug__Recover( msg );
            return choice_____Debug__Path__Recover( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_ServerComm:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__purgeotherMessage( msg );
            return choice_____Debug__Path__purgeotherMessage( msg );
        }
        return currentState;
    case port_Master:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__purgeotherMessage( msg );
            return choice_____Debug__Path__purgeotherMessage( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::state_____RunAsMaster( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_Timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____Debug__ServerFaliure( msg );
            return choice_____Debug__Path__ServerFaliure( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_MasterAnnounceTimer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____Debug__MasterAnnounce( msg );
            return choice_____Debug__Path__MasterAnnounce( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_KeepAliveTimer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____Debug__KeepAlive( msg );
            return choice_____Debug__Path__KeepAlive( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_ServerComm:
        switch( msg->getSignalId() )
        {
        case Services::signal_Request:
            actionchain_____Debug__ServiceRequest( msg );
            return choice_____Debug__Path__ServiceRequest( msg );
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

Capsule_Server::State Capsule_Server::state_____StandBy( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_ConfigComm:
        switch( msg->getSignalId() )
        {
        case Config::signal_StartUp:
            actionchain_____Debug__StandBy__CheckConfig__5( msg );
            return choice_____Debug__Path__StandBy__CheckConfig__5( msg );
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
        Capsule_Server::port_ConfigComm,
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
        Capsule_Server::port_KeepAliveTimer,
        "Timing",
        "KeepAliveTimer",
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
        Capsule_Server::port_Master,
        "FailOver",
        "Master",
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
        Capsule_Server::port_MasterAnnounceTimer,
        "Timing",
        "MasterAnnounceTimer",
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
        Capsule_Server::port_ServerComm,
        "Services",
        "ServerComm",
        "",
        5,
        true,
        true,
        false,
        false,
        false,
        false,
        true
    },
    {
        Capsule_Server::port_Slave,
        "FailOver",
        "Slave",
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
        Capsule_Server::port_Timer,
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
        Capsule_Server::port_extComm,
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

static void instantiate_Server( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_Server( &Server, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Server = 
{
    "Server",
    &Host,
    instantiate_Server,
    0,
    NULL,
    8,
    portroles_border,
    0,
    NULL
};

