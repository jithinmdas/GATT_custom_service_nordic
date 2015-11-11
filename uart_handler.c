/** @file
 * 
 * @author  Jithin M Das
 * 
 * @brief   Application uart handler c file
 */

#include "uart_handler.h"
#include "nrf51_bitfields.h"
#include "app_error.h"
#include "app_uart.h"
#include "ble_custom_service.h"
#include "nordic_common.h"

#define RX_PIN_NUMBER  11
#define TX_PIN_NUMBER  9
#define CTS_PIN_NUMBER 10
#define RTS_PIN_NUMBER 8

#define UART_TX_BUF_SIZE                256
#define UART_RX_BUF_SIZE                256

void uart_evt_handler(app_uart_evt_t * p_event);

void uart_init(void)
{
    uint32_t err_code;
    const app_uart_comm_params_t comm_params = {
        RX_PIN_NUMBER,
        TX_PIN_NUMBER,
        RTS_PIN_NUMBER,
        CTS_PIN_NUMBER,
        APP_UART_FLOW_CONTROL_DISABLED,
        false,
        UART_BAUDRATE_BAUDRATE_Baud38400
    };
    
    APP_UART_FIFO_INIT( &comm_params,
                        UART_RX_BUF_SIZE,
                        UART_TX_BUF_SIZE,
                        uart_evt_handler,
                        APP_IRQ_PRIORITY_LOW,
                        err_code );
    APP_ERROR_CHECK(err_code);
}

void uart_evt_handler(app_uart_evt_t * p_event)
{
    
    static uint8_t data_array[BLE_CUS_MAX_DATA_LEN];
    static uint8_t index = 0;
    uint32_t       err_code;

    switch (p_event->evt_type)
    {
        case APP_UART_DATA_READY:
            UNUSED_VARIABLE(app_uart_get(&data_array[index]));
            index++;

            if ((data_array[index - 1] == '\n') || (index >= (BLE_CUS_MAX_DATA_LEN)))
            {
                err_code = ble_cus_string_send(&m_cus, data_array, index);
                if (err_code != NRF_ERROR_INVALID_STATE)
                {
                    APP_ERROR_CHECK(err_code);
                }
                
                index = 0;
            }
            break;

        case APP_UART_COMMUNICATION_ERROR:
            APP_ERROR_HANDLER(p_event->data.error_communication);
            break;

        case APP_UART_FIFO_ERROR:
            APP_ERROR_HANDLER(p_event->data.error_code);
            break;

        default:
            break;
    }
}
