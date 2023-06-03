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

    // if (BitPacker::isLittleEndian()) {
    //     variable = swap(variable);
    // }

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
	template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
  static size_t encode(T variable, size_t startBit, size_t length, std::vector<std::byte>& buffer, bool littleEndian) {
    int byteIndex = startBit / 8;  // Index of the byte containing the start bit
    int bitIndex = startBit % 8;   // Bit position within the byte, with 0 being the left most bit

    // if (littleEndian) {
    //     variable = swap(variable);
    // }

    // Encode the value by shifting bits and performing bitwise OR operations
    for (int i = 0; i < length; i++) {
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
	static size_t decode(const std::vector<std::byte>& buffer, size_t startBit, size_t length, bool littleEndian);

private:

	static bool isLittleEndian();
	/**
	* Performs a byte swap on the provided value.
	* @param val - The value to be swapped.
	* @return - the provided value byte swapped
	*/
	static int16_t swap(int16_t val);

	/**
	* Performs a byte swap on the provided value.
	* @param val - The value to be swapped.
	* @return - the provided value byte swapped
	*/
	static int32_t swap(int32_t val);

	/**
	* Performs a byte swap on the provided value.
	* @param val - The value to be swapped.
	* @return - the provided value byte swapped
	*/
	static int64_t swap(int64_t val);

	/**
	* Performs a byte swap on the provided value.  Note, since this is swapping a float
	* it needs to be returned as an unsigned 32-bit integer to avoid the processor
	* interpreting the value as a float which will change the actual bits.
	* @param val - The value to be swapped.
	* @return - the provided value byte swapped
	*/
	static uint32_t swap(float val);

	/**
	* Performs a byte swap on the provided value.  Note, since this is swapping a double
	* it needs to be returned as an unsigned 64-bit integer to avoid the processor
	* interpreting the value as a double which will change the actual bits.
	* @param val - The value to be swapped.
	* @return - the provided value byte swapped
	*/
	static uint64_t swap(double val);

	/**
	* Performs a byte swap on the provided value.
	* @param val - The value to be swapped.
	* @return - the provided value byte swapped
	*/
	static uint16_t swap(uint16_t val);

	/**
	* Performs a byte swap on the provided value.
	* @param val - The value to be swapped.
	* @return - the provided value byte swapped
	*/
	static uint32_t swap(uint32_t val);

	/**
	* Performs a byte swap on the provided value.
	* @param val - The value to be swapped.
	* @return - the provided value byte swapped
	*/
	static uint64_t swap(uint64_t val);
};
