/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c
 *
 * Code generated for Simulink model 'Sense'.
 *
 * Model version                  : 1.12
 * Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
 * C/C++ source code generated on : Thu Nov 25 18:30:50 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include <iostream>
#include <stddef.h>
#include <stdio.h>              /* This ert_main.c example uses printf/fflush */
#include "Sense.h"                     /* Model's header file */
#include "rtwtypes.h"
#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64.hpp>
using namespace std::chrono_literals;

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
//extern "C" void Sense_step(void);
//extern "C" void Sense_initialize(void);
//extern "C" void Sense_terminate(void);
void Sense_step(void);
void Sense_initialize(void);
void Sense_terminate(void);

void rt_OneStep(void);
void rt_OneStep(void)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(Sense_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  Sense_step();
  //printf("value : %f\n", Sense_Y.out);

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}


class SinPub : public rclcpp::Node
{
  public:
    SinPub()
    : Node("Sin_Publisher"), count_(0)
    {
      publisher_ = this->create_publisher<std_msgs::msg::Float64>("sense_value", 10);
      timer_ = this->create_wall_timer(
      100ms, std::bind(&SinPub::timer_callback, this));
    }

  private:
    void timer_callback()
    {
      rt_OneStep();
      auto message = std_msgs::msg::Float64();
      message.data = Sense_Y.out;
      printf("%f\n", Sense_Y.out);
      RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", message.data);
      publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_;
    size_t count_;
};




/*
 * The example "main" function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific.  This example
 * illustrates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char *argv[])
{
  /* Unused arguments */
  (void)(argc);
  (void)(argv);

  /* Initialize model */
  Sense_initialize();

  /* Attach rt_OneStep to a timer or interrupt service routine with
   * period 0.1 seconds (the model's base sample time) here.  The
   * call syntax for rt_OneStep is
   *
   *  rt_OneStep();
   */
  printf("Warning: The simulation will run forever. "
         "Generated ERT main won't simulate model step behavior. "
         "To change this behavior select the 'MAT-file logging' option.\n");
  fflush((NULL));
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SinPub>());
  rclcpp::shutdown();
  /*
  while (rtmGetErrorStatus(Sense_M) == (NULL)) {
	  rt_OneStep();
  }
*/

  /* Disable rt_OneStep() here */

  /* Terminate model */
  Sense_terminate();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
