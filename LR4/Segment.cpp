#include "Segment.h"

Segment::Segment() : status(SegmentStatus::Hidden) {}

SegmentStatus Segment::getStatus() const {
    return status;
}

void Segment::setStatus(SegmentStatus newStatus) {
    status = newStatus;
}

void Segment::takeDamage() {
    if (status == SegmentStatus::Hidden) {
        status = SegmentStatus::Damaged;
    } else if (status == SegmentStatus::Damaged) {
        status = SegmentStatus::Destroyed;
    }
}


