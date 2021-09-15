# 极光Aurora

#### 介绍
极光（Aurora）解析程序

#### 软件架构
软件架构说明


## 安装教程

安装文件 `aurora.tar.gz`

运行环境：Linux平台

### 第一步，解压
```
tar -zxvf aurora.tar.gz
```

### 第二步，配置
解压后可以看见整个文件目录结构如下
- config.txt 配置文件，具体的配置项里面都有说明
- newproto 该文件夹用来存放基于json配置文件的自定义协议解析，该文件夹的路径需要在config.txt文件中进行配置
- run 该文件夹是相关的执行文件

### 第三步，运行
在run文件夹下运行如下命令即可
```
./aurora -r [config.txt配置文件的路径]
```

## 其他
初次运行可能会面临缺相关依赖的问题，暂时只能自己安装，例如
```
yum install libpcap*
```

## Build GCC version
```
gcc g++ >= 8 
because of the regular expression in std c++ 11 and higher version