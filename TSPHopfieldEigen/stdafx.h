// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once


#include <stdio.h>
#ifdef __APPLE__
#elif defined _WIN32 || defined _WIN64
#include "targetver.h"
#include <tchar.h>
#endif

#include "Eigen/Core"

// TODO: プログラムに必要な追加ヘッダーをここで参照してください
