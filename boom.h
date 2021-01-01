#ifndef BOOM_H
#define BOOM_H
#include "library2.h"
#include "lecture.h"
#include "AVLnode.h"
#include "AVLtree.h"
#include "course.h"


/* class boom is the primary class.
boom element contains two AVL trees. one for courses and one for lectures.
boom element contains intiger counting the number of all in all lectures (aka classes).*/

class boom
{
private:
    AVLtree<course,int> courses;
    AVLtree<lecture, lectureKey> lectures;
    int class_counter;
public:
/*constructor.*/
    boom()=default;
/*destructor.*/
    ~boom();
/*AddCourse is the function which adding new course to the boom element.
I will add the course to its place on the courses trees and will create new lectures (in the 
numOfClasses amount) and put them into lectures tree accordingly.*/
    bool AddCourse(int courseID, int numOfClasses);
/*RemoveCourse tragets course by given id.
remove this course from the courses tree and removes corresponded lectures from lectures tree.*/
    bool RemoveCourse(int courseID);
/*WatchClass adds to a specified lecture time to its time field. (means it has been watched)*/
    StatusType WatchClass(int courseID, int classID, int time);
/*TimeViewed returns the time field of a specified lecture*/
    int TimeViewed(int courseID, int classID);
/*GetMostViewedClasses returns a specified amount of classes (lectures) the been most viewed.*/
    bool GetMostViewedClasses(int numOfClasses, int *courses_array, int *classes_array);

};

#endif /* BOOM_H */