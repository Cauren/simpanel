

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

    USB_Descriptor_Interface_Association_t	CDC_IAD;
    // CDC Control Interface
    USB_Descriptor_Interface_t			CDC_CCI_Interface;
    USB_CDC_Descriptor_FunctionalHeader_t	CDC_Functional_Header;
    USB_CDC_Descriptor_FunctionalACM_t		CDC_Functional_ACM;
    USB_CDC_Descriptor_FunctionalUnion_t	CDC_Functional_Union;
    USB_Descriptor_Endpoint_t			CDC_ManagementEndpoint;
    // CDC Data Interface
    USB_Descriptor_Interface_t			CDC_DCI_Interface;
    USB_Descriptor_Endpoint_t			CDC_DataOutEndpoint;
    USB_Descriptor_Endpoint_t			CDC_DataInEndpoint;

} USB_Descriptor_Configuration_t;

#define SIMPANEL_IN_EPADDR	(ENDPOINT_DIR_IN | 1)
#define CDC_NOTIFICATION_EPADDR (ENDPOINT_DIR_IN | 2)
#define CDC_TX_EPADDR		(ENDPOINT_DIR_IN | 3)
#define CDC_RX_EPADDR		(ENDPOINT_DIR_OUT | 4)

#define DTYPE_HID                 0x21
#define DTYPE_Report              0x22

uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
				    const uint16_t wIndex,
				    const void** const DescriptorAddress)
    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);


typedef struct {
    uint8_t		dswitch[4];
    uint16_t		ap;
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
	    HID_RI_USAGE(8, 2), // ordinal 1
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
	    HID_RI_USAGE(8, 3), // ordinal 1
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
	    HID_RI_USAGE(8, 4), // ordinal 1
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
	    SMAX(ap_sw2),
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
    .ReleaseNumber          = VERSION_BCD(0,9,0),

    .ManufacturerStrIndex   = SI_mfg,
    .ProductStrIndex        = SI_product,
    .SerialNumStrIndex      = USE_INTERNAL_SERIAL,

    .NumberOfConfigurations = 1,
};

const USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor =
{
    .Config =
      {
	.Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

	.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
	.TotalInterfaces        = 3,

	.ConfigurationNumber    = 1,
	.ConfigurationStrIndex  = NO_DESCRIPTOR,

	.ConfigAttributes       = (USB_CONFIG_ATTR_RESERVED | USB_CONFIG_ATTR_SELFPOWERED),

	.MaxPowerConsumption    = USB_CONFIG_POWER_MA(100)
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

    .CDC_IAD =
      {
	.Header                 = {.Size = sizeof(USB_Descriptor_Interface_Association_t), .Type = DTYPE_InterfaceAssociation},

	.FirstInterfaceIndex    = 1,
	.TotalInterfaces        = 2,

	.Class                  = CDC_CSCP_CDCClass,
	.SubClass               = CDC_CSCP_ACMSubclass,
	.Protocol               = CDC_CSCP_ATCommandProtocol,

	.IADStrIndex            = SI_ctc,
      },

    .CDC_CCI_Interface =
      {
	.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

	.InterfaceNumber        = 1,
	.AlternateSetting       = 0,

	.TotalEndpoints         = 1,

	.Class                  = CDC_CSCP_CDCClass,
	.SubClass               = CDC_CSCP_ACMSubclass,
	.Protocol               = CDC_CSCP_ATCommandProtocol,

	.InterfaceStrIndex      = NO_DESCRIPTOR
      },

    .CDC_Functional_Header =
      {
	.Header                 = {.Size = sizeof(USB_CDC_Descriptor_FunctionalHeader_t), .Type = CDC_DTYPE_CSInterface},
	.Subtype                = CDC_DSUBTYPE_CSInterface_Header,

	.CDCSpecification       = VERSION_BCD(1,1,0),
      },

    .CDC_Functional_ACM =
      {
	.Header                 = {.Size = sizeof(USB_CDC_Descriptor_FunctionalACM_t), .Type = CDC_DTYPE_CSInterface},
	.Subtype                = CDC_DSUBTYPE_CSInterface_ACM,

	.Capabilities           = 0x06,
      },

    .CDC_Functional_Union =
      {
	.Header                 = {.Size = sizeof(USB_CDC_Descriptor_FunctionalUnion_t), .Type = CDC_DTYPE_CSInterface},
	.Subtype                = CDC_DSUBTYPE_CSInterface_Union,

	.MasterInterfaceNumber  = 1,
	.SlaveInterfaceNumber   = 2,
      },

    .CDC_ManagementEndpoint =
      {
	.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

	.EndpointAddress        = CDC_NOTIFICATION_EPADDR,
	.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
	.EndpointSize           = 8,
	.PollingIntervalMS      = 0xFF
      },

    .CDC_DCI_Interface =
      {
	.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

	.InterfaceNumber        = 2,
	.AlternateSetting       = 0,

	.TotalEndpoints         = 2,

	.Class                  = CDC_CSCP_CDCDataClass,
	.SubClass               = CDC_CSCP_NoDataSubclass,
	.Protocol               = CDC_CSCP_NoDataProtocol,

	.InterfaceStrIndex      = NO_DESCRIPTOR
      },

    .CDC_DataOutEndpoint =
      {
	.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

	.EndpointAddress        = CDC_RX_EPADDR,
	.Attributes             = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
	.EndpointSize           = 16,
	.PollingIntervalMS      = 0x05
      },

    .CDC_DataInEndpoint =
      {
	.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

	.EndpointAddress        = CDC_TX_EPADDR,
	.Attributes             = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
	.EndpointSize           = 16,
	.PollingIntervalMS      = 0x05
      },

};



uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint16_t wIndex,
                                    const void** const DescriptorAddress)
{
    const uint8_t  DescriptorType   = (wValue >> 8);
    const uint8_t  DescriptorNumber = (wValue & 0xFF);

    const void* Address = NULL;
    uint16_t    Size    = NO_DESCRIPTOR;

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
	  {
	    USB_Descriptor_String_t* a = (USB_Descriptor_String_t*)pgm_read_ptr(Strings+DescriptorNumber);
	    Address = a;
	    Size = pgm_read_byte(&(a->Header.Size));
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
static volatile bool		slow_report = false;
static volatile bool		connected = false;

static CDC_LineEncoding_t linesetup = {	.BaudRateBPS = 115200,
    					.CharFormat  = CDC_LINEENCODING_OneStopBit,
					.ParityType  = CDC_PARITY_None,
					.DataBits    = 8
};

volatile uint8_t status=0;

void EVENT_USB_Device_Connect(void)
{
    connected = true;
    slow_report = false;
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
	if(ConfigSuccess) status++;
        ConfigSuccess &= Endpoint_ConfigureEndpoint(CDC_NOTIFICATION_EPADDR, EP_TYPE_INTERRUPT, 8, 1);
	if(ConfigSuccess) status++;
        ConfigSuccess &= Endpoint_ConfigureEndpoint(CDC_TX_EPADDR, EP_TYPE_BULK, 16, 1);
	if(ConfigSuccess) status++;
        ConfigSuccess &= Endpoint_ConfigureEndpoint(CDC_RX_EPADDR, EP_TYPE_BULK, 16, 1);
	if(ConfigSuccess) status++;
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

static IOBuf* volatile  b_usbin = 0;
static IOBuf* volatile  bl_usbin = 0;
static IOBuf* volatile  b_usbout = 0;
static IOBuf* volatile	b_out = 0;

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
	Endpoint_Write_Stream_LE((Report*)&report, sizeof(Report), NULL);
	Endpoint_ClearIN();
	report_changed = false;
	update_report();
    }

    if(b_usbout) {

	Endpoint_SelectEndpoint(CDC_TX_EPADDR);

	uint16_t sent = b_usbout->len;

	switch(Endpoint_Write_Stream_LE((uint8_t*)b_usbout->buf, b_usbout->end, &sent)) {
	  case ENDPOINT_RWSTREAM_IncompleteTransfer:
	    b_usbout->len = sent;
	    break;

	  default:
	    Endpoint_ClearIN();
	    cli();
	    b_usbout->end = 0;
	    b_usbout = b_usbout->next;
	    sei();
	    break;
	}
    }

#if 0
	uint8_t left = 16 - Endpoint_BytesInEndpoint();
	uint8_t send = b_usbout->end - b_usbout->len;

	if(send) {
	    if(!left)
		break;
	    if(send > left)
		send = left;
	    if(send) {
		Endpoint_Write_Stream_LE((uint8_t*)b_usbout->buf+b_usbout->len, send, NULL);
		if(send < left) {
		    cli();
		    b_usbout->end = 0;
		    b_usbout = b_usbout->next;
		    sei();
		} else
		    b_usbout->len += send;
	    }
	    Endpoint_ClearIN();
	} else if(b_usbout->len >= b_usbout->end) {
	    cli();
	    b_usbout->end = 0;
	    b_usbout = b_usbout->next;
	    sei();
	    Endpoint_ClearIN();
	}
    }
#endif

    Endpoint_SelectEndpoint(CDC_RX_EPADDR);
    if(Endpoint_IsOUTReceived()) {
	while(Endpoint_BytesInEndpoint() > 0) {

	    uint8_t rx = Endpoint_Read_8();

	    if(rx < 32) {
		if(bl_usbin) {
		    cli();
		    if(rx == 'X'-0x40) {
			bl_usbin->end = 0;
			bl_usbin = 0;
			sei();
			continue;
		    }
		    bl_usbin->len = bl_usbin->end;
		    queuebuf(bl_usbin, &b_usbin);
		    bl_usbin = 0;
		    sei();
		}
		continue;
	    }
	    if(!bl_usbin) {
		bl_usbin = newbuf(1);
		bl_usbin->buf[0] = rx;
		continue;
	    }
	    if(bl_usbin->end < BSIZE)
		bl_usbin->buf[bl_usbin->end++] = rx;
	}
	Endpoint_ClearOUT();
    }

}

