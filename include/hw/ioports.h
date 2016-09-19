 /*
  * 
  * MADos, a free OS for N* handsets  
  * Copyright (C) 2003/2004 MADos Core Developer Team  
  * 
  * This library is free software; you can redistribute it and/or  
  * modify it under the terms of the GNU Lesser General Public  
  * License as published by the Free Software Foundation; either  
  * version 2.1 of the License, or (at your option) any later version.  
  * 
  * This library is distributed in the hope that it will be useful,  
  * but WITHOUT ANY WARRANTY; without even the implied warranty of  
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU  
  * Lesser General Public License for more details.  
  * 
  * You should have received a copy of the GNU Lesser General Public  
  * License along with this library; if not, write to the Free Software  
  * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA  
  * 
  * contact http://64.246.26.121/forum/forumdisplay.php?f=99  
  * 
  */

extern int io_tmp;

#ifdef PHONE_5110

// 5110

#define IO_CTSI_RST   0x01
#define IO_CTSI_DSP   0x02
#define IO_CTSI_WDT   0x03
#define IO_CTSI_TMR1  0x04
#define IO_CTSI_FIQL  0x08
#define IO_CTSI_IRQL  0x09
#define IO_CTSI_FIQM  0x0A
#define IO_CTSI_IRQM  0x0B
#define IO_CTSI_ICR   0x0C
#define IO_CTSI_CTRL  0x0D
#define IO_CTSI_TMR0D 0x0F
#define IO_CTSI_TMR0  0x10
#define IO_CTSI_TMR0T 0x12

#define CTSI_CTL_AC   0x01
#define CTSI_CTL_AC2  0x02
#define CTSI_CTL_GC   0x04
#define CTSI_CTL_UU   0x08
#define CTSI_CTL_SC   0x20

#define CTSI_DSP_RST   0x01
#define CTSI_ICR_FIQE  0x01
#define CTSI_ICR_FIQD  0x02
#define CTSI_ICR_IRQE  0x04
#define CTSI_ICR_IRQD  0x08
#define CTSI_ICR_IRQ8  0x20
#define CTSI_ICR_IRQ8M 0x40

#define IO_UIF_CTRL2   0x32
#define IO_UIF_CTRL3   0x33

#define UIF_CTRL2_RST  0x20
#define UIF_CTRL3_VPP  0x01
#define UIF_CTRL3_LED  0x02
#define UIF_CTRL3_MAP  0x08
#define UIF_CTRL3_BTN  0x20
#define UIF_CTRL3_CHR  0x40


#define IO_PUP_CTRL    0x15
#define PUP_CTRL_MBUS_SPEED	0x07
#define PUP_CTRL_MBUS_EN	0x08
#define PUP_CTRL_VIB_EN	0x10
#define PUP_VIB_EN		PUP_CTRL_VIB_EN /* Compatibility */
#define PUP_CTRL_BUZ_EN	0x20
#define PUP_BUZ_EN		PUP_CTRL_BUZ_EN /* Compatibility */
#define PUP_CTRL_MBUS_SYNC	0x40
#define PUP_MBUS_SYN		PUP_CTRL_MBUS_SYNC  /* Compatibility */
#define PUP_CTRL_MCLK_DBL	0x80
#define PUP_MBUS_SPD		PUP_CTRL_MCLK_DBL   /* Compatibility */

#define IO_PUP_FIQ8    0x16
#define PUP_FIQ8_EN    0x01
#define PUP_FIQ8_ACT   0x02
#define PUP_FIQ8_MSK   0x04

#define IO_PUP_BUZ_FH  0x1C
#define IO_PUP_BUZ_FL  0x1D
#define IO_PUP_BUZ_V   0x1E
#define IO_PUP_VIB     0x1B
#define IO_PUP_GENIO   0x20

