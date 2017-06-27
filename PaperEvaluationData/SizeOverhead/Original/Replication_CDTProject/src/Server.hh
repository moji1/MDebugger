
#ifndef SERVER_HH
#define SERVER_HH

#include "ConfigProtocol.hh"
#include "FailOver.hh"
#include "Host.hh"
#include "Services.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
#include "umlrttimerid.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

class Capsule_Server : public Capsule_Host
{
public:
    Capsule_Server( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    ConfigProtocol::Base ConfigComm;
public:
    enum BorderPortId
    {
        borderport_ConfigComm,
        borderport_KeepAliveTimer,
        borderport_Master,
        borderport_MasterAnnounceTimer,
        borderport_ServerComm,
        borderport_Slave,
        borderport_Timer
    };
protected:
    UMLRTTimerProtocol_baserole KeepAliveTimer;
    FailOver::Base Master;
    UMLRTTimerProtocol_baserole MasterAnnounceTimer;
    Services::Conj ServerComm;
    FailOver::Conj Slave;
    UMLRTTimerProtocol_baserole Timer;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_ConfigComm,
        port_KeepAliveTimer,
        port_Master,
        port_MasterAnnounceTimer,
        port_ServerComm,
        port_Slave,
        port_Timer
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    UMLRTTimerId KeepAliveTimerId;
    int KeepAliveTimeOut;
    UMLRTTimerId AnnouncementTimerId;
    int AnnouncementTimeOut;
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        Backup,
        Backup__RunAsSlave,
        Backup__TryBeMaster,
        Failure,
        RunAsMaster,
        StandBy,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[7];
    State currentState;
    State history[1];
    void save_history( State compositeState, State subState );
    bool check_history( State compositeState, State subState );
    void entryaction_____Backup( const UMLRTMessage * msg );
    void entryaction_____Backup__RunAsSlave( const UMLRTMessage * msg );
    void entryaction_____Backup__TryBeMaster( const UMLRTMessage * msg );
    void entryaction_____Failure( const UMLRTMessage * msg );
    void entryaction_____RunAsMaster( const UMLRTMessage * msg );
    void entryaction_____StandBy( const UMLRTMessage * msg );
    void exitaction_____Backup( const UMLRTMessage * msg );
    void exitaction_____Backup__RunAsSlave( const UMLRTMessage * msg );
    void exitaction_____Backup__TryBeMaster( const UMLRTMessage * msg );
    void exitaction_____Failure( const UMLRTMessage * msg );
    void exitaction_____RunAsMaster( const UMLRTMessage * msg );
    void exitaction_____StandBy( const UMLRTMessage * msg );
    void transitionaction_____Backup__BackToSlave( const UMLRTMessage * msg );
    void transitionaction_____Backup__KeepAliveMsg( const UMLRTMessage * msg );
    void transitionaction_____Backup__NokeepAlive( const UMLRTMessage * msg );
    void transitionaction_____BeingMaster( const UMLRTMessage * msg );
    void transitionaction_____KeepAlive( const UMLRTMessage * msg );
    void transitionaction_____MasterAnnounce( const UMLRTMessage * msg );
    void transitionaction_____Recover( const UMLRTMessage * msg );
    void transitionaction_____ServerFaliure( const UMLRTMessage * msg );
    void transitionaction_____ServiceRequest( const UMLRTMessage * msg );
    void transitionaction_____TransitionAction8( const UMLRTMessage * msg );
    void transitionaction_____TransitionAction9( const UMLRTMessage * msg );
    void transitionaction_____initTimer( const UMLRTMessage * msg );
    bool action_____ActiveMode__checkConfig( const UMLRTMessage * msg );
    bool action_____Backup__CheckNoMaster__CheckNoServer( const UMLRTMessage * msg );
    bool action_____initTimer__CheckConfig( const UMLRTMessage * msg );
    void actionchain_____Backup__BackToSlave( const UMLRTMessage * msg );
    void actionchain_____Backup__KeepAliveMsg( const UMLRTMessage * msg );
    void actionchain_____Backup__NokeepAlive( const UMLRTMessage * msg );
    void actionchain_____Backup__ReplyConfig( const UMLRTMessage * msg );
    void actionchain_____Backup__backtoslave( const UMLRTMessage * msg );
    void actionchain_____Backup__new_transition_1( const UMLRTMessage * msg );
    void actionchain_____Backup__new_transition_2( const UMLRTMessage * msg );
    void actionchain_____Backup__new_transition_3( const UMLRTMessage * msg );
    void actionchain_____BeSlave( const UMLRTMessage * msg );
    void actionchain_____BeingMaster( const UMLRTMessage * msg );
    void actionchain_____KeepAlive( const UMLRTMessage * msg );
    void actionchain_____MasterAnnounce( const UMLRTMessage * msg );
    void actionchain_____PassiveMode( const UMLRTMessage * msg );
    void actionchain_____Recover( const UMLRTMessage * msg );
    void actionchain_____ServerFaliure( const UMLRTMessage * msg );
    void actionchain_____ServiceRequest( const UMLRTMessage * msg );
    void actionchain_____TransitionAction21( const UMLRTMessage * msg );
    void actionchain_____TransitionAction8( const UMLRTMessage * msg );
    void actionchain_____TransitionAction9( const UMLRTMessage * msg );
    void actionchain_____initTimer( const UMLRTMessage * msg );
    void actionchain_____purgeotherMessage( const UMLRTMessage * msg );
    State junction_____Backup__ExitPoint1( const UMLRTMessage * msg );
    State junction_____Backup__Slave( const UMLRTMessage * msg );
    State junction_____BeMaster( const UMLRTMessage * msg );
    State choice_____Backup__Choice2( const UMLRTMessage * msg );
    State choice_____Backup__deephistory( const UMLRTMessage * msg );
    State choice_____CheckConfig( const UMLRTMessage * msg );
    State choice_____Choice1( const UMLRTMessage * msg );
    State state_____Backup__RunAsSlave( const UMLRTMessage * msg );
    State state_____Backup__TryBeMaster( const UMLRTMessage * msg );
    State state_____Failure( const UMLRTMessage * msg );
    State state_____RunAsMaster( const UMLRTMessage * msg );
    State state_____StandBy( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass Server;

#endif

