
extern void start_display();
extern void end_display();

extern void dp_draw(short x, short y, const short* palette, const unsigned char* image);
extern void dp_write(short x, short y, const short* palette, const unsigned char* font, const char* text);
extern void dp_fill(short x, short y, short w, short h, const short color);

/* callback */
extern void dp_touch(unsigned char dpy, unsigned char touch, unsigned char x, unsigned char y);

