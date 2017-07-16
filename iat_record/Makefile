#common makefile header

DIR_BIN = ../bin
DIR_LIB = ../libs

ASR_CFLAGS = -I../include/asr
ASR_LDFLAGS := -L$(DIR_LIB) -lmsc -lrt -ldl -lpthread -lwiringPi -lasound


MQTT_VERSION := 1.4.11
#MQTT_VERSION := 0.15

GLIB2_CFLAGS = $(shell pkg-config --cflags glib-2.0 gobject-2.0 gthread-2.0 gssdp-1.0)
GLIB2_LDFLAGS = $(shell pkg-config --libs glib-2.0 gobject-2.0 gthread-2.0 gssdp-1.0)

MQTT_CFLAGS  = -DVERSION="\"$(MQTT_VERSION)\""
MQTT_LDFLAGS = -lmosquitto

ASR_PARSE_CFLAGS  = -I../include/asr_parse
ASR_PARSE_LDFLAGS = -L$(DIR_LIB) -lsemantic


CFLAGS := -Wall -g -fPIC \
        $(ASR_CFLAGS) $(GLIB2_CFLAGS) $(MQTT_CFLAGS) $(ASR_PARSE_CFLAGS) \
        -I./mqtt_client -I../include
LDFLAGS := $(ASR_LDFLAGS) $(GLIB2_LDFLAGS) $(MQTT_LDFLAGS) $(ASR_PARSE_LDFLAGS)



TARGET	= asr 
BIN_TARGET = $(DIR_BIN)/$(TARGET)

SRC := $(wildcard *.c) $(wildcard mqtt_client/*.c) $(wildcard mqtt_client/mosquitto-$(MQTT_VERSION)/*.c)
OBJECTS := $(patsubst %.c,%.o, $(SRC))

$(TARGET) : $(OBJECTS)
	gcc $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@cp $(TARGET) $(DIR_BIN)

%.o : %.c
	gcc -c $(CFLAGS) $< -o $@


clean:
	@rm -f $(OBJECTS) $(TARGET) $(BIN_TARGET)

.PHONY:clean

#common makefile foot
