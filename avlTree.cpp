#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>


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
	Tree<TData> * print( TIndex it = 0 ) {
		auto tab = [ ]( TIndex size ) -> std::string {
			std::stringstream s;
			for ( TIndex i=0; i<size; s << "\t", i++);
			return s.str();
		};
		std::cout << tab( it ) << this->data << std::endl;
		if ( this->left!=nullptr ) {
			this->left->print( it + 1 );
		} else if ( this->right!=nullptr ) {
			std::cout << tab( it + 1 ) << "-" << std::endl;
		}
		if ( this->right!=nullptr ) {
			this->right->print( it + 1 );
		} else if ( this->left!=nullptr ) {
			std::cout << tab( it + 1 ) << "-" << std::endl;
		}
		return this;
	}

private:
	Tree<TData> * setLeft( Tree<TData> * tree ) {
		this->left = tree;
		return this;
	}
	Tree<TData> * setRight( Tree<TData> * tree ) {
		this->right = tree;
		return this;
	}
	Tree<TData> * remove() {
		Tree<TData> * left = this->left;
		Tree<TData> * right = this->right;
		this->setLeft( nullptr )->setRight( nullptr );
		delete this;
		// choose new one
		if ( left==nullptr ) {
			return right;
		} else if ( right==nullptr ) {
			return left;
		} else if ( left->right==nullptr ) {
			return left->setRight( right );
		} else if ( right->left==nullptr ) {
			return right->setRight( left );
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

public:
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
							p->setLeft( p->left->remove() );
							return this;
						}
						p = p->left;
						break;
					case TREE_RIGHT:
						if ( p->right==nullptr ) {
							p->setRight( data );
							return this;
						} else if ( compare( p->right->data, data ) == TREE_EQUAL ) {
							p->setRight( p->right->remove() );
							return this;
						}
						p = p->right;						
						break;
					case TREE_EQUAL:
					default:
						throw std::runtime_error( "???" );
				}
			}
		}
	}

private:
// public:
	// https://ru.wikipedia.org/wiki/%D0%90%D0%92%D0%9B-%D0%B4%D0%B5%D1%80%D0%B5%D0%B2%D0%BE
	Tree<TData> * rotateLeft( ) {
		Tree<TData> * root = this;
		Tree<TData> * right = this->right;
		Tree<TData> * rightLeft = this->right->left;
		root->setRight( rightLeft );
		right->setLeft( root );
		return right;
	}
	Tree<TData> * rotateRight( ) {
		Tree<TData> * root = this;
		Tree<TData> * left = this->left;
		Tree<TData> * leftRight = this->left->right;
		root->setLeft( leftRight );
		left->setRight( root );
		return left;
	}
	Tree<TData> * rotateBigLeft( ) {
		return this;
	}
	Tree<TData> * rotateBigRight( ) {
		return this;
	}

public:
	Tree<TData> * balance( ) {
		if ( this->amountDiff()>1 && this->left->amountDiff()>=0 ) {
			// small right routation
			return this->rotateRight();
		}
		else if ( -this->amountDiff()>1 && -this->left->amountDiff()>=0 ) {
			// small left routation
			return this->rotateLeft();
		}
		// if ( fabs( this->amountDiff() ) <= 1 ) {

		// }
		return this;
	}
};





int main () {
	typedef Tree<int> iTree;
	iTree * tree = iTree::init( 10 )
		->push( 5 )
		->push( 15 )
		->push( 3 )
		->push( 7 )
		->push( 17 )
		->push( 13 )
		->push( 19 )
		->push( 29 )
		->push( 22 )
		->push( 23 )
		// ->rotateLeft()
		->print();
	delete tree;	
}

