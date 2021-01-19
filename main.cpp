#include <iostream>

#include "algorithm.h"
#include "simple_algorithm.h"
#include "matrix.h"

using namespace gradient_finder;

template <typename ImageType>
void solve()
{
    size_t width, height;
    std::cin >> width >> height;

    ImageType image(width, height);
    std::cin.read(image.bytes(), 1); // space
    std::cin.read(image.bytes(), sizeof(image[0][0]) * width * height);

    auto ans = find_gradient(image);
    std::cout << ans.left << ' ' << ans.right << ' ' << ans.up << ' ' << ans.down << std::endl;

    /*std::cout << width << std::endl;
    std::cout << height << std::endl;
    std::cout << int(image.ubytes()[0]) << std::endl;
    std::cout << int(image.ubytes()[50000]) << std::endl;
    std::cout << int(image.ubytes()[50001]) << std::endl;
    std::cout << int(image.ubytes()[50002]) << std::endl;*/

    //std::cout << int(image.bytes()[0]) << ' ' << int(image.bytes()[1337]) << ' ' << int(image.bytes()[1488]);
    //std::cout.write(image.bytes(), sizeof(Gray) * width * height);
}

int main()
{
    bool grayscale;

    std::cin >> grayscale;
    if (grayscale)
    {
        solve<GrayscaleImage>();
    }
    else
    {
        solve<RGBImageType>();
    }

    return 0;
}
