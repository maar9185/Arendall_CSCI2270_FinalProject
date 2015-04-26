#include <iostream>
#include "MovieTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

MovieTree::MovieTree()
{
    // Create the sentinal node 
    nil = new MovieNode(0);
    // Set the root to be nil 
    root = nil;
    // Make nil a black node with both children nil
    nil->isRed = false;
    nil->leftChild = nil;
    nil->rightChild = nil;
    nil->parent = nil;
    // Start op count at 1
    opCount = 1;
}

MovieTree::~MovieTree()
{
    // Delete all the nodes 
    if (root != nil)
        DeleteAll(root);
    // Delete the sentinal node 
    delete nil; 
}

/* Used to delete all nodes in the tree */
void MovieTree::DeleteAll(MovieNode * node)
{
    // clean to the left
    if (node->leftChild  != nil)
        DeleteAll(node->leftChild );
    // clean to the right
    if (node->rightChild != nil)
        DeleteAll(node->rightChild);
    // delete this node
    //cout << "deleting: " << node->key << endl;
    delete node;
}

/* Helper for the printMovieInventory recursive function */
void MovieTree::printMovieInventory()
{
    printNodeParent(root);
    opCount++;
}

/* Prints the inventory(in order traversal) */
void MovieTree::printMovieInventory(MovieNode * node)
{
    // Left Node
    if(node->leftChild !=nil)
        printMovieInventory(node->leftChild);
    cout << node->key << endl;
    
    // Right Node
    if(node->rightChild!=nil)
        printMovieInventory(node->rightChild);
    return;
}

//recursively print cities in the tree
void MovieTree::printNodeParent(MovieNode *node){
    cout<<"value: "<<node->key<<endl;
    //we can print the parent, provided the node has one
    if(node->parent!=nil)
        cout<<"  parent "<<node->parent->key<<endl;
    if(node->leftChild!=nil)
        printNodeParent(node->leftChild);
    if(node->rightChild!=nil)
        printNodeParent(node->rightChild);
}

double MovieTree::countLongestPath()
{
    int height = countLongestPath(root);
    opCount++;
    return height;
}

double MovieTree::countLongestPath(MovieNode * node)
{
    // If we hit the end, just return the count;
    if (node == nil)
        return 0;
    // Return the largest path from this point. 
    return max(countLongestPath(node->rightChild),countLongestPath(node->leftChild)) + 1;

}


void MovieTree::addMovieNode(int key)
{

    // Create the node we will be inserting
    MovieNode * newMovie = new MovieNode(key);
    newMovie->leftChild = nil;
    newMovie->rightChild = nil;
    MovieNode * x = root;
    MovieNode * y = NULL;

    // Do we have an empty tree?
    if (root == nil)
    {
        root = newMovie;
        newMovie->parent = nil;
    }
    // If the tree is not empty
    else
    {
        // Get to the end of the tree, where we need to add this node.
        while (x != nil)
        {

            y = x;
            if(newMovie->key < x->key)
                x = x->leftChild ;
            else
                x = x->rightChild;

        }

        // set the parent of this node to be the previous node.
        newMovie->parent = y;

        // Determine which child to this previous node we are at.
        if (newMovie->key < y->key)
            y->leftChild  = newMovie;
        else
            y->rightChild = newMovie;
    }

    // Update count
    opCount++;

    // Balance tree after adding this node. 
    rbAddFixup(newMovie);

    return;
}

/* used to do any necessary modifications after inserting to tree */
void MovieTree::rbAddFixup(MovieNode * node)
{
    MovieNode * uncle = NULL;

    // Set the left/right nodes to the sentinal
    node->leftChild = nil;
    node->rightChild = nil;

    // Now we restore the red-black properties. 
    while ((node != root) && (node->parent->isRed))
    {
        // If our parent is a a left child.  
        if (node->parent == node->parent->parent->leftChild)
        {
            // If node's parent is a left, y is x's right uncle. 
            uncle = node->parent->parent->rightChild;

            // Case 1, red uncle node 
            if (uncle->isRed)
            {
                // Change colors of parent,uncle,grandparent
                node->parent->isRed = false;
                uncle->isRed = false;
                node->parent->parent->isRed = true;
                // Move node up the tree. 
                node = node->parent->parent;
            }

            // Case 2/3 , black uncle node 
            else
            {
                // right child of left child 
                if (node == node->parent->rightChild)
                {
                    // Rotate the parent around node. 
                    node = node->parent;
                    leftRotate(node);
                }
                // Case 3 left child of left child
                node->parent->isRed = false;
                node->parent->parent->isRed = true;
                rightRotate(node->parent->parent);
            }
        }
        // Else if the parent is a right child. 
        else 
        {
            // If node's parent is a left, y is x's right uncle. 
            uncle = node->parent->parent->leftChild;
            // Case 1, red uncle node 
            if (uncle->isRed == true)
            {
                // Change colors of parent,uncle,grandparent
                node->parent->isRed = false;
                uncle->isRed = false;
                node->parent->parent->isRed = true;
                // Move node up the tree. 
                node = node->parent->parent;
            }

            // Case 2/3 , black uncle node 
            else
            {
                // left child of left child 
                if (node == node->parent->leftChild)
                {
                    // Rotate the parent around node. 
                    node = node->parent;
                    rightRotate(node);
                }
                // Case 3 left child of left child
                node->parent->isRed = false;
                node->parent->parent->isRed = true;
                leftRotate(node->parent->parent);
            }
        }
    }

    // Ensure the root is still black. 
    root->isRed = false;

    return;
}

