#ifndef BST_H
#define BST_H


//INCLUDES
#include <cstdlib>


//CLASS DEFINITONS
template <class T>
struct BST_node
{
public:
  //data Memebers
  T key;
  BST_node<T> * left;
  BST_node<T> * right;
};

//Tree container
template <class T>
class BST
{
 public:
  //root
  BST_node<T> * root;

  //FUNCTIONS:

  //CONSTRUCTOR
  BST() : root(NULL){}
  //INSERT
  void insert(T value);
  void insert(BST_node<T> *& , BST_node<T> *&);

  //SEARCH
  BST_node<T> *& search( T );
  BST_node<T> *& search( T , BST_node<T> *& );

  //DELETE
  void remove( T );
  void delete_node( T , BST_node<T>*& );
  void do_delete( BST_node<T> *& );

  //SPECIFIC SEARCH FUNCTIONS

  //LEAST
  BST_node<T> *& find_least( BST_node<T> *);

  //INORDER TRAVERSAL
  void print_inorder();
  void print_inorder( BST_node<T> * ) ;

  //DEPTH FUNCTION
  int depth( T , BST_node<T> * rt );

  //PATH COST FUNCTION
  T path_cost( T );


  //Balanced
  int height(BST_node<T> *);
  bool balanced(BST_node<T> *);
  int max(int, int);

};

#endif
