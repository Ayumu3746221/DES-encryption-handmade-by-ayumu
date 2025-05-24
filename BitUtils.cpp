#include "BitUtils.hpp"

namespace des {
namespace BitUtils {

uint8_t getBit(uint64_t data, int pos) {
    int shift = 64 - pos;
    return static_cast<uint8_t>((data >> shift) & 0x01);
}

void setBitOut(uint64_t &output, int idx, uint8_t value) {
    uint64_t mask = uint64_t(1) << idx;
    if (value) output |= mask;
    else output &= ~mask;
}

} // namespace BitUtils
} // namespace des
