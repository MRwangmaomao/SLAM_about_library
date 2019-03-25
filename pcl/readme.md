---

# PCL编程规范

### 1 PCL命名规范

##### 文件命名
头文件 .h
模板类 .hpp
源文件 .cpp

##### 目录命名

头文件 include/
模板类 include/impl
源文件 src/

##### include语句
同一目录下 include用双引号
其他情况用尖括号

例如:
```c++
#include <pcl/module_name/file_name.h>
#include <pcl/module/impl/file_name.hpp>
#include "file_name.cpp"
```

##### 宏定义命名
