// Copyright (c) 2013-2014 by Wayne C. Gramlich all rights reserved.

#include <assert.h>
#include <ctype.h>

#include "File.hpp"
#include "String.hpp"

// *File* routines:

/// @brief Read a byte from *file*.
/// @param file to read from.
/// @returns byte read from *file*.
///
/// *File__byte_read*() will read a byte from *file* and return it.

unsigned int File__byte_read(File file) {
    int byte = fgetc(file);
    assert (byte >= 0);
    return (unsigned int)byte;
}

/// @brief Write *byte* ot *file*.
/// @param file to read from.
/// @param byte to write out.
///
/// *File__byte_write*() will write *byte* to *file*.

void File__byte_write(File file, unsigned int byte) {
    fputc(byte, file);
}

/// @brief Return the next character read from *in_file*.
/// @param in_file to read from.
/// @returns character read from *in_file*.
///
/// *File__character_read*() will read in and return the next character
/// from *in_file*.  (*char*)(-1) is returned when an end of file
/// condition is encountered on *in_file*.

int File__character_read(File in_file) {
    return fgetc(in_file);
}

/// @brief Closes *file*.
/// @param file to close.
///
/// *File__close*() will close *file*.

void File__close(File file) {
    assert (fclose(file) == 0);
}

/// @brief Reads in an XML attribute with a floating point value.
/// @param in_file is the input file to read from.
/// @param attribute_name is the attribute name.
/// @returns the floating point value.
///
/// *File__double_attribute_read*() will read in a pattern that matches
/// ' ATTRIBUTE_NAME="VALUE"', where ATTRIBUTE_NAME matches *attribute_name*
/// and VALUE is an optionally signed floating point number.  This is used
/// for parsing "XML" file input.  "XML" is in quotes is because this is
/// really not a very robust XML parser.  An assertion failure occurs if
/// the input does not parse properly.

double File__double_attribute_read(File in_file, String_Const attribute_name) {
    File__string_match(in_file, " ");
    File__string_match(in_file, attribute_name);
    File__string_match(in_file, "=\"");
    double fraction = (double)1.0;
    bool have_decimal_point = (bool)0;
    bool negative = (bool)0;
    double result = (double)0.0;
    while (1) {
        int character = File__character_read(in_file);
	if (isdigit(character)) {
	    if (have_decimal_point) {
		fraction /= (double)10.0;
		result += fraction * (double)(character - '0');
	    } else {
		result = result * 10.0 + (double)(character - '0');
	    }
	} else if (character == '"') {
	    break;
	} else if (character == '.') {
	    have_decimal_point = (bool)1;
	} else if (character == '-') {
	    negative = (bool)1;
	} else {
	    assert(0);
	}
    }
    if (negative) {
	result = -result;
    }
    return result;
}

/// @brief will write *format* out to *file* with all patterns that
/// start with "%" replaced by formatted versions of its arguments.
/// @param file to output to.
/// @param format is the formatting string.
///
/// *File__format*() will write *format* out to *file* with all patterns that
/// start with "%" replaced by formatted versions of its arguments.

void File__format(File file, String_Const format, ...) {
    // Set up *variadic_arguments to start after *format*:
    va_list variadic_arguments;
    va_start(variadic_arguments, format);

    // Perform the format:
    unsigned int formatted_size = vfprintf(file, format, variadic_arguments);
}

/// @brief Reads in an XML attribute with a floating point value.
/// @param in_file is the input file to read from.
/// @param attribute_name is the attribute name.
/// @returns the floating point value.
///
/// *File__float_attribute_read*() will read in a pattern that matches
/// ' ATTRIBUTE_NAME="VALUE"', where ATTRIBUTE_NAME matches *attribute_name*
/// and VALUE is an optionally signed floating point number.  This is used
/// for parsing "XML" file input.  "XML" is in quotes is because this is
/// really not a very robust XML parser.  An assertion failure occurs if
/// the input does not parse properly.

float File__float_attribute_read(File in_file, String_Const attribute_name) {
    File__string_match(in_file, " ");
    File__string_match(in_file, attribute_name);
    File__string_match(in_file, "=\"");
    float fraction = (float)1.0;
    bool have_decimal_point = (bool)0;
    bool negative = (bool)0;
    float result = (float)0.0;
    while (1) {
        char character = File__character_read(in_file);
	if (isdigit(character)) {
	    if (have_decimal_point) {
		fraction /= (float)10.0;
		result += fraction * (float)(character - '0');
	    } else {
		result = result * 10.0 + (float)(character - '0');
	    }
	} else if (character == '"') {
	    break;
	} else if (character == '.') {
	    have_decimal_point = (bool)1;
	} else if (character == '-') {
	    negative = (bool)1;
	} else {
	    assert(0);
	}
    }
    if (negative) {
	result = -result;
    }
    return result;
}

