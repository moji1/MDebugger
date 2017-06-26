
#include "Debug__TopControllers.hh"

#include "Car.hh"
#include "CentralLock.hh"
#include "Debug__Top.hh"
#include "Door.hh"
#include "GateWay.hh"
#include "Lock.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcapsulepart.hh"
#include "umlrtcommsport.hh"
#include "umlrtcommsportfarend.hh"
#include "umlrtcontroller.hh"
#include "umlrtslot.hh"
#include <cstddef>


static UMLRTController DefaultController_( "DefaultController" );

UMLRTController * DefaultController = &DefaultController_;

static Capsule_Debug__Top debug__Top( &Debug__Top, &Debug__Top_slots[InstId_Debug__Top], NULL, NULL, true );

static UMLRTSlot * slots_Debug__Top[] = 
{
    &Debug__Top_slots[InstId_Debug__Top_Debug__Car],
    &Debug__Top_slots[InstId_Debug__Top_Debug__Gateway]
};

static UMLRTCapsulePart parts_Debug__Top[] = 
{
    {
        &Debug__Top,
        Capsule_Debug__Top::part_Debug__Car,
        1,
        &slots_Debug__Top[0]
    },
    {
        &Debug__Top,
        Capsule_Debug__Top::part_Debug__Gateway,
        1,
        &slots_Debug__Top[1]
    }
};

static Capsule_Car debug__Top_Debug__Car( &Car, &Debug__Top_slots[InstId_Debug__Top_Debug__Car], NULL, NULL, true );

static UMLRTSlot * slots_Debug__Top_Debug__Car[] = 
{
    &Debug__Top_slots[InstId_Debug__Top_Debug__Car_centralLock],
    &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door1],
    &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door2],
    &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door3],
    &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door4]
};

static UMLRTCapsulePart parts_Debug__Top_Debug__Car[] = 
{
    {
        &Car,
        Capsule_Car::part_centralLock,
        1,
        &slots_Debug__Top_Debug__Car[0]
    },
    {
        &Car,
        Capsule_Car::part_door1,
        1,
        &slots_Debug__Top_Debug__Car[1]
    },
    {
        &Car,
        Capsule_Car::part_door2,
        1,
        &slots_Debug__Top_Debug__Car[2]
    },
    {
        &Car,
        Capsule_Car::part_door3,
        1,
        &slots_Debug__Top_Debug__Car[3]
    },
    {
        &Car,
        Capsule_Car::part_door4,
        1,
        &slots_Debug__Top_Debug__Car[4]
    }
};

static UMLRTCommsPortFarEnd borderfarEndList_Debug__Top_Debug__Car_centralLock[] = 
{
    {
        0,
        NULL
    },
    {
        0,
        &borderports_Debug__Top_Debug__Car_door1_lock[Capsule_Lock::borderport_lockPort]
    },
    {
        0,
        &borderports_Debug__Top_Debug__Car_door2_lock[Capsule_Lock::borderport_lockPort]
    },
    {
        0,
        &borderports_Debug__Top_Debug__Car_door3_lock[Capsule_Lock::borderport_lockPort]
    },
    {
        0,
        &borderports_Debug__Top_Debug__Car_door4_lock[Capsule_Lock::borderport_lockPort]
    },
    {
        0,
        NULL
    }
};

