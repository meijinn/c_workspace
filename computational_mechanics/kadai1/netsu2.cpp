#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float L; //����
float W; //��
int N; //�i�q��
#define Tm 50
#define T0 0.0      // ���E����1
//#define T1 10       // ���E����2
#define T2 0.0      // ���E����3
#define T3 0.0      // ���E����4
#define TOL 1e-2 //�덷���x
#define MAX_ITER 100000 //�v�Z�̔�����

int main()
{
    printf("�����H ���H �i�q���H�F");
    scanf("%f %f %d",&L, &W, &N);
    double T[N+2][N+2];  // �i�q�_�̉��x
    double T_new[N+2][N+2];  // �X�V��̊i�q�_�̉��x
    double T_true[N+2][N+2] = {0}; //�^�l
    double diff;  // ��������Ɏg�p���鍷��
    int i, j, iter; //�J�E���^

  // �����l�̐ݒ�
  for (i = 0; i < N+2; i++) {
    for (j = 0; j < N+2; j++) {
      T_new[i][j] = 0.0; // 0���ŏ�����
      T[i][j] = 0.0;
    }
  }

  // ���E�����̐ݒ�
  for (i = 0; i < N+2; i++) {
    T[i][0] = T0;   // ����
    T[i][N+1] = T2; // �E��
  }
  for (j = 0; j < N+2; j++) {
    T[0][j] = Tm*sin((M_PI/L)*j);   // ���
    T[N+1][j] = T3; // ����
  }


    // �K�E�X�U�C�f���@�ɂ����
    for (iter = 0; iter < MAX_ITER; iter++) {
        diff = 0;

        for (i = 1; i < N+1; i++) {
            for (j = 1; j < N+1; j++) {
                T_new[i][j] = 0.25 * (T[i-1][j] + T[i+1][j] + T[i][j-1] + T[i][j+1]);  // �K�E�X�U�C�f���@�̎�

                // �������X�V
                diff += fabs(T_new[i][j] - T[i][j]);

                // �V�������x���i�q�_�ɑ��
                T[i][j] = T_new[i][j];
            }
        }

        // ��������
        if (diff < TOL) {
            break;
        }
    }

    // ���ʂ̏o��
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