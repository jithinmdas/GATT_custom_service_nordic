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
#include "ble_gap.h"

#define IS_SRVC_CHANGED_CHARACT_PRESENT 0
#define DEVICE_NAME                     "Custom_Service"

#define CONN_SUP_TIMEOUT    MSEC_TO_UNITS(4000, UNIT_10_MS) 
#define MAX_CONN_INTERVAL   MSEC_TO_UNITS(75, UNIT_1_25_MS)
#define MIN_CONN_INTERVAL   MSEC_TO_UNITS(20, UNIT_1_25_MS)
#define SLAVE_LATENCY       0

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

/**@brief Function for the GAP initialization.
 *
 * @details This function will set up all the necessary GAP (Generic Access Profile) parameters of 
 *          the device. It also sets the permissions and appearance.
 */
void gap_params_init()
{
    uint32_t err_code;
    ble_gap_conn_sec_mode_t sec_mode;
    ble_gap_conn_params_t ble_gap_conn_params;
    
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);
    
    err_code = sd_ble_gap_device_name_set(&sec_mode, (const uint8_t *)DEVICE_NAME, strlen(DEVICE_NAME));
    APP_ERROR_CHECK(err_code);
    
    memset(&ble_gap_conn_params, 0, sizeof(ble_gap_conn_params));
    ble_gap_conn_params.conn_sup_timeout = CONN_SUP_TIMEOUT;
    ble_gap_conn_params.max_conn_interval = MAX_CONN_INTERVAL;
    ble_gap_conn_params.min_conn_interval = MIN_CONN_INTERVAL;
    ble_gap_conn_params.slave_latency = SLAVE_LATENCY;
    
    err_code = sd_ble_gap_ppcp_set(&ble_gap_conn_params);
    APP_ERROR_CHECK(err_code);
}

int main(void)
{
    timer_init();
    uart_init();
    printf("Hello world\n");
    ble_stack_init();
    gap_params_init();
    for(;;)
    {

    }
}
