#ifndef MOVIETREE_H
#define MOVIETREE_H

#include <json/json.h>
#include <vector>

using namespace std;

struct MovieNode{
    int key;
    bool isRed;
    MovieNode *parent;
    MovieNode *leftChild;
    MovieNode *rightChild;

    MovieNode(){};

    MovieNode(int in_key)
    {
        key = in_key;
        // Now that we are using nil these NULL's should be overwritten in addMovieNode.
    	leftChild = NULL;
    	rightChild = NULL;
        parent = NULL;
        isRed = true;
    }

};

class MovieTree
{
        int opCount;

    public:
        MovieTree();
        virtual ~MovieTree();
        void printMovieInventory();
        int countMovieNodes();
        void deleteMovieNode(int key);
        void addMovieNode(int key);
        void findMovie(int key);
        bool isValid();
        double countLongestPath();
        MovieNode* chooseMatch();
        MovieNode* chooseCurrent();
        void calculateScore(int score, bool flagWon);
        bool checkNIL(MovieNode * node);

    protected:

    private:
        void DeleteAll(MovieNode * node); //use this for the post-order traversal deletion of the tree
        void printMovieInventory(MovieNode * node);//, json_object * traverseLog);
        void printNodeParent(MovieNode *node);
        void rbAddFixup(MovieNode * node); // called after insert to fix tree
        void leftRotate(MovieNode * x);
        void rbDelete(MovieNode * z);
        void rightRotate(MovieNode * x);
        void rbDeleteFixup(MovieNode * node);
        void rbTransplant(MovieNode * u, MovieNode * v);
        int rbValid(MovieNode * node);
        int countMovieNodes(MovieNode *node);
        double countLongestPath(MovieNode *node);
        MovieNode* searchMovieTree(MovieNode * node, int key);//, json_object * traverseLog);
        MovieNode *root;
        MovieNode *nil;


};

#endif // MOVIETREE_H
