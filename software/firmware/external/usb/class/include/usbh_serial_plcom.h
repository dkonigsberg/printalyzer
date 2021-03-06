#ifndef __USBH_SERIAL_PLCOM_H
#define __USBH_SERIAL_PLCOM_H

#ifdef __cplusplus
extern "C" {
#endif

/*-
 * Protocol constants and related comments are covered under the following license:
 *
 * SPDX-License-Identifier: BSD-2-Clause-FreeBSD AND BSD-2-Clause-NetBSD
 *
 * Copyright (c) 2001-2003, 2005 Shunsuke Akiyama <akiyama@jp.FreeBSD.org>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <stdbool.h>
#include "usbh_core.h"
#include "usbh_cdc.h"

extern USBH_ClassTypeDef VENDOR_SERIAL_PLCOM_Class;
#define USBH_VENDOR_SERIAL_PLCOM_CLASS &VENDOR_SERIAL_PLCOM_Class

typedef enum {
    USBH_PLCOM_STATE_IDLE = 0U,
    USBH_PLCOM_STATE_SET_LINE_CODING,
    USBH_PLCOM_STATE_GET_LAST_LINE_CODING,
    USBH_PLCOM_STATE_TRANSFER_DATA,
    USBH_PLCOM_STATE_ERROR
} usbh_plcom_state_t;

typedef enum {
    USBH_PLCOM_IDLE_DATA = 0U,
    USBH_PLCOM_SEND_DATA,
    USBH_PLCOM_SEND_DATA_WAIT,
    USBH_PLCOM_RECEIVE_DATA,
    USBH_PLCOM_RECEIVE_DATA_WAIT,
    USBH_PLCOM_NOTIFY_DATA,
    USBH_PLCOM_NOTIFY_DATA_WAIT
} usbh_plcom_data_state_t;

typedef struct {
    uint8_t in_pipe;
    uint8_t in_ep;
    uint16_t in_ep_size;

    uint8_t out_pipe;
    uint8_t out_ep;
    uint16_t out_ep_size;

    uint8_t notif_pipe;
    uint8_t notif_ep;
    uint16_t notif_ep_size;

    uint8_t *in_ep_buffer;
    uint8_t *out_ep_buffer;
    uint8_t *notif_ep_buffer;
} usbh_plcom_endpoints_t;

typedef struct _PLCOM_Process {
    usbh_plcom_state_t state;
    uint16_t line;
    CDC_LineCodingTypeDef linecoding;
    CDC_LineCodingTypeDef *user_linecoding;
    uint8_t lsr;             /* local status register */
    uint8_t msr;             /* plcom status register */
    uint8_t chiptype;        /* type of chip */
    uint8_t ctrl_iface_no;
    uint8_t data_iface_no;
    uint8_t iface_index[2];
    usbh_plcom_endpoints_t endpoints;
    usbh_plcom_data_state_t data_tx_state;
    usbh_plcom_data_state_t data_rx_state;
    usbh_plcom_data_state_t data_notif_state;
    uint8_t *tx_data;
    uint8_t *rx_data;
    uint32_t tx_data_length;
    uint32_t rx_data_length;
    uint32_t timer;
    uint16_t poll;
} PLCOM_HandleTypeDef;

#define PLCOM_MIN_POLL 40U

/**
 * Get whether the provided USB handle is a supported PLCOM device.
 *
 * Since many USB serial devices all appear under the same "vendor" device
 * class, this provides an easy way to determine if a device is appropriate
 * for this implementation.
 */
bool USBH_PLCOM_IsDeviceType(USBH_HandleTypeDef *phost);

USBH_StatusTypeDef USBH_PLCOM_SetDtr(USBH_HandleTypeDef *phost, uint8_t onoff);
USBH_StatusTypeDef USBH_PLCOM_SetRts(USBH_HandleTypeDef *phost, uint8_t onoff);
USBH_StatusTypeDef USBH_PLCOM_SetBreak(USBH_HandleTypeDef *phost, uint8_t onoff);
USBH_StatusTypeDef USBH_PLCOM_SetRtsCts(USBH_HandleTypeDef *phost, uint8_t onoff);

USBH_StatusTypeDef USBH_PLCOM_SetLineCoding(USBH_HandleTypeDef *phost, CDC_LineCodingTypeDef *linecoding);
USBH_StatusTypeDef USBH_PLCOM_GetLineCoding(USBH_HandleTypeDef *phost, CDC_LineCodingTypeDef *linecoding);

USBH_StatusTypeDef USBH_PLCOM_Transmit(USBH_HandleTypeDef *phost, const uint8_t *pbuff, uint32_t length);
USBH_StatusTypeDef USBH_PLCOM_Stop(USBH_HandleTypeDef *phost);

/**
 * Weak function, implement to be notified of transmit complete.
 */
void USBH_PLCOM_TransmitCallback(USBH_HandleTypeDef *phost);

/**
 * Weak function, implement to be notified of new received data.
 */
void USBH_PLCOM_ReceiveCallback(USBH_HandleTypeDef *phost, uint8_t *data, size_t length);

/**
 * Weak function, implement to be notified of line coding changes.
 */
void USBH_PLCOM_LineCodingChanged(USBH_HandleTypeDef *phost);

#ifdef __cplusplus
}
#endif

#endif /* __USBH_SERIAL_PLCOM_H */
