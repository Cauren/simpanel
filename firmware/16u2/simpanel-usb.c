

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>

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
    uint8_t		dials;
    uint8_t		dswitch[4];
    uint16_t		ap;
    uint8_t		switches[3];
} Report;

typedef struct {
    int8_t		dials[4];
    uint16_t		ap;
    uint8_t		switches[3];
    uint8_t		dswitch;
} MCUReport;

#define S(_sn_) _HID_RI_ENTRY(HID_RI_TYPE_LOCAL , 0x70, 8, SI_##_sn_)
#define SMIN(_sn_) _HID_RI_ENTRY(HID_RI_TYPE_LOCAL , 0x80, 8, SI_##_sn_)
#define SMAX(_sn_) _HID_RI_ENTRY(HID_RI_TYPE_LOCAL , 0x90, 8, SI_##_sn_)

const USB_Descriptor_HIDReport_Datatype_t PROGMEM ControlsReport[] = {
    HID_RI_USAGE_PAGE(8, 0x01), /* Generic Desktop */
    HID_RI_USAGE(8, 0x05), /* Gamepad */
    HID_RI_COLLECTION(8, 0x01), /* Application */

    	// Autopilot
        HID_RI_USAGE_PAGE(8, 0x02), /* Simulation controls */
        HID_RI_USAGE(8, 0x01), /* Flight Simulation device */
	S(g_ap),
	HID_RI_COLLECTION(8, 0x02),

	    HID_RI_LOGICAL_MINIMUM(8, 0),
	    HID_RI_LOGICAL_MAXIMUM(8, 1),
	    HID_RI_USAGE_PAGE(8, 0x09), /* Button */
	    HID_RI_USAGE_MINIMUM(8, 1),
	    HID_RI_USAGE_MAXIMUM(8, 8),
	    SMIN(dial1m),
	    SMAX(dial4p),
	    HID_RI_REPORT_COUNT(8, 8),
	    HID_RI_REPORT_SIZE(8, 1),
	    HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

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
		HID_RI_USAGE(8, 9),
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
		HID_RI_USAGE(8, 10),
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
		HID_RI_USAGE(8, 11),
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
		HID_RI_USAGE(8, 12),
		HID_RI_LOGICAL_MINIMUM(8, 0),
		HID_RI_LOGICAL_MAXIMUM(8, 1),
		S(dial4b),
		HID_RI_REPORT_COUNT(8, 1),
		HID_RI_REPORT_SIZE(8, 1),
		HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
	    HID_RI_END_COLLECTION(0),

	    HID_RI_USAGE_PAGE(8, 0x09), /* Button */
	    HID_RI_USAGE_MINIMUM(8, 13),
	    HID_RI_USAGE_MAXIMUM(8, 24),
	    HID_RI_LOGICAL_MINIMUM(8, 0),
	    HID_RI_LOGICAL_MAXIMUM(8, 1),
	    SMIN(ap_sw1),
	    SMAX(ap_sw12),
	    HID_RI_REPORT_COUNT(8, 12),
	    HID_RI_REPORT_SIZE(8, 1),
	    HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

	    HID_RI_REPORT_COUNT(8, 1),
	    HID_RI_REPORT_SIZE(8, 4),
	    HID_RI_INPUT(8, HID_IOF_CONSTANT),

	HID_RI_END_COLLECTION(0),

	HID_RI_USAGE_PAGE(8, 0x02),
	HID_RI_USAGE(8, 0x01),
	S(g_sw),
	HID_RI_COLLECTION(8, 0x02),

	    HID_RI_USAGE_PAGE(8, 0x09), /* Button */
	    HID_RI_USAGE_MINIMUM(8, 25),
	    HID_RI_USAGE_MAXIMUM(8, 46),
	    SMIN(s1),
	    SMAX(s16),
	    HID_RI_REPORT_COUNT(8, 22),
	    HID_RI_REPORT_SIZE(8, 1),
	    HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

	    HID_RI_REPORT_COUNT(8, 1),
	    HID_RI_REPORT_SIZE(8, 2),
	    HID_RI_INPUT(8, HID_IOF_CONSTANT),

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
	.Header                 = {.Size = sizeof(USB_CDC_Descriptor_FunctionalHeader_t), .Type = DTYPE_CSInterface},
	.Subtype                = CDC_DSUBTYPE_CSInterface_Header,

	.CDCSpecification       = VERSION_BCD(1,1,0),
      },

    .CDC_Functional_ACM =
      {
	.Header                 = {.Size = sizeof(USB_CDC_Descriptor_FunctionalACM_t), .Type = DTYPE_CSInterface},
	.Subtype                = CDC_DSUBTYPE_CSInterface_ACM,

	.Capabilities           = 0x06,
      },

    .CDC_Functional_Union =
      {
	.Header                 = {.Size = sizeof(USB_CDC_Descriptor_FunctionalUnion_t), .Type = DTYPE_CSInterface},
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
static volatile MCUReport	mcu_report;
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

#define BUFS 8
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
static IOBuf* volatile  b_mcuin = 0;
static IOBuf* volatile  bl_mcuin = 0;
static IOBuf* volatile  b_mcuout = 0;
static IOBuf* volatile  b_out = 0;

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


ISR(USART1_RX_vect)
{
    char rx = UDR1;
    if(rx & 0x80) {
	if(bl_mcuin)
	    queuebuf(bl_mcuin, &b_mcuin);
	bl_mcuin = newbuf(rx & 0x7F);
    } else if(bl_mcuin) {
	if(bl_mcuin->end < BSIZE)
	    bl_mcuin->buf[bl_mcuin->end++] = rx;
	if(bl_mcuin->end > bl_mcuin->len) {
	    queuebuf(bl_mcuin, &b_mcuin);
	    bl_mcuin = 0;
	}
    }
}

ISR(USART1_UDRE_vect)
{
    if(b_mcuout && b_mcuout->len < b_mcuout->end) {
	UDR1 = b_mcuout->buf[b_mcuout->len++];
	if(b_mcuout->len >= b_mcuout->end) {
	    b_mcuout->end = 0;
	    b_mcuout = b_mcuout->next;
	}
    }
    if(!b_mcuout)
	UCSR1B = UCSR1B & ~0x20;
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

uint8_t unhex(const char* s) {
    return ( (s[0] - ((s[0]>'9')? 55: 48)) << 4 )
	   | (s[1] - ((s[1]>'9')? 55: 48));
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

void update_report(void)
{
    new_report.dswitch[0] = (mcu_report.dswitch&0x01) ? 0x80: 0x00;
    new_report.dswitch[1] = (mcu_report.dswitch&0x02) ? 0x80: 0x00;
    new_report.dswitch[2] = (mcu_report.dswitch&0x04) ? 0x80: 0x00;
    new_report.dswitch[3] = (mcu_report.dswitch&0x08) ? 0x80: 0x00;
    new_report.ap = mcu_report.ap;
    new_report.switches[0] = mcu_report.switches[0];
    new_report.switches[1] = mcu_report.switches[1];
    new_report.switches[2] = mcu_report.switches[2];

    if(!report_changed && !slow_report) {
	uint8_t dials = 0;
	for(uint8_t i=0; i<4; i++)
	    if(!(new_report.dials & (0x03<<(i*2)))) {
		if(mcu_report.dials[i] < 0) {
		    dials |= 0x01 << (i*2);
		    new_report.dswitch[i] |= 0x7F;
		    mcu_report.dials[i]++;
		} else if(mcu_report.dials[i] > 0) {
		    dials |= 0x02 << (i*2);
		    new_report.dswitch[i] |= 0x01;
		    mcu_report.dials[i]--;
		}
	    }
	new_report.dials = dials;
    }

    cli();
    if(   report.dials != new_report.dials
       || report.dswitch[0] != new_report.dswitch[0]
       || report.dswitch[1] != new_report.dswitch[1]
       || report.dswitch[2] != new_report.dswitch[2]
       || report.dswitch[3] != new_report.dswitch[3]
       || report.ap != new_report.ap
       || report.switches[0] != new_report.switches[0]
       || report.switches[1] != new_report.switches[1]
       || report.switches[2] != new_report.switches[2] ) {
	memcpy((void*)&report, (const void*)&new_report, sizeof(report));
	report_changed = true;
    }
    sei();
}

static uint8_t updates = 0;
void do_mcu_in(char* s, uint8_t len) {
    if(!connected)
	return;

    switch(*s) {
      case 'l':
      case 'i':
      case 'x':
      case 'd':
	  if(len) {
	      out(*s-32);
	      while(--len)
		  out(*++s);
	      write();
	  }
	  return;

      case 's':
	if(len == sizeof(mcu_report)*2+1) {
	    updates++;
	    if(slow_report) {
		out('S');
		for(uint8_t i=1; i<len; i++)
		    out(s[i]);
		write();
	    }
	    ++s;
	    uint8_t* d = (uint8_t*)&mcu_report;
	    for(uint8_t i=0; i<4; i++) {
		int16_t v = mcu_report.dials[i];
		v += (int8_t)unhex(s);
		if(v < -127)
		    v = -127;
		if(v > 127)
		    v = 127;
		mcu_report.dials[i] = v;
		s += 2;
	    }
	    d += 4;
	    len -= 9;
	    while(len) {
		*d++ = unhex(s);
		s += 2;
		len -= 2;
	    }
	    update_report();
	    return;
	}
	break;
    }

    out('m');
    out(*s);
    out('?');
    write();
}

const char PROGMEM s_model[] = "SIMPANEL rev. A";
const char PROGMEM s_version[] = "01.00";

void mcu_send(char* s, uint8_t len) {
    IOBuf* w = newbuf(len+1);

    w->buf[0] = 0x80 | len;
    while(len--)
	w->buf[w->end++] = *s++;
    status = 5;
    w->len = 0;
    queuebuf(w, &b_mcuout);
    UCSR1B = UCSR1B | 0x20;
}

void do_con_in(char* s, uint8_t len) {
    switch(*s) {
      case 'm':
	if(len>1)
	    mcu_send(s+1, len-1);
	return;

      case 'f':
	do_mcu_in(s+1, len-1);
	return;

      case 's':
	out('S');
	hex(status);
	out(' ');
	hex(updates);
	write();
	return;

      case 'r':
	out('R');
	for(uint8_t i=0; i<sizeof(report); i++)
	    hex(((char*)&report)[i]);
	write();
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

      case 'x':
	if(len == 2)
	    slow_report = (s[1]=='s');
	out('X');
	out(slow_report? 'S': 'F');
	write();
	return;

      case 'v':
	  out('M'); outs(s_model, 15); crlf();
	  out('V'); outs(s_version, 5); write();
	  *s = 'v';
	  mcu_send(s, 1);
	  return;
    }

    while(len--)
	out(*s++);
    out('?');
    write();

}

void wait(int ms)
{
    while(ms--) {

	TCNT1 = 0;

	do {

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
		if((b = b_mcuin)) {
		    b_mcuin = b_mcuin->next;
		    sei();
		    // if((b->buf[0]&0x7F) == b->end-1)
			do_mcu_in((char*)b->buf+1, b->end-1);
		    cli();
		    b->end = 0;
		}
		sei();
	    }

	} while(TCNT1 < 250);

    }
}

int main(void)
{
    DDRD |= 0x30;
    PORTD |= 0x30;

    MCUSR &= ~(1 << WDRF);
    wdt_disable();
    clock_prescale_set(clock_div_1);

    linesetup.BaudRateBPS = 0;

    for(int i=0; i<BUFS; i++)
	iobuf[i].end = 0;

    b_usbin = 0;
    bl_usbin = 0;
    b_usbout = 0;
    b_mcuin = 0;
    bl_mcuin = 0;
    b_mcuout = 0;
    b_out = 0;
    updates = 0;

    TCCR1B = 0x03;

    UCSR1A = 0x02; // U2X1
    UCSR1B = 0x98; // Enable xmit, xmit interrupt, rcv
    UCSR1C = 0x06; // 8 bit 1 stop no parity
    UCSR1D = 0x00; // no flow control
    UBRR1 = 7;     // 250kbps

    USB_Init();
    GlobalInterruptEnable();

    for(;;) {
	wait(2000-status*300);
	for(uint8_t i=status; i; --i) {
	    PORTD = (PORTD & 0xEF) | 0x00;
	    wait(200);
	    PORTD = (PORTD & 0xEF) | 0x10;
	    wait(100);
	}
    }
}

