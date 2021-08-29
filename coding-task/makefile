BUILDDIR = build
INCDIR = inc
SRCDIR = src
OUTPUTNAME = coding_task
LINKERNAME = linker

SOURCES += $(SRCDIR)/main.c \
		   $(SRCDIR)/bsp.c \
		   $(SRCDIR)/circular_buffer.c \
		   $(SRCDIR)/currentsensor.c \
		   $(SRCDIR)/propcom.c

OBJECTS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))

INCLUDES += -I$(INCDIR)

ELF = $(BUILDDIR)/$(OUTPUTNAME).elf
HEX = $(BUILDDIR)/$(OUTPUTNAME).hex
BIN = $(BUILDDIR)/$(OUTPUTNAME).bin

CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
AR = arm-none-eabi-ar
OBJCOPY = arm-none-eabi-objcopy
 	
CFLAGS  = -O0 -g -Wall -I. \
   -mcpu=cortex-m4 -mthumb \
   -mfloat-abi=soft $(INCLUDES)\
      
LDSCRIPT = $(LINKERNAME).ld
LDFLAGS += -T$(LDSCRIPT) -mthumb -mcpu=cortex-m4 --specs=nosys.specs

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@

$(ELF): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

$(BUILDDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(BUILDDIR)