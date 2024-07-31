#include "ultrasonic.h"
#include "lcd.h"
#include <util/delay.h>
int main() {
    /* Initialize peripherals*/
    LCD_init();
    Ultrasonic_init();

    LCD_displayString("Distance: ");

    // Main loop
    while (1) {
       /*  Measure distance*/
        uint16 distance_cm = Ultrasonic_readDistance();

        /* Display distance on LCD */
        LCD_moveCursor(0,10); /* Move cursor  */
        LCD_intgerToString(distance_cm);
        LCD_displayString(" cm");

        _delay_ms(300); /* Delay between measurements */
    }

    return 0;
}
