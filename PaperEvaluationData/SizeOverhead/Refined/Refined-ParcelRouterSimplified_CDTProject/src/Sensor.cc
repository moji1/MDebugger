
#include "Sensor.hh"

#include "ExtInterface.hh"
#include "detection.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "Parcel.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_Sensor::Capsule_Sensor( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, detection( borderPorts[borderport_detection] )
, extComm( borderPorts[borderport_extComm] )
, switchProtocol( borderPorts[borderport_switchProtocol] )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[Debug__C__IDLE__IDLE__9] = "Debug__C__IDLE__IDLE__9";
    stateNames[Debug__C__Initial] = "Debug__C__Initial";
    stateNames[Debug__C__IDLE__IDLE__9__Debug__A__Ac__IDLE__IDLE__9] = "Debug__C__IDLE__IDLE__9__Debug__A__Ac__IDLE__IDLE__9";
    stateNames[Debug__C__IDLE__IDLE__9__Debug__A__En__IDLE] = "Debug__C__IDLE__IDLE__9__Debug__A__En__IDLE";
    stateNames[Debug__C__IDLE__IDLE__9__Debug__B__Ac__IDLE__IDLE__9] = "Debug__C__IDLE__IDLE__9__Debug__B__Ac__IDLE__IDLE__9";
    stateNames[Debug__C__IDLE__IDLE__9__Debug__B__Ex__IDLE] = "Debug__C__IDLE__IDLE__9__Debug__B__Ex__IDLE";
    stateNames[Debug__C__IDLE__IDLE__9__boundary] = "Debug__C__IDLE__IDLE__9__boundary";
    stateNames[Debug__C__Initial__Debug__A__Ac__Initial] = "Debug__C__Initial__Debug__A__Ac__Initial";
    stateNames[Debug__C__Initial__Debug__A__En__Initial] = "Debug__C__Initial__Debug__A__En__Initial";
    stateNames[Debug__C__Initial__Debug__B__Ac__Initial] = "Debug__C__Initial__Debug__B__Ac__Initial";
    stateNames[Debug__C__Initial__boundary] = "Debug__C__Initial__boundary";
    stateNames[Debug__InitState] = "Debug__InitState";
    stateNames[IDLE] = "IDLE";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
    int i = 0;
    while( i < 2 )
        history[i++] = SPECIAL_INTERNAL_STATE_UNVISITED;
}








void Capsule_Sensor::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_detection:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_detection, index, true );
            break;
        case borderport_switchProtocol:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_switchProtocol, index, true );
            break;
        }
}

void Capsule_Sensor::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_detection:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_detection, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_detection], index );
            break;
        case borderport_switchProtocol:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_switchProtocol, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_switchProtocol], index );
            break;
        }
}





void Capsule_Sensor::Debug__variablesView()
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor operation Debug__variablesView */
    std::string tempS="";
    if (Debug__variablesData==NULL)
    Debug__variablesData=(char *)malloc(strlen(tempS.c_str())+1);
    else if (strlen(Debug__variablesData)<strlen(tempS.c_str()))
    Debug__variablesData=(char *) realloc(Debug__variablesData,strlen(tempS.c_str())+1);
    strcpy(Debug__variablesData,tempS.c_str());
    /* UMLRTGEN-USERREGION-END */
}

bool Capsule_Sensor::Debug__variablesChange( char * varName, char * varValue )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor operation Debug__variablesChange */
    std::string tempVarName="";
    tempVarName.append(varName);
    return false;
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_Sensor::Debug__sendEvent( debugEvents::EVENTSOURCEKIND eventSourceKind, debugEvents::EVENTTYPE eventType, const char * instanceName, int capsuleIndex, const char * signalName, char * capsuleName, char * sourceName, char * reserve1, char * reserve2, char * reserve3 )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor operation Debug__sendEvent */
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

void Capsule_Sensor::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case IDLE:
        currentState = state_____IDLE( &message );
        break;
    case Debug__InitState:
        currentState = state_____Debug__InitState( &message );
        break;
    case Debug__C__IDLE__IDLE__9__Debug__B__Ex__IDLE:
        currentState = state_____Debug__C__IDLE__IDLE__9__Debug__B__Ex__IDLE( &message );
        break;
    case Debug__C__IDLE__IDLE__9__Debug__B__Ac__IDLE__IDLE__9:
        currentState = state_____Debug__C__IDLE__IDLE__9__Debug__B__Ac__IDLE__IDLE__9( &message );
        break;
    case Debug__C__IDLE__IDLE__9__Debug__A__Ac__IDLE__IDLE__9:
        currentState = state_____Debug__C__IDLE__IDLE__9__Debug__A__Ac__IDLE__IDLE__9( &message );
        break;
    case Debug__C__IDLE__IDLE__9__Debug__A__En__IDLE:
        currentState = state_____Debug__C__IDLE__IDLE__9__Debug__A__En__IDLE( &message );
        break;
    case Debug__C__IDLE__IDLE__9__boundary:
        currentState = state_____Debug__C__IDLE__IDLE__9__boundary( &message );
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
    default:
        break;
    }
}

