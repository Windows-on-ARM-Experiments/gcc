/* do not edit automatically generated by mc from SymbolKey.  */
/* SymbolKey.mod binary tree operations for storing symbols.

Copyright (C) 2001-2023 Free Software Foundation, Inc.
Contributed by Gaius Mulley <gaius.mulley@southwales.ac.uk>.

This file is part of GNU Modula-2.

GNU Modula-2 is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GNU Modula-2 is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Modula-2; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   if !defined (FALSE)
#      define FALSE (1==0)
#   endif

#include <stddef.h>
#   include "GStorage.h"
#if defined(__cplusplus)
#   undef NULL
#   define NULL 0
#endif
#define _SymbolKey_H
#define _SymbolKey_C

#   include "GStorage.h"
#   include "GStrIO.h"
#   include "GNumberIO.h"
#   include "GNameKey.h"
#   include "GAssertion.h"
#   include "GDebug.h"

#   define SymbolKey_NulKey 0
typedef struct SymbolKey_IsSymbol_p SymbolKey_IsSymbol;

typedef struct SymbolKey_PerformOperation_p SymbolKey_PerformOperation;

typedef struct SymbolKey_Node_r SymbolKey_Node;

typedef SymbolKey_Node *SymbolKey_SymbolTree;

typedef unsigned int (*SymbolKey_IsSymbol_t) (unsigned int);
struct SymbolKey_IsSymbol_p { SymbolKey_IsSymbol_t proc; };

typedef void (*SymbolKey_PerformOperation_t) (unsigned int);
struct SymbolKey_PerformOperation_p { SymbolKey_PerformOperation_t proc; };

struct SymbolKey_Node_r {
                          NameKey_Name KeyName;
                          unsigned int KeySym;
                          SymbolKey_SymbolTree Left;
                          SymbolKey_SymbolTree Right;
                        };

extern "C" void SymbolKey_InitTree (SymbolKey_SymbolTree *t);
extern "C" void SymbolKey_KillTree (SymbolKey_SymbolTree *t);

/*
   ContainsSymKey - return TRUE if tree, t, contains an entry for, NameKey.
*/

extern "C" unsigned int SymbolKey_GetSymKey (SymbolKey_SymbolTree t, NameKey_Name NameKey);

/*
   ContainsSymKey - return TRUE if tree, t, contains an entry for, NameKey.
*/

extern "C" void SymbolKey_PutSymKey (SymbolKey_SymbolTree t, NameKey_Name NameKey, unsigned int SymKey);

/*
   DelSymKey - deletes an entry in the binary tree.

               NB in order for this to work we must ensure that the InitTree sets
               both Left and Right to NIL.
*/

extern "C" void SymbolKey_DelSymKey (SymbolKey_SymbolTree t, NameKey_Name NameKey);

/*
   IsEmptyTree - returns true if SymbolTree, t, is empty.
*/

extern "C" unsigned int SymbolKey_IsEmptyTree (SymbolKey_SymbolTree t);

/*
   DoesTreeContainAny - returns true if SymbolTree, t, contains any
                        symbols which in turn return true when procedure,
                        P, is called with a symbol as its parameter.
                        The SymbolTree root is empty apart from the field,
                        Left, hence we need two procedures.
*/

extern "C" unsigned int SymbolKey_DoesTreeContainAny (SymbolKey_SymbolTree t, SymbolKey_IsSymbol P);

/*
   ForeachNodeDo - for each node in SymbolTree, t, a procedure, P,
                   is called with the node symbol as its parameter.
                   The tree root node only contains a legal Left pointer,
                   therefore we need two procedures to examine this tree.
*/

extern "C" void SymbolKey_ForeachNodeDo (SymbolKey_SymbolTree t, SymbolKey_PerformOperation P);

/*
   ContainsSymKey - return TRUE if tree, t, contains an entry for, NameKey.
*/

extern "C" unsigned int SymbolKey_ContainsSymKey (SymbolKey_SymbolTree t, NameKey_Name NameKey);

/*
   NoOfNodes - returns the number of nodes in the tree t.
*/

extern "C" unsigned int SymbolKey_NoOfNodes (SymbolKey_SymbolTree t, SymbolKey_IsSymbol condition);

/*
   ForeachNodeConditionDo - traverse the tree t and for any node which satisfied
                            condition call P.
*/

