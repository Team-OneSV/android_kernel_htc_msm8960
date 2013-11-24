static char led_pwm1[2] = {0x51, 0xF0};
static char led_pwm2[2] = {0x53, 0x24};
static char dsi_novatek_dim_on[] = {0x53, 0x2C};
static char dsi_novatek_dim_off[] = {0x53, 0x24};

static struct dsi_cmd_desc novatek_dim_on_cmds[] = {
        {DTYPE_DCS_LWRITE, 1, 0, 0, 1, sizeof(dsi_novatek_dim_on), dsi_novatek_dim_on},
};

static struct dsi_cmd_desc novatek_dim_off_cmds[] = {
        {DTYPE_DCS_LWRITE, 1, 0, 0, 1, sizeof(dsi_novatek_dim_off), dsi_novatek_dim_off},
};

static struct dsi_cmd_desc novatek_cmd_backlight_cmds[] = {
        {DTYPE_DCS_LWRITE, 1, 0, 0, 1, sizeof(led_pwm1), led_pwm1},
};

static char k2_f0_1[] = {
    0xF0, 0x55, 0xAA, 0x52,
    0x08, 0x01}; 
static char k2_b0_1[] = {
    0xB0, 0x0F}; 
static char k2_b1_1[] = {
    0xB1, 0x0F}; 
static char k2_b2[] = {
    0xB2, 0x00}; 
static char k2_b3[] = {
    0xB3, 0x07}; 
static char k2_b6_1[] = {
    0xB6, 0x14}; 
static char k2_b7_1[] = {
    0xB7, 0x15}; 
static char k2_b8_1[] = {
    0xB8, 0x24}; 
static char k2_b9[] = {
    0xB9, 0x36}; 
static char k2_ba[] = {
    0xBA, 0x24}; 
static char k2_bf[] = {
    0xBF, 0x01}; 
static char k2_c3[] = {
    0xC3, 0x11}; 
static char k2_c2[] = {
    0xC2, 0x00}; 
static char k2_c0[] = {
    0xC0, 0x00, 0x00}; 
static char k2_bc_1[] = {
    0xBC, 0x00, 0x88, 0x00}; 
static char k2_bd[] = {
    0xBD, 0x00, 0x88, 0x00}; 

static char k2_d1[] = {
    0xD1, 0x00, 0x87, 0x00, 0x8F, 0x00, 0xA2, 0x00, 0xB1, 0x00,
    0xC1, 0x00, 0xDF, 0x00, 0xF5, 0x01, 0x1B, 0x01, 0x3E, 0x01,
    0x75, 0x01, 0xA3, 0x01, 0xEE, 0x02, 0x2A, 0x02, 0x2B, 0x02,
    0x62, 0x02, 0xA0, 0x02, 0xC9, 0x03, 0x01, 0x03, 0x20, 0x03,
    0x46, 0x03, 0x5F, 0x03, 0x7C, 0x03, 0x98, 0x03, 0xAC, 0x03,
    0xD4, 0x03, 0xF9};
static char k2_d2[] = {
    0xD2, 0x00, 0xD8, 0x00, 0xDC, 0x00, 0xEA, 0x00, 0xF4, 0x00,
    0xFF, 0x01, 0x12, 0x01, 0x24, 0x01, 0x44, 0x01, 0x60, 0x01,
    0x90, 0x01, 0xB8, 0x01, 0xFB, 0x02, 0x35, 0x02, 0x35, 0x02,
    0x6B, 0x02, 0xA7, 0x02, 0xD0, 0x03, 0x07, 0x03, 0x27, 0x03,
    0x4F, 0x03, 0x6A, 0x03, 0x8C, 0x03, 0xA7, 0x03, 0xC8, 0x03,
    0xE2, 0x03, 0xF8};