void out(char c) {
    if(!b_out) {
	b_out = newbuf(1);
	b_out->buf[0] = c;
	return;
    }
    if(b_out->end < BSIZE)
	b_out->buf[b_out->end++] = c;
}

void outs(const char* s, uint8_t len) {
    while(len--)
	out(pgm_read_byte(s++));
}

void hex(uint8_t n) {
    out('0'+((n>>4)&0x0F)+((n>0x9F)? 7: 0));
    out('0'+(n&0x0F)+(((n&0x0F)>9)? 7: 0));
}

void crlf(void) {
    out('\r');
    out('\n');
}

void write(void) {
    if(b_out) {
	crlf();
	b_out->len = 0;
	queuebuf(b_out, &b_usbout);
	b_out = 0;
    }
}

const char PROGMEM s_model[] = "SIMPANEL rev. C";
const char PROGMEM s_version[] = "01.030";

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

    new_report.ap = 0;
    for(int i=0; i<11; i++) {
	if(inputs[4+i] & 0x10)
	    new_report.ap |= 1<<i;
    }

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
       || report.ap != new_report.ap
       || report.switches[0] != new_report.switches[0]
       || report.switches[1] != new_report.switches[1]
       || report.switches[2] != new_report.switches[2] ) {
	memcpy((void*)&report, (const void*)&new_report, sizeof(report));
	report_changed = true;
    }
    sei();
}

uint8_t		dpy_step;
uint16_t	dpybits[24];

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
	  i2ce = 2;
	  if((TWSR&0xF8) == 0x08) {
	      i2cs = I2CAddr;
	      TWDR = i2cbuf[i2cptr++];
	      TWCR = 0x85;
	      return;
	  }
	  break;
	case I2CAddr:
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

static const uint8_t digit_seg[] PROGMEM = {
    0x3F, // 0
    0x06, // 1
    0x03, // 2
    0x4f, // 3
    0x66, // 4
    0x6d, // 5
    0x7d, // 6
    0x07, // 7
    0x7f, // 8
    0x6f, // 9
    0x77, // A
    0x7c, // B
    0x39, // C
    0x5e, // D
    0x79, // E
    0x71, // F
    0x40, // G (-)
    0x70, // H (1/2 +)
    0x63, // I (degree)
    0x00, // j (space)
    0x08, // k (uline)
};

static const uint8_t digit_index[] PROGMEM = {
    15, 16, 17, 12, 13, 14, 9, 10, 11, 6, 7, 8, 3, 4, 5, 0, 1, 2,
};

static const uint8_t digit_mask[] PROGMEM = {
    0xF8, 0xF8, 0xF8, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xF8, 0xF8, 0xF8, 0xFF, 0xFF, 0xFF,
};

static char	display[18];
static uint16_t	leds;

