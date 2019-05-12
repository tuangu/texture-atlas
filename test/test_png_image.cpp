#include "catch2/catch.hpp"

#include <exception>
#include <dlib/image_io.h>
#include "png_image.h"

TEST_CASE("PngImage functionalities", "[png_image]") {
    dlib::array2d<dlib::rgb_alpha_pixel> img_1(101, 101);
    dlib::array2d<dlib::rgb_alpha_pixel> img_2(101, 101);
    std::string path_1{"png_image_test_img_1.png"};
    std::string path_2{"png_image_test_img_2.png"};
    for (long row = 0; row < img_1.nr(); row++) {
        for (long col = 0; col < img_1.nc(); col++)
            img_1[row][col] = dlib::rgb_alpha_pixel(255, 0, 0, 1);
    }
    dlib::save_png(img_1, path_1);
    for (long row = 0; row < img_2.nr(); row++) {
        for (long col = 0; col < img_2.nc(); col++)
            img_2[row][col] = dlib::rgb_alpha_pixel(0, 255, 0, 0.5);
    }
    dlib::save_png(img_2, path_2);

    Point origin_img_1{0, 0};
    Point origin_img_2{10, 5};
    PngImage png_img_1{path_1, origin_img_1};
    PngImage png_img_2{path_2, origin_img_2};

    SECTION("PngImage has correct metadata") {
        auto meta = png_img_1.metadata();
        
        REQUIRE(meta.origin().X() == 0);
        REQUIRE(meta.origin().Y() == 0);
        REQUIRE(meta.extent().X() == 100);
        REQUIRE(meta.extent().Y() == 100);
    }

    SECTION("PngImage's origin can be changed") {
        png_img_1.setOrigin(origin_img_2);
        auto img_1_meta = png_img_1.metadata();

        REQUIRE(img_1_meta.origin().X() == 10);
        REQUIRE(img_1_meta.origin().Y() == 5);
        REQUIRE(img_1_meta.extent().X() == 110);
        REQUIRE(img_1_meta.extent().Y() == 105);
        
        // Reset the image metadata
        png_img_1.setOrigin(origin_img_1);
    }

    SECTION("PngImage contains correct data") {
        dlib::array2d<dlib::rgb_alpha_pixel> png_1;
        bool is_throw_exception = false;
        try {
            png_img_1.save(png_1);
        } catch (std::exception& e) {
            is_throw_exception = true;
        }
    
        REQUIRE(is_throw_exception);

        png_1.set_size(
            png_img_1.metadata().height(), png_img_1.metadata().width()
        );
        png_img_1.save(png_1);
        bool is_all_pixel_equal = true;
        for (long row = 0; row < png_1.nr(); row++) {
            for (long col = 0; col < png_1.nc(); col++) {
                if ((png_1[row][col].blue != 0)
                    || (png_1[row][col].red != 255)
                    || (png_1[row][col].green != 0)
                    || (png_1[row][col].alpha != 1)) {
                    is_all_pixel_equal = false;
                    break;
                }
            }
            if (!is_all_pixel_equal)
                break;
        }

        REQUIRE(is_all_pixel_equal);
    }

    SECTION("PngImage is always full") {
        REQUIRE(png_img_1.isEnoughSpace(100) == false);
    }

    SECTION("PngImage can not add children") {
        REQUIRE(png_img_1.addChild(nullptr) == false);
    }
}