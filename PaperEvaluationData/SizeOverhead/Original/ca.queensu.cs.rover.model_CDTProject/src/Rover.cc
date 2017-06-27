
#include "Rover.hh"

#include "DetectionSensor.hh"
#include "EngineController.hh"
#include "TemperatureSensor.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcapsulepart.hh"
#include "umlrtcapsulerole.hh"
#include "umlrtcommsport.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtframeservice.hh"
#include "umlrtslot.hh"
#include <cstddef>
class UMLRTRtsInterface;

Capsule_Rover::Capsule_Rover( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, detection( borderPorts[borderport_detection] )
, engine( borderPorts[borderport_engine] )
, temperature( borderPorts[borderport_temperature] )
, detectionSensor( &slot->parts[part_detectionSensor] )
, detectionSensor2( &slot->parts[part_detectionSensor2] )
, engineController( &slot->parts[part_engineController] )
, temperatureSensor( &slot->parts[part_temperatureSensor] )
{
}











void Capsule_Rover::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_detection:
            switch( index )
            {
            case 0:
                UMLRTFrameService::connectRelayPort( borderPorts[borderport_detection], index, &slot->parts[part_detectionSensor2].slots[0]->ports[Capsule_DetectionSensor::borderport_detection], 0 );
                UMLRTFrameService::bindSubcapsulePort( true, slot->parts[part_detectionSensor2].slots[0]->capsule, portId, index );
                break;
            }
            break;
        case borderport_engine:
            switch( index )
            {
            case 0:
                UMLRTFrameService::connectRelayPort( borderPorts[borderport_engine], index, &slot->parts[part_engineController].slots[0]->ports[Capsule_EngineController::borderport_engine], 0 );
                UMLRTFrameService::bindSubcapsulePort( true, slot->parts[part_engineController].slots[0]->capsule, portId, index );
                break;
            }
            break;
        }
}

void Capsule_Rover::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_detection:
            switch( index )
            {
            case 0:
                UMLRTFrameService::unbindSubcapsulePort( true, slot->parts[part_detectionSensor2].slots[0]->capsule, portId, index );
                break;
            }
            break;
        case borderport_engine:
            switch( index )
            {
            case 0:
                UMLRTFrameService::unbindSubcapsulePort( true, slot->parts[part_engineController].slots[0]->capsule, portId, index );
                break;
            }
            break;
        }
}

void Capsule_Rover::initialize( const UMLRTMessage & msg )
{
}

void Capsule_Rover::inject( const UMLRTMessage & msg )
{
}


static const UMLRTCapsuleRole roles[] = 
{
    {
        "detectionSensor",
        &DetectionSensor,
        1,
        1,
        false,
        false
    },
    {
        "detectionSensor2",
        &DetectionSensor,
        1,
        1,
        false,
        false
    },
    {
        "engineController",
        &EngineController,
        1,
        1,
        false,
        false
    },
    {
        "temperatureSensor",
        &TemperatureSensor,
        1,
        1,
        false,
        false
    }
};

static const UMLRTCommsPortRole portroles_border[] = 
{
    {
        Capsule_Rover::port_detection,
        "Detection",
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
        Capsule_Rover::port_engine,
        "Engine",
        "engine",
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
        Capsule_Rover::port_temperature,
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

static void instantiate_Rover( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    UMLRTFrameService::connectRelayPort( borderPorts[Capsule_Rover::borderport_detection], 0, &slot->parts[Capsule_Rover::part_detectionSensor2].slots[0]->ports[Capsule_DetectionSensor::borderport_detection], 0 );
    UMLRTFrameService::connectRelayPort( borderPorts[Capsule_Rover::borderport_engine], 0, &slot->parts[Capsule_Rover::part_engineController].slots[0]->ports[Capsule_EngineController::borderport_engine], 0 );
    DetectionSensor.instantiate( NULL, slot->parts[Capsule_Rover::part_detectionSensor].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Rover::part_detectionSensor].slots[0], DetectionSensor.numPortRolesBorder ) );
    DetectionSensor.instantiate( NULL, slot->parts[Capsule_Rover::part_detectionSensor2].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Rover::part_detectionSensor2].slots[0], DetectionSensor.numPortRolesBorder ) );
    EngineController.instantiate( NULL, slot->parts[Capsule_Rover::part_engineController].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Rover::part_engineController].slots[0], EngineController.numPortRolesBorder ) );
    TemperatureSensor.instantiate( NULL, slot->parts[Capsule_Rover::part_temperatureSensor].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Rover::part_temperatureSensor].slots[0], TemperatureSensor.numPortRolesBorder ) );
    slot->capsule = new Capsule_Rover( &Rover, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Rover = 
{
    "Rover",
    NULL,
    instantiate_Rover,
    4,
    roles,
    3,
    portroles_border,
    0,
    NULL
};

