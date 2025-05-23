#include "KeyGenerator.hpp"
#include <random>
#include <bit>  // C++20 の std::popcount を使う場合

namespace des {

    uint8_t KeyGenerator::withParity(uint8_t sevenBits) {
        // 7bit の 1 の数をカウント
        int ones = __builtin_popcount(sevenBits & 0x7f);
        // DESでは「奇数パリティ」：全体で1の数が奇数になるようにする。
        uint8_t parity = (ones % 2 == 0) ? 1 : 0;
        // 上位 7bit を左シフトし LSB にパリティを入れる
        return static_cast<uint8_t>((sevenBits << 1) | parity);
    }

    uint64_t KeyGenerator::genarateMasterKey() {
        // 暗号用乱数生成器
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<uint8_t> dist(0, 0x7F); // 7bitの乱数

        uint64_t key = 0;
        for (int i = 0; i < 8; ++i)
        {
            uint8_t seven = dist(gen);          // 0~127の乱数
            uint8_t withP = withParity(seven);  // パリティ付与
            key = (key << 8) | withP;           // 8bitごとに連結
        }
        return key;
    }
} // namespace des