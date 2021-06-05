#include <iostream>
#include <fstream>
#include <filesystem>
#include <random>
#include <climits>
#include <cmath>
#include <math.h>
#include <string>
#include <stdint.h>
# define M_PI           3.14159265358979323846  /* pi */









// task_0 code
void write_bmp(const char* path, const unsigned width, const unsigned height, const int* const data) {
    const unsigned pad=(4-(3*width)%4)%4, filesize=54+(3*width+pad)*height; // horizontal line must be a multiple of 4 bytes long, header is 54 bytes
    char header[54] = { 'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0, 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0 };
    for(unsigned i=0; i<4; i++) {
        header[ 2+i] = (char)((filesize>>(8*i))&255);
        header[18+i] = (char)((width   >>(8*i))&255);
        header[22+i] = (char)((height  >>(8*i))&255);
    }
    char* img = new char[filesize];
    for(unsigned i=0; i<54; i++) img[i] = header[i];
    for(unsigned y=0; y<height; y++) {
        for(unsigned x=0; x<width; x++) {
            const int color = data[x+(height-1-y)*width];
            const int i = 54+3*x+y*(3*width+pad);
            img[i  ] = (char)( color     &255);
            img[i+1] = (char)((color>> 8)&255);
            img[i+2] = (char)((color>>16)&255);
        }
        for(unsigned p=0; p<pad; p++) img[54+(3*width+p)+y*(3*width+pad)] = 0;
    }
    std::ofstream file(path, std::ios::out|std::ios::binary);
    file.write(img, filesize);
    file.close();
    delete[] img;
}

void write_bmp(const char* path, const unsigned width, const unsigned height, const bool* const data) {
    const unsigned pad=(4-(3*width)%4)%4, filesize=54+(3*width+pad)*height; // horizontal line must be a multiple of 4 bytes long, header is 54 bytes
    char header[54] = { 'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0, 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0 };
    for(unsigned i=0; i<4; i++) {
        header[ 2+i] = (char)((filesize>>(8*i))&255);
        header[18+i] = (char)((width   >>(8*i))&255);
        header[22+i] = (char)((height  >>(8*i))&255);
    }
    char* img = new char[filesize];
    for(unsigned i=0; i<54; i++) img[i] = header[i];
    for(unsigned y=0; y<height; y++) {
        for(unsigned x=0; x<width; x++) {
            const int color = (data[x+(height-1-y)*width] ? ((((255) << 8) + 255) << 8) + 255  :  0 );
            const int i = 54+3*x+y*(3*width+pad);
            img[i  ] = (char)( color     &255);
            img[i+1] = (char)((color>> 8)&255);
            img[i+2] = (char)((color>>16)&255);
        }
        for(unsigned p=0; p<pad; p++) img[54+(3*width+p)+y*(3*width+pad)] = 0;
    }
    std::ofstream file(path, std::ios::out|std::ios::binary);
    file.write(img, filesize);
    file.close();
    delete[] img;
}


inline void task_0(){
    //constexpr size_t D = 2;
    constexpr size_t N = 1000;
    constexpr size_t NN = N*N;
    constexpr size_t STEPS = 1000;
    constexpr size_t TOTAL_ITER = 100000;
    constexpr bool GENERATE_IMAGES          = 0;
    constexpr bool GENERATE_DATA            = 1;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dist(0.0,1.0); 

    double offset = std::sqrt(std::sqrt(2));
    double offsetMultiplier = offset;

    bool arr[NN] = {false};

    std::vector<bool*> alive;
    alive.reserve(NN);
    alive.resize(NN);
    size_t potentCount = 0;
    size_t matureIndex = NN-1;

    alive[potentCount++] = &arr[N/2 + NN/2];
    *alive[0] = true;

    std::string dirName_0 = "data/";
    std::filesystem::create_directory(dirName_0.c_str());
    std::string dirName_1 = dirName_0 + "eden_img/";
    std::filesystem::create_directory(dirName_1.c_str());

    std::string fileName = "edenGrowth.txt";
    std::ofstream ofs((dirName_0 + fileName).c_str(), std::ofstream::out);
    for(size_t iter = 0; iter<TOTAL_ITER; iter++){
        bool foundPotent = false;
        int potent;
        do{
            potent = dist(gen) * potentCount;
            bool* neighbour_U = (alive[potent] - N*sizeof(bool));  
            bool* neighbour_D = (alive[potent] + N*sizeof(bool)); 
            bool* neighbour_L = (alive[potent] - sizeof(bool)); 
            bool* neighbour_R = (alive[potent] + sizeof(bool));
            if(!(*neighbour_U && *neighbour_D && *neighbour_L && *neighbour_R)) {
                foundPotent = true;
                bool * neighbours[4];
                int neighbourCount = 0;
                if(!*neighbour_U){
                    neighbours[neighbourCount++] = neighbour_U;
                }
                if(!*neighbour_D){
                    neighbours[neighbourCount++] = neighbour_D;
                }
                if(!*neighbour_L){
                    neighbours[neighbourCount++] = neighbour_L;
                }
                if(!*neighbour_R){
                    neighbours[neighbourCount++] = neighbour_R;
                }
                int i =dist(gen) * neighbourCount;
                *neighbours[i] = true;
                alive[potentCount++] = neighbours[i];

            }
            else{
                alive[matureIndex--] = alive[potent];
                alive[potent] = alive[--potentCount];
            }
        }
        while(!foundPotent);

    
        if(!((iter+1) % static_cast<long>(offset))){
            offset *= offsetMultiplier;
            if constexpr(GENERATE_DATA){
                int x = [&](){
                        int ret = 0;
                        for(int i = 0; i < N; i++){
                            for(int j = 0; j < N; j++){
                                ret += (arr[i*N + j] ? j : 0);
                            }
                        }
                        int c = potentCount + NN - matureIndex - 1;
                        return ret/( c ? c : 1);
                    }();

                int y = [&](){
                        int ret = 0;
                        for(int i = 0; i < N; i++){
                            for(int j = 0; j < N; j++){
                                ret += (arr[i*N + j] ? i : 0);
                            }
                        }
                        int c = potentCount + NN - matureIndex - 1;
                        return ret/( c ? c : 1);
                    }();
/*
                unsigned long r = 0;
                size_t borderCount = 0; // porentCount can have undiscovered unpotent
                for(int i = 0; i < N; i++){
                    for(int j = 0; j < N; j++){
                        const bool* neighbour_U = (&arr[i*N + j] - N*sizeof(bool));  
                        const bool* neighbour_D = (&arr[i*N + j] + N*sizeof(bool)); 
                        const bool* neighbour_L = (&arr[i*N + j] - sizeof(bool)); 
                        const bool* neighbour_R = (&arr[i*N + j] + sizeof(bool));
                        if(!(*neighbour_U && *neighbour_D && *neighbour_L && *neighbour_R)) {
                            r += std::sqrt(pow(x-j,2) + pow(y-i,2));
                            borderCount++;
                        }
                    }
                }
                r /= borderCount;
*/
            
                unsigned long r0 = 0;
                unsigned long r1 = 0;
                unsigned long r2 = 0;
                unsigned long r3 = 0;
                while( arr[(y+r0)*N + x]) r0++;
                while( arr[(y)*N + x+r1]) r1++;
                while( arr[(y-r2)*N + x]) r2++;
                while( arr[(y)*N + x-r3]) r3++;

                unsigned long r01 = 0;
                unsigned long r12 = 0;
                unsigned long r23 = 0;
                unsigned long r30 = 0;
                while( arr[(y+r01)*N + x+r01]) r01++;
                while( arr[(y-r12)*N + x+r12]) r12++;
                while( arr[(y-r23)*N + x-r23]) r23++;
                while( arr[(y+r30)*N + x-r30]) r30++;
                double r = (r0+r1+r2+r3 + (r01+r12+r23+r30)*std::sqrt(2))/8.0;

                ofs << iter+2 << " " << r << "\n";
            }
            if constexpr(GENERATE_IMAGES){
                std::string imgName = "eden(" + std::to_string(iter) + ").bmp";
                write_bmp((dirName_1+imgName).c_str(), N, N, arr);

            }

        }
    }
    ofs.close();
}










// task_1 code
void task_1(){
    //constexpr size_t D = 2;
    constexpr size_t N = 1000;
    constexpr size_t NN = N*N;
    constexpr size_t STEPS = 1000;
    constexpr size_t TOTAL_ITER = 100000;
    constexpr size_t MODE = 2;
    constexpr size_t GENERATOR = 0;
    constexpr size_t CRAWLER = 0;
    constexpr bool GENERATE_IMAGES          = 1;
    constexpr bool GENERATE_DATA            = 1;
    constexpr bool IGNORE_EXISTING_IMAGES   = 1;
    constexpr bool IGNORE_EXISTING_FILES    = 0;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dist(0.0,1.0); 

    double offset = std::sqrt(std::sqrt(2));
    double offsetMultiplier = offset;

    bool arr[NN] = {false};


    arr[N/2 + NN/2] = true;
    if constexpr (MODE == 1){
        arr[N/2+1 + NN/2    ] = true;
        arr[N/2+1 + NN/2 + N] = true;
        arr[N/2   + NN/2 + N] = true;
    }
    else if constexpr (MODE == 2){
        arr[N/2+1 + NN/2    ] = true;
        arr[N/2+1 + NN/2 + N] = true;
        arr[N/2   + NN/2 + N] = true;

        arr[N/2-1   + NN/2 - N] = true;
        arr[N/2-1   + NN/2 ] = true;
        arr[N/2-1   + NN/2 + N] = true;
        arr[N/2   + NN/2 - N] = true;
        arr[N/2+1   + NN/2 - N] = true;

    }
    

    std::string dirName_0 = "data/";
    std::filesystem::create_directory(dirName_0.c_str());
    std::string dirName_1 = dirName_0 + "dla_img_mode" + std::to_string(MODE)  + "_gen" + std::to_string(GENERATOR)  + "_crawl" + std::to_string(CRAWLER)  + "/";
    std::filesystem::create_directory(dirName_1.c_str());

    std::string fileName = "dlaGrowth_M" + std::to_string(MODE)  + "G" + std::to_string(GENERATOR)  + "C" + std::to_string(CRAWLER) + ".txt";
    std::ofstream ofs;
    if (!std::filesystem::exists((dirName_0 + fileName).c_str())) ofs.open((dirName_0 + fileName).c_str(), std::ofstream::out);
    for(size_t iter = 0; iter<TOTAL_ITER; iter++){
       
                double x;
                double y;
                if constexpr (GENERATOR == 0){
                    if((iter-2) < N/2){
                        do {
                            x = dist(gen) * (iter-2) + (iter)/2;
                            y = dist(gen) * (iter-2) + (iter)/2;
                        }while(arr[static_cast<size_t>(y)*N + static_cast<size_t>(x)]);
                    }
                    else{
                        do {
                            x = dist(gen) * (N-4)+2;
                            y = dist(gen) * (N-4)+2;
                        }while(arr[static_cast<size_t>(y)*N + static_cast<size_t>(x)]);
                    }
                }
                else if constexpr (GENERATOR == 1){
                    double alpha = dist(gen) * 2 *M_PI;
                    x = cos(alpha) * (N/2 - 1) + N/2;
                    y = sin(alpha) * (N/2 - 1) + N/2;
                }
                else if constexpr (GENERATOR == 2){
                    switch(static_cast<size_t>(dist(gen) * 4)){
                        case 0:
                            x = dist(gen) * (N-3) +1.5;
                            y = 2;
                            break;
                        case 1:
                            x = N-3;
                            y = dist(gen) * (N-3) +1.5;
                            break;
                        case 2:
                            x = dist(gen) * (N-3) +1.5;
                            y = N-3;
                            break;
                        case 3:
                            x = 2;
                            y = dist(gen) * (N-3) +1.5;
                            break;
                    }
                }
                else if constexpr (GENERATOR == 3){
                    static const double translate =  (1000 - sqrt(3)*500);
                    switch(static_cast<size_t>(dist(gen) * 3)){
                        case 0:
                            x = dist(gen) * (N-3) +1.5;
                            y = translate;
                            break;
                        case 1:
                            x = dist(gen) * (N-3)/2 +1.5;
                            y = sqrt(3)*x + translate;
                            break;
                        case 2:
                            x = dist(gen) * (N-3)/2 +1.5+(N-3)/2;
                            y = -sqrt(3)*x + 1000*sqrt(3) +translate;
                            break;
                    }
                }
                else if constexpr (GENERATOR == 4){
                    switch(static_cast<size_t>(dist(gen) * 2)){
                        case 0:
                            x = 2;
                            y = 2;
                            break;
                        case 1:
                            x = (N-3);
                            y = (N-3);
                            break;
                    }
                }

                while(static_cast<size_t>(
                    arr[(static_cast<size_t>(y)-1)*N + static_cast<size_t>(x)] +
                    arr[(static_cast<size_t>(y)-1)*N + static_cast<size_t>(x)+1] +
                    arr[(static_cast<size_t>(y))*N + static_cast<size_t>(x)+1] +
                    arr[(static_cast<size_t>(y)+1)*N + static_cast<size_t>(x)+1] +
                    arr[(static_cast<size_t>(y)+1)*N + static_cast<size_t>(x)] +
                    arr[(static_cast<size_t>(y)+1)*N + static_cast<size_t>(x)-1] +
                    arr[(static_cast<size_t>(y))*N + static_cast<size_t>(x)-1] +
                    arr[(static_cast<size_t>(y)+-1)*N + static_cast<size_t>(x)-1]
                    ) < MODE+1
                ){

                    if constexpr (CRAWLER == 0){
                        double temp_x;
                        double temp_y;
                        do{
                            switch(static_cast<size_t>(dist(gen) * 4)){
                            case 0:
                                temp_x = x + 1;
                                break;
                            case 1:
                                temp_y = y + 1;
                                break;
                            case 2:
                                temp_x = x - 1;
                                break;
                            case 3:
                                temp_y = y - 1;
                                break;
                        }
                        }
                        while(temp_x < 2 || temp_x > N-3 || temp_y < 2 || temp_y > N-3 || arr[static_cast<size_t>(y)*N + static_cast<size_t>(x)]);
                        x = temp_x;
                        y = temp_y;
                    }
                    else if constexpr (CRAWLER == 1){
                        double d = std::sqrt(pow(x - N/2,2) + pow(y - N/2,2));
                        double alpha = std::asin((x-N/2)/d);
                        double beta = std::asin((y-N/2)/d);

                        double tetha = dist(gen) * M_PI*(3.0/4.0) - M_PI*(3.0/8.0);
                        x -= sin(alpha + tetha);
                        y -= sin(beta - tetha);
                    }
                }

                arr[static_cast<size_t>(y)*N + static_cast<size_t>(x)] = true;

                



        if(!((iter+1) % static_cast<long>(offset))){
            offset *= offsetMultiplier;
            if constexpr(GENERATE_DATA){
                /*
                unsigned long r0 = 0;
                unsigned long r1 = 0;
                unsigned long r2 = 0;
                unsigned long r3 = 0;
                while( !arr[(r0)*N + N/2]) r0++;
                while( !arr[(N/2)*N + N-1-r1]) r1++;
                while( !arr[(N-1-r2)*N + N/2]) r2++;
                while( !arr[(N/2)*N + r3]) r3++;

                unsigned long r01 = 0;
                unsigned long r12 = 0;
                unsigned long r23 = 0;
                unsigned long r30 = 0;
                while( !arr[(r01)*N + r01]) r01++;
                while( !arr[(r12)*N + N-1-r12]) r12++;
                while( !arr[(N-1-r23)*N + N-1-r23]) r23++;
                while( !arr[(N-1-r30)*N + r30]) r30++;
                double r = (2/N * (r0+r1+r2+r3) + (2*N-(r01+r12+r23+r30))*std::sqrt(2))/8.0;
                */

                double max_radius = 0.0;
                for(int i = 0; i < N; i++){
                    for(int j = 0; j < N; j++){
                        if(arr[i*N + j]){
                            double r = std::sqrt(pow(i-static_cast<int>(N/2), 2) + pow(j-static_cast<int>(N/2), 2));
                            if(max_radius < r) max_radius = r;
                            //std::cout << r << " " << max_radius << std::endl;
                        }
                    }
                }

                ofs << iter+2 << " " << max_radius << "\n";
            }
            if constexpr(GENERATE_IMAGES){
                std::string imgName = "dla_M" + std::to_string(MODE)  + "G" + std::to_string(GENERATOR)  + "C" + std::to_string(CRAWLER)  + "(" + std::to_string(iter) + ").bmp";
                if constexpr(!IGNORE_EXISTING_IMAGES) {
                    if (! std::filesystem::exists((dirName_1 + imgName).c_str())){
                        write_bmp((dirName_1+imgName).c_str(), N, N, arr);
                    }
                }
                else{
                    write_bmp((dirName_1+imgName).c_str(), N, N, arr);
                }
            }
        }
    }
    ofs.close();
}










// task_2 code 
void task_2(){
    constexpr size_t N = 1000;
    constexpr size_t NN = N*N;
    constexpr size_t STEPS = 1000;
    constexpr size_t TOTAL_ITER = 490;
    constexpr size_t MODE = 2;
    constexpr bool GENERATE_IMAGES          = 1;
    constexpr bool GENERATE_DATA            = 0;
    constexpr bool IGNORE_EXISTING_IMAGES   = 1;
    constexpr bool IGNORE_EXISTING_FILES    = 0;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dist(0.0,1.0); 

    double offset = std::sqrt(std::sqrt(2));
    double offsetMultiplier = offset;

    bool arr[NN] = {false};


    arr[N/2 + NN/2] = true;
    if constexpr (MODE == 2){
        arr[N/2+1 + NN/2    ] = true;
        arr[N/2+1 + NN/2 + N] = true;
        arr[N/2   + NN/2 + N] = true;
    }

    std::string dirName_0 = "data/";
    std::filesystem::create_directory(dirName_0.c_str());
    std::string dirName_1 = dirName_0 + "snow_img_mode" + std::to_string(MODE)  + "/";
    std::filesystem::create_directory(dirName_1.c_str());

    std::string fileName = "snowGrowth_" + std::to_string(MODE)  + ".txt";
    std::ofstream ofs;
    if (!std::filesystem::exists((dirName_0 + fileName).c_str())) ofs.open((dirName_0 + fileName).c_str(), std::ofstream::out);
    for(size_t iter = 0; iter<TOTAL_ITER; iter++){
       
    
        std::vector<bool*> potent;
        for(int i = 1; i < N-1; i++){
            for(int j = 1; j < N-1; j++){
                size_t neighbors = static_cast<size_t>(
                    arr[i*N + j+1] +
                    arr[i*N + j-1] +
                    arr[(i-1)*N + j] +
                    arr[(i+1)*N + j] +
                    arr[(i-1)*N + j + ( i%2 ? 1 : -1)] +
                    arr[(i+1)*N + j + ( i%2 ? 1 : -1)]
                );

                if constexpr (MODE == 0) { if( neighbors == 1 ){ potent.push_back(&arr[i*N + j]);} }
                if constexpr (MODE == 1) { if( neighbors  > 0 ){ potent.push_back(&arr[i*N + j]);} }
                if constexpr (MODE == 2) { if( neighbors == 2 ){ potent.push_back(&arr[i*N + j]);} }
                
            }
        }

        for(int i = 0; i < potent.size(); i++){
            *potent[i] = true;
        }
        

    
        if(!((iter+1) % static_cast<long>(offset))){
            offset *= offsetMultiplier;
            if constexpr(GENERATE_DATA){
                
            }
            if constexpr(GENERATE_IMAGES){
                std::string imgName = "snow(" + std::to_string(iter) + ").bmp";
                if constexpr(IGNORE_EXISTING_FILES) {
                    if (! std::filesystem::exists((dirName_1 + imgName).c_str())){
                        write_bmp((dirName_1+imgName).c_str(), N, N, arr);
                    }
                }
                else{
                    write_bmp((dirName_1+imgName).c_str(), N, N, arr);
                }
            }
        }
    }
    ofs.close();
}







int main(){
    const int TASK_PART = 1;

    if constexpr (TASK_PART == 0) task_0();
    if constexpr (TASK_PART == 1) task_1();
    if constexpr (TASK_PART == 2) task_2();

    return 0;
}