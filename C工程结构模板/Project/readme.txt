参考：https://www.jianshu.com/p/e13c05edfdb6
build/:项目编译目录，各种编译的临时文件和最终的目标文件皆存于此，可分为debug/和release/子目录
doc/:保存项目各种文档
include/:公共头文件目录，可以按模块划分组织目录来保存模块相关头文件
src/：源码目录
dist/:分发目录，最终发布的可执行程序和各种运行支持文件存放在此目录，打包此目录即可完成项目分发
samples/:样例程序目录
tools/:项目支撑工具目录
app/：入口程序
test/: 测试数据
Makefile:项目构建配置文件，当然也有可能是其他类型的构建配置文件,比如bjam
README:项目的总体说明文件