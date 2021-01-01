#ifndef AVLTREE
#define AVLTREE
#include "AVLnode.h"
#include "library.h"
#include <iostream>
/********************************************************************************/
//   This calss implements an AVL tree and its correspondends functions
/********************************************************************************/

template <class T , class M>
class AVLtree
{
    AVLnode<T, M>* rotateLeftLeft(AVLnode<T, M> *vertex);
    AVLnode<T, M>* rotateRightRight(AVLnode<T, M> *vertex);
    AVLnode<T, M>* rotateLeftRight(AVLnode<T, M> *vertex);
    AVLnode<T, M>* rotateRightLeft(AVLnode<T, M> *vertex);
    int setHeight(AVLnode<T, M> *vertex);
    void rebalance(AVLnode<T, M> *vertex);
    void setBalance(AVLnode<T, M> *vertex);

    public:
    AVLnode<T,M> *root;
    AVLnode<T, M> *biggest;
    AVLnode<T, M> *smallest;
    AVLtree();
    ~AVLtree();
    AVLnode<T,M>* getRoot();
    StatusType addVertex(AVLnode<T,M> *new_vertex);
    StatusType removeVertex(AVLnode<T,M> *new_vertex);
    StatusType applyFromRight
    (int &num, void (*doSomething)(AVLnode<T,M> *item,int* &courses,int* &classes, int &max_actions), int* &courses,int* &classes);  
    StatusType applyFromLeft
    (int &num, void (*doSomething)(AVLnode<T,M> *item,int* &courses,int* &classes, int &max_actions),int* &courses,int* &classes);  
    AVLnode<T,M>* find(M to_find);
    void printBalance();
    void printTree();
    void inOrder(AVLnode<T,M> *target, void (*doSomething)(AVLnode<T,M> *item));
    void postOrder(AVLnode<T,M> *target, void (*doSomething)(AVLnode<T,M> *item));
      // void fastRemove(AVLnode<T,M>*);

};

/**************************************/
/*      Explore function section      */
/**************************************/
//In order scanning.
template <class T, class M>
void AVLtree<T,M>::inOrder(AVLnode<T,M> *target, void (*doSomething)(AVLnode<T,M> *item)){
    if (target == nullptr)
    {
        return ;
    }
    inOrder(target->left_son,doSomething);
    doSomething(target);
    inOrder(target->right_son, doSomething);  
}

template <class T, class M>
AVLnode<T,M>* AVLtree<T,M>::getRoot(){
    return root;
}
//Post order scanning.
template <class T, class M>
void AVLtree<T,M>::postOrder(AVLnode<T,M> *target, void (*doSomething)(AVLnode<T,M> *item)){
    if (target == nullptr)
    {
        return ;
    }
    postOrder(target->left_son, doSomething);
    postOrder(target->right_son ,doSomething);
    doSomething(target);
}
//Reverse in order scanning.
template <class T, class M>
int reversInOrder(AVLnode<T,M> *target, void (*doSomething)(AVLnode<T,M> *item,int* &courses,int* &classes, int &max_actions),int &num, int* &courses,int* &classes){
    if ((target == nullptr) || (num <= 0))
    {
        return 0;
    }
    int temp = reversInOrder(target->right_son, doSomething ,num, courses,classes);
    if (num <= 0)
    {
        return temp;
    }
    doSomething(target, courses,classes,num);
    temp++;
    temp += reversInOrder(target->left_son, doSomething, num, courses,classes);
    return temp; 
}

