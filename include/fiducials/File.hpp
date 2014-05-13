// Copyright (c) 2013 by Wayne C. Gramlich.  All rights reserved.

#if !defined(FILE_H_INCLUDED)
#define FILE_H_INCLUDED 1

#include <stdio.h>
#include <stdarg.h>

#include "Character.hpp"
#include "Double.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "Unsigned.hpp"

/// @brief *FILE* is a file I/O object.
typedef FILE *File;

// External declarations:
extern Unsigned File__byte_read(File file);
extern void File__byte_write(File file, Unsigned byte);
extern Character File__character_read(File in_file);
extern void File__close(File file);
extern Double File__double_attribute_read(
  File in_file, String_Const attribute_name);
extern Float File__float_attribute_read(
  File in_file, String_Const attribute_name);
extern void File__flush(File file);
extern void File__format(File file, String_Const format, ...);
extern Integer File__integer_attribute_read(
  File in_file, String_Const attribute_name);
extern Unsigned File__little_endian_short_read(File);
extern void File__little_endian_short_write(File, Unsigned xshort);
extern File File__open(String_Const file_name, String_Const flags);
extern void File__string_match(File in_file, String_Const pattern);
extern void File__tag_match(File in_file, String_Const tag_name);

#endif // !defined(FILE_H_INCLUDED)
