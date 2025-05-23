#include "KeySchedule.hpp"
#include "BitUtils.hpp"
#include "Tables.hpp"

namespace des {

    KeySchedule::KeySchedule(uint64_t key){
        generateSubkeys(key);
    }

    void KeySchedule::generateSubkeys(uint64_t key){
        // 1) PC-1 適用：64bit -> 56bit
        uint64_t perm56 = BitUtils::applyPermutation<56>(key, PC1);
        // 2) 28bit halbves
        uint32_t C = static_cast<uint32_t>(perm56 >> 28);
        uint32_t D = static_cast<uint32_t>(perm56 & 0x0FFFFFFF);

        // シフトテーブル（1 or 2 bit shifts per round）
        constexpr std::array<int, 16> shifts = {1, 1, 2, 2, 2, 2, 1, 2,
                                                2, 2, 2, 1, 2, 2, 2, 1};

        for (int i = 0; i < 16; i++)
        {
            // 循環左シフト
            C = ((C << shifts[i]) | (C >> (28 - shifts[i]))) & 0x0FFFFFFF;
            D = ((D << shifts[i]) | (D >> (28 - shifts[i]))) & 0x0FFFFFFF;

            // 再結合
            uint64_t combined = (uint64_t(C) << 28) | D;
            // PC-2 適用：56bit -> 48bit
            uint64_t subkey = BitUtils::applyPermutation<48>(combined << 8, PC2);
            subkeys_[i] = subkey;
        }
    }

    uint64_t KeySchedule::getSubkey(int round) const {
        return subkeys_[round];
    }
} // namespace des