#include <iostream>
#include <stdexcept>
#include <vector>

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
	typedef int TIndex;
	typedef enum { TREE_LEFT=-1, TREE_EQUAL=0, TREE_RIGHT=1 } TCompare;

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

private:
	Tree<TData> * setLeft( Tree<TData> * tree ) {
		this->left = tree;
		return this;
	}
	Tree<TData> * setRight( Tree<TData> * tree ) {
		this->right = tree;
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

public:
	void print( TIndex it = 0 ) const {
		for ( TIndex i=0; i<it; i++) {
			std::cout << " ";
		}
		std::cout << this->data << std::endl;
		if ( this->left!=nullptr ) {
			this->left->print( it + 1 );
		}
		if ( this->right!=nullptr ) {
			this->right->print( it + 1 );
		}
	}

private:
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
		auto compare = [ ] ( TData a, TData b ) -> TCompare {
			return a < b ? TREE_LEFT : a > b ? TREE_RIGHT : TREE_EQUAL;
		};
		if ( this->data == data ) {
			return this->remove();
		} else {
			
		}
		return nullptr;
		// for ( Tree<TData> * p = this->root; p!=nullptr; ) {
		// 	switch ( cmp( p->getData(), data ) ) {
		// 		case TREE_LEFT:
		// 			if ( p->getLeft()==nullptr ) {
		// 				p->setLeft( data );
		// 				return;
		// 			} else {
		// 				p = p->getLeft();
		// 				break;
		// 			}
		// 		case TREE_RIGHT:
		// 			if ( p->getRight()==nullptr ) {
		// 				p->setRight( data );
		// 				return;
		// 			} else {
		// 				p = p->getRight();
		// 				break;
		// 			}
		// 		case TREE_EQUAL:
		// 		default:
		// 			// TODO search where to add ...
		// 			break;
		// 	}
		// }		
	}


};

// 	



// public:
// 	void balance () {
// 		// TODO: balance 
// 	}

// };


int main () {
	Tree<int> * tree = nullptr;
	tree = Tree<int>::init( 10 );
	tree->setLeft( 5 );
	tree->getLeft( )->setLeft( 3 );
	tree->getLeft( )->setRight( 7 );
	tree->setRight( 15 );
	tree->getRight( )->setLeft( 13 );
	tree->getRight( )->setRight( 17 );
	tree->print();

		
}

