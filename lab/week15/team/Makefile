CONTIKI_PROJECT = receiver sender relay
CONTIKI = ../../..

MODULES_REL += $(TARGET)
MAKE_NET = MAKE_NET_NULLNET

all: $(CONTIKI_PROJECT)

include $(CONTIKI)/Makefile.include

# Include normal LAB makefile for testing, building etc
include ../../Makefile.include
