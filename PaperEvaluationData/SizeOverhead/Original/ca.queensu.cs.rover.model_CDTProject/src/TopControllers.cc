
#include "TopControllers.hh"

#include "ControlSoftware.hh"
#include "DetectionSensor.hh"
#include "EngineController.hh"
#include "Rover.hh"
#include "TemperatureSensor.hh"
#include "Top.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcapsulepart.hh"
#include "umlrtcommsport.hh"
#include "umlrtcommsportfarend.hh"
#include "umlrtcontroller.hh"
#include "umlrtslot.hh"
#include <cstddef>


static UMLRTController DefaultController_( "DefaultController" );

UMLRTController * DefaultController = &DefaultController_;

static Capsule_Top top( &Top, &Top_slots[InstId_Top], NULL, NULL, true );

static UMLRTSlot * slots_Top[] = 
{
    &Top_slots[InstId_Top_controlSoftware],
    &Top_slots[InstId_Top_rover]
};

static UMLRTCapsulePart parts_Top[] = 
{
    {
        &Top,
        Capsule_Top::part_controlSoftware,
        1,
        &slots_Top[0]
    },
    {
        &Top,
        Capsule_Top::part_rover,
        1,
        &slots_Top[1]
    }
};

static UMLRTCommsPortFarEnd borderfarEndList_Top_controlSoftware[] = 
{
    {
        0,
        &borderports_Top_rover_detectionSensor2[Capsule_DetectionSensor::borderport_detection]
    },
    {
        0,
        &borderports_Top_rover_engineController[Capsule_EngineController::borderport_engine]
    },
    {
        0,
        NULL
    },
    {
        0,
        &borderports_Top_rover[Capsule_Rover::borderport_temperature]
    },
    {
        0,
        NULL
    }
};

