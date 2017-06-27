
#include "CentralLock.hh"

#include "ExtInterface.hh"
#include "Locking.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include "umlrttimerprotocol.hh"
#include <cstddef>
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_CentralLock::Capsule_CentralLock( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, extComm( borderPorts[borderport_extComm] )
, lockPort( borderPorts[borderport_lockPort] )
, startupTimer( borderPorts[borderport_startupTimer] )
, tmpInt( 0 )
, locksCount( 4 )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8] = "Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8";
    stateNames[Debug__C__AllDoorClosed__doorsClosed__1] = "Debug__C__AllDoorClosed__doorsClosed__1";
    stateNames[Debug__C__Choice1__WaitAllDoorBeOpened__7] = "Debug__C__Choice1__WaitAllDoorBeOpened__7";
    stateNames[Debug__C__Choice1__doorsOpen__5] = "Debug__C__Choice1__doorsOpen__5";
    stateNames[Debug__C__Initial1__StartingUp__3] = "Debug__C__Initial1__StartingUp__3";
    stateNames[Debug__C__StartingUp__doorsOpen__10] = "Debug__C__StartingUp__doorsOpen__10";
    stateNames[Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9] = "Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9";
    stateNames[Debug__C__WaitAllDoorBeOpened__Choice1__6] = "Debug__C__WaitAllDoorBeOpened__Choice1__6";
    stateNames[Debug__C__doorsClosed__WaitAllDoorBeOpened__4] = "Debug__C__doorsClosed__WaitAllDoorBeOpened__4";
    stateNames[Debug__C__doorsOpen__WaitAllDoorBeClosed__2] = "Debug__C__doorsOpen__WaitAllDoorBeClosed__2";
    stateNames[Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8] = "Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8";
    stateNames[Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8] = "Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8";
    stateNames[Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8] = "Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8";
    stateNames[Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__boundary] = "Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__boundary";
    stateNames[Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__Ac__AllDoorClosed__doorsClosed__1] = "Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__Ac__AllDoorClosed__doorsClosed__1";
    stateNames[Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__En__AllDoorClosed__doorsClosed__1] = "Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__En__AllDoorClosed__doorsClosed__1";
    stateNames[Debug__C__AllDoorClosed__doorsClosed__1__Debug__B__Ac__AllDoorClosed__doorsClosed__1] = "Debug__C__AllDoorClosed__doorsClosed__1__Debug__B__Ac__AllDoorClosed__doorsClosed__1";
    stateNames[Debug__C__AllDoorClosed__doorsClosed__1__boundary] = "Debug__C__AllDoorClosed__doorsClosed__1__boundary";
    stateNames[Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7] = "Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7";
    stateNames[Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__En__Choice1__WaitAllDoorBeOpened__7] = "Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__En__Choice1__WaitAllDoorBeOpened__7";
    stateNames[Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7] = "Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7";
    stateNames[Debug__C__Choice1__WaitAllDoorBeOpened__7__boundary] = "Debug__C__Choice1__WaitAllDoorBeOpened__7__boundary";
    stateNames[Debug__C__Choice1__doorsOpen__5__Debug__A__Ac__Choice1__doorsOpen__5] = "Debug__C__Choice1__doorsOpen__5__Debug__A__Ac__Choice1__doorsOpen__5";
    stateNames[Debug__C__Choice1__doorsOpen__5__Debug__A__En__Choice1__doorsOpen__5] = "Debug__C__Choice1__doorsOpen__5__Debug__A__En__Choice1__doorsOpen__5";
    stateNames[Debug__C__Choice1__doorsOpen__5__Debug__B__Ac__Choice1__doorsOpen__5] = "Debug__C__Choice1__doorsOpen__5__Debug__B__Ac__Choice1__doorsOpen__5";
    stateNames[Debug__C__Choice1__doorsOpen__5__boundary] = "Debug__C__Choice1__doorsOpen__5__boundary";
    stateNames[Debug__C__Initial1__StartingUp__3__Debug__A__Ac__Initial1__StartingUp__3] = "Debug__C__Initial1__StartingUp__3__Debug__A__Ac__Initial1__StartingUp__3";
    stateNames[Debug__C__Initial1__StartingUp__3__Debug__A__En__Initial1__StartingUp__3] = "Debug__C__Initial1__StartingUp__3__Debug__A__En__Initial1__StartingUp__3";
    stateNames[Debug__C__Initial1__StartingUp__3__Debug__B__Ac__Initial1__StartingUp__3] = "Debug__C__Initial1__StartingUp__3__Debug__B__Ac__Initial1__StartingUp__3";
    stateNames[Debug__C__Initial1__StartingUp__3__boundary] = "Debug__C__Initial1__StartingUp__3__boundary";
    stateNames[Debug__C__StartingUp__doorsOpen__10__Debug__A__Ac__StartingUp__doorsOpen__10] = "Debug__C__StartingUp__doorsOpen__10__Debug__A__Ac__StartingUp__doorsOpen__10";
    stateNames[Debug__C__StartingUp__doorsOpen__10__Debug__A__En__doorsOpen] = "Debug__C__StartingUp__doorsOpen__10__Debug__A__En__doorsOpen";
    stateNames[Debug__C__StartingUp__doorsOpen__10__Debug__B__Ac__StartingUp__doorsOpen__10] = "Debug__C__StartingUp__doorsOpen__10__Debug__B__Ac__StartingUp__doorsOpen__10";
    stateNames[Debug__C__StartingUp__doorsOpen__10__Debug__B__Ex__StartingUp] = "Debug__C__StartingUp__doorsOpen__10__Debug__B__Ex__StartingUp";
    stateNames[Debug__C__StartingUp__doorsOpen__10__boundary] = "Debug__C__StartingUp__doorsOpen__10__boundary";
    stateNames[Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9] = "Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9";
    stateNames[Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9] = "Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9";
    stateNames[Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ex__WaitAllDoorBeClosed] = "Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ex__WaitAllDoorBeClosed";
    stateNames[Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__boundary] = "Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__boundary";
    stateNames[Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6] = "Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6";
    stateNames[Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6] = "Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6";
    stateNames[Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ex__WaitAllDoorBeOpened] = "Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ex__WaitAllDoorBeOpened";
    stateNames[Debug__C__WaitAllDoorBeOpened__Choice1__6__boundary] = "Debug__C__WaitAllDoorBeOpened__Choice1__6__boundary";
    stateNames[Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4] = "Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4";
    stateNames[Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__En__WaitAllDoorBeOpened] = "Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__En__WaitAllDoorBeOpened";
    stateNames[Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4] = "Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4";
    stateNames[Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ex__doorsClosed] = "Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ex__doorsClosed";
    stateNames[Debug__C__doorsClosed__WaitAllDoorBeOpened__4__boundary] = "Debug__C__doorsClosed__WaitAllDoorBeOpened__4__boundary";
    stateNames[Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2] = "Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2";
    stateNames[Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__En__WaitAllDoorBeClosed] = "Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__En__WaitAllDoorBeClosed";
    stateNames[Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2] = "Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2";
    stateNames[Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ex__doorsOpen] = "Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ex__doorsOpen";
    stateNames[Debug__C__doorsOpen__WaitAllDoorBeClosed__2__boundary] = "Debug__C__doorsOpen__WaitAllDoorBeClosed__2__boundary";
    stateNames[Debug__InitState] = "Debug__InitState";
    stateNames[StartingUp] = "StartingUp";
    stateNames[WaitAllDoorBeClosed] = "WaitAllDoorBeClosed";
    stateNames[WaitAllDoorBeOpened] = "WaitAllDoorBeOpened";
    stateNames[doorsClosed] = "doorsClosed";
    stateNames[doorsOpen] = "doorsOpen";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
    int i = 0;
    while( i < 10 )
        history[i++] = SPECIAL_INTERNAL_STATE_UNVISITED;
}







void Capsule_CentralLock::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_lockPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_lockPort, index, true );
            break;
        }
}

void Capsule_CentralLock::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_lockPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_lockPort, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_lockPort], index );
            break;
        }
}







void Capsule_CentralLock::Debug__variablesView()
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock operation Debug__variablesView */
    std::string tempS="";
    tempS.append("tmpInt,");
    tempS.append("Integer,");
    if(tmpInt!=0){
    char tempR[10];
    sprintf(tempR,"%d",tmpInt);
    tempS.append(tempR);
    tempS.append("\n");
    }else {
    tempS.append("0");
    tempS.append("\n");
    };
    tempS.append("locksCount,");
    tempS.append("Integer,");
    if(locksCount!=0){
    char tempR[10];
    sprintf(tempR,"%d",locksCount);
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

bool Capsule_CentralLock::Debug__variablesChange( char * varName, char * varValue )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock operation Debug__variablesChange */
    std::string tempVarName="";
    tempVarName.append(varName);
    if ("tmpInt"==tempVarName){
    tmpInt=atoi(varValue);
    return true;
    }else if ("locksCount"==tempVarName){
    locksCount=atoi(varValue);
    return true;
    }else 
    return false;
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_CentralLock::Debug__sendEvent( debugEvents::EVENTSOURCEKIND eventSourceKind, debugEvents::EVENTTYPE eventType, const char * instanceName, int capsuleIndex, const char * signalName, char * capsuleName, char * sourceName, char * reserve1, char * reserve2, char * reserve3 )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock operation Debug__sendEvent */
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

void Capsule_CentralLock::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case doorsOpen:
        currentState = state_____doorsOpen( &message );
        break;
    case doorsClosed:
        currentState = state_____doorsClosed( &message );
        break;
    case WaitAllDoorBeClosed:
        currentState = state_____WaitAllDoorBeClosed( &message );
        break;
    case WaitAllDoorBeOpened:
        currentState = state_____WaitAllDoorBeOpened( &message );
        break;
    case StartingUp:
        currentState = state_____StartingUp( &message );
        break;
    case Debug__InitState:
        currentState = state_____Debug__InitState( &message );
        break;
    case Debug__C__AllDoorClosed__doorsClosed__1__Debug__B__Ac__AllDoorClosed__doorsClosed__1:
        currentState = state_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__B__Ac__AllDoorClosed__doorsClosed__1( &message );
        break;
    case Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__Ac__AllDoorClosed__doorsClosed__1:
        currentState = state_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__Ac__AllDoorClosed__doorsClosed__1( &message );
        break;
    case Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__En__AllDoorClosed__doorsClosed__1:
        currentState = state_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__En__AllDoorClosed__doorsClosed__1( &message );
        break;
    case Debug__C__AllDoorClosed__doorsClosed__1__boundary:
        currentState = state_____Debug__C__AllDoorClosed__doorsClosed__1__boundary( &message );
        break;
    case Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ex__doorsOpen:
        currentState = state_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ex__doorsOpen( &message );
        break;
    case Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2:
        currentState = state_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2( &message );
        break;
    case Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2:
        currentState = state_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2( &message );
        break;
    case Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__En__WaitAllDoorBeClosed:
        currentState = state_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__En__WaitAllDoorBeClosed( &message );
        break;
    case Debug__C__doorsOpen__WaitAllDoorBeClosed__2__boundary:
        currentState = state_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__boundary( &message );
        break;
    case Debug__C__Initial1__StartingUp__3__Debug__B__Ac__Initial1__StartingUp__3:
        currentState = state_____Debug__C__Initial1__StartingUp__3__Debug__B__Ac__Initial1__StartingUp__3( &message );
        break;
    case Debug__C__Initial1__StartingUp__3__Debug__A__Ac__Initial1__StartingUp__3:
        currentState = state_____Debug__C__Initial1__StartingUp__3__Debug__A__Ac__Initial1__StartingUp__3( &message );
        break;
    case Debug__C__Initial1__StartingUp__3__Debug__A__En__Initial1__StartingUp__3:
        currentState = state_____Debug__C__Initial1__StartingUp__3__Debug__A__En__Initial1__StartingUp__3( &message );
        break;
    case Debug__C__Initial1__StartingUp__3__boundary:
        currentState = state_____Debug__C__Initial1__StartingUp__3__boundary( &message );
        break;
    case Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ex__doorsClosed:
        currentState = state_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ex__doorsClosed( &message );
        break;
    case Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4:
        currentState = state_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4( &message );
        break;
    case Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4:
        currentState = state_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4( &message );
        break;
    case Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__En__WaitAllDoorBeOpened:
        currentState = state_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__En__WaitAllDoorBeOpened( &message );
        break;
    case Debug__C__doorsClosed__WaitAllDoorBeOpened__4__boundary:
        currentState = state_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__boundary( &message );
        break;
    case Debug__C__Choice1__doorsOpen__5__Debug__B__Ac__Choice1__doorsOpen__5:
        currentState = state_____Debug__C__Choice1__doorsOpen__5__Debug__B__Ac__Choice1__doorsOpen__5( &message );
        break;
    case Debug__C__Choice1__doorsOpen__5__Debug__A__Ac__Choice1__doorsOpen__5:
        currentState = state_____Debug__C__Choice1__doorsOpen__5__Debug__A__Ac__Choice1__doorsOpen__5( &message );
        break;
    case Debug__C__Choice1__doorsOpen__5__Debug__A__En__Choice1__doorsOpen__5:
        currentState = state_____Debug__C__Choice1__doorsOpen__5__Debug__A__En__Choice1__doorsOpen__5( &message );
        break;
    case Debug__C__Choice1__doorsOpen__5__boundary:
        currentState = state_____Debug__C__Choice1__doorsOpen__5__boundary( &message );
        break;
    case Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ex__WaitAllDoorBeOpened:
        currentState = state_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ex__WaitAllDoorBeOpened( &message );
        break;
    case Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6:
        currentState = state_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6( &message );
        break;
    case Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6:
        currentState = state_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6( &message );
        break;
    case Debug__C__WaitAllDoorBeOpened__Choice1__6__boundary:
        currentState = state_____Debug__C__WaitAllDoorBeOpened__Choice1__6__boundary( &message );
        break;
    case Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7:
        currentState = state_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7( &message );
        break;
    case Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7:
        currentState = state_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7( &message );
        break;
    case Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__En__Choice1__WaitAllDoorBeOpened__7:
        currentState = state_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__En__Choice1__WaitAllDoorBeOpened__7( &message );
        break;
    case Debug__C__Choice1__WaitAllDoorBeOpened__7__boundary:
        currentState = state_____Debug__C__Choice1__WaitAllDoorBeOpened__7__boundary( &message );
        break;
    case Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8:
        currentState = state_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( &message );
        break;
    case Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8:
        currentState = state_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( &message );
        break;
    case Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8:
        currentState = state_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8( &message );
        break;
    case Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__boundary:
        currentState = state_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__boundary( &message );
        break;
    case Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ex__WaitAllDoorBeClosed:
        currentState = state_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ex__WaitAllDoorBeClosed( &message );
        break;
    case Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9:
        currentState = state_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9( &message );
        break;
    case Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9:
        currentState = state_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9( &message );
        break;
    case Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__boundary:
        currentState = state_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__boundary( &message );
        break;
    case Debug__C__StartingUp__doorsOpen__10__Debug__B__Ex__StartingUp:
        currentState = state_____Debug__C__StartingUp__doorsOpen__10__Debug__B__Ex__StartingUp( &message );
        break;
    case Debug__C__StartingUp__doorsOpen__10__Debug__B__Ac__StartingUp__doorsOpen__10:
        currentState = state_____Debug__C__StartingUp__doorsOpen__10__Debug__B__Ac__StartingUp__doorsOpen__10( &message );
        break;
    case Debug__C__StartingUp__doorsOpen__10__Debug__A__Ac__StartingUp__doorsOpen__10:
        currentState = state_____Debug__C__StartingUp__doorsOpen__10__Debug__A__Ac__StartingUp__doorsOpen__10( &message );
        break;
    case Debug__C__StartingUp__doorsOpen__10__Debug__A__En__doorsOpen:
        currentState = state_____Debug__C__StartingUp__doorsOpen__10__Debug__A__En__doorsOpen( &message );
        break;
    case Debug__C__StartingUp__doorsOpen__10__boundary:
        currentState = state_____Debug__C__StartingUp__doorsOpen__10__boundary( &message );
        break;
    default:
        break;
    }
}

void Capsule_CentralLock::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Debug__InitDebug( &message );
    currentState = Debug__InitState;
}

const char * Capsule_CentralLock::getCurrentStateString() const
{
    return stateNames[currentState];
}





void Capsule_CentralLock::save_history( Capsule_CentralLock::State compositeState, Capsule_CentralLock::State subState )
{
    history[compositeState] = subState;
}

