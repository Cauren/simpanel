

#include "display.h"
#include "images.h"


// 00101000 00101000 00101000 c0
// 00111100 00111001 00101011 c1
// 00110010 00101111 00100010 c2
// 00100011 00100001 00010100 c3
// 01001001 01000110 00111000 c4
// 00000000 00000000 00000000 black
// 10110011 11111111 00000000 lit_led
// 00011100 00100011 00001110 off_led
// 11111111 11111010 11110100 white


// 0011 0001 1000 0110 c0
// 0010 1001 0100 0101
// 0011 1001 1100 0101 c1
// 0011 0001 0110 0100 c2
// 0010 0001 0000 0010 c3
// 0100 1010 0010 0111 c4
// 0000 0000 0000 0000 black
// 1011 0111 1110 0000 lit_led
// 0001 1001 0000 0001 off_led
// 1111 1111 1101 1110 white
// 0010 0111 1110 0100 red text

static const unsigned short default_pal[8] = {
	0x2945, // c0
	0x39C5, // c1
	0x3164, // c2
	0x2102, // c3
	0x4A27, // c4
	0x0000, // black
	0xB7E0, // lit_led
	0xFFDE, // white
};

static const unsigned short lit_led_pal[8] = {
	0x2945, // c0
	0x39C5, // c1
	0x3164, // c2
	0x2102, // c3
	0x4A27, // c4
	0x0000, // black
	0xB7E0, // lit_led
	0x1901, // unlit_led
};

static const unsigned short unlit_led_pal[8] = {
	0x2945, // c0
	0x39C5, // c1
	0x3164, // c2
	0x2102, // c3
	0x4A27, // c4
	0x0000, // black
	0x1901, // unlit_led
	0xB7E0, // lit_led
};

static const unsigned short red_text_pal[8] = {
	0x2945, // c0
	0x39C5, // c1
	0x3164, // c2
	0x2102, // c3
	0x4A27, // c4
	0x0000, // black
	0xB7E0, // lit_led
	0x27E4, // red_text
};


typedef enum {
    Mode_COM, Mode_XPNDR, Mode_NAV, Mode_ADF, Mode_TACAN,
} DisplayMode;

typedef enum {
    Phase_Init, Phase_Update, Phase_Menu, Phase_Start_Keypad, Phase_Keypad,
} DisplayPhase;

DisplayMode mode = Mode_COM;
DisplayPhase phase = Phase_Init;

unsigned int com1_kHz = 123200;
unsigned int com1_stdby_kHz = 121900;
unsigned int com2_kHz = 11396;
unsigned int com2_stdby_kHz = 6577;
unsigned int nav1_kHz = 110100;
unsigned int nav1_stdby_kHz = 111000;
unsigned int nav2_kHz = 117250;
unsigned int nav2_stdby_kHz = 116750;
unsigned int adf_kHz = 1045;
unsigned char monitor = 1; // com1 com2 nav1 nav2 adf
unsigned char mic = 0;

void bracket(short y1, short y2, const unsigned char* bra_start)
{
    draw(1,   7, y1, default_pal, bra_start);
    draw(1,  79, y1, default_pal, IMAGE_BIT(bra_mid));
    draw(1, 191, y1, default_pal, IMAGE_BIT(bra_end));
    draw(1,   7, y2, default_pal, IMAGE_BIT(ket_start));
    draw(1,  71, y2, default_pal, IMAGE_BIT(ket_mid));
    draw(1, 191, y2, default_pal, IMAGE_BIT(ket_end));
}

unsigned char map_dp_button()
{
    int b = 1 + dp_x + 3*dp_y;

    switch(mode) {
      case Mode_COM:
      case Mode_NAV:
	switch(b) {
	  case 2:
	  case 5:
	  case 8:
	  case 11:
	    b--;
	    break;
	  case 6:
	    b = 3;
	    break;
	  case 12:
	    b = 9;
	    break;
	  case 14:
	    if(mode==Mode_NAV)
		b = 0;
	    break;
	}
	break;
      case Mode_XPNDR:
	if(b<4)
	    b = 1;
	else if(b<13)
	    b = 0;
	break;
    }

    return b;
}

