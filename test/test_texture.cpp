#include "catch2/catch.hpp"

#include <exception>
#include <filesystem>
#include <string>
#include <utility>
#include <dlib/image_io.h>

#include "texture.h"
#include "png_image.h"

namespace fs = std::filesystem;

void make_png(dlib::array2d<dlib::rgb_alpha_pixel>& img, const std::string& path) {
    auto int_generator = Catch::Generators::RandomIntegerGenerator(0, 255);

    for (long row = 0; row < img.nr(); row++) {
        for (long col = 0; col < img.nc(); col++) {
            img[row][col] = dlib::rgb_alpha_pixel(int_generator.get(), 
                                                  int_generator.get(),
                                                  int_generator.get(),
                                                  255);
        }
    }

    dlib::save_png(img, path);
}

TEST_CASE("Texture functionalities", "[texture]") {
    fs::create_directories("test_image");

    Point origin{0, 0};
    long width = 1000;
    long height = 1000;
    Texture atlas{origin, width, height};

    SECTION("Texture has correct metadata") {
        auto meta =  atlas.metadata();

        REQUIRE(meta.origin().X() == 0);
        REQUIRE(meta.origin().Y() == 0);
        REQUIRE(meta.extent().X() == 999);
        REQUIRE(meta.extent().Y() == 999);
    }

    SECTION("Texture's origin can be changed") {
        Point newOrigin{100, 100};
        atlas.setOrigin(newOrigin);
        auto meta = atlas.metadata();

        REQUIRE(meta.origin().X() == 100);
        REQUIRE(meta.origin().Y() == 100);
        REQUIRE(meta.extent().X() == 1099);
        REQUIRE(meta.extent().Y() == 1099);

        // Reset atlas origin
        atlas.setOrigin(origin);
    }

    SECTION("Texture manipulation") {
        dlib::array2d<dlib::rgb_alpha_pixel> small_png_raw(101, 101);
        std::string small_png_path{"test_image/texture_test_small.png"};
        dlib::array2d<dlib::rgb_alpha_pixel> large_png_raw(1001, 1001);
        std::string large_png_path{"test_image/texture_test_large.png"};
        make_png(small_png_raw, small_png_path);
        make_png(large_png_raw, large_png_path);
        Point png_origin{0, 0};
        auto small_png = std::make_shared<PngImage>(small_png_path, png_origin);
        auto large_png = std::make_shared<PngImage>(large_png_path, png_origin);

        SECTION("Texture can insert children if it has enough space") {
            REQUIRE(atlas.addChild(small_png) == true);
            REQUIRE(atlas.addChild(large_png) == false);

            std::string out_path{"test_image/texture_test_generated.png"};
            atlas.save(out_path);

            dlib::array2d<dlib::rgb_alpha_pixel> generated_png_raw;
            dlib::load_png(generated_png_raw, out_path);

            REQUIRE(generated_png_raw.nc() == 1000);
            REQUIRE(generated_png_raw.nr() == 1000);
        }
    }
}