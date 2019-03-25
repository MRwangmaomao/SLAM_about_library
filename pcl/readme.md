---

# 1 PCL编程规范

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

# 2 PCL点类型以及添加自己定义的类型

PointXYZ-float x, y, z;
```c
union
{
    float data[4];
    struct  
    {
        float x;
        float y;
        float z; 
    };
};
```

PointXYZI-float x, y, z, intensity;
```c
union
{
    float data[4];
    struct
    {
        float x;
        float y;
        float z;
    };
};
union
{
    struct
    {
        float intensity;
    } 
    float data_c[4];
};

```

PointXYZRGBA-float x, y, z; uint32_t rgba;
```c
union
{
    float data[4];
    struct 
    {
        float x;
        float y;
        float z;
    };
};
union
{
    struct
    {
        uint32_t rgba; 
    };
    float data_c[4];
}
```

简单的二维 x-y point 结构
```c
struct
{
    float x;
    float y;
};
```

InterestPoint-float x, y, z, strength;
```c
union
{
    float data[4];
    struct
    {
        float x;
        float y;
        float z;
    };
};
union
{
    struct
    {
        float strength;
    };
    float data_c[4];
}
```

Normal-float normal[3], curvature;
Normal结构体表示给定点所在样本曲面上的法线方向,以及对应曲率的测量值
用户访问法向量的第一个坐标,可以通过points[i].data_n[0]  points[i].normal[0] 或者point[i].normal_x
```c
union
{
    float data_n[4];
    float normal[3]; 
    struct
    {
        float normal_x;
        float normal_y;
        float normal_z;
    };
};
union
{
    struct
    {
        float curvature;
    };
    float data_c[4];
};
```

PointNormal-float x, y, z; float normal[3], curvature;
存储XYZ数据,采样点对应的法线和曲率
```c
union
{
    float data[4];
    struct
    {
        float x;
        float y;
        float z;
    };
};
union
{
    float data_n[4];
    float normal[3];
    struct
    {
        float normal_x;
        float normal_y;
        float normal_z;
    };
};
union
{
    struct
    {
        float curvature;
    };
    float data_c[4];
};
```

PointXYZRGBNormal-float x, y, z, rgb, normal[3], curvature;
PointXYZRGBNormal存储了XYZ数据和RGB数据,并且还包括法线和曲率

PointXYZINormal-float x, y, z, intensity, normal[3], curvature;
PointXYZINormal存储了XYZ数据和强度值,并且还包括曲面法线和曲率

PointWithRange-float x, y, z(union with float point[4]), range;
除了range包含从所获得的视点到采集点的距离测量外,其他与PointXYZI类似

PointWithViewpoint-float x, y, z, vp_z, vp_y, vp_z;
vp_x vp_y vp_z 表示视点

MomentInvariants-float j1, j2, j3;
包含采样曲面上面片的三个不变矩的point类型
```c
struct
{
    float j1, j2, j3;
};

```

PrincipalRadiiRSD-float r_min, r_max;
包含曲面块上两个RSD半径的point类型

Boundary-uint8_t boundary_point;
存储一个点是否位于曲面边界上的简单point类型

PrincipalCurvatures-float principal_curvature[3], pcl, pc2;

PFHSignature125-float pfh[125];
包含给定点的PFH(点特征直方图)的简单point类型

FPFHSignature33-float fpfh[33];
包含给定点的FPFH(快速点特征直方图)的简单point类型
```c
struct
{
    float histogram[33];
};
```

VFHSignature308-float vfh[308];
包含给定点VFH(视点特征直方图)的简单point类型
```c
struct
{
    float histogram[308];
};
```

# 3 输入和输出
PCL内部支持对常用3D格式文件的打开与存储操作,以及与PCD内部格式之间的互相转化.

