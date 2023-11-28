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
    long m_time_elapsed; // elapsed time in microseconds

public:
    /**
     * @brief Default constructor.
     */
    Timer() : m_start_time(Clock::now()), m_time_elapsed(0) {}

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
        auto duration = Clock::now();
        m_time_elapsed = std::chrono::duration_cast<std::chrono::microseconds>(duration - m_start_time).count();
    }

    /**
     * @return The elapsed time in microseconds.
     */
    long get_elapsed_time() {
        return m_time_elapsed;
    }

};
#endif //ASSIGNMENT_3_TIMER_H
