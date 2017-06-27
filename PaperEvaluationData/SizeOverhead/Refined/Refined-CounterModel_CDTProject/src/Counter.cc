
#include "Counter.hh"

#include "ExtInterface.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include "umlrttimerprotocol.hh"
#include <cstddef>
#include "umlrtcapsuleclass.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_Counter::Capsule_Counter( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
, extComm( borderPorts[borderport_extComm] )
, timer1( borderPorts[borderport_timer1] )
{
    stateNames[Debug__C__intittrans] = "Debug__C__intittrans";
    stateNames[Debug__C__trans1] = "Debug__C__trans1";
    stateNames[Debug__C__intittrans__Debug__A__Ac__intittrans] = "Debug__C__intittrans__Debug__A__Ac__intittrans";
    stateNames[Debug__C__intittrans__Debug__A__En__intittrans] = "Debug__C__intittrans__Debug__A__En__intittrans";
    stateNames[Debug__C__intittrans__Debug__B__Ac__intittrans] = "Debug__C__intittrans__Debug__B__Ac__intittrans";
    stateNames[Debug__C__intittrans__boundary] = "Debug__C__intittrans__boundary";
    stateNames[Debug__C__trans1__Debug__A__Ac__trans1] = "Debug__C__trans1__Debug__A__Ac__trans1";
    stateNames[Debug__C__trans1__Debug__A__En__State1] = "Debug__C__trans1__Debug__A__En__State1";
    stateNames[Debug__C__trans1__Debug__B__Ac__trans1] = "Debug__C__trans1__Debug__B__Ac__trans1";
    stateNames[Debug__C__trans1__Debug__B__Ex__State1] = "Debug__C__trans1__Debug__B__Ex__State1";
    stateNames[Debug__C__trans1__boundary] = "Debug__C__trans1__boundary";
    stateNames[Debug__InitState] = "Debug__InitState";
    stateNames[State1] = "State1";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
    int i = 0;
    while( i < 2 )
        history[i++] = SPECIAL_INTERNAL_STATE_UNVISITED;
}


void Capsule_Counter::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case State1:
        currentState = state_____State1( &message );
        break;
    case Debug__InitState:
        currentState = state_____Debug__InitState( &message );
        break;
    case Debug__C__intittrans__Debug__B__Ac__intittrans:
        currentState = state_____Debug__C__intittrans__Debug__B__Ac__intittrans( &message );
        break;
    case Debug__C__intittrans__Debug__A__Ac__intittrans:
        currentState = state_____Debug__C__intittrans__Debug__A__Ac__intittrans( &message );
        break;
    case Debug__C__intittrans__Debug__A__En__intittrans:
        currentState = state_____Debug__C__intittrans__Debug__A__En__intittrans( &message );
        break;
    case Debug__C__intittrans__boundary:
        currentState = state_____Debug__C__intittrans__boundary( &message );
        break;
    case Debug__C__trans1__Debug__B__Ex__State1:
        currentState = state_____Debug__C__trans1__Debug__B__Ex__State1( &message );
        break;
    case Debug__C__trans1__Debug__B__Ac__trans1:
        currentState = state_____Debug__C__trans1__Debug__B__Ac__trans1( &message );
        break;
    case Debug__C__trans1__Debug__A__Ac__trans1:
        currentState = state_____Debug__C__trans1__Debug__A__Ac__trans1( &message );
        break;
    case Debug__C__trans1__Debug__A__En__State1:
        currentState = state_____Debug__C__trans1__Debug__A__En__State1( &message );
        break;
    case Debug__C__trans1__boundary:
        currentState = state_____Debug__C__trans1__boundary( &message );
        break;
    default:
        break;
    }
}

void Capsule_Counter::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Debug__InitDebug( &message );
    currentState = Debug__InitState;
}

const char * Capsule_Counter::getCurrentStateString() const
{
    return stateNames[currentState];
}





void Capsule_Counter::save_history( Capsule_Counter::State compositeState, Capsule_Counter::State subState )
{
    history[compositeState] = subState;
}

bool Capsule_Counter::check_history( Capsule_Counter::State compositeState, Capsule_Counter::State subState )
{
    return history[compositeState] == subState;
}

