
#ifndef DEBUG__TOP_HH
#define DEBUG__TOP_HH

#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
struct UMLRTCapsulePart;
struct UMLRTCommsPort;
struct UMLRTSlot;

class Capsule_Debug__Top : public UMLRTCapsule
{
public:
    Capsule_Debug__Top( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
    enum PartId
    {
        part_Debug__Gateway,
        part_Debug__Top
    };
protected:
    const UMLRTCapsulePart * const Debug__Gateway;
    const UMLRTCapsulePart * const Debug__Top;
public:
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    virtual void initialize( const UMLRTMessage & msg );
    virtual void inject( const UMLRTMessage & msg );
};
extern const UMLRTCapsuleClass Debug__Top;

#endif

