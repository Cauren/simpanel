
#include <assert.h>

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>

#include <util/twi.h>
#include <util/delay.h>

#include <LUFA/Drivers/USB/USB.h>
// #include <LUFA/Platform/Platform.h>


#include "strings.c"

typedef struct
{
    USB_Descriptor_Configuration_Header_t	Config;

    USB_Descriptor_Interface_t			HID_Interface;
    USB_HID_Descriptor_HID_t			HID_JoystickHID;
    USB_Descriptor_Endpoint_t			HID_ReportINEndpoint;

} USB_Descriptor_Configuration_t;

#define SIMPANEL_IN_EPADDR	(ENDPOINT_DIR_IN | 1)

#define DTYPE_HID                 0x21
#define DTYPE_Report              0x22

typedef struct {
    uint8_t		id;
    uint8_t		dswitch[4];
    uint8_t		aplo;
    uint8_t		aphi;
    uint8_t		switches[3];
} Report;

typedef struct {
    uint8_t		digits[18];
    uint16_t		leds;
} LedReport;

#define S(_sn_) _HID_RI_ENTRY(HID_RI_TYPE_LOCAL , 0x70, 8, SI_##_sn_)
#define SMIN(_sn_) _HID_RI_ENTRY(HID_RI_TYPE_LOCAL , 0x80, 8, SI_##_sn_)
#define SMAX(_sn_) _HID_RI_ENTRY(HID_RI_TYPE_LOCAL , 0x90, 8, SI_##_sn_)

