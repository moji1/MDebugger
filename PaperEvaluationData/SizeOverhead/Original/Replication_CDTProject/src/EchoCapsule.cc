
#include "EchoCapsule.hh"

#include "Echo.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "umlrtcapsuleclass.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

#include <iostream>

Capsule_EchoCapsule::Capsule_EchoCapsule( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, Echo( borderPorts[borderport_Echo] )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[WaitForEcho] = "WaitForEcho";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}





void Capsule_EchoCapsule::bindPort( bool isBorder, int portId, int index )
{
}

void Capsule_EchoCapsule::unbindPort( bool isBorder, int portId, int index )
{
}

void Capsule_EchoCapsule::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case WaitForEcho:
        currentState = state_____WaitForEcho( &message );
        break;
    default:
        break;
    }
}

void Capsule_EchoCapsule::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____TransitionAction0( &message );
    currentState = WaitForEcho;
}

const char * Capsule_EchoCapsule::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_EchoCapsule::entryaction_____WaitForEcho( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Utility::EchoCapsule::WaitForEcho entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::exitaction_____WaitForEcho( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Utility::EchoCapsule::WaitForEcho exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::transitionaction_____DoEcho( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Utility::EchoCapsule transition WaitForEcho,WaitForEcho,Echo:Echo */
    std::cout<<"EchoCapsule: The Echo message was recieved\n";
    int tempid=msg->sapIndex0_;
    Echo.Echo().sendAt(tempid);
    std::cout<<"EchoCapsule: The Echo message was replied\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::transitionaction_____TransitionAction0( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Utility::EchoCapsule transition init,WaitForEcho */
    std::cout<<"EchoCapsule: Intializing\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_EchoCapsule::actionchain_____DoEcho( const UMLRTMessage * msg )
{
    exitaction_____WaitForEcho( msg );
    transitionaction_____DoEcho( msg );
    entryaction_____WaitForEcho( msg );
}

void Capsule_EchoCapsule::actionchain_____TransitionAction0( const UMLRTMessage * msg )
{
    transitionaction_____TransitionAction0( msg );
    entryaction_____WaitForEcho( msg );
}

Capsule_EchoCapsule::State Capsule_EchoCapsule::state_____WaitForEcho( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_Echo:
        switch( msg->getSignalId() )
        {
        case Echo::signal_Echo:
            actionchain_____DoEcho( msg );
            return WaitForEcho;
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
    1,
    portroles_border,
    0,
    NULL
};

