/**
 * @file Timer.h
 * @brief A timer class template for measuring elapsed time.
 * @author Kaitlyn Archambault
 * @date 2023-11-01
 *
 */

#ifndef ASSIGNMENT_3_TIMER_H
#define ASSIGNMENT_3_TIMER_H

#include <chrono>

/**
 * @class Timer
 * @brief A timer class template that measures elapsed time using std::chrono.
 * @tparam Clock The clock type to use for timing (default: std::chrono::high_resolution_clock).
 */
template <typename Clock = std::chrono::high_resolution_clock>
class Timer {
private:
    typename Clock::time_point m_start_time; // starting time point
    typename Clock::time_point m_duration;

    struct ElapsedTime {
        long m_value;
        const char* m_unit;

        ElapsedTime(long val, const char* u) : m_value(val), m_unit(u) {}
    };

public:
    /**
     * @brief Default constructor.
     */
    Timer() : m_start_time(Clock::now()), m_duration(Clock::now()) {}

    /**
     * Measure the time it takes to execute a given function.
     * @param func The function to be measured.
     * @return The elapsed time in microseconds.
     */
    template <typename Func>
    void measure_function_time(const Func& func) {
        start();
        func();
        stop();
    }

    /**
     * Start the timer by recording the current time.
     */
    void start() {
        m_start_time = Clock::now();
    }

    /**
     * Stop the timer and calculate the elapsed time in microseconds.
     */
    void stop() {
        m_duration = Clock::now();
    }

    /**
     * @return The elapsed time in microseconds.
     */
    long get_elapsed_time_ms() {
        return std::chrono::duration_cast<std::chrono::microseconds>(m_duration - m_start_time).count();
    }

    /**
     * @return The elapsed time in seconds.
     */
    long get_elapsed_time_s() {
        return std::chrono::duration_cast<std::chrono::seconds>(m_duration - m_start_time).count();
    }


    ElapsedTime get_elapsed_time() {
        if (get_elapsed_time_s() > 0) {
            return ElapsedTime(get_elapsed_time_s(), "second(s)");
        } else {
            return ElapsedTime(get_elapsed_time_ms(), "microsecond(s)");
        }
    }
};
#endif //ASSIGNMENT_3_TIMER_H
