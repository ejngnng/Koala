/*
* Description: record from mic use ALSA api
* 
* Author: ninja
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "qisr.h"
#include "msp_cmn.h"
#include "msp_errors.h"
#include "speech_recognizer.h"

/* interrupt and operation after asr */
#include <wiringPi.h>
#include "operation.h"

/* global variables for interrupt */
volatile int isr_flag = 0;
int isr_pin = 6; // BCM GPIO 25

#define FRAME_LEN	640 
#define	BUFFER_SIZE	4096


static void show_result(char *string, char is_over)
{
	printf("\rResult: [ %s ]", string);
	if(is_over)
		putchar('\n');
}

static char *g_result = NULL;
static unsigned int g_buffersize = BUFFER_SIZE;

void on_result(const char *result, char is_last)
{
	if (result) {
		size_t left = g_buffersize - 1 - strlen(g_result);
		size_t size = strlen(result);
		if (left < size) {
			g_result = (char*)realloc(g_result, g_buffersize + BUFFER_SIZE);
			if (g_result)
				g_buffersize += BUFFER_SIZE;
			else {
				printf("mem alloc failed\n");
				return;
			}
		}
//		strncat(g_result, result, size);
//		show_result(g_result, is_last);
		parse_and_operation(result);
	}
}
void on_speech_begin()
{
	if (g_result)
	{
		free(g_result);
	}
	g_result = (char*)malloc(BUFFER_SIZE);
	g_buffersize = BUFFER_SIZE;
	memset(g_result, 0, g_buffersize);

	printf("Start Listening...\n");
}
void on_speech_end(int reason)
{
	if (reason == END_REASON_VAD_DETECT){
		printf("\nSpeaking done \n");
		return;
	}else {
		printf("\nRecognizer error %d\n", reason);
		return;
	}
}


/* demo recognize the audio from microphone */
static void demo_mic(const char* session_begin_params)
{
	int errcode;
	int i = 0;

	struct speech_rec iat;

	struct speech_rec_notifier recnotifier = {
		on_result,
		on_speech_begin,
		on_speech_end
	};

	errcode = sr_init(&iat, session_begin_params, SR_MIC, &recnotifier);
	if (errcode) {
		printf("speech recognizer init failed\n");
		return;
	}
	errcode = sr_start_listening(&iat);
	if (errcode) {
		printf("start listen failed %d\n", errcode);
	}
	/* demo 15 seconds recording */
	while(i++ < 15)
		sleep(1);
	errcode = sr_stop_listening(&iat);
	if (errcode) {
		printf("stop listening failed %d\n", errcode);
	}
	sr_uninit(&iat);
}

/* wiringPi interrupt callback */
void isr_cb(){
	printf("interrupt happy...\n");
	isr_flag = 1;
}

/* wiringPi interrupt init */
void isr_setup(){

	wiringPiSetup();
	pinMode(isr_pin, INPUT);
	pullUpDnControl(isr_pin, PUD_UP);
	wiringPiISR(isr_pin, INT_EDGE_FALLING, isr_cb);

}

/*
 * main thread: start/stop record ; query the result of recgonization.
 * record thread: record callback(data write)
 */
 int main(int argc, char* argv[])
 {	
 	int ret = MSP_SUCCESS;
 	/* login params, please do keep the appid correct */
 	const char* login_params = "appid = 58cbfb41, work_dir = .";

 	/*
 	* See "iFlytek MSC Reference Manual"
 	*/
 	const char* session_begin_params =
 		"sub = iat, domain = iat, language = zh_cn, "
 		"accent = mandarin, sample_rate = 16000, "
 		"result_type = plain, result_encoding = utf8";

 	/* Login first. the 1st arg is username, the 2nd arg is password
 	 * just set them as NULL. the 3rd arg is login paramertes 
 	 * */
 	ret = MSPLogin(NULL, NULL, login_params);
 	if (MSP_SUCCESS != ret)	{
 		printf("MSPLogin failed , Error code %d.\n",ret);
 		goto exit; // login fail, exit the program
 	}
	
	isr_setup();	

	while(1){
		if(isr_flag){
			isr_flag = 0;
			demo_mic(session_begin_params);
		}
	}

exit:
 	MSPLogout(); // Logout...
 	return 0;
}


