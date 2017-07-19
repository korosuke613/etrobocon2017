#include "Pid.h"

//Constructor
Pid::Pid(double _p_gain,double _i_gain,double _d_gain,double _target){
    wrapper_of_constructor(_p_gain,_i_gain,_d_gain,0,0,_target,0);
    FILE *fp;

    if ((fp = fopen("test.csv", "w")) == NULL) {
            printf("file open error!!\n");
            return;
    }
    fprintf(fp, "light_value, integral, pg, ig, dg, p, i, d, diff, old_diff, output\n");
    fclose(fp);
}

//wrapper
void Pid::wrapper_of_constructor(double _p_gain, double _i_gain, double _d_gain,
        double _diff, double _integral, double _target, double _output) {
    p_gain   = _p_gain;
    i_gain   = _i_gain;
    d_gain   = _d_gain;
    old_diff = _diff;
    integral = _integral;
    target   = _target;
    output   = _output;
    del      = 0.004;

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
<<<<<<< HEAD:str/app/Pid.cpp
void Pid::setPid(double _p_gain, double _i_gain, double _d_gain, double _target) {
    p_gain = _p_gain;
    i_gain = _i_gain;
    d_gain = _d_gain;
    target = _target;
}

/*
 * target値を入力する
 */
void Pid::setTarget(double _target) {
    wrapper_of_constructor(p_gain, i_gain, d_gain, 0, 0, _target, 0);
=======
void Pid::setPid(double _p_gain,double _i_gain,double _d_gain,double _target){
    //wrapper_of_constructor(_p_gain, _i_gain, _d_gain, 0, 0, _target, 0);
	p_gain = _p_gain ;
	i_gain = _i_gain ;
	d_gain = _d_gain ;
	target = _target ;
>>>>>>> dev_PidRun_NormalCourse:str/app/pid.cpp
}