void MovieTree::leftRotate(MovieNode * x)
{
    // Create a pointer for the node that is rotating left(the right child)    
    MovieNode * y = x->rightChild;

    // Set left right of x to be the left child of y. 
    x->rightChild = y->leftChild;

    // If y has a left child, set it's parent to be x.  
    if ( y->leftChild != nil)
        y->leftChild->parent = x;

    // Set y's parent to be x's parent. 
    y->parent = x->parent;

   // If x is the root, then set y to be the root. 
   if ( x->parent == nil ) 
       root = y;

   // If x is not the root, update the root to point to it's new child. 
   else
   {
        // If x was a left child, set y to be the left child. 
       if ( x == (x->parent)->leftChild ){
           x->parent->leftChild = y;
       }

       // Else if x was a right child, set y to be the right child. 
       else{
           x->parent->rightChild = y;
       }
   }
   // Now flip the nodes. 
   // Set y's left to be x. 
   y->leftChild = x;
   x->parent = y;
}

void MovieTree::rightRotate(MovieNode * x)
{
    // Create a pointer for the node that is rotating right(the left child)
    MovieNode * y = x->leftChild;
    
    // Set left child of x to be the right child of y. 
    x->leftChild = y->rightChild;

    // If y has a right child, set it's parent to be x.  
    if ( y->rightChild != nil )
        y->rightChild->parent = x;

    // Set y's parent to be x's parent. 
    y->parent = x->parent;

   // If x is the root, then set y to be the root. 
   if ( x->parent == nil ) 
       root = y;

   // If x is not the root, update the root to point to it's new child. 
   else
   {
        // If x was a left child, set y to be the left child. 
       if ( x == (x->parent)->leftChild )
       {
           x->parent->leftChild = y;
       }
       // Else if x was a right child, set y to be the right child. 
       else
       {
           x->parent->rightChild = y;
       }
   }

   // Now flip the nodes. 
   // Set y's right to be x. 
   y->rightChild = x;
   // Set x's parent to be y. 
   x->parent = y;
}

/* used to find movie information, provides info or says movie can't be found */
void MovieTree::findMovie(int key)
{
    // Find the movie
    MovieNode * foundMovie = searchMovieTree(root,key);
    if (foundMovie != nil)
    {
        cout << "Node Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << foundMovie->key<<endl;
    }
    else
        cout << "Movie not found." << endl;

    return;
}

MovieNode* MovieTree::searchMovieTree(MovieNode * node, int key)
{
    // If the node is NULL, we just return. Failed to find node.
    if (node == nil)
        return nil;
    // Return this node if it is the one we are searching for
    else if (node->key == key)
        return node;

    // Else return the correct recursive call.
    else
    {
        if(key < node->key)
            return searchMovieTree(node->leftChild ,key);

        else
            return searchMovieTree(node->rightChild,key);
    }
}


void MovieTree::deleteMovieNode(int key)
{
    // Find the movie to delete 
    MovieNode * foundMovie = searchMovieTree(root,key);

    // If the movie exists
    if (foundMovie != nil)
    {
        // Call the red black deletion function
        rbDelete(foundMovie);
        opCount++;
    }
    else
    {
        // If it doesn't exist
        cout << "Movie not found." << endl;
    }

}

void MovieTree::rbTransplant(MovieNode * u, MovieNode * v)
{
    // if u is the root, set v to be the root. 
    if (u->parent == nil)
        root = v;

    // if u is a left child, set parent's left child to be v. 
    else if (u == u->parent->leftChild)
        u->parent->leftChild = v;

    // if u is a right child
    else 
        u->parent->rightChild = v;
    
    // update the parent of v
    v->parent = u->parent;

}

void MovieTree::rbDelete(MovieNode * z)
{
    MovieNode * y = z;
    MovieNode * x = nil;
    bool yOrigColor = y->isRed;

    if (z->leftChild == nil)
    {
        x = z->rightChild;
        rbTransplant(z,z->rightChild);
    }
    else if (z->rightChild == nil)
    {
        x = z->leftChild;
        rbTransplant(z,z->leftChild);
    }
    else
    {
            // y = tree min of right
            y = z->rightChild;
            while (y->leftChild != nil)
            {
                y = y->leftChild ;
            }

            yOrigColor = y->isRed;
            x = y->rightChild;

            if (y->parent == z)
                x->parent = y;
            
            else
            {
                rbTransplant(y,y->rightChild);
                y->rightChild = z->rightChild;
                y->rightChild->parent = y;
            }
            rbTransplant(z,y);
            y->leftChild = z->leftChild;
            y->leftChild->parent = y;
            y->isRed = z->isRed;
    }

    // Actually the node. 
    delete z;
    
    // Check if we need to now fix the tree. 
    if (yOrigColor == false)
        rbDeleteFixup(x);
    
}

