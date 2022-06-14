
/*  ########  *\
樹狀數組 Binary Indexed Tree(BIT or Fenwick Tree)
時間複雜度: 
    更新 = O(log n)
    查詢 = O(log n)
資節用途: 計算前綴...

由於[l, r]之和 = [1, r] - [1, l-1]，
因此可以用來寫區間和
\*  ########  */
const int N = 2e5+5;
int BIT[N]; //BIT從1開始數
void upd(int i, int v) {
    for (; i<=N; i += i&-i) BIT[i] += v;
}
int qry(int i) {
    int sum = 0;
    for (; i>0; i -= i&-i) sum += BIT[i];
    return sum;
}