bool dpy_set(void)
{
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
	i2clen = 3;
	i2cbuf[1] = 0xFD;
	i2cbuf[2] = 0xC0;
	break;

      case 2:
	i2cbuf[1] = 0x06;
	i2cbuf[2] = 0x11;
	break;

      case 4:
	i2cbuf[1] = 0x04;
	i2cbuf[2] = 0x2B;
	break;

      case 6:
	i2cbuf[1] = 0x05;
	i2cbuf[2] = 0xC0;
	break;

      case 8:
	i2cbuf[1] = 0x00;
	i2cbuf[2] = 0x40;
	break;

      case 10:
	i2clen = 3;
	i2cbuf[1] = 0x09;
	i2cbuf[2] = 0x03;
	break;

      case 12:
	i2cbuf[1] = 0xFD;
	i2cbuf[2] = 0x40;
	break;

      case 14:
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
	i2clen = 24;
	i2cbuf[1] = 0x18 + ((dpy_step-16)&~1)*11;
	for(uint8_t i=2; i<24; i++)
	    i2cbuf[i] = pgm_read_byte(pwm_bits
				     + ((dpy_step&1)? 132: 0)
				     + ((dpy_step-16)&~1)*11
				     + i-2);
	break;

      case 28:
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
    dpy_step++;
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

void do_con_in(char* s, uint8_t len) {
    switch(*s) {
      case 's':
	out('S');
	hex(status);
	write();
	return;

      case 'r':
	out('R');
	for(uint8_t i=0; i<sizeof(report); i++)
	    hex(((char*)&report)[i]);
	out(' ');
	hex(dpy_step);
	hex(i2cs);
	hex(i2ce);
	hex(TWCR);
	hex(TWSR);
	write();
	return;

      case 'd':
	if(len == 4) {
	    if(s[1]>='a' && s[1]<'s')
		display[s[1]-'a'] = unhex(s+2);
	    if(dpy_set())
		dpy_step = 32;
	}
	return;

      case 'l':
	if(len==3) {
	    leds = unhex(s+1);
	    if(dpy_set())
		dpy_step = 32;
	}
	return;

      case 'b':
	if(len == 2 && s[1]=='P') {
	    _delay_ms(1);
	    USB_Detach();
	    _delay_ms(2);
	    cli();
	    *(uint16_t*)(RAMEND-1) = 0x7777;
	    wdt_enable(WDTO_120MS);
	    for(;;)
		;
	}
	break;

      case 'v':
	  out('M'); outs(s_model, 15); crlf();
	  out('V'); outs(s_version, 5); write();
	  return;
    }

    while(len--)
	out(*s++);
    out('?');
    write();

}

void EVENT_USB_Device_ControlRequest(void)
{
        /* Handle HID Class specific requests */
        switch (USB_ControlRequest.bRequest) {
	  case HID_REQ_GetReport:
	    if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
	      {
		Endpoint_ClearSETUP();
		Endpoint_Write_Control_Stream_LE((Report*)&report, sizeof(Report));
		report_changed = false;
		Endpoint_ClearOUT();
	      }

	    break;

	  case HID_REQ_SetReport:
	    if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
	      {
		Endpoint_ClearSETUP();

		if(Endpoint_Read_Control_Stream_LE((uint8_t*)&led_report, sizeof(LedReport)) == ENDPOINT_RWSTREAM_NoError) {
		    for(int i=0; i<18; i++)
			display[i] = led_report.digits[i];
		    leds = led_report.leds;
		    if(dpy_set())
			dpy_step = 32;
		}

		Endpoint_ClearIN();
	      }

	    break;

	  case CDC_REQ_GetLineEncoding:
	    if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
	      {
		Endpoint_ClearSETUP();

		/* Write the line coding data to the control endpoint */
		Endpoint_Write_Control_Stream_LE(&linesetup, sizeof(CDC_LineEncoding_t));
		Endpoint_ClearOUT();
	      }

	    break;
	  case CDC_REQ_SetLineEncoding:
	    if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
	      {
		Endpoint_ClearSETUP();

		/* Read the line coding data in from the host into the global struct */
		Endpoint_Read_Control_Stream_LE(&linesetup, sizeof(CDC_LineEncoding_t));
		Endpoint_ClearIN();
	      }

	    break;
	  case CDC_REQ_SetControlLineState:
	    if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
	      {
		Endpoint_ClearSETUP();
		Endpoint_ClearStatusStage();

		/* NOTE: Here you can read in the line state mask from the host, to get the current state of the output handshake
		   lines. The mask is read in from the wValue parameter in USB_ControlRequest, and can be masked against the
		   CONTROL_LINE_OUT_* masks to determine the RTS and DTR line states using the following code:
		 */
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

    linesetup.BaudRateBPS = 0;

    for(uint8_t i=0; i<8; i++)
	iobuf[i].end = 0;
//    xmit_buf = 0;
//    recv_buf = 0;
//    write_buf = 0;
//    read_buf = 0;
    b_usbin = 0;
    bl_usbin = 0;
    b_usbout = 0;
    b_out = 0;
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

    dpy_step = 0;
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
	// decode();

	if(ready)
	    dpy_update();

	if(milis > 50) {

	    milis = 0;
	    ready = 1;

	    if(!report_changed)
		update_report();
//	    if(report_changed) {
//		report_changed = false;
//		out('s');
//		for(int i=0; i<4; i++)
//		    hex(report.dswitch[i]);
//		out(' ');
//		hex(report.ap>>8);
//		hex(report.ap);
//		out(' ');
//		for(int i=0; i<3; i++)
//		    hex(report.switches[i]);
//		crlf();
//		write();
//	    }

	    USB_USBTask();
	    if (USB_DeviceState == DEVICE_STATE_Configured) {

		update_report();
		do_usb_io();

		cli();
		IOBuf* b;
		if((b = b_usbin)) {
		    b_usbin = b_usbin->next;
		    sei();
		    do_con_in((char*)b->buf, b->end);
		    cli();
		    b->end = 0;
		}
		sei();
	    }

	}

    }
}