// node is the node we are fixing from. 
void MovieTree::rbDeleteFixup(MovieNode *node)
{
    MovieNode * w = NULL;

    // Now we restore the red-black properties. 
    while ((node != root) && (node->isRed == false))
    {
        // If we are a left child  
        if (node == node->parent->leftChild)
        {
            w = node->parent->rightChild;

            // If helper is red 
            if (w->isRed)
            {
                w->isRed = false;
                node->parent->isRed = true;
                leftRotate(node->parent);
                w = node->parent->rightChild;
            }

            // If helper's children are both black 
            if (w->leftChild->isRed == false && w->rightChild->isRed == false)
            {
                w->isRed = true;
                node = node->parent;
            }
            else 
            {
                if (w->rightChild->isRed == false)
                {
                    // case 3
                    w->leftChild->isRed = false;
                    w->isRed = true;
                    rightRotate(w);
                    w = node->parent->rightChild;
                }
                // case 4
                w->isRed = node->parent->isRed;
                node->parent->isRed = false;
                w->rightChild->isRed = false;
                leftRotate(node->parent);
                node = root; 
            }
        }

        // If we are a right child 
        else
        {

            // helper is the left child 
            w = node->parent->leftChild;
            // If helper is red 
            if (w->isRed)
            {
                w->isRed = false;
                node->parent->isRed = true;
                rightRotate(node->parent);
                w = node->parent->leftChild;
            }

            // If helper's children are both black 
            if (w->leftChild->isRed == false && w->rightChild->isRed == false)
            {
                w->isRed = true;
                node = node->parent;
            }

            else 
            {
                if (w->leftChild->isRed == false)
                {
                    // case 3
                    w->rightChild->isRed = false;
                    w->isRed = true;
                    leftRotate(w);
                    w = node->parent->leftChild;
                }

                // case 4
                w->isRed = node->parent->isRed;
                node->parent->isRed = false;
                w->leftChild->isRed = false;
                rightRotate(node->parent);
                node = root; 
            }
        }
               
    }

    node->isRed = false;
    return;
}

int MovieTree::countMovieNodes()
{
    // Determine the count
    int count = countMovieNodes(root);
    opCount++;

    return count;
}

int MovieTree::countMovieNodes(MovieNode *node)
{
    if (node == nil)
        return 0;
    return countMovieNodes(node->leftChild ) + countMovieNodes(node->rightChild) + 1;
}

bool MovieTree::isValid()
{
    //return isValid(root);
    if (rbValid(root) == 0)
    {
        return false;
    }
    else
    {
        cout << "BLACK HEIGHT: " << rbValid(root) << endl;
        return true;
    }
}


/* if return is 0 it's invalid, otherwise returns the black height */
int MovieTree::rbValid(MovieNode * node)
{
    int lh = 0;
    int rh = 0;

    // If we are at a nil node just return 1
    if (node == nil)
        return 1; 

    else
    {
        MovieNode * ln = node->leftChild;
        MovieNode * rn = node->rightChild;

        // consecutive red links 
        if (node->isRed)
        {
            if(ln->isRed || rn->isRed)
            {
                cout << "red violation\n";
                return 0;
            }
        }

        lh = rbValid(ln);
        rh = rbValid(rn);

        // black height mismatch 
        if (lh != 0 && rh != 0 && lh != rh)
        {
            cout << "Black height violation\n";
            return 0;
        }

        if (lh != 0 && rh != 0)
        {
                return node->isRed ? lh : lh + 1;
        }
        else
        {
            return 0;
        }

    }
}

MovieNode* MovieTree::chooseCurrent()
{
	return root;
}

MovieNode* MovieTree::chooseMatch()
{
	MovieNode * Match = root;
	/*while (1)
	{
		if(Match->rightChild != nil && Match->leftChild != nil)
		{
			//cout<<1<<endl;
			if(rand() % 100 > 50) 
				Match = Match->rightChild;
			else
				Match = Match->leftChild;	
		}
		else
			break;
	}*/
	int num = rand() % 100;
	if(num > 50){
		while(Match->rightChild != nil){
			Match = Match->rightChild;
		}
		while(Match->leftChild != nil){
			Match = Match->leftChild;
		}
	}
	else{
		while(Match->leftChild != nil){
			Match = Match->leftChild;
		}
		while(Match->rightChild != nil){
			Match = Match->rightChild;
		}
	}
	return Match;
}
void MovieTree::calculateScore(int score, bool flagWon)
{
	double numerator = countMovieNodes(root);
	double denominator = score;
	double val;
	
	if(flagWon == true)
	{
		val = (numerator / denominator)*100;
		// Do calculation of score
		cout<< "You Won!!!" << endl;
		cout<< "Score: " << val << endl;
	}
	else
		cout<< "You Lost, better luck next time" << endl;
}

bool MovieTree::checkNIL(MovieNode * node){
	if(node == nil)
		return true;
	return false;
}


