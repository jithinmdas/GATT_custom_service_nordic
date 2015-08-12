/** @file
 * 
 * @author  Jithin M Das
 * 
 * @brief   Application main file
 */
 
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "timer_handler.h"
#include "uart_handler.h"
#include "nordic_common.h"
#include "softdevice_handler.h"

#define IS_SRVC_CHANGED_CHARACT_PRESENT 0

void scheduler_init(void);
static void ble_evt_handler(ble_evt_t * p_ble_evt);

void ble_stack_init()
{
    uint32_t err_code;
    
    // Initialize soft_device
    SOFTDEVICE_HANDLER_INIT(NRF_CLOCK_LFCLKSRC_XTAL_20_PPM, NULL);
    
    // Enable BLE stack.
    ble_enable_params_t ble_enable_params;
    memset(&ble_enable_params, 0, sizeof(ble_enable_params));
    ble_enable_params.gatts_enable_params.service_changed = IS_SRVC_CHANGED_CHARACT_PRESENT;
    err_code = sd_ble_enable(&ble_enable_params);
    APP_ERROR_CHECK(err_code);
    
    // Subscribe for BLE events.
    err_code = softdevice_ble_evt_handler_set(ble_evt_handler);
    APP_ERROR_CHECK(err_code);
}

static void ble_evt_handler(ble_evt_t * p_ble_evt)
{
}

int main(void)
{
    timer_init();
    uart_init();
    printf("Hello world\n");
    ble_stack_init();
    for(;;)
    {

    }
}
