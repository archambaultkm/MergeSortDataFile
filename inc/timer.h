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
    long m_time_elapsed_ms; // elapsed time in microseconds
    long m_time_elapsed_s;

public:
    /**
     * @brief Default constructor.
     */
    Timer() : m_start_time(Clock::now()), m_duration(Clock::now()), m_time_elapsed_ms(0), m_time_elapsed_s(0) {}

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
        //m_time_elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(duration - m_start_time).count();
        //m_time_elapsed_s = std::chrono::duration_cast<std::chrono::seconds>(duration - m_start_time).count();
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
};
#endif //ASSIGNMENT_3_TIMER_H
