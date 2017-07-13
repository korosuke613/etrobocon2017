#include "Pid.h"

//Constructor
<<<<<<< HEAD:str/app/pid.cpp
Pid::Pid(double p_gain, double i_gain, double d_gain, double target) {
    wrapper_of_constructor(p_gain,i_gain,d_gain,0,0,target,0);
=======
Pid::Pid(double _p_gain,double _i_gain,double _d_gain,double _target){
    wrapper_of_constructor(_p_gain,_i_gain,_d_gain,0,0,_target,0);
    FILE *fp;

    if ((fp = fopen("test.csv", "w")) == NULL) {
            printf("file open error!!\n");
            return;
    }
    fprintf(fp, "light_value, integral, pg, ig, dg, p, i, d, diff, old_diff, output\n");
    fclose(fp);
>>>>>>> dev_PidRun:str/app/Pid.cpp
}

//wrapper
void Pid::wrapper_of_constructor(double _p_gain, double _i_gain, double _d_gain,
        double _diff, double _integral, double _target, double _output) {
    p_gain   = _p_gain;
    i_gain   = _i_gain;
    d_gain   = _d_gain;
    old_diff = _diff;
    integral = _integral;
<<<<<<< HEAD:str/app/pid.cpp
    target   = _target;
    output   = _output;
    del      = 1;
=======
    target = _target;
    output = _output;
    del = 0.004;
>>>>>>> dev_PidRun:str/app/Pid.cpp
}
void Pid::calculate(double light_value) {
    double p,i,d;
    double diff = light_value - target;
    FILE *fp;
    if ((fp = fopen("test.csv", "a")) == NULL) {
            printf("file open error!!\n");
            return;
    }
    integral += (old_diff + diff)/2 * del;
    p =  p_gain * diff;
    i = i_gain * integral;
    d = d_gain * (diff - old_diff)/del;
    old_diff = diff;
    output = p + i + d;
    fprintf(fp, "%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf\n",
    light_value, integral, p_gain, i_gain, d_gain, p, i, d, diff, old_diff, output);
    fclose(fp);
}
double Pid::get_output() {
    return output;
}
void Pid::change_del(double next_del) {
    del = next_del;
}

/*
 * PID値を入力する
 */
void Pid::setPid(double _p_gain, double _i_gain, double _d_gain, double _target) {
    wrapper_of_constructor(_p_gain, _i_gain, _d_gain, 0, 0, _target, 0);
}

/*
 * target値を入力する
 */
void Pid::setTarget(double _target) {
    wrapper_of_constructor(p_gain, i_gain, d_gain, 0, 0, _target, 0);
}
