
#ifndef ENGINECONTROLLER_HH
#define ENGINECONTROLLER_HH

#include "Engine.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
#include "umlrttimerid.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include "GPIOClass.hh"

class Capsule_EngineController : public UMLRTCapsule
{
public:
    Capsule_EngineController( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
    enum BorderPortId
    {
        borderport_engine,
        borderport_timer,
        borderport_log
    };
protected:
    Engine::Conj engine;
    UMLRTLogProtocol_baserole log;
    UMLRTTimerProtocol_baserole timer;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_engine,
        port_log,
        port_timer
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    UMLRTTimerId timerId;
    GPIOClass leftMotorForward;
    GPIOClass rightMotorForward;
    GPIOClass rightMotorBackwards;
    GPIOClass leftMotorBackwards;
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        IDLE,
        MOVING_BACKWARDS,
        MOVING_FORWARD,
        TURNING_LEFT,
        TURNING_RIGHT,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[6];
    State currentState;
    void entryaction_____IDLE( const UMLRTMessage * msg );
    void entryaction_____MOVING_BACKWARDS( const UMLRTMessage * msg );
    void entryaction_____MOVING_FORWARD( const UMLRTMessage * msg );
    void entryaction_____TURNING_LEFT( const UMLRTMessage * msg );
    void entryaction_____TURNING_RIGHT( const UMLRTMessage * msg );
    void exitaction_____IDLE( const UMLRTMessage * msg );
    void exitaction_____MOVING_BACKWARDS( const UMLRTMessage * msg );
    void exitaction_____MOVING_FORWARD( const UMLRTMessage * msg );
    void exitaction_____TURNING_LEFT( const UMLRTMessage * msg );
    void exitaction_____TURNING_RIGHT( const UMLRTMessage * msg );
    void transitionaction_____init( const UMLRTMessage * msg );
    void transitionaction_____stop_moving_backwards( const UMLRTMessage * msg );
    void transitionaction_____stop_moving_forward( const UMLRTMessage * msg );
    void transitionaction_____stop_turning_left( const UMLRTMessage * msg );
    void transitionaction_____stop_turning_right( const UMLRTMessage * msg );
    void transitionaction_____turn_left( const UMLRTMessage * msg );
    void transitionaction_____turn_right( const UMLRTMessage * msg );
    void actionchain_____init( const UMLRTMessage * msg );
    void actionchain_____move_backwards( const UMLRTMessage * msg );
    void actionchain_____move_forward( const UMLRTMessage * msg );
    void actionchain_____stop_moving_backwards( const UMLRTMessage * msg );
    void actionchain_____stop_moving_forward( const UMLRTMessage * msg );
    void actionchain_____stop_turning_left( const UMLRTMessage * msg );
    void actionchain_____stop_turning_right( const UMLRTMessage * msg );
    void actionchain_____turn_left( const UMLRTMessage * msg );
    void actionchain_____turn_right( const UMLRTMessage * msg );
    State state_____IDLE( const UMLRTMessage * msg );
    State state_____MOVING_BACKWARDS( const UMLRTMessage * msg );
    State state_____MOVING_FORWARD( const UMLRTMessage * msg );
    State state_____TURNING_LEFT( const UMLRTMessage * msg );
    State state_____TURNING_RIGHT( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass EngineController;

#endif

