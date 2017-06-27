
#ifndef SERVER_HH
#define SERVER_HH

#include "Config.hh"
#include "ExtInterface.hh"
#include "FailOver.hh"
#include "Host.hh"
#include "Services.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
#include "umlrttimerid.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include "Event.h"

#include "SROManager.h"

class Capsule_Server : public Capsule_Host
{
public:
    Capsule_Server( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    Config::Base ConfigComm;
public:
    enum BorderPortId
    {
        borderport_ConfigComm,
        borderport_KeepAliveTimer,
        borderport_Master,
        borderport_MasterAnnounceTimer,
        borderport_ServerComm,
        borderport_Slave,
        borderport_Timer,
        borderport_extComm
    };
protected:
    UMLRTTimerProtocol_baserole KeepAliveTimer;
    FailOver::Base Master;
    UMLRTTimerProtocol_baserole MasterAnnounceTimer;
    Services::Conj ServerComm;
    FailOver::Conj Slave;
    UMLRTTimerProtocol_baserole Timer;
    ExtInterface::Conj extComm;
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
        port_Timer,
        port_extComm
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    UMLRTTimerId KeepAliveTimerId;
    int KeepAliveTimeOut;
    UMLRTTimerId AnnouncementTimerId;
    int AnnouncementTimeOut;
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
        Backup,
        Backup__Debug__C__BackToSlave,
        Backup__Debug__C__CheckNoMaster,
        Backup__Debug__C__Initial1__RunAsSlave__2,
        Backup__Debug__C__KeepAliveMsg,
        Backup__Debug__C__NokeepAlive,
        Backup__Debug__C__ReplyConfig,
        Backup__Debug__C__backtoslave,
        Backup__Debug__C__backtoslave1,
        Debug__C__ActiveMode,
        Debug__C__BeSlave,
        Debug__C__BeingMaster,
        Debug__C__ExitPoint1__BeMaster__4,
        Debug__C__Init__StandBy__3,
        Debug__C__KeepAlive,
        Debug__C__PassiveMode,
        Debug__C__Recover,
        Debug__C__ServerFaliure,
        Debug__C__StandBy__CheckConfig__5,
        Debug__C__initTimer,
        Debug__C__purgeotherMessage,
        Backup__Debug__C__BackToSlave__Debug__A__Ac__BackToSlave,
        Backup__Debug__C__BackToSlave__Debug__B__Ac__BackToSlave,
        Backup__Debug__C__BackToSlave__Debug__B__Ex__TryBeMaster,
        Backup__Debug__C__BackToSlave__boundary,
        Backup__Debug__C__CheckNoMaster__Debug__A__Ac__CheckNoMaster,
        Backup__Debug__C__CheckNoMaster__Debug__B__Ac__CheckNoMaster,
        Backup__Debug__C__CheckNoMaster__boundary,
        Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__Ac__Initial1__RunAsSlave__2,
        Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__En__Initial1__RunAsSlave__2,
        Backup__Debug__C__Initial1__RunAsSlave__2__Debug__B__Ac__Initial1__RunAsSlave__2,
        Backup__Debug__C__Initial1__RunAsSlave__2__boundary,
        Backup__Debug__C__KeepAliveMsg__Debug__A__Ac__KeepAliveMsg,
        Backup__Debug__C__KeepAliveMsg__Debug__A__En__RunAsSlave,
        Backup__Debug__C__KeepAliveMsg__Debug__B__Ac__KeepAliveMsg,
        Backup__Debug__C__KeepAliveMsg__Debug__B__Ex__RunAsSlave,
        Backup__Debug__C__KeepAliveMsg__boundary,
        Backup__Debug__C__NokeepAlive__Debug__A__Ac__NokeepAlive,
        Backup__Debug__C__NokeepAlive__Debug__A__En__TryBeMaster,
        Backup__Debug__C__NokeepAlive__Debug__B__Ac__NokeepAlive,
        Backup__Debug__C__NokeepAlive__Debug__B__Ex__RunAsSlave,
        Backup__Debug__C__NokeepAlive__boundary,
        Backup__Debug__C__ReplyConfig__Debug__A__Ac__ReplyConfig,
        Backup__Debug__C__ReplyConfig__Debug__B__Ac__ReplyConfig,
        Backup__Debug__C__ReplyConfig__Debug__B__Ex__TryBeMaster,
        Backup__Debug__C__ReplyConfig__boundary,
        Backup__Debug__C__backtoslave1__Debug__A__Ac__backtoslave1,
        Backup__Debug__C__backtoslave1__Debug__B__Ac__backtoslave1,
        Backup__Debug__C__backtoslave1__boundary,
        Backup__Debug__C__backtoslave__Debug__A__Ac__backtoslave,
        Backup__Debug__C__backtoslave__Debug__A__En__backtoslave,
        Backup__Debug__C__backtoslave__Debug__B__Ac__backtoslave,
        Backup__Debug__C__backtoslave__boundary,
        Backup__RunAsSlave,
        Backup__TryBeMaster,
        Debug__C__ActiveMode__Debug__A__Ac__ActiveMode,
        Debug__C__ActiveMode__Debug__B__Ac__ActiveMode,
        Debug__C__ActiveMode__boundary,
        Debug__C__BeSlave__Debug__A__Ac__BeSlave,
        Debug__C__BeSlave__Debug__A__En__BeSlave,
        Debug__C__BeSlave__Debug__B__Ac__BeSlave,
        Debug__C__BeSlave__boundary,
        Debug__C__BeingMaster__Debug__A__Ac__BeingMaster,
        Debug__C__BeingMaster__Debug__A__En__BeingMaster,
        Debug__C__BeingMaster__Debug__B__Ac__BeingMaster,
        Debug__C__BeingMaster__boundary,
        Debug__C__ExitPoint1__BeMaster__4__Debug__A__Ac__ExitPoint1__BeMaster__4,
        Debug__C__ExitPoint1__BeMaster__4__Debug__B__Ac__ExitPoint1__BeMaster__4,
        Debug__C__ExitPoint1__BeMaster__4__boundary,
        Debug__C__Init__StandBy__3__Debug__A__Ac__Init__StandBy__3,
        Debug__C__Init__StandBy__3__Debug__A__En__Init__StandBy__3,
        Debug__C__Init__StandBy__3__Debug__B__Ac__Init__StandBy__3,
        Debug__C__Init__StandBy__3__boundary,
        Debug__C__KeepAlive__Debug__A__Ac__KeepAlive,
        Debug__C__KeepAlive__Debug__A__En__RunAsMaster,
        Debug__C__KeepAlive__Debug__B__Ac__KeepAlive,
        Debug__C__KeepAlive__Debug__B__Ex__RunAsMaster,
        Debug__C__KeepAlive__boundary,
        Debug__C__MasterAnnounce,
        Debug__C__PassiveMode__Debug__A__Ac__PassiveMode,
        Debug__C__PassiveMode__Debug__A__En__PassiveMode,
        Debug__C__PassiveMode__Debug__B__Ac__PassiveMode,
        Debug__C__PassiveMode__boundary,
        Debug__C__Recover__Debug__A__Ac__Recover,
        Debug__C__Recover__Debug__B__Ac__Recover,
        Debug__C__Recover__Debug__B__Ex__Failure,
        Debug__C__Recover__boundary,
        Debug__C__ServerFaliure__Debug__A__Ac__ServerFaliure,
        Debug__C__ServerFaliure__Debug__A__En__Failure,
        Debug__C__ServerFaliure__Debug__B__Ac__ServerFaliure,
        Debug__C__ServerFaliure__Debug__B__Ex__RunAsMaster,
        Debug__C__ServerFaliure__boundary,
        Debug__C__ServiceRequest,
        Debug__C__StandBy__CheckConfig__5__Debug__A__Ac__StandBy__CheckConfig__5,
        Debug__C__StandBy__CheckConfig__5__Debug__B__Ac__StandBy__CheckConfig__5,
        Debug__C__StandBy__CheckConfig__5__Debug__B__Ex__StandBy,
        Debug__C__StandBy__CheckConfig__5__boundary,
        Debug__C__initTimer__Debug__A__Ac__initTimer,
        Debug__C__initTimer__Debug__A__En__initTimer,
        Debug__C__initTimer__Debug__B__Ac__initTimer,
        Debug__C__initTimer__boundary,
        Debug__C__purgeotherMessage__Debug__A__Ac__purgeotherMessage,
        Debug__C__purgeotherMessage__Debug__A__En__Failure,
        Debug__C__purgeotherMessage__Debug__B__Ac__purgeotherMessage,
        Debug__C__purgeotherMessage__Debug__B__Ex__Failure,
        Debug__C__purgeotherMessage__boundary,
        Debug__InitState,
        Failure,
        RunAsMaster,
        StandBy,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[111];
    State currentState;
    State history[21];
    void save_history( State compositeState, State subState );
    bool check_history( State compositeState, State subState );
    void entryaction_____Backup( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__BackToSlave__Debug__A__Ac__BackToSlave( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__BackToSlave__Debug__B__Ac__BackToSlave( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__BackToSlave__Debug__B__Ex__TryBeMaster( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__BackToSlave__boundary( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__CheckNoMaster__Debug__A__Ac__CheckNoMaster( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__CheckNoMaster__Debug__B__Ac__CheckNoMaster( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__CheckNoMaster__boundary( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__Ac__Initial1__RunAsSlave__2( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__En__Initial1__RunAsSlave__2( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__B__Ac__Initial1__RunAsSlave__2( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__Initial1__RunAsSlave__2__boundary( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__KeepAliveMsg__Debug__A__Ac__KeepAliveMsg( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__KeepAliveMsg__Debug__A__En__RunAsSlave( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__KeepAliveMsg__Debug__B__Ac__KeepAliveMsg( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__KeepAliveMsg__Debug__B__Ex__RunAsSlave( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__KeepAliveMsg__boundary( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__NokeepAlive__Debug__A__Ac__NokeepAlive( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__NokeepAlive__Debug__A__En__TryBeMaster( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__NokeepAlive__Debug__B__Ac__NokeepAlive( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__NokeepAlive__Debug__B__Ex__RunAsSlave( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__NokeepAlive__boundary( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__ReplyConfig__Debug__A__Ac__ReplyConfig( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__ReplyConfig__Debug__B__Ac__ReplyConfig( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__ReplyConfig__Debug__B__Ex__TryBeMaster( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__ReplyConfig__boundary( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__backtoslave1__Debug__A__Ac__backtoslave1( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__backtoslave1__Debug__B__Ac__backtoslave1( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__backtoslave1__boundary( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__backtoslave__Debug__A__Ac__backtoslave( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__backtoslave__Debug__A__En__backtoslave( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__backtoslave__Debug__B__Ac__backtoslave( const UMLRTMessage * msg );
    void entryaction_____Backup__Debug__C__backtoslave__boundary( const UMLRTMessage * msg );
    void entryaction_____Backup__RunAsSlave( const UMLRTMessage * msg );
    void entryaction_____Backup__TryBeMaster( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ActiveMode__Debug__A__Ac__ActiveMode( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ActiveMode__Debug__B__Ac__ActiveMode( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ActiveMode__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__BeSlave__Debug__A__Ac__BeSlave( const UMLRTMessage * msg );
    void entryaction_____Debug__C__BeSlave__Debug__A__En__BeSlave( const UMLRTMessage * msg );
    void entryaction_____Debug__C__BeSlave__Debug__B__Ac__BeSlave( const UMLRTMessage * msg );
    void entryaction_____Debug__C__BeSlave__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__BeingMaster__Debug__A__Ac__BeingMaster( const UMLRTMessage * msg );
    void entryaction_____Debug__C__BeingMaster__Debug__A__En__BeingMaster( const UMLRTMessage * msg );
    void entryaction_____Debug__C__BeingMaster__Debug__B__Ac__BeingMaster( const UMLRTMessage * msg );
    void entryaction_____Debug__C__BeingMaster__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ExitPoint1__BeMaster__4__Debug__A__Ac__ExitPoint1__BeMaster__4( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ExitPoint1__BeMaster__4__Debug__B__Ac__ExitPoint1__BeMaster__4( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ExitPoint1__BeMaster__4__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Init__StandBy__3__Debug__A__Ac__Init__StandBy__3( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Init__StandBy__3__Debug__A__En__Init__StandBy__3( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Init__StandBy__3__Debug__B__Ac__Init__StandBy__3( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Init__StandBy__3__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__KeepAlive__Debug__A__Ac__KeepAlive( const UMLRTMessage * msg );
    void entryaction_____Debug__C__KeepAlive__Debug__A__En__RunAsMaster( const UMLRTMessage * msg );
    void entryaction_____Debug__C__KeepAlive__Debug__B__Ac__KeepAlive( const UMLRTMessage * msg );
    void entryaction_____Debug__C__KeepAlive__Debug__B__Ex__RunAsMaster( const UMLRTMessage * msg );
    void entryaction_____Debug__C__KeepAlive__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__MasterAnnounce( const UMLRTMessage * msg );
    void entryaction_____Debug__C__PassiveMode__Debug__A__Ac__PassiveMode( const UMLRTMessage * msg );
    void entryaction_____Debug__C__PassiveMode__Debug__A__En__PassiveMode( const UMLRTMessage * msg );
    void entryaction_____Debug__C__PassiveMode__Debug__B__Ac__PassiveMode( const UMLRTMessage * msg );
    void entryaction_____Debug__C__PassiveMode__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Recover__Debug__A__Ac__Recover( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Recover__Debug__B__Ac__Recover( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Recover__Debug__B__Ex__Failure( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Recover__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ServerFaliure__Debug__A__Ac__ServerFaliure( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ServerFaliure__Debug__A__En__Failure( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ServerFaliure__Debug__B__Ac__ServerFaliure( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ServerFaliure__Debug__B__Ex__RunAsMaster( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ServerFaliure__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ServiceRequest( const UMLRTMessage * msg );
    void entryaction_____Debug__C__StandBy__CheckConfig__5__Debug__A__Ac__StandBy__CheckConfig__5( const UMLRTMessage * msg );
    void entryaction_____Debug__C__StandBy__CheckConfig__5__Debug__B__Ac__StandBy__CheckConfig__5( const UMLRTMessage * msg );
    void entryaction_____Debug__C__StandBy__CheckConfig__5__Debug__B__Ex__StandBy( const UMLRTMessage * msg );
    void entryaction_____Debug__C__StandBy__CheckConfig__5__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__initTimer__Debug__A__Ac__initTimer( const UMLRTMessage * msg );
    void entryaction_____Debug__C__initTimer__Debug__A__En__initTimer( const UMLRTMessage * msg );
    void entryaction_____Debug__C__initTimer__Debug__B__Ac__initTimer( const UMLRTMessage * msg );
    void entryaction_____Debug__C__initTimer__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__purgeotherMessage__Debug__A__Ac__purgeotherMessage( const UMLRTMessage * msg );
    void entryaction_____Debug__C__purgeotherMessage__Debug__A__En__Failure( const UMLRTMessage * msg );
    void entryaction_____Debug__C__purgeotherMessage__Debug__B__Ac__purgeotherMessage( const UMLRTMessage * msg );
    void entryaction_____Debug__C__purgeotherMessage__Debug__B__Ex__Failure( const UMLRTMessage * msg );
    void entryaction_____Debug__C__purgeotherMessage__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__InitState( const UMLRTMessage * msg );
    void entryaction_____Failure( const UMLRTMessage * msg );
    void entryaction_____RunAsMaster( const UMLRTMessage * msg );
    void entryaction_____StandBy( const UMLRTMessage * msg );
    void exitaction_____Backup( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__BackToSlave__Debug__A__Ac__BackToSlave( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__BackToSlave__Debug__B__Ac__BackToSlave( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__BackToSlave__Debug__B__Ex__TryBeMaster( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__BackToSlave__boundary( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__CheckNoMaster__Debug__A__Ac__CheckNoMaster( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__CheckNoMaster__Debug__B__Ac__CheckNoMaster( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__CheckNoMaster__boundary( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__Ac__Initial1__RunAsSlave__2( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__En__Initial1__RunAsSlave__2( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__B__Ac__Initial1__RunAsSlave__2( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__Initial1__RunAsSlave__2__boundary( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__KeepAliveMsg__Debug__A__Ac__KeepAliveMsg( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__KeepAliveMsg__Debug__A__En__RunAsSlave( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__KeepAliveMsg__Debug__B__Ac__KeepAliveMsg( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__KeepAliveMsg__Debug__B__Ex__RunAsSlave( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__KeepAliveMsg__boundary( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__NokeepAlive__Debug__A__Ac__NokeepAlive( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__NokeepAlive__Debug__A__En__TryBeMaster( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__NokeepAlive__Debug__B__Ac__NokeepAlive( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__NokeepAlive__Debug__B__Ex__RunAsSlave( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__NokeepAlive__boundary( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__ReplyConfig__Debug__A__Ac__ReplyConfig( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__ReplyConfig__Debug__B__Ac__ReplyConfig( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__ReplyConfig__Debug__B__Ex__TryBeMaster( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__ReplyConfig__boundary( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__backtoslave1__Debug__A__Ac__backtoslave1( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__backtoslave1__Debug__B__Ac__backtoslave1( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__backtoslave1__boundary( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__backtoslave__Debug__A__Ac__backtoslave( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__backtoslave__Debug__A__En__backtoslave( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__backtoslave__Debug__B__Ac__backtoslave( const UMLRTMessage * msg );
    void exitaction_____Backup__Debug__C__backtoslave__boundary( const UMLRTMessage * msg );
    void exitaction_____Backup__RunAsSlave( const UMLRTMessage * msg );
    void exitaction_____Backup__TryBeMaster( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ActiveMode__Debug__A__Ac__ActiveMode( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ActiveMode__Debug__B__Ac__ActiveMode( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ActiveMode__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__BeSlave__Debug__A__Ac__BeSlave( const UMLRTMessage * msg );
    void exitaction_____Debug__C__BeSlave__Debug__A__En__BeSlave( const UMLRTMessage * msg );
    void exitaction_____Debug__C__BeSlave__Debug__B__Ac__BeSlave( const UMLRTMessage * msg );
    void exitaction_____Debug__C__BeSlave__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__BeingMaster__Debug__A__Ac__BeingMaster( const UMLRTMessage * msg );
    void exitaction_____Debug__C__BeingMaster__Debug__A__En__BeingMaster( const UMLRTMessage * msg );
    void exitaction_____Debug__C__BeingMaster__Debug__B__Ac__BeingMaster( const UMLRTMessage * msg );
    void exitaction_____Debug__C__BeingMaster__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ExitPoint1__BeMaster__4__Debug__A__Ac__ExitPoint1__BeMaster__4( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ExitPoint1__BeMaster__4__Debug__B__Ac__ExitPoint1__BeMaster__4( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ExitPoint1__BeMaster__4__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Init__StandBy__3__Debug__A__Ac__Init__StandBy__3( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Init__StandBy__3__Debug__A__En__Init__StandBy__3( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Init__StandBy__3__Debug__B__Ac__Init__StandBy__3( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Init__StandBy__3__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__KeepAlive__Debug__A__Ac__KeepAlive( const UMLRTMessage * msg );
    void exitaction_____Debug__C__KeepAlive__Debug__A__En__RunAsMaster( const UMLRTMessage * msg );
    void exitaction_____Debug__C__KeepAlive__Debug__B__Ac__KeepAlive( const UMLRTMessage * msg );
    void exitaction_____Debug__C__KeepAlive__Debug__B__Ex__RunAsMaster( const UMLRTMessage * msg );
    void exitaction_____Debug__C__KeepAlive__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__MasterAnnounce( const UMLRTMessage * msg );
    void exitaction_____Debug__C__PassiveMode__Debug__A__Ac__PassiveMode( const UMLRTMessage * msg );
    void exitaction_____Debug__C__PassiveMode__Debug__A__En__PassiveMode( const UMLRTMessage * msg );
    void exitaction_____Debug__C__PassiveMode__Debug__B__Ac__PassiveMode( const UMLRTMessage * msg );
    void exitaction_____Debug__C__PassiveMode__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Recover__Debug__A__Ac__Recover( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Recover__Debug__B__Ac__Recover( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Recover__Debug__B__Ex__Failure( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Recover__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ServerFaliure__Debug__A__Ac__ServerFaliure( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ServerFaliure__Debug__A__En__Failure( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ServerFaliure__Debug__B__Ac__ServerFaliure( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ServerFaliure__Debug__B__Ex__RunAsMaster( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ServerFaliure__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ServiceRequest( const UMLRTMessage * msg );
    void exitaction_____Debug__C__StandBy__CheckConfig__5__Debug__A__Ac__StandBy__CheckConfig__5( const UMLRTMessage * msg );
    void exitaction_____Debug__C__StandBy__CheckConfig__5__Debug__B__Ac__StandBy__CheckConfig__5( const UMLRTMessage * msg );
    void exitaction_____Debug__C__StandBy__CheckConfig__5__Debug__B__Ex__StandBy( const UMLRTMessage * msg );
    void exitaction_____Debug__C__StandBy__CheckConfig__5__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__initTimer__Debug__A__Ac__initTimer( const UMLRTMessage * msg );
    void exitaction_____Debug__C__initTimer__Debug__A__En__initTimer( const UMLRTMessage * msg );
    void exitaction_____Debug__C__initTimer__Debug__B__Ac__initTimer( const UMLRTMessage * msg );
    void exitaction_____Debug__C__initTimer__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__purgeotherMessage__Debug__A__Ac__purgeotherMessage( const UMLRTMessage * msg );
    void exitaction_____Debug__C__purgeotherMessage__Debug__A__En__Failure( const UMLRTMessage * msg );
    void exitaction_____Debug__C__purgeotherMessage__Debug__B__Ac__purgeotherMessage( const UMLRTMessage * msg );
    void exitaction_____Debug__C__purgeotherMessage__Debug__B__Ex__Failure( const UMLRTMessage * msg );
    void exitaction_____Debug__C__purgeotherMessage__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__InitState( const UMLRTMessage * msg );
    void exitaction_____Failure( const UMLRTMessage * msg );
    void exitaction_____RunAsMaster( const UMLRTMessage * msg );
    void exitaction_____StandBy( const UMLRTMessage * msg );
    void transitionaction_____ActiveMode( const UMLRTMessage * msg );
    void transitionaction_____Backup__BackToSlave( const UMLRTMessage * msg );
    void transitionaction_____Backup__CheckNoMaster( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__BackToSlave( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__BackToSlave__E( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__BackToSlave__S( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__BackToSlave__dbg( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__BackToSlave__Debug__AC__BackToSlave( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__BackToSlave__Debug__Ex__TryBeMaster( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__BackToSlave__Debug__end__trans__BackToSlave( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__Ac__Initial1__RunAsSlave__2( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__En__RunAsSlave( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__end__trans__Initial1__RunAsSlave__2( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__init__trans__Initial1__RunAsSlave__2( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__KeepAliveMsg__Debug__AC__KeepAliveMsg( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__KeepAliveMsg__Debug__En__RunAsSlave( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__KeepAliveMsg__Debug__Ex__RunAsSlave( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__KeepAliveMsg__Debug__end__trans__KeepAliveMsg( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__KeepAliveMsg__Debug__init__trans__KeepAliveMsg( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__NokeepAlive__Debug__AC__NokeepAlive( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__NokeepAlive__Debug__En__TryBeMaster( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__NokeepAlive__Debug__Ex__RunAsSlave( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__NokeepAlive__Debug__end__trans__NokeepAlive( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__NokeepAlive__Debug__init__trans__NokeepAlive( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__ReplyConfig__Debug__AC__ReplyConfig( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__ReplyConfig__Debug__Ex__TryBeMaster( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__ReplyConfig__Debug__end__trans__ReplyConfig( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__backtoslave__Debug__Ac__backtoslave( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__backtoslave__Debug__En__RunAsSlave( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__backtoslave__Debug__end__trans__backtoslave( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__C__backtoslave__Debug__init__trans__backtoslave( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__CheckNoMaster( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__CheckNoMaster__E( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__CheckNoMaster__S( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__CheckNoMaster__dbg( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__Initial1__RunAsSlave__2__E( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__Initial1__RunAsSlave__2__S( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__Initial1__RunAsSlave__2__dbg( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__KeepAliveMsg( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__KeepAliveMsg__E( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__KeepAliveMsg__S( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__KeepAliveMsg__dbg( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__NokeepAlive( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__NokeepAlive__E( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__NokeepAlive__S( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__NokeepAlive__dbg( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__ReplyConfig( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__ReplyConfig__E( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__ReplyConfig__S( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__ReplyConfig__dbg( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__backtoslave( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__backtoslave1( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__backtoslave1__E( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__backtoslave1__S( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__backtoslave1__dbg( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__backtoslave__E( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__backtoslave__S( const UMLRTMessage * msg );
    void transitionaction_____Backup__Debug__backtoslave__dbg( const UMLRTMessage * msg );
    void transitionaction_____Backup__Initial1__RunAsSlave__2( const UMLRTMessage * msg );
    void transitionaction_____Backup__KeepAliveMsg( const UMLRTMessage * msg );
    void transitionaction_____Backup__NokeepAlive( const UMLRTMessage * msg );
    void transitionaction_____Backup__ReplyConfig( const UMLRTMessage * msg );
    void transitionaction_____Backup__backtoslave( const UMLRTMessage * msg );
    void transitionaction_____Backup__backtoslave1( const UMLRTMessage * msg );
    void transitionaction_____Backup__new_transition_11( const UMLRTMessage * msg );
    void transitionaction_____BeSlave( const UMLRTMessage * msg );
    void transitionaction_____BeingMaster( const UMLRTMessage * msg );
    void transitionaction_____Debug__ActiveMode( const UMLRTMessage * msg );
    void transitionaction_____Debug__ActiveMode__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__ActiveMode__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__ActiveMode__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__BeSlave( const UMLRTMessage * msg );
    void transitionaction_____Debug__BeSlave__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__BeSlave__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__BeSlave__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__BeingMaster( const UMLRTMessage * msg );
    void transitionaction_____Debug__BeingMaster__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__BeingMaster__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__BeingMaster__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__BeSlave__Debug__Ac__BeSlave( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__BeSlave__Debug__En__Backup( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__BeSlave__Debug__end__trans__BeSlave( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__BeSlave__Debug__init__trans__BeSlave( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__BeingMaster__Debug__Ac__BeingMaster( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__BeingMaster__Debug__En__RunAsMaster( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__BeingMaster__Debug__end__trans__BeingMaster( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__BeingMaster__Debug__init__trans__BeingMaster( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Init__StandBy__3__Debug__Ac__Init__StandBy__3( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Init__StandBy__3__Debug__En__StandBy( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Init__StandBy__3__Debug__end__trans__Init__StandBy__3( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Init__StandBy__3__Debug__init__trans__Init__StandBy__3( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__KeepAlive__Debug__AC__KeepAlive( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__KeepAlive__Debug__En__RunAsMaster( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__KeepAlive__Debug__Ex__RunAsMaster( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__KeepAlive__Debug__end__trans__KeepAlive( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__KeepAlive__Debug__init__trans__KeepAlive( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__PassiveMode__Debug__Ac__PassiveMode( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__PassiveMode__Debug__En__Backup( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__PassiveMode__Debug__end__trans__PassiveMode( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__PassiveMode__Debug__init__trans__PassiveMode( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Recover__Debug__AC__Recover( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Recover__Debug__Ex__Failure( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Recover__Debug__end__trans__Recover( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__ServerFaliure__Debug__AC__ServerFaliure( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__ServerFaliure__Debug__En__Failure( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__ServerFaliure__Debug__Ex__RunAsMaster( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__ServerFaliure__Debug__end__trans__ServerFaliure( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__ServerFaliure__Debug__init__trans__ServerFaliure( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__StandBy__CheckConfig__5__Debug__AC__StandBy__CheckConfig__5( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__StandBy__CheckConfig__5__Debug__Ex__StandBy( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__StandBy__CheckConfig__5__Debug__end__trans__StandBy__CheckConfig__5( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__initTimer__Debug__Ac__initTimer( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__initTimer__Debug__En__RunAsMaster( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__initTimer__Debug__end__trans__initTimer( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__initTimer__Debug__init__trans__initTimer( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__purgeotherMessage__Debug__AC__purgeotherMessage( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__purgeotherMessage__Debug__En__Failure( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__purgeotherMessage__Debug__Ex__Failure( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__purgeotherMessage__Debug__end__trans__purgeotherMessage( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__purgeotherMessage__Debug__init__trans__purgeotherMessage( const UMLRTMessage * msg );
    void transitionaction_____Debug__ExitPoint1__BeMaster__4( const UMLRTMessage * msg );
    void transitionaction_____Debug__ExitPoint1__BeMaster__4__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__ExitPoint1__BeMaster__4__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__ExitPoint1__BeMaster__4__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__InitDebug( const UMLRTMessage * msg );
    void transitionaction_____Debug__Init__StandBy__3( const UMLRTMessage * msg );
    void transitionaction_____Debug__Init__StandBy__3__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__Init__StandBy__3__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__Init__StandBy__3__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__KeepAlive( const UMLRTMessage * msg );
    void transitionaction_____Debug__KeepAlive__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__KeepAlive__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__KeepAlive__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__MasterAnnounce( const UMLRTMessage * msg );
    void transitionaction_____Debug__MasterAnnounce__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__MasterAnnounce__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__MasterAnnounce__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__PassiveMode( const UMLRTMessage * msg );
    void transitionaction_____Debug__PassiveMode__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__PassiveMode__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__PassiveMode__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__Recover( const UMLRTMessage * msg );
    void transitionaction_____Debug__Recover__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__Recover__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__Recover__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__ServerFaliure( const UMLRTMessage * msg );
    void transitionaction_____Debug__ServerFaliure__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__ServerFaliure__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__ServerFaliure__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__ServiceRequest( const UMLRTMessage * msg );
    void transitionaction_____Debug__ServiceRequest__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__ServiceRequest__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__ServiceRequest__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__StandBy__CheckConfig__5( const UMLRTMessage * msg );
    void transitionaction_____Debug__StandBy__CheckConfig__5__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__StandBy__CheckConfig__5__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__StandBy__CheckConfig__5__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__initTimer( const UMLRTMessage * msg );
    void transitionaction_____Debug__initTimer__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__initTimer__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__initTimer__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__purgeotherMessage( const UMLRTMessage * msg );
    void transitionaction_____Debug__purgeotherMessage__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__purgeotherMessage__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__purgeotherMessage__dbg( const UMLRTMessage * msg );
    void transitionaction_____ExitPoint1__BeMaster__4( const UMLRTMessage * msg );
    void transitionaction_____Init__StandBy__3( const UMLRTMessage * msg );
    void transitionaction_____KeepAlive( const UMLRTMessage * msg );
    void transitionaction_____MasterAnnounce( const UMLRTMessage * msg );
    void transitionaction_____PassiveMode( const UMLRTMessage * msg );
    void transitionaction_____Recover( const UMLRTMessage * msg );
    void transitionaction_____ServerFaliure( const UMLRTMessage * msg );
    void transitionaction_____ServiceRequest( const UMLRTMessage * msg );
    void transitionaction_____StandBy__CheckConfig__5( const UMLRTMessage * msg );
    void transitionaction_____initTimer( const UMLRTMessage * msg );
    void transitionaction_____purgeotherMessage( const UMLRTMessage * msg );
    bool action_____Backup__Debug__BackToSlave__S__Debug__GuardBackToSlave( const UMLRTMessage * msg );
    bool action_____Backup__Debug__CheckNoMaster__CheckNoServer( const UMLRTMessage * msg );
    bool action_____Backup__Debug__CheckNoMaster__S__Debug__GuardCheckNoMaster( const UMLRTMessage * msg );
    bool action_____Backup__Debug__Initial1__RunAsSlave__2__S__Debug__GuardInitial1__RunAsSlave__2( const UMLRTMessage * msg );
    bool action_____Backup__Debug__KeepAliveMsg__S__Debug__GuardKeepAliveMsg( const UMLRTMessage * msg );
    bool action_____Backup__Debug__NokeepAlive__S__Debug__GuardNokeepAlive( const UMLRTMessage * msg );
    bool action_____Backup__Debug__ReplyConfig__S__Debug__GuardReplyConfig( const UMLRTMessage * msg );
    bool action_____Backup__Debug__backtoslave1__S__Debug__Guardbacktoslave1( const UMLRTMessage * msg );
    bool action_____Backup__Debug__backtoslave__S__Debug__Guardbacktoslave( const UMLRTMessage * msg );
    bool action_____Debug__ActiveMode__S__Debug__GuardActiveMode( const UMLRTMessage * msg );
    bool action_____Debug__ActiveMode__checkConfig( const UMLRTMessage * msg );
    bool action_____Debug__BeSlave__S__Debug__GuardBeSlave( const UMLRTMessage * msg );
    bool action_____Debug__BeingMaster__S__Debug__GuardBeingMaster( const UMLRTMessage * msg );
    bool action_____Debug__ExitPoint1__BeMaster__4__S__Debug__GuardExitPoint1__BeMaster__4( const UMLRTMessage * msg );
    bool action_____Debug__Init__StandBy__3__S__Debug__GuardInit__StandBy__3( const UMLRTMessage * msg );
    bool action_____Debug__KeepAlive__S__Debug__GuardKeepAlive( const UMLRTMessage * msg );
    bool action_____Debug__MasterAnnounce__S__Debug__GuardMasterAnnounce( const UMLRTMessage * msg );
    bool action_____Debug__PassiveMode__S__Debug__GuardPassiveMode( const UMLRTMessage * msg );
    bool action_____Debug__Recover__S__Debug__GuardRecover( const UMLRTMessage * msg );
    bool action_____Debug__ServerFaliure__S__Debug__GuardServerFaliure( const UMLRTMessage * msg );
    bool action_____Debug__ServiceRequest__S__Debug__GuardServiceRequest( const UMLRTMessage * msg );
    bool action_____Debug__StandBy__CheckConfig__5__S__Debug__GuardStandBy__CheckConfig__5( const UMLRTMessage * msg );
    bool action_____Debug__initTimer__CheckConfig( const UMLRTMessage * msg );
    bool action_____Debug__initTimer__S__Debug__GuardinitTimer( const UMLRTMessage * msg );
    bool action_____Debug__purgeotherMessage__S__Debug__GuardpurgeotherMessage( const UMLRTMessage * msg );
    void actionchain_____ActiveMode( const UMLRTMessage * msg );
    void actionchain_____Backup__BackToSlave( const UMLRTMessage * msg );
    void actionchain_____Backup__CheckNoMaster( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__BackToSlave( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__BackToSlave__E( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__BackToSlave__S( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__BackToSlave__dbg( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__BackToSlave__Debug__AC__BackToSlave( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__BackToSlave__Debug__Ex__TryBeMaster( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__BackToSlave__Debug__end__trans__BackToSlave( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__BackToSlave__Debug__init__trans__BackToSlave( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__BackToSlave__new_transition_20( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__BackToSlave__new_transition_21( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__BackToSlave__new_transition_22( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__BackToSlave__new_transition_23_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__BackToSlave__new_transition_24( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__BackToSlave__new_transition_25( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__BackToSlave__new_transition_26( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__BackToSlave__new_transition_27( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__CheckNoMaster__Debug__Ac__CheckNoMaster( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__CheckNoMaster__Debug__end__trans__CheckNoMaster( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__CheckNoMaster__Debug__init__trans__CheckNoMaster( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__CheckNoMaster__new_transition_60( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__CheckNoMaster__new_transition_61( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__CheckNoMaster__new_transition_62_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__CheckNoMaster__new_transition_63( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__CheckNoMaster__new_transition_64( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__CheckNoMaster__new_transition_65( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__Ac__Initial1__RunAsSlave__2( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__En__RunAsSlave( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__end__trans__Initial1__RunAsSlave__2( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__init__trans__Initial1__RunAsSlave__2( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_12( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_13( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_14( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_15_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_16( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_17( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_18( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__Initial1__RunAsSlave__2__new_transition_19( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__KeepAliveMsg__Debug__AC__KeepAliveMsg( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__KeepAliveMsg__Debug__En__RunAsSlave( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__KeepAliveMsg__Debug__Ex__RunAsSlave( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__KeepAliveMsg__Debug__end__trans__KeepAliveMsg( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__KeepAliveMsg__Debug__init__trans__KeepAliveMsg( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_50( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_51( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_52( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_53( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_54_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_55( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_56( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_57( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_58( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__KeepAliveMsg__new_transition_59( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__NokeepAlive__Debug__AC__NokeepAlive( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__NokeepAlive__Debug__En__TryBeMaster( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__NokeepAlive__Debug__Ex__RunAsSlave( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__NokeepAlive__Debug__end__trans__NokeepAlive( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__NokeepAlive__Debug__init__trans__NokeepAlive( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__NokeepAlive__new_transition_66( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__NokeepAlive__new_transition_67( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__NokeepAlive__new_transition_68( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__NokeepAlive__new_transition_69( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__NokeepAlive__new_transition_70_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__NokeepAlive__new_transition_71( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__NokeepAlive__new_transition_72( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__NokeepAlive__new_transition_73( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__NokeepAlive__new_transition_74( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__NokeepAlive__new_transition_75( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__ReplyConfig__Debug__AC__ReplyConfig( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__ReplyConfig__Debug__Ex__TryBeMaster( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__ReplyConfig__Debug__end__trans__ReplyConfig( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__ReplyConfig__Debug__init__trans__ReplyConfig( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__ReplyConfig__new_transition_36( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__ReplyConfig__new_transition_37( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__ReplyConfig__new_transition_38( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__ReplyConfig__new_transition_39_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__ReplyConfig__new_transition_40( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__ReplyConfig__new_transition_41( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__ReplyConfig__new_transition_42( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__ReplyConfig__new_transition_43( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__backtoslave1__Debug__Ac__backtoslave1( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__backtoslave1__Debug__end__trans__backtoslave1( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__backtoslave1__Debug__init__trans__backtoslave1( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__backtoslave1__new_transition_44( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__backtoslave1__new_transition_45( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__backtoslave1__new_transition_46_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__backtoslave1__new_transition_47( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__backtoslave1__new_transition_48( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__backtoslave1__new_transition_49( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__backtoslave__Debug__Ac__backtoslave( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__backtoslave__Debug__En__RunAsSlave( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__backtoslave__Debug__end__trans__backtoslave( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__backtoslave__Debug__init__trans__backtoslave( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__backtoslave__new_transition_28( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__backtoslave__new_transition_29( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__backtoslave__new_transition_30( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__backtoslave__new_transition_31_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__backtoslave__new_transition_32( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__backtoslave__new_transition_33( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__backtoslave__new_transition_34( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__C__backtoslave__new_transition_35( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__CheckNoMaster( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__CheckNoMaster__E( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__CheckNoMaster__S( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__CheckNoMaster__dbg( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__Initial1__RunAsSlave__2__E( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__Initial1__RunAsSlave__2__S( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__Initial1__RunAsSlave__2__dbg( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__KeepAliveMsg( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__KeepAliveMsg__E( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__KeepAliveMsg__S( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__KeepAliveMsg__dbg( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__NokeepAlive( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__NokeepAlive__E( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__NokeepAlive__S( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__NokeepAlive__dbg( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__ReplyConfig( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__ReplyConfig__E( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__ReplyConfig__S( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__ReplyConfig__dbg( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__backtoslave( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__backtoslave1( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__backtoslave1__E( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__backtoslave1__S( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__backtoslave1__dbg( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__backtoslave__E( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__backtoslave__S( const UMLRTMessage * msg );
    void actionchain_____Backup__Debug__backtoslave__dbg( const UMLRTMessage * msg );
    void actionchain_____Backup__Initial1__RunAsSlave__2( const UMLRTMessage * msg );
    void actionchain_____Backup__KeepAliveMsg( const UMLRTMessage * msg );
    void actionchain_____Backup__NokeepAlive( const UMLRTMessage * msg );
    void actionchain_____Backup__ReplyConfig( const UMLRTMessage * msg );
    void actionchain_____Backup__backtoslave( const UMLRTMessage * msg );
    void actionchain_____Backup__backtoslave1( const UMLRTMessage * msg );
    void actionchain_____Backup__new_transition_1( const UMLRTMessage * msg );
    void actionchain_____Backup__new_transition_11( const UMLRTMessage * msg );
    void actionchain_____Backup__new_transition_2( const UMLRTMessage * msg );
    void actionchain_____BeSlave( const UMLRTMessage * msg );
    void actionchain_____BeingMaster( const UMLRTMessage * msg );
    void actionchain_____Debug__ActiveMode( const UMLRTMessage * msg );
    void actionchain_____Debug__ActiveMode__E( const UMLRTMessage * msg );
    void actionchain_____Debug__ActiveMode__S( const UMLRTMessage * msg );
    void actionchain_____Debug__ActiveMode__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__BeSlave( const UMLRTMessage * msg );
    void actionchain_____Debug__BeSlave__E( const UMLRTMessage * msg );
    void actionchain_____Debug__BeSlave__S( const UMLRTMessage * msg );
    void actionchain_____Debug__BeSlave__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__BeingMaster( const UMLRTMessage * msg );
    void actionchain_____Debug__BeingMaster__E( const UMLRTMessage * msg );
    void actionchain_____Debug__BeingMaster__S( const UMLRTMessage * msg );
    void actionchain_____Debug__BeingMaster__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ActiveMode__Debug__Ac__ActiveMode( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ActiveMode__Debug__end__trans__ActiveMode( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ActiveMode__Debug__init__trans__ActiveMode( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ActiveMode__new_transition_118( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ActiveMode__new_transition_119( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ActiveMode__new_transition_120_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ActiveMode__new_transition_121( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ActiveMode__new_transition_122( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ActiveMode__new_transition_123( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeSlave__Debug__Ac__BeSlave( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeSlave__Debug__En__Backup( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeSlave__Debug__end__trans__BeSlave( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeSlave__Debug__init__trans__BeSlave( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeSlave__new_transition_100( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeSlave__new_transition_101( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeSlave__new_transition_94( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeSlave__new_transition_95( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeSlave__new_transition_96( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeSlave__new_transition_97_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeSlave__new_transition_98( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeSlave__new_transition_99( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeingMaster__Debug__Ac__BeingMaster( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeingMaster__Debug__En__RunAsMaster( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeingMaster__Debug__end__trans__BeingMaster( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeingMaster__Debug__init__trans__BeingMaster( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeingMaster__new_transition_140( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeingMaster__new_transition_141( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeingMaster__new_transition_142( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeingMaster__new_transition_143_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeingMaster__new_transition_144( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeingMaster__new_transition_145( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeingMaster__new_transition_146( const UMLRTMessage * msg );
    void actionchain_____Debug__C__BeingMaster__new_transition_147( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ExitPoint1__BeMaster__4__Debug__Ac__ExitPoint1__BeMaster__4( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ExitPoint1__BeMaster__4__Debug__end__trans__ExitPoint1__BeMaster__4( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ExitPoint1__BeMaster__4__Debug__init__trans__ExitPoint1__BeMaster__4( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ExitPoint1__BeMaster__4__new_transition_124( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ExitPoint1__BeMaster__4__new_transition_125( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ExitPoint1__BeMaster__4__new_transition_126_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ExitPoint1__BeMaster__4__new_transition_127( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ExitPoint1__BeMaster__4__new_transition_128( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ExitPoint1__BeMaster__4__new_transition_129( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__StandBy__3__Debug__Ac__Init__StandBy__3( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__StandBy__3__Debug__En__StandBy( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__StandBy__3__Debug__end__trans__Init__StandBy__3( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__StandBy__3__Debug__init__trans__Init__StandBy__3( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__StandBy__3__new_transition_102( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__StandBy__3__new_transition_103( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__StandBy__3__new_transition_104( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__StandBy__3__new_transition_105_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__StandBy__3__new_transition_106( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__StandBy__3__new_transition_107( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__StandBy__3__new_transition_108( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Init__StandBy__3__new_transition_109( const UMLRTMessage * msg );
    void actionchain_____Debug__C__KeepAlive__Debug__AC__KeepAlive( const UMLRTMessage * msg );
    void actionchain_____Debug__C__KeepAlive__Debug__En__RunAsMaster( const UMLRTMessage * msg );
    void actionchain_____Debug__C__KeepAlive__Debug__Ex__RunAsMaster( const UMLRTMessage * msg );
    void actionchain_____Debug__C__KeepAlive__Debug__end__trans__KeepAlive( const UMLRTMessage * msg );
    void actionchain_____Debug__C__KeepAlive__Debug__init__trans__KeepAlive( const UMLRTMessage * msg );
    void actionchain_____Debug__C__KeepAlive__new_transition_130( const UMLRTMessage * msg );
    void actionchain_____Debug__C__KeepAlive__new_transition_131( const UMLRTMessage * msg );
    void actionchain_____Debug__C__KeepAlive__new_transition_132( const UMLRTMessage * msg );
    void actionchain_____Debug__C__KeepAlive__new_transition_133( const UMLRTMessage * msg );
    void actionchain_____Debug__C__KeepAlive__new_transition_134_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__KeepAlive__new_transition_135( const UMLRTMessage * msg );
    void actionchain_____Debug__C__KeepAlive__new_transition_136( const UMLRTMessage * msg );
    void actionchain_____Debug__C__KeepAlive__new_transition_137( const UMLRTMessage * msg );
    void actionchain_____Debug__C__KeepAlive__new_transition_138( const UMLRTMessage * msg );
    void actionchain_____Debug__C__KeepAlive__new_transition_139( const UMLRTMessage * msg );
    void actionchain_____Debug__C__PassiveMode__Debug__Ac__PassiveMode( const UMLRTMessage * msg );
    void actionchain_____Debug__C__PassiveMode__Debug__En__Backup( const UMLRTMessage * msg );
    void actionchain_____Debug__C__PassiveMode__Debug__end__trans__PassiveMode( const UMLRTMessage * msg );
    void actionchain_____Debug__C__PassiveMode__Debug__init__trans__PassiveMode( const UMLRTMessage * msg );
    void actionchain_____Debug__C__PassiveMode__new_transition_166( const UMLRTMessage * msg );
    void actionchain_____Debug__C__PassiveMode__new_transition_167( const UMLRTMessage * msg );
    void actionchain_____Debug__C__PassiveMode__new_transition_168( const UMLRTMessage * msg );
    void actionchain_____Debug__C__PassiveMode__new_transition_169_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__PassiveMode__new_transition_170( const UMLRTMessage * msg );
    void actionchain_____Debug__C__PassiveMode__new_transition_171( const UMLRTMessage * msg );
    void actionchain_____Debug__C__PassiveMode__new_transition_172( const UMLRTMessage * msg );
    void actionchain_____Debug__C__PassiveMode__new_transition_173( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Recover__Debug__AC__Recover( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Recover__Debug__Ex__Failure( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Recover__Debug__end__trans__Recover( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Recover__Debug__init__trans__Recover( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Recover__new_transition_110( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Recover__new_transition_111( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Recover__new_transition_112( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Recover__new_transition_113_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Recover__new_transition_114( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Recover__new_transition_115( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Recover__new_transition_116( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Recover__new_transition_117( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServerFaliure__Debug__AC__ServerFaliure( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServerFaliure__Debug__En__Failure( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServerFaliure__Debug__Ex__RunAsMaster( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServerFaliure__Debug__end__trans__ServerFaliure( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServerFaliure__Debug__init__trans__ServerFaliure( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServerFaliure__new_transition_84( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServerFaliure__new_transition_85( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServerFaliure__new_transition_86( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServerFaliure__new_transition_87( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServerFaliure__new_transition_88_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServerFaliure__new_transition_89( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServerFaliure__new_transition_90( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServerFaliure__new_transition_91( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServerFaliure__new_transition_92( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServerFaliure__new_transition_93( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StandBy__CheckConfig__5__Debug__AC__StandBy__CheckConfig__5( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StandBy__CheckConfig__5__Debug__Ex__StandBy( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StandBy__CheckConfig__5__Debug__end__trans__StandBy__CheckConfig__5( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StandBy__CheckConfig__5__Debug__init__trans__StandBy__CheckConfig__5( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_158( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_159( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_160( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_161_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_162( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_163( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_164( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StandBy__CheckConfig__5__new_transition_165( const UMLRTMessage * msg );
    void actionchain_____Debug__C__initTimer__Debug__Ac__initTimer( const UMLRTMessage * msg );
    void actionchain_____Debug__C__initTimer__Debug__En__RunAsMaster( const UMLRTMessage * msg );
    void actionchain_____Debug__C__initTimer__Debug__end__trans__initTimer( const UMLRTMessage * msg );
    void actionchain_____Debug__C__initTimer__Debug__init__trans__initTimer( const UMLRTMessage * msg );
    void actionchain_____Debug__C__initTimer__new_transition_76( const UMLRTMessage * msg );
    void actionchain_____Debug__C__initTimer__new_transition_77( const UMLRTMessage * msg );
    void actionchain_____Debug__C__initTimer__new_transition_78( const UMLRTMessage * msg );
    void actionchain_____Debug__C__initTimer__new_transition_79_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__initTimer__new_transition_80( const UMLRTMessage * msg );
    void actionchain_____Debug__C__initTimer__new_transition_81( const UMLRTMessage * msg );
    void actionchain_____Debug__C__initTimer__new_transition_82( const UMLRTMessage * msg );
    void actionchain_____Debug__C__initTimer__new_transition_83( const UMLRTMessage * msg );
    void actionchain_____Debug__C__purgeotherMessage__Debug__AC__purgeotherMessage( const UMLRTMessage * msg );
    void actionchain_____Debug__C__purgeotherMessage__Debug__En__Failure( const UMLRTMessage * msg );
    void actionchain_____Debug__C__purgeotherMessage__Debug__Ex__Failure( const UMLRTMessage * msg );
    void actionchain_____Debug__C__purgeotherMessage__Debug__end__trans__purgeotherMessage( const UMLRTMessage * msg );
    void actionchain_____Debug__C__purgeotherMessage__Debug__init__trans__purgeotherMessage( const UMLRTMessage * msg );
    void actionchain_____Debug__C__purgeotherMessage__new_transition_148( const UMLRTMessage * msg );
    void actionchain_____Debug__C__purgeotherMessage__new_transition_149( const UMLRTMessage * msg );
    void actionchain_____Debug__C__purgeotherMessage__new_transition_150( const UMLRTMessage * msg );
    void actionchain_____Debug__C__purgeotherMessage__new_transition_151( const UMLRTMessage * msg );
    void actionchain_____Debug__C__purgeotherMessage__new_transition_152_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__purgeotherMessage__new_transition_153( const UMLRTMessage * msg );
    void actionchain_____Debug__C__purgeotherMessage__new_transition_154( const UMLRTMessage * msg );
    void actionchain_____Debug__C__purgeotherMessage__new_transition_155( const UMLRTMessage * msg );
    void actionchain_____Debug__C__purgeotherMessage__new_transition_156( const UMLRTMessage * msg );
    void actionchain_____Debug__C__purgeotherMessage__new_transition_157( const UMLRTMessage * msg );
    void actionchain_____Debug__ExitPoint1__BeMaster__4( const UMLRTMessage * msg );
    void actionchain_____Debug__ExitPoint1__BeMaster__4__E( const UMLRTMessage * msg );
    void actionchain_____Debug__ExitPoint1__BeMaster__4__S( const UMLRTMessage * msg );
    void actionchain_____Debug__ExitPoint1__BeMaster__4__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__InitDebug( const UMLRTMessage * msg );
    void actionchain_____Debug__Init__StandBy__3( const UMLRTMessage * msg );
    void actionchain_____Debug__Init__StandBy__3__E( const UMLRTMessage * msg );
    void actionchain_____Debug__Init__StandBy__3__S( const UMLRTMessage * msg );
    void actionchain_____Debug__Init__StandBy__3__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__KeepAlive( const UMLRTMessage * msg );
    void actionchain_____Debug__KeepAlive__E( const UMLRTMessage * msg );
    void actionchain_____Debug__KeepAlive__S( const UMLRTMessage * msg );
    void actionchain_____Debug__KeepAlive__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__MasterAnnounce( const UMLRTMessage * msg );
    void actionchain_____Debug__MasterAnnounce__E( const UMLRTMessage * msg );
    void actionchain_____Debug__MasterAnnounce__S( const UMLRTMessage * msg );
    void actionchain_____Debug__MasterAnnounce__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__PassiveMode( const UMLRTMessage * msg );
    void actionchain_____Debug__PassiveMode__E( const UMLRTMessage * msg );
    void actionchain_____Debug__PassiveMode__S( const UMLRTMessage * msg );
    void actionchain_____Debug__PassiveMode__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__Recover( const UMLRTMessage * msg );
    void actionchain_____Debug__Recover__E( const UMLRTMessage * msg );
    void actionchain_____Debug__Recover__S( const UMLRTMessage * msg );
    void actionchain_____Debug__Recover__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__ServerFaliure( const UMLRTMessage * msg );
    void actionchain_____Debug__ServerFaliure__E( const UMLRTMessage * msg );
    void actionchain_____Debug__ServerFaliure__S( const UMLRTMessage * msg );
    void actionchain_____Debug__ServerFaliure__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__ServiceRequest( const UMLRTMessage * msg );
    void actionchain_____Debug__ServiceRequest__E( const UMLRTMessage * msg );
    void actionchain_____Debug__ServiceRequest__S( const UMLRTMessage * msg );
    void actionchain_____Debug__ServiceRequest__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__StandBy__CheckConfig__5( const UMLRTMessage * msg );
    void actionchain_____Debug__StandBy__CheckConfig__5__E( const UMLRTMessage * msg );
    void actionchain_____Debug__StandBy__CheckConfig__5__S( const UMLRTMessage * msg );
    void actionchain_____Debug__StandBy__CheckConfig__5__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__initTimer( const UMLRTMessage * msg );
    void actionchain_____Debug__initTimer__E( const UMLRTMessage * msg );
    void actionchain_____Debug__initTimer__S( const UMLRTMessage * msg );
    void actionchain_____Debug__initTimer__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__purgeotherMessage( const UMLRTMessage * msg );
    void actionchain_____Debug__purgeotherMessage__E( const UMLRTMessage * msg );
    void actionchain_____Debug__purgeotherMessage__S( const UMLRTMessage * msg );
    void actionchain_____Debug__purgeotherMessage__dbg( const UMLRTMessage * msg );
    void actionchain_____ExitPoint1__BeMaster__4( const UMLRTMessage * msg );
    void actionchain_____Init__StandBy__3( const UMLRTMessage * msg );
    void actionchain_____KeepAlive( const UMLRTMessage * msg );
    void actionchain_____MasterAnnounce( const UMLRTMessage * msg );
    void actionchain_____PassiveMode( const UMLRTMessage * msg );
    void actionchain_____Recover( const UMLRTMessage * msg );
    void actionchain_____ServerFaliure( const UMLRTMessage * msg );
    void actionchain_____ServiceRequest( const UMLRTMessage * msg );
    void actionchain_____StandBy__CheckConfig__5( const UMLRTMessage * msg );
    void actionchain_____initTimer( const UMLRTMessage * msg );
    void actionchain_____purgeotherMessage( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__BackToSlave__en( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__BackToSlave__ex( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__BackToSlave__new_exitpoint_2( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__CheckNoMaster__en( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__CheckNoMaster__ex( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__CheckNoMaster__new_exitpoint_7( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__Initial1__RunAsSlave__2__en( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__Initial1__RunAsSlave__2__ex( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__Initial1__RunAsSlave__2__new_exitpoint_1( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__KeepAliveMsg__en( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__KeepAliveMsg__ex( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__KeepAliveMsg__new_exitpoint_6( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__NokeepAlive__en( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__NokeepAlive__ex( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__NokeepAlive__new_exitpoint_8( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__ReplyConfig__en( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__ReplyConfig__ex( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__ReplyConfig__new_exitpoint_4( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__backtoslave1__en( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__backtoslave1__ex( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__backtoslave1__new_exitpoint_5( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__backtoslave__en( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__backtoslave__ex( const UMLRTMessage * msg );
    State junction_____Backup__Debug__C__backtoslave__new_exitpoint_3( const UMLRTMessage * msg );
    State junction_____Backup__ExitPoint1( const UMLRTMessage * msg );
    State junction_____Backup__Slave( const UMLRTMessage * msg );
    State junction_____BeMaster( const UMLRTMessage * msg );
    State junction_____Debug__C__ActiveMode__en( const UMLRTMessage * msg );
    State junction_____Debug__C__ActiveMode__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__ActiveMode__new_exitpoint_14( const UMLRTMessage * msg );
    State junction_____Debug__C__BeSlave__en( const UMLRTMessage * msg );
    State junction_____Debug__C__BeSlave__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__BeSlave__new_exitpoint_11( const UMLRTMessage * msg );
    State junction_____Debug__C__BeingMaster__en( const UMLRTMessage * msg );
    State junction_____Debug__C__BeingMaster__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__BeingMaster__new_exitpoint_17( const UMLRTMessage * msg );
    State junction_____Debug__C__ExitPoint1__BeMaster__4__en( const UMLRTMessage * msg );
    State junction_____Debug__C__ExitPoint1__BeMaster__4__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__ExitPoint1__BeMaster__4__new_exitpoint_15( const UMLRTMessage * msg );
    State junction_____Debug__C__Init__StandBy__3__en( const UMLRTMessage * msg );
    State junction_____Debug__C__Init__StandBy__3__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__Init__StandBy__3__new_exitpoint_12( const UMLRTMessage * msg );
    State junction_____Debug__C__KeepAlive__en( const UMLRTMessage * msg );
    State junction_____Debug__C__KeepAlive__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__KeepAlive__new_exitpoint_16( const UMLRTMessage * msg );
    State junction_____Debug__C__PassiveMode__en( const UMLRTMessage * msg );
    State junction_____Debug__C__PassiveMode__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__PassiveMode__new_exitpoint_20( const UMLRTMessage * msg );
    State junction_____Debug__C__Recover__en( const UMLRTMessage * msg );
    State junction_____Debug__C__Recover__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__Recover__new_exitpoint_13( const UMLRTMessage * msg );
    State junction_____Debug__C__ServerFaliure__en( const UMLRTMessage * msg );
    State junction_____Debug__C__ServerFaliure__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__ServerFaliure__new_exitpoint_10( const UMLRTMessage * msg );
    State junction_____Debug__C__StandBy__CheckConfig__5__en( const UMLRTMessage * msg );
    State junction_____Debug__C__StandBy__CheckConfig__5__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__StandBy__CheckConfig__5__new_exitpoint_19( const UMLRTMessage * msg );
    State junction_____Debug__C__initTimer__en( const UMLRTMessage * msg );
    State junction_____Debug__C__initTimer__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__initTimer__new_exitpoint_9( const UMLRTMessage * msg );
    State junction_____Debug__C__purgeotherMessage__en( const UMLRTMessage * msg );
    State junction_____Debug__C__purgeotherMessage__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__purgeotherMessage__new_exitpoint_18( const UMLRTMessage * msg );
    State choice_____Backup__Choice2( const UMLRTMessage * msg );
    State choice_____Backup__Debug__C__BackToSlave__deephistory( const UMLRTMessage * msg );
    State choice_____Backup__Debug__C__CheckNoMaster__deephistory( const UMLRTMessage * msg );
    State choice_____Backup__Debug__C__Initial1__RunAsSlave__2__deephistory( const UMLRTMessage * msg );
    State choice_____Backup__Debug__C__KeepAliveMsg__deephistory( const UMLRTMessage * msg );
    State choice_____Backup__Debug__C__NokeepAlive__deephistory( const UMLRTMessage * msg );
    State choice_____Backup__Debug__C__ReplyConfig__deephistory( const UMLRTMessage * msg );
    State choice_____Backup__Debug__C__backtoslave1__deephistory( const UMLRTMessage * msg );
    State choice_____Backup__Debug__C__backtoslave__deephistory( const UMLRTMessage * msg );
    State choice_____Backup__Debug__Path__BackToSlave( const UMLRTMessage * msg );
    State choice_____Backup__Debug__Path__CheckNoMaster( const UMLRTMessage * msg );
    State choice_____Backup__Debug__Path__Initial1__RunAsSlave__2( const UMLRTMessage * msg );
    State choice_____Backup__Debug__Path__KeepAliveMsg( const UMLRTMessage * msg );
    State choice_____Backup__Debug__Path__NokeepAlive( const UMLRTMessage * msg );
    State choice_____Backup__Debug__Path__ReplyConfig( const UMLRTMessage * msg );
    State choice_____Backup__Debug__Path__backtoslave( const UMLRTMessage * msg );
    State choice_____Backup__Debug__Path__backtoslave1( const UMLRTMessage * msg );
    State choice_____Backup__deephistory( const UMLRTMessage * msg );
    State choice_____CheckConfig( const UMLRTMessage * msg );
    State choice_____Choice1( const UMLRTMessage * msg );
    State choice_____Debug__C__ActiveMode__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__BeSlave__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__BeingMaster__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__ExitPoint1__BeMaster__4__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__Init__StandBy__3__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__KeepAlive__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__PassiveMode__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__Recover__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__ServerFaliure__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__StandBy__CheckConfig__5__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__initTimer__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__purgeotherMessage__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__Path__ActiveMode( const UMLRTMessage * msg );
    State choice_____Debug__Path__BeSlave( const UMLRTMessage * msg );
    State choice_____Debug__Path__BeingMaster( const UMLRTMessage * msg );
    State choice_____Debug__Path__ExitPoint1__BeMaster__4( const UMLRTMessage * msg );
    State choice_____Debug__Path__Init__StandBy__3( const UMLRTMessage * msg );
    State choice_____Debug__Path__KeepAlive( const UMLRTMessage * msg );
    State choice_____Debug__Path__MasterAnnounce( const UMLRTMessage * msg );
    State choice_____Debug__Path__PassiveMode( const UMLRTMessage * msg );
    State choice_____Debug__Path__Recover( const UMLRTMessage * msg );
    State choice_____Debug__Path__ServerFaliure( const UMLRTMessage * msg );
    State choice_____Debug__Path__ServiceRequest( const UMLRTMessage * msg );
    State choice_____Debug__Path__StandBy__CheckConfig__5( const UMLRTMessage * msg );
    State choice_____Debug__Path__initTimer( const UMLRTMessage * msg );
    State choice_____Debug__Path__purgeotherMessage( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__BackToSlave__Debug__A__Ac__BackToSlave( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__BackToSlave__Debug__B__Ac__BackToSlave( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__BackToSlave__Debug__B__Ex__TryBeMaster( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__BackToSlave__boundary( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__CheckNoMaster__Debug__A__Ac__CheckNoMaster( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__CheckNoMaster__Debug__B__Ac__CheckNoMaster( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__CheckNoMaster__boundary( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__Ac__Initial1__RunAsSlave__2( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__A__En__Initial1__RunAsSlave__2( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__Initial1__RunAsSlave__2__Debug__B__Ac__Initial1__RunAsSlave__2( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__Initial1__RunAsSlave__2__boundary( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__KeepAliveMsg__Debug__A__Ac__KeepAliveMsg( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__KeepAliveMsg__Debug__A__En__RunAsSlave( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__KeepAliveMsg__Debug__B__Ac__KeepAliveMsg( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__KeepAliveMsg__Debug__B__Ex__RunAsSlave( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__KeepAliveMsg__boundary( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__NokeepAlive__Debug__A__Ac__NokeepAlive( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__NokeepAlive__Debug__A__En__TryBeMaster( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__NokeepAlive__Debug__B__Ac__NokeepAlive( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__NokeepAlive__Debug__B__Ex__RunAsSlave( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__NokeepAlive__boundary( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__ReplyConfig__Debug__A__Ac__ReplyConfig( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__ReplyConfig__Debug__B__Ac__ReplyConfig( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__ReplyConfig__Debug__B__Ex__TryBeMaster( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__ReplyConfig__boundary( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__backtoslave1__Debug__A__Ac__backtoslave1( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__backtoslave1__Debug__B__Ac__backtoslave1( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__backtoslave1__boundary( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__backtoslave__Debug__A__Ac__backtoslave( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__backtoslave__Debug__A__En__backtoslave( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__backtoslave__Debug__B__Ac__backtoslave( const UMLRTMessage * msg );
    State state_____Backup__Debug__C__backtoslave__boundary( const UMLRTMessage * msg );
    State state_____Backup__RunAsSlave( const UMLRTMessage * msg );
    State state_____Backup__TryBeMaster( const UMLRTMessage * msg );
    State state_____Debug__C__ActiveMode__Debug__A__Ac__ActiveMode( const UMLRTMessage * msg );
    State state_____Debug__C__ActiveMode__Debug__B__Ac__ActiveMode( const UMLRTMessage * msg );
    State state_____Debug__C__ActiveMode__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__BeSlave__Debug__A__Ac__BeSlave( const UMLRTMessage * msg );
    State state_____Debug__C__BeSlave__Debug__A__En__BeSlave( const UMLRTMessage * msg );
    State state_____Debug__C__BeSlave__Debug__B__Ac__BeSlave( const UMLRTMessage * msg );
    State state_____Debug__C__BeSlave__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__BeingMaster__Debug__A__Ac__BeingMaster( const UMLRTMessage * msg );
    State state_____Debug__C__BeingMaster__Debug__A__En__BeingMaster( const UMLRTMessage * msg );
    State state_____Debug__C__BeingMaster__Debug__B__Ac__BeingMaster( const UMLRTMessage * msg );
    State state_____Debug__C__BeingMaster__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__ExitPoint1__BeMaster__4__Debug__A__Ac__ExitPoint1__BeMaster__4( const UMLRTMessage * msg );
    State state_____Debug__C__ExitPoint1__BeMaster__4__Debug__B__Ac__ExitPoint1__BeMaster__4( const UMLRTMessage * msg );
    State state_____Debug__C__ExitPoint1__BeMaster__4__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__Init__StandBy__3__Debug__A__Ac__Init__StandBy__3( const UMLRTMessage * msg );
    State state_____Debug__C__Init__StandBy__3__Debug__A__En__Init__StandBy__3( const UMLRTMessage * msg );
    State state_____Debug__C__Init__StandBy__3__Debug__B__Ac__Init__StandBy__3( const UMLRTMessage * msg );
    State state_____Debug__C__Init__StandBy__3__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__KeepAlive__Debug__A__Ac__KeepAlive( const UMLRTMessage * msg );
    State state_____Debug__C__KeepAlive__Debug__A__En__RunAsMaster( const UMLRTMessage * msg );
    State state_____Debug__C__KeepAlive__Debug__B__Ac__KeepAlive( const UMLRTMessage * msg );
    State state_____Debug__C__KeepAlive__Debug__B__Ex__RunAsMaster( const UMLRTMessage * msg );
    State state_____Debug__C__KeepAlive__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__MasterAnnounce( const UMLRTMessage * msg );
    State state_____Debug__C__PassiveMode__Debug__A__Ac__PassiveMode( const UMLRTMessage * msg );
    State state_____Debug__C__PassiveMode__Debug__A__En__PassiveMode( const UMLRTMessage * msg );
    State state_____Debug__C__PassiveMode__Debug__B__Ac__PassiveMode( const UMLRTMessage * msg );
    State state_____Debug__C__PassiveMode__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__Recover__Debug__A__Ac__Recover( const UMLRTMessage * msg );
    State state_____Debug__C__Recover__Debug__B__Ac__Recover( const UMLRTMessage * msg );
    State state_____Debug__C__Recover__Debug__B__Ex__Failure( const UMLRTMessage * msg );
    State state_____Debug__C__Recover__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__ServerFaliure__Debug__A__Ac__ServerFaliure( const UMLRTMessage * msg );
    State state_____Debug__C__ServerFaliure__Debug__A__En__Failure( const UMLRTMessage * msg );
    State state_____Debug__C__ServerFaliure__Debug__B__Ac__ServerFaliure( const UMLRTMessage * msg );
    State state_____Debug__C__ServerFaliure__Debug__B__Ex__RunAsMaster( const UMLRTMessage * msg );
    State state_____Debug__C__ServerFaliure__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__ServiceRequest( const UMLRTMessage * msg );
    State state_____Debug__C__StandBy__CheckConfig__5__Debug__A__Ac__StandBy__CheckConfig__5( const UMLRTMessage * msg );
    State state_____Debug__C__StandBy__CheckConfig__5__Debug__B__Ac__StandBy__CheckConfig__5( const UMLRTMessage * msg );
    State state_____Debug__C__StandBy__CheckConfig__5__Debug__B__Ex__StandBy( const UMLRTMessage * msg );
    State state_____Debug__C__StandBy__CheckConfig__5__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__initTimer__Debug__A__Ac__initTimer( const UMLRTMessage * msg );
    State state_____Debug__C__initTimer__Debug__A__En__initTimer( const UMLRTMessage * msg );
    State state_____Debug__C__initTimer__Debug__B__Ac__initTimer( const UMLRTMessage * msg );
    State state_____Debug__C__initTimer__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__purgeotherMessage__Debug__A__Ac__purgeotherMessage( const UMLRTMessage * msg );
    State state_____Debug__C__purgeotherMessage__Debug__A__En__Failure( const UMLRTMessage * msg );
    State state_____Debug__C__purgeotherMessage__Debug__B__Ac__purgeotherMessage( const UMLRTMessage * msg );
    State state_____Debug__C__purgeotherMessage__Debug__B__Ex__Failure( const UMLRTMessage * msg );
    State state_____Debug__C__purgeotherMessage__boundary( const UMLRTMessage * msg );
    State state_____Debug__InitState( const UMLRTMessage * msg );
    State state_____Failure( const UMLRTMessage * msg );
    State state_____RunAsMaster( const UMLRTMessage * msg );
    State state_____StandBy( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass Server;

#endif

