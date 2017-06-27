
#ifndef CONFIGPROTOCOL_HH
#define CONFIGPROTOCOL_HH

#include "SystemConfig.hh"
#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace ConfigProtocol
{
    class Base : public UMLRTProtocol
    {
    public:
        Base( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal IAMMaster( char * MasterName ) const;
        UMLRTOutSignal QueryConfig() const;
        UMLRTOutSignal QueryMasterId() const;
        UMLRTOutSignal QueryReplicationMode() const;
        UMLRTOutSignal QueryServerRole( char * ServerName ) const;
    };
    class Conj : public UMLRTProtocol
    {
    public:
        Conj( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal BIT() const;
        UMLRTOutSignal ReplyConfig( const SystemConfig & config ) const;
        UMLRTOutSignal ReplyMasterId( int MasterId ) const;
        UMLRTOutSignal ReplyReplicationMode( int RunningMode ) const;
        UMLRTOutSignal ReplyServerRole( int ServerRole ) const;
        UMLRTOutSignal Shutdown() const;
        UMLRTOutSignal StartUp( const SystemConfig & config ) const;
    };
    enum SignalId
    {
        signal_BIT = UMLRTSignal::FIRST_PROTOCOL_SIGNAL_ID,
        signal_ReplyConfig,
        signal_ReplyMasterId,
        signal_ReplyReplicationMode,
        signal_ReplyServerRole,
        signal_Shutdown,
        signal_StartUp,
        signal_IAMMaster,
        signal_QueryConfig,
        signal_QueryMasterId,
        signal_QueryReplicationMode,
        signal_QueryServerRole
    };
};

#endif

