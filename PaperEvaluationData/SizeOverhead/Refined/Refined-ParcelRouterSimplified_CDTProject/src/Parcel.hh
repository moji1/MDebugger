
#ifndef PARCEL_HH
#define PARCEL_HH

#include "umlrtobjectclass.hh"

class Parcel
{
public:
    Parcel();
    Parcel( const Parcel & other );
    ~Parcel();
    int number;
    int level;
    int stage;
    Parcel & operator=( const Parcel & other );
    static const UMLRTObject_field fields[];
};
extern const UMLRTObject_class UMLRTType_Parcel;

#endif

