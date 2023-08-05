#include "includes.h"

string resolveProp423(list<kaddr>& recurrce, kaddr prop) {
    if (prop) {
        string cname = FField::getClassName(prop);

        if (isEqual(cname, "ObjectProperty") || isEqual(cname, "WeakObjectProperty")
            || isEqual(cname, "LazyObjectProperty") || isEqual(cname, "AssetObjectProperty")
            || isEqual(cname, "SoftObjectProperty")) {
            kaddr propertyClass = UObjectProperty::getPropertyClass(prop);
            recurrce.push_back(propertyClass);
            return UObject::getName(propertyClass) + "*";
        }
        else if (isEqual(cname, "ClassProperty") || isEqual(cname, "AssetClassProperty") ||
            isEqual(cname, "SoftClassProperty")) {
            kaddr metaClass = UClassProperty::getMetaClass(prop);
            recurrce.push_back(metaClass);
            return "class " + UObject::getName(metaClass);
        }
        else if (isEqual(cname, "InterfaceProperty")) {
            kaddr interfaceClass = UInterfaceProperty::getInterfaceClass(prop);
            recurrce.push_back(interfaceClass);
            return "interface class" + UObject::getName(interfaceClass);
        }
        else if (isEqual(cname, "StructProperty")) {
            kaddr Struct = UStructProperty::getStruct(prop);
            recurrce.push_back(Struct);
            return UObject::getName(Struct);
        }
        else if (isEqual(cname, "ArrayProperty")) {
            return resolveProp423(recurrce, UArrayProperty::getInner(prop)) + "[]";
        }
        else if (isEqual(cname, "SetProperty")) {
            return "<" + resolveProp423(recurrce, USetProperty::getElementProp(prop)) + ">";
        }
        else if (isEqual(cname, "MapProperty")) {
            return "<" + resolveProp423(recurrce, UMapProperty::getKeyProp(prop)) + "," +
                resolveProp423(recurrce, UMapProperty::getValueProp(prop)) + ">";
        }
        else if (isEqual(cname, "BoolProperty")) {
            return "bool";
        }
        else if (isEqual(cname, "ByteProperty")) {
            return "byte";
        }
        else if (isEqual(cname, "IntProperty")) {
            return "int";
        }
        else if (isEqual(cname, "Int8Property")) {
            return "int8";
        }
        else if (isEqual(cname, "Int16Property")) {
            return "int16";
        }
        else if (isEqual(cname, "Int64Property")) {
            return "int64";
        }
        else if (isEqual(cname, "UInt16Property")) {
            return "uint16";
        }
        else if (isEqual(cname, "UInt32Property")) {
            return "uint32";
        }
        else if (isEqual(cname, "UInt64Property")) {
            return "uint64";
        }
        else if (isEqual(cname, "DoubleProperty")) {
            return "double";
        }
        else if (isEqual(cname, "FloatProperty")) {
            return "float";
        }
        else if (isEqual(cname, "EnumProperty")) {
            return "enum";
        }
        else if (isEqual(cname, "StrProperty")) {
            return "FString";
        }
        else if (isEqual(cname, "TextProperty")) {
            return "FText";
        }
        else if (isEqual(cname, "NameProperty")) {
            return "FName";
        }
        else if (isEqual(cname, "DelegateProperty") ||
            isEqual(cname, "MulticastDelegateProperty")||
            isEqual(cname, "MulticastSparseDelegateProperty")) {
            return "delegate";
        }
        else {
            return FField::getName(prop) + "(" + cname + ")";
        }
    }
    return "NULL";
}

//---------------------------------------------------------------------------------------------------------------------------//

uint32 classCount = 0;

vector<uint32> structIDMap;

bool isScanned(uint32 id) {
    for (int i = 0; i < structIDMap.size(); i++) {
        if (structIDMap[i] == id) { return true; }
    }
    return false;
}


