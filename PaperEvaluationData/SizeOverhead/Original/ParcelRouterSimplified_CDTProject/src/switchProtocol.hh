
#ifndef SWITCHPROTOCOL_HH
#define SWITCHPROTOCOL_HH

#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace switchProtocol
{
    class Conj : public UMLRTProtocol
    {
    public:
        Conj( const UMLRTCommsPort * & srcPort );
    };
    enum SignalId
    {
        signal_setSwitch = UMLRTSignal::FIRST_PROTOCOL_SIGNAL_ID
    };
    class Base : public UMLRTProtocol
    {
    public:
        Base( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal setSwitch( int c ) const;
    };
};

#endif

