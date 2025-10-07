//Ahmed Abdullah Ahmed 20240034 -> Filter 1-4
//Abdelrahman Essam Adly 20240718 -> Filters 2-5
//Mahmoud Khairy Qadry - no id yet (just transfered) -> Filter 3-6-9-12-15 and menu


//The program is an image processing application that allows users to apply various filters and transformations to images.
//It starts with the main function, which prompts the user to enter the name of an image file.
//The program checks if the file exists and then calls the menu function.
//passing the filename as an argument and allowing the user to choose from a list of filters and transformations.

using namespace std;
#include <fstream>
#include <iostream>
#include "Image_Class.h"


int menu(string picname){
    int filtersnum;
    cout <<"Choose filter (By entering just the number):\n 0.Load new image\n 1.Grayscale Conversion\n 2.Black and White\n 3.Invert image\n 4.Merge Images\n 5.Flip image\n 6.Rotate image\n 7.Darken and lighten\n 8.Crop images\n 9.Purple effect\n 10.Detect edges\n 11.resize image\n 12.Blur image\n 13.Sunlight\n 14.Oil painting\n 15.Infrared effect\n 16.Exit\n";
    cout <<"chosen option:";
    cin >> filtersnum;


        if(filtersnum == 0) {                   //Load new image
            string picname1;
            cout <<"Enter picture name with extension (.jpg, .bmp, .png, .tga):";
            cin >> picname1;

            ifstream file(picname1);
            if (file.good()) {
            menu(picname1);
            }   

            else {
            cout << "file does not exist or forgot to write extinsion.\n";

            return 0;
            }
        }


 else if(filtersnum == 1) {                  //Grayscale conv
            string imageName;
    cout << "Enter the colored image name to convert it to grayscale: ";
    cin >> imageName;
    Image image(imageName);

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg = 0; 
            for (int k = 0; k < 3; ++k)
            {
                avg += image(i, j, k);
            }
            avg /= 3; 
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
    cout << "Enter the name of the new image (include extension .jpg, .bmp, .png, or .tga): ";
    cin >> imageName;
    image.saveImage(imageName);
    
        }


        else if(filtersnum == 2) {  //B & W
             string filename;
    cout << "Pls enter colored image name to turn to black&white: ";
    cin >> filename;

    Image image(filename);
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            unsigned int avg = (image(i, j, 0) + image(i, j, 1) + image(i, j, 2)) / 3;
            unsigned int bw_value = (avg > 128) ? 255 : 0;

            for (int k = 0; k < image.channels; k++)
            {
                image(i, j, k) = bw_value;
            }
        }
    }
   cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";

    cin >> filename;
    image.saveImage(filename);
        
        }


        else if(filtersnum == 3) {                  //inverted image
            Image invert_image(picname);

            for (int i = 1; i < invert_image.width; i++) {
                for (int j = 1; j < invert_image.height; j++) {
                    for (int k = 0; k < 3; k++) {
                        invert_image(i, j, k) = 255 - invert_image(i, j, k);
                    }
                }
            }   

            cout << "Pls enter image name to store new image and specify extension(.jpg, .bmp, .png, .tga): ";
            cin >> picname;
            invert_image.saveImage(picname);

            menu(picname);  
       
        }


        else if(filtersnum == 4) {                  //Merge imgage

             auto resizeImage = [&](const Image& input, int newWidth, int newHeight) {
        Image output(newWidth, newHeight);

        float x_ratio = (float)input.width / newWidth;
        float y_ratio = (float)input.height / newHeight;

        for (int i = 0; i < newWidth; ++i) {
            for (int j = 0; j < newHeight; ++j) {
                float origX = i * x_ratio;
                float origY = j * y_ratio;
                for (int k = 0; k < input.channels; ++k) {
                    output(i, j, k) = input((int)origX, (int)origY, k); 
                }
            }
        }
        return output;
    };

    string file1, file2;
    cout << "Enter first image: ";
    cin >> file1;
    cout << "Enter second image: ";
    cin >> file2;

    Image image1(file1);
    Image image2(file2);

    cout << "1-resize smaller\n2-crop bigger\n";
    int choice;
    cin >> choice;
    int width, height;

    if (choice == 1) {
        if (image1.width * image1.height < image2.width * image2.height) {
            image1 = resizeImage(image1, image2.width, image2.height);
        } else {
            image2= resizeImage(image2, image1.width, image1.height);
        }
        width = image1.width;
        height = image1.height;
    } 
    else if (choice == 2) {
        width = min(image1.width, image2.width);
        height = min(image1.height, image2.height);
    } 
    else {
        return 0; 
    }

    Image merged(width, height);

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            for (int k = 0; k < 3; ++k) {
                merged(i, j, k) = (image1(i, j, k) + image2(i, j, k)) / 2;
            }
        }
    }

    string outFile;
    cout << "Enter output image: ";
    cin >> outFile;
    merged.saveImage(outFile);

        }

 
         else if(filtersnum == 5){                  // Flip image
              string filp;
    cout << "Vertical or Horizontal flip? (v/h): ";
    cin >> filp;
    
    string filename;
    cout << "Enter the image filename (with extension): ";
    cin >> filename;
    
    Image image(filename);

    if (filp == "v")
    {
        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height / 2; j++)
            {
                for (int k = 0; k < image.channels; k++) {
                    unsigned int temp = image(i, j, k);
                    image(i, j, k) = image(i, image.height - 1 - j, k);
                    image(i, image.height - 1 - j, k) = temp;
                }
            }
        }
    }
    else if (filp == "h")
    {
        for (int i = 0; i < image.width / 2; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                for (int k = 0; k < image.channels; k++)
                {
                    unsigned int temp = image(i, j, k);
                    image(i, j, k) = image(image.width - 1 - i, j, k);
                    image(image.width - 1 - i, j, k) = temp;
                }
            }
        }
    }
    else {
        cout << "Invalid input. Please enter 'v' for vertical flip or 'h' for horizontal flip." << endl;
        return 1;
    }

    string saved_image = "flipped_" + filename;
    image.saveImage(saved_image);
    cout << "Image saved as: " << saved_image << endl;

         }

        else if(filtersnum == 6) {                  //Rotate image
            int deg;
            cout << "choose degree of rotation(90, 180, 270): ";
            cin >> deg;
            Image Original(picname);
                if (deg == 90){
                    Image Rotate_image(Original.height, Original.width);

                    for (int i = 0; i < Rotate_image.width; i++) {
                        for (int j = 0; j < Rotate_image.height; j++) {
                            for (int k = 0; k < 3; k++) {
                                Rotate_image(i, j, k) = Original(j, (Rotate_image.width - 1) - i, k);
                            }
                        }
                    }
            

                    cout << "Pls enter image name to store new image and specify extension(.jpg, .bmp, .png, .tga): ";
                    cin >> picname;
                    Rotate_image.saveImage(picname);

                    menu(picname);
                }


                else if (deg == 180){
                    Image Rotate_image(Original.width, Original.height);

                    for (int i = 0; i < Rotate_image.width; i++) {
                        for (int j = 0; j < Rotate_image.height; j++) {
                            for (int k = 0; k < 3; k++) {
                                Rotate_image(i, j, k) = Original((Rotate_image.width - 1) - i, (Rotate_image.height - 1) - j, k);
                            }
                        }
                    }
            

                    cout << "Pls enter image name to store new image and specify extension(.jpg, .bmp, .png, .tga): ";
                    cin >> picname;
                    Rotate_image.saveImage(picname);

                    menu(picname);
                    
                }


                else if(deg == 270){
                    Image Rotate_image(Original.height, Original.width);

                    for (int i = 0; i < Rotate_image.width; i++) {
                        for (int j = 0; j < Rotate_image.height; j++) {
                            for (int k = 0; k < 3; k++) {
                                Rotate_image(i, j, k) = Original((Rotate_image.height - 1) - j, i, k);
                            }
                        }
                    }
            

                    cout << "Pls enter image name to store new image and specify extension(.jpg, .bmp, .png, .tga):";
                    cin >> picname;
                    Rotate_image.saveImage(picname);

                    menu(picname);
                }

                else{
                    cout <<"Invalid input\n";
                    menu(picname);
                }    
            }


         else if(filtersnum == 7) {                 //Darken and Lighten
       
             Image image(picname);   
    int mode;
    cout << "For dark enter 0, for light enter 1: ";
    cin >> mode;

    if (mode == 0) {
      
        for (int x = 0; x < image.width; x++) {
            for (int y = 0; y < image.height; y++) {
                for (int c = 0; c < 3; c++) {
                    image(x, y, c) = image(x, y, c) * 0.5;
                }
            }
        }
    } else {
        
        for (int x = 0; x < image.width; x++) {
            for (int y = 0; y < image.height; y++) {
                for (int c = 0; c < 3; c++) {
                    image(x, y, c) = (image(x, y, c) + 255) / 2;
                }
            }
        }
    }

    cout << "Enter output image name : ";
    string outFile;
    cin >> outFile;
    image.saveImage(outFile);        
        }


        else if(filtersnum == 8) {                 //Crop image
        return 0;
        }


        else if(filtersnum == 9) {                 //Purple effect
            Image Original(picname);
            Image purple(Original.width, Original.height);
            int R, G, B;
            for (int i = 0; i <Original.width; i++) {
                for (int j = 0; j < Original.height; j++) {
                    R = Original(i, j, 0) + 50 * 1;
                    G = Original(i, j, 1) - 50 * 0.55;
                    B = Original(i, j, 2) + 50 * 1;

                    if (R > 255) R = 255; if (R < 0) R = 0;

                    if (G > 255) G = 255; if (G < 0) G = 0;

                    if (B > 255) B = 255; if (B < 0) B = 0;
                                        
                    purple(i, j, 0) = R;
                    purple(i, j, 1) = G;
                    purple(i, j, 2) = B;
                }
            }


        cout << "Pls enter image name to store new image and specify extension(.jpg, .bmp, .png, .tga): ";
        cin >> picname;
        purple.saveImage(picname);

        menu(picname); 
           
        }


        else if(filtersnum == 10) {                 //Detect image edges     
            string filename;
    cout << "Enter the source image file name: ";
    cin >> filename;
    Image image(filename);   
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned int grayvalue = (image(i, j, 0) + image(i, j, 1) + image(i, j, 2)) / 3;
            int pixelValue = (grayvalue > 127) ? 255 : 0;
            for (int k = 0; k < 3; k++) {
                image(i, j, k) = pixelValue;
            }
        }
    } 
    Image edgeimage(image.width , image.height);
    for (int i = 1; i < image.width - 1; i++) {
        for (int j = 1; j < image.height - 1; j++) {
            int center = image(i, j, 0);
          if (center == 0 && (image(i-1, j, 0) == 255 || image(i+1, j, 0) == 255)) {
                for (int k = 0; k < 3; k++) edgeimage(i, j, k) = 255;
            } else {
                for (int k = 0; k < 3; k++) edgeimage(i, j, k) = center;
            }
        }
    }
    string outFile;
    cout << "Enter output image name : ";
    cin >> outFile;
    edgeimage.saveImage(outFile); 
            
        }


        else if(filtersnum == 11) {                 //Resize image
        return 0;
        }


        else if(filtersnum == 12) {                 //Blur image
            int blur;
            cout << "Enter blur amount (0-100): ";
            cin >> blur;
            if (blur < 0 || blur > 100) {
                cout << "\nInvalid blur amount. Please retry and enter a value between 0 and 100.\n\n";
                menu(picname);
            }

            
            Image Original(picname);
            Image Blur_eff(Original.width, Original.height);
            int kernel = 25 * blur / 100;

            if (kernel < 3) {
                kernel = 3;
            }

                for (int i = 0; i < Original.width; i++) {
                    for (int j = 0; j < Original.height; j++) {
                        int count = 0;
                        int R = 0;
                        int G = 0;
                        int B = 0;
                        

                        for (int a = i - (kernel - 1) / 2; a <= i + (kernel - 1) / 2; a++) {
                            for (int b = j - (kernel - 1) / 2; b <= j + (kernel - 1) / 2; b++) {
                                if (a >= 0 && a < Original.width && b >= 0 && b < Original.height) {
                                    R += Original(a, b, 0);
                                    G += Original(a, b, 1);
                                    B += Original(a, b, 2);
                                    count++;
                                }
                            }
                        }

                        R /= count;
                        G /= count;
                        B /= count;

                        Blur_eff(i, j, 0) = R;
                        Blur_eff(i, j, 1) = G;
                        Blur_eff(i, j, 2) = B;
                    }
                }


        cout << "Pls enter image name to store new image and specify extension(.jpg, .bmp, .png, .tga): ";
        cin >> picname;
        Blur_eff.saveImage(picname);

        menu(picname);

        }


        else if(filtersnum == 13) {                 //Sunlight
        return 0;
        }


        else if(filtersnum == 14) {                 //Oil painting
        return 0;
        }


        else if(filtersnum == 15) {                 //Infrared
            Image infra(picname);
            for (int i = 1; i < infra.width; i++) {
                for (int j = 1; j < infra.height; j++) {
                        int R = infra(i, j, 0);
                        int G = infra(i, j, 1);
                        int B = infra(i, j, 2);

                R = 255;
                G = 255 - G;
                B = 255 - B;
            
                infra(i, j, 0) = R;
                infra(i, j, 1) = G;
                infra(i, j, 2) = B;
                }
            }


        cout << "Pls enter image name to store new image and specify extension(.jpg, .bmp, .png, .tga): ";
        cin >> picname;
        infra.saveImage(picname);
            
        menu(picname);

        }


        else if(filtersnum == 16) {                 //Exit application
        return 0;
        }
        

        else {
        cout <<"wrong input.\n";
        menu(picname);
        }

    return 0;
    }


int main (){
    string picname;
    cout <<"Enter picture name with extension (.jpg, .bmp, .png, .tga):";
    cin >> picname;

    ifstream file(picname);
    if (file.good()) {
        menu(picname);
    }

    else {
        cout << "file does not exist or forgot to write extinsion.\n";
        main();
    }

    return 0;
}