static char k2_d3[] = {
    0xD3, 0x00, 0x2B, 0x00, 0x3C, 0x00, 0x52, 0x00, 0x69, 0x00,
    0x7E, 0x00, 0xA0, 0x00, 0xC1, 0x00, 0xF0, 0x01, 0x19, 0x01,
    0x59, 0x01, 0x8D, 0x01, 0xDF, 0x02, 0x21, 0x02, 0x21, 0x02,
    0x5A, 0x02, 0x9B, 0x02, 0xC5, 0x02, 0xFF, 0x03, 0x1F, 0x03,
    0x49, 0x03, 0x66, 0x03, 0x97, 0x03, 0xBC, 0x03, 0xD1, 0x03,
    0xE1, 0x03, 0xFF};
static char k2_d4[] = {
    0xD4, 0x00, 0x87, 0x00, 0x8F, 0x00, 0xA2, 0x00, 0xB1, 0x00,
    0xC1, 0x00, 0xDF, 0x00, 0xF5, 0x01, 0x1B, 0x01, 0x3E, 0x01,
    0x75, 0x01, 0xA3, 0x01, 0xEE, 0x02, 0x2A, 0x02, 0x2B, 0x02,
    0x62, 0x02, 0xA0, 0x02, 0xC9, 0x03, 0x01, 0x03, 0x20, 0x03,
    0x46, 0x03, 0x5F, 0x03, 0x7C, 0x03, 0x98, 0x03, 0xAC, 0x03,
    0xD4, 0x03, 0xF9};
static char k2_d5[] = {
    0xD5, 0x00, 0xD8, 0x00, 0xDC, 0x00, 0xEA, 0x00, 0xF4, 0x00,
    0xFF, 0x01, 0x12, 0x01, 0x24, 0x01, 0x44, 0x01, 0x60, 0x01,
    0x90, 0x01, 0xB8, 0x01, 0xFB, 0x02, 0x35, 0x02, 0x35, 0x02,
    0x6B, 0x02, 0xA7, 0x02, 0xD0, 0x03, 0x07, 0x03, 0x27, 0x03,
    0x4F, 0x03, 0x6A, 0x03, 0x8C, 0x03, 0xA7, 0x03, 0xC8, 0x03,
    0xE2, 0x03, 0xF8};
static char k2_d6[] = {
    0xD6, 0x00, 0x2B, 0x00, 0x3C, 0x00, 0x52, 0x00, 0x69, 0x00,
    0x7E, 0x00, 0xA0, 0x00, 0xC1, 0x00, 0xF0, 0x01, 0x19, 0x01,
    0x59, 0x01, 0x8D, 0x01, 0xDF, 0x02, 0x21, 0x02, 0x21, 0x02,
    0x5A, 0x02, 0x9B, 0x02, 0xC5, 0x02, 0xFF, 0x03, 0x1F, 0x03,
    0x49, 0x03, 0x66, 0x03, 0x97, 0x03, 0xBC, 0x03, 0xD1, 0x03,
    0xE1, 0x03, 0xFF};

static char k2_f0_2[] = {
    0xF0, 0x55, 0xAA, 0x52,
    0x08, 0x00}; 
static char k2_b6_2[] = {
    0xB6, 0x03}; 
static char k2_b7_2[] = {
    0xB7, 0x70, 0x70}; 
static char k2_b8_2[] = {
    0xB8, 0x00, 0x02, 0x02,
    0x02}; 
static char k2_bc_2[] = {
    0xBC, 0x00}; 
static char k2_b0_2[] = {
    0xB0, 0x00, 0x0A, 0x0E,
    0x09, 0x04}; 
static char k2_b1_2[] = {
    0xB1, 0x60, 0x00, 0x01}; 
static char k2_e0[] = {
    0xE0, 0x01, 0x01};

#ifdef NOVATEK_CABC
static char k2_e3[] = {
    0xE3, 0xFF, 0xF7, 0xEF,
    0xE7, 0xDF, 0xD7, 0xCF,
    0xC7, 0xBF, 0xB7}; 
static char k2_5e[] = {
    0x5E, 0x06}; 
static char led_cabc_pwm_on[] = {
    0x55, 0x02}; 
#ifdef CONFIG_MSM_ACL_ENABLE
static char led_cabc_pwm_off[] = {
    0x55, 0x00}; 
