
#include "Car.hh"

#include "CentralLock.hh"
#include "Door.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcapsulepart.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "umlrtcapsulerole.hh"
#include "umlrtcommsport.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;

Capsule_Car::Capsule_Car( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, centralLock( &slot->parts[part_centralLock] )
, door1( &slot->parts[part_door1] )
, door2( &slot->parts[part_door2] )
, door3( &slot->parts[part_door3] )
, door4( &slot->parts[part_door4] )
{
}







void Capsule_Car::bindPort( bool isBorder, int portId, int index )
{
}

void Capsule_Car::unbindPort( bool isBorder, int portId, int index )
{
}

void Capsule_Car::initialize( const UMLRTMessage & msg )
{
}

void Capsule_Car::inject( const UMLRTMessage & msg )
{
}


static const UMLRTCapsuleRole roles[] = 
{
    {
        "centralLock",
        &CentralLock,
        1,
        1,
        false,
        false
    },
    {
        "door1",
        &Door,
        1,
        1,
        false,
        false
    },
    {
        "door2",
        &Door,
        1,
        1,
        false,
        false
    },
    {
        "door3",
        &Door,
        1,
        1,
        false,
        false
    },
    {
        "door4",
        &Door,
        1,
        1,
        false,
        false
    }
};

static void instantiate_Car( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Car::part_centralLock].slots[0]->ports[Capsule_CentralLock::borderport_lockPort], 0, &slot->parts[Capsule_Car::part_door1].slots[0]->ports[Capsule_Door::borderport_lockPort], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Car::part_centralLock].slots[0]->ports[Capsule_CentralLock::borderport_lockPort], 1, &slot->parts[Capsule_Car::part_door2].slots[0]->ports[Capsule_Door::borderport_lockPort], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Car::part_centralLock].slots[0]->ports[Capsule_CentralLock::borderport_lockPort], 2, &slot->parts[Capsule_Car::part_door3].slots[0]->ports[Capsule_Door::borderport_lockPort], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Car::part_centralLock].slots[0]->ports[Capsule_CentralLock::borderport_lockPort], 3, &slot->parts[Capsule_Car::part_door4].slots[0]->ports[Capsule_Door::borderport_lockPort], 0 );
    CentralLock.instantiate( NULL, slot->parts[Capsule_Car::part_centralLock].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Car::part_centralLock].slots[0], CentralLock.numPortRolesBorder ) );
    Door.instantiate( NULL, slot->parts[Capsule_Car::part_door1].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Car::part_door1].slots[0], Door.numPortRolesBorder ) );
    Door.instantiate( NULL, slot->parts[Capsule_Car::part_door2].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Car::part_door2].slots[0], Door.numPortRolesBorder ) );
    Door.instantiate( NULL, slot->parts[Capsule_Car::part_door3].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Car::part_door3].slots[0], Door.numPortRolesBorder ) );
    Door.instantiate( NULL, slot->parts[Capsule_Car::part_door4].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Car::part_door4].slots[0], Door.numPortRolesBorder ) );
    slot->capsule = new Capsule_Car( &Car, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Car = 
{
    "Car",
    NULL,
    instantiate_Car,
    5,
    roles,
    0,
    NULL,
    0,
    NULL
};

