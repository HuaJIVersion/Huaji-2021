[toc]
我们组约定使用OpenCV4.1.0版本开发。这篇博客记录win10安装OpenCV和配置VS 2019 OpenCV编程环境。


## 官网下载OpenCV4.1.0

去[官网下载](https://opencv.org/releases/)[OpenCV4.1.0](https://sourceforge.net/projects/opencvlibrary/files/4.1.0/opencv-4.1.0-vc14_vc15.exe/download)

![官网](https://raw.githubusercontent.com/cyicz123/Picture/main/img/20201002143714.png)

![OpenCV4.1.0](https://raw.githubusercontent.com/cyicz123/Picture/main/img/20201002143731.png)

## 解压并添加环境变量

下载好后，双击运行exe程序解压，选择一个解压后的目录。( 其会自动生成一个opencv目录，不需要单独再创一个opencv目录。另，**不建议将其解压到C盘根目录下的Program Files或Program File (x86)目录下，可能会因系统权限导致各种问题** )

![解压](https://raw.githubusercontent.com/cyicz123/Picture/main/img/20201002143921.png)

## 新建VS 2019配置属性表

在VS 2019中新建一个空项目（具体操作看[RM编程环境配置](https://cyicz123.top/2020/10/01/RM%E7%BC%96%E7%A8%8B%E7%8E%AF%E5%A2%83%E9%85%8D%E7%BD%AE/)），然后打开属性管理器

![属性管理器](https://raw.githubusercontent.com/cyicz123/Picture/main/img/20201002152922.png)

选择Debug X64->右键->添加新项目属性表

![新项目属性表](https://raw.githubusercontent.com/cyicz123/Picture/main/img/20201002153344.png)

这里我重命名为debug为了等下和release属性表区分

![debug](http://image.cyicz123.top/img/20201002154008.png)

## 添加头文件和库文件

在刚刚安装opencv的目录中找到如下文件

```markdown
# 头文件
C:\Users\60292\AppData\Local\opencv\build\include
C:\Users\60292\AppData\Local\opencv\build\include\opencv2
# 库文件
C:\Users\60292\AppData\Local\opencv\build\x64\vc15\lib
```

右键点击刚刚添加的debug属性表

将刚刚的头文件目录路径添加到包含目录里，库文件目录路径添加到库目录里

![包含目录](http://image.cyicz123.top/img/20201002154154.png)

![包含目录路径](https://raw.githubusercontent.com/cyicz123/Picture/main/img/20201002154624.png)

![库目录路径](https://raw.githubusercontent.com/cyicz123/Picture/main/img/20201002154655.png)

添加依赖库

进入刚才库文件的目录，复制库文件的名字。

```markdown
#根据自己安装版本选择
opencv_world410d.lib # 带后缀d的为目前debug属性表依赖
opencv_world411.lib	 # 不带后缀d的为等下release属性表依赖
```

![](http://image.cyicz123.top/img/20201002154214.png)

最后点击确定完成debug属性表的设置。

## 设置release属性表

选择Release X64->右键->添加新项目属性表

重命名为release与前文的debug区分

包含目录和库目录设置和前文一样，只有最后添加依赖库时要把带d后缀去掉

![依赖库](https://raw.githubusercontent.com/cyicz123/Picture/main/img/20201002155019.png)

**设置完毕后需要重启电脑**

## 代码测试

新建源文件

输入以下代码

```c++
#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main()
{
	Mat src = imread("C:/Girlfriend.jpg"); //图片路径记得修改
    if (src.empty()) {
        cout << "image load fail" << endl;
        return 0;
    }
    namedWindow("test");
    imshow("test", src);
    waitKey(0);//没有的话，窗口一闪而过。
    return 0;
}
```

记得将上面的类型改为Debug和X64

![修改为Debug](https://raw.githubusercontent.com/cyicz123/Picture/main/img/20201002155643.png)

F5运行

弹出西野七濑照片

![西野七濑](http://image.cyicz123.top/img/20201002155727.png)

## 最后

其他项目代码可以直接在属性管理器里添加现有属性表（即上文建立的的不过debug和release属性表），debug模式用debug属性表，release模式用release属性表。

