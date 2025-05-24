#pragma once
#include <array>
#include <cstdint>
namespace des {

    class KeySchedule
    {
    public:
        /**
         * @brief コンストラクタ
         * @param key 64ビットのマスターキー（パリティビット含む）
         */
        explicit KeySchedule(uint64_t key);

        /**
         * @brief 指定ラウンドの48ビットサブキーを取得
         * @param round 0~15
         * @return 48ビットサブキー（下位ビットに格納）
        */
       uint64_t getSubkey(int round) const;


    private:
        std::array<uint64_t, 16> subkeys_; // 各ラウンドの48ビットキー
        void generateSubkeys(uint64_t key);
    };
} // namespace des