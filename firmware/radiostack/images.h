
extern const unsigned char* images_buttons[][2];
extern const unsigned char* images_bits[];


enum image_button_enum {
      BUTTON_keypad_1, BUTTON_keypad_2, BUTTON_keypad_3,
      BUTTON_keypad_4, BUTTON_keypad_5, BUTTON_keypad_6,
      BUTTON_keypad_7, BUTTON_keypad_8, BUTTON_keypad_9,
      BUTTON_keypad_decimal, BUTTON_keypad_0, BUTTON_keypad_backspace,
      BUTTON_keypad_cancel, BUTTON_keypad_xfer, BUTTON_keypad_enter,
      BUTTON_keypad_x, BUTTON_keypad_y,
      BUTTON_menu_com, BUTTON_menu_xpndr, BUTTON_menu_nav, BUTTON_menu_adf, BUTTON_menu_tacan,
      BUTTON_xfer,
      BUTTON_com1, BUTTON_mic, BUTTON_com2, BUTTON_nav1, BUTTON_nav2, BUTTON_adf,
      BUTTOM_on, BUTTON_alt, BUTTON_ident,
      BUTTON_led_single, BUTTON_led_double,

      NO_BUTTON,
};

enum image_bit_enum {
    BIT_digit_0=0, BIT_digit_decimal=10,
    BIT_unit_mhz, BIT_unit_khz,
    BIT_bra_com1, BIT_bra_com2, BIT_bra_nav1, BIT_bra_nav2, BIT_bra_adf, BIT_bra_xpndr, BIT_bra_tacan, BIT_bra_mid, BIT_bra_end,
    BIT_ket_start, BIT_ket_mid, BIT_ket_end,
};

#if defined(ARCH_HAS_MULTI_ADDRESS_SPACE)
  #define IMAGE_BIT(which) pgm_read_ptr(images_bits[BIT_##which])
  #define IMAGE_BUTTON(which,press) pgm_read_ptr(images_buttons[BUTTON_##which][press])
#else
  #define PROGMEM
  #define IMAGE_BIT(which) (images_bits[BIT_##which])
  #define IMAGE_BUTTON(which,press) (images_buttons[BUTTON_##which][press])
#endif

