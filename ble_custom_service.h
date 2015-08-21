#include <stdint.h>
#include <stdbool.h>
#include "ble.h"

#define BLE_CUS_MAX_DATA_LEN (GATT_MTU_SIZE_DEFAULT - 3)
#define BLE_UUID_CUS_SERVICE 0x0001 

typedef struct ble_cus_s ble_cus_t;

typedef void (*ble_cus_data_handler_t) (ble_cus_t * p_cus, uint8_t * p_data, uint16_t length);

typedef void (*ble_cus_data_handler_t) (ble_cus_t * p_nus, uint8_t * p_data, uint16_t length);

typedef struct
{
    ble_cus_data_handler_t data_handler; /**< Event handler to be called for handling received data. */
} ble_cus_init_t;

struct ble_cus_s
{
    uint8_t                  uuid_type;               
    uint16_t                 service_handle;          
    ble_gatts_char_handles_t cus_send_handles;              
    ble_gatts_char_handles_t cus_recv_handles;              
    uint16_t                 conn_handle;             
    bool                     is_notification_enabled; 
    ble_cus_data_handler_t   data_handler;            
};

static void on_connect(ble_cus_t * p_cus, ble_evt_t * p_ble_evt);
uint32_t ble_cus_init(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init);
uint32_t ble_cus_string_send(ble_cus_t * p_cus, uint8_t * p_string, uint16_t length);
