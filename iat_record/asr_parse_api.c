#include <string.h>
#include "syntax.h"





int voice_initialized = 0;

Sentence line; /* store the voice content data */
Action action; /* store the parsed result data, used to output */
Syntax syntax; /* syntax engine, syntax data */



int voice_init()
{
    if (voice_sentence_init(&line) != STATUS_SUCCESS) {
        voice_log_error("Voice sentence init failed!\n");
        return STATUS_FAILED;
    }

    if (voice_action_init(&action) != STATUS_SUCCESS) {
        voice_log_error("Voice action init failed!\n");
        return STATUS_FAILED;
    }

    if (voice_syntax_init(&syntax) != STATUS_SUCCESS) {
        voice_log_error("Voice syntax init failed!\n");
        return STATUS_FAILED;
    }

    voice_initialized = 1;

    voice_log_debug("Voice init finished!\n");
    return STATUS_SUCCESS;
}

int voice_destroy()
{
    return voice_meta_tree_destory(&((&syntax)->tree));

    return STATUS_FAILED;
}

int voice_parse_to_message(const char* voice_data, char* message)
{
    Action* act = &action;
    unsigned int index = 0;
    char* value;
    int type = 0;
    char filedName[50] = {0};
    char filedTarget[50] = {0};
    char filedAction[50] = {0};
    char filedValue[50] = {0};
    int ret = STATUS_FAILED;

    strcat(filedName, "\"name\":\"switch\",");
    strcat(filedTarget, "\"target_id\":");
    strcat(filedAction, "\"action\":\"turn on\",");
    strcat(filedValue, "\"value\":");

    if(voice_initialized != 1) {
        voice_log_debug("error, voic not initialized\n");
        return STATUS_FAILED;	
    }

    if (voice_sentence_set_data(&line, voice_data) != STATUS_SUCCESS) {
        voice_log_error("Set sentence data failed!\n");

        /* if app exit, the memory must be free */
        voice_destroy(&syntax);
        return STATUS_FAILED;
    }

    /* main process: input: line, process: syntax, output: action */
    if (voice_syntax_parse_sentece(&syntax, &line, &action) == STATUS_SUCCESS) {
        voice_log_debug("Voice syntax parse sentence success!\n");

        /* generate the output data to the format of what we want. */


        voice_log_info(" ---- Gen Result ----\n");
        for (index = 0; index < act->length; index++) {
            type = voice_token_get_type(act->list[index]);
            value = voice_token_get_value(act->list[index]);

            /* 开/关 */
            if(type == 3) {
                if(strcmp(value, "开") == 0)
                    strcat(filedValue, "\"1\"");
                else
                    strcat(filedValue, "\"0\"");
            }
            /* 厨房/客厅/卧室 */
            else if(type == 1) {
                if(strcmp(value, "厨房") == 0)
                    strcat(filedTarget, "\"switch1\",");
                else if(strcmp(value, "客厅") == 0)
                    strcat(filedTarget, "\"switch2\",");
                else if(strcmp(value, "卧室") == 0)
                    strcat(filedTarget, "\"switch3\",");
            }

            voice_log_info("  Step %d: token: %s, type: %d\n", index + 1, value, type);
        }

        strcat(message, "{");
        strcat(message, filedName);
        strcat(message, filedTarget);
        strcat(message, filedAction);
        strcat(message, filedValue);
        strcat(message, "}");

        /* free memroy */
        voice_destroy(&syntax);
        return ret;
    } else {
        voice_log_debug("Voice syntax parse sentence failed!\n");
    }

    return 0;
}

