/*

Original source written in C++ by Safronov Pavel (http://www.progc.narod.ru, mail: progc@narod.ru)

Adaptation for MADos, reworking, interface: kraze1984 (kraze1984@hotmail.com)

*/
#include <hw/kpd.h>
#include <core/lib.h>
#include <hw/ccont.h>
#include <hw/vibra.h>
#include <apps/arcanoid.h>
#include <core/sched.h>

int x = 33, y = 39, vx = 1, vy = 1, key = 0, h = 0, h1 = 0, arcx = 30, i = 0, i1 = 0, n = 0;
int live = 3, kub = 0, hsc = 0, diff = 0, timet = 0, lev = 1;
int k1[60], k2[60], k3[60], k4[60], k5[60], k6[60], k7[60], k8[60], k9[60], k10[60], k11[60], k12[60], k13[60], k14[60], k15[60], k16[60];
//long *timetime = (long*)MK_FP(0x40, 0x6c);
long t1 = 0, t2 = 0, t3 = 0, t4 = 0;

//15.05.2004 menus
void
marc_skill (  )
{
    char *marcmenu[] = { "beginner", "easy", "normal", "hard", "*back*", NULL };
    unsigned char key, k;

    while ( 1 )
    {
        key = menu_main ( marcmenu, 0 );
        kpd_wait_release (  );
        lib_rand ( key );
        if ( key == 0xff )
            break;
        key++;
        if ( key == 0x5 )
            break;
        switch ( key )
        {
            case 0x1:
                diff = 50000;
                k = 0xff;
                break;
            case 0x2:
                diff = 30000;
                k = 0xff;
                break;
            case 0x3:
                diff = 15000;
                k = 0xff;
                break;
            case 0x4:
                diff = 7000;
                k = 0xff;
                break;

            default:
                break;
        }
        if ( k == 0xff )
            break;
        usleep ( 50000 );
    }
}

void
marc_level (  )
{
    char *marcmenu[] = { "table 1", "table 2", "*back*", NULL };
    unsigned char key, k;

    while ( 1 )
    {

        key = menu_main ( marcmenu, 0 );
        kpd_wait_release (  );
        lib_rand ( key );
        if ( key == 0xff )
            break;
        key++;
        if ( key == 0x3 )
            break;
        switch ( key )
        {
            case 0x1:
                lev = 1;
                k = 0xff;
                break;
            case 0x2:
                lev = 3;
                k = 0xff;
                break;

            default:
                break;
        }
        if ( k == 0xff )
            break;
        usleep ( 50000 );
    }
}


void
marc_main (  )
{
    char *marcmenu[] = { "1- play MArc", "2- table", "3- skill", "4- *back*", NULL };
    unsigned char key;


    while ( 1 )
    {
        key = menu_main ( marcmenu, 0 );
        kpd_wait_release (  );
        lib_rand ( key );
        if ( key == 0xff )
            break;
        key++;
        if ( key == 0x4 )
            break;
        switch ( key )
        {
            case 0x1:
                lcd_clr (  );
                arcanoid_main (  );
                break;
            case 0x2:
                marc_level (  );
                break;
            case 0x3:
                marc_skill (  );
                break;
            default:
                break;
        }
    }
}


