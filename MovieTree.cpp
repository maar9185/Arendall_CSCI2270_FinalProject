#include <iostream>
#include "MovieTree.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

MovieTree::MovieTree()
{
    // Create the sentinal node 
    nil = new MovieNode(0,"NIL",0,0);
    // Set the root to be nil 
    root = nil;
    // Make nil a black node with both children nil
    nil->isRed = false;
    nil->leftChild = nil;
    nil->rightChild = nil;
    // Start op count at 1
    opCount = 1;
    // Create our json object. 
    Assignment6Output = json_object_new_object();
}

MovieTree::~MovieTree()
{
    // Delete all the nodes 
    if (root != nil)
        DeleteAll(root);
    // Delete the sentinal node 
    delete nil; 

    // Clean up json object
    json_object_put(Assignment6Output);
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
    cout << "deleting: " << node->title << endl;
    delete node;
}

/* Helper for the printMovieInventory recursive function */
void MovieTree::printMovieInventory()
{
    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();
    json_object * travLog = json_object_new_array();

    printMovieInventory(root,travLog);

    // Update our json object
    json_object *jsonOperation = json_object_new_string("traverse");
    json_object_object_add(newJSON,"operation",jsonOperation);
    json_object_object_add(newJSON,"output",travLog);
    json_object_object_add(Assignment6Output,to_string(opCount).c_str(),newJSON);

    opCount++;
}

/* Prints the inventory(in order traversal) */
void MovieTree::printMovieInventory(MovieNode * node, json_object * traverseLog)
{

    // Left Node
    if(node->leftChild !=nil)
        printMovieInventory(node->leftChild ,traverseLog);

    cout << node->title << endl;
       
    // Update the traversal log
    json_object *curTitle = json_object_new_string(node->title.c_str());
    json_object_array_add(traverseLog, curTitle);

    // Right Node
    if(node->rightChild!=nil)
        printMovieInventory(node->rightChild,traverseLog);

    return;
}


int MovieTree::countLongestPath()
{
    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();

    int height = countLongestPath(root);


    // Update our json object
    json_object *jsonOperation = json_object_new_string("height");
    json_object_object_add(newJSON,"operation",jsonOperation);
    json_object *jsonOutput = json_object_new_string(to_string(height).c_str());
    json_object_object_add(newJSON,"output",jsonOutput);
    json_object_object_add(Assignment6Output,to_string(opCount).c_str(),newJSON);
    opCount++;

    return height;
}

int MovieTree::countLongestPath(MovieNode * node)
{
    // If we hit the end, just return the count;
    if (node == nil)
        return 0;
    // Return the largest path from this point. 
    return max(countLongestPath(node->rightChild),countLongestPath(node->leftChild)) + 1;

}


void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity)
{
    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();
    // Create a log for the traversal
    json_object * travLog = json_object_new_array();

    // Create the node we will be inserting
    MovieNode * newMovie = new MovieNode(ranking,title,releaseYear,quantity);
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
            // Add the current node to the traversal log before moving to next.
            json_object *curTitle = json_object_new_string(x->title.c_str());
            json_object_array_add(travLog, curTitle);

            y = x;
            if(newMovie->title.compare(x->title) < 0)
                x = x->leftChild ;
            else
                x = x->rightChild;

        }

        // set the parent of this node to be the previous node.
        newMovie->parent = y;

        // Determine which child to this previous node we are at.
        if (newMovie->title.compare(y->title) < 0)
            y->leftChild  = newMovie;
        else
            y->rightChild = newMovie;
    }

    // Update our json object
    json_object *jsonOperation = json_object_new_string("add");
    json_object_object_add(newJSON,"operation",jsonOperation);
    json_object *jsonTitle = json_object_new_string(title.c_str());
    json_object_object_add(newJSON,"parameter",jsonTitle);
    json_object_object_add(newJSON,"output",travLog);
    json_object_object_add(Assignment6Output,to_string(opCount).c_str(),newJSON);
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
void MovieTree::findMovie(std::string title)
{
    // Create a traversal log
    json_object * travLog = json_object_new_array();
    // Find the movie
    MovieNode * foundMovie = searchMovieTree(root,title,travLog);
    if (foundMovie != nil)
    {
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << foundMovie->ranking << endl;
        cout << "Title:" << foundMovie->title << endl;
        cout << "Year:" << foundMovie->year << endl;
        cout << "Quantity:" << foundMovie->quantity << endl;
    }
    else
        cout << "Movie not found." << endl;

    return;
}

