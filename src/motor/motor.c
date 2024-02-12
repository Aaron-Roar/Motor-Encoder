const char motor = 10;

void motorInit() {
    pinMode(10, OUTPUT);
}

void motorPowPercent(float percent) {
    writePwm(motor, percent);
}
