
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>

#include <util/delay.h>

#define BUFS 8
#define BSIZE 44
typedef struct _iobuf {
    volatile uint8_t		len;
    volatile uint8_t		end;
    struct _iobuf* volatile	next;
    volatile char		buf[BSIZE];
} IOBuf;

static IOBuf		iobuf[BUFS];
static IOBuf* volatile	xmit_buf = 0;
static IOBuf* volatile	recv_buf = 0;
static IOBuf* volatile	write_buf = 0;
static IOBuf* volatile	read_buf = 0;

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
    }
}

void queuebuf(IOBuf* buf, IOBuf* volatile* bp)
{
    if(*bp) {
	IOBuf* b = *bp;
	while(b->next)
	    b = b->next;
	b->next = buf;
    } else
	*bp = buf;
}

void xmitbuf(IOBuf* b)
{
    b->len = 0;
    cli();
    queuebuf(b, &xmit_buf);
    UCSR0B = UCSR0B | 0x20;
    sei();
}

ISR(USART0_RX_vect)
{
    char rx = UDR0;
    if(rx & 0x80) {
	if(recv_buf)
	    queuebuf(recv_buf, &read_buf);
	recv_buf = newbuf(rx & 0x7F);
    } else if(recv_buf) {
	if(recv_buf->end < BSIZE)
	    recv_buf->buf[recv_buf->end++] = rx;
	if(recv_buf->end > recv_buf->len) {
	    queuebuf(recv_buf, &read_buf);
	    recv_buf = 0;
	}
    }
}

ISR(USART0_UDRE_vect)
{
    if(xmit_buf && xmit_buf->len < xmit_buf->end) {
	UDR0 = xmit_buf->buf[xmit_buf->len++];
	if(xmit_buf->len >= xmit_buf->end) {
	    xmit_buf->end = 0;
	    xmit_buf = xmit_buf->next;
	}
    }
    if(!xmit_buf)
	UCSR0B = UCSR0B & ~0x20;
}

static uint8_t inputs[38];
static int8_t  encoders[4];
static uint8_t encstate[4];
static uint8_t milis;

static const uint8_t enc_sm[20] PROGMEM = {
    /*             AB    aB    Ab    ab    */
    /*  Z:0 */   0x00, 0x04, 0x01, 0x00,
    /*  A:1 */   0x02, 0x04, 0x01, 0x00,
    /* AB:2 */   0x02, 0x14, 0x01, 0x00,
    /* BA:3 */   0x03, 0x04, 0x21, 0x00,
    /*  B:4 */   0x03, 0x04, 0x01, 0x00,
};

#define BOUNCE(n) { if(inputs[n]<7) inputs[n]++; } else if(inputs[n]) --inputs[n]

ISR(TIMER1_COMPA_vect)
{
    uint8_t	pins = PINA;

    if(!(pins&0x01)) BOUNCE(0);
    if(!(pins&0x02)) BOUNCE(1);
    if(!(pins&0x04)) BOUNCE(2);
    if(!(pins&0x08)) BOUNCE(3);
    if(!(pins&0x10)) BOUNCE(4);
    if(!(pins&0x20)) BOUNCE(5);
    if(!(pins&0x40)) BOUNCE(6);
    if(!(pins&0x80)) BOUNCE(7);

    pins = PINB;
    if( (pins&0x01)) BOUNCE(36);
    if( (pins&0x04)) BOUNCE(37);

    pins = PINC;
    if(!(pins&0x01)) BOUNCE(8);
    if(!(pins&0x02)) BOUNCE(9);
    if(!(pins&0x04)) BOUNCE(10);
    if( (pins&0x08)) BOUNCE(16);
    if( (pins&0x10)) BOUNCE(17);
    if( (pins&0x20)) BOUNCE(18);
    if( (pins&0x40)) BOUNCE(19);
    if( (pins&0x80)) BOUNCE(20);

    pins = PIND;
    if( (pins&0x80)) BOUNCE(32);

    pins = PINE;
    if(!(pins&0x08)) BOUNCE(12);
    if(!(pins&0x10)) BOUNCE(15);
    if(!(pins&0x20)) BOUNCE(14);

    pins = PING;
    if( (pins&0x01)) BOUNCE(29);
    if( (pins&0x02)) BOUNCE(30);
    if( (pins&0x04)) BOUNCE(31);
    if(!(pins&0x20)) BOUNCE(13);

    pins = PINH;
    if( (pins&0x10)) BOUNCE(33);
    if( (pins&0x20)) BOUNCE(34);
    if( (pins&0x40)) BOUNCE(35);

    pins = PINL;
    if( (pins&0x01)) BOUNCE(21);
    if( (pins&0x02)) BOUNCE(22);
    if( (pins&0x04)) BOUNCE(23);
    if( (pins&0x08)) BOUNCE(24);
    if( (pins&0x10)) BOUNCE(25);
    if( (pins&0x20)) BOUNCE(26);
    if( (pins&0x40)) BOUNCE(27);
    if( (pins&0x80)) BOUNCE(28);

    milis++;
}

