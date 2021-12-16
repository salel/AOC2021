#include <iostream>
#include <vector>

using namespace std;

struct packet {
    int version;
    int id;
    long number;
    bool lengthid;
    int length;
    int bit_size;
    vector<packet> sub_packets;
};

int count_version(const packet p) {
    int c = p.version;
    for (const auto a : p.sub_packets) c += count_version(a);
    return c;
}

packet parse(const vector<bool> bits, int& cursor) {
    int old_cursor = cursor;
    auto extract_bits = [&](int size) {
        int a = 0;
        for (int i=size-1;i>=0;i--) {
            a = (a | (bits[cursor]<<i));
            cursor++;
        }
        return a;
    };

    packet p;
    p.version = extract_bits(3);
    p.id = extract_bits(3);

    if (p.id == 4) {
        long number = 0;
        while (true) {
            number = number << 4;
            int cont = extract_bits(1);
            number = (number | extract_bits(4));
            if (!cont) break;
        }
        p.number = number;
    } else {
        p.lengthid = extract_bits(1);
        if (p.lengthid) {
            p.length = extract_bits(11);
            for (int i=0;i<p.length;i++) {
                p.sub_packets.push_back(parse(bits, cursor));
            }
        } else {
            p.length = extract_bits(15);
            int current_length = cursor;
            while (true) {
                p.sub_packets.push_back(parse(bits, cursor));
                if (cursor - current_length == p.length) break;
            }
        }
    }
    p.bit_size = cursor-old_cursor;
    return p;
}

int main() {

    vector<bool> bits;

    while (true) {
        int c = cin.get();
        if (c == '\r' || c == '\n') break;
        if (c >= 'A') c = (c-'A'+10);
        else c = c-'0';

        for (int i=0b1000;i!=0;i=i>>1) bits.push_back(c&i);
    }

    int cursor = 0;
    auto p = parse(bits, cursor);

    cout << count_version(p) << endl;
    
}