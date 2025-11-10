#include "BlinkLedUseCase.h"
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(blink_usecase, LOG_LEVEL_DBG);

namespace usecases
{

    // Define thread stack outside the class
    K_THREAD_STACK_DEFINE(blink_stack, BlinkLedUseCase::THREAD_STACK_SIZE);

    BlinkLedUseCase::BlinkLedUseCase(ports::IGpioPort &gpioPort)
        : gpioPort_(gpioPort), threadId_(nullptr), isOn_(false), threadStack_(blink_stack)
    {
    }

    int BlinkLedUseCase::initialize()
    {
        int ret = gpioPort_.configureOutput(LED_PIN);
        if (ret < 0)
        {
            LOG_ERR("Failed to configure LED pin: %d", ret);
            return ret;
        }

        LOG_INF("Blink LED use case initialized (pin=%d, interval=%dms)",
                LED_PIN, BLINK_INTERVAL_MS);
        return 0;
    }

    int BlinkLedUseCase::startThread()
    {
        threadId_ = k_thread_create(
            &threadData_,
            threadStack_,
            THREAD_STACK_SIZE,
            run,
            this,
            nullptr,
            nullptr,
            THREAD_PRIORITY,
            0,
            K_NO_WAIT);

        if (threadId_ == nullptr)
        {
            LOG_ERR("Failed to create blink thread");
            return -ENOMEM;
        }

        k_thread_name_set(threadId_, "blink");
        LOG_INF("Blink thread started");
        return 0;
    }

    void BlinkLedUseCase::run(void *arg1, void *arg2, void *arg3)
    {
        BlinkLedUseCase *useCase = static_cast<BlinkLedUseCase *>(arg1);

        while (true)
        {
            useCase->isOn_ = !useCase->isOn_;
            useCase->gpioPort_.setLevel(LED_PIN, useCase->isOn_);

            LOG_INF("LED state: %s", useCase->isOn_ ? "ON" : "OFF");

            k_msleep(BLINK_INTERVAL_MS);
        }
    }

} // namespace usecases
