#include "BitUtils.hpp"

namespace des {
namespace BitUtils {

// 指定位置のビットを取得する（1始まりインデックス）
// getBit(0b1010, 2) => 0
uint8_t getBit(uint64_t data, int pos) {
    // pos=1 は最上位ビット (bit63)
    int shift = 64 - pos;
    return static_cast<uint8_t>((data >> shift) & 0x01);
}

//指定した位置のビットを設定する（1始まりインデックス）
// setBit(data, 2, 1) => dataの2番目のビットを1に設定
void setBit(uint64_t &data, int pos, uint8_t value) {
    int shift = 64 - pos;
    uint64_t mask = uint64_t(1) << shift;
    if (value) {
        data |= mask;
    } else {
        data &= ~mask; // ~ <= ビット反転
    }
}

} // namespace BitUtils
} // namespace des
