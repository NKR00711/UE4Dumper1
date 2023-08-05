#include "includes.h"

uint32 MAX_SIZE = 100;
uint32 GNameLimit = 170000;

struct WideStr {
    static int is_surrogate(UTF16 uc) {
        return (uc - 0xd800u) < 2048u;
    }

    static int is_high_surrogate(UTF16 uc) {
        return (uc & 0xfffffc00) == 0xd800;
    }

    static int is_low_surrogate(UTF16 uc) {
        return (uc & 0xfffffc00) == 0xdc00;
    }

    static wchar_t surrogate_to_utf32(UTF16 high, UTF16 low) {
        return (high << 10) + low - 0x35fdc00;
    }

    static wchar_t* w_str(kaddr str, size_t len) {
        wchar_t* output = new wchar_t[len + 1];

        UTF16* source = ReadArr<UTF16>(str,  len);

        for (int i = 0; i < len; i++) {
            const UTF16 uc = source[i];
            if (!is_surrogate(uc)) {
                output[i] = uc;
            }
            else {
                if (is_high_surrogate(uc) && is_low_surrogate(source[i]))
                    output[i] = surrogate_to_utf32(uc, source[i]);
                else
                    output[i] = L'?';
            }
        }

        output[len] = L'\0';
        return output;
    }

    static string getString(kaddr StrPtr, int StrLength) {
        wstring str = w_str(StrPtr, StrLength);

        string result(MAX_SIZE, '\0');

        wcstombs((char*)result.data(), str.c_str(), MAX_SIZE);

        return result;
    }
};



std::string GetFNameFromID(uint32 key)
{
    auto chunkOffset = (uint32_t)((int)(key) >> 16);
    auto nameOffset = (uint16_t)key & 65535;

    auto namePoolChunk = getPtr(getRealOffset(Offsets::GNames) + ((chunkOffset + 2) * 8));
    auto entryOffset = namePoolChunk + (ULONG)(2 * nameOffset);
    auto nameEntry = Read<INT16>(entryOffset);

    auto nameLength = nameEntry >> 6;
    ///Unicode Dumping Not Supported Yet
    if (nameLength > 0 && nameLength < 250) {
        bool wide = nameEntry & 1;
        if (wide) {
            return WideStr::getString(entryOffset + 2, nameLength);
        }
        else {
            return ReadStr2(entryOffset + 2, nameLength);
        }
    }
    else {
        return "None";
    }
}