#define IO_UIF_KPD_R   0x31     // 28
#define IO_UIF_KPD_C   0x30     // 2A
#define IO_UIF_UNK_R   0x23     // 68
#define IO_UIF_UNK_C   0x2E     // 6A
#define IO_UIF_IM_R    0x26     // 69
#define IO_UIF_IM_C    0x33     // 6B
#define IO_UIF_DIR_R   0x2F     // A8
#define IO_UIF_DIR_C   0x27     // A9
#define IO_UIF_UNK     0x32     // AB


#define UIF_CTRL2_VPP1 0x01
#define UIF_CTRL2_VPP2 0x20
#define UIF_CTRL3_LED2 0x20     // for 6210 LED control

#define IO_PUP_DIR     0x24

#define PUP_GENIO_DISP 0x20     // 08
#define PUP_GENIO_LED  0x40
#define GENSIO_LCD_DATA		0x2B    // 2E
#define GENSIO_LCD_CMD 0x2C     // 6E

// data field for GENSIO_CFG
#define GENSIO_LCD_ENABLE	0x24    // 20
// data field for GENSIO_STATUS
#define GENSIO_STATUS_RDY	0x01


#define GENSIO_CFG     0x28     // 2D
#define GENSIO_STATUS  0x29     // 6D
#define GENSIO_CC_WR   0x2A     // 2C
#define GENSIO_CC_RD   0x2D     // 6C

#define GENSIO_RDY_WR  0x01
#define GENSIO_RDY_TR  0x02
#define GENSIO_RDY_RD  0x04

#define IO_MBUS_CTRL   0x18
#define MBUS_CTRL_TXD		0x20
#define MBUS_CTRL_RXD		0x40
#define MBUS_CTRL_RESET	0x80
#define IO_MBUS_STATUS 0x19
#define MBUS_STATUS_BITCNT	0x07
#define MBUS_STATUS_TXDRDY	0x10
#define MBUS_STATUS_RXDRDY	0x20
#define MBUS_STATUS_SCL	0x40
#define MBUS_STATUS_SDA	0x80
#define IO_MBUS_BYTE   0x1A

#define SIMI_TXD 0x36
#define SIMI_RXD 0x37
#define SIMI_UART_INT 0x38
#define SIMI_CTRL 0x39
#define SIMI_CLK_CTRL 0x3A
#define SIMI_TXD_LWM 0x3B
#define SIMI_RXD_QUE 0x3C
#define SIMI_RXD_FL 0x3D
#define SIMI_TXD_FL 0x3E
#define SIMI_TXD_QUE 0x3F



#else

  // other phones


#define IO_CTSI_RST   0x01
#define IO_CTSI_DSP   0x02
#define IO_CTSI_WDT   0x03
#define IO_CTSI_TMR1  0x04
#define IO_CTSI_FIQL  0x08
#define IO_CTSI_IRQL  0x09
#define IO_CTSI_FIQM  0x0A
#define IO_CTSI_IRQM  0x0B
#define IO_CTSI_ICR   0x0C
#define IO_CTSI_CTRL  0x0D
#define IO_CTSI_TMR0D 0x0F
#define IO_CTSI_TMR0  0x10
#define IO_CTSI_TMR0T 0x12

#define CTSI_CTL_AC   0x01
#define CTSI_CTL_AC2  0x02
#define CTSI_CTL_GC   0x04
#define CTSI_CTL_UU   0x08
#define CTSI_CTL_SC   0x20

#define CTSI_DSP_RST   0x01
#define CTSI_ICR_FIQE  0x01
#define CTSI_ICR_FIQD  0x02
#define CTSI_ICR_IRQE  0x04
#define CTSI_ICR_IRQD  0x08
#define CTSI_ICR_IRQ8  0x20
#define CTSI_ICR_IRQ8M 0x40

#define IO_UIF_CTRL2   0x32
#define IO_UIF_CTRL3   0x33

