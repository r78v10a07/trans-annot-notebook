/* 
 * File:   TimeUtils.h
 * Author: veraalva
 *
 * Created on February 16, 2016, 8:49 AM
 */

#ifndef TIMEUTILS_H
#define TIMEUTILS_H

class TimeUtils {
public:

    static TimeUtils *instance() {
        if (!s_instance)
            s_instance = new TimeUtils;
        return s_instance;
    }

    void SetStartTime() {
        startTime = clock();
    }

    void SetClock() {
        begin = clock();
    }

    double GetTimeSec() {
        return double(clock() - begin) / CLOCKS_PER_SEC;
    }

    double GetTimeMin() {
        return GetTimeSec() / 60;
    }

    double GetTimeHour() {
        return GetTimeSec() / 3600;
    }

    double GetElapseTimeSec() {
        return double(clock() - startTime) / CLOCKS_PER_SEC;
    }

    double GetElapseTimeMin() {
        return GetElapseTimeSec() / 60;
    }

    double GetElapseTimeHour() {
        return GetElapseTimeSec() / 3600;
    }

    double GetTimeSecFrom(clock_t b) {
        return double(clock() - b) / CLOCKS_PER_SEC;
    }

    double GetTimeMinFrom(clock_t b) {
        return GetTimeSecFrom(b) / 60;
    }

    double GetTimeHourFrom(clock_t b) {
        return GetTimeSecFrom(b) / 3600;
    }
private:
    clock_t begin;
    clock_t startTime;
    static TimeUtils *s_instance;
};

#endif /* TIMEUTILS_H */

