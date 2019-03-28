

#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/console/print.h>
#include <pcl/console/parse.h>
#include <pcl/console/time.h>

using namespace pcl;
using namespace pcl::io;
using namespace pcl::console;

bool loadCloud(const std::string &filename, pcl::PCLPointCloud2 &cloud)
{
    pcl::console::TicToc tt;
    print_highlight("Loading ");
    print_value("%s ", filename.c_str());

    tt.tic();
    if (reader.read(filename, cloud) < 0)
        return (false);
    print_info("[done, ");
    print_value("%g", tt.toc());
    print_info(" ms : ");
    print_value("%d", cloud.width * cloud.height);
    print_info(" points]\n");
    print_info("Available dimensions: ");
    print_value("%s\n", pcl::getFieldsList(cloud).c_str());

    return (true);
}

void saveCloud(const std::string &filename, const pcl::PCLPointCloud2 &cloud, bool format)
{
    TicToc tt;
    tt.tic();

    print_highlight("Saving ");
    print_value("%s ", filename.c_str());

    pcl::PCDWriter writer;
    writer.write(filename, cloud, Eigen::Vector4f::Zero(), Eigen::Quaternionf::Identity(), format);

    print_info("[done, ");
    print_value("%g", tt.toc());
    print_info(" ms : ");
    print_value("%d", cloud.width * cloud.height);
    print_info(" points]\n");
}

/* ---[ */
int main(int argc, char **argv)
{
    print_info("Convert a PLY file to PCD format. For more information, use: %s -h\n", argv[0]);

    // Command line parsing
    bool format = 1;
    print_info("PCD output format: ");
    print_value("%s\n", (format ? "binary" : "ascii"));

    // Load the first file
    pcl::PCLPointCloud2 cloud;
    if (!loadCloud("test.ply", cloud))
        return (-1);

    // Convert to PLY and save
    saveCloud("test_pcd.pcd", cloud, format);

    return (0);
}