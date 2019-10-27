//TREE WITH ALL IMPLEMENTATIONS  TASK 1 EXAM 0 2012

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include "tree.cpp"
 
 using namespace std;

int main () {
	typedef Tree<int> iTree;
	//iTree * tree = iTree::init( 'A' )
		// ->push( 'C' )
		// ->push( 'T' )
		// ->push( 'I' )
		// ->push( 'O' )
		// ->push( 'N' )
		// ->push( 'S' )
		// ->push( 'S' )
		// ->push( 'P' )
		// ->push( 'E' )
		// ->push( 'A' )
		// ->push( 'K' )
		// ->push( 'L' )
		// ->push( 'O' )
		// ->push( 'U' )
		// ->push( 'D' )
		// ->push( 'E' )
		// ->push( 'R' )
		// ->push( 'T' )
		// ->push( 'H' )
		// ->push( 'A' )
		// ->push( 'N' )
		// ->push( 'W' )
		// ->push( 'O' )
		// ->push( 'R' )
		// ->push( 'D' )
		// ->push( 'S' )
	iTree * tree = iTree::init( 10 )
		->push( 15 )
		->push( 6 )
		->push( 2 )
		->push( 20 )
		->push( 17 )
		->push( 34 )
		->push( 1 )
		->push( 8 )
		->push( 11 )
		->push( 19 )
		->balance( )
		->print();
	cout << "size: " << tree->amount() << endl;
	delete tree;	
}

//ACTIONS SPEAK LOUDER THAN WORDS