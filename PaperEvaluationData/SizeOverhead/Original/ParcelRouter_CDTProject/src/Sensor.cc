
#include "Sensor.hh"

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
, switchProtocol( borderPorts[borderport_switchProtocol] )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[IDLE] = "IDLE";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
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

void Capsule_Sensor::inject( const UMLRTMessage & message )
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

void Capsule_Sensor::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Initial( &message );
    currentState = IDLE;
}

const char * Capsule_Sensor::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_Sensor::entryaction_____IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouter/model.uml RootElement::Sensor::IDLE entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Sensor::exitaction_____IDLE( const UMLRTMessage * msg )
{
    #define umlrtparam_p ( *(const Parcel * )msg->getParam( 0 ) )
    #define rtdata ( (const Parcel * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouter/model.uml RootElement::Sensor::IDLE exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_p
}

void Capsule_Sensor::transitionaction_____TransitionAction1( const UMLRTMessage * msg )
{
    #define umlrtparam_p ( *(const Parcel * )msg->getParam( 0 ) )
    #define rtdata ( (const Parcel * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/ParcelRouter/model.uml RootElement::Sensor transition IDLE,IDLE,detect:detection */
    int reducedNumber = umlrtparam_p.number/umlrtparam_p.level; 
    int isPair = reducedNumber % 2;
    if (isPair == 0) {
    log.show("At stage %s (%d), turn left.\n", getName(), umlrtparam_p.level);
    switchProtocol.setSwitch(0).send();
    }
    else {
    log.show("At stage %s (%d), turn right.\n", getName(), umlrtparam_p.level);
    switchProtocol.setSwitch(1).send();
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_p
}

void Capsule_Sensor::actionchain_____Initial( const UMLRTMessage * msg )
{
    entryaction_____IDLE( msg );
}

void Capsule_Sensor::actionchain_____TransitionAction1( const UMLRTMessage * msg )
{
    exitaction_____IDLE( msg );
    transitionaction_____TransitionAction1( msg );
    entryaction_____IDLE( msg );
}

Capsule_Sensor::State Capsule_Sensor::state_____IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_detection:
        switch( msg->getSignalId() )
        {
        case detection::signal_detect:
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
    3,
    portroles_border,
    0,
    NULL
};

