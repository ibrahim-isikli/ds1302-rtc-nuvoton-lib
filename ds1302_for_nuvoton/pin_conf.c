/****************************************************************************
 * @file     pin_conf.c
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
Pin Configuration:
Pin28:PA.2
Pin29:PA.1
Pin30:PA.0
Pin33:ICE_DAT
Pin34:ICE_CLK
Pin41:UART0_TXD
Pin42:UART0_RXD
Module Configuration:
PA.0(Pin:30)
PA.1(Pin:29)
PA.2(Pin:28)
ICE_CLK(Pin:34)
ICE_DAT(Pin:33)
UART0_RXD(Pin:42)
UART0_TXD(Pin:41)
GPIO Configuration:
PA.0:PA.0(Pin:30)
PA.1:PA.1(Pin:29)
PA.2:PA.2(Pin:28)
PD.2:UART0_RXD(Pin:42)
PD.3:UART0_TXD(Pin:41)
PF.0:ICE_DAT(Pin:33)
PF.1:ICE_CLK(Pin:34)
********************/

#include "ds1302_for_nuvoton.h"

/*
 * @brief This function provides the configured MFP registers
 * @param None
 * @return None
 */
void Pin_Init(void)
{
    //SYS->GPA_MFPH = 0x00000000UL;
    //SYS->GPA_MFPL = 0x00000000UL;
    //SYS->GPB_MFPH = 0x00000000UL;
    //SYS->GPB_MFPL = 0x00000000UL;
    //SYS->GPC_MFPH = 0x00000000UL;
    //SYS->GPC_MFPL = 0x00000000UL;
    //SYS->GPD_MFPH = 0x00000000UL;
    //SYS->GPD_MFPL = 0x00009900UL;
    //SYS->GPF_MFPH = 0x00000000UL;
    //SYS->GPF_MFPL = 0x000000EEUL;

    SYS->GPA_MFPH = 0x00000000;
    SYS->GPA_MFPL = SYS_GPA_MFPL_PA2MFP_GPIO | SYS_GPA_MFPL_PA1MFP_GPIO | SYS_GPA_MFPL_PA0MFP_GPIO;
    SYS->GPB_MFPH = 0x00000000;
    SYS->GPB_MFPL = 0x00000000;
    SYS->GPC_MFPH = 0x00000000;
    SYS->GPC_MFPL = 0x00000000;
    SYS->GPD_MFPH = 0x00000000;
    SYS->GPD_MFPL = SYS_GPD_MFPL_PD3MFP_UART0_TXD | SYS_GPD_MFPL_PD2MFP_UART0_RXD;
    SYS->GPF_MFPH = 0x00000000;
    SYS->GPF_MFPL = SYS_GPF_MFPL_PF1MFP_ICE_CLK | SYS_GPF_MFPL_PF0MFP_ICE_DAT;

    return;
}

/*** (C) COPYRIGHT 2016-2025 Nuvoton Technology Corp. ***/
