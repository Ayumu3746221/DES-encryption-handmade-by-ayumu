#include "DES.hpp"
#include "BitUtils.hpp"
#include "Tables.hpp"
#include "KeySchedule.hpp"
#include "FeistelFunction.hpp"

namespace des {

uint64_t DES::initialPermute(uint64_t block) {
    return BitUtils::applyPermutation<64>(block, IP);
}

uint64_t DES::finalPermute(uint64_t block) {
    return BitUtils::applyPermutation<64>(block, IP_INV);
}

uint64_t DES::feistelRounds(uint64_t block, bool encrypt) const{
    // 分割
    uint32_t L = uint32_t(block >> 32);
    uint32_t R = uint32_t(block & 0xFFFFFFFFULL);

    // 16ラウンド
    for (int i = 0; i < 16; ++i) {
        int idx = encrypt ? i : (15 - i);
        uint32_t nextL = R;
        uint32_t f = FeistelFunction::apply(R, keySchedule_.getSubkey(idx));
        R = L ^ f;
        L = nextL;
    }

    // 最終入れ替え用にR||L
    return (uint64_t(R) << 32) | L;
}

DES::DES(uint64_t key)
    : keySchedule_(key)
{}

uint64_t DES::encrypt(uint64_t plaintext) const {
    uint64_t ip = initialPermute(plaintext);
    uint64_t fe = feistelRounds(ip, true);
    return finalPermute(fe);
}

uint64_t DES::decrypt(uint64_t ciphertext) const {
    uint64_t ip = initialPermute(ciphertext);
    uint64_t fe = feistelRounds(ip, false);
    return finalPermute(fe);
}

} // namespace des