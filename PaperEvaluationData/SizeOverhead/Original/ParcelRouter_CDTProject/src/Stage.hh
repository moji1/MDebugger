
#ifndef STAGE_HH
#define STAGE_HH

#include "Parcel.hh"
#include "transmission.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
struct UMLRTCapsulePart;
struct UMLRTCommsPort;
struct UMLRTSlot;

class Capsule_Stage : public UMLRTCapsule
{
public:
    Capsule_Stage( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    transmission::Conj enter;
public:
    enum BorderPortId
    {
        borderport_enter,
        borderport_left,
        borderport_right,
        borderport_log
    };
protected:
    transmission::Base left;
    UMLRTLogProtocol_baserole log;
    transmission::Base right;
public:
    enum PartId
    {
        part_chute1,
        part_chute2,
        part_sensor,
        part_switcher
    };
protected:
    const UMLRTCapsulePart * const chute1;
    const UMLRTCapsulePart * const chute2;
    const UMLRTCapsulePart * const sensor;
    const UMLRTCapsulePart * const switcher;
public:
    enum PortId
    {
        port_enter,
        port_left,
        port_log,
        port_right
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    Parcel parcel;
    virtual void initialize( const UMLRTMessage & msg );
    virtual void inject( const UMLRTMessage & msg );
};
extern const UMLRTCapsuleClass Stage;

#endif