MovieNode* MovieTree::searchMovieTree(MovieNode * node, std::string title, json_object * traverseLog)
{
    // Add the current node to the traverse log
    if (node != nil)
    {
        json_object *curTitle = json_object_new_string(node->title.c_str());
        json_object_array_add(traverseLog, curTitle);
    }

    // If the node is NULL, we just return. Failed to find node.
    if (node == nil)
        return nil;
    // Return this node if it is the one we are searching for
    else if (node->title == title)
        return node;

    // Else return the correct recursive call.
    else
    {
        if(title.compare(node->title) < 0)
            return searchMovieTree(node->leftChild ,title,traverseLog);

        else
            return searchMovieTree(node->rightChild,title,traverseLog);
    }
}

void MovieTree::rentMovie(std::string title)
{
    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();

    int stockOutput = 0;

    json_object * travLog = json_object_new_array();
    MovieNode * foundMovie = searchMovieTree(root,title,travLog);

    // If the movie exists.
    if (foundMovie != nil)
    {
        // If it's in stock.
        if (foundMovie->quantity > 0)
        {
            cout << "Movie has been rented." << endl;
            foundMovie->quantity--;
            stockOutput = foundMovie->quantity;

            // Update our json object
            json_object *jsonOperation = json_object_new_string("rent");
            json_object_object_add(newJSON,"operation",jsonOperation);
            json_object *jsonTitle = json_object_new_string(title.c_str());
            json_object_object_add(newJSON,"parameter",jsonTitle);
            json_object *jsonOutput = json_object_new_string(to_string(stockOutput).c_str());
            json_object_object_add(newJSON,"output",jsonOutput);
            json_object_object_add(Assignment6Output,to_string(opCount).c_str(),newJSON);

            opCount++;

            //change this to print information
            cout << "Movie Info:" << endl;
            cout << "===========" << endl;
            cout << "Ranking:" << foundMovie->ranking << endl;
            cout << "Title:" << foundMovie->title << endl;
            cout << "Year:" << foundMovie->year << endl;
            cout << "Quantity:" << foundMovie->quantity << endl;
            // If the stock is 0 delete the movie
            if (foundMovie->quantity == 0)
                deleteMovieNode(foundMovie->title);

        }
        // If it's not in stock.
        else
            cout << "Movie out of stock." << endl;

    }
    // If it doesn't exist.
    else
        cout << "Movie not found." << endl;

}


void MovieTree::deleteMovieNode(std::string title)
{
    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();

    // Create our traverse log
    json_object * travLog = json_object_new_array();

    // Find the movie to delete 
    MovieNode * foundMovie = searchMovieTree(root,title,travLog);

    // If the movie exists
    if (foundMovie != nil)
    {
        // Call the red black deletion function
        rbDelete(foundMovie);

        // Update our json object
        json_object *jsonOperation = json_object_new_string("delete");
        json_object_object_add(newJSON,"operation",jsonOperation);
        json_object *jsonTitle = json_object_new_string(title.c_str());
        json_object_object_add(newJSON,"parameter",jsonTitle);
        json_object_object_add(newJSON,"output",travLog);
        json_object_object_add(Assignment6Output,to_string(opCount).c_str(),newJSON);
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
    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();

    // Determine the count
    int count = countMovieNodes(root);

    // Update our json object
    json_object *jsonOperation = json_object_new_string("count");
    json_object_object_add(newJSON,"operation",jsonOperation);
    json_object *jsonOutput = json_object_new_string(to_string(count).c_str());
    json_object_object_add(newJSON,"output",jsonOutput);
    json_object_object_add(Assignment6Output,to_string(opCount).c_str(),newJSON);
    opCount++;

    return count;
}

int MovieTree::countMovieNodes(MovieNode *node)
{
    if (node == nil)
        return 0;
    return countMovieNodes(node->leftChild ) + countMovieNodes(node->rightChild) + 1;
}

json_object* MovieTree::getJsonObject()
{
    return Assignment6Output;
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
