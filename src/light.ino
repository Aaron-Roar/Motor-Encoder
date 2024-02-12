
char pwm_output_pin = 5; //The pin which to preform pwm output

ISR(TIMER1_OVF_vect) {
    digitalWrite(pwm_output_pin, HIGH);
}

ISR(TIMER1_COMPA_vect) {
    digitalWrite(pwm_output_pin, LOW);
}

void writePwm(char gpio, float pwm) {
    pwm_output_pin = gpio;

    TCCR1A = 0; //Initialize timer 1
    TCCR1B = 0; //More initialization of same timer

    TCCR1B |= 0b00000001; //Setting prescalar, smallest option for higher frequency
    OCR1A = (uint16_t)(65535*pwm); //Compare address. (ovf)*pwm%

    TIMSK1 |= 0b00000010; //Setting compare interupt on
    TIMSK1 |= 0b00000001; //Setting ovf interupt on
}


void setup() {
    writePwm(5, 100);
}

void loop() {
}
