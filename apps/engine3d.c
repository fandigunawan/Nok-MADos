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

 // atm i don't know, if i should made the source available for public :D
 // if anybody is interessted in developing 3D things i will do...

 // this source is build upon the tutorial at http://pages.infinit.net/jstlouis/3dbhole/ - thanks Jerome St-Louis!!!
 // i changed some things ;)

#include <hw/lcd.h>
//#include <core/ui.h>
//#include <hw/kpd.h>
#include <core/lib.h>
#include <core/softfloat.h>
/*
#define MAX_POLYGONS 20
#define MAX_VERTICES 300

typedef struct {
	float32 x, y, z;
} vertex_type;

typedef struct {
	unsigned int a, b, c;
} polygon_type;

typedef struct {
	vertex_type vertex[MAX_VERTICES];
	polygon_type polygon[MAX_POLYGONS];
} obj_type, *obj_type_ptr;

/*
#define MAX_POLYGONS 20
polygon_type polygon[MAX_POLYGONS];

#define MAX_VERTICES 300
vertex_type vertex[MAX_VERTICES];
*/
/*
void threeDee_main ( void ) {
	// let's draw some objects and maybe manipulate them. my dreams come true
	
	obj_type obj;
	
	obj.vertex[0].x=int32_to_float32 ( 0 );  obj.vertex[0].y=int32_to_float32 ( 0 );  obj.vertex[0].z=int32_to_float32 ( 0 ); //vertex v0
	obj.vertex[1].x=int32_to_float32 ( 1 );  obj.vertex[1].y=int32_to_float32 ( 0 );  obj.vertex[1].z=int32_to_float32 ( 0 ); //vertex v1
	obj.vertex[2].x=int32_to_float32 ( 1 );  obj.vertex[2].y=int32_to_float32 ( 0 );  obj.vertex[2].z=int32_to_float32 ( 1 ); //vertex v2
	obj.vertex[3].x=int32_to_float32 ( 0 );  obj.vertex[3].y=int32_to_float32 ( 0 );  obj.vertex[3].z=int32_to_float32 ( 1 ); //vertex v3
	obj.vertex[4].x=int32_to_float32 ( 0 );  obj.vertex[4].y=int32_to_float32 ( 1 );  obj.vertex[4].z=int32_to_float32 ( 0 ); //vertex v4
	obj.vertex[5].x=int32_to_float32 ( 1 );  obj.vertex[5].y=int32_to_float32 ( 1 );  obj.vertex[5].z=int32_to_float32 ( 0 ); //vertex v5
	obj.vertex[6].x=int32_to_float32 ( 1 );  obj.vertex[6].y=int32_to_float32 ( 1 );  obj.vertex[6].z=int32_to_float32 ( 1 ); //vertex v6
	obj.vertex[7].x=int32_to_float32 ( 0 );  obj.vertex[7].y=int32_to_float32 ( 1 );  obj.vertex[7].z=int32_to_float32 ( 1 ); //vertex v7
	
	obj.polygon[0].a=0;  obj.polygon[0].b=1;  obj.polygon[0].c=4;  //polygon v0,v1,v4
	obj.polygon[1].a=1;  obj.polygon[1].b=5;  obj.polygon[1].c=4;  //polygon v1,v5,v4
	obj.polygon[2].a=1;  obj.polygon[2].b=2;  obj.polygon[2].c=5;  //polygon v1,v2,v5
	obj.polygon[3].a=2;  obj.polygon[3].b=6;  obj.polygon[3].c=5;  //polygon v2,v6,v5
	obj.polygon[4].a=2;  obj.polygon[4].b=3;  obj.polygon[4].c=6;  //polygon v2,v3,v6
	obj.polygon[5].a=3;  obj.polygon[5].b=7;  obj.polygon[5].c=6;  //polygon v3,v7,v6
	obj.polygon[6].a=3;  obj.polygon[6].b=0;  obj.polygon[6].c=7;  //polygon v3,v0,v7
	obj.polygon[7].a=0;  obj.polygon[7].b=4;  obj.polygon[7].c=7;  //polygon v0,v4,v7
	obj.polygon[8].a=4;  obj.polygon[8].b=5;  obj.polygon[8].c=7;  //polygon v4,v5,v7
	obj.polygon[9].a=5;  obj.polygon[9].b=6;  obj.polygon[9].c=7;  //polygon v5,v6,v7
	obj.polygon[10].a=3; obj.polygon[10].b=2; obj.polygon[10].c=0; //polygon v3,v2,v0
	obj.polygon[11].a=2; obj.polygon[11].b=1; obj.polygon[11].c=0; //polygon v2,v1,v0
	return;

}
*/

