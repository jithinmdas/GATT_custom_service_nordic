#include <stdint.h>
#include <stdbool.h>
#include "ble.h"

typedef struct ble_cus_s ble_cus_t;

typedef void (*ble_cus_data_handler_t) (ble_cus_t * p_cus, uint8_t * p_data, uint16_t length);

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
