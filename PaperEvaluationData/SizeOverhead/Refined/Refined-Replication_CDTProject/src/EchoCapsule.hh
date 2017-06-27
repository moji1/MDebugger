
#ifndef ECHOCAPSULE_HH
#define ECHOCAPSULE_HH

#include "Echo.hh"
#include "ExtInterface.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include "Event.h"

#include "SROManager.h"

class Capsule_EchoCapsule : public UMLRTCapsule
{
public:
    Capsule_EchoCapsule( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    Echo::Base Echo;
public:
    enum BorderPortId
    {
        borderport_Echo,
        borderport_extComm
    };
protected:
    ExtInterface::Conj extComm;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_Echo,
        port_extComm
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    bool Debug__flag;
    char * Debug__variablesData;
    debugEvents::Event Debug__event;
    SROManager Debug__SRO;
    void Debug__variablesView();
    bool Debug__variablesChange( char * varName, char * varValue );
    void Debug__sendEvent( debugEvents::EVENTSOURCEKIND eventSourceKind, debugEvents::EVENTTYPE eventType, const char * instanceName, int capsuleIndex, const char * signalName, char * capsuleName, char * sourceName, char * reserve1, char * reserve2, char * reserve3 );
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        Debug__C__DoEcho,
        Debug__C__init__WaitForEcho__1,
        Debug__C__DoEcho__Debug__A__Ac__DoEcho,
        Debug__C__DoEcho__Debug__A__En__WaitForEcho,
        Debug__C__DoEcho__Debug__B__Ac__DoEcho,
        Debug__C__DoEcho__Debug__B__Ex__WaitForEcho,
        Debug__C__DoEcho__boundary,
        Debug__C__init__WaitForEcho__1__Debug__A__Ac__init__WaitForEcho__1,
        Debug__C__init__WaitForEcho__1__Debug__A__En__init__WaitForEcho__1,
        Debug__C__init__WaitForEcho__1__Debug__B__Ac__init__WaitForEcho__1,
        Debug__C__init__WaitForEcho__1__boundary,
        Debug__InitState,
        WaitForEcho,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[14];
    State currentState;
    State history[2];
    void save_history( State compositeState, State subState );
    bool check_history( State compositeState, State subState );
    void entryaction_____Debug__C__DoEcho__Debug__A__Ac__DoEcho( const UMLRTMessage * msg );
    void entryaction_____Debug__C__DoEcho__Debug__A__En__WaitForEcho( const UMLRTMessage * msg );
    void entryaction_____Debug__C__DoEcho__Debug__B__Ac__DoEcho( const UMLRTMessage * msg );
    void entryaction_____Debug__C__DoEcho__Debug__B__Ex__WaitForEcho( const UMLRTMessage * msg );
    void entryaction_____Debug__C__DoEcho__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__init__WaitForEcho__1__Debug__A__Ac__init__WaitForEcho__1( const UMLRTMessage * msg );
    void entryaction_____Debug__C__init__WaitForEcho__1__Debug__A__En__init__WaitForEcho__1( const UMLRTMessage * msg );
    void entryaction_____Debug__C__init__WaitForEcho__1__Debug__B__Ac__init__WaitForEcho__1( const UMLRTMessage * msg );
    void entryaction_____Debug__C__init__WaitForEcho__1__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__InitState( const UMLRTMessage * msg );
    void entryaction_____WaitForEcho( const UMLRTMessage * msg );
    void exitaction_____Debug__C__DoEcho__Debug__A__Ac__DoEcho( const UMLRTMessage * msg );
    void exitaction_____Debug__C__DoEcho__Debug__A__En__WaitForEcho( const UMLRTMessage * msg );
    void exitaction_____Debug__C__DoEcho__Debug__B__Ac__DoEcho( const UMLRTMessage * msg );
    void exitaction_____Debug__C__DoEcho__Debug__B__Ex__WaitForEcho( const UMLRTMessage * msg );
    void exitaction_____Debug__C__DoEcho__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__WaitForEcho__1__Debug__A__Ac__init__WaitForEcho__1( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__WaitForEcho__1__Debug__A__En__init__WaitForEcho__1( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__WaitForEcho__1__Debug__B__Ac__init__WaitForEcho__1( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__WaitForEcho__1__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__InitState( const UMLRTMessage * msg );
    void exitaction_____WaitForEcho( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__DoEcho__Debug__AC__DoEcho( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__DoEcho__Debug__En__WaitForEcho( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__DoEcho__Debug__Ex__WaitForEcho( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__DoEcho__Debug__end__trans__DoEcho( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__DoEcho__Debug__init__trans__DoEcho( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__WaitForEcho__1__Debug__Ac__init__WaitForEcho__1( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__WaitForEcho__1__Debug__En__WaitForEcho( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__WaitForEcho__1__Debug__end__trans__init__WaitForEcho__1( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__WaitForEcho__1__Debug__init__trans__init__WaitForEcho__1( const UMLRTMessage * msg );
    void transitionaction_____Debug__DoEcho( const UMLRTMessage * msg );
    void transitionaction_____Debug__DoEcho__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__DoEcho__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__DoEcho__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__InitDebug( const UMLRTMessage * msg );
    void transitionaction_____Debug__init__WaitForEcho__1( const UMLRTMessage * msg );
    void transitionaction_____Debug__init__WaitForEcho__1__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__init__WaitForEcho__1__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__init__WaitForEcho__1__dbg( const UMLRTMessage * msg );
    void transitionaction_____DoEcho( const UMLRTMessage * msg );
    void transitionaction_____init__WaitForEcho__1( const UMLRTMessage * msg );
    bool action_____Debug__DoEcho__S__Debug__GuardDoEcho( const UMLRTMessage * msg );
    bool action_____Debug__init__WaitForEcho__1__S__Debug__Guardinit__WaitForEcho__1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__DoEcho__Debug__AC__DoEcho( const UMLRTMessage * msg );
    void actionchain_____Debug__C__DoEcho__Debug__En__WaitForEcho( const UMLRTMessage * msg );
    void actionchain_____Debug__C__DoEcho__Debug__Ex__WaitForEcho( const UMLRTMessage * msg );
    void actionchain_____Debug__C__DoEcho__Debug__end__trans__DoEcho( const UMLRTMessage * msg );
    void actionchain_____Debug__C__DoEcho__Debug__init__trans__DoEcho( const UMLRTMessage * msg );
    void actionchain_____Debug__C__DoEcho__new_transition_1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__DoEcho__new_transition_10( const UMLRTMessage * msg );
    void actionchain_____Debug__C__DoEcho__new_transition_2( const UMLRTMessage * msg );
    void actionchain_____Debug__C__DoEcho__new_transition_3( const UMLRTMessage * msg );
    void actionchain_____Debug__C__DoEcho__new_transition_4( const UMLRTMessage * msg );
    void actionchain_____Debug__C__DoEcho__new_transition_5_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__DoEcho__new_transition_6( const UMLRTMessage * msg );
    void actionchain_____Debug__C__DoEcho__new_transition_7( const UMLRTMessage * msg );
    void actionchain_____Debug__C__DoEcho__new_transition_8( const UMLRTMessage * msg );
    void actionchain_____Debug__C__DoEcho__new_transition_9( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__WaitForEcho__1__Debug__Ac__init__WaitForEcho__1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__WaitForEcho__1__Debug__En__WaitForEcho( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__WaitForEcho__1__Debug__end__trans__init__WaitForEcho__1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__WaitForEcho__1__Debug__init__trans__init__WaitForEcho__1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__WaitForEcho__1__new_transition_11( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__WaitForEcho__1__new_transition_12( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__WaitForEcho__1__new_transition_13( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__WaitForEcho__1__new_transition_14_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__WaitForEcho__1__new_transition_15( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__WaitForEcho__1__new_transition_16( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__WaitForEcho__1__new_transition_17( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__WaitForEcho__1__new_transition_18( const UMLRTMessage * msg );
    void actionchain_____Debug__DoEcho( const UMLRTMessage * msg );
    void actionchain_____Debug__DoEcho__E( const UMLRTMessage * msg );
    void actionchain_____Debug__DoEcho__S( const UMLRTMessage * msg );
    void actionchain_____Debug__DoEcho__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__InitDebug( const UMLRTMessage * msg );
    void actionchain_____Debug__init__WaitForEcho__1( const UMLRTMessage * msg );
    void actionchain_____Debug__init__WaitForEcho__1__E( const UMLRTMessage * msg );
    void actionchain_____Debug__init__WaitForEcho__1__S( const UMLRTMessage * msg );
    void actionchain_____Debug__init__WaitForEcho__1__dbg( const UMLRTMessage * msg );
    void actionchain_____DoEcho( const UMLRTMessage * msg );
    void actionchain_____init__WaitForEcho__1( const UMLRTMessage * msg );
    State junction_____Debug__C__DoEcho__en( const UMLRTMessage * msg );
    State junction_____Debug__C__DoEcho__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__DoEcho__new_exitpoint_1( const UMLRTMessage * msg );
    State junction_____Debug__C__init__WaitForEcho__1__en( const UMLRTMessage * msg );
    State junction_____Debug__C__init__WaitForEcho__1__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__init__WaitForEcho__1__new_exitpoint_2( const UMLRTMessage * msg );
    State choice_____Debug__C__DoEcho__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__init__WaitForEcho__1__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__Path__DoEcho( const UMLRTMessage * msg );
    State choice_____Debug__Path__init__WaitForEcho__1( const UMLRTMessage * msg );
    State state_____Debug__C__DoEcho__Debug__A__Ac__DoEcho( const UMLRTMessage * msg );
    State state_____Debug__C__DoEcho__Debug__A__En__WaitForEcho( const UMLRTMessage * msg );
    State state_____Debug__C__DoEcho__Debug__B__Ac__DoEcho( const UMLRTMessage * msg );
    State state_____Debug__C__DoEcho__Debug__B__Ex__WaitForEcho( const UMLRTMessage * msg );
    State state_____Debug__C__DoEcho__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__init__WaitForEcho__1__Debug__A__Ac__init__WaitForEcho__1( const UMLRTMessage * msg );
    State state_____Debug__C__init__WaitForEcho__1__Debug__A__En__init__WaitForEcho__1( const UMLRTMessage * msg );
    State state_____Debug__C__init__WaitForEcho__1__Debug__B__Ac__init__WaitForEcho__1( const UMLRTMessage * msg );
    State state_____Debug__C__init__WaitForEcho__1__boundary( const UMLRTMessage * msg );
    State state_____Debug__InitState( const UMLRTMessage * msg );
    State state_____WaitForEcho( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass EchoCapsule;

#endif

