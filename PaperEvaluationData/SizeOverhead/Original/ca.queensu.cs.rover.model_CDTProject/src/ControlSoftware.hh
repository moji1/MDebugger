
#ifndef CONTROLSOFTWARE_HH
#define CONTROLSOFTWARE_HH

#include "Detection.hh"
#include "Engine.hh"
#include "Temperature.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

class Capsule_ControlSoftware : public UMLRTCapsule
{
public:
    Capsule_ControlSoftware( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    Detection::Base detection;
public:
    enum BorderPortId
    {
        borderport_detection,
        borderport_engine,
        borderport_temperature,
        borderport_timer,
        borderport_log
    };
protected:
    Engine::Base engine;
    UMLRTLogProtocol_baserole log;
    Temperature::Base temperature;
    UMLRTTimerProtocol_baserole timer;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_detection,
        port_engine,
        port_log,
        port_temperature,
        port_timer
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    double threshold;
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        MOVING_BACKWARDS,
        MOVING_FORWARD,
        ROTATING,
        STANDBY,
        STOPPING_MOVING_BACKWARDS,
        STOPPING_MOVING_FORWARD,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[7];
    State currentState;
    void entryaction_____MOVING_BACKWARDS( const UMLRTMessage * msg );
    void entryaction_____MOVING_FORWARD( const UMLRTMessage * msg );
    void entryaction_____ROTATING( const UMLRTMessage * msg );
    void entryaction_____STANDBY( const UMLRTMessage * msg );
    void entryaction_____STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg );
    void entryaction_____STOPPING_MOVING_FORWARD( const UMLRTMessage * msg );
    void exitaction_____MOVING_BACKWARDS( const UMLRTMessage * msg );
    void exitaction_____MOVING_FORWARD( const UMLRTMessage * msg );
    void exitaction_____ROTATING( const UMLRTMessage * msg );
    void exitaction_____STANDBY( const UMLRTMessage * msg );
    void exitaction_____STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg );
    void exitaction_____STOPPING_MOVING_FORWARD( const UMLRTMessage * msg );
    void transitionaction_____greaterThan( const UMLRTMessage * msg );
    void transitionaction_____lowerThanThreshold( const UMLRTMessage * msg );
    bool action_____greaterThan__greaterThanThreshold( const UMLRTMessage * msg );
    bool action_____lowerThanThreshold__lessThanThreshold( const UMLRTMessage * msg );
    void actionchain_____greaterThan( const UMLRTMessage * msg );
    void actionchain_____init( const UMLRTMessage * msg );
    void actionchain_____lowerThanThreshold( const UMLRTMessage * msg );
    void actionchain_____moving_forward( const UMLRTMessage * msg );
    void actionchain_____stopped( const UMLRTMessage * msg );
    void actionchain_____stopped_moving_backwards( const UMLRTMessage * msg );
    void actionchain_____timeout( const UMLRTMessage * msg );
    void actionchain_____turnedRight( const UMLRTMessage * msg );
    State state_____MOVING_BACKWARDS( const UMLRTMessage * msg );
    State state_____MOVING_FORWARD( const UMLRTMessage * msg );
    State state_____ROTATING( const UMLRTMessage * msg );
    State state_____STANDBY( const UMLRTMessage * msg );
    State state_____STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg );
    State state_____STOPPING_MOVING_FORWARD( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass ControlSoftware;

#endif

