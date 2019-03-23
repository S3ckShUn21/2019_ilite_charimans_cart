/*
    Title : Chairmans Cart Code 2019
    Hardware : Arduino Uno
    Author : Cole Roof
    Version : 3-23-19
*/

// Button that chairmans person will press
#define button_pin 8

// All of the PWM pins
// These are the pins that will fade
#define red_pwm_b 11
#define white_pwm_g 10
#define blue_pwm_r 9

// All of the digital pins for the border
// These will either be on or off
#define red_digital_pin 12
#define white_digital_r A4
#define white_digital_b A3
#define blue_digital_pin A5

// Below are the pins for the front panel
// All of them are digital

// Big planet it purple
#define big_planet_r 2
#define big_planet_b 3
// Stars are white
#define stars_r 4
#define stars_g 5
#define stars_b 6
// The middle small planets are green
#define planets_g 7

// Constants for the PWMS
#define PWM_FULL 0xff
#define PWM_OFF 0x00

// This is the variable that keeps track of what part of
// the speech they are in
uint8_t button_counter;
// A debounce variable
bool allowed_to_trigger;

void setup()
{
    Serial.begin(9600);
    Serial.println("Chairmans Cart Initialized");

    // This button is triggered when it is connected to ground
    // Hence the pullup resistor
    pinMode(button_pin, INPUT_PULLUP);

    pinMode(red_digital_pin, OUTPUT);
    pinMode(red_pwm_b, OUTPUT);

    pinMode(blue_pwm_r, OUTPUT);
    pinMode(blue_digital_pin, OUTPUT);

    pinMode(white_digital_r, OUTPUT);
    pinMode(white_pwm_g, OUTPUT);
    pinMode(white_digital_b, OUTPUT);

    pinMode(stars_r, OUTPUT);
    pinMode(stars_g, OUTPUT);
    pinMode(stars_b, OUTPUT);

    pinMode(big_planet_r, OUTPUT);
    pinMode(big_planet_b, OUTPUT);

    pinMode(planets_g, OUTPUT);

    // Init vars
    button_counter = 0;
    allowed_to_trigger = true;

    // Makes sure that at startup all of the lights are off`
    turn_all_off();

    // Slight pause for to catch up
    delay(100);
}

void loop()
{
    //Button pressed && the debounce has been reset
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
        // This is a saftey press so the lights don't turn off by accident
        break;
    case 9:
        // This is also a saftey press so the lights don't turn off by accident
        break;
    case 10:
        turn_all_off();
        Serial.println("Turnned all leds off");
        Serial.println("Chairmans cart finished");
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
    // Blue Pin should not be triggered for this call
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
