#include <iostream>
#include <iomanip>
#include "DES.hpp"

int main() {
    // サンプル平文と鍵
    uint64_t plaintext  = 0x0123456789ABCDEFULL;
    uint64_t masterKey  = 0x133457799BBCDFF1ULL;

    // DES オブジェクト生成
    des::DES des(masterKey);

    // 暗号化
    uint64_t ciphertext = des.encrypt(plaintext);
    std::cout << "Plaintext:  0x" << std::hex << std::uppercase << plaintext << std::endl;
    std::cout << "Ciphertext: 0x" << std::hex << std::uppercase << ciphertext << std::endl;

    // 復号化
    uint64_t recovered = des.decrypt(ciphertext);
    std::cout << "Recovered:  0x" << std::hex << std::uppercase << recovered << std::endl;

    return 0;
}