void Capsule_Sensor::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Debug__InitDebug( &message );
    currentState = Debug__InitState;
}

const char * Capsule_Sensor::getCurrentStateString() const
{
    return stateNames[currentState];
}





void Capsule_Sensor::save_history( Capsule_Sensor::State compositeState, Capsule_Sensor::State subState )
{
    history[compositeState] = subState;
}

bool Capsule_Sensor::check_history( Capsule_Sensor::State compositeState, Capsule_Sensor::State subState )
{
    return history[compositeState] == subState;
}

void Capsule_Sensor::entryaction_____Debug__C__IDLE__IDLE__9__Debug__A__Ac__IDLE__IDLE__9( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__C__IDLE__IDLE__9::Debug__A__Ac__IDLE__IDLE__9 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__C__IDLE__IDLE__9::Region1::Debug__A__Ac__IDLE__IDLE__9",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE__IDLE__9","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("IDLE","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::entryaction_____Debug__C__IDLE__IDLE__9__Debug__A__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__C__IDLE__IDLE__9::Debug__A__En__IDLE entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__C__IDLE__IDLE__9::Region1::Debug__A__En__IDLE",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::entryaction_____Debug__C__IDLE__IDLE__9__Debug__B__Ac__IDLE__IDLE__9( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__C__IDLE__IDLE__9::Debug__B__Ac__IDLE__IDLE__9 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__C__IDLE__IDLE__9::Region1::Debug__B__Ac__IDLE__IDLE__9",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("IDLE__IDLE__9","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::entryaction_____Debug__C__IDLE__IDLE__9__Debug__B__Ex__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__C__IDLE__IDLE__9::Debug__B__Ex__IDLE entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__C__IDLE__IDLE__9::Region1::Debug__B__Ex__IDLE",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::entryaction_____Debug__C__IDLE__IDLE__9__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Sensor::entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__C__Initial::Debug__A__Ac__Initial entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__C__Initial::Region1::Debug__A__Ac__Initial",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Initial","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("IDLE","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::entryaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__C__Initial::Debug__A__En__Initial entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__C__Initial::Region1::Debug__A__En__Initial",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("IDLE","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__C__Initial::Debug__B__Ac__Initial entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__C__Initial::Region1::Debug__B__Ac__Initial",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("Initial","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::entryaction_____Debug__C__Initial__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Sensor::entryaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__InitState entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::entryaction_____IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::IDLE entry  */
    if( not Debug__SRO.checkDebug("IDLE",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::IDLE",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::exitaction_____Debug__C__IDLE__IDLE__9__Debug__A__Ac__IDLE__IDLE__9( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__C__IDLE__IDLE__9::Debug__A__Ac__IDLE__IDLE__9 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__C__IDLE__IDLE__9::Region1::Debug__A__Ac__IDLE__IDLE__9",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::exitaction_____Debug__C__IDLE__IDLE__9__Debug__A__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__C__IDLE__IDLE__9::Debug__A__En__IDLE exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__C__IDLE__IDLE__9::Region1::Debug__A__En__IDLE",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::exitaction_____Debug__C__IDLE__IDLE__9__Debug__B__Ac__IDLE__IDLE__9( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__C__IDLE__IDLE__9::Debug__B__Ac__IDLE__IDLE__9 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__C__IDLE__IDLE__9::Region1::Debug__B__Ac__IDLE__IDLE__9",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::exitaction_____Debug__C__IDLE__IDLE__9__Debug__B__Ex__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__C__IDLE__IDLE__9::Debug__B__Ex__IDLE exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__C__IDLE__IDLE__9::Region1::Debug__B__Ex__IDLE",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::exitaction_____Debug__C__IDLE__IDLE__9__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Sensor::exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__C__Initial::Debug__A__Ac__Initial exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__C__Initial::Region1::Debug__A__Ac__Initial",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::exitaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__C__Initial::Debug__A__En__Initial exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__C__Initial::Region1::Debug__A__En__Initial",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__C__Initial::Debug__B__Ac__Initial exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__C__Initial::Region1::Debug__B__Ac__Initial",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::exitaction_____Debug__C__Initial__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Sensor::exitaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__InitState exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::exitaction_____IDLE( const UMLRTMessage * msg )
{
    #define umlrtparam_p ( *(const Parcel * )msg->getParam( 0 ) )
    #define rtdata ( (const Parcel * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::IDLE exit  */
    if( not Debug__SRO.checkDebug("IDLE",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::IDLE",(char *)"",(char *)"",(char *)"");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_p
}

void Capsule_Sensor::transitionaction_____Debug__C__IDLE__IDLE__9__Debug__AC__IDLE__IDLE__9( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__C__IDLE__IDLE__9 transition Debug__C__IDLE__IDLE__9::Debug__B__Ac__IDLE__IDLE__9,Debug__C__IDLE__IDLE__9::Debug__A__Ac__IDLE__IDLE__9,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__C__IDLE__IDLE__9::Region1::Debug__AC__IDLE__IDLE__9",(char *)"Debug__B__Ac__IDLE__IDLE__9",(char *)"Debug__A__Ac__IDLE__IDLE__9",(char *)"");
    int reducedNumber = 1; 
    int isOdd = reducedNumber % 2;
    if (isOdd == 0) {
    log.show("At stage %s (%d), turn left.\n", getName(), 1);
    switchProtocol.setSwitch(0).send();
    }
    else {
    log.show("At stage %s (%d), turn right.\n", getName(), 1);
    switchProtocol.setSwitch(1).send();
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::transitionaction_____Debug__C__IDLE__IDLE__9__Debug__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__C__IDLE__IDLE__9 transition Debug__C__IDLE__IDLE__9::Debug__A__Ac__IDLE__IDLE__9,Debug__C__IDLE__IDLE__9::Debug__A__En__IDLE,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__C__IDLE__IDLE__9::Region1::Debug__En__IDLE",(char *)"Debug__A__Ac__IDLE__IDLE__9",(char *)"Debug__A__En__IDLE",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::transitionaction_____Debug__C__IDLE__IDLE__9__Debug__Ex__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__C__IDLE__IDLE__9 transition Debug__C__IDLE__IDLE__9::Debug__B__Ex__IDLE,Debug__C__IDLE__IDLE__9::Debug__B__Ac__IDLE__IDLE__9,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__C__IDLE__IDLE__9::Region1::Debug__Ex__IDLE",(char *)"Debug__B__Ex__IDLE",(char *)"Debug__B__Ac__IDLE__IDLE__9",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::transitionaction_____Debug__C__IDLE__IDLE__9__Debug__end__trans__IDLE__IDLE__9( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__C__IDLE__IDLE__9 transition Debug__C__IDLE__IDLE__9::Debug__A__En__IDLE,Debug__C__IDLE__IDLE__9::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__C__IDLE__IDLE__9::Region1::Debug__end__trans__IDLE__IDLE__9",(char *)"Debug__A__En__IDLE",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::transitionaction_____Debug__C__IDLE__IDLE__9__Debug__init__trans__IDLE__IDLE__9( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__C__IDLE__IDLE__9 transition Debug__C__IDLE__IDLE__9::en,Debug__C__IDLE__IDLE__9::Debug__B__Ex__IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__C__IDLE__IDLE__9::Region1::Debug__init__trans__IDLE__IDLE__9",(char *)"en",(char *)"Debug__B__Ex__IDLE",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::transitionaction_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__C__Initial transition Debug__C__Initial::Debug__B__Ac__Initial,Debug__C__Initial::Debug__A__Ac__Initial,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__C__Initial::Region1::Debug__Ac__Initial",(char *)"Debug__B__Ac__Initial",(char *)"Debug__A__Ac__Initial",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::transitionaction_____Debug__C__Initial__Debug__En__IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__C__Initial transition Debug__C__Initial::Debug__A__Ac__Initial,Debug__C__Initial::Debug__A__En__Initial,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__C__Initial::Region1::Debug__En__IDLE",(char *)"Debug__A__Ac__Initial",(char *)"Debug__A__En__Initial",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::transitionaction_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__C__Initial transition Debug__C__Initial::Debug__A__En__Initial,Debug__C__Initial::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__C__Initial::Region1::Debug__end__trans__Initial",(char *)"Debug__A__En__Initial",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::transitionaction_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor::Debug__C__Initial transition Debug__C__Initial::en,Debug__C__Initial::Debug__B__Ac__Initial */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__C__Initial::Region1::Debug__init__trans__Initial",(char *)"en",(char *)"Debug__B__Ac__Initial",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::transitionaction_____Debug__IDLE__IDLE__9( const UMLRTMessage * msg )
{
    #define umlrtparam_p ( *(const Parcel * )msg->getParam( 0 ) )
    #define rtdata ( (const Parcel * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor transition IDLE,Debug__Path__IDLE__IDLE__9,detect:detection */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__IDLE__IDLE__9",(char *)"IDLE",(char *)"Debug__Path__IDLE__IDLE__9",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_p
}

void Capsule_Sensor::transitionaction_____Debug__IDLE__IDLE__9__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor transition Debug__C__IDLE__IDLE__9::ex,IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__IDLE__IDLE__9__E",(char *)"ex",(char *)"IDLE",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::transitionaction_____Debug__IDLE__IDLE__9__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor transition Debug__Path__IDLE__IDLE__9,Debug__C__IDLE__IDLE__9::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__IDLE__IDLE__9__S",(char *)"Debug__Path__IDLE__IDLE__9",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::transitionaction_____Debug__IDLE__IDLE__9__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor transition Debug__C__IDLE__IDLE__9::new_exitpoint_1,Debug__C__IDLE__IDLE__9 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__IDLE__IDLE__9__dbg",(char *)"Debug__C__IDLE__IDLE__9",(char *)"Debug__C__IDLE__IDLE__9",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::transitionaction_____Debug__InitDebug( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor transition Pseudo10,Debug__InitState */
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

void Capsule_Sensor::transitionaction_____Debug__Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor transition Debug__InitState,Debug__Path__Initial,null:extComm */
    if (this->Debug__SRO.getExecMode()==Stepping){
    Debug__SRO.addTransitionsFromState("IDLE","","IDLE","transmit","transmission");
    Debug__SRO.addTransitionsFromState("GENERATING","","GENERATING","timeout","Timing");
    Debug__SRO.addTransitionsFromState("IDLE","","IDLE","setSwitch","switchProtocol");
    Debug__SRO.addTransitionsFromState("IDLE","reception","OCCUPIED","transmit","transmission");
    Debug__SRO.addTransitionsFromState("OCCUPIED","transmission","IDLE","timeout","Timing");
    Debug__SRO.addTransitionsFromState("","Initial","IDLE","","");
    Debug__SRO.addTransitionsFromState("OCCUPIED","","OCCUPIED","setSwitch","switchProtocol");
    Debug__SRO.addTransitionsFromState("IDLE","","IDLE","detect","detection");
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

void Capsule_Sensor::transitionaction_____Debug__Initial__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor transition Debug__C__Initial::ex,IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__Initial__E",(char *)"ex",(char *)"IDLE",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::transitionaction_____Debug__Initial__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor transition Debug__Path__Initial,Debug__C__Initial::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__Initial__S",(char *)"Debug__Path__Initial",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::transitionaction_____Debug__Initial__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor transition Debug__C__Initial::new_exitpoint_2,Debug__C__Initial */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Debug__Initial__dbg",(char *)"Debug__C__Initial",(char *)"Debug__C__Initial",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::transitionaction_____IDLE__IDLE__9( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor transition Debug__Path__IDLE__IDLE__9,IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::IDLE__IDLE__9",(char *)"Debug__Path__IDLE__IDLE__9",(char *)"IDLE",(char *)"");
    int reducedNumber = 1; 
    int isOdd = reducedNumber % 2;
    if (isOdd == 0) {
    log.show("At stage %s (%d), turn left.\n", getName(), 1);
    switchProtocol.setSwitch(0).send();
    }
    else {
    log.show("At stage %s (%d), turn right.\n", getName(), 2);
    switchProtocol.setSwitch(1).send();
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::transitionaction_____Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor transition Debug__Path__Initial,IDLE */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Sensor::SensorStateMachine::Region::Initial",(char *)"Debug__Path__Initial",(char *)"IDLE",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Sensor::action_____Debug__IDLE__IDLE__9__S__Debug__GuardIDLE__IDLE__9( const UMLRTMessage * msg )
{
    #define umlrtparam_p ( *(const Parcel * )msg->getParam( 0 ) )
    #define rtdata ( (const Parcel * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor guard Debug__Path__IDLE__IDLE__9,Debug__C__IDLE__IDLE__9::en */
    return Debug__SRO.checkDebug("IDLE",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_p
}

bool Capsule_Sensor::action_____Debug__Initial__S__Debug__GuardInitial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-ParcelRouterSimplified/model.uml RootElement::Sensor guard Debug__Path__Initial,Debug__C__Initial::en */
    return Debug__SRO.checkDebug("Pseudo10","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::actionchain_____Debug__C__IDLE__IDLE__9__Debug__AC__IDLE__IDLE__9( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__IDLE__IDLE__9__Debug__B__Ac__IDLE__IDLE__9( msg );
    transitionaction_____Debug__C__IDLE__IDLE__9__Debug__AC__IDLE__IDLE__9( msg );
    entryaction_____Debug__C__IDLE__IDLE__9__Debug__A__Ac__IDLE__IDLE__9( msg );
}

void Capsule_Sensor::actionchain_____Debug__C__IDLE__IDLE__9__Debug__En__IDLE( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__IDLE__IDLE__9__Debug__A__Ac__IDLE__IDLE__9( msg );
    transitionaction_____Debug__C__IDLE__IDLE__9__Debug__En__IDLE( msg );
    entryaction_____Debug__C__IDLE__IDLE__9__Debug__A__En__IDLE( msg );
}

void Capsule_Sensor::actionchain_____Debug__C__IDLE__IDLE__9__Debug__Ex__IDLE( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__IDLE__IDLE__9__Debug__B__Ex__IDLE( msg );
    transitionaction_____Debug__C__IDLE__IDLE__9__Debug__Ex__IDLE( msg );
    entryaction_____Debug__C__IDLE__IDLE__9__Debug__B__Ac__IDLE__IDLE__9( msg );
}

void Capsule_Sensor::actionchain_____Debug__C__IDLE__IDLE__9__Debug__end__trans__IDLE__IDLE__9( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__IDLE__IDLE__9__Debug__A__En__IDLE( msg );
    transitionaction_____Debug__C__IDLE__IDLE__9__Debug__end__trans__IDLE__IDLE__9( msg );
    save_history( Debug__C__IDLE__IDLE__9, Debug__C__IDLE__IDLE__9__Debug__A__En__IDLE );
}

void Capsule_Sensor::actionchain_____Debug__C__IDLE__IDLE__9__Debug__init__trans__IDLE__IDLE__9( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__IDLE__IDLE__9__Debug__init__trans__IDLE__IDLE__9( msg );
    entryaction_____Debug__C__IDLE__IDLE__9__Debug__B__Ex__IDLE( msg );
}

void Capsule_Sensor::actionchain_____Debug__C__IDLE__IDLE__9__new_transition_1( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__IDLE__IDLE__9__Debug__B__Ex__IDLE( msg );
}

void Capsule_Sensor::actionchain_____Debug__C__IDLE__IDLE__9__new_transition_10( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__IDLE__IDLE__9__boundary( msg );
    save_history( Debug__C__IDLE__IDLE__9, Debug__C__IDLE__IDLE__9__boundary );
}

void Capsule_Sensor::actionchain_____Debug__C__IDLE__IDLE__9__new_transition_2( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__IDLE__IDLE__9__Debug__B__Ac__IDLE__IDLE__9( msg );
}

void Capsule_Sensor::actionchain_____Debug__C__IDLE__IDLE__9__new_transition_3( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__IDLE__IDLE__9__Debug__A__Ac__IDLE__IDLE__9( msg );
}

void Capsule_Sensor::actionchain_____Debug__C__IDLE__IDLE__9__new_transition_4( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__IDLE__IDLE__9__Debug__A__En__IDLE( msg );
}

void Capsule_Sensor::actionchain_____Debug__C__IDLE__IDLE__9__new_transition_5_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__IDLE__IDLE__9__boundary( msg );
}

void Capsule_Sensor::actionchain_____Debug__C__IDLE__IDLE__9__new_transition_6( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__IDLE__IDLE__9__Debug__B__Ex__IDLE( msg );
    save_history( Debug__C__IDLE__IDLE__9, Debug__C__IDLE__IDLE__9__Debug__B__Ex__IDLE );
}

void Capsule_Sensor::actionchain_____Debug__C__IDLE__IDLE__9__new_transition_7( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__IDLE__IDLE__9__Debug__B__Ac__IDLE__IDLE__9( msg );
    save_history( Debug__C__IDLE__IDLE__9, Debug__C__IDLE__IDLE__9__Debug__B__Ac__IDLE__IDLE__9 );
}

void Capsule_Sensor::actionchain_____Debug__C__IDLE__IDLE__9__new_transition_8( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__IDLE__IDLE__9__Debug__A__Ac__IDLE__IDLE__9( msg );
    save_history( Debug__C__IDLE__IDLE__9, Debug__C__IDLE__IDLE__9__Debug__A__Ac__IDLE__IDLE__9 );
}

void Capsule_Sensor::actionchain_____Debug__C__IDLE__IDLE__9__new_transition_9( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__IDLE__IDLE__9__Debug__A__En__IDLE( msg );
    save_history( Debug__C__IDLE__IDLE__9, Debug__C__IDLE__IDLE__9__Debug__A__En__IDLE );
}

void Capsule_Sensor::actionchain_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    transitionaction_____Debug__C__Initial__Debug__Ac__Initial( msg );
    entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
}

void Capsule_Sensor::actionchain_____Debug__C__Initial__Debug__En__IDLE( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    transitionaction_____Debug__C__Initial__Debug__En__IDLE( msg );
    entryaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
}

void Capsule_Sensor::actionchain_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    transitionaction_____Debug__C__Initial__Debug__end__trans__Initial( msg );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Sensor::actionchain_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__Initial__Debug__init__trans__Initial( msg );
    entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
}

void Capsule_Sensor::actionchain_____Debug__C__Initial__new_transition_11( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
}

void Capsule_Sensor::actionchain_____Debug__C__Initial__new_transition_12( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
}

void Capsule_Sensor::actionchain_____Debug__C__Initial__new_transition_13( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
}

void Capsule_Sensor::actionchain_____Debug__C__Initial__new_transition_14_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__Initial__boundary( msg );
}

void Capsule_Sensor::actionchain_____Debug__C__Initial__new_transition_15( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( msg );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial );
}

void Capsule_Sensor::actionchain_____Debug__C__Initial__new_transition_16( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( msg );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial );
}

void Capsule_Sensor::actionchain_____Debug__C__Initial__new_transition_17( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__Debug__A__En__Initial( msg );
    save_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial );
}

void Capsule_Sensor::actionchain_____Debug__C__Initial__new_transition_18( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__boundary( msg );
    save_history( Debug__C__Initial, Debug__C__Initial__boundary );
}

void Capsule_Sensor::actionchain_____Debug__IDLE__IDLE__9( const UMLRTMessage * msg )
{
    exitaction_____IDLE( msg );
    transitionaction_____Debug__IDLE__IDLE__9( msg );
}

void Capsule_Sensor::actionchain_____Debug__IDLE__IDLE__9__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__IDLE__IDLE__9__boundary( msg );
    transitionaction_____Debug__IDLE__IDLE__9__E( msg );
    entryaction_____IDLE( msg );
}

void Capsule_Sensor::actionchain_____Debug__IDLE__IDLE__9__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__IDLE__IDLE__9__S( msg );
    entryaction_____Debug__C__IDLE__IDLE__9__boundary( msg );
}

void Capsule_Sensor::actionchain_____Debug__IDLE__IDLE__9__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__IDLE__IDLE__9__boundary( msg );
    transitionaction_____Debug__IDLE__IDLE__9__dbg( msg );
    entryaction_____Debug__C__IDLE__IDLE__9__boundary( msg );
}

void Capsule_Sensor::actionchain_____Debug__InitDebug( const UMLRTMessage * msg )
{
    transitionaction_____Debug__InitDebug( msg );
    entryaction_____Debug__InitState( msg );
}

void Capsule_Sensor::actionchain_____Debug__Initial( const UMLRTMessage * msg )
{
    exitaction_____Debug__InitState( msg );
    transitionaction_____Debug__Initial( msg );
}

void Capsule_Sensor::actionchain_____Debug__Initial__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__boundary( msg );
    transitionaction_____Debug__Initial__E( msg );
    entryaction_____IDLE( msg );
}

