/**
 * @file Pid.h
 * @brief PID制御の計算を行うクラス
 * @author Futa HIRAKOBA
 */
#ifndef __PID__
#define __PID__

/*! @class Pid Pid.h "Pid.h"
 *  @brief PID制御の計算を行うクラス
 */
class Pid{
public:
  /** コンストラクタ */
  Pid(double p_gain,double i_gain,double d_gain,double target);

  /** Kp, Ki, Kd, 目標値を設定する
  * @param _p_gain Kp
  * @param _i_gain Ki
  * @param _d_gain Kd
  * @param _target 目標値 */
  void setPid(double _p_gain,double _i_gain,double _d_gain,double _target);
  void wrapper_of_constructor(double _p_gain,double _i_gain,double _d_gain,
    double _diff, double _integral,
    double _target,double _output);

  /** PID制御の計算をする
  * @param light_value 現在の値 */
  void calculate(double light_value); 

 protected:
  /** PID計算値を取得する
  * @return 計算値 */
  double get_output();

  /** PID計算値を制限する
  * @param PID計算値
  * @return PID計算値 */
  double limitOutput(double pid_value);

private:
  double p_gain;
  double i_gain;
  double d_gain;
  double old_diff;
  double integral;
  double target;
  double output;
  double del;
};

#endif
