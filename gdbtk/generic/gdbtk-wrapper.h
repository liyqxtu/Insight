/* longjmp-free interface between gdb and gdbtk.
   Copyright (C) 1999-2016 Free Software Foundation, Inc.

This file is part of GDB.  It contains routines to safely call common gdb
functions without the fear of longjmp'ing.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA.  */

#ifndef GDBTK_WRAPPER_H
#define GDBTK_WRAPPER_H
#include "vec.h"

/* Use this struct used to pass arguments to wrapper routines. We assume
   (arbitrarily) that no gdb function takes more than ten arguments. */
struct gdb_wrapper_arguments {

  /* Pointer to some result from the gdb function call, if any */
  union
  {
    int integer;
    void *ptr;
    const void *cstptr;
  } result;

  /* The list of arguments. */
  union
  {
    void *ptr;
    int integer;
  } args[10];
};

/* FIXME: cagney/2002-01-04: GDB no longer uses or supplies the
   value_ptr typedef.  Provide one here to keep the Insight code
   immediatly happy.  */
typedef struct value *value_ptr;

/* Whenever any gdb function wrapper is called, its return status is: */
typedef enum gdb_wrapper_status { GDB_OK, GDB_ERROR } gdb_result;

/* This list of functions which have been wrapped. Please keep this list
   in alphabetical order, using "GDB_" to prefix the actual name of the
   function. */
extern gdb_result GDB_evaluate_expression (struct expression *expr,
					   value_ptr * val);
extern gdb_result GDB_type_print (value_ptr val, char *varstring,
				  struct ui_file *stream, int show);
extern gdb_result GDB_value_fetch_lazy (value_ptr value);
extern gdb_result GDB_value_equal (value_ptr val1, value_ptr val2,
				   int *result);
/*
extern gdb_result GDB_parse_exp_1 (char **stringptr, struct block *block,
				   int comma, struct expression **result);
*/
extern gdb_result GDB_evaluate_type (struct expression *exp,
				     value_ptr * result);
extern gdb_result GDB_block_for_pc (CORE_ADDR pc, const struct block **result);
extern gdb_result GDB_block_innermost_frame (struct block *block,
					     struct frame_info **result);
extern gdb_result GDB_reinit_frame_cache (void);
extern gdb_result GDB_value_ind (value_ptr val, value_ptr * rval);
extern gdb_result GDB_value_slice (value_ptr val, int low, int num,
				   value_ptr * rval);
extern gdb_result GDB_value_coerce_array (value_ptr val, value_ptr * rval);
extern gdb_result GDB_value_struct_elt (value_ptr * argp, value_ptr * args,
					char *name, int *static_memfunc,
					char *err, value_ptr * rval);
extern gdb_result GDB_value_cast (struct type *type, value_ptr val,
				  value_ptr * rval);
gdb_result GDB_get_frame_block (struct frame_info *fi,
				const struct block **rval);
extern gdb_result GDB_get_prev_frame (struct frame_info *fi,
				      struct frame_info **result);
extern gdb_result GDB_get_next_frame (struct frame_info *fi,
				      struct frame_info **result);
extern gdb_result GDB_find_relative_frame (struct frame_info *fi,
					   int *start,
					   struct frame_info **result);
extern gdb_result GDB_get_current_frame (struct frame_info **result);
extern gdb_result GDB_varobj_update (struct varobj **varp, int xplicit,
				     VEC (varobj_update_result) **changes);
#endif /* GDBTK_WRAPPER_H */

