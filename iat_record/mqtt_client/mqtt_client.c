

#include <mosquitto.h>
#include <glib.h>

#include "mqtt_client.h"

int light_controller_action(const char* item, const char* action)
{
    g_print("Debug: Control light '%s' action '%s'...\n", item, action);

//TBD "TODO: add API to control light here..."

    return RET_OK;
}


gpointer
mqtt_receive_thread(gpointer data)
{
    int ret = RET_ERROR;
    GLOBAL_PARAM_T* parent_data = (GLOBAL_PARAM_T*)data;

    if (parent_data == NULL || parent_data->master == NULL || parent_data->target == NULL) {
        g_print("ERROR: the input params for mqtt thread is error, please check!\n");
        return NULL;
    }
    parent_data->mqtt_exit = THREAD_EXIT_CODE_RUNNING;

    ret = mqtt_sub_client_recv(parent_data->master, parent_data->target, light_controller_action);
    if (ret != RET_OK) {
        g_print("ERROR: Start MQTT sub client failed!\n");
        parent_data->mqtt_exit = THREAD_EXIT_CODE_ERROR;
    } else {
        parent_data->mqtt_exit = THREAD_EXIT_CODE_QUIT;
    }

    return NULL;
}


