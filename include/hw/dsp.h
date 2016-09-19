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

#ifndef MADOS_DSP
#define MADOS_DSP

struct dsp_codeblock
{
    unsigned short header[5];
    unsigned short data[];
};

void dsp_init ( void );
void dsp_setmem ( unsigned int mode );
void dsp_genint ( void );
void dsp_enable ( void );
void dsp_disable ( void );
void dsp_reset ( void );
void dsp_upload ( unsigned int block, const unsigned short *src, unsigned int len );
int dsp_upload_codeblock ( struct dsp_codeblock *c, int sub );
void dsp_int_handler ( void );
void dsp_clear_ram ( void );
void dsp_bootstrap ( const unsigned short *block, unsigned int len );
int dsp_test ( void );
void dsp_readmem ( void );


#define DSP_MEM_HOST   0
#define DSP_MEM_SHARED 1

/* In words */
#define DSP_SHARED_SIZE		(0x1000/2)

/* _dsp shared memory areas */
#define DSP_MDISND_TAIL		(0x0A4/2)
#define DSP_MDISND_HEAD		(0x0A6/2)
#define DSP_INITDATA		(0x0A8/2)
#define DSP_MDISND_QUEUE	(0x000/2)
#define DSP_MDISND_SIZE		(0x0A4/2)
#define DSP_MDISND_QUEUEEND	(DSP_MDISND_QUEUE + DSP_MDISND_SIZE)
#define DSP_UPLOADREQUEST	(0x0E2/2)
#define DSP_UPLOADREPLY		(0x0E4/2)
#define DSP_UPLOADREPLY_MORE		0x0002
#define DSP_UPLOADREPLY_FINISHED	0x0004
#define DSP_UPLOADHEADER	(0x0F6/2)
#define DSP_MDIRCV_QUEUE	(0x100/2)
#define DSP_MDIRCV_SIZE		(0x0C8/2)
#define DSP_MDIRCV_QUEUEEND	(DSP_MDIRCV_QUEUE + DSP_MDIRCV_SIZE)
#define DSP_MDIRCV_TAIL		(0x1C8/2)
#define DSP_MDIRCV_HEAD		(0x1CA/2)


/* Offsets in upload header */
#define DSP_UPLHDR_TARGET	0
#define DSP_UPLHDR_SIZE 	2
#define DSP_UPLHDR_OFFSET 	3
#define DSP_UPLHDR_BLOCKSIZE	4


/* DSPIF constants */
#define DSPIF_ENABLE_SHARED	0x0000
#define DSPIF_DISABLE_SHARED	0x0002
#define DSPIF_INTERRUPT		0x0004


#endif