UMLRTCommsPort borderports_Debug__Top_Debug__Car_centralLock[] = 
{
    {
        &CentralLock,
        Capsule_CentralLock::borderport_extComm,
        &Debug__Top_slots[InstId_Debug__Top_Debug__Car_centralLock],
        1,
        borderfarEndList_Debug__Top_Debug__Car_centralLock,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        true,
        false,
        false,
        true,
        false,
        false,
        false
    },
    {
        &CentralLock,
        Capsule_CentralLock::borderport_lockPort,
        &Debug__Top_slots[InstId_Debug__Top_Debug__Car_centralLock],
        4,
        &borderfarEndList_Debug__Top_Debug__Car_centralLock[1],
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
        &CentralLock,
        Capsule_CentralLock::borderport_startupTimer,
        &Debug__Top_slots[InstId_Debug__Top_Debug__Car_centralLock],
        1,
        &borderfarEndList_Debug__Top_Debug__Car_centralLock[5],
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
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * borderports_Debug__Top_Debug__Car_centralLock_ptrs[] = 
{
    &borderports_Debug__Top_Debug__Car_centralLock[0],
    &borderports_Debug__Top_Debug__Car_centralLock[1],
    &borderports_Debug__Top_Debug__Car_centralLock[2]
};

static Capsule_CentralLock debug__Top_Debug__Car_centralLock( &CentralLock, &Debug__Top_slots[InstId_Debug__Top_Debug__Car_centralLock], borderports_Debug__Top_Debug__Car_centralLock_ptrs, NULL, true );

static UMLRTCommsPortFarEnd borderfarEndList_Debug__Top_Debug__Car_door1[] = 
{
    {
        0,
        NULL
    }
};

UMLRTCommsPort borderports_Debug__Top_Debug__Car_door1[] = 
{
    {
        &Door,
        Capsule_Door::borderport_lockPort,
        &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door1],
        1,
        borderfarEndList_Debug__Top_Debug__Car_door1,
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
    }
};

static const UMLRTCommsPort * borderports_Debug__Top_Debug__Car_door1_ptrs[] = 
{
    &borderports_Debug__Top_Debug__Car_door1[0]
};

static Capsule_Door debug__Top_Debug__Car_door1( &Door, &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door1], borderports_Debug__Top_Debug__Car_door1_ptrs, NULL, true );

static UMLRTSlot * slots_Debug__Top_Debug__Car_door1[] = 
{
    &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door1_lock]
};

static UMLRTCapsulePart parts_Debug__Top_Debug__Car_door1[] = 
{
    {
        &Door,
        Capsule_Door::part_lock,
        1,
        &slots_Debug__Top_Debug__Car_door1[0]
    }
};

static UMLRTCommsPortFarEnd borderfarEndList_Debug__Top_Debug__Car_door1_lock[] = 
{
    {
        0,
        NULL
    },
    {
        0,
        &borderports_Debug__Top_Debug__Car_centralLock[Capsule_CentralLock::borderport_lockPort]
    }
};

UMLRTCommsPort borderports_Debug__Top_Debug__Car_door1_lock[] = 
{
    {
        &Lock,
        Capsule_Lock::borderport_lockPort,
        &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door1_lock],
        1,
        &borderfarEndList_Debug__Top_Debug__Car_door1_lock[1],
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
        &Lock,
        Capsule_Lock::borderport_extComm,
        &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door1_lock],
        1,
        borderfarEndList_Debug__Top_Debug__Car_door1_lock,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        true,
        false,
        false,
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * borderports_Debug__Top_Debug__Car_door1_lock_ptrs[] = 
{
    &borderports_Debug__Top_Debug__Car_door1_lock[0],
    &borderports_Debug__Top_Debug__Car_door1_lock[1]
};

static Capsule_Lock debug__Top_Debug__Car_door1_lock( &Lock, &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door1_lock], borderports_Debug__Top_Debug__Car_door1_lock_ptrs, NULL, true );

static UMLRTCommsPortFarEnd borderfarEndList_Debug__Top_Debug__Car_door2[] = 
{
    {
        0,
        NULL
    }
};

UMLRTCommsPort borderports_Debug__Top_Debug__Car_door2[] = 
{
    {
        &Door,
        Capsule_Door::borderport_lockPort,
        &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door2],
        1,
        borderfarEndList_Debug__Top_Debug__Car_door2,
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
    }
};

static const UMLRTCommsPort * borderports_Debug__Top_Debug__Car_door2_ptrs[] = 
{
    &borderports_Debug__Top_Debug__Car_door2[0]
};

static Capsule_Door debug__Top_Debug__Car_door2( &Door, &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door2], borderports_Debug__Top_Debug__Car_door2_ptrs, NULL, true );

static UMLRTSlot * slots_Debug__Top_Debug__Car_door2[] = 
{
    &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door2_lock]
};

static UMLRTCapsulePart parts_Debug__Top_Debug__Car_door2[] = 
{
    {
        &Door,
        Capsule_Door::part_lock,
        1,
        &slots_Debug__Top_Debug__Car_door2[0]
    }
};

