#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <map>

using namespace std;

struct SBLnode {
	string name;
	SBLnode *next;
	SBLnode * left, * right;
};

struct Queue {
	SBLnode * first, * last;
};

typedef SBLnode* BST;

struct SBL {
	Queue q;
	BST root;
};

void SBL_init (SBL & sbl) { 
	sbl.q.first = NULL;
	sbl.q.last = NULL;
	sbl.root = NULL;
}

int SBL_size (const SBL& sbl)
{ 
	if (sbl.root == NULL)
		return 0;
	else
	{
		BST a = sbl.q.first;
		int count = 0;
		while (NULL != a)
		{
			a = a->next;
			count++;
		}
		return count;
	}
}

string SBL_first (const SBL& sbl) 
{
	assert(SBL_size(sbl) > 0);
	return sbl.root->name;
}

void SBL_printInArrivalOrder (const SBL& sbl) 
{
	BST a = sbl.q.first;
	while (NULL != a)
	{
		cout << a->name << endl;
		a = a->next;
	}
}

void SBL_printInAlphabeticalOrder (const SBL& sbl) 
{ 
	if (NULL != sbl.root)
	{
		SBL a;
		a.root = sbl.root->left;
		SBL_printInAlphabeticalOrder(a);
		cout << sbl.root->name << endl;
		SBL b;
		b.root = sbl.root->right;
		SBL_printInAlphabeticalOrder(b);
	}
}

bool SBL_lookup (const SBL& sbl, string name)
{ 
	BST a = sbl.root;
	while ((NULL != a)&&(a->name != name))
		a = a->next;
	if (NULL == a)
		return false;
	else 
		return true;
}

void SBL_enter(string name, BST& bst,Queue& q)
{
	if (NULL == bst) { 
		bst = new SBLnode; 
		bst->name = name;
		bst->left = NULL; 
		bst->right = NULL; 
		q.last = bst;
	}
	else if (name == bst->name)
	{
		cerr << "duplicate name: " << name << endl;
		assert(false);
	}
	else if (name < bst->name) {
		SBL_enter(name, bst->left, q); 
	} 
	else { 
		SBL_enter(name, bst->right,q); 
	} 
}

void SBL_arrive (string name, SBL& sbl) 
{
	SBL_enter(name, sbl.root, sbl.q);
	int c = SBL_size(sbl);
	if (c != 0)
	{
		BST b = sbl.q.first;
		BST a = sbl.q.first->next;
		while (NULL != a)
		{
			b = b->next;
			a = a->next;
		}

		BST c = sbl.root;
		while (name != c->name)
		{
			if (name > c->name)
				c = c->right;
			else
				c = c->left;
		}
		c->next = NULL;
		b->next = c;
	}
	else
	{
		sbl.q.first = sbl.root;
		sbl.q.first->next = NULL;
	}

} 

void BST_delete (string key, BST& tree, Queue& z)
{
	if 	(key == tree->name)
	{
		if ((tree->left == NULL)&&(tree->right == NULL))
		{
			BST a = tree;
			tree =  NULL;
			z.first = NULL; 
			delete a;
		}
		else if (tree->left == NULL)
		{
			z.first = z.first->next;
			BST a = tree;
			tree = tree->right;
			delete a;
		}
		else if (tree->right == NULL)
		{
			z.first = z.first->next;
			BST a = tree;
			tree = tree->left;
			delete a;
		}
		else
		{
			z.first = z.first->next;
			BST act = tree;
			BST b = tree->left;
			BST c = tree->left->right;

			if (NULL == c)
			{
				b->right = tree->right;
				tree = b;

				delete act;
			}
			else
			{
				while (NULL != c->right)
				{
					b = b->right;
					c = c->right;
				}
				b->right = c->left;
				c->right = tree->right;
				c->left = tree->left;
				tree = c;
				delete act;
			}

		}
	}
	else if ((tree->right != NULL)&&(key == tree->right->name))
	{
		BST y;
		y = tree->right;
		z.first = z.first->next;

		if ((y->left == NULL)&&(y->right == NULL))
		{
			BST a = y;
			tree->right = NULL;
			delete a;
		}
		else if (y->left == NULL)
		{
			BST a = y;
			tree->right = y->right;
			delete a;
		}
		else if (y->right == NULL)
		{
			BST a = y;
			tree->right = y->left;
			delete a;
		}
		else
		{
			BST act = tree->right;
			BST b = y->left;
			BST c = y->left->right;
			if (NULL == c)
			{
				b->right = y->right;
				tree->right = b;
				delete act;
			}
			else
			{
				while (NULL != c->right)
				{
					b = b->right;
					c = c->right;
				}
				b->right = c->left;
				c->right = y->right;
				c->left = y->left;
				tree->right = c;
				delete act;
			}

		}
	}
	else if ((tree->left != NULL)&&(key == tree->left->name))
	{
		z.first = z.first->next;

		BST y;
		y = tree->left;

		if ((y->left == NULL)&&(y->right == NULL))
		{
			BST a = y;
			tree->left = NULL;
			delete a;
		}
		else if (y->left == NULL)
		{
			BST a = y;
			tree->left = y->right;
			delete a;
		}
		else if (y->right == NULL)
		{
			BST a = y;
			tree->left = y->left;
			delete a;
		}
		else
		{
			BST act = tree->left;
			BST b = y->left;
			BST c = y->left->right;
			if (NULL == c)
			{
				b->right = y->right;
				b->left = NULL;;
				tree->left = b;
				delete act;
			}
			else
			{
				while (NULL != c->right)
				{
					b = b->right;
					c = c->right;
				}
				b->right = c->left;
				c->right = y->right;
				c->left = y->left;
				tree->left = c;
				delete act;
			}
		}
	}
	else if (key < tree->name) {
		return BST_delete (key ,tree->left, z); }
	else {
		return BST_delete (key, tree->right, z); 
	}
}

void SBL_leave (SBL& sbl)
{
	assert(SBL_size(sbl) > 0);
	string a = sbl.q.first->name;

	BST_delete(a,sbl.root,sbl.q);

	if (1 == SBL_size(sbl))
		sbl.q.last = sbl.root;	
}


int main()
{
	
}