template <class T, class M>
StatusType applyFromRightHelper
(int &num, AVLnode<T,M>* target, void (*doSomething)(AVLnode<T,M> *item,int* &courses,int* &classes, int &max_actions), int* &courses,int* &classes)  
{
    if ((target == nullptr) || (num == 0))
    {
        return SUCCESS;
    }
    doSomething(target, courses,classes, num);
    reversInOrder(target->left_son , doSomething, num , courses,classes);
    if (applyFromRightHelper(num,target->parent,doSomething, courses,classes)!=SUCCESS)
    {
        return FAILURE;
    } 
    return SUCCESS;
}
//This functions can move across an AVL tree from its biggest node ("the rightest node") and
//reverse in-order-wise while activating the called function on every node.
template <class T, class M>
StatusType AVLtree<T,M>::applyFromRight(int &num, void (*doSomething)(AVLnode<T,M> *item,int* &courses,int* &classes, int &max_actions), int* &courses,int* &classes)  
{
    return applyFromRightHelper(num, biggest, doSomething, courses,classes);
}

//In order scaning that can be constricted to certain amount of moves.
template <class T, class M>
int superInOrder(AVLnode<T,M> *target, void (*doSomething)(AVLnode<T,M> *item,int* &courses,int* &classes, int &max_actions),int &num,int* &courses,int* &classes){
    if ((target == nullptr) || (num <= 0))
    {
        return 0;
    }
    int temp = superInOrder(target->left_son, doSomething ,num, courses,classes);
    if (num <= 0)
    {
        return temp;
    }
    doSomething(target, courses,classes,num);
    temp++;
    temp += superInOrder(target->left_son, doSomething ,num, courses,classes);
    return temp; 
}

template <class T, class M>
StatusType applyFromLeftHelper(int &num, AVLnode<T,M>* target, void (*doSomething)(AVLnode<T,M> *item,int* &courses,int* &classes, int &max_actions),int* &courses,int* &classes)  
{
    if ((target == nullptr) || (num == 0))
    {
        return SUCCESS;
    }
    doSomething(target,courses,classes, num);
    superInOrder(target->right_son , doSomething, num  ,courses,classes);
    if (applyFromLeftHelper(num,target->parent,doSomething, courses,classes)!=SUCCESS)
    {
        return FAILURE;
    } 
    return SUCCESS;
}
//This functions can move across an AVL tree from its smallest node ("the leftmoset node") and
//reverse in-order-wise while activating the called function on every node.
template <class T, class M>
StatusType AVLtree<T,M>::applyFromLeft(int &num, void (*doSomething)(AVLnode<T,M> *item,int* &courses,int* &classes, int &max_actions),int* &courses,int* &classes)  
{
    return applyFromLeftHelper(num, smallest, doSomething, courses, classes);
}

/**************************************/
/*     C'tors and D'tors section      */
/**************************************/
template <class T, class M>
AVLtree<T,M>::AVLtree() : root(nullptr),biggest(nullptr),smallest(nullptr) {}

template <class T, class M> 
void deleteNode(AVLnode<T,M> *toDelete)
{
    if (toDelete != nullptr)
    {
        delete(toDelete);
    }
}

template <class T, class M>
AVLtree<T,M>::~AVLtree()
{
    postOrder(root, deleteNode);
}

/****************************************/
/*     Method implementation section    */
/****************************************/