#define SIN(x) SinTable[lib_abs((int)x&255)]
#define COS(x) CosTable[lib_abs((int)x&255)]
/*
#define SF_ONE int32_to_float32 ( 1 )
#define SF_ZERO int32_to_float32 ( 0 )
#define PI float32_div( int32_to_float32 ( 31415926 ), int32_to_float32 ( 10000000 ) )
*/

// softfloats in big endian
#define SF_ONE 0x3F800000
#define SF_ZERO 0x00000000
#define SF_42 0x42280000
#define SF_24 0x41C00000

#define FOCAL_DISTANCE 50

#define MaxPoint(a,b) ((a.y > b.y) ? a : b)
#define MinPoint(a,b) ((b.y > a.y) ? a : b)

#define MaxPoint3(a,b,c) MaxPoint(MaxPoint(a,b),MaxPoint(b,c))
// MidPoint3 doesn't work right. if a is the lowest of the three, than MidPoint will return a and that's wrong - i have to use something else :(
#define MidPoint3(a,b,c) MaxPoint(MinPoint(a,b),MinPoint(a,c))
#define MinPoint3(a,b,c) MinPoint(MinPoint(a,b),MinPoint(b,c))


typedef struct
{
    short x, y;
} _2D;

typedef struct
{
    float32 x, y, z;
} _3D;

typedef struct
{
    _3D Local;
    _3D World;
    _3D Aligned;
    _2D Screen;                 //added for projection
} Vertex_t;

typedef struct
{
    _2D Points[20];
    int PointsCount;
    int Texture;
} Polygon2D_t;

typedef struct
{
    int Count;
    int *Vertex;
    int Texture;

    Vertex_t P, M, N;
} Polygon_t;

typedef struct
{
    int VertexCount;
    int PolygonCount;
    Vertex_t *Vertex;
    Polygon_t *Polygon;
    _3D Scaling;
    _3D Position;
    _3D Angle;
    int NeedUpdate;
} Object_t;

typedef struct
{
    int Count;
    _3D Vertex[20];
} CPolygon_t;


float32 mat1[4][4], mat2[4][4];
float32 SinTable[256], CosTable[256];

void
MAT_Copy ( float32 source[4][4], float32 dest[4][4] )
{
    int i, j;
    for ( i = 0; i < 4; i++ )
        for ( j = 0; j < 4; j++ )
            dest[i][j] = source[i][j];
}

void
MAT_Mult ( float32 mat1[4][4], float32 mat2[4][4], float32 dest[4][4] )
{
    int i, j;
    for ( i = 0; i < 4; i++ )
        for ( j = 0; j < 4; j++ )
            /*
             * dest[i][j]=mat1[i][0]*mat2[0][j]+
             * mat1[i][1]*mat2[1][j]+
             * mat1[i][2]*mat2[2][j]+
             * mat1[i][3]*mat2[3][j];
             */
            dest[i][j] =
                float32_add ( float32_mul ( mat1[i][0], mat2[0][j] ),
                              float32_add ( float32_mul ( mat1[i][1], mat2[1][j] ), float32_add ( float32_mul ( mat1[i][2], mat2[2][j] ), float32_mul ( mat1[i][3], mat2[3][j] ) ) ) );
}

void
VEC_MultMatrix ( _3D * Source, float32 mat[4][4], _3D * Dest )
{
    /*
     * Dest->x=Source->x*mat[0][0]+
     * Source->y*mat[1][0]+
     * Source->z*mat[2][0]+
     * mat[3][0];
     */
    Dest->x = float32_add ( float32_mul ( Source->x, mat[0][0] ), float32_add ( float32_mul ( Source->y, mat[1][0] ), float32_add ( float32_mul ( Source->z, mat[2][0] ), mat[3][0] ) ) );
    /*
     * Dest->y=Source->x*mat[0][1]+
     * Source->y*mat[1][1]+
     * Source->z*mat[2][1]+
     * mat[3][1];
     */
    Dest->x = float32_add ( float32_mul ( Source->x, mat[0][1] ), float32_add ( float32_mul ( Source->y, mat[1][1] ), float32_add ( float32_mul ( Source->z, mat[2][1] ), mat[3][1] ) ) );
    /*
     * Dest->z=Source->x*mat[0][2]+
     * Source->y*mat[1][2]+
     * Source->z*mat[2][2]+
     * mat[3][2];
     */
    Dest->x = float32_add ( float32_mul ( Source->x, mat[0][2] ), float32_add ( float32_mul ( Source->y, mat[1][2] ), float32_add ( float32_mul ( Source->z, mat[2][2] ), mat[3][2] ) ) );
}