void decode(void)
{
    uint8_t ns;
    uint8_t pins = PINB;

    ns = pgm_read_byte(enc_sm + (encstate[3]<<2) + (((pins&0x02)>>1) | ((pins&0x08)>>2)));
    encstate[3] = ns & 0x0F;
    if((ns&0x10) && encoders[3]<127)
	encoders[3]++;
    if((ns&0x20) && encoders[3]>-127)
	--encoders[3];

    ns = pgm_read_byte(enc_sm + (encstate[1]<<2) + ((pins>>4) & 0x03));
    encstate[1] = ns & 0x0F;
    if((ns&0x10) && encoders[1]<127)
	encoders[1]++;
    if((ns&0x20) && encoders[1]>-127)
	--encoders[1];

    ns = pgm_read_byte(enc_sm + (encstate[2]<<2) + ((pins>>6) & 0x03));
    encstate[2] = ns & 0x0F;
    if((ns&0x10) && encoders[2]<127)
	encoders[2]++;
    if((ns&0x20) && encoders[2]>-127)
	--encoders[2];

    ns = pgm_read_byte(enc_sm + (encstate[0]<<2) + (PINJ & 3));
    encstate[0] = ns & 0x0F;
    if((ns&0x10) && encoders[0]<127)
	encoders[0]++;
    if((ns&0x20) && encoders[0]>-127)
	--encoders[0];

}

const char PROGMEM info[] = "i:SIMPANEL SB rev. A 00.90";

void out(IOBuf* b, char c) {
    if(b->end < BSIZE)
	b->buf[b->end++] = c;
}

void outs(IOBuf* b, const char* s, uint8_t len) {
    while(len-- && b->end < BSIZE)
	b->buf[b->end++] = pgm_read_byte(s++);
}

void hex(IOBuf* b, uint8_t n) {
    out(b, '0'+((n>>4)&0x0F)+((n>0x9F)? 7: 0));
    out(b, '0'+(n&0x0F)+(((n&0x0F)>9)? 7: 0));
}

static uint8_t prport[10];
static uint8_t report[10];