const USB_Descriptor_HIDReport_Datatype_t PROGMEM ControlsReport[] = {
    HID_RI_USAGE_PAGE(8, 0x02), /* Simulation controls */
    HID_RI_USAGE(8, 0x01), /* Flight Simulation device */
    HID_RI_COLLECTION(8, 0x01), /* Application */

        HID_RI_REPORT_ID(8, 1),

    	// Autopilot
        HID_RI_USAGE_PAGE(8, 0x02), /* Simulation controls */
        HID_RI_USAGE(8, 0x01), /* Flight Simulation device */
	S(g_ap),
	HID_RI_COLLECTION(8, 0x02),

	    HID_RI_USAGE_PAGE(8, 0x0A),
	    HID_RI_USAGE(8, 1), // ordinal 1
	    HID_RI_COLLECTION(8, 0x00),
		HID_RI_USAGE_PAGE(8, 0x01),
		HID_RI_USAGE(8, 0x37), // Dial
		S(dial1),
		HID_RI_LOGICAL_MINIMUM(8, -63),
		HID_RI_LOGICAL_MAXIMUM(8, 63),
		HID_RI_REPORT_COUNT(8, 1),
		HID_RI_REPORT_SIZE(8, 7),
		HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_WRAP | HID_IOF_RELATIVE | HID_IOF_VOLATILE),
		HID_RI_USAGE_PAGE(8, 0x09), // button
		HID_RI_USAGE(8, 1),
		HID_RI_LOGICAL_MINIMUM(8, 0),
		HID_RI_LOGICAL_MAXIMUM(8, 1),
		S(dial1b),
		HID_RI_REPORT_COUNT(8, 1),
		HID_RI_REPORT_SIZE(8, 1),
		HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
	    HID_RI_END_COLLECTION(0),

	    HID_RI_USAGE_PAGE(8, 0x0A),
	    HID_RI_USAGE(8, 2), // ordinal 2
	    HID_RI_COLLECTION(8, 0x00),
		HID_RI_USAGE_PAGE(8, 0x01),
		HID_RI_USAGE(8, 0x37), // Dial
		S(dial2),
		HID_RI_LOGICAL_MINIMUM(8, -63),
		HID_RI_LOGICAL_MAXIMUM(8, 63),
		HID_RI_REPORT_COUNT(8, 1),
		HID_RI_REPORT_SIZE(8, 7),
		HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_WRAP | HID_IOF_RELATIVE | HID_IOF_VOLATILE),
		HID_RI_USAGE_PAGE(8, 0x09), // button
		HID_RI_USAGE(8, 1),
		HID_RI_LOGICAL_MINIMUM(8, 0),
		HID_RI_LOGICAL_MAXIMUM(8, 1),
		S(dial2b),
		HID_RI_REPORT_COUNT(8, 1),
		HID_RI_REPORT_SIZE(8, 1),
		HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
	    HID_RI_END_COLLECTION(0),

	    HID_RI_USAGE_PAGE(8, 0x0A),
	    HID_RI_USAGE(8, 3), // ordinal 3
	    HID_RI_COLLECTION(8, 0x00),
		HID_RI_USAGE_PAGE(8, 0x01),
		HID_RI_USAGE(8, 0x37), // Dial
		S(dial3),
		HID_RI_LOGICAL_MINIMUM(8, -63),
		HID_RI_LOGICAL_MAXIMUM(8, 63),
		HID_RI_REPORT_COUNT(8, 1),
		HID_RI_REPORT_SIZE(8, 7),
		HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_WRAP | HID_IOF_RELATIVE | HID_IOF_VOLATILE),
		HID_RI_USAGE_PAGE(8, 0x09), // button
		HID_RI_USAGE(8, 1),
		HID_RI_LOGICAL_MINIMUM(8, 0),
		HID_RI_LOGICAL_MAXIMUM(8, 1),
		S(dial3b),
		HID_RI_REPORT_COUNT(8, 1),
		HID_RI_REPORT_SIZE(8, 1),
		HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
	    HID_RI_END_COLLECTION(0),

	    HID_RI_USAGE_PAGE(8, 0x0A),
	    HID_RI_USAGE(8, 4), // ordinal 4
	    HID_RI_COLLECTION(8, 0x00),
		HID_RI_USAGE_PAGE(8, 0x01),
		HID_RI_USAGE(8, 0x37), // Dial
		S(dial4),
		HID_RI_LOGICAL_MINIMUM(8, -63),
		HID_RI_LOGICAL_MAXIMUM(8, 63),
		HID_RI_REPORT_COUNT(8, 1),
		HID_RI_REPORT_SIZE(8, 7),
		HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_WRAP | HID_IOF_RELATIVE | HID_IOF_VOLATILE),
		HID_RI_USAGE_PAGE(8, 0x09), // button
		HID_RI_USAGE(8, 1),
		HID_RI_LOGICAL_MINIMUM(8, 0),
		HID_RI_LOGICAL_MAXIMUM(8, 1),
		S(dial4b),
		HID_RI_REPORT_COUNT(8, 1),
		HID_RI_REPORT_SIZE(8, 1),
		HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
	    HID_RI_END_COLLECTION(0),

	    HID_RI_USAGE_PAGE(8, 0x09), /* Button */
	    HID_RI_USAGE_MINIMUM(8, 1),
	    HID_RI_USAGE_MAXIMUM(8, 11),
	    HID_RI_LOGICAL_MINIMUM(8, 0),
	    HID_RI_LOGICAL_MAXIMUM(8, 1),
	    SMIN(ap_sw1),
	    SMAX(ap_sw12),
	    HID_RI_REPORT_COUNT(8, 11),
	    HID_RI_REPORT_SIZE(8, 1),
	    HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

	    HID_RI_REPORT_COUNT(8, 1),
	    HID_RI_REPORT_SIZE(8, 5),
	    HID_RI_INPUT(8, HID_IOF_CONSTANT),

	HID_RI_END_COLLECTION(0),

	HID_RI_USAGE_PAGE(8, 0x02),
	HID_RI_USAGE(8, 0x01),
	S(g_sw),
	HID_RI_COLLECTION(8, 0x02),

	    HID_RI_USAGE_PAGE(8, 0x09), /* Button */
	    HID_RI_USAGE_MINIMUM(8, 1),
	    HID_RI_USAGE_MAXIMUM(8, 20),
	    SMIN(s1),
	    SMAX(s13d),
	    HID_RI_REPORT_COUNT(8, 20),
	    HID_RI_REPORT_SIZE(8, 1),
	    HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

	    HID_RI_REPORT_COUNT(8, 1),
	    HID_RI_REPORT_SIZE(8, 4),
	    HID_RI_INPUT(8, HID_IOF_CONSTANT),

	HID_RI_END_COLLECTION(0),

	HID_RI_REPORT_ID(8, 2),
	HID_RI_USAGE_PAGE(8, 0x14),
	HID_RI_USAGE(8, 0x01),
	HID_RI_COLLECTION(8, 0x02),

	    HID_RI_USAGE(8, 0x43),
	    HID_RI_USAGE(8, 0x2C),
	    HID_RI_REPORT_COUNT(8, 18),
	    HID_RI_REPORT_SIZE(8, 8),
	    S(digs),
	    HID_RI_OUTPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE | HID_IOF_NON_VOLATILE),

	    HID_RI_USAGE_PAGE(8, 0x08),
	    HID_RI_USAGE_MINIMUM(8, 1),
	    HID_RI_USAGE_MAXIMUM(8, 11),
	    SMIN(ap_sw1),
	    SMAX(ap_sw12),
	    HID_RI_REPORT_COUNT(8, 11),
	    HID_RI_REPORT_SIZE(8, 1),
	    HID_RI_OUTPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE | HID_IOF_NON_VOLATILE),

	    HID_RI_REPORT_COUNT(8, 1),
	    HID_RI_REPORT_SIZE(8, 5),
	    HID_RI_OUTPUT(8, HID_IOF_CONSTANT),

	HID_RI_END_COLLECTION(0),

    HID_RI_END_COLLECTION(0),
};

