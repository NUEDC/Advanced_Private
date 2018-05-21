# Advanced_Private
私有专用库函数
/**********2018/5/21************/
对原有的函数进行了相应的更改，更改项目如下：
1、添加了port初始化函数 PORT_INIT()可以实现对一组端口进行的初始化设置
2、在标准库文件中添加了一组 "stm32f10x_define.h"对 PORT和 PIN 和 CLK进行了设置
   现在对GPIO_INIT 和 PORT_INIT两个函数设置时不需要使用数字设置，可以直接使用GPIOA_SET等
   代替原来的数字操作，具体见"stm32f10x_define.h"中的define
/**********2018/5/22***********/
原有函数改变较大，更改项目如下：
1、完成基本函数的编写
2、在老一代版本基础上，对函数内的uint port 进行了修改，更改为另一种类型变量，GPIO_TypeDef* GPIOx
   可以直接设置GPIOA等，减小Switch量
3、变量定义部分define在stm32f10x_define.h中，此函数加在了标准库文件中
