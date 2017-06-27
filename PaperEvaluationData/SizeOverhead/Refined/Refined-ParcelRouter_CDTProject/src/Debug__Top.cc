
#include "Debug__Top.hh"

#include "GateWay.hh"
#include "Parcer_Router.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcapsulepart.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "umlrtcapsulerole.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_Debug__Top::Capsule_Debug__Top( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, Debug__Gateway( &slot->parts[part_Debug__Gateway] )
, Debug__Parcer_Router( &slot->parts[part_Debug__Parcer_Router] )
{
}




void Capsule_Debug__Top::bindPort( bool isBorder, int portId, int index )
{
}

void Capsule_Debug__Top::unbindPort( bool isBorder, int portId, int index )
{
}

void Capsule_Debug__Top::initialize( const UMLRTMessage & msg )
{
}

void Capsule_Debug__Top::inject( const UMLRTMessage & msg )
{
}


static const UMLRTCapsuleRole roles[] = 
{
    {
        "Debug__Gateway",
        &GateWay,
        1,
        1,
        false,
        false
    },
    {
        "Debug__Parcer_Router",
        &Parcer_Router,
        1,
        1,
        false,
        false
    }
};

static void instantiate_Debug__Top( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    GateWay.instantiate( NULL, slot->parts[Capsule_Debug__Top::part_Debug__Gateway].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Debug__Top::part_Debug__Gateway].slots[0], GateWay.numPortRolesBorder ) );
    Parcer_Router.instantiate( NULL, slot->parts[Capsule_Debug__Top::part_Debug__Parcer_Router].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Debug__Top::part_Debug__Parcer_Router].slots[0], Parcer_Router.numPortRolesBorder ) );
    slot->capsule = new Capsule_Debug__Top( &Debug__Top, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Debug__Top = 
{
    "Debug__Top",
    NULL,
    instantiate_Debug__Top,
    2,
    roles,
    0,
    NULL,
    0,
    NULL
};

