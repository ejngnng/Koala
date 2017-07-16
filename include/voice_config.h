/* 
 * Copyright (C) 2017
 *
 * Author: zhouzx
 *
 */

#ifndef _VOICE_CONFIG_H_
#define _VOICE_CONFIG_H_

#include <glib.h>

#define RET_OK      (0)
#define RET_ERROR   (-1)

typedef enum {
    VOICE_DEVICE_ROLE_NONE   = 0,
    VOICE_DEVICE_ROLE_MASTER = 1,
    VOICE_DEVICE_ROLE_CLIENT = 2,
} VOICE_DEV_ROLE_T;

#define VOICE_DEVICE_SET_ROLE(dev, dev_role)    do{(dev)->role |= (0x01 << dev_role);}while(0)
#define VOICE_DEVICE_CHECK_ROLE(dev, dev_role)  (((dev)->role) & (0x01 << dev_role))

#define THREAD_EXIT_CODE_ERROR     (-1)
#define THREAD_EXIT_CODE_NONE      (0)
#define THREAD_EXIT_CODE_QUIT      (1)
#define THREAD_EXIT_CODE_RUNNING   (2)
#define THREAD_EXIT_CODE_PENDING   (3)

#define THREAD_IS_EXIT(exit_code) (THREAD_EXIT_CODE_ERROR == (exit_code) || THREAD_EXIT_CODE_QUIT == (exit_code))

typedef struct _global_param_t_ {
    GMainLoop* loop;
    GThread*   mqtt_thread;
    int        mqtt_exit;

    GThread*   voice_thread;
    int        voice_exit;

    unsigned int role;

    char master[32];
    char standby[32];
    char target[32];

    char configuraton[128];
} GLOBAL_PARAM_T;

#define GLOBAL_PARAM_INIT {NULL,  \
                           NULL, THREAD_EXIT_CODE_NONE,     \
                           NULL, THREAD_EXIT_CODE_NONE,     \
                           0, {0}, {0}, {0},   \
                           {0}}

#define GLOBAL_PARAM_SET_ITEM_STR(param, item, str) strncpy((param)->item, (str), sizeof((param)->item) - 1)

extern GLOBAL_PARAM_T* voice_get_global_param(void);

#endif /* _VOICE_CONFIG_H_ */
