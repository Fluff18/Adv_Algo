#include "../include/splay_tree.hpp"
#include <iostream>
//Geeksfor Geeks is used a reference
using namespace std;

class splay_tree_implementation : public splay_tree
{
public:
    class node
    {
        public:
        int key;
        node *lt, *rt;
    };
    node* root;
    vector<int> g;
        int total ;
    splay_tree_implementation()
    {
        root = NULL;total = 0;
        
    }
    node* newNode(int key)  
{  
    node* Node = new node(); 
    Node->key = key;  
    Node->lt = Node->rt = NULL;  
    return (Node);  
}  
    int get_num_nodes()
    {
        return total;
    }
    node *rtRotate(node *x)
    {
        node *y = x->lt;
        x->lt = y->rt;
        y->rt = x;
        return y;
    }
    node *ltRotate(node *x)
    {
        node *y = x->rt;
        x->rt = y->lt;
        y->lt = x;
        return y;
    }
    
    node *splay(node* root, int key)
    {
        // Base cases: root is NULL or
        // key is present at root
        if (root == NULL || root->key == key)
        return root;
        
        // Key lies in lt subtree
        if (root->key > key)
        {
            // Key is not in tree, we are done
            if (root->lt == NULL) return root;
            
            // Zig-Zig (lt lt)
            if (root->lt->key > key)
            {
                // First recursively bring the
                // key as root of lt-lt
                root->lt->lt = splay(root->lt->lt, key);
                
                // Do first rotation for root,
                // second rotation is done after else
                root = rtRotate(root);
            }
            else if (root->lt->key < key) // Zig-Zag (lt rt)
            {
                // First recursively bring
                // the key as root of lt-rt
                root->lt->rt = splay(root->lt->rt, key);
                
                // Do first rotation for root->lt
                if (root->lt->rt != NULL)
                root->lt = ltRotate(root->lt);
            }
            
            // Do second rotation for root
            return (root->lt == NULL)? root: rtRotate(root);
        }
        else // Key lies in rt subtree
        {
            // Key is not in tree, we are done
            if (root->rt == NULL) return root;
            
            // Zag-Zig (rt lt)
            if (root->rt->key > key)
            {
                // Bring the key as root of rt-lt
                root->rt->lt = splay(root->rt->lt, key);
                
                // Do first rotation for root->rt
                if (root->rt->lt != NULL)
                root->rt = rtRotate(root->rt);
            }
            else if (root->rt->key < key)// Zag-Zag (rt rt)
            {
                // Bring the key as root of
                // rt-rt and do first rotation
                root->rt->rt = splay(root->rt->rt, key);
                root = ltRotate(root);
            }
            
            // Do second rotation for root
            return (root->rt == NULL)? root: ltRotate(root);
        }
    }
    int find(int key)
    {
    	int x = splay(root,key)->key;
        return x;
    }
    void insert(int k)
    {
        // Simple Case: If tree is empty
        if (root == NULL)
        {
        	root = newNode(k);
        	total++;
        	return;
        }
        
        // Bring the closest leaf node to root
        root = splay(root, k);
        
        // If key is already present, then return
        if (root->key==k) return;
        
        // Otherwise allocate memory for new node
        node *newnode = newNode(k);
        
        // If root's key is greater, make
        // root as rt child of newnode
        // and copy the lt child of root to newnode
        if (root->key > k)
        {
            newnode->rt = root;
            newnode->lt = root->lt;
            root->lt = NULL;
        }
        
        // If root's key is smaller, make
        // root as lt child of newnode
        // and copy the rt child of root to newnode
        else
        {
            newnode->lt = root;
            newnode->rt = root->rt;
            root->rt = NULL;
        }
        total++;
        root=newnode;
        
        return; // newnode becomes new root
    }
    void remove(int key)
    {
        total--;
        node *temp;
        if (!root)
        return;
        
        // Splay the given key
        root = splay(root, key);
        
        // If key is not present, then
        // return root
        if (key != root->key)
        {
            total++;
            return;
        }
        
        // If key is present
        // If lt child of root does not exist
        // make root->rt as root
        if (!root->lt)
        {
            temp = root;
            root = root->rt;
        }
        
        // Else if lt child exits
        else
        {
            temp = root;
            
            /*Note: Since key == root->key,
             so after Splay(key, root->lchild),
             the tree we get will have no rt child tree
             and maximum node in lt subtree will get splayed*/
            // New root
            root = splay(root->lt, key);
            
            // Make rt child of previous root  as
            // new root's rt child
            root->rt = temp->rt;
        }
        
        // free the previous root node, that is,
        // the node containing the key
        free(temp);
        
        // return root of the new Splay Tree
        return ;
        
    }
    void preOrder_rec(struct node *root)
    {
       
        if (root != NULL)
        {
            g.push_back(root->key);
            preOrder_rec(root->lt);
            preOrder_rec(root->rt);
        }
    }
    vector<int> pre_order()
    {
        g.clear();
        preOrder_rec(root);
        return g;
    }
    void postOrder_rec(struct node *root)
    {
        
        if (root != NULL)
        {
            
            postOrder_rec(root->lt);
            postOrder_rec(root->rt);
            g.push_back(root->key);
        }
    }
    vector<int> post_order()
    {
        g.clear();
        postOrder_rec(root);
        return g;
    }
    void inOrder_rec(struct node *root)
    {
        
        if (root != NULL)
        {
            
            inOrder_rec(root->lt);
                        g.push_back(root->key);

            inOrder_rec(root->rt);
        }
    }
    vector<int> in_order()
    {
        g.clear();
        inOrder_rec(root);
        return g;
    }
    
    
};

