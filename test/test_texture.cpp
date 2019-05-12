#include "catch2/catch.hpp"

#include <exception>
#include <string>
#include <utility>
#include <dlib/image_io.h>
#include "texture.h"
#include "png_image.h"

void make_png(dlib::array2d<dlib::rgb_alpha_pixel>& img, const std::string& path) {
    auto int_generator = Catch::Generators::RandomIntegerGenerator(0, 255);

    for (long row = 0; row < img.nr(); row++) {
        for (long col = 0; col < img.nc(); col++) {
            img[row][col] = dlib::rgb_alpha_pixel(int_generator.get(), 
                                                  int_generator.get(),
                                                  int_generator.get(),
                                                  1);
        }
    }

    dlib::save_png(img, path);
}

TEST_CASE("Texture functionalities", "[texture]") {
    Point origin{0, 0};
    long width = 1000;
    long height = 1000;
    Texture atlas{origin, width, height};

    REQUIRE(atlas.get_textures_size() == 0);

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
        std::string small_png_path{"texture_test_small.png"};
        dlib::array2d<dlib::rgb_alpha_pixel> large_png_raw(1001, 1001);
        std::string large_png_path{"texture_test_large.png"};
        make_png(small_png_raw, small_png_path);
        make_png(large_png_raw, large_png_path);
        Point png_origin{0, 0};
        auto small_png = std::make_unique<PngImage>(small_png_path, png_origin);
        auto large_png = std::make_unique<PngImage>(large_png_path, png_origin);

        SECTION("Other image can check if it fits into the texture") {
            REQUIRE(atlas.isEnoughSpace(small_png->metadata().area()) == true);
            REQUIRE(atlas.isEnoughSpace(large_png->metadata().area()) == false);
        }

        SECTION("Texture can insert children if it has enough space") {
            REQUIRE(atlas.addChild(std::move(small_png)) == true);
            REQUIRE(atlas.addChild(std::move(large_png)) == false);

            REQUIRE(small_png == nullptr);
            REQUIRE(large_png == nullptr);
            
            REQUIRE(atlas.get_textures_size() == 3);

            std::string out_path{"texture_test_generated.png"};
            atlas.save(out_path);

            dlib::array2d<dlib::rgb_alpha_pixel> generated_png_raw;
            dlib::load_png(generated_png_raw, out_path);

            REQUIRE(generated_png_raw.nc() == 1000);
            REQUIRE(generated_png_raw.nr() == 1000);
        }
    }
}