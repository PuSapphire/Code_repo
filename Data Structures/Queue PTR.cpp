class queue {
  int len = 0;
  struct node {
    int s;
    node *nxt;
    node (int v) {
      s = v; nxt = NULL;
    }
  }; node *front=NULL, *back=NULL;

  void printorder(node *n) {
    if (n == NULL) return;
    cout << n->s << ' ';
    printorder(n->nxt);
  }

  public:
  queue() { front = back = NULL; len = 0; }
  int size() { return len; }
  void order() { printorder(front); }

  void push(int v) {
    node *tmp = new node(v);
    if (!len) front = back = tmp;
    else {
      back->nxt = tmp;
      back = tmp;
    }
    len++;
  } 
  bool pop() {
    if (!len) return 0;
    node *tmp = front;
    front = front->nxt;
    if (!--len) back = NULL;
    delete tmp;
    return 1;
  }
  void append(queue &qu) {
    if (!qu.len) return;
    if (!(this->len)) {
      this->front = qu.front;
      this->back = qu.back;
      this->len = qu.len;
      qu = queue();
    } else {
      this->back->nxt = qu.front;
      this->back = qu.back;
      this->len += qu.len;
      qu = queue();
    }
  }
};
