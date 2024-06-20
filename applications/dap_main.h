#ifndef DAP_MAIN_H
#define DAP_MAIN_H

#include "usbd_core.h"
#include "usbd_cdc.h"
#include "usbd_msc.h"
#include "chry_ringbuffer.h"

#define LCKFB_DAPLINK_VERSION_MAJOR '1'
#define LCKFB_DAPLINK_VERSION_MINOR '0'
#define LCKFB_DAPLINK_VERSION_PATCH '0'

extern chry_ringbuffer_t g_uartrx;
extern chry_ringbuffer_t g_uartrx_for_lvgl;
extern chry_ringbuffer_t g_usbrx;

int chry_dap_init(void);
void chry_dap_handle(void);
void chry_dap_usb2uart_handle(void);

void chry_dap_usb2uart_uart_config_callback(struct cdc_line_coding *line_coding);
void chry_dap_usb2uart_uart_send_bydma(uint8_t *data, uint16_t len);
void chry_dap_usb2uart_uart_send_complete(uint32_t size);

uint32_t get_cdc_g_line_coding_dwDTERate(void);
uint8_t get_cdc_g_line_coding_bCharFormat(void);
uint8_t get_cdc_g_line_coding_bParityType(void);
uint8_t get_cdc_g_line_coding_bDataBits(void);

#endif
