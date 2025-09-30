using namespace std;
#include <fstream>
#include <iostream>
#include "Image_Class.h"


int menu(string picname){
    int filtersnum;
    cout <<"Choose filter (By entering just the number):\n 0.Load new image\n 1.Grayscale Conversion\n 2.Black and White\n 3.Invert image\n 4.Merge Images\n 5.Flip image\n 6.Rotate image\n 21.Exit\n";
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
            string filename;
    cout << "Pls enter colored image name to turn to gray scale: ";
    cin >> filename;

    Image image(filename);

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

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";

    cin >> filename;
    image.saveImage(filename);

    return 0;
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
            

                    cout << "Pls enter image name to store new image and specify extension(.jpg, .bmp, .png, .tga): ";
                    cin >> picname;
                    Rotate_image.saveImage(picname);

                    menu(picname);
                }

                else{
                    cout <<"Invalid input\n";
                    menu(picname);
                }    
            }


        else if(filtersnum == 21) {                 //Exit application
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










