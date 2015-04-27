# Arendall_CSCI2270_FinalProject

## Matthew Arendall
## Tree Maze Wizard

##Project Documentation

**MovieTree Class Public Functions**

```
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
```

/*
Function prototype:
MovieTree();
virtual ~MovieTree();

Function description:
These functions are the constructor and destructor for the MovieTree class.

Example:
MovieTree *mt = new MovieTree();

Precondition: Nothing is established or initialized.
Post condition: Varaibles are given inital conditions and at the end everything is removed.
*/
```
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
```

/*
Function prototype:
void printMovieInventory();

Function description:
Prints the Randomized created Red Black Tree.

Example:
MovieTree *mt = new MovieTree();
mt->printMovieInventory();

Precondition: Nothing is printed.
Post condition: Tree is printed, each node listing its parent
*/
```
void MovieTree::printMovieInventory()
{
    printNodeParent(root);
    opCount++;
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
```
