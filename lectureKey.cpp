#include "lectureKey.h"

bool lectureKey::operator<(const lectureKey& target) const
{
    if (viewTime < target.viewTime)
    {
        return true;
    }
    else if (viewTime > target.viewTime)
    {
        return false;
    }
    else
    {
        if(courseID > target.courseID)
        {
            return true;
        }
        else if (courseID < target.courseID)
        {
            return false;
        }
        else
        {
            if (lectureID > target.lectureID)
            {
                return true;
            }
            else
            {
                return false;
            }    
        } 
    }
     return false;
}

bool lectureKey::operator>(const lectureKey& target) const
{
    if ((*this == target) || (*this < target))
    {
        return false;
    }
    return true;
}