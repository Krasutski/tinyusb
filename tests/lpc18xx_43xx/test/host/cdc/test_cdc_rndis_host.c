/**************************************************************************/
/*!
    @file     test_cdc_rndis_host.c
    @author   hathach (tinyusb.org)

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2013, hathach (tinyusb.org)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    This file is part of the tinyusb stack.
*/
/**************************************************************************/

#include "stdlib.h"
#include "unity.h"
#include "tusb_option.h"
#include "errors.h"
#include "binary.h"
#include "type_helper.h"

#include "mock_osal.h"
#include "mock_hcd.h"
#include "mock_usbh.h"
#include "mock_cdc_callback.h"

#include "descriptor_cdc.h"
#include "cdc_host.h"

static uint8_t dev_addr;
static uint16_t length;

static tusb_descriptor_interface_t const * p_comm_interface = &rndis_config_descriptor.cdc_comm_interface;
static tusb_descriptor_endpoint_t const * p_endpoint_notification = &rndis_config_descriptor.cdc_endpoint_notification;
static tusb_descriptor_endpoint_t const * p_endpoint_out = &rndis_config_descriptor.cdc_endpoint_out;
static tusb_descriptor_endpoint_t const * p_endpoint_in = &rndis_config_descriptor.cdc_endpoint_in;

static pipe_handle_t pipe_notification = { .dev_addr = 1, .xfer_type = TUSB_XFER_INTERRUPT };
static pipe_handle_t pipe_out          = { .dev_addr  = 1, .xfer_type = TUSB_XFER_BULK, .index = 0 };
static pipe_handle_t pipe_int          = { .dev_addr  = 1, .xfer_type = TUSB_XFER_BULK, .index = 1 };

extern cdch_data_t cdch_data[TUSB_CFG_HOST_DEVICE_MAX];
static cdch_data_t * p_cdc = &cdch_data[0];


void setUp(void)
{
  length = 0;
  dev_addr = 1;

  cdch_init();

  hcd_pipe_open_ExpectAndReturn(dev_addr, p_endpoint_notification, TUSB_CLASS_CDC, pipe_notification);
  hcd_pipe_open_ExpectAndReturn(dev_addr, p_endpoint_out, TUSB_CLASS_CDC, pipe_out);
  hcd_pipe_open_ExpectAndReturn(dev_addr, p_endpoint_in, TUSB_CLASS_CDC, pipe_int);
}

void tearDown(void)
{

}

//tusb_
void test_rndis_send_initalize(void)
{
//  usbh_control_xfer_subtask_ExpectAndReturn(dev_addr, )

  //------------- Code Under Test -------------//
  TEST_ASSERT_EQUAL( TUSB_ERROR_NONE, cdch_open_subtask(dev_addr, p_comm_interface, &length) );
}