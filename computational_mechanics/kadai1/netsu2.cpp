#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float L; //長さ
float W; //幅
int N; //格子数
#define Tm 50
#define T0 0.0      // 境界条件1
//#define T1 10       // 境界条件2
#define T2 0.0      // 境界条件3
#define T3 0.0      // 境界条件4
#define TOL 1e-2 //誤差精度
#define MAX_ITER 100000 //計算の反復回数

int main()
{
    printf("長さ？ 幅？ 格子数？：");
    scanf("%f %f %d",&L, &W, &N);
    double T[N+2][N+2];  // 格子点の温度
    double T_new[N+2][N+2];  // 更新後の格子点の温度
    double T_true[N+2][N+2] = {0}; //真値
    double diff;  // 収束判定に使用する差分
    int i, j, iter; //カウンタ

  // 初期値の設定
  for (i = 0; i < N+2; i++) {
    for (j = 0; j < N+2; j++) {
      T_new[i][j] = 0.0; // 0℃で初期化
      T[i][j] = 0.0;
    }
  }

  // 境界条件の設定
  for (i = 0; i < N+2; i++) {
    T[i][0] = T0;   // 左辺
    T[i][N+1] = T2; // 右辺
  }
  for (j = 0; j < N+2; j++) {
    T[0][j] = Tm*sin((M_PI/L)*j);   // 上辺
    T[N+1][j] = T3; // 下辺
  }


    // ガウスザイデル法による解析
    for (iter = 0; iter < MAX_ITER; iter++) {
        diff = 0;

        for (i = 1; i < N+1; i++) {
            for (j = 1; j < N+1; j++) {
                T_new[i][j] = 0.25 * (T[i-1][j] + T[i+1][j] + T[i][j-1] + T[i][j+1]);  // ガウスザイデル法の式

                // 差分を更新
                diff += fabs(T_new[i][j] - T[i][j]);

                // 新しい温度を格子点に代入
                T[i][j] = T_new[i][j];
            }
        }

        // 収束判定
        if (diff < TOL) {
            break;
        }
    }

    // 結果の出力
    printf("Final temperature distribution:\n");
    for (i = 1; i < N+1; i++) {
        for (j = 1; j < N+1; j++) {
            printf("%f ", T[i][j]);
            printf("(%f) ", T_true[i][j]);
        }
        printf("\n");
      }
      return 0;
}