const USB_Descriptor_Device_t PROGMEM DeviceDescriptor =
{
    .Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},

    .USBSpecification       = VERSION_BCD(1,1,0),
    .Class                  = USB_CSCP_NoDeviceClass,
    .SubClass               = USB_CSCP_NoDeviceSubclass,
    .Protocol               = USB_CSCP_NoDeviceProtocol,

    .Endpoint0Size          = 8,

    .VendorID               = 0x1209,
    .ProductID              = 0xC00C,
    .ReleaseNumber          = VERSION_BCD(1,0,0),

    .ManufacturerStrIndex   = SI_mfg,
    .ProductStrIndex        = SI_product,
    .SerialNumStrIndex      = SI_serial,

    .NumberOfConfigurations = 1,
};

const USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor =
{
    .Config =
      {
	.Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

	.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
	.TotalInterfaces        = 1,

	.ConfigurationNumber    = 1,
	.ConfigurationStrIndex  = NO_DESCRIPTOR,

	.ConfigAttributes       = (USB_CONFIG_ATTR_RESERVED | USB_CONFIG_ATTR_SELFPOWERED),

	.MaxPowerConsumption    = USB_CONFIG_POWER_MA(250)
      },

    .HID_Interface =
      {
	.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

	.InterfaceNumber        = 0,
	.AlternateSetting       = 0,

	.TotalEndpoints         = 1,

	.Class                  = HID_CSCP_HIDClass,
	.SubClass               = HID_CSCP_NonBootSubclass,
	.Protocol               = HID_CSCP_NonBootProtocol,

	.InterfaceStrIndex      = SI_hid,
      },

    .HID_JoystickHID =
      {
	.Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

	.HIDSpec                = VERSION_BCD(1,1,1),
	.CountryCode            = 0x00,
	.TotalReportDescriptors = 1,
	.HIDReportType          = HID_DTYPE_Report,
	.HIDReportLength        = sizeof(ControlsReport)
      },

    .HID_ReportINEndpoint =
      {
	.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

	.EndpointAddress        = SIMPANEL_IN_EPADDR,
	.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
	.EndpointSize           = sizeof(Report),
	.PollingIntervalMS      = 0x0A
      },

};


static const wchar_t EEMEM serial_number_number[] = L"AP-2100-03";

uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint16_t wIndex,
                                    const void** const DescriptorAddress,
				    uint8_t* const DescriptorMemorySpace)
{
    _Static_assert(sizeof(wchar_t)==sizeof(unsigned short), "wchar_t is not a short");

    static struct {
	USB_Descriptor_String_t d;
	wchar_t			pad[16];
    } serial_number;
    const uint8_t  DescriptorType   = (wValue >> 8);
    const uint8_t  DescriptorNumber = (wValue & 0xFF);

    const void* Address = NULL;
    uint16_t    Size    = NO_DESCRIPTOR;

    *DescriptorMemorySpace = MEMSPACE_FLASH;

    switch (DescriptorType) {
      case DTYPE_Device:
	Address = &DeviceDescriptor;
	Size    = sizeof(USB_Descriptor_Device_t);
	break;
      case DTYPE_Configuration:
	Address = &ConfigurationDescriptor;
	Size    = sizeof(USB_Descriptor_Configuration_t);
	break;
      case DTYPE_String:
	switch(DescriptorNumber) {
	  case SI_serial: {
	      size_t len = 0;
	      USB_Descriptor_String_t* a = &serial_number.d;
	      Address = a;
	      while((a->UnicodeString[len] = eeprom_read_word((const unsigned int*)serial_number_number+len)))
		  len++;
	      Size = a->Header.Size = sizeof(USB_Descriptor_Header_t) + len*sizeof(wchar_t);
	      a->Header.Type = DTYPE_String;
	      *DescriptorMemorySpace = MEMSPACE_RAM;
	      break;
	  }
	  default: {
	      USB_Descriptor_String_t* a = (USB_Descriptor_String_t*)pgm_read_ptr(Strings+DescriptorNumber);
	      Address = a;
	      Size = pgm_read_byte(&(a->Header.Size));
	      break;
	  }
	}
	break;
      case DTYPE_HID:
	Address = &ConfigurationDescriptor.HID_JoystickHID;
	Size    = sizeof(USB_HID_Descriptor_HID_t);
	break;
      case DTYPE_Report:
	Address = &ControlsReport;
	Size    = sizeof(ControlsReport);
	break;
    }

    *DescriptorAddress = Address;
    return Size;
}

