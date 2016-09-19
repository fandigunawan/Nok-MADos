/*
 * 
 * MADos, a free OS for N* handsets  
 * Copyright (C) 2003/2004 MADos Core Developer Team  
 *
 * Written by g3gg0
 * Adapted to NokiX by [Yak] (c) 2005
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//
// g3gg0:  to debug it on PC
//
//#define DEBUG_SOLVER

#include "solver.h"

#ifdef DEBUG_SOLVER
int tmp = 0;
int tab_depth = 0;
#endif

/* string to double converting function from NokiaOS DCT3 */
RET_VALUE str2double (char *);

struct func_table_entry
{
  char *name;
    RET_VALUE (*function) (RET_VALUE);
};

static RET_VALUE
ctan (RET_VALUE x)
{
  return 1 / tan (x);
}

static RET_VALUE
actan (RET_VALUE x)
{
  return atan (1 / x);
}

#ifndef DEBUG_SOLVER
static RET_VALUE
abs (RET_VALUE x)
{
  return x < 0 ? -x : x;
}
#else
RET_VALUE
str2double (char s[])
{

  printf ("str2double: RET %d\n", atoi (s));
  return atoi (s);
}
#endif

static const struct func_table_entry func_table[] = {
  {"abs", abs},
  {"sqrt", sqrt},
  {"sin", sin},
  {"cos", cos},
  {"tan", tan},
  {"tg", tan},
  {"ctan", ctan},
  {"ctg", ctan},
  {"asin", asin},
  {"acos", acos},
  {"atan", atan},
  {"atg", atan},
  {"actan", actan},
  {"actg", actan},
  {"log", log10},
  {"ln", log},
  {NULL, NULL}
};

RET_VALUE
solver_get_var (char *var)
{
  return 0;
}


static char *
strtolower (char *str)
{
  int i;
  for (i = 0; str[i]; i++)
    str[i] = tolower (str[i]);
  return str;
}






static int
solver_get (char *formula, int *type, int *pos)
{
  int done = 0;
  unsigned char c = 0;

  *type = TYPE_UNK;
  *pos = 0;

  strtolower (formula);

  while (!done)
    {
      c = formula[*pos];

      if (!c)
	done = 1;
      else if (isdigit (c) || c == '.')	/* improved by [Yak] */
	{
	  if (*type == TYPE_UNK)
	    {
	      *type = TYPE_VAL;
	      (*pos)++;
	    }
	  else
	    {
	      if (*type == TYPE_VAL)
		(*pos)++;
	      else
		done = 1;
	    }
	}
      else if (c >= 'a' && c <= 'z')
	{
	  if (*type == TYPE_UNK)
	    {
	      *type = TYPE_VAR;
	      (*pos)++;
	    }
	  else
	    {
	      if (*type == TYPE_VAR)
		(*pos)++;
	      else
		done = 1;
	    }
	}
      else if (c == '*' || c == '/' || c == '+' || c == '-' || c == '\'')	/* changed by [Yak] */
	{
	  if (*type == TYPE_UNK)
	    {
	      *type = TYPE_OP;
	      (*pos)++;
	    }
	  done = 1;
	}
      else if (c == '(' || c == ')' || c == '{' || c == '}')
	{
	  if (*type == TYPE_UNK)
	    {
	      *type = TYPE_PAR;
	      (*pos)++;
	    }
	  done = 1;
	}
      else
	return 0;
    }

  if (*type == TYPE_VAR)
    {
      int i, l;

      for (i = 0; func_table[i].name; i++)
	{
	  l = strlen (func_table[i].name);
	  if (*pos == l && !strncmp (formula, func_table[i].name, l))
	    {
	      *type = TYPE_FUNC;
	      break;
	    }
	}
    }

  if (*type != TYPE_UNK && *pos)
    return 1;

  return 0;
}

