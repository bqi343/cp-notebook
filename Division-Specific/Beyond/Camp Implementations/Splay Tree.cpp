//http://codeforces.com/blog/entry/18462
//https://sites.google.com/site/kc97ble/container/splay-tree/splaytree-cpp-3
 
#include<bits/stdc++.h>
 
using namespace std;
 
struct Node{
    Node *par, *child[2];
    int v;
};
 
Node *root;
 
void setLink(Node *x, Node * y, int d) {
   x->child[d] = y;
   y->par = x;
}
 
int getDir(Node * x, Node * y) {
   return x->child[0] == y ? 0 : 1;
}
 
void rotate(Node * x, int d) {
   Node * y = x->child[d], * z = x->par;
   setLink(x, y->child[d^1], d);
   setLink(y, x, d^1);
   setLink(z, y, getDir(z, x));
}
 
void splay(Node * x) {
   while(x->par) {
      Node * y = x->par, * z = y->par;
      int dy = getDir(y, x), dz = getDir(z, y);
      if (!z) rotate(y, dy);
      else if (dy == dz) rotate(z, dz), rotate(y, dy);
      else rotate(y, dy), rotate(z, dz);
   }
}
 
void Insert(int v) {
    if(!root) {
        root=(Node *)malloc(sizeof(Node));
        root->child[0]=NULL;
        root->child[1]=NULL;
        root->par=NULL;
        root->v=v;
        return;
    }
     
    Node *P=root;
    while(1) {
        if(P->v==v) break; // not multiset
         
        int i = ((v < (P->v)) ? 0 : 1);
         
        if(P->child[i]) P = P->child[i];
        else {
            P->child[i]=(Node *)malloc(sizeof(Node));
            P->child[i]->par = P;
            P->child[i]->child[1]=NULL;
            P->child[i]->child[0]=NULL;
            P->child[i]->v = v;
            P = P->child[i];
            break;
        }
    } 
    splay(P);
}
 
void Inorder(Node *R) {
    if(!R) return;
     
    Inorder(R->child[0]);
     
    cout << "v: " << R->v << " ";
    if (R->child[0]) cout << "l: " << R->child[0]->v << " ";
    if(R->child[1]) cout << "r: " << R->child[1]->v;
    cout << "\n";
     
    Inorder(R->child[1]);
}
 
Node* Find(int v) {
    if(!root) return NULL;
    Node *P=root;
     
    while (P) {
        if(P->v == v) break;
        int i;
        if(v < (P->v)) i = 0;
        else i = 1;
         
        if(P->child[i]) P=P->child[i];
        else break;
    }
     
    splay(P);
    if(P->v == v) return P;
    else return NULL;
}
 
bool Erase(int v) {
    Node *N=Find(v);
    if(!N) return false;
    splay(N); //check once more;
     
    Node *P = N->child[0];
    if(!P) {
        root = N->child[1];
        root->par = NULL;
        free(N);
        return true;
    }
    while(P->child[1]) P = P->child[1];
    if(N->child[1]) {
        P->child[1] = N->child[1];
        N->child[1]->par = P;
    }
    root = N->child[0];
    root->par = NULL;
     
    free(N);
    return true;
}
 
int main() {
    while(1) {
        int t; cin >> t;
        if(t!=0 && t!=-1) Insert(t);
        else if(t==0) {
            cin >> t;
            if(!Find(t)) cout << "Couldn't Find " << t << "!\n";
            else cout << "Found " << t << "!\n";
        } else {
            cin >> t;
            if(Erase(t)) cout << "Deleted " << t << "!\n";
            else cout << "Couldn't Find " << t << "!\n";
        }
        if(root) cout << "root: " << root->v << "\n";
        Inorder(root);
    }
}
