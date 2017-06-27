
#include "CarControllers.hh"

#include "Car.hh"
#include "CentralLock.hh"
#include "Door.hh"
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

static Capsule_Car car( &Car, &Car_slots[InstId_Car], NULL, NULL, true );

static UMLRTSlot * slots_Car[] = 
{
    &Car_slots[InstId_Car_centralLock],
    &Car_slots[InstId_Car_door1],
    &Car_slots[InstId_Car_door2],
    &Car_slots[InstId_Car_door3],
    &Car_slots[InstId_Car_door4]
};

static UMLRTCapsulePart parts_Car[] = 
{
    {
        &Car,
        Capsule_Car::part_centralLock,
        1,
        &slots_Car[0]
    },
    {
        &Car,
        Capsule_Car::part_door1,
        1,
        &slots_Car[1]
    },
    {
        &Car,
        Capsule_Car::part_door2,
        1,
        &slots_Car[2]
    },
    {
        &Car,
        Capsule_Car::part_door3,
        1,
        &slots_Car[3]
    },
    {
        &Car,
        Capsule_Car::part_door4,
        1,
        &slots_Car[4]
    }
};

static UMLRTCommsPortFarEnd borderfarEndList_Car_centralLock[] = 
{
    {
        0,
        &borderports_Car_door1_lock[Capsule_Lock::borderport_lockPort]
    },
    {
        0,
        &borderports_Car_door2_lock[Capsule_Lock::borderport_lockPort]
    },
    {
        0,
        &borderports_Car_door3_lock[Capsule_Lock::borderport_lockPort]
    },
    {
        0,
        &borderports_Car_door4_lock[Capsule_Lock::borderport_lockPort]
    },
    {
        0,
        NULL
    }
};

