#include "boom.h"

bool boom::AddCourse (int courseID, int numOfClasses)
{
    AVLnode<course,int>*check= courses.find(courseID);
    if(check != nullptr) return false;
    course new_course(courseID,numOfClasses);
    AVLnode<course, int>* new_ver = new AVLnode<course, int>(new_course, courseID);
    courses.addVertex(new_ver);
    class_counter+=numOfClasses;
    return true;
}

void inorderDelete(AVLnode<course,int>* node){
    if (node == nullptr) return;
    inorderDelete(node->left_son);
    inorderDelete(node->right_son);
    AVLnode<lecture, lectureKey>** courses = node->info.getLectures();
    for(int i=0; i<node->info.getNumOfClasses() ; i++)
    {
        delete courses[i];
    }
    delete[] courses;

}
boom::~boom()
{
    inorderDelete(courses.getRoot());
    lectures.root=nullptr;
}

bool boom::RemoveCourse(int courseID)
{
    AVLnode<course,int>* course_to_delete = courses.find(courseID);
    if(course_to_delete == nullptr) return false;
    class_counter-=course_to_delete->info.getNumOfClasses();
    AVLnode<lecture, lectureKey>** lectures_to_delete = course_to_delete->info.getLectures();
    int num_of_classes = course_to_delete->info.getNumOfClasses();
    for(int i=0; i<num_of_classes;i++){
        StatusType control=lectures.removeVertex(lectures_to_delete[i]);
        if (lectures_to_delete[i] != NULL)
        {
            delete (lectures_to_delete[i]);
        }
        if(control!=SUCCESS) return false;
    }
    delete[] lectures_to_delete;
    StatusType control=courses.removeVertex(course_to_delete);
    delete (course_to_delete);
    if(control==SUCCESS) return true;
    return false;
}

StatusType boom::WatchClass(int courseID, int classID, int time)
{   
    AVLnode<course,int>* temp = courses.find(courseID);
    if(temp == nullptr) return FAILURE;
    if (temp->info.getNumOfClasses() < (classID +1))
    {
        return INVALID_INPUT;
    }
    AVLnode<lecture, lectureKey>* lec = (temp->info.getLectures())[classID];
    if (lectures.removeVertex(lec) != SUCCESS) return FAILURE;
    lec->info.getViewTime() += time;
    lec->key.viewTime += time;
    if (lectures.addVertex(lec) != SUCCESS) return FAILURE;
    lec->info.papa = &lectures;
    return SUCCESS;
}

int boom::TimeViewed(int courseID, int classID){
    AVLnode<course,int>* wanted_course = courses.find(courseID);
    if (wanted_course == NULL) return -1;
    if (wanted_course->info.getNumOfClasses() <= classID) return -2;
    AVLnode<lecture, lectureKey>** wanted_course_lectures = wanted_course->info.getLectures();
    int TimeViewed = wanted_course_lectures[classID]->info.getViewTime();
    return TimeViewed;
}

void recieveFromLecturesTree(AVLnode<lecture,lectureKey> *item,int* &courses,int* &classes,int &max_actions){
    if (max_actions <= 0) return;
    *classes=item->info.getLectureID();
    classes++;
    *courses=item->info.getCourseID();
    courses++; 
    max_actions--;  
}

void recieveFromCoursesTree(AVLnode<course,int> *item,int* &courses,int* &classes, int &max_actions)
{
    for (int i = 0; ((i < item->info.getNumOfClasses()) && (max_actions > 0)) ; i++ )
    {
        if ((item->info.getLectures()[i])->info.getViewTime() == 0)
        {
            *courses = item->info.getCourseID();
            courses++;
            *classes = i;
            classes++;
            max_actions--;
        }
    }
}

bool boom::GetMostViewedClasses(int numOfClasses, int *courses_array, int *classes_array)
{   
    if (class_counter < numOfClasses)
    {
        return false;
    }
    lectures.applyFromRight(numOfClasses,recieveFromLecturesTree, courses_array,classes_array);
    //starting with lectures that known to be watched.
    courses.applyFromLeft(numOfClasses, recieveFromCoursesTree, courses_array,classes_array);
    return true;
}


