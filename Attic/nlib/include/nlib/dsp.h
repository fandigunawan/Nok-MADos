#ifndef WMX_DSP
#define WMX_DSP

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

struct dsp_codeblock
{
    uint16 header[5];
    uint16 data[];
};

/* DSPIF constants */
#define DSPIF_ENABLE_SHARED	0x0000
#define DSPIF_DISABLE_SHARED	0x0002
#define DSPIF_INTERRUPT		0x0004

void DSP_initialize (  );
void DSP_startup (  );
void DSP_interrupt (  );
void DSP_enable ( int state );
int DSP_uploadCodeblock ( struct dsp_codeblock *c, int sub );

#endif
