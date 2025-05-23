#pragma once
#include <cstdint>

namespace des {

    class KeyGenerator
    {
    public:
        /**
         * @brief 56bit 乱数から 8bit パリティを付与し、DES用 64bit マスターキーを生成
         */
        static uint64_t generateMasterKey();
    private:
        /**
         * @brief 7bit 値に対し「奇数パリティ」を持つ 8bit 値に変換
         * @param sevenBits 下位 7bitを使う
         * @return 8bit 値(上位 7bit は入力、LSBはパリティビット)
         */
        static uint8_t withParity(uint8_t sevenBits);
    };
} // namespace des