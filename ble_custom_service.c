#include "ble_srv_common.h"
#include "ble_custom_service.h"
#include "nordic_common.h"
#include <string.h>

static void on_connect(ble_cus_t * p_cus, ble_evt_t * p_ble_evt)
{
    p_cus->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
}

static void on_disconnect(ble_cus_t * p_cus, ble_evt_t * p_ble_evt)
{
    UNUSED_PARAMETER(p_ble_evt);
    p_cus->conn_handle = BLE_CONN_HANDLE_INVALID;
}

static void on_write(ble_cus_t * p_cus, ble_evt_t * p_ble_evt)
{
    ble_gatts_evt_write_t * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;
    
    if((p_evt_write->handle == p_cus->cus_recv_handles.cccd_handle) && (p_evt_write->data))
    {
        if(ble_srv_is_notification_enabled(p_evt_write->data))
        {
            p_cus->is_notification_enabled = true;
        }
        else
        {
            p_cus->is_notification_enabled = false;
        }
    }
    else if((p_evt_write->handle == p_cus->cus_send_handles.value_handle) && (p_cus->data_handler != NULL))
    {
        p_cus->data_handler(p_cus, p_evt_write->data, p_evt_write->len);
    }
    else
    {
    }
}
