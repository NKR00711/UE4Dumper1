#pragma once

#include <string>
#include <ctime>
#include <Windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <tchar.h>
#include <fstream>
#include <vector>
#include <array>
#include <list>
// Unsigned base types.
typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

// Signed base types.
typedef signed char int8;
typedef signed short int int16;
typedef signed int int32;
typedef signed long long int64;
typedef unsigned short UTF16;
typedef unsigned __int64  uintptr_t;

typedef uint64_t kaddr;

using namespace std;

#include "memory.h"
#include "kmods.h"
#include "offsets.h"
#include "settings.h"
#include "FNames.h"
#include "StructsSDK.h"
#include "SDK.h"


