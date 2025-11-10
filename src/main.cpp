#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "adapters/LedAdapter.h"
#include "usecases/BlinkLedUseCase.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

int main(void)
{
    adapters::LedAdapter gpioAdapter;

    usecases::BlinkLedUseCase blinkUseCase(gpioAdapter);

    blinkUseCase.initialize();
    blinkUseCase.startThread();

    while (true)
    {
        k_sleep(K_MSEC(1000));
    }

    return 0;
}
