
#include "Door.hh"

#include "Lock.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcapsulepart.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "umlrtcapsulerole.hh"
#include "umlrtcommsport.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;

Capsule_Door::Capsule_Door( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, lockPort( borderPorts[borderport_lockPort] )
, lock( &slot->parts[part_lock] )
{
}






void Capsule_Door::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_lockPort:
            switch( index )
            {
            case 0:
                UMLRTFrameService::connectRelayPort( borderPorts[borderport_lockPort], index, &slot->parts[part_lock].slots[0]->ports[Capsule_Lock::borderport_lockPort], 0 );
                UMLRTFrameService::bindSubcapsulePort( true, slot->parts[part_lock].slots[0]->capsule, portId, index );
                break;
            }
            break;
        }
}

void Capsule_Door::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_lockPort:
            switch( index )
            {
            case 0:
                UMLRTFrameService::unbindSubcapsulePort( true, slot->parts[part_lock].slots[0]->capsule, portId, index );
                break;
            }
            break;
        }
}

void Capsule_Door::initialize( const UMLRTMessage & msg )
{
}

void Capsule_Door::inject( const UMLRTMessage & msg )
{
}


static const UMLRTCapsuleRole roles[] = 
{
    {
        "lock",
        &Lock,
        1,
        1,
        false,
        false
    }
};

static const UMLRTCommsPortRole portroles_border[] = 
{
    {
        Capsule_Door::port_lockPort,
        "Locking",
        "lockPort",
        "",
        1,
        true,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static void instantiate_Door( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    UMLRTFrameService::connectRelayPort( borderPorts[Capsule_Door::borderport_lockPort], 0, &slot->parts[Capsule_Door::part_lock].slots[0]->ports[Capsule_Lock::borderport_lockPort], 0 );
    Lock.instantiate( NULL, slot->parts[Capsule_Door::part_lock].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Door::part_lock].slots[0], Lock.numPortRolesBorder ) );
    slot->capsule = new Capsule_Door( &Door, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Door = 
{
    "Door",
    NULL,
    instantiate_Door,
    1,
    roles,
    1,
    portroles_border,
    0,
    NULL
};

