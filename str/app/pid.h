#ifndef __PID__
#define __PID__

class Pid{
  //menber variables
private:
  double p_gain;
  double i_gain;
  double d_gain;
  double old_diff;
  double integral;
  double target;
  double output;
  double del;

  //member methods
public:
  //Constructor
  Pid(double p_gain,double i_gain,double d_gain,double target);
  void setPid(double _p_gain,double _i_gain,double _d_gain,double _target);
  void setTarget(double _target);
  void calculate(double light_value);
  double get_output();
private:
  void wrapper_of_constructor(double _p_gain,double _i_gain,double _d_gain,
			      double _diff, double _integral,
			      double _target,double _output);
  void change_del(double next_del);
};




#endif
