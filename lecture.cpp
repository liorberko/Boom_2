#include "lecture.h"

bool lecture::operator<(const lecture target) const 
{
    if(key.viewTime < target.key.viewTime){
        return true;
    }
    if (key.viewTime == target.key.viewTime && key.lectureID > target.key.lectureID)
    {
        return true;
    }
    else if (key.viewTime == target.key.viewTime && key.lectureID==target.key.lectureID && key.courseID > target.key.courseID){
        return true;
    }
    return false;
}
bool lecture::operator>(const lecture target) const 
{
    if(key.viewTime > target.key.viewTime){
        return true;
    }
    if (key.viewTime == target.key.viewTime && key.lectureID < target.key.lectureID)
    {
        return true;
    }
    else if (key.viewTime == target.key.viewTime && key.lectureID==target.key.lectureID && key.courseID < target.key.courseID){
        return true;
    }
    return false;
}

bool lecture::operator==(const lecture target) const 
{
    if ((key.lectureID == target.key.lectureID) && (key.courseID == target.key.courseID) && (key.viewTime == target.key.viewTime))
    {
        return true;
    }
    return false;
}

lecture& lecture::operator=(const lecture target) {
    if (this == &target)
    {
        return *this;
    }
    this->key.lectureID=target.key.courseID;
    this->key.courseID=target.key.courseID;
    this->key.viewTime=target.key.viewTime;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const lecture target) 
{
    out << "lecture id: " << target.key.lectureID << std::endl;
    out << "course id: " << target.key.courseID << std::endl;
    out << "lecture view time: " << target.key.viewTime << std::endl;
    return out;
}
int& lecture::getLectureID()
{
    return key.lectureID;
}

int& lecture::getCourseID()
{
    return key.courseID;
}

int& lecture::getViewTime()
{
    return key.viewTime;
}

lectureKey& lecture::getKey()
{
    return key;
}
