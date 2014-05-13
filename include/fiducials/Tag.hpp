// Copyright (c) 20013 by Wayne C. Gramlich.  All rights reserved.

#if !defined(TAG_H_INCLUDED)
#define TAG_H_INCLUDED 1

/// @brief *Tag* is a representation of a ceiling fiducial marker.
///
/// A *Tag* represents a 5-tuple:
///
///        (id, twist, x, y, arcs)
///
/// where:
///
/// * *id* is the tag identifier,
///
/// * *twist* is the amount the tag is twisted from the floor X axis,
///
/// * *x* is the absolute X floor coordinate of the center of *Tag*,
///
/// * *y* is the absolute Y floor coordinate of the center of *Tag*,
///
/// * *arcs* is a list of 0, 1, or more *Arc*'s that connect to other
///   *Tag*'s.
///
/// *twist* needs a little more discussion.  The bottom edge of the
/// fiducial establishes a coordinate system for the *Tag*.  The vector
/// from the lower left corner to the lower right corner is the Tag "X"
/// axis.  Here is some crude ASCII art:
///
///        UL-------UR
///        |         |
///        |    O----+------> "X axis"
///        |         |
///        LL-------LR
///
/// The four corners are labeled UL, UR, LL, and LR for Upper Left, Upper
/// Right, Lower Left, and Lower Right respectively.  O stands for Origin
/// and is located in the exact center of the fiducial.  The "X axis"
/// for the fiducial goes to the left starting from the origin (O) and
/// moving to the right.  The "X axis" is parallel the line the goes
/// through the points LL and LR.
///
/// Internally, *twist* is represented in radians.

#include <vector>

#include "Bounding_Box.hpp"
#include "CV.hpp"
#include "Double.hpp"
#include "File.hpp"
#include "SVG.hpp"
#include "Unsigned.hpp"

/// @brief A *Tag* is a pointer to a *Tag_Struct* object.
typedef struct Tag__Struct *Tag;

/// @brief A *Tag_Height* is a point to a *Tag_Height__Struct* object.
typedef struct Tag_Height__Struct *Tag_Height;

#include "Map.hpp"
#include "Arc.hpp"


/// @brief A *Tag_Struct* represents the location and orientation of one 
/// ceiling fiducial tag.
struct Tag__Struct {
    /// @brief List *Arc*'s connected to this *Tag*.
    std::vector<Arc> arcs_;

    /// @brief Fiducial tag diagnal distance in camera pixels.
    Double diagonal;

    /// @brief Distance along one side of the tag in world units.
    Double world_diagonal;

    ///@brief True if rest of *Tag* is initialized.
    bool initialized;

    /// @brief Distance from origin in hops:
    Unsigned hop_count;

    /// @brief Tag identifier.
    Unsigned id;

    /// @brief Parent *Map* object.
    Map map;

    /// @brief The twist from the floor X axis to the tag bottom edge.
    Double twist;

    /// @brief True if tag is currently visible in camera field of view.
    bool visible;

    /// @brief Visit counter.
    Unsigned visit;

    /// @brief Absolute X floor coordinate.
    Double x;

    /// @brief Absolute Y floor coordinate.
    Double y;

    /// @brief Absolute Z floor coordinate.
    Double z;

    /// @brief Set if tag was updated
    bool updated;
};

/// @brief A *Tag_Height__Struct* represents a span of tags a the same
/// ceiling height.
struct Tag_Height__Struct {
    /// @brief Distance along one side of the tag in world units.
    Double world_diagonal;

    /// @brief The first tag identifier in the span.
    Unsigned first_id;

    /// @brief The last tag identifier in the span.
    Unsigned last_id;

    /// @brief The fiducial height above the floor.
    Double z;
};

// *Tag* routines;

extern void Tag__arc_append(Tag tag, Arc arc);
extern void Tag__bounding_box_update(Tag tag, Bounding_Box bounding_box);
extern Tag Tag__create(Unsigned id, Map map);
extern int Tag__compare(Tag tag1, Tag tag2);
extern bool Tag__less(Tag tag1, Tag tag2);
extern void Tag__free(Tag tag);
extern void Tag__initialize(
  Tag tag, Double angle, Double x, Double y, Double diagonal, Unsigned visit);
extern void Tag__sort(Tag tag);
extern Tag Tag__read(File in_file, Map map);
extern void Tag__svg_write(Tag tag, SVG svg);
extern void Tag__write(Tag tag, File out_file);
extern void Tag__update_via_arc(
  Tag tag, Arc arc, CV_Image image, Unsigned sequence_number);

// *Tag_Height* routines:
extern int Tag_Height__compare(
  Tag_Height tag_height1, Tag_Height tag_height2);
extern void Tag_Height__free(Tag_Height tag_height);
extern Tag_Height Tag_Height__xml_read(File in_file);

#endif // !defined(TAG_H_INCLUDED)
