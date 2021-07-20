
LUFA_PATH=LUFA/LUFA

MCU          = at90usb646
ARCH         = AVR8
BOARD        = AT90USBKEY
F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = simpanel90
SRC          = simpanel90.c $(LUFA_SRC_USB) $(LUFA_SRC_USBCLASS) $(LUFA_SRC_PLATFORM)
CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -IConfig

# obj/simpanel-usb.o: strings.c

strings.c: strings.txt mkstr.pl
	./mkstr.pl strings.txt >strings.c

include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk
include $(LUFA_PATH)/Build/lufa_doxygen.mk
include $(LUFA_PATH)/Build/lufa_dfu.mk
include $(LUFA_PATH)/Build/lufa_hid.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
include $(LUFA_PATH)/Build/lufa_atprogram.mk

