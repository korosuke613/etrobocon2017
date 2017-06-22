#include "Pid.h"

//Constructor
Pid::Pid(double p_gain,double i_gain,double d_gain,double target){
    wrapper_of_constructor(p_gain,i_gain,d_gain,0,0,target,0);
}

//wrapper
void Pid::wrapper_of_constructor(double _p_gain,double _i_gain,double _d_gain,
        double _diff, double _integral,
        double _target,double _output){
    p_gain = _p_gain;
    i_gain = _i_gain;
    d_gain = _d_gain;
    old_diff = _diff;
    integral = _integral;
    target = _target;
    output = _output;
    del = 1;
}
void Pid::calculate(double light_value){
    double p,i,d;
    double diff = light_value - target;
    integral += (old_diff + diff)/2 * del;
    p =  p_gain * diff;
    i = i_gain * integral;
    d = d_gain * (diff - old_diff)/del;
    old_diff = diff;
    output = p + i + d;
}
double Pid::get_output(){
    return output;
}
void Pid::change_del(double next_del){
    del = next_del;
}

/*
 * PID値を入力する
 */
void Pid::setPid(double _p_gain,double _i_gain,double _d_gain,double _target){
    wrapper_of_constructor(_p_gain, _i_gain, _d_gain, 0, 0, _target, 0);
}
