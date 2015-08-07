/** @file
 * 
 * @author  Jithin M Das
 * 
 * @brief   Application main file
 */

#include <stdio.h>
#include "timer_handler.h"
#include "uart_handler.h"
#include "app_scheduler.h"

static void scheduler_init(void);

int main(void)
{
    timer_init();
    uart_init();
    scheduler_init();
    printf("Hello world");
    
    for(;;)
    {
        app_sched_execute();
    }
}

static void scheduler_init()
{
    APP_SCHED_INIT( 
}
