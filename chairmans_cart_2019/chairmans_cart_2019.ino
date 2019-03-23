#include <Adafruit_TLC59711.h>

/*
    Title : Chairmans Cart Code 2019
    Hardware : Arduino Uno
    Author : Cole Roof
    Version : 3-6-19
*/

#define button_pin 8

#define red_pwm_b 11
#define white_pwm_g 10
#define blue_pwm_r 9

#define red_digital_pin 12
#define white_digital_r A4
#define white_digital_b A3
#define blue_digital_pin A5

#define big_planet_r 2
#define big_planet_b 3
#define stars_r 4
#define stars_g 5
#define stars_b 6
#define planets_g 7

#define PWM_FULL 0xff
#define PWM_OFF 0x00

uint8_t button_counter;
bool allowed_to_trigger;

void setup()
{
    // Serial.begin( 9600 );
    // Serial.println( "Chairmans Cart Initialized" );

    // Button that the chairman's people will press
    pinMode(button_pin, INPUT_PULLUP);

    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);

    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);

    pinMode( A3, OUTPUT);
    pinMode( A4, OUTPUT);
    pinMode( A5, OUTPUT);

    // Init vars
    button_counter = 0;
    allowed_to_trigger = true;

    turn_all_off();

    // digitalWrite(planets_g, LOW);

    // Slight pause for computer
    delay(100);
}

void loop()
{
    //Button pressed
    if (digitalRead(button_pin) == 0 && allowed_to_trigger)
    {
        button_counter++;
        order_of_operations(button_counter);
        allowed_to_trigger = false;
    }
    // Button not pressed
    else if (digitalRead(button_pin))
    {
        // Allow the button the be pressed again
        allowed_to_trigger = true;
        delay(100);
    }
}

void order_of_operations(uint8_t count)
{
    switch (count)
    {
    case 1:
        // Show stars
        digitalWrite(stars_r, HIGH);
        digitalWrite(stars_g, HIGH);
        digitalWrite(stars_b, HIGH);
        break;
    case 2:
        // Show planets
        digitalWrite(planets_g, HIGH);
        break;
    case 3:
        // Show big planet
        digitalWrite(big_planet_r, HIGH);
        digitalWrite(big_planet_b, HIGH);
        break;
    case 4:
        trigger_red_leds();
        // Serial.println( "Triggered Red LEDs" );
        break;
    case 5:
        trigger_white_leds();
        // Serial.println( "Triggered White LEDs" );
        break;
    case 6:
        trigger_blue_leds();
        // Serial.println( "Triggered Blue LEDs" );
        break;
    case 7:
        // Serial.println( "About to fade to purple" );
        fade_all_to_purple();
        // Serial.println( "Fadded to purple" );
        break;
    case 8:
        break;
    case 9:
        break;
    case 10:
        turn_all_off();
        // Serial.println( "Turnned all leds off" );
        break;
    }
}

void trigger_white_leds()
{
    // full value white needs all pins to be turned to full

    digitalWrite(white_digital_r, HIGH);
    analogWrite(white_pwm_g, PWM_FULL);
    analogWrite(white_digital_b, HIGH);
}

void trigger_red_leds()
{
    // full red value

    digitalWrite(red_digital_pin, HIGH);
    // No green pin for digitaltrip
    // Blue Pin should ndigitaltriggered for thidigital
}

void trigger_blue_leds()
{
    // full blue value

    // Red pin should not be tiggered for this call
    // No green pin for this strip
    digitalWrite(blue_digital_pin, HIGH);
}

void fade_all_to_purple()
{
    for (int i = 0; i < PWM_FULL; i++)
    {
        analogWrite(red_pwm_b, i);              // Slowly turns blue on for the red strip
        analogWrite(white_pwm_g, PWM_FULL - i); // Slowly turns green off for the white strip
        analogWrite(blue_pwm_r, i);             // Slowly turns red on for the blue strip
        delay(20);                              // That is a total fade time of 5.1 seconds
                                                // .02s * 255 loop cycles = 5.1s in total
    }
}

void turn_all_off()
{
    // Turn off all of the digital MOSFET pins
    digitalWrite(red_digital_pin, LOW);
    digitalWrite(white_digital_r, LOW);
    digitalWrite(white_digital_b, LOW);
    digitalWrite(blue_digital_pin, LOW);

    //Turn off all of the analog MOSFET pins
    analogWrite(red_pwm_b, PWM_OFF);
    analogWrite(white_pwm_g, PWM_OFF);
    analogWrite(blue_pwm_r, PWM_OFF);

    // Turn off all of the front facing lights
    digitalWrite(stars_r, LOW);
    digitalWrite(stars_g, LOW);
    digitalWrite(stars_b, LOW);

    digitalWrite(planets_g, LOW);

    digitalWrite(big_planet_r, LOW);
    digitalWrite(big_planet_b, LOW);
}