list<kaddr> writeStructChild423(ofstream& sdk, kaddr childprop) {
    list<kaddr> recurrce;
    kaddr child = childprop;
    while (child) {
        kaddr prop = child;
        string oname = FField::getName(prop);
        string cname = FField::getClassName(prop);

        if (isEqual(cname, "ObjectProperty") || isEqual(cname, "WeakObjectProperty") ||
            isEqual(cname, "LazyObjectProperty") || isEqual(cname, "AssetObjectProperty") ||
            isEqual(cname, "SoftObjectProperty")) {
            kaddr propertyClass = UObjectProperty::getPropertyClass(prop);

            sdk << "\t" << UObject::getName(propertyClass) << "* " << oname << ";"
                << "//[Offset: 0x" << setbase(16) << UProperty::getOffset(prop) << ", "
                << "Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;

            recurrce.push_back(propertyClass);
        }
        else if (isEqual(cname, "ClassProperty") || isEqual(cname, "AssetClassProperty") ||
            isEqual(cname, "SoftClassProperty")) {
            kaddr metaClass = UClassProperty::getMetaClass(prop);

            sdk << "\tclass " << UObject::getName(metaClass) << "* " << oname << ";"
                << "//[Offset: 0x" << setbase(16) << UProperty::getOffset(prop) << ", "
                << "Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;

            recurrce.push_back(metaClass);
        }
        else if (isEqual(cname, "InterfaceProperty")) {
            kaddr interfaceClass = UInterfaceProperty::getInterfaceClass(prop);

            sdk << "\tinterface class " << UObject::getName(interfaceClass) << "* " << oname << ";"
                << "//[Offset: 0x" << setbase(16) << UProperty::getOffset(prop) << ", "
                << "Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;
        }
        else if (isEqual(cname, "StructProperty")) {
            kaddr Struct = UStructProperty::getStruct(prop);

            sdk << "\t" << UObject::getName(Struct) << " " << oname << ";"
                << "//[Offset: 0x" << setbase(16) << UProperty::getOffset(prop) << ", "
                << "Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;

            recurrce.push_back(Struct);
        }
        else if (isEqual(cname, "ArrayProperty")) {
            sdk << "\t" << resolveProp423(recurrce, UArrayProperty::getInner(prop)) << "[] "
                << oname << ";"
                << "//[Offset: 0x" << setbase(16) << UProperty::getOffset(prop) << ", "
                << "Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;
        }
        else if (isEqual(cname, "SetProperty")) {
            sdk << "\t<" << resolveProp423(recurrce, USetProperty::getElementProp(prop)) << "> "
                << oname << ";"
                << "//[Offset: 0x" << setbase(16) << UProperty::getOffset(prop) << ", "
                << "Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;
        }
        else if (isEqual(cname, "MapProperty")) {
            sdk << "\t<" << resolveProp423(recurrce, UMapProperty::getKeyProp(prop)) << ","
                << resolveProp423(recurrce, UMapProperty::getValueProp(prop)) << "> " << oname
                << ";"
                << "//[Offset: 0x" << setbase(16) << UProperty::getOffset(prop) << ", "
                << "Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;
        }
        else if (isEqual(cname, "BoolProperty")) {
            sdk << "\tbool " << oname << ";"
                << setbase(10) << "//(ByteOffset: " << (int)UBoolProperty::getByteOffset(prop)
                << ", ByteMask: " << (int)UBoolProperty::getByteMask(prop)
                << ", FieldMask: " << (int)UBoolProperty::getFieldMask(prop) << ")"
                << "[Offset: 0x" << setbase(16) << UProperty::getOffset(prop) << ", "
                << "Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;
        }
        else if (isEqual(cname, "ByteProperty")) {
            sdk << "\tbyte " << oname << ";"
                << "//[Offset: 0x" << setbase(16) << UProperty::getOffset(prop) << ", "
                << "Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;
        }
        else if (isEqual(cname, "IntProperty")) {
            sdk << "\tint " << oname << ";"
                << "//[Offset: 0x" << setbase(16) << UProperty::getOffset(prop) << ", "
                << "Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;
        }
        else if (isEqual(cname, "Int8Property")) {
            sdk << "\tint8 " << oname << ";"
                << "//[Offset: 0x" << setbase(16) << UProperty::getOffset(prop) << ", "
                << "Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;
        }
        else if (isEqual(cname, "Int16Property")) {
            sdk << "\tint16 " << oname << ";"
                << "//[Offset: 0x" << setbase(16) << UProperty::getOffset(prop) << ", "
                << "Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;
        }
        else if (isEqual(cname, "Int64Property")) {
            sdk << "\tint64 " << oname << ";"
                << "//[Offset: 0x" << setbase(16) << UProperty::getOffset(prop) << ", "
                << "Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;
        }
        else if (isEqual(cname, "UInt16Property")) {
            sdk << "\tuint16 " << oname << ";"
                << "//[Offset: 0x" << setbase(16) << UProperty::getOffset(prop) << ", "
                << "Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;
        }
        else if (isEqual(cname, "UInt32Property")) {
            sdk << "\tuint32 " << oname << ";"
                << "//[Offset: 0x" << setbase(16) << UProperty::getOffset(prop) << ", "
                << "Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;
        }
        else if (isEqual(cname, "UInt64Property")) {
            sdk << "\tuint64 " << oname << ";"
                << "//[Offset: 0x" << setbase(16) << UProperty::getOffset(prop) << ", "
                << "Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;
        }
        else if (isEqual(cname, "DoubleProperty")) {
            sdk << "\tdouble " << oname << ";"
                << "//[Offset: 0x" << setbase(16) << UProperty::getOffset(prop) << ", "
                << "Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;
        }
        else if (isEqual(cname, "FloatProperty")) {
            sdk << "\tfloat " << oname << ";"
                << "//[Offset: 0x" << setbase(16) << UProperty::getOffset(prop) << ", "
                << "Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;
        }
        else if (isEqual(cname, "EnumProperty")) {
            sdk << "\tenum " << oname << ";"
                << "//[Offset: 0x" << setbase(16) << UProperty::getOffset(prop) << ", "
                << "Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;
        }
        else if (isEqual(cname, "StrProperty")) {
            sdk << "\tFString " << oname << ";"
                << "//[Offset: 0x" << setbase(16) << UProperty::getOffset(prop) << ", "
                << "Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;
        }
        else if (isEqual(cname, "TextProperty")) {
            sdk << "\tFText " << oname << ";"
                << "//[Offset: 0x" << setbase(16) << UProperty::getOffset(prop) << ", "
                << "Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;
        }
        else if (isEqual(cname, "NameProperty")) {
            sdk << "\tFName " << oname << ";"
                << "//[Offset: 0x" << setbase(16) << UProperty::getOffset(prop) << ", "
                << "Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;
        }
        else if (isEqual(cname, "DelegateProperty") ||
            isEqual(cname, "MulticastDelegateProperty")||
            isEqual(cname, "MulticastSparseDelegateProperty")) {
            sdk << "\tdelegate " << oname << ";"
                << "//[Offset: 0x" << setbase(16) << UProperty::getOffset(prop) << ", "
                << "Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;
        }
        else {
            sdk << "\t" << cname << " " << oname << ";"
                << "//[Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;
        }

        child = FField::getNext(child);
    }
    return recurrce;
}