static volatile Report		report;
static volatile Report		new_report;
static volatile LedReport	led_report;
static volatile bool		report_changed = true;
static volatile bool		connected = false;

volatile uint8_t status=0;

void EVENT_USB_Device_Connect(void)
{
    connected = true;
    report_changed = false;
}

void EVENT_USB_Device_Disconnect(void)
{
    connected = false;
}

void EVENT_USB_Device_ConfigurationChanged(void)
{
        bool ConfigSuccess = true;

        /* Setup HID Report Endpoint */
        ConfigSuccess &= Endpoint_ConfigureEndpoint(SIMPANEL_IN_EPADDR, EP_TYPE_INTERRUPT, sizeof(Report), 1);
}


#define BUFS 16
#define BSIZE 44
typedef struct _iobuf {
    volatile uint8_t            len;
    volatile uint8_t            end;
    struct _iobuf* volatile     next;
    volatile char               buf[BSIZE];
} IOBuf;

static IOBuf            iobuf[BUFS];

static IOBuf* volatile  b_usbout = 0;

IOBuf* newbuf(uint8_t len)
{   
    uint8_t srs = SREG;
    for(;;) {
	cli();
	for(uint8_t n=0; n<BUFS; n++)
	  { 
	    IOBuf* b = iobuf+n;
	    if(b->end == 0) {
		b->len = len;
		b->buf[0] = len | 0x80;
		b->end = 1;
		b->next = 0;
		SREG = srs;
		return b;
	    }
	  }
	SREG = srs;
	USB_USBTask();
    }
}

void queuebuf(IOBuf* buf, IOBuf* volatile* bp)
{   
    uint8_t srs = SREG;
    cli();
    if(*bp) {
	IOBuf* b = *bp;
	while(b->next)
	    b = b->next;
	b->next = buf;
    } else
	*bp = buf;
    SREG = srs;
}


void update_report(void);

void do_usb_io(void)
{
    if(!connected) {
	if(b_usbout) {
	    cli();
	    for(IOBuf* b = b_usbout; b; b=b->next)
		b->end = 0;
	    sei();
	}
	return;
    }

    Endpoint_SelectEndpoint(SIMPANEL_IN_EPADDR);
    if(report_changed && Endpoint_IsINReady()) {
	report.id = 1;
	Endpoint_Write_Stream_LE((Report*)&report, sizeof(Report), NULL);
	Endpoint_ClearIN();
	report_changed = false;
	update_report();
    }

}

uint8_t		dpy_base = 0;
uint8_t		dpy_step;
uint16_t	dpybits[24];


static uint8_t	inputs[38];
static int16_t	encoders[4];
static uint8_t	encstate[4];
static uint8_t	milis;

