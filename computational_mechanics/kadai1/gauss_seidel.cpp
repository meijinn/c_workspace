#include <stdio.h>
#include <math.h>

#define NX 6  // x方向のグリッド数
#define NY 6  // y方向のグリッド数
#define DX (L/NX) // x方向のグリッド間隔
#define DY (L/NY) // y方向のグリッド間隔
#define L 0.12  // シミュレーション領域のサイズ
#define EPS 1e-6  // 収束判定の閾値


int main() {
    double u[NX][NY] = {{0}};  // 温度分布
    double error = EPS + 1.0;  // 誤差

    // 初期条件の設定
        for (int j = 0; j < NY; j++) {
            u[0][j] = 50*sin((M_PI/L)*j*DX);
        }

    // ガウスザイデル法による反復計算
    while (error > EPS) {
        error = 0.0;
        for (int i = 1; i < NX - 1; i++) {
            for (int j = 1; j < NY - 1; j++) {
                double tmp = u[i][j];
                u[i][j] = (u[i-1][j] + u[i+1][j] + u[i][j-1] + u[i][j+1]) / 4.0;
                error += fabs(u[i][j] - tmp);
            }
        }
    }

    // 温度分布の出力
    for (int i = 0; i < NX; i++) {
        for (int j = 0; j < NY; j++) {
            printf("%lf ", u[i][j]);
        }
        printf("\n");
    }

    return 0;
}