int
free_tree (f_node * root)
{
  //static int depth = 0;
  f_oper *node_op = NULL;
  f_func *node_func = NULL;
  f_leaf_val *node_val = NULL;
  f_leaf_var *node_var = NULL;
  f_leaf_txt *node_txt = NULL;
  int done = 0;
  int pos = 0;

  switch (root->type)
    {
    case TYPE_FUNC:
      node_func = (f_func *) root;
      if (node_func->func)
	free (node_func->func);
      //
      // !!!!fall-through here to free subnodes!!!!       
      //
    case TYPE_OP:
      node_op = (f_oper *) root;
      for (pos = 0; pos < node_op->num_leaves; pos++)
	{
	  //TABI;
	  free_tree (node_op->leaves[pos]);
	  //TABD;
	}
      free (node_op->leaves);
      break;
    case TYPE_VAR:		// this ans TYPE_TXT are the same
//            node_var = ( f_leaf_var * ) root;
//            free ( node_var->val );
//            break;
//        case TYPE_VAL:
//            node_val = ( f_leaf_val * ) root;
//            break;
    case TYPE_TXT:
      node_txt = (f_leaf_txt *) root;
      free (node_txt->val);
      break;
    }
  free (root);
  return 1;
}

RET_VALUE
calc_tree (f_node * root)
{
  //static int depth = 0;
  f_func *node_func = NULL;
  f_oper *node_op = NULL;
  int done = 0;
  int pos = 0;
  RET_VALUE sum = 0;
  RET_VALUE ret = 0;

  switch (root->type)
    {
    case TYPE_FUNC:
      node_func = (f_func *) root;
      ret = calc_tree (node_func->leaves[0]);
      if (isnan (ret) || isinf (ret))	/* fixed by [Yak] */
	return ret;
      printf ("%s (%i)", node_func->func, ret);

      //
      //  TODO: Function handlers (sin, cos, etc)
      //
      strtolower (node_func->func);

      {
	int i;

	for (i = 0; func_table[i].name; i++)
	  {
	    if (!strcmp (node_func->func, func_table[i].name))
	      return func_table[i].function (ret);
	  }
//        return 0;
      }

      break;
    case TYPE_OP:
      node_op = (f_oper *) root;

      DEB (TAB;
	   printf ("(");
	);
      for (pos = 0; pos < node_op->num_leaves; pos++)
	{
	  ret = calc_tree (node_op->leaves[pos]);
	  if (isnan (ret) || isinf (ret))	/* fixed by [Yak] */
	    return ret;
	  switch (node_op->op)
	    {
	    case '+':
	      if (pos == 0)
		sum = 0;
	      if (((f_node *) node_op->leaves[pos])->reverse)
		{
		  DEB (TAB;
		       printf ("-%i", ret);
		    );
		  sum -= ret;
		}
	      else
		{
		  DEB (TAB;
		       if (pos) printf ("+"); printf ("+%i", ret););
		  sum += ret;
		}
	      break;
	    case '*':
	      if (pos == 0)
		sum = 1;
	      if (((f_node *) node_op->leaves[pos])->reverse)
		{
		  DEB (TAB;
		       printf ("/%i", ret);
		    );
		  if (ret == 0)
		    return NAN;
		  sum /= ret;
		}
	      else
		{
		  DEB (TAB;
		       if (pos) printf ("*"); printf ("%i", ret););
		  sum *= ret;
		}
	      break;
	    case '\'':		/* (we don't have '^' on nokia) changed by [Yak] */
	      if (pos == 0)
		sum = ret;
	      if (pos == 1)
		{
		  DEB (TAB;
		       printf ("%i^%i", sum, ret);
		    );
		  sum = pow (sum, ret);	/* simplified by [Yak] */
		}
	      break;
	    default:
	      break;
	    }
	}
      DEB (TAB;
	   printf (")");
	);
      return sum;
      break;
    case TYPE_VAR:
      {
	return solver_get_var (((f_leaf_var *) root)->val);
	break;
      }
    case TYPE_VAL:
      return ((f_leaf_val *) root)->val;
      break;
    case TYPE_TXT:
      printf ("ERROR: Trying to resolve TEXT '%s'....\n",
	      ((f_leaf_txt *) root)->val);
      return NAN;
      break;
    default:
      break;
    }
  return NAN;
}

