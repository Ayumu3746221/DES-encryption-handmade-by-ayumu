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

# テストを有効にする
enable_testing()
add_test(NAME TestKeySchedule COMMAND TestKeySchedule)
add_test(NAME TestIP COMMAND TestIP)
