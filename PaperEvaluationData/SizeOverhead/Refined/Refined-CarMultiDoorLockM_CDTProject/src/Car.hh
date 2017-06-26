
#ifndef CAR_HH
#define CAR_HH

#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
struct UMLRTCapsulePart;
struct UMLRTCommsPort;
struct UMLRTSlot;

class Capsule_Car : public UMLRTCapsule
{
public:
    Capsule_Car( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
    enum PartId
    {
        part_centralLock,
        part_door1,
        part_door2,
        part_door3,
        part_door4
    };
protected:
    const UMLRTCapsulePart * const centralLock;
    const UMLRTCapsulePart * const door1;
    const UMLRTCapsulePart * const door2;
    const UMLRTCapsulePart * const door3;
    const UMLRTCapsulePart * const door4;
public:
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    virtual void initialize( const UMLRTMessage & msg );
    virtual void inject( const UMLRTMessage & msg );
};
extern const UMLRTCapsuleClass Car;

#endif

