#ifndef I_GPIO_PORT_HPP
#define I_GPIO_PORT_HPP

#include <cstdint>

namespace ports
{

    /**
     * @brief GPIO Port Interface
     *
     * Abstract interface for GPIO operations in hexagonal architecture.
     * Adapters implement this interface for specific hardware.
     */
    class IGpioPort
    {
    public:
        virtual ~IGpioPort() = default;

        /**
         * @brief Set GPIO pin level
         * @param pin GPIO pin number
         * @param value true for high, false for low
         * @return 0 on success, negative error code on failure
         */
        virtual int setLevel(uint32_t pin, bool value) = 0;

        /**
         * @brief Get GPIO pin level
         * @param pin GPIO pin number
         * @return Pin level (0 or 1), or negative error code
         */
        virtual int getLevel(uint32_t pin) = 0;

        /**
         * @brief Configure GPIO pin as output
         * @param pin GPIO pin number
         * @return 0 on success, negative error code on failure
         */
        virtual int configureOutput(uint32_t pin) = 0;
    };

} // namespace ports

#endif // I_GPIO_PORT_HPP
