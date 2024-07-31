#include "ultrasonic.h"
#include "gpio.h"
#include "icu.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

static volatile uint8 g_edgeCount = 0;
static volatile uint16 g_pulse_duration = 0;
static volatile uint16 g_distance_cm = 0;

void Ultrasonic_init(void)
{
	/* Create configuration structure for ICU driver */
		ICU_ConfigType ICU_Configurations = {F_CPU_8,RAISING};

		/* Enable Global Interrupt I-Bit */
		SREG |= (1<<7);

		/* Initialize the ICU driver */
		ICU_init(&ICU_Configurations);

		/* Set the Call back function pointer in the ICU driver */
		ICU_setCallBack(Ultrasonic_edgeProcessing);

		/*Configure trigger pin as output*/
		GPIO_setupPinDirection(TRIGGER_PORT,TRIGGER_PIN,PIN_OUTPUT);
}
void Ultrasonic_edgeProcessing(void)
{
	 g_edgeCount++;
		if(g_edgeCount == 1)
		{
			/*
			 * Clear the timer counter register to start measurements from the
			 * first detected rising edge
			 */
			ICU_clearTimerValue();
			/* Detect falling edge */
			ICU_setEdgeDetectionType(FALLING);
		}
		else if(g_edgeCount == 2)
		{
			/* Record the end time of the pulse */
			g_pulse_duration = ICU_getInputCaptureValue();

			    /* Calculate distance in centimeters*/
			    /* Speed of sound in air at room temperature is approximately 343 m/s*/
			    /* Divide by 2 to account for round-trip*/
			     g_distance_cm = (g_pulse_duration / 57.7);

			     /* OR
			      *  distance_cm = (g_pulse_duration * 0.01733);
			      */

			/* Detect rising edge */
			ICU_setEdgeDetectionType(RAISING);

			 g_edgeCount=0;
		}

}
void Ultrasonic_Trigger(void)
{
	/* Send a 10µs high pulse to trigger pin*/
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void)
{
	 /* Send trigger pulse*/
	 Ultrasonic_Trigger();

	 /*Wait for capture to complete*/
    _delay_ms(50);

	 return g_distance_cm ;
}
