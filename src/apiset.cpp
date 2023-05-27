#include <fstream>
#include <iostream>
#include <format>
#include <vector>
#include <stdint.h>

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

int main() {
    API_SET_NAMESPACE_HEADER_10 h;
    vector<API_SET_NAMESPACE_ENTRY_10> ents;

    // FIXME - mmap?

    ifstream f("/home/hellas/Desktop/apiset-22H2", ios::binary);

    // FIXME - use binutils to extract .apiset section
    // FIXME - solicit filename
    // FIXME - throw error if fails

    f.read((char*)&h, sizeof(h));

    cout << format("Version {:x}, Size {:x}, Flags {:x}, Count {:x}, ArrayOffset {:x}, HashOffset {:x}, HashMultiplier {:x}\n",
                   h.Version, h.Size, h.Flags, h.Count, h.ArrayOffset, h.HashOffset, h.HashMultiplier);

    // FIXME - skip to array offset

    ents.resize(h.Count);

    f.read((char*)ents.data(), ents.size() * sizeof(API_SET_NAMESPACE_ENTRY_10));

    for (const auto& e : ents) {
        cout << format("Flags {:x}, NameOffset {:x}, NameLength {:x}, AliasOffset {:x}, HostsOffset {:x}, NumberOfHosts {:x}\n",
                       e.Flags, e.NameOffset, e.NameLength, e.AliasOffset, e.HostsOffset, e.NumberOfHosts);
    }

    return 0;
}
