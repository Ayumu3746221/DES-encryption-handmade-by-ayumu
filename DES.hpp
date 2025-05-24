#pragma once
#include <cstdint>
#include "KeySchedule.hpp"

namespace des {

class DES {
public:
    /**
     * @brief コンストラクタ
     * @param key 64bitマスターキー（パリティ込）
     */
    explicit DES(uint64_t key);

    /**
     * @brief 64bit平文を暗号化
     * @param plaintext 平文
     * @return 64bit暗号文
     */
    uint64_t encrypt(uint64_t plaintext) const;

    /**
     * @brief 64bit暗号文を復号化
     * @param ciphertext 暗号文
     * @return 64bit復号平文
     */
    uint64_t decrypt(uint64_t ciphertext) const;

private:
    // 初期・逆初期置換
    static uint64_t initialPermute(uint64_t block);
    static uint64_t finalPermute(uint64_t block);

    // 16ラウンドのFeistel処理
    uint64_t feistelRounds(uint64_t block, bool encrypt) const;
    KeySchedule keySchedule_;
};

} // namespace des