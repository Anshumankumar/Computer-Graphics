#include <string>
#include <sstream>
#include <png.h>
#include <stdio.h>
#include <iomanip>
int writeImage(int frameNo , unsigned char *data , int width, int height)
{
    int depth = 8;
    std::stringstream ss;
    ss << std::setw(5) << std::setfill('0') << frameNo;
    std::string s = ss.str();
    std::string filename = "../images/frame_" + s + ".png";
    FILE *fp = fopen(filename.c_str(),"wb");
    if (!fp) return -1;

    png_structp png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING,
            NULL, NULL, NULL);
    if (!png_ptr) return -1;
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        png_destroy_write_struct(&png_ptr,(png_infopp)NULL);
        return -1;
    }
    if
        (setjmp(png_jmpbuf(png_ptr)))
        {
            png_destroy_write_struct(&png_ptr, &info_ptr);
            fclose(fp);
            return -1;
        }
    png_set_IHDR (png_ptr,
            info_ptr,
            width,
            height,
            depth,
            PNG_COLOR_TYPE_RGB,
            PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_BASE,
            PNG_FILTER_TYPE_BASE);
    unsigned char* row_pointers[height];
    data = data + width*(height-1)*3;
    for (int i = 0;i < height;i++)
    {
        row_pointers[i] = data;
        data = data-width*3;
    }
    png_init_io (png_ptr, fp);
    png_write_info(png_ptr, info_ptr);
    png_write_image(png_ptr, row_pointers);
    png_write_end(png_ptr, info_ptr);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose (fp);
    return 0;
}

#ifdef TEST
int main()
{
    int width = 100;
    int height = 100;
    unsigned char *image;
    image   = new unsigned char[width*height*3];
    for (int i =0;i<width;i++)
    {
        for (int j =0; j <height;j++)
        {
            image[300*i + 3*j] = i;
            image[300*i + 3*j +1 ] = i;
            image[300*i + 3*j +2 ] = i;
        }
    }
    writeImage(1,image,100,100);
}
#endif
