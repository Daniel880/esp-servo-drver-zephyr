#ifndef BLINK_LED_USE_CASE_H
#define BLINK_LED_USE_CASE_H

#include "../ports/IGpioPort.hpp"
#include <cstdint>
#include <zephyr/kernel.h>

namespace usecases
{

    /**
     * @brief Blink LED Use Case
     *
     * Contains business logic for blinking an LED.
     * Framework-agnostic, depends only on the port interface.
     * Runs in its own thread.
     */
    class BlinkLedUseCase
    {
    public:
        static constexpr uint8_t LED_PIN = 2;
        static constexpr uint32_t BLINK_INTERVAL_MS = 200;
        static constexpr uint32_t THREAD_STACK_SIZE = 1024;
        static constexpr int THREAD_PRIORITY = 5;

        explicit BlinkLedUseCase(ports::IGpioPort &gpioPort);

        /**
         * @brief Initialize the use case
         * @return 0 on success, negative error code on failure
         */
        int initialize();

        /**
         * @brief Start the blink thread
         * @return 0 on success, negative error code on failure
         */
        int startThread();

    private:
        static void run(void *arg1, void *arg2, void *arg3);

        ports::IGpioPort &gpioPort_;
        k_tid_t threadId_;
        bool isOn_;

        k_thread threadData_;
        k_thread_stack_t *threadStack_;
    };

} // namespace usecases

#endif // BLINK_LED_USE_CASE_H