UMLRTCommsPort borderports_Car_centralLock[] = 
{
    {
        &CentralLock,
        Capsule_CentralLock::borderport_lockPort,
        &Car_slots[InstId_Car_centralLock],
        4,
        borderfarEndList_Car_centralLock,
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
        &Car_slots[InstId_Car_centralLock],
        1,
        &borderfarEndList_Car_centralLock[4],
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

static const UMLRTCommsPort * borderports_Car_centralLock_ptrs[] = 
{
    &borderports_Car_centralLock[0],
    &borderports_Car_centralLock[1]
};

static Capsule_CentralLock car_centralLock( &CentralLock, &Car_slots[InstId_Car_centralLock], borderports_Car_centralLock_ptrs, NULL, true );

static UMLRTCommsPortFarEnd borderfarEndList_Car_door1[] = 
{
    {
        0,
        NULL
    }
};

UMLRTCommsPort borderports_Car_door1[] = 
{
    {
        &Door,
        Capsule_Door::borderport_lockPort,
        &Car_slots[InstId_Car_door1],
        1,
        borderfarEndList_Car_door1,
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

static const UMLRTCommsPort * borderports_Car_door1_ptrs[] = 
{
    &borderports_Car_door1[0]
};

static Capsule_Door car_door1( &Door, &Car_slots[InstId_Car_door1], borderports_Car_door1_ptrs, NULL, true );

static UMLRTSlot * slots_Car_door1[] = 
{
    &Car_slots[InstId_Car_door1_lock]
};

static UMLRTCapsulePart parts_Car_door1[] = 
{
    {
        &Door,
        Capsule_Door::part_lock,
        1,
        &slots_Car_door1[0]
    }
};

static UMLRTCommsPortFarEnd borderfarEndList_Car_door1_lock[] = 
{
    {
        0,
        &borderports_Car_centralLock[Capsule_CentralLock::borderport_lockPort]
    }
};

UMLRTCommsPort borderports_Car_door1_lock[] = 
{
    {
        &Lock,
        Capsule_Lock::borderport_lockPort,
        &Car_slots[InstId_Car_door1_lock],
        1,
        borderfarEndList_Car_door1_lock,
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

static const UMLRTCommsPort * borderports_Car_door1_lock_ptrs[] = 
{
    &borderports_Car_door1_lock[0]
};

static Capsule_Lock car_door1_lock( &Lock, &Car_slots[InstId_Car_door1_lock], borderports_Car_door1_lock_ptrs, NULL, true );

static UMLRTCommsPortFarEnd borderfarEndList_Car_door2[] = 
{
    {
        0,
        NULL
    }
};

UMLRTCommsPort borderports_Car_door2[] = 
{
    {
        &Door,
        Capsule_Door::borderport_lockPort,
        &Car_slots[InstId_Car_door2],
        1,
        borderfarEndList_Car_door2,
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

static const UMLRTCommsPort * borderports_Car_door2_ptrs[] = 
{
    &borderports_Car_door2[0]
};

static Capsule_Door car_door2( &Door, &Car_slots[InstId_Car_door2], borderports_Car_door2_ptrs, NULL, true );

static UMLRTSlot * slots_Car_door2[] = 
{
    &Car_slots[InstId_Car_door2_lock]
};

static UMLRTCapsulePart parts_Car_door2[] = 
{
    {
        &Door,
        Capsule_Door::part_lock,
        1,
        &slots_Car_door2[0]
    }
};

static UMLRTCommsPortFarEnd borderfarEndList_Car_door2_lock[] = 
{
    {
        1,
        &borderports_Car_centralLock[Capsule_CentralLock::borderport_lockPort]
    }
};

UMLRTCommsPort borderports_Car_door2_lock[] = 
{
    {
        &Lock,
        Capsule_Lock::borderport_lockPort,
        &Car_slots[InstId_Car_door2_lock],
        1,
        borderfarEndList_Car_door2_lock,
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

static const UMLRTCommsPort * borderports_Car_door2_lock_ptrs[] = 
{
    &borderports_Car_door2_lock[0]
};

static Capsule_Lock car_door2_lock( &Lock, &Car_slots[InstId_Car_door2_lock], borderports_Car_door2_lock_ptrs, NULL, true );

static UMLRTCommsPortFarEnd borderfarEndList_Car_door3[] = 
{
    {
        0,
        NULL
    }
};

UMLRTCommsPort borderports_Car_door3[] = 
{
    {
        &Door,
        Capsule_Door::borderport_lockPort,
        &Car_slots[InstId_Car_door3],
        1,
        borderfarEndList_Car_door3,
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

static const UMLRTCommsPort * borderports_Car_door3_ptrs[] = 
{
    &borderports_Car_door3[0]
};

static Capsule_Door car_door3( &Door, &Car_slots[InstId_Car_door3], borderports_Car_door3_ptrs, NULL, true );

static UMLRTSlot * slots_Car_door3[] = 
{
    &Car_slots[InstId_Car_door3_lock]
};

static UMLRTCapsulePart parts_Car_door3[] = 
{
    {
        &Door,
        Capsule_Door::part_lock,
        1,
        &slots_Car_door3[0]
    }
};

static UMLRTCommsPortFarEnd borderfarEndList_Car_door3_lock[] = 
{
    {
        2,
        &borderports_Car_centralLock[Capsule_CentralLock::borderport_lockPort]
    }
};

UMLRTCommsPort borderports_Car_door3_lock[] = 
{
    {
        &Lock,
        Capsule_Lock::borderport_lockPort,
        &Car_slots[InstId_Car_door3_lock],
        1,
        borderfarEndList_Car_door3_lock,
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

static const UMLRTCommsPort * borderports_Car_door3_lock_ptrs[] = 
{
    &borderports_Car_door3_lock[0]
};

static Capsule_Lock car_door3_lock( &Lock, &Car_slots[InstId_Car_door3_lock], borderports_Car_door3_lock_ptrs, NULL, true );

static UMLRTCommsPortFarEnd borderfarEndList_Car_door4[] = 
{
    {
        0,
        NULL
    }
};

UMLRTCommsPort borderports_Car_door4[] = 
{
    {
        &Door,
        Capsule_Door::borderport_lockPort,
        &Car_slots[InstId_Car_door4],
        1,
        borderfarEndList_Car_door4,
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

static const UMLRTCommsPort * borderports_Car_door4_ptrs[] = 
{
    &borderports_Car_door4[0]
};

static Capsule_Door car_door4( &Door, &Car_slots[InstId_Car_door4], borderports_Car_door4_ptrs, NULL, true );

static UMLRTSlot * slots_Car_door4[] = 
{
    &Car_slots[InstId_Car_door4_lock]
};

static UMLRTCapsulePart parts_Car_door4[] = 
{
    {
        &Door,
        Capsule_Door::part_lock,
        1,
        &slots_Car_door4[0]
    }
};

static UMLRTCommsPortFarEnd borderfarEndList_Car_door4_lock[] = 
{
    {
        3,
        &borderports_Car_centralLock[Capsule_CentralLock::borderport_lockPort]
    }
};

UMLRTCommsPort borderports_Car_door4_lock[] = 
{
    {
        &Lock,
        Capsule_Lock::borderport_lockPort,
        &Car_slots[InstId_Car_door4_lock],
        1,
        borderfarEndList_Car_door4_lock,
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

static const UMLRTCommsPort * borderports_Car_door4_lock_ptrs[] = 
{
    &borderports_Car_door4_lock[0]
};

static Capsule_Lock car_door4_lock( &Lock, &Car_slots[InstId_Car_door4_lock], borderports_Car_door4_lock_ptrs, NULL, true );

UMLRTSlot Car_slots[] = 
{
    {
        "Car",
        0,
        &Car,
        NULL,
        0,
        &car,
        &DefaultController_,
        5,
        parts_Car,
        0,
        NULL,
        NULL,
        true,
        false
    },
    {
        "Car.centralLock",
        0,
        &CentralLock,
        &Car,
        Capsule_Car::part_centralLock,
        &car_centralLock,
        &DefaultController_,
        0,
        NULL,
        2,
        borderports_Car_centralLock,
        NULL,
        true,
        false
    },
    {
        "Car.door1",
        0,
        &Door,
        &Car,
        Capsule_Car::part_door1,
        &car_door1,
        &DefaultController_,
        1,
        parts_Car_door1,
        1,
        borderports_Car_door1,
        NULL,
        true,
        false
    },
    {
        "Car.door1.lock",
        0,
        &Lock,
        &Door,
        Capsule_Door::part_lock,
        &car_door1_lock,
        &DefaultController_,
        0,
        NULL,
        1,
        borderports_Car_door1_lock,
        NULL,
        true,
        false
    },
    {
        "Car.door2",
        0,
        &Door,
        &Car,
        Capsule_Car::part_door2,
        &car_door2,
        &DefaultController_,
        1,
        parts_Car_door2,
        1,
        borderports_Car_door2,
        NULL,
        true,
        false
    },
    {
        "Car.door2.lock",
        0,
        &Lock,
        &Door,
        Capsule_Door::part_lock,
        &car_door2_lock,
        &DefaultController_,
        0,
        NULL,
        1,
        borderports_Car_door2_lock,
        NULL,
        true,
        false
    },
    {
        "Car.door3",
        0,
        &Door,
        &Car,
        Capsule_Car::part_door3,
        &car_door3,
        &DefaultController_,
        1,
        parts_Car_door3,
        1,
        borderports_Car_door3,
        NULL,
        true,
        false
    },
    {
        "Car.door3.lock",
        0,
        &Lock,
        &Door,
        Capsule_Door::part_lock,
        &car_door3_lock,
        &DefaultController_,
        0,
        NULL,
        1,
        borderports_Car_door3_lock,
        NULL,
        true,
        false
    },
    {
        "Car.door4",
        0,
        &Door,
        &Car,
        Capsule_Car::part_door4,
        &car_door4,
        &DefaultController_,
        1,
        parts_Car_door4,
        1,
        borderports_Car_door4,
        NULL,
        true,
        false
    },
    {
        "Car.door4.lock",
        0,
        &Lock,
        &Door,
        Capsule_Door::part_lock,
        &car_door4_lock,
        &DefaultController_,
        0,
        NULL,
        1,
        borderports_Car_door4_lock,
        NULL,
        true,
        false
    }
};