void update_report(void)
{
    cli();
    for(int e=0; e<4; e++) {
	uint8_t enc = 0;
	if(encoders[e] < -63) {
	    enc = -63 & 0x7F;
	    encoders[e] += 63;
	} else if(encoders[e] > 63) {
	    enc = 63;
	    encoders[e] -= 63;
	} else if(encoders[e]) {
	    enc = encoders[e] & 0x7F;
	    encoders[e] = 0;
	}
	if(inputs[e] & 0x10)
	    enc |= 0x80;
	new_report.dswitch[e] = enc;
    }

    uint16_t ap = 0;
    for(int i=0; i<11; i++) {
	if(inputs[4+i] & 0x10)
	    ap |= 1<<i;
    }
    new_report.aplo = ap;
    new_report.aphi = ap>>8;

    new_report.switches[0] = 0;
    new_report.switches[1] = 0;
    new_report.switches[2] = 0;
    for(int i=0; i<8; i++) {
	if(inputs[15+i] & 0x10)
	    new_report.switches[0] |= 1<<i;
	if(inputs[23+i] & 0x10)
	    new_report.switches[1] |= 1<<i;
	if(i<4 && (inputs[31+i] & 0x10))
	    new_report.switches[2] |= 1<<i;
    }

    if(   (report.dswitch[0]&0x80) != (new_report.dswitch[0]&0x80)
       || (report.dswitch[1]&0x80) != (new_report.dswitch[1]&0x80)
       || (report.dswitch[2]&0x80) != (new_report.dswitch[2]&0x80)
       || (report.dswitch[3]&0x80) != (new_report.dswitch[3]&0x80)
       || (new_report.dswitch[0] & 0x7F)
       || (new_report.dswitch[1] & 0x7F)
       || (new_report.dswitch[2] & 0x7F)
       || (new_report.dswitch[3] & 0x7F)
       || report.aplo != new_report.aplo
       || report.aphi != new_report.aphi
       || report.switches[0] != new_report.switches[0]
       || report.switches[1] != new_report.switches[1]
       || report.switches[2] != new_report.switches[2] ) {
	memcpy((void*)&report, (const void*)&new_report, sizeof(report));
	report_changed = true;
    }
    sei();
}

enum _i2c_state {
    I2CIdle, I2CStart, I2CAddr, I2CData, I2CStop,
    I2CRead,
};

static enum _i2c_state i2cs;
static uint8_t i2cbuf[32];
static uint8_t i2clen;
static uint8_t i2cptr;
static uint8_t i2ce;

uint8_t unhex(const char* s) {
    return ( (s[0] - ((s[0]>'9')? 55: 48)) << 4 )
	   | (s[1] - ((s[1]>'9')? 55: 48));
}

ISR(TWI_vect)
{
    switch(i2cs) {
	case I2CStart:
	  status |= 1;
	  i2ce = 2;
	  if((TWSR&0xF8) == 0x08) {
	      i2cs = I2CAddr;
	      TWDR = i2cbuf[i2cptr++];
	      TWCR = 0x85;
	      return;
	  }
	  break;
	case I2CAddr:
	  status |= 2;
	  i2ce = 3;
	  switch(TWSR&0xF8) {
	    case 0x38:
	      i2cs = I2CStart;
	      i2ce = 4;
	      TWCR = 0xA5;
	      i2cptr = 0;
	      return;
	    case 0x48:
	    case 0x20:
	      i2ce = 5;
	      break;
	    case 0x18:
	      i2ce = 6;
	      i2cs = I2CData;
	      TWDR = i2cbuf[i2cptr++];
	      TWCR = 0x85;
	      return;
	    case 0x40:
	      i2ce = 13;
	      i2cs = I2CRead;
	      TWCR = (i2cptr < (i2clen-1))? 0xC5: 0x85;
	      return;
	  }
	  break;
	case I2CRead:
	  i2ce = 14;
	  i2cbuf[i2cptr++] = TWDR;
	  if(i2cptr < i2clen) {
	      TWCR = (i2cptr < (i2clen-1))? 0xC5: 0x85;
	      return;
	  }
	  i2cs = I2CIdle;
	  TWCR = 0x95;
	  return;

	case I2CData:
	  i2ce = 7;
	  switch(TWSR&0xF8) {
	    case 0x28:
	      i2ce = 8;
	      if(i2cptr < i2clen) {
		  i2ce = 9;
		  TWDR = i2cbuf[i2cptr++];
		  TWCR = 0x85;
	      } else {
		  i2cs = I2CIdle;
		  i2ce = 10;
		  TWCR = 0x95;
	      }
	      return;
	    case 0x30:
	      i2ce = 11;
	      i2cs = I2CIdle;
	      TWCR = 0x95;
	      return;
	  }
	  break;
	case I2CStop:
	  status |= 8;
	  i2ce += 16;
	  i2cs = I2CIdle;
	  TWCR = 0x84;
	  return;

	case I2CIdle:
	  i2ce = 12;
	  break;
    }
    i2cs = I2CIdle;
    TWCR = 0x84;
}

