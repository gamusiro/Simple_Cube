# Cmake バージョン指定
cmake_minimum_required(VERSION 3.20.0)

# プロジェクトのセットアップ
set(NAME GLAD)
project(${NAME})

# ソースコードとヘッダーのディレクトリ
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# ライブラリの生成
add_library(${NAME} STATIC ${SRC_DIR}/glad.c)

# インクルードディレクトリを設定
target_include_directories(${NAME} PUBLIC ${INCLUDE_DIR})