//04.04.2004 score
void
show_score ( void )
{
    char score_buf[4], live_buf[1]; //, rows_buf[4];

    lib_dtoa ( score_buf, kub, 4, 0 );
    //lib_dtoa ( live_buf, live, 1, 0 );
    //lib_dtoa ( rows_buf, rows, 3, 0 );

    lcd_draw_rect ( 60, 7 + 0 * 8, 58 + 3 * 8, 7 + 1 * 8, 0 );
    lcd_draw_rect ( 75, 7 + 3 * 8, 75 + 5, 7 + 4 * 8, 0 );
    //lcd_draw_rect ( 62 + 4, 7 + 2 * 8, 62 + 4 + 4 * 8, 7 + 3 * 8, 0 );

    if ( kub == 0 )
    {
        lcd_render_text ( 60, 7 + 0 * 8, "pts.", 1 );
        lib_dtoa ( live_buf, live, 1, 0 );
        lcd_render_text ( 75, 7 + 3 * 8 + 1, live_buf, 1 );
        //    lcd_render_text ( 60, 7 + 3 * 8, "ball", 1 );
        //    lcd_render_text ( 42 + 4, 20 + 2 * 8, "rows", 1 );
    }
    else
    {
        lcd_render_text ( 60, 7 + 0 * 8, score_buf, 1 );
        lib_dtoa ( live_buf, live, 1, 0 );
        lcd_render_text ( 75, 7 + 3 * 8 + 1, live_buf, 1 );
        //lcd_render_text ( 50, 20 + 2 * 8, rows_buf, BLACK );
    }
}


//28.04.2004 vibration function

void
marc_vibra ( void )
{

    vibra_setmode ( 2 );
    vibra_setfreq ( 20 );

    usleep ( 100000 );

    vibra_setmode ( 0 );
    vibra_setfreq ( 0 );

    usleep ( 70000 );

    return;
}


void
arcanoid ( void )
{
/*	gotoxy(1,25);
	for(int i=0; i<79; i++)
		printf(" ");
	gotoxy(arcx,25);
	printf("|");
	for(i=0; i<3; i++)
	{
		printf("#");
	}
	printf("|");*/
    lcd_draw_line ( 1, 47, 57, 47, 0 );
    lcd_draw_line ( 1, 46, 57, 46, 0 );
    lcd_draw_line ( 1, 45, 57, 45, 0 );
    lcd_draw_line ( 1, 44, 57, 44, 0 );
    lcd_to_screen (  );

    lcd_draw_line ( arcx, 45, arcx + 1, 45, 1 );
    lcd_draw_line ( arcx + 7, 45, arcx + 8, 45, 1 );
    lcd_draw_line ( arcx + 1, 46, arcx + 7, 46, 1 );
    lcd_draw_line ( arcx + 1, 44, arcx + 7, 44, 1 );
    lcd_to_screen (  );
}

void
clr_cube ( void )
{

    i1 = i;
    lcd_draw_line ( i1, y, i1 + 2, y, 0 );
}


