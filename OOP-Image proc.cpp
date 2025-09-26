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
        
        }


        else if(filtersnum == 2) {                  //B & W
        
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
        
        }


        else if(filtersnum == 5) {                  //Flip image
        
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


