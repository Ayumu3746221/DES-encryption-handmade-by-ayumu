#pragma once
#include <cstdint>

namespace des {
    class FeistelFunction
    {
    public:
        /**
         * @brief Feistel関数 F
         * @param right 右側の32ビットブロック
         * @param subkey 48ビットのサブキー
         * @return 32ビットの出力
         */
        static uint32_t apply(uint32_t halfBlock, uint64_t subkey);
    };
} // namespace des