#endif
static char k2_f5 [] = {
    0xF5, 0x44, 0x44, 0x44,
    0x44, 0x44, 0x00, 0xD9,
    0x17}; 
#ifdef CONFIG_MSM_CABC_VIDEO_ENHANCE
static char k2_e3_video[] = {
    0xE3, 0xFF, 0xF1, 0xE0,
    0xCE, 0xBE, 0xAD, 0x9C,
    0x8A, 0x78, 0x66}; 
static char k2_f5_video[] = {
    0xF5, 0x66, 0x66, 0x66,
    0x66, 0x66, 0x00, 0xD9,
    0x17}; 
#endif
#endif

static char k2_ff_1[] = {
    0xFF, 0xAA, 0x55, 0xA5,
    0x80}; 
static char k2_f7[] = {
    0xF7, 0x63, 0x40, 0x00,
    0x00, 0x00, 0x01, 0xC4,
    0xA2, 0x00, 0x02, 0x64,
    0x54, 0x48, 0x00, 0xD0}; 
static char k2_f8[] = {
    0xF8, 0x00, 0x00, 0x33,
    0x0F, 0x0F, 0x20, 0x00,
    0x01, 0x00, 0x00, 0x20,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00}; 

static char k2_b4[] = {
    0xB4, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 
static char k2_d6_1[] = {
    0xD6, 0x00, 0x05, 0x10, 0x17, 0x22, 0x26, 0x29, 0x29, 0x26, 0x23, 0x17, 0x12, 0x06, 0x02, 0x01, 0x00}; 
static char k2_d7[] = {
    0xD7, 0x30, 0x30, 0x30, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; 
static char k2_d8[] = {
    0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x30, 0x00}; 

static char k2_f0_3[] = {
    0xF0, 0x55, 0xAA, 0x52,
    0x00, 0x00}; 
static char k2_ff_2[] = {
    0xFF, 0xAA, 0x55, 0xA5,
    0x00}; 

static char k2_peripheral_on[] = {0x00, 0x00}; 
static char k2_peripheral_off[] = {0x00, 0x00}; 

static struct dsi_cmd_desc k2_auo_display_on_cmds[] = {
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_f0_1), k2_f0_1},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_b0_1), k2_b0_1},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_b1_1), k2_b1_1},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_b2), k2_b2},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_b3), k2_b3},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_b6_1), k2_b6_1},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_b7_1), k2_b7_1},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_b8_1), k2_b8_1},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_b9), k2_b9},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_ba), k2_ba},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_bf), k2_bf},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_c3), k2_c3},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_c2), k2_c2},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_c0), k2_c0},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_bc_1), k2_bc_1},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_bd), k2_bd},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_d1), k2_d1},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_d2), k2_d2},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_d3), k2_d3},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_d4), k2_d4},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_d5), k2_d5},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_d6), k2_d6},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_f0_2), k2_f0_2},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_b6_2), k2_b6_2},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_b7_2), k2_b7_2},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_b8_2), k2_b8_2},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_bc_2), k2_bc_2},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_b0_2), k2_b0_2},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_b1_2), k2_b1_2},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_e0), k2_e0},
#ifdef NOVATEK_CABC
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_e3), k2_e3},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_5e), k2_5e},
#ifdef CONFIG_MSM_ACL_ENABLE
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(led_cabc_pwm_off), led_cabc_pwm_off},
#else
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(led_cabc_pwm_on), led_cabc_pwm_on},
#endif
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_ff_1), k2_ff_1},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_f5), k2_f5},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_ff_2), k2_ff_2},
#endif
        
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_ff_1), k2_ff_1},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_f7), k2_f7},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_f8), k2_f8},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_b4), k2_b4},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_d6_1), k2_d6_1},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_d7), k2_d7},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_d8), k2_d8},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_f0_3), k2_f0_3},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_ff_2), k2_ff_2},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(led_pwm2), led_pwm2},
        {DTYPE_PERIPHERAL_ON, 1, 0, 1, 120, sizeof(k2_peripheral_on), k2_peripheral_on},
};

