#include <stdio.h>
#include <math.h>

#define NX 100         // 格子点の数
#define DT 0.1         // 時間刻み幅
#define DX 0.01        // 空間刻み幅
#define ALPHA 1.0e-4   // 熱伝導率
#define TIME 1.0       // 計算時間
#define TEMP_LEFT 100  // 左端の温度
#define TEMP_RIGHT 0   // 右端の温度

int main() {
  double u[NX+1], unew[NX+1];  // 温度の配列
  double t, x;                 // 時間、空間変数
  int i, n;

  // 初期条件の設定
  for (i = 1; i <= NX; i++) {
    u[i] = 0.0;
  }
  u[1] = TEMP_LEFT;
  u[NX] = TEMP_RIGHT;

  // 時間ループ
  for (t = 0.0, n = 0; t < TIME; t += DT, n++) {
    // 空間ループ
    for (i = 2; i < NX; i++) {
      unew[i] = u[i] + ALPHA*DT/(DX*DX)*(u[i-1] - 2.0*u[i] + u[i+1]);
    }
    // 境界条件の設定
    unew[1] = TEMP_LEFT;
    unew[NX] = TEMP_RIGHT;

    // uを更新
    for (i = 1; i <= NX; i++) {
      u[i] = unew[i];
    }

    // 結果の出力
    if (n % 10 == 0) {
      printf("%f ", t);
      for (i = 1; i <= NX; i++) {
        printf("%f ", u[i]);
      }
      printf("\n");
    }
  }

  return 0;
}
