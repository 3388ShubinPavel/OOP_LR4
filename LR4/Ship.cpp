#include "Ship.h"
#include <stdexcept>

Ship::Ship(int len, bool vertical) : length(len), isVertical(vertical), segments(len) {}

int Ship::getLength() const {
    return length;
}

bool Ship::isVerticalOrientation() const {
    return isVertical;
}

void Ship::setOrientation(bool vertical) {
    isVertical = vertical;
}

Segment& Ship::getSegment(int index) {
    return segments.at(index);
}

int Ship::getSegmentCount() const {
    return segments.size(); 
}

const Segment& Ship::getSegment(int index) const {
    return segments.at(index);
}

void Ship::takeDamage(int segmentIndex) {
    if (segmentIndex >= 0 && segmentIndex < length) {
        segments[segmentIndex].takeDamage();
    }
}

void Ship::forceDestroySegment(int segmentIndex) {
    if (segmentIndex >= 0 && segmentIndex < length) {
        segments[segmentIndex].setStatus(SegmentStatus::Destroyed);
    }
}

bool Ship::isDestroyed() const {
    for (const auto& segment : segments) {
        if (segment.getStatus() != SegmentStatus::Destroyed) {
            return false;
        }
    }
    return true;
}
