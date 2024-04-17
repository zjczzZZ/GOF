#include <chrono>
#include <functional>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <vector>

using namespace std;

typedef function<void()> TimerCallback;

class Timer {
public:
    Timer(int interval, TimerCallback callback)
        : interval_(interval),
          callback_(callback) {
    }

    void run() {
        callback_();
    }

    int getInterval() const {
        return interval_;
    }

private:
    int interval_;
    TimerCallback callback_;
};

class TimeWheel {
public:
    TimeWheel(int slot_num, int interval)
        : slot_num_(slot_num),
          interval_(interval),
          cur_slot_(0),
          slots_(slot_num) {
    }

    void start() {
        thread t([&]() {
            while (true) {
                int next_slot = (cur_slot_ + 1) % slot_num_;
                vector<Timer*> expired_timers = move(slots_[next_slot]);
                for (auto timer : expired_timers) {
                    timer->run();
                    delete timer;
                }
                cur_slot_ = next_slot;
                this_thread::sleep_for(chrono::milliseconds(interval_));
            }
        });
        t.detach();
    }

    void addTimer(Timer* timer) {
        int expiration = (cur_slot_ + timer->getInterval() / interval_) % slot_num_;
        slots_[expiration].push_back(timer);
    }

private:
    int slot_num_;
    int interval_;
    int cur_slot_;
    vector<vector<Timer*>> slots_;
};

class TimerManager {
public:
    TimerManager(int slot_num, int interval)
        : time_wheel_(slot_num, interval) {
    }

    void addTimer(int interval, TimerCallback callback) {
        Timer* timer = new Timer(interval, callback);
        time_wheel_.addTimer(timer);
    }

    void start() {
        time_wheel_.start();
    }

private:
    TimeWheel time_wheel_;
};