/// @brief Flushes file content out of internal buffers.
/// @param file to flush.
///
/// *File__flush*() will flush out the internal buffers of *out_file*.

void File__flush(File file) {
    (void)fflush(file);
}


/// @brief Reads in an XML attribute with a integer value.
/// @param in_file is the input file to read from.
/// @param attribute_name is the attribute name.
/// @returns the floating point value.
///
/// *File__integer_attribute_read*() will read in a pattern that matches
/// ' ATTRIBUTE_NAME="VALUE"', where ATTRIBUTE_NAME matches *attribute_name*
/// and VALUE is an optionally signed integer number.  This is used
/// for parsing "XML" file input.  "XML" is in quotes is because this is
/// really not a very robust XML parser.  An assertion failure occurs if
/// the input does not parse properly.

int File__integer_attribute_read(
  File in_file, String_Const attribute_name) {
    File__string_match(in_file, " ");
    File__string_match(in_file, attribute_name);
    File__string_match(in_file, "=\"");
    bool negative = (bool)0;
    int result = 0;
    while (1) {
        char character = File__character_read(in_file);
	if (isdigit(character)) {
	    result = result * 10 + (character - '0');
	} else if (character == '"') {
	    break;
	} else if (character == '-') {
	    negative = (bool)1;
	} else {
	    assert(0);
	}
    }
    if (negative) {
	result = -result;
    }
    return result;
}

/// @brief Read a little endian short (16-bits) from *file*.
/// @param file to read from.
/// @returns 16-bit value from *file*.
///
/// *File__little_endian_short_read*() will read a 16-bit unsigned integer
/// from *file* and return it.

unsigned int File__little_endian_short_read(File file) {
    int low_byte = fgetc(file);
    assert (low_byte >= 0);
    int high_byte = fgetc(file);
    assert (high_byte >= 0);
    unsigned int result = ((unsigned int)high_byte << 8) | (unsigned int)low_byte;
    return result;
}

/// @brief Write 16-bit *xshort* to *file* in little endian format.
/// @param file to write.
/// @param xshort to write.
///
/// *File__little_endian_short_write*() will write write *xshort* to *file*
/// as a little endian 16-bit unsigned integer.

void File__little_endian_short_write(File file, unsigned int xshort) {
    fputc(xshort & 0xff, file);
    fputc((xshort >> 8) & 0xff, file);
}

/// @brief will open *file_name* using *flags* to specify read/write options.
/// @param file_name is the file name to open.
/// @param flags specify the read/write options.
///
/// *File__open*() will open *file_name* using *flags* to read/write options.
/// An open *File* object is returned or (*File)0 if the open failed.

File File__open(String_Const file_name, String_Const flags) {
    return fopen(file_name, flags);
}

/// @brief Exactly matches *pattern* read from *in_file*.
/// @param in_file to read from.
/// @param pattern to matach.
///
/// *File__string_match*() will read characters from *in_file* that must
/// exactly match *pattern*.  An assertion failure occurs if *pattern*
/// does not match exactly.

void File__string_match(File in_file, String_Const pattern) {
    unsigned int size = String__size(pattern);
    for (unsigned int index = 0; index < size; index++) {
        char character = File__character_read(in_file);
	assert(character == pattern[index]);
    }
}

/// @brief Matchs and "XML" start tag.
/// @param in_file is the file to read from.
/// @param tag_name is the name of the tat to match.
///
/// *File__tag_match*() parse "WHITESPACE<TAG" where WHTITESPACE  is zero
/// or more spaces and TAG matches *tag_name*.  An assertion failure occurs
/// the pattern does not parse properly.  This is not a very robust XML
/// parser.

void File__tag_match(File in_file, String_Const tag_name) {
    while (1) {
        char character = File__character_read(in_file);
	if (character == '<') {
	    break;
	} else if (character == ' ') {
	    // Do nothing:
	} else {
	    assert(0);
	}
    }
    File__string_match(in_file, tag_name);
}

