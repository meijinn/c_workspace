#include<stdio.h>
#include<math.h>
#define L 0.2
#define N 10 
#define DX (L / N)
#define DT 250
#define rambda  1.26 //?M?`????
#define rho 1600 // ???x
#define c 1050 //??M
#define Ta 1000
#define Tb 0

const double a = rambda/(rho * c);

double T_old[N+1];
double T_new[N+1];

double _a[N - 1];
double _b[N - 1]; 
double _c[N - 1]; 
double _d[N - 1]; 
int size = sizeof(_d)/sizeof(double); //9 N-1
double r = (a*DT/(DX*DX));

void init (){
    //???E????
    for(int x = 1; x < N; x++){
        T_old[x] = Tb;
        T_new[x] = Tb;
    }
    T_old[0] = Ta;
    T_new[0] = Ta;
}

void init_thomas(){
    for(int x = 0; x < N-1; x++){
        _a[x] = -r;
        _b[x] = 1 + 2 * r;
        _c[x] = -r;
        if(x == 0){
            _d[x] = r * T_old[x] + T_old[x+1]; 
        }else if(x == N - 2){
            _d[x] = r * T_old[x+2] + T_old[x+1]; 
        }else{
            _d[x] = T_old[x+1];
        }
    }
}

//?g?[?}?X?@
void thomas(){
    for(int x = 1; x < N-1; x++){
        double e = _a[x]/_b[x-1];
        _b[x] = _b[x] - e * _c[x-1];
        _d[x] = _d[x] - e * _d[x-1];
    }
    _d[N-2] = _d[N-2]/_b[N-2];
    for(int x = N - 3; x >= 0; x--){
        _d[x] = (_d[x] - _c[x] * _d[x+1])/_b[x];
    }
    for(int x = 1; x < N; x++){
        T_new[x] = _d[x-1];
    }
}

void cpy_array(){
    for(int x = 0; x < N+1; x++){
        T_old[x] = T_new[x];
    }
}

void print_array(int time){
    printf("%d[s] ",time);
    for(int x = 0; x < N+1; x++){
        printf("%5.1f ",T_new[x]);
    }
    printf("\n");
}

//???????@
void backword_dif(){
    for(int t = 1; t <= 20; t++){
        thomas();
        if(t % 4 == 0){
            print_array(t * DT);
        } 
        cpy_array();
        init_thomas();
    }
}

int main(){
    init();
    init_thomas();
    backword_dif();
    return 0;
}