void
M3D_Init (  )
{
    int d;
    for ( d = 0; d < 256; d++ )
    {
        //hmmm i think i have to use also softfloat here - hehe jep
        //also PI must be defined as a constant!!!! - done (?!), maybe ;)
        /*
         * SinTable[d]=sin(d*PI/128.0);
         * CosTable[d]=cos(d*PI/128.0);
         */
        SinTable[d] = sine ( float32_div ( float32_mul ( int32_to_float32 ( d ), PI ), int32_to_float32 ( 128 ) ) );
        CosTable[d] = cosine ( float32_div ( float32_mul ( int32_to_float32 ( d ), PI ), int32_to_float32 ( 128 ) ) );
    }
}

void
MAT_Identity ( float32 mat[4][4] )
{
    mat[0][0] = SF_ONE;
    mat[0][1] = SF_ZERO;
    mat[0][2] = SF_ZERO;
    mat[0][3] = SF_ZERO;
    mat[1][0] = SF_ZERO;
    mat[1][1] = SF_ONE;
    mat[1][2] = SF_ZERO;
    mat[1][3] = SF_ZERO;
    mat[2][0] = SF_ZERO;
    mat[2][1] = SF_ZERO;
    mat[2][2] = SF_ONE;
    mat[2][3] = SF_ZERO;
    mat[3][0] = SF_ZERO;
    mat[3][1] = SF_ZERO;
    mat[3][2] = SF_ZERO;
    mat[3][3] = SF_ONE;
}

void
TR_Translate ( float32 matrix[4][4], float32 tx, float32 ty, float32 tz )
{
    float32 tmat[4][4];
    tmat[0][0] = SF_ONE;
    tmat[0][1] = SF_ZERO;
    tmat[0][2] = SF_ZERO;
    tmat[0][3] = SF_ZERO;
    tmat[1][0] = SF_ZERO;
    tmat[1][1] = SF_ONE;
    tmat[1][2] = SF_ZERO;
    tmat[1][3] = SF_ZERO;
    tmat[2][0] = SF_ZERO;
    tmat[2][1] = SF_ZERO;
    tmat[2][2] = SF_ONE;
    tmat[2][3] = SF_ZERO;
    tmat[3][0] = tx;
    tmat[3][1] = ty;
    tmat[3][2] = tz;
    tmat[3][3] = SF_ONE;
    MAT_Mult ( matrix, tmat, mat1 );
    MAT_Copy ( mat1, matrix );
}

void
TR_Scale ( float32 matrix[4][4], float32 sx, float32 sy, float32 sz )
{
    float32 smat[4][4];
    smat[0][0] = sx;
    smat[0][1] = SF_ZERO;
    smat[0][2] = SF_ZERO;
    smat[0][3] = SF_ZERO;
    smat[1][0] = SF_ZERO;
    smat[1][1] = sy;
    smat[1][2] = SF_ZERO;
    smat[1][3] = SF_ZERO;
    smat[2][0] = SF_ZERO;
    smat[2][1] = SF_ZERO;
    smat[2][2] = sz;
    smat[2][3] = SF_ZERO;
    smat[3][0] = SF_ZERO;
    smat[3][1] = SF_ZERO;
    smat[3][2] = SF_ZERO;
    smat[3][3] = SF_ONE;
    MAT_Mult ( matrix, smat, mat1 );
    MAT_Copy ( mat1, matrix );
}

