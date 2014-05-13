// Copyright (c) by Wayne C. Gramlich.  All rights reserved.

#include "Unsigned.hpp"

/// @brief Return -1, 0, or 1 if depending on sort order.
/// @param unsigned1 is the left *Unsigned* to compare.
/// @param unsigned2 is the right *Unsigned* to compare.
/// @returns -1, 0, 1 depending on sort order.
///
/// *Unsigned__compare*() will return -1 if *unsigned1* is less than
/// *unsigned2*, zero if they are equal, and 1 if *unsigned1* greater
/// than *unsigned2*.

int Unsigned__compare(Unsigned unsigned1, Unsigned unsigned2) {
    int result = 0;
    if (unsigned1 < unsigned2) {
	result = -1;
    } else if (unsigned1 > unsigned2) {
	result = 1;
    }
    return result;
}

/// @brief Return true if *unsigned1* equals *unsigned2*.
/// @param unsigned1 is the first *Unsigned* to compare.
/// @param unsigned2 is the second *Unsigned* to compare.
/// @returns true if *unsigned1* is equal to *unsigned2*.
///
/// *Unsigned__equal*() will return true (i.e. (*bool*)1) if *unsigned1*
/// is equal to *unsigned2* and false (i.e. (*bool*)0) otherwise.

bool Unsigned__equal(Unsigned unsigned1, Unsigned unsigned2) {
    return (bool)(unsigned1 == unsigned2);
}

/// @brief Return a hash of *unsigned1*
/// @param unsigned1 the value to hash.
/// @returns hash value.
///
/// *Unsigned__hash*() will return a hash of *unsigned1*.

Unsigned Unsigned__hash(Unsigned unsigned1) {
    return unsigned1;
}

/// @brief Return the minumum of *unsigned1* and *unsigned2*.
/// @param unsigned1 is the first *Unsigned* to compare.
/// @param unsigned2 is the second *Unsigned* to compare.
/// @returns the minumum of *unsigned1* and *unsigned2*.
///
/// *Unsigned__minimum*() will return the minimum of *unsigned1*
/// and *unsigned2*.

Unsigned Unsigned__minimum(Unsigned unsigned1, Unsigned unsigned2) {
    Unsigned result = unsigned1;
    if (unsigned2 < result) {
	result = unsigned2;
    }
    return result;
}

