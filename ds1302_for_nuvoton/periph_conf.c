#include "ds1302_for_nuvoton.h"
void CLK_Init(void)
{

    /* Configure clock detector functions, which are able to monitor the operations of HXT and LXT */
    CLK->CLKDCTL = (CLK_CLKDCTL_HXTFDEN_Msk | CLK_CLKDCTL_HXTFQDEN_Msk | CLK_CLKDCTL_LXTFDEN_Msk);

}
/*--------------------------------------------------------------------------------------------*/
/* GPIO                                                                                     */
/*--------------------------------------------------------------------------------------------*/
void GPIO_Init()
{
    volatile const uint32_t u32RegDefault = 0;

    //GPIO_PA disable digital input path
    PA->DINOFF =

        (0 << GPIO_DINOFF_DINOFF0_Pos) |

        (0 << GPIO_DINOFF_DINOFF1_Pos) |

        (0 << GPIO_DINOFF_DINOFF2_Pos) |

        u32RegDefault;

    //GPIO_PA out data
    PA->DOUT =

        (1 << GPIO_DOUT_DOUT0_Pos) |

        (1 << GPIO_DOUT_DOUT1_Pos) |

        (1 << GPIO_DOUT_DOUT2_Pos) |

        u32RegDefault;

    //GPIO_PA DOUT mask
    PA->DATMSK =

        (0 << GPIO_DATMSK_DATMSK0_Pos) |

        (0 << GPIO_DATMSK_DATMSK1_Pos) |

        (0 << GPIO_DATMSK_DATMSK2_Pos) |

        u32RegDefault;

    //GPIO_PA mode
    PA->MODE =

        (0x1UL << GPIO_MODE_MODE0_Pos) |

        (0x3UL << GPIO_MODE_MODE1_Pos) |

        (0x1UL << GPIO_MODE_MODE2_Pos) |

        u32RegDefault;

    //GPIO_PA enable de-bounce
    PA->DBEN =

        (0 << GPIO_DBEN_DBEN0_Pos) |

        (0 << GPIO_DBEN_DBEN1_Pos) |

        (0 << GPIO_DBEN_DBEN2_Pos) |

        u32RegDefault;

    //GPIO_PA edge or level interrupt
    PA->INTTYPE =

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE0_Pos) |

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE1_Pos) |

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE2_Pos) |

        u32RegDefault;

    //GPIO_PA enable falling(edge) or low(level) interrupt
    PA->INTEN =

        (0 << GPIO_INTEN_FLIEN0_Pos) |

        (0 << GPIO_INTEN_FLIEN1_Pos) |

        (0 << GPIO_INTEN_FLIEN2_Pos) |

        u32RegDefault;

    //GPIO_PA enable rising(edge) or high(level) interrupt
    PA->INTEN |=

        (0 << GPIO_INTEN_RHIEN0_Pos) |

        (0 << GPIO_INTEN_RHIEN1_Pos) |

        (0 << GPIO_INTEN_RHIEN2_Pos) |

        u32RegDefault;

}
void SYS_Init(void)
{

    /* Disable Brown-Out Detector function */
    SYS_DisableBOD();

    /* Dsiable Low-Voltage Detector function */
    SYS_DISABLE_LVR();

}
void TIMER0_Init()
{
    TIMER_Open(TIMER0, TIMER0_MODE, TIMER0_FREQ);

#if (TIMER0_MODE == TIMER_TOGGLE_MODE)
    TIMER_SELECT_TOUT_PIN(TIMER0, TIMER_TOUT_PIN_FROM_TX);
#endif

}
void UART0_Init()
{

    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, UART0_BAUD);

    /* RX FIFO Interrupt Trigger Level */
    UART0->FIFO = (UART0->FIFO & ~ UART_FIFO_RFITL_Msk) | UART_FIFO_RFITL_1BYTE;

}

void Periph_Init(void)
{

    CLK_Init();

    SYS_Init();

    UART0_Init();

    GPIO_Init();

    TIMER0_Init();

}