// inserting new node (pointer to) to the tree.
template <class T, class M>
StatusType AVLtree<T,M>::addVertex(AVLnode<T,M> *new_vertex)  {
    if(root==NULL){
        root= new_vertex;
    }
    if ((biggest == nullptr) || (biggest->info < new_vertex->info))
    {
        biggest = new_vertex;
    }
    if ((smallest == nullptr) || (smallest->info > new_vertex->info))
    {
        smallest = new_vertex;
    }
    AVLnode<T,M> *current_vertex = root;
    AVLnode<T,M> *parent; // so we have a grasp on parent vertex
    while(true)
    {
        if(current_vertex->info == new_vertex->info) return SUCCESS; // this vertex already exists.
        parent=current_vertex;
        bool procede_left;
        if(current_vertex->info > new_vertex->info) procede_left = true;// if current node bigger then new node, we need to go left.
        else procede_left = false;// else we need to go right
        current_vertex = procede_left ? current_vertex->left_son : current_vertex->right_son;
        //when adding a new vertex it must become a leaf at first
        if(current_vertex==NULL)
        { // we made it all the way down to find new leaf spot
            if ((parent->left_son == nullptr ) && (parent->right_son == nullptr)) parent->height++;
            if(procede_left){
                parent->left_son = new_vertex;
            }
            else{
                parent->right_son = new_vertex;
            }
            new_vertex->parent=parent;
            setBalance(parent);
            new_vertex->height=0;
            //parent->height++;
            while(parent->parent != NULL && parent->height == parent->parent->height){
                //if the height of the parent of the vertex is bigger by 1 from the vertex's height then the
                //the tree above is already balanced.
                parent=parent->parent;
                rebalance(parent);
                parent->height=setHeight(parent);
            }
            while(parent != NULL)
            {
                setBalance(parent);
                parent=parent->parent;
            }
            break;
        }
    }
return SUCCESS;
}
//Rotation to the right
template <class T, class M>
AVLnode<T,M>* AVLtree<T, M>::rotateLeftLeft(AVLnode<T,M> *vertex){
    AVLnode<T,M> *p=vertex->parent;
    AVLnode<T,M> *b=vertex->left_son;
    if(b->right_son!=NULL) b->right_son->parent=vertex;
    vertex->left_son = b->right_son;
    b->right_son=vertex;
    vertex->parent=b;
    b->parent=p;
    if(p!=NULL){
        if(p->left_son==vertex){
            p->left_son=b;
        }
        else{
            p->right_son=b;
        }
    }
    else{
        root=b;
    }
    vertex->height = setHeight(vertex);
    b->height=setHeight(b);
    setBalance(vertex);
    setBalance(b);
    return b;
}
//Rotation to the left
template <class T, class M>
AVLnode<T,M>* AVLtree<T,M>::rotateRightRight(AVLnode<T,M> *vertex){
    AVLnode<T,M> *p=vertex->parent;
    AVLnode<T,M> *c=vertex->right_son;
    if(c->left_son!=NULL) c->left_son->parent=vertex;
    vertex->right_son = c->left_son;
    c->left_son=vertex;
    vertex->parent=c;
    c->parent=p;
    if(p!=NULL){
        if(p->right_son==vertex){
            p->right_son=c;
        }
        else{
            p->left_son=c;
        }
    }
    else
    {
        root = c;
    }
    vertex->height = setHeight(vertex);
    c->height=setHeight(c);
    setBalance(vertex);
    setBalance(c);
    return c;
    
}
//Left - right rotation
template<class T, class M>
AVLnode<T,M>* AVLtree<T,M>::rotateLeftRight(AVLnode<T,M> *vertex){
    vertex->left_son=rotateRightRight(vertex->left_son);
    rotateLeftLeft(vertex);
    return vertex;
}
//Right - left rotation
template<class T, class M>
AVLnode<T,M>* AVLtree<T,M>::rotateRightLeft(AVLnode<T,M> *vertex){
    vertex->right_son=rotateLeftLeft(vertex->right_son);
    rotateRightRight(vertex);
    return vertex;
}
// Determines a given vertex highet in current position in tree.
template<class T, class M>
int AVLtree<T,M>::setHeight(AVLnode<T,M> *vertex){
    if(vertex==NULL){
        return -1;
    }
    if ( vertex->left_son == nullptr && vertex->right_son == nullptr)
    {
        return 0;
    }
    else if(vertex->left_son == nullptr)
    {
        return (vertex->right_son->height +1);
    }
    else if (vertex->right_son == nullptr)
    {
        return (vertex->left_son->height +1);
    }
    return 1+std::max(vertex->left_son->height, vertex->right_son->height);
}
// Determines a given vertex balance in current position in tree.
template <class T, class M>
void AVLtree<T,M>::setBalance(AVLnode<T,M> *vertex) {
    if ( vertex->left_son == nullptr && vertex->right_son == nullptr)
    {
        vertex->balance=0;
        return;
    }
    else if(vertex->left_son == nullptr)
    {
        vertex->balance = -1 - vertex->right_son->height;
        return;
    }
    else if (vertex->right_son == nullptr)
    {
        vertex->balance = vertex->left_son->height + 1;
        return;
    }
    else vertex->balance = vertex->left_son->height - vertex->right_son->height;
}
//This function is rebalancing the AVL tree, using rotations.
template <class T, class M>
void AVLtree<T,M>::rebalance(AVLnode<T,M> *vertex){
    setBalance(vertex);
    if(vertex->balance==-2){
        vertex->right_son->balance<=0 ? rotateRightRight(vertex) : rotateRightLeft(vertex);
    }
    if(vertex->balance==2){
        vertex->left_son->balance>=0 ? rotateLeftLeft(vertex) : rotateLeftRight(vertex);
    }
}
// Removing new node (pointer to) to the tree.
template <class T, class M>
StatusType AVLtree<T,M>::removeVertex(AVLnode<T,M> *ver_to_remove)
{
    if(ver_to_remove->parent==nullptr && ver_to_remove->right_son==nullptr && ver_to_remove->left_son==nullptr){
        if (ver_to_remove == root)
        {
            smallest=nullptr;
            biggest=nullptr;
            root = nullptr;
            return SUCCESS;
        }
        else
        {
            return SUCCESS; 
        }
        
    }
    if(ver_to_remove == smallest && ver_to_remove -> right_son != nullptr) smallest = ver_to_remove->right_son;
    else if(ver_to_remove == smallest && ver_to_remove -> parent != nullptr) smallest = ver_to_remove->parent;
    if(ver_to_remove == biggest && ver_to_remove->left_son != nullptr) biggest = ver_to_remove->left_son;
    else if(ver_to_remove==biggest && ver_to_remove->parent != nullptr) biggest = ver_to_remove->parent;
    AVLnode<T,M> *to_fix;
    if ((ver_to_remove->right_son == nullptr) &&(ver_to_remove->left_son == nullptr))
    {
        if (ver_to_remove->parent != nullptr)
        {
            if(ver_to_remove->parent->right_son == ver_to_remove)
            {
                ver_to_remove->parent->right_son = nullptr;
            }
            else 
            {
                ver_to_remove->parent->left_son = nullptr;
            }
        }
        to_fix = ver_to_remove->parent;
        if (ver_to_remove == root)
        {
            root = nullptr;
        }
    }
    else if ((ver_to_remove->right_son == nullptr)  && !(ver_to_remove->left_son == nullptr))
    {
        if (ver_to_remove->parent != nullptr)
        {
            if(ver_to_remove->parent->right_son == ver_to_remove)
            {
                ver_to_remove->parent->right_son = ver_to_remove->left_son;
            }
            else 
            {
                ver_to_remove->parent->left_son = ver_to_remove->left_son;
            }
        }
        ver_to_remove->left_son->parent = ver_to_remove->parent;
        to_fix = ver_to_remove->left_son;
        if (ver_to_remove == root)
        {
            root = ver_to_remove->left_son;
        }
    }
    else if (!(ver_to_remove->right_son == nullptr)  && (ver_to_remove->left_son == nullptr))
    {
        if (ver_to_remove->parent != nullptr)
        {
            if(ver_to_remove->parent->right_son == ver_to_remove)
            {
                ver_to_remove->parent->right_son = ver_to_remove->right_son;
            }
            else 
            {
                ver_to_remove->parent->left_son = ver_to_remove->right_son;
            }
        }
        ver_to_remove->right_son->parent = ver_to_remove->parent;
        to_fix = ver_to_remove->right_son;
        if (ver_to_remove == root)
        {
            root = ver_to_remove->right_son;
        }
    }
    else
    {
        AVLnode<T,M> * temp1 = ver_to_remove->right_son;
        AVLnode<T,M> * temp2 = temp1->left_son;
        AVLnode<T,M> * temp3 = temp1->right_son;
        while (temp2 != nullptr)
        {
            temp3 = temp2->right_son;
            temp1 = temp2;
            temp2 = temp2->left_son;
        }
        if(temp1->parent->right_son == temp1)
        {
            temp1->parent->right_son = temp3;
            if (temp3 != nullptr)
            {
                temp3->parent = temp1->parent;
            }
        }
        else    
        {
            temp1->parent->left_son = temp3;
            if (temp3 != nullptr)
            {
                temp3->parent = temp1->parent;
            }
        }
        temp1->right_son = ver_to_remove->right_son;
        if (temp1->right_son != nullptr)
        {
            temp1->right_son->parent = temp1;
        }
        temp1->left_son = ver_to_remove->left_son;
        if (temp1->left_son != nullptr)
        {
            temp1->left_son->parent = temp1;
        }
        to_fix = temp1->parent;
        if (root == ver_to_remove)
        {
            root = temp1;
            temp1->parent = nullptr;
            if (temp1->right_son != nullptr)
            {
                to_fix = temp1->right_son;
            }
            else
            {
                to_fix = temp1;
            }
        }
        else
        {
            temp1->parent = ver_to_remove->parent;
            if(ver_to_remove->parent->right_son == ver_to_remove)
            {
                ver_to_remove->parent->right_son = temp1;
            }
            else 
            {
                ver_to_remove->parent->left_son = temp1;
            }
        }
    }
    AVLnode<T,M> *to_fix_balance = to_fix;
    while(to_fix_balance != NULL)
    {
        to_fix_balance->height = setHeight(to_fix_balance);
        setBalance(to_fix_balance);
        to_fix_balance=to_fix_balance->parent;
    }
    while (to_fix != nullptr)
    {
        rebalance(to_fix);
        to_fix = to_fix->parent;
    }
    ver_to_remove->parent = nullptr;
    ver_to_remove->right_son = nullptr;
    ver_to_remove->left_son = nullptr;
return SUCCESS;
}
template <class T, class M>
AVLnode<T,M>* findHelper(AVLnode<T,M>* begin, M to_find){
    if (begin == nullptr)
    {
        return nullptr;
    }
    if(begin->key == to_find) return begin;
    if(begin->key > to_find) return findHelper(begin->left_son,to_find);
    if(begin->key < to_find) return findHelper(begin->right_son, to_find);
    return nullptr;
} 
//Given an ID, finds ID's node.
template <class T, class M>
AVLnode<T,M>* AVLtree<T,M>::find(M to_find)
{
    return findHelper(root, to_find);
}
//testing helper (printer)
// template <class T, class M>
// void printVertex(AVLnode<T,M> *vertex) {
//     std::cout <<"info: ";
//     std::cout << vertex->info << std::endl;
//     std::cout <<"hieght: ";
//     std::cout <<vertex->height<< std::endl;
//     std::cout <<"balance: ";
//     std::cout <<vertex->balance<< std::endl;
//     std::cout <<"left son: ";
//     if (vertex->left_son != nullptr) 
//     {
//         std::cout <<vertex->left_son->info<< std::endl;
//     }
//     else 
//     {
//         std::cout << "no left son" << std::endl;
//     }
//     std::cout <<"right son: ";
//     if(vertex->right_son != nullptr){
//         std::cout <<vertex->right_son->info<< std::endl;
//     }
//     else std::cout<<"no right son" << std::endl;
//     std::cout <<"parent: ";
//     if (vertex->parent != nullptr)
//     {
//         std::cout <<vertex->parent->info<< std::endl;
//     }
//     else
//     {
//         std::cout << "I am the groot"<<std::endl;
//     }
    
//     std::cout << std::endl;
// }
//testing helper (printer)
// template <class T, class M>
// void AVLtree<T,M>::printTree() {
//     inOrder(root,printVertex);
//     std::cout <<"the end"<< std::endl;
// }

#endif  