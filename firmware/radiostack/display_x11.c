#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>

static Display* dpy;

static Window	wkp;
static Window	wdp;
static XImage*	ikp;
static XImage*	idp;
static Visual*	visual;
static GC	gc;
static int	cancel_display = 0;

static pthread_t event_thread;

void* run_display(void* arg)
{
    while(!cancel_display) {
	XEvent e;

	XNextEvent(dpy, &e);
	switch(e.type) {
	  case Expose:
	    if(e.xexpose.count)
		break;
	    if(e.xexpose.window == wkp)
		XPutImage(dpy, wkp, gc, ikp, 0, 0, 0, 0, 320, 480);
	    if(e.xexpose.window == wdp)
		XPutImage(dpy, wdp, gc, idp, 0, 0, 0, 0, 320, 480);
	    break;

	  case KeyPress:
	    cancel_display = 1;
	    break;
	}

    }

    XCloseDisplay(dpy);
    return 0;
}

void start_display() {

    dpy = XOpenDisplay(0);
    int scrn = DefaultScreen(dpy);

    wkp = XCreateSimpleWindow(dpy, RootWindow(dpy, scrn), 0, 0, 320, 480, 3, BlackPixel(dpy, scrn), WhitePixel(dpy, scrn));
    wdp = XCreateSimpleWindow(dpy, RootWindow(dpy, scrn), 400, 0, 320, 480, 3, BlackPixel(dpy, scrn), WhitePixel(dpy, scrn));

    XSelectInput(dpy, wkp, ExposureMask | KeyPressMask);
    XSelectInput(dpy, wdp, ExposureMask | KeyPressMask);

    XWindowAttributes xwa;
    XGetWindowAttributes(dpy, wkp, &xwa);

    XMapWindow(dpy, wkp);
    XMapWindow(dpy, wdp);

    ikp = XCreateImage(dpy, xwa.visual, xwa.depth, ZPixmap, 0, malloc(320*480*4), 320, 480, 32, 0);
    idp = XCreateImage(dpy, xwa.visual, xwa.depth, ZPixmap, 0, malloc(320*480*4), 320, 480, 32, 0);

    gc = DefaultGC(dpy, scrn);

    pthread_create(&event_thread, 0, run_display, 0);

}

void end_display() {

    cancel_display = 1;
    pthread_join(event_thread, 0);

}


int main(int argc, char** argv)
{

    start_display();
    sleep(10);
    end_display();

    return 0;
}