static struct dsi_cmd_desc k2_auo_display_on_cmds_c2[] = {
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_f0_1), k2_f0_1},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_b0_1), k2_b0_1},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_b1_1), k2_b1_1},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_b2), k2_b2},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_b3), k2_b3},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_b6_1), k2_b6_1},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_b7_1), k2_b7_1},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_b8_1), k2_b8_1},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_b9), k2_b9},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_ba), k2_ba},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_bf), k2_bf},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_c3), k2_c3},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_c2), k2_c2},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_c0), k2_c0},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_bc_1), k2_bc_1},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_bd), k2_bd},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_d1), k2_d1},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_d2), k2_d2},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_d3), k2_d3},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_d4), k2_d4},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_d5), k2_d5},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_d6), k2_d6},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_f0_2), k2_f0_2},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_b6_2), k2_b6_2},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_b7_2), k2_b7_2},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_b8_2), k2_b8_2},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_bc_2), k2_bc_2},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_b0_2), k2_b0_2},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_b1_2), k2_b1_2},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_e0), k2_e0},
#ifdef NOVATEK_CABC
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_e3), k2_e3},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_5e), k2_5e},
#ifdef CONFIG_MSM_ACL_ENABLE
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(led_cabc_pwm_off), led_cabc_pwm_off},
#else
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(led_cabc_pwm_on), led_cabc_pwm_on},
#endif
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_ff_1), k2_ff_1},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_f5), k2_f5},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_ff_2), k2_ff_2},
#endif
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_b4), k2_b4},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_d6_1), k2_d6_1},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_d7), k2_d7},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_d8), k2_d8},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_f0_3), k2_f0_3},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_ff_2), k2_ff_2},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(led_pwm2), led_pwm2},
        {DTYPE_PERIPHERAL_ON, 1, 0, 1, 120, sizeof(k2_peripheral_on), k2_peripheral_on},
};

static char k2_jdi_f0[] = {
    0xF0, 0x55, 0xAA, 0x52,
    0x08, 0x00}; 
static char k2_jdi_b1[] = {
    0xB1, 0x68, 0x00, 0x01}; 
