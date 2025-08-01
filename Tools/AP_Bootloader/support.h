#pragma once

#include <AP_HAL_ChibiOS/AP_HAL_ChibiOS.h>

#define LED_ACTIVITY	1
#define LED_BOOTLOADER	2

#ifndef AP_FLASH_ECC_CHECK_ENABLED
#define AP_FLASH_ECC_CHECK_ENABLED defined(STM32H7) && CH_CFG_USE_HEAP
#endif

/* board info forwarded from board-specific code to booloader */
struct boardinfo {
    uint32_t	board_type;
    uint32_t	board_rev;
    uint32_t	fw_size;
    uint32_t    extf_size;
} __attribute__((packed));

extern struct boardinfo board_info;

void init_uarts(void);
int16_t cin(unsigned timeout_ms);
int cin_word(uint32_t *wp, unsigned timeout_ms);
void cout(const uint8_t *data, uint32_t len);
void port_setbaud(uint32_t baudrate);
#if defined(BOOTLOADER_FORWARD_OTG2_SERIAL)
bool update_otg2_serial_forward(void);
#endif
void flash_init();

uint32_t flash_func_read_word(uint32_t offset);
bool flash_func_write_word(uint32_t offset, uint32_t v);
bool flash_func_write_words(uint32_t offset, uint32_t *v, uint8_t n);
uint32_t flash_func_sector_size(uint32_t sector);
bool flash_func_is_erased(uint32_t sector);
bool flash_func_erase_sector(uint32_t sector, bool force_erase = false);
uint32_t flash_func_read_otp(uint32_t idx);
uint32_t flash_func_read_sn(uint32_t idx);
void flash_set_keep_unlocked(bool);
void lock_bl_port(void);

bool flash_write_flush(void);
bool flash_write_buffer(uint32_t address, const uint32_t *v, uint8_t nwords);

uint32_t get_mcu_id(void);
uint32_t get_mcu_desc(uint32_t len, uint8_t *buf);

uint32_t board_get_rtc_signature(void);
void board_set_rtc_signature(uint32_t sig);

void led_on(unsigned led);
void led_off(unsigned led);
void led_toggle(unsigned led);

void thread_sleep_ms(uint32_t ms);
void thread_sleep_us(uint32_t us);

void custom_startup(void);

#if AP_FLASH_ECC_CHECK_ENABLED
void check_ecc_errors(void);
#endif

// printf to debug uart (or USB)
extern "C" {
void uprintf(const char *fmt, ...) FMT_PRINTF(1,2);
}

// generate a LED sequence forever
void led_pulses(uint8_t npulses);

typedef struct mcu_des_t {
    uint16_t mcuid;
    const char *desc;
} mcu_des_t;

typedef struct mcu_rev_t {
    uint16_t revid;
    char  rev;
} mcu_rev_t;
