实验三
1、实验内容：
熟悉OPENGL，通过Bresenham中点、改进Bresenham算法生成直线段

2、实验目的：
安装OPENGL，能编写代码运行，参考课本代码

Bresenham中点
关键代码：见cpp文件
void MidpointBresenham(int x0,int y0,int x1,int y1) { //中点Bresenham算法画线
          ……
      }
结果：
![Image text]()

改进：
关键代码：见cpp文件
void ProBresenham(int x0, int y0, int x1, int y1){//改进的Bresenham算法
          ……
      }
结果：
![Image text]()

总结：
首先假设0≤k≤1，由于x是最大位移方向，因此每次在x方向上加1，y方向上或加1 或加0。假定当前点是P(xi,yi),则下一个点在pu(xi+1,yi+1)与pd(xi+1,yi)中选一。以M表示pu和pd的终点即M(xi+1,yi+0.5)。又设Q是理想直线与垂直线x=xi+1的交点。
显然,若M在Q的下方，则pu(xi+1,yi+1)离直线近，应取为下一个像素，否则应取Pd（xi+1,yi）。
Bresenham算法对任意斜率的直线段具有通用性，对于斜率为整且大于1的直线段，只需要交换x和y之间的规则。
对于负斜率，除了一个坐标递减而另一个坐标地政外，其余程序是类似的。