static char k2_jdi_b4[] = {
    0xB4, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 
static char k2_jdi_d6_2[] = {
    0xD6, 0x00, 0x05, 0x10, 0x17, 0x22, 0x26, 0x29, 0x29, 0x26, 0x23, 0x17, 0x12, 0x06, 0x02, 0x01, 0x00}; 
static char k2_jdi_d7[] = {
    0xD7, 0x30, 0x30, 0x30, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 
static char k2_jdi_d8[] = {
    0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x30, 0x00}; 
static char k2_jdi_b6[] = {
    0xB6, 0x07}; 
static char k2_jdi_b7[] = {
    0xB7, 0x33, 0x03}; 
static char k2_jdi_b8[] = {
    0xB8, 0x00, 0x00, 0x02, 0x00}; 
static char k2_jdi_ba[] = {
    0xBA, 0x01}; 
static char k2_jdi_bb[] = {
    0xBB, 0x44, 0x40}; 
static char k2_jdi_c1[] = {
    0xC1, 0x01 }; 
static char k2_jdi_c2[] = {
    0xC2, 0x00, 0x00, 0x55,
    0x55, 0x55, 0x00, 0x55,
    0x55};
static char k2_jdi_c7[] = {
    0xC7, 0x00 }; 
static char k2_jdi_ca[] = {
    0xCA, 0x05, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x01, 0x00};
static char k2_jdi_e0[] = {
    0xE0, 0x01, 0x01};
static char k2_jdi_e1[] = {
    0xE1, 0x00, 0xFF};
static char k2_jdi_f0_1[] = {
    0xF0, 0x55, 0xAA, 0x52,
    0x08, 0x01}; 
static char k2_jdi_b0[] = {
    0xB0, 0x0A }; 
static char k2_jdi_b1_1[] = {
    0xB1, 0x0A }; 
static char k2_jdi_b2_1[] = {
    0xB2, 0x00 }; 
static char k2_jdi_b3[] = {
    0xB3, 0x08 }; 
static char k2_jdi_b4_1[] = {
    0xB4, 0x28 }; 
static char k2_jdi_b5[] = {
    0xB5, 0x05 }; 
static char k2_jdi_b6_1[] = {
    0xB6, 0x35};
static char k2_jdi_b7_1[] = {
    0xB7, 0x35 }; 
static char k2_jdi_b8_1[] = {
    0xB8, 0x25 }; 
static char k2_jdi_b9[] = {
    0xB9, 0x37 }; 
static char k2_jdi_ba_1[] = {
    0xBA, 0x15 }; 
static char k2_jdi_cc[] = {
    0xCC, 0x64 }; 
static char k2_jdi_d1[] = {
    0xD1, 0x00, 0xC7, 0x00, 0xCF, 0x00, 0xE2, 0x00,
    0xE9, 0x00, 0xF8, 0x01, 0x0F, 0x01, 0x23, 0x01,
    0x45, 0x01, 0x62, 0x01, 0x93, 0x01, 0xBB, 0x01,
    0xFB, 0x02, 0x2D, 0x02, 0x2E, 0x02, 0x62, 0x02,
    0x98, 0x02, 0xBA, 0x02, 0xEB, 0x03, 0x0D, 0x03,
    0x38, 0x03, 0x53, 0x03, 0x7A, 0x03, 0x97, 0x03,
    0xA6, 0x03, 0xCA, 0x03, 0xD0};
static char k2_jdi_d2[] = {
    0xD2, 0x00, 0x98, 0x00, 0xA1, 0x00, 0xBA, 0x00,
    0xC8, 0x00, 0xD7, 0x00, 0xF3, 0x01, 0x0B, 0x01,
    0x32, 0x01, 0x52, 0x01, 0x87, 0x01, 0xB2, 0x01,
    0xF4, 0x02, 0x29, 0x02, 0x2A, 0x02, 0x5F, 0x02,
    0x96, 0x02, 0xB8, 0x02, 0xE9, 0x03, 0x0B, 0x03,
    0x37, 0x03, 0x53, 0x03, 0x7A, 0x03, 0x96, 0x03,
    0xAA, 0x03, 0xCA, 0x03, 0xD0};
static char k2_jdi_d3[] = {
    0xD3, 0x00, 0x3F, 0x00, 0x4C, 0x00, 0x71, 0x00,
    0x7E, 0x00, 0x94, 0x00, 0xBB, 0x00, 0xD8, 0x01,
    0x08, 0x01, 0x2D, 0x01, 0x6A, 0x01, 0x9B, 0x01,
    0xE6, 0x02, 0x1F, 0x02, 0x20, 0x02, 0x57, 0x02,
    0x91, 0x02, 0xB4, 0x02, 0xE7, 0x03, 0x09, 0x03,
    0x37, 0x03, 0x54, 0x03, 0x7B, 0x03, 0x93, 0x03,
    0xB3, 0x03, 0xCA, 0x03, 0xD0};
static char k2_jdi_d4[] = {
    0xD4, 0x00, 0xC7, 0x00, 0xCF, 0x00, 0xE2, 0x00,
    0xE9, 0x00, 0xF8, 0x01, 0x0F, 0x01, 0x23, 0x01,
    0x45, 0x01, 0x62, 0x01, 0x93, 0x01, 0xBB, 0x01,
    0xFB, 0x02, 0x2D, 0x02, 0x2E, 0x02, 0x62, 0x02,
    0x98, 0x02, 0xBA, 0x02, 0xEB, 0x03, 0x0D, 0x03,
    0x38, 0x03, 0x53, 0x03, 0x7A, 0x03, 0x97, 0x03,
    0xA6, 0x03, 0xCA, 0x03, 0xD0};
static char k2_jdi_d5[] = {
    0xD5, 0x00, 0x98, 0x00, 0xA1, 0x00, 0xBA, 0x00,
    0xC8, 0x00, 0xD7, 0x00, 0xF3, 0x01, 0x0B, 0x01,
    0x32, 0x01, 0x52, 0x01, 0x87, 0x01, 0xB2, 0x01,
    0xF4, 0x02, 0x29, 0x02, 0x2A, 0x02, 0x5F, 0x02,
    0x96, 0x02, 0xB8, 0x02, 0xE9, 0x03, 0x0B, 0x03,
    0x37, 0x03, 0x53, 0x03, 0x7A, 0x03, 0x96, 0x03,
    0xAA, 0x03, 0xCA, 0x03, 0xD0};
static char k2_jdi_d6_1[] = {
    0xD6, 0x00, 0x3F, 0x00, 0x4C, 0x00, 0x71, 0x00,
    0x7E, 0x00, 0x94, 0x00, 0xBB, 0x00, 0xD8, 0x01,
    0x08, 0x01, 0x2D, 0x01, 0x6A, 0x01, 0x9B, 0x01,
    0xE6, 0x02, 0x1F, 0x02, 0x20, 0x02, 0x57, 0x02,
    0x91, 0x02, 0xB4, 0x02, 0xE7, 0x03, 0x09, 0x03,
    0x37, 0x03, 0x54, 0x03, 0x7B, 0x03, 0x93, 0x03,
    0xB3, 0x03, 0xCA, 0x03, 0xD0};

static char k2_jdi_f0_2[] = {
    0xF0, 0x55, 0xAA, 0x52,
    0x00, 0x00}; 
static char k2_jdi_ff_2[] = {
    0xFF, 0xAA, 0x55, 0xA5,
    0x00}; 

static char k2_jdi_pwm2[] = {0x53, 0x24}; 

static char k2_jdi_peripheral_on[] = {0x00, 0x00}; 
static char k2_jdi_peripheral_off[] = {0x00, 0x00};


static struct dsi_cmd_desc  k2_jdi_display_on_cmds[] = {
    {DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(k2_jdi_f0), k2_jdi_f0},
    {DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(k2_jdi_b1), k2_jdi_b1},
    {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_jdi_b4), k2_jdi_b4},
    {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_jdi_d6_2), k2_jdi_d6_2},
    {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_jdi_d7), k2_jdi_d7},
    {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_jdi_d8), k2_jdi_d8},
    {DTYPE_GEN_WRITE2, 1, 0, 0, 0, sizeof(k2_jdi_b6), k2_jdi_b6},
    {DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(k2_jdi_b7), k2_jdi_b7},
    {DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(k2_jdi_b8), k2_jdi_b8},
    {DTYPE_GEN_WRITE2, 1, 0, 0, 0, sizeof(k2_jdi_ba), k2_jdi_ba},
    {DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(k2_jdi_bb), k2_jdi_bb},
    {DTYPE_GEN_WRITE2, 1, 0, 0, 0, sizeof(k2_jdi_c1), k2_jdi_c1},
    {DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(k2_jdi_c2), k2_jdi_c2},
    {DTYPE_GEN_WRITE2, 1, 0, 0, 0, sizeof(k2_jdi_c7), k2_jdi_c7},
    {DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(k2_jdi_ca), k2_jdi_ca},
    {DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(k2_jdi_e0), k2_jdi_e0},
    {DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(k2_jdi_e1), k2_jdi_e1},
