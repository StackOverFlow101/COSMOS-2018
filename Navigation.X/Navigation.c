void Forward(int speed) {
    Roach_LeftMtrSpeed(speed);
    Roach_RightMtrSpeed(speed);
}

void Reverse(int speed) {
    Roach_LeftMtrSpeed(-speed);
    Roach_RightMtrSpeed(-speed);
}

void Stop(void) {
    Roach_LeftMtrSpeed(0);
    Roach_RightMtrSpeed(0);
}

void RotateRight(int speed) {
    Roach_LeftMtrSpeed(speed);
    Roach_RightMtrSpeed(-speed);
}

void RotateLeft(int speed) {
    Roach_LeftMtrSpeed(-speed);
    Roach_RightMtrSpeed(speed);
}

void PivotLeft(int speed) {
    Roach_LeftMtrSpeed(0);
    Roach_RightMtrSpeed(speed);
}

void PivotRight(int speed) {
    Roach_LeftMtrSpeed(speed);
    Roach_RightMtrSpeed(0);
}

void ArcLeft(int speed) {
    Roach_LeftMtrSpeed((int) (speed * 0.8));
    Roach_RightMtrSpeed(speed);
}

void ArcRight(int speed) {
    Roach_RightMtrSpeed((int) (speed * 0.8));
    Roach_LeftMtrSpeed(speed);
}