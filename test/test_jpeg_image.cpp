#include "catch2/catch.hpp"

#include <filesystem>
#include <exception>
#include <dlib/image_io.h>

#include "jpeg_image.h"

namespace fs = std::filesystem;

TEST_CASE("JpegImage functionalities", "[jpeg_image]") {
    fs::create_directories("test_image");
    dlib::array2d<dlib::rgb_pixel> img_1(101, 101);
    dlib::array2d<dlib::rgb_pixel> img_2(101, 101);
    std::string path_1{"test_image/jpeg_image_test_img_1.jpeg"};
    std::string path_2{"test_image/jpeg_image_test_img_2.jpeg"};
    for (long row = 0; row < img_1.nr(); row++) {
        for (long col = 0; col < img_1.nc(); col++)
            img_1[row][col] = dlib::rgb_pixel(200, 0, 0);
    }
    dlib::save_jpeg(img_1, path_1);
    for (long row = 0; row < img_2.nr(); row++) {
        for (long col = 0; col < img_2.nc(); col++)
            img_2[row][col] = dlib::rgb_pixel(0, 200, 0);
    }
    dlib::save_jpeg(img_2, path_2);

    Point origin_img_1{0, 0};
    Point origin_img_2{10, 5};
    JpegImage jpeg_img_1{path_1, origin_img_1};
    JpegImage jpeg_img_2{path_2, origin_img_2};

    SECTION("JpegImage has correct metadata") {
        auto meta = jpeg_img_1.metadata();
        
        REQUIRE(meta.origin().X() == 0);
        REQUIRE(meta.origin().Y() == 0);
        REQUIRE(meta.extent().X() == 100);
        REQUIRE(meta.extent().Y() == 100);
    }

    SECTION("JpegImage's origin can be changed") {
        jpeg_img_1.setOrigin(origin_img_2);
        auto img_1_meta = jpeg_img_1.metadata();

        REQUIRE(img_1_meta.origin().X() == 10);
        REQUIRE(img_1_meta.origin().Y() == 5);
        REQUIRE(img_1_meta.extent().X() == 110);
        REQUIRE(img_1_meta.extent().Y() == 105);
        
        // Reset the image metadata
        jpeg_img_1.setOrigin(origin_img_1);
    }

    SECTION("JpegImage contains correct data") {
        dlib::array2d<dlib::rgb_alpha_pixel> jpeg_1;
        bool is_throw_exception = false;
        try {
            jpeg_img_1.save(jpeg_1);
        } catch (std::exception& e) {
            is_throw_exception = true;
        }
    
        REQUIRE(is_throw_exception);

        jpeg_1.set_size(
            jpeg_img_1.metadata().height(), jpeg_img_1.metadata().width()
        );
        jpeg_img_1.save(jpeg_1);
        bool is_all_pixel_equal = true;
        for (long row = 0; row < jpeg_1.nr(); row++) {
            for (long col = 0; col < jpeg_1.nc(); col++) {
                if ((jpeg_1[row][col].blue != 0)
                    || (jpeg_1[row][col].red != 200)
                    || (jpeg_1[row][col].green != 0)) {
                    is_all_pixel_equal = false;
                    break;
                }
            }
            if (!is_all_pixel_equal)
                break;
        }

        REQUIRE(is_all_pixel_equal);
    }

    SECTION("JpegImage can not add children") {
        REQUIRE(jpeg_img_1.addChild(nullptr) == false);
    }
}