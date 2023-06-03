#include <vector>
#include "BitPacker.h"
#include <cstddef>
#include <cstring>

size_t BitPacker::decode(const std::vector<std::byte>& buffer, size_t startBit, size_t length) {
    unsigned int value = 0;
    int byteIndex = startBit / 8;  // Index of the byte containing the start bit
    int bitIndex = startBit % 8;   // Bit position within the byte, assuming the left most bit is idx 0

    // handle case where the length is greater than the number of bits remaining in the buffer
    // this also handles the case where the startBit is greater than the buffer size
    if (length > buffer.size() * 8 - startBit) {
      return 0;
    }


    // Extract the value by shifting bits and performing bitwise OR operations
    for (int i = length - 1; i >= 0; i--) {
        value |= (static_cast<unsigned int>(buffer[byteIndex]) >> (7 - bitIndex) & 1) << i;

        // Move to the next bit
        if (++bitIndex == 8) {
            bitIndex = 0;
            byteIndex++;
        }
    }

    return value;
}
