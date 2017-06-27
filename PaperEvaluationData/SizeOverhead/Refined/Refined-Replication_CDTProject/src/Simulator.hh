
#ifndef SIMULATOR_HH
#define SIMULATOR_HH

#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
struct UMLRTCapsulePart;
struct UMLRTCommsPort;
struct UMLRTSlot;

class Capsule_Simulator : public UMLRTCapsule
{
public:
    Capsule_Simulator( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
    enum PartId
    {
        part_ENV,
        part_client,
        part_server1,
        part_server2
    };
protected:
    const UMLRTCapsulePart * const ENV;
    const UMLRTCapsulePart * const client;
    const UMLRTCapsulePart * const server1;
    const UMLRTCapsulePart * const server2;
public:
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    virtual void initialize( const UMLRTMessage & msg );
    virtual void inject( const UMLRTMessage & msg );
};
extern const UMLRTCapsuleClass Simulator;

#endif

