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
