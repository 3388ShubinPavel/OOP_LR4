#pragma once

#include <vector>
#include "Segment.h"

class Ship {
private:
    int length;
    bool isVertical;
    std::vector<Segment> segments;
    bool destroyed;
public:
    Ship(int len, bool vertical);
    int getLength() const;
    bool isVerticalOrientation() const;
    void setOrientation(bool vertical);
    int getSegmentCount() const;
    Segment& getSegment(int index);
    const Segment& getSegment(int index) const;
    void takeDamage(int segmentIndex);
    void forceDestroySegment(int segmentIndex); 
    bool isDestroyed() const;
};
