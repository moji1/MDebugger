
#ifndef LOCKING_HH
#define LOCKING_HH

#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace Locking
{
    class Base : public UMLRTProtocol
    {
    public:
        Base( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal lockStatus( bool locked ) const;
    };
    class Conj : public UMLRTProtocol
    {
    public:
        Conj( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal lock() const;
        UMLRTOutSignal unlock() const;
    };
    enum SignalId
    {
        signal_lock = UMLRTSignal::FIRST_PROTOCOL_SIGNAL_ID,
        signal_unlock,
        signal_lockStatus
    };
};

#endif

