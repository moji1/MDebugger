
#include "EchoCapsule.hh"

#include "Echo.hh"
#include "ExtInterface.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include <cstddef>
class UMLRTRtsInterface;
struct UMLRTCommsPort;

#include <iostream>

Capsule_EchoCapsule::Capsule_EchoCapsule( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, Echo( borderPorts[borderport_Echo] )
, extComm( borderPorts[borderport_extComm] )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[Debug__C__DoEcho] = "Debug__C__DoEcho";
    stateNames[Debug__C__init__WaitForEcho__1] = "Debug__C__init__WaitForEcho__1";
    stateNames[Debug__C__DoEcho__Debug__A__Ac__DoEcho] = "Debug__C__DoEcho__Debug__A__Ac__DoEcho";
    stateNames[Debug__C__DoEcho__Debug__A__En__WaitForEcho] = "Debug__C__DoEcho__Debug__A__En__WaitForEcho";
    stateNames[Debug__C__DoEcho__Debug__B__Ac__DoEcho] = "Debug__C__DoEcho__Debug__B__Ac__DoEcho";
    stateNames[Debug__C__DoEcho__Debug__B__Ex__WaitForEcho] = "Debug__C__DoEcho__Debug__B__Ex__WaitForEcho";
    stateNames[Debug__C__DoEcho__boundary] = "Debug__C__DoEcho__boundary";
    stateNames[Debug__C__init__WaitForEcho__1__Debug__A__Ac__init__WaitForEcho__1] = "Debug__C__init__WaitForEcho__1__Debug__A__Ac__init__WaitForEcho__1";
    stateNames[Debug__C__init__WaitForEcho__1__Debug__A__En__init__WaitForEcho__1] = "Debug__C__init__WaitForEcho__1__Debug__A__En__init__WaitForEcho__1";
    stateNames[Debug__C__init__WaitForEcho__1__Debug__B__Ac__init__WaitForEcho__1] = "Debug__C__init__WaitForEcho__1__Debug__B__Ac__init__WaitForEcho__1";
    stateNames[Debug__C__init__WaitForEcho__1__boundary] = "Debug__C__init__WaitForEcho__1__boundary";
    stateNames[Debug__InitState] = "Debug__InitState";
    stateNames[WaitForEcho] = "WaitForEcho";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
    int i = 0;
    while( i < 2 )
        history[i++] = SPECIAL_INTERNAL_STATE_UNVISITED;
}






void Capsule_EchoCapsule::bindPort( bool isBorder, int portId, int index )
{
}

void Capsule_EchoCapsule::unbindPort( bool isBorder, int portId, int index )
{
}





void Capsule_EchoCapsule::Debug__variablesView()
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::EchoCapsule operation Debug__variablesView */
    std::string tempS="";
    if (Debug__variablesData==NULL)
    Debug__variablesData=(char *)malloc(strlen(tempS.c_str())+1);
    else if (strlen(Debug__variablesData)<strlen(tempS.c_str()))
    Debug__variablesData=(char *) realloc(Debug__variablesData,strlen(tempS.c_str())+1);
    strcpy(Debug__variablesData,tempS.c_str());
    /* UMLRTGEN-USERREGION-END */
}

bool Capsule_EchoCapsule::Debug__variablesChange( char * varName, char * varValue )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::EchoCapsule operation Debug__variablesChange */
    std::string tempVarName="";
    tempVarName.append(varName);
    return false;
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_EchoCapsule::Debug__sendEvent( debugEvents::EVENTSOURCEKIND eventSourceKind, debugEvents::EVENTTYPE eventType, const char * instanceName, int capsuleIndex, const char * signalName, char * capsuleName, char * sourceName, char * reserve1, char * reserve2, char * reserve3 )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::EchoCapsule operation Debug__sendEvent */
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

void Capsule_EchoCapsule::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case WaitForEcho:
        currentState = state_____WaitForEcho( &message );
        break;
    case Debug__InitState:
        currentState = state_____Debug__InitState( &message );
        break;
    case Debug__C__DoEcho__Debug__B__Ex__WaitForEcho:
        currentState = state_____Debug__C__DoEcho__Debug__B__Ex__WaitForEcho( &message );
        break;
    case Debug__C__DoEcho__Debug__B__Ac__DoEcho:
        currentState = state_____Debug__C__DoEcho__Debug__B__Ac__DoEcho( &message );
        break;
    case Debug__C__DoEcho__Debug__A__Ac__DoEcho:
        currentState = state_____Debug__C__DoEcho__Debug__A__Ac__DoEcho( &message );
        break;
    case Debug__C__DoEcho__Debug__A__En__WaitForEcho:
        currentState = state_____Debug__C__DoEcho__Debug__A__En__WaitForEcho( &message );
        break;
    case Debug__C__DoEcho__boundary:
        currentState = state_____Debug__C__DoEcho__boundary( &message );
        break;
    case Debug__C__init__WaitForEcho__1__Debug__B__Ac__init__WaitForEcho__1:
        currentState = state_____Debug__C__init__WaitForEcho__1__Debug__B__Ac__init__WaitForEcho__1( &message );
        break;
    case Debug__C__init__WaitForEcho__1__Debug__A__Ac__init__WaitForEcho__1:
        currentState = state_____Debug__C__init__WaitForEcho__1__Debug__A__Ac__init__WaitForEcho__1( &message );
        break;
    case Debug__C__init__WaitForEcho__1__Debug__A__En__init__WaitForEcho__1:
        currentState = state_____Debug__C__init__WaitForEcho__1__Debug__A__En__init__WaitForEcho__1( &message );
        break;
    case Debug__C__init__WaitForEcho__1__boundary:
        currentState = state_____Debug__C__init__WaitForEcho__1__boundary( &message );
        break;
    default:
        break;
    }
}

