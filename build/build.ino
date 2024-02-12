
#include <stdlib.h>
#include <stdio.h> 
#include <stddef.h>
#include <stdio.h> 
#include <stdint.h>
const char lights = 4;

void lightsInit() {
    pinMode(4, OUTPUT);
}

void lightsOn() {
    digitalWrite(4, HIGH);
}

void lightsOff() {
    digitalWrite(4, LOW);
}
//WRITING PWM SIGNALS
//-----------------------------------------------------------------------
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

const char motor = 10;

void motorInit() {
    pinMode(10, OUTPUT);
}

void motorPowPercent(float percent) {
    writePwm(motor, percent);
}
//Below is ON
#define CHAN_ACTIVE 980


const char a_chan = 17;
const char b_chan = 16;

const char a_power = 7;
const char b_power = 6;

void photoResInit() {
    pinMode(a_chan, INPUT);
    pinMode(b_chan, INPUT);

    pinMode(a_power, OUTPUT);
    pinMode(b_power, OUTPUT);
}

void photoResOn() {
    digitalWrite(a_power, HIGH);
    digitalWrite(b_power, HIGH);
}

void photoResOff() {
    digitalWrite(a_power, LOW);
    digitalWrite(b_power, LOW);
}

bool readChannel(int channel_pin) {
    if(analogRead(channel_pin) < CHAN_ACTIVE)
        return 1;
    return 0;
}
typedef struct WaveForm {
    bool a_chan[200];
    bool b_chan[200];
    unsigned long time[200];
}WaveForm;


WaveForm wave = {0};
int index = 0;
int cap = 200;
unsigned long start_time = 0;

ISR(TIMER2_OVF_vect) {
    if(index >= cap)
        TIMSK2 = 0; //stops interupt

    wave.a_chan[index] = readChannel(a_chan);
    wave.b_chan[index] = readChannel(b_chan);
    wave.time[index] = 1;//micros() - start_time;

    index += 1;
    TCNT2 = 250;
}

//Starts the channel iterupt
void readChannels() {
    TCCR2A = 0; //Initialize timer 1
    TCCR2B = 0; //More initialization of same timer

    TCCR2B |= 0b00000001; //Setting prescalar, smallest option for higher frequency
    TCNT2 = 250;

    start_time = micros();
    TIMSK2 |= 0b00000001; //Setting ovf interupt on
}

void printWaveForm() {
    while(index < cap) {
        Serial.println("---Waveform---");
    }
    int i = 0;
    while(i < cap) {
        Serial.print("A:");
        Serial.print(wave.a_chan[i]);
        Serial.print(" B:");
        Serial.print(wave.b_chan[i]);
        Serial.print(" T:");
        Serial.println(wave.time[i]);
        
        i += 1;
    }
}
//If Lower is on

void setup() {
    Serial.begin(9600);

    lightsInit();
    lightsOn();

    photoResInit();
    photoResOn();

    motorInit();
    motorPowPercent(0.23);
    delay(10000);

    readChannels();
    printWaveForm();

}

void loop() {
//    Serial.print("A: ");
//    Serial.println(readChannel(a_chan));
//
//    Serial.print("B: ");
//    Serial.println(readChannel(b_chan));
//    delay(200);
}