extern "C" void SymbolKey_ForeachNodeConditionDo (SymbolKey_SymbolTree t, SymbolKey_IsSymbol condition, SymbolKey_PerformOperation P);

/*
   FindNodeParentInTree - find a node, child, in a binary tree, t, with name equal to n.
                          if an entry is found, parent is set to the node above child.
*/

static void FindNodeParentInTree (SymbolKey_SymbolTree t, NameKey_Name n, SymbolKey_SymbolTree *child, SymbolKey_SymbolTree *parent);

/*
   SearchForAny - performs the search required for DoesTreeContainAny.
                  The root node always contains a nul data value,
                  therefore we must skip over it.
*/

static unsigned int SearchForAny (SymbolKey_SymbolTree t, SymbolKey_IsSymbol P);

/*
   SearchAndDo - searches all the nodes in SymbolTree, t, and
                 calls procedure, P, with a node as its parameter.
                 It traverse the tree in order.
*/

static void SearchAndDo (SymbolKey_SymbolTree t, SymbolKey_PerformOperation P);

/*
   CountNodes - wrapper for NoOfNodes.
*/

static unsigned int CountNodes (SymbolKey_SymbolTree t, SymbolKey_IsSymbol condition, unsigned int count);

/*
   SearchConditional - wrapper for ForeachNodeConditionDo.
*/

static void SearchConditional (SymbolKey_SymbolTree t, SymbolKey_IsSymbol condition, SymbolKey_PerformOperation P);


/*
   FindNodeParentInTree - find a node, child, in a binary tree, t, with name equal to n.
                          if an entry is found, parent is set to the node above child.
*/

static void FindNodeParentInTree (SymbolKey_SymbolTree t, NameKey_Name n, SymbolKey_SymbolTree *child, SymbolKey_SymbolTree *parent)
{
  /* remember to skip the sentinal value and assign parent and child  */
  (*parent) = t;
  if (t == NULL)
    {
      Debug_Halt ((const char *) "parameter t should never be NIL", 31, 240, (const char *) "../../gcc-git-devel-modula2/gcc/m2/gm2-compiler/SymbolKey.mod", 61);
    }
  Assertion_Assert (t->Right == NULL);
  (*child) = t->Left;
  if ((*child) != NULL)
    {
      do {
        if (n < (*child)->KeyName)
          {
            (*parent) = (*child);
            (*child) = (*child)->Left;
          }
        else if (n > (*child)->KeyName)
          {
            /* avoid dangling else.  */
            (*parent) = (*child);
            (*child) = (*child)->Right;
          }
      } while (! (((*child) == NULL) || (n == (*child)->KeyName)));
    }
}


/*
   SearchForAny - performs the search required for DoesTreeContainAny.
                  The root node always contains a nul data value,
                  therefore we must skip over it.
*/

static unsigned int SearchForAny (SymbolKey_SymbolTree t, SymbolKey_IsSymbol P)
{
  if (t == NULL)
    {
      return FALSE;
    }
  else
    {
      return (((*P.proc) (t->KeySym)) || (SearchForAny (t->Left, P))) || (SearchForAny (t->Right, P));
    }
  /* static analysis guarentees a RETURN statement will be used before here.  */
  __builtin_unreachable ();
}


/*
   SearchAndDo - searches all the nodes in SymbolTree, t, and
                 calls procedure, P, with a node as its parameter.
                 It traverse the tree in order.
*/

static void SearchAndDo (SymbolKey_SymbolTree t, SymbolKey_PerformOperation P)
{
  if (t != NULL)
    {
      SearchAndDo (t->Right, P);
      (*P.proc) (t->KeySym);
      SearchAndDo (t->Left, P);
    }
}


/*
   CountNodes - wrapper for NoOfNodes.
*/

static unsigned int CountNodes (SymbolKey_SymbolTree t, SymbolKey_IsSymbol condition, unsigned int count)
{
  if (t != NULL)
    {
      if ((*condition.proc) (t->KeySym))
        {
          count += 1;
        }
      count = CountNodes (t->Left, condition, count);
      count = CountNodes (t->Right, condition, count);
    }
  return count;
  /* static analysis guarentees a RETURN statement will be used before here.  */
  __builtin_unreachable ();
}


/*
   SearchConditional - wrapper for ForeachNodeConditionDo.
*/

