
#include "Lock.hh"

#include "ExtInterface.hh"
#include "Locking.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_Lock::Capsule_Lock( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, extComm( borderPorts[borderport_extComm] )
, lockPort( borderPorts[borderport_lockPort] )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[Debug__C__init] = "Debug__C__init";
    stateNames[Debug__C__lock] = "Debug__C__lock";
    stateNames[Debug__C__twiceLock] = "Debug__C__twiceLock";
    stateNames[Debug__C__twiceUnlock] = "Debug__C__twiceUnlock";
    stateNames[Debug__C__unlock] = "Debug__C__unlock";
    stateNames[Debug__C__init__Debug__A__Ac__init] = "Debug__C__init__Debug__A__Ac__init";
    stateNames[Debug__C__init__Debug__A__En__init] = "Debug__C__init__Debug__A__En__init";
    stateNames[Debug__C__init__Debug__B__Ac__init] = "Debug__C__init__Debug__B__Ac__init";
    stateNames[Debug__C__init__boundary] = "Debug__C__init__boundary";
    stateNames[Debug__C__lock__Debug__A__Ac__lock] = "Debug__C__lock__Debug__A__Ac__lock";
    stateNames[Debug__C__lock__Debug__A__En__locked] = "Debug__C__lock__Debug__A__En__locked";
    stateNames[Debug__C__lock__Debug__B__Ac__lock] = "Debug__C__lock__Debug__B__Ac__lock";
    stateNames[Debug__C__lock__Debug__B__Ex__unlocked] = "Debug__C__lock__Debug__B__Ex__unlocked";
    stateNames[Debug__C__lock__boundary] = "Debug__C__lock__boundary";
    stateNames[Debug__C__twiceLock__Debug__A__Ac__twiceLock] = "Debug__C__twiceLock__Debug__A__Ac__twiceLock";
    stateNames[Debug__C__twiceLock__Debug__A__En__locked] = "Debug__C__twiceLock__Debug__A__En__locked";
    stateNames[Debug__C__twiceLock__Debug__B__Ac__twiceLock] = "Debug__C__twiceLock__Debug__B__Ac__twiceLock";
    stateNames[Debug__C__twiceLock__Debug__B__Ex__locked] = "Debug__C__twiceLock__Debug__B__Ex__locked";
    stateNames[Debug__C__twiceLock__boundary] = "Debug__C__twiceLock__boundary";
    stateNames[Debug__C__twiceUnlock__Debug__A__Ac__twiceUnlock] = "Debug__C__twiceUnlock__Debug__A__Ac__twiceUnlock";
    stateNames[Debug__C__twiceUnlock__Debug__A__En__unlocked] = "Debug__C__twiceUnlock__Debug__A__En__unlocked";
    stateNames[Debug__C__twiceUnlock__Debug__B__Ac__twiceUnlock] = "Debug__C__twiceUnlock__Debug__B__Ac__twiceUnlock";
    stateNames[Debug__C__twiceUnlock__Debug__B__Ex__unlocked] = "Debug__C__twiceUnlock__Debug__B__Ex__unlocked";
    stateNames[Debug__C__twiceUnlock__boundary] = "Debug__C__twiceUnlock__boundary";
    stateNames[Debug__C__unlock__Debug__A__Ac__unlock] = "Debug__C__unlock__Debug__A__Ac__unlock";
    stateNames[Debug__C__unlock__Debug__A__En__unlocked] = "Debug__C__unlock__Debug__A__En__unlocked";
    stateNames[Debug__C__unlock__Debug__B__Ac__unlock] = "Debug__C__unlock__Debug__B__Ac__unlock";
    stateNames[Debug__C__unlock__Debug__B__Ex__locked] = "Debug__C__unlock__Debug__B__Ex__locked";
    stateNames[Debug__C__unlock__boundary] = "Debug__C__unlock__boundary";
    stateNames[Debug__InitState] = "Debug__InitState";
    stateNames[locked] = "locked";
    stateNames[unlocked] = "unlocked";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
    int i = 0;
    while( i < 5 )
        history[i++] = SPECIAL_INTERNAL_STATE_UNVISITED;
}






void Capsule_Lock::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_lockPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_lockPort, index, true );
            break;
        }
}

void Capsule_Lock::unbindPort( bool isBorder, int portId, int index )
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





void Capsule_Lock::Debug__variablesView()
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock operation Debug__variablesView */
    std::string tempS="";
    if (Debug__variablesData==NULL)
    Debug__variablesData=(char *)malloc(strlen(tempS.c_str())+1);
    else if (strlen(Debug__variablesData)<strlen(tempS.c_str()))
    Debug__variablesData=(char *) realloc(Debug__variablesData,strlen(tempS.c_str())+1);
    strcpy(Debug__variablesData,tempS.c_str());
    /* UMLRTGEN-USERREGION-END */
}

bool Capsule_Lock::Debug__variablesChange( char * varName, char * varValue )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock operation Debug__variablesChange */
    std::string tempVarName="";
    tempVarName.append(varName);
    return false;
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_Lock::Debug__sendEvent( debugEvents::EVENTSOURCEKIND eventSourceKind, debugEvents::EVENTTYPE eventType, const char * instanceName, int capsuleIndex, const char * signalName, char * capsuleName, char * sourceName, char * reserve1, char * reserve2, char * reserve3 )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock operation Debug__sendEvent */
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

void Capsule_Lock::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case unlocked:
        currentState = state_____unlocked( &message );
        break;
    case locked:
        currentState = state_____locked( &message );
        break;
    case Debug__InitState:
        currentState = state_____Debug__InitState( &message );
        break;
    case Debug__C__lock__Debug__B__Ex__unlocked:
        currentState = state_____Debug__C__lock__Debug__B__Ex__unlocked( &message );
        break;
    case Debug__C__lock__Debug__B__Ac__lock:
        currentState = state_____Debug__C__lock__Debug__B__Ac__lock( &message );
        break;
    case Debug__C__lock__Debug__A__Ac__lock:
        currentState = state_____Debug__C__lock__Debug__A__Ac__lock( &message );
        break;
    case Debug__C__lock__Debug__A__En__locked:
        currentState = state_____Debug__C__lock__Debug__A__En__locked( &message );
        break;
    case Debug__C__lock__boundary:
        currentState = state_____Debug__C__lock__boundary( &message );
        break;
    case Debug__C__unlock__Debug__B__Ex__locked:
        currentState = state_____Debug__C__unlock__Debug__B__Ex__locked( &message );
        break;
    case Debug__C__unlock__Debug__B__Ac__unlock:
        currentState = state_____Debug__C__unlock__Debug__B__Ac__unlock( &message );
        break;
    case Debug__C__unlock__Debug__A__Ac__unlock:
        currentState = state_____Debug__C__unlock__Debug__A__Ac__unlock( &message );
        break;
    case Debug__C__unlock__Debug__A__En__unlocked:
        currentState = state_____Debug__C__unlock__Debug__A__En__unlocked( &message );
        break;
    case Debug__C__unlock__boundary:
        currentState = state_____Debug__C__unlock__boundary( &message );
        break;
    case Debug__C__twiceLock__Debug__B__Ex__locked:
        currentState = state_____Debug__C__twiceLock__Debug__B__Ex__locked( &message );
        break;
    case Debug__C__twiceLock__Debug__B__Ac__twiceLock:
        currentState = state_____Debug__C__twiceLock__Debug__B__Ac__twiceLock( &message );
        break;
    case Debug__C__twiceLock__Debug__A__Ac__twiceLock:
        currentState = state_____Debug__C__twiceLock__Debug__A__Ac__twiceLock( &message );
        break;
    case Debug__C__twiceLock__Debug__A__En__locked:
        currentState = state_____Debug__C__twiceLock__Debug__A__En__locked( &message );
        break;
    case Debug__C__twiceLock__boundary:
        currentState = state_____Debug__C__twiceLock__boundary( &message );
        break;
    case Debug__C__twiceUnlock__Debug__B__Ex__unlocked:
        currentState = state_____Debug__C__twiceUnlock__Debug__B__Ex__unlocked( &message );
        break;
    case Debug__C__twiceUnlock__Debug__B__Ac__twiceUnlock:
        currentState = state_____Debug__C__twiceUnlock__Debug__B__Ac__twiceUnlock( &message );
        break;
    case Debug__C__twiceUnlock__Debug__A__Ac__twiceUnlock:
        currentState = state_____Debug__C__twiceUnlock__Debug__A__Ac__twiceUnlock( &message );
        break;
    case Debug__C__twiceUnlock__Debug__A__En__unlocked:
        currentState = state_____Debug__C__twiceUnlock__Debug__A__En__unlocked( &message );
        break;
    case Debug__C__twiceUnlock__boundary:
        currentState = state_____Debug__C__twiceUnlock__boundary( &message );
        break;
    case Debug__C__init__Debug__B__Ac__init:
        currentState = state_____Debug__C__init__Debug__B__Ac__init( &message );
        break;
    case Debug__C__init__Debug__A__Ac__init:
        currentState = state_____Debug__C__init__Debug__A__Ac__init( &message );
        break;
    case Debug__C__init__Debug__A__En__init:
        currentState = state_____Debug__C__init__Debug__A__En__init( &message );
        break;
    case Debug__C__init__boundary:
        currentState = state_____Debug__C__init__boundary( &message );
        break;
    default:
        break;
    }
}