static int
solver_extend (f_oper * node_op, unsigned char *text, int length, int reverse)
{
  //unsigned char buffer[128];

  //memset ( buffer, 0x00, 128 );

  if ((text[0] == '(' || text[0] == '{' || text[0] == '[')
      && (text[length - 1] == ')' || text[length - 1] == '}'
	  || text[length - 1] == ']'))
    {
      //DEB ( printf ( "----------------- STRIPPED PARENTHESIS ------------\n" );
      //     );
      text++;
      length--;
      length--;
    }
  //strncpy ( buffer, text, length );

  if (node_op->num_leaves == 0)
    node_op->leaves = malloc ((node_op->num_leaves + 1) * sizeof (void *));
  else
    node_op->leaves =
      realloc (node_op->leaves, (node_op->num_leaves + 1) * sizeof (void *));

  {
    f_leaf_txt *node = malloc (sizeof (f_node));

    node->val = malloc (length + 1);
    strncpy (node->val, text, length);
    node->val[length] = '\0';
    node->type = TYPE_TXT;
    node->reverse = reverse;

    node_op->leaves[node_op->num_leaves] = node;
    node_op->num_leaves++;
  }
}

int
solver_parse (f_node * root)
{
// break up the function first in '-' operands, then '+' '*' '/'
  static int depth = 0;

  int done = 0;
  int type = TYPE_UNK;
  int last_type = TYPE_UNK;
  int pars = 0;
  int len = 0;
  int pos = 0;
  int cur = 0;
  int op = 0;
  int found = 0;
  int reverse_op = 0;
  f_oper *node_op = NULL;
  //f_node *node = NULL;
  unsigned char buffer[128];
  unsigned char operand_1[] = "+*'";
  unsigned char operand_2[] = "-/'";
  unsigned char *ptr = NULL;
  unsigned char *formula = NULL;
  unsigned char current = 0;

  if (root->type != TYPE_TXT)
    {
      // nothing to do here
      return 1;
    }
  formula = ((f_leaf_txt *) root)->val;
  node_op = malloc (sizeof (f_node));
  node_op->type = TYPE_UNK;
  node_op->num_leaves = 0;

restart:



  done = 0;
  type = TYPE_UNK;
  last_type = TYPE_UNK;
  pars = 0;
  len = 0;
  pos = 0;
  cur = 0;
  op = 0;
  found = 0;
  reverse_op = 0;

  //
  //  preparse  (check for correct bracket amount)
  //
  len = strlen (formula);
  for (pos = 0; pos < len; pos++)
    {
      switch (formula[pos])
	{
	case '(':
	case '{':
	case '[':
	  pars++;
	  break;
	case ')':
	case '}':
	case ']':
	  pars--;
	  break;
	default:
	  break;
	}
    }
  if (pars != 0)
    {
      DEB (printf ("ERROR: bracket count doesnt fit!\n");) return 0;
    }

  pos = 0;
  len = 0;

  while (!done)
    {
      DEB (TAB;
	   printf (" - looking for '%c %c' in '%s'\n", operand_1[op],
		   operand_2[op], formula + cur + pos);
	);
      if (solver_get (formula + pos + cur, &type, &len))
	{
	  current = formula[pos + cur];

	  if ((last_type == TYPE_PAR || last_type == TYPE_VAR
	       || last_type == TYPE_VAL) && (type == TYPE_PAR
					     || type == TYPE_VAR
					     || type == TYPE_VAL))
	    {
	      type = TYPE_OP;
	      len = 0;
	      current = '*';
	      DEB (TAB;
		   printf (" - inserting a '*'\n");
		);
	    }

	  if (type == TYPE_PAR)
	    {
	      switch (formula[pos + cur])
		{
		case '(':
		case '{':
		case '[':
		  pars++;
		  break;
		case ')':
		case '}':
		case ']':
		  pars--;
		  break;
		default:
		  break;
		}
	    }

	  if (type == TYPE_OP && !pars)
	    {
	      if (current == operand_1[op] || current == operand_2[op])
		{
		  found = 1;
		  DEB (TAB;
		       printf (" - found at pos %i\n", cur);
		    );
		  node_op->type = TYPE_OP;
		  node_op->op = operand_1[op];
		  node_op->reverse = ((f_leaf_txt *) root)->reverse;
		  // split here
		  if (cur)
		    solver_extend (node_op, formula + pos, cur, reverse_op);
		  DEB (TAB;
		       printf (" - new subnode '%s'\n", formula + pos);
		    );
		  if (last_type == TYPE_OP)
		    reverse_op ^= (current == operand_1[op]) ? 0 : 1;
		  else
		    reverse_op = (current == operand_1[op]) ? 0 : 1;
		  DEB (TAB; if (reverse_op) printf ("   reverse\n"););


		  // recurse here...
		  TABI;
		  if (cur)
		    solver_parse (node_op->leaves[node_op->num_leaves - 1]);
		  TABD;
		  pos += cur + len;
		  cur = 0;
		  len = 0;
		}
	    }
	  last_type = type;
	  cur += len;
	}
      else
	{
	  if (found)
	    {
	      DEB (TAB;
		   printf (" - last subnode '%s'\n", formula + pos);
		);
	      solver_extend (node_op, formula + pos, strlen (formula + pos),
			     reverse_op);
	      // recurse here...
	      TABI;
	      solver_parse (node_op->leaves[node_op->num_leaves - 1]);
	      TABD;

	      memcpy (root, node_op, sizeof (f_node));
	      //free ( node_op );
	      //node_op = NULL;
	      done = 1;
	    }
	  else
	    {
	      last_type = TYPE_UNK;
	      pos = 0;
	      cur = 0;
	      op++;
	      if (!operand_1[op])
		{
		  // here theres no operand anymore, free unused operand
		  //free ( node_op );
		  DEB (TAB;
		       printf ("END-leaf: '%s'\n", formula);
		    );
		  if (solver_get (formula, &type, &len))
		    {
		      switch (type)
			{
			case TYPE_VAR:
			  //node = malloc ( sizeof ( f_node ) );
			  ((f_leaf_var *) root)->type = TYPE_VAR;
			  ((f_leaf_var *) root)->val = strdup (formula);
			  //( ( f_leaf_var * ) node )->reverse = ( ( f_leaf_var * ) root )->reverse;
			  //memcpy ( root, node, sizeof ( f_node ) );
			  //free ( node );
			  //node = NULL;
			  break;
			case TYPE_VAL:
			  //node = malloc ( sizeof ( f_node ) );
			  ((f_leaf_val *) root)->type = TYPE_VAL;
			  //( ( f_leaf_val * ) node )->reverse = ( ( f_leaf_val * ) root )->reverse;
			  //sscanf ( formula, "%i", &( ( f_leaf_var * ) node )->val );
			  ((f_leaf_val *) root)->val = str2double (formula);	// Nokia specific! by [Yak]
			  //memcpy ( root, node, sizeof ( f_node ) );
			  //free ( node );
			  //node = NULL;
			  break;
			case TYPE_FUNC:
			  //node = malloc ( sizeof ( f_node ) );
			  ((f_func *) root)->type = TYPE_FUNC;
			  //( ( f_func * ) node )->reverse = ( ( f_func * ) root )->reverse;
			  ((f_func *) root)->num_leaves = 0;
			  //memset ( buffer, 0x00, 128 );
			  ptr = strrchr (formula, ')');
			  if (!ptr)
			    break;
			  ptr[0] = '\000';
			  ptr = strchr (formula, '(');
			  if (!ptr)
			    break;
			  ptr[0] = '\000';
			  ptr++;
			  //sscanf ( formula, "%s", buffer );
			  /* we can replace it with strcpy() since in formula there is always single string ??? */
			  //strcpy(buffer,formula);
			  ((f_func *) root)->func = strdup (formula);
			  //memcpy ( root, node, sizeof ( f_node ) );
			  //free ( node );

			  solver_extend (((f_oper *) root), ptr, strlen (ptr),
					 0);
			  // recurse here...
			  TABI;
			  solver_parse (((f_func *) root)->leaves[0]);
			  TABD;
			  //node = NULL;
			  break;
			default:
			  DEB (TAB;
			       printf (" # its a text\n");
			    );
			  if (formula[0] == '(' || formula[0] == '{' ||
			      formula[0] == '[')
			    {
			      int tmp_len = 0;
			      tmp_len = strlen (formula);
			      if (formula[tmp_len - 1] == ')' ||
				  formula[tmp_len - 1] == '}' ||
				  formula[tmp_len - 1] == ']')
				{
				  formula[tmp_len - 1] = '\000';
				  memcpy (formula, formula + 1, tmp_len - 2);
				  formula[tmp_len - 2] = '\000';
				  goto restart;
				}
			    }
			  break;
			}
		    }
		  done = 1;
		}
	      DEB (TAB;
		   printf (" * trying next operand '%c %c'\n", operand_1[op],
			   operand_2[op]);
		);
	    }
	}
    }

  free (node_op);
  free (formula);
  return 1;
}


