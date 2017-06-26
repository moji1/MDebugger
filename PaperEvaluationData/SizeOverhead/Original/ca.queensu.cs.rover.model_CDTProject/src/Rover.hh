
#ifndef ROVER_HH
#define ROVER_HH

#include "Detection.hh"
#include "Engine.hh"
#include "Temperature.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
struct UMLRTCapsulePart;
struct UMLRTCommsPort;
struct UMLRTSlot;

class Capsule_Rover : public UMLRTCapsule
{
public:
    Capsule_Rover( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    Detection::Conj detection;
public:
    enum BorderPortId
    {
        borderport_detection,
        borderport_engine,
        borderport_temperature
    };
protected:
    Engine::Conj engine;
    Temperature::Conj temperature;
public:
    enum PartId
    {
        part_detectionSensor,
        part_detectionSensor2,
        part_engineController,
        part_temperatureSensor
    };
protected:
    const UMLRTCapsulePart * const detectionSensor;
    const UMLRTCapsulePart * const detectionSensor2;
    const UMLRTCapsulePart * const engineController;
    const UMLRTCapsulePart * const temperatureSensor;
public:
    enum PortId
    {
        port_detection,
        port_engine,
        port_temperature
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    virtual void initialize( const UMLRTMessage & msg );
    virtual void inject( const UMLRTMessage & msg );
};
extern const UMLRTCapsuleClass Rover;

#endif

