#pragma once

enum class SegmentStatus {
    Hidden,
    Damaged,
    Destroyed
};

class Segment {
private:
    SegmentStatus status = SegmentStatus::Hidden;
public:
    Segment();
    SegmentStatus getStatus() const;
    void setStatus(SegmentStatus newStatus); 
    void takeDamage();
};