static void SearchConditional (SymbolKey_SymbolTree t, SymbolKey_IsSymbol condition, SymbolKey_PerformOperation P)
{
  if (t != NULL)
    {
      SearchConditional (t->Right, condition, P);
      if ((t->KeySym != 0) && ((*condition.proc) (t->KeySym)))
        {
          (*P.proc) (t->KeySym);
        }
      SearchConditional (t->Left, condition, P);
    }
}

extern "C" void SymbolKey_InitTree (SymbolKey_SymbolTree *t)
{
  Storage_ALLOCATE ((void **) &(*t), sizeof (SymbolKey_Node));  /* The value entity  */
  (*t)->Left = NULL;
  (*t)->Right = NULL;
}

extern "C" void SymbolKey_KillTree (SymbolKey_SymbolTree *t)
{
  /* 
    we used to get problems compiling KillTree below - so it was split
    into the two procedures below.


PROCEDURE KillTree (VAR t: SymbolTree) ;
BEGIN
   IF t#NIL
   THEN
      Kill(t) ;   Would like to place Kill in here but the compiler 
                  gives a type incompatible error... so i've split  
                  the procedure into two. - Problem i think with    
                  VAR t at the top?                                 
      t := NIL
   END
END KillTree ;


PROCEDURE Kill (t: SymbolTree) ;
BEGIN
   IF t#NIL
   THEN
      Kill(t^.Left) ;
      Kill(t^.Right) ;
      DISPOSE(t)
   END
END Kill ;
  */
  if ((*t) != NULL)
    {
      SymbolKey_KillTree (&(*t)->Left);
      SymbolKey_KillTree (&(*t)->Right);
      Storage_DEALLOCATE ((void **) &(*t), sizeof (SymbolKey_Node));
      (*t) = NULL;
    }
}


/*
   ContainsSymKey - return TRUE if tree, t, contains an entry for, NameKey.
*/

extern "C" unsigned int SymbolKey_GetSymKey (SymbolKey_SymbolTree t, NameKey_Name NameKey)
{
  SymbolKey_SymbolTree father;
  SymbolKey_SymbolTree child;

  FindNodeParentInTree (t, NameKey, &child, &father);
  if (child == NULL)
    {
      return static_cast<unsigned int> (SymbolKey_NulKey);
    }
  else
    {
      return child->KeySym;
    }
  /* static analysis guarentees a RETURN statement will be used before here.  */
  __builtin_unreachable ();
}


/*
   ContainsSymKey - return TRUE if tree, t, contains an entry for, NameKey.
*/

extern "C" void SymbolKey_PutSymKey (SymbolKey_SymbolTree t, NameKey_Name NameKey, unsigned int SymKey)
{
  SymbolKey_SymbolTree father;
  SymbolKey_SymbolTree child;

  FindNodeParentInTree (t, NameKey, &child, &father);
  if (child == NULL)
    {
      /* no child found, now is NameKey less than father or greater?  */
      if (father == t)
        {
          /* empty tree, add it to the left branch of t  */
          Storage_ALLOCATE ((void **) &child, sizeof (SymbolKey_Node));
          father->Left = child;
        }
      else
        {
          if (NameKey < father->KeyName)
            {
              Storage_ALLOCATE ((void **) &child, sizeof (SymbolKey_Node));
              father->Left = child;
            }
          else if (NameKey > father->KeyName)
            {
              /* avoid dangling else.  */
              Storage_ALLOCATE ((void **) &child, sizeof (SymbolKey_Node));
              father->Right = child;
            }
        }
      child->Right = NULL;
      child->Left = NULL;
      child->KeySym = SymKey;
      child->KeyName = NameKey;
    }
  else
    {
      Debug_Halt ((const char *) "symbol already stored", 21, 156, (const char *) "../../gcc-git-devel-modula2/gcc/m2/gm2-compiler/SymbolKey.mod", 61);
    }
}


/*
   DelSymKey - deletes an entry in the binary tree.

               NB in order for this to work we must ensure that the InitTree sets
               both Left and Right to NIL.
*/

