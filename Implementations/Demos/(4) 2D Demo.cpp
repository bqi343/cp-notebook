/**
* Link: http://www.spoj.com/problems/MATSUM/ (modified)
* Description: Use with 2D BIT, 2D SegBIT, 2D SegTree
*/

int main() {
    BIT2D<int,1024> B = BIT2D<int,1024>();
    Node<int> S = Node<int>();
     
    F0R(i,100000) {
        int c = rand()&1;
        if (c == 0) {
            int x = rand() % SZ, y = rand() % SZ, num = rand() % 100; 
            S.upd(x,y,num);
            x++, y++;
            B.upd(x,y,num);
        } else if (c == 1) {
            int x1 = rand() % SZ, y1 = rand() % SZ, x2 = rand() % SZ, y2 = rand() % SZ;
            if (x1 > x2) swap(x1,x2);
            if (y1 > y2) swap(y1,y2);
            int a = S.query(x1,x2,y1,y2);
            x1 ++, y1 ++, x2 ++, y2++;
            int b = B.query(x1,x2,y1,y2);
            assert(a == b);
        } else break;
    }
}