#include <string>
#include <iostream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

int main(){
    char* outText;

    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    if (api->Init(nullptr, "eng")) {
        std::cerr << "Could not initialize tesseract." << std::endl;
        return 1;
    }

    // Open input image with leptonica library
    Pix *image = pixRead("./magcardexg300.png");
    api->SetImage(image);
    //Get the specific name rectangle in (left, top, width, height)
    api->SetRectangle(650, 81, 280, 45);
    // Get OCR result for the name
    outText = api->GetUTF8Text();
    printf("OCR output:\n%s", outText);
    //Get the specific card number
    api->SetRectangle(655, 997, 43, 17);
    // Get OCR result for the number
    outText = api->GetUTF8Text();
    printf("%s", outText);

     // Destroy used object and release memory
     api->End();
     delete api;
     delete [] outText;
     pixDestroy(&image);
 
     return 0;
}