void Capsule_Lock::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Debug__InitDebug( &message );
    currentState = Debug__InitState;
}

const char * Capsule_Lock::getCurrentStateString() const
{
    return stateNames[currentState];
}





void Capsule_Lock::save_history( Capsule_Lock::State compositeState, Capsule_Lock::State subState )
{
    history[compositeState] = subState;
}

bool Capsule_Lock::check_history( Capsule_Lock::State compositeState, Capsule_Lock::State subState )
{
    return history[compositeState] == subState;
}

void Capsule_Lock::entryaction_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__init::Debug__A__Ac__init entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__init::Region1::Debug__A__Ac__init",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("init","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("unlocked","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__init::Debug__A__En__init entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__init::Region1::Debug__A__En__init",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("unlocked","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__init::Debug__B__Ac__init entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__init::Region1::Debug__B__Ac__init",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("init","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__C__init__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__C__lock__Debug__A__Ac__lock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__lock::Debug__A__Ac__lock entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__lock::Region1::Debug__A__Ac__lock",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("lock","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("locked","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__C__lock__Debug__A__En__locked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__lock::Debug__A__En__locked entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__lock::Region1::Debug__A__En__locked",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("locked","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__C__lock__Debug__B__Ac__lock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__lock::Debug__B__Ac__lock entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__lock::Region1::Debug__B__Ac__lock",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("unlocked","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("lock","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__C__lock__Debug__B__Ex__unlocked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__lock::Debug__B__Ex__unlocked entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__lock::Region1::Debug__B__Ex__unlocked",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("unlocked","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__C__lock__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__C__twiceLock__Debug__A__Ac__twiceLock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceLock::Debug__A__Ac__twiceLock entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceLock::Region1::Debug__A__Ac__twiceLock",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("twiceLock","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("locked","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__C__twiceLock__Debug__A__En__locked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceLock::Debug__A__En__locked entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceLock::Region1::Debug__A__En__locked",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("locked","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__C__twiceLock__Debug__B__Ac__twiceLock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceLock::Debug__B__Ac__twiceLock entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceLock::Region1::Debug__B__Ac__twiceLock",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("locked","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("twiceLock","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__C__twiceLock__Debug__B__Ex__locked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceLock::Debug__B__Ex__locked entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceLock::Region1::Debug__B__Ex__locked",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("locked","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__C__twiceLock__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__C__twiceUnlock__Debug__A__Ac__twiceUnlock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceUnlock::Debug__A__Ac__twiceUnlock entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceUnlock::Region1::Debug__A__Ac__twiceUnlock",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("twiceUnlock","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("unlocked","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__C__twiceUnlock__Debug__A__En__unlocked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceUnlock::Debug__A__En__unlocked entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceUnlock::Region1::Debug__A__En__unlocked",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("unlocked","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__C__twiceUnlock__Debug__B__Ac__twiceUnlock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceUnlock::Debug__B__Ac__twiceUnlock entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceUnlock::Region1::Debug__B__Ac__twiceUnlock",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("unlocked","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("twiceUnlock","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__C__twiceUnlock__Debug__B__Ex__unlocked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceUnlock::Debug__B__Ex__unlocked entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceUnlock::Region1::Debug__B__Ex__unlocked",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("unlocked","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__C__twiceUnlock__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__C__unlock__Debug__A__Ac__unlock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__unlock::Debug__A__Ac__unlock entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__unlock::Region1::Debug__A__Ac__unlock",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("unlock","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("unlocked","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__C__unlock__Debug__A__En__unlocked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__unlock::Debug__A__En__unlocked entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__unlock::Region1::Debug__A__En__unlocked",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("unlocked","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__C__unlock__Debug__B__Ac__unlock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__unlock::Debug__B__Ac__unlock entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__unlock::Region1::Debug__B__Ac__unlock",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("locked","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("unlock","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__C__unlock__Debug__B__Ex__locked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__unlock::Debug__B__Ex__locked entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__unlock::Region1::Debug__B__Ex__locked",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("locked","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__C__unlock__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Lock::entryaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__InitState entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::entryaction_____locked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::locked entry  */
    if( not Debug__SRO.checkDebug("locked",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::locked",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::entryaction_____unlocked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::unlocked entry  */
    if( not Debug__SRO.checkDebug("unlocked",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::unlocked",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__init::Debug__A__Ac__init exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__init::Region1::Debug__A__Ac__init",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__init::Debug__A__En__init exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__init::Region1::Debug__A__En__init",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__init::Debug__B__Ac__init exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__init::Region1::Debug__B__Ac__init",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__init__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__lock__Debug__A__Ac__lock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__lock::Debug__A__Ac__lock exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__lock::Region1::Debug__A__Ac__lock",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__lock__Debug__A__En__locked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__lock::Debug__A__En__locked exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__lock::Region1::Debug__A__En__locked",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__lock__Debug__B__Ac__lock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__lock::Debug__B__Ac__lock exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__lock::Region1::Debug__B__Ac__lock",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__lock__Debug__B__Ex__unlocked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__lock::Debug__B__Ex__unlocked exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__lock::Region1::Debug__B__Ex__unlocked",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__lock__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__twiceLock__Debug__A__Ac__twiceLock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceLock::Debug__A__Ac__twiceLock exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceLock::Region1::Debug__A__Ac__twiceLock",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__twiceLock__Debug__A__En__locked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceLock::Debug__A__En__locked exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceLock::Region1::Debug__A__En__locked",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__twiceLock__Debug__B__Ac__twiceLock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceLock::Debug__B__Ac__twiceLock exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceLock::Region1::Debug__B__Ac__twiceLock",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__twiceLock__Debug__B__Ex__locked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceLock::Debug__B__Ex__locked exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceLock::Region1::Debug__B__Ex__locked",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__twiceLock__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__twiceUnlock__Debug__A__Ac__twiceUnlock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceUnlock::Debug__A__Ac__twiceUnlock exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceUnlock::Region1::Debug__A__Ac__twiceUnlock",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__twiceUnlock__Debug__A__En__unlocked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceUnlock::Debug__A__En__unlocked exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceUnlock::Region1::Debug__A__En__unlocked",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__twiceUnlock__Debug__B__Ac__twiceUnlock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceUnlock::Debug__B__Ac__twiceUnlock exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceUnlock::Region1::Debug__B__Ac__twiceUnlock",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__twiceUnlock__Debug__B__Ex__unlocked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceUnlock::Debug__B__Ex__unlocked exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceUnlock::Region1::Debug__B__Ex__unlocked",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__twiceUnlock__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__unlock__Debug__A__Ac__unlock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__unlock::Debug__A__Ac__unlock exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__unlock::Region1::Debug__A__Ac__unlock",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__unlock__Debug__A__En__unlocked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__unlock::Debug__A__En__unlocked exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__unlock::Region1::Debug__A__En__unlocked",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__unlock__Debug__B__Ac__unlock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__unlock::Debug__B__Ac__unlock exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__unlock::Region1::Debug__B__Ac__unlock",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__unlock__Debug__B__Ex__locked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__unlock::Debug__B__Ex__locked exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__unlock::Region1::Debug__B__Ex__locked",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__C__unlock__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Lock::exitaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__InitState exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____locked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::locked exit  */
    if( not Debug__SRO.checkDebug("locked",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::locked",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::exitaction_____unlocked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::unlocked exit  */
    if( not Debug__SRO.checkDebug("unlocked",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::unlocked",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__init__Debug__Ac__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__init transition Debug__C__init::Debug__B__Ac__init,Debug__C__init::Debug__A__Ac__init,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__init::Region1::Debug__Ac__init",(char *)"Debug__B__Ac__init",(char *)"Debug__A__Ac__init",(char *)"");
    std::cout<<"The Lock "<<this->borderPorts[0]->slotName()<<"  is unlocked"<<std::endl;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__init__Debug__En__unlocked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__init transition Debug__C__init::Debug__A__Ac__init,Debug__C__init::Debug__A__En__init,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__init::Region1::Debug__En__unlocked",(char *)"Debug__A__Ac__init",(char *)"Debug__A__En__init",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__init__Debug__end__trans__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__init transition Debug__C__init::Debug__A__En__init,Debug__C__init::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__init::Region1::Debug__end__trans__init",(char *)"Debug__A__En__init",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__init__Debug__init__trans__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__init transition Debug__C__init::en,Debug__C__init::Debug__B__Ac__init */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__init::Region1::Debug__init__trans__init",(char *)"en",(char *)"Debug__B__Ac__init",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__lock__Debug__AC__lock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__lock transition Debug__C__lock::Debug__B__Ac__lock,Debug__C__lock::Debug__A__Ac__lock,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__lock::Region1::Debug__AC__lock",(char *)"Debug__B__Ac__lock",(char *)"Debug__A__Ac__lock",(char *)"");
    std::cout<<"The Lock "<<this->borderPorts[0]->slotName()<<"  is locked"<<std::endl;
    lockPort.lockStatus(true).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__lock__Debug__En__locked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__lock transition Debug__C__lock::Debug__A__Ac__lock,Debug__C__lock::Debug__A__En__locked,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__lock::Region1::Debug__En__locked",(char *)"Debug__A__Ac__lock",(char *)"Debug__A__En__locked",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__lock__Debug__Ex__unlocked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__lock transition Debug__C__lock::Debug__B__Ex__unlocked,Debug__C__lock::Debug__B__Ac__lock,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__lock::Region1::Debug__Ex__unlocked",(char *)"Debug__B__Ex__unlocked",(char *)"Debug__B__Ac__lock",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__lock__Debug__end__trans__lock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__lock transition Debug__C__lock::Debug__A__En__locked,Debug__C__lock::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__lock::Region1::Debug__end__trans__lock",(char *)"Debug__A__En__locked",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__lock__Debug__init__trans__lock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__lock transition Debug__C__lock::en,Debug__C__lock::Debug__B__Ex__unlocked */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__lock::Region1::Debug__init__trans__lock",(char *)"en",(char *)"Debug__B__Ex__unlocked",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__twiceLock__Debug__AC__twiceLock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceLock transition Debug__C__twiceLock::Debug__B__Ac__twiceLock,Debug__C__twiceLock::Debug__A__Ac__twiceLock,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceLock::Region1::Debug__AC__twiceLock",(char *)"Debug__B__Ac__twiceLock",(char *)"Debug__A__Ac__twiceLock",(char *)"");
    std::cout<<"The Lock   "<<this->borderPorts[0]->slotName()<<"  is already unlocked"<<std::endl;
    lockPort.lockStatus(false).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__twiceLock__Debug__En__locked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceLock transition Debug__C__twiceLock::Debug__A__Ac__twiceLock,Debug__C__twiceLock::Debug__A__En__locked,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceLock::Region1::Debug__En__locked",(char *)"Debug__A__Ac__twiceLock",(char *)"Debug__A__En__locked",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__twiceLock__Debug__Ex__locked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceLock transition Debug__C__twiceLock::Debug__B__Ex__locked,Debug__C__twiceLock::Debug__B__Ac__twiceLock,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceLock::Region1::Debug__Ex__locked",(char *)"Debug__B__Ex__locked",(char *)"Debug__B__Ac__twiceLock",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__twiceLock__Debug__end__trans__twiceLock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceLock transition Debug__C__twiceLock::Debug__A__En__locked,Debug__C__twiceLock::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceLock::Region1::Debug__end__trans__twiceLock",(char *)"Debug__A__En__locked",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__twiceLock__Debug__init__trans__twiceLock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceLock transition Debug__C__twiceLock::en,Debug__C__twiceLock::Debug__B__Ex__locked */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceLock::Region1::Debug__init__trans__twiceLock",(char *)"en",(char *)"Debug__B__Ex__locked",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__twiceUnlock__Debug__AC__twiceUnlock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceUnlock transition Debug__C__twiceUnlock::Debug__B__Ac__twiceUnlock,Debug__C__twiceUnlock::Debug__A__Ac__twiceUnlock,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceUnlock::Region1::Debug__AC__twiceUnlock",(char *)"Debug__B__Ac__twiceUnlock",(char *)"Debug__A__Ac__twiceUnlock",(char *)"");
    std::cout<<"The Lock   "<<this->borderPorts[0]->slotName()<<"  is already unlocked"<<std::endl;
    lockPort.lockStatus(true).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__twiceUnlock__Debug__En__unlocked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceUnlock transition Debug__C__twiceUnlock::Debug__A__Ac__twiceUnlock,Debug__C__twiceUnlock::Debug__A__En__unlocked,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceUnlock::Region1::Debug__En__unlocked",(char *)"Debug__A__Ac__twiceUnlock",(char *)"Debug__A__En__unlocked",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__twiceUnlock__Debug__Ex__unlocked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceUnlock transition Debug__C__twiceUnlock::Debug__B__Ex__unlocked,Debug__C__twiceUnlock::Debug__B__Ac__twiceUnlock,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceUnlock::Region1::Debug__Ex__unlocked",(char *)"Debug__B__Ex__unlocked",(char *)"Debug__B__Ac__twiceUnlock",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__twiceUnlock__Debug__end__trans__twiceUnlock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceUnlock transition Debug__C__twiceUnlock::Debug__A__En__unlocked,Debug__C__twiceUnlock::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceUnlock::Region1::Debug__end__trans__twiceUnlock",(char *)"Debug__A__En__unlocked",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__twiceUnlock__Debug__init__trans__twiceUnlock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__twiceUnlock transition Debug__C__twiceUnlock::en,Debug__C__twiceUnlock::Debug__B__Ex__unlocked */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__twiceUnlock::Region1::Debug__init__trans__twiceUnlock",(char *)"en",(char *)"Debug__B__Ex__unlocked",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__unlock__Debug__AC__unlock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__unlock transition Debug__C__unlock::Debug__B__Ac__unlock,Debug__C__unlock::Debug__A__Ac__unlock,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__unlock::Region1::Debug__AC__unlock",(char *)"Debug__B__Ac__unlock",(char *)"Debug__A__Ac__unlock",(char *)"");
    std::cout<<"The Lock "<<this->borderPorts[0]->slotName()<<"  is unlocked"<<std::endl;
    lockPort.lockStatus(false).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__unlock__Debug__En__unlocked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__unlock transition Debug__C__unlock::Debug__A__Ac__unlock,Debug__C__unlock::Debug__A__En__unlocked,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__unlock::Region1::Debug__En__unlocked",(char *)"Debug__A__Ac__unlock",(char *)"Debug__A__En__unlocked",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__unlock__Debug__Ex__locked( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__unlock transition Debug__C__unlock::Debug__B__Ex__locked,Debug__C__unlock::Debug__B__Ac__unlock,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__unlock::Region1::Debug__Ex__locked",(char *)"Debug__B__Ex__locked",(char *)"Debug__B__Ac__unlock",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__unlock__Debug__end__trans__unlock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__unlock transition Debug__C__unlock::Debug__A__En__unlocked,Debug__C__unlock::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__unlock::Region1::Debug__end__trans__unlock",(char *)"Debug__A__En__unlocked",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__C__unlock__Debug__init__trans__unlock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock::Debug__C__unlock transition Debug__C__unlock::en,Debug__C__unlock::Debug__B__Ex__locked */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__C__unlock::Region1::Debug__init__trans__unlock",(char *)"en",(char *)"Debug__B__Ex__locked",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__InitDebug( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition Initial1,Debug__InitState */
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

void Capsule_Lock::transitionaction_____Debug__init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition Debug__InitState,Debug__Path__init,null:extComm */
    if (this->Debug__SRO.getExecMode()==Stepping){
    Debug__SRO.addTransitionsFromState("locked","twiceLock","locked","lock","Locking");
    Debug__SRO.addTransitionsFromState("unlocked","twiceUnlock","unlocked","unlock","Locking");
    Debug__SRO.addTransitionsFromState("unlocked","lock","locked","lock","Locking");
    Debug__SRO.addTransitionsFromState("Initial1","init","unlocked","","");
    Debug__SRO.addTransitionsFromState("locked","unlock","unlocked","unlock","Locking");
    std::cout<<this->getName()<<": Connection with debugger is in progress\n";
    char  tempS[256];
    sprintf(tempS,"%s%d",this->getName(),(int)this->getIndex());
    extComm.registerToControl(tempS).send();
    Debug__sendEvent(debugEvents::DEBUG,debugEvents::REGISTER,this->getName(),this->getIndex(),msg->getSignalName(),(char *) "",(char *) "",(char *) "",(char *)"",(char *) "");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__init__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition Debug__C__init::ex,unlocked */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__init__E",(char *)"ex",(char *)"unlocked",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__init__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition Debug__Path__init,Debug__C__init::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__init__S",(char *)"Debug__Path__init",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__init__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition Debug__C__init::new_exitpoint_5,Debug__C__init */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__init__dbg",(char *)"Debug__C__init",(char *)"Debug__C__init",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__lock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition unlocked,Debug__Path__lock,lock:lockPort */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__lock",(char *)"unlocked",(char *)"Debug__Path__lock",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__lock__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition Debug__C__lock::ex,locked */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__lock__E",(char *)"ex",(char *)"locked",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__lock__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition Debug__Path__lock,Debug__C__lock::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__lock__S",(char *)"Debug__Path__lock",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__lock__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition Debug__C__lock::new_exitpoint_1,Debug__C__lock */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__lock__dbg",(char *)"Debug__C__lock",(char *)"Debug__C__lock",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__twiceLock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition locked,Debug__Path__twiceLock,lock:lockPort */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__twiceLock",(char *)"locked",(char *)"Debug__Path__twiceLock",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__twiceLock__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition Debug__C__twiceLock::ex,locked */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__twiceLock__E",(char *)"ex",(char *)"locked",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__twiceLock__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition Debug__Path__twiceLock,Debug__C__twiceLock::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__twiceLock__S",(char *)"Debug__Path__twiceLock",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__twiceLock__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition Debug__C__twiceLock::new_exitpoint_3,Debug__C__twiceLock */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__twiceLock__dbg",(char *)"Debug__C__twiceLock",(char *)"Debug__C__twiceLock",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__twiceUnlock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition unlocked,Debug__Path__twiceUnlock,unlock:lockPort */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__twiceUnlock",(char *)"unlocked",(char *)"Debug__Path__twiceUnlock",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__twiceUnlock__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition Debug__C__twiceUnlock::ex,unlocked */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__twiceUnlock__E",(char *)"ex",(char *)"unlocked",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__twiceUnlock__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition Debug__Path__twiceUnlock,Debug__C__twiceUnlock::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__twiceUnlock__S",(char *)"Debug__Path__twiceUnlock",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__twiceUnlock__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition Debug__C__twiceUnlock::new_exitpoint_4,Debug__C__twiceUnlock */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__twiceUnlock__dbg",(char *)"Debug__C__twiceUnlock",(char *)"Debug__C__twiceUnlock",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__unlock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition locked,Debug__Path__unlock,unlock:lockPort */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__unlock",(char *)"locked",(char *)"Debug__Path__unlock",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__unlock__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition Debug__C__unlock::ex,unlocked */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__unlock__E",(char *)"ex",(char *)"unlocked",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__unlock__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition Debug__Path__unlock,Debug__C__unlock::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__unlock__S",(char *)"Debug__Path__unlock",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____Debug__unlock__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition Debug__C__unlock::new_exitpoint_2,Debug__C__unlock */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::Debug__unlock__dbg",(char *)"Debug__C__unlock",(char *)"Debug__C__unlock",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition Debug__Path__init,unlocked */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::init",(char *)"Debug__Path__init",(char *)"unlocked",(char *)"");
    std::cout<<"The Lock "<<this->borderPorts[0]->slotName()<<"  is unlocked"<<std::endl;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____lock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition Debug__Path__lock,locked */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::lock",(char *)"Debug__Path__lock",(char *)"locked",(char *)"");
    std::cout<<"The Lock "<<this->borderPorts[0]->slotName()<<"  is locked"<<std::endl;
    lockPort.lockStatus(true).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____twiceLock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition Debug__Path__twiceLock,locked */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::twiceLock",(char *)"Debug__Path__twiceLock",(char *)"locked",(char *)"");
    std::cout<<"The Lock   "<<this->borderPorts[0]->slotName()<<"  is already unlocked"<<std::endl;
    lockPort.lockStatus(false).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____twiceUnlock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition Debug__Path__twiceUnlock,unlocked */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::twiceUnlock",(char *)"Debug__Path__twiceUnlock",(char *)"unlocked",(char *)"");
    std::cout<<"The Lock   "<<this->borderPorts[0]->slotName()<<"  is already unlocked"<<std::endl;
    lockPort.lockStatus(true).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::transitionaction_____unlock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock transition Debug__Path__unlock,unlocked */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"CarDoorLock::Lock::lockSM::Region1::unlock",(char *)"Debug__Path__unlock",(char *)"unlocked",(char *)"");
    std::cout<<"The Lock "<<this->borderPorts[0]->slotName()<<"  is unlocked"<<std::endl;
    lockPort.lockStatus(false).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Lock::action_____Debug__init__S__Debug__Guardinit( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock guard Debug__Path__init,Debug__C__init::en */
    return Debug__SRO.checkDebug("Initial1","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Lock::action_____Debug__lock__S__Debug__Guardlock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock guard Debug__Path__lock,Debug__C__lock::en */
    return Debug__SRO.checkDebug("unlocked",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Lock::action_____Debug__twiceLock__S__Debug__GuardtwiceLock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock guard Debug__Path__twiceLock,Debug__C__twiceLock::en */
    return Debug__SRO.checkDebug("locked",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Lock::action_____Debug__twiceUnlock__S__Debug__GuardtwiceUnlock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock guard Debug__Path__twiceUnlock,Debug__C__twiceUnlock::en */
    return Debug__SRO.checkDebug("unlocked",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Lock::action_____Debug__unlock__S__Debug__Guardunlock( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CarMultiDoorLockM/CarDoorLock.uml CarDoorLock::Lock guard Debug__Path__unlock,Debug__C__unlock::en */
    return Debug__SRO.checkDebug("locked",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Lock::actionchain_____Debug__C__init__Debug__Ac__init( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__B__Ac__init( msg );
    transitionaction_____Debug__C__init__Debug__Ac__init( msg );
    entryaction_____Debug__C__init__Debug__A__Ac__init( msg );
}

void Capsule_Lock::actionchain_____Debug__C__init__Debug__En__unlocked( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__A__Ac__init( msg );
    transitionaction_____Debug__C__init__Debug__En__unlocked( msg );
    entryaction_____Debug__C__init__Debug__A__En__init( msg );
}

void Capsule_Lock::actionchain_____Debug__C__init__Debug__end__trans__init( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__A__En__init( msg );
    transitionaction_____Debug__C__init__Debug__end__trans__init( msg );
    save_history( Debug__C__init, Debug__C__init__Debug__A__En__init );
}

void Capsule_Lock::actionchain_____Debug__C__init__Debug__init__trans__init( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__init__Debug__init__trans__init( msg );
    entryaction_____Debug__C__init__Debug__B__Ac__init( msg );
}

void Capsule_Lock::actionchain_____Debug__C__init__new_transition_41( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__Debug__B__Ac__init( msg );
}

void Capsule_Lock::actionchain_____Debug__C__init__new_transition_42( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__Debug__A__Ac__init( msg );
}

void Capsule_Lock::actionchain_____Debug__C__init__new_transition_43( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__Debug__A__En__init( msg );
}

void Capsule_Lock::actionchain_____Debug__C__init__new_transition_44_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__init__boundary( msg );
}

void Capsule_Lock::actionchain_____Debug__C__init__new_transition_45( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__B__Ac__init( msg );
    save_history( Debug__C__init, Debug__C__init__Debug__B__Ac__init );
}

void Capsule_Lock::actionchain_____Debug__C__init__new_transition_46( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__A__Ac__init( msg );
    save_history( Debug__C__init, Debug__C__init__Debug__A__Ac__init );
}

void Capsule_Lock::actionchain_____Debug__C__init__new_transition_47( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__Debug__A__En__init( msg );
    save_history( Debug__C__init, Debug__C__init__Debug__A__En__init );
}

void Capsule_Lock::actionchain_____Debug__C__init__new_transition_48( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__boundary( msg );
    save_history( Debug__C__init, Debug__C__init__boundary );
}

void Capsule_Lock::actionchain_____Debug__C__lock__Debug__AC__lock( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__lock__Debug__B__Ac__lock( msg );
    transitionaction_____Debug__C__lock__Debug__AC__lock( msg );
    entryaction_____Debug__C__lock__Debug__A__Ac__lock( msg );
}

void Capsule_Lock::actionchain_____Debug__C__lock__Debug__En__locked( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__lock__Debug__A__Ac__lock( msg );
    transitionaction_____Debug__C__lock__Debug__En__locked( msg );
    entryaction_____Debug__C__lock__Debug__A__En__locked( msg );
}

void Capsule_Lock::actionchain_____Debug__C__lock__Debug__Ex__unlocked( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__lock__Debug__B__Ex__unlocked( msg );
    transitionaction_____Debug__C__lock__Debug__Ex__unlocked( msg );
    entryaction_____Debug__C__lock__Debug__B__Ac__lock( msg );
}

void Capsule_Lock::actionchain_____Debug__C__lock__Debug__end__trans__lock( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__lock__Debug__A__En__locked( msg );
    transitionaction_____Debug__C__lock__Debug__end__trans__lock( msg );
    save_history( Debug__C__lock, Debug__C__lock__Debug__A__En__locked );
}

void Capsule_Lock::actionchain_____Debug__C__lock__Debug__init__trans__lock( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__lock__Debug__init__trans__lock( msg );
    entryaction_____Debug__C__lock__Debug__B__Ex__unlocked( msg );
}

void Capsule_Lock::actionchain_____Debug__C__lock__new_transition_1( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__lock__Debug__B__Ex__unlocked( msg );
}

void Capsule_Lock::actionchain_____Debug__C__lock__new_transition_10( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__lock__boundary( msg );
    save_history( Debug__C__lock, Debug__C__lock__boundary );
}

void Capsule_Lock::actionchain_____Debug__C__lock__new_transition_2( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__lock__Debug__B__Ac__lock( msg );
}

void Capsule_Lock::actionchain_____Debug__C__lock__new_transition_3( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__lock__Debug__A__Ac__lock( msg );
}

void Capsule_Lock::actionchain_____Debug__C__lock__new_transition_4( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__lock__Debug__A__En__locked( msg );
}

void Capsule_Lock::actionchain_____Debug__C__lock__new_transition_5_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__lock__boundary( msg );
}

void Capsule_Lock::actionchain_____Debug__C__lock__new_transition_6( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__lock__Debug__B__Ex__unlocked( msg );
    save_history( Debug__C__lock, Debug__C__lock__Debug__B__Ex__unlocked );
}

void Capsule_Lock::actionchain_____Debug__C__lock__new_transition_7( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__lock__Debug__B__Ac__lock( msg );
    save_history( Debug__C__lock, Debug__C__lock__Debug__B__Ac__lock );
}

void Capsule_Lock::actionchain_____Debug__C__lock__new_transition_8( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__lock__Debug__A__Ac__lock( msg );
    save_history( Debug__C__lock, Debug__C__lock__Debug__A__Ac__lock );
}

void Capsule_Lock::actionchain_____Debug__C__lock__new_transition_9( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__lock__Debug__A__En__locked( msg );
    save_history( Debug__C__lock, Debug__C__lock__Debug__A__En__locked );
}

void Capsule_Lock::actionchain_____Debug__C__twiceLock__Debug__AC__twiceLock( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__twiceLock__Debug__B__Ac__twiceLock( msg );
    transitionaction_____Debug__C__twiceLock__Debug__AC__twiceLock( msg );
    entryaction_____Debug__C__twiceLock__Debug__A__Ac__twiceLock( msg );
}

void Capsule_Lock::actionchain_____Debug__C__twiceLock__Debug__En__locked( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__twiceLock__Debug__A__Ac__twiceLock( msg );
    transitionaction_____Debug__C__twiceLock__Debug__En__locked( msg );
    entryaction_____Debug__C__twiceLock__Debug__A__En__locked( msg );
}

void Capsule_Lock::actionchain_____Debug__C__twiceLock__Debug__Ex__locked( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__twiceLock__Debug__B__Ex__locked( msg );
    transitionaction_____Debug__C__twiceLock__Debug__Ex__locked( msg );
    entryaction_____Debug__C__twiceLock__Debug__B__Ac__twiceLock( msg );
}

void Capsule_Lock::actionchain_____Debug__C__twiceLock__Debug__end__trans__twiceLock( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__twiceLock__Debug__A__En__locked( msg );
    transitionaction_____Debug__C__twiceLock__Debug__end__trans__twiceLock( msg );
    save_history( Debug__C__twiceLock, Debug__C__twiceLock__Debug__A__En__locked );
}

void Capsule_Lock::actionchain_____Debug__C__twiceLock__Debug__init__trans__twiceLock( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__twiceLock__Debug__init__trans__twiceLock( msg );
    entryaction_____Debug__C__twiceLock__Debug__B__Ex__locked( msg );
}

void Capsule_Lock::actionchain_____Debug__C__twiceLock__new_transition_21( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__twiceLock__Debug__B__Ex__locked( msg );
}

void Capsule_Lock::actionchain_____Debug__C__twiceLock__new_transition_22( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__twiceLock__Debug__B__Ac__twiceLock( msg );
}

void Capsule_Lock::actionchain_____Debug__C__twiceLock__new_transition_23( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__twiceLock__Debug__A__Ac__twiceLock( msg );
}

void Capsule_Lock::actionchain_____Debug__C__twiceLock__new_transition_24( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__twiceLock__Debug__A__En__locked( msg );
}

void Capsule_Lock::actionchain_____Debug__C__twiceLock__new_transition_25_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__twiceLock__boundary( msg );
}

void Capsule_Lock::actionchain_____Debug__C__twiceLock__new_transition_26( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__twiceLock__Debug__B__Ex__locked( msg );
    save_history( Debug__C__twiceLock, Debug__C__twiceLock__Debug__B__Ex__locked );
}

void Capsule_Lock::actionchain_____Debug__C__twiceLock__new_transition_27( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__twiceLock__Debug__B__Ac__twiceLock( msg );
    save_history( Debug__C__twiceLock, Debug__C__twiceLock__Debug__B__Ac__twiceLock );
}

void Capsule_Lock::actionchain_____Debug__C__twiceLock__new_transition_28( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__twiceLock__Debug__A__Ac__twiceLock( msg );
    save_history( Debug__C__twiceLock, Debug__C__twiceLock__Debug__A__Ac__twiceLock );
}

void Capsule_Lock::actionchain_____Debug__C__twiceLock__new_transition_29( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__twiceLock__Debug__A__En__locked( msg );
    save_history( Debug__C__twiceLock, Debug__C__twiceLock__Debug__A__En__locked );
}

void Capsule_Lock::actionchain_____Debug__C__twiceLock__new_transition_30( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__twiceLock__boundary( msg );
    save_history( Debug__C__twiceLock, Debug__C__twiceLock__boundary );
}

void Capsule_Lock::actionchain_____Debug__C__twiceUnlock__Debug__AC__twiceUnlock( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__twiceUnlock__Debug__B__Ac__twiceUnlock( msg );
    transitionaction_____Debug__C__twiceUnlock__Debug__AC__twiceUnlock( msg );
    entryaction_____Debug__C__twiceUnlock__Debug__A__Ac__twiceUnlock( msg );
}

void Capsule_Lock::actionchain_____Debug__C__twiceUnlock__Debug__En__unlocked( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__twiceUnlock__Debug__A__Ac__twiceUnlock( msg );
    transitionaction_____Debug__C__twiceUnlock__Debug__En__unlocked( msg );
    entryaction_____Debug__C__twiceUnlock__Debug__A__En__unlocked( msg );
}

void Capsule_Lock::actionchain_____Debug__C__twiceUnlock__Debug__Ex__unlocked( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__twiceUnlock__Debug__B__Ex__unlocked( msg );
    transitionaction_____Debug__C__twiceUnlock__Debug__Ex__unlocked( msg );
    entryaction_____Debug__C__twiceUnlock__Debug__B__Ac__twiceUnlock( msg );
}

void Capsule_Lock::actionchain_____Debug__C__twiceUnlock__Debug__end__trans__twiceUnlock( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__twiceUnlock__Debug__A__En__unlocked( msg );
    transitionaction_____Debug__C__twiceUnlock__Debug__end__trans__twiceUnlock( msg );
    save_history( Debug__C__twiceUnlock, Debug__C__twiceUnlock__Debug__A__En__unlocked );
}

void Capsule_Lock::actionchain_____Debug__C__twiceUnlock__Debug__init__trans__twiceUnlock( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__twiceUnlock__Debug__init__trans__twiceUnlock( msg );
    entryaction_____Debug__C__twiceUnlock__Debug__B__Ex__unlocked( msg );
}

void Capsule_Lock::actionchain_____Debug__C__twiceUnlock__new_transition_31( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__twiceUnlock__Debug__B__Ex__unlocked( msg );
}

void Capsule_Lock::actionchain_____Debug__C__twiceUnlock__new_transition_32( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__twiceUnlock__Debug__B__Ac__twiceUnlock( msg );
}

void Capsule_Lock::actionchain_____Debug__C__twiceUnlock__new_transition_33( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__twiceUnlock__Debug__A__Ac__twiceUnlock( msg );
}

void Capsule_Lock::actionchain_____Debug__C__twiceUnlock__new_transition_34( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__twiceUnlock__Debug__A__En__unlocked( msg );
}

void Capsule_Lock::actionchain_____Debug__C__twiceUnlock__new_transition_35_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__twiceUnlock__boundary( msg );
}

void Capsule_Lock::actionchain_____Debug__C__twiceUnlock__new_transition_36( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__twiceUnlock__Debug__B__Ex__unlocked( msg );
    save_history( Debug__C__twiceUnlock, Debug__C__twiceUnlock__Debug__B__Ex__unlocked );
}

void Capsule_Lock::actionchain_____Debug__C__twiceUnlock__new_transition_37( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__twiceUnlock__Debug__B__Ac__twiceUnlock( msg );
    save_history( Debug__C__twiceUnlock, Debug__C__twiceUnlock__Debug__B__Ac__twiceUnlock );
}

void Capsule_Lock::actionchain_____Debug__C__twiceUnlock__new_transition_38( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__twiceUnlock__Debug__A__Ac__twiceUnlock( msg );
    save_history( Debug__C__twiceUnlock, Debug__C__twiceUnlock__Debug__A__Ac__twiceUnlock );
}

void Capsule_Lock::actionchain_____Debug__C__twiceUnlock__new_transition_39( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__twiceUnlock__Debug__A__En__unlocked( msg );
    save_history( Debug__C__twiceUnlock, Debug__C__twiceUnlock__Debug__A__En__unlocked );
}

void Capsule_Lock::actionchain_____Debug__C__twiceUnlock__new_transition_40( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__twiceUnlock__boundary( msg );
    save_history( Debug__C__twiceUnlock, Debug__C__twiceUnlock__boundary );
}

void Capsule_Lock::actionchain_____Debug__C__unlock__Debug__AC__unlock( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__unlock__Debug__B__Ac__unlock( msg );
    transitionaction_____Debug__C__unlock__Debug__AC__unlock( msg );
    entryaction_____Debug__C__unlock__Debug__A__Ac__unlock( msg );
}

void Capsule_Lock::actionchain_____Debug__C__unlock__Debug__En__unlocked( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__unlock__Debug__A__Ac__unlock( msg );
    transitionaction_____Debug__C__unlock__Debug__En__unlocked( msg );
    entryaction_____Debug__C__unlock__Debug__A__En__unlocked( msg );
}

void Capsule_Lock::actionchain_____Debug__C__unlock__Debug__Ex__locked( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__unlock__Debug__B__Ex__locked( msg );
    transitionaction_____Debug__C__unlock__Debug__Ex__locked( msg );
    entryaction_____Debug__C__unlock__Debug__B__Ac__unlock( msg );
}

void Capsule_Lock::actionchain_____Debug__C__unlock__Debug__end__trans__unlock( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__unlock__Debug__A__En__unlocked( msg );
    transitionaction_____Debug__C__unlock__Debug__end__trans__unlock( msg );
    save_history( Debug__C__unlock, Debug__C__unlock__Debug__A__En__unlocked );
}

void Capsule_Lock::actionchain_____Debug__C__unlock__Debug__init__trans__unlock( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__unlock__Debug__init__trans__unlock( msg );
    entryaction_____Debug__C__unlock__Debug__B__Ex__locked( msg );
}

void Capsule_Lock::actionchain_____Debug__C__unlock__new_transition_11( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__unlock__Debug__B__Ex__locked( msg );
}

void Capsule_Lock::actionchain_____Debug__C__unlock__new_transition_12( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__unlock__Debug__B__Ac__unlock( msg );
}

void Capsule_Lock::actionchain_____Debug__C__unlock__new_transition_13( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__unlock__Debug__A__Ac__unlock( msg );
}

void Capsule_Lock::actionchain_____Debug__C__unlock__new_transition_14( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__unlock__Debug__A__En__unlocked( msg );
}

void Capsule_Lock::actionchain_____Debug__C__unlock__new_transition_15_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__unlock__boundary( msg );
}

void Capsule_Lock::actionchain_____Debug__C__unlock__new_transition_16( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__unlock__Debug__B__Ex__locked( msg );
    save_history( Debug__C__unlock, Debug__C__unlock__Debug__B__Ex__locked );
}

void Capsule_Lock::actionchain_____Debug__C__unlock__new_transition_17( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__unlock__Debug__B__Ac__unlock( msg );
    save_history( Debug__C__unlock, Debug__C__unlock__Debug__B__Ac__unlock );
}

void Capsule_Lock::actionchain_____Debug__C__unlock__new_transition_18( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__unlock__Debug__A__Ac__unlock( msg );
    save_history( Debug__C__unlock, Debug__C__unlock__Debug__A__Ac__unlock );
}

void Capsule_Lock::actionchain_____Debug__C__unlock__new_transition_19( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__unlock__Debug__A__En__unlocked( msg );
    save_history( Debug__C__unlock, Debug__C__unlock__Debug__A__En__unlocked );
}

void Capsule_Lock::actionchain_____Debug__C__unlock__new_transition_20( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__unlock__boundary( msg );
    save_history( Debug__C__unlock, Debug__C__unlock__boundary );
}

void Capsule_Lock::actionchain_____Debug__InitDebug( const UMLRTMessage * msg )
{
    transitionaction_____Debug__InitDebug( msg );
    entryaction_____Debug__InitState( msg );
}

void Capsule_Lock::actionchain_____Debug__init( const UMLRTMessage * msg )
{
    exitaction_____Debug__InitState( msg );
    transitionaction_____Debug__init( msg );
}

void Capsule_Lock::actionchain_____Debug__init__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__boundary( msg );
    transitionaction_____Debug__init__E( msg );
    entryaction_____unlocked( msg );
}

void Capsule_Lock::actionchain_____Debug__init__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__init__S( msg );
    entryaction_____Debug__C__init__boundary( msg );
}

void Capsule_Lock::actionchain_____Debug__init__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__init__boundary( msg );
    transitionaction_____Debug__init__dbg( msg );
    entryaction_____Debug__C__init__boundary( msg );
}

void Capsule_Lock::actionchain_____Debug__lock( const UMLRTMessage * msg )
{
    exitaction_____unlocked( msg );
    transitionaction_____Debug__lock( msg );
}

void Capsule_Lock::actionchain_____Debug__lock__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__lock__boundary( msg );
    transitionaction_____Debug__lock__E( msg );
    entryaction_____locked( msg );
}

void Capsule_Lock::actionchain_____Debug__lock__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__lock__S( msg );
    entryaction_____Debug__C__lock__boundary( msg );
}

void Capsule_Lock::actionchain_____Debug__lock__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__lock__boundary( msg );
    transitionaction_____Debug__lock__dbg( msg );
    entryaction_____Debug__C__lock__boundary( msg );
}

void Capsule_Lock::actionchain_____Debug__twiceLock( const UMLRTMessage * msg )
{
    exitaction_____locked( msg );
    transitionaction_____Debug__twiceLock( msg );
}

void Capsule_Lock::actionchain_____Debug__twiceLock__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__twiceLock__boundary( msg );
    transitionaction_____Debug__twiceLock__E( msg );
    entryaction_____locked( msg );
}

void Capsule_Lock::actionchain_____Debug__twiceLock__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__twiceLock__S( msg );
    entryaction_____Debug__C__twiceLock__boundary( msg );
}

void Capsule_Lock::actionchain_____Debug__twiceLock__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__twiceLock__boundary( msg );
    transitionaction_____Debug__twiceLock__dbg( msg );
    entryaction_____Debug__C__twiceLock__boundary( msg );
}

void Capsule_Lock::actionchain_____Debug__twiceUnlock( const UMLRTMessage * msg )
{
    exitaction_____unlocked( msg );
    transitionaction_____Debug__twiceUnlock( msg );
}

void Capsule_Lock::actionchain_____Debug__twiceUnlock__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__twiceUnlock__boundary( msg );
    transitionaction_____Debug__twiceUnlock__E( msg );
    entryaction_____unlocked( msg );
}

void Capsule_Lock::actionchain_____Debug__twiceUnlock__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__twiceUnlock__S( msg );
    entryaction_____Debug__C__twiceUnlock__boundary( msg );
}

void Capsule_Lock::actionchain_____Debug__twiceUnlock__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__twiceUnlock__boundary( msg );
    transitionaction_____Debug__twiceUnlock__dbg( msg );
    entryaction_____Debug__C__twiceUnlock__boundary( msg );
}

void Capsule_Lock::actionchain_____Debug__unlock( const UMLRTMessage * msg )
{
    exitaction_____locked( msg );
    transitionaction_____Debug__unlock( msg );
}

void Capsule_Lock::actionchain_____Debug__unlock__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__unlock__boundary( msg );
    transitionaction_____Debug__unlock__E( msg );
    entryaction_____unlocked( msg );
}

void Capsule_Lock::actionchain_____Debug__unlock__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__unlock__S( msg );
    entryaction_____Debug__C__unlock__boundary( msg );
}

void Capsule_Lock::actionchain_____Debug__unlock__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__unlock__boundary( msg );
    transitionaction_____Debug__unlock__dbg( msg );
    entryaction_____Debug__C__unlock__boundary( msg );
}

void Capsule_Lock::actionchain_____init( const UMLRTMessage * msg )
{
    transitionaction_____init( msg );
    entryaction_____unlocked( msg );
}

void Capsule_Lock::actionchain_____lock( const UMLRTMessage * msg )
{
    transitionaction_____lock( msg );
    entryaction_____locked( msg );
}

void Capsule_Lock::actionchain_____twiceLock( const UMLRTMessage * msg )
{
    transitionaction_____twiceLock( msg );
    entryaction_____locked( msg );
}

void Capsule_Lock::actionchain_____twiceUnlock( const UMLRTMessage * msg )
{
    transitionaction_____twiceUnlock( msg );
    entryaction_____unlocked( msg );
}

void Capsule_Lock::actionchain_____unlock( const UMLRTMessage * msg )
{
    transitionaction_____unlock( msg );
    entryaction_____unlocked( msg );
}

Capsule_Lock::State Capsule_Lock::junction_____Debug__C__init__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__init__Debug__init__trans__init( msg );
    return Debug__C__init__Debug__B__Ac__init;
}

Capsule_Lock::State Capsule_Lock::junction_____Debug__C__init__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__init__E( msg );
    return unlocked;
}

Capsule_Lock::State Capsule_Lock::junction_____Debug__C__init__new_exitpoint_5( const UMLRTMessage * msg )
{
    actionchain_____Debug__init__dbg( msg );
    return choice_____Debug__C__init__deephistory( msg );
}

Capsule_Lock::State Capsule_Lock::junction_____Debug__C__lock__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__lock__Debug__init__trans__lock( msg );
    return Debug__C__lock__Debug__B__Ex__unlocked;
}

Capsule_Lock::State Capsule_Lock::junction_____Debug__C__lock__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__lock__E( msg );
    return locked;
}

Capsule_Lock::State Capsule_Lock::junction_____Debug__C__lock__new_exitpoint_1( const UMLRTMessage * msg )
{
    actionchain_____Debug__lock__dbg( msg );
    return choice_____Debug__C__lock__deephistory( msg );
}

Capsule_Lock::State Capsule_Lock::junction_____Debug__C__twiceLock__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__twiceLock__Debug__init__trans__twiceLock( msg );
    return Debug__C__twiceLock__Debug__B__Ex__locked;
}

Capsule_Lock::State Capsule_Lock::junction_____Debug__C__twiceLock__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__twiceLock__E( msg );
    return locked;
}

Capsule_Lock::State Capsule_Lock::junction_____Debug__C__twiceLock__new_exitpoint_3( const UMLRTMessage * msg )
{
    actionchain_____Debug__twiceLock__dbg( msg );
    return choice_____Debug__C__twiceLock__deephistory( msg );
}

Capsule_Lock::State Capsule_Lock::junction_____Debug__C__twiceUnlock__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__twiceUnlock__Debug__init__trans__twiceUnlock( msg );
    return Debug__C__twiceUnlock__Debug__B__Ex__unlocked;
}

Capsule_Lock::State Capsule_Lock::junction_____Debug__C__twiceUnlock__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__twiceUnlock__E( msg );
    return unlocked;
}

