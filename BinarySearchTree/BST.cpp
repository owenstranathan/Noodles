#include "BST.h"
#include <cstdlib>
#include <iostream>

//INSERT FUNCTION: CREATES A NEW NODE AND PASSES IT TO THE OVERLOADED INSERT FUNCTION
template <class T>
void BST<T>::insert(T value)
{
  //TEMP NODE TO USE IN PRIVATE INSERT
  BST_node<T> * newNode;

  newNode = new BST_node<T>;
  newNode->key = value;
  newNode->left = newNode->right = NULL;

  //INSERT
  insert(newNode, root);
}


//OVERLOADED INSERT FUNCTION, RECURSIVELY INSERTS A NODE INTO THE TREE
template <class T>
void BST<T>::insert(BST_node<T> * &newGuy, BST_node<T> * &rt)
{
  //IF THE NODE CALLED RT IS NULL SET IT EQUAL TO THE NEW NODE
  if(rt == NULL)
      rt = newGuy;
  //ELSE IF THE VALUE OF THE NEW GUY IS LESS THAN THE RT INSERT LEFT
  else if(newGuy->key < rt->key)
      insert(newGuy, rt->left);
  //ELSE INSERT RIGHT
  else
      insert(newGuy, rt->right);
}

//SEARCH FUNCTION: RETURNS A CALL TO THE OVERLOADED SEARCH FUNCTION
template <class T>
BST_node<T> *& BST<T>::search(T value)
{
  //Call to the overloaded recursive function
  return search(value, root);
}

//OVERLOAED SEARCH FUNCTION: SEARCHES FOR A NODE IN THE TREE AND RETURNS THE NODE IF IT FINDS IT
template <class T>
BST_node<T> *& BST<T>::search(T value, BST_node<T> *& rt)
{
  if(rt == NULL)
    {
      return rt;
    }
  else if( rt->key == value )
    {
      return rt;
    }
  else if( rt->key > value )
    {
      return search( value, rt->left );
    }
  else
    {
      return search(value, rt->right);
    }
}


// FIND_LEAST: FINDS THE LOWEST VALUED NODE IN A GIVE SUBTREE AND RETURNS IT
template <class T>
BST_node<T> *& BST<T>::find_least( BST_node<T> * rt)
{
  if(rt->left == NULL)
    {
      return rt;
    }
  else
    {
      find_least( rt->left );
    }
}

//REMOVE FUNCTION USED IN DELETION
template <class T>
void BST<T>::remove( T value )
{
  delete_node( value, root );
}

//DELETE_NODE FUNCTION: DELETES A NODE OF A  GIVEN VALUE FROM THE TREE (CALLS SEARCH, FIND_GREATEST AND FIND_LEAST)
//I USED THE CS1 AND CS 2 BOOK AS REFERENCE TO WRITE THIS FUNCTION
//BOOK TITLE: STARTING OUT WITH C++: FROM CONTROL STRUCTURES THROUGH OBJECTS 7TH EDITION
//AUTHOR: TONY GADDIS
template<class T>
void BST<T>::delete_node( T value, BST_node<T> *& rt )
{

  if(value < rt->key)
    delete_node(value, rt->left );
  else if( value > rt->key )
    delete_node( value, rt->right );
  else
    do_delete( rt );
}

//DO_DELETE USED BY DELETE NODE (ACTUALLY DOES THE DELETION JOB
template <class T>
void BST<T>::do_delete(BST_node<T> *& nodePtr )
{

  //TEMP NODE POINTER
  BST_node<T> * temp;

  //IF THE NODE IS NOT IN THE TREE
  if( nodePtr == NULL )
    {
      std::cout << "Node not found." << std::endl;
    }


  else if( nodePtr->right == NULL )
    {
      temp = nodePtr;
      nodePtr = temp->left;
      delete temp;
      temp = NULL;
    }

  //IF THE NODE HAS NO LEFT CHILD
  else if( nodePtr->left == NULL )
    {
      temp = nodePtr;
      nodePtr = temp->right;
      delete temp;
      temp = NULL;
    }

  //IF THE NODE HAS TWO CHILDREN
  else
    {
      //MOVE ONE NODE TO THE RIGHT
      temp = nodePtr->right;

      //GO TO THE LEFT MOST LEAF NODE
      temp = find_least(temp);

      //REATTACH THE LEFT SUBTREE
      temp->left = nodePtr->left;

      //POINT TEMP TO THE NODE FOR DELETION
      temp = nodePtr;

      //POINT NODEPTR TO THE RIGHT SUBTREE THUS PRESERVING THE ENTIRE TREE
      nodePtr = nodePtr->right;

      //DELETE THE NODE
      delete temp;
      temp = NULL;
    }

}

template <class T>
void BST<T>::print_inorder()
{
  print_inorder(root);
}


//OVERLOADED INORDER TRAVERSAL FUNCTION
template <class T>
void BST<T>::print_inorder( BST_node<T> * nodePtr )
{
  if(nodePtr)
    {
      //VISIT THE RIGHT SUBTREE FIRST
      print_inorder( nodePtr->right );

      //PRINT THE NODE
      std::cout << nodePtr->key << std::endl;

      //VISIT THE LEFT SUBTREE
      print_inorder( nodePtr->left );
    }
}

template <class T>
int BST<T>::depth(T value, BST_node<T> * rt)
{
  if(rt == NULL)
    {
      return -1;
    }
  else if( rt->key == value )
    {
      return 0;
    }
  else if( rt->key > value )
    {
      return 1 + depth( value, rt->left );
    }
  else
    {
      return 1 + depth(value, rt->right);
    }


}

template <class T>
T BST<T>::path_cost( T value )
{
  BST_node<T> * rt = root;

  T sum;

  while(rt->key != value || rt != NULL)
    {

      sum += rt->key;

      if(rt->key > value)
	rt = rt->left;
      else if (rt->key < value)
	 rt = rt->right;
      else
	break;
    }

  if(rt == NULL)
    return -1;

  return sum;


}

template <class T>
int BST<T>::height(BST_node<T> * rt)
{
  int lefth , righth;
  if(rt == NULL )
    return -1;

  else
    return 1 + max( height(rt->left), height(rt->right));

}


template <class T>
bool BST<T>::balanced(BST_node<T> * rt)
{
  if(rt == NULL)
    return 1;

  int lefth, righth;

  lefth = height(rt->left);
  righth = height(rt->right);

  if( abs(lefth - righth) <= 1 && balanced(rt->left) && balanced(rt->right) )
    return 1;

  else
    return 0;

}

template <class T>
int BST<T>::max(int a, int b)
{
  return ((a>=b) ? a : b);

}
