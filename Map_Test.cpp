// Copyright (c) 2013-2014 by Wayne C. Gramlich.  All rights reserved.

#include <assert.h>

#include "Arc.hpp"
#include "CV.hpp"
#include "File.hpp"
#include "Map.hpp"
#include "String.hpp"
#include "Tag.hpp"

extern void Map__build(Map map);

int main(int arguments_size, char * arguments[]) {
    Map map1 = Map__create(".", "Map_Test_Map",
      (void *)0, Fiducials__arc_announce, Fiducials__tag_announce,
      (String_Const)0, "main:Map__new");
    unsigned int visit = map1->visit;

    double pi = 3.14159265358979323846264;
    double degrees_to_radians = pi / 180.0;

    // Some angles (in radians) to use:
    double angle0   =   0.0 * degrees_to_radians;
    double angle10  =  10.0 * degrees_to_radians;
    double angle20  =  20.0 * degrees_to_radians;
    double angle30  =  30.0 * degrees_to_radians;
    double angle40  =  40.0 * degrees_to_radians;
    double angle45  =  45.0 * degrees_to_radians;
    double angle90  =  90.0 * degrees_to_radians;
    double angle135 = 135.0 * degrees_to_radians;
    double angle180 = 180.0 * degrees_to_radians;

    double square_root_200 = hypot(10.0, 10.0);
    double square_root_50 = hypot(5.0, 5.0);

    // The test map looks as follows:
    //

    //  3---2
    //  |\ /|
    //  | 4 |
    //  |/ \|
    //  0---1

    unsigned int tag_size = 1.0;
    Tag * tag0 = Map__tag_lookup(map1, 0);
    tag0->initialize(0.0, 0.0, 0.0, tag_size, visit);
    Tag * tag1 = Map__tag_lookup(map1, 1);
    tag1->initialize(0.0, 0.0, 0.0, tag_size, visit);
    Tag * tag2 = Map__tag_lookup(map1, 2);
    tag2->initialize(0.0, 0.0, 0.0, tag_size, visit);
    Tag * tag3 = Map__tag_lookup(map1, 3);
    tag3->initialize(0.0, 0.0, 0.0, tag_size, visit);
    Tag * tag4 = Map__tag_lookup(map1, 4);
    tag4->initialize(0.0, 0.0, 0.0, tag_size, visit);

    // The tags are twisted by the tag id x 10 degerees.  Thus, tag
    // 0 has no twist, tag 1 is 10 degerees, ..., and tag 4 is 40 degrees.

    // Sides:
    double d = 10.0;
    new Arc(tag0, 0.0 + 0.0,           d, tag1, -angle180 + angle10, 0.0);
    new Arc(tag1, -angle90 + angle10,  d, tag2,  angle90  + angle20, 0.0);
    new Arc(tag0, -angle90,            d, tag3,  angle90  + angle30, 0.0);
    new Arc(tag2, -angle180 + angle20, d, tag3,  0.0      + angle30, 0.0);

    // Arcs to center:
    d = square_root_50;
    new Arc(tag0, -angle45,            d, tag4,  angle135 + angle40, 0.0);
    new Arc(tag1, -angle135 + angle10, d, tag4,  angle135 + angle40, 0.0);
    new Arc(tag2, -angle45  + angle20, d, tag4,  -angle45 + angle40, 0.0);
    new Arc(tag3,  angle45  + angle30, d, tag4, -angle135 + angle40, 0.0);

    // Large diagonals:
    d = square_root_200;
    //Arc__create(tag0, ??, square_root_200, tag2, ??, 0.0);
    //Arc__create(tag1, ??, square_root_200, tag3, ??, 0.0);

    Map__update(map1, (CV_Image)0, 0);

    Map__save(map1);

    Map map2 = Map__create(".", "Map_Test_Map",
      (void *)0, Fiducials__arc_announce, Fiducials__tag_announce,
      (String_Const)0, "main:Map__new");

    assert (Map__equals(map1, map2));

    std::vector<Location*> locations;
    Map__svg_write(map1, "Map_Test", locations);

    return 0;
}

void Map__build(Map map) {
}
