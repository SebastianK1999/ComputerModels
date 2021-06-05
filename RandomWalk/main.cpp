#include <iostream>
#include <fstream>
#include <filesystem>
#include <random>
#include <climits>
#include <cmath>
#include <string>










// task_0 code
static unsigned long holdrand = 0;

inline int myRand(void){
    holdrand = holdrand * 214013 + 2531011;
    return (unsigned int)(holdrand >> 16) % 0x7fff;
}

void mySrand(unsigned int seed){
    holdrand = seed;
}

inline void task_0(){
    constexpr size_t loops = 10000;
    constexpr size_t range = 100;
    size_t randHist[range+1] = {0};
    size_t mt19937Hist[range+1] = {0};

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dist(0.0,1.0); 
    mySrand(rd());

    for(size_t _ = 0;  _ < loops; _++){
        randHist[(size_t)(floor((myRand() / float(32767))*range))]++;
        mt19937Hist[(size_t)(floor(dist(gen) * range))]++;
    }


    //ofs << "i, rand(), std::mt19937\n";

    size_t sumRd = 0;
    size_t sumMt = 0;
    for(int i = 0; i < range;  i++){
        sumRd += randHist[i];
        sumMt += mt19937Hist[i];
        std::cout << i << " " << randHist[i] << " " << mt19937Hist[i] << "\n";
    }


    std::cout << "sumRd:\t" << sumRd << "\tsumMt:\t" << sumMt << "\n";
}










// task_1 code
template <unsigned int D>
void randMove(const double* pos0, double* pos1){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<size_t> dist_index(0, D-1); 
    static std::uniform_int_distribution<uint16_t> dist_sign(0, 1); 

    size_t direction_index = dist_index(gen);
    uint16_t direction_sign = dist_sign(gen);

    for(int i = 0; i < D; i++){
        pos1[i] = pos0[i];    
    }

    pos1[direction_index] += (direction_sign == 1 ? 1 : -1 );
}

void task_1(){
    constexpr size_t STEPS = 1000;
    constexpr size_t D = 2;
    constexpr size_t TOTAL_ITER = 1000;
    constexpr bool OFS_TITLES = false;
    constexpr bool IGNORE_EXISTING_FILES = false;
    const static std::string SEP = " ";

    double arr[STEPS][D] = {0};

    for(int iter = 0; iter < TOTAL_ITER; iter++){
        std::string dirName = "walks/" + std::to_string(D) + "D/";
        std::filesystem::create_directory(dirName.c_str());
        std::string fileName = "walk(" + std::to_string(iter) + ").txt";
        if constexpr(!IGNORE_EXISTING_FILES) if (std::filesystem::exists((dirName + fileName).c_str())) continue;

        std::ofstream ofs((dirName + fileName).c_str(), std::ofstream::out);
        if constexpr(D > 1){
            if constexpr (OFS_TITLES){
                ofs << "x0";
                for(int d = 1; d < D; d ++){
                    ofs << SEP << "x" + std::to_string(d);
                }
                ofs << "\n";
            }

            ofs << arr[0][0];
            for(int j = 1; j < D; j ++){
                ofs << SEP << arr[1][j];
            }
            ofs << "\n";

            for(int i = 1; i < STEPS; i ++){
                randMove<D>(arr[i-1], arr[i]);
                ofs << arr[i][0];
                for(int j = 1; j < D; j ++){
                    ofs << SEP << arr[i][j];
                }
                ofs << "\n";
            }
        }
        else{
            if constexpr(OFS_TITLES) ofs << "x0" << SEP << "x1" << "\n";

            ofs << 0 << SEP << arr[1][0] << "\n";
            for(int i = 1; i < STEPS; i ++){
                randMove<D>(arr[i-1], arr[i]);
                ofs << i << SEP << arr[i][0] << "\n";
            }
        }
        ofs.close();
    }
}










// task_2 code 
void task_2(){
    constexpr size_t STEPS = 1000;
    constexpr size_t D = 2;
    constexpr size_t TOTAL_ITER = 100000;
    constexpr bool OFS_TITLES = false;
    const static std::string SEP = " ";

    std::string dirName = "walks/";
    //std::filesystem::create_directory(dirName.c_str());
    std::string fileName = "endOfWalks_" + std::to_string(D) + "D.txt";
    std::ofstream ofs((dirName + fileName).c_str(), std::ofstream::out);

    if constexpr (OFS_TITLES){
        ofs << "x0";
        for(int d = 1; d < D; d ++){
            ofs << SEP << "x" + std::to_string(d);
        }
        ofs << "\n";
    }
    
    for(int iter = 0; iter < TOTAL_ITER; iter++){
        double arr0[D] = {0};
        double arr1[D] = {0};
        double* first;
        double* second;
        first = arr0;
        second = arr1;

        for(int i = 0; i < STEPS; i ++){
            randMove<D>(first, second);
            std::swap(first, second);
        }
        ofs << first[0];
        for(int i = 1; i < D; i ++){
            ofs << SEP << first[i];
        }
        ofs << "\n";
    }
}










