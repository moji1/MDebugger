
#ifndef ENV_HH
#define ENV_HH

#include "Config.hh"
#include "Configuration.hh"
#include "ExtInterface.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
#include "umlrttimerid.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include "Event.h"

#include "SROManager.h"

class Capsule_ENV : public UMLRTCapsule
{
public:
    Capsule_ENV( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    UMLRTTimerProtocol_baserole AnnouncmentServer1;
public:
    enum BorderPortId
    {
        borderport_AnnouncmentServer1,
        borderport_AnnouncmentServer2,
        borderport_BITTimer,
        borderport_ConfigComm,
        borderport_FailureTimer,
        borderport_GeneralTimer,
        borderport_configTimer,
        borderport_extComm
    };
protected:
    UMLRTTimerProtocol_baserole AnnouncmentServer2;
    UMLRTTimerProtocol_baserole BITTimer;
    Config::Conj ConfigComm;
    UMLRTTimerProtocol_baserole FailureTimer;
    UMLRTTimerProtocol_baserole GeneralTimer;
    UMLRTTimerProtocol_baserole configTimer;
    ExtInterface::Conj extComm;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_AnnouncmentServer1,
        port_AnnouncmentServer2,
        port_BITTimer,
        port_ConfigComm,
        port_FailureTimer,
        port_GeneralTimer,
        port_configTimer,
        port_extComm
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    Configuration config;
    UMLRTTimerId AnnouncementServer1Id;
    int AnnouncmentServerTimeout;
    UMLRTTimerId AnnouncementServer2Id;
    Configuration configuration;
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
        Debug__C__ConfigNOK,
        Debug__C__Init__ReadConfig__8,
        Debug__C__MasterAnnouncment,
        Debug__C__QueryConfig,
        Debug__C__RetryConfig,
        Debug__C__Server1Failure,
        Debug__C__configLoaded,
        Debug__C__configOK,
        Debug__C__server2Failure,
        ConfigFailure,
        Debug__C__ConfigNOK__Debug__A__Ac__ConfigNOK,
        Debug__C__ConfigNOK__Debug__A__En__ConfigNOK,
        Debug__C__ConfigNOK__Debug__B__Ac__ConfigNOK,
        Debug__C__ConfigNOK__boundary,
        Debug__C__Init__ReadConfig__8__Debug__A__Ac__Init__ReadConfig__8,
        Debug__C__Init__ReadConfig__8__Debug__A__En__Init__ReadConfig__8,
        Debug__C__Init__ReadConfig__8__Debug__B__Ac__Init__ReadConfig__8,
        Debug__C__Init__ReadConfig__8__boundary,
        Debug__C__MasterAnnouncment__Debug__A__Ac__MasterAnnouncment,
        Debug__C__MasterAnnouncment__Debug__A__En__Running,
        Debug__C__MasterAnnouncment__Debug__B__Ac__MasterAnnouncment,
        Debug__C__MasterAnnouncment__Debug__B__Ex__Running,
        Debug__C__MasterAnnouncment__boundary,
        Debug__C__QueryConfig__Debug__A__Ac__QueryConfig,
        Debug__C__QueryConfig__Debug__A__En__Running,
        Debug__C__QueryConfig__Debug__B__Ac__QueryConfig,
        Debug__C__QueryConfig__Debug__B__Ex__Running,
        Debug__C__QueryConfig__boundary,
        Debug__C__RetryConfig__Debug__A__Ac__RetryConfig,
        Debug__C__RetryConfig__Debug__A__En__ReadConfig,
        Debug__C__RetryConfig__Debug__B__Ac__RetryConfig,
        Debug__C__RetryConfig__Debug__B__Ex__ConfigFailure,
        Debug__C__RetryConfig__boundary,
        Debug__C__Server1Failure__Debug__A__Ac__Server1Failure,
        Debug__C__Server1Failure__Debug__A__En__Running,
        Debug__C__Server1Failure__Debug__B__Ac__Server1Failure,
        Debug__C__Server1Failure__Debug__B__Ex__Running,
        Debug__C__Server1Failure__boundary,
        Debug__C__configLoaded__Debug__A__Ac__configLoaded,
        Debug__C__configLoaded__Debug__B__Ac__configLoaded,
        Debug__C__configLoaded__Debug__B__Ex__ReadConfig,
        Debug__C__configLoaded__boundary,
        Debug__C__configOK__Debug__A__Ac__configOK,
        Debug__C__configOK__Debug__A__En__configOK,
        Debug__C__configOK__Debug__B__Ac__configOK,
        Debug__C__configOK__boundary,
        Debug__C__server2Failure__Debug__A__Ac__server2Failure,
        Debug__C__server2Failure__Debug__A__En__Running,
        Debug__C__server2Failure__Debug__B__Ac__server2Failure,
        Debug__C__server2Failure__Debug__B__Ex__Running,
        Debug__C__server2Failure__boundary,
        Debug__InitState,
        ReadConfig,
        Running,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[55];
    State currentState;
    State history[9];
    void save_history( State compositeState, State subState );
    bool check_history( State compositeState, State subState );
    void entryaction_____ConfigFailure( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ConfigNOK__Debug__A__Ac__ConfigNOK( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ConfigNOK__Debug__A__En__ConfigNOK( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ConfigNOK__Debug__B__Ac__ConfigNOK( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ConfigNOK__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Init__ReadConfig__8__Debug__A__Ac__Init__ReadConfig__8( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Init__ReadConfig__8__Debug__A__En__Init__ReadConfig__8( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Init__ReadConfig__8__Debug__B__Ac__Init__ReadConfig__8( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Init__ReadConfig__8__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__MasterAnnouncment__Debug__A__Ac__MasterAnnouncment( const UMLRTMessage * msg );
    void entryaction_____Debug__C__MasterAnnouncment__Debug__A__En__Running( const UMLRTMessage * msg );
    void entryaction_____Debug__C__MasterAnnouncment__Debug__B__Ac__MasterAnnouncment( const UMLRTMessage * msg );
    void entryaction_____Debug__C__MasterAnnouncment__Debug__B__Ex__Running( const UMLRTMessage * msg );
    void entryaction_____Debug__C__MasterAnnouncment__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__QueryConfig__Debug__A__Ac__QueryConfig( const UMLRTMessage * msg );
    void entryaction_____Debug__C__QueryConfig__Debug__A__En__Running( const UMLRTMessage * msg );
    void entryaction_____Debug__C__QueryConfig__Debug__B__Ac__QueryConfig( const UMLRTMessage * msg );
    void entryaction_____Debug__C__QueryConfig__Debug__B__Ex__Running( const UMLRTMessage * msg );
    void entryaction_____Debug__C__QueryConfig__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__RetryConfig__Debug__A__Ac__RetryConfig( const UMLRTMessage * msg );
    void entryaction_____Debug__C__RetryConfig__Debug__A__En__ReadConfig( const UMLRTMessage * msg );
    void entryaction_____Debug__C__RetryConfig__Debug__B__Ac__RetryConfig( const UMLRTMessage * msg );
    void entryaction_____Debug__C__RetryConfig__Debug__B__Ex__ConfigFailure( const UMLRTMessage * msg );
    void entryaction_____Debug__C__RetryConfig__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Server1Failure__Debug__A__Ac__Server1Failure( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Server1Failure__Debug__A__En__Running( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Server1Failure__Debug__B__Ac__Server1Failure( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Server1Failure__Debug__B__Ex__Running( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Server1Failure__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__configLoaded__Debug__A__Ac__configLoaded( const UMLRTMessage * msg );
    void entryaction_____Debug__C__configLoaded__Debug__B__Ac__configLoaded( const UMLRTMessage * msg );
    void entryaction_____Debug__C__configLoaded__Debug__B__Ex__ReadConfig( const UMLRTMessage * msg );
    void entryaction_____Debug__C__configLoaded__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__configOK__Debug__A__Ac__configOK( const UMLRTMessage * msg );
    void entryaction_____Debug__C__configOK__Debug__A__En__configOK( const UMLRTMessage * msg );
    void entryaction_____Debug__C__configOK__Debug__B__Ac__configOK( const UMLRTMessage * msg );
    void entryaction_____Debug__C__configOK__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__server2Failure__Debug__A__Ac__server2Failure( const UMLRTMessage * msg );
    void entryaction_____Debug__C__server2Failure__Debug__A__En__Running( const UMLRTMessage * msg );
    void entryaction_____Debug__C__server2Failure__Debug__B__Ac__server2Failure( const UMLRTMessage * msg );
    void entryaction_____Debug__C__server2Failure__Debug__B__Ex__Running( const UMLRTMessage * msg );
    void entryaction_____Debug__C__server2Failure__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__InitState( const UMLRTMessage * msg );
    void entryaction_____ReadConfig( const UMLRTMessage * msg );
    void entryaction_____Running( const UMLRTMessage * msg );
    void exitaction_____ConfigFailure( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ConfigNOK__Debug__A__Ac__ConfigNOK( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ConfigNOK__Debug__A__En__ConfigNOK( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ConfigNOK__Debug__B__Ac__ConfigNOK( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ConfigNOK__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Init__ReadConfig__8__Debug__A__Ac__Init__ReadConfig__8( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Init__ReadConfig__8__Debug__A__En__Init__ReadConfig__8( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Init__ReadConfig__8__Debug__B__Ac__Init__ReadConfig__8( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Init__ReadConfig__8__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__MasterAnnouncment__Debug__A__Ac__MasterAnnouncment( const UMLRTMessage * msg );
    void exitaction_____Debug__C__MasterAnnouncment__Debug__A__En__Running( const UMLRTMessage * msg );
    void exitaction_____Debug__C__MasterAnnouncment__Debug__B__Ac__MasterAnnouncment( const UMLRTMessage * msg );
    void exitaction_____Debug__C__MasterAnnouncment__Debug__B__Ex__Running( const UMLRTMessage * msg );
    void exitaction_____Debug__C__MasterAnnouncment__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__QueryConfig__Debug__A__Ac__QueryConfig( const UMLRTMessage * msg );
    void exitaction_____Debug__C__QueryConfig__Debug__A__En__Running( const UMLRTMessage * msg );
    void exitaction_____Debug__C__QueryConfig__Debug__B__Ac__QueryConfig( const UMLRTMessage * msg );
    void exitaction_____Debug__C__QueryConfig__Debug__B__Ex__Running( const UMLRTMessage * msg );
    void exitaction_____Debug__C__QueryConfig__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__RetryConfig__Debug__A__Ac__RetryConfig( const UMLRTMessage * msg );
    void exitaction_____Debug__C__RetryConfig__Debug__A__En__ReadConfig( const UMLRTMessage * msg );
    void exitaction_____Debug__C__RetryConfig__Debug__B__Ac__RetryConfig( const UMLRTMessage * msg );
    void exitaction_____Debug__C__RetryConfig__Debug__B__Ex__ConfigFailure( const UMLRTMessage * msg );
    void exitaction_____Debug__C__RetryConfig__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Server1Failure__Debug__A__Ac__Server1Failure( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Server1Failure__Debug__A__En__Running( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Server1Failure__Debug__B__Ac__Server1Failure( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Server1Failure__Debug__B__Ex__Running( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Server1Failure__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__configLoaded__Debug__A__Ac__configLoaded( const UMLRTMessage * msg );
    void exitaction_____Debug__C__configLoaded__Debug__B__Ac__configLoaded( const UMLRTMessage * msg );
    void exitaction_____Debug__C__configLoaded__Debug__B__Ex__ReadConfig( const UMLRTMessage * msg );
    void exitaction_____Debug__C__configLoaded__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__configOK__Debug__A__Ac__configOK( const UMLRTMessage * msg );
    void exitaction_____Debug__C__configOK__Debug__A__En__configOK( const UMLRTMessage * msg );
    void exitaction_____Debug__C__configOK__Debug__B__Ac__configOK( const UMLRTMessage * msg );
    void exitaction_____Debug__C__configOK__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__server2Failure__Debug__A__Ac__server2Failure( const UMLRTMessage * msg );
    void exitaction_____Debug__C__server2Failure__Debug__A__En__Running( const UMLRTMessage * msg );
    void exitaction_____Debug__C__server2Failure__Debug__B__Ac__server2Failure( const UMLRTMessage * msg );
    void exitaction_____Debug__C__server2Failure__Debug__B__Ex__Running( const UMLRTMessage * msg );
    void exitaction_____Debug__C__server2Failure__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__InitState( const UMLRTMessage * msg );
    void exitaction_____ReadConfig( const UMLRTMessage * msg );
    void exitaction_____Running( const UMLRTMessage * msg );
    void transitionaction_____ConfigNOK( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__ConfigNOK__Debug__Ac__ConfigNOK( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__ConfigNOK__Debug__En__ConfigFailure( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__ConfigNOK__Debug__end__trans__ConfigNOK( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__ConfigNOK__Debug__init__trans__ConfigNOK( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Init__ReadConfig__8__Debug__Ac__Init__ReadConfig__8( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Init__ReadConfig__8__Debug__En__ReadConfig( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Init__ReadConfig__8__Debug__end__trans__Init__ReadConfig__8( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Init__ReadConfig__8__Debug__init__trans__Init__ReadConfig__8( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__MasterAnnouncment__Debug__AC__MasterAnnouncment( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__MasterAnnouncment__Debug__En__Running( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__MasterAnnouncment__Debug__Ex__Running( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__MasterAnnouncment__Debug__end__trans__MasterAnnouncment( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__MasterAnnouncment__Debug__init__trans__MasterAnnouncment( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__QueryConfig__Debug__AC__QueryConfig( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__QueryConfig__Debug__En__Running( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__QueryConfig__Debug__Ex__Running( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__QueryConfig__Debug__end__trans__QueryConfig( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__QueryConfig__Debug__init__trans__QueryConfig( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__RetryConfig__Debug__AC__RetryConfig( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__RetryConfig__Debug__En__ReadConfig( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__RetryConfig__Debug__Ex__ConfigFailure( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__RetryConfig__Debug__end__trans__RetryConfig( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__RetryConfig__Debug__init__trans__RetryConfig( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Server1Failure__Debug__AC__Server1Failure( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Server1Failure__Debug__En__Running( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Server1Failure__Debug__Ex__Running( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Server1Failure__Debug__end__trans__Server1Failure( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Server1Failure__Debug__init__trans__Server1Failure( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__configLoaded__Debug__AC__configLoaded( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__configLoaded__Debug__Ex__ReadConfig( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__configLoaded__Debug__end__trans__configLoaded( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__configOK__Debug__Ac__configOK( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__configOK__Debug__En__Running( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__configOK__Debug__end__trans__configOK( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__configOK__Debug__init__trans__configOK( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__server2Failure__Debug__AC__server2Failure( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__server2Failure__Debug__En__Running( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__server2Failure__Debug__Ex__Running( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__server2Failure__Debug__end__trans__server2Failure( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__server2Failure__Debug__init__trans__server2Failure( const UMLRTMessage * msg );
    void transitionaction_____Debug__ConfigNOK( const UMLRTMessage * msg );
    void transitionaction_____Debug__ConfigNOK__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__ConfigNOK__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__ConfigNOK__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__InitDebug( const UMLRTMessage * msg );
    void transitionaction_____Debug__Init__ReadConfig__8( const UMLRTMessage * msg );
    void transitionaction_____Debug__Init__ReadConfig__8__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__Init__ReadConfig__8__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__Init__ReadConfig__8__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__MasterAnnouncment( const UMLRTMessage * msg );
    void transitionaction_____Debug__MasterAnnouncment__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__MasterAnnouncment__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__MasterAnnouncment__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__QueryConfig( const UMLRTMessage * msg );
    void transitionaction_____Debug__QueryConfig__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__QueryConfig__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__QueryConfig__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__RetryConfig( const UMLRTMessage * msg );
    void transitionaction_____Debug__RetryConfig__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__RetryConfig__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__RetryConfig__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__Server1Failure( const UMLRTMessage * msg );
    void transitionaction_____Debug__Server1Failure__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__Server1Failure__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__Server1Failure__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__configLoaded( const UMLRTMessage * msg );
    void transitionaction_____Debug__configLoaded__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__configLoaded__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__configLoaded__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__configOK( const UMLRTMessage * msg );
    void transitionaction_____Debug__configOK__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__configOK__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__configOK__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__server2Failure( const UMLRTMessage * msg );
    void transitionaction_____Debug__server2Failure__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__server2Failure__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__server2Failure__dbg( const UMLRTMessage * msg );
    void transitionaction_____Init__ReadConfig__8( const UMLRTMessage * msg );
    void transitionaction_____MasterAnnouncment( const UMLRTMessage * msg );
    void transitionaction_____QueryConfig( const UMLRTMessage * msg );
    void transitionaction_____RetryConfig( const UMLRTMessage * msg );
    void transitionaction_____Server1Failure( const UMLRTMessage * msg );
    void transitionaction_____configLoaded( const UMLRTMessage * msg );
    void transitionaction_____configOK( const UMLRTMessage * msg );
    void transitionaction_____server2Failure( const UMLRTMessage * msg );
    bool action_____Debug__ConfigNOK__S__Debug__GuardConfigNOK( const UMLRTMessage * msg );
    bool action_____Debug__Init__ReadConfig__8__S__Debug__GuardInit__ReadConfig__8( const UMLRTMessage * msg );
    bool action_____Debug__MasterAnnouncment__S__Debug__GuardMasterAnnouncment( const UMLRTMessage * msg );
    bool action_____Debug__QueryConfig__S__Debug__GuardQueryConfig( const UMLRTMessage * msg );
    bool action_____Debug__RetryConfig__S__Debug__GuardRetryConfig( const UMLRTMessage * msg );
    bool action_____Debug__Server1Failure__S__Debug__GuardServer1Failure( const UMLRTMessage * msg );
    bool action_____Debug__configLoaded__S__Debug__GuardconfigLoaded( const UMLRTMessage * msg );
    bool action_____Debug__configOK__S__Debug__GuardconfigOK( const UMLRTMessage * msg );
    bool action_____Debug__configOK__checkConfig( const UMLRTMessage * msg );
    bool action_____Debug__server2Failure__S__Debug__Guardserver2Failure( const UMLRTMessage * msg );
    void actionchain_____ConfigNOK( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ConfigNOK__Debug__Ac__ConfigNOK( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ConfigNOK__Debug__En__ConfigFailure( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ConfigNOK__Debug__end__trans__ConfigNOK( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ConfigNOK__Debug__init__trans__ConfigNOK( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ConfigNOK__new_transition_55( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ConfigNOK__new_transition_56( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ConfigNOK__new_transition_57( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ConfigNOK__new_transition_58_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ConfigNOK__new_transition_59( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ConfigNOK__new_transition_60( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ConfigNOK__new_transition_61( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ConfigNOK__new_transition_62( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__ReadConfig__8__Debug__Ac__Init__ReadConfig__8( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__ReadConfig__8__Debug__En__ReadConfig( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__ReadConfig__8__Debug__end__trans__Init__ReadConfig__8( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__ReadConfig__8__Debug__init__trans__Init__ReadConfig__8( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__ReadConfig__8__new_transition_11( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__ReadConfig__8__new_transition_12( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__ReadConfig__8__new_transition_13( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__ReadConfig__8__new_transition_14_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__ReadConfig__8__new_transition_15( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__ReadConfig__8__new_transition_16( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__ReadConfig__8__new_transition_17( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__ReadConfig__8__new_transition_18( const UMLRTMessage * msg );
    void actionchain_____Debug__C__MasterAnnouncment__Debug__AC__MasterAnnouncment( const UMLRTMessage * msg );
    void actionchain_____Debug__C__MasterAnnouncment__Debug__En__Running( const UMLRTMessage * msg );
    void actionchain_____Debug__C__MasterAnnouncment__Debug__Ex__Running( const UMLRTMessage * msg );
    void actionchain_____Debug__C__MasterAnnouncment__Debug__end__trans__MasterAnnouncment( const UMLRTMessage * msg );
    void actionchain_____Debug__C__MasterAnnouncment__Debug__init__trans__MasterAnnouncment( const UMLRTMessage * msg );
    void actionchain_____Debug__C__MasterAnnouncment__new_transition_1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__MasterAnnouncment__new_transition_10( const UMLRTMessage * msg );
    void actionchain_____Debug__C__MasterAnnouncment__new_transition_2( const UMLRTMessage * msg );
    void actionchain_____Debug__C__MasterAnnouncment__new_transition_3( const UMLRTMessage * msg );
    void actionchain_____Debug__C__MasterAnnouncment__new_transition_4( const UMLRTMessage * msg );
    void actionchain_____Debug__C__MasterAnnouncment__new_transition_5_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__MasterAnnouncment__new_transition_6( const UMLRTMessage * msg );
    void actionchain_____Debug__C__MasterAnnouncment__new_transition_7( const UMLRTMessage * msg );
    void actionchain_____Debug__C__MasterAnnouncment__new_transition_8( const UMLRTMessage * msg );
    void actionchain_____Debug__C__MasterAnnouncment__new_transition_9( const UMLRTMessage * msg );
    void actionchain_____Debug__C__QueryConfig__Debug__AC__QueryConfig( const UMLRTMessage * msg );
    void actionchain_____Debug__C__QueryConfig__Debug__En__Running( const UMLRTMessage * msg );
    void actionchain_____Debug__C__QueryConfig__Debug__Ex__Running( const UMLRTMessage * msg );
    void actionchain_____Debug__C__QueryConfig__Debug__end__trans__QueryConfig( const UMLRTMessage * msg );
    void actionchain_____Debug__C__QueryConfig__Debug__init__trans__QueryConfig( const UMLRTMessage * msg );
    void actionchain_____Debug__C__QueryConfig__new_transition_63( const UMLRTMessage * msg );
    void actionchain_____Debug__C__QueryConfig__new_transition_64( const UMLRTMessage * msg );
    void actionchain_____Debug__C__QueryConfig__new_transition_65( const UMLRTMessage * msg );
    void actionchain_____Debug__C__QueryConfig__new_transition_66( const UMLRTMessage * msg );
    void actionchain_____Debug__C__QueryConfig__new_transition_67_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__QueryConfig__new_transition_68( const UMLRTMessage * msg );
    void actionchain_____Debug__C__QueryConfig__new_transition_69( const UMLRTMessage * msg );
    void actionchain_____Debug__C__QueryConfig__new_transition_70( const UMLRTMessage * msg );
    void actionchain_____Debug__C__QueryConfig__new_transition_71( const UMLRTMessage * msg );
    void actionchain_____Debug__C__QueryConfig__new_transition_72( const UMLRTMessage * msg );
    void actionchain_____Debug__C__RetryConfig__Debug__AC__RetryConfig( const UMLRTMessage * msg );
    void actionchain_____Debug__C__RetryConfig__Debug__En__ReadConfig( const UMLRTMessage * msg );
    void actionchain_____Debug__C__RetryConfig__Debug__Ex__ConfigFailure( const UMLRTMessage * msg );
    void actionchain_____Debug__C__RetryConfig__Debug__end__trans__RetryConfig( const UMLRTMessage * msg );
    void actionchain_____Debug__C__RetryConfig__Debug__init__trans__RetryConfig( const UMLRTMessage * msg );
    void actionchain_____Debug__C__RetryConfig__new_transition_19( const UMLRTMessage * msg );
    void actionchain_____Debug__C__RetryConfig__new_transition_20( const UMLRTMessage * msg );
    void actionchain_____Debug__C__RetryConfig__new_transition_21( const UMLRTMessage * msg );
    void actionchain_____Debug__C__RetryConfig__new_transition_22( const UMLRTMessage * msg );
    void actionchain_____Debug__C__RetryConfig__new_transition_23_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__RetryConfig__new_transition_24( const UMLRTMessage * msg );
    void actionchain_____Debug__C__RetryConfig__new_transition_25( const UMLRTMessage * msg );
    void actionchain_____Debug__C__RetryConfig__new_transition_26( const UMLRTMessage * msg );
    void actionchain_____Debug__C__RetryConfig__new_transition_27( const UMLRTMessage * msg );
    void actionchain_____Debug__C__RetryConfig__new_transition_28( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Server1Failure__Debug__AC__Server1Failure( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Server1Failure__Debug__En__Running( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Server1Failure__Debug__Ex__Running( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Server1Failure__Debug__end__trans__Server1Failure( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Server1Failure__Debug__init__trans__Server1Failure( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Server1Failure__new_transition_73( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Server1Failure__new_transition_74( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Server1Failure__new_transition_75( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Server1Failure__new_transition_76( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Server1Failure__new_transition_77_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Server1Failure__new_transition_78( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Server1Failure__new_transition_79( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Server1Failure__new_transition_80( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Server1Failure__new_transition_81( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Server1Failure__new_transition_82( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configLoaded__Debug__AC__configLoaded( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configLoaded__Debug__Ex__ReadConfig( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configLoaded__Debug__end__trans__configLoaded( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configLoaded__Debug__init__trans__configLoaded( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configLoaded__new_transition_47( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configLoaded__new_transition_48( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configLoaded__new_transition_49( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configLoaded__new_transition_50_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configLoaded__new_transition_51( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configLoaded__new_transition_52( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configLoaded__new_transition_53( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configLoaded__new_transition_54( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configOK__Debug__Ac__configOK( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configOK__Debug__En__Running( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configOK__Debug__end__trans__configOK( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configOK__Debug__init__trans__configOK( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configOK__new_transition_39( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configOK__new_transition_40( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configOK__new_transition_41( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configOK__new_transition_42_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configOK__new_transition_43( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configOK__new_transition_44( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configOK__new_transition_45( const UMLRTMessage * msg );
    void actionchain_____Debug__C__configOK__new_transition_46( const UMLRTMessage * msg );
    void actionchain_____Debug__C__server2Failure__Debug__AC__server2Failure( const UMLRTMessage * msg );
    void actionchain_____Debug__C__server2Failure__Debug__En__Running( const UMLRTMessage * msg );
    void actionchain_____Debug__C__server2Failure__Debug__Ex__Running( const UMLRTMessage * msg );
    void actionchain_____Debug__C__server2Failure__Debug__end__trans__server2Failure( const UMLRTMessage * msg );
    void actionchain_____Debug__C__server2Failure__Debug__init__trans__server2Failure( const UMLRTMessage * msg );
    void actionchain_____Debug__C__server2Failure__new_transition_29( const UMLRTMessage * msg );
    void actionchain_____Debug__C__server2Failure__new_transition_30( const UMLRTMessage * msg );
    void actionchain_____Debug__C__server2Failure__new_transition_31( const UMLRTMessage * msg );
    void actionchain_____Debug__C__server2Failure__new_transition_32( const UMLRTMessage * msg );
    void actionchain_____Debug__C__server2Failure__new_transition_33_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__server2Failure__new_transition_34( const UMLRTMessage * msg );
    void actionchain_____Debug__C__server2Failure__new_transition_35( const UMLRTMessage * msg );
    void actionchain_____Debug__C__server2Failure__new_transition_36( const UMLRTMessage * msg );
    void actionchain_____Debug__C__server2Failure__new_transition_37( const UMLRTMessage * msg );
    void actionchain_____Debug__C__server2Failure__new_transition_38( const UMLRTMessage * msg );
    void actionchain_____Debug__ConfigNOK( const UMLRTMessage * msg );
    void actionchain_____Debug__ConfigNOK__E( const UMLRTMessage * msg );
    void actionchain_____Debug__ConfigNOK__S( const UMLRTMessage * msg );
    void actionchain_____Debug__ConfigNOK__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__InitDebug( const UMLRTMessage * msg );
    void actionchain_____Debug__Init__ReadConfig__8( const UMLRTMessage * msg );
    void actionchain_____Debug__Init__ReadConfig__8__E( const UMLRTMessage * msg );
    void actionchain_____Debug__Init__ReadConfig__8__S( const UMLRTMessage * msg );
    void actionchain_____Debug__Init__ReadConfig__8__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__MasterAnnouncment( const UMLRTMessage * msg );
    void actionchain_____Debug__MasterAnnouncment__E( const UMLRTMessage * msg );
    void actionchain_____Debug__MasterAnnouncment__S( const UMLRTMessage * msg );
    void actionchain_____Debug__MasterAnnouncment__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__QueryConfig( const UMLRTMessage * msg );
    void actionchain_____Debug__QueryConfig__E( const UMLRTMessage * msg );
    void actionchain_____Debug__QueryConfig__S( const UMLRTMessage * msg );
    void actionchain_____Debug__QueryConfig__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__RetryConfig( const UMLRTMessage * msg );
    void actionchain_____Debug__RetryConfig__E( const UMLRTMessage * msg );
    void actionchain_____Debug__RetryConfig__S( const UMLRTMessage * msg );
    void actionchain_____Debug__RetryConfig__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__Server1Failure( const UMLRTMessage * msg );
    void actionchain_____Debug__Server1Failure__E( const UMLRTMessage * msg );
    void actionchain_____Debug__Server1Failure__S( const UMLRTMessage * msg );
    void actionchain_____Debug__Server1Failure__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__configLoaded( const UMLRTMessage * msg );
    void actionchain_____Debug__configLoaded__E( const UMLRTMessage * msg );
    void actionchain_____Debug__configLoaded__S( const UMLRTMessage * msg );
    void actionchain_____Debug__configLoaded__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__configOK( const UMLRTMessage * msg );
    void actionchain_____Debug__configOK__E( const UMLRTMessage * msg );
    void actionchain_____Debug__configOK__S( const UMLRTMessage * msg );
    void actionchain_____Debug__configOK__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__server2Failure( const UMLRTMessage * msg );
    void actionchain_____Debug__server2Failure__E( const UMLRTMessage * msg );
    void actionchain_____Debug__server2Failure__S( const UMLRTMessage * msg );
    void actionchain_____Debug__server2Failure__dbg( const UMLRTMessage * msg );
    void actionchain_____Init__ReadConfig__8( const UMLRTMessage * msg );
    void actionchain_____MasterAnnouncment( const UMLRTMessage * msg );
    void actionchain_____QueryConfig( const UMLRTMessage * msg );
    void actionchain_____RetryConfig( const UMLRTMessage * msg );
    void actionchain_____Server1Failure( const UMLRTMessage * msg );
    void actionchain_____configLoaded( const UMLRTMessage * msg );
    void actionchain_____configOK( const UMLRTMessage * msg );
    void actionchain_____server2Failure( const UMLRTMessage * msg );
    State junction_____Debug__C__ConfigNOK__en( const UMLRTMessage * msg );
    State junction_____Debug__C__ConfigNOK__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__ConfigNOK__new_exitpoint_7( const UMLRTMessage * msg );
    State junction_____Debug__C__Init__ReadConfig__8__en( const UMLRTMessage * msg );
    State junction_____Debug__C__Init__ReadConfig__8__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__Init__ReadConfig__8__new_exitpoint_2( const UMLRTMessage * msg );
    State junction_____Debug__C__MasterAnnouncment__en( const UMLRTMessage * msg );
    State junction_____Debug__C__MasterAnnouncment__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__MasterAnnouncment__new_exitpoint_1( const UMLRTMessage * msg );
    State junction_____Debug__C__QueryConfig__en( const UMLRTMessage * msg );
    State junction_____Debug__C__QueryConfig__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__QueryConfig__new_exitpoint_8( const UMLRTMessage * msg );
    State junction_____Debug__C__RetryConfig__en( const UMLRTMessage * msg );
    State junction_____Debug__C__RetryConfig__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__RetryConfig__new_exitpoint_3( const UMLRTMessage * msg );
    State junction_____Debug__C__Server1Failure__en( const UMLRTMessage * msg );
    State junction_____Debug__C__Server1Failure__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__Server1Failure__new_exitpoint_9( const UMLRTMessage * msg );
    State junction_____Debug__C__configLoaded__en( const UMLRTMessage * msg );
    State junction_____Debug__C__configLoaded__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__configLoaded__new_exitpoint_6( const UMLRTMessage * msg );
    State junction_____Debug__C__configOK__en( const UMLRTMessage * msg );
    State junction_____Debug__C__configOK__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__configOK__new_exitpoint_5( const UMLRTMessage * msg );
    State junction_____Debug__C__server2Failure__en( const UMLRTMessage * msg );
    State junction_____Debug__C__server2Failure__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__server2Failure__new_exitpoint_4( const UMLRTMessage * msg );
    State choice_____Config( const UMLRTMessage * msg );
    State choice_____Debug__C__ConfigNOK__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__Init__ReadConfig__8__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__MasterAnnouncment__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__QueryConfig__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__RetryConfig__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__Server1Failure__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__configLoaded__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__configOK__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__server2Failure__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__Path__ConfigNOK( const UMLRTMessage * msg );
    State choice_____Debug__Path__Init__ReadConfig__8( const UMLRTMessage * msg );
    State choice_____Debug__Path__MasterAnnouncment( const UMLRTMessage * msg );
    State choice_____Debug__Path__QueryConfig( const UMLRTMessage * msg );
    State choice_____Debug__Path__RetryConfig( const UMLRTMessage * msg );
    State choice_____Debug__Path__Server1Failure( const UMLRTMessage * msg );
    State choice_____Debug__Path__configLoaded( const UMLRTMessage * msg );
    State choice_____Debug__Path__configOK( const UMLRTMessage * msg );
    State choice_____Debug__Path__server2Failure( const UMLRTMessage * msg );
    State state_____ConfigFailure( const UMLRTMessage * msg );
    State state_____Debug__C__ConfigNOK__Debug__A__Ac__ConfigNOK( const UMLRTMessage * msg );
    State state_____Debug__C__ConfigNOK__Debug__A__En__ConfigNOK( const UMLRTMessage * msg );
    State state_____Debug__C__ConfigNOK__Debug__B__Ac__ConfigNOK( const UMLRTMessage * msg );
    State state_____Debug__C__ConfigNOK__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__Init__ReadConfig__8__Debug__A__Ac__Init__ReadConfig__8( const UMLRTMessage * msg );
    State state_____Debug__C__Init__ReadConfig__8__Debug__A__En__Init__ReadConfig__8( const UMLRTMessage * msg );
    State state_____Debug__C__Init__ReadConfig__8__Debug__B__Ac__Init__ReadConfig__8( const UMLRTMessage * msg );
    State state_____Debug__C__Init__ReadConfig__8__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__MasterAnnouncment__Debug__A__Ac__MasterAnnouncment( const UMLRTMessage * msg );
    State state_____Debug__C__MasterAnnouncment__Debug__A__En__Running( const UMLRTMessage * msg );
    State state_____Debug__C__MasterAnnouncment__Debug__B__Ac__MasterAnnouncment( const UMLRTMessage * msg );
    State state_____Debug__C__MasterAnnouncment__Debug__B__Ex__Running( const UMLRTMessage * msg );
    State state_____Debug__C__MasterAnnouncment__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__QueryConfig__Debug__A__Ac__QueryConfig( const UMLRTMessage * msg );
    State state_____Debug__C__QueryConfig__Debug__A__En__Running( const UMLRTMessage * msg );
    State state_____Debug__C__QueryConfig__Debug__B__Ac__QueryConfig( const UMLRTMessage * msg );
    State state_____Debug__C__QueryConfig__Debug__B__Ex__Running( const UMLRTMessage * msg );
    State state_____Debug__C__QueryConfig__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__RetryConfig__Debug__A__Ac__RetryConfig( const UMLRTMessage * msg );
    State state_____Debug__C__RetryConfig__Debug__A__En__ReadConfig( const UMLRTMessage * msg );
    State state_____Debug__C__RetryConfig__Debug__B__Ac__RetryConfig( const UMLRTMessage * msg );
    State state_____Debug__C__RetryConfig__Debug__B__Ex__ConfigFailure( const UMLRTMessage * msg );
    State state_____Debug__C__RetryConfig__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__Server1Failure__Debug__A__Ac__Server1Failure( const UMLRTMessage * msg );
    State state_____Debug__C__Server1Failure__Debug__A__En__Running( const UMLRTMessage * msg );
    State state_____Debug__C__Server1Failure__Debug__B__Ac__Server1Failure( const UMLRTMessage * msg );
    State state_____Debug__C__Server1Failure__Debug__B__Ex__Running( const UMLRTMessage * msg );
    State state_____Debug__C__Server1Failure__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__configLoaded__Debug__A__Ac__configLoaded( const UMLRTMessage * msg );
    State state_____Debug__C__configLoaded__Debug__B__Ac__configLoaded( const UMLRTMessage * msg );
    State state_____Debug__C__configLoaded__Debug__B__Ex__ReadConfig( const UMLRTMessage * msg );
    State state_____Debug__C__configLoaded__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__configOK__Debug__A__Ac__configOK( const UMLRTMessage * msg );
    State state_____Debug__C__configOK__Debug__A__En__configOK( const UMLRTMessage * msg );
    State state_____Debug__C__configOK__Debug__B__Ac__configOK( const UMLRTMessage * msg );
    State state_____Debug__C__configOK__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__server2Failure__Debug__A__Ac__server2Failure( const UMLRTMessage * msg );
    State state_____Debug__C__server2Failure__Debug__A__En__Running( const UMLRTMessage * msg );
    State state_____Debug__C__server2Failure__Debug__B__Ac__server2Failure( const UMLRTMessage * msg );
    State state_____Debug__C__server2Failure__Debug__B__Ex__Running( const UMLRTMessage * msg );
    State state_____Debug__C__server2Failure__boundary( const UMLRTMessage * msg );
    State state_____Debug__InitState( const UMLRTMessage * msg );
    State state_____ReadConfig( const UMLRTMessage * msg );
    State state_____Running( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass ENV;

#endif

