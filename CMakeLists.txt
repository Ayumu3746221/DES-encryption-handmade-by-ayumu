cmake_minimum_required(VERSION 3.10)
project(DES)

set(CMAKE_CXX_STANDARD 17)

# Google Testの設定
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# プロジェクトのルートディレクトリをインクルードパスに追加
include_directories(${CMAKE_SOURCE_DIR})

# IPテーブルのテストを追加
add_executable(TestIP tests/TestIP.cpp BitUtils.cpp)
target_link_libraries(TestIP ${GTEST_LIBRARIES} pthread)

# KeyScheduleのテストを追加
add_executable(TestKeySchedule tests/TestKeySchedule.cpp KeySchedule.cpp BitUtils.cpp)
target_link_libraries(TestKeySchedule ${GTEST_LIBRARIES} pthread)

# FeistelFunctionのテストを追加
add_executable(TestFeistelFunction tests/TestFeistelFunction.cpp FeistelFunction.cpp BitUtils.cpp)
target_link_libraries(TestFeistelFunction ${GTEST_LIBRARIES} pthread)

# FeistelDemoを追加
add_executable(FeistelDemo FeistelDemo.cpp FeistelFunction.cpp KeySchedule.cpp BitUtils.cpp)

# main.cpp を使った実行ファイルを追加
add_executable(main main.cpp DES.cpp KeySchedule.cpp BitUtils.cpp FeistelFunction.cpp)

# テストを有効にする
enable_testing()
add_test(NAME TestKeySchedule COMMAND TestKeySchedule)
add_test(NAME TestIP COMMAND TestIP)
add_test(NAME TestFeistelFunction COMMAND TestFeistelFunction)