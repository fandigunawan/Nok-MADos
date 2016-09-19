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

#ifndef PC

typedef char *va_list;
typedef unsigned int size_t;
#define  _AUPBND         (sizeof (int) - 1)
#define  _ADNBND         (sizeof (int) - 1)
#define _bnd(X, bnd)    (((sizeof (X)) + (bnd)) & (~(bnd)))
#define va_arg(ap, T)   (*(T *)(((ap) += (_bnd (T, _AUPBND))) - (_bnd (T,_ADNBND))))
#define va_end(ap)      (void) 0
#define va_start(ap, A) (void) ((ap) = (((char *) &(A)) + (_bnd (A,_AUPBND))))
#define isdigit(c) ('0' <= (c) && (c)  <= '9')
#define do_div(n,base)                                                 \
({                                                                     \
        int __res;                                                     \
        __res = lib_mod ( ((unsigned long)n), (unsigned int)base );    \
        n = lib_div ( ((unsigned long)n), (unsigned int)base );        \
        __res;                                                         \
})

#define ZEROPAD 1               /* pad with zero */
#define SIGN    2               /* unsigned/signed long */
#define PLUS    4               /* show plus */
#define SPACE   8               /* space if plus */
#define LEFT    16              /* left justified */
#define SPECIAL 32              /* 0x */
#define LARGE   64              /* use 'ABCDEF' instead of 'abcdef' */

int vsnprintf ( char *buf, size_t size, const char *fmt, va_list args );
int sprintf ( char *__restrict buf, const char *__restrict format, ... );
static char *number ( char *buf, char *end, long long num, int base, int size, int precision, int type );
size_t strnlen ( const char *s, size_t count );
static int skip_atoi ( const char **s );

#endif
