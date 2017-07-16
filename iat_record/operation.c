#include <stdio.h>
#include <mqtt_client.h>
#include <time.h>

#include "asr_parse_api.h"





int parse_and_operation(const char* asr_result) 
{
        FILE *fp;
	char master[128] = {0};
	char *target = "inTopic";
	char *message = "{\"name\":\"switch\",\"target_id\":\"switch1\",\"action\":\"turn on\",\"value\":\"1\"}";
        //char *voice = "请打开厨房的灯";
	char *voice = asr_result;
        char msg[200] = {0};

	int rc;

        voice_init();
	voice_parse_to_message(voice, msg);

	printf("voice: %s\n", voice);
	printf("parse to: %s\n", msg);

	fp = fopen("/etc/config/ssdp_client", "r");
	if(fp)
	{
	    fread(master, 1, 128, fp);	
	    printf("get ssdp_server %s\n", master);
	}
	else
	    sprintf(master, "%s", "127.0.0.1");
	

//	rc = mqtt_pub_client(master, target, message);
	rc = mqtt_pub_client(master, target, msg);

	printf("mqtt_pub, return %d, %ld\n", rc, time(NULL));

        voice_destroy();
	return 0;
}
