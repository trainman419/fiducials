// Copyright (c) 2013-2014 by Wayne C. Gramlich.  All rights reserved.

#include <assert.h>

#include "Bounding_Box.hpp"
#include "String.hpp"
#include "SVG.hpp"

#include <algorithm>

/// @brief Turns *svg* into a cartesian graphing canvas bounded by
/// *bounding_box*.
/// @param svg is the *SVG* object to modify.
/// @param x_width is the available width graph on.
/// @param y_height is the available height graph on.
/// @param bounding_box specifies the *Bounding_Box* of the values
/// to be graphed.
///
/// *SVG__cartesian_scale*() will modifiy *svg* so that it can graph
/// lines, rectangles, etc, in an area bounded by *bounding_box*.
/// The available graphing area is *x_width* by *y_height*.

void SVG__cartesian_scale(
  SVG svg, double x_width, double y_height, Bounding_Box bounding_box) {
    // Grab the minimum/maximum values from *bounding_box*.
    double maximum_x = bounding_box->maximum_x;
    double minimum_x = bounding_box->minimum_x;
    double maximum_y = bounding_box->maximum_y;
    double minimum_y = bounding_box->minimum_y;

    // Compute the span in x and y:
    double x_span = maximum_x - minimum_x;
    double y_span = maximum_y - minimum_y;
    //File__format(stderr, "X/Y span=(%.2f, %.2f)\n", x_span, y_span);

    // COmpute the axis independent scale in X and Y:
    double x_scale = x_width / x_span;
    double y_scale = y_height / y_span;
    //File__format(stderr, "X/Y scale=(%.6f, %.6f)\n", x_scale, y_scale);

    // Take the smaller of the two so that the X and Y scales are equal:
    x_scale = std::min(x_scale, y_scale);
    y_scale = x_scale;
    //File__format(stderr, "X/Y scale=(%.6f, %.6f)\n", x_scale, y_scale);

    // Compute X/Y spans adjusted by the aspect ratio:
    double scaled_x_span = x_span;
    double scaled_y_span = y_span;
    //File__format(stderr,
    //  "Scaled X/Y span=(%.2f, %.2f)\n", scaled_x_span, scaled_y_span);
    
    // Now compute the X and Y offsets:
    double x_offset = (minimum_x + maximum_x) / 2.0 - scaled_x_span / 2.0;
    // Swap Y axis direction by adding *scaled_y_span* instead of subtracting:
    double y_offset = (minimum_y + maximum_y) / 2.0 + scaled_y_span / 2.0;
    //File__format(stderr, "X/Y offset=(%.2f, %.2f)\n", x_offset, y_offset);
    
    // Load up *svg*:
    svg->width = x_width * x_scale;
    svg->height = y_height * y_scale;
    svg->x_scale = x_scale;
    // Swap Y axis direction by negating *y_scale*:
    svg->y_scale = -y_scale;
    svg->x_offset = -x_offset;
    svg->y_offset = -y_offset;
}


/// @brief Close SVG object.
/// @param svg object to close
///
/// *SVG__close*() will close *svg*.

void SVG__close(SVG svg) {
    // Close *svg*:
    File svg_stream = svg->stream;
    File__format(svg_stream, "</svg>\n");
    File__close(svg_stream);
    svg->stream = (File)0;
    Memory__free((Memory)svg);
}

/// @brief Draw a line from (*x1*, *y1*) to (*x2*, *y2*) using *stroke*.
/// @param svg is the *SVG* object to draw line to.
/// @param x1 is X coordinate of first point.
/// @param y1 is Y coordinate of first point.
/// @param x2 is X coordinate of second point.
/// @param y2 is Y coordinate of second point.
/// @param stroke is stroke string.
///
/// *SVG__line*() will draw a line to *svg* from (*x1*, *y1*) to (*x2*, *y2*)
/// using *stroke*.

void SVG__line(SVG svg,
  double x1, double y1, double x2, double y2, String_Const stroke) {
    // Extract some values from *svg*:
    File svg_stream = svg->stream;
    double x_offset = svg->x_offset;
    double y_offset = svg->y_offset;
    double x_scale = svg->x_scale;
    double y_scale = svg->y_scale;
    String_Const units = svg->units;

    // Output "<line ... />" to *svg_stream*:
    File__format(svg_stream,
      "<line x1=\"%f%s\" y1=\"%f%s\"",
      (x1 + x_offset) * x_scale, units, (y1 + y_offset) * y_scale, units);
    File__format(svg_stream, 
      " x2=\"%f%s\" y2=\"%f%s\"", 
      (x2 + x_offset) * x_scale, units, (y2 + y_offset) * y_scale, units);
    File__format(svg_stream,
       " style=\"stroke:%s\"/>\n", stroke);
}

