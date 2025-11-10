#ifndef LED_ADAPTER_H
#define LED_ADAPTER_H

#include "../ports/IGpioPort.hpp"
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

namespace adapters
{

    /**
     * @brief LED Adapter
     *
     * Implements IGpioPort using Zephyr's GPIO API for LED control.
     * This adapter connects the domain logic to Zephyr hardware.
     * Handles device tree configuration for led0.
     */
    class LedAdapter : public ports::IGpioPort
    {
    public:
        /**
         * @brief Create LED adapter from device tree (hardcoded to led0 alias)
         */
        LedAdapter();

        int setLevel(uint32_t pin, bool value) override;
        int getLevel(uint32_t pin) override;
        int configureOutput(uint32_t pin) override;

        const gpio_dt_spec *getSpec() const { return spec_; }

    private:
        const gpio_dt_spec *spec_;
    };

} // namespace adapters

#endif // LED_ADAPTER_H