// task_3 code 
void task_3(){
    constexpr size_t STEPS = 1000;
    constexpr size_t D = 1;
    constexpr size_t TOTAL_ITER = 100000;
    constexpr bool OFS_TITLES = false;
    const static std::string SEP = " ";

    size_t backTostartCount[STEPS] = {0};

    std::string dirName = "walks/";
    std::string fileName = "backTostartCount_" + std::to_string(D) + "D.txt";
    std::ofstream ofs((dirName + fileName).c_str(), std::ofstream::out);

    if constexpr (OFS_TITLES){
        ofs << "x0";
        for(int d = 1; d < D; d ++){
            ofs << SEP << "x" + std::to_string(d);
        }
        ofs << "\n";
    }
    
    for(int iter = 0; iter < TOTAL_ITER; iter++){
        double arr0[D] = {0};
        double arr1[D] = {0};
        double* first;
        double* second;
        first = arr0;
        second = arr1;

        for(int i = 0; i < STEPS; i ++){
            randMove<D>(first, second);
            [&](){
                for(int j = 0; j < D; j++){
                    if(second[j] != 0 ) return;
                }
                backTostartCount[i] += 1;
            }();
            std::swap(first, second);
        }
    }

    for(int i = 0; i < STEPS; i ++){ // [0] breaks the plot
        ofs << backTostartCount[i] << "\n";
    }

}










// task_4 code 
void task_4(){
    // the same as task_1 byt deferent parameters
    constexpr size_t STEPS = 1000;
    constexpr size_t D = 3;
    constexpr size_t TOTAL_ITER = 10;
    constexpr bool OFS_TITLES = false;
    constexpr bool IGNORE_EXISTING_FILES = false;
    const static std::string SEP = " ";

    double arr[STEPS][D] = {0};

    for(int iter = 0; iter < TOTAL_ITER; iter++){
        std::string dirName = "walks/" + std::to_string(D) + "D/";
        std::filesystem::create_directory(dirName.c_str());
        std::string fileName = "walk(" + std::to_string(iter) + ").txt";
        if constexpr(!IGNORE_EXISTING_FILES) if (std::filesystem::exists((dirName + fileName).c_str())) continue;

        std::ofstream ofs((dirName + fileName).c_str(), std::ofstream::out);
        if constexpr(D > 1){
            if constexpr (OFS_TITLES){
                ofs << "x0";
                for(int d = 1; d < D; d ++){
                    ofs << SEP << "x" + std::to_string(d);
                }
                ofs << "\n";
            }

            ofs << arr[0][0];
            for(int j = 1; j < D; j ++){
                ofs << SEP << arr[1][j];
            }
            ofs << "\n";

            for(int i = 1; i < STEPS; i ++){
                randMove<D>(arr[i-1], arr[i]);
                ofs << arr[i][0];
                for(int j = 1; j < D; j ++){
                    ofs << SEP << arr[i][j];
                }
                ofs << "\n";
            }
        }
        else{
            if constexpr(OFS_TITLES) ofs << "x0" << SEP << "x1" << "\n";

            ofs << 0 << SEP << arr[1][0] << "\n";
            for(int i = 1; i < STEPS; i ++){
                randMove<D>(arr[i-1], arr[i]);
                ofs << i << SEP << arr[i][0] << "\n";
            }
        }
        ofs.close();
    }
}










// task_5 code 
template <unsigned int D>
void randMove_diagonal(const double* pos0, double* pos1){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<size_t> dist_index(0, D-1); 
    static std::uniform_int_distribution<uint16_t> dist_sign(0, 1); 

    bool isMoved = false;
    
    for(int i = 0; i < D; i++){
        pos1[i] = pos0[i];
        if(dist_sign(gen) == 0){
            isMoved = true;
            pos1[i] += (dist_sign(gen) == 1 ? 1 : -1 );
        }
    }
    if(!isMoved){
        size_t direction_index = dist_index(gen);
        uint16_t direction_sign = dist_sign(gen);
        pos1[direction_index] += (direction_sign == 1 ? 1 : -1 );
    }
}

void task_5(){
    constexpr size_t STEPS = 10000;
    constexpr size_t D = 3;
    constexpr size_t TOTAL_ITER = 10000;
    constexpr bool OFS_TITLES = false;
    const static std::string SEP = " ";

    double x[STEPS] = {0};
    double x2[STEPS] = {0};

    std::string dirName = "walks/";
    std::string fileName = "shift_" + std::to_string(D) + "D.txt";
    std::ofstream ofs((dirName + fileName).c_str(), std::ofstream::out);

    if constexpr (OFS_TITLES){
        ofs << "x" << SEP << "x^2" << SEP << "sqrt(x^2)" << "\n";
    }
    
    for(int iter = 0; iter < TOTAL_ITER; iter++){
        double arr0[D] = {0};
        double arr1[D] = {0};
        double* first;
        double* second;
        first = arr0;
        second = arr1;

        for(int i = 0; i < STEPS; i ++){
            randMove<D>(first, second);
            int xx = [&](){
                int value = first[0] * first[0];
                for(int d = 1;  d < D; d++){
                    value += first[0] * first[0];
                }
                return value;
            }();
            double sqrxx = std::sqrt(xx);

            x[i] += sqrxx;
            x2[i] += xx;

            std::swap(first, second);
        }
    }

    for(int i = 0; i < STEPS; i ++){
        ofs << x[i] / TOTAL_ITER << SEP << x2[i] / TOTAL_ITER << SEP << sqrt(x2[i] / TOTAL_ITER) << "\n";
    }
}










int main(){
    const int TASK_PART = 5;

    if constexpr (TASK_PART == 0) task_0();
    if constexpr (TASK_PART == 1) task_1();
    if constexpr (TASK_PART == 2) task_2();
    if constexpr (TASK_PART == 3) task_3();
    if constexpr (TASK_PART == 4) task_4();
    if constexpr (TASK_PART == 5) task_5();

    return 0;
}