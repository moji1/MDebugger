
#include "Bin.hh"

#include "transmission.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "Parcel.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_Bin::Capsule_Bin( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, enter( borderPorts[borderport_enter] )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[IDLE] = "IDLE";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}






void Capsule_Bin::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_enter:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_enter, index, true );
            break;
        }
}

void Capsule_Bin::unbindPort( bool isBorder, int portId, int index )
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


void Capsule_Bin::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case IDLE:
        currentState = state_____IDLE( &message );
        break;
    default:
        break;
    }
}

void Capsule_Bin::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Initial( &message );
    currentState = IDLE;
}

const char * Capsule_Bin::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_Bin::entryaction_____IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouterSimplified/model.uml RootElement::Bin::IDLE entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Bin::exitaction_____IDLE( const UMLRTMessage * msg )
{
    #define umlrtparam_p ( *(const Parcel * )msg->getParam( 0 ) )
    #define rtdata ( (const Parcel * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouterSimplified/model.uml RootElement::Bin::IDLE exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_p
}

void Capsule_Bin::transitionaction_____Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouterSimplified/model.uml RootElement::Bin transition initial,IDLE */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Bin::transitionaction_____TransitionAction1( const UMLRTMessage * msg )
{
    #define umlrtparam_p ( *(const Parcel * )msg->getParam( 0 ) )
    #define rtdata ( (const Parcel * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouterSimplified/model.uml RootElement::Bin transition IDLE,IDLE,transmit:enter */
    log.show("%s received Parcel (%d)\n", getName(), 1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_p
}

void Capsule_Bin::actionchain_____Initial( const UMLRTMessage * msg )
{
    transitionaction_____Initial( msg );
    entryaction_____IDLE( msg );
}

void Capsule_Bin::actionchain_____TransitionAction1( const UMLRTMessage * msg )
{
    exitaction_____IDLE( msg );
    transitionaction_____TransitionAction1( msg );
    entryaction_____IDLE( msg );
}

Capsule_Bin::State Capsule_Bin::state_____IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_enter:
        switch( msg->getSignalId() )
        {
        case transmission::signal_transmit:
            actionchain_____TransitionAction1( msg );
            return IDLE;
        default:
            this->unexpectedMessage();
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
        Capsule_Bin::port_enter,
        "transmission",
        "enter",
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
        Capsule_Bin::port_log,
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

static void instantiate_Bin( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_Bin( &Bin, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Bin = 
{
    "Bin",
    NULL,
    instantiate_Bin,
    0,
    NULL,
    2,
    portroles_border,
    0,
    NULL
};

