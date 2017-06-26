
#ifndef ENGINE_HH
#define ENGINE_HH

#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace Engine
{
    class Base : public UMLRTProtocol
    {
    public:
        Base( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal moveBackwards() const;
        UMLRTOutSignal moveForward() const;
        UMLRTOutSignal stop() const;
        UMLRTOutSignal turnLeft( int angle ) const;
        UMLRTOutSignal turnRight( int angle ) const;
    };
    class Conj : public UMLRTProtocol
    {
    public:
        Conj( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal stopped() const;
        UMLRTOutSignal turnedLeft() const;
        UMLRTOutSignal turnedRight() const;
    };
    enum SignalId
    {
        signal_stopped = UMLRTSignal::FIRST_PROTOCOL_SIGNAL_ID,
        signal_turnedLeft,
        signal_turnedRight,
        signal_moveBackwards,
        signal_moveForward,
        signal_stop,
        signal_turnLeft,
        signal_turnRight
    };
};

#endif

