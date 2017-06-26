
#include "Top.hh"

#include "ControlSoftware.hh"
#include "Rover.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcapsulepart.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "umlrtcapsulerole.hh"
#include "umlrtcommsport.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;

Capsule_Top::Capsule_Top( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, controlSoftware( &slot->parts[part_controlSoftware] )
, rover( &slot->parts[part_rover] )
{
}




void Capsule_Top::bindPort( bool isBorder, int portId, int index )
{
}

void Capsule_Top::unbindPort( bool isBorder, int portId, int index )
{
}

void Capsule_Top::initialize( const UMLRTMessage & msg )
{
}

void Capsule_Top::inject( const UMLRTMessage & msg )
{
}


static const UMLRTCapsuleRole roles[] = 
{
    {
        "controlSoftware",
        &ControlSoftware,
        1,
        1,
        false,
        false
    },
    {
        "rover",
        &Rover,
        1,
        1,
        false,
        false
    }
};

static void instantiate_Top( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Top::part_controlSoftware].slots[0]->ports[Capsule_ControlSoftware::borderport_detection], 0, &slot->parts[Capsule_Top::part_rover].slots[0]->ports[Capsule_Rover::borderport_detection], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Top::part_controlSoftware].slots[0]->ports[Capsule_ControlSoftware::borderport_engine], 0, &slot->parts[Capsule_Top::part_rover].slots[0]->ports[Capsule_Rover::borderport_engine], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Top::part_controlSoftware].slots[0]->ports[Capsule_ControlSoftware::borderport_temperature], 0, &slot->parts[Capsule_Top::part_rover].slots[0]->ports[Capsule_Rover::borderport_temperature], 0 );
    ControlSoftware.instantiate( NULL, slot->parts[Capsule_Top::part_controlSoftware].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Top::part_controlSoftware].slots[0], ControlSoftware.numPortRolesBorder ) );
    Rover.instantiate( NULL, slot->parts[Capsule_Top::part_rover].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Top::part_rover].slots[0], Rover.numPortRolesBorder ) );
    slot->capsule = new Capsule_Top( &Top, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Top = 
{
    "Top",
    NULL,
    instantiate_Top,
    2,
    roles,
    0,
    NULL,
    0,
    NULL
};

