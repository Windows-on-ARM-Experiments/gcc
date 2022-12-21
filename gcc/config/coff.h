/* elfos.h  --  operating system specific defines to be used when
   targeting GCC for some generic ELF system
   Copyright (C) 1991-2022 Free Software Foundation, Inc.
   Based on svr4.h contributed by Ron Guilmette (rfg@netcom.com).

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

/* The GNU tools operate better with dwarf2, and it is required by some
   psABI's.  Since we don't have any native tools to be compatible with,
   default to dwarf2.  */

#define DWARF2_LINENO_DEBUGGING_INFO 1

#undef PREFERRED_DEBUGGING_TYPE
#define PREFERRED_DEBUGGING_TYPE DWARF2_DEBUG

#define GLOBAL_ASM_OP "\t.global\t"
#define TEXT_SECTION_ASM_OP	"\t.text"
#define DATA_SECTION_ASM_OP	"\t.data"
#define BSS_SECTION_ASM_OP	"\t.bss"


/* This is how to store into the string LABEL
   the symbol_ref name of an internal numbered label where
   PREFIX is the class of label and NUM is the number within the class.
   This is suitable for output with `assemble_name'.

   For most svr4 systems, the convention is that any symbol which begins
   with a period is not put into the linker symbol table by the assembler.  */

#undef  ASM_GENERATE_INTERNAL_LABEL
#define ASM_GENERATE_INTERNAL_LABEL(LABEL, PREFIX, NUM)		\
  do								\
    {								\
      char *__p;						\
      (LABEL)[0] = '*';						\
      (LABEL)[1] = '.';						\
      __p = stpcpy (&(LABEL)[2], PREFIX);			\
      sprint_ul (__p, (unsigned long) (NUM));			\
    }								\
  while (0)

#define ASM_OUTPUT_ALIGN(STREAM, POWER)		\
  fprintf(STREAM, "\t.align\t%d\n", (int)POWER)

/* Output a common block.  */
#ifndef ASM_OUTPUT_COMMON
#define ASM_OUTPUT_COMMON(STREAM, NAME, SIZE, ROUNDED)	\
  do							\
    {							\
      fprintf (STREAM, "\t.comm\t");			\
      assemble_name (STREAM, NAME);			\
      asm_fprintf (STREAM, ", %d\t%@ %d\n", 		\
	           (int)(ROUNDED), (int)(SIZE));	\
    }							\
  while (0)
#endif

/* This says how to output an assembler line
   to define a local common symbol.  */

#define ASM_OUTPUT_LOCAL(FILE, NAME, SIZE, ROUNDED)  \
( fputs (".lcomm ", (FILE)),			\
  assemble_name ((FILE), (NAME)),		\
  fprintf ((FILE), ",%u\n", (int)(ROUNDED)))

#define SKIP_ASM_OP	"\t.zero\t"

#undef  ASM_OUTPUT_SKIP
#define ASM_OUTPUT_SKIP(FILE, SIZE) \
   fprintf ((FILE), "%s" HOST_WIDE_INT_PRINT_UNSIGNED "\n",\
	    SKIP_ASM_OP, (SIZE))

/* This is how to declare the size of a function.  */
#ifndef ASM_DECLARE_FUNCTION_SIZE
#define ASM_DECLARE_FUNCTION_SIZE(FILE, FNAME, DECL)
#endif

#define ASM_OUTPUT_TYPE_DIRECTIVE(STREAM, NAME, TYPE)
// #define TYPE_ASM_OP	"\t.type\t"

// #undef TYPE_OPERAND_FMT
// #define TYPE_OPERAND_FMT	"%%%s"

#undef  SET_ASM_OP
#define SET_ASM_OP	"\t.set\t"

#define CTORS_SECTION_ASM_OP "\t.section\t.init_array,\"aw\",%init_array"
#define DTORS_SECTION_ASM_OP "\t.section\t.fini_array,\"aw\",%fini_array"

#define SIG_ATOMIC_TYPE "int"

#define INT8_TYPE "signed char"
#define INT16_TYPE "short int"
#define INT32_TYPE "int"
#define INT64_TYPE "long long int"
#define UINT8_TYPE "unsigned char"
#define UINT16_TYPE "short unsigned int"
#define UINT32_TYPE "unsigned int"
#define UINT64_TYPE "long long unsigned int"

#define INT_LEAST8_TYPE "signed char"
#define INT_LEAST16_TYPE "short int"
#define INT_LEAST32_TYPE "int"
#define INT_LEAST64_TYPE "long long int"
#define UINT_LEAST8_TYPE "unsigned char"
#define UINT_LEAST16_TYPE "short unsigned int"
#define UINT_LEAST32_TYPE "unsigned int"
#define UINT_LEAST64_TYPE "long long unsigned int"

#define INT_FAST8_TYPE "signed char"
#define INT_FAST16_TYPE "short int"
#define INT_FAST32_TYPE "int"
#define INT_FAST64_TYPE "long long int"
#define UINT_FAST8_TYPE "unsigned char"
#define UINT_FAST16_TYPE "short unsigned int"
#define UINT_FAST32_TYPE "unsigned int"
#define UINT_FAST64_TYPE "long long unsigned int"

#define INTPTR_TYPE "long long int"
#define UINTPTR_TYPE "long long unsigned int"

#define TARGET_ASM_NAMED_SECTION default_coff_asm_named_section

#define ABI_SPEC  "-mabi=llp64"
#define MULTILIB_DEFAULTS { "mabi=llp64" }