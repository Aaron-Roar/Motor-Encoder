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
