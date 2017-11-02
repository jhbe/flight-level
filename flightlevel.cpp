#include <stdio.h>
#include <math.h>
#include "delay.h"
#include "systemtimer.h"
#include "uart.h"
#include "pitchandroll.h"
#include "xyz.h"
#include "mpu6050.h"
#include "servos.h"
#include "input.h"
#include "interrupts.h"
#include "gpio.h"
#include "led.h"

#define INPUT_0_GPIO   4
#define INPUT_1_GPIO  17
#define INPUT_2_GPIO  27
#define INPUT_3_GPIO  10
#define INPUT_4_GPIO   9

#define SERVO_0_GPIO  18
#define SERVO_1_GPIO  23
#define SERVO_2_GPIO  24
#define SERVO_3_GPIO  25

#define GPIO_IRQ_NUMBER 49
#define PERIODIC_TIMER_CHANNEL 1

Led led(47, true);
Servos servos(SERVO_0_GPIO, SERVO_1_GPIO, SERVO_2_GPIO, SERVO_3_GPIO);
Input input_0(INPUT_0_GPIO);
Input input_1(INPUT_1_GPIO);
Input input_2(INPUT_2_GPIO);
Input input_3(INPUT_3_GPIO);
Input input_4(INPUT_4_GPIO);
PitchAndRoll pnr;

void service(void) {
	led.Service();
}

typedef enum {
	Initializing, Calibrating, Running
} State;

int main(void) {
	enable_interrupts();
	enable_gpio_interrupts();
	enable_timer_interrupts(PERIODIC_TIMER_CHANNEL);
	enable_timer_interrupts(SERVOS_TIMER_CHANNEL);

	systemtimer_set_alarm(PERIODIC_TIMER_CHANNEL, 100000); // 100ms

	uart_init();
	mpu6050_init();

	led.Clear();

	servos.OnTimerIsr();

	State state = Initializing;

	XYZ zero_angles;
	XYZ accel;
	int num_calibration_samples;

	uint64_t last_time = systemtimer_get();
	uint64_t last_state_update = last_time;

	while (1) {
		uint64_t now = systemtimer_get();
		float dt = (now - last_time) / 1000000.0;

		float gx, gy, gz, ax, ay, az;
		mpu6050_read(gx, gy, gz, ax, ay, az, &service);

		if (state == Initializing) {
			state = Calibrating;
			last_state_update = now;

			zero_angles.Reset();
			accel.Reset();
			num_calibration_samples = 0;

			led.Flash();
		} else if (state == Calibrating) {
			zero_angles.Add(gx, gy, gz);
			accel.Add(ax, ay, az);
			num_calibration_samples++;

			if (abs(gx) > 5.0 || abs(gy) > 5.0 || abs(gz) > 5.0) {
				state = Initializing;
			} else if (abs(ax) > 0.1 || abs(ay) > 0.1 || abs(az-0.9) > 0.1) {
				state = Initializing;
			} else if (now - last_state_update > 5000000) {
				state = Running;
				last_state_update = now;

				zero_angles /= (float) num_calibration_samples;
				accel /= (float) num_calibration_samples;

				pnr.Adjust(accel.X(), accel.Y(), accel.Z(), 1.0);

				led.Set();
			}
		} else {
			uint64_t start = systemtimer_get();
			pnr.Put(gx - zero_angles.X(), gy - zero_angles.Y(),
					gz - zero_angles.Z(), dt);
			pnr.Adjust(ax, ay, az, 0.01);
			uint64_t end = systemtimer_get();

			float roll = pnr.Roll();
			if (roll < -45.0) {
				roll = -45.0;
			} else if (roll > 45.0) {
				roll = 45.0;
			}
			int length = 1500 + (int) (500.0 * roll / 45.0);
			servos.Set(0, length);

			float pitch = pnr.Pitch();
			if (pitch < -45.0) {
				pitch = -45.0;
			} else if (pitch > 45.0) {
				pitch = 45.0;
			}
			length = 1500 + (int) (500.0 * pitch / 45.0);
			servos.Set(1, length);

//		      printf("R: %7.3f  P: %7.3f    %d\n\r", pnr.Roll(), pnr.Pitch(), end - start);
//			printf("%6d %6d %6d %6d    %6d\n\r", input_0.Get(), input_1.Get(),
//					input_2.Get(), input_3.Get(), input_4.Get());
		}

		last_time = now;
	}
}

extern "C" {

void c_irq_handler(void) {
	if (interrupt_pending(GPIO_IRQ_NUMBER)) {
		if (gpio_get_edge_detected(INPUT_0_GPIO)) {
			input_0.Service();
		}
		if (gpio_get_edge_detected(INPUT_1_GPIO)) {
			input_1.Service();
		}
		if (gpio_get_edge_detected(INPUT_2_GPIO)) {
			input_2.Service();
		}
		if (gpio_get_edge_detected(INPUT_3_GPIO)) {
			input_3.Service();
		}
		if (gpio_get_edge_detected(INPUT_4_GPIO)) {
			input_4.Service();
		}
	}
	if (interrupt_pending(PERIODIC_TIMER_CHANNEL)) {
		input_0.Service();
		input_1.Service();
		input_2.Service();
		input_3.Service();
		input_4.Service();

		//
		// Reset for another 100ms in the future.
		//
		systemtimer_set_alarm(PERIODIC_TIMER_CHANNEL, 100000); // 100ms
	}
	if (interrupt_pending(SERVOS_TIMER_CHANNEL)) {
		servos.OnTimerIsr();
	}
}

void c_undefined_handler(void) {
	printf("\n\r*** UNDEFINED\n\r");
	while (1)
		;
}

void c_swi_handler(void) {
	printf("\n\r*** SWI\n\r");
	while (1)
		;
}

void c_prefetch_handler(void) {
	printf("\n\r*** PREFETCH\n\r");
	while (1)
		;
}

void c_data_handler(void) {
	printf("\n\r*** DATA\n\r");
	while (1)
		;
}

}
