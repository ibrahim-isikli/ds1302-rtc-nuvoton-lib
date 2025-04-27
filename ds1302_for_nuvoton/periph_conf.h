/****************************************************************************
 * @file     periph_conf.h
 * @version  V0.42
 * @Date     2025/04/27-18:23:34
 * @brief    NuMicro generated code file
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright (C) 2016-2025 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

/********************
MCU:M032SE3AE(LQFP64)
********************/

/*--------------------------------------------------------------------------*/
/* CLK Configuration                                                        */
/*--------------------------------------------------------------------------*/

#define CLK_HXT_FREQUENCY_RANGE_UPPER_BOUND     (697)

#define CLK_HXT_FREQUENCY_RANGE_LOWER_BOUND     (669)

/*--------------------------------------------------------------------------*/
/* GPIO PA Configuration                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* TIMER0 Configuration                                                     */
/*--------------------------------------------------------------------------*/

#define TIMER0_MODE                     TIMER_PERIODIC_MODE

#define TIMER0_FREQ                     1000000

/*--------------------------------------------------------------------------*/
/* UART0 Configuration                                                      */
/*--------------------------------------------------------------------------*/

#define UART0_MATCH_ADDRSS1     0xC0
#define UART0_MATCH_ADDRSS2     0xA2
#define UART0_UNMATCH_ADDRSS1   0xB1
#define UART0_UNMATCH_ADDRSS2   0xD3

#define UART0_BAUD                      115200

/*** (C) COPYRIGHT 2016-2025 Nuvoton Technology Corp. ***/