void draw_dp_button(unsigned char b, unsigned char pressed)
{
    switch(mode) {
      case Mode_COM:
	switch(b) {
	  case 13:
	    draw(1, 7, 384, default_pal, IMAGE_BUTTON(com1, pressed));
	    draw(1, 7, 441, (monitor&1)? lit_led_pal: unlit_led_pal, IMAGE_BUTTON(led_single, pressed));
	    break;
	  case 14:
	    draw(1, 111, 384, default_pal, IMAGE_BUTTON(mic, pressed));
	    draw(1, 111, 441, (mic==0)? lit_led_pal: unlit_led_pal, IMAGE_BUTTON(led_double, pressed));
	    break;
	  case 15:
	    draw(1, 215, 384, default_pal, IMAGE_BUTTON(com2, pressed));
	    draw(1, 215, 441, (monitor&2)? lit_led_pal: unlit_led_pal, IMAGE_BUTTON(led_single, pressed));
	    break;
	  case 3:
	    draw(1, 242, 61, default_pal, IMAGE_BUTTON(xfer, pressed));
	    break;
	  case 9:
	    draw(1, 242, 249, default_pal, IMAGE_BUTTON(xfer, pressed));
	    break;
	}
	break;
      case Mode_NAV:
	switch(b) {
	  case 13:
	    draw(1, 7, 384, default_pal, IMAGE_BUTTON(nav1, pressed));
	    draw(1, 7, 441, (monitor&4)? lit_led_pal: unlit_led_pal, IMAGE_BUTTON(led_single, pressed));
	    break;
	  case 15:
	    draw(1, 215, 384, default_pal, IMAGE_BUTTON(nav2, pressed));
	    draw(1, 215, 441, (monitor&8)? lit_led_pal: unlit_led_pal, IMAGE_BUTTON(led_single, pressed));
	    break;
	  case 3:
	    draw(1, 242, 61, default_pal, IMAGE_BUTTON(xfer, pressed));
	    break;
	  case 9:
	    draw(1, 242, 249, default_pal, IMAGE_BUTTON(xfer, pressed));
	    break;
	}
	break;
    }
}

