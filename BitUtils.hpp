#pragma once
#include <array>
#include <cstdint>

namespace des {
namespace BitUtils {

/**
 * @brief 指定位置のビットを取得する（1始まりインデックス）
 * @param data ビット列を格納する整数
 * @param pos 1～64 の位置（左から数える）
 * @return 取得したビット (0 or 1)
 */
uint8_t getBit(uint64_t data, int pos);

/**
 * @brief 指定位置にビットを設定する（LSB=0 から起算）
 * @param output ビット列を格納する整数
 * @param idx 1～64 の位置（左から数える）
 * @param value 設定するビット (0 or 1)
 * @note 0以外の値が指定された場合は1として扱う
 */
void setBitOut(uint64_t &output, int idx, uint8_t value);

/**
 * @brief 入力ビット列にテーブルに基づく置換を適用する
 * @tparam N テーブルサイズ
 * @param input 元のビット列 (最大64ビット)
 * @param table 1始まりの変換先インデックス配列
 * @return 置換後のビット列
 */
template <size_t N>
uint64_t applyPermutation(uint64_t input, const std::array<int, N> &table) {
    uint64_t output = 0;
    for (size_t i = 0; i < N; ++i) {
        // table の値は 1～64 の位置を示す
        uint8_t bit = getBit(input, table[i]);
        setBitOut(output, N - 1 - static_cast<int>(i), bit);
    }
    return output;
}

} // namespace BitUtils
} // namespace des