#include <catch2/catch_test_macros.hpp>
#include <BitPacker.h>

// Your test cases here
TEST_CASE("Generic encode and decode", "[tag]") {
  // encode several different data types
  //0000111111111111
  uint16_t full = 4095;
  char c = 'a';
  int8_t i = -7;

  // vector has 40 bits
  std::vector<std::byte> testVector(5);
  BitPacker::encode(full, 0, 8, testVector);
  BitPacker::encode(c, 8, 8, testVector);
  BitPacker::encode(i, 16, 8, testVector);

  size_t basicTestValue = BitPacker::decode(testVector, 0, 8);
  char outC = static_cast<char>(BitPacker::decode(testVector, 8, 8));
  int8_t outI = static_cast<char>(BitPacker::decode(testVector, 16, 8));
  // Test assertions
  REQUIRE(basicTestValue == (full >> 4));
  REQUIRE(outC == c);
  REQUIRE(outI == i);
}

TEST_CASE("Encode and decode within byte", "[tag]") {
  // encode several different data types
  //0000111111111111
  uint16_t full = 4095;
  int8_t i = -7;

  // vector has 40 bits
  std::vector<std::byte> testVector(2);
  BitPacker::encode(full, 0, 3, testVector);
  BitPacker::encode(i, 3, 8, testVector);

  size_t basicTestValue = BitPacker::decode(testVector, 0, 3);
  int8_t outI = static_cast<char>(BitPacker::decode(testVector, 3, 8));
  // Test assertions
  REQUIRE(basicTestValue == 7);
  REQUIRE(outI == i);
}
TEST_CASE("Encode and decode across bytes", "[tag]") {
  // encode several different data types
  //0000111111111111
  uint16_t full = 4095;
  char c = 'a';
  int8_t i = -15;

  // vector has 40 bits
  std::vector<std::byte> testVector(5);
  BitPacker::encode(full, 0, 12, testVector);
  BitPacker::encode(c, 12, 8, testVector);
  BitPacker::encode(i, 20, 8, testVector);

  size_t basicTestValue = BitPacker::decode(testVector, 0, 12);
  char outC = static_cast<char>(BitPacker::decode(testVector, 12, 8));
  int8_t outI = static_cast<char>(BitPacker::decode(testVector, 20, 8));
  // Test assertions
  REQUIRE(basicTestValue == full);
  REQUIRE(outC == c);
  REQUIRE(outI == i);
}
TEST_CASE("Encode and decode values larger than 16 bits", "[BitPacker]"){
  int32_t full = 33554431;

  std::vector<std::byte> testVector(5);
  BitPacker::encode(full, 0, 25, testVector);

  size_t basicTestValue = BitPacker::decode(testVector, 0, 25);

  REQUIRE(basicTestValue == full);
}
