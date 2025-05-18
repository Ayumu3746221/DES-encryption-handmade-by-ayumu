#include <gtest/gtest.h>
#include "BitUtils.hpp"
#include "Tables.hpp"

using namespace des;

// Known test vector for IP:
// Input:  0x0123456789ABCDEF
// Expected after IP: 0xCC00CCFFF0AAF0AA (see DES spec examples)

TEST(PermutationTests, InitialPermutation) {
    uint64_t input = 0x0123456789ABCDEFULL;
    uint64_t expected = 0xCC00CCFFF0AAF0AAULL;

    // Apply initial permutation
    uint64_t output = BitUtils::applyPermutation<64>(input, IP);

    EXPECT_EQ(output, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
