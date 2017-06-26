
#include "Host.hh"

#include "umlrtslot.hh"
#include <cstddef>
#include "umlrtcapsuleclass.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_Host::Capsule_Host( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, messageID( 0.0 )
{
}


void Capsule_Host::bindPort( bool isBorder, int portId, int index )
{
}

void Capsule_Host::unbindPort( bool isBorder, int portId, int index )
{
}









void Capsule_Host::initialize( const UMLRTMessage & msg )
{
}

void Capsule_Host::inject( const UMLRTMessage & msg )
{
}


static void instantiate_Host( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_Host( &Host, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Host = 
{
    "Host",
    NULL,
    instantiate_Host,
    0,
    NULL,
    0,
    NULL,
    0,
    NULL
};