void
TR_Rotate ( float32 matrix[4][4], int ax, int ay, int az )
{
    float32 xmat[4][4], ymat[4][4], zmat[4][4];
    xmat[0][0] = SF_ONE;
    xmat[0][1] = SF_ZERO;
    xmat[0][2] = SF_ZERO;
    xmat[0][3] = SF_ZERO;
    xmat[1][0] = SF_ZERO;
    xmat[1][1] = COS ( ax );
    xmat[1][2] = SIN ( ax );
    xmat[1][3] = SF_ZERO;
    xmat[2][0] = SF_ZERO;
    xmat[2][1] = float32_mul ( int32_to_float32 ( -1 ), SIN ( ax ) );
    xmat[2][2] = COS ( ax );
    xmat[2][3] = SF_ZERO;
    xmat[3][0] = SF_ZERO;
    xmat[3][1] = SF_ZERO;
    xmat[3][2] = SF_ZERO;
    xmat[3][3] = SF_ONE;

    ymat[0][0] = COS ( ay );
    ymat[0][1] = SF_ZERO;
    ymat[0][2] = float32_mul ( int32_to_float32 ( -1 ), SIN ( ay ) );
    ymat[0][3] = SF_ZERO;
    ymat[1][0] = SF_ZERO;
    ymat[1][1] = SF_ONE;
    ymat[1][2] = SF_ZERO;
    ymat[1][3] = SF_ZERO;
    ymat[2][0] = SIN ( ay );
    ymat[2][1] = SF_ZERO;
    ymat[2][2] = COS ( ay );
    ymat[2][3] = SF_ZERO;
    ymat[3][0] = SF_ZERO;
    ymat[3][1] = SF_ZERO;
    ymat[3][2] = SF_ZERO;
    ymat[3][3] = SF_ONE;

    zmat[0][0] = COS ( az );
    zmat[0][1] = SIN ( az );
    zmat[0][2] = SF_ZERO;
    zmat[0][3] = SF_ZERO;
    zmat[1][0] = float32_mul ( int32_to_float32 ( -1 ), SIN ( az ) );
    zmat[1][1] = COS ( az );
    zmat[1][2] = SF_ZERO;
    zmat[1][3] = SF_ZERO;
    zmat[2][0] = SF_ZERO;
    zmat[2][1] = SF_ZERO;
    zmat[2][2] = SF_ONE;
    zmat[2][3] = SF_ZERO;
    zmat[3][0] = SF_ZERO;
    zmat[3][1] = SF_ZERO;
    zmat[3][2] = SF_ZERO;
    zmat[3][3] = SF_ONE;

    MAT_Mult ( matrix, ymat, mat1 );
    MAT_Mult ( mat1, xmat, mat2 );
    MAT_Mult ( mat2, zmat, matrix );
}

void
Project ( Vertex_t * Vertex )
{

    if (  /*float32_eq ( */ !Vertex->Aligned.z /*, SF_ZERO) */  )   //should work without anything :)
        Vertex->Aligned.z = SF_ONE;
    //don't have a Screen in Vertex :( added it
    /*
     * Vertex->Screen.x = FOCAL_DISTANCE * Vertex->Aligned.x / Vertex->Aligned.z + 42;
     * Vertex->Screen.y = FOCAL_DISTANCE * Vertex->Aligned.y / Vertex->Aligned.z + 24;
     */
    Vertex->Screen.x = float32_add ( float32_div ( float32_mul ( int32_to_float32 ( FOCAL_DISTANCE ), Vertex->Aligned.x ), Vertex->Aligned.z ), SF_42 );    //42 could be replaced with const float
    Vertex->Screen.y = float32_add ( float32_div ( float32_mul ( int32_to_float32 ( FOCAL_DISTANCE ), Vertex->Aligned.y ), Vertex->Aligned.z ), SF_24 );    //24 also ... ok trying it
}


void
VID_HLine ( int x1, int x2, int y, char c )
{
    int x;
    for ( x = x1; x <= x2; x++ )
        lcd_set_pixel ( x, y, c );
}


