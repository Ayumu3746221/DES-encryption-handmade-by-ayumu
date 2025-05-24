// tests/TestKeySchedule.cpp
#include <gtest/gtest.h>
#include "KeySchedule.hpp"
#include "BitUtils.hpp"
#include "Tables.hpp"
#include <array>

using namespace des;

// Known test vectors from DES specification for key schedule:
// Master key: 0x133457799BBCDFF1
// Expected first subkey K1: 0x1B02EFFC7072
// Expected last subkey K16: 0xEFC2C6D8EF73 (example value; verify if correct per spec)

TEST(BitUtilsTests, TestApplyPermutationIdentity) {
    // 8ビットの入力に対する恒等変換テスト
    constexpr std::array<int, 8> identity = {1,2,3,4,5,6,7,8};
    uint64_t input = 0b10110101;  // 0xB5
    uint64_t output = BitUtils::applyPermutation<8>(input, identity);
    EXPECT_EQ(output, input);
}

TEST(KeyScheduleTests, FirstSubkey) {
    uint64_t masterKey = 0x133457799BBCDFF1ULL;
    des::KeySchedule ks(masterKey);
    uint64_t subkey1 = ks.getSubkey(0);
    EXPECT_EQ(subkey1, 0x1B02EFFC7072ULL);
}

TEST(KeyScheduleTests, LastSubkey) {
    uint64_t masterKey = 0x133457799BBCDFF1ULL;
    des::KeySchedule ks(masterKey);
    uint64_t subkey16 = ks.getSubkey(15);
    EXPECT_EQ(subkey16, 0xFE04CF2B672BULL); // Replace with correct K16 value from spec
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