void Capsule_Sensor::actionchain_____Debug__Initial__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__Initial__S( msg );
    entryaction_____Debug__C__Initial__boundary( msg );
}

void Capsule_Sensor::actionchain_____Debug__Initial__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__Initial__boundary( msg );
    transitionaction_____Debug__Initial__dbg( msg );
    entryaction_____Debug__C__Initial__boundary( msg );
}

void Capsule_Sensor::actionchain_____IDLE__IDLE__9( const UMLRTMessage * msg )
{
    transitionaction_____IDLE__IDLE__9( msg );
    entryaction_____IDLE( msg );
}

void Capsule_Sensor::actionchain_____Initial( const UMLRTMessage * msg )
{
    transitionaction_____Initial( msg );
    entryaction_____IDLE( msg );
}

Capsule_Sensor::State Capsule_Sensor::junction_____Debug__C__IDLE__IDLE__9__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__IDLE__IDLE__9__Debug__init__trans__IDLE__IDLE__9( msg );
    return Debug__C__IDLE__IDLE__9__Debug__B__Ex__IDLE;
}

Capsule_Sensor::State Capsule_Sensor::junction_____Debug__C__IDLE__IDLE__9__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__IDLE__IDLE__9__E( msg );
    return IDLE;
}

Capsule_Sensor::State Capsule_Sensor::junction_____Debug__C__IDLE__IDLE__9__new_exitpoint_1( const UMLRTMessage * msg )
{
    actionchain_____Debug__IDLE__IDLE__9__dbg( msg );
    return choice_____Debug__C__IDLE__IDLE__9__deephistory( msg );
}