void draw_freq(short y, unsigned long freq, unsigned char mhz)
{
    unsigned char d[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    unsigned char nd = 0;
    while(freq && nd<8) {
	d[nd++] = freq % 10;
	freq /= 10;
    }
    const unsigned short* pal = default_pal;
    if(mhz) {
	draw(1, 27, y, pal, IMAGE_BIT(digit_0+d[5]));
	draw(1, 56, y, pal, IMAGE_BIT(digit_0+d[4]));
	draw(1, 85, y, pal, IMAGE_BIT(digit_0+d[3]));
	draw(1, 114, y, pal, IMAGE_BIT(digit_decimal));
	draw(1, 143, y, pal, IMAGE_BIT(digit_0+d[2]));
	draw(1, 172, y, pal, IMAGE_BIT(digit_0+d[1]));
	draw(1, 201, y, pal, IMAGE_BIT(digit_0+d[0]));
	draw(1, 191, y+36, default_pal, IMAGE_BIT(unit_mhz));
    } else {
	int leading=1;
	for(int i=0; i<7; i++)
	    if(d[6-i]) {
		draw(1, 27+29*i, y, pal, IMAGE_BIT(digit_0+d[6-i]));
		leading = 0;
	    } else {
		if(!leading)
		    draw(1, 27+29*i, y, pal, IMAGE_BIT(digit_0));
		else
		    fill(1, 27+29*i, y, 26, 34, pal);
	    }
	draw(1, 191, y+36, default_pal, IMAGE_BIT(unit_khz));
    }
}

int main(int argc, char** argv)
{
    start_display();

    wait_display();
    fill(0, 0, 0, 320, 480, default_pal);

    int kp_pressing = 0;
    int dp_pressing = 0;
    int kp_over;
    int dp_over;
    int kp_pushed;
    int dp_pushed;

    for(;;) {
	if(mode == Mode_TACAN)
	    break;

	wait_display();

	switch(phase) {
	  case Phase_Init:
	    fill(0, 7, 8, 205, 464, default_pal);
	    fill(1, 0, 0, 320, 480, default_pal);
	    for(int m=0; m<5; m++)
		draw(0, 215, 7+95*m, default_pal, images_buttons[m+BUTTON_menu_com][(m==mode)? 1: 0]);
	    phase = Phase_Menu;
	    kp_pressing = 0;
	    dp_pressing = 0;
	    switch(mode) {
	      case Mode_COM:
		bracket( 11, 177, IMAGE_BIT(bra_com1));
		bracket(199, 365, IMAGE_BIT(bra_com2));
		draw_dp_button(13, 0);
		draw_dp_button(14, 0);
		draw_dp_button(15, 0);
		draw_dp_button(3, 0);
		draw_dp_button(9, 0);
		draw_freq(46, com1_kHz, 1);
		draw_freq(119, com1_stdby_kHz, 1);
		draw_freq(234, com2_kHz, 0);
		draw_freq(307, com2_stdby_kHz, 0);
		break;
	      case Mode_NAV:
		bracket( 11, 177, IMAGE_BIT(bra_nav1));
		bracket(199, 365, IMAGE_BIT(bra_nav2));
		draw_dp_button(13, 0);
		draw_dp_button(15, 0);
		draw_dp_button(3, 0);
		draw_dp_button(9, 0);
		draw_freq(46, nav1_kHz, 1);
		draw_freq(119, nav1_stdby_kHz, 1);
		draw_freq(234, nav2_kHz, 1);
		draw_freq(307, nav2_stdby_kHz, 1);
		break;
	    }
	    break;

	  case Phase_Keypad:
	    break;

	  case Phase_Menu:
	    kp_over = 1 + kp_x + 3*kp_y;
	    dp_over = map_dp_button();

	    if(kp_press) {
		DisplayMode nm = mode;
		switch(kp_over) {
		  case 3: nm = Mode_COM; break;
		  case 6: nm = Mode_XPNDR; break;
		  case 9: nm = Mode_NAV; break;
		  case 12: nm = Mode_ADF; break;
		  case 15: nm = Mode_TACAN; break;
		}
		if(nm != mode) {
		    mode = nm;
		    phase = Phase_Init;
		    break;
		}
	    }

	    if(dp_pressing) {
		if(dp_press && dp_pushed != (dp_over==dp_pressing)) {
		    dp_pushed = dp_over==dp_pressing;
		    draw_dp_button(dp_pressing, dp_pushed);
		}
		if(!dp_press) {
		    if(dp_pushed) {
			unsigned int tmp;

			switch(mode) {
			  case Mode_COM:
			    switch(dp_pressing) {
			      case 3: // COM1 XFER
				tmp = com1_kHz;
				com1_kHz = com1_stdby_kHz;
				com1_stdby_kHz = tmp;
				draw_freq(46, com1_kHz, 1);
				draw_freq(119, com1_stdby_kHz, 1);
				break;
			      case 9:
				tmp = com2_kHz;
				com2_kHz = com2_stdby_kHz;
				com2_stdby_kHz = tmp;
				draw_freq(234, com2_kHz, 0);
				draw_freq(307, com2_stdby_kHz, 0);
				break; // COM2 XFER
			      case 13: // mon COM1
				if(mic != 0)
				    monitor ^= 1;
				break;
			      case 14: // mic
				mic = mic? 0: 1;
				monitor |= mic? 2: 1;
				draw_dp_button(13, 0);
				draw_dp_button(15, 0);
				break;
			      case 15: // mon COM2
				if(mic != 1)
				    monitor ^= 2;
				break;

			    }
			    break;
			  case Mode_NAV:
			    switch(dp_pressing) {
			      case 3: // NAV1 XFER
				tmp = nav1_kHz;
				nav1_kHz = nav1_stdby_kHz;
				nav1_stdby_kHz = tmp;
				draw_freq(46, nav1_kHz, 1);
				draw_freq(119, nav1_stdby_kHz, 1);
				break;
			      case 9:
				tmp = nav2_kHz;
				nav2_kHz = nav2_stdby_kHz;
				nav2_stdby_kHz = tmp;
				draw_freq(234, nav2_kHz, 1);
				draw_freq(307, nav2_stdby_kHz, 1);
				break; // NAV2 XFER
			      case 13: // mon NAV1
				monitor ^= 4;
				break;
			      case 15: // mon NAV2
				monitor ^= 8;
				break;

			    }
			    break;
			}
			draw_dp_button(dp_pressing, 0);
		    }

		    dp_pressing = 0;
		}
	    } else if(dp_press && dp_over) {
		switch(mode) {
		  case Mode_COM:
		  case Mode_NAV:
		    switch(dp_over) {
		      case 1: // COM1 FREQ
			break;
		      case 4: // COM1 STBY
			break;
		      case 7: // COM2 FREQ
			break;
		      case 10:// COM2 STBY
			break;
		      default:
			dp_pressing = dp_over;
			dp_pushed = 1;
			draw_dp_button(dp_pressing, 1);
			break;
		    }
		    break;
		}
	    }
	    break;
	}
    }

    end_display();
}

