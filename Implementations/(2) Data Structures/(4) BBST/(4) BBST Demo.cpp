/**
* Description: use for treap, splay tree
*/

int main() {
    root = ins(root,1); root = ins(root,9); root = ins(root,3);
    root->inOrder(1);
    
    root = ins(root,7); root = ins(root,4); root = del(root,9);
    root->inOrder(1);
}