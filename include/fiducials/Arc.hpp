// Copyright (c) by Wayne C. Gramlich.  All rights reserved.

#if !defined(ARC_H_INCLUDED)
#define ARC_H_INCLUDED 1

/// @brief *Arc* is just a pointer to *Arc__Struct*.

typedef struct Arc__Struct *Arc;

#include "File.hpp"
#include "Double.hpp"
#include "Map.hpp"
#include "SVG.hpp"
#include "Tag.hpp"

/// @brief An *Arc_Struct* represents arc from the *from* *Tag* to the
/// *to* *Tag*.
///
/// Ultimately an *Arc* specifies an ordered 5-tuple:
///
///        (from_tag, from_twist, distance, to_tag, from_twist)
///
/// where
///
/// * *from_tag* is the *Tag* we start from.
///
/// * *from_twist* is the amount the tag is twisted relative to the ray
///   that starts from *from_tag* and ends at *to_tag*.
///
/// * *distance is the distance between the center of *from_tag* and
///   the center of *to_tag*.
///
/// * *to_tag* is the *Tag* we end at.
///
/// * *to_twist* is the amount the tag is twisted relative to the ray
///   that starts from *to_tag* and ends at *from_tag*.
///
/// Note that the *from_twist* and *to_twist* rays point is opposite
/// directions.  By convention, we store the *Tag* with the smaller
/// id in *from_tag*.
///
/// The conjugate (or inverse) of an *Arc* is generated by swapping
/// *from_tag* with *to_tag* and *from_twist* with *to_twist*.
///
///        from_tag                             to_tag
///      +-----------+                       +-----------+
///      |           |                       |           |
///      |           |       distance        |           |
///      |     O----->-----------------------<-----O     |
///      |           |                       |           |
///      |           |                       |           |
///      +-----------+                       +-----------+

struct Arc__Struct {
    /// @brief The angle in radians from the *origin* center parallel to the
    /// bottom edge to the line that connects the *origin* and *target* centers.
    Double angle;

    /// @brief The distance between the *from* and *to*.
    Double distance;

    /// @brief The from *Tag*.
    Tag from_tag;

    /// @brief The amount *from_tag* is twisted from distance line segment.
    Double from_twist;

    /// @brief Distance between camera center and line connecting both tags.
    Double goodness;

    /// @brief Set to true if this *Arc* is part of the map tree.
    bool in_tree;

    /// @brief The to *Tag* (has larger id than *from*).
    Tag to_tag;

    /// @brief The amount *to_tag* is twisted from distance line segment.
    Double to_twist;

    /// @brief The visit number for the arc.
    Unsigned visit;
};

// *Arc* routines:

extern int Arc__compare(Arc arc1, Arc arc2);
extern bool Arc__less(Arc arc1, Arc arc2);
extern int Arc__distance_compare(Arc arc1, Arc arc2);
extern bool Arc__distance_less(Arc arc1, Arc arc2);
extern Arc Arc__create(Tag from_tag, Double from_twist,
  Double distance, Tag to_tag, Double to_twist, Double goodness);
extern void Arc__free(Arc arc);
extern Arc Arc__new(String from);
extern Arc Arc__read(File out_file, Map map);
extern void Arc__svg_write(Arc arc, SVG svg);
extern void Arc__update(
  Arc arc, Double distance, Double angle, Double twist, Double goodness);
extern void Arc__write(Arc arc, File out_file);

#endif // !defined(ARC_H_INCLUDED)

