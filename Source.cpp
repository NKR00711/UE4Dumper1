#pragma warning(disable : 4996)
#include "includes.h"
void findGnames() {

    std::ofstream myfile;
    myfile.open("Gname.txt");
    for (size_t i = 0x6000000; i < 0x6f00000; i += 8) {

        auto chunkOffset = (uint32_t)((int)(0) >> 16);
        auto nameOffset = (uint16_t)0 & 65535;

        auto namePoolChunk = getPtr(getRealOffset(i) + ((chunkOffset + 2) * 8));
        auto entryOffset = namePoolChunk + (ULONG)(2 * nameOffset);
        auto nameEntry = Read<INT16>(entryOffset);

        auto StrLength = nameEntry >> 6;

        if (StrLength > 0 && StrLength < 5)
        {
            string name(StrLength, '\0');
            readRaw((void*)(entryOffset + 0x2), (void*)name.data(), StrLength * sizeof(char), 0);
            name.shrink_to_fit();

            if (strstr(name.c_str(), "None") && (strlen(name.c_str()) < 5)) {

                printf("\nGname Offsets: 0x%lX  vTable: 0x%lX\n", i, 0);
                myfile << "0x" << std::hex << i << "  " << "0x" << std::hex << 0x110 << "\n";

            }
        }
    }
    myfile.close();
}
void findgworld() {
    //SolarWorldSettings
    //DefaultPhysicsVolume
    std::ofstream myfile;
    myfile.open("Gworld.txt");
    for (size_t i = 0x6000000; i < 0x6f00000; i += 8)
    {

        kaddr gworld = getPtr(getRealOffset(i));
        kaddr level = getPtr(gworld + Offsets::UWorldToPersistentLevel);
        kaddr actorList = getPtr(level + Offsets::ULevelToAActors);
        kaddr actor = getPtr(actorList + (0 * Offsets::PointerSize));

        int entityStruct = Read<int>(actor + 0x18);
        auto chunkOffset = (uint32_t)((int)(entityStruct) >> 16);
        auto nameOffset = (uint16_t)entityStruct & 65535;

        auto namePoolChunk = getPtr(getRealOffset(Offsets::GNames) + ((chunkOffset + 2) * 8)); // <= put gname address
        auto entryOffset = namePoolChunk + (ULONG)(2 * nameOffset);
        auto nameEntry = Read<INT16>(entryOffset);

        auto StrLength = nameEntry >> 6;
        if (StrLength > 0 && StrLength < 19)
        {
            string name(StrLength, '\0');
            readRaw((void*)(entryOffset + 0x2), (void*)name.data(), StrLength * sizeof(char), 0);
            name.shrink_to_fit();
            if (strstr(name.c_str(), "WorldSettings")) {

                printf("\nGworld Offsets: 0x%lX  vTable: 0x%lX\n", i, 0);
                myfile << "0x" << std::hex << i << "  " << "0x" << std::hex << 0x0 << "\n";

            }
        }
    }
    myfile.close();
}
int main()
{
    Offsets::initOffsets_32();
    Offsets::patchUE423_32();
	Offsets::Base = 0x6;

	Offsets::GNames = 0x0;
	Offsets::GWorld = 0x0;
   
	 pID = FindProcessId("SolarlandClient-Win64-Shipping.exe");
     if (pID > 0)
     {
     re:
         system("cls");
         std::cout << "[+] Game PID " << std::hex << pID << std::endl;

         Offsets::Base = ImageBase();

         if (ValidPointer(Offsets::Base))
         {
             std::cout << "Dump Game Press [ 1 ]" << std::endl;
             std::cout << "Find Gname Press [ 2 ]" << std::endl;
             std::cout << "Find Gword Press [ 3 ]" << std::endl;

             int index = 0;
             std::cin >> index;
             if (index == 1)
             {
                 std::cout << "Input Gname Address" << std::endl;
                 DWORD_PTR GnameAddress;
                 std::cin >> std::hex >> GnameAddress;
                 Offsets::GNames = GnameAddress;
                 std::cout << "Input Gworld Address" << std::endl;
                 DWORD_PTR GworldAddress;
                 std::cin >> std::hex >> GworldAddress;
                 Offsets::GWorld = GworldAddress;
                 if (Offsets::Base != 0 && Offsets::GNames != 0 && Offsets::GWorld != 0)
                 {
                     DumpSDKW("");
                 }
                 else
                 {
                     std::cout << "Error Address" << std::endl;

                 }
                 std::cout << "Finshed" << std::endl;
             }
             else if (index == 2)
             {
                 findGnames();
             }
             else if (index == 3)
             {
                 std::cout << "Input Gname Address" << std::endl;
                 DWORD_PTR GnameAddress;
                 std::cin >> std::hex >> GnameAddress;
                 Offsets::GNames = GnameAddress;
                 findgworld();

             }
        
             std::cout << "Finshed" << std::endl;
             getchar();
             goto re;
         }
         else
         {
             std::cout << "Cant Find Base Address" << std::endl;
         }
	 }
     else
     {
         std::cout << "Error Can Not Find Game" << std::endl;
     }
	getchar();
	return 0;
}