void
POLY_Triangle ( _2D p1, _2D p2, _2D p3, char c )
{
// the comments are from the tutorial - i leave them just for understanding and maybe add some comments
    _2D p1d, p2d, p3d;
    int xd1, yd1, xd2, yd2, i;
    int Lx, Rx;

    // And we will do a first sorting of our 3 points: (tut)

    p1d = MinPoint3 ( p1, p2, p3 );
    p2d = MidPoint3 ( p2, p3, p1 );
    p3d = MaxPoint3 ( p3, p1, p2 );

    // Why is there a rotation of the points when calling these macros? I'll tell you I'm not sure myself, but it probably has something to do with the fact that points are passed counter-clockwise. Try to change the macro and you will see junk on your screen! Now, we're not sure about our MidPoint, so we do a little check, and when we're in this condition, it seems that the MinPoint can be wrong, so we correct that too: (tut)
    // example (where MidPoint3 doesn't work) at definition above

    if ( p2.y < p1.y )
    {
        p1d = MinPoint3 ( p2, p1, p3 );
        p2d = MidPoint3 ( p1, p3, p2 );
    }

    // I know these orders seem strange, but just try to change them and everything turns to garbage so either try to understand them (and then please mail me your conclusion so I can add it here), or accept them the way they are. Anyway, now we must compute the deltas: (tut)

    xd1 = p2d.x - p1d.x;
    yd1 = p2d.y - p1d.y;
    xd2 = p3d.x - p1d.x;
    yd2 = p3d.y - p1d.y;

    //Ok, here is the first side, that we only bother to draw if there is a delta y: (tut)

    if ( yd1 )
        for ( i = p1d.y; i <= p2d.y; i++ )
        {

            // We compute the x values with the starting x coordinate, adding the delta y between the current point and our starting point, multiplied by the inverse of the slope ( x / y ). (tut)

            Lx = p1d.x + ( ( i - p1d.y ) * xd1 ) / yd1;
            Rx = p1d.x + ( ( i - p1d.y ) * xd2 ) / yd2;

            // If we are not on the same point, draw the horizontal run, passing the two points in order: (tut)

            if ( Lx != Rx )
                VID_HLine ( MIN ( Lx, Rx ), MAX ( Lx, Rx ), i, c );
            //here it's possible to use ower own line function (lcd_draw_line)
        }

    // Now we recompute the first deltas and do the second side: (tut)

    xd1 = p3d.x - p2d.x;
    yd1 = p3d.y - p2d.y;

    if ( yd1 )
        for ( i = p2d.y; i <= p3d.y; i++ )
        {
            Lx = p1d.x + ( ( i - p1d.y ) * xd2 ) / yd2;
            Rx = p2d.x + ( ( i - p2d.y ) * xd1 ) / yd1;
            if ( Lx != Rx )
                VID_HLine ( MIN ( Lx, Rx ), MAX ( Lx, Rx ), i, c );
        }
}


void
POLY_Draw ( Polygon2D_t * Polygon )
{
    _2D P1, P2, P3;
    int i;

    P1 = Polygon->Points[0];
    for ( i = 1; i < Polygon->PointsCount - 1; i++ )    //hmm < or <= ? //Polygon->PointsCount i think...
    {
        P2 = Polygon->Points[i];
        P3 = Polygon->Points[i + 1];
        POLY_Triangle ( P1, P2, P3, Polygon->Texture );
    }
}

void
M3D_Project ( CPolygon_t * Polygon, Polygon2D_t * Clipped, int focaldistance )
{
    int v;
    for ( v = 0; v < Polygon->Count; v++ )
    {
        /*
         * if(!Polygon->Vertex[v].z)
         * Polygon->Vertex[v].z = float32_add ( Polygon->Vertex[v]z, SF_ONE );
         *///hate if someone hates div by zero :D
        Clipped->Points[v].x = float32_add ( float32_div ( float32_mul ( Polygon->Vertex[v].x, int32_to_float32 ( FOCAL_DISTANCE ) ), Polygon->Vertex[v].z ), SF_42 );
        Clipped->Points[v].y = float32_add ( float32_div ( float32_mul ( Polygon->Vertex[v].y, int32_to_float32 ( FOCAL_DISTANCE ) ), Polygon->Vertex[v].z ), SF_24 );
    }
    Clipped->PointsCount = Polygon->Count;
}


typedef struct
{
    float32 x, y, z;
} simple_cube_point;

typedef struct
{
    unsigned int count;
    simple_cube_point point[10];
    float32 d, p, t;
} simple_cube_object;

