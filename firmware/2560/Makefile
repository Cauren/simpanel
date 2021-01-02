DEPDIR := .cache
DEPFILES = $(wildcard $(patsubst %,%/*.d,$(DEPDIR)))
#CPPOPTS = -march=haswell -std=c++20 -ggdb -g3 -fsemantic-interposition -Og -I.
CCOPTS = -pipe -gdwarf-2 -g2 -mmcu=atmega2560 -fshort-enums -fno-inline-small-functions -fpack-struct -Wall -fno-strict-aliasing -funsigned-char -funsigned-bitfields -ffunction-sections -DF_CPU=16000000UL -mrelax -fno-jump-tables -x c -Os -std=gnu99 -Wstrict-prototypes

all:		simpanel.hex simpanel.eep

%.o:		%.c
		avr-gcc $(CCOPTS) -Wp,-MMD,"$(*D)/$(DEPDIR)/$(*F).d",-MQ,"$@",-MP -c $(<) -o $*.o

%.elf:		%.o
		avr-gcc -mmcu=atmega2560 $(<) -o $*.elf
		avr-size --mcu=atmega2560 --format=avr $*.elf

%.hex:		%.elf
		avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature $*.elf $*.hex

%.eep:		%.elf
		avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings $*.elf $*.eep

try:		try.o smart.a -lpthread # -lsigsegv
		@echo "[LD ] $@"
		@$(CPP) $(CPPOPTS) -o $@ $^

-include $(DEPFILES) /dev/null

