
#ifndef TEMPERATURESENSOR_HH
#define TEMPERATURESENSOR_HH

#include "Temperature.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

class Capsule_TemperatureSensor : public UMLRTCapsule
{
public:
    Capsule_TemperatureSensor( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    Temperature::Conj temperature;
public:
    enum BorderPortId
    {
        borderport_temperature
    };
    enum PartId
    {
    };
    enum PortId
    {
        port_temperature
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    virtual void initialize( const UMLRTMessage & msg );
    virtual void inject( const UMLRTMessage & msg );
};
extern const UMLRTCapsuleClass TemperatureSensor;

#endif

