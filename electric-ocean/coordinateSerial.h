#pragma once

#include <array>
#include <iostream>

constexpr int corner_x_coords[] = 
{ 36,  36,  35,  13,  12,  12,  11,  -3 ,
  -4,  -4,  -3,   1,   2,   2,   3,  11 ,
  10,   4,   3,   3,   4,  10,  11,  11 ,
  12,  12,  11,   3,   2,   2,   3,  25 ,
  26,  26,  27,  35,  34,  28,  27,  27 ,
  28,  34,  35,  35,  36,  36,  35,  27 ,
  26,  26,  27,  41,  42,  42,  41,  37};

constexpr int corner_y_coords[] = 
{ 11,  33,  34,  34,  35,  39,  40,  40 ,
  39,  25,  24,  24,  25,  33,  34,  34 ,
  33,  33,  32,  26,  25,  25,  26,  32 ,
  33,  25,  24,  24,  23,   1,   0,   0 ,
   1,   9,  10,  10,   9,   9,   8,   2 ,
   1,   1,   2,   8,   9,   1,   0,   0 ,
  -1,  -5,  -6,  -6,  -5,   9,  10,  10};

//Indexes of each corner LED in the arrangement.
constexpr int cI[] = 
 { 0,  11,  12,  23,  24,  26,  27,  34,
  35,  42,  43,  45,  46,  50,  51,  55,
  56,  59,  60,  63,  64,  67,  68,  71,
  72,  76,  77,  81,  82,  93,  94, 105,
 106, 110, 111, 115, 116, 119, 120, 123,
 124, 127, 128, 131, 132, 136, 137, 141,
 142, 144, 145, 152, 153, 160, 161, 163};




/*
Compute the sign function of a value.
*/
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
};

/*
Helper function to get the size of completed LED coordinate array using the last value of cI,
which by definition is one less than the total LED count. */
constexpr std::size_t compute_size(const int indexes[], std::size_t N) {
    return indexes[N-1]; // The size of cI determines the size of the new array.
}

void fillCoordinateArray(int* coords, size_t s) {
    for (int i=0; i<s; i+=2 ){
      int c1 = coords[i], c2 = coords[i+1];
      int sign_dd = sgn( c2 - c1);

      for (int j = cI[i]; j <= cI[i+1]; j++, c1+=sign_dd) { 
        coords[j] = c1;
      }
    }
};

template<std::size_t N_LED, std::size_t N_CORD >
constexpr auto calcCoordinates(const int corner_coords[], const int cI[]) {
    std::array<int, N_LED> coords = {};

    for (std::size_t i=0; i< N_CORD; i+=2 ){
      int c1 = corner_coords[i], c2 = corner_coords[i+1];
      int sign_dd = sgn( c2 - c1);

      if(sign_dd != 0){
        for (std::size_t j = cI[i]; j <= cI[i+1]; j++, c1+=sign_dd) { 
          coords[j] = c1;
        }
      }else{
        for (std::size_t j = cI[i]; j <= cI[i+1]; j++){
          coords[j] = c1;
        }
      }
    }
    return coords;
}

#define NUM_LEDS_PER_STRIP 164
#define NUM_LEDS 164
#define NUM_COORDS (sizeof(cI)/sizeof((cI)[0]))

// constexpr int ledx[NUM_LEDS] = []{
//     std::array<int, NUM_LEDS> temp = calcCoordinates<NUM_LEDS, NUM_COORDS>(corner_x_coords, cI);
//     int result[NUM_LEDS] = {};
//     for (std::size_t i = 0; i < NUM_LEDS; ++i) {
//         result[i] = temp[i];
//     }
//     return result;
// }();

// constexpr int ledy[NUM_LEDS] = []{
//     std::array<int, NUM_LEDS> temp = calcCoordinates<NUM_LEDS, NUM_COORDS>(corner_y_coords, cI);
//     int result[NUM_LEDS] = {};
//     for (std::size_t i = 0; i < NUM_LEDS; ++i) {
//         result[i] = temp[i];
//     }
//     return result;
// }();

void fillCoordinates(){
  std::size_t s = cI[NUM_COORDS -1];
  fillCoordinateArray(corner_x_coords, s);
  fillCoordinateArray(corner_y_coords, s);
}




