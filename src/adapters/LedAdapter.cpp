#include "LedAdapter.h"
#include <zephyr/logging/log.h>
#include <zephyr/devicetree.h>

LOG_MODULE_REGISTER(led_adapter, LOG_LEVEL_DBG);

namespace adapters
{

    // Static storage for device tree spec
    static struct gpio_dt_spec dt_spec_storage;

    LedAdapter::LedAdapter()
    {
// Get the device tree node from led0 alias
#define LED0_NODE DT_ALIAS(led0)

        // Initialize the static gpio_dt_spec from device tree
        dt_spec_storage = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
        spec_ = &dt_spec_storage;

        if (!gpio_is_ready_dt(spec_))
        {
            LOG_ERR("LED device not ready");
        }
        else
        {
            LOG_INF("LED adapter initialized (port=%p, pin=%d)",
                    spec_->port, spec_->pin);
        }
    }

    int LedAdapter::setLevel(uint32_t pin, bool value)
    {
        if (!device_is_ready(spec_->port))
        {
            LOG_ERR("GPIO device not ready");
            return -ENODEV;
        }

        return gpio_pin_set(spec_->port, pin, value ? 1 : 0);
    }

    int LedAdapter::getLevel(uint32_t pin)
    {
        if (!device_is_ready(spec_->port))
        {
            LOG_ERR("GPIO device not ready");
            return -ENODEV;
        }

        return gpio_pin_get(spec_->port, pin);
    }

    int LedAdapter::configureOutput(uint32_t pin)
    {
        if (!device_is_ready(spec_->port))
        {
            LOG_ERR("GPIO device not ready");
            return -ENODEV;
        }

        return gpio_pin_configure(spec_->port, pin, GPIO_OUTPUT_INACTIVE);
    }

} // namespace adapters
