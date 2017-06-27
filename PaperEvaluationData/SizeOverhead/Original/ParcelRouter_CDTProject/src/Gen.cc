
#include "Gen.hh"

#include "transmission.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include "umlrttimerprotocol.hh"
#include <cstddef>
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_Gen::Capsule_Gen( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, enter( borderPorts[borderport_enter] )
, timer( borderPorts[borderport_timer] )
, delay( 8 )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[GENERATING] = "GENERATING";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}







void Capsule_Gen::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_enter:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_enter, index, true );
            break;
        }
}

void Capsule_Gen::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_enter:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_enter, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_enter], index );
            break;
        }
}




void Capsule_Gen::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case GENERATING:
        currentState = state_____GENERATING( &message );
        break;
    default:
        break;
    }
}

void Capsule_Gen::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Initial( &message );
    currentState = GENERATING;
}

const char * Capsule_Gen::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_Gen::entryaction_____GENERATING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouter/model.uml RootElement::Gen::GENERATING entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::exitaction_____GENERATING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouter/model.uml RootElement::Gen::GENERATING exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::transitionaction_____Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouter/model.uml RootElement::Gen transition initial,GENERATING */
    srand(time(0));
    timer.informEvery(UMLRTTimespec(4,0));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::transitionaction_____TransitionAction1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouter/model.uml RootElement::Gen transition GENERATING,GENERATING,timeout:timer */
    if (!this->successorFree) {
    log.show("impossible to generate a new parcel: the first chute is obfuscated\n");
    }
    else {  
    int random = rand() % 4;
    parcel = Parcel();
    parcel.number = random;
    parcel.stage = 0; // 0 for "top", 1 for "left", 2 for "right"
    parcel.level = 2;
    enter.transmit(parcel).send();
    log.show("generating a parcel %d on stage %d\n", random, parcel.stage);
    this->successorFree = false;
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Gen::transitionaction_____TransitionAction2( const UMLRTMessage * msg )
{
    #define umlrtparam_free ( *(bool *)msg->getParam( 0 ) )
    #define rtdata ( (bool *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouter/model.uml RootElement::Gen transition GENERATING,GENERATING,setFree:enter */
    this->successorFree = free;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_free
}

void Capsule_Gen::actionchain_____Initial( const UMLRTMessage * msg )
{
    transitionaction_____Initial( msg );
    entryaction_____GENERATING( msg );
}

void Capsule_Gen::actionchain_____TransitionAction1( const UMLRTMessage * msg )
{
    exitaction_____GENERATING( msg );
    transitionaction_____TransitionAction1( msg );
    entryaction_____GENERATING( msg );
}

void Capsule_Gen::actionchain_____TransitionAction2( const UMLRTMessage * msg )
{
    exitaction_____GENERATING( msg );
    transitionaction_____TransitionAction2( msg );
    entryaction_____GENERATING( msg );
}

Capsule_Gen::State Capsule_Gen::state_____GENERATING( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____TransitionAction1( msg );
            return GENERATING;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_enter:
        switch( msg->getSignalId() )
        {
        case transmission::signal_setFree:
            actionchain_____TransitionAction2( msg );
            return GENERATING;
        default:
            this->unexpectedMessage();
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
        Capsule_Gen::port_enter,
        "transmission",
        "enter",
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
        Capsule_Gen::port_timer,
        "Timing",
        "timer",
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
        Capsule_Gen::port_log,
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

static void instantiate_Gen( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_Gen( &Gen, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Gen = 
{
    "Gen",
    NULL,
    instantiate_Gen,
    0,
    NULL,
    3,
    portroles_border,
    0,
    NULL
};