list<kaddr> writeStructChild423_Func(ofstream& sdk, kaddr childprop) {
    list<kaddr> recurrce;
    kaddr child = childprop;
    while (child) {
        kaddr prop = child;
        string oname = UObject::getName(prop);
        string cname = UObject::getClassName(prop);

        if (isStartWith(cname, "Function") || isEqual(cname, "DelegateFunction")) {
            string returnVal = "void";
            string params = "";

            kaddr funcParam = UStruct::getChildProperties(prop);
            while (funcParam) {
                uint64 PropertyFlags = UProperty::getPropertyFlags(funcParam);

                if ((PropertyFlags & 0x0000000000000400) == 0x0000000000000400) {
                    returnVal = resolveProp423(recurrce, funcParam);
                }
                else {
                    if ((PropertyFlags & 0x0000000000000100) == 0x0000000000000100) {
                        params += "out ";
                    }
                    /*if((PropertyFlags & 0x0000000008000000) == 0x0000000008000000){
                        params += "ref ";
                    }*/
                    if ((PropertyFlags & 0x0000000000000002) == 0x0000000000000002) {
                        params += "const ";
                    }
                    params += resolveProp423(recurrce, funcParam);
                    params += " ";
                    params += FField::getName(funcParam);
                    params += ", ";
                }

                funcParam = FField::getNext(funcParam);
            }

            if (!params.empty()) {
                params.pop_back();
                params.pop_back();
            }

            sdk << "\t";

            int32 FunctionFlags = UFunction::getFunctionFlags(prop);

            if ((FunctionFlags & 0x00002000) == 0x00002000) {
                sdk << "static" << " ";
            }
            /*if((FunctionFlags & 0x00000001) == 0x00000001){
                sdk << "final" << " ";
            }
            if((FunctionFlags & 0x00020000) == 0x00020000){
                sdk << "public" << " ";
            }
            if((FunctionFlags & 0x00040000) == 0x00040000){
                sdk << "private" << " ";
            }
            if((FunctionFlags & 0x00080000) == 0x00080000){
                sdk << "protected" << " ";
            }*/

            sdk << returnVal << " " << oname << "(" << params << ");"
                << "// 0x" << setbase(16) << (UFunction::getFunc(prop) - Offsets::Base) << endl;
        }
        else {
            sdk << "\t" << cname << " " << oname << ";"
                << "//[Size: " << setbase(10) << UProperty::getElementSize(prop) << "]" << endl;
        }

        child = UField::getNext(child);
    }
    return recurrce;
}

