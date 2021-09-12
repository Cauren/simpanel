#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>

static Display* dpy;

static Window	wkp;
static Window	wdp;
static XImage*	ikp;
static XImage*	idp;
static Visual*	visual;
static GC	gc;

unsigned char ready = 0;
unsigned char kp_press = 0;
unsigned char kp_x, kp_y;
unsigned char dp_press = 0;
unsigned char dp_x, dp_y;
unsigned char dp_dirty = 0;

void wait_display()
{
    do {
	XEvent e;

	if(dp_dirty & 1)
	    XPutImage(dpy, wkp, gc, ikp, 0, 0, 0, 0, 320, 480);
	if(dp_dirty & 2)
	    XPutImage(dpy, wdp, gc, idp, 0, 0, 0, 0, 320, 480);
	if(dp_dirty)
	    XFlush(dpy);
	dp_dirty = 0;

	XNextEvent(dpy, &e);
	switch(e.type) {
	  case Expose:
	    if(e.xexpose.count)
		break;
	    if(e.xexpose.window == wkp) {
		ready |= 1;
		XPutImage(dpy, wkp, gc, ikp, 0, 0, 0, 0, 320, 480);
	    }
	    if(e.xexpose.window == wdp) {
		ready |= 2;
		XPutImage(dpy, wdp, gc, idp, 0, 0, 0, 0, 320, 480);
	    }
	    break;

	  case ButtonPress:
	    if(e.xmotion.window == wkp) {
		kp_press = 1;
		kp_x = e.xbutton.x / 107;
		kp_y = e.xbutton.y / 96;
	    } else if(e.xmotion.window == wdp) {
		dp_press = 1;
		dp_x = e.xbutton.x / 107;
		dp_y = e.xbutton.y / 96;
	    }
	    break;

	  case ButtonRelease:
	    if(e.xmotion.window == wkp) {
		kp_press = 0;
		kp_x = e.xbutton.x / 107;
		kp_y = e.xbutton.y / 96;
	    } else if(e.xmotion.window == wdp) {
		dp_press = 0;
		dp_x = e.xbutton.x / 107;
		dp_y = e.xbutton.y / 96;
	    }
	    break;

	  case MotionNotify:

	    if(e.xmotion.window == wkp) {
		kp_x = e.xmotion.x / 107;
		kp_y = e.xmotion.y / 96;
	    } else if(e.xmotion.window == wdp) {
		dp_x = e.xmotion.x / 107;
		dp_y = e.xmotion.y / 96;
	    }
	    break;
	}
    } while(ready != 3);

}

void start_display() {

    dpy = XOpenDisplay(0);
    int scrn = DefaultScreen(dpy);

    wkp = XCreateSimpleWindow(dpy, RootWindow(dpy, scrn), 0, 0, 320, 480, 3, BlackPixel(dpy, scrn), WhitePixel(dpy, scrn));
    wdp = XCreateSimpleWindow(dpy, RootWindow(dpy, scrn), 400, 0, 320, 480, 3, BlackPixel(dpy, scrn), WhitePixel(dpy, scrn));

    XSelectInput(dpy, wkp, ExposureMask | ButtonPressMask | ButtonReleaseMask | ButtonMotionMask);
    XSelectInput(dpy, wdp, ExposureMask | ButtonPressMask | ButtonReleaseMask | ButtonMotionMask);

    XWindowAttributes xwa;
    XGetWindowAttributes(dpy, wkp, &xwa);

    XMapWindow(dpy, wkp);
    XMapWindow(dpy, wdp);

    ikp = XCreateImage(dpy, xwa.visual, xwa.depth, ZPixmap, 0, malloc(320*480*4), 320, 480, 32, 0);
    idp = XCreateImage(dpy, xwa.visual, xwa.depth, ZPixmap, 0, malloc(320*480*4), 320, 480, 32, 0);

    gc = DefaultGC(dpy, scrn);

}

void end_display()
{
    XCloseDisplay(dpy);

}

static inline unsigned int rgb(unsigned short col)
{
    unsigned int c = col;
    return ( (c << 8) & 0xF80000 )
	 | ( (c << 5) & 0x07FC00 )
	 | ( (c << 3) & 0x0003F8 )
	 | (  c       & 0x000007 );
}

void draw(short dp, short sx, short sy, const unsigned short* palette, const unsigned char* image)
{
    int w = *image++;
    int h = *image++;
    int pitch = (dp? idp->bytes_per_line: ikp->bytes_per_line)/sizeof(unsigned int);
    unsigned int* pixmap = sy*pitch + (unsigned int*)(dp? idp->data: ikp->data);
    int skip = 0;
    int run = 0;
    int half = 0;

    assert(w+sx <= 320);
    assert(h+sy <= 480);

    unsigned int old[128];

    for(int i=0; i<w; i++)
	old[i] = rgb(palette[0]);


    while(h--) {
	unsigned int* row = pixmap + sx;
	pixmap += pitch;
	int x = 0;
	while(x < w) {
	    if(skip) {
		--skip;
	    } else if(run) {
		old[x] = old[x? x-1: w-1];
		--run;
	    } else if(half) {
		old[x] = rgb(palette[*image++ & 7]);
		half = 0;
	    } else switch(*image & 0xC0) {
	      case 0xC0:
		half = 1;
		old[x] = rgb(palette[(*image >> 3) & 7]);
		break;
	      case 0x80:
		run = 3 + (*image++ & 0x3F);
		continue;
	      default:
		skip = 3 + *image++;
		continue;
	    }
	    *row++ = old[x++];
	}
    }
    dp_dirty |= 1<<dp;

}

void fill(short dp, short sx, short sy, short w, short h, const unsigned short* color)
{
    unsigned int c = rgb(*color);
    int pitch = (dp? idp->bytes_per_line: ikp->bytes_per_line)/sizeof(unsigned int);
    unsigned int* pixmap = sy*pitch + (unsigned int*)(dp? idp->data: ikp->data);

    for(int y=0; y<h; y++) {
	unsigned int* row = pixmap + sx;
	pixmap += pitch;
	for(int x=0; x<w; x++)
	    *row++ = c;
    }
    dp_dirty |= 1<<dp;

}



