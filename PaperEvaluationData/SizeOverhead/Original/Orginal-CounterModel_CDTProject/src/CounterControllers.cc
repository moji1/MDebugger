
#include "CounterControllers.hh"

#include "Counter.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcommsport.hh"
#include "umlrtcommsportfarend.hh"
#include "umlrtcontroller.hh"
#include "umlrtslot.hh"
#include <cstddef>


static UMLRTController DefaultController_( "DefaultController" );

UMLRTController * DefaultController = &DefaultController_;

static UMLRTCommsPortFarEnd borderfarEndList_Counter[] = 
{
    {
        0,
        NULL
    }
};

UMLRTCommsPort borderports_Counter[] = 
{
    {
        &Counter,
        Capsule_Counter::borderport_timer1,
        &Counter_slots[InstId_Counter],
        1,
        borderfarEndList_Counter,
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

static const UMLRTCommsPort * borderports_Counter_ptrs[] = 
{
    &borderports_Counter[0]
};

static Capsule_Counter counter( &Counter, &Counter_slots[InstId_Counter], borderports_Counter_ptrs, NULL, true );

UMLRTSlot Counter_slots[] = 
{
    {
        "Counter",
        0,
        &Counter,
        NULL,
        0,
        &counter,
        &DefaultController_,
        0,
        NULL,
        1,
        borderports_Counter,
        NULL,
        true,
        false
    }
};

