
#ifndef EXTINTERFACE_HH
#define EXTINTERFACE_HH

#include "COMMANDS.hh"
#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace ExtInterface
{
    class Conj : public UMLRTProtocol
    {
    public:
        Conj( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal event( char * eventInfo ) const;
        UMLRTOutSignal registerToControl( char * capsuleInstanceName ) const;
        UMLRTOutSignal selfExec() const;
    };
    enum SignalId
    {
        signal_event = UMLRTSignal::FIRST_PROTOCOL_SIGNAL_ID,
        signal_registerToControl,
        signal_selfExec,
        signal_dbgCommand,
        signal_dbgExec,
        signal_dbgRemBreakPoint,
        signal_dbgSetBreakPoint,
        signal_dbgSetExecMode,
        signal_dbgVarChange,
        signal_dbgViewBreakPoints
    };
    class Base : public UMLRTProtocol
    {
    public:
        Base( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal dbgCommand( const COMMANDS & data ) const;
        UMLRTOutSignal dbgExec() const;
        UMLRTOutSignal dbgRemBreakPoint( char * location, int breakPointType, int place ) const;
        UMLRTOutSignal dbgSetBreakPoint( char * location, int breakPointType, int place ) const;
        UMLRTOutSignal dbgSetExecMode( int execMode ) const;
        UMLRTOutSignal dbgVarChange( char * varName, char * varValue ) const;
        UMLRTOutSignal dbgViewBreakPoints() const;
    };
};

#endif

