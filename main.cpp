#include <iostream>
using namespace std;

// Simple portable pixmap format (PPM) Image Output
int main()
{
    // Create a default 256 x 256 pixel image
    const int imageWidth = 256;
    const int imageHeight = 256;

    cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n"; // PP

    for (int i = imageHeight - 1; i >= 0; i--) // For each row in the image
    {
        cerr << "\rDEBUG: Scanlines remaining: " << i << ' ' << flush;
        for (int j = 0; j < imageWidth; j++) // For each column in the image
        {
            auto r = double(j) / (imageWidth - 1);
            auto g = double(i) / (imageHeight - 1);
            auto b = 0.25; 

            int imageRed = static_cast<int> (255.999 * r);
            int imageGreen = static_cast<int> (255.999 * g);
            int imageBlue = static_cast<int> (255.999 * b);

            cout << imageRed << " " << imageGreen << " " << imageBlue << "\n";
        }
    }

    cerr << "\nDEBUG: Done\n";
}
