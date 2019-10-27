#ifndef TREE_CPP
#define TREE_CPP


#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

using namespace std;

template< class TData >
class Tree {
public:
	static Tree<TData> * init( TData data, Tree<TData> * tree = nullptr ) {
		if ( tree==nullptr ) {
			return new Tree<TData> ( data );
		} else {
			return tree->push( data );
		}
	}

public:
	typedef long long TIndex;

private:
	TData data;
	Tree<TData> * left;
	Tree<TData> * right;

private:
	Tree( const TData data ): data( data ), left( nullptr ), right( nullptr ) { }
	Tree( const Tree & tree ): Tree( tree.data ) { }
	Tree(
			const TData data,
			const Tree<TData> * const left,
			const Tree<TData> * const right
		): data( data ), left( left ), right( right ) { }

public:
	~Tree( ) {
		this->clear();
	}

public:
	TData getData() const {
		return this->data;
	}
	Tree<TData> * getLeft() const {
		return this->left;
	}
	Tree<TData> * getRight() const {
		return this->right;
	}

public:
	const Tree<TData> * setLeft( TData data ) {
		this->left = new Tree<TData>( data );
		return this;
	}
	const Tree<TData> * setRight( TData data ) {
		this->right = new Tree<TData>( data );
		return this;
	}

public:
	TIndex amount() const {
		return 1 + this->amountLeft() + this->amountRight();
	}
	TIndex amountLeft() const {
		return this->left==nullptr ? 0 : this->left->amount();
	}
	TIndex amountRight() const {
		return this->right==nullptr ? 0 : this->right->amount();
	}
	TIndex amountDiff() const {
		return this->amountLeft() - this->amountRight();
	}

public:
	Tree<TData> * clear() {
		return this->clearLeft()->clearRight();
	}
	Tree<TData> * clearLeft() {
		if ( this->left!=nullptr ) {
			delete this->left;
		}
		return this;
	}
	Tree<TData> * clearRight() {
		if ( this->right!=nullptr ) {
			delete this->right;
		}
		return this;
	}

public:
	TIndex depth() const {
		TIndex Ldepth = this->depthLeft();
		TIndex Rdepth = this->depthRight();
		return 1 + ( Ldepth > Rdepth ? Ldepth : Rdepth );
	}
	TIndex depthLeft() const {
		return this->left==nullptr ? 0 : this->left->depth();
	}
	TIndex depthRight() const {
		return this->right==nullptr ? 0 : this->right->depth();
	}
	TIndex depthDiff() const {
		return this->depthLeft() - this->depthRight();
	}

public:
	Tree<TData> * balance( int it = 0 ) {
		Tree<TData> * root = this;
		// if ( root->amountDiff()>1 ) {
		// 	root = root->rotateSmallRight();
		// } else
		// if ( -root->amountDiff()>1 ) {
		// 	root = root->rotateSmallLeft();
		// } else 
		if ( root->rotateBigLeftCheck() ) {
			root = root->rotateBigLeft();
		} else if ( root->rotateBigRightCheck() ) {
			root = root->rotateBigRight();
		} else if ( root->rotateSmallLeftCheck() ) {
			root = root->rotateSmallLeft();
		} else if ( root->rotateSmallRightCheck() ) {
			root = root->rotateSmallRight();
		}
		// balance in depth
		if ( root->left!=nullptr ) {
			root->left = root->left->balance( it + 1 );
		}
		if ( root->right!=nullptr ) {
			root->right = root->right->balance( it + 1 );
		}
		return root;
	}

	Tree<TData> * print( TIndex it = 0 ) {
		auto tab = [ ]( TIndex size ) -> string {
			stringstream s;
			for ( TIndex i=0; i<size; s << "\t", i++);
			return s.str();
		};
		auto info = [ ]( Tree<TData> * tree ) -> string {
			stringstream s;
			s << tree->data;
			s << "       ( ";
			s << "dl: " << tree->depthLeft() << ", ";
			s << "dr: " << tree->depthRight() << ", ";
			s << "al: " << tree->amountLeft() << ", ";
			s << "ar: " << tree->amountRight();
			s << " ) ";
			return s.str();
		};
		cout << tab( it ) << info( this ) << endl;
		if ( this->left!=nullptr ) {
			this->left->print( it + 1 );
		} else if ( this->right!=nullptr ) {
			cout << tab( it + 1 ) << "-" << endl;
		}
		if ( this->right!=nullptr ) {
			this->right->print( it + 1 );
		} else if ( this->left!=nullptr ) {
			cout << tab( it + 1 ) << "-" << endl;
		}
		return this;
	}

