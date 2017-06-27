
#include "Parcer_Router.hh"

#include "Bin.hh"
#include "Gen.hh"
#include "Stage.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcapsulepart.hh"
#include "umlrtcommsport.hh"
#include "umlrtframeservice.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "umlrtcapsulerole.hh"
class UMLRTRtsInterface;

Capsule_Parcer_Router::Capsule_Parcer_Router( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, bin0( &slot->parts[part_bin0] )
, bin1( &slot->parts[part_bin1] )
, bin2( &slot->parts[part_bin2] )
, bin3( &slot->parts[part_bin3] )
, gen( &slot->parts[part_gen] )
, left( &slot->parts[part_left] )
, right( &slot->parts[part_right] )
, top( &slot->parts[part_top] )
{
}










void Capsule_Parcer_Router::bindPort( bool isBorder, int portId, int index )
{
}

void Capsule_Parcer_Router::unbindPort( bool isBorder, int portId, int index )
{
}

void Capsule_Parcer_Router::initialize( const UMLRTMessage & msg )
{
}

void Capsule_Parcer_Router::inject( const UMLRTMessage & msg )
{
}


static const UMLRTCapsuleRole roles[] = 
{
    {
        "bin0",
        &Bin,
        1,
        1,
        false,
        false
    },
    {
        "bin1",
        &Bin,
        1,
        1,
        false,
        false
    },
    {
        "bin2",
        &Bin,
        1,
        1,
        false,
        false
    },
    {
        "bin3",
        &Bin,
        1,
        1,
        false,
        false
    },
    {
        "gen",
        &Gen,
        1,
        1,
        false,
        false
    },
    {
        "left",
        &Stage,
        1,
        1,
        false,
        false
    },
    {
        "right",
        &Stage,
        1,
        1,
        false,
        false
    },
    {
        "top",
        &Stage,
        1,
        1,
        false,
        false
    }
};

static void instantiate_Parcer_Router( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Parcer_Router::part_bin0].slots[0]->ports[Capsule_Bin::borderport_enter], 0, &slot->parts[Capsule_Parcer_Router::part_left].slots[0]->ports[Capsule_Stage::borderport_left], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Parcer_Router::part_bin1].slots[0]->ports[Capsule_Bin::borderport_enter], 0, &slot->parts[Capsule_Parcer_Router::part_left].slots[0]->ports[Capsule_Stage::borderport_right], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Parcer_Router::part_bin2].slots[0]->ports[Capsule_Bin::borderport_enter], 0, &slot->parts[Capsule_Parcer_Router::part_right].slots[0]->ports[Capsule_Stage::borderport_left], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Parcer_Router::part_bin3].slots[0]->ports[Capsule_Bin::borderport_enter], 0, &slot->parts[Capsule_Parcer_Router::part_right].slots[0]->ports[Capsule_Stage::borderport_right], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Parcer_Router::part_gen].slots[0]->ports[Capsule_Gen::borderport_enter], 0, &slot->parts[Capsule_Parcer_Router::part_top].slots[0]->ports[Capsule_Stage::borderport_enter], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Parcer_Router::part_left].slots[0]->ports[Capsule_Stage::borderport_enter], 0, &slot->parts[Capsule_Parcer_Router::part_top].slots[0]->ports[Capsule_Stage::borderport_left], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Parcer_Router::part_right].slots[0]->ports[Capsule_Stage::borderport_enter], 0, &slot->parts[Capsule_Parcer_Router::part_top].slots[0]->ports[Capsule_Stage::borderport_right], 0 );
    Bin.instantiate( NULL, slot->parts[Capsule_Parcer_Router::part_bin0].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Parcer_Router::part_bin0].slots[0], Bin.numPortRolesBorder ) );
    Bin.instantiate( NULL, slot->parts[Capsule_Parcer_Router::part_bin1].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Parcer_Router::part_bin1].slots[0], Bin.numPortRolesBorder ) );
    Bin.instantiate( NULL, slot->parts[Capsule_Parcer_Router::part_bin2].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Parcer_Router::part_bin2].slots[0], Bin.numPortRolesBorder ) );
    Bin.instantiate( NULL, slot->parts[Capsule_Parcer_Router::part_bin3].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Parcer_Router::part_bin3].slots[0], Bin.numPortRolesBorder ) );
    Gen.instantiate( NULL, slot->parts[Capsule_Parcer_Router::part_gen].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Parcer_Router::part_gen].slots[0], Gen.numPortRolesBorder ) );
    Stage.instantiate( NULL, slot->parts[Capsule_Parcer_Router::part_left].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Parcer_Router::part_left].slots[0], Stage.numPortRolesBorder ) );
    Stage.instantiate( NULL, slot->parts[Capsule_Parcer_Router::part_right].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Parcer_Router::part_right].slots[0], Stage.numPortRolesBorder ) );
    Stage.instantiate( NULL, slot->parts[Capsule_Parcer_Router::part_top].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Parcer_Router::part_top].slots[0], Stage.numPortRolesBorder ) );
    slot->capsule = new Capsule_Parcer_Router( &Parcer_Router, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Parcer_Router = 
{
    "Parcer_Router",
    NULL,
    instantiate_Parcer_Router,
    8,
    roles,
    0,
    NULL,
    0,
    NULL
};

