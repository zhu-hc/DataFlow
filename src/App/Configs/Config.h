#ifndef __CONFIG_H
#define __CONFIG_H

/*=========================
   Hardware Configuration
 *=========================*/

/** PRIORITIES */
#define TASK_WIFI_PRIORITIES        (configMAX_PRIORITIES - 4)
#define TASK_LVGL_PRIORITIES        (configMAX_PRIORITIES - 3)
#define TASK_RGB_PRIORITIES         (configMAX_PRIORITIES - 2)

/* Screen */
#define CONFIG_SCREEN_CS_PIN        6
#define CONFIG_SCREEN_DC_PIN        4
#define CONFIG_SCREEN_RST_PIN       7
#define CONFIG_SCREEN_SCK_PIN       5
#define CONFIG_SCREEN_MOSI_PIN      15
#define CONFIG_SCREEN_MISO_PIN      -1
#define CONFIG_SCREEN_BLK_PIN       16

/* Screen */
#define CONFIG_SCREEN_HOR_RES       320
#define CONFIG_SCREEN_VER_RES       240
#define CONFIG_SCREEN_BUFFER_SIZE   (CONFIG_SCREEN_HOR_RES * CONFIG_SCREEN_VER_RES / 1)

/* Rgb */
#define CONFIG_RGB_NUM              2
#define CONFIG_RGB_S0               20
#define CONFIG_RGB_S1               19
#define CONFIG_RGB_LEDS             11
#define CONFIG_RGB_FADE             60

/* Led */
#define CONFIG_LED_SHCP             21
#define CONFIG_LED_STCP             14
#define CONFIG_LED_DS               13
#define CONFIG_LED_REC              3

/* Battery */
#define CONFIG_BAT_DET_PIN          1
#define CONFIG_BAT_CHG_DET_PIN      40

/* Power */
#define CONFIG_POWER_CHK            45
#define CONFIG_POWER_HOLD           35
#define CONFIG_USB_CHK              39

/* SD CARD */
#define CONFIG_SD_CD_PIN            12
#define CONFIG_SD_CMD_PIN           11
#define CONFIG_SD_DATA0_PIN         9
#define CONFIG_SD_SCK_PIN           10

/* Encoder */
#define CONFIG_ENCODER_LEFT_B_PIN        36
#define CONFIG_ENCODER_LEFT_PUSH_PIN     37
#define CONFIG_ENCODER_LEFT_A_PIN        38

#define CONFIG_ENCODER_RIGHT_B_PIN       17
#define CONFIG_ENCODER_RIGHT_PUSH_PIN    18
#define CONFIG_ENCODER_RIGHT_A_PIN       8

/* KEY */
#define CONFIG_KEY_LEFT_PIN              48
#define CONFIG_KEY_RIGHT_PIN             47

/* UART */
#define CONFIG_UART_TIMEOUT              200
#define CONFIG_UART_RX_PIN               42
#define CONFIG_UART_TX_PIN               41

/* FFS */

#endif