//hmm, now i don't know what to do with all the stuff :D
//ok, first try a simple 3d cube wireframe without all that confusing vector, matrix and texture stuff
void
simple_cube_redraw ( simple_cube_object cube )
{
    unsigned int points;
    int xold, yold, xnew, ynew;
    float32 xe, ye, ze;
    float32 st = sine ( cube.t );
    float32 ct = cosine ( cube.t );
    float32 sp = sine ( cube.p );
    float32 cp = cosine ( cube.p );

    xe = float32_add ( float32_mul ( float32_mul ( int32_to_float32 ( -1 ), cube.point[0].x ), st ), float32_mul ( cube.point[0].y, ct ) );
    ye = float32_add ( float32_sub ( float32_mul ( float32_mul ( float32_mul ( int32_to_float32 ( -1 ), cube.point[0].x ), ct ), cp ), float32_mul ( float32_mul ( st, cp ), cube.point[0].y ) ),
                       float32_mul ( cube.point[0].z, sp ) );
    ze = float32_add ( float32_sub
                       ( float32_sub ( float32_mul ( float32_mul ( float32_mul ( int32_to_float32 ( -1 ), cube.point[0].x ), sp ), ct ), float32_mul ( float32_mul ( st, sp ), cube.point[0].y ) ),
                         float32_mul ( cube.point[0].z, cp ) ), int32_to_float32 ( 4 ) );
    // this could be very slow ;) but could be optized

    xold = float32_to_int32 ( float32_add ( float32_div ( float32_mul ( cube.d, xe ), ze ), float32_div ( int32_to_float32 ( 83 ), int32_to_float32 ( 2 ) ) ) );
    yold = float32_to_int32 ( float32_add ( float32_div ( float32_mul ( cube.d, ye ), ze ), float32_div ( int32_to_float32 ( 83 ), int32_to_float32 ( 2 ) ) ) );

    for ( points = 0; points < cube.count - 1; points++ )
    {
        xe = float32_add ( float32_mul ( float32_mul ( int32_to_float32 ( -1 ), cube.point[points].x ), st ), float32_mul ( cube.point[points].y, ct ) );
        ye = float32_add ( float32_sub
                           ( float32_mul ( float32_mul ( float32_mul ( int32_to_float32 ( -1 ), cube.point[points].x ), ct ), cp ), float32_mul ( float32_mul ( st, cp ), cube.point[points].y ) ),
                           float32_mul ( cube.point[points].z, sp ) );
        ze = float32_add ( float32_sub
                           ( float32_sub
                             ( float32_mul ( float32_mul ( float32_mul ( int32_to_float32 ( -1 ), cube.point[points].x ), sp ), ct ), float32_mul ( float32_mul ( st, sp ), cube.point[points].y ) ),
                             float32_mul ( cube.point[points].z, cp ) ), int32_to_float32 ( 4 ) );

        xnew = float32_to_int32 ( float32_add ( float32_div ( float32_mul ( cube.d, xe ), ze ), float32_div ( int32_to_float32 ( 83 ), int32_to_float32 ( 2 ) ) ) );
        ynew = float32_to_int32 ( float32_add ( float32_div ( float32_mul ( cube.d, ye ), ze ), float32_div ( int32_to_float32 ( 47 ), int32_to_float32 ( 2 ) ) ) );

        lcd_draw_line ( xold, yold, xnew, ynew, 1 );

        xold = xnew;
        yold = ynew;
    }
}


//and it has a bug :(
void
simple_cube_main ( void )       //huh, what's simple here ?
{
    int i;
    simple_cube_object cube;

    cube.count = 4;
    cube.point[0].x = int32_to_float32 ( 1 );
    cube.point[0].y = int32_to_float32 ( 1 );
    cube.point[0].z = int32_to_float32 ( 1 );
    cube.point[1].x = int32_to_float32 ( -1 );
    cube.point[1].y = int32_to_float32 ( 1 );
    cube.point[1].z = int32_to_float32 ( 1 );
    cube.point[2].x = int32_to_float32 ( -1 );
    cube.point[2].y = int32_to_float32 ( -1 );
    cube.point[2].z = int32_to_float32 ( 1 );
    cube.point[3].x = int32_to_float32 ( 1 );
    cube.point[3].y = int32_to_float32 ( -1 );
    cube.point[3].z = int32_to_float32 ( 1 );

    cube.d = int32_to_float32 ( 10 );
    cube.t = float32_div ( int32_to_float32 ( 7 ), int32_to_float32 ( 10 ) );   //0.7
    cube.p = float32_div ( int32_to_float32 ( 13 ), int32_to_float32 ( 10 ) );  //1.3

    for ( i = 0; ( i < 10000 ) && kpd_getkey (  ) == 0xFF; i++ )
    {
        lcd_clr (  );
        lcd_render_text ( 5, 5, "test", 1 );
        simple_cube_redraw ( cube );
        lcd_to_screen (  );
        usleep ( 10000 );
        cube.t = float32_add ( cube.t, float32_div ( SF_ONE, int32_to_float32 ( 100 ) ) );  //0.1
        lcd_clr (  );
        lcd_to_screen (  );
        usleep ( 10000 );
    }

}
