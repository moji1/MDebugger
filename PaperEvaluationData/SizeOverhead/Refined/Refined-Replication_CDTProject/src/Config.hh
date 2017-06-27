
#ifndef CONFIG_HH
#define CONFIG_HH

#include "Configuration.hh"
#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace Config
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
        UMLRTOutSignal ReplyConfig( const Configuration & config ) const;
        UMLRTOutSignal ReplyMasterId( int MasterId ) const;
        UMLRTOutSignal ReplyReplicationMode( int RunningMode ) const;
        UMLRTOutSignal ReplyServerRole( int ServerRole ) const;
        UMLRTOutSignal Shutdown() const;
        UMLRTOutSignal StartUp( const Configuration & config ) const;
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

