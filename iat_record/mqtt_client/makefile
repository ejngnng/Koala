# BINS = 
# xxx_CSRCS = 
# xxx_CXXSRCS =
# xxx_CFLAGS = 
# xxx_CXXFLAGS =
# xxx_LDFLAGS = 

# LIBS = 
# xxx_CSRCS = 
# xxx_CXXSRCS = 
# xxx_CFLAGS = 
# xxx_CXXFLAGS =
# xxx_LDFLAGS = 

# SUB_DIRS =

WORK_DIR ?= $(shell pwd)/..
PROJ_DIR ?= $(WORK_DIR)


LIBS = mqtt

#mqtt_CSRCS = client_shared.c pub_client.c sub_client.c mqtt_client.c
mqtt_CSRCS = $(wildcard ./mosquitto-$(MQTT_VERSION)/*.c) mqtt_client.c


include $(PROJ_DIR)/main.mk

