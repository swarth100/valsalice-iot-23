DEFINES=PROJECT_CONF_H=\"project-conf.h\"

# Define the target platform
ifndef TARGET
TARGET=sky
endif

# Define additional source files to be compiled (if any)
PROJECT_SOURCEFILES += settings_jamlab.c settings_cc2420_rssi.c settings_noisefloor_sampling.c

#Normal Contiki
CONTIKI = ../../../contiki-jamlab
include $(CONTIKI)/Makefile.include

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

# Including Math library
CUSTOM_RULE_LINK=1
%.$(TARGET): %.co $(PROJECT_OBJECTFILES) $(PROJECT_LIBRARIES) contiki-$(TARGET).a
	$(LD) $(LDFLAGS) $(TARGET_STARTFILES) ${filter-out %.a,$^} ${filter %.a,$^} $(TARGET_LIBFILES) -o $@ -lm