f_node *
solver_create (char *formula)
{
  f_leaf_txt *root;

  root = malloc (sizeof (f_node));
  root->type = TYPE_TXT;
  root->reverse = 0;
  root->val = strdup (formula);

  return root;
}




#ifdef DEBUG_SOLVER
int
dump_tree (f_node * root, unsigned char op, int num)
{
  static int depth = 0;
  f_oper *node_op = NULL;
  f_func *node_func = NULL;
  f_leaf_val *node_val = NULL;
  f_leaf_var *node_var = NULL;
  f_leaf_txt *node_txt = NULL;
  int done = 0;
  int pos = 0;

  switch (root->type)
    {
    case TYPE_OP:
      node_op = (f_oper *) root;
      TAB;
      printf ("Type:\tOPERATION\n", node_op->type);
      TAB;
      printf ("Rev:\t%i\n", node_op->reverse);
      TAB;
      printf ("OP:\t%c\n", node_op->op);
      TAB;
      printf ("num_l:\t%i\n", node_op->num_leaves);
      TAB;
      printf ("------------------------------\n");
      for (pos = 0; pos < node_op->num_leaves; pos++)
	{
	  TABI;
	  dump_tree (node_op->leaves[pos], node_op->op, pos);
	  TABD;
	}
      break;
    case TYPE_VAR:
      node_var = (f_leaf_var *) root;
      TAB;
      printf ("Type:\tVARIABLE\n", node_var->type);
      TAB;
      printf ("Rev:\t%i\n", node_var->reverse);
      TAB;
      printf ("Val:\t%s\n", node_var->val);
      TAB;
      printf ("------------------------------\n");
      break;
    case TYPE_VAL:
      node_val = (f_leaf_val *) root;
      TAB;
      printf ("Type:\tVALUE\n", node_val->type);
      TAB;
      printf ("Rev:\t%i\n", node_val->reverse);
      TAB;
      printf ("Val:\t%i\n", node_val->val);
      TAB;
      printf ("------------------------------\n");
      break;
    case TYPE_TXT:
      node_txt = (f_leaf_txt *) root;
      TAB;
      printf ("Type:\tTEXT\n", node_txt->type);
      TAB;
      printf ("Rev:\t%i\n", node_txt->reverse);
      TAB;
      printf ("Val:\t%s\n", node_txt->val);
      TAB;
      printf ("------------------------------\n");
      break;
    case TYPE_FUNC:
      node_func = (f_func *) root;
      TAB;
      printf ("Type:\tFUNCTION\n", node_func->type);
      TAB;
      printf ("Rev:\t%i\n", node_func->reverse);
      TAB;
      printf ("Func:\t%s\n", node_func->func);
      TAB;
      printf ("num_l:\t%i\n", node_func->num_leaves);
      TAB;
      printf ("------------------------------\n");
      TABI;
      dump_tree (node_func->leaves[0], '+', pos);
      TABD;
      break;
    default:
      break;
    }
  return 1;
}


