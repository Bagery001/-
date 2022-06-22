真实感图形

结果：
实验运行屏幕截图
![Image text](https://github.com/Bagery001/-/blob/main/%E6%9D%8E%E6%9E%97%E8%94%93-20201050336/%E6%9C%9F%E6%9C%AB%E4%BD%9C%E4%B8%9A/pic/teapot1.jpg)
![Image text](https://github.com/Bagery001/-/blob/main/%E6%9D%8E%E6%9E%97%E8%94%93-20201050336/%E6%9C%9F%E6%9C%AB%E4%BD%9C%E4%B8%9A/pic/teapot2.jpg)
用鼠标点击一个角度后，茶壶转换角度旋转
![Image text]()
![Image text]()
通过鼠标输入123，茶壶旋转不同角度
![Image text]()
![Image text]()
![Image text]()
程序开始可以看见一个侧面自动保持一定速度旋转的茶壶，当识别到一个方向的鼠标右键点击之后，炒一个方向旋转一定角度后沿另一条中心轴原速旋转；当识别到键盘输入1、2、3时，响应键盘点击事件，改变茶壶旋转方向。
总结：
本次实验主要使用课本知识三维图像的建立，纹理的映射，光照模型，鼠标和键盘的人机交互，如上文。学习的新知识：自动旋转的设置，以及更加清楚地认识到了光照应用，包括OpenGL提供了管理四种光（辐射光、环境光、镜面光和漫反射光）的方法，另外还可以指定模型表面的反射特性。
遇到的问题：
一开始程序运行错误，提示报错如下图。
![Image text]()
后通过上网查询将void key( char k, int x, int y)改为void key(unsigned char k, int x, int y)后运行正确。
![Image text]()
以及程序任然存在的走样问题。
