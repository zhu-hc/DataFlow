// Setup for the TTGO T Display
#define USER_SETUP_ID 25

// See SetupX_Template.h for all options available

#define ST7789_DRIVER
#define TFT_SDA_READ   // Display has a bidirectional SDA pin

#define TFT_WIDTH  240
#define TFT_HEIGHT 320

#define CGRAM_OFFSET      // Library will add offsets required

//#define TFT_MISO -1

#define TFT_MOSI            15
#define TFT_SCLK            5
#define TFT_CS              6
#define TFT_DC              4
#define TFT_RST             7

//#define TFT_BL          4  // Display backlight control pin

#define TFT_BACKLIGHT_ON HIGH  // HIGH or LOW are options

#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF

#define SMOOTH_FONT

//#define SPI_FREQUENCY  27000000
  #define SPI_FREQUENCY  40000000


#define SPI_READ_FREQUENCY  6000000 // 6 MHz is the maximum SPI read speed for the ST7789V
