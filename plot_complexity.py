import matplotlib.pyplot as graph
import numpy as np

#顯示中文
graph.rcParams['font.sans-serif'] = ['Microsoft JhengHei'] 
graph.rcParams['axes.unicode_minus'] = False
graph.rcParams['font.size'] = 24
###

sz = int(1e8 + 1e7)

#O(n!)
x, y = [], []
for i in range(1, 13):
    x.append(i)
    y.append(np.math.factorial(i))
graph.plot(x, y, c="r", label = "$O(n!)$", zorder=7)
###

#O(2**n), O(n**x)
x, y = [], []
for i in range(1, 29):
    x.append(i)
    y.append(2**i)
graph.plot(x, y, c="orange", label="$O(2^n)$", zorder=8)
x, y = [], []
for i in range(1, 800):
    x.append(i)
    y.append(i**3)
graph.plot(x, y, c="gold", label="$O(n^3)$", zorder=6)
x, y = [], []
for i in range(1, 20000):
    x.append(i)
    y.append(i**2)
graph.plot(x, y, c="olivedrab", label="$O(n^2)$", zorder=9)

#Most other O()
x = [i for i in range(1, 100)]
x += [i for i in range(100, int(5e5), 100)]
graph.plot(x, x*np.sqrt(x), c="g", label="$O(n\sqrt n)$")
x += [i for i in range(int(5e5), int(6e6), 100)]
x.remove(1)
graph.plot(x, x*np.log2(x), c="teal", label="$O(n\ \log\ n)$")
x.insert(0, 1)
x += [i for i in range(int(1e6), sz, 100)]
graph.plot([1,sz], [1,sz], c="b", label="$O(n)$")
graph.plot(x, np.sqrt(x), c="purple", label="$O(\sqrt n)$")
x.remove(1)
graph.plot(x, np.log2(x), c="saddlebrown", label="$O(\log\ n)$")
graph.plot([1,sz], [1.1,1.1], c="k", label="$O(1)$", zorder=0)
###

#顯示
graph.axhline(1e8, c="k")
graph.grid(1)
graph.title("時間複雜度圖表 Time Complexity Chart\nC++計算1e8次約可估成要跑1秒")
graph.xlabel("輸入大小 number of inputs")
graph.ylabel("計算數量 number of operations")
graph.xscale("log")
graph.yscale("log")
graph.xticks([10**i for i in range(9)])
graph.yticks([10**i for i in range(9)])
graph.legend(loc = "upper left", prop={'size':14})
graph.ylim(ymin=1)
graph.xlim(xmin=1)
graph.show()
###