static UMLRTCommsPortFarEnd borderfarEndList_Debug__Top_Debug__Car_door2_lock[] = 
{
    {
        0,
        NULL
    },
    {
        1,
        &borderports_Debug__Top_Debug__Car_centralLock[Capsule_CentralLock::borderport_lockPort]
    }
};

UMLRTCommsPort borderports_Debug__Top_Debug__Car_door2_lock[] = 
{
    {
        &Lock,
        Capsule_Lock::borderport_lockPort,
        &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door2_lock],
        1,
        &borderfarEndList_Debug__Top_Debug__Car_door2_lock[1],
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
        &Lock,
        Capsule_Lock::borderport_extComm,
        &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door2_lock],
        1,
        borderfarEndList_Debug__Top_Debug__Car_door2_lock,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        true,
        false,
        false,
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * borderports_Debug__Top_Debug__Car_door2_lock_ptrs[] = 
{
    &borderports_Debug__Top_Debug__Car_door2_lock[0],
    &borderports_Debug__Top_Debug__Car_door2_lock[1]
};

static Capsule_Lock debug__Top_Debug__Car_door2_lock( &Lock, &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door2_lock], borderports_Debug__Top_Debug__Car_door2_lock_ptrs, NULL, true );

static UMLRTCommsPortFarEnd borderfarEndList_Debug__Top_Debug__Car_door3[] = 
{
    {
        0,
        NULL
    }
};

UMLRTCommsPort borderports_Debug__Top_Debug__Car_door3[] = 
{
    {
        &Door,
        Capsule_Door::borderport_lockPort,
        &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door3],
        1,
        borderfarEndList_Debug__Top_Debug__Car_door3,
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
    }
};

static const UMLRTCommsPort * borderports_Debug__Top_Debug__Car_door3_ptrs[] = 
{
    &borderports_Debug__Top_Debug__Car_door3[0]
};

static Capsule_Door debug__Top_Debug__Car_door3( &Door, &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door3], borderports_Debug__Top_Debug__Car_door3_ptrs, NULL, true );

static UMLRTSlot * slots_Debug__Top_Debug__Car_door3[] = 
{
    &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door3_lock]
};

static UMLRTCapsulePart parts_Debug__Top_Debug__Car_door3[] = 
{
    {
        &Door,
        Capsule_Door::part_lock,
        1,
        &slots_Debug__Top_Debug__Car_door3[0]
    }
};

static UMLRTCommsPortFarEnd borderfarEndList_Debug__Top_Debug__Car_door3_lock[] = 
{
    {
        0,
        NULL
    },
    {
        2,
        &borderports_Debug__Top_Debug__Car_centralLock[Capsule_CentralLock::borderport_lockPort]
    }
};

UMLRTCommsPort borderports_Debug__Top_Debug__Car_door3_lock[] = 
{
    {
        &Lock,
        Capsule_Lock::borderport_lockPort,
        &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door3_lock],
        1,
        &borderfarEndList_Debug__Top_Debug__Car_door3_lock[1],
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
        &Lock,
        Capsule_Lock::borderport_extComm,
        &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door3_lock],
        1,
        borderfarEndList_Debug__Top_Debug__Car_door3_lock,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        true,
        false,
        false,
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * borderports_Debug__Top_Debug__Car_door3_lock_ptrs[] = 
{
    &borderports_Debug__Top_Debug__Car_door3_lock[0],
    &borderports_Debug__Top_Debug__Car_door3_lock[1]
};

static Capsule_Lock debug__Top_Debug__Car_door3_lock( &Lock, &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door3_lock], borderports_Debug__Top_Debug__Car_door3_lock_ptrs, NULL, true );

static UMLRTCommsPortFarEnd borderfarEndList_Debug__Top_Debug__Car_door4[] = 
{
    {
        0,
        NULL
    }
};

UMLRTCommsPort borderports_Debug__Top_Debug__Car_door4[] = 
{
    {
        &Door,
        Capsule_Door::borderport_lockPort,
        &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door4],
        1,
        borderfarEndList_Debug__Top_Debug__Car_door4,
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
    }
};