#ifdef NOVATEK_CABC
    {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_e3), k2_e3},
    {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(k2_5e), k2_5e},
#ifdef CONFIG_MSM_ACL_ENABLE
    {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(led_cabc_pwm_off), led_cabc_pwm_off},
#else
    {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(led_cabc_pwm_on), led_cabc_pwm_on},
#endif
    {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_ff_1), k2_ff_1},
    {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_f5), k2_f5},
    {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_ff_2), k2_ff_2},
#endif
    {DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(k2_jdi_f0_1), k2_jdi_f0_1},
    {DTYPE_GEN_WRITE2, 1, 0, 0, 0, sizeof(k2_jdi_b0), k2_jdi_b0},
    {DTYPE_GEN_WRITE2, 1, 0, 0, 0, sizeof(k2_jdi_b1_1), k2_jdi_b1_1},
    {DTYPE_GEN_WRITE2, 1, 0, 0, 0, sizeof(k2_jdi_b2_1), k2_jdi_b2_1},
    {DTYPE_GEN_WRITE2, 1, 0, 0, 0, sizeof(k2_jdi_b3), k2_jdi_b3},
    {DTYPE_GEN_WRITE2, 1, 0, 0, 0, sizeof(k2_jdi_b4_1), k2_jdi_b4_1},
    {DTYPE_GEN_WRITE2, 1, 0, 0, 0, sizeof(k2_jdi_b5), k2_jdi_b5},
    {DTYPE_GEN_WRITE2, 1, 0, 0, 0, sizeof(k2_jdi_b6_1), k2_jdi_b6_1},
    {DTYPE_GEN_WRITE2, 1, 0, 0, 0, sizeof(k2_jdi_b7_1), k2_jdi_b7_1},
    {DTYPE_GEN_WRITE2, 1, 0, 0, 0, sizeof(k2_jdi_b8_1), k2_jdi_b8_1},
    {DTYPE_GEN_WRITE2, 1, 0, 0, 0, sizeof(k2_jdi_b9), k2_jdi_b9},
    {DTYPE_GEN_WRITE2, 1, 0, 0, 0, sizeof(k2_jdi_ba_1), k2_jdi_ba_1},
    {DTYPE_GEN_WRITE2, 1, 0, 0, 0, sizeof(k2_jdi_cc), k2_jdi_cc},
    {DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(k2_jdi_d1), k2_jdi_d1},
    {DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(k2_jdi_d2), k2_jdi_d2},
    {DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(k2_jdi_d3), k2_jdi_d3},
    {DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(k2_jdi_d4), k2_jdi_d4},
    {DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(k2_jdi_d5), k2_jdi_d5},
    {DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(k2_jdi_d6_1), k2_jdi_d6_1},
    {DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(k2_jdi_f0_2), k2_jdi_f0_2},
    {DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(k2_jdi_ff_2), k2_jdi_ff_2},
    {DTYPE_GEN_WRITE2, 1, 0, 0, 0, sizeof(k2_jdi_pwm2), k2_jdi_pwm2},
    {DTYPE_PERIPHERAL_ON, 1, 0, 1, 120, sizeof(k2_jdi_peripheral_on), k2_jdi_peripheral_on},
};

