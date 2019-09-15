#include <iostream>
#include <stdexcept>
#include <vector>

template< class TData >
class Node {
public:
	typedef int TIndex;
private:
	TData data;
	Node * left;
	Node * right;

public:
	Node( const TData data ): data( data ), left( nullptr ), right( nullptr ) { }
	Node( const TData data, const Node * const left, const Node * const right ): data( data ), left( left ), right( right ) { }
	Node( const Node & node ): Node( node.data ) { }
	~Node( ) { }

public:
	TData getData() const {
		return this->data;
	}
	Node * getLeft() const {
		return this->left;
	}
	Node * getRight() {
		return this->right;
	}

	void setLeft( const Node & node ) {
		this->left = new Node( node );
	}
	void setRight( const Node & node ) {
		this->right = new Node( node );
	}

	void setLeft( const TData data ) {
		this->left = new Node( data );
	}
	void setRight( const TData data ) {
		this->right = new Node( data );
	}

public:
	TIndex amount() {
		return 1 + this->amountL() + this->amountR();
	}

	TIndex amountL() {
		return this->left==nullptr ? 0 : this->left->amount();
	}

	TIndex amountR() {
		return this->right==nullptr ? 0 : this->right->amount();
	}

	TIndex depth() {
		TIndex Ldepth = this->depthL();
		TIndex Rdepth = this->depthR();
		return 1 + ( Ldepth > Rdepth ? Ldepth : Rdepth );
	}

	TIndex depthL() {
		return this->left==nullptr ? 0 : this->left->depth();
	}

	TIndex depthR() {
		return this->right==nullptr ? 0 : this->right->depth();
	}

};

template< class TData >
class Tree {
private:
	typedef Node<TData> TNode;
	typedef enum { TREE_LEFT=-1, TREE_EQUAL=0, TREE_RIGHT=1 } TCmp;
private:
	TNode * root;

public:
	Tree( ): root( nullptr ) { }
	~Tree( ) {
		this->clear();
	}

public:
	void clear() {
		for ( std::vector<Node *> list( this->root ); list.size()>0; ) { 
			TNode * p = list.pop_back();
			TNode * left = p->getLeft();
			if ( left!=nullptr ) {
				list.push_back( left );
			}
			TNode * right = p->getRight();
			if ( right!=nullptr ) {
				list.push_back( right );
			}
			delete p;
		}
		this->root = nullptr;
	}

public:
	void add( TData data ) {
		if ( this->root==nullptr) {
			this->root = new Node( data );
		} else {
			auto cmp = []( TData root, TData data ) -> bool {
				return data < root ? TREE_LEFT : data > root : TREE_RIGHT : TREE_EQUAL;
			};
			for ( TNode * p = this->root; p!=nullptr; ) {
				switch ( cmp( p->getData(), data ) ) {
					case TREE_LEFT:
						if ( p->getLeft()==nullptr ) {
							p->setLeft( data );
							return;
						} else {
							p = p->getLeft();
							break;
						}
					case TREE_RIGHT:
						if ( p->getRight()==nullptr ) {
							p->setRight( data );
							return;
						} else {
							p = p->getRight();
							break;
						}
					case TREE_EQUAL:
					default:
						// TODO search where to add ...
						break;
				}

			}
		} 
	}

public:
	void balance () {
		// TODO: balance 
	}

};


int main(){
	
}