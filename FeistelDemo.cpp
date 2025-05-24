// FeistelDemo.cpp
#include <iostream>
#include <iomanip>
#include "FeistelFunction.hpp"
#include "KeySchedule.hpp"
#include "BitUtils.hpp"
#include "Tables.hpp"

int main() {
    // テストベクタの例: ラウンド1
    uint32_t R0 = 0xF0AAF0AA;
    uint64_t masterKey = 0x133457799BBCDFF1ULL;
    des::KeySchedule ks(masterKey);
    uint64_t K1 = ks.getSubkey(0);

    uint32_t f_out = des::FeistelFunction::apply(R0, K1);

    std::cout << "Feistel F(R0, K1) = 0x"
              << std::hex << std::uppercase << std::setw(8) << std::setfill('0')
              << f_out << std::endl;

    return 0;
}