void Capsule_Counter::entryaction_____Debug__C__intittrans__Debug__A__Ac__intittrans( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__C__intittrans::Debug__A__Ac__intittrans entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__C__intittrans::Region1::Debug__A__Ac__intittrans",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("intittrans","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("State1","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::entryaction_____Debug__C__intittrans__Debug__A__En__intittrans( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__C__intittrans::Debug__A__En__intittrans entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__C__intittrans::Region1::Debug__A__En__intittrans",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("State1","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::entryaction_____Debug__C__intittrans__Debug__B__Ac__intittrans( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__C__intittrans::Debug__B__Ac__intittrans entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__C__intittrans::Region1::Debug__B__Ac__intittrans",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("intittrans","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::entryaction_____Debug__C__intittrans__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Counter::entryaction_____Debug__C__trans1__Debug__A__Ac__trans1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__C__trans1::Debug__A__Ac__trans1 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__C__trans1::Region1::Debug__A__Ac__trans1",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("trans1","","",3,TransitionEffectBreakPoint,1) or Debug__SRO.checkDebug("State1","","",4,StateEntryBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::entryaction_____Debug__C__trans1__Debug__A__En__State1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__C__trans1::Debug__A__En__State1 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__C__trans1::Region1::Debug__A__En__State1",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("State1","","",4,StateEntryBreakPoint,1))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::entryaction_____Debug__C__trans1__Debug__B__Ac__trans1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__C__trans1::Debug__B__Ac__trans1 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__C__trans1::Region1::Debug__B__Ac__trans1",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("State1","","",2,StateExitBreakPoint,1) or Debug__SRO.checkDebug("trans1","","",3,TransitionEffectBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::entryaction_____Debug__C__trans1__Debug__B__Ex__State1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__C__trans1::Debug__B__Ex__State1 entry  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__C__trans1::Region1::Debug__B__Ex__State1",(char *)"",(char *)"",(char *)"");
    if (not(Debug__SRO.checkDebug("State1","","",2,StateExitBreakPoint,0))){
    extComm.selfExec().send();}
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::entryaction_____Debug__C__trans1__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Counter::entryaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__InitState entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::entryaction_____State1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::State1 entry  */
    if( not Debug__SRO.checkDebug("State1",msg->destPort->role()->protocol,msg->getSignalName(),5,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEENTRYSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::State1",(char *)"",(char *)"",(char *)"");
    std::cout<<"State 1 is vistited\n";
    std::cout<<"Counter is "<<counter<<"\n";
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::exitaction_____Debug__C__intittrans__Debug__A__Ac__intittrans( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__C__intittrans::Debug__A__Ac__intittrans exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__C__intittrans::Region1::Debug__A__Ac__intittrans",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::exitaction_____Debug__C__intittrans__Debug__A__En__intittrans( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__C__intittrans::Debug__A__En__intittrans exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__C__intittrans::Region1::Debug__A__En__intittrans",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::exitaction_____Debug__C__intittrans__Debug__B__Ac__intittrans( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__C__intittrans::Debug__B__Ac__intittrans exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__C__intittrans::Region1::Debug__B__Ac__intittrans",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::exitaction_____Debug__C__intittrans__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Counter::exitaction_____Debug__C__trans1__Debug__A__Ac__trans1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__C__trans1::Debug__A__Ac__trans1 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__C__trans1::Region1::Debug__A__Ac__trans1",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::exitaction_____Debug__C__trans1__Debug__A__En__State1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__C__trans1::Debug__A__En__State1 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__C__trans1::Region1::Debug__A__En__State1",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::exitaction_____Debug__C__trans1__Debug__B__Ac__trans1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__C__trans1::Debug__B__Ac__trans1 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__C__trans1::Region1::Debug__B__Ac__trans1",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::exitaction_____Debug__C__trans1__Debug__B__Ex__State1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__C__trans1::Debug__B__Ex__State1 exit  */
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__C__trans1::Region1::Debug__B__Ex__State1",(char *)"",(char *)"",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::exitaction_____Debug__C__trans1__boundary( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    #undef rtdata
}

void Capsule_Counter::exitaction_____Debug__InitState( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__InitState exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::exitaction_____State1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::State1 exit  */
    if( not Debug__SRO.checkDebug("State1",msg->destPort->role()->protocol,msg->getSignalName(),0,StateExitBreakPoint,0)) {
    Debug__sendEvent(debugEvents::STATE,debugEvents::STATEEXITSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::State1",(char *)"",(char *)"",(char *)"");
    std::cout<<"State 1 exit is running\n";
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::transitionaction_____Debug__C__intittrans__Debug__Ac__intittrans( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__C__intittrans transition Debug__C__intittrans::Debug__B__Ac__intittrans,Debug__C__intittrans::Debug__A__Ac__intittrans,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__C__intittrans::Region1::Debug__Ac__intittrans",(char *)"Debug__B__Ac__intittrans",(char *)"Debug__A__Ac__intittrans",(char *)"");
    std::cout<<"Capsule is started\n"; 
    timer1.informEvery(UMLRTTimespec(3,1));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::transitionaction_____Debug__C__intittrans__Debug__En__State1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__C__intittrans transition Debug__C__intittrans::Debug__A__Ac__intittrans,Debug__C__intittrans::Debug__A__En__intittrans,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__C__intittrans::Region1::Debug__En__State1",(char *)"Debug__A__Ac__intittrans",(char *)"Debug__A__En__intittrans",(char *)"");
    std::cout<<"State 1 is vistited\n";
    std::cout<<"Counter is "<<counter<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::transitionaction_____Debug__C__intittrans__Debug__end__trans__intittrans( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__C__intittrans transition Debug__C__intittrans::Debug__A__En__intittrans,Debug__C__intittrans::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__C__intittrans::Region1::Debug__end__trans__intittrans",(char *)"Debug__A__En__intittrans",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::transitionaction_____Debug__C__intittrans__Debug__init__trans__intittrans( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__C__intittrans transition Debug__C__intittrans::en,Debug__C__intittrans::Debug__B__Ac__intittrans */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__C__intittrans::Region1::Debug__init__trans__intittrans",(char *)"en",(char *)"Debug__B__Ac__intittrans",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::transitionaction_____Debug__C__trans1__Debug__AC__trans1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__C__trans1 transition Debug__C__trans1::Debug__B__Ac__trans1,Debug__C__trans1::Debug__A__Ac__trans1,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__C__trans1::Region1::Debug__AC__trans1",(char *)"Debug__B__Ac__trans1",(char *)"Debug__A__Ac__trans1",(char *)"");
    counter=counter+1;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::transitionaction_____Debug__C__trans1__Debug__En__State1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__C__trans1 transition Debug__C__trans1::Debug__A__Ac__trans1,Debug__C__trans1::Debug__A__En__State1,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__C__trans1::Region1::Debug__En__State1",(char *)"Debug__A__Ac__trans1",(char *)"Debug__A__En__State1",(char *)"");
    std::cout<<"State 1 is vistited\n";
    std::cout<<"Counter is "<<counter<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::transitionaction_____Debug__C__trans1__Debug__Ex__State1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__C__trans1 transition Debug__C__trans1::Debug__B__Ex__State1,Debug__C__trans1::Debug__B__Ac__trans1,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__C__trans1::Region1::Debug__Ex__State1",(char *)"Debug__B__Ex__State1",(char *)"Debug__B__Ac__trans1",(char *)"");
    std::cout<<"State 1 exit is running\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::transitionaction_____Debug__C__trans1__Debug__end__trans__trans1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__C__trans1 transition Debug__C__trans1::Debug__A__En__State1,Debug__C__trans1::ex,dbgExec:extComm */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__C__trans1::Region1::Debug__end__trans__trans1",(char *)"Debug__A__En__State1",(char *)"ex",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::transitionaction_____Debug__C__trans1__Debug__init__trans__trans1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter::Debug__C__trans1 transition Debug__C__trans1::en,Debug__C__trans1::Debug__B__Ex__State1 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__C__trans1::Region1::Debug__init__trans__trans1",(char *)"en",(char *)"Debug__B__Ex__State1",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::transitionaction_____Debug__InitDebug( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter transition Initial1,Debug__InitState */
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

void Capsule_Counter::transitionaction_____Debug__intittrans( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter transition Debug__InitState,Debug__Path__intittrans,null:extComm */
    if (this->Debug__SRO.getExecMode()==Stepping){
    Debug__SRO.addTransitionsFromState("State1","trans1","State1","timeout","Timing");
    Debug__SRO.addTransitionsFromState("Initial1","intittrans","State1","","");
    std::cout<<this->getName()<<": Connection with debugger is in progress\n";
    char  tempS[256];
    sprintf(tempS,"%s%d",this->getName(),(int)this->getIndex());
    extComm.registerToControl(tempS).send();
    Debug__sendEvent(debugEvents::DEBUG,debugEvents::REGISTER,this->getName(),this->getIndex(),msg->getSignalName(),(char *) "",(char *) "",(char *) "",(char *)"",(char *) "");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::transitionaction_____Debug__intittrans__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter transition Debug__C__intittrans::ex,State1 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__intittrans__E",(char *)"ex",(char *)"State1",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::transitionaction_____Debug__intittrans__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter transition Debug__Path__intittrans,Debug__C__intittrans::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__intittrans__S",(char *)"Debug__Path__intittrans",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::transitionaction_____Debug__intittrans__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter transition Debug__C__intittrans::new_exitpoint_1,Debug__C__intittrans */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__intittrans__dbg",(char *)"Debug__C__intittrans",(char *)"Debug__C__intittrans",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::transitionaction_____Debug__trans1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter transition State1,Debug__Path__trans1,timeout:timer1 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__trans1",(char *)"State1",(char *)"Debug__Path__trans1",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::transitionaction_____Debug__trans1__E( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter transition Debug__C__trans1::ex,State1 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__trans1__E",(char *)"ex",(char *)"State1",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::transitionaction_____Debug__trans1__S( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter transition Debug__Path__trans1,Debug__C__trans1::en */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__trans1__S",(char *)"Debug__Path__trans1",(char *)"en",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::transitionaction_____Debug__trans1__dbg( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter transition Debug__C__trans1::new_exitpoint_2,Debug__C__trans1 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::Debug__trans1__dbg",(char *)"Debug__C__trans1",(char *)"Debug__C__trans1",(char *)"");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::transitionaction_____intittrans( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter transition Debug__Path__intittrans,State1 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::intittrans",(char *)"Debug__Path__intittrans",(char *)"State1",(char *)"");
    std::cout<<"Capsule is started\n"; 
    timer1.informEvery(UMLRTTimespec(3,1));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::transitionaction_____trans1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter transition Debug__Path__trans1,State1 */
    Debug__sendEvent(debugEvents::TRANISTION,debugEvents::TRANISTIONSTART,this->getName(),this->getIndex(),msg->getSignalName(),(char *)"",(char *)"RootElement::Counter::StateMachine1::Region1::trans1",(char *)"Debug__Path__trans1",(char *)"State1",(char *)"");
    counter=counter+1;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Counter::action_____Debug__intittrans__S__Debug__Guardintittrans( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter guard Debug__Path__intittrans,Debug__C__intittrans::en */
    return Debug__SRO.checkDebug("Initial1","","",1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Counter::action_____Debug__trans1__S__Debug__Guardtrans1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter guard Debug__Path__trans1,Debug__C__trans1::en */
    return Debug__SRO.checkDebug("State1",msg->destPort->role()->protocol,msg->getSignalName(),1,TransitionEffectBreakPoint,0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::actionchain_____Debug__C__intittrans__Debug__Ac__intittrans( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__intittrans__Debug__B__Ac__intittrans( msg );
    transitionaction_____Debug__C__intittrans__Debug__Ac__intittrans( msg );
    entryaction_____Debug__C__intittrans__Debug__A__Ac__intittrans( msg );
}

void Capsule_Counter::actionchain_____Debug__C__intittrans__Debug__En__State1( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__intittrans__Debug__A__Ac__intittrans( msg );
    transitionaction_____Debug__C__intittrans__Debug__En__State1( msg );
    entryaction_____Debug__C__intittrans__Debug__A__En__intittrans( msg );
}

void Capsule_Counter::actionchain_____Debug__C__intittrans__Debug__end__trans__intittrans( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__intittrans__Debug__A__En__intittrans( msg );
    transitionaction_____Debug__C__intittrans__Debug__end__trans__intittrans( msg );
    save_history( Debug__C__intittrans, Debug__C__intittrans__Debug__A__En__intittrans );
}

void Capsule_Counter::actionchain_____Debug__C__intittrans__Debug__init__trans__intittrans( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__intittrans__Debug__init__trans__intittrans( msg );
    entryaction_____Debug__C__intittrans__Debug__B__Ac__intittrans( msg );
}

void Capsule_Counter::actionchain_____Debug__C__intittrans__new_transition_1( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__intittrans__Debug__B__Ac__intittrans( msg );
}

void Capsule_Counter::actionchain_____Debug__C__intittrans__new_transition_2( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__intittrans__Debug__A__Ac__intittrans( msg );
}

void Capsule_Counter::actionchain_____Debug__C__intittrans__new_transition_3( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__intittrans__Debug__A__En__intittrans( msg );
}

void Capsule_Counter::actionchain_____Debug__C__intittrans__new_transition_4_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__intittrans__boundary( msg );
}

void Capsule_Counter::actionchain_____Debug__C__intittrans__new_transition_5( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__intittrans__Debug__B__Ac__intittrans( msg );
    save_history( Debug__C__intittrans, Debug__C__intittrans__Debug__B__Ac__intittrans );
}

void Capsule_Counter::actionchain_____Debug__C__intittrans__new_transition_6( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__intittrans__Debug__A__Ac__intittrans( msg );
    save_history( Debug__C__intittrans, Debug__C__intittrans__Debug__A__Ac__intittrans );
}

void Capsule_Counter::actionchain_____Debug__C__intittrans__new_transition_7( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__intittrans__Debug__A__En__intittrans( msg );
    save_history( Debug__C__intittrans, Debug__C__intittrans__Debug__A__En__intittrans );
}

void Capsule_Counter::actionchain_____Debug__C__intittrans__new_transition_8( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__intittrans__boundary( msg );
    save_history( Debug__C__intittrans, Debug__C__intittrans__boundary );
}

void Capsule_Counter::actionchain_____Debug__C__trans1__Debug__AC__trans1( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__trans1__Debug__B__Ac__trans1( msg );
    transitionaction_____Debug__C__trans1__Debug__AC__trans1( msg );
    entryaction_____Debug__C__trans1__Debug__A__Ac__trans1( msg );
}

void Capsule_Counter::actionchain_____Debug__C__trans1__Debug__En__State1( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__trans1__Debug__A__Ac__trans1( msg );
    transitionaction_____Debug__C__trans1__Debug__En__State1( msg );
    entryaction_____Debug__C__trans1__Debug__A__En__State1( msg );
}

void Capsule_Counter::actionchain_____Debug__C__trans1__Debug__Ex__State1( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__trans1__Debug__B__Ex__State1( msg );
    transitionaction_____Debug__C__trans1__Debug__Ex__State1( msg );
    entryaction_____Debug__C__trans1__Debug__B__Ac__trans1( msg );
}

void Capsule_Counter::actionchain_____Debug__C__trans1__Debug__end__trans__trans1( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__trans1__Debug__A__En__State1( msg );
    transitionaction_____Debug__C__trans1__Debug__end__trans__trans1( msg );
    save_history( Debug__C__trans1, Debug__C__trans1__Debug__A__En__State1 );
}

void Capsule_Counter::actionchain_____Debug__C__trans1__Debug__init__trans__trans1( const UMLRTMessage * msg )
{
    transitionaction_____Debug__C__trans1__Debug__init__trans__trans1( msg );
    entryaction_____Debug__C__trans1__Debug__B__Ex__State1( msg );
}

void Capsule_Counter::actionchain_____Debug__C__trans1__new_transition_10( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__trans1__Debug__B__Ac__trans1( msg );
}

void Capsule_Counter::actionchain_____Debug__C__trans1__new_transition_11( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__trans1__Debug__A__Ac__trans1( msg );
}

void Capsule_Counter::actionchain_____Debug__C__trans1__new_transition_12( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__trans1__Debug__A__En__State1( msg );
}

void Capsule_Counter::actionchain_____Debug__C__trans1__new_transition_13_to_boundary( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__trans1__boundary( msg );
}

void Capsule_Counter::actionchain_____Debug__C__trans1__new_transition_14( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__trans1__Debug__B__Ex__State1( msg );
    save_history( Debug__C__trans1, Debug__C__trans1__Debug__B__Ex__State1 );
}

void Capsule_Counter::actionchain_____Debug__C__trans1__new_transition_15( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__trans1__Debug__B__Ac__trans1( msg );
    save_history( Debug__C__trans1, Debug__C__trans1__Debug__B__Ac__trans1 );
}

void Capsule_Counter::actionchain_____Debug__C__trans1__new_transition_16( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__trans1__Debug__A__Ac__trans1( msg );
    save_history( Debug__C__trans1, Debug__C__trans1__Debug__A__Ac__trans1 );
}

void Capsule_Counter::actionchain_____Debug__C__trans1__new_transition_17( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__trans1__Debug__A__En__State1( msg );
    save_history( Debug__C__trans1, Debug__C__trans1__Debug__A__En__State1 );
}

void Capsule_Counter::actionchain_____Debug__C__trans1__new_transition_18( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__trans1__boundary( msg );
    save_history( Debug__C__trans1, Debug__C__trans1__boundary );
}

void Capsule_Counter::actionchain_____Debug__C__trans1__new_transition_9( const UMLRTMessage * msg )
{
    entryaction_____Debug__C__trans1__Debug__B__Ex__State1( msg );
}

void Capsule_Counter::actionchain_____Debug__InitDebug( const UMLRTMessage * msg )
{
    transitionaction_____Debug__InitDebug( msg );
    entryaction_____Debug__InitState( msg );
}

void Capsule_Counter::actionchain_____Debug__intittrans( const UMLRTMessage * msg )
{
    exitaction_____Debug__InitState( msg );
    transitionaction_____Debug__intittrans( msg );
}

void Capsule_Counter::actionchain_____Debug__intittrans__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__intittrans__boundary( msg );
    transitionaction_____Debug__intittrans__E( msg );
    entryaction_____State1( msg );
}

void Capsule_Counter::actionchain_____Debug__intittrans__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__intittrans__S( msg );
    entryaction_____Debug__C__intittrans__boundary( msg );
}

void Capsule_Counter::actionchain_____Debug__intittrans__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__intittrans__boundary( msg );
    transitionaction_____Debug__intittrans__dbg( msg );
    entryaction_____Debug__C__intittrans__boundary( msg );
}

void Capsule_Counter::actionchain_____Debug__trans1( const UMLRTMessage * msg )
{
    exitaction_____State1( msg );
    transitionaction_____Debug__trans1( msg );
}

void Capsule_Counter::actionchain_____Debug__trans1__E( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__trans1__boundary( msg );
    transitionaction_____Debug__trans1__E( msg );
    entryaction_____State1( msg );
}

void Capsule_Counter::actionchain_____Debug__trans1__S( const UMLRTMessage * msg )
{
    transitionaction_____Debug__trans1__S( msg );
    entryaction_____Debug__C__trans1__boundary( msg );
}

void Capsule_Counter::actionchain_____Debug__trans1__dbg( const UMLRTMessage * msg )
{
    exitaction_____Debug__C__trans1__boundary( msg );
    transitionaction_____Debug__trans1__dbg( msg );
    entryaction_____Debug__C__trans1__boundary( msg );
}

void Capsule_Counter::actionchain_____intittrans( const UMLRTMessage * msg )
{
    transitionaction_____intittrans( msg );
    entryaction_____State1( msg );
}

void Capsule_Counter::actionchain_____trans1( const UMLRTMessage * msg )
{
    transitionaction_____trans1( msg );
    entryaction_____State1( msg );
}

Capsule_Counter::State Capsule_Counter::junction_____Debug__C__intittrans__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__intittrans__Debug__init__trans__intittrans( msg );
    return Debug__C__intittrans__Debug__B__Ac__intittrans;
}

Capsule_Counter::State Capsule_Counter::junction_____Debug__C__intittrans__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__intittrans__E( msg );
    return State1;
}

Capsule_Counter::State Capsule_Counter::junction_____Debug__C__intittrans__new_exitpoint_1( const UMLRTMessage * msg )
{
    actionchain_____Debug__intittrans__dbg( msg );
    return choice_____Debug__C__intittrans__deephistory( msg );
}

Capsule_Counter::State Capsule_Counter::junction_____Debug__C__trans1__en( const UMLRTMessage * msg )
{
    actionchain_____Debug__C__trans1__Debug__init__trans__trans1( msg );
    return Debug__C__trans1__Debug__B__Ex__State1;
}

Capsule_Counter::State Capsule_Counter::junction_____Debug__C__trans1__ex( const UMLRTMessage * msg )
{
    actionchain_____Debug__trans1__E( msg );
    return State1;
}

Capsule_Counter::State Capsule_Counter::junction_____Debug__C__trans1__new_exitpoint_2( const UMLRTMessage * msg )
{
    actionchain_____Debug__trans1__dbg( msg );
    return choice_____Debug__C__trans1__deephistory( msg );
}

Capsule_Counter::State Capsule_Counter::choice_____Debug__C__intittrans__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__intittrans, Debug__C__intittrans__Debug__B__Ac__intittrans ) )
    {
        actionchain_____Debug__C__intittrans__new_transition_1( msg );
        return Debug__C__intittrans__Debug__B__Ac__intittrans;
    }
    else if( check_history( Debug__C__intittrans, Debug__C__intittrans__Debug__A__Ac__intittrans ) )
    {
        actionchain_____Debug__C__intittrans__new_transition_2( msg );
        return Debug__C__intittrans__Debug__A__Ac__intittrans;
    }
    else if( check_history( Debug__C__intittrans, Debug__C__intittrans__Debug__A__En__intittrans ) )
    {
        actionchain_____Debug__C__intittrans__new_transition_3( msg );
        return Debug__C__intittrans__Debug__A__En__intittrans;
    }
    else if( check_history( Debug__C__intittrans, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__intittrans__new_transition_4_to_boundary( msg );
        return Debug__C__intittrans__boundary;
    }
    return currentState;
}

Capsule_Counter::State Capsule_Counter::choice_____Debug__C__trans1__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Debug__C__trans1, Debug__C__trans1__Debug__B__Ex__State1 ) )
    {
        actionchain_____Debug__C__trans1__new_transition_9( msg );
        return Debug__C__trans1__Debug__B__Ex__State1;
    }
    else if( check_history( Debug__C__trans1, Debug__C__trans1__Debug__B__Ac__trans1 ) )
    {
        actionchain_____Debug__C__trans1__new_transition_10( msg );
        return Debug__C__trans1__Debug__B__Ac__trans1;
    }
    else if( check_history( Debug__C__trans1, Debug__C__trans1__Debug__A__Ac__trans1 ) )
    {
        actionchain_____Debug__C__trans1__new_transition_11( msg );
        return Debug__C__trans1__Debug__A__Ac__trans1;
    }
    else if( check_history( Debug__C__trans1, Debug__C__trans1__Debug__A__En__State1 ) )
    {
        actionchain_____Debug__C__trans1__new_transition_12( msg );
        return Debug__C__trans1__Debug__A__En__State1;
    }
    else if( check_history( Debug__C__trans1, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Debug__C__trans1__new_transition_13_to_boundary( msg );
        return Debug__C__trans1__boundary;
    }
    return currentState;
}

Capsule_Counter::State Capsule_Counter::choice_____Debug__Path__intittrans( const UMLRTMessage * msg )
{
    if( action_____Debug__intittrans__S__Debug__Guardintittrans( msg ) )
    {
        actionchain_____Debug__intittrans__S( msg );
        return junction_____Debug__C__intittrans__en( msg );
    }
    else
    {
        actionchain_____intittrans( msg );
        return State1;
    }
    return currentState;
}

Capsule_Counter::State Capsule_Counter::choice_____Debug__Path__trans1( const UMLRTMessage * msg )
{
    if( action_____Debug__trans1__S__Debug__Guardtrans1( msg ) )
    {
        actionchain_____Debug__trans1__S( msg );
        return junction_____Debug__C__trans1__en( msg );
    }
    else
    {
        actionchain_____trans1( msg );
        return State1;
    }
    return currentState;
}

Capsule_Counter::State Capsule_Counter::state_____Debug__C__intittrans__Debug__A__Ac__intittrans( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__intittrans__Debug__En__State1( msg );
            return Debug__C__intittrans__Debug__A__En__intittrans;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__intittrans__new_transition_6( msg );
            return junction_____Debug__C__intittrans__new_exitpoint_1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Counter::State Capsule_Counter::state_____Debug__C__intittrans__Debug__A__En__intittrans( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__intittrans__Debug__end__trans__intittrans( msg );
            return junction_____Debug__C__intittrans__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__intittrans__new_transition_7( msg );
            return junction_____Debug__C__intittrans__new_exitpoint_1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Counter::State Capsule_Counter::state_____Debug__C__intittrans__Debug__B__Ac__intittrans( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__intittrans__Debug__Ac__intittrans( msg );
            return Debug__C__intittrans__Debug__A__Ac__intittrans;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__intittrans__new_transition_5( msg );
            return junction_____Debug__C__intittrans__new_exitpoint_1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Counter::State Capsule_Counter::state_____Debug__C__intittrans__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__intittrans__new_transition_8( msg );
            return junction_____Debug__C__intittrans__new_exitpoint_1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Counter::State Capsule_Counter::state_____Debug__C__trans1__Debug__A__Ac__trans1( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__trans1__Debug__En__State1( msg );
            return Debug__C__trans1__Debug__A__En__State1;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__trans1__new_transition_16( msg );
            return junction_____Debug__C__trans1__new_exitpoint_2( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Counter::State Capsule_Counter::state_____Debug__C__trans1__Debug__A__En__State1( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__trans1__Debug__end__trans__trans1( msg );
            return junction_____Debug__C__trans1__ex( msg );
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__trans1__new_transition_17( msg );
            return junction_____Debug__C__trans1__new_exitpoint_2( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Counter::State Capsule_Counter::state_____Debug__C__trans1__Debug__B__Ac__trans1( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__trans1__Debug__AC__trans1( msg );
            return Debug__C__trans1__Debug__A__Ac__trans1;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__trans1__new_transition_15( msg );
            return junction_____Debug__C__trans1__new_exitpoint_2( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Counter::State Capsule_Counter::state_____Debug__C__trans1__Debug__B__Ex__State1( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgExec:
            actionchain_____Debug__C__trans1__Debug__Ex__State1( msg );
            return Debug__C__trans1__Debug__B__Ac__trans1;
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__trans1__new_transition_14( msg );
            return junction_____Debug__C__trans1__new_exitpoint_2( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Counter::State Capsule_Counter::state_____Debug__C__trans1__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_dbgVarChange:
            actionchain_____Debug__C__trans1__new_transition_18( msg );
            return junction_____Debug__C__trans1__new_exitpoint_2( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Counter::State Capsule_Counter::state_____Debug__InitState( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____Debug__intittrans( msg );
            return choice_____Debug__Path__intittrans( msg );
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Counter::State Capsule_Counter::state_____State1( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer1:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____Debug__trans1( msg );
            return choice_____Debug__Path__trans1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}





void Capsule_Counter::bindPort( bool isBorder, int portId, int index )
{
}

void Capsule_Counter::unbindPort( bool isBorder, int portId, int index )
{
}







void Capsule_Counter::Debug__variablesView()
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter operation Debug__variablesView */
    std::string tempS="";
    tempS.append("Attribute1,");
    tempS.append("Integer,");
    if(Attribute1!=0){
    char tempR[10];
    sprintf(tempR,"%d",Attribute1);
    tempS.append(tempR);
    tempS.append("\n");
    }else {
    tempS.append("0");
    tempS.append("\n");
    };
    tempS.append("counter,");
    tempS.append("Integer,");
    if(counter!=0){
    char tempR[10];
    sprintf(tempR,"%d",counter);
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

bool Capsule_Counter::Debug__variablesChange( char * varName, char * varValue )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter operation Debug__variablesChange */
    std::string tempVarName="";
    tempVarName.append(varName);
    if ("counter"==tempVarName){
    counter=atoi(varValue);
    return true;
    }else if ("Attribute1"==tempVarName){
    Attribute1=atoi(varValue);
    return true;
    }else 
    return false;
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_Counter::Debug__sendEvent( debugEvents::EVENTSOURCEKIND eventSourceKind, debugEvents::EVENTTYPE eventType, const char * instanceName, int capsuleIndex, const char * signalName, char * capsuleName, char * sourceName, char * reserve1, char * reserve2, char * reserve3 )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Refined-CounterModel/Counter.uml RootElement::Counter operation Debug__sendEvent */
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


static const UMLRTCommsPortRole portroles_border[] = 
{
    {
        Capsule_Counter::port_extComm,
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
        Capsule_Counter::port_timer1,
        "Timing",
        "timer1",
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

static void instantiate_Counter( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_Counter( &Counter, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Counter = 
{
    "Counter",
    NULL,
    instantiate_Counter,
    0,
    NULL,
    2,
    portroles_border,
    0,
    NULL
};

