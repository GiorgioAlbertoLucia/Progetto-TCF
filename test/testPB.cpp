#include <vector>

#include "../pbPlots/pbPlots.hpp"
#include "../pbPlots/supportLib.hpp"

using namespace std;

int main()
{
    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
    StringReference * errorMessage = new StringReference();

    vector<double> x{-2, -1, 0, 1, 2};
    vector<double> y{2, -1, -2, -1, 2};

    DrawScatterPlot(imageRef, 600, 400, &x, &y, errorMessage);

    vector<double> *pngData = ConvertToPNG(imageRef->image);
    WriteToFile(pngData, "graphs/testPB.png");

    DeleteImage(imageRef->image);


    return 0;
}