void i2c_send(void)
{
    cli();
    if(i2clen < 2)
	return;
    while(i2cs != I2CIdle) {
	sei();
	while(i2cs != I2CIdle)
	    ;
	cli();
    }
    i2cptr = 0;
    i2cs = I2CStart;
    i2ce = 1;
    TWCR = 0xA5;
    sei();
}

static const uint8_t pwm_bits[] PROGMEM = {
    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,

    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

static const uint8_t digit_index[] PROGMEM = {
    15, 16, 17, 12, 13, 14, 9, 10, 11, 6, 7, 8, 3, 4, 5, 0, 1, 2,
};

static const uint8_t digit_mask[] PROGMEM = {
    0xF8, 0xF8, 0xF8, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xF8, 0xF8, 0xF8, 0xFF, 0xFF, 0xFF,
};

static char	display[18];
static uint16_t	leds;

static bool attract_mode = true;

bool dpy_set(void)
{
    status |= 4;
    bool refresh = false;

    for(int i=0; i<18; i++) {
	uint16_t bits = display[i];
	uint16_t mask = pgm_read_byte(digit_mask+i);
	uint16_t *dest = dpybits + pgm_read_byte(digit_index+i);

	bits = (bits&~mask) | ((bits&mask)<<2);

	if(dest && *dest != bits) {
	    *dest = bits;
	    refresh = true;
	}
    }

    if(dpybits[23] != leds) {
	dpybits[23] = leds;
	refresh = true;
    }

    return refresh;
}

static int attract_step = 0;

void do_attract_mode(void)
{

    if(attract_step > 50)
	display[17] = 1 << (attract_step % 6);

    switch(attract_step) {
      case 100:
	attract_mode = false;
	for(int i=0; i<17; i++)
	    display[i] = 0x00;
	display[17] = 0x80;
	leds = 0;
	break;

      case 0:
	for(int i=0; i<18; i++)
	    display[i] = 0x40;
	leds = 0;
	break;

      case 20:
	display[0] = 0x77;
	display[1] = 0x73;
	display[2] = 0x00;
	display[3] = 0x86;
	display[4] = 0xBF;
	display[5] = 0x3F;
	for(int i=6; i<18; i++)
	    display[i] = 0;
	break;

      case 30:
	leds = 0x201;
	break;
      case 34:
	leds = 0x20F;
	break;
      case 38:
	leds = 0x21F;
	break;
      case 42:
	leds = 0x23F;
	break;
      case 46:
	leds = 0x27F;
	break;
      case 50:
	leds = 0x7FF;
	break;
      case 54:
	leds = 0x5FD;
	break;
      case 58:
	leds = 0x5F0;
	break;
      case 62:
	leds = 0x5E0;
	break;
      case 66:
	leds = 0x5C0;
	break;
      case 70:
	leds = 0x580;
	break;
      case 74:
	leds = 0x000;
	break;
    }

    if(dpy_set())
	dpy_step = 32+dpy_base;

    attract_step++;
}

void dpy_update(void)
{
    cli();
    if(dpy_step>35 || i2cs!=I2CIdle) {
	sei();
	return;
    }
    sei();
    switch(dpy_step) {
      case 0:
      case 1:
	i2clen = 3;
	i2cbuf[1] = 0xFD;
	i2cbuf[2] = 0xC0;
	break;

      case 2:
      case 3:
	i2cbuf[1] = 0x06;
	i2cbuf[2] = 0x11;
	break;

      case 4:
      case 5:
	i2cbuf[1] = 0x04;
	i2cbuf[2] = 0x2B;
	break;

      case 6:
      case 7:
	i2cbuf[1] = 0x05;
	i2cbuf[2] = 0xC0;
	break;

      case 8:
      case 9:
	i2cbuf[1] = 0x00;
	i2cbuf[2] = 0x40;
	break;

      case 10:
      case 11:
	i2clen = 3;
	i2cbuf[1] = 0x09;
	i2cbuf[2] = 0x03;
	break;

      case 12:
      case 13:
	i2cbuf[1] = 0xFD;
	i2cbuf[2] = 0x40;
	break;

      case 14:
      case 15:
	i2clen = 26;
	i2cbuf[1] = 0x00;
	for(uint8_t i=2; i<26; i++)
	    i2cbuf[i] = 0x00;
	break;

      case 16:
      case 17:
      case 18:
      case 19:
      case 20:
      case 21:
      case 22:
      case 23:
      case 24:
      case 25:
      case 26:
      case 27:
	i2clen = 24;
	i2cbuf[1] = 0x18 + ((dpy_step-16)&~1)*11;
	for(uint8_t i=2; i<24; i++)
	    i2cbuf[i] = pgm_read_byte(pwm_bits
				     + ((dpy_step&1)? 132: 0)
				     + ((dpy_step-16)&~1)*11
				     + i-2);
	break;

      case 28:
      case 29:
	i2clen = 3;
	i2cbuf[1] = 0xFD;
	i2cbuf[2] = 0x80;
	break;

      case 30:
	i2clen = 14;
	i2cbuf[1] = 0x00;
	for(uint8_t i=0; i<12; i++)
	    i2cbuf[i+2] = 0x60;
	break;

      case 31:
	for(uint8_t i=0; i<12; i++)
	    i2cbuf[i+2] = 0x60;
	break;

      case 32:
      case 33:
	i2clen = 3;
	i2cbuf[1] = 0xFD;
	i2cbuf[2] = 0x01;
	break;

      case 34:
	i2clen = 26;
	i2cbuf[1] = 0x00;
	for(uint8_t i=0; i<12; i++) {
	    i2cbuf[2+(i*2)] = dpybits[i] & 0xFF;
	    i2cbuf[3+(i*2)] = (dpybits[i]>>8) & 0x07;
	}
	break;

      case 35:
	i2clen = 26;
	i2cbuf[1] = 0x00;
	for(uint8_t i=0; i<12; i++) {
	    i2cbuf[2+(i*2)] = dpybits[i+12] & 0xFF;
	    i2cbuf[3+(i*2)] = (dpybits[i+12]>>8) & 0x07;
	}
	// dpy_step = 31;
	break;
    }

    i2cbuf[0] = (dpy_step&1)? 0x6E: 0x60;
    dpy_step ++;
    i2cptr = 0;
    i2ce = 1;
    i2cs = I2CStart;
    TWCR = 0xA5;
}

static const uint8_t enc_sm[20] PROGMEM = {
    /*             AB    aB    Ab    ab    */
    /*  Z:0 */   0x00, 0x04, 0x01, 0x00,
    /*  A:1 */   0x02, 0x04, 0x01, 0x00,
    /* AB:2 */   0x02, 0x14, 0x01, 0x00,
    /* BA:3 */   0x03, 0x04, 0x21, 0x00,
    /*  B:4 */   0x03, 0x04, 0x01, 0x00,
};

#define BOUNCE(n) { if(inputs[n]<31) inputs[n]++; } else if(inputs[n]) --inputs[n]

ISR(TIMER1_COMPA_vect)
{
    uint8_t	pins = PINB;
    if(!(pins&0x01)) BOUNCE(0);
    if(!(pins&0x02)) BOUNCE(1);
    if(!(pins&0x04)) BOUNCE(2);
    if(!(pins&0x08)) BOUNCE(3);
    if(!(pins&0x10)) BOUNCE(4);
    if(!(pins&0x20)) BOUNCE(5);
    if(!(pins&0x40)) BOUNCE(6);
    if(!(pins&0x80)) BOUNCE(7);

    pins = PINC;
    if(!(pins&0x01)) BOUNCE(8);
    if(!(pins&0x02)) BOUNCE(9);
    if(!(pins&0x04)) BOUNCE(10);
    if(!(pins&0x08)) BOUNCE(11);
    if(!(pins&0x10)) BOUNCE(12);
    if(!(pins&0x20)) BOUNCE(13);
    if(!(pins&0x40)) BOUNCE(14);

    pins = PIND;
    if(!(pins&0x10)) BOUNCE(15);
    if(!(pins&0x20)) BOUNCE(16);
    if(!(pins&0x40)) BOUNCE(17);
    if(!(pins&0x80)) BOUNCE(18);

    pins = PINE;
    if(!(pins&0x01)) BOUNCE(19);
    if(!(pins&0x02)) BOUNCE(20);
    if(!(pins&0x04)) BOUNCE(21);
    if(!(pins&0x08)) BOUNCE(22);
    if(!(pins&0x10)) BOUNCE(23);
    if(!(pins&0x20)) BOUNCE(24);
    if(!(pins&0x40)) BOUNCE(25);
    if(!(pins&0x80)) BOUNCE(26);

    pins = PINF;
    if(!(pins&0x01)) BOUNCE(27);
    if(!(pins&0x02)) BOUNCE(28);
    if(!(pins&0x04)) BOUNCE(29);
    if(!(pins&0x08)) BOUNCE(30);
    if(!(pins&0x10)) BOUNCE(31);
    if(!(pins&0x20)) BOUNCE(32);
    if(!(pins&0x40)) BOUNCE(33);
    if(!(pins&0x80)) BOUNCE(34);

    pins = PINA;
    for(int e=0; e<4; e++) {
	uint8_t ns = pgm_read_byte(enc_sm + (encstate[e]<<2) + (pins&3));
	encstate[e] = ns & 0x0f;
	if((ns&0x10) && encoders[e]<32767)
	    encoders[e]++;
	if((ns&0x20) && encoders[e]>-32767)
	    --encoders[e];

	pins >>= 2;
    }

    milis++;
}

void EVENT_USB_Device_ControlRequest(void)
{
        /* Handle HID Class specific requests */
        switch (USB_ControlRequest.bRequest) {

	  case HID_REQ_GetReport:
	    if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
	      {
		Endpoint_ClearSETUP();
		report.id = 1;
		Endpoint_Write_Control_Stream_LE((Report*)&report, sizeof(Report));
		report_changed = false;
		Endpoint_ClearOUT();
	      }
	    break;

	  case HID_REQ_SetReport:
	    if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
	      {
		Endpoint_ClearSETUP();

		uint8_t report[sizeof(LedReport)+1];

		if(Endpoint_Read_Control_Stream_LE(report, sizeof(LedReport)+1) == ENDPOINT_RWSTREAM_NoError) {
		    if(report[0] == 2) {
			for(int i=0; i<18; i++)
			    display[i] = report[i+1];
			attract_mode = false;
			leds = ((int)report[19])<<8 | report[20];
			if(dpy_set())
			    dpy_step = 32+dpy_base;
		    }
		}

		Endpoint_ClearIN();
	      }

	    break;

	}
}

int main(void)
{
    int mcucr = MCUCR | 0x80;
    MCUCR = mcucr;
    MCUCR = mcucr;
    MCUSR &= ~(1 << WDRF);
    wdt_disable();
    clock_prescale_set(clock_div_1);

    for(uint8_t i=0; i<8; i++)
	iobuf[i].end = 0;
    b_usbout = 0;
    memset(inputs, 0, 38);
    memset(encoders, 0, 4);
    memset(encstate, 0, 4);

    ADCSRA = 0x00; // disable ADC
    ACSR   = 0x80; // disable analog comarator
    DIDR1  = 0x00; // make sure digital in is enabled

    DDRA   = 0x00;
    PORTA  = 0xFF;
    DDRB   = 0x00;
    PORTB  = 0xFF;
    DDRC   = 0x80;
    PORTC  = 0xFF;
    DDRD   = 0x00;
    PORTD  = 0xF3;
    DDRE   = 0x00;
    PORTE  = 0xFF;
    DDRF   = 0x00;
    PORTF  = 0xFF;

    TCCR1A = 0x00;  // no output, WGM = 0b..00
    TCCR1B = 0x0A;  // clock/8, WGM = 0b01..
    OCR1A  = 2000;  // every ms
    TIMSK1 = 0x02;  // enable interrupt on OCR1A

    TWBR   = 24;     // BR = 16Mhz / 16+2*TWIBR = 16Mhz / 64 = 256Khz
    TWCR   = 0x04;
    i2cs   = I2CIdle;
    i2ce   = 0;

    dpy_step = dpy_base;
    for(uint8_t i=0; i<24; i++) {
	dpybits[i] = 0x7FF;
    }

    uint8_t ready = 0;

    wdt_enable(WDTO_500MS);
    sei();
    USB_Init();
    GlobalInterruptEnable();

    for(;;) {
	wdt_reset();

	if(ready)
	    dpy_update();

	if(milis > 50) {

	    milis = 0;
	    ready = 1;

	    if(!report_changed)
		update_report();

	    USB_USBTask();
	    if (USB_DeviceState == DEVICE_STATE_Configured) {

		if(attract_mode)
		    do_attract_mode();
		update_report();
		do_usb_io();
	    }

	}

    }
}

