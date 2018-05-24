
#ifndef STARTPROTOCOL_HH
#define STARTPROTOCOL_HH

#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace StartProtocol
{
    class Conj : public UMLRTProtocol
    {
    public:
        Conj( const UMLRTCommsPort * & srcPort );
    };
    enum SignalId
    {
        signal_start = UMLRTSignal::FIRST_PROTOCOL_SIGNAL_ID
    };
    class Base : public UMLRTProtocol
    {
    public:
        Base( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal start() const;
    };
};

#endif