	Tree<TData> * push( TData data ) {
		typedef enum { TREE_LEFT=-1, TREE_EQUAL=0, TREE_RIGHT=1 } TCompare;
		auto compare = [ ] ( TData a, TData b ) -> TCompare {
			return a > b ? TREE_LEFT : a < b ? TREE_RIGHT : TREE_EQUAL;
		};
		if ( compare( this->data, data ) == TREE_EQUAL ) {
			return this->remove();
		} else {
			for ( Tree<TData> * p=this; true; ) {
				switch ( compare( p->data, data ) ) {
					case TREE_LEFT:
						if ( p->left==nullptr ) {
							p->setLeft( data );
							return this;
						} else if ( compare( p->left->data, data ) == TREE_EQUAL ) {
							p->left = p->left->remove();
							return this;
						}
						p = p->left;
						break;
					case TREE_RIGHT:
						if ( p->right==nullptr ) {
							p->setRight( data );
							return this;
						} else if ( compare( p->right->data, data ) == TREE_EQUAL ) {
							p->right = p->right->remove();
							return this;
						}
						p = p->right;						
						break;
					case TREE_EQUAL:
					default:
						throw runtime_error( "???" );
				}
			}
		}
	}

private:
	Tree<TData> * remove() {
		Tree<TData> * left = this->left;
		Tree<TData> * right = this->right;
		this->left = nullptr;
		this->right = nullptr;
		delete this;
		// choose new one
		if ( left==nullptr ) {
			return right;
		} else if ( right==nullptr ) {
			return left;
		} else if ( left->right==nullptr ) {
			left->right = right;
			return left;
		} else if ( right->left==nullptr ) {
			right->left = left;
			return right;
		} else if ( left->amount() < right->amount() ) {
			Tree<TData> * p = right;
			for ( ; p->left!=nullptr; p=p->left );
			p->left = left;
			return right;
		} else {
			Tree<TData> * p = left;
			for ( ; p->right!=nullptr; p=p->right );
			p->right = right;
			return left;
		}
	}

	// https://ru.wikipedia.org/wiki/%D0%90%D0%92%D0%9B-%D0%B4%D0%B5%D1%80%D0%B5%D0%B2%D0%BE
	bool rotateSmallLeftCheck( ) {
		return -this->depthDiff()>1 && -this->right->depthDiff()>=0;
	}
	Tree<TData> * rotateSmallLeft( ) {
		Tree<TData> * root = this;
		Tree<TData> * right = this->right;
		Tree<TData> * rightLeft = this->right->left;
		root->right = rightLeft;
		right->left = root;
		return right;
	}
	bool rotateSmallRightCheck( ) {
		return this->depthDiff()>1 && this->left->depthDiff()>=0;
	}
	Tree<TData> * rotateSmallRight( ) {
		Tree<TData> * root = this;
		Tree<TData> * left = this->left;
		Tree<TData> * leftRight = this->left->right;
		root->left = leftRight;
		left->right = root;
		return left;
	}
	bool rotateBigLeftCheck( ) {
		return -this->depthDiff()>1 && this->right->depthDiff()>0;
	}
	Tree<TData> * rotateBigLeft( ) {
		Tree<TData> * root = this;
		Tree<TData> * right = this->right;
		Tree<TData> * rightLeft = this->right->left;
		Tree<TData> * rightLeftLeft = this->right->left->left;
		Tree<TData> * rightLeftRight = this->right->left->right;
		rightLeft->left = root;
		rightLeft->right = right;
		root->right = rightLeftLeft;
		right->left = rightLeftRight;
		return rightLeft;
	}
	bool rotateBigRightCheck( ) {
		return this->depthDiff()>1 && -this->left->depthDiff()>0;
	}
	Tree<TData> * rotateBigRight( ) {
		Tree<TData> * root = this;
		Tree<TData> * left = this->left;
		Tree<TData> * leftRight = this->left->right;
		Tree<TData> * leftRightLeft = this->left->right->left;
		Tree<TData> * leftRightRight = this->left->right->right;
		leftRight->right = root;
		leftRight->left = left;
		root->left = leftRightRight;
		left->right = leftRightLeft;
		return leftRight;
	}

};

#endif // TREE_CPP

