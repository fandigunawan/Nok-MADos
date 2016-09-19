
#define	NOKIA3310OLD	0
#define	NOKIA3310NEW	1
#define	NOKIA3330OLD	2
#define	NOKIA3330NEW	3
#define	NOKIA8210	4
#define	NOKIA3410	5
#define	NOKIA3350	6
#define	NOKIA6210	7
#define	NOKIA2100	8
#define	NOKIA5110	9

typedef struct
{
    char *name;
    unsigned char genio;
    unsigned char kpd;
    unsigned char kpd_matrix;
    unsigned char kpd_led;
    unsigned char led;
    unsigned char lcd;
    unsigned char lcd_xsize;
    unsigned char lcd_ysize;
    unsigned char lcd_contrast;
    unsigned char flashvpp;
}
phone_info_t;

#ifndef __MADOS_MAIN_C__
extern const phone_info_t mados_info[];
extern unsigned char mados_phone;
#endif