int
show_tree (f_node * root, unsigned char op, int num)
{
  static int depth = 0;
  f_oper *node_op = NULL;
  f_func *node_func = NULL;
  int done = 0;
  int pos = 0;
  int sum = 0;

  switch (root->type)
    {
    case TYPE_OP:
      node_op = (f_oper *) root;

      if (((f_node *) root)->reverse)
	{
	  if (op == '+')
	    op = '-';
	  if (op == '*')
	    op = '/';
	}
      if (((f_node *) root)->reverse || num)
	printf ("%c", op);
      if (depth)
	printf ("(");
      for (pos = 0; pos < node_op->num_leaves; pos++)
	{
	  TABI;
	  show_tree (node_op->leaves[pos], node_op->op, pos);
	  TABD;
	}
      if (depth)
	printf (")");
      return sum;
      break;
    case TYPE_VAR:
      if (((f_node *) root)->reverse)
	{
	  if (op == '+')
	    op = '-';
	  if (op == '*')
	    op = '/';
	}
      if (((f_node *) root)->reverse || num)
	printf ("%c", op);
      printf ("%s", ((f_leaf_var *) root)->val);
      break;
    case TYPE_VAL:
      if (((f_node *) root)->reverse)
	{
	  if (op == '+')
	    op = '-';
	  if (op == '*')
	    op = '/';
	}
      if (((f_node *) root)->reverse || num)
	printf ("%c", op);
      printf ("%i", ((f_leaf_val *) root)->val);
      break;
    case TYPE_FUNC:
      node_func = (f_oper *) root;

      if (node_func->reverse)
	{
	  if (op == '+')
	    op = '-';
	  if (op == '*')
	    op = '/';
	}
      if (node_func->reverse || num)
	printf ("%c", op);

      printf ("%s", node_func->func);
      printf ("(");
      for (pos = 0; pos < node_func->num_leaves; pos++)
	{
	  TABI;
	  show_tree (node_func->leaves[pos], '+', pos);
	  TABD;
	}
      printf (")");
      break;
    case TYPE_TXT:
      if (((f_node *) root)->reverse)
	{
	  if (op == '+')
	    op = '-';
	  if (op == '*')
	    op = '/';
	}
      if (((f_node *) root)->reverse || num)
	printf ("%c", op);
      printf ("%s", ((f_leaf_txt *) root)->val);
      return -1;
      break;
    default:
      break;
    }
  return 1;
}


