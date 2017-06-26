
#include "TemperatureSensor.hh"

#include <cstddef>
#include "umlrtcapsuleclass.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtframeservice.hh"
#include "umlrtslot.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_TemperatureSensor::Capsule_TemperatureSensor( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, temperature( borderPorts[borderport_temperature] )
{
}





void Capsule_TemperatureSensor::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_temperature:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_temperature, index, true );
            break;
        }
}

void Capsule_TemperatureSensor::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_temperature:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_temperature, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_temperature], index );
            break;
        }
}

void Capsule_TemperatureSensor::initialize( const UMLRTMessage & msg )
{
}

void Capsule_TemperatureSensor::inject( const UMLRTMessage & msg )
{
}


static const UMLRTCommsPortRole portroles_border[] = 
{
    {
        Capsule_TemperatureSensor::port_temperature,
        "Temperature",
        "temperature",
        "",
        1,
        true,
        true,
        false,
        false,
        false,
        false,
        true
    }
};

static void instantiate_TemperatureSensor( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_TemperatureSensor( &TemperatureSensor, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass TemperatureSensor = 
{
    "TemperatureSensor",
    NULL,
    instantiate_TemperatureSensor,
    0,
    NULL,
    1,
    portroles_border,
    0,
    NULL
};