extern "C" void SymbolKey_DelSymKey (SymbolKey_SymbolTree t, NameKey_Name NameKey)
{
  SymbolKey_SymbolTree i;
  SymbolKey_SymbolTree child;
  SymbolKey_SymbolTree father;

  FindNodeParentInTree (t, NameKey, &child, &father);  /* find father and child of the node  */
  if ((child != NULL) && (child->KeyName == NameKey))
    {
      /* Have found the node to be deleted  */
      if (father->Right == child)
        {
          /* most branch of child^.Left.  */
          if (child->Left != NULL)
            {
              /* Scan for Right most node of child^.Left  */
              i = child->Left;
              while (i->Right != NULL)
                {
                  i = i->Right;
                }
              i->Right = child->Right;
              father->Right = child->Left;
            }
          else
            {
              /* (as in a single linked list) to child^.Right  */
              father->Right = child->Right;
            }
          Storage_DEALLOCATE ((void **) &child, sizeof (SymbolKey_Node));
        }
      else
        {
          /* branch of child^.Right  */
          if (child->Right != NULL)
            {
              /* Scan for Left most node of child^.Right  */
              i = child->Right;
              while (i->Left != NULL)
                {
                  i = i->Left;
                }
              i->Left = child->Left;
              father->Left = child->Right;
            }
          else
            {
              /* (as in a single linked list) to child^.Left.  */
              father->Left = child->Left;
            }
          Storage_DEALLOCATE ((void **) &child, sizeof (SymbolKey_Node));
        }
    }
  else
    {
      Debug_Halt ((const char *) "trying to delete a symbol that is not in the tree - the compiler never expects this to occur", 92, 223, (const char *) "../../gcc-git-devel-modula2/gcc/m2/gm2-compiler/SymbolKey.mod", 61);
    }
}


/*
   IsEmptyTree - returns true if SymbolTree, t, is empty.
*/

extern "C" unsigned int SymbolKey_IsEmptyTree (SymbolKey_SymbolTree t)
{
  return t->Left == NULL;
  /* static analysis guarentees a RETURN statement will be used before here.  */
  __builtin_unreachable ();
}


/*
   DoesTreeContainAny - returns true if SymbolTree, t, contains any
                        symbols which in turn return true when procedure,
                        P, is called with a symbol as its parameter.
                        The SymbolTree root is empty apart from the field,
                        Left, hence we need two procedures.
*/

extern "C" unsigned int SymbolKey_DoesTreeContainAny (SymbolKey_SymbolTree t, SymbolKey_IsSymbol P)
{
  return SearchForAny (t->Left, P);
  /* static analysis guarentees a RETURN statement will be used before here.  */
  __builtin_unreachable ();
}


/*
   ForeachNodeDo - for each node in SymbolTree, t, a procedure, P,
                   is called with the node symbol as its parameter.
                   The tree root node only contains a legal Left pointer,
                   therefore we need two procedures to examine this tree.
*/

extern "C" void SymbolKey_ForeachNodeDo (SymbolKey_SymbolTree t, SymbolKey_PerformOperation P)
{
  SearchAndDo (t->Left, P);
}


/*
   ContainsSymKey - return TRUE if tree, t, contains an entry for, NameKey.
*/

extern "C" unsigned int SymbolKey_ContainsSymKey (SymbolKey_SymbolTree t, NameKey_Name NameKey)
{
  SymbolKey_SymbolTree father;
  SymbolKey_SymbolTree child;

  FindNodeParentInTree (t, NameKey, &child, &father);
  return child != NULL;
  /* static analysis guarentees a RETURN statement will be used before here.  */
  __builtin_unreachable ();
}


/*
   NoOfNodes - returns the number of nodes in the tree t.
*/

extern "C" unsigned int SymbolKey_NoOfNodes (SymbolKey_SymbolTree t, SymbolKey_IsSymbol condition)
{
  return CountNodes (t->Left, condition, 0);
  /* static analysis guarentees a RETURN statement will be used before here.  */
  __builtin_unreachable ();
}


/*
   ForeachNodeConditionDo - traverse the tree t and for any node which satisfied
                            condition call P.
*/

extern "C" void SymbolKey_ForeachNodeConditionDo (SymbolKey_SymbolTree t, SymbolKey_IsSymbol condition, SymbolKey_PerformOperation P)
{
  if (t != NULL)
    {
      Assertion_Assert (t->Right == NULL);
      SearchConditional (t->Left, condition, P);
    }
}

extern "C" void _M2_SymbolKey_init (__attribute__((unused)) int argc,__attribute__((unused)) char *argv[],__attribute__((unused)) char *envp[])
{
}

extern "C" void _M2_SymbolKey_finish (__attribute__((unused)) int argc,__attribute__((unused)) char *argv[],__attribute__((unused)) char *envp[])
{
}