int
main (int argc, unsigned char argv[])
{
  RET_VALUE val = 0;
  f_node *tree = NULL;

//  tree = malloc (sizeof (f_node));
//  ((f_leaf_txt *) tree)->type = TYPE_TXT;
  //    ( ( f_leaf_txt * ) tree )->val = "1-4-2+(4+6)*2+4/4*3";
  //    ( ( f_leaf_txt * ) tree )->val = "2-1+20-2-3-5-2+3+4-4-3+3-3+3-3+5-3+5
  //    ( ( f_leaf_txt * ) tree )->val = "2+2+2+2+2+2+2-7-7";
  //    ( ( f_leaf_txt * ) tree )->val = "12x^2+16x+20";
  //    ( ( f_leaf_txt * ) tree )->val = "12x^3+1238x+322-32x^2+16x+202-1+20-2
  //    ( ( f_leaf_txt * ) tree )->val = "-12+(2--2)";
  //((f_leaf_txt *) tree)->val = "(2*2)";
  tree = solver_create ("((((((((((2+4))))))))))");

  printf ("    // dump just that one text entry\n");
  dump_tree (tree, '+', 0);
  printf ("\n");
  printf ("\n");

  printf ("    // parse the whole term    \n");
  solver_parse (tree);
  printf ("\n");
  printf ("\n");

  printf ("    // show the algebraic content of the tree\n");
  show_tree (tree, '+', 0);
  printf ("\n");
  printf ("\n");

  printf ("    // dump all the objects in the tree\n");
  dump_tree (tree, '+', 0);
  printf ("\n");
  printf ("\n");

  printf
    ("    // output the result (the term output is just crap for tracing purposes\n");
  val = calc_tree (tree);
  if (val == NAN)
    printf ("\n\nError parsing function\n");
  else
    printf ("\n\n => Result: %02d\n", val);
  printf ("\n");

  free_tree (tree);
  return 0;
}
#endif // DEBUG_SOLVER
