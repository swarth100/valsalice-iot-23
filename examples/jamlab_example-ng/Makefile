DEFINES=PROJECT_CONF_H=\"project-conf.h\"


# Configure nullmac and other aspects
MAKE_MAC = MAKE_MAC_NULLMAC

# Define the target platform
ifndef TARGET
TARGET=sky
endif

# Give a name to your project
CONTIKI_PROJECT = jamlab_example

# Compile project typing "make"
all: $(CONTIKI_PROJECT)

# Upload project typing "make upload"
upload: $(CONTIKI_PROJECT).upload

# Reset nodes
reset: sky-reset

ifdef JAMLAB_TYPE
  CFLAGS += -DJAMLAB_TYPE=$(JAMLAB_TYPE)
endif
ifdef AMOUNT_NODES_INVOLVED
  CFLAGS += -DAMOUNT_NODES_INVOLVED=$(AMOUNT_NODES_INVOLVED)
endif

# Define additional source files to be compiled (if any)
CONTIKI_TARGET_SOURCEFILES += settings_jamlab.c
CONTIKI_TARGET_SOURCEFILES += settings_cc2420_rssi.c
CONTIKI_TARGET_SOURCEFILES += settings_noisefloor_sampling.c

#Normal Contiki
CONTIKI=../..
include $(CONTIKI)/Makefile.include

# Specify the custom linker script
LDFLAGS += -T custom_memory.ld

# Including Math library
CUSTOM_RULE_LINK=1
%.$(TARGET): %.co $(PROJECT_OBJECTFILES) $(PROJECT_LIBRARIES) contiki-$(TARGET).a
	$(LD) $(LDFLAGS) $(TARGET_STARTFILES) ${filter-out %.a,$^} ${filter %.a,$^} $(TARGET_LIBFILES) -o $@ -lm