static const UMLRTCommsPort * borderports_Debug__Top_Debug__Car_door4_ptrs[] = 
{
    &borderports_Debug__Top_Debug__Car_door4[0]
};

static Capsule_Door debug__Top_Debug__Car_door4( &Door, &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door4], borderports_Debug__Top_Debug__Car_door4_ptrs, NULL, true );

static UMLRTSlot * slots_Debug__Top_Debug__Car_door4[] = 
{
    &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door4_lock]
};

static UMLRTCapsulePart parts_Debug__Top_Debug__Car_door4[] = 
{
    {
        &Door,
        Capsule_Door::part_lock,
        1,
        &slots_Debug__Top_Debug__Car_door4[0]
    }
};

static UMLRTCommsPortFarEnd borderfarEndList_Debug__Top_Debug__Car_door4_lock[] = 
{
    {
        0,
        NULL
    },
    {
        3,
        &borderports_Debug__Top_Debug__Car_centralLock[Capsule_CentralLock::borderport_lockPort]
    }
};

UMLRTCommsPort borderports_Debug__Top_Debug__Car_door4_lock[] = 
{
    {
        &Lock,
        Capsule_Lock::borderport_lockPort,
        &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door4_lock],
        1,
        &borderfarEndList_Debug__Top_Debug__Car_door4_lock[1],
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
        &Lock,
        Capsule_Lock::borderport_extComm,
        &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door4_lock],
        1,
        borderfarEndList_Debug__Top_Debug__Car_door4_lock,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        true,
        false,
        false,
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * borderports_Debug__Top_Debug__Car_door4_lock_ptrs[] = 
{
    &borderports_Debug__Top_Debug__Car_door4_lock[0],
    &borderports_Debug__Top_Debug__Car_door4_lock[1]
};

static Capsule_Lock debug__Top_Debug__Car_door4_lock( &Lock, &Debug__Top_slots[InstId_Debug__Top_Debug__Car_door4_lock], borderports_Debug__Top_Debug__Car_door4_lock_ptrs, NULL, true );

static UMLRTCommsPortFarEnd borderfarEndList_Debug__Top_Debug__Gateway[] = 
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
    },
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
    },
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
    },
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
    },
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
    },
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
    },
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
    },
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
    },
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
    },
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
    },
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
    },
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
    },
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
    },
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
    },
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
    },
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
    },
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
    },
    {
        0,
        NULL
    }
};

UMLRTCommsPort borderports_Debug__Top_Debug__Gateway[] = 
{
    {
        &GateWay,
        Capsule_GateWay::borderport_commandTimer,
        &Debug__Top_slots[InstId_Debug__Top_Debug__Gateway],
        1,
        borderfarEndList_Debug__Top_Debug__Gateway,
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
        &GateWay,
        Capsule_GateWay::borderport_configTimer,
        &Debug__Top_slots[InstId_Debug__Top_Debug__Gateway],
        1,
        &borderfarEndList_Debug__Top_Debug__Gateway[1],
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
        &GateWay,
        Capsule_GateWay::borderport_extComm,
        &Debug__Top_slots[InstId_Debug__Top_Debug__Gateway],
        50,
        &borderfarEndList_Debug__Top_Debug__Gateway[2],
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
        true,
        false,
        false
    }
};

static const UMLRTCommsPort * borderports_Debug__Top_Debug__Gateway_ptrs[] = 
{
    &borderports_Debug__Top_Debug__Gateway[0],
    &borderports_Debug__Top_Debug__Gateway[1],
    &borderports_Debug__Top_Debug__Gateway[2]
};

static Capsule_GateWay debug__Top_Debug__Gateway( &GateWay, &Debug__Top_slots[InstId_Debug__Top_Debug__Gateway], borderports_Debug__Top_Debug__Gateway_ptrs, NULL, true );

