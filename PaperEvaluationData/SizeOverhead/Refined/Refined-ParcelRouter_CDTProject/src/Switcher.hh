
#ifndef SWITCHER_HH
#define SWITCHER_HH

#include "ExtInterface.hh"
#include "Parcel.hh"
#include "switchProtocol.hh"
#include "transmission.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include "Event.h"

#include "SROManager.h"

class Capsule_Switcher : public UMLRTCapsule
{
public:
    Capsule_Switcher( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
    enum BorderPortId
    {
        borderport_left,
        borderport_right,
        borderport_enter,
        borderport_switchProtocol,
        borderport_extComm,
        borderport_timer,
        borderport_log
    };
protected:
    transmission::Conj enter;
    ExtInterface::Conj extComm;
    transmission::Base left;
    UMLRTLogProtocol_baserole log;
    transmission::Base right;
    switchProtocol::Conj switchProtocol;
    UMLRTTimerProtocol_baserole timer;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_enter,
        port_extComm,
        port_left,
        port_log,
        port_right,
        port_switchProtocol,
        port_timer
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    int choice;
    Parcel parcel;
    bool leftSuccessorFree;
    bool rightSuccessorFree;
    int delay;
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
        Debug__C__IDLE__IDLE__4,
        Debug__C__IDLE__IDLE__6,
        Debug__C__IDLE__IDLE__9,
        Debug__C__Initial,
        Debug__C__Jam____IDLE__5,
        Debug__C__Jam____OCCUPIED__7,
        Debug__C__OCCUPIED__OCCUPIED__10,
        Debug__C__OCCUPIED__OCCUPIED__11,
        Debug__C__OCCUPIED__OCCUPIED__3,
        Debug__C__reception,
        Debug__C__transmission,
        Debug__C__IDLE__IDLE__4__Debug__A__Ac__IDLE__IDLE__4,
        Debug__C__IDLE__IDLE__4__Debug__A__En__IDLE,
        Debug__C__IDLE__IDLE__4__Debug__B__Ac__IDLE__IDLE__4,
        Debug__C__IDLE__IDLE__4__Debug__B__Ex__IDLE,
        Debug__C__IDLE__IDLE__4__boundary,
        Debug__C__IDLE__IDLE__6__Debug__A__Ac__IDLE__IDLE__6,
        Debug__C__IDLE__IDLE__6__Debug__A__En__IDLE,
        Debug__C__IDLE__IDLE__6__Debug__B__Ac__IDLE__IDLE__6,
        Debug__C__IDLE__IDLE__6__Debug__B__Ex__IDLE,
        Debug__C__IDLE__IDLE__6__boundary,
        Debug__C__IDLE__IDLE__9__Debug__A__Ac__IDLE__IDLE__9,
        Debug__C__IDLE__IDLE__9__Debug__A__En__IDLE,
        Debug__C__IDLE__IDLE__9__Debug__B__Ac__IDLE__IDLE__9,
        Debug__C__IDLE__IDLE__9__Debug__B__Ex__IDLE,
        Debug__C__IDLE__IDLE__9__boundary,
        Debug__C__Initial__Debug__A__Ac__Initial,
        Debug__C__Initial__Debug__A__En__Initial,
        Debug__C__Initial__Debug__B__Ac__Initial,
        Debug__C__Initial__boundary,
        Debug__C__Jam____IDLE__5__Debug__A__Ac__Jam____IDLE__5,
        Debug__C__Jam____IDLE__5__Debug__A__En__Jam____IDLE__5,
        Debug__C__Jam____IDLE__5__Debug__B__Ac__Jam____IDLE__5,
        Debug__C__Jam____IDLE__5__boundary,
        Debug__C__Jam____OCCUPIED__7__Debug__A__Ac__Jam____OCCUPIED__7,
        Debug__C__Jam____OCCUPIED__7__Debug__A__En__Jam____OCCUPIED__7,
        Debug__C__Jam____OCCUPIED__7__Debug__B__Ac__Jam____OCCUPIED__7,
        Debug__C__Jam____OCCUPIED__7__boundary,
        Debug__C__OCCUPIED__OCCUPIED__10__Debug__A__Ac__OCCUPIED__OCCUPIED__10,
        Debug__C__OCCUPIED__OCCUPIED__10__Debug__A__En__OCCUPIED,
        Debug__C__OCCUPIED__OCCUPIED__10__Debug__B__Ac__OCCUPIED__OCCUPIED__10,
        Debug__C__OCCUPIED__OCCUPIED__10__Debug__B__Ex__OCCUPIED,
        Debug__C__OCCUPIED__OCCUPIED__10__boundary,
        Debug__C__OCCUPIED__OCCUPIED__11__Debug__A__Ac__OCCUPIED__OCCUPIED__11,
        Debug__C__OCCUPIED__OCCUPIED__11__Debug__A__En__OCCUPIED,
        Debug__C__OCCUPIED__OCCUPIED__11__Debug__B__Ac__OCCUPIED__OCCUPIED__11,
        Debug__C__OCCUPIED__OCCUPIED__11__Debug__B__Ex__OCCUPIED,
        Debug__C__OCCUPIED__OCCUPIED__11__boundary,
        Debug__C__OCCUPIED__OCCUPIED__3__Debug__A__Ac__OCCUPIED__OCCUPIED__3,
        Debug__C__OCCUPIED__OCCUPIED__3__Debug__A__En__OCCUPIED,
        Debug__C__OCCUPIED__OCCUPIED__3__Debug__B__Ac__OCCUPIED__OCCUPIED__3,
        Debug__C__OCCUPIED__OCCUPIED__3__Debug__B__Ex__OCCUPIED,
        Debug__C__OCCUPIED__OCCUPIED__3__boundary,
        Debug__C__reception__Debug__A__Ac__reception,
        Debug__C__reception__Debug__A__En__OCCUPIED,
        Debug__C__reception__Debug__B__Ac__reception,
        Debug__C__reception__Debug__B__Ex__IDLE,
        Debug__C__reception__boundary,
        Debug__C__transmission__Debug__A__Ac__transmission,
        Debug__C__transmission__Debug__B__Ac__transmission,
        Debug__C__transmission__Debug__B__Ex__OCCUPIED,
        Debug__C__transmission__boundary,
        Debug__InitState,
        IDLE,
        OCCUPIED,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[66];
    State currentState;
    State history[11];
    void save_history( State compositeState, State subState );
    bool check_history( State compositeState, State subState );
    void entryaction_____Debug__C__IDLE__IDLE__4__Debug__A__Ac__IDLE__IDLE__4( const UMLRTMessage * msg );
    void entryaction_____Debug__C__IDLE__IDLE__4__Debug__A__En__IDLE( const UMLRTMessage * msg );
    void entryaction_____Debug__C__IDLE__IDLE__4__Debug__B__Ac__IDLE__IDLE__4( const UMLRTMessage * msg );
    void entryaction_____Debug__C__IDLE__IDLE__4__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void entryaction_____Debug__C__IDLE__IDLE__4__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__IDLE__IDLE__6__Debug__A__Ac__IDLE__IDLE__6( const UMLRTMessage * msg );
    void entryaction_____Debug__C__IDLE__IDLE__6__Debug__A__En__IDLE( const UMLRTMessage * msg );
    void entryaction_____Debug__C__IDLE__IDLE__6__Debug__B__Ac__IDLE__IDLE__6( const UMLRTMessage * msg );
    void entryaction_____Debug__C__IDLE__IDLE__6__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void entryaction_____Debug__C__IDLE__IDLE__6__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__IDLE__IDLE__9__Debug__A__Ac__IDLE__IDLE__9( const UMLRTMessage * msg );
    void entryaction_____Debug__C__IDLE__IDLE__9__Debug__A__En__IDLE( const UMLRTMessage * msg );
    void entryaction_____Debug__C__IDLE__IDLE__9__Debug__B__Ac__IDLE__IDLE__9( const UMLRTMessage * msg );
    void entryaction_____Debug__C__IDLE__IDLE__9__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void entryaction_____Debug__C__IDLE__IDLE__9__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Jam____IDLE__5__Debug__A__Ac__Jam____IDLE__5( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Jam____IDLE__5__Debug__A__En__Jam____IDLE__5( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Jam____IDLE__5__Debug__B__Ac__Jam____IDLE__5( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Jam____IDLE__5__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Jam____OCCUPIED__7__Debug__A__Ac__Jam____OCCUPIED__7( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Jam____OCCUPIED__7__Debug__A__En__Jam____OCCUPIED__7( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Jam____OCCUPIED__7__Debug__B__Ac__Jam____OCCUPIED__7( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Jam____OCCUPIED__7__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__OCCUPIED__OCCUPIED__10__Debug__A__Ac__OCCUPIED__OCCUPIED__10( const UMLRTMessage * msg );
    void entryaction_____Debug__C__OCCUPIED__OCCUPIED__10__Debug__A__En__OCCUPIED( const UMLRTMessage * msg );
    void entryaction_____Debug__C__OCCUPIED__OCCUPIED__10__Debug__B__Ac__OCCUPIED__OCCUPIED__10( const UMLRTMessage * msg );
    void entryaction_____Debug__C__OCCUPIED__OCCUPIED__10__Debug__B__Ex__OCCUPIED( const UMLRTMessage * msg );
    void entryaction_____Debug__C__OCCUPIED__OCCUPIED__10__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__OCCUPIED__OCCUPIED__11__Debug__A__Ac__OCCUPIED__OCCUPIED__11( const UMLRTMessage * msg );
    void entryaction_____Debug__C__OCCUPIED__OCCUPIED__11__Debug__A__En__OCCUPIED( const UMLRTMessage * msg );
    void entryaction_____Debug__C__OCCUPIED__OCCUPIED__11__Debug__B__Ac__OCCUPIED__OCCUPIED__11( const UMLRTMessage * msg );
    void entryaction_____Debug__C__OCCUPIED__OCCUPIED__11__Debug__B__Ex__OCCUPIED( const UMLRTMessage * msg );
    void entryaction_____Debug__C__OCCUPIED__OCCUPIED__11__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__OCCUPIED__OCCUPIED__3__Debug__A__Ac__OCCUPIED__OCCUPIED__3( const UMLRTMessage * msg );
    void entryaction_____Debug__C__OCCUPIED__OCCUPIED__3__Debug__A__En__OCCUPIED( const UMLRTMessage * msg );
    void entryaction_____Debug__C__OCCUPIED__OCCUPIED__3__Debug__B__Ac__OCCUPIED__OCCUPIED__3( const UMLRTMessage * msg );
    void entryaction_____Debug__C__OCCUPIED__OCCUPIED__3__Debug__B__Ex__OCCUPIED( const UMLRTMessage * msg );
    void entryaction_____Debug__C__OCCUPIED__OCCUPIED__3__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__reception__Debug__A__Ac__reception( const UMLRTMessage * msg );
    void entryaction_____Debug__C__reception__Debug__A__En__OCCUPIED( const UMLRTMessage * msg );
    void entryaction_____Debug__C__reception__Debug__B__Ac__reception( const UMLRTMessage * msg );
    void entryaction_____Debug__C__reception__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void entryaction_____Debug__C__reception__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__transmission__Debug__A__Ac__transmission( const UMLRTMessage * msg );
    void entryaction_____Debug__C__transmission__Debug__B__Ac__transmission( const UMLRTMessage * msg );
    void entryaction_____Debug__C__transmission__Debug__B__Ex__OCCUPIED( const UMLRTMessage * msg );
    void entryaction_____Debug__C__transmission__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__InitState( const UMLRTMessage * msg );
    void entryaction_____IDLE( const UMLRTMessage * msg );
    void entryaction_____OCCUPIED( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__4__Debug__A__Ac__IDLE__IDLE__4( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__4__Debug__A__En__IDLE( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__4__Debug__B__Ac__IDLE__IDLE__4( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__4__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__4__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__6__Debug__A__Ac__IDLE__IDLE__6( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__6__Debug__A__En__IDLE( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__6__Debug__B__Ac__IDLE__IDLE__6( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__6__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__6__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__9__Debug__A__Ac__IDLE__IDLE__9( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__9__Debug__A__En__IDLE( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__9__Debug__B__Ac__IDLE__IDLE__9( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__9__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__9__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Jam____IDLE__5__Debug__A__Ac__Jam____IDLE__5( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Jam____IDLE__5__Debug__A__En__Jam____IDLE__5( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Jam____IDLE__5__Debug__B__Ac__Jam____IDLE__5( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Jam____IDLE__5__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Jam____OCCUPIED__7__Debug__A__Ac__Jam____OCCUPIED__7( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Jam____OCCUPIED__7__Debug__A__En__Jam____OCCUPIED__7( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Jam____OCCUPIED__7__Debug__B__Ac__Jam____OCCUPIED__7( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Jam____OCCUPIED__7__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__OCCUPIED__OCCUPIED__10__Debug__A__Ac__OCCUPIED__OCCUPIED__10( const UMLRTMessage * msg );
    void exitaction_____Debug__C__OCCUPIED__OCCUPIED__10__Debug__A__En__OCCUPIED( const UMLRTMessage * msg );
    void exitaction_____Debug__C__OCCUPIED__OCCUPIED__10__Debug__B__Ac__OCCUPIED__OCCUPIED__10( const UMLRTMessage * msg );
    void exitaction_____Debug__C__OCCUPIED__OCCUPIED__10__Debug__B__Ex__OCCUPIED( const UMLRTMessage * msg );
    void exitaction_____Debug__C__OCCUPIED__OCCUPIED__10__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__OCCUPIED__OCCUPIED__11__Debug__A__Ac__OCCUPIED__OCCUPIED__11( const UMLRTMessage * msg );
    void exitaction_____Debug__C__OCCUPIED__OCCUPIED__11__Debug__A__En__OCCUPIED( const UMLRTMessage * msg );
    void exitaction_____Debug__C__OCCUPIED__OCCUPIED__11__Debug__B__Ac__OCCUPIED__OCCUPIED__11( const UMLRTMessage * msg );
    void exitaction_____Debug__C__OCCUPIED__OCCUPIED__11__Debug__B__Ex__OCCUPIED( const UMLRTMessage * msg );
    void exitaction_____Debug__C__OCCUPIED__OCCUPIED__11__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__OCCUPIED__OCCUPIED__3__Debug__A__Ac__OCCUPIED__OCCUPIED__3( const UMLRTMessage * msg );
    void exitaction_____Debug__C__OCCUPIED__OCCUPIED__3__Debug__A__En__OCCUPIED( const UMLRTMessage * msg );
    void exitaction_____Debug__C__OCCUPIED__OCCUPIED__3__Debug__B__Ac__OCCUPIED__OCCUPIED__3( const UMLRTMessage * msg );
    void exitaction_____Debug__C__OCCUPIED__OCCUPIED__3__Debug__B__Ex__OCCUPIED( const UMLRTMessage * msg );
    void exitaction_____Debug__C__OCCUPIED__OCCUPIED__3__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__reception__Debug__A__Ac__reception( const UMLRTMessage * msg );
    void exitaction_____Debug__C__reception__Debug__A__En__OCCUPIED( const UMLRTMessage * msg );
    void exitaction_____Debug__C__reception__Debug__B__Ac__reception( const UMLRTMessage * msg );
    void exitaction_____Debug__C__reception__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void exitaction_____Debug__C__reception__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__transmission__Debug__A__Ac__transmission( const UMLRTMessage * msg );
    void exitaction_____Debug__C__transmission__Debug__B__Ac__transmission( const UMLRTMessage * msg );
    void exitaction_____Debug__C__transmission__Debug__B__Ex__OCCUPIED( const UMLRTMessage * msg );
    void exitaction_____Debug__C__transmission__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__InitState( const UMLRTMessage * msg );
    void exitaction_____IDLE( const UMLRTMessage * msg );
    void exitaction_____OCCUPIED( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__4__Debug__AC__IDLE__IDLE__4( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__4__Debug__En__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__4__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__4__Debug__end__trans__IDLE__IDLE__4( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__4__Debug__init__trans__IDLE__IDLE__4( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__6__Debug__AC__IDLE__IDLE__6( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__6__Debug__En__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__6__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__6__Debug__end__trans__IDLE__IDLE__6( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__6__Debug__init__trans__IDLE__IDLE__6( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__9__Debug__AC__IDLE__IDLE__9( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__9__Debug__En__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__9__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__9__Debug__end__trans__IDLE__IDLE__9( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__9__Debug__init__trans__IDLE__IDLE__9( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__En__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Jam____IDLE__5__Debug__Ac__Jam____IDLE__5( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Jam____IDLE__5__Debug__En__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Jam____IDLE__5__Debug__end__trans__Jam____IDLE__5( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Jam____IDLE__5__Debug__init__trans__Jam____IDLE__5( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Jam____OCCUPIED__7__Debug__Ac__Jam____OCCUPIED__7( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Jam____OCCUPIED__7__Debug__En__OCCUPIED( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Jam____OCCUPIED__7__Debug__end__trans__Jam____OCCUPIED__7( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Jam____OCCUPIED__7__Debug__init__trans__Jam____OCCUPIED__7( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__OCCUPIED__OCCUPIED__10__Debug__AC__OCCUPIED__OCCUPIED__10( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__OCCUPIED__OCCUPIED__10__Debug__En__OCCUPIED( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__OCCUPIED__OCCUPIED__10__Debug__Ex__OCCUPIED( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__OCCUPIED__OCCUPIED__10__Debug__end__trans__OCCUPIED__OCCUPIED__10( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__OCCUPIED__OCCUPIED__10__Debug__init__trans__OCCUPIED__OCCUPIED__10( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__OCCUPIED__OCCUPIED__11__Debug__AC__OCCUPIED__OCCUPIED__11( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__OCCUPIED__OCCUPIED__11__Debug__En__OCCUPIED( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__OCCUPIED__OCCUPIED__11__Debug__Ex__OCCUPIED( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__OCCUPIED__OCCUPIED__11__Debug__end__trans__OCCUPIED__OCCUPIED__11( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__OCCUPIED__OCCUPIED__11__Debug__init__trans__OCCUPIED__OCCUPIED__11( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__OCCUPIED__OCCUPIED__3__Debug__AC__OCCUPIED__OCCUPIED__3( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__OCCUPIED__OCCUPIED__3__Debug__En__OCCUPIED( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__OCCUPIED__OCCUPIED__3__Debug__Ex__OCCUPIED( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__OCCUPIED__OCCUPIED__3__Debug__end__trans__OCCUPIED__OCCUPIED__3( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__OCCUPIED__OCCUPIED__3__Debug__init__trans__OCCUPIED__OCCUPIED__3( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__reception__Debug__AC__reception( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__reception__Debug__En__OCCUPIED( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__reception__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__reception__Debug__end__trans__reception( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__reception__Debug__init__trans__reception( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__transmission__Debug__AC__transmission( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__transmission__Debug__Ex__OCCUPIED( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__transmission__Debug__end__trans__transmission( const UMLRTMessage * msg );
    void transitionaction_____Debug__IDLE__IDLE__4( const UMLRTMessage * msg );
    void transitionaction_____Debug__IDLE__IDLE__4__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__IDLE__IDLE__4__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__IDLE__IDLE__4__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__IDLE__IDLE__6( const UMLRTMessage * msg );
    void transitionaction_____Debug__IDLE__IDLE__6__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__IDLE__IDLE__6__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__IDLE__IDLE__6__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__IDLE__IDLE__9( const UMLRTMessage * msg );
    void transitionaction_____Debug__IDLE__IDLE__9__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__IDLE__IDLE__9__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__IDLE__IDLE__9__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__InitDebug( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__Jam____IDLE__5( const UMLRTMessage * msg );
    void transitionaction_____Debug__Jam____IDLE__5__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__Jam____IDLE__5__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__Jam____IDLE__5__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__Jam____OCCUPIED__7( const UMLRTMessage * msg );
    void transitionaction_____Debug__Jam____OCCUPIED__7__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__Jam____OCCUPIED__7__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__Jam____OCCUPIED__7__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__OCCUPIED__OCCUPIED__10( const UMLRTMessage * msg );
    void transitionaction_____Debug__OCCUPIED__OCCUPIED__10__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__OCCUPIED__OCCUPIED__10__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__OCCUPIED__OCCUPIED__10__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__OCCUPIED__OCCUPIED__11( const UMLRTMessage * msg );
    void transitionaction_____Debug__OCCUPIED__OCCUPIED__11__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__OCCUPIED__OCCUPIED__11__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__OCCUPIED__OCCUPIED__11__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__OCCUPIED__OCCUPIED__3( const UMLRTMessage * msg );
    void transitionaction_____Debug__OCCUPIED__OCCUPIED__3__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__OCCUPIED__OCCUPIED__3__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__OCCUPIED__OCCUPIED__3__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__reception( const UMLRTMessage * msg );
    void transitionaction_____Debug__reception__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__reception__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__reception__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__transmission( const UMLRTMessage * msg );
    void transitionaction_____Debug__transmission__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__transmission__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__transmission__dbg( const UMLRTMessage * msg );
    void transitionaction_____IDLE__IDLE__4( const UMLRTMessage * msg );
    void transitionaction_____IDLE__IDLE__6( const UMLRTMessage * msg );
    void transitionaction_____IDLE__IDLE__9( const UMLRTMessage * msg );
    void transitionaction_____Initial( const UMLRTMessage * msg );
    void transitionaction_____Jam____IDLE__5( const UMLRTMessage * msg );
    void transitionaction_____Jam____OCCUPIED__7( const UMLRTMessage * msg );
    void transitionaction_____OCCUPIED__OCCUPIED__10( const UMLRTMessage * msg );
    void transitionaction_____OCCUPIED__OCCUPIED__11( const UMLRTMessage * msg );
    void transitionaction_____OCCUPIED__OCCUPIED__3( const UMLRTMessage * msg );
    void transitionaction_____reception( const UMLRTMessage * msg );
    void transitionaction_____transmission( const UMLRTMessage * msg );
    bool action_____Debug__IDLE__IDLE__4__S__Debug__GuardIDLE__IDLE__4( const UMLRTMessage * msg );
    bool action_____Debug__IDLE__IDLE__6__S__Debug__GuardIDLE__IDLE__6( const UMLRTMessage * msg );
    bool action_____Debug__IDLE__IDLE__9__S__Debug__GuardIDLE__IDLE__9( const UMLRTMessage * msg );
    bool action_____Debug__Initial__S__Debug__GuardInitial( const UMLRTMessage * msg );
    bool action_____Debug__Jam____IDLE__5__S__Debug__GuardJam____IDLE__5( const UMLRTMessage * msg );
    bool action_____Debug__Jam____IDLE__5__null( const UMLRTMessage * msg );
    bool action_____Debug__Jam____OCCUPIED__7__S__Debug__GuardJam____OCCUPIED__7( const UMLRTMessage * msg );
    bool action_____Debug__Jam____OCCUPIED__7__null( const UMLRTMessage * msg );
    bool action_____Debug__OCCUPIED__OCCUPIED__10__S__Debug__GuardOCCUPIED__OCCUPIED__10( const UMLRTMessage * msg );
    bool action_____Debug__OCCUPIED__OCCUPIED__11__S__Debug__GuardOCCUPIED__OCCUPIED__11( const UMLRTMessage * msg );
    bool action_____Debug__OCCUPIED__OCCUPIED__3__S__Debug__GuardOCCUPIED__OCCUPIED__3( const UMLRTMessage * msg );
    bool action_____Debug__reception__S__Debug__Guardreception( const UMLRTMessage * msg );
    bool action_____Debug__transmission__S__Debug__Guardtransmission( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__4__Debug__AC__IDLE__IDLE__4( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__4__Debug__En__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__4__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__4__Debug__end__trans__IDLE__IDLE__4( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__4__Debug__init__trans__IDLE__IDLE__4( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__4__new_transition_11( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__4__new_transition_12( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__4__new_transition_13( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__4__new_transition_14( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__4__new_transition_15_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__4__new_transition_16( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__4__new_transition_17( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__4__new_transition_18( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__4__new_transition_19( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__4__new_transition_20( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__6__Debug__AC__IDLE__IDLE__6( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__6__Debug__En__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__6__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__6__Debug__end__trans__IDLE__IDLE__6( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__6__Debug__init__trans__IDLE__IDLE__6( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__6__new_transition_39( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__6__new_transition_40( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__6__new_transition_41( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__6__new_transition_42( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__6__new_transition_43_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__6__new_transition_44( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__6__new_transition_45( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__6__new_transition_46( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__6__new_transition_47( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__6__new_transition_48( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__9__Debug__AC__IDLE__IDLE__9( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__9__Debug__En__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__9__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__9__Debug__end__trans__IDLE__IDLE__9( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__9__Debug__init__trans__IDLE__IDLE__9( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__9__new_transition_73( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__9__new_transition_74( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__9__new_transition_75( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__9__new_transition_76( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__9__new_transition_77_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__9__new_transition_78( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__9__new_transition_79( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__9__new_transition_80( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__9__new_transition_81( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__9__new_transition_82( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__Debug__En__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_65( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_66( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_67( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_68_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_69( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_70( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_71( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_72( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____IDLE__5__Debug__Ac__Jam____IDLE__5( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____IDLE__5__Debug__En__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____IDLE__5__Debug__end__trans__Jam____IDLE__5( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____IDLE__5__Debug__init__trans__Jam____IDLE__5( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____IDLE__5__new_transition_21( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____IDLE__5__new_transition_22( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____IDLE__5__new_transition_23( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____IDLE__5__new_transition_24_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____IDLE__5__new_transition_25( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____IDLE__5__new_transition_26( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____IDLE__5__new_transition_27( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____IDLE__5__new_transition_28( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____OCCUPIED__7__Debug__Ac__Jam____OCCUPIED__7( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____OCCUPIED__7__Debug__En__OCCUPIED( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____OCCUPIED__7__Debug__end__trans__Jam____OCCUPIED__7( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____OCCUPIED__7__Debug__init__trans__Jam____OCCUPIED__7( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____OCCUPIED__7__new_transition_49( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____OCCUPIED__7__new_transition_50( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____OCCUPIED__7__new_transition_51( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____OCCUPIED__7__new_transition_52_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____OCCUPIED__7__new_transition_53( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____OCCUPIED__7__new_transition_54( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____OCCUPIED__7__new_transition_55( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Jam____OCCUPIED__7__new_transition_56( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__10__Debug__AC__OCCUPIED__OCCUPIED__10( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__10__Debug__En__OCCUPIED( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__10__Debug__Ex__OCCUPIED( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__10__Debug__end__trans__OCCUPIED__OCCUPIED__10( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__10__Debug__init__trans__OCCUPIED__OCCUPIED__10( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__10__new_transition_83( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__10__new_transition_84( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__10__new_transition_85( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__10__new_transition_86( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__10__new_transition_87_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__10__new_transition_88( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__10__new_transition_89( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__10__new_transition_90( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__10__new_transition_91( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__10__new_transition_92( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__11__Debug__AC__OCCUPIED__OCCUPIED__11( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__11__Debug__En__OCCUPIED( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__11__Debug__Ex__OCCUPIED( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__11__Debug__end__trans__OCCUPIED__OCCUPIED__11( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__11__Debug__init__trans__OCCUPIED__OCCUPIED__11( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__11__new_transition_100( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__11__new_transition_101( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__11__new_transition_102( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__11__new_transition_93( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__11__new_transition_94( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__11__new_transition_95( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__11__new_transition_96( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__11__new_transition_97_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__11__new_transition_98( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__11__new_transition_99( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__3__Debug__AC__OCCUPIED__OCCUPIED__3( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__3__Debug__En__OCCUPIED( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__3__Debug__Ex__OCCUPIED( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__3__Debug__end__trans__OCCUPIED__OCCUPIED__3( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__3__Debug__init__trans__OCCUPIED__OCCUPIED__3( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__3__new_transition_1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__3__new_transition_10( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__3__new_transition_2( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__3__new_transition_3( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__3__new_transition_4( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__3__new_transition_5_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__3__new_transition_6( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__3__new_transition_7( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__3__new_transition_8( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__3__new_transition_9( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__Debug__AC__reception( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__Debug__En__OCCUPIED( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__Debug__end__trans__reception( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__Debug__init__trans__reception( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__new_transition_29( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__new_transition_30( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__new_transition_31( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__new_transition_32( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__new_transition_33_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__new_transition_34( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__new_transition_35( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__new_transition_36( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__new_transition_37( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__new_transition_38( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__Debug__AC__transmission( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__Debug__Ex__OCCUPIED( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__Debug__end__trans__transmission( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__Debug__init__trans__transmission( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__new_transition_57( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__new_transition_58( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__new_transition_59( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__new_transition_60_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__new_transition_61( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__new_transition_62( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__new_transition_63( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__new_transition_64( const UMLRTMessage * msg );
    void actionchain_____Debug__IDLE__IDLE__4( const UMLRTMessage * msg );
    void actionchain_____Debug__IDLE__IDLE__4__E( const UMLRTMessage * msg );
    void actionchain_____Debug__IDLE__IDLE__4__S( const UMLRTMessage * msg );
    void actionchain_____Debug__IDLE__IDLE__4__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__IDLE__IDLE__6( const UMLRTMessage * msg );
    void actionchain_____Debug__IDLE__IDLE__6__E( const UMLRTMessage * msg );
    void actionchain_____Debug__IDLE__IDLE__6__S( const UMLRTMessage * msg );
    void actionchain_____Debug__IDLE__IDLE__6__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__IDLE__IDLE__9( const UMLRTMessage * msg );
    void actionchain_____Debug__IDLE__IDLE__9__E( const UMLRTMessage * msg );
    void actionchain_____Debug__IDLE__IDLE__9__S( const UMLRTMessage * msg );
    void actionchain_____Debug__IDLE__IDLE__9__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__InitDebug( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial__E( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial__S( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__Jam____IDLE__5( const UMLRTMessage * msg );
    void actionchain_____Debug__Jam____IDLE__5__E( const UMLRTMessage * msg );
    void actionchain_____Debug__Jam____IDLE__5__S( const UMLRTMessage * msg );
    void actionchain_____Debug__Jam____IDLE__5__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__Jam____OCCUPIED__7( const UMLRTMessage * msg );
    void actionchain_____Debug__Jam____OCCUPIED__7__E( const UMLRTMessage * msg );
    void actionchain_____Debug__Jam____OCCUPIED__7__S( const UMLRTMessage * msg );
    void actionchain_____Debug__Jam____OCCUPIED__7__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__OCCUPIED__OCCUPIED__10( const UMLRTMessage * msg );
    void actionchain_____Debug__OCCUPIED__OCCUPIED__10__E( const UMLRTMessage * msg );
    void actionchain_____Debug__OCCUPIED__OCCUPIED__10__S( const UMLRTMessage * msg );
    void actionchain_____Debug__OCCUPIED__OCCUPIED__10__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__OCCUPIED__OCCUPIED__11( const UMLRTMessage * msg );
    void actionchain_____Debug__OCCUPIED__OCCUPIED__11__E( const UMLRTMessage * msg );
    void actionchain_____Debug__OCCUPIED__OCCUPIED__11__S( const UMLRTMessage * msg );
    void actionchain_____Debug__OCCUPIED__OCCUPIED__11__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__OCCUPIED__OCCUPIED__3( const UMLRTMessage * msg );
    void actionchain_____Debug__OCCUPIED__OCCUPIED__3__E( const UMLRTMessage * msg );
    void actionchain_____Debug__OCCUPIED__OCCUPIED__3__S( const UMLRTMessage * msg );
    void actionchain_____Debug__OCCUPIED__OCCUPIED__3__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__reception( const UMLRTMessage * msg );
    void actionchain_____Debug__reception__E( const UMLRTMessage * msg );
    void actionchain_____Debug__reception__S( const UMLRTMessage * msg );
    void actionchain_____Debug__reception__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__transmission( const UMLRTMessage * msg );
    void actionchain_____Debug__transmission__E( const UMLRTMessage * msg );
    void actionchain_____Debug__transmission__S( const UMLRTMessage * msg );
    void actionchain_____Debug__transmission__dbg( const UMLRTMessage * msg );
    void actionchain_____IDLE__IDLE__4( const UMLRTMessage * msg );
    void actionchain_____IDLE__IDLE__6( const UMLRTMessage * msg );
    void actionchain_____IDLE__IDLE__9( const UMLRTMessage * msg );
    void actionchain_____Initial( const UMLRTMessage * msg );
    void actionchain_____Jam____IDLE__5( const UMLRTMessage * msg );
    void actionchain_____Jam____OCCUPIED__7( const UMLRTMessage * msg );
    void actionchain_____OCCUPIED__OCCUPIED__10( const UMLRTMessage * msg );
    void actionchain_____OCCUPIED__OCCUPIED__11( const UMLRTMessage * msg );
    void actionchain_____OCCUPIED__OCCUPIED__3( const UMLRTMessage * msg );
    void actionchain_____reception( const UMLRTMessage * msg );
    void actionchain_____transmission( const UMLRTMessage * msg );
    State junction_____Debug__C__IDLE__IDLE__4__en( const UMLRTMessage * msg );
    State junction_____Debug__C__IDLE__IDLE__4__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__IDLE__IDLE__4__new_exitpoint_2( const UMLRTMessage * msg );
    State junction_____Debug__C__IDLE__IDLE__6__en( const UMLRTMessage * msg );
    State junction_____Debug__C__IDLE__IDLE__6__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__IDLE__IDLE__6__new_exitpoint_5( const UMLRTMessage * msg );
    State junction_____Debug__C__IDLE__IDLE__9__en( const UMLRTMessage * msg );
    State junction_____Debug__C__IDLE__IDLE__9__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__IDLE__IDLE__9__new_exitpoint_9( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__en( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__new_exitpoint_8( const UMLRTMessage * msg );
    State junction_____Debug__C__Jam____IDLE__5__en( const UMLRTMessage * msg );
    State junction_____Debug__C__Jam____IDLE__5__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__Jam____IDLE__5__new_exitpoint_3( const UMLRTMessage * msg );
    State junction_____Debug__C__Jam____OCCUPIED__7__en( const UMLRTMessage * msg );
    State junction_____Debug__C__Jam____OCCUPIED__7__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__Jam____OCCUPIED__7__new_exitpoint_6( const UMLRTMessage * msg );
    State junction_____Debug__C__OCCUPIED__OCCUPIED__10__en( const UMLRTMessage * msg );
    State junction_____Debug__C__OCCUPIED__OCCUPIED__10__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__OCCUPIED__OCCUPIED__10__new_exitpoint_10( const UMLRTMessage * msg );
    State junction_____Debug__C__OCCUPIED__OCCUPIED__11__en( const UMLRTMessage * msg );
    State junction_____Debug__C__OCCUPIED__OCCUPIED__11__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__OCCUPIED__OCCUPIED__11__new_exitpoint_11( const UMLRTMessage * msg );
    State junction_____Debug__C__OCCUPIED__OCCUPIED__3__en( const UMLRTMessage * msg );
    State junction_____Debug__C__OCCUPIED__OCCUPIED__3__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__OCCUPIED__OCCUPIED__3__new_exitpoint_1( const UMLRTMessage * msg );
    State junction_____Debug__C__reception__en( const UMLRTMessage * msg );
    State junction_____Debug__C__reception__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__reception__new_exitpoint_4( const UMLRTMessage * msg );
    State junction_____Debug__C__transmission__en( const UMLRTMessage * msg );
    State junction_____Debug__C__transmission__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__transmission__new_exitpoint_7( const UMLRTMessage * msg );
    State choice_____Debug__C__IDLE__IDLE__4__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__IDLE__IDLE__6__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__IDLE__IDLE__9__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__Initial__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__Jam____IDLE__5__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__Jam____OCCUPIED__7__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__OCCUPIED__OCCUPIED__10__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__OCCUPIED__OCCUPIED__11__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__OCCUPIED__OCCUPIED__3__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__reception__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__transmission__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__Path__IDLE__IDLE__4( const UMLRTMessage * msg );
    State choice_____Debug__Path__IDLE__IDLE__6( const UMLRTMessage * msg );
    State choice_____Debug__Path__IDLE__IDLE__9( const UMLRTMessage * msg );
    State choice_____Debug__Path__Initial( const UMLRTMessage * msg );
    State choice_____Debug__Path__Jam____IDLE__5( const UMLRTMessage * msg );
    State choice_____Debug__Path__Jam____OCCUPIED__7( const UMLRTMessage * msg );
    State choice_____Debug__Path__OCCUPIED__OCCUPIED__10( const UMLRTMessage * msg );
    State choice_____Debug__Path__OCCUPIED__OCCUPIED__11( const UMLRTMessage * msg );
    State choice_____Debug__Path__OCCUPIED__OCCUPIED__3( const UMLRTMessage * msg );
    State choice_____Debug__Path__reception( const UMLRTMessage * msg );
    State choice_____Debug__Path__transmission( const UMLRTMessage * msg );
    State choice_____Jam__( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__4__Debug__A__Ac__IDLE__IDLE__4( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__4__Debug__A__En__IDLE( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__4__Debug__B__Ac__IDLE__IDLE__4( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__4__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__4__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__6__Debug__A__Ac__IDLE__IDLE__6( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__6__Debug__A__En__IDLE( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__6__Debug__B__Ac__IDLE__IDLE__6( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__6__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__6__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__9__Debug__A__Ac__IDLE__IDLE__9( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__9__Debug__A__En__IDLE( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__9__Debug__B__Ac__IDLE__IDLE__9( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__9__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__9__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__Jam____IDLE__5__Debug__A__Ac__Jam____IDLE__5( const UMLRTMessage * msg );
    State state_____Debug__C__Jam____IDLE__5__Debug__A__En__Jam____IDLE__5( const UMLRTMessage * msg );
    State state_____Debug__C__Jam____IDLE__5__Debug__B__Ac__Jam____IDLE__5( const UMLRTMessage * msg );
    State state_____Debug__C__Jam____IDLE__5__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__Jam____OCCUPIED__7__Debug__A__Ac__Jam____OCCUPIED__7( const UMLRTMessage * msg );
    State state_____Debug__C__Jam____OCCUPIED__7__Debug__A__En__Jam____OCCUPIED__7( const UMLRTMessage * msg );
    State state_____Debug__C__Jam____OCCUPIED__7__Debug__B__Ac__Jam____OCCUPIED__7( const UMLRTMessage * msg );
    State state_____Debug__C__Jam____OCCUPIED__7__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__OCCUPIED__OCCUPIED__10__Debug__A__Ac__OCCUPIED__OCCUPIED__10( const UMLRTMessage * msg );
    State state_____Debug__C__OCCUPIED__OCCUPIED__10__Debug__A__En__OCCUPIED( const UMLRTMessage * msg );
    State state_____Debug__C__OCCUPIED__OCCUPIED__10__Debug__B__Ac__OCCUPIED__OCCUPIED__10( const UMLRTMessage * msg );
    State state_____Debug__C__OCCUPIED__OCCUPIED__10__Debug__B__Ex__OCCUPIED( const UMLRTMessage * msg );
    State state_____Debug__C__OCCUPIED__OCCUPIED__10__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__OCCUPIED__OCCUPIED__11__Debug__A__Ac__OCCUPIED__OCCUPIED__11( const UMLRTMessage * msg );
    State state_____Debug__C__OCCUPIED__OCCUPIED__11__Debug__A__En__OCCUPIED( const UMLRTMessage * msg );
    State state_____Debug__C__OCCUPIED__OCCUPIED__11__Debug__B__Ac__OCCUPIED__OCCUPIED__11( const UMLRTMessage * msg );
    State state_____Debug__C__OCCUPIED__OCCUPIED__11__Debug__B__Ex__OCCUPIED( const UMLRTMessage * msg );
    State state_____Debug__C__OCCUPIED__OCCUPIED__11__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__OCCUPIED__OCCUPIED__3__Debug__A__Ac__OCCUPIED__OCCUPIED__3( const UMLRTMessage * msg );
    State state_____Debug__C__OCCUPIED__OCCUPIED__3__Debug__A__En__OCCUPIED( const UMLRTMessage * msg );
    State state_____Debug__C__OCCUPIED__OCCUPIED__3__Debug__B__Ac__OCCUPIED__OCCUPIED__3( const UMLRTMessage * msg );
    State state_____Debug__C__OCCUPIED__OCCUPIED__3__Debug__B__Ex__OCCUPIED( const UMLRTMessage * msg );
    State state_____Debug__C__OCCUPIED__OCCUPIED__3__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__reception__Debug__A__Ac__reception( const UMLRTMessage * msg );
    State state_____Debug__C__reception__Debug__A__En__OCCUPIED( const UMLRTMessage * msg );
    State state_____Debug__C__reception__Debug__B__Ac__reception( const UMLRTMessage * msg );
    State state_____Debug__C__reception__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    State state_____Debug__C__reception__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__transmission__Debug__A__Ac__transmission( const UMLRTMessage * msg );
    State state_____Debug__C__transmission__Debug__B__Ac__transmission( const UMLRTMessage * msg );
    State state_____Debug__C__transmission__Debug__B__Ex__OCCUPIED( const UMLRTMessage * msg );
    State state_____Debug__C__transmission__boundary( const UMLRTMessage * msg );
    State state_____Debug__InitState( const UMLRTMessage * msg );
    State state_____IDLE( const UMLRTMessage * msg );
    State state_____OCCUPIED( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass Switcher;

#endif

