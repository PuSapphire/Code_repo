
#include <iostream>
const int N = 500;
int dis[N][N];
void floyd() {
    for (int k=0; k<N; ++k)
        for (int i=0; i<N; ++i)
            for (int j=0; j<N; ++j)
                dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
}