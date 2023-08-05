#include "includes.h"
namespace Offsets {
    //Global
    kaddr Base;
    kaddr GWorld;
    kaddr GNames;
    kaddr PointerSize;

    //---------SDK-----------//
    //---------4.23+---------//
    //Class: UStruct
    kaddr UStructToChildProperties;
    //Class: FField
    kaddr FFieldToClass;
    kaddr FFieldToNext;
    kaddr FFieldToName;
    //---------4.18+---------//
    //Class: FNameEntry
    //-----------------------//
    //Class: FUObjectArray
    //Class: TUObjectArray
    //Class: UObject
    kaddr UObjectToInternalIndex;
    kaddr UObjectToClassPrivate;
    kaddr UObjectToFNameIndex;
    kaddr UObjectToOuterPrivate;
    //Class: UField
    kaddr UFieldToNext;
    //Class: UStruct
    kaddr UStructToSuperStruct;
    kaddr UStructToChildren;
    //Class: UFunction
    kaddr UFunctionToFunctionFlags;
    kaddr UFunctionToFunc;
    //Class: UProperty
    kaddr UPropertyToElementSize;
    kaddr UPropertyToPropertyFlags;
    kaddr UPropertyToOffsetInternal;
    //Class: UBoolProperty
    kaddr UBoolPropertyToFieldSize;
    kaddr UBoolPropertyToByteOffset;
    kaddr UBoolPropertyToByteMask;
    kaddr UBoolPropertyToFieldMask;
    //Class: UObjectProperty
    kaddr UObjectPropertyToPropertyClass;
    //Class: UClassProperty
    kaddr UClassPropertyToMetaClass;
    //Class: UInterfaceProperty
    kaddr UInterfacePropertyToInterfaceClass;
    //Class: UArrayProperty
    kaddr UArrayPropertyToInnerProperty;
    //Class: UMapProperty
    kaddr UMapPropertyToKeyProp;
    kaddr UMapPropertyToValueProp;
    //Class: USetProperty
    kaddr USetPropertyToElementProp;
    //Class: UStructProperty
    kaddr UStructPropertyToStruct;

    kaddr UWorldToPersistentLevel;

    kaddr ULevelToAActors;
    kaddr ULevelToAActorsCount;
    void initOffsets_32() {
        //Global
        PointerSize = 0x8;

        //---------SDK-----------
        //Class: UObject
        UObjectToInternalIndex = 0xC;
        UObjectToClassPrivate = 0x10;
        UObjectToFNameIndex = 0x18;
        UObjectToOuterPrivate = 0x20;
        //Class: UField
        UFieldToNext = 0x28;
        //Class: UStruct
        UStructToSuperStruct = 0x40;
        UStructToChildren = 0x48;
        //Class: UFunction
        UFunctionToFunctionFlags = 0xB0;
        UFunctionToFunc = 0xB0 + 0x28;
        //Class: UProperty
        UPropertyToElementSize = 0x38;
        UPropertyToPropertyFlags = 0x40;
        UPropertyToOffsetInternal = 0x4C;
        //Class: UBoolProperty
        UBoolPropertyToFieldSize = 0x78;
        UBoolPropertyToByteOffset = 0x79;
        UBoolPropertyToByteMask = 0x7A;
        UBoolPropertyToFieldMask = 0x7B;
        //Class: UObjectProperty
        UObjectPropertyToPropertyClass = 0x78;
        //Class: UClassProperty
        UClassPropertyToMetaClass = 0x80;
        //Class: UInterfaceProperty
        UInterfacePropertyToInterfaceClass = 0x80;
        //Class: UArrayProperty
        UArrayPropertyToInnerProperty = 0x78;
        //Class: UMapProperty
        UMapPropertyToKeyProp = 0x78;
        UMapPropertyToValueProp = 0x80;
        //Class: USetProperty
        USetPropertyToElementProp = 0x78;
        //Class: UStructProperty
        UStructPropertyToStruct = 0x78;
        //Class: UWorld
        UWorldToPersistentLevel = 0x30;
        //Class: ULevel
        ULevelToAActors = 0x98;
        ULevelToAActorsCount = 0xA0;
    }
    void patchUE423_32() {
        //Class: UStruct
        UStructToChildProperties = 0x50;
        //Class: FField
        FFieldToClass = 0x8;
        FFieldToNext = 0x20;
        FFieldToName = 0x28;
    }

}

