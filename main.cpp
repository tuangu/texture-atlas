#include <cstddef>
#include <exception>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>

#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include "png_image.h"

int main(int argc, char* argv[]) try {
    if (argc != 2) 
        throw std::invalid_argument("error: missing image paths");

    // std::string img_path_1{argv[1]};
    // std::string img_path_2{argv[2]};
    // dlib::image_window win;
    // dlib::array2d<dlib::rgb_alpha_pixel> img_1;
    // dlib::array2d<dlib::rgb_alpha_pixel> img_2;
    // dlib::load_png(img_1, img_path_1);
    // dlib::load_png(img_2, img_path_2);

    // dlib::array2d<dlib::rgb_alpha_pixel> img(img_1.nr() + img_2.nr(), std::max(img_1.nc(), img_2.nc()));
    // for (long row = 0; row < img.nr(); row++) {
    //     for (long col = 0; col < img.nc(); col++)
    //         img[row][col] = dlib::rgb_alpha_pixel(255, 255, 255, 0);
    // }

    // for (long row = 0; row < img_1.nr(); row++) {
    //     for (long col = 0; col < std::min(img_1.nc(), img.nc()); col++) {
    //         img[row][col] = img_1[row][col];
    //     }
    // }
    // long img_1_row = img_1.nr();
    // for (long row = 0; row < img_2.nr(); row++) {
    //     for (long col = 0; col < std::min(img_2.nc(), img.nc()); col++) {
    //         img[row + img_1_row][col] = img_2[row][col];
    //     }
    // }

    // win.set_background_color(255, 255, 255);
    // win.set_image(img);
    // std::cin.get();
    // dlib::array2d<dlib::rgb_alpha_pixel> img_1;
    // dlib::load_png(img_1, argv[1]);
    // dlib::save_jpeg(img_1, "img.jpeg");
    // dlib::save_png(img_1, "img.png");

    Point p{0,0};
    PngImage img{argv[1], p};
    img.save("img.png");

    return 0;
} catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
}