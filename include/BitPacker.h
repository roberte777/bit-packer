#pragma once
#include <type_traits>
#include <cstdint>
#include <vector>
#include <cstddef>
#include <cstring>
class BitPacker {
public:

	template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
  static size_t encode(T variable, size_t startBit, size_t length, std::vector<std::byte>& buffer) {
    int byteIndex = startBit / 8;  // Index of the byte containing the start bit
    int bitIndex = startBit % 8;   // Bit position within the byte, with 0 being the left most bit

    // handle case where the length is greater than the number of bits remaining in the buffer
    // this also handles the case where the startBit is greater than the buffer size
    if (length > buffer.size() * 8 - startBit) {
      return 0;
    }

    //handle case where the length is greater than the bits in the variable
    if (length > sizeof(variable) * 8) {
      return 0;
    }

    // Encode the value by shifting bits and performing bitwise OR operations
    for (int i = 0; i < length; i++) {
        auto t = variable >> (length - i - 1);
        buffer[byteIndex] = buffer[byteIndex] | static_cast<std::byte>((((variable >> (length - i - 1)) & 0x01) << (7 - bitIndex)));

        // Move to the next bit
        if (++bitIndex == 8) {
            bitIndex = 0;
            byteIndex++;
        }
    }

    return length;
  }

	static size_t decode(const std::vector<std::byte>& buffer, size_t startBit, size_t length);

};
