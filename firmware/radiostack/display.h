
extern void start_display();
extern void end_display();
extern void wait_display();

extern void draw(short dp, short x, short y, const unsigned short* palette, const unsigned char* image);
extern void fill(short dp, short x, short y, short w, short h, const unsigned short* color);

extern unsigned char kp_press, kp_x, kp_y;
extern unsigned char dp_press, dp_x, dp_y;