UMLRTSlot Debug__Top_slots[] = 
{
    {
        "Debug__Top",
        0,
        &Debug__Top,
        NULL,
        0,
        &debug__Top,
        &DefaultController_,
        2,
        parts_Debug__Top,
        0,
        NULL,
        NULL,
        true,
        false
    },
    {
        "Debug__Top.Debug__Car",
        0,
        &Car,
        &Debug__Top,
        Capsule_Debug__Top::part_Debug__Car,
        &debug__Top_Debug__Car,
        &DefaultController_,
        5,
        parts_Debug__Top_Debug__Car,
        0,
        NULL,
        NULL,
        true,
        false
    },
    {
        "Debug__Top.Debug__Car.centralLock",
        0,
        &CentralLock,
        &Car,
        Capsule_Car::part_centralLock,
        &debug__Top_Debug__Car_centralLock,
        &DefaultController_,
        0,
        NULL,
        3,
        borderports_Debug__Top_Debug__Car_centralLock,
        NULL,
        true,
        false
    },
    {
        "Debug__Top.Debug__Car.door1",
        0,
        &Door,
        &Car,
        Capsule_Car::part_door1,
        &debug__Top_Debug__Car_door1,
        &DefaultController_,
        1,
        parts_Debug__Top_Debug__Car_door1,
        1,
        borderports_Debug__Top_Debug__Car_door1,
        NULL,
        true,
        false
    },
    {
        "Debug__Top.Debug__Car.door1.lock",
        0,
        &Lock,
        &Door,
        Capsule_Door::part_lock,
        &debug__Top_Debug__Car_door1_lock,
        &DefaultController_,
        0,
        NULL,
        2,
        borderports_Debug__Top_Debug__Car_door1_lock,
        NULL,
        true,
        false
    },
    {
        "Debug__Top.Debug__Car.door2",
        0,
        &Door,
        &Car,
        Capsule_Car::part_door2,
        &debug__Top_Debug__Car_door2,
        &DefaultController_,
        1,
        parts_Debug__Top_Debug__Car_door2,
        1,
        borderports_Debug__Top_Debug__Car_door2,
        NULL,
        true,
        false
    },
    {
        "Debug__Top.Debug__Car.door2.lock",
        0,
        &Lock,
        &Door,
        Capsule_Door::part_lock,
        &debug__Top_Debug__Car_door2_lock,
        &DefaultController_,
        0,
        NULL,
        2,
        borderports_Debug__Top_Debug__Car_door2_lock,
        NULL,
        true,
        false
    },
    {
        "Debug__Top.Debug__Car.door3",
        0,
        &Door,
        &Car,
        Capsule_Car::part_door3,
        &debug__Top_Debug__Car_door3,
        &DefaultController_,
        1,
        parts_Debug__Top_Debug__Car_door3,
        1,
        borderports_Debug__Top_Debug__Car_door3,
        NULL,
        true,
        false
    },
    {
        "Debug__Top.Debug__Car.door3.lock",
        0,
        &Lock,
        &Door,
        Capsule_Door::part_lock,
        &debug__Top_Debug__Car_door3_lock,
        &DefaultController_,
        0,
        NULL,
        2,
        borderports_Debug__Top_Debug__Car_door3_lock,
        NULL,
        true,
        false
    },
    {
        "Debug__Top.Debug__Car.door4",
        0,
        &Door,
        &Car,
        Capsule_Car::part_door4,
        &debug__Top_Debug__Car_door4,
        &DefaultController_,
        1,
        parts_Debug__Top_Debug__Car_door4,
        1,
        borderports_Debug__Top_Debug__Car_door4,
        NULL,
        true,
        false
    },
    {
        "Debug__Top.Debug__Car.door4.lock",
        0,
        &Lock,
        &Door,
        Capsule_Door::part_lock,
        &debug__Top_Debug__Car_door4_lock,
        &DefaultController_,
        0,
        NULL,
        2,
        borderports_Debug__Top_Debug__Car_door4_lock,
        NULL,
        true,
        false
    },
    {
        "Debug__Top.Debug__Gateway",
        0,
        &GateWay,
        &Debug__Top,
        Capsule_Debug__Top::part_Debug__Gateway,
        &debug__Top_Debug__Gateway,
        &DefaultController_,
        0,
        NULL,
        3,
        borderports_Debug__Top_Debug__Gateway,
        NULL,
        true,
        false
    }
};

