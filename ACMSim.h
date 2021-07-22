#ifndef ACMSIM_H
#define ACMSIM_H

/* standard lib */
#include <stdio.h> // printf #include <stdbool.h> // bool for _Bool and true for 1
#include <stdbool.h> // bool for _Bool and true for 1
#include <process.h>//reqd. for system function prototype
#include <conio.h> // for clrscr, and getch()
#include "stdlib.h" // for rand()
#include "math.h"

/* How long should I go? */
#define NUMBER_OF_LINES (200000)

#define IM_TS 1.25e-4        //电机仿真步长
#define IM_TS_INVERSE 8000   //电机仿真频率
#define DOWN_FREQ_EXE 2      //电机仿真降采样是2
#define DOWN_FREQ_EXE_INVERSE 0.5 //控制器降采样是0.5
#define TS (IM_TS*DOWN_FREQ_EXE) //2.5e-4 -> 
#define TS_INVERSE (IM_TS_INVERSE*DOWN_FREQ_EXE_INVERSE) // 4000 -> 控制器的步长


/* General Constants */
#define TRUE True
#define FALSE False
#define True (1)
#define False (0)
#define lTpi                  0.15915494309189535 // 1/(2*pi)
#define TWO_PI_OVER_3         2.0943951023931953
#define SIN_2PI_SLASH_3       0.86602540378443871 // sin(2*pi/3)
#define SIN_DASH_2PI_SLASH_3 -0.86602540378443871 // sin(-2*pi/3)
#define SQRT_2_SLASH_3        0.81649658092772603 // sqrt(2.0/3.0)
// #define RPM_2_RAD_PER_SEC     0.20943951023931953 // (2/60*Tpi)
// #define RAD_PER_SEC_2_RPM     4.7746482927568605 // 1/(im.npp/60*Tpi)
#define abs                   use_fabs_instead_or_you_will_regret //abs -> 绝对值
#define RAD_PER_SEC_2_RPM (60.0/(2*M_PI*im.npp))
#define RPM_2_RAD_PER_SEC ((2*M_PI*im.npp)/60.0)
// #define PI_D 3.1415926535897932384626433832795 /* double */
#define M_PI_OVER_180   0.017453292519943295

// 补充的宏，为了实现实验/仿真代码大一统
#define Uint32 unsigned long int
#define Uint16 unsigned int
#define PHASE_NUMBER 3

//定义电机，仿真的结构体
struct InductionMachineSimulated{
    double x[13]; ////////////////////////////////
    double rpm;                //转速
    double rpm_cmd;           //转速指令 
    double rpm_deriv_cmd;    //转速指令的导数
    double Tload;           //负载转矩
    double Tem;            //电磁转矩

    double Lsigma;        //漏感
    double rs;           //定子电阻  
    double rreq;        //转子电阻  
    double Lmu;        //励磁电感
    double Lmu_inv;   //励磁电感倒数
    double alpha;    //转子时间常数的倒数

    double Js;       //转动惯量
    double npp;     //极对数
    double mu_m;   //mu_m = npp/Js
    double Ts;    //timestep0 时间步长 

    double iqs;   //定子电阻电流  beta
    double ids;  //定子电阻电流   alpha

    double ual;  //alpha轴电压
    double ube; //beta轴电压
};
extern struct InductionMachineSimulated IM;

//extern作用是告诉其他C文件，如果要找IM结构体实例的话，要从别的地方找，在别的地方定义即可

#include "controller.h"
#include "observer.h"


/* Declaration of Utility Function */
bool isNumber(double x);
void write_data_to_file(FILE *fw);

#endif