
#ifndef DOOR_HH
#define DOOR_HH

#include "Locking.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
struct UMLRTCapsulePart;
struct UMLRTCommsPort;
struct UMLRTSlot;

class Capsule_Door : public UMLRTCapsule
{
public:
    Capsule_Door( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    Locking::Base lockPort;
public:
    enum BorderPortId
    {
        borderport_lockPort
    };
    enum PartId
    {
        part_lock
    };
protected:
    const UMLRTCapsulePart * const lock;
public:
    enum PortId
    {
        port_lockPort
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    virtual void initialize( const UMLRTMessage & msg );
    virtual void inject( const UMLRTMessage & msg );
};
extern const UMLRTCapsuleClass Door;

#endif

