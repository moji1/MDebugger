
#include "Parcel.hh"

#include "umlrtobjectclass.hh"
#include "umlrtobjectclassgeneric.hh"
#include <cstddef>

const UMLRTObject_field Parcel::fields[] = 
{
    {
        "number",
        &UMLRTType_int,
        offsetof( Parcel, number ),
        1,
        0
    },
    {
        "level",
        &UMLRTType_int,
        offsetof( Parcel, level ),
        1,
        0
    },
    {
        "stage",
        &UMLRTType_int,
        offsetof( Parcel, stage ),
        1,
        0
    }
};
Parcel::Parcel()
{
}

Parcel::Parcel( const Parcel & other )
{
    number = other.number;
    level = other.level;
    stage = other.stage;
}

Parcel::~Parcel()
{
}




Parcel & Parcel::operator=( const Parcel & other )
{
    if( &other == this )
        return *this;
    number = other.number;
    level = other.level;
    stage = other.stage;
    return *this;
}



const UMLRTObject_class UMLRTType_Parcel = 
{
    UMLRTObjectInitialize<Parcel>,
    UMLRTObjectCopy<Parcel>,
    UMLRTObject_decode,
    UMLRTObject_encode,
    UMLRTObjectDestroy<Parcel>,
    UMLRTObject_fprintf,
    "Parcel",
    NULL,
    {
        sizeof( Parcel ),
        3,
        Parcel::fields
    },
    UMLRTOBJECTCLASS_DEFAULT_VERSION,
    UMLRTOBJECTCLASS_DEFAULT_BACKWARDS
};

