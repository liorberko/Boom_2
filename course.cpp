#include "course.h"


bool course::operator<(const course &target) const {
    if (courseID < target.courseID)
    {
        return true;
    }
    return false;
}

bool course::operator>(const course &target) const {
    if(courseID>target.courseID) return true;
    return false;
}
bool course::operator==(const course &target) const
{
    if (courseID == target.courseID)
    {
        return true;
    }
    return false;
}
course& course::operator=(const course &target) 
{
    if (this == &target)
    {
        return *this;
    }
    courseID = target.courseID;
    num_of_classes = target.num_of_classes;
    lectures = target.lectures;
    // array<AVLnode<lecture, lectureKey>*>* new_lectures = new array<AVLnode<lecture, lectureKey>*>(num_of_classes);
    // try 
    // {
    //     for (int i=0; i < num_of_classes ; i++ )
    //     {
    //         AVLnode<lecture, lectureKey>* temp = new AVLnode<lecture, lectureKey>(target.lectures[i]);
    //         (*new_lectures)[i] = temp;
    //     } 
    // } catch (...) {
    //     delete[] new_lectures;
    //     throw;
    // }
    // delete (&lectures);
    // lectures = *new_lectures;
    return *this;
}
std::ostream& operator<<(std::ostream& out, const course target) 
{
    out<< target.courseID;
    return out;
}

int course::getCourseID()
{
    return courseID;
}

int course::getNumOfClasses()
{
    return num_of_classes;
}

AVLnode<lecture, lectureKey>** course::getLectures()
{
    return lectures;
}

// course::~course()
// {
//     for(int i=0; i<num_of_classes ; i++)
//     {
//         if(lectures[i] != NULL)
//         {
//             delete (lectures[i]);
//         }
//     }
// }