Capsule_Lock::State Capsule_Lock::junction_____Debug__C__twiceUnlock__new_exitpoint_4( const UMLRTMessage * msg )
{
    actionchain_____Debug__twiceUnlock__dbg( msg );
    return choice_____Debug__C__twiceUnlock__deephistory( msg );
}

Capsule_Lock::State Capsule_Lock::junction_____Debug__C__unlock__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__unlock__Debug__init__trans__unlock( msg );
    return Debug__C__unlock__Debug__B__Ex__locked;
}

Capsule_Lock::State Capsule_Lock::junction_____Debug__C__unlock__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__unlock__E( msg );
    return unlocked;
}

Capsule_Lock::State Capsule_Lock::junction_____Debug__C__unlock__new_exitpoint_2( const UMLRTMessage * msg )
{
    actionchain_____Debug__unlock__dbg( msg );
    return choice_____Debug__C__unlock__deephistory( msg );
}

Capsule_Lock::State Capsule_Lock::choice_____Debug__C__init__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__init, Debug__C__init__Debug__B__Ac__init ) )
    {
        actionchain_____Debug__C__init__new_transition_41( msg );
        return Debug__C__init__Debug__B__Ac__init;
    }
    else if( check_history( Debug__C__init, Debug__C__init__Debug__A__Ac__init ) )
    {
        actionchain_____Debug__C__init__new_transition_42( msg );
        return Debug__C__init__Debug__A__Ac__init;
    }
    else if( check_history( Debug__C__init, Debug__C__init__Debug__A__En__init ) )
    {
        actionchain_____Debug__C__init__new_transition_43( msg );
        return Debug__C__init__Debug__A__En__init;
    }
    else if( check_history( Debug__C__init, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__init__new_transition_44_to_boundary( msg );
        return Debug__C__init__boundary;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::choice_____Debug__C__lock__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__lock, Debug__C__lock__Debug__B__Ex__unlocked ) )
    {
        actionchain_____Debug__C__lock__new_transition_1( msg );
        return Debug__C__lock__Debug__B__Ex__unlocked;
    }
    else if( check_history( Debug__C__lock, Debug__C__lock__Debug__B__Ac__lock ) )
    {
        actionchain_____Debug__C__lock__new_transition_2( msg );
        return Debug__C__lock__Debug__B__Ac__lock;
    }
    else if( check_history( Debug__C__lock, Debug__C__lock__Debug__A__Ac__lock ) )
    {
        actionchain_____Debug__C__lock__new_transition_3( msg );
        return Debug__C__lock__Debug__A__Ac__lock;
    }
    else if( check_history( Debug__C__lock, Debug__C__lock__Debug__A__En__locked ) )
    {
        actionchain_____Debug__C__lock__new_transition_4( msg );
        return Debug__C__lock__Debug__A__En__locked;
    }
    else if( check_history( Debug__C__lock, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__lock__new_transition_5_to_boundary( msg );
        return Debug__C__lock__boundary;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::choice_____Debug__C__twiceLock__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__twiceLock, Debug__C__twiceLock__Debug__B__Ex__locked ) )
    {
        actionchain_____Debug__C__twiceLock__new_transition_21( msg );
        return Debug__C__twiceLock__Debug__B__Ex__locked;
    }
    else if( check_history( Debug__C__twiceLock, Debug__C__twiceLock__Debug__B__Ac__twiceLock ) )
    {
        actionchain_____Debug__C__twiceLock__new_transition_22( msg );
        return Debug__C__twiceLock__Debug__B__Ac__twiceLock;
    }
    else if( check_history( Debug__C__twiceLock, Debug__C__twiceLock__Debug__A__Ac__twiceLock ) )
    {
        actionchain_____Debug__C__twiceLock__new_transition_23( msg );
        return Debug__C__twiceLock__Debug__A__Ac__twiceLock;
    }
    else if( check_history( Debug__C__twiceLock, Debug__C__twiceLock__Debug__A__En__locked ) )
    {
        actionchain_____Debug__C__twiceLock__new_transition_24( msg );
        return Debug__C__twiceLock__Debug__A__En__locked;
    }
    else if( check_history( Debug__C__twiceLock, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__twiceLock__new_transition_25_to_boundary( msg );
        return Debug__C__twiceLock__boundary;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::choice_____Debug__C__twiceUnlock__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__twiceUnlock, Debug__C__twiceUnlock__Debug__B__Ex__unlocked ) )
    {
        actionchain_____Debug__C__twiceUnlock__new_transition_31( msg );
        return Debug__C__twiceUnlock__Debug__B__Ex__unlocked;
    }
    else if( check_history( Debug__C__twiceUnlock, Debug__C__twiceUnlock__Debug__B__Ac__twiceUnlock ) )
    {
        actionchain_____Debug__C__twiceUnlock__new_transition_32( msg );
        return Debug__C__twiceUnlock__Debug__B__Ac__twiceUnlock;
    }
    else if( check_history( Debug__C__twiceUnlock, Debug__C__twiceUnlock__Debug__A__Ac__twiceUnlock ) )
    {
        actionchain_____Debug__C__twiceUnlock__new_transition_33( msg );
        return Debug__C__twiceUnlock__Debug__A__Ac__twiceUnlock;
    }
    else if( check_history( Debug__C__twiceUnlock, Debug__C__twiceUnlock__Debug__A__En__unlocked ) )
    {
        actionchain_____Debug__C__twiceUnlock__new_transition_34( msg );
        return Debug__C__twiceUnlock__Debug__A__En__unlocked;
    }
    else if( check_history( Debug__C__twiceUnlock, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__twiceUnlock__new_transition_35_to_boundary( msg );
        return Debug__C__twiceUnlock__boundary;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::choice_____Debug__C__unlock__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__unlock, Debug__C__unlock__Debug__B__Ex__locked ) )
    {
        actionchain_____Debug__C__unlock__new_transition_11( msg );
        return Debug__C__unlock__Debug__B__Ex__locked;
    }
    else if( check_history( Debug__C__unlock, Debug__C__unlock__Debug__B__Ac__unlock ) )
    {
        actionchain_____Debug__C__unlock__new_transition_12( msg );
        return Debug__C__unlock__Debug__B__Ac__unlock;
    }
    else if( check_history( Debug__C__unlock, Debug__C__unlock__Debug__A__Ac__unlock ) )
    {
        actionchain_____Debug__C__unlock__new_transition_13( msg );
        return Debug__C__unlock__Debug__A__Ac__unlock;
    }
    else if( check_history( Debug__C__unlock, Debug__C__unlock__Debug__A__En__unlocked ) )
    {
        actionchain_____Debug__C__unlock__new_transition_14( msg );
        return Debug__C__unlock__Debug__A__En__unlocked;
    }
    else if( check_history( Debug__C__unlock, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__unlock__new_transition_15_to_boundary( msg );
        return Debug__C__unlock__boundary;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::choice_____Debug__Path__init( const UMLRTMessage * msg )
{
    if( action_____Debug__init__S__Debug__Guardinit( msg ) )
    {
        actionchain_____Debug__init__S( msg );
        return junction_____Debug__C__init__en( msg );
    }
    else
    {
        actionchain_____init( msg );
        return unlocked;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::choice_____Debug__Path__lock( const UMLRTMessage * msg )
{
    if( action_____Debug__lock__S__Debug__Guardlock( msg ) )
    {
        actionchain_____Debug__lock__S( msg );
        return junction_____Debug__C__lock__en( msg );
    }
    else
    {
        actionchain_____lock( msg );
        return locked;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::choice_____Debug__Path__twiceLock( const UMLRTMessage * msg )
{
    if( action_____Debug__twiceLock__S__Debug__GuardtwiceLock( msg ) )
    {
        actionchain_____Debug__twiceLock__S( msg );
        return junction_____Debug__C__twiceLock__en( msg );
    }
    else
    {
        actionchain_____twiceLock( msg );
        return locked;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::choice_____Debug__Path__twiceUnlock( const UMLRTMessage * msg )
{
    if( action_____Debug__twiceUnlock__S__Debug__GuardtwiceUnlock( msg ) )
    {
        actionchain_____Debug__twiceUnlock__S( msg );
        return junction_____Debug__C__twiceUnlock__en( msg );
    }
    else
    {
        actionchain_____twiceUnlock( msg );
        return unlocked;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::choice_____Debug__Path__unlock( const UMLRTMessage * msg )
{
    if( action_____Debug__unlock__S__Debug__Guardunlock( msg ) )
    {
        actionchain_____Debug__unlock__S( msg );
        return junction_____Debug__C__unlock__en( msg );
    }
    else
    {
        actionchain_____unlock( msg );
        return unlocked;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__init__Debug__En__unlocked( msg );
            return Debug__C__init__Debug__A__En__init;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__init__new_transition_46( msg );
            return junction_____Debug__C__init__new_exitpoint_5( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__init__Debug__end__trans__init( msg );
            return junction_____Debug__C__init__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__init__new_transition_47( msg );
            return junction_____Debug__C__init__new_exitpoint_5( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__init__Debug__Ac__init( msg );
            return Debug__C__init__Debug__A__Ac__init;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__init__new_transition_45( msg );
            return junction_____Debug__C__init__new_exitpoint_5( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__init__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__init__new_transition_48( msg );
            return junction_____Debug__C__init__new_exitpoint_5( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__lock__Debug__A__Ac__lock( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__lock__Debug__En__locked( msg );
            return Debug__C__lock__Debug__A__En__locked;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__lock__new_transition_8( msg );
            return junction_____Debug__C__lock__new_exitpoint_1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__lock__Debug__A__En__locked( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__lock__Debug__end__trans__lock( msg );
            return junction_____Debug__C__lock__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__lock__new_transition_9( msg );
            return junction_____Debug__C__lock__new_exitpoint_1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__lock__Debug__B__Ac__lock( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__lock__Debug__AC__lock( msg );
            return Debug__C__lock__Debug__A__Ac__lock;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__lock__new_transition_7( msg );
            return junction_____Debug__C__lock__new_exitpoint_1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__lock__Debug__B__Ex__unlocked( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__lock__Debug__Ex__unlocked( msg );
            return Debug__C__lock__Debug__B__Ac__lock;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__lock__new_transition_6( msg );
            return junction_____Debug__C__lock__new_exitpoint_1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__lock__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__lock__new_transition_10( msg );
            return junction_____Debug__C__lock__new_exitpoint_1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__twiceLock__Debug__A__Ac__twiceLock( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__twiceLock__Debug__En__locked( msg );
            return Debug__C__twiceLock__Debug__A__En__locked;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__twiceLock__new_transition_28( msg );
            return junction_____Debug__C__twiceLock__new_exitpoint_3( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__twiceLock__Debug__A__En__locked( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__twiceLock__Debug__end__trans__twiceLock( msg );
            return junction_____Debug__C__twiceLock__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__twiceLock__new_transition_29( msg );
            return junction_____Debug__C__twiceLock__new_exitpoint_3( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__twiceLock__Debug__B__Ac__twiceLock( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__twiceLock__Debug__AC__twiceLock( msg );
            return Debug__C__twiceLock__Debug__A__Ac__twiceLock;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__twiceLock__new_transition_27( msg );
            return junction_____Debug__C__twiceLock__new_exitpoint_3( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__twiceLock__Debug__B__Ex__locked( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__twiceLock__Debug__Ex__locked( msg );
            return Debug__C__twiceLock__Debug__B__Ac__twiceLock;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__twiceLock__new_transition_26( msg );
            return junction_____Debug__C__twiceLock__new_exitpoint_3( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__twiceLock__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__twiceLock__new_transition_30( msg );
            return junction_____Debug__C__twiceLock__new_exitpoint_3( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__twiceUnlock__Debug__A__Ac__twiceUnlock( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__twiceUnlock__Debug__En__unlocked( msg );
            return Debug__C__twiceUnlock__Debug__A__En__unlocked;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__twiceUnlock__new_transition_38( msg );
            return junction_____Debug__C__twiceUnlock__new_exitpoint_4( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__twiceUnlock__Debug__A__En__unlocked( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__twiceUnlock__Debug__end__trans__twiceUnlock( msg );
            return junction_____Debug__C__twiceUnlock__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__twiceUnlock__new_transition_39( msg );
            return junction_____Debug__C__twiceUnlock__new_exitpoint_4( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__twiceUnlock__Debug__B__Ac__twiceUnlock( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__twiceUnlock__Debug__AC__twiceUnlock( msg );
            return Debug__C__twiceUnlock__Debug__A__Ac__twiceUnlock;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__twiceUnlock__new_transition_37( msg );
            return junction_____Debug__C__twiceUnlock__new_exitpoint_4( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__twiceUnlock__Debug__B__Ex__unlocked( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__twiceUnlock__Debug__Ex__unlocked( msg );
            return Debug__C__twiceUnlock__Debug__B__Ac__twiceUnlock;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__twiceUnlock__new_transition_36( msg );
            return junction_____Debug__C__twiceUnlock__new_exitpoint_4( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__twiceUnlock__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__twiceUnlock__new_transition_40( msg );
            return junction_____Debug__C__twiceUnlock__new_exitpoint_4( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__unlock__Debug__A__Ac__unlock( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__unlock__Debug__En__unlocked( msg );
            return Debug__C__unlock__Debug__A__En__unlocked;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__unlock__new_transition_18( msg );
            return junction_____Debug__C__unlock__new_exitpoint_2( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__unlock__Debug__A__En__unlocked( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__unlock__Debug__end__trans__unlock( msg );
            return junction_____Debug__C__unlock__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__unlock__new_transition_19( msg );
            return junction_____Debug__C__unlock__new_exitpoint_2( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__unlock__Debug__B__Ac__unlock( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__unlock__Debug__AC__unlock( msg );
            return Debug__C__unlock__Debug__A__Ac__unlock;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__unlock__new_transition_17( msg );
            return junction_____Debug__C__unlock__new_exitpoint_2( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__unlock__Debug__B__Ex__locked( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__unlock__Debug__Ex__locked( msg );
            return Debug__C__unlock__Debug__B__Ac__unlock;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__unlock__new_transition_16( msg );
            return junction_____Debug__C__unlock__new_exitpoint_2( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__C__unlock__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__unlock__new_transition_20( msg );
            return junction_____Debug__C__unlock__new_exitpoint_2( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____Debug__InitState( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__init( msg );
            return choice_____Debug__Path__init( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____locked( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_lockPort:
        switch( msg->getSignalId() )
        {
        case Locking::signal_unlock:
            actionchain_____Debug__unlock( msg );
            return choice_____Debug__Path__unlock( msg );
        case Locking::signal_lock:
            actionchain_____Debug__twiceLock( msg );
            return choice_____Debug__Path__twiceLock( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Lock::State Capsule_Lock::state_____unlocked( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_lockPort:
        switch( msg->getSignalId() )
        {
        case Locking::signal_lock:
            actionchain_____Debug__lock( msg );
            return choice_____Debug__Path__lock( msg );
        case Locking::signal_unlock:
            actionchain_____Debug__twiceUnlock( msg );
            return choice_____Debug__Path__twiceUnlock( msg );
        default:
            this->unexpectedMessage();
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
        Capsule_Lock::port_lockPort,
        "Locking",
        "lockPort",
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
        Capsule_Lock::port_extComm,
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

static void instantiate_Lock( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_Lock( &Lock, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Lock = 
{
    "Lock",
    NULL,
    instantiate_Lock,
    0,
    NULL,
    2,
    portroles_border,
    0,
    NULL
};