UMLRTCommsPort borderports_Top_controlSoftware[] = 
{
    {
        &ControlSoftware,
        Capsule_ControlSoftware::borderport_detection,
        &Top_slots[InstId_Top_controlSoftware],
        1,
        borderfarEndList_Top_controlSoftware,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    },
    {
        &ControlSoftware,
        Capsule_ControlSoftware::borderport_engine,
        &Top_slots[InstId_Top_controlSoftware],
        1,
        &borderfarEndList_Top_controlSoftware[1],
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    },
    {
        &ControlSoftware,
        Capsule_ControlSoftware::borderport_temperature,
        &Top_slots[InstId_Top_controlSoftware],
        1,
        &borderfarEndList_Top_controlSoftware[3],
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    },
    {
        &ControlSoftware,
        Capsule_ControlSoftware::borderport_timer,
        &Top_slots[InstId_Top_controlSoftware],
        1,
        &borderfarEndList_Top_controlSoftware[4],
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    },
    {
        &ControlSoftware,
        Capsule_ControlSoftware::borderport_log,
        &Top_slots[InstId_Top_controlSoftware],
        1,
        &borderfarEndList_Top_controlSoftware[2],
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_Top_controlSoftware_ptrs[] = 
{
    &borderports_Top_controlSoftware[0],
    &borderports_Top_controlSoftware[1],
    &borderports_Top_controlSoftware[2],
    &borderports_Top_controlSoftware[3],
    &borderports_Top_controlSoftware[4]
};

static Capsule_ControlSoftware top_controlSoftware( &ControlSoftware, &Top_slots[InstId_Top_controlSoftware], borderports_Top_controlSoftware_ptrs, NULL, true );

static UMLRTCommsPortFarEnd borderfarEndList_Top_rover[] = 
{
    {
        0,
        NULL
    },
    {
        0,
        NULL
    },
    {
        0,
        &borderports_Top_controlSoftware[Capsule_ControlSoftware::borderport_temperature]
    }
};

UMLRTCommsPort borderports_Top_rover[] = 
{
    {
        &Rover,
        Capsule_Rover::borderport_detection,
        &Top_slots[InstId_Top_rover],
        1,
        borderfarEndList_Top_rover,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        true,
        false,
        false,
        false,
        true
    },
    {
        &Rover,
        Capsule_Rover::borderport_engine,
        &Top_slots[InstId_Top_rover],
        1,
        &borderfarEndList_Top_rover[1],
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        true,
        false,
        false,
        false,
        true
    },
    {
        &Rover,
        Capsule_Rover::borderport_temperature,
        &Top_slots[InstId_Top_rover],
        1,
        &borderfarEndList_Top_rover[2],
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_Top_rover_ptrs[] = 
{
    &borderports_Top_rover[0],
    &borderports_Top_rover[1],
    &borderports_Top_rover[2]
};

static Capsule_Rover top_rover( &Rover, &Top_slots[InstId_Top_rover], borderports_Top_rover_ptrs, NULL, true );

static UMLRTSlot * slots_Top_rover[] = 
{
    &Top_slots[InstId_Top_rover_detectionSensor],
    &Top_slots[InstId_Top_rover_detectionSensor2],
    &Top_slots[InstId_Top_rover_engineController],
    &Top_slots[InstId_Top_rover_temperatureSensor]
};

static UMLRTCapsulePart parts_Top_rover[] = 
{
    {
        &Rover,
        Capsule_Rover::part_detectionSensor,
        1,
        &slots_Top_rover[0]
    },
    {
        &Rover,
        Capsule_Rover::part_detectionSensor2,
        1,
        &slots_Top_rover[1]
    },
    {
        &Rover,
        Capsule_Rover::part_engineController,
        1,
        &slots_Top_rover[2]
    },
    {
        &Rover,
        Capsule_Rover::part_temperatureSensor,
        1,
        &slots_Top_rover[3]
    }
};

static UMLRTCommsPortFarEnd borderfarEndList_Top_rover_detectionSensor[] = 
{
    {
        0,
        NULL
    },
    {
        0,
        NULL
    },
    {
        0,
        NULL
    }
};

UMLRTCommsPort borderports_Top_rover_detectionSensor[] = 
{
    {
        &DetectionSensor,
        Capsule_DetectionSensor::borderport_detection,
        &Top_slots[InstId_Top_rover_detectionSensor],
        1,
        borderfarEndList_Top_rover_detectionSensor,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    },
    {
        &DetectionSensor,
        Capsule_DetectionSensor::borderport_timer,
        &Top_slots[InstId_Top_rover_detectionSensor],
        1,
        &borderfarEndList_Top_rover_detectionSensor[2],
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    },
    {
        &DetectionSensor,
        Capsule_DetectionSensor::borderport_log,
        &Top_slots[InstId_Top_rover_detectionSensor],
        1,
        &borderfarEndList_Top_rover_detectionSensor[1],
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_Top_rover_detectionSensor_ptrs[] = 
{
    &borderports_Top_rover_detectionSensor[0],
    &borderports_Top_rover_detectionSensor[1],
    &borderports_Top_rover_detectionSensor[2]
};

static Capsule_DetectionSensor top_rover_detectionSensor( &DetectionSensor, &Top_slots[InstId_Top_rover_detectionSensor], borderports_Top_rover_detectionSensor_ptrs, NULL, true );

static UMLRTCommsPortFarEnd borderfarEndList_Top_rover_detectionSensor2[] = 
{
    {
        0,
        &borderports_Top_controlSoftware[Capsule_ControlSoftware::borderport_detection]
    },
    {
        0,
        NULL
    },
    {
        0,
        NULL
    }
};

UMLRTCommsPort borderports_Top_rover_detectionSensor2[] = 
{
    {
        &DetectionSensor,
        Capsule_DetectionSensor::borderport_detection,
        &Top_slots[InstId_Top_rover_detectionSensor2],
        1,
        borderfarEndList_Top_rover_detectionSensor2,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    },
    {
        &DetectionSensor,
        Capsule_DetectionSensor::borderport_timer,
        &Top_slots[InstId_Top_rover_detectionSensor2],
        1,
        &borderfarEndList_Top_rover_detectionSensor2[2],
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    },
    {
        &DetectionSensor,
        Capsule_DetectionSensor::borderport_log,
        &Top_slots[InstId_Top_rover_detectionSensor2],
        1,
        &borderfarEndList_Top_rover_detectionSensor2[1],
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_Top_rover_detectionSensor2_ptrs[] = 
{
    &borderports_Top_rover_detectionSensor2[0],
    &borderports_Top_rover_detectionSensor2[1],
    &borderports_Top_rover_detectionSensor2[2]
};

static Capsule_DetectionSensor top_rover_detectionSensor2( &DetectionSensor, &Top_slots[InstId_Top_rover_detectionSensor2], borderports_Top_rover_detectionSensor2_ptrs, NULL, true );

static UMLRTCommsPortFarEnd borderfarEndList_Top_rover_engineController[] = 
{
    {
        0,
        &borderports_Top_controlSoftware[Capsule_ControlSoftware::borderport_engine]
    },
    {
        0,
        NULL
    },
    {
        0,
        NULL
    }
};

UMLRTCommsPort borderports_Top_rover_engineController[] = 
{
    {
        &EngineController,
        Capsule_EngineController::borderport_engine,
        &Top_slots[InstId_Top_rover_engineController],
        1,
        borderfarEndList_Top_rover_engineController,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    },
    {
        &EngineController,
        Capsule_EngineController::borderport_timer,
        &Top_slots[InstId_Top_rover_engineController],
        1,
        &borderfarEndList_Top_rover_engineController[2],
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    },
    {
        &EngineController,
        Capsule_EngineController::borderport_log,
        &Top_slots[InstId_Top_rover_engineController],
        1,
        &borderfarEndList_Top_rover_engineController[1],
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_Top_rover_engineController_ptrs[] = 
{
    &borderports_Top_rover_engineController[0],
    &borderports_Top_rover_engineController[1],
    &borderports_Top_rover_engineController[2]
};

static Capsule_EngineController top_rover_engineController( &EngineController, &Top_slots[InstId_Top_rover_engineController], borderports_Top_rover_engineController_ptrs, NULL, true );

static UMLRTCommsPortFarEnd borderfarEndList_Top_rover_temperatureSensor[] = 
{
    {
        0,
        NULL
    }
};

UMLRTCommsPort borderports_Top_rover_temperatureSensor[] = 
{
    {
        &TemperatureSensor,
        Capsule_TemperatureSensor::borderport_temperature,
        &Top_slots[InstId_Top_rover_temperatureSensor],
        1,
        borderfarEndList_Top_rover_temperatureSensor,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_Top_rover_temperatureSensor_ptrs[] = 
{
    &borderports_Top_rover_temperatureSensor[0]
};

static Capsule_TemperatureSensor top_rover_temperatureSensor( &TemperatureSensor, &Top_slots[InstId_Top_rover_temperatureSensor], borderports_Top_rover_temperatureSensor_ptrs, NULL, true );

UMLRTSlot Top_slots[] = 
{
    {
        "Top",
        0,
        &Top,
        NULL,
        0,
        &top,
        &DefaultController_,
        2,
        parts_Top,
        0,
        NULL,
        NULL,
        true,
        false
    },
    {
        "Top.controlSoftware",
        0,
        &ControlSoftware,
        &Top,
        Capsule_Top::part_controlSoftware,
        &top_controlSoftware,
        &DefaultController_,
        0,
        NULL,
        5,
        borderports_Top_controlSoftware,
        NULL,
        true,
        false
    },
    {
        "Top.rover",
        0,
        &Rover,
        &Top,
        Capsule_Top::part_rover,
        &top_rover,
        &DefaultController_,
        4,
        parts_Top_rover,
        3,
        borderports_Top_rover,
        NULL,
        true,
        false
    },
    {
        "Top.rover.detectionSensor",
        0,
        &DetectionSensor,
        &Rover,
        Capsule_Rover::part_detectionSensor,
        &top_rover_detectionSensor,
        &DefaultController_,
        0,
        NULL,
        3,
        borderports_Top_rover_detectionSensor,
        NULL,
        true,
        false
    },
    {
        "Top.rover.detectionSensor2",
        0,
        &DetectionSensor,
        &Rover,
        Capsule_Rover::part_detectionSensor2,
        &top_rover_detectionSensor2,
        &DefaultController_,
        0,
        NULL,
        3,
        borderports_Top_rover_detectionSensor2,
        NULL,
        true,
        false
    },
    {
        "Top.rover.engineController",
        0,
        &EngineController,
        &Rover,
        Capsule_Rover::part_engineController,
        &top_rover_engineController,
        &DefaultController_,
        0,
        NULL,
        3,
        borderports_Top_rover_engineController,
        NULL,
        true,
        false
    },
    {
        "Top.rover.temperatureSensor",
        0,
        &TemperatureSensor,
        &Rover,
        Capsule_Rover::part_temperatureSensor,
        &top_rover_temperatureSensor,
        &DefaultController_,
        0,
        NULL,
        1,
        borderports_Top_rover_temperatureSensor,
        NULL,
        true,
        false
    }
};