#define UIF_CTRL2_RST  0x20
#define UIF_CTRL3_VPP  0x01
#define UIF_CTRL3_LED  0x02
#define UIF_CTRL3_MAP  0x08
#define UIF_CTRL3_BTN  0x20
#define UIF_CTRL3_CHR  0x40


#define IO_PUP_CTRL    0x15
#define PUP_CTRL_MBUS_SPEED	0x07
#define PUP_CTRL_MBUS_EN	0x08
#define PUP_CTRL_VIB_EN	0x10
#define PUP_VIB_EN		PUP_CTRL_VIB_EN /* Compatibility */
#define PUP_CTRL_BUZ_EN	0x20
#define PUP_BUZ_EN		PUP_CTRL_BUZ_EN /* Compatibility */
#define PUP_CTRL_MBUS_SYNC	0x40
#define PUP_MBUS_SYN		PUP_CTRL_MBUS_SYNC  /* Compatibility */
#define PUP_CTRL_MCLK_DBL	0x80
#define PUP_MBUS_SPD		PUP_CTRL_MCLK_DBL   /* Compatibility */

#define IO_PUP_FIQ8    0x16
#define PUP_FIQ8_EN    0x01
#define PUP_FIQ8_ACT   0x02
#define PUP_FIQ8_MSK   0x04

#define IO_PUP_BUZ_FH  0x1C
#define IO_PUP_BUZ_FL  0x1D
#define IO_PUP_BUZ_V   0x1E
#define IO_PUP_VIB     0x1B
#define IO_PUP_GENIO   0x20

#define IO_UIF_KPD_R   0x28
#define IO_UIF_KPD_C   0x2A
#define IO_UIF_UNK_R   0x68
#define IO_UIF_UNK_C   0x6A
#define IO_UIF_IM_R    0x69
#define IO_UIF_IM_C    0x6B
#define IO_UIF_DIR_R   0xA8
#define IO_UIF_DIR_C   0xA9
#define IO_UIF_UNK     0xAB


#define UIF_CTRL2_VPP1 0x01
#define UIF_CTRL2_VPP2 0x20
#define UIF_CTRL3_LED2 0x20     // for 6210 LED control

#define IO_PUP_DIR     0x24

#define PUP_GENIO_DISP 0x08
#define PUP_GENIO_LED  0x00
#define GENSIO_LCD_DATA		0x2E
#define GENSIO_LCD_CMD 0x6E

// data field for GENSIO_CFG
#define GENSIO_LCD_ENABLE	0x20
// data field for GENSIO_STATUS
#define GENSIO_STATUS_RDY	0x01


#define GENSIO_CC_WR   0x2C
#define GENSIO_CFG     0x2D
#define GENSIO_CC_RD   0x6C
#define GENSIO_STATUS  0x6D

#define GENSIO_RDY_WR  0x01
#define GENSIO_RDY_TR  0x02
#define GENSIO_RDY_RD  0x04

#define IO_MBUS_CTRL   0x18
#define MBUS_CTRL_TXD		0x20
#define MBUS_CTRL_RXD		0x40
#define MBUS_CTRL_RESET	0x80
#define IO_MBUS_STATUS 0x19
#define MBUS_STATUS_BITCNT	0x07
#define MBUS_STATUS_TXDRDY	0x10
#define MBUS_STATUS_RXDRDY	0x20
#define MBUS_STATUS_SCL	0x40
#define MBUS_STATUS_SDA	0x80
#define IO_MBUS_BYTE   0x1A

#define SIMI_TXD 0x36
#define SIMI_RXD 0x37
#define SIMI_UART_INT 0x38
#define SIMI_CTRL 0x39
#define SIMI_CLK_CTRL 0x3A
#define SIMI_TXD_LWM 0x3B
#define SIMI_RXD_QUE 0x3C
#define SIMI_RXD_FL 0x3D
#define SIMI_TXD_FL 0x3E
#define SIMI_TXD_QUE 0x3F
#endif
