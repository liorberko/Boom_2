#ifndef LECTURE_H
#define LECTURE_H
#include "AVLnode.h"
#include "AVLtree.h"
#include "lectureKey.h"

class lecture 
{
    public:
    lectureKey key;
    AVLtree<lecture,lectureKey>* papa;
    int& getLectureID();
    int& getCourseID();
    int& getViewTime();
    lectureKey& getKey();
    bool operator<(const lecture target) const ;
    bool operator>(const lecture target) const ;
    bool operator==(const lecture target) const ;
    lecture& operator=(const lecture target) ;
    friend std::ostream& operator<<(std::ostream& out, const lecture target) ;
    lecture()  : key(0,0,0) , papa(NULL) {}
    lecture(int lectureID, int courseID, int viewTime = 0, AVLtree<lecture,lectureKey>* papa= NULL ) : key(lectureID, courseID, viewTime),  papa(papa){} 
    lecture(const lecture& target) : key(target.key.lectureID, target.key.courseID, target.key.viewTime) ,papa(target.papa){}
    ~lecture() = default;
//    {
//         if (papa != NULL)
//         {
//             papa->removeVertex(papa->find(key));
//         }
//     }
};



#endif /* LECTURE_H */