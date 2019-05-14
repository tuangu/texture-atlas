#include <cstddef>

#include "app.h"
#include "report.h"

int main(int argc, char* argv[]) try {
    if (argc != 2) {
        throw std::invalid_argument("error: missing images' folder path");
    }

    Report reporter;
    App app(reporter, argv[1]);
    app.run();

    return 0;
} catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
}