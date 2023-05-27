#include "apiset.h"
#include "mmap.h"
#include <iostream>
#include <format>
#include <vector>
#include <codecvt>
#include <stdint.h>
#include <fcntl.h>

struct API_SET_NAMESPACE_ENTRY_10 {
    uint32_t Flags;
    uint32_t NameOffset;
    uint32_t NameLength;
    uint32_t AliasOffset;
    uint32_t HostsOffset;
    uint32_t NumberOfHosts;
};

struct API_SET_NAMESPACE_HEADER_10 {
    uint32_t Version;
    uint32_t Size;
    uint32_t Flags;
    uint32_t Count;
    uint32_t ArrayOffset;
    uint32_t HashOffset;
    uint32_t HashMultiplier;
};

using namespace std;

static string utf16_to_utf8(u16string_view sv) {
    wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t> convert;

    return convert.to_bytes(sv.data(), sv.data() + sv.length());
}

int main() {
    try {
        unique_handle hup{open("/home/hellas/Desktop/apiset-22H2", O_RDONLY, 0)};
        if (hup.get() == -1)
            throw errno_error("open", errno);

        // FIXME - check size

        mmap m(hup.get());

        auto data = m.map();

        auto& h = *(API_SET_NAMESPACE_HEADER_10*)data.data();

        // FIXME - use binutils to extract .apiset section
        // FIXME - solicit filename
        // FIXME - throw error if fails

        cout << format("Version {:x}, Size {:x}, Flags {:x}, Count {:x}, ArrayOffset {:x}, HashOffset {:x}, HashMultiplier {:x}\n",
                       h.Version, h.Size, h.Flags, h.Count, h.ArrayOffset, h.HashOffset, h.HashMultiplier);

        auto ents = span((const API_SET_NAMESPACE_ENTRY_10*)(data.data() + h.ArrayOffset), h.Count);

        for (const auto& e : ents) {
            auto name = u16string_view((char16_t*)(data.data() + e.NameOffset), e.NameLength / sizeof(char16_t));

            cout << format("Flags {:x}, Name {}, AliasOffset {:x}, HostsOffset {:x}, NumberOfHosts {:x}\n",
                           e.Flags, utf16_to_utf8(name), e.AliasOffset, e.HostsOffset, e.NumberOfHosts);
        }
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
        return 1;
    }

    return 0;
}
