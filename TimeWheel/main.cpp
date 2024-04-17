#include <iostream>

#include "TimeWheel.hpp"

int count111 = 0;

void func() {
    cout << "Timer " << count111 << " expired!" << endl;
    count111++;
}

int main() {
    TimerManager timer_manager(60, 1000);
    timer_manager.addTimer(3000, func);
    timer_manager.addTimer(8000, func);
    timer_manager.start();
    while (true) {
    }
    return 0;
}