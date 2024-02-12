typedef struct WaveForm {
    bool a_chan[280];
    bool b_chan[280];
    unsigned long time[280];
}WaveForm;

WaveForm wave = {0};

unsigned long time = 0;
//(256 - preload) * (1/ratio) * (1/16*10^6)
const unsigned long delta_clock = 1.6; //Microseconds

int index = 0;
const int cap = 280;

ISR(TIMER2_OVF_vect) {
    if(index >= cap)
        TIMSK2 = 0; //stops interupt

    wave.a_chan[index] = readChannel(a_chan);
    wave.b_chan[index] = readChannel(b_chan);

    wave.time[index] = time;
    time += delta_clock; 

    index += 1;
    //TCNT2 = 250; //Preloading
}

//Starts the channel iterupt
void readChannels() {
    TCCR2A = 0; //Initialize timer 1
    TCCR2B = 0; //More initialization of same timer

    TCCR2B |= 0b00000001; //Setting prescalar, smallest option for higher frequency
    //TCNT2 = 250; //Preloading

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
    Serial.println("---End---Waveform---");
}

//How far is B following A maxiumum
int maxBOffset() {
    int max_offset = 0;
    int current_offset = 0;
    bool prev_a = 1;

    //This method is flawed bc it does not handle if chan_a 1->0 
    //before chan_b 0->1
    int index = 0;
    while(index < cap) {
        if(prev_a == 0 && wave.a_chan[index] == 1) {
            while(index < cap) {
                if(wave.b_chan[index] == (bool)1) {
                    if(current_offset > max_offset)
                        max_offset = current_offset;
                    current_offset = 0;
                    break; //This is the end of the offset
                }
                else {
                    current_offset += 1; //This is another b offset
                }

                prev_a = wave.a_chan[index];
                index += 1;
            }
        }

        prev_a = wave.a_chan[index];
        index += 1;
    }

    return max_offset;
        //A goes to 1 from 0
        //How many B 0's are there until its 1
        //repeat every A 0 to 1 change
}

bool determineDirection() {
    int offset = maxBOffset();
    if(offset > 14) {
        return 1;
    }
    return 0;
}

float avgSpeed() {
    bool prev_b = 0;
    unsigned long t1 = 0;
    unsigned long t2 = 0;

    int i = 0;
    while(i < cap) {
        if(wave.b_chan[i] == (bool)0 && prev_b == (bool)1) {
            t1 = wave.time[i];
            prev_b = wave.b_chan[i];
            break;
        }

        prev_b = wave.b_chan[i];
        i += 1;
    }
    //At B 1->0

    while(i < cap) {
        if(wave.b_chan[i] == (bool)0 && prev_b == (bool)1) {
            t2 = wave.time[i];
            prev_b = wave.b_chan[i];
            break;
        }

        prev_b = wave.b_chan[i];
        i += 1;
    }
    //At next B 1->0

    float dt = (t2 - t1);
    //Time from B 1->0->1 

    return (90*1000000*60)/(dt*360);

}
