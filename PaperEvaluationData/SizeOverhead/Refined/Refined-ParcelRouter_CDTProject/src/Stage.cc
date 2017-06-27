
#include "Stage.hh"

#include "Chute.hh"
#include "Sensor.hh"
#include "Switcher.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcapsulepart.hh"
#include "umlrtcapsulerole.hh"
#include "umlrtcommsport.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtframeservice.hh"
#include "umlrtslot.hh"
#include <cstddef>
class UMLRTRtsInterface;

Capsule_Stage::Capsule_Stage( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, enter( borderPorts[borderport_enter] )
, left( borderPorts[borderport_left] )
, right( borderPorts[borderport_right] )
, chute1( &slot->parts[part_chute1] )
, chute2( &slot->parts[part_chute2] )
, sensor( &slot->parts[part_sensor] )
, switcher( &slot->parts[part_switcher] )
{
}












void Capsule_Stage::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_enter:
            switch( index )
            {
            case 0:
                UMLRTFrameService::connectRelayPort( borderPorts[borderport_enter], index, &slot->parts[part_chute1].slots[0]->ports[Capsule_Chute::borderport_enter], 0 );
                UMLRTFrameService::bindSubcapsulePort( true, slot->parts[part_chute1].slots[0]->capsule, portId, index );
                break;
            }
            break;
        case borderport_left:
            switch( index )
            {
            case 0:
                UMLRTFrameService::connectRelayPort( borderPorts[borderport_left], index, &slot->parts[part_switcher].slots[0]->ports[Capsule_Switcher::borderport_left], 0 );
                UMLRTFrameService::bindSubcapsulePort( true, slot->parts[part_switcher].slots[0]->capsule, portId, index );
                break;
            }
            break;
        case borderport_right:
            switch( index )
            {
            case 0:
                UMLRTFrameService::connectRelayPort( borderPorts[borderport_right], index, &slot->parts[part_switcher].slots[0]->ports[Capsule_Switcher::borderport_right], 0 );
                UMLRTFrameService::bindSubcapsulePort( true, slot->parts[part_switcher].slots[0]->capsule, portId, index );
                break;
            }
            break;
        }
}

void Capsule_Stage::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_enter:
            switch( index )
            {
            case 0:
                UMLRTFrameService::unbindSubcapsulePort( true, slot->parts[part_chute1].slots[0]->capsule, portId, index );
                break;
            }
            break;
        case borderport_left:
            switch( index )
            {
            case 0:
                UMLRTFrameService::unbindSubcapsulePort( true, slot->parts[part_switcher].slots[0]->capsule, portId, index );
                break;
            }
            break;
        case borderport_right:
            switch( index )
            {
            case 0:
                UMLRTFrameService::unbindSubcapsulePort( true, slot->parts[part_switcher].slots[0]->capsule, portId, index );
                break;
            }
            break;
        }
}


void Capsule_Stage::initialize( const UMLRTMessage & msg )
{
}

void Capsule_Stage::inject( const UMLRTMessage & msg )
{
}


static const UMLRTCapsuleRole roles[] = 
{
    {
        "chute1",
        &Chute,
        1,
        1,
        false,
        false
    },
    {
        "chute2",
        &Chute,
        1,
        1,
        false,
        false
    },
    {
        "sensor",
        &Sensor,
        1,
        1,
        false,
        false
    },
    {
        "switcher",
        &Switcher,
        1,
        1,
        false,
        false
    }
};

static const UMLRTCommsPortRole portroles_border[] = 
{
    {
        Capsule_Stage::port_enter,
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
        Capsule_Stage::port_left,
        "transmission",
        "left",
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
        Capsule_Stage::port_right,
        "transmission",
        "right",
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
        Capsule_Stage::port_log,
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

static void instantiate_Stage( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    UMLRTFrameService::connectRelayPort( borderPorts[Capsule_Stage::borderport_enter], 0, &slot->parts[Capsule_Stage::part_chute1].slots[0]->ports[Capsule_Chute::borderport_enter], 0 );
    UMLRTFrameService::connectRelayPort( borderPorts[Capsule_Stage::borderport_left], 0, &slot->parts[Capsule_Stage::part_switcher].slots[0]->ports[Capsule_Switcher::borderport_left], 0 );
    UMLRTFrameService::connectRelayPort( borderPorts[Capsule_Stage::borderport_right], 0, &slot->parts[Capsule_Stage::part_switcher].slots[0]->ports[Capsule_Switcher::borderport_right], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Stage::part_chute1].slots[0]->ports[Capsule_Chute::borderport_detection], 0, &slot->parts[Capsule_Stage::part_sensor].slots[0]->ports[Capsule_Sensor::borderport_detection], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Stage::part_chute1].slots[0]->ports[Capsule_Chute::borderport_exit], 0, &slot->parts[Capsule_Stage::part_chute2].slots[0]->ports[Capsule_Chute::borderport_enter], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Stage::part_chute2].slots[0]->ports[Capsule_Chute::borderport_exit], 0, &slot->parts[Capsule_Stage::part_switcher].slots[0]->ports[Capsule_Switcher::borderport_enter], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Stage::part_sensor].slots[0]->ports[Capsule_Sensor::borderport_switchProtocol], 0, &slot->parts[Capsule_Stage::part_switcher].slots[0]->ports[Capsule_Switcher::borderport_switchProtocol], 0 );
    Chute.instantiate( NULL, slot->parts[Capsule_Stage::part_chute1].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Stage::part_chute1].slots[0], Chute.numPortRolesBorder ) );
    Chute.instantiate( NULL, slot->parts[Capsule_Stage::part_chute2].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Stage::part_chute2].slots[0], Chute.numPortRolesBorder ) );
    Sensor.instantiate( NULL, slot->parts[Capsule_Stage::part_sensor].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Stage::part_sensor].slots[0], Sensor.numPortRolesBorder ) );
    Switcher.instantiate( NULL, slot->parts[Capsule_Stage::part_switcher].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Stage::part_switcher].slots[0], Switcher.numPortRolesBorder ) );
    slot->capsule = new Capsule_Stage( &Stage, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Stage = 
{
    "Stage",
    NULL,
    instantiate_Stage,
    4,
    roles,
    4,
    portroles_border,
    0,
    NULL
};