Capsule_Sensor::State Capsule_Sensor::junction_____Debug__C__Initial__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__Initial__Debug__init__trans__Initial( msg );
    return Debug__C__Initial__Debug__B__Ac__Initial;
}

Capsule_Sensor::State Capsule_Sensor::junction_____Debug__C__Initial__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__E( msg );
    return IDLE;
}

Capsule_Sensor::State Capsule_Sensor::junction_____Debug__C__Initial__new_exitpoint_2( const UMLRTMessage * msg )
{
    actionchain_____Debug__Initial__dbg( msg );
    return choice_____Debug__C__Initial__deephistory( msg );
}

Capsule_Sensor::State Capsule_Sensor::choice_____Debug__C__IDLE__IDLE__9__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__IDLE__IDLE__9, Debug__C__IDLE__IDLE__9__Debug__B__Ex__IDLE ) )
    {
        actionchain_____Debug__C__IDLE__IDLE__9__new_transition_1( msg );
        return Debug__C__IDLE__IDLE__9__Debug__B__Ex__IDLE;
    }
    else if( check_history( Debug__C__IDLE__IDLE__9, Debug__C__IDLE__IDLE__9__Debug__B__Ac__IDLE__IDLE__9 ) )
    {
        actionchain_____Debug__C__IDLE__IDLE__9__new_transition_2( msg );
        return Debug__C__IDLE__IDLE__9__Debug__B__Ac__IDLE__IDLE__9;
    }
    else if( check_history( Debug__C__IDLE__IDLE__9, Debug__C__IDLE__IDLE__9__Debug__A__Ac__IDLE__IDLE__9 ) )
    {
        actionchain_____Debug__C__IDLE__IDLE__9__new_transition_3( msg );
        return Debug__C__IDLE__IDLE__9__Debug__A__Ac__IDLE__IDLE__9;
    }
    else if( check_history( Debug__C__IDLE__IDLE__9, Debug__C__IDLE__IDLE__9__Debug__A__En__IDLE ) )
    {
        actionchain_____Debug__C__IDLE__IDLE__9__new_transition_4( msg );
        return Debug__C__IDLE__IDLE__9__Debug__A__En__IDLE;
    }
    else if( check_history( Debug__C__IDLE__IDLE__9, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__IDLE__IDLE__9__new_transition_5_to_boundary( msg );
        return Debug__C__IDLE__IDLE__9__boundary;
    }
    return currentState;
}

