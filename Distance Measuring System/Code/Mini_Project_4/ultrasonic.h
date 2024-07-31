#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include"std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define TRIGGER_PORT				PORTB_ID
#define TRIGGER_PIN                 PIN5_ID
#define ECHO_PORT				    PORTD_ID
#define ECHO_PIN                    PIN6_ID

void Ultrasonic_init(void);
void Ultrasonic_Trigger(void);
uint16 Ultrasonic_readDistance(void);
void Ultrasonic_edgeProcessing(void);



#endif
