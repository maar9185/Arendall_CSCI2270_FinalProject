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
*Function prototype:*
MovieTree();
virtual ~MovieTree();

*Function description:*
These functions are the constructor and destructor for the MovieTree class.

*Example:*

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
*Function prototype:*
void printMovieInventory();

*Function description:*
Prints the Randomized created Red Black Tree.

*Example:*

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

/*
*Function prototype:*
void addMovieNode(int key);

*Function description:*
Adds a node into the tree. Then calls the rbAddFixup(MovieNode * node),
to satisfy a Red Black Tree and evenly distribute the branches.

*Example:*

MovieTree *mt = new MovieTree();

mt->addMovieNode(val);

Precondition: An integer value is the input for the addMovieNode(int key).

Post condition: Ineger is added, then the tree is fixed to satisfy the red black conditions.
*/
```
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
```

/*
*Function prototype:*
MovieNode* chooseMatch();

*Function description:*
Finds a random node with two nil children in a red black tree, and then returns that node.

*Example:*

MovieNode * Matched = new MovieNode;

Matched = mt->chooseMatch();

Precondition: Input is MovieNode*.

Post condition: Returns a random MovieNode* with two nil children.
*/

```
MovieNode* MovieTree::chooseMatch()
{
	MovieNode * Match = root;
	while (1)
	{
		if(Match->rightChild != nil || Match->leftChild != nil)
		{
			//cout<<1<<endl;

			if(rand() % 100 > 50) 
				Match = Match->rightChild;
			else
				Match = Match->leftChild;

		}
		else{
			if(Match == nil){
				Match = root;
			}
			else
				break;
		}
			
	}
	return Match;
}
```

/*
*Function prototype:*
MovieNode* chooseCurrent();

*Function description:*
Returns the root of the red black tree.

*Example:*

MovieNode * current = new MovieNode;

Matched = mt->chooseCurrent();

Precondition: There is no input, just needs to access private root.

Post condition: Returns the root of the red black tree as a *MovieNode.
*/
```
MovieNode* MovieTree::chooseCurrent()
{
	return root;
}
```

/*
*Function prototype:*
void calculateScore(int score, bool flagWon);

*Function description:*
Calculates the score of the user based off the tree's height and number of guesses.

*Example:*

MovieTree *mt = new MovieTree();

mt->calculateScore(score, flagWon);

Precondition: Input is the score (number of guesses), and a flag whether if the user
won or not.

Post condition: Calculates score and displays it to the user.
*/

```
void MovieTree::calculateScore(int score, bool flagWon)
{
	double numerator = rbValid(root);
	double denominator = score;
	double val;
	
	if(flagWon == true)
	{
		val = (numerator / (denominator+1))*100;
		// Do calculation of score
		cout<< "You Won!!!" << endl;
		cout<< "Score: " << val << endl;
	}
	else
		cout<< "You Lost, better luck next time" << endl;
}
```

/*
*Function prototype:*
bool checkNIL(MovieNode * node);

*Function description:*
Checks to see if the node is a nil (NULL).

*Example:*

MovieTree *mt = new MovieTree();

if(mt->checkNIL(current))

Precondition: Inpout is a MovieNode*.

Post condition: If node is a nil, returns true, if not, returns false.
*/

```
bool MovieTree::checkNIL(MovieNode * node){
	if(node == nil)
		return true;
	return false;
}
```