/// @brief Open an SVG object:
/// @param base_name is the base name of the file name without the .svg.
/// @param width is the width of the SVG.
/// @param height is the height of the SVG.
/// @param x_scale is the amount is scale in X.
/// @param y_scale is the amount to scale in Y.
/// @param units is the units to use.
/// @returns a new *SVG* object.
///
/// *SVG__open*() will create and return a new *SVG* for writing out
/// scable vector graphics.

SVG SVG__open(String_Const base_name,
  double width, double height, double x_scale, double y_scale,
  String_Const units) {
    // Verify that units are OK:
    assert (String__equal(units, "cm") ||
      String__equal(units, "mm") ||
      String__equal(units, "in"));

    // Get *svg_stream* opened:
    SVG svg = (SVG)0;
    char file_name[100];
    (void)sprintf(file_name, "%s.svg", base_name);
    File svg_stream = File__open(file_name, "w");
    if (svg_stream == (File)0) {
	File__format(stderr, "Unable to open %s.svg\n", base_name);
    } else {
        // Allocate and load up *svg*:
	svg = Memory__new(SVG, "SVG__open");
	svg->height = height;
	svg->stream = svg_stream;
	svg->width = width;
	svg->units = units;
	svg->x_scale = x_scale;
	svg->y_scale = y_scale;
	svg->x_offset = 0.0;
	svg->y_offset = 0.0;

	// Ouput the header for *svg*:
	File__format(svg_stream,
	  "<?xml version=\"1.0\" standalone=\"no\"?>\n\n");
	File__format(svg_stream,
	  "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n");
	File__format(svg_stream,
          " \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n\n");
	File__format(svg_stream,
	  "<svg width=\"%f%s\" height=\"%f%s\"\n",
	  width * x_scale, units, height * y_scale, units);
	File__format(svg_stream,
	 " version=\"1.1\"\n");
	File__format(svg_stream,
	 " xmlns=\"http://www.w3.org/2000/svg\">\n\n");
    }

    // Clean up and return:
    //String__free(file_name);
    return svg;
}

/// @brief Draw a *width* by *height* rectangle at (*x*, *y*).
/// @param svg is the *SVG* object to draw rectangle to.
/// @param x is the upper left X coordinate.
/// @param y is the uppper left Y coordinate.
/// @param width is the rectangle width.
/// @param height is the rectangle height.
/// @param stroke_color is the exterior line color.
/// @param fill_color is the interior fill color.
///
/// *SVG__rectangle* will draw a *width* by *height* rectangle at (*x*, *y*)
/// with *stroke_color* and *fill_color* specifying the external line color
/// and internal fill color respectivily.

void SVG__rectangle(SVG svg, double x, double y,
  double width, double height, String_Const stroke_color,
  String_Const fill_color) {
    // Grab some values from svg:
    File svg_stream = svg->stream;
    double x_offset = svg->x_offset;
    double y_offset = svg->y_offset;
    double x_scale = svg->x_scale;
    double y_scale = svg->y_scale;
    String_Const units = svg->units;

    // Output "<rect ... />" to *svg_stream*:
    double x_final = (x + x_offset) * x_scale;
    double y_final = (y + y_offset) * y_scale;
    File__format(svg_stream, 
      "<rect x=\"%f%s\" y=\"%f%s\"", x_final, units, y_final, units);
    File__format(svg_stream,
      " width=\"%f%s\" height=\"%f%s\"",
      width * x_scale,  units, height * y_scale, units);
    File__format(svg_stream,
      " style=\"stroke:%s; fill:%s\"/>\n", stroke_color, fill_color);
}

/// @brief draw *message* at (*x*, *y*).
/// @param svg is the *SVG* object to use.
/// @param message is the message to draw.
/// @param x is the X coordinate to draw text at.
/// @param y is the Y coordinate of draw text at.
/// @param font_family is the font family to use.
/// @param font_size is the font size.
///
/// *SVG__text*() will draw *message* at (*x*, *y*) with *font_size* font
/// of type *font_family*.

void SVG__text(SVG svg,
  String_Const message, double x, double y, String_Const font_family,
  unsigned int font_size) {
    // Grab some values from *svg*:
    File svg_stream = svg->stream;
    double x_offset = svg->x_offset;
    double y_offset = svg->y_offset;
    double x_scale = svg->x_scale;
    double y_scale = svg->y_scale;
    String_Const units = svg->units;

    File__format(svg_stream,
      "<text x=\"%f%s\" y=\"%f%s\"",
      (x + x_offset) * x_scale, units, (y + y_offset) * y_scale, units);
    File__format(svg_stream,
      " style=\"font-family:%s; font-size:%d\">", font_family, font_size);
    File__format(svg_stream, "%s</text>\n", message);
}
