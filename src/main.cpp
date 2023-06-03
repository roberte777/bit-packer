#include <cstddef>
#include <iostream>
#include <ostream>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <BitPacker.h>


int main() {
  std::vector<std::byte> byteVector;
  int n = 1;
  // little endian if true
  if (*(char*)&n == 1) { 
      std::cout << "This machine is little endian" << std::endl;
  } else {
    std::cout << "This machine is Big Endian" << std::endl;
  }

  // First test: Just encode and decode 1, bytes from this uint16
  //0000111111111111
  uint16_t full = 4095;
  // vector has 40 bits
  std::vector<std::byte> testVector(5);
  BitPacker::encode(full, 0, 12, testVector);
  size_t basicTestValue = BitPacker::decode(testVector, 0, 12);
  std::cout << "This is the basic test value: " << basicTestValue << std::endl;

  //next, I want to put a few bits at a random spot, then decode from that
  BitPacker::encode(full, 24, 3, testVector);
  //expected value is 001110 or 14
  auto randomEncodingDecoding = BitPacker::decode(testVector, 22, 6);
  std::cout << "This is endoding and decoding from semi random spots: " << randomEncodingDecoding << std::endl;

  // vector has 56 bits
  std::vector<std::byte> largerVector(7);
  //next, I want to encode and decode across bytes
  BitPacker::encode(full, 38, 8, largerVector);
  //expected value is 001111111100 or 1020
  auto acrossBytes = BitPacker::decode(largerVector, 36, 12);
  std::cout << "This is endoding and decoding across bytes: " << acrossBytes << std::endl;


  return 0;
}
