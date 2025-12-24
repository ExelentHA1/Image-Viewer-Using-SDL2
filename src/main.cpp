#include <bits/stdc++.h>
#include "Window.hpp"

// windows are hardcoded relative to the dimention of the image
const int HIGHT = 526;
const int WIDTH = 526;

int main(int argc,char* argv[])
{
    WindowRenderer WINDOW;
    WINDOW.create("Yes. You read tha right!!", WIDTH, HIGHT);
    std::string str;

    // Open the binary file for reading
    std::ifstream file("Fuck.rgb", std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file for reading.";
        return 1;
    }
    size_t bytes = WIDTH * HIGHT * 3;
    size_t pix_inx = 0; // pixel index
    int r, g, b; // rgb values
    unsigned char* buffer = new unsigned char[bytes]; // byte arrays 
    file.read(reinterpret_cast<char*>(buffer), bytes); // dumbgpt said this line is unnesessary thakfully copilot print it back..

    bool run = true;
    SDL_Event event;
    while(run)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                run = false;
        }
        WINDOW.clear();
        // render image
        pix_inx = 0; // reset index for each frame (copilot fix)
        for(int y = 0; y < HIGHT; y++)
        {
            for(int x = 0; x < WIDTH; x++)
            {
                /*.raw file bytes group is R G B R G B R G B ...
                the 1st group of bytes R G B, is the pixel data
                of an image... we can also see it like this
                R1 G1 B1 R2 G2 B2 R3 G3 B3 .....
                we need to properly index the iteration by 3
                Ex: index 1 reads R1 G1 B1 => index 2 is R2 G2 B2 */

                r = buffer[pix_inx];
                g = buffer[pix_inx + 1];
                b = buffer[pix_inx + 2];
                pix_inx += 3; // thanks to copilot for debugging the code... my code is -> pix_inx++; (im a dumb fuck)
                WINDOW.render(x, y, r, g, b);

            }
        }
        WINDOW.present();
        // constrains cuz' if we dont, it will run the process as fast as your computer can (the program will cpu intensive)
        SDL_Delay(1000); 
    }
    WINDOW.clean();
    delete[] buffer;
    file.close();

    return 0;
}
