
#ifndef ENV_HH
#define ENV_HH

#include "ConfigProtocol.hh"
#include "SystemConfig.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
#include "umlrttimerid.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

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
        borderport_configTimer
    };
protected:
    UMLRTTimerProtocol_baserole AnnouncmentServer2;
    UMLRTTimerProtocol_baserole BITTimer;
    ConfigProtocol::Conj ConfigComm;
    UMLRTTimerProtocol_baserole FailureTimer;
    UMLRTTimerProtocol_baserole GeneralTimer;
    UMLRTTimerProtocol_baserole configTimer;
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
        port_configTimer
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    UMLRTTimerId AnnouncementServer1Id;
    int AnnouncmentServerTimeout;
    UMLRTTimerId AnnouncementServer2Id;
    SystemConfig systemConfig;
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        ConfigFailure,
        ReadConfig,
        Running,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[4];
    State currentState;
    void entryaction_____ConfigFailure( const UMLRTMessage * msg );
    void entryaction_____ReadConfig( const UMLRTMessage * msg );
    void entryaction_____Running( const UMLRTMessage * msg );
    void exitaction_____ConfigFailure( const UMLRTMessage * msg );
    void exitaction_____ReadConfig( const UMLRTMessage * msg );
    void exitaction_____Running( const UMLRTMessage * msg );
    void transitionaction_____ConfigNOK( const UMLRTMessage * msg );
    void transitionaction_____MasterAnnouncment( const UMLRTMessage * msg );
    void transitionaction_____QueryConfig( const UMLRTMessage * msg );
    void transitionaction_____RetryConfig( const UMLRTMessage * msg );
    void transitionaction_____Server1Failure( const UMLRTMessage * msg );
    void transitionaction_____TransitionAction0( const UMLRTMessage * msg );
    void transitionaction_____configLoaded( const UMLRTMessage * msg );
    void transitionaction_____configOK( const UMLRTMessage * msg );
    void transitionaction_____server2Failure( const UMLRTMessage * msg );
    bool action_____configOK__checkConfig( const UMLRTMessage * msg );
    void actionchain_____ConfigNOK( const UMLRTMessage * msg );
    void actionchain_____MasterAnnouncment( const UMLRTMessage * msg );
    void actionchain_____QueryConfig( const UMLRTMessage * msg );
    void actionchain_____RetryConfig( const UMLRTMessage * msg );
    void actionchain_____Server1Failure( const UMLRTMessage * msg );
    void actionchain_____TransitionAction0( const UMLRTMessage * msg );
    void actionchain_____configLoaded( const UMLRTMessage * msg );
    void actionchain_____configOK( const UMLRTMessage * msg );
    void actionchain_____server2Failure( const UMLRTMessage * msg );
    State choice_____Config( const UMLRTMessage * msg );
    State state_____ConfigFailure( const UMLRTMessage * msg );
    State state_____ReadConfig( const UMLRTMessage * msg );
    State state_____Running( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass ENV;

#endif