Capsule_Sensor::State Capsule_Sensor::choice_____Debug__C__Initial__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__Initial, Debug__C__Initial__Debug__B__Ac__Initial ) )
    {
        actionchain_____Debug__C__Initial__new_transition_11( msg );
        return Debug__C__Initial__Debug__B__Ac__Initial;
    }
    else if( check_history( Debug__C__Initial, Debug__C__Initial__Debug__A__Ac__Initial ) )
    {
        actionchain_____Debug__C__Initial__new_transition_12( msg );
        return Debug__C__Initial__Debug__A__Ac__Initial;
    }
    else if( check_history( Debug__C__Initial, Debug__C__Initial__Debug__A__En__Initial ) )
    {
        actionchain_____Debug__C__Initial__new_transition_13( msg );
        return Debug__C__Initial__Debug__A__En__Initial;
    }
    else if( check_history( Debug__C__Initial, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__Initial__new_transition_14_to_boundary( msg );
        return Debug__C__Initial__boundary;
    }
    return currentState;
}

Capsule_Sensor::State Capsule_Sensor::choice_____Debug__Path__IDLE__IDLE__9( const UMLRTMessage * msg )
{
    if( action_____Debug__IDLE__IDLE__9__S__Debug__GuardIDLE__IDLE__9( msg ) )
    {
        actionchain_____Debug__IDLE__IDLE__9__S( msg );
        return junction_____Debug__C__IDLE__IDLE__9__en( msg );
    }
    else
    {
        actionchain_____IDLE__IDLE__9( msg );
        return IDLE;
    }
    return currentState;
}