bool Capsule_CentralLock::check_history( Capsule_CentralLock::State compositeState, Capsule_CentralLock::State subState )
{
    return history[compositeState] == subState;
}

void Capsule_CentralLock::entryaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::Region1::Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("AllDoorClosed__WaitAllDoorBeClosed__8","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("WaitAllDoorBeClosed","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::Region1::Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("WaitAllDoorBeClosed","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::Region1::Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("AllDoorClosed__WaitAllDoorBeClosed__8","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__Ac__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__AllDoorClosed__doorsClosed__1::Debug__A__Ac__AllDoorClosed__doorsClosed__1 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__AllDoorClosed__doorsClosed__1::Region1::Debug__A__Ac__AllDoorClosed__doorsClosed__1",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("AllDoorClosed__doorsClosed__1","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("doorsClosed","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__En__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__AllDoorClosed__doorsClosed__1::Debug__A__En__AllDoorClosed__doorsClosed__1 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__AllDoorClosed__doorsClosed__1::Region1::Debug__A__En__AllDoorClosed__doorsClosed__1",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("doorsClosed","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__B__Ac__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__AllDoorClosed__doorsClosed__1::Debug__B__Ac__AllDoorClosed__doorsClosed__1 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__AllDoorClosed__doorsClosed__1::Region1::Debug__B__Ac__AllDoorClosed__doorsClosed__1",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("AllDoorClosed__doorsClosed__1","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__AllDoorClosed__doorsClosed__1__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Choice1__WaitAllDoorBeOpened__7::Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Choice1__WaitAllDoorBeOpened__7::Region1::Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Choice1__WaitAllDoorBeOpened__7","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("WaitAllDoorBeOpened","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__En__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Choice1__WaitAllDoorBeOpened__7::Debug__A__En__Choice1__WaitAllDoorBeOpened__7 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Choice1__WaitAllDoorBeOpened__7::Region1::Debug__A__En__Choice1__WaitAllDoorBeOpened__7",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("WaitAllDoorBeOpened","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Choice1__WaitAllDoorBeOpened__7::Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Choice1__WaitAllDoorBeOpened__7::Region1::Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Choice1__WaitAllDoorBeOpened__7","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__Choice1__doorsOpen__5__Debug__A__Ac__Choice1__doorsOpen__5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Choice1__doorsOpen__5::Debug__A__Ac__Choice1__doorsOpen__5 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Choice1__doorsOpen__5::Region1::Debug__A__Ac__Choice1__doorsOpen__5",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Choice1__doorsOpen__5","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("doorsOpen","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__Choice1__doorsOpen__5__Debug__A__En__Choice1__doorsOpen__5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Choice1__doorsOpen__5::Debug__A__En__Choice1__doorsOpen__5 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Choice1__doorsOpen__5::Region1::Debug__A__En__Choice1__doorsOpen__5",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("doorsOpen","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__Choice1__doorsOpen__5__Debug__B__Ac__Choice1__doorsOpen__5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Choice1__doorsOpen__5::Debug__B__Ac__Choice1__doorsOpen__5 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Choice1__doorsOpen__5::Region1::Debug__B__Ac__Choice1__doorsOpen__5",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Choice1__doorsOpen__5","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__Choice1__doorsOpen__5__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__Initial1__StartingUp__3__Debug__A__Ac__Initial1__StartingUp__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Initial1__StartingUp__3::Debug__A__Ac__Initial1__StartingUp__3 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Initial1__StartingUp__3::Region1::Debug__A__Ac__Initial1__StartingUp__3",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Initial1__StartingUp__3","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("StartingUp","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__Initial1__StartingUp__3__Debug__A__En__Initial1__StartingUp__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Initial1__StartingUp__3::Debug__A__En__Initial1__StartingUp__3 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Initial1__StartingUp__3::Region1::Debug__A__En__Initial1__StartingUp__3",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("StartingUp","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__Initial1__StartingUp__3__Debug__B__Ac__Initial1__StartingUp__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Initial1__StartingUp__3::Debug__B__Ac__Initial1__StartingUp__3 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Initial1__StartingUp__3::Region1::Debug__B__Ac__Initial1__StartingUp__3",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Initial1__StartingUp__3","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__Initial1__StartingUp__3__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__StartingUp__doorsOpen__10__Debug__A__Ac__StartingUp__doorsOpen__10( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__StartingUp__doorsOpen__10::Debug__A__Ac__StartingUp__doorsOpen__10 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__StartingUp__doorsOpen__10::Region1::Debug__A__Ac__StartingUp__doorsOpen__10",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("StartingUp__doorsOpen__10","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("doorsOpen","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__StartingUp__doorsOpen__10__Debug__A__En__doorsOpen( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__StartingUp__doorsOpen__10::Debug__A__En__doorsOpen entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__StartingUp__doorsOpen__10::Region1::Debug__A__En__doorsOpen",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("doorsOpen","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__StartingUp__doorsOpen__10__Debug__B__Ac__StartingUp__doorsOpen__10( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__StartingUp__doorsOpen__10::Debug__B__Ac__StartingUp__doorsOpen__10 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__StartingUp__doorsOpen__10::Region1::Debug__B__Ac__StartingUp__doorsOpen__10",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("StartingUp","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("StartingUp__doorsOpen__10","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__StartingUp__doorsOpen__10__Debug__B__Ex__StartingUp( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__StartingUp__doorsOpen__10::Debug__B__Ex__StartingUp entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__StartingUp__doorsOpen__10::Region1::Debug__B__Ex__StartingUp",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("StartingUp","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__StartingUp__doorsOpen__10__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::Region1::Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("WaitAllDoorBeClosed__AllDoorClosed__9","","",3,TransitionEffectBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::Region1::Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("WaitAllDoorBeClosed","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("WaitAllDoorBeClosed__AllDoorClosed__9","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ex__WaitAllDoorBeClosed( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::Debug__B__Ex__WaitAllDoorBeClosed entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::Region1::Debug__B__Ex__WaitAllDoorBeClosed",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("WaitAllDoorBeClosed","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__WaitAllDoorBeOpened__Choice1__6::Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__WaitAllDoorBeOpened__Choice1__6::Region1::Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("WaitAllDoorBeOpened__Choice1__6","","",3,TransitionEffectBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__WaitAllDoorBeOpened__Choice1__6::Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__WaitAllDoorBeOpened__Choice1__6::Region1::Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("WaitAllDoorBeOpened","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("WaitAllDoorBeOpened__Choice1__6","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ex__WaitAllDoorBeOpened( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__WaitAllDoorBeOpened__Choice1__6::Debug__B__Ex__WaitAllDoorBeOpened entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__WaitAllDoorBeOpened__Choice1__6::Region1::Debug__B__Ex__WaitAllDoorBeOpened",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("WaitAllDoorBeOpened","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Region1::Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("doorsClosed__WaitAllDoorBeOpened__4","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("WaitAllDoorBeOpened","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__En__WaitAllDoorBeOpened( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Debug__A__En__WaitAllDoorBeOpened entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Region1::Debug__A__En__WaitAllDoorBeOpened",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("WaitAllDoorBeOpened","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Region1::Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("doorsClosed","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("doorsClosed__WaitAllDoorBeOpened__4","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ex__doorsClosed( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Debug__B__Ex__doorsClosed entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Region1::Debug__B__Ex__doorsClosed",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("doorsClosed","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Region1::Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("doorsOpen__WaitAllDoorBeClosed__2","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("WaitAllDoorBeClosed","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__En__WaitAllDoorBeClosed( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Debug__A__En__WaitAllDoorBeClosed entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Region1::Debug__A__En__WaitAllDoorBeClosed",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("WaitAllDoorBeClosed","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Region1::Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("doorsOpen","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("doorsOpen__WaitAllDoorBeClosed__2","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ex__doorsOpen( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Debug__B__Ex__doorsOpen entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Region1::Debug__B__Ex__doorsOpen",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("doorsOpen","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__InitState entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____StartingUp( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::StartingUp entry  */
    if( not Debug__SRO.checkDebug("StartingUp",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::StartingUp",(char *)"",(char *)"",(char *)"");
    startupTimer.informIn(UMLRTTimespec(3,0));
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____WaitAllDoorBeClosed( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::WaitAllDoorBeClosed entry  */
    if( not Debug__SRO.checkDebug("WaitAllDoorBeClosed",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::WaitAllDoorBeClosed",(char *)"",(char *)"",(char *)"");
    tmpInt++;
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____WaitAllDoorBeOpened( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::WaitAllDoorBeOpened entry  */
    if( not Debug__SRO.checkDebug("WaitAllDoorBeOpened",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::WaitAllDoorBeOpened",(char *)"",(char *)"",(char *)"");
    tmpInt++;
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____doorsClosed( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::doorsClosed entry  */
    if( not Debug__SRO.checkDebug("doorsClosed",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::doorsClosed",(char *)"",(char *)"",(char *)"");
    std::cout<<"Doors are closed"<<std::endl;
    std::cout<<"Press any key to open doors"<<std::endl;
    getchar();
    std::cout<<"Sending UnLock message to doors\n"<<std::endl;
    /// send message to first door
    lockPort.unlock().send(4);
    tmpInt=1;
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::entryaction_____doorsOpen( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::doorsOpen entry  */
    if( not Debug__SRO.checkDebug("doorsOpen",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::doorsOpen",(char *)"",(char *)"",(char *)"");
    std::cout<<"Doors are open"<<std::endl;
    std::cout<<"Press any key to close doors"<<std::endl;
    getchar();
    std::cout<<"Sending Lock message to doors\n"<<std::endl;
    /// send message to first door
    lockPort.lock().send(4);
    tmpInt=1;
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::Region1::Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::Region1::Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::Region1::Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__Ac__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__AllDoorClosed__doorsClosed__1::Debug__A__Ac__AllDoorClosed__doorsClosed__1 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__AllDoorClosed__doorsClosed__1::Region1::Debug__A__Ac__AllDoorClosed__doorsClosed__1",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__En__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__AllDoorClosed__doorsClosed__1::Debug__A__En__AllDoorClosed__doorsClosed__1 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__AllDoorClosed__doorsClosed__1::Region1::Debug__A__En__AllDoorClosed__doorsClosed__1",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__B__Ac__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__AllDoorClosed__doorsClosed__1::Debug__B__Ac__AllDoorClosed__doorsClosed__1 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__AllDoorClosed__doorsClosed__1::Region1::Debug__B__Ac__AllDoorClosed__doorsClosed__1",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__AllDoorClosed__doorsClosed__1__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Choice1__WaitAllDoorBeOpened__7::Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Choice1__WaitAllDoorBeOpened__7::Region1::Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__En__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Choice1__WaitAllDoorBeOpened__7::Debug__A__En__Choice1__WaitAllDoorBeOpened__7 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Choice1__WaitAllDoorBeOpened__7::Region1::Debug__A__En__Choice1__WaitAllDoorBeOpened__7",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Choice1__WaitAllDoorBeOpened__7::Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Choice1__WaitAllDoorBeOpened__7::Region1::Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__Choice1__doorsOpen__5__Debug__A__Ac__Choice1__doorsOpen__5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Choice1__doorsOpen__5::Debug__A__Ac__Choice1__doorsOpen__5 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Choice1__doorsOpen__5::Region1::Debug__A__Ac__Choice1__doorsOpen__5",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__Choice1__doorsOpen__5__Debug__A__En__Choice1__doorsOpen__5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Choice1__doorsOpen__5::Debug__A__En__Choice1__doorsOpen__5 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Choice1__doorsOpen__5::Region1::Debug__A__En__Choice1__doorsOpen__5",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__Choice1__doorsOpen__5__Debug__B__Ac__Choice1__doorsOpen__5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Choice1__doorsOpen__5::Debug__B__Ac__Choice1__doorsOpen__5 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Choice1__doorsOpen__5::Region1::Debug__B__Ac__Choice1__doorsOpen__5",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__Choice1__doorsOpen__5__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__Initial1__StartingUp__3__Debug__A__Ac__Initial1__StartingUp__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Initial1__StartingUp__3::Debug__A__Ac__Initial1__StartingUp__3 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Initial1__StartingUp__3::Region1::Debug__A__Ac__Initial1__StartingUp__3",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__Initial1__StartingUp__3__Debug__A__En__Initial1__StartingUp__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Initial1__StartingUp__3::Debug__A__En__Initial1__StartingUp__3 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Initial1__StartingUp__3::Region1::Debug__A__En__Initial1__StartingUp__3",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__Initial1__StartingUp__3__Debug__B__Ac__Initial1__StartingUp__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Initial1__StartingUp__3::Debug__B__Ac__Initial1__StartingUp__3 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Initial1__StartingUp__3::Region1::Debug__B__Ac__Initial1__StartingUp__3",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__Initial1__StartingUp__3__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__StartingUp__doorsOpen__10__Debug__A__Ac__StartingUp__doorsOpen__10( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__StartingUp__doorsOpen__10::Debug__A__Ac__StartingUp__doorsOpen__10 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__StartingUp__doorsOpen__10::Region1::Debug__A__Ac__StartingUp__doorsOpen__10",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__StartingUp__doorsOpen__10__Debug__A__En__doorsOpen( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__StartingUp__doorsOpen__10::Debug__A__En__doorsOpen exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__StartingUp__doorsOpen__10::Region1::Debug__A__En__doorsOpen",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__StartingUp__doorsOpen__10__Debug__B__Ac__StartingUp__doorsOpen__10( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__StartingUp__doorsOpen__10::Debug__B__Ac__StartingUp__doorsOpen__10 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__StartingUp__doorsOpen__10::Region1::Debug__B__Ac__StartingUp__doorsOpen__10",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__StartingUp__doorsOpen__10__Debug__B__Ex__StartingUp( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__StartingUp__doorsOpen__10::Debug__B__Ex__StartingUp exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__StartingUp__doorsOpen__10::Region1::Debug__B__Ex__StartingUp",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__StartingUp__doorsOpen__10__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::Region1::Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::Region1::Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ex__WaitAllDoorBeClosed( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::Debug__B__Ex__WaitAllDoorBeClosed exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::Region1::Debug__B__Ex__WaitAllDoorBeClosed",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__WaitAllDoorBeOpened__Choice1__6::Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__WaitAllDoorBeOpened__Choice1__6::Region1::Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__WaitAllDoorBeOpened__Choice1__6::Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__WaitAllDoorBeOpened__Choice1__6::Region1::Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ex__WaitAllDoorBeOpened( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__WaitAllDoorBeOpened__Choice1__6::Debug__B__Ex__WaitAllDoorBeOpened exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__WaitAllDoorBeOpened__Choice1__6::Region1::Debug__B__Ex__WaitAllDoorBeOpened",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Region1::Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__En__WaitAllDoorBeOpened( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Debug__A__En__WaitAllDoorBeOpened exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Region1::Debug__A__En__WaitAllDoorBeOpened",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Region1::Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ex__doorsClosed( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Debug__B__Ex__doorsClosed exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Region1::Debug__B__Ex__doorsClosed",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Region1::Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__En__WaitAllDoorBeClosed( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Debug__A__En__WaitAllDoorBeClosed exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Region1::Debug__A__En__WaitAllDoorBeClosed",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Region1::Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ex__doorsOpen( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Debug__B__Ex__doorsOpen exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Region1::Debug__B__Ex__doorsOpen",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__InitState exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____StartingUp( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::StartingUp exit  */
    if( not Debug__SRO.checkDebug("StartingUp",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::StartingUp",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::exitaction_____WaitAllDoorBeClosed( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::WaitAllDoorBeClosed exit  */
    if( not Debug__SRO.checkDebug("WaitAllDoorBeClosed",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::WaitAllDoorBeClosed",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

void Capsule_CentralLock::exitaction_____WaitAllDoorBeOpened( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::WaitAllDoorBeOpened exit  */
    if( not Debug__SRO.checkDebug("WaitAllDoorBeOpened",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::WaitAllDoorBeOpened",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

void Capsule_CentralLock::exitaction_____doorsClosed( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::doorsClosed exit  */
    if( not Debug__SRO.checkDebug("doorsClosed",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::doorsClosed",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

void Capsule_CentralLock::exitaction_____doorsOpen( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::doorsOpen exit  */
    if( not Debug__SRO.checkDebug("doorsOpen",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::doorsOpen",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

void Capsule_CentralLock::transitionaction_____AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__Path__AllDoorClosed__WaitAllDoorBeClosed__8,WaitAllDoorBeClosed */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::AllDoorClosed__WaitAllDoorBeClosed__8",(char *)"Debug__Path__AllDoorClosed__WaitAllDoorBeClosed__8",(char *)"WaitAllDoorBeClosed",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__Path__AllDoorClosed__doorsClosed__1,doorsClosed */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::AllDoorClosed__doorsClosed__1",(char *)"Debug__Path__AllDoorClosed__doorsClosed__1",(char *)"doorsClosed",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__Path__Choice1__WaitAllDoorBeOpened__7,WaitAllDoorBeOpened */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Choice1__WaitAllDoorBeOpened__7",(char *)"Debug__Path__Choice1__WaitAllDoorBeOpened__7",(char *)"WaitAllDoorBeOpened",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Choice1__doorsOpen__5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__Path__Choice1__doorsOpen__5,doorsOpen */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Choice1__doorsOpen__5",(char *)"Debug__Path__Choice1__doorsOpen__5",(char *)"doorsOpen",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition AllDoorClosed,Debug__Path__AllDoorClosed__WaitAllDoorBeClosed__8 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__AllDoorClosed__WaitAllDoorBeClosed__8",(char *)"AllDoorClosed",(char *)"Debug__Path__AllDoorClosed__WaitAllDoorBeClosed__8",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::ex,WaitAllDoorBeClosed */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__AllDoorClosed__WaitAllDoorBeClosed__8__E",(char *)"ex",(char *)"WaitAllDoorBeClosed",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__Path__AllDoorClosed__WaitAllDoorBeClosed__8,Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__AllDoorClosed__WaitAllDoorBeClosed__8__S",(char *)"Debug__Path__AllDoorClosed__WaitAllDoorBeClosed__8",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::new_exitpoint_8,Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__AllDoorClosed__WaitAllDoorBeClosed__8__dbg",(char *)"Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8",(char *)"Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition AllDoorClosed,Debug__Path__AllDoorClosed__doorsClosed__1 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__AllDoorClosed__doorsClosed__1",(char *)"AllDoorClosed",(char *)"Debug__Path__AllDoorClosed__doorsClosed__1",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__AllDoorClosed__doorsClosed__1__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__C__AllDoorClosed__doorsClosed__1::ex,doorsClosed */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__AllDoorClosed__doorsClosed__1__E",(char *)"ex",(char *)"doorsClosed",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__AllDoorClosed__doorsClosed__1__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__Path__AllDoorClosed__doorsClosed__1,Debug__C__AllDoorClosed__doorsClosed__1::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__AllDoorClosed__doorsClosed__1__S",(char *)"Debug__Path__AllDoorClosed__doorsClosed__1",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__AllDoorClosed__doorsClosed__1__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__C__AllDoorClosed__doorsClosed__1::new_exitpoint_1,Debug__C__AllDoorClosed__doorsClosed__1 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__AllDoorClosed__doorsClosed__1__dbg",(char *)"Debug__C__AllDoorClosed__doorsClosed__1",(char *)"Debug__C__AllDoorClosed__doorsClosed__1",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8 transition Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8,Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::Region1::Debug__Ac__AllDoorClosed__WaitAllDoorBeClosed__8",(char *)"Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8",(char *)"Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__En__WaitAllDoorBeClosed( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8 transition Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8,Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::Region1::Debug__En__WaitAllDoorBeClosed",(char *)"Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8",(char *)"Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8",(char *)"");
    tmpInt++;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__end__trans__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8 transition Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8,Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::Region1::Debug__end__trans__AllDoorClosed__WaitAllDoorBeClosed__8",(char *)"Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__init__trans__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8 transition Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::en,Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::Region1::Debug__init__trans__AllDoorClosed__WaitAllDoorBeClosed__8",(char *)"en",(char *)"Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__Ac__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__AllDoorClosed__doorsClosed__1 transition Debug__C__AllDoorClosed__doorsClosed__1::Debug__B__Ac__AllDoorClosed__doorsClosed__1,Debug__C__AllDoorClosed__doorsClosed__1::Debug__A__Ac__AllDoorClosed__doorsClosed__1,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__AllDoorClosed__doorsClosed__1::Region1::Debug__Ac__AllDoorClosed__doorsClosed__1",(char *)"Debug__B__Ac__AllDoorClosed__doorsClosed__1",(char *)"Debug__A__Ac__AllDoorClosed__doorsClosed__1",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__En__doorsClosed( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__AllDoorClosed__doorsClosed__1 transition Debug__C__AllDoorClosed__doorsClosed__1::Debug__A__Ac__AllDoorClosed__doorsClosed__1,Debug__C__AllDoorClosed__doorsClosed__1::Debug__A__En__AllDoorClosed__doorsClosed__1,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__AllDoorClosed__doorsClosed__1::Region1::Debug__En__doorsClosed",(char *)"Debug__A__Ac__AllDoorClosed__doorsClosed__1",(char *)"Debug__A__En__AllDoorClosed__doorsClosed__1",(char *)"");
    std::cout<<"Doors are closed"<<std::endl;
    std::cout<<"Press any key to open doors"<<std::endl;
    getchar();
    std::cout<<"Sending UnLock message to doors\n"<<std::endl;
    /// send message to first door
    lockPort.unlock().send(4);
    tmpInt=1;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__end__trans__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__AllDoorClosed__doorsClosed__1 transition Debug__C__AllDoorClosed__doorsClosed__1::Debug__A__En__AllDoorClosed__doorsClosed__1,Debug__C__AllDoorClosed__doorsClosed__1::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__AllDoorClosed__doorsClosed__1::Region1::Debug__end__trans__AllDoorClosed__doorsClosed__1",(char *)"Debug__A__En__AllDoorClosed__doorsClosed__1",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__init__trans__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__AllDoorClosed__doorsClosed__1 transition Debug__C__AllDoorClosed__doorsClosed__1::en,Debug__C__AllDoorClosed__doorsClosed__1::Debug__B__Ac__AllDoorClosed__doorsClosed__1 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__AllDoorClosed__doorsClosed__1::Region1::Debug__init__trans__AllDoorClosed__doorsClosed__1",(char *)"en",(char *)"Debug__B__Ac__AllDoorClosed__doorsClosed__1",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__Ac__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Choice1__WaitAllDoorBeOpened__7 transition Debug__C__Choice1__WaitAllDoorBeOpened__7::Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7,Debug__C__Choice1__WaitAllDoorBeOpened__7::Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Choice1__WaitAllDoorBeOpened__7::Region1::Debug__Ac__Choice1__WaitAllDoorBeOpened__7",(char *)"Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7",(char *)"Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__En__WaitAllDoorBeOpened( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Choice1__WaitAllDoorBeOpened__7 transition Debug__C__Choice1__WaitAllDoorBeOpened__7::Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7,Debug__C__Choice1__WaitAllDoorBeOpened__7::Debug__A__En__Choice1__WaitAllDoorBeOpened__7,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Choice1__WaitAllDoorBeOpened__7::Region1::Debug__En__WaitAllDoorBeOpened",(char *)"Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7",(char *)"Debug__A__En__Choice1__WaitAllDoorBeOpened__7",(char *)"");
    tmpInt++;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__end__trans__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Choice1__WaitAllDoorBeOpened__7 transition Debug__C__Choice1__WaitAllDoorBeOpened__7::Debug__A__En__Choice1__WaitAllDoorBeOpened__7,Debug__C__Choice1__WaitAllDoorBeOpened__7::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Choice1__WaitAllDoorBeOpened__7::Region1::Debug__end__trans__Choice1__WaitAllDoorBeOpened__7",(char *)"Debug__A__En__Choice1__WaitAllDoorBeOpened__7",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__init__trans__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Choice1__WaitAllDoorBeOpened__7 transition Debug__C__Choice1__WaitAllDoorBeOpened__7::en,Debug__C__Choice1__WaitAllDoorBeOpened__7::Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Choice1__WaitAllDoorBeOpened__7::Region1::Debug__init__trans__Choice1__WaitAllDoorBeOpened__7",(char *)"en",(char *)"Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__Choice1__doorsOpen__5__Debug__Ac__Choice1__doorsOpen__5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Choice1__doorsOpen__5 transition Debug__C__Choice1__doorsOpen__5::Debug__B__Ac__Choice1__doorsOpen__5,Debug__C__Choice1__doorsOpen__5::Debug__A__Ac__Choice1__doorsOpen__5,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Choice1__doorsOpen__5::Region1::Debug__Ac__Choice1__doorsOpen__5",(char *)"Debug__B__Ac__Choice1__doorsOpen__5",(char *)"Debug__A__Ac__Choice1__doorsOpen__5",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__Choice1__doorsOpen__5__Debug__En__doorsOpen( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Choice1__doorsOpen__5 transition Debug__C__Choice1__doorsOpen__5::Debug__A__Ac__Choice1__doorsOpen__5,Debug__C__Choice1__doorsOpen__5::Debug__A__En__Choice1__doorsOpen__5,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Choice1__doorsOpen__5::Region1::Debug__En__doorsOpen",(char *)"Debug__A__Ac__Choice1__doorsOpen__5",(char *)"Debug__A__En__Choice1__doorsOpen__5",(char *)"");
    std::cout<<"Doors are open"<<std::endl;
    std::cout<<"Press any key to close doors"<<std::endl;
    getchar();
    std::cout<<"Sending Lock message to doors\n"<<std::endl;
    /// send message to first door
    lockPort.lock().send(4);
    tmpInt=1;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__Choice1__doorsOpen__5__Debug__end__trans__Choice1__doorsOpen__5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Choice1__doorsOpen__5 transition Debug__C__Choice1__doorsOpen__5::Debug__A__En__Choice1__doorsOpen__5,Debug__C__Choice1__doorsOpen__5::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Choice1__doorsOpen__5::Region1::Debug__end__trans__Choice1__doorsOpen__5",(char *)"Debug__A__En__Choice1__doorsOpen__5",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__Choice1__doorsOpen__5__Debug__init__trans__Choice1__doorsOpen__5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Choice1__doorsOpen__5 transition Debug__C__Choice1__doorsOpen__5::en,Debug__C__Choice1__doorsOpen__5::Debug__B__Ac__Choice1__doorsOpen__5 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Choice1__doorsOpen__5::Region1::Debug__init__trans__Choice1__doorsOpen__5",(char *)"en",(char *)"Debug__B__Ac__Choice1__doorsOpen__5",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__Initial1__StartingUp__3__Debug__Ac__Initial1__StartingUp__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Initial1__StartingUp__3 transition Debug__C__Initial1__StartingUp__3::Debug__B__Ac__Initial1__StartingUp__3,Debug__C__Initial1__StartingUp__3::Debug__A__Ac__Initial1__StartingUp__3,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Initial1__StartingUp__3::Region1::Debug__Ac__Initial1__StartingUp__3",(char *)"Debug__B__Ac__Initial1__StartingUp__3",(char *)"Debug__A__Ac__Initial1__StartingUp__3",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__Initial1__StartingUp__3__Debug__En__StartingUp( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Initial1__StartingUp__3 transition Debug__C__Initial1__StartingUp__3::Debug__A__Ac__Initial1__StartingUp__3,Debug__C__Initial1__StartingUp__3::Debug__A__En__Initial1__StartingUp__3,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Initial1__StartingUp__3::Region1::Debug__En__StartingUp",(char *)"Debug__A__Ac__Initial1__StartingUp__3",(char *)"Debug__A__En__Initial1__StartingUp__3",(char *)"");
    startupTimer.informIn(UMLRTTimespec(3,0));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__Initial1__StartingUp__3__Debug__end__trans__Initial1__StartingUp__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Initial1__StartingUp__3 transition Debug__C__Initial1__StartingUp__3::Debug__A__En__Initial1__StartingUp__3,Debug__C__Initial1__StartingUp__3::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Initial1__StartingUp__3::Region1::Debug__end__trans__Initial1__StartingUp__3",(char *)"Debug__A__En__Initial1__StartingUp__3",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__Initial1__StartingUp__3__Debug__init__trans__Initial1__StartingUp__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__Initial1__StartingUp__3 transition Debug__C__Initial1__StartingUp__3::en,Debug__C__Initial1__StartingUp__3::Debug__B__Ac__Initial1__StartingUp__3 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__Initial1__StartingUp__3::Region1::Debug__init__trans__Initial1__StartingUp__3",(char *)"en",(char *)"Debug__B__Ac__Initial1__StartingUp__3",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__StartingUp__doorsOpen__10__Debug__AC__StartingUp__doorsOpen__10( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__StartingUp__doorsOpen__10 transition Debug__C__StartingUp__doorsOpen__10::Debug__B__Ac__StartingUp__doorsOpen__10,Debug__C__StartingUp__doorsOpen__10::Debug__A__Ac__StartingUp__doorsOpen__10,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__StartingUp__doorsOpen__10::Region1::Debug__AC__StartingUp__doorsOpen__10",(char *)"Debug__B__Ac__StartingUp__doorsOpen__10",(char *)"Debug__A__Ac__StartingUp__doorsOpen__10",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__StartingUp__doorsOpen__10__Debug__En__doorsOpen( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__StartingUp__doorsOpen__10 transition Debug__C__StartingUp__doorsOpen__10::Debug__A__Ac__StartingUp__doorsOpen__10,Debug__C__StartingUp__doorsOpen__10::Debug__A__En__doorsOpen,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__StartingUp__doorsOpen__10::Region1::Debug__En__doorsOpen",(char *)"Debug__A__Ac__StartingUp__doorsOpen__10",(char *)"Debug__A__En__doorsOpen",(char *)"");
    std::cout<<"Doors are open"<<std::endl;
    std::cout<<"Press any key to close doors"<<std::endl;
    getchar();
    std::cout<<"Sending Lock message to doors\n"<<std::endl;
    /// send message to first door
    lockPort.lock().send(4);
    tmpInt=1;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__StartingUp__doorsOpen__10__Debug__Ex__StartingUp( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__StartingUp__doorsOpen__10 transition Debug__C__StartingUp__doorsOpen__10::Debug__B__Ex__StartingUp,Debug__C__StartingUp__doorsOpen__10::Debug__B__Ac__StartingUp__doorsOpen__10,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__StartingUp__doorsOpen__10::Region1::Debug__Ex__StartingUp",(char *)"Debug__B__Ex__StartingUp",(char *)"Debug__B__Ac__StartingUp__doorsOpen__10",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__StartingUp__doorsOpen__10__Debug__end__trans__StartingUp__doorsOpen__10( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__StartingUp__doorsOpen__10 transition Debug__C__StartingUp__doorsOpen__10::Debug__A__En__doorsOpen,Debug__C__StartingUp__doorsOpen__10::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__StartingUp__doorsOpen__10::Region1::Debug__end__trans__StartingUp__doorsOpen__10",(char *)"Debug__A__En__doorsOpen",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__StartingUp__doorsOpen__10__Debug__init__trans__StartingUp__doorsOpen__10( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__StartingUp__doorsOpen__10 transition Debug__C__StartingUp__doorsOpen__10::en,Debug__C__StartingUp__doorsOpen__10::Debug__B__Ex__StartingUp */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__StartingUp__doorsOpen__10::Region1::Debug__init__trans__StartingUp__doorsOpen__10",(char *)"en",(char *)"Debug__B__Ex__StartingUp",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__AC__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9 transition Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9,Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::Region1::Debug__AC__WaitAllDoorBeClosed__AllDoorClosed__9",(char *)"Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9",(char *)"Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__Ex__WaitAllDoorBeClosed( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9 transition Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::Debug__B__Ex__WaitAllDoorBeClosed,Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::Region1::Debug__Ex__WaitAllDoorBeClosed",(char *)"Debug__B__Ex__WaitAllDoorBeClosed",(char *)"Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__end__trans__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9 transition Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9,Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::Region1::Debug__end__trans__WaitAllDoorBeClosed__AllDoorClosed__9",(char *)"Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__AC__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__WaitAllDoorBeOpened__Choice1__6 transition Debug__C__WaitAllDoorBeOpened__Choice1__6::Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6,Debug__C__WaitAllDoorBeOpened__Choice1__6::Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__WaitAllDoorBeOpened__Choice1__6::Region1::Debug__AC__WaitAllDoorBeOpened__Choice1__6",(char *)"Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6",(char *)"Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__Ex__WaitAllDoorBeOpened( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__WaitAllDoorBeOpened__Choice1__6 transition Debug__C__WaitAllDoorBeOpened__Choice1__6::Debug__B__Ex__WaitAllDoorBeOpened,Debug__C__WaitAllDoorBeOpened__Choice1__6::Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__WaitAllDoorBeOpened__Choice1__6::Region1::Debug__Ex__WaitAllDoorBeOpened",(char *)"Debug__B__Ex__WaitAllDoorBeOpened",(char *)"Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__end__trans__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__WaitAllDoorBeOpened__Choice1__6 transition Debug__C__WaitAllDoorBeOpened__Choice1__6::Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6,Debug__C__WaitAllDoorBeOpened__Choice1__6::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__WaitAllDoorBeOpened__Choice1__6::Region1::Debug__end__trans__WaitAllDoorBeOpened__Choice1__6",(char *)"Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__AC__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsClosed__WaitAllDoorBeOpened__4 transition Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4,Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Region1::Debug__AC__doorsClosed__WaitAllDoorBeOpened__4",(char *)"Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4",(char *)"Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__En__WaitAllDoorBeOpened( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsClosed__WaitAllDoorBeOpened__4 transition Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4,Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Debug__A__En__WaitAllDoorBeOpened,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Region1::Debug__En__WaitAllDoorBeOpened",(char *)"Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4",(char *)"Debug__A__En__WaitAllDoorBeOpened",(char *)"");
    tmpInt++;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__Ex__doorsClosed( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsClosed__WaitAllDoorBeOpened__4 transition Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Debug__B__Ex__doorsClosed,Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Region1::Debug__Ex__doorsClosed",(char *)"Debug__B__Ex__doorsClosed",(char *)"Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__end__trans__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsClosed__WaitAllDoorBeOpened__4 transition Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Debug__A__En__WaitAllDoorBeOpened,Debug__C__doorsClosed__WaitAllDoorBeOpened__4::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Region1::Debug__end__trans__doorsClosed__WaitAllDoorBeOpened__4",(char *)"Debug__A__En__WaitAllDoorBeOpened",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__init__trans__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsClosed__WaitAllDoorBeOpened__4 transition Debug__C__doorsClosed__WaitAllDoorBeOpened__4::en,Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Debug__B__Ex__doorsClosed */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsClosed__WaitAllDoorBeOpened__4::Region1::Debug__init__trans__doorsClosed__WaitAllDoorBeOpened__4",(char *)"en",(char *)"Debug__B__Ex__doorsClosed",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__AC__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsOpen__WaitAllDoorBeClosed__2 transition Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2,Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Region1::Debug__AC__doorsOpen__WaitAllDoorBeClosed__2",(char *)"Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2",(char *)"Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__En__WaitAllDoorBeClosed( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsOpen__WaitAllDoorBeClosed__2 transition Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2,Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Debug__A__En__WaitAllDoorBeClosed,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Region1::Debug__En__WaitAllDoorBeClosed",(char *)"Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2",(char *)"Debug__A__En__WaitAllDoorBeClosed",(char *)"");
    tmpInt++;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__Ex__doorsOpen( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsOpen__WaitAllDoorBeClosed__2 transition Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Debug__B__Ex__doorsOpen,Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Region1::Debug__Ex__doorsOpen",(char *)"Debug__B__Ex__doorsOpen",(char *)"Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__end__trans__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsOpen__WaitAllDoorBeClosed__2 transition Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Debug__A__En__WaitAllDoorBeClosed,Debug__C__doorsOpen__WaitAllDoorBeClosed__2::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Region1::Debug__end__trans__doorsOpen__WaitAllDoorBeClosed__2",(char *)"Debug__A__En__WaitAllDoorBeClosed",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__init__trans__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock::Debug__C__doorsOpen__WaitAllDoorBeClosed__2 transition Debug__C__doorsOpen__WaitAllDoorBeClosed__2::en,Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Debug__B__Ex__doorsOpen */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__C__doorsOpen__WaitAllDoorBeClosed__2::Region1::Debug__init__trans__doorsOpen__WaitAllDoorBeClosed__2",(char *)"en",(char *)"Debug__B__Ex__doorsOpen",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Choice1,Debug__Path__Choice1__WaitAllDoorBeOpened__7 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__Choice1__WaitAllDoorBeOpened__7",(char *)"Choice1",(char *)"Debug__Path__Choice1__WaitAllDoorBeOpened__7",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__Choice1__WaitAllDoorBeOpened__7__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__C__Choice1__WaitAllDoorBeOpened__7::ex,WaitAllDoorBeOpened */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__Choice1__WaitAllDoorBeOpened__7__E",(char *)"ex",(char *)"WaitAllDoorBeOpened",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__Choice1__WaitAllDoorBeOpened__7__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__Path__Choice1__WaitAllDoorBeOpened__7,Debug__C__Choice1__WaitAllDoorBeOpened__7::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__Choice1__WaitAllDoorBeOpened__7__S",(char *)"Debug__Path__Choice1__WaitAllDoorBeOpened__7",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__Choice1__WaitAllDoorBeOpened__7__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__C__Choice1__WaitAllDoorBeOpened__7::new_exitpoint_7,Debug__C__Choice1__WaitAllDoorBeOpened__7 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__Choice1__WaitAllDoorBeOpened__7__dbg",(char *)"Debug__C__Choice1__WaitAllDoorBeOpened__7",(char *)"Debug__C__Choice1__WaitAllDoorBeOpened__7",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__Choice1__doorsOpen__5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Choice1,Debug__Path__Choice1__doorsOpen__5 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__Choice1__doorsOpen__5",(char *)"Choice1",(char *)"Debug__Path__Choice1__doorsOpen__5",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__Choice1__doorsOpen__5__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__C__Choice1__doorsOpen__5::ex,doorsOpen */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__Choice1__doorsOpen__5__E",(char *)"ex",(char *)"doorsOpen",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__Choice1__doorsOpen__5__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__Path__Choice1__doorsOpen__5,Debug__C__Choice1__doorsOpen__5::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__Choice1__doorsOpen__5__S",(char *)"Debug__Path__Choice1__doorsOpen__5",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__Choice1__doorsOpen__5__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__C__Choice1__doorsOpen__5::new_exitpoint_5,Debug__C__Choice1__doorsOpen__5 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__Choice1__doorsOpen__5__dbg",(char *)"Debug__C__Choice1__doorsOpen__5",(char *)"Debug__C__Choice1__doorsOpen__5",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__InitDebug( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Initial1,Debug__InitState */
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

void Capsule_CentralLock::transitionaction_____Debug__Initial1__StartingUp__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__InitState,Debug__Path__Initial1__StartingUp__3,null:extComm */
    if (this->Debug__SRO.getExecMode()==Stepping){
    Debug__SRO.addTransitionsFromState("locked","twiceLock","locked","lock","Locking");
    Debug__SRO.addTransitionsFromState("WaitAllDoorBeClosed","","AllDoorClosed","lockStatus","Locking");
    Debug__SRO.addTransitionsFromState("unlocked","lock","locked","lock","Locking");
    Debug__SRO.addTransitionsFromState("StartingUp","","doorsOpen","timeout","Timing");
    Debug__SRO.addTransitionsFromState("Choice1","","doorsOpen","","");
    Debug__SRO.addTransitionsFromState("WaitAllDoorBeOpened","","Choice1","lockStatus","Locking");
    Debug__SRO.addTransitionsFromState("Choice1","","WaitAllDoorBeOpened","","");
    Debug__SRO.addTransitionsFromState("AllDoorClosed","","WaitAllDoorBeClosed","","");
    Debug__SRO.addTransitionsFromState("unlocked","twiceUnlock","unlocked","unlock","Locking");
    Debug__SRO.addTransitionsFromState("AllDoorClosed","","doorsClosed","","");
    Debug__SRO.addTransitionsFromState("doorsOpen","","WaitAllDoorBeClosed","lockStatus","Locking");
    Debug__SRO.addTransitionsFromState("Initial1","","StartingUp","","");
    Debug__SRO.addTransitionsFromState("Initial1","init","unlocked","","");
    Debug__SRO.addTransitionsFromState("locked","unlock","unlocked","unlock","Locking");
    Debug__SRO.addTransitionsFromState("doorsClosed","","WaitAllDoorBeOpened","lockStatus","Locking");
    std::cout<<this->getName()<<": Connection with debugger is in progress\n";
    char  tempS[256];
    sprintf(tempS,"%s%d",this->getName(),(int)this->getIndex());
    extComm.registerToControl(tempS).send();
    Debug__sendEvent(debugEvents::DEBUG,debugEvents::REGISTER,this->getName(),this->getIndex(),msg->getSignalName(),(char *) "",(char *) "",(char *) "",(char *)"",(char *) "");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__Initial1__StartingUp__3__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__C__Initial1__StartingUp__3::ex,StartingUp */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__Initial1__StartingUp__3__E",(char *)"ex",(char *)"StartingUp",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__Initial1__StartingUp__3__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__Path__Initial1__StartingUp__3,Debug__C__Initial1__StartingUp__3::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__Initial1__StartingUp__3__S",(char *)"Debug__Path__Initial1__StartingUp__3",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__Initial1__StartingUp__3__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__C__Initial1__StartingUp__3::new_exitpoint_3,Debug__C__Initial1__StartingUp__3 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__Initial1__StartingUp__3__dbg",(char *)"Debug__C__Initial1__StartingUp__3",(char *)"Debug__C__Initial1__StartingUp__3",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__StartingUp__doorsOpen__10( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition StartingUp,Debug__Path__StartingUp__doorsOpen__10,timeout:startupTimer */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__StartingUp__doorsOpen__10",(char *)"StartingUp",(char *)"Debug__Path__StartingUp__doorsOpen__10",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__StartingUp__doorsOpen__10__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__C__StartingUp__doorsOpen__10::ex,doorsOpen */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__StartingUp__doorsOpen__10__E",(char *)"ex",(char *)"doorsOpen",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__StartingUp__doorsOpen__10__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__Path__StartingUp__doorsOpen__10,Debug__C__StartingUp__doorsOpen__10::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__StartingUp__doorsOpen__10__S",(char *)"Debug__Path__StartingUp__doorsOpen__10",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__StartingUp__doorsOpen__10__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__C__StartingUp__doorsOpen__10::new_exitpoint_10,Debug__C__StartingUp__doorsOpen__10 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__StartingUp__doorsOpen__10__dbg",(char *)"Debug__C__StartingUp__doorsOpen__10",(char *)"Debug__C__StartingUp__doorsOpen__10",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition WaitAllDoorBeClosed,Debug__Path__WaitAllDoorBeClosed__AllDoorClosed__9,lockStatus:lockPort */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__WaitAllDoorBeClosed__AllDoorClosed__9",(char *)"WaitAllDoorBeClosed",(char *)"Debug__Path__WaitAllDoorBeClosed__AllDoorClosed__9",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

void Capsule_CentralLock::transitionaction_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::ex,AllDoorClosed */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__WaitAllDoorBeClosed__AllDoorClosed__9__E",(char *)"ex",(char *)"AllDoorClosed",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__Path__WaitAllDoorBeClosed__AllDoorClosed__9,Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__WaitAllDoorBeClosed__AllDoorClosed__9__S",(char *)"Debug__Path__WaitAllDoorBeClosed__AllDoorClosed__9",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::new_exitpoint_9,Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__WaitAllDoorBeClosed__AllDoorClosed__9__dbg",(char *)"Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9",(char *)"Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition WaitAllDoorBeOpened,Debug__Path__WaitAllDoorBeOpened__Choice1__6,lockStatus:lockPort */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__WaitAllDoorBeOpened__Choice1__6",(char *)"WaitAllDoorBeOpened",(char *)"Debug__Path__WaitAllDoorBeOpened__Choice1__6",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

void Capsule_CentralLock::transitionaction_____Debug__WaitAllDoorBeOpened__Choice1__6__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__C__WaitAllDoorBeOpened__Choice1__6::ex,Choice1 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__WaitAllDoorBeOpened__Choice1__6__E",(char *)"ex",(char *)"Choice1",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__WaitAllDoorBeOpened__Choice1__6__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__Path__WaitAllDoorBeOpened__Choice1__6,Debug__C__WaitAllDoorBeOpened__Choice1__6::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__WaitAllDoorBeOpened__Choice1__6__S",(char *)"Debug__Path__WaitAllDoorBeOpened__Choice1__6",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__WaitAllDoorBeOpened__Choice1__6__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__C__WaitAllDoorBeOpened__Choice1__6::new_exitpoint_6,Debug__C__WaitAllDoorBeOpened__Choice1__6 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__WaitAllDoorBeOpened__Choice1__6__dbg",(char *)"Debug__C__WaitAllDoorBeOpened__Choice1__6",(char *)"Debug__C__WaitAllDoorBeOpened__Choice1__6",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition doorsClosed,Debug__Path__doorsClosed__WaitAllDoorBeOpened__4,lockStatus:lockPort */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__doorsClosed__WaitAllDoorBeOpened__4",(char *)"doorsClosed",(char *)"Debug__Path__doorsClosed__WaitAllDoorBeOpened__4",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

void Capsule_CentralLock::transitionaction_____Debug__doorsClosed__WaitAllDoorBeOpened__4__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__C__doorsClosed__WaitAllDoorBeOpened__4::ex,WaitAllDoorBeOpened */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__doorsClosed__WaitAllDoorBeOpened__4__E",(char *)"ex",(char *)"WaitAllDoorBeOpened",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__doorsClosed__WaitAllDoorBeOpened__4__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__Path__doorsClosed__WaitAllDoorBeOpened__4,Debug__C__doorsClosed__WaitAllDoorBeOpened__4::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__doorsClosed__WaitAllDoorBeOpened__4__S",(char *)"Debug__Path__doorsClosed__WaitAllDoorBeOpened__4",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__doorsClosed__WaitAllDoorBeOpened__4__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__C__doorsClosed__WaitAllDoorBeOpened__4::new_exitpoint_4,Debug__C__doorsClosed__WaitAllDoorBeOpened__4 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__doorsClosed__WaitAllDoorBeOpened__4__dbg",(char *)"Debug__C__doorsClosed__WaitAllDoorBeOpened__4",(char *)"Debug__C__doorsClosed__WaitAllDoorBeOpened__4",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition doorsOpen,Debug__Path__doorsOpen__WaitAllDoorBeClosed__2,lockStatus:lockPort */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__doorsOpen__WaitAllDoorBeClosed__2",(char *)"doorsOpen",(char *)"Debug__Path__doorsOpen__WaitAllDoorBeClosed__2",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

void Capsule_CentralLock::transitionaction_____Debug__doorsOpen__WaitAllDoorBeClosed__2__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__C__doorsOpen__WaitAllDoorBeClosed__2::ex,WaitAllDoorBeClosed */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__doorsOpen__WaitAllDoorBeClosed__2__E",(char *)"ex",(char *)"WaitAllDoorBeClosed",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__doorsOpen__WaitAllDoorBeClosed__2__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__Path__doorsOpen__WaitAllDoorBeClosed__2,Debug__C__doorsOpen__WaitAllDoorBeClosed__2::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__doorsOpen__WaitAllDoorBeClosed__2__S",(char *)"Debug__Path__doorsOpen__WaitAllDoorBeClosed__2",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Debug__doorsOpen__WaitAllDoorBeClosed__2__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__C__doorsOpen__WaitAllDoorBeClosed__2::new_exitpoint_2,Debug__C__doorsOpen__WaitAllDoorBeClosed__2 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Debug__doorsOpen__WaitAllDoorBeClosed__2__dbg",(char *)"Debug__C__doorsOpen__WaitAllDoorBeClosed__2",(char *)"Debug__C__doorsOpen__WaitAllDoorBeClosed__2",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____Initial1__StartingUp__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__Path__Initial1__StartingUp__3,StartingUp */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::Initial1__StartingUp__3",(char *)"Debug__Path__Initial1__StartingUp__3",(char *)"StartingUp",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____StartingUp__doorsOpen__10( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__Path__StartingUp__doorsOpen__10,doorsOpen */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::StartingUp__doorsOpen__10",(char *)"Debug__Path__StartingUp__doorsOpen__10",(char *)"doorsOpen",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__Path__WaitAllDoorBeClosed__AllDoorClosed__9,AllDoorClosed */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::WaitAllDoorBeClosed__AllDoorClosed__9",(char *)"Debug__Path__WaitAllDoorBeClosed__AllDoorClosed__9",(char *)"AllDoorClosed",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__Path__WaitAllDoorBeOpened__Choice1__6,Choice1 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::WaitAllDoorBeOpened__Choice1__6",(char *)"Debug__Path__WaitAllDoorBeOpened__Choice1__6",(char *)"Choice1",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__Path__doorsClosed__WaitAllDoorBeOpened__4,WaitAllDoorBeOpened */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::doorsClosed__WaitAllDoorBeOpened__4",(char *)"Debug__Path__doorsClosed__WaitAllDoorBeOpened__4",(char *)"WaitAllDoorBeOpened",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_CentralLock::transitionaction_____doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock transition Debug__Path__doorsOpen__WaitAllDoorBeClosed__2,WaitAllDoorBeClosed */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::CentralLock::centralLockSM::Region1::doorsOpen__WaitAllDoorBeClosed__2",(char *)"Debug__Path__doorsOpen__WaitAllDoorBeClosed__2",(char *)"WaitAllDoorBeClosed",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_CentralLock::action_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8__S__Debug__GuardAllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock guard Debug__Path__AllDoorClosed__WaitAllDoorBeClosed__8,Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8::en */
    return Debug__SRO.checkDebug("AllDoorClosed","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

bool Capsule_CentralLock::action_____Debug__AllDoorClosed__doorsClosed__1__S__Debug__GuardAllDoorClosed__doorsClosed__1( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock guard Debug__Path__AllDoorClosed__doorsClosed__1,Debug__C__AllDoorClosed__doorsClosed__1::en */
    return Debug__SRO.checkDebug("AllDoorClosed","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

bool Capsule_CentralLock::action_____Debug__AllDoorClosed__doorsClosed__1__null( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock guard AllDoorClosed,Debug__Path__AllDoorClosed__doorsClosed__1 */
    return tmpInt==locksCount;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

bool Capsule_CentralLock::action_____Debug__Choice1__WaitAllDoorBeOpened__7__S__Debug__GuardChoice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock guard Debug__Path__Choice1__WaitAllDoorBeOpened__7,Debug__C__Choice1__WaitAllDoorBeOpened__7::en */
    return Debug__SRO.checkDebug("Choice1","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

bool Capsule_CentralLock::action_____Debug__Choice1__doorsOpen__5__S__Debug__GuardChoice1__doorsOpen__5( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock guard Debug__Path__Choice1__doorsOpen__5,Debug__C__Choice1__doorsOpen__5::en */
    return Debug__SRO.checkDebug("Choice1","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

bool Capsule_CentralLock::action_____Debug__Choice1__doorsOpen__5__null( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock guard Choice1,Debug__Path__Choice1__doorsOpen__5 */
    return tmpInt==locksCount;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

bool Capsule_CentralLock::action_____Debug__Initial1__StartingUp__3__S__Debug__GuardInitial1__StartingUp__3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock guard Debug__Path__Initial1__StartingUp__3,Debug__C__Initial1__StartingUp__3::en */
    return Debug__SRO.checkDebug("Initial1","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_CentralLock::action_____Debug__StartingUp__doorsOpen__10__S__Debug__GuardStartingUp__doorsOpen__10( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock guard Debug__Path__StartingUp__doorsOpen__10,Debug__C__StartingUp__doorsOpen__10::en */
    return Debug__SRO.checkDebug("StartingUp",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_CentralLock::action_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9__S__Debug__GuardWaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock guard Debug__Path__WaitAllDoorBeClosed__AllDoorClosed__9,Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9::en */
    return Debug__SRO.checkDebug("WaitAllDoorBeClosed",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

bool Capsule_CentralLock::action_____Debug__WaitAllDoorBeOpened__Choice1__6__S__Debug__GuardWaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock guard Debug__Path__WaitAllDoorBeOpened__Choice1__6,Debug__C__WaitAllDoorBeOpened__Choice1__6::en */
    return Debug__SRO.checkDebug("WaitAllDoorBeOpened",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

bool Capsule_CentralLock::action_____Debug__doorsClosed__WaitAllDoorBeOpened__4__S__Debug__GuarddoorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock guard Debug__Path__doorsClosed__WaitAllDoorBeOpened__4,Debug__C__doorsClosed__WaitAllDoorBeOpened__4::en */
    return Debug__SRO.checkDebug("doorsClosed",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

bool Capsule_CentralLock::action_____Debug__doorsOpen__WaitAllDoorBeClosed__2__S__Debug__GuarddoorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg )
{
    #define umlrtparam_locked ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::CentralLock guard Debug__Path__doorsOpen__WaitAllDoorBeClosed__2,Debug__C__doorsOpen__WaitAllDoorBeClosed__2::en */
    return Debug__SRO.checkDebug("doorsOpen",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_locked
}

void Capsule_CentralLock::actionchain_____AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg )
{
    transitionaction_____AllDoorClosed__WaitAllDoorBeClosed__8( msg );
    entryaction_____WaitAllDoorBeClosed( msg );
}

void Capsule_CentralLock::actionchain_____AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg )
{
    transitionaction_____AllDoorClosed__doorsClosed__1( msg );
    entryaction_____doorsClosed( msg );
}

void Capsule_CentralLock::actionchain_____Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg )
{
    transitionaction_____Choice1__WaitAllDoorBeOpened__7( msg );
    entryaction_____WaitAllDoorBeOpened( msg );
}

void Capsule_CentralLock::actionchain_____Choice1__doorsOpen__5( const UMLRTMessage * msg )
{
    transitionaction_____Choice1__doorsOpen__5( msg );
    entryaction_____doorsOpen( msg );
}

void Capsule_CentralLock::actionchain_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg )
{
    transitionaction_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8( msg );
}

void Capsule_CentralLock::actionchain_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__boundary( msg );
    transitionaction_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8__E( msg );
    entryaction_____WaitAllDoorBeClosed( msg );
}

void Capsule_CentralLock::actionchain_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8__S( msg );
    entryaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__boundary( msg );
    transitionaction_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8__dbg( msg );
    entryaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg )
{
    transitionaction_____Debug__AllDoorClosed__doorsClosed__1( msg );
}

void Capsule_CentralLock::actionchain_____Debug__AllDoorClosed__doorsClosed__1__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__AllDoorClosed__doorsClosed__1__boundary( msg );
    transitionaction_____Debug__AllDoorClosed__doorsClosed__1__E( msg );
    entryaction_____doorsClosed( msg );
}

void Capsule_CentralLock::actionchain_____Debug__AllDoorClosed__doorsClosed__1__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__AllDoorClosed__doorsClosed__1__S( msg );
    entryaction_____Debug__C__AllDoorClosed__doorsClosed__1__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__AllDoorClosed__doorsClosed__1__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__AllDoorClosed__doorsClosed__1__boundary( msg );
    transitionaction_____Debug__AllDoorClosed__doorsClosed__1__dbg( msg );
    entryaction_____Debug__C__AllDoorClosed__doorsClosed__1__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( msg );
    transitionaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( msg );
    entryaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__En__WaitAllDoorBeClosed( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( msg );
    transitionaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__En__WaitAllDoorBeClosed( msg );
    entryaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__end__trans__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8( msg );
    transitionaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__end__trans__AllDoorClosed__WaitAllDoorBeClosed__8( msg );
    save_history( Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8, Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8 );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__init__trans__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__init__trans__AllDoorClosed__WaitAllDoorBeClosed__8( msg );
    entryaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_61( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_62( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_63( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_64_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_65( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( msg );
    save_history( Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8, Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8 );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_66( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( msg );
    save_history( Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8, Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8 );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_67( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8( msg );
    save_history( Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8, Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8 );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_68( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__boundary( msg );
    save_history( Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8, Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__boundary );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__Ac__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__B__Ac__AllDoorClosed__doorsClosed__1( msg );
    transitionaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__Ac__AllDoorClosed__doorsClosed__1( msg );
    entryaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__Ac__AllDoorClosed__doorsClosed__1( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__En__doorsClosed( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__Ac__AllDoorClosed__doorsClosed__1( msg );
    transitionaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__En__doorsClosed( msg );
    entryaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__En__AllDoorClosed__doorsClosed__1( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__end__trans__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__En__AllDoorClosed__doorsClosed__1( msg );
    transitionaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__end__trans__AllDoorClosed__doorsClosed__1( msg );
    save_history( Debug__C__AllDoorClosed__doorsClosed__1, Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__En__AllDoorClosed__doorsClosed__1 );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__init__trans__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__init__trans__AllDoorClosed__doorsClosed__1( msg );
    entryaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__B__Ac__AllDoorClosed__doorsClosed__1( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_1( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__B__Ac__AllDoorClosed__doorsClosed__1( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_2( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__Ac__AllDoorClosed__doorsClosed__1( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_3( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__En__AllDoorClosed__doorsClosed__1( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_4_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__AllDoorClosed__doorsClosed__1__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_5( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__B__Ac__AllDoorClosed__doorsClosed__1( msg );
    save_history( Debug__C__AllDoorClosed__doorsClosed__1, Debug__C__AllDoorClosed__doorsClosed__1__Debug__B__Ac__AllDoorClosed__doorsClosed__1 );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_6( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__Ac__AllDoorClosed__doorsClosed__1( msg );
    save_history( Debug__C__AllDoorClosed__doorsClosed__1, Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__Ac__AllDoorClosed__doorsClosed__1 );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_7( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__En__AllDoorClosed__doorsClosed__1( msg );
    save_history( Debug__C__AllDoorClosed__doorsClosed__1, Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__En__AllDoorClosed__doorsClosed__1 );
}

void Capsule_CentralLock::actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_8( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__AllDoorClosed__doorsClosed__1__boundary( msg );
    save_history( Debug__C__AllDoorClosed__doorsClosed__1, Debug__C__AllDoorClosed__doorsClosed__1__boundary );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__Ac__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7( msg );
    transitionaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__Ac__Choice1__WaitAllDoorBeOpened__7( msg );
    entryaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__En__WaitAllDoorBeOpened( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7( msg );
    transitionaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__En__WaitAllDoorBeOpened( msg );
    entryaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__En__Choice1__WaitAllDoorBeOpened__7( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__end__trans__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__En__Choice1__WaitAllDoorBeOpened__7( msg );
    transitionaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__end__trans__Choice1__WaitAllDoorBeOpened__7( msg );
    save_history( Debug__C__Choice1__WaitAllDoorBeOpened__7, Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__En__Choice1__WaitAllDoorBeOpened__7 );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__init__trans__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__init__trans__Choice1__WaitAllDoorBeOpened__7( msg );
    entryaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_53( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_54( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_55( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__En__Choice1__WaitAllDoorBeOpened__7( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_56_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_57( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7( msg );
    save_history( Debug__C__Choice1__WaitAllDoorBeOpened__7, Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7 );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_58( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7( msg );
    save_history( Debug__C__Choice1__WaitAllDoorBeOpened__7, Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7 );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_59( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__En__Choice1__WaitAllDoorBeOpened__7( msg );
    save_history( Debug__C__Choice1__WaitAllDoorBeOpened__7, Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__En__Choice1__WaitAllDoorBeOpened__7 );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_60( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__boundary( msg );
    save_history( Debug__C__Choice1__WaitAllDoorBeOpened__7, Debug__C__Choice1__WaitAllDoorBeOpened__7__boundary );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__doorsOpen__5__Debug__Ac__Choice1__doorsOpen__5( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Choice1__doorsOpen__5__Debug__B__Ac__Choice1__doorsOpen__5( msg );
    transitionaction_____Debug__C__Choice1__doorsOpen__5__Debug__Ac__Choice1__doorsOpen__5( msg );
    entryaction_____Debug__C__Choice1__doorsOpen__5__Debug__A__Ac__Choice1__doorsOpen__5( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__doorsOpen__5__Debug__En__doorsOpen( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Choice1__doorsOpen__5__Debug__A__Ac__Choice1__doorsOpen__5( msg );
    transitionaction_____Debug__C__Choice1__doorsOpen__5__Debug__En__doorsOpen( msg );
    entryaction_____Debug__C__Choice1__doorsOpen__5__Debug__A__En__Choice1__doorsOpen__5( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__doorsOpen__5__Debug__end__trans__Choice1__doorsOpen__5( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Choice1__doorsOpen__5__Debug__A__En__Choice1__doorsOpen__5( msg );
    transitionaction_____Debug__C__Choice1__doorsOpen__5__Debug__end__trans__Choice1__doorsOpen__5( msg );
    save_history( Debug__C__Choice1__doorsOpen__5, Debug__C__Choice1__doorsOpen__5__Debug__A__En__Choice1__doorsOpen__5 );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__doorsOpen__5__Debug__init__trans__Choice1__doorsOpen__5( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__Choice1__doorsOpen__5__Debug__init__trans__Choice1__doorsOpen__5( msg );
    entryaction_____Debug__C__Choice1__doorsOpen__5__Debug__B__Ac__Choice1__doorsOpen__5( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_37( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Choice1__doorsOpen__5__Debug__B__Ac__Choice1__doorsOpen__5( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_38( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Choice1__doorsOpen__5__Debug__A__Ac__Choice1__doorsOpen__5( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_39( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Choice1__doorsOpen__5__Debug__A__En__Choice1__doorsOpen__5( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_40_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Choice1__doorsOpen__5__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_41( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Choice1__doorsOpen__5__Debug__B__Ac__Choice1__doorsOpen__5( msg );
    save_history( Debug__C__Choice1__doorsOpen__5, Debug__C__Choice1__doorsOpen__5__Debug__B__Ac__Choice1__doorsOpen__5 );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_42( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Choice1__doorsOpen__5__Debug__A__Ac__Choice1__doorsOpen__5( msg );
    save_history( Debug__C__Choice1__doorsOpen__5, Debug__C__Choice1__doorsOpen__5__Debug__A__Ac__Choice1__doorsOpen__5 );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_43( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Choice1__doorsOpen__5__Debug__A__En__Choice1__doorsOpen__5( msg );
    save_history( Debug__C__Choice1__doorsOpen__5, Debug__C__Choice1__doorsOpen__5__Debug__A__En__Choice1__doorsOpen__5 );
}

void Capsule_CentralLock::actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_44( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Choice1__doorsOpen__5__boundary( msg );
    save_history( Debug__C__Choice1__doorsOpen__5, Debug__C__Choice1__doorsOpen__5__boundary );
}

void Capsule_CentralLock::actionchain_____Debug__C__Initial1__StartingUp__3__Debug__Ac__Initial1__StartingUp__3( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial1__StartingUp__3__Debug__B__Ac__Initial1__StartingUp__3( msg );
    transitionaction_____Debug__C__Initial1__StartingUp__3__Debug__Ac__Initial1__StartingUp__3( msg );
    entryaction_____Debug__C__Initial1__StartingUp__3__Debug__A__Ac__Initial1__StartingUp__3( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__Initial1__StartingUp__3__Debug__En__StartingUp( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial1__StartingUp__3__Debug__A__Ac__Initial1__StartingUp__3( msg );
    transitionaction_____Debug__C__Initial1__StartingUp__3__Debug__En__StartingUp( msg );
    entryaction_____Debug__C__Initial1__StartingUp__3__Debug__A__En__Initial1__StartingUp__3( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__Initial1__StartingUp__3__Debug__end__trans__Initial1__StartingUp__3( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial1__StartingUp__3__Debug__A__En__Initial1__StartingUp__3( msg );
    transitionaction_____Debug__C__Initial1__StartingUp__3__Debug__end__trans__Initial1__StartingUp__3( msg );
    save_history( Debug__C__Initial1__StartingUp__3, Debug__C__Initial1__StartingUp__3__Debug__A__En__Initial1__StartingUp__3 );
}

void Capsule_CentralLock::actionchain_____Debug__C__Initial1__StartingUp__3__Debug__init__trans__Initial1__StartingUp__3( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__Initial1__StartingUp__3__Debug__init__trans__Initial1__StartingUp__3( msg );
    entryaction_____Debug__C__Initial1__StartingUp__3__Debug__B__Ac__Initial1__StartingUp__3( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_19( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Initial1__StartingUp__3__Debug__B__Ac__Initial1__StartingUp__3( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_20( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Initial1__StartingUp__3__Debug__A__Ac__Initial1__StartingUp__3( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_21( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Initial1__StartingUp__3__Debug__A__En__Initial1__StartingUp__3( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_22_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Initial1__StartingUp__3__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_23( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial1__StartingUp__3__Debug__B__Ac__Initial1__StartingUp__3( msg );
    save_history( Debug__C__Initial1__StartingUp__3, Debug__C__Initial1__StartingUp__3__Debug__B__Ac__Initial1__StartingUp__3 );
}

void Capsule_CentralLock::actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_24( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial1__StartingUp__3__Debug__A__Ac__Initial1__StartingUp__3( msg );
    save_history( Debug__C__Initial1__StartingUp__3, Debug__C__Initial1__StartingUp__3__Debug__A__Ac__Initial1__StartingUp__3 );
}

void Capsule_CentralLock::actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_25( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial1__StartingUp__3__Debug__A__En__Initial1__StartingUp__3( msg );
    save_history( Debug__C__Initial1__StartingUp__3, Debug__C__Initial1__StartingUp__3__Debug__A__En__Initial1__StartingUp__3 );
}

void Capsule_CentralLock::actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_26( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial1__StartingUp__3__boundary( msg );
    save_history( Debug__C__Initial1__StartingUp__3, Debug__C__Initial1__StartingUp__3__boundary );
}

void Capsule_CentralLock::actionchain_____Debug__C__StartingUp__doorsOpen__10__Debug__AC__StartingUp__doorsOpen__10( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StartingUp__doorsOpen__10__Debug__B__Ac__StartingUp__doorsOpen__10( msg );
    transitionaction_____Debug__C__StartingUp__doorsOpen__10__Debug__AC__StartingUp__doorsOpen__10( msg );
    entryaction_____Debug__C__StartingUp__doorsOpen__10__Debug__A__Ac__StartingUp__doorsOpen__10( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__StartingUp__doorsOpen__10__Debug__En__doorsOpen( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StartingUp__doorsOpen__10__Debug__A__Ac__StartingUp__doorsOpen__10( msg );
    transitionaction_____Debug__C__StartingUp__doorsOpen__10__Debug__En__doorsOpen( msg );
    entryaction_____Debug__C__StartingUp__doorsOpen__10__Debug__A__En__doorsOpen( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__StartingUp__doorsOpen__10__Debug__Ex__StartingUp( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StartingUp__doorsOpen__10__Debug__B__Ex__StartingUp( msg );
    transitionaction_____Debug__C__StartingUp__doorsOpen__10__Debug__Ex__StartingUp( msg );
    entryaction_____Debug__C__StartingUp__doorsOpen__10__Debug__B__Ac__StartingUp__doorsOpen__10( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__StartingUp__doorsOpen__10__Debug__end__trans__StartingUp__doorsOpen__10( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StartingUp__doorsOpen__10__Debug__A__En__doorsOpen( msg );
    transitionaction_____Debug__C__StartingUp__doorsOpen__10__Debug__end__trans__StartingUp__doorsOpen__10( msg );
    save_history( Debug__C__StartingUp__doorsOpen__10, Debug__C__StartingUp__doorsOpen__10__Debug__A__En__doorsOpen );
}

void Capsule_CentralLock::actionchain_____Debug__C__StartingUp__doorsOpen__10__Debug__init__trans__StartingUp__doorsOpen__10( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__StartingUp__doorsOpen__10__Debug__init__trans__StartingUp__doorsOpen__10( msg );
    entryaction_____Debug__C__StartingUp__doorsOpen__10__Debug__B__Ex__StartingUp( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_77( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__StartingUp__doorsOpen__10__Debug__B__Ex__StartingUp( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_78( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__StartingUp__doorsOpen__10__Debug__B__Ac__StartingUp__doorsOpen__10( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_79( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__StartingUp__doorsOpen__10__Debug__A__Ac__StartingUp__doorsOpen__10( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_80( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__StartingUp__doorsOpen__10__Debug__A__En__doorsOpen( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_81_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__StartingUp__doorsOpen__10__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_82( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StartingUp__doorsOpen__10__Debug__B__Ex__StartingUp( msg );
    save_history( Debug__C__StartingUp__doorsOpen__10, Debug__C__StartingUp__doorsOpen__10__Debug__B__Ex__StartingUp );
}

void Capsule_CentralLock::actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_83( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StartingUp__doorsOpen__10__Debug__B__Ac__StartingUp__doorsOpen__10( msg );
    save_history( Debug__C__StartingUp__doorsOpen__10, Debug__C__StartingUp__doorsOpen__10__Debug__B__Ac__StartingUp__doorsOpen__10 );
}

void Capsule_CentralLock::actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_84( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StartingUp__doorsOpen__10__Debug__A__Ac__StartingUp__doorsOpen__10( msg );
    save_history( Debug__C__StartingUp__doorsOpen__10, Debug__C__StartingUp__doorsOpen__10__Debug__A__Ac__StartingUp__doorsOpen__10 );
}

void Capsule_CentralLock::actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_85( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StartingUp__doorsOpen__10__Debug__A__En__doorsOpen( msg );
    save_history( Debug__C__StartingUp__doorsOpen__10, Debug__C__StartingUp__doorsOpen__10__Debug__A__En__doorsOpen );
}

void Capsule_CentralLock::actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_86( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StartingUp__doorsOpen__10__boundary( msg );
    save_history( Debug__C__StartingUp__doorsOpen__10, Debug__C__StartingUp__doorsOpen__10__boundary );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__AC__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9( msg );
    transitionaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__AC__WaitAllDoorBeClosed__AllDoorClosed__9( msg );
    entryaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__Ex__WaitAllDoorBeClosed( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ex__WaitAllDoorBeClosed( msg );
    transitionaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__Ex__WaitAllDoorBeClosed( msg );
    entryaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__end__trans__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9( msg );
    transitionaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__end__trans__WaitAllDoorBeClosed__AllDoorClosed__9( msg );
    save_history( Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9, Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9 );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__init__trans__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ex__WaitAllDoorBeClosed( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_69( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ex__WaitAllDoorBeClosed( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_70( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_71( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_72_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_73( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ex__WaitAllDoorBeClosed( msg );
    save_history( Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9, Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ex__WaitAllDoorBeClosed );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_74( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9( msg );
    save_history( Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9, Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9 );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_75( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9( msg );
    save_history( Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9, Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9 );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_76( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__boundary( msg );
    save_history( Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9, Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__boundary );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__AC__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6( msg );
    transitionaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__AC__WaitAllDoorBeOpened__Choice1__6( msg );
    entryaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__Ex__WaitAllDoorBeOpened( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ex__WaitAllDoorBeOpened( msg );
    transitionaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__Ex__WaitAllDoorBeOpened( msg );
    entryaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__end__trans__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6( msg );
    transitionaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__end__trans__WaitAllDoorBeOpened__Choice1__6( msg );
    save_history( Debug__C__WaitAllDoorBeOpened__Choice1__6, Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6 );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__init__trans__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ex__WaitAllDoorBeOpened( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_45( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ex__WaitAllDoorBeOpened( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_46( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_47( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_48_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_49( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ex__WaitAllDoorBeOpened( msg );
    save_history( Debug__C__WaitAllDoorBeOpened__Choice1__6, Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ex__WaitAllDoorBeOpened );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_50( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6( msg );
    save_history( Debug__C__WaitAllDoorBeOpened__Choice1__6, Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6 );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_51( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6( msg );
    save_history( Debug__C__WaitAllDoorBeOpened__Choice1__6, Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6 );
}

void Capsule_CentralLock::actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_52( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__boundary( msg );
    save_history( Debug__C__WaitAllDoorBeOpened__Choice1__6, Debug__C__WaitAllDoorBeOpened__Choice1__6__boundary );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__AC__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4( msg );
    transitionaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__AC__doorsClosed__WaitAllDoorBeOpened__4( msg );
    entryaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__En__WaitAllDoorBeOpened( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4( msg );
    transitionaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__En__WaitAllDoorBeOpened( msg );
    entryaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__En__WaitAllDoorBeOpened( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__Ex__doorsClosed( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ex__doorsClosed( msg );
    transitionaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__Ex__doorsClosed( msg );
    entryaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__end__trans__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__En__WaitAllDoorBeOpened( msg );
    transitionaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__end__trans__doorsClosed__WaitAllDoorBeOpened__4( msg );
    save_history( Debug__C__doorsClosed__WaitAllDoorBeOpened__4, Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__En__WaitAllDoorBeOpened );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__init__trans__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__init__trans__doorsClosed__WaitAllDoorBeOpened__4( msg );
    entryaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ex__doorsClosed( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_27( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ex__doorsClosed( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_28( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_29( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_30( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__En__WaitAllDoorBeOpened( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_31_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_32( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ex__doorsClosed( msg );
    save_history( Debug__C__doorsClosed__WaitAllDoorBeOpened__4, Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ex__doorsClosed );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_33( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4( msg );
    save_history( Debug__C__doorsClosed__WaitAllDoorBeOpened__4, Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4 );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_34( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4( msg );
    save_history( Debug__C__doorsClosed__WaitAllDoorBeOpened__4, Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4 );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_35( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__En__WaitAllDoorBeOpened( msg );
    save_history( Debug__C__doorsClosed__WaitAllDoorBeOpened__4, Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__En__WaitAllDoorBeOpened );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_36( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__boundary( msg );
    save_history( Debug__C__doorsClosed__WaitAllDoorBeOpened__4, Debug__C__doorsClosed__WaitAllDoorBeOpened__4__boundary );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__AC__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2( msg );
    transitionaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__AC__doorsOpen__WaitAllDoorBeClosed__2( msg );
    entryaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__En__WaitAllDoorBeClosed( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2( msg );
    transitionaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__En__WaitAllDoorBeClosed( msg );
    entryaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__En__WaitAllDoorBeClosed( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__Ex__doorsOpen( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ex__doorsOpen( msg );
    transitionaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__Ex__doorsOpen( msg );
    entryaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__end__trans__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__En__WaitAllDoorBeClosed( msg );
    transitionaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__end__trans__doorsOpen__WaitAllDoorBeClosed__2( msg );
    save_history( Debug__C__doorsOpen__WaitAllDoorBeClosed__2, Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__En__WaitAllDoorBeClosed );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__init__trans__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__init__trans__doorsOpen__WaitAllDoorBeClosed__2( msg );
    entryaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ex__doorsOpen( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_10( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_11( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_12( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__En__WaitAllDoorBeClosed( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_13_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_14( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ex__doorsOpen( msg );
    save_history( Debug__C__doorsOpen__WaitAllDoorBeClosed__2, Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ex__doorsOpen );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_15( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2( msg );
    save_history( Debug__C__doorsOpen__WaitAllDoorBeClosed__2, Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2 );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_16( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2( msg );
    save_history( Debug__C__doorsOpen__WaitAllDoorBeClosed__2, Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2 );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_17( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__En__WaitAllDoorBeClosed( msg );
    save_history( Debug__C__doorsOpen__WaitAllDoorBeClosed__2, Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__En__WaitAllDoorBeClosed );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_18( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__boundary( msg );
    save_history( Debug__C__doorsOpen__WaitAllDoorBeClosed__2, Debug__C__doorsOpen__WaitAllDoorBeClosed__2__boundary );
}

void Capsule_CentralLock::actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_9( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ex__doorsOpen( msg );
}

void Capsule_CentralLock::actionchain_____Debug__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg )
{
    transitionaction_____Debug__Choice1__WaitAllDoorBeOpened__7( msg );
}

void Capsule_CentralLock::actionchain_____Debug__Choice1__WaitAllDoorBeOpened__7__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__boundary( msg );
    transitionaction_____Debug__Choice1__WaitAllDoorBeOpened__7__E( msg );
    entryaction_____WaitAllDoorBeOpened( msg );
}

void Capsule_CentralLock::actionchain_____Debug__Choice1__WaitAllDoorBeOpened__7__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__Choice1__WaitAllDoorBeOpened__7__S( msg );
    entryaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__Choice1__WaitAllDoorBeOpened__7__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__boundary( msg );
    transitionaction_____Debug__Choice1__WaitAllDoorBeOpened__7__dbg( msg );
    entryaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__Choice1__doorsOpen__5( const UMLRTMessage * msg )
{
    transitionaction_____Debug__Choice1__doorsOpen__5( msg );
}

void Capsule_CentralLock::actionchain_____Debug__Choice1__doorsOpen__5__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Choice1__doorsOpen__5__boundary( msg );
    transitionaction_____Debug__Choice1__doorsOpen__5__E( msg );
    entryaction_____doorsOpen( msg );
}

void Capsule_CentralLock::actionchain_____Debug__Choice1__doorsOpen__5__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__Choice1__doorsOpen__5__S( msg );
    entryaction_____Debug__C__Choice1__doorsOpen__5__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__Choice1__doorsOpen__5__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Choice1__doorsOpen__5__boundary( msg );
    transitionaction_____Debug__Choice1__doorsOpen__5__dbg( msg );
    entryaction_____Debug__C__Choice1__doorsOpen__5__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__InitDebug( const UMLRTMessage * msg )
{
    transitionaction_____Debug__InitDebug( msg );
    entryaction_____Debug__InitState( msg );
}

void Capsule_CentralLock::actionchain_____Debug__Initial1__StartingUp__3( const UMLRTMessage * msg )
{
    exitaction_____Debug__InitState( msg );
    transitionaction_____Debug__Initial1__StartingUp__3( msg );
}

void Capsule_CentralLock::actionchain_____Debug__Initial1__StartingUp__3__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial1__StartingUp__3__boundary( msg );
    transitionaction_____Debug__Initial1__StartingUp__3__E( msg );
    entryaction_____StartingUp( msg );
}

void Capsule_CentralLock::actionchain_____Debug__Initial1__StartingUp__3__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__Initial1__StartingUp__3__S( msg );
    entryaction_____Debug__C__Initial1__StartingUp__3__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__Initial1__StartingUp__3__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial1__StartingUp__3__boundary( msg );
    transitionaction_____Debug__Initial1__StartingUp__3__dbg( msg );
    entryaction_____Debug__C__Initial1__StartingUp__3__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__StartingUp__doorsOpen__10( const UMLRTMessage * msg )
{
    exitaction_____StartingUp( msg );
    transitionaction_____Debug__StartingUp__doorsOpen__10( msg );
}

void Capsule_CentralLock::actionchain_____Debug__StartingUp__doorsOpen__10__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StartingUp__doorsOpen__10__boundary( msg );
    transitionaction_____Debug__StartingUp__doorsOpen__10__E( msg );
    entryaction_____doorsOpen( msg );
}

void Capsule_CentralLock::actionchain_____Debug__StartingUp__doorsOpen__10__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__StartingUp__doorsOpen__10__S( msg );
    entryaction_____Debug__C__StartingUp__doorsOpen__10__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__StartingUp__doorsOpen__10__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__StartingUp__doorsOpen__10__boundary( msg );
    transitionaction_____Debug__StartingUp__doorsOpen__10__dbg( msg );
    entryaction_____Debug__C__StartingUp__doorsOpen__10__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg )
{
    exitaction_____WaitAllDoorBeClosed( msg );
    transitionaction_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9( msg );
}

void Capsule_CentralLock::actionchain_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__boundary( msg );
    transitionaction_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9__E( msg );
}

void Capsule_CentralLock::actionchain_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9__S( msg );
    entryaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__boundary( msg );
    transitionaction_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9__dbg( msg );
    entryaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg )
{
    exitaction_____WaitAllDoorBeOpened( msg );
    transitionaction_____Debug__WaitAllDoorBeOpened__Choice1__6( msg );
}

void Capsule_CentralLock::actionchain_____Debug__WaitAllDoorBeOpened__Choice1__6__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__boundary( msg );
    transitionaction_____Debug__WaitAllDoorBeOpened__Choice1__6__E( msg );
}

void Capsule_CentralLock::actionchain_____Debug__WaitAllDoorBeOpened__Choice1__6__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__WaitAllDoorBeOpened__Choice1__6__S( msg );
    entryaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__WaitAllDoorBeOpened__Choice1__6__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__boundary( msg );
    transitionaction_____Debug__WaitAllDoorBeOpened__Choice1__6__dbg( msg );
    entryaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg )
{
    exitaction_____doorsClosed( msg );
    transitionaction_____Debug__doorsClosed__WaitAllDoorBeOpened__4( msg );
}

void Capsule_CentralLock::actionchain_____Debug__doorsClosed__WaitAllDoorBeOpened__4__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__boundary( msg );
    transitionaction_____Debug__doorsClosed__WaitAllDoorBeOpened__4__E( msg );
    entryaction_____WaitAllDoorBeOpened( msg );
}

void Capsule_CentralLock::actionchain_____Debug__doorsClosed__WaitAllDoorBeOpened__4__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__doorsClosed__WaitAllDoorBeOpened__4__S( msg );
    entryaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__doorsClosed__WaitAllDoorBeOpened__4__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__boundary( msg );
    transitionaction_____Debug__doorsClosed__WaitAllDoorBeOpened__4__dbg( msg );
    entryaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg )
{
    exitaction_____doorsOpen( msg );
    transitionaction_____Debug__doorsOpen__WaitAllDoorBeClosed__2( msg );
}

void Capsule_CentralLock::actionchain_____Debug__doorsOpen__WaitAllDoorBeClosed__2__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__boundary( msg );
    transitionaction_____Debug__doorsOpen__WaitAllDoorBeClosed__2__E( msg );
    entryaction_____WaitAllDoorBeClosed( msg );
}

void Capsule_CentralLock::actionchain_____Debug__doorsOpen__WaitAllDoorBeClosed__2__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__doorsOpen__WaitAllDoorBeClosed__2__S( msg );
    entryaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Debug__doorsOpen__WaitAllDoorBeClosed__2__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__boundary( msg );
    transitionaction_____Debug__doorsOpen__WaitAllDoorBeClosed__2__dbg( msg );
    entryaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__boundary( msg );
}

void Capsule_CentralLock::actionchain_____Initial1__StartingUp__3( const UMLRTMessage * msg )
{
    transitionaction_____Initial1__StartingUp__3( msg );
    entryaction_____StartingUp( msg );
}

void Capsule_CentralLock::actionchain_____StartingUp__doorsOpen__10( const UMLRTMessage * msg )
{
    transitionaction_____StartingUp__doorsOpen__10( msg );
    entryaction_____doorsOpen( msg );
}

void Capsule_CentralLock::actionchain_____WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg )
{
    transitionaction_____WaitAllDoorBeClosed__AllDoorClosed__9( msg );
}

void Capsule_CentralLock::actionchain_____WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg )
{
    transitionaction_____WaitAllDoorBeOpened__Choice1__6( msg );
}

void Capsule_CentralLock::actionchain_____doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg )
{
    transitionaction_____doorsClosed__WaitAllDoorBeOpened__4( msg );
    entryaction_____WaitAllDoorBeOpened( msg );
}

void Capsule_CentralLock::actionchain_____doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg )
{
    transitionaction_____doorsOpen__WaitAllDoorBeClosed__2( msg );
    entryaction_____WaitAllDoorBeClosed( msg );
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__init__trans__AllDoorClosed__WaitAllDoorBeClosed__8( msg );
    return Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8;
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8__E( msg );
    return WaitAllDoorBeClosed;
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_exitpoint_8( const UMLRTMessage * msg )
{
    actionchain_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8__dbg( msg );
    return choice_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__deephistory( msg );
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__AllDoorClosed__doorsClosed__1__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__init__trans__AllDoorClosed__doorsClosed__1( msg );
    return Debug__C__AllDoorClosed__doorsClosed__1__Debug__B__Ac__AllDoorClosed__doorsClosed__1;
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__AllDoorClosed__doorsClosed__1__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__AllDoorClosed__doorsClosed__1__E( msg );
    return doorsClosed;
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__AllDoorClosed__doorsClosed__1__new_exitpoint_1( const UMLRTMessage * msg )
{
    actionchain_____Debug__AllDoorClosed__doorsClosed__1__dbg( msg );
    return choice_____Debug__C__AllDoorClosed__doorsClosed__1__deephistory( msg );
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__init__trans__Choice1__WaitAllDoorBeOpened__7( msg );
    return Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7;
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__Choice1__WaitAllDoorBeOpened__7__E( msg );
    return WaitAllDoorBeOpened;
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_exitpoint_7( const UMLRTMessage * msg )
{
    actionchain_____Debug__Choice1__WaitAllDoorBeOpened__7__dbg( msg );
    return choice_____Debug__C__Choice1__WaitAllDoorBeOpened__7__deephistory( msg );
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__Choice1__doorsOpen__5__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__Choice1__doorsOpen__5__Debug__init__trans__Choice1__doorsOpen__5( msg );
    return Debug__C__Choice1__doorsOpen__5__Debug__B__Ac__Choice1__doorsOpen__5;
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__Choice1__doorsOpen__5__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__Choice1__doorsOpen__5__E( msg );
    return doorsOpen;
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__Choice1__doorsOpen__5__new_exitpoint_5( const UMLRTMessage * msg )
{
    actionchain_____Debug__Choice1__doorsOpen__5__dbg( msg );
    return choice_____Debug__C__Choice1__doorsOpen__5__deephistory( msg );
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__Initial1__StartingUp__3__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__Initial1__StartingUp__3__Debug__init__trans__Initial1__StartingUp__3( msg );
    return Debug__C__Initial1__StartingUp__3__Debug__B__Ac__Initial1__StartingUp__3;
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__Initial1__StartingUp__3__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial1__StartingUp__3__E( msg );
    return StartingUp;
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__Initial1__StartingUp__3__new_exitpoint_3( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial1__StartingUp__3__dbg( msg );
    return choice_____Debug__C__Initial1__StartingUp__3__deephistory( msg );
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__StartingUp__doorsOpen__10__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__StartingUp__doorsOpen__10__Debug__init__trans__StartingUp__doorsOpen__10( msg );
    return Debug__C__StartingUp__doorsOpen__10__Debug__B__Ex__StartingUp;
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__StartingUp__doorsOpen__10__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__StartingUp__doorsOpen__10__E( msg );
    return doorsOpen;
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__StartingUp__doorsOpen__10__new_exitpoint_10( const UMLRTMessage * msg )
{
    actionchain_____Debug__StartingUp__doorsOpen__10__dbg( msg );
    return choice_____Debug__C__StartingUp__doorsOpen__10__deephistory( msg );
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__init__trans__WaitAllDoorBeClosed__AllDoorClosed__9( msg );
    return Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ex__WaitAllDoorBeClosed;
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9__E( msg );
    return choice_____AllDoorClosed( msg );
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_exitpoint_9( const UMLRTMessage * msg )
{
    actionchain_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9__dbg( msg );
    return choice_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__deephistory( msg );
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__init__trans__WaitAllDoorBeOpened__Choice1__6( msg );
    return Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ex__WaitAllDoorBeOpened;
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__WaitAllDoorBeOpened__Choice1__6__E( msg );
    return choice_____Choice1( msg );
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_exitpoint_6( const UMLRTMessage * msg )
{
    actionchain_____Debug__WaitAllDoorBeOpened__Choice1__6__dbg( msg );
    return choice_____Debug__C__WaitAllDoorBeOpened__Choice1__6__deephistory( msg );
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__init__trans__doorsClosed__WaitAllDoorBeOpened__4( msg );
    return Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ex__doorsClosed;
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__doorsClosed__WaitAllDoorBeOpened__4__E( msg );
    return WaitAllDoorBeOpened;
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_exitpoint_4( const UMLRTMessage * msg )
{
    actionchain_____Debug__doorsClosed__WaitAllDoorBeOpened__4__dbg( msg );
    return choice_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__deephistory( msg );
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__init__trans__doorsOpen__WaitAllDoorBeClosed__2( msg );
    return Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ex__doorsOpen;
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__doorsOpen__WaitAllDoorBeClosed__2__E( msg );
    return WaitAllDoorBeClosed;
}

Capsule_CentralLock::State Capsule_CentralLock::junction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_exitpoint_2( const UMLRTMessage * msg )
{
    actionchain_____Debug__doorsOpen__WaitAllDoorBeClosed__2__dbg( msg );
    return choice_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__deephistory( msg );
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____AllDoorClosed( const UMLRTMessage * msg )
{
    if( action_____Debug__AllDoorClosed__doorsClosed__1__null( msg ) )
    {
        actionchain_____Debug__AllDoorClosed__doorsClosed__1( msg );
        return choice_____Debug__Path__AllDoorClosed__doorsClosed__1( msg );
    }
    else
    {
        actionchain_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8( msg );
        return choice_____Debug__Path__AllDoorClosed__WaitAllDoorBeClosed__8( msg );
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____Choice1( const UMLRTMessage * msg )
{
    if( action_____Debug__Choice1__doorsOpen__5__null( msg ) )
    {
        actionchain_____Debug__Choice1__doorsOpen__5( msg );
        return choice_____Debug__Path__Choice1__doorsOpen__5( msg );
    }
    else
    {
        actionchain_____Debug__Choice1__WaitAllDoorBeOpened__7( msg );
        return choice_____Debug__Path__Choice1__WaitAllDoorBeOpened__7( msg );
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8, Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8 ) )
    {
        actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_61( msg );
        return Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8;
    }
    else if( check_history( Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8, Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8 ) )
    {
        actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_62( msg );
        return Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8;
    }
    else if( check_history( Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8, Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8 ) )
    {
        actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_63( msg );
        return Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8;
    }
    else if( check_history( Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_64_to_boundary( msg );
        return Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__boundary;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____Debug__C__AllDoorClosed__doorsClosed__1__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__AllDoorClosed__doorsClosed__1, Debug__C__AllDoorClosed__doorsClosed__1__Debug__B__Ac__AllDoorClosed__doorsClosed__1 ) )
    {
        actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_1( msg );
        return Debug__C__AllDoorClosed__doorsClosed__1__Debug__B__Ac__AllDoorClosed__doorsClosed__1;
    }
    else if( check_history( Debug__C__AllDoorClosed__doorsClosed__1, Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__Ac__AllDoorClosed__doorsClosed__1 ) )
    {
        actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_2( msg );
        return Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__Ac__AllDoorClosed__doorsClosed__1;
    }
    else if( check_history( Debug__C__AllDoorClosed__doorsClosed__1, Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__En__AllDoorClosed__doorsClosed__1 ) )
    {
        actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_3( msg );
        return Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__En__AllDoorClosed__doorsClosed__1;
    }
    else if( check_history( Debug__C__AllDoorClosed__doorsClosed__1, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_4_to_boundary( msg );
        return Debug__C__AllDoorClosed__doorsClosed__1__boundary;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____Debug__C__Choice1__WaitAllDoorBeOpened__7__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__Choice1__WaitAllDoorBeOpened__7, Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7 ) )
    {
        actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_53( msg );
        return Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7;
    }
    else if( check_history( Debug__C__Choice1__WaitAllDoorBeOpened__7, Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7 ) )
    {
        actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_54( msg );
        return Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7;
    }
    else if( check_history( Debug__C__Choice1__WaitAllDoorBeOpened__7, Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__En__Choice1__WaitAllDoorBeOpened__7 ) )
    {
        actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_55( msg );
        return Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__En__Choice1__WaitAllDoorBeOpened__7;
    }
    else if( check_history( Debug__C__Choice1__WaitAllDoorBeOpened__7, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_56_to_boundary( msg );
        return Debug__C__Choice1__WaitAllDoorBeOpened__7__boundary;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____Debug__C__Choice1__doorsOpen__5__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__Choice1__doorsOpen__5, Debug__C__Choice1__doorsOpen__5__Debug__B__Ac__Choice1__doorsOpen__5 ) )
    {
        actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_37( msg );
        return Debug__C__Choice1__doorsOpen__5__Debug__B__Ac__Choice1__doorsOpen__5;
    }
    else if( check_history( Debug__C__Choice1__doorsOpen__5, Debug__C__Choice1__doorsOpen__5__Debug__A__Ac__Choice1__doorsOpen__5 ) )
    {
        actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_38( msg );
        return Debug__C__Choice1__doorsOpen__5__Debug__A__Ac__Choice1__doorsOpen__5;
    }
    else if( check_history( Debug__C__Choice1__doorsOpen__5, Debug__C__Choice1__doorsOpen__5__Debug__A__En__Choice1__doorsOpen__5 ) )
    {
        actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_39( msg );
        return Debug__C__Choice1__doorsOpen__5__Debug__A__En__Choice1__doorsOpen__5;
    }
    else if( check_history( Debug__C__Choice1__doorsOpen__5, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_40_to_boundary( msg );
        return Debug__C__Choice1__doorsOpen__5__boundary;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____Debug__C__Initial1__StartingUp__3__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__Initial1__StartingUp__3, Debug__C__Initial1__StartingUp__3__Debug__B__Ac__Initial1__StartingUp__3 ) )
    {
        actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_19( msg );
        return Debug__C__Initial1__StartingUp__3__Debug__B__Ac__Initial1__StartingUp__3;
    }
    else if( check_history( Debug__C__Initial1__StartingUp__3, Debug__C__Initial1__StartingUp__3__Debug__A__Ac__Initial1__StartingUp__3 ) )
    {
        actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_20( msg );
        return Debug__C__Initial1__StartingUp__3__Debug__A__Ac__Initial1__StartingUp__3;
    }
    else if( check_history( Debug__C__Initial1__StartingUp__3, Debug__C__Initial1__StartingUp__3__Debug__A__En__Initial1__StartingUp__3 ) )
    {
        actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_21( msg );
        return Debug__C__Initial1__StartingUp__3__Debug__A__En__Initial1__StartingUp__3;
    }
    else if( check_history( Debug__C__Initial1__StartingUp__3, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_22_to_boundary( msg );
        return Debug__C__Initial1__StartingUp__3__boundary;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____Debug__C__StartingUp__doorsOpen__10__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__StartingUp__doorsOpen__10, Debug__C__StartingUp__doorsOpen__10__Debug__B__Ex__StartingUp ) )
    {
        actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_77( msg );
        return Debug__C__StartingUp__doorsOpen__10__Debug__B__Ex__StartingUp;
    }
    else if( check_history( Debug__C__StartingUp__doorsOpen__10, Debug__C__StartingUp__doorsOpen__10__Debug__B__Ac__StartingUp__doorsOpen__10 ) )
    {
        actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_78( msg );
        return Debug__C__StartingUp__doorsOpen__10__Debug__B__Ac__StartingUp__doorsOpen__10;
    }
    else if( check_history( Debug__C__StartingUp__doorsOpen__10, Debug__C__StartingUp__doorsOpen__10__Debug__A__Ac__StartingUp__doorsOpen__10 ) )
    {
        actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_79( msg );
        return Debug__C__StartingUp__doorsOpen__10__Debug__A__Ac__StartingUp__doorsOpen__10;
    }
    else if( check_history( Debug__C__StartingUp__doorsOpen__10, Debug__C__StartingUp__doorsOpen__10__Debug__A__En__doorsOpen ) )
    {
        actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_80( msg );
        return Debug__C__StartingUp__doorsOpen__10__Debug__A__En__doorsOpen;
    }
    else if( check_history( Debug__C__StartingUp__doorsOpen__10, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_81_to_boundary( msg );
        return Debug__C__StartingUp__doorsOpen__10__boundary;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9, Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ex__WaitAllDoorBeClosed ) )
    {
        actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_69( msg );
        return Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ex__WaitAllDoorBeClosed;
    }
    else if( check_history( Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9, Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9 ) )
    {
        actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_70( msg );
        return Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9;
    }
    else if( check_history( Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9, Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9 ) )
    {
        actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_71( msg );
        return Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9;
    }
    else if( check_history( Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_72_to_boundary( msg );
        return Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__boundary;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____Debug__C__WaitAllDoorBeOpened__Choice1__6__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__WaitAllDoorBeOpened__Choice1__6, Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ex__WaitAllDoorBeOpened ) )
    {
        actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_45( msg );
        return Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ex__WaitAllDoorBeOpened;
    }
    else if( check_history( Debug__C__WaitAllDoorBeOpened__Choice1__6, Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6 ) )
    {
        actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_46( msg );
        return Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6;
    }
    else if( check_history( Debug__C__WaitAllDoorBeOpened__Choice1__6, Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6 ) )
    {
        actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_47( msg );
        return Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6;
    }
    else if( check_history( Debug__C__WaitAllDoorBeOpened__Choice1__6, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_48_to_boundary( msg );
        return Debug__C__WaitAllDoorBeOpened__Choice1__6__boundary;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__doorsClosed__WaitAllDoorBeOpened__4, Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ex__doorsClosed ) )
    {
        actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_27( msg );
        return Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ex__doorsClosed;
    }
    else if( check_history( Debug__C__doorsClosed__WaitAllDoorBeOpened__4, Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4 ) )
    {
        actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_28( msg );
        return Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4;
    }
    else if( check_history( Debug__C__doorsClosed__WaitAllDoorBeOpened__4, Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4 ) )
    {
        actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_29( msg );
        return Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4;
    }
    else if( check_history( Debug__C__doorsClosed__WaitAllDoorBeOpened__4, Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__En__WaitAllDoorBeOpened ) )
    {
        actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_30( msg );
        return Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__En__WaitAllDoorBeOpened;
    }
    else if( check_history( Debug__C__doorsClosed__WaitAllDoorBeOpened__4, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_31_to_boundary( msg );
        return Debug__C__doorsClosed__WaitAllDoorBeOpened__4__boundary;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__doorsOpen__WaitAllDoorBeClosed__2, Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ex__doorsOpen ) )
    {
        actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_9( msg );
        return Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ex__doorsOpen;
    }
    else if( check_history( Debug__C__doorsOpen__WaitAllDoorBeClosed__2, Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2 ) )
    {
        actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_10( msg );
        return Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2;
    }
    else if( check_history( Debug__C__doorsOpen__WaitAllDoorBeClosed__2, Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2 ) )
    {
        actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_11( msg );
        return Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2;
    }
    else if( check_history( Debug__C__doorsOpen__WaitAllDoorBeClosed__2, Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__En__WaitAllDoorBeClosed ) )
    {
        actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_12( msg );
        return Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__En__WaitAllDoorBeClosed;
    }
    else if( check_history( Debug__C__doorsOpen__WaitAllDoorBeClosed__2, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_13_to_boundary( msg );
        return Debug__C__doorsOpen__WaitAllDoorBeClosed__2__boundary;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____Debug__Path__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg )
{
    if( action_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8__S__Debug__GuardAllDoorClosed__WaitAllDoorBeClosed__8( msg ) )
    {
        actionchain_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8__S( msg );
        return junction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__en( msg );
    }
    else
    {
        actionchain_____AllDoorClosed__WaitAllDoorBeClosed__8( msg );
        return WaitAllDoorBeClosed;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____Debug__Path__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg )
{
    if( action_____Debug__AllDoorClosed__doorsClosed__1__S__Debug__GuardAllDoorClosed__doorsClosed__1( msg ) )
    {
        actionchain_____Debug__AllDoorClosed__doorsClosed__1__S( msg );
        return junction_____Debug__C__AllDoorClosed__doorsClosed__1__en( msg );
    }
    else
    {
        actionchain_____AllDoorClosed__doorsClosed__1( msg );
        return doorsClosed;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____Debug__Path__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg )
{
    if( action_____Debug__Choice1__WaitAllDoorBeOpened__7__S__Debug__GuardChoice1__WaitAllDoorBeOpened__7( msg ) )
    {
        actionchain_____Debug__Choice1__WaitAllDoorBeOpened__7__S( msg );
        return junction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__en( msg );
    }
    else
    {
        actionchain_____Choice1__WaitAllDoorBeOpened__7( msg );
        return WaitAllDoorBeOpened;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____Debug__Path__Choice1__doorsOpen__5( const UMLRTMessage * msg )
{
    if( action_____Debug__Choice1__doorsOpen__5__S__Debug__GuardChoice1__doorsOpen__5( msg ) )
    {
        actionchain_____Debug__Choice1__doorsOpen__5__S( msg );
        return junction_____Debug__C__Choice1__doorsOpen__5__en( msg );
    }
    else
    {
        actionchain_____Choice1__doorsOpen__5( msg );
        return doorsOpen;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____Debug__Path__Initial1__StartingUp__3( const UMLRTMessage * msg )
{
    if( action_____Debug__Initial1__StartingUp__3__S__Debug__GuardInitial1__StartingUp__3( msg ) )
    {
        actionchain_____Debug__Initial1__StartingUp__3__S( msg );
        return junction_____Debug__C__Initial1__StartingUp__3__en( msg );
    }
    else
    {
        actionchain_____Initial1__StartingUp__3( msg );
        return StartingUp;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____Debug__Path__StartingUp__doorsOpen__10( const UMLRTMessage * msg )
{
    if( action_____Debug__StartingUp__doorsOpen__10__S__Debug__GuardStartingUp__doorsOpen__10( msg ) )
    {
        actionchain_____Debug__StartingUp__doorsOpen__10__S( msg );
        return junction_____Debug__C__StartingUp__doorsOpen__10__en( msg );
    }
    else
    {
        actionchain_____StartingUp__doorsOpen__10( msg );
        return doorsOpen;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____Debug__Path__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg )
{
    if( action_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9__S__Debug__GuardWaitAllDoorBeClosed__AllDoorClosed__9( msg ) )
    {
        actionchain_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9__S( msg );
        return junction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__en( msg );
    }
    else
    {
        actionchain_____WaitAllDoorBeClosed__AllDoorClosed__9( msg );
        return choice_____AllDoorClosed( msg );
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____Debug__Path__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg )
{
    if( action_____Debug__WaitAllDoorBeOpened__Choice1__6__S__Debug__GuardWaitAllDoorBeOpened__Choice1__6( msg ) )
    {
        actionchain_____Debug__WaitAllDoorBeOpened__Choice1__6__S( msg );
        return junction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__en( msg );
    }
    else
    {
        actionchain_____WaitAllDoorBeOpened__Choice1__6( msg );
        return choice_____Choice1( msg );
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____Debug__Path__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg )
{
    if( action_____Debug__doorsClosed__WaitAllDoorBeOpened__4__S__Debug__GuarddoorsClosed__WaitAllDoorBeOpened__4( msg ) )
    {
        actionchain_____Debug__doorsClosed__WaitAllDoorBeOpened__4__S( msg );
        return junction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__en( msg );
    }
    else
    {
        actionchain_____doorsClosed__WaitAllDoorBeOpened__4( msg );
        return WaitAllDoorBeOpened;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::choice_____Debug__Path__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg )
{
    if( action_____Debug__doorsOpen__WaitAllDoorBeClosed__2__S__Debug__GuarddoorsOpen__WaitAllDoorBeClosed__2( msg ) )
    {
        actionchain_____Debug__doorsOpen__WaitAllDoorBeClosed__2__S( msg );
        return junction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__en( msg );
    }
    else
    {
        actionchain_____doorsOpen__WaitAllDoorBeClosed__2( msg );
        return WaitAllDoorBeClosed;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__En__WaitAllDoorBeClosed( msg );
            return Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_66( msg );
            return junction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_exitpoint_8( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__end__trans__AllDoorClosed__WaitAllDoorBeClosed__8( msg );
            return junction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_67( msg );
            return junction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_exitpoint_8( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( msg );
            return Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_65( msg );
            return junction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_exitpoint_8( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_68( msg );
            return junction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_exitpoint_8( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__Ac__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__En__doorsClosed( msg );
            return Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__En__AllDoorClosed__doorsClosed__1;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_6( msg );
            return junction_____Debug__C__AllDoorClosed__doorsClosed__1__new_exitpoint_1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__En__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__end__trans__AllDoorClosed__doorsClosed__1( msg );
            return junction_____Debug__C__AllDoorClosed__doorsClosed__1__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_7( msg );
            return junction_____Debug__C__AllDoorClosed__doorsClosed__1__new_exitpoint_1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__B__Ac__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__Ac__AllDoorClosed__doorsClosed__1( msg );
            return Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__Ac__AllDoorClosed__doorsClosed__1;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_5( msg );
            return junction_____Debug__C__AllDoorClosed__doorsClosed__1__new_exitpoint_1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__AllDoorClosed__doorsClosed__1__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_8( msg );
            return junction_____Debug__C__AllDoorClosed__doorsClosed__1__new_exitpoint_1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__En__WaitAllDoorBeOpened( msg );
            return Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__En__Choice1__WaitAllDoorBeOpened__7;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_58( msg );
            return junction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_exitpoint_7( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__En__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__end__trans__Choice1__WaitAllDoorBeOpened__7( msg );
            return junction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_59( msg );
            return junction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_exitpoint_7( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__Ac__Choice1__WaitAllDoorBeOpened__7( msg );
            return Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_57( msg );
            return junction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_exitpoint_7( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__Choice1__WaitAllDoorBeOpened__7__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_60( msg );
            return junction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_exitpoint_7( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__Choice1__doorsOpen__5__Debug__A__Ac__Choice1__doorsOpen__5( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Choice1__doorsOpen__5__Debug__En__doorsOpen( msg );
            return Debug__C__Choice1__doorsOpen__5__Debug__A__En__Choice1__doorsOpen__5;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_42( msg );
            return junction_____Debug__C__Choice1__doorsOpen__5__new_exitpoint_5( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__Choice1__doorsOpen__5__Debug__A__En__Choice1__doorsOpen__5( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Choice1__doorsOpen__5__Debug__end__trans__Choice1__doorsOpen__5( msg );
            return junction_____Debug__C__Choice1__doorsOpen__5__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_43( msg );
            return junction_____Debug__C__Choice1__doorsOpen__5__new_exitpoint_5( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__Choice1__doorsOpen__5__Debug__B__Ac__Choice1__doorsOpen__5( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Choice1__doorsOpen__5__Debug__Ac__Choice1__doorsOpen__5( msg );
            return Debug__C__Choice1__doorsOpen__5__Debug__A__Ac__Choice1__doorsOpen__5;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_41( msg );
            return junction_____Debug__C__Choice1__doorsOpen__5__new_exitpoint_5( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__Choice1__doorsOpen__5__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_44( msg );
            return junction_____Debug__C__Choice1__doorsOpen__5__new_exitpoint_5( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__Initial1__StartingUp__3__Debug__A__Ac__Initial1__StartingUp__3( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Initial1__StartingUp__3__Debug__En__StartingUp( msg );
            return Debug__C__Initial1__StartingUp__3__Debug__A__En__Initial1__StartingUp__3;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_24( msg );
            return junction_____Debug__C__Initial1__StartingUp__3__new_exitpoint_3( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__Initial1__StartingUp__3__Debug__A__En__Initial1__StartingUp__3( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Initial1__StartingUp__3__Debug__end__trans__Initial1__StartingUp__3( msg );
            return junction_____Debug__C__Initial1__StartingUp__3__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_25( msg );
            return junction_____Debug__C__Initial1__StartingUp__3__new_exitpoint_3( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__Initial1__StartingUp__3__Debug__B__Ac__Initial1__StartingUp__3( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Initial1__StartingUp__3__Debug__Ac__Initial1__StartingUp__3( msg );
            return Debug__C__Initial1__StartingUp__3__Debug__A__Ac__Initial1__StartingUp__3;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_23( msg );
            return junction_____Debug__C__Initial1__StartingUp__3__new_exitpoint_3( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__Initial1__StartingUp__3__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_26( msg );
            return junction_____Debug__C__Initial1__StartingUp__3__new_exitpoint_3( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__StartingUp__doorsOpen__10__Debug__A__Ac__StartingUp__doorsOpen__10( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__StartingUp__doorsOpen__10__Debug__En__doorsOpen( msg );
            return Debug__C__StartingUp__doorsOpen__10__Debug__A__En__doorsOpen;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_84( msg );
            return junction_____Debug__C__StartingUp__doorsOpen__10__new_exitpoint_10( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__StartingUp__doorsOpen__10__Debug__A__En__doorsOpen( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__StartingUp__doorsOpen__10__Debug__end__trans__StartingUp__doorsOpen__10( msg );
            return junction_____Debug__C__StartingUp__doorsOpen__10__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_85( msg );
            return junction_____Debug__C__StartingUp__doorsOpen__10__new_exitpoint_10( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__StartingUp__doorsOpen__10__Debug__B__Ac__StartingUp__doorsOpen__10( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__StartingUp__doorsOpen__10__Debug__AC__StartingUp__doorsOpen__10( msg );
            return Debug__C__StartingUp__doorsOpen__10__Debug__A__Ac__StartingUp__doorsOpen__10;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_83( msg );
            return junction_____Debug__C__StartingUp__doorsOpen__10__new_exitpoint_10( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__StartingUp__doorsOpen__10__Debug__B__Ex__StartingUp( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__StartingUp__doorsOpen__10__Debug__Ex__StartingUp( msg );
            return Debug__C__StartingUp__doorsOpen__10__Debug__B__Ac__StartingUp__doorsOpen__10;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_82( msg );
            return junction_____Debug__C__StartingUp__doorsOpen__10__new_exitpoint_10( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__StartingUp__doorsOpen__10__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_86( msg );
            return junction_____Debug__C__StartingUp__doorsOpen__10__new_exitpoint_10( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__end__trans__WaitAllDoorBeClosed__AllDoorClosed__9( msg );
            return junction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_75( msg );
            return junction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_exitpoint_9( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__AC__WaitAllDoorBeClosed__AllDoorClosed__9( msg );
            return Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_74( msg );
            return junction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_exitpoint_9( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ex__WaitAllDoorBeClosed( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__Ex__WaitAllDoorBeClosed( msg );
            return Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_73( msg );
            return junction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_exitpoint_9( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_76( msg );
            return junction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_exitpoint_9( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__end__trans__WaitAllDoorBeOpened__Choice1__6( msg );
            return junction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_51( msg );
            return junction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_exitpoint_6( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__AC__WaitAllDoorBeOpened__Choice1__6( msg );
            return Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_50( msg );
            return junction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_exitpoint_6( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ex__WaitAllDoorBeOpened( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__Ex__WaitAllDoorBeOpened( msg );
            return Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_49( msg );
            return junction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_exitpoint_6( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__WaitAllDoorBeOpened__Choice1__6__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_52( msg );
            return junction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_exitpoint_6( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__En__WaitAllDoorBeOpened( msg );
            return Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__En__WaitAllDoorBeOpened;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_34( msg );
            return junction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_exitpoint_4( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__En__WaitAllDoorBeOpened( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__end__trans__doorsClosed__WaitAllDoorBeOpened__4( msg );
            return junction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_35( msg );
            return junction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_exitpoint_4( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__AC__doorsClosed__WaitAllDoorBeOpened__4( msg );
            return Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_33( msg );
            return junction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_exitpoint_4( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ex__doorsClosed( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__Ex__doorsClosed( msg );
            return Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_32( msg );
            return junction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_exitpoint_4( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_36( msg );
            return junction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_exitpoint_4( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__En__WaitAllDoorBeClosed( msg );
            return Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__En__WaitAllDoorBeClosed;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_16( msg );
            return junction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_exitpoint_2( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__En__WaitAllDoorBeClosed( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__end__trans__doorsOpen__WaitAllDoorBeClosed__2( msg );
            return junction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_17( msg );
            return junction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_exitpoint_2( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__AC__doorsOpen__WaitAllDoorBeClosed__2( msg );
            return Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_15( msg );
            return junction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_exitpoint_2( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ex__doorsOpen( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__Ex__doorsOpen( msg );
            return Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_14( msg );
            return junction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_exitpoint_2( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_18( msg );
            return junction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_exitpoint_2( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____Debug__InitState( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__Initial1__StartingUp__3( msg );
            return choice_____Debug__Path__Initial1__StartingUp__3( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____StartingUp( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_startupTimer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____Debug__StartingUp__doorsOpen__10( msg );
            return choice_____Debug__Path__StartingUp__doorsOpen__10( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____WaitAllDoorBeClosed( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_lockPort:
        switch( msg->getSignalId() )
        {
        case Locking::signal_lockStatus:
            actionchain_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9( msg );
            return choice_____Debug__Path__WaitAllDoorBeClosed__AllDoorClosed__9( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____WaitAllDoorBeOpened( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_lockPort:
        switch( msg->getSignalId() )
        {
        case Locking::signal_lockStatus:
            actionchain_____Debug__WaitAllDoorBeOpened__Choice1__6( msg );
            return choice_____Debug__Path__WaitAllDoorBeOpened__Choice1__6( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____doorsClosed( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_lockPort:
        switch( msg->getSignalId() )
        {
        case Locking::signal_lockStatus:
            actionchain_____Debug__doorsClosed__WaitAllDoorBeOpened__4( msg );
            return choice_____Debug__Path__doorsClosed__WaitAllDoorBeOpened__4( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_CentralLock::State Capsule_CentralLock::state_____doorsOpen( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_lockPort:
        switch( msg->getSignalId() )
        {
        case Locking::signal_lockStatus:
            actionchain_____Debug__doorsOpen__WaitAllDoorBeClosed__2( msg );
            return choice_____Debug__Path__doorsOpen__WaitAllDoorBeClosed__2( msg );
        default:
            this->unexpectedMessage();
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
        Capsule_CentralLock::port_extComm,
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
        Capsule_CentralLock::port_lockPort,
        "Locking",
        "lockPort",
        "",
        4,
        true,
        true,
        false,
        false,
        false,
        false,
        true
    },
    {
        Capsule_CentralLock::port_startupTimer,
        "Timing",
        "startupTimer",
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

static void instantiate_CentralLock( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_CentralLock( &CentralLock, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass CentralLock = 
{
    "CentralLock",
    NULL,
    instantiate_CentralLock,
    0,
    NULL,
    3,
    portroles_border,
    0,
    NULL
};

