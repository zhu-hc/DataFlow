/**
 * @file lv_port_indev_templ.c
 *
 */

/*Copy this file as "lv_port_indev.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lvgl.h"
#include "HAL/HAL.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void encoder_init(void);
static void main_encoder_read(lv_indev_drv_t* indev_drv, lv_indev_data_t* data);
static void minor_encoder_read(lv_indev_drv_t* indev_drv, lv_indev_data_t* data);

/**********************
 *  STATIC VARIABLES
 **********************/

static lv_indev_t* main_encoder_indev;
static lv_indev_t* minor_encoder_indev;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
static lv_indev_drv_t indev_drv_main_encoder;
static lv_indev_drv_t indev_drv_minor_encoder;

void lv_port_indev_init(void)
{

    /*------------------
     * Encoder
     * -----------------*/

    /*Initialize your encoder if you have*/
    encoder_init();

    /*Register a encoder input device*/
    lv_indev_drv_init(&indev_drv_main_encoder);
    indev_drv_main_encoder.type = LV_INDEV_TYPE_ENCODER;
    indev_drv_main_encoder.read_cb = main_encoder_read;
    indev_drv_main_encoder.user_data = (void *)"Main";
    main_encoder_indev = lv_indev_drv_register(&indev_drv_main_encoder);

    lv_indev_drv_init(&indev_drv_minor_encoder);
    indev_drv_minor_encoder.type = LV_INDEV_TYPE_ENCODER;
    indev_drv_minor_encoder.read_cb = minor_encoder_read;
    indev_drv_minor_encoder.user_data = (void *)"Minor";
    minor_encoder_indev = lv_indev_drv_register(&indev_drv_minor_encoder);

    /* Later you should create group(s) with `lv_group_t * group = lv_group_create()`,
     * add objects to the group with `lv_group_add_obj(group, obj)`
     * and assign this input device to group to navigate in it:
     * `lv_indev_set_group(indev_encoder, group);` */
}


/**********************
 *   STATIC FUNCTIONS
 **********************/

/*------------------
 * Encoder
 * -----------------*/

/* Initialize your keypad */
static void encoder_init(void)
{
    /*Do it in Init*/
}


/* Will be called by the library to read the encoder */
static void main_encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    data->enc_diff = HAL::Encoder_GetRightDiff();
    data->state =  HAL::Encoder_GetRightIsPush() ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
}

static void minor_encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    data->enc_diff = HAL::Encoder_GetLeftDiff();
    data->state =  HAL::Encoder_GetLeftIsPush() ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
}

#else /* Enable this file at the top */

/* This dummy typedef exists purely to silence -Wpedantic. */
typedef int keep_pedantic_happy;
#endif
