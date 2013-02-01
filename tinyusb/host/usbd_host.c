/*
 * usbd_host.c
 *
 *  Created on: Jan 19, 2013
 *      Author: hathach
 */

/*
 * Software License Agreement (BSD License)
 * Copyright (c) 2013, hathach (tinyusb.net)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the tiny usb stack.
 */

#include "tusb_option.h"

#ifdef TUSB_CFG_HOST

#define _TINY_USB_SOURCE_FILE_

//--------------------------------------------------------------------+
// INCLUDE
//--------------------------------------------------------------------+
#include "common/common.h"
#include "usbd_host.h"
#include "osal/osal.h"

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF
//--------------------------------------------------------------------+


//--------------------------------------------------------------------+
// INTERNAL OBJECT & FUNCTION DECLARATION
//--------------------------------------------------------------------+
STATIC_ usbh_device_info_t device_info_pool[TUSB_CFG_HOST_DEVICE_MAX];

//--------------------------------------------------------------------+
// PUBLIC API (Parameter Verification is required)
//--------------------------------------------------------------------+
tusbh_device_status_t tusbh_device_status_get (tusb_handle_device_t const device_hdl)
{
  ASSERT(device_hdl < TUSB_CFG_HOST_DEVICE_MAX, 0);
  return device_info_pool[device_hdl].status;
}

//--------------------------------------------------------------------+
// ENUMERATION TASK & ITS DATA
//--------------------------------------------------------------------+
OSAL_TASK_DEF(enumeration_task, usbh_enumerate_task, 128, OSAL_PRIO_HIGH);

#define ENUM_QUEUE_DEPTH  5
OSAL_DEF_QUEUE(enumeration_queue, ENUM_QUEUE_DEPTH, uin32_t);
osal_queue_handle_t enumeration_queue_hdl;

void usbh_enumerate_task(void)
{
  OSAL_TASK_LOOP
  {
    OSAL_TASK_LOOP_BEGIN



    OSAL_TASK_LOOP_END
  }
}

//--------------------------------------------------------------------+
// CLASS-USBD API (don't require to verify parameters)
//--------------------------------------------------------------------+
tusb_error_t usbh_init(void)
{
  uint32_t i;

  memset(device_info_pool, 0, sizeof(usbh_device_info_t)*TUSB_CFG_HOST_DEVICE_MAX);

  for(i=0; i<TUSB_CFG_HOST_CONTROLLER_NUM; i++)
  {
    ASSERT_STATUS( hcd_init(i) );
  }

  ASSERT_STATUS( osal_task_create(&enumeration_task) );
  enumeration_queue_hdl = osal_queue_create(&enumeration_queue);
  ASSERT_PTR(enumeration_queue_hdl, TUSB_ERROR_OSAL_QUEUE_FAILED);

  return TUSB_ERROR_NONE;
}
#endif
