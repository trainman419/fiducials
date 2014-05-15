// Copyright (c) 2013 by Wayne C. Gramlich.  All rights reserved.

#include "Bounding_Box.hpp"
#include "Memory.hpp"
#include <algorithm>

/// @brief Release the storage associated with *bounding_box*.
/// @param bounding_box the *Bounding_Box* object to release storage of.
///
/// *Bounding_Box__free*() will release the storage associated with
/// *bounding_box*.

void Bounding_Box__free(Bounding_Box bounding_box) {
    Memory__free((Memory)bounding_box);
}

/// @brief Returns a new empty *Bounding_Box* object.
/// @returns an empty *Bounding_Box* object.
///
/// *Bounding_Box__new*() will return a new empty *Bounding_Box* object.

Bounding_Box Bounding_Box__new(void) {
    Bounding_Box bounding_box = Memory__new(Bounding_Box, "Bounding_Box__new");
    Bounding_Box__reset(bounding_box);
    return bounding_box;
}

/// @brief Resets the contents of *bounding_box* to empty.
/// @param bounding_box to be reset.
///
/// *Bounding_Box__reset*() will reset *bounding_box* to the empty state.

void Bounding_Box__reset(Bounding_Box bounding_box) {
    double big = 123456789.0;
    bounding_box->maximum_x = -big;
    bounding_box->minimum_x = big;
    bounding_box->maximum_y = -big;
    bounding_box->minimum_y = big;
}

/// @brief Adds the point (*x*, *y) to *bounding_box*.
/// @param bounding_box to be updated.
/// @param x is the X value to update.
/// @param y is the Y value to update.
///
/// *Bounding_Box__update*() will update the contents of *bounding_box* to
/// enclose (*x*, *y*).

void Bounding_Box__update(Bounding_Box bounding_box, double x, double y) {
    bounding_box->maximum_x = std::max(bounding_box->maximum_x, x);
    bounding_box->minimum_x = std::min(bounding_box->minimum_x, x);
    bounding_box->maximum_y = std::max(bounding_box->maximum_y, y);
    bounding_box->minimum_y = std::min(bounding_box->minimum_y, y);
}

