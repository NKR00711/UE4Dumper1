#pragma once

namespace Offsets {
    //Global
    extern kaddr Base;
    extern kaddr GWorld;
    extern kaddr GNames;
    extern kaddr PointerSize;

    //---------SDK-----------//
    //---------4.23+---------//
    //Class: UStruct
    extern kaddr UStructToChildProperties;
    //Class: FField
    extern kaddr FFieldToClass;
    extern kaddr FFieldToNext;
    extern kaddr FFieldToName;
    //---------4.18+---------//
    //Class: FNameEntry
    //-----------------------//
    //Class: FUObjectArray
    //Class: TUObjectArray
    //Class: UObject
    extern kaddr UObjectToInternalIndex;
    extern kaddr UObjectToClassPrivate;
    extern kaddr UObjectToFNameIndex;
    extern kaddr UObjectToOuterPrivate;
    //Class: UField
    extern kaddr UFieldToNext;
    //Class: UStruct
    extern kaddr UStructToSuperStruct;
    extern kaddr UStructToChildren;
    //Class: UFunction
    extern kaddr UFunctionToFunctionFlags;
    extern kaddr UFunctionToFunc;
    //Class: UProperty
    extern kaddr UPropertyToElementSize;
    extern kaddr UPropertyToPropertyFlags;
    extern kaddr UPropertyToOffsetInternal;
    //Class: UBoolProperty
    extern kaddr UBoolPropertyToFieldSize;
    extern kaddr UBoolPropertyToByteOffset;
    extern kaddr UBoolPropertyToByteMask;
    extern kaddr UBoolPropertyToFieldMask;
    //Class: UObjectProperty
    extern kaddr UObjectPropertyToPropertyClass;
    //Class: UClassProperty
    extern kaddr UClassPropertyToMetaClass;
    //Class: UInterfaceProperty
    extern kaddr UInterfacePropertyToInterfaceClass;
    //Class: UArrayProperty
    extern kaddr UArrayPropertyToInnerProperty;
    //Class: UMapProperty
    extern kaddr UMapPropertyToKeyProp;
    extern kaddr UMapPropertyToValueProp;
    //Class: USetProperty
    extern kaddr USetPropertyToElementProp;
    //Class: UStructProperty
    extern kaddr UStructPropertyToStruct;
    //Class: UWorld
    extern kaddr UWorldToPersistentLevel;
    //Class: ULevel
    extern kaddr ULevelToAActors;
    extern kaddr ULevelToAActorsCount;

    void initOffsets_32();
    void patchUE423_32();
}





