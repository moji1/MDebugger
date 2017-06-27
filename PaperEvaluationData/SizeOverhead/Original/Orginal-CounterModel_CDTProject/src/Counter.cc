
#include "Counter.hh"

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
, timer1( borderPorts[borderport_timer1] )
{
    stateNames[State1] = "State1";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}


void Capsule_Counter::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case State1:
        currentState = state_____State1( &message );
        break;
    default:
        break;
    }
}

void Capsule_Counter::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____intittrans( &message );
    currentState = State1;
}

const char * Capsule_Counter::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_Counter::entryaction_____State1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Orginal-CounterModel/Counter.uml RootElement::Counter::State1 entry  */
    std::cout<<"State 1 is vistited\n";
    std::cout<<"Counter is "<<counter<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::exitaction_____State1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Orginal-CounterModel/Counter.uml RootElement::Counter::State1 exit  */
    std::cout<<"State 1 exit is running\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::transitionaction_____intittrans( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Orginal-CounterModel/Counter.uml RootElement::Counter transition Initial1,State1 */
    std::cout<<"Capsule is started\n"; 
    timer1.informEvery(UMLRTTimespec(3,1));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::transitionaction_____trans1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Orginal-CounterModel/Counter.uml RootElement::Counter transition State1,State1,timeout:timer1 */
    counter=counter+1;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Counter::actionchain_____intittrans( const UMLRTMessage * msg )
{
    transitionaction_____intittrans( msg );
    entryaction_____State1( msg );
}

void Capsule_Counter::actionchain_____trans1( const UMLRTMessage * msg )
{
    exitaction_____State1( msg );
    transitionaction_____trans1( msg );
    entryaction_____State1( msg );
}

Capsule_Counter::State Capsule_Counter::state_____State1( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer1:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____trans1( msg );
            return State1;
        default:
            this->unexpectedMessage();
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




static const UMLRTCommsPortRole portroles_border[] = 
{
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
    1,
    portroles_border,
    0,
    NULL
};