int
ball ( void )
{
    //t2=*timetime;
    t2 = lib_get_time (  );
    if ( ( t2 - t1 ) < timet )
    {
        return 0;
    }
    t1 = lib_get_time (  );
    //gotoxy(x,y);
    //printf(" ");

    lcd_draw_rect ( x, y, x + 3, y + 3, 0 );
    lcd_to_screen (  );


    if ( x < 2 )
        vx *= -1;
    if ( x > 53 )
        vx *= -1;
    if ( y > 39 )
    {
        if ( x == ( arcx - 2 ) )
        {
            vy = -1;
            vx = -2;
        }
        if ( x == ( arcx - 1 ) )
        {
            vy = -1;
            vx = -2;
        }
        if ( x == arcx )
        {
            vy = -2;
            vx = -2;
        }
        if ( x == ( arcx + 1 ) )
        {
            vy = -2;
            vx = -1;
        }
        if ( x == ( arcx + 2 ) )
        {
            if ( vy == -2 || vy == -1 )
                vy = 1;
            if ( vy == 1 || vy == 2 )
                vy = -1;
            vx = 0;
        }
        if ( x == ( arcx + 3 ) )
        {
            vy = -2;
            vx = 1;
        }
        if ( x == ( arcx + 4 ) )
        {
            vy = -2;
            vx = 2;
        }
        if ( x == ( arcx + 5 ) )
        {
            vy = -1;
            vx = 2;
        }
        if ( x == ( arcx + 6 ) )
        {
            vy = -1;
            vx = 2;

        }
        if ( x > ( arcx + 6 ) || x < ( arcx - 2 ) )
            return 1;
    }
    if ( y < 2 )
        vy *= -1;
    x += vx;
    y += vy;
    //gotoxy(x,y);
    //printf(" ");
    //gotoxy(x,y);
    //printf("*");

    lcd_draw_rect ( x, y, x + 2, y + 2, 0 );
    lcd_to_screen (  );

    lcd_draw_line ( x, y + 2, x, y + 1, 1 );
    lcd_draw_line ( x + 1, y, x + 2, y, 1 );
    lcd_draw_line ( x + 3, y + 1, x + 3, y + 2, 1 );
    lcd_draw_line ( x + 2, y + 3, x + 1, y + 3, 1 );
    lcd_to_screen (  );

    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k1[i] == 1 )
        {
            if ( x == ( i - 2 ) && y == 2 )
            {
                kub++;
                k1[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 2 )
            {
                kub++;
                k1[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 2 )
            {
                kub++;
                k1[i] = 0;
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 2 )
            {
                kub++;
                k1[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 2 )
            {
                kub++;
                k1[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 2 )
            {
                kub++;
                k1[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k2[i] == 1 )
        {
            if ( x == ( i - 2 ) && y == 4 )
            {
                kub++;
                k2[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 4 )
            {
                kub++;
                k2[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 4 )
            {
                kub++;
                k2[i] = 0;
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 4 )
            {
                kub++;
                k2[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 4 )
            {
                kub++;
                k2[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 4 )
            {
                kub++;
                k2[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k3[i] == 1 )
        {
            if ( x == ( i - 2 ) && y == 6 )
            {
                kub++;
                k3[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 6 )
            {
                kub++;
                k3[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 6 )
            {
                kub++;
                k3[i] = 0;
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 6 )
            {
                kub++;
                k3[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 6 )
            {
                kub++;
                k3[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 6 )
            {
                kub++;
                k3[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k4[i] == 1 )
        {
            if ( x == ( i - 2 ) && y == 8 )
            {
                kub++;
                k4[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 8 )
            {
                kub++;
                k4[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 8 )
            {
                kub++;
                k4[i] = 0;
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 8 )
            {
                kub++;
                k4[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 8 )
            {
                kub++;
                k4[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 8 )
            {
                kub++;
                k4[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k5[i] == 1 )
        {
            if ( x == ( i - 2 ) && y == 10 )
            {
                kub++;
                k5[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 10 )
            {
                kub++;
                k5[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 10 )
            {
                kub++;
                k5[i] = 0;
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 10 )
            {
                kub++;
                k5[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 10 )
            {
                kub++;
                k5[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 10 )
            {
                kub++;
                k5[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k6[i] == 1 )
        {
            if ( x == ( i - 2 ) && y == 12 )
            {
                kub++;
                k6[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 12 )
            {
                kub++;
                k6[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 12 )
            {
                kub++;
                k6[i] = 0;
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 12 )
            {
                kub++;
                k6[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 12 )
            {
                kub++;
                k6[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 12 )
            {
                kub++;
                k6[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k7[i] == 1 )
        {
            if ( x == ( i - 2 ) && y == 14 )
            {
                kub++;
                k7[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 14 )
            {
                kub++;
                k7[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 14 )
            {
                kub++;
                k7[i] = 0;
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 14 )
            {
                kub++;
                k7[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 14 )
            {
                kub++;
                k7[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 14 )
            {
                kub++;
                k7[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k8[i] == 1 )
        {
            if ( x == ( i - 2 ) && y == 16 )
            {
                kub++;
                k8[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 16 )
            {
                kub++;
                k8[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 16 )
            {
                kub++;
                k8[i] = 0;
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 16 )
            {
                kub++;
                k8[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 16 )
            {
                kub++;
                k8[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 16 )
            {
                kub++;
                k8[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k9[i] == 1 )
        {
            if ( x == ( i - 2 ) && y == 18 )
            {
                kub++;
                k9[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 18 )
            {
                kub++;
                k9[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 18 )
            {
                kub++;
                k9[i] = 0;
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 18 )
            {
                kub++;
                k9[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 18 )
            {
                kub++;
                k9[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 18 )
            {
                kub++;
                k9[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k10[i] == 1 )
        {
            if ( x == ( i - 2 ) && y == 20 )
            {
                kub++;
                k10[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 20 )
            {
                kub++;
                k10[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 20 )
            {
                kub++;
                k10[i] = 0;
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 20 )
            {
                kub++;
                k10[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 20 )
            {
                kub++;
                k10[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 20 )
            {
                kub++;
                k10[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k11[i] == 1 )
        {
            if ( x == ( i - 2 ) && y == 22 )
            {
                kub++;
                k11[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 22 )
            {
                kub++;
                k11[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 22 )
            {
                kub++;
                k11[i] = 0;
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 22 )
            {
                kub++;
                k11[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 22 )
            {
                kub++;
                k11[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 22 )
            {
                kub++;
                k11[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k12[i] == 1 )
        {
            if ( x == ( i - 2 ) && y == 24 )
            {
                kub++;
                k12[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 24 )
            {
                kub++;
                k12[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 24 )
            {
                kub++;
                k12[i] = 0;
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 24 )
            {
                kub++;
                k12[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 24 )
            {
                kub++;
                k12[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 24 )
            {
                kub++;
                k12[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k13[i] == 1 )
        {
            if ( x == ( i - 2 ) && y == 26 )
            {
                kub++;
                k13[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 26 )
            {
                kub++;
                k13[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 26 )
            {
                kub++;
                k13[i] = 0;
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 26 )
            {
                kub++;
                k13[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 26 )
            {
                kub++;
                k13[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 26 )
            {
                kub++;
                k13[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k14[i] == 1 )
        {
            if ( x == ( i - 2 ) && y == 28 )
            {
                kub++;
                k14[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 28 )
            {
                kub++;
                k14[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 28 )
            {
                kub++;
                k14[i] = 0;
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 28 )
            {
                kub++;
                k14[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 28 )
            {
                kub++;
                k14[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 28 )
            {
                kub++;
                k14[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k15[i] == 1 )
        {
            if ( x == ( i - 2 ) && y == 30 )
            {
                kub++;
                k15[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 30 )
            {
                kub++;
                k15[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 30 )
            {
                kub++;
                k15[i] = 0;
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 30 )
            {
                kub++;
                k15[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 30 )
            {
                kub++;
                k15[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 30 )
            {
                kub++;
                k15[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k16[i] == 1 )
        {
            if ( x == ( i - 2 ) && y == 32 )
            {
                kub++;
                k16[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 32 )
            {
                kub++;
                k16[i] = 0;
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 32 )
            {
                kub++;
                k16[i] = 0;
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 32 )
            {
                kub++;
                k16[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 32 )
            {
                kub++;
                k16[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 32 )
            {
                kub++;
                k16[i] = 0;
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }

//********************************REACTION ON STONES**********************
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k1[i] == 2 )
        {
            if ( x == ( i - 2 ) && y == 2 )
            {
                vy *= -1;
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 2 )
            {
                vy *= -1;
                marc_vibra (  );
            }
            if ( x == i && y == 2 )
            {
                vy *= -1;
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 2 )
            {
                vy *= -1;
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 2 )
            {
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 2 )
            {
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k2[i] == 2 )
        {
            if ( x == ( i - 2 ) && y == 4 )
            {
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 4 )
            {
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 4 )
            {
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 4 )
            {
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 4 )
            {
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 4 )
            {
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k3[i] == 2 )
        {
            if ( x == ( i - 2 ) && y == 6 )
            {
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 6 )
            {
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 6 )
            {
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 6 )
            {
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 6 )
            {
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 6 )
            {
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k4[i] == 2 )
        {
            if ( x == ( i - 2 ) && y == 8 )
            {
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 8 )
            {
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 8 )
            {
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 8 )
            {
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 8 )
            {
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 8 )
            {
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k5[i] == 2 )
        {
            if ( x == ( i - 2 ) && y == 10 )
            {
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 10 )
            {
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 10 )
            {
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 10 )
            {
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 10 )
            {
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 10 )
            {
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k6[i] == 2 )
        {
            if ( x == ( i - 2 ) && y == 12 )
            {
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 12 )
            {
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 12 )
            {
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 12 )
            {
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 12 )
            {
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 12 )
            {
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k7[i] == 2 )
        {
            if ( x == ( i - 2 ) && y == 14 )
            {
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 14 )
            {
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 14 )
            {
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 14 )
            {
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 14 )
            {
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 14 )
            {
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k8[i] == 2 )
        {
            if ( x == ( i - 2 ) && y == 16 )
            {
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 16 )
            {
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 16 )
            {
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 16 )
            {
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 16 )
            {
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 16 )
            {
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k9[i] == 2 )
        {
            if ( x == ( i - 2 ) && y == 18 )
            {
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 18 )
            {
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 18 )
            {
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 18 )
            {
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 18 )
            {
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 18 )
            {
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k10[i] == 2 )
        {
            if ( x == ( i - 2 ) && y == 20 )
            {
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 20 )
            {
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 20 )
            {
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 20 )
            {
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 20 )
            {
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 20 )
            {
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k11[i] == 2 )
        {
            if ( x == ( i - 2 ) && y == 22 )
            {
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 22 )
            {
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 22 )
            {
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 22 )
            {
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 22 )
            {
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 22 )
            {
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k12[i] == 2 )
        {
            if ( x == ( i - 2 ) && y == 24 )
            {
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 24 )
            {
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 24 )
            {
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 24 )
            {
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 24 )
            {
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 24 )
            {
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k13[i] == 2 )
        {
            if ( x == ( i - 2 ) && y == 26 )
            {
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 26 )
            {
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 26 )
            {
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 26 )
            {
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 26 )
            {
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 26 )
            {
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k14[i] == 2 )
        {
            if ( x == ( i - 2 ) && y == 28 )
            {
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 28 )
            {
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 28 )
            {
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 28 )
            {
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 28 )
            {
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 28 )
            {
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k15[i] == 2 )
        {
            if ( x == ( i - 2 ) && y == 30 )
            {
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 30 )
            {
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 30 )
            {
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 30 )
            {
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 30 )
            {
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 30 )
            {
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }
    for ( i = 2; i < 55; i = i + 4 )
    {
        if ( k16[i] == 2 )
        {
            if ( x == ( i - 2 ) && y == 32 )
            {
                vy *= -1;
                lcd_draw_line ( x + 2, y, x + 4, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i - 1 ) && y == 32 )
            {
                vy *= -1;
                lcd_draw_line ( x + 1, y, x + 3, y, 0 );
                marc_vibra (  );
            }
            if ( x == i && y == 32 )
            {
                vy *= -1;
                lcd_draw_line ( x, y, x + 2, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 1 ) && y == 32 )
            {
                vy *= -1;
                lcd_draw_line ( x - 1, y, x + 1, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 2 ) && y == 32 )
            {
                vy *= -1;
                lcd_draw_line ( x - 2, y, x, y, 0 );
                marc_vibra (  );
            }
            if ( x == ( i + 3 ) && y == 32 )
            {
                vy *= -1;
                lcd_draw_line ( x - 3, y, x - 1, y, 0 );
                marc_vibra (  );
            }
        }
    }

    //gotoxy(1,2);
    //printf("%d",kub);
    return 0;
}


void
kubic ( void )
{
    lcd_draw_line ( i, h, i + 2, h, 0 );
    lcd_draw_line ( i, h + 1, i + 2, h + 1, 1 );
    //printf("\376");
}

void
kubic0 ( void )
{
    lcd_draw_line ( i, h, i + 2, h, 0 );
    lcd_draw_line ( i, h + 1, i + 2, h + 1, 0 );

}

void
stone ( void )
{
    lcd_draw_rect ( i - 1, h, i + 3, h + 2, 1 );
    lcd_draw_line ( i, h + 1, i + 2, h + 1, 0 );
}



void
cubes ( void )
{
/*	for(int i=0; i<60; i++)
	{
		gotoxy((10+i),3);
		kubic();
	}
	for(i=0; i<60; i++)
	{
		gotoxy((10+i),4);
		kubic();
	}
	for(i=0; i<60; i++)
	{
		gotoxy((10+i),5);
		kubic();
	}
	for(i=0; i<60; i++)
	{
		gotoxy((10+i),6);
		kubic();
	}
	for(i=0; i<60; i++)
	{
		gotoxy((10+i),7);
		kubic();
	}
*/

//***************************DRAWS 1st LEVEL*********************
    if ( lev == 1 )
    {
        for ( i = 2; i < 55; i = i + 4 )
        {
            for ( h = 1; h < 14; h = h + 2 )
            {
                kubic (  );
                lcd_to_screen (  );
            }
        }
        return;
    }

//**************************DRAWS 3rd LEVEL**********************
    if ( lev == 3 )
    {
        i = 2;
        h = 1;
        kubic (  );
        i = 54;
        h = 1;
        kubic (  );
        for ( i = 2; i < 11; i = i + 4 )
        {
            for ( h = 3; h < 10; h = h + 2 )
            {
                kubic (  );
            }

        }
        for ( i = 46; i < 55; i = i + 4 )
        {
            for ( h = 3; h < 10; h = h + 2 )
            {
                kubic (  );
            }
        }
        for ( h = 5; h < 12; h = h + 2 )
        {
            i = 14;
            kubic (  );
            i = 42;
            kubic (  );
        }
        for ( i = 18; i < 39; i = i + 4 )
        {
            for ( h = 11; h < 18; h = h + 2 )
            {
                kubic (  );
            }
        }
        h = 21;
        i = 2;
        stone (  );
        i = 54;
        stone (  );
        h = 5;
        i = 26;
        stone (  );
        i = 30;
        stone (  );

        lcd_to_screen (  );

        return;
    }
}

/*
	RULES FOR LEVELS:
	
1. The level consists of bricks (kubic) that are 1 pixel thick and 3 pixels long
2. You can place stones (stone) 3 pixels thick and 5 pixels long
3. The bricks are located in a grid with 16 rows and 14 columns
4. i is x coordinate, and h is y coordinate of LCD
5. Between bricks the distance is 1 pixel. Between stone and brick the distance is
   2 pixels - vertically, 0 pixels horizontally.
6. The action of colliding with brick is defined in collision tables:
    0 - nothing happens
    1 - it's a brick - the ball collides with unit, destroys it, repercutes and you get points
    2 - it's a stone - the ball can never destroy the unit

*/

void
interf ( void )
{
    lcd_draw_line ( 0, 47, 0, 0, 1 );
    lcd_draw_line ( 1, 0, 58, 0, 1 );
    lcd_draw_line ( 58, 1, 58, 47, 1 );
    lcd_draw_line ( 58, 1, 59, 1, 1 );
    lcd_draw_line ( 58, 20, 58, 31, 1 );
    lcd_draw_line ( 59, 2, 59, 18, 1 );
    lcd_draw_line ( 59, 31, 59, 46, 1 );
    lcd_draw_line ( 60, 0, 82, 0, 1 );
    lcd_draw_line ( 60, 19, 82, 19, 1 );
    lcd_draw_line ( 60, 30, 82, 30, 1 );
    lcd_draw_line ( 60, 47, 82, 47, 1 );
    lcd_draw_line ( 83, 1, 83, 18, 1 );
    lcd_draw_line ( 83, 31, 83, 46, 1 );
    lcd_draw_line ( 62, 27, 62, 22, 1 );
    lcd_draw_line ( 62, 22, 64, 24, 1 );
    lcd_draw_line ( 64, 24, 66, 22, 1 );
    lcd_draw_line ( 66, 22, 66, 27, 1 );
    lcd_draw_line ( 68, 27, 70, 22, 1 );
    lcd_draw_line ( 70, 22, 72, 27, 1 );
    lcd_draw_line ( 69, 25, 71, 25, 1 );
    lcd_draw_line ( 74, 27, 74, 24, 1 );
    lcd_draw_line ( 74, 26, 76, 24, 1 );
    lcd_draw_line ( 80, 24, 79, 24, 1 );
    lcd_draw_line ( 80, 27, 79, 27, 1 );
    lcd_draw_line ( 78, 25, 78, 26, 1 );
}

void
arcanoid_main (  )
{
//  clrscr();

    lcd_draw_rect ( 1, 1, 56, 47, 0 );


//def all collisions to 0

    for ( n = 2; n < 55; n = n + 4 )
    {
        k1[n] = 0;
    }
    for ( n = 2; n < 55; n = n + 4 )
    {
        k2[n] = 0;
    }
    for ( n = 2; n < 55; n = n + 4 )
    {
        k3[n] = 0;
    }
    for ( n = 2; n < 55; n = n + 4 )
    {
        k4[n] = 0;
    }
    for ( n = 2; n < 55; n = n + 4 )
    {
        k5[n] = 0;
    }
    for ( n = 2; n < 55; n = n + 4 )
    {
        k6[n] = 0;
    }
    for ( n = 2; n < 55; n = n + 4 )
    {
        k7[n] = 0;
    }
    for ( n = 2; n < 55; n = n + 4 )
    {
        k8[n] = 0;
    }
    for ( n = 2; n < 55; n = n + 4 )
    {
        k9[n] = 0;
    }
    for ( n = 2; n < 55; n = n + 4 )
    {
        k10[n] = 0;
    }
    for ( n = 2; n < 55; n = n + 4 )
    {
        k11[n] = 0;
    }
    for ( n = 2; n < 55; n = n + 4 )
    {
        k12[n] = 0;
    }
    for ( n = 2; n < 55; n = n + 4 )
    {
        k13[n] = 0;
    }
    for ( n = 2; n < 55; n = n + 4 )
    {
        k14[n] = 0;
    }
    for ( n = 2; n < 55; n = n + 4 )
    {
        k15[n] = 0;
    }
    for ( n = 2; n < 55; n = n + 4 )
    {
        k16[n] = 0;
    }

//collision table for LEVEL 1
    if ( lev == 1 )
    {
        for ( n = 2; n < 55; n = n + 4 )
        {
            k1[n] = 1;
        }
        for ( n = 2; n < 55; n = n + 4 )
        {
            k2[n] = 1;
        }
        for ( n = 2; n < 55; n = n + 4 )
        {
            k3[n] = 1;
        }
        for ( n = 2; n < 55; n = n + 4 )
        {
            k4[n] = 1;
        }
        for ( n = 2; n < 55; n = n + 4 )
        {
            k5[n] = 1;
        }
        for ( n = 2; n < 55; n = n + 4 )
        {
            k6[n] = 1;
        }
        for ( n = 2; n < 55; n = n + 4 )
        {
            k7[n] = 1;
        }
    }
    else
    {

//collision table for LEVEL 3
        if ( lev == 3 )
        {
            for ( n = 2; n < 55; n = n + 52 )
            {
                k1[n] = 1;
            }
            for ( n = 2; n < 11; n = n + 4 )
            {
                k2[n] = 1;
            }
            for ( n = 46; n < 55; n = n + 4 )
            {
                k2[n] = 1;
            }
            for ( n = 2; n < 15; n = n + 4 )
            {
                k3[n] = 1;
            }
            for ( n = 26; n < 31; n = n + 4 )
            {
                k3[n] = 2;
            }
            for ( n = 41; n < 55; n = n + 4 )
            {
                k3[n] = 1;
            }
            for ( n = 2; n < 15; n = n + 4 )
            {
                k4[n] = 1;
            }
            for ( n = 41; n < 55; n = n + 4 )
            {
                k4[n] = 1;
            }
            for ( n = 2; n < 15; n = n + 4 )
            {
                k5[n] = 1;
            }
            for ( n = 41; n < 55; n = n + 4 )
            {
                k5[n] = 1;
            }
            for ( n = 14; n < 43; n = n + 4 )
            {
                k6[n] = 1;
            }
            for ( n = 18; n < 39; n = n + 4 )
            {
                k7[n] = 1;
            }
            for ( n = 18; n < 39; n = n + 4 )
            {
                k8[n] = 1;
            }
            for ( n = 18; n < 39; n = n + 4 )
            {
                k9[n] = 1;
            }
            for ( n = 2; n < 55; n = n + 52 )
            {
                k11[n] = 2;
            }

        }
/*		else
		{
		}
*/
    }

    //clrscr();

    lcd_clr (  );
    interf (  );
    lcd_to_screen (  );


    //timet=diff + 1;
    cubes (  );
    do
    {
        key = 0;
        //if(kpd_getkey())
        //{
        show_score (  );
        //kpd_wait_keypress_x ( 100 );
        kpd_wait_keypress_x ( 1 );
        usleep ( diff );
        key = kpd_getkey (  );
        arcanoid (  );
        if ( key == 0x6 )
            arcx = arcx + 4;
        if ( key == 0x4 )
            arcx = arcx - 4;
        if ( arcx < 1 )
            arcx = 1;
        if ( arcx > 49 )
            arcx = 49;
        if ( key == KPD_CANCEL )
            break;
        //arcanoid();
        //}
        if ( kub == 98 )
            break;
        if ( ball (  ) )
        {
            live--;
            if ( live < 0 )
                break;
            else
            {
                x = 33;
                y = 39;
                vx = 1;
                vy = 1;
                arcx = 30;
            }
        }
//redraws unerased cubics and clears erased cubics
/*		for(n=2; n<55; n=n+4)
		{
		        if (k1[n]=0)
			    {
				i=n;
				h=1;
				kubic();
			    }
		        else
			    {
				i=n;
				h=1;
				kubic0();
			    }
			
		}
		for(n=2; n<55; n=n+4)
		{
		if (k2[n]=0)
		    {
		            i=n;
		            h=3;
		            kubic();
		    }
		    else
			{
		            i=n;
		            h=3;
		            kubic0();
			}
				
		}
		for(n=2; n<55; n=n+4)
		{
		if (k3[n]=0)
		    {
		            i=n;
		            h=5;
		            kubic();
		    }
		    else
		        {
		            i=n;
		            h=5;
		            kubic0();
			}
						
		}
		for(n=2; n<55; n=n+4)
		{
		if (k4[n]=0)
		    {
		            i=n;
		            h=7;
		            kubic();
		    }
		    else
		    {
		            i=n;
		            h=7;
		            kubic0();
		    }
						
		}
		for(n=2; n<55; n=n+4)
		{
		if (k5[n]=0)
		    {
		            i=n;
		            h=9;
		            kubic();
		    }
		    else
		    {
		            i=n;
		            h=9;
		            kubic0();
		    }
						
		} 
*/
//redraws interface     
        interf (  );
    }
    while ( 1 );

    if ( kub > 50 )
    {
        if ( kub > hsc )
        {
            lcd_render_text ( 3, 18, "HIGHSCORE", 1 );
            gameover_screen (  );
            return;
        }
        lcd_render_text ( 3, 18, "You win! :)", 1 );
        //printf("\n\nYou are winner! :)");
        gameover_screen (  );
        return;
    }
    lcd_render_text ( 3, 18, "Looser!", 1 );
    gameover_screen (  );

}


void
gameover_screen (  )
{
    lcd_render_text ( 3, 28, "Game Over", 1 );
    lcd_to_screen (  );
    marc_vibra (  );
    marc_vibra (  );
    marc_vibra (  );
    kpd_wait_keypress (  );
    x = 33;
    y = 39;
    vx = 1;
    vy = 1;
    arcx = 30;
    if ( kub > hsc )
        hsc = kub;
    else
        hsc = hsc;
    kub = 0;
    live = 3;
}
