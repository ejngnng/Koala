

#ifndef _MQTT_CLIENT_H_
#define _MQTT_CLIENT_H_

#include <glib.h>
#include <voice_config.h>


#define VOICE_MQTT_RECV_THREAD_NAME "mqtt_recv_th"

gpointer mqtt_receive_thread(gpointer data);

typedef int (*recv_action_func)(const char*, const char*);

int mqtt_pub_client(const char* master_addr, const char* target, const char* action_msg);
int mqtt_sub_client_recv(const char* master_addr, const char* target, recv_action_func action_cb);


#endif /* _MQTT_CLIENT_H_ */