void Capsule_EchoCapsule::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Debug__InitDebug( &message );
    currentState = Debug__InitState;
}

const char * Capsule_EchoCapsule::getCurrentStateString() const
{
    return stateNames[currentState];
}





void Capsule_EchoCapsule::save_history( Capsule_EchoCapsule::State compositeState, Capsule_EchoCapsule::State subState )
{
    history[compositeState] = subState;
}

bool Capsule_EchoCapsule::check_history( Capsule_EchoCapsule::State compositeState, Capsule_EchoCapsule::State subState )
{
    return history[compositeState] == subState;
}

void Capsule_EchoCapsule::entryaction_____Debug__C__DoEcho__Debug__A__Ac__DoEcho( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__C__DoEcho::Debug__A__Ac__DoEcho entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__C__DoEcho::Region1::Debug__A__Ac__DoEcho",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("DoEcho","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("WaitForEcho","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::entryaction_____Debug__C__DoEcho__Debug__A__En__WaitForEcho( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__C__DoEcho::Debug__A__En__WaitForEcho entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__C__DoEcho::Region1::Debug__A__En__WaitForEcho",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("WaitForEcho","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::entryaction_____Debug__C__DoEcho__Debug__B__Ac__DoEcho( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__C__DoEcho::Debug__B__Ac__DoEcho entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__C__DoEcho::Region1::Debug__B__Ac__DoEcho",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("WaitForEcho","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("DoEcho","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::entryaction_____Debug__C__DoEcho__Debug__B__Ex__WaitForEcho( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__C__DoEcho::Debug__B__Ex__WaitForEcho entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__C__DoEcho::Region1::Debug__B__Ex__WaitForEcho",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("WaitForEcho","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::entryaction_____Debug__C__DoEcho__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_EchoCapsule::entryaction_____Debug__C__init__WaitForEcho__1__Debug__A__Ac__init__WaitForEcho__1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__C__init__WaitForEcho__1::Debug__A__Ac__init__WaitForEcho__1 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__C__init__WaitForEcho__1::Region1::Debug__A__Ac__init__WaitForEcho__1",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("init__WaitForEcho__1","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("WaitForEcho","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::entryaction_____Debug__C__init__WaitForEcho__1__Debug__A__En__init__WaitForEcho__1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__C__init__WaitForEcho__1::Debug__A__En__init__WaitForEcho__1 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__C__init__WaitForEcho__1::Region1::Debug__A__En__init__WaitForEcho__1",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("WaitForEcho","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::entryaction_____Debug__C__init__WaitForEcho__1__Debug__B__Ac__init__WaitForEcho__1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__C__init__WaitForEcho__1::Debug__B__Ac__init__WaitForEcho__1 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__C__init__WaitForEcho__1::Region1::Debug__B__Ac__init__WaitForEcho__1",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("init__WaitForEcho__1","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::entryaction_____Debug__C__init__WaitForEcho__1__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_EchoCapsule::entryaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__InitState entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::entryaction_____WaitForEcho( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::WaitForEcho entry  */
    if( not Debug__SRO.checkDebug("WaitForEcho",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::WaitForEcho",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::exitaction_____Debug__C__DoEcho__Debug__A__Ac__DoEcho( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__C__DoEcho::Debug__A__Ac__DoEcho exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__C__DoEcho::Region1::Debug__A__Ac__DoEcho",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::exitaction_____Debug__C__DoEcho__Debug__A__En__WaitForEcho( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__C__DoEcho::Debug__A__En__WaitForEcho exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__C__DoEcho::Region1::Debug__A__En__WaitForEcho",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::exitaction_____Debug__C__DoEcho__Debug__B__Ac__DoEcho( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__C__DoEcho::Debug__B__Ac__DoEcho exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__C__DoEcho::Region1::Debug__B__Ac__DoEcho",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::exitaction_____Debug__C__DoEcho__Debug__B__Ex__WaitForEcho( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__C__DoEcho::Debug__B__Ex__WaitForEcho exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__C__DoEcho::Region1::Debug__B__Ex__WaitForEcho",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::exitaction_____Debug__C__DoEcho__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_EchoCapsule::exitaction_____Debug__C__init__WaitForEcho__1__Debug__A__Ac__init__WaitForEcho__1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__C__init__WaitForEcho__1::Debug__A__Ac__init__WaitForEcho__1 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__C__init__WaitForEcho__1::Region1::Debug__A__Ac__init__WaitForEcho__1",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::exitaction_____Debug__C__init__WaitForEcho__1__Debug__A__En__init__WaitForEcho__1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__C__init__WaitForEcho__1::Debug__A__En__init__WaitForEcho__1 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__C__init__WaitForEcho__1::Region1::Debug__A__En__init__WaitForEcho__1",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::exitaction_____Debug__C__init__WaitForEcho__1__Debug__B__Ac__init__WaitForEcho__1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__C__init__WaitForEcho__1::Debug__B__Ac__init__WaitForEcho__1 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__C__init__WaitForEcho__1::Region1::Debug__B__Ac__init__WaitForEcho__1",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::exitaction_____Debug__C__init__WaitForEcho__1__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_EchoCapsule::exitaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__InitState exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::exitaction_____WaitForEcho( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::WaitForEcho exit  */
    if( not Debug__SRO.checkDebug("WaitForEcho",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::WaitForEcho",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::transitionaction_____Debug__C__DoEcho__Debug__AC__DoEcho( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__C__DoEcho transition Debug__C__DoEcho::Debug__B__Ac__DoEcho,Debug__C__DoEcho::Debug__A__Ac__DoEcho,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__C__DoEcho::Region1::Debug__AC__DoEcho",(char *)"Debug__B__Ac__DoEcho",(char *)"Debug__A__Ac__DoEcho",(char *)"");
    std::cout<<"EchoCapsule: The Echo message was recieved\n";
    int tempid=msg->sapIndex0_;
    Echo.Echo().sendAt(tempid);
    std::cout<<"EchoCapsule: The Echo message was replied\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::transitionaction_____Debug__C__DoEcho__Debug__En__WaitForEcho( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__C__DoEcho transition Debug__C__DoEcho::Debug__A__Ac__DoEcho,Debug__C__DoEcho::Debug__A__En__WaitForEcho,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__C__DoEcho::Region1::Debug__En__WaitForEcho",(char *)"Debug__A__Ac__DoEcho",(char *)"Debug__A__En__WaitForEcho",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::transitionaction_____Debug__C__DoEcho__Debug__Ex__WaitForEcho( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__C__DoEcho transition Debug__C__DoEcho::Debug__B__Ex__WaitForEcho,Debug__C__DoEcho::Debug__B__Ac__DoEcho,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__C__DoEcho::Region1::Debug__Ex__WaitForEcho",(char *)"Debug__B__Ex__WaitForEcho",(char *)"Debug__B__Ac__DoEcho",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::transitionaction_____Debug__C__DoEcho__Debug__end__trans__DoEcho( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__C__DoEcho transition Debug__C__DoEcho::Debug__A__En__WaitForEcho,Debug__C__DoEcho::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__C__DoEcho::Region1::Debug__end__trans__DoEcho",(char *)"Debug__A__En__WaitForEcho",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::transitionaction_____Debug__C__DoEcho__Debug__init__trans__DoEcho( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__C__DoEcho transition Debug__C__DoEcho::en,Debug__C__DoEcho::Debug__B__Ex__WaitForEcho */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__C__DoEcho::Region1::Debug__init__trans__DoEcho",(char *)"en",(char *)"Debug__B__Ex__WaitForEcho",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::transitionaction_____Debug__C__init__WaitForEcho__1__Debug__Ac__init__WaitForEcho__1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__C__init__WaitForEcho__1 transition Debug__C__init__WaitForEcho__1::Debug__B__Ac__init__WaitForEcho__1,Debug__C__init__WaitForEcho__1::Debug__A__Ac__init__WaitForEcho__1,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__C__init__WaitForEcho__1::Region1::Debug__Ac__init__WaitForEcho__1",(char *)"Debug__B__Ac__init__WaitForEcho__1",(char *)"Debug__A__Ac__init__WaitForEcho__1",(char *)"");
    std::cout<<"EchoCapsule: Intializing\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::transitionaction_____Debug__C__init__WaitForEcho__1__Debug__En__WaitForEcho( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__C__init__WaitForEcho__1 transition Debug__C__init__WaitForEcho__1::Debug__A__Ac__init__WaitForEcho__1,Debug__C__init__WaitForEcho__1::Debug__A__En__init__WaitForEcho__1,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__C__init__WaitForEcho__1::Region1::Debug__En__WaitForEcho",(char *)"Debug__A__Ac__init__WaitForEcho__1",(char *)"Debug__A__En__init__WaitForEcho__1",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::transitionaction_____Debug__C__init__WaitForEcho__1__Debug__end__trans__init__WaitForEcho__1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__C__init__WaitForEcho__1 transition Debug__C__init__WaitForEcho__1::Debug__A__En__init__WaitForEcho__1,Debug__C__init__WaitForEcho__1::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__C__init__WaitForEcho__1::Region1::Debug__end__trans__init__WaitForEcho__1",(char *)"Debug__A__En__init__WaitForEcho__1",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::transitionaction_____Debug__C__init__WaitForEcho__1__Debug__init__trans__init__WaitForEcho__1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule::Debug__C__init__WaitForEcho__1 transition Debug__C__init__WaitForEcho__1::en,Debug__C__init__WaitForEcho__1::Debug__B__Ac__init__WaitForEcho__1 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__C__init__WaitForEcho__1::Region1::Debug__init__trans__init__WaitForEcho__1",(char *)"en",(char *)"Debug__B__Ac__init__WaitForEcho__1",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::transitionaction_____Debug__DoEcho( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule transition WaitForEcho,Debug__Path__DoEcho,Echo:Echo */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__DoEcho",(char *)"WaitForEcho",(char *)"Debug__Path__DoEcho",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::transitionaction_____Debug__DoEcho__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule transition Debug__C__DoEcho::ex,WaitForEcho */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__DoEcho__E",(char *)"ex",(char *)"WaitForEcho",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::transitionaction_____Debug__DoEcho__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule transition Debug__Path__DoEcho,Debug__C__DoEcho::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__DoEcho__S",(char *)"Debug__Path__DoEcho",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::transitionaction_____Debug__DoEcho__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule transition Debug__C__DoEcho::new_exitpoint_1,Debug__C__DoEcho */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__DoEcho__dbg",(char *)"Debug__C__DoEcho",(char *)"Debug__C__DoEcho",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::transitionaction_____Debug__InitDebug( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule transition init,Debug__InitState */
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

void Capsule_EchoCapsule::transitionaction_____Debug__init__WaitForEcho__1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule transition Debug__InitState,Debug__Path__init__WaitForEcho__1,null:extComm */
    if (this->Debug__SRO.getExecMode()==Stepping){
    Debug__SRO.addTransitionsFromState("init","","WaitForEcho","","");
    Debug__SRO.addTransitionsFromState("WaitForEcho","DoEcho","WaitForEcho","Echo","Echo");
    std::cout<<this->getName()<<": Connection with debugger is in progress\n";
    char  tempS[256];
    sprintf(tempS,"%s%d",this->getName(),(int)this->getIndex());
    extComm.registerToControl(tempS).send();
    Debug__sendEvent(debugEvents::DEBUG,debugEvents::REGISTER,this->getName(),this->getIndex(),msg->getSignalName(),(char *) "",(char *) "",(char *) "",(char *)"",(char *) "");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::transitionaction_____Debug__init__WaitForEcho__1__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule transition Debug__C__init__WaitForEcho__1::ex,WaitForEcho */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__init__WaitForEcho__1__E",(char *)"ex",(char *)"WaitForEcho",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::transitionaction_____Debug__init__WaitForEcho__1__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule transition Debug__Path__init__WaitForEcho__1,Debug__C__init__WaitForEcho__1::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__init__WaitForEcho__1__S",(char *)"Debug__Path__init__WaitForEcho__1",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::transitionaction_____Debug__init__WaitForEcho__1__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule transition Debug__C__init__WaitForEcho__1::new_exitpoint_2,Debug__C__init__WaitForEcho__1 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::Debug__init__WaitForEcho__1__dbg",(char *)"Debug__C__init__WaitForEcho__1",(char *)"Debug__C__init__WaitForEcho__1",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::transitionaction_____DoEcho( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule transition Debug__Path__DoEcho,WaitForEcho */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::DoEcho",(char *)"Debug__Path__DoEcho",(char *)"WaitForEcho",(char *)"");
    std::cout<<"EchoCapsule: The Echo message was recieved\n";
    int tempid=msg->sapIndex0_;
    Echo.Echo().sendAt(tempid);
    std::cout<<"EchoCapsule: The Echo message was replied\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::transitionaction_____init__WaitForEcho__1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule transition Debug__Path__init__WaitForEcho__1,WaitForEcho */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"Replication::Utility::EchoCapsule::StateMachine1::Region1::init__WaitForEcho__1",(char *)"Debug__Path__init__WaitForEcho__1",(char *)"WaitForEcho",(char *)"");
    std::cout<<"EchoCapsule: Intializing\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_EchoCapsule::action_____Debug__DoEcho__S__Debug__GuardDoEcho( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule guard Debug__Path__DoEcho,Debug__C__DoEcho::en */
    return Debug__SRO.checkDebug("WaitForEcho",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_EchoCapsule::action_____Debug__init__WaitForEcho__1__S__Debug__Guardinit__WaitForEcho__1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-Replication/Replication.uml Replication::Utility::EchoCapsule guard Debug__Path__init__WaitForEcho__1,Debug__C__init__WaitForEcho__1::en */
    return Debug__SRO.checkDebug("init","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::actionchain_____Debug__C__DoEcho__Debug__AC__DoEcho( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__DoEcho__Debug__B__Ac__DoEcho( msg );
    transitionaction_____Debug__C__DoEcho__Debug__AC__DoEcho( msg );
    entryaction_____Debug__C__DoEcho__Debug__A__Ac__DoEcho( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__DoEcho__Debug__En__WaitForEcho( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__DoEcho__Debug__A__Ac__DoEcho( msg );
    transitionaction_____Debug__C__DoEcho__Debug__En__WaitForEcho( msg );
    entryaction_____Debug__C__DoEcho__Debug__A__En__WaitForEcho( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__DoEcho__Debug__Ex__WaitForEcho( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__DoEcho__Debug__B__Ex__WaitForEcho( msg );
    transitionaction_____Debug__C__DoEcho__Debug__Ex__WaitForEcho( msg );
    entryaction_____Debug__C__DoEcho__Debug__B__Ac__DoEcho( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__DoEcho__Debug__end__trans__DoEcho( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__DoEcho__Debug__A__En__WaitForEcho( msg );
    transitionaction_____Debug__C__DoEcho__Debug__end__trans__DoEcho( msg );
    save_history( Debug__C__DoEcho, Debug__C__DoEcho__Debug__A__En__WaitForEcho );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__DoEcho__Debug__init__trans__DoEcho( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__DoEcho__Debug__init__trans__DoEcho( msg );
    entryaction_____Debug__C__DoEcho__Debug__B__Ex__WaitForEcho( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__DoEcho__new_transition_1( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__DoEcho__Debug__B__Ex__WaitForEcho( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__DoEcho__new_transition_10( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__DoEcho__boundary( msg );
    save_history( Debug__C__DoEcho, Debug__C__DoEcho__boundary );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__DoEcho__new_transition_2( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__DoEcho__Debug__B__Ac__DoEcho( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__DoEcho__new_transition_3( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__DoEcho__Debug__A__Ac__DoEcho( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__DoEcho__new_transition_4( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__DoEcho__Debug__A__En__WaitForEcho( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__DoEcho__new_transition_5_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__DoEcho__boundary( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__DoEcho__new_transition_6( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__DoEcho__Debug__B__Ex__WaitForEcho( msg );
    save_history( Debug__C__DoEcho, Debug__C__DoEcho__Debug__B__Ex__WaitForEcho );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__DoEcho__new_transition_7( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__DoEcho__Debug__B__Ac__DoEcho( msg );
    save_history( Debug__C__DoEcho, Debug__C__DoEcho__Debug__B__Ac__DoEcho );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__DoEcho__new_transition_8( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__DoEcho__Debug__A__Ac__DoEcho( msg );
    save_history( Debug__C__DoEcho, Debug__C__DoEcho__Debug__A__Ac__DoEcho );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__DoEcho__new_transition_9( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__DoEcho__Debug__A__En__WaitForEcho( msg );
    save_history( Debug__C__DoEcho, Debug__C__DoEcho__Debug__A__En__WaitForEcho );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__init__WaitForEcho__1__Debug__Ac__init__WaitForEcho__1( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__WaitForEcho__1__Debug__B__Ac__init__WaitForEcho__1( msg );
    transitionaction_____Debug__C__init__WaitForEcho__1__Debug__Ac__init__WaitForEcho__1( msg );
    entryaction_____Debug__C__init__WaitForEcho__1__Debug__A__Ac__init__WaitForEcho__1( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__init__WaitForEcho__1__Debug__En__WaitForEcho( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__WaitForEcho__1__Debug__A__Ac__init__WaitForEcho__1( msg );
    transitionaction_____Debug__C__init__WaitForEcho__1__Debug__En__WaitForEcho( msg );
    entryaction_____Debug__C__init__WaitForEcho__1__Debug__A__En__init__WaitForEcho__1( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__init__WaitForEcho__1__Debug__end__trans__init__WaitForEcho__1( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__WaitForEcho__1__Debug__A__En__init__WaitForEcho__1( msg );
    transitionaction_____Debug__C__init__WaitForEcho__1__Debug__end__trans__init__WaitForEcho__1( msg );
    save_history( Debug__C__init__WaitForEcho__1, Debug__C__init__WaitForEcho__1__Debug__A__En__init__WaitForEcho__1 );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__init__WaitForEcho__1__Debug__init__trans__init__WaitForEcho__1( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__init__WaitForEcho__1__Debug__init__trans__init__WaitForEcho__1( msg );
    entryaction_____Debug__C__init__WaitForEcho__1__Debug__B__Ac__init__WaitForEcho__1( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__init__WaitForEcho__1__new_transition_11( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__WaitForEcho__1__Debug__B__Ac__init__WaitForEcho__1( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__init__WaitForEcho__1__new_transition_12( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__WaitForEcho__1__Debug__A__Ac__init__WaitForEcho__1( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__init__WaitForEcho__1__new_transition_13( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__WaitForEcho__1__Debug__A__En__init__WaitForEcho__1( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__init__WaitForEcho__1__new_transition_14_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__WaitForEcho__1__boundary( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__init__WaitForEcho__1__new_transition_15( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__WaitForEcho__1__Debug__B__Ac__init__WaitForEcho__1( msg );
    save_history( Debug__C__init__WaitForEcho__1, Debug__C__init__WaitForEcho__1__Debug__B__Ac__init__WaitForEcho__1 );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__init__WaitForEcho__1__new_transition_16( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__WaitForEcho__1__Debug__A__Ac__init__WaitForEcho__1( msg );
    save_history( Debug__C__init__WaitForEcho__1, Debug__C__init__WaitForEcho__1__Debug__A__Ac__init__WaitForEcho__1 );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__init__WaitForEcho__1__new_transition_17( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__WaitForEcho__1__Debug__A__En__init__WaitForEcho__1( msg );
    save_history( Debug__C__init__WaitForEcho__1, Debug__C__init__WaitForEcho__1__Debug__A__En__init__WaitForEcho__1 );
}

void Capsule_EchoCapsule::actionchain_____Debug__C__init__WaitForEcho__1__new_transition_18( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__WaitForEcho__1__boundary( msg );
    save_history( Debug__C__init__WaitForEcho__1, Debug__C__init__WaitForEcho__1__boundary );
}

void Capsule_EchoCapsule::actionchain_____Debug__DoEcho( const UMLRTMessage * msg )
{
    exitaction_____WaitForEcho( msg );
    transitionaction_____Debug__DoEcho( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__DoEcho__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__DoEcho__boundary( msg );
    transitionaction_____Debug__DoEcho__E( msg );
    entryaction_____WaitForEcho( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__DoEcho__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__DoEcho__S( msg );
    entryaction_____Debug__C__DoEcho__boundary( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__DoEcho__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__DoEcho__boundary( msg );
    transitionaction_____Debug__DoEcho__dbg( msg );
    entryaction_____Debug__C__DoEcho__boundary( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__InitDebug( const UMLRTMessage * msg )
{
    transitionaction_____Debug__InitDebug( msg );
    entryaction_____Debug__InitState( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__init__WaitForEcho__1( const UMLRTMessage * msg )
{
    exitaction_____Debug__InitState( msg );
    transitionaction_____Debug__init__WaitForEcho__1( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__init__WaitForEcho__1__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__WaitForEcho__1__boundary( msg );
    transitionaction_____Debug__init__WaitForEcho__1__E( msg );
    entryaction_____WaitForEcho( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__init__WaitForEcho__1__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__init__WaitForEcho__1__S( msg );
    entryaction_____Debug__C__init__WaitForEcho__1__boundary( msg );
}

void Capsule_EchoCapsule::actionchain_____Debug__init__WaitForEcho__1__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__WaitForEcho__1__boundary( msg );
    transitionaction_____Debug__init__WaitForEcho__1__dbg( msg );
    entryaction_____Debug__C__init__WaitForEcho__1__boundary( msg );
}

void Capsule_EchoCapsule::actionchain_____DoEcho( const UMLRTMessage * msg )
{
    transitionaction_____DoEcho( msg );
    entryaction_____WaitForEcho( msg );
}

void Capsule_EchoCapsule::actionchain_____init__WaitForEcho__1( const UMLRTMessage * msg )
{
    transitionaction_____init__WaitForEcho__1( msg );
    entryaction_____WaitForEcho( msg );
}

Capsule_EchoCapsule::State Capsule_EchoCapsule::junction_____Debug__C__DoEcho__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__DoEcho__Debug__init__trans__DoEcho( msg );
    return Debug__C__DoEcho__Debug__B__Ex__WaitForEcho;
}

Capsule_EchoCapsule::State Capsule_EchoCapsule::junction_____Debug__C__DoEcho__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__DoEcho__E( msg );
    return WaitForEcho;
}

Capsule_EchoCapsule::State Capsule_EchoCapsule::junction_____Debug__C__DoEcho__new_exitpoint_1( const UMLRTMessage * msg )
{
    actionchain_____Debug__DoEcho__dbg( msg );
    return choice_____Debug__C__DoEcho__deephistory( msg );
}

Capsule_EchoCapsule::State Capsule_EchoCapsule::junction_____Debug__C__init__WaitForEcho__1__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__init__WaitForEcho__1__Debug__init__trans__init__WaitForEcho__1( msg );
    return Debug__C__init__WaitForEcho__1__Debug__B__Ac__init__WaitForEcho__1;
}

Capsule_EchoCapsule::State Capsule_EchoCapsule::junction_____Debug__C__init__WaitForEcho__1__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__init__WaitForEcho__1__E( msg );
    return WaitForEcho;
}

Capsule_EchoCapsule::State Capsule_EchoCapsule::junction_____Debug__C__init__WaitForEcho__1__new_exitpoint_2( const UMLRTMessage * msg )
{
    actionchain_____Debug__init__WaitForEcho__1__dbg( msg );
    return choice_____Debug__C__init__WaitForEcho__1__deephistory( msg );
}

Capsule_EchoCapsule::State Capsule_EchoCapsule::choice_____Debug__C__DoEcho__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__DoEcho, Debug__C__DoEcho__Debug__B__Ex__WaitForEcho ) )
    {
        actionchain_____Debug__C__DoEcho__new_transition_1( msg );
        return Debug__C__DoEcho__Debug__B__Ex__WaitForEcho;
    }
    else if( check_history( Debug__C__DoEcho, Debug__C__DoEcho__Debug__B__Ac__DoEcho ) )
    {
        actionchain_____Debug__C__DoEcho__new_transition_2( msg );
        return Debug__C__DoEcho__Debug__B__Ac__DoEcho;
    }
    else if( check_history( Debug__C__DoEcho, Debug__C__DoEcho__Debug__A__Ac__DoEcho ) )
    {
        actionchain_____Debug__C__DoEcho__new_transition_3( msg );
        return Debug__C__DoEcho__Debug__A__Ac__DoEcho;
    }
    else if( check_history( Debug__C__DoEcho, Debug__C__DoEcho__Debug__A__En__WaitForEcho ) )
    {
        actionchain_____Debug__C__DoEcho__new_transition_4( msg );
        return Debug__C__DoEcho__Debug__A__En__WaitForEcho;
    }
    else if( check_history( Debug__C__DoEcho, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__DoEcho__new_transition_5_to_boundary( msg );
        return Debug__C__DoEcho__boundary;
    }
    return currentState;
}

Capsule_EchoCapsule::State Capsule_EchoCapsule::choice_____Debug__C__init__WaitForEcho__1__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__init__WaitForEcho__1, Debug__C__init__WaitForEcho__1__Debug__B__Ac__init__WaitForEcho__1 ) )
    {
        actionchain_____Debug__C__init__WaitForEcho__1__new_transition_11( msg );
        return Debug__C__init__WaitForEcho__1__Debug__B__Ac__init__WaitForEcho__1;
    }
    else if( check_history( Debug__C__init__WaitForEcho__1, Debug__C__init__WaitForEcho__1__Debug__A__Ac__init__WaitForEcho__1 ) )
    {
        actionchain_____Debug__C__init__WaitForEcho__1__new_transition_12( msg );
        return Debug__C__init__WaitForEcho__1__Debug__A__Ac__init__WaitForEcho__1;
    }
    else if( check_history( Debug__C__init__WaitForEcho__1, Debug__C__init__WaitForEcho__1__Debug__A__En__init__WaitForEcho__1 ) )
    {
        actionchain_____Debug__C__init__WaitForEcho__1__new_transition_13( msg );
        return Debug__C__init__WaitForEcho__1__Debug__A__En__init__WaitForEcho__1;
    }
    else if( check_history( Debug__C__init__WaitForEcho__1, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__init__WaitForEcho__1__new_transition_14_to_boundary( msg );
        return Debug__C__init__WaitForEcho__1__boundary;
    }
    return currentState;
}

Capsule_EchoCapsule::State Capsule_EchoCapsule::choice_____Debug__Path__DoEcho( const UMLRTMessage * msg )
{
    if( action_____Debug__DoEcho__S__Debug__GuardDoEcho( msg ) )
    {
        actionchain_____Debug__DoEcho__S( msg );
        return junction_____Debug__C__DoEcho__en( msg );
    }
    else
    {
        actionchain_____DoEcho( msg );
        return WaitForEcho;
    }
    return currentState;
}

Capsule_EchoCapsule::State Capsule_EchoCapsule::choice_____Debug__Path__init__WaitForEcho__1( const UMLRTMessage * msg )
{
    if( action_____Debug__init__WaitForEcho__1__S__Debug__Guardinit__WaitForEcho__1( msg ) )
    {
        actionchain_____Debug__init__WaitForEcho__1__S( msg );
        return junction_____Debug__C__init__WaitForEcho__1__en( msg );
    }
    else
    {
        actionchain_____init__WaitForEcho__1( msg );
        return WaitForEcho;
    }
    return currentState;
}

Capsule_EchoCapsule::State Capsule_EchoCapsule::state_____Debug__C__DoEcho__Debug__A__Ac__DoEcho( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__DoEcho__Debug__En__WaitForEcho( msg );
            return Debug__C__DoEcho__Debug__A__En__WaitForEcho;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__DoEcho__new_transition_8( msg );
            return junction_____Debug__C__DoEcho__new_exitpoint_1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_EchoCapsule::State Capsule_EchoCapsule::state_____Debug__C__DoEcho__Debug__A__En__WaitForEcho( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__DoEcho__Debug__end__trans__DoEcho( msg );
            return junction_____Debug__C__DoEcho__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__DoEcho__new_transition_9( msg );
            return junction_____Debug__C__DoEcho__new_exitpoint_1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_EchoCapsule::State Capsule_EchoCapsule::state_____Debug__C__DoEcho__Debug__B__Ac__DoEcho( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__DoEcho__Debug__AC__DoEcho( msg );
            return Debug__C__DoEcho__Debug__A__Ac__DoEcho;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__DoEcho__new_transition_7( msg );
            return junction_____Debug__C__DoEcho__new_exitpoint_1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_EchoCapsule::State Capsule_EchoCapsule::state_____Debug__C__DoEcho__Debug__B__Ex__WaitForEcho( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__DoEcho__Debug__Ex__WaitForEcho( msg );
            return Debug__C__DoEcho__Debug__B__Ac__DoEcho;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__DoEcho__new_transition_6( msg );
            return junction_____Debug__C__DoEcho__new_exitpoint_1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_EchoCapsule::State Capsule_EchoCapsule::state_____Debug__C__DoEcho__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__DoEcho__new_transition_10( msg );
            return junction_____Debug__C__DoEcho__new_exitpoint_1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_EchoCapsule::State Capsule_EchoCapsule::state_____Debug__C__init__WaitForEcho__1__Debug__A__Ac__init__WaitForEcho__1( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__init__WaitForEcho__1__Debug__En__WaitForEcho( msg );
            return Debug__C__init__WaitForEcho__1__Debug__A__En__init__WaitForEcho__1;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__init__WaitForEcho__1__new_transition_16( msg );
            return junction_____Debug__C__init__WaitForEcho__1__new_exitpoint_2( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_EchoCapsule::State Capsule_EchoCapsule::state_____Debug__C__init__WaitForEcho__1__Debug__A__En__init__WaitForEcho__1( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__init__WaitForEcho__1__Debug__end__trans__init__WaitForEcho__1( msg );
            return junction_____Debug__C__init__WaitForEcho__1__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__init__WaitForEcho__1__new_transition_17( msg );
            return junction_____Debug__C__init__WaitForEcho__1__new_exitpoint_2( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_EchoCapsule::State Capsule_EchoCapsule::state_____Debug__C__init__WaitForEcho__1__Debug__B__Ac__init__WaitForEcho__1( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__init__WaitForEcho__1__Debug__Ac__init__WaitForEcho__1( msg );
            return Debug__C__init__WaitForEcho__1__Debug__A__Ac__init__WaitForEcho__1;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__init__WaitForEcho__1__new_transition_15( msg );
            return junction_____Debug__C__init__WaitForEcho__1__new_exitpoint_2( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_EchoCapsule::State Capsule_EchoCapsule::state_____Debug__C__init__WaitForEcho__1__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__init__WaitForEcho__1__new_transition_18( msg );
            return junction_____Debug__C__init__WaitForEcho__1__new_exitpoint_2( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_EchoCapsule::State Capsule_EchoCapsule::state_____Debug__InitState( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__init__WaitForEcho__1( msg );
            return choice_____Debug__Path__init__WaitForEcho__1( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_EchoCapsule::State Capsule_EchoCapsule::state_____WaitForEcho( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_Echo:
        switch( msg->getSignalId() )
        {
        case Echo::signal_Echo:
            actionchain_____Debug__DoEcho( msg );
            return choice_____Debug__Path__DoEcho( msg );
        default:
            this->unexpectedMessage();
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
        Capsule_EchoCapsule::port_Echo,
        "Echo",
        "Echo",
        "",
        8,
        true,
        false,
        false,
        false,
        false,
        true,
        false
    },
    {
        Capsule_EchoCapsule::port_extComm,
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

static void instantiate_EchoCapsule( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_EchoCapsule( &EchoCapsule, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass EchoCapsule = 
{
    "EchoCapsule",
    NULL,
    instantiate_EchoCapsule,
    0,
    NULL,
    2,
    portroles_border,
    0,
    NULL
};