void writeStruct(ofstream& sdk, kaddr clazz) {
    list<kaddr> recurrce;

    kaddr currStruct = clazz;
    while (UStruct::isValid(currStruct)) {
        string name = UObject::getName(currStruct);
        if (isEqual(name, "None") || isContain(name, "_png") || name.empty()) {
            break;
        }

        uint32 NameID = UObject::getNameID(currStruct);
        if (!isScanned(NameID)) {
            //Verbose Output
            if (Settings::isVerbose) {
                cout << "Name: " << name << endl;
                cout << "Class: " << UStruct::getStructClassPath(currStruct) << endl;
                cout << endl;
            }

            //Dumping
            structIDMap.push_back(NameID);
            sdk << "Class: " << UStruct::getStructClassPath(currStruct) << endl;
            recurrce.merge(writeStructChild423(sdk, UStruct::getChildProperties(currStruct)));
            recurrce.merge(writeStructChild423_Func(sdk, UStruct::getChildren(currStruct)));

            sdk << "\n--------------------------------" << endl;
            classCount++;
        }

        currStruct = UStruct::getSuperClass(currStruct);
    }

    for (auto it = recurrce.begin(); it != recurrce.end(); ++it)
        writeStruct(sdk, *it);
}



void DumpSDKW(string out) {
    ofstream sdk(out + "SDK.txt", ofstream::out);
    if (sdk.is_open()) {
        cout << "Dumping SDK List" << endl;
        clock_t begin = clock();
        kaddr gworld =getPtr(getRealOffset(Offsets::GWorld));
        cout << "UWorld: " << setbase(16) << gworld << setbase(10) << " | Name: "
            << UObject::getName(gworld) << endl;
        if (UObject::isValid(gworld)) {
            //Iterate World
            writeStruct(sdk, UObject::getClass(gworld));
            //Iterate Entities
            kaddr level = getPtr(gworld + Offsets::UWorldToPersistentLevel);
            kaddr actorList = getPtr(level + Offsets::ULevelToAActors);
            int actorsCount = Read<int>(level + Offsets::ULevelToAActorsCount);
            for (int i = 0; i < actorsCount; i++) {
                kaddr actor = getPtr(actorList + (i * Offsets::PointerSize));
                if (UObject::isValid(actor)) {
                    writeStruct(sdk, UObject::getClass(actor));
                }
            }
        }
        sdk.close();
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        cout << classCount << " Items Dumped in SDK in " << elapsed_secs << "S" << endl;
    }
}