int main(void)
{
    //    TCCR1B = 0x03;
    //
    MCUCR = MCUCR & ~0x10;

    UCSR0A = 0x02; // U2X1
    UCSR0B = 0x98; // Enable xmit, xmit interrupt, rcv
    UCSR0C = 0x06; // 8 bit 1 stop no parity
    UBRR0 = 7;     // 250kbps

    MCUSR &= ~(1 << WDRF);
    wdt_disable();
    clock_prescale_set(clock_div_1);

    for(uint8_t i=0; i<8; i++)
	iobuf[i].end = 0;
    xmit_buf = 0;
    recv_buf = 0;
    write_buf = 0;
    read_buf = 0;
    memset(inputs, 0, 38);
    memset(encoders, 0, 4);
    memset(encstate, 0, 4);

    ADCSRA = 0x00; // disable ADC
    ACSR   = 0x80; // disable analog comarator
    DIDR1  = 0x00; // make sure digital in is enabled

    DDRA   = 0x00;
    PORTA  = 0xFF;
    DDRB   = 0x00;
    PORTB  = 0xFA;
    DDRC   = 0x00;
    PORTC  = 0x07;
    DDRD   = 0x00;
    PORTD  = 0x00;
    DDRE   = 0x00;
    PORTE  = 0x38;
    DDRG   = 0x00;
    PORTG  = 0x20;
    DDRH   = 0x00;
    PORTH  = 0x00;
    DDRJ   = 0x00;
    PORTJ  = 0x03;
    DDRL   = 0x00;
    PORTL  = 0x00;

    TCCR3A = 0x00;
    TCCR4A = 0x00;
    TCCR5A = 0x00;

    TCCR1A = 0x00;  // no output, WGM = 0b..00
    TCCR1B = 0x0A;  // clock/8, WGM = 0b01..
    OCR1A  = 2000;  // every ms
    TIMSK1 = 0x02;  // enable interrupt on OCR1A

    sei();

    for(;;) {
	decode();
	if(milis > 50) {
	    uint8_t send = 0;

	    milis = 0;

	    for(uint8_t i=0; i<4; i++) {
		send |= (report[i] = encoders[i]);
		encoders[i] = 0;
	    }

	    report[4]   = ((inputs[ 0]&4)? 0x01: 0)
	    		| ((inputs[ 1]&4)? 0x02: 0)
			| ((inputs[ 2]&4)? 0x04: 0)
			| ((inputs[ 3]&4)? 0x08: 0)
			| ((inputs[ 4]&4)? 0x10: 0)
			| ((inputs[ 5]&4)? 0x20: 0)
			| ((inputs[ 6]&4)? 0x40: 0)
			| ((inputs[ 7]&4)? 0x80: 0);
	    report[5]   = ((inputs[ 8]&4)? 0x01: 0)
			| ((inputs[ 9]&4)? 0x02: 0)
			| ((inputs[10]&4)? 0x04: 0);
	    report[6]   = ((inputs[16]&4)? 0x01: 0)
			| ((inputs[17]&4)? 0x02: 0)
			| ((inputs[18]&4)? 0x04: 0)
			| ((inputs[19]&4)? 0x08: 0)
			| ((inputs[20]&4)? 0x10: 0)
			| ((inputs[21]&4)? 0x20: 0)
			| ((inputs[22]&4)? 0x40: 0)
			| ((inputs[23]&4)? 0x80: 0);
	    report[7]   = ((inputs[24]&4)? 0x01: 0)
			| ((inputs[25]&4)? 0x02: 0)
			| ((inputs[26]&4)? 0x04: 0)
			| ((inputs[27]&4)? 0x08: 0)
			| ((inputs[28]&4)? 0x10: 0)
			| ((inputs[29]&4)? 0x20: 0)
			| ((inputs[30]&4)? 0x40: 0)
			| ((inputs[31]&4)? 0x80: 0);
	    report[8]   = ((inputs[32]&4)? 0x01: 0)
			| ((inputs[33]&4)? 0x02: 0)
			| ((inputs[34]&4)? 0x04: 0)
			| ((inputs[35]&4)? 0x08: 0)
			| ((inputs[36]&4)? 0x10: 0)
			| ((inputs[37]&4)? 0x20: 0);
	    report[9]   = ((inputs[12]&4)? 0x01: 0)
			| ((inputs[13]&4)? 0x02: 0)
			| ((inputs[14]&4)? 0x04: 0)
			| ((inputs[15]&4)? 0x08: 0);

	    for(uint8_t i=4; i<10; i++)
		if(prport[i] != report[i]) {
		    send |= 1;
		    prport[i] = report[i];
		}

	    if(send) {
		IOBuf* b = newbuf(21);
		out(b, 's');

		for(uint8_t i=0; i<10; i++) {
		    hex(b, report[i]);
		}

		xmitbuf(b);
	    }
	}
	cli();
	IOBuf*	b = read_buf;
	if(b)
	    read_buf = b->next;
	sei();
	if(b) {
	    if(!write_buf)
		write_buf = newbuf(0);
	    if(b->end == b->len+1) switch(b->buf[1]) {
	      case 'v':
		outs(write_buf, info, sizeof(info));
		break;
	      case 'r':
		out(write_buf, 'l');
		out(write_buf, 'T');
		for(uint8_t i=0; i<11; i++)
		    out(write_buf, (inputs[i]&4)? '*': 'o');
		for(uint8_t i=0; i<4; i++) {
		    out(write_buf, ' ');
		    hex(write_buf, encoders[i]);
		}
		break;
	      case 's':
		out(write_buf, 'l');
		out(write_buf, 'S');

		for(uint8_t i=0; i<10; i++) {
		    hex(write_buf, report[i]);
		}
		break;

	      default:
		out(write_buf, 'l');
		out(write_buf, 'E');
		out(write_buf, b->buf[1]);
		out(write_buf, '?');
		break;
	    }
	    b->end = 0;
	    if(write_buf->end > 1) {
		write_buf->buf[0] = 0x80 | (write_buf->len = write_buf->end-1);
		xmitbuf(write_buf);
		write_buf = 0;
	    }
	}
    }
}

