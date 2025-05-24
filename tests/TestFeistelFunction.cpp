#include <gtest/gtest.h>
#include "FeistelFunction.hpp"
#include "KeySchedule.hpp"
#include "BitUtils.hpp"

using namespace des;

// テストベクタ（FIPS PUB 46準拠）:
// マスターキー: 0x133457799BBCDFF1
// 初期R0: 0xF0AAF0AA
// サブキーK1: 0x1B02EFFC7072
// Feistel関数F(R0, K1) の結果: 0xE2DD53F0

TEST(FeistelTests, Round1Function) {
    uint32_t R0 = 0xF0AAF0AA;
    uint64_t K1 = 0x1B02EFFC7072ULL;

    uint32_t output = FeistelFunction::apply(R0, K1);
    EXPECT_EQ(output, 0x234AA9BB);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
