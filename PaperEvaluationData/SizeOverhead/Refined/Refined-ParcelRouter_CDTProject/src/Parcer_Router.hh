
#ifndef PARCER_ROUTER_HH
#define PARCER_ROUTER_HH

#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
struct UMLRTCapsulePart;
struct UMLRTCommsPort;
struct UMLRTSlot;

class Capsule_Parcer_Router : public UMLRTCapsule
{
public:
    Capsule_Parcer_Router( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
    enum PartId
    {
        part_bin0,
        part_bin1,
        part_bin2,
        part_bin3,
        part_gen,
        part_left,
        part_right,
        part_top
    };
protected:
    const UMLRTCapsulePart * const bin0;
    const UMLRTCapsulePart * const bin1;
    const UMLRTCapsulePart * const bin2;
    const UMLRTCapsulePart * const bin3;
    const UMLRTCapsulePart * const gen;
    const UMLRTCapsulePart * const left;
    const UMLRTCapsulePart * const right;
    const UMLRTCapsulePart * const top;
public:
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    virtual void initialize( const UMLRTMessage & msg );
    virtual void inject( const UMLRTMessage & msg );
};
extern const UMLRTCapsuleClass Parcer_Router;

#endif

