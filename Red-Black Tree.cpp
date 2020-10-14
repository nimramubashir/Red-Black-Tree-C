# include <iostream>
using namespace std;

struct Node
{
	int data;
	char colour; 
	Node * left; 
	Node * right; 

	Node()
	{
		colour = 'r'; 
		left = nullptr; 
		right = nullptr; 
	}
};

class Tree
{
	Node * root; 

	void Inorder(Node *  temp)
	{
		if (temp != nullptr)
		{
			Inorder(temp->left);
			cout << temp->data << " ";
			cout << temp->colour << endl; 
			Inorder(temp->right);
		}
	}

	void preorder(Node * temp)
	{
		if (temp != nullptr)
		{
			cout << temp->data << " ";
			cout << temp->colour << endl;
			preorder(temp->left);
			preorder(temp->right);
		}
	}

	void postorder(Node * temp)
	{
		if (temp != nullptr)
		{
			postorder(temp->left);
			postorder(temp->right);
			cout << temp->data << " ";
			cout << temp->colour << endl;
		}
	}

	Node * searchParent(int val , Node * temp)
	{
		if (temp != nullptr)
		{
			if (temp->left != nullptr)
				if (temp->left->data == val)
					return temp;
			if (temp->right != nullptr)
				if (temp->right->data == val)
					return temp;
			if (val > temp->data)
				return searchParent(val, temp->right);
			else if (val < temp->data)
				return searchParent(val, temp->left);
			else
				return nullptr; 		
		}
		return nullptr; 
	}

public: 

	Tree()
	{
		root = nullptr;
	}


	void recolour(Node * parent)
	{
		if (parent ->left != nullptr)
			parent->left ->colour = parent->colour; 

		if (parent-> right  != nullptr)
			parent->right->colour = parent -> colour; 

		if (parent->colour == 'r')
			parent->colour = 'b'; 
		else
			parent->colour = 'r';


		if (root == parent)
			parent->colour = 'b'; 
	}

	void rotate_left(Node * parent)
	{
		Node * child = parent->right; 
		Node * grand = search(parent->data); 
		Node * ok = parent->left; 

		if (grand == root)
			 root = parent ;
		else
		{
			Node *gParent = search(grand->data); 

			if (gParent->left == grand)
				gParent->left = parent;
			else
				gParent->right = parent; 
		}

		parent->left = grand; 
		grand->right = ok; 

	}

	void rotate_right(Node * parent )
	{
		Node * child = parent-> left ;
		Node * grand = search(parent->data);
		Node * ok = parent->left;

		if (grand == root)
			root = parent;
		else
		{
			Node *gParent = search(grand->data);

			if (gParent->left == grand)
				gParent->left = parent;
			else
				gParent->right = parent;
		}

		parent-> right  = grand; 
		grand->left = ok ; 
	}

	void BalanceTree(Node * parent)
	{

		Node * grand = search(parent->data); 

		Node * child = nullptr;

		if (parent->left != nullptr)
			child = parent->left;

		if (parent->right != nullptr)
			child = parent->right;

		// case 3 n's parent and uncle are red 

		if ((grand->right != nullptr) && (grand->left != nullptr))
		{
			if ((grand->left->colour == 'r') && (grand->right->colour == 'r'))
			{
				recolour(grand);
				return;
			}
		}
		
		// case 5 rotate left
		// n is added to left of left child of grandparent

		if (((grand->left == nullptr) || (grand->left ->colour == 'b') )
			&& (child == parent->right))
		{
			rotate_left(parent);
			recolour(parent); 
		}
			
		// case 5 rotate right
		// N is added to right of right child of grandparent 

		else if (((grand->right == nullptr) || (grand->right ->colour == 'b'))
			&& (child == parent->left))
		{
			rotate_right(parent);
			recolour(parent);
		}

		// case 4 
		// N is added to left of right child of grandparent 

		else if (((grand->left == nullptr) || (grand ->left ->colour == 'b' ))
			&& (child == parent-> left ))
		{
			child->right = parent; 
			parent->left = nullptr; 
			grand->right = child; 

			rotate_left(parent);
			recolour(parent);
		}

		//case 4 2 rotations and colour change 
		// N is added to right of left child of grandparent

		else if (((grand->right  == nullptr) || (grand-> right ->colour == 'b'))
			&& (child == parent->right))
		{
			child-> left  = parent;
			parent-> right = nullptr;
			grand-> left  = child;

			rotate_right(parent);
			recolour(parent);
		}
			
	}

	void insert(int val)
	{
		Node * newNode;
		newNode = new Node;
		newNode->data = val;

		if (root == nullptr)
		{
			root = newNode;
			root->colour = 'b'; 
		}
		else
		{
			Node*temp = root;
			while (1)
			{
				if (val > temp->data)
				{
					if (temp->right == nullptr)
					{
						temp->right = newNode;
						break;
					}
					else	
						temp = temp->right;
					
				}
				else
				{
					if (temp->left == nullptr)
					{
						temp->left = newNode;
						break;
					}
					else
						temp = temp->left;				
				}
			}

			if ((temp->colour == 'r') && (newNode->colour == 'r'))
			{
				BalanceTree(temp);
				Node * node = root; 

				while (1)
				{
					if (node->data == val)
						break; 
					if (val > node->data)
					{
						if (node->colour == 'r')
						{
							if (node->right->colour =='r')
								BalanceTree(node); 
						}
						node = node->right; 
					}
					else
					{
						if (node->colour == 'r')
						{
							if (node->right->colour == ' r')
								BalanceTree(node);
						}
						node = node->left;
					}
					
				}
			}
				
		}
	}

	void order()
	{
		if (root != nullptr)
			Inorder(root);
		else
			cout << " Tree is empty" << endl;

		cout << endl;
	}

	void porder()
	{
		if (root != nullptr)
			preorder(root);
		else
			cout << " Tree is empty" << endl;

		cout << endl;
	}

	void posorder()
	{
		if (root != nullptr)
			postorder(root);
		else
			cout << " Tree is empty" << endl;

		cout << endl;
	}

	Node *  search( int val )
	{
		if (root == nullptr)
			return nullptr; 
		else
		{
			Node * temp = searchParent(val , root); 
			return temp;
		}
		
	}

};

int main()
{
	Tree t;
	
	t.insert(1);
	t.insert(2);
	t.insert(3);
	t.insert(4);
	t.insert(5);
	t.insert(6);
	t.insert(7);
	t.insert(8);
	t.insert(9);
	t.insert(10);
	//t.search(10); 
	// cout << endl;
	t.order(); 
	system("pause"); 
	return 0; 
}