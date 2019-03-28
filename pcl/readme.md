---

# 0 PCL编程规范

### 0 PCL命名规范

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

# 1 PCL点类型以及添加自己定义的类型


### 1.1 PointXYZ-float x, y, z;
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

### 1.2 PointXYZI-float x, y, z, intensity;
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

### 1.3 PointXYZRGBA-float x, y, z; uint32_t rgba;
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

### 1.4 简单的二维 x-y point 结构
```c
struct
{
    float x;
    float y;
};
```

### 1.5 InterestPoint-float x, y, z, strength;
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

### 1.6 Normal-float normal[3], curvature;
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

### 1.7 PointNormal-float x, y, z; float normal[3], curvature;
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

### 1.8 PointXYZRGBNormal-float x, y, z, rgb, normal[3], curvature;
PointXYZRGBNormal存储了XYZ数据和RGB数据,并且还包括法线和曲率

### 1.9 PointXYZINormal-float x, y, z, intensity, normal[3], curvature;
PointXYZINormal存储了XYZ数据和强度值,并且还包括曲面法线和曲率

### 1.10 PointWithRange-float x, y, z(union with float point[4]), range;
除了range包含从所获得的视点到采集点的距离测量外,其他与PointXYZI类似

### 1.11 PointWithViewpoint-float x, y, z, vp_z, vp_y, vp_z;
vp_x vp_y vp_z 表示视点

### 1.12 omentInvariants-float j1, j2, j3;
包含采样曲面上面片的三个不变矩的point类型
```c
struct
{
    float j1, j2, j3;
};

```

### 1.13 PrincipalRadiiRSD-float r_min, r_max;
包含曲面块上两个RSD半径的point类型

### 1.14 Boundary-uint8_t boundary_point;
存储一个点是否位于曲面边界上的简单point类型

### 1.15 PrincipalCurvatures-float principal_curvature[3], pcl, pc2;

### 1.16 PFHSignature125-float pfh[125];
包含给定点的PFH(点特征直方图)的简单point类型

### 1.17 FPFHSignature33-float fpfh[33];
包含给定点的FPFH(快速点特征直方图)的简单point类型
```c
struct
{
    float histogram[33];
};
```

### 1.18 VFHSignature308-float vfh[308];
包含给定点VFH(视点特征直方图)的简单point类型
```c
struct
{
    float histogram[308];
};
```

# 2 输入和输出
PCL内部支持对常用3D格式文件的打开与存储操作,以及与PCD内部格式之间的互相转化.

支持3D点云存储的文件类型:

PCD(点云数据)

PLY 多边形文件格式

STL 主要用于CAD领域

OBJ 几何学上定义的文件格式

X3D 符合ISO标准的基于XML的文件格式

### 2.1 PCD文件IO操作

##### 2.1.1 从PCD文件中读取点云数据

```c
#include <pcl/io/pcd_io.h> //包含了PCD输入输出操作的声明
#include <pcl/point_types.h> //包含了PointT类型结构体的声明

pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
```
创建一个PointCloud<PointXYZ>boost共享指针并进行实例化.

```c
if(pcl::io::loadPCDFile<pcl::PointXYZ>("test_pcd.pcd", *cloud) == -1)
//打开文件
{
    PCL_ERROR("Couldn't read file test_pcd.pcd\n");
}
```
##### 2.1.2 向PCD文件写入点云数据

```c
// 创建点云
pcl::PointCloud<pcl::PointXYZ> cloud;

cloud.width = 5;
cloud.height = 1;
cloud.is_dense = false;
cloud.points.resize(cloud.width * cloud.height);
for(size_t i = 0; i < cloud.points.size();++i)
{
    cloud.points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
    cloud.points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
    cloud.points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
}

pcl::io::savePCDFileASSCII("test_pcd.pcd",cloud);
```

##### 2.1.3 点云拼接
两个字段类型和维度相同的点云进行拼接 cloud_c = cloud_a + cloud_b

两个不同字段的点云进行拼接 pcl::concatenateFields(cloud_a,n_cloud_b,p_n_cloud_c);

##### 2.1.4 PLY LAS等数据格式与PCD的转换
LAS是用于激光雷达数据交换的标准文件格式.

'''c
pcl::PCLPointCloud2 cloud;
pcl::PLYReader reader;
reader.read(filename, cloud);
pcl::PCDWriter writer;
writer.write(filename, cloud, Eigen::Vector4f::Zero(), Eigen::Quaternionf::Identity(), format);

'''


# 3Kd树与八叉树

### 3.1 K紧邻搜索
搜索最近某个点最近的n个点
```c
kdtree.nearestKSearch(searchPoint, K, pointIdxNKNSearch, pointNKNSquaredDistance) 
```

搜索距离某个点小于一定范围的点 

```c
pcl::KdTreeFLANN<pcl::PointXYZ> kdtree; //创建一个kdtree对象
kdtree.nearestKSearch(searchPoint, K, pointIdxNKNSearch, pointNKNSquaredDistance)
```

### 3.2 八叉树空间分割进行点云压缩

Octree八插树是一种用于描述三维空间的树状数据结构。
八叉树的每个节点表示一个正方体的体积元素，每个节点有八个子节点，
将八个子节点所表示的体积元素加在一起就等于父节点的体积。
Octree模型：又称为八叉树模型，若不为空树的话，
树中任一节点的子节点恰好只会有八个，或零个，也就是子节点不会有0与8以外的数目。
Log8(房间内的所有物品数)的时间内就可找到金币。
因此，八叉树就是用在3D空间中的场景管理，可以很快地知道物体在3D场景中的位置，
或侦测与其它物体是否有碰撞以及是否在可视范围内。