static struct dsi_cmd_desc k2_jdi_display_off_cmds[] = {
        {DTYPE_PERIPHERAL_OFF, 1, 0, 1, 70, sizeof(k2_jdi_peripheral_off), k2_jdi_peripheral_off},
};

static struct dsi_cmd_desc k2_auo_display_off_cmds[] = {
        {DTYPE_PERIPHERAL_OFF, 1, 0, 1, 70, sizeof(k2_peripheral_off), k2_peripheral_off},
};

#ifdef CONFIG_MSM_ACL_ENABLE
static struct dsi_cmd_desc novatek_cabc_on_cmds[] = {
        {DTYPE_DCS_LWRITE, 1, 0, 0, 1, sizeof(led_cabc_pwm_on), led_cabc_pwm_on},
};

static struct dsi_cmd_desc novatek_cabc_off_cmds[] = {
        {DTYPE_DCS_LWRITE, 1, 0, 0, 1, sizeof(led_cabc_pwm_off), led_cabc_pwm_off},
};
#endif

#ifdef CONFIG_MSM_CABC_VIDEO_ENHANCE
static struct dsi_cmd_desc novatek_cabc_UI_cmds[] = {
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_e3), k2_e3},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_ff_1), k2_ff_1},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_f5), k2_f5},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_ff_2), k2_ff_2},
};
static struct dsi_cmd_desc novatek_cabc_video_cmds[] = {
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_e3_video), k2_e3_video},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_ff_1), k2_ff_1},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_f5_video), k2_f5_video},
        {DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_ff_2), k2_ff_2},
};
#endif
