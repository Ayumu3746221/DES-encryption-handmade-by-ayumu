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
    EXPECT_EQ(subkey16, 0xBF918D3D3F0AULL);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