Capsule_Sensor::State Capsule_Sensor::choice_____Debug__Path__Initial( const UMLRTMessage * msg )
{
    if( action_____Debug__Initial__S__Debug__GuardInitial( msg ) )
    {
        actionchain_____Debug__Initial__S( msg );
        return junction_____Debug__C__Initial__en( msg );
    }
    else
    {
        actionchain_____Initial( msg );
        return IDLE;
    }
    return currentState;
}

Capsule_Sensor::State Capsule_Sensor::state_____Debug__C__IDLE__IDLE__9__Debug__A__Ac__IDLE__IDLE__9( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__IDLE__IDLE__9__Debug__En__IDLE( msg );
            return Debug__C__IDLE__IDLE__9__Debug__A__En__IDLE;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__IDLE__IDLE__9__new_transition_8( msg );
            return junction_____Debug__C__IDLE__IDLE__9__new_exitpoint_1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Sensor::State Capsule_Sensor::state_____Debug__C__IDLE__IDLE__9__Debug__A__En__IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__IDLE__IDLE__9__Debug__end__trans__IDLE__IDLE__9( msg );
            return junction_____Debug__C__IDLE__IDLE__9__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__IDLE__IDLE__9__new_transition_9( msg );
            return junction_____Debug__C__IDLE__IDLE__9__new_exitpoint_1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Sensor::State Capsule_Sensor::state_____Debug__C__IDLE__IDLE__9__Debug__B__Ac__IDLE__IDLE__9( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__IDLE__IDLE__9__Debug__AC__IDLE__IDLE__9( msg );
            return Debug__C__IDLE__IDLE__9__Debug__A__Ac__IDLE__IDLE__9;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__IDLE__IDLE__9__new_transition_7( msg );
            return junction_____Debug__C__IDLE__IDLE__9__new_exitpoint_1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Sensor::State Capsule_Sensor::state_____Debug__C__IDLE__IDLE__9__Debug__B__Ex__IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__IDLE__IDLE__9__Debug__Ex__IDLE( msg );
            return Debug__C__IDLE__IDLE__9__Debug__B__Ac__IDLE__IDLE__9;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__IDLE__IDLE__9__new_transition_6( msg );
            return junction_____Debug__C__IDLE__IDLE__9__new_exitpoint_1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Sensor::State Capsule_Sensor::state_____Debug__C__IDLE__IDLE__9__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__IDLE__IDLE__9__new_transition_10( msg );
            return junction_____Debug__C__IDLE__IDLE__9__new_exitpoint_1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Sensor::State Capsule_Sensor::state_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__Initial__Debug__En__IDLE( msg );
            return Debug__C__Initial__Debug__A__En__Initial;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Initial__new_transition_16( msg );
            return junction_____Debug__C__Initial__new_exitpoint_2( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Sensor::State Capsule_Sensor::state_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg )
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
            actionchain_____Debug__C__Initial__new_transition_17( msg );
            return junction_____Debug__C__Initial__new_exitpoint_2( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Sensor::State Capsule_Sensor::state_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg )
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
            actionchain_____Debug__C__Initial__new_transition_15( msg );
            return junction_____Debug__C__Initial__new_exitpoint_2( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Sensor::State Capsule_Sensor::state_____Debug__C__Initial__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__Initial__new_transition_18( msg );
            return junction_____Debug__C__Initial__new_exitpoint_2( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Sensor::State Capsule_Sensor::state_____Debug__InitState( const UMLRTMessage * msg )
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

Capsule_Sensor::State Capsule_Sensor::state_____IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_detection:
        switch( msg->getSignalId() )
        {
        case detection::signal_detect:
            actionchain_____Debug__IDLE__IDLE__9( msg );
            return choice_____Debug__Path__IDLE__IDLE__9( msg );
        default:
            this->unexpectedMessage();
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
        Capsule_Sensor::port_detection,
        "detection",
        "detection",
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
        Capsule_Sensor::port_switchProtocol,
        "switchProtocol",
        "switchProtocol",
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
        Capsule_Sensor::port_extComm,
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
        Capsule_Sensor::port_log,
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

static void instantiate_Sensor( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_Sensor( &Sensor, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Sensor = 
{
    "Sensor",
    NULL,
    instantiate_Sensor,
    0,
    NULL,
    4,
    portroles_border,
    0,
    NULL
};

