#pragma once
#define IOCTL_READ_MEM CTL_CODE(FILE_DEVICE_UNKNOWN, 0x903, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_WRITE_MEM CTL_CODE(FILE_DEVICE_UNKNOWN, 0x902, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_BASE_MEM CTL_CODE(FILE_DEVICE_UNKNOWN, 0x901, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DRIVER_NAME L"\\\\.\\612d112d"

#define ValidPointer( pointer ) ( pointer != NULL && (DWORD_PTR)pointer >= 0x10000 && (DWORD_PTR)pointer < 0x00007FFFFFFEFFFF /*&& some other checks*/ )


extern DWORD pID;
bool readRaw(LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead);
uint64_t ImageBase();

DWORD FindProcessId(const std::string& processName);

kaddr getRealOffset(kaddr offset);
template<typename T>
T Read(kaddr address);

template<typename T>
string ReadStr(kaddr address, unsigned int size);
string ReadStr2(kaddr address, unsigned int size);
kaddr getPtr(kaddr address);
void HexDump(kaddr addr, int lines);
void HexDump1B(kaddr addr, int lines);
void HexDump4B(kaddr addr, int lines);
void HexDump8B(kaddr addr, int lines);

template<typename T>
T Read(kaddr address) {
    T data;
   if(ValidPointer(address))
    readRaw(reinterpret_cast<void*>(address), reinterpret_cast<void*>(&data), sizeof(T), 0);
    return data;
}

template<typename T>
T* ReadArr(kaddr address,unsigned int size) {
    T* data = new T[size];
    if (ValidPointer(address))
    readRaw(reinterpret_cast<void*>(address), reinterpret_cast<void*>(data), (sizeof(T) * size), 0);
    return data;
}
