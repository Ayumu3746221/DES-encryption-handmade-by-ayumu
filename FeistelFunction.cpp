#include "FeistelFunction.hpp"
#include "BitUtils.hpp"
#include "Tables.hpp"

namespace des {

    static uint64_t expand32to48(uint32_t half){
        uint64_t out = 0;
        // E は 1 ~ 32 の位置指定
        for (int i = 0; i < 48; i++)
        {
            int pos = E[i];
            // ビット位置は MSB = 1, LSB = 32 として half から直接取得
            uint8_t bit = (half >> (32 - pos)) & 0x01;
            // 出力は MSB 側から詰める（bit47 が i=0, bit0 が i = 47）
            out |= (uint64_t(bit) << (47 - i));
        }
        return out;
    }

    uint32_t FeistelFunction::apply(uint32_t halfBlock, uint64_t subkey) {
        using namespace BitUtils;

        // 1. E拡張： 32bit -> 48bit;
        uint64_t expanded = expand32to48(halfBlock);

        // 2. サブキーとXOR
        uint64_t xored = expanded ^ subkey;


        // 3. S-Box処理（8チャンク）
        uint32_t sOutput = 0;
        for (int i = 0; i < 8; i++)
        {
            // 上位6ビットからチャンクを抽出
            int shift = 42 - 6 * i;
            uint8_t chunk6 = (xored >> shift) & 0x3F;
            int row = ((chunk6 & 0x20) >> 4) | (chunk6 & 0x01);
            int col = (chunk6 >> 1) & 0x0F;
            uint8_t sVal = S_BOX[i][row][col];
            sOutput |= uint32_t(sVal) << (28 - 4 * i);
        }

        // 4. Pパーミュテーション: 32bit -> 32bit
        uint32_t permuted = 0;
        for (int i = 0; i < 32; ++i) {
            int pos = P[i];  // 1～32
            uint8_t bit = (sOutput >> (32 - pos)) & 0x01;
            permuted |= uint32_t(bit) << (31 - i);
        }

        return static_cast<uint32_t>(permuted & 0xFFFFFFFF);
    }
}