#include <vector>
#include "BitPacker.h"
int16_t BitPacker::swap(int16_t val)
{
    return static_cast<int16_t>(((val & 0x00FF) << 8) |
        ((val & 0xFF00) >> 8));
}

int32_t BitPacker::swap(int32_t val)
{
    return static_cast<int32_t>(((static_cast<uint32_t>(val) & 0x000000FF) << 24) |
        ((static_cast<uint32_t>(val) & 0x0000FF00) << 8) |
        ((static_cast<uint32_t>(val) & 0x00FF0000) >> 8) |
        ((static_cast<uint32_t>(val) & 0xFF000000) >> 24));
}

int64_t BitPacker::swap(int64_t val)
{
    int32_t* i = reinterpret_cast<int32_t*>(&val);
    int32_t temp = swap(i[0]);
    i[0] = swap(i[1]);
    i[1] = temp;
    return val;
}

uint16_t BitPacker::swap(uint16_t val)
{
    return static_cast<uint16_t>(((val & 0x00FF) << 8) |
        ((val & 0xFF00) >> 8));
}

uint32_t BitPacker::swap(uint32_t val)
{
    return ((val & 0x000000FF) << 24) |
        ((val & 0x0000FF00) << 8) |
        ((val & 0x00FF0000) >> 8) |
        ((val & 0xFF000000) >> 24);
}

uint64_t BitPacker::swap(uint64_t val)
{
    uint32_t* i = reinterpret_cast<uint32_t*>(&val);
    uint32_t temp = swap(i[0]);
    i[0] = swap(i[1]);
    i[1] = temp;
    return val;
}

uint32_t BitPacker::swap(float val)
{
    uint32_t* i = reinterpret_cast<uint32_t*>(&val);
    i[0] = swap(i[0]);
    uint32_t result;
    memcpy(&result, i, sizeof(result));
    return result;
}

uint64_t BitPacker::swap(double val)
{
    uint32_t* i = reinterpret_cast<uint32_t*>(&val);
    uint32_t temp = swap(i[0]);
    i[0] = swap(i[1]);
    i[1] = temp;
    uint64_t result;
    memcpy(&result, i, sizeof(result));
    return result;
}
bool BitPacker::isLittleEndian()
{
    static const uint32_t test_value{0x44332211};
    return (reinterpret_cast<const char*>(&test_value)[0] == 0x11) &&
        (reinterpret_cast<const char*>(&test_value)[1] == 0x22);
}

size_t BitPacker::decode(const std::vector<std::byte>& buffer, size_t startBit, size_t length) {
    unsigned int value = 0;
    int byteIndex = startBit / 8;  // Index of the byte containing the start bit
    int bitIndex = startBit % 8;   // Bit position within the byte, assuming the left most bit is idx 0

    // Extract the value by shifting bits and performing bitwise OR operations
    for (int i = length - 1; i >= 0; i--) {
        value |= (static_cast<unsigned int>(buffer[byteIndex]) >> (7 - bitIndex) & 1) << i;

        // Move to the next bit
        if (++bitIndex == 8) {
            bitIndex = 0;
            byteIndex++;
        }
    }

    // if (BitPacker::isLittleEndian()) {
    //     value = swap(value);
    // }

    return value;
}
size_t BitPacker::decode(const std::vector<std::byte>& buffer, size_t startBit, size_t length, bool littleEndian) {
    unsigned int value = 0;
    int byteIndex = startBit / 8;  // Index of the byte containing the start bit
    int bitIndex = startBit % 8;   // Bit position within the byte, assuming the left most bit is idx 0

    // Extract the value by shifting bits and performing bitwise OR operations
    for (int i = length - 1; i >= 0; i--) {
        value |= (static_cast<unsigned int>(buffer[byteIndex]) >> (7 - bitIndex) & 1) << i;

        // Move to the next bit
        if (++bitIndex == 8) {
            bitIndex = 0;
            byteIndex++;
        }
    }

    // if (littleEndian) {
    //     value = swap(value);
    // }

    return value;
}

