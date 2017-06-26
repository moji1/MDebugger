
#ifndef SENSOR_HH
#define SENSOR_HH

#include "detection.hh"
#include "switchProtocol.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

class Capsule_Sensor : public UMLRTCapsule
{
public:
    Capsule_Sensor( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
    enum BorderPortId
    {
        borderport_detection,
        borderport_switchProtocol,
        borderport_log
    };
protected:
    detection::Conj detection;
    UMLRTLogProtocol_baserole log;
    switchProtocol::Base switchProtocol;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_detection,
        port_log,
        port_switchProtocol
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        IDLE,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[2];
    State currentState;
    void entryaction_____IDLE( const UMLRTMessage * msg );
    void exitaction_____IDLE( const UMLRTMessage * msg );
    void transitionaction_____TransitionAction1( const UMLRTMessage * msg );
    void actionchain_____Initial( const UMLRTMessage * msg );
    void actionchain_____TransitionAction1( const UMLRTMessage * msg );
    State state_____IDLE( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass Sensor;

#endif

