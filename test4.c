#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

unsigned char logo16[] =
{ 0b10000000, 0b00000001,
  0b01000000, 0b00000010,
  0b00100000, 0b00000100,
  0b00010000, 0b00001000,
  0b00001000, 0b00010000,
  0b00000100, 0b00100000,
  0b00000010, 0b01000000,
  0b00000001, 0b10000000,
  0b00000001, 0b10000000,
  0b00000010, 0b01000000,
  0b00000100, 0b00100000,
  0b00001000, 0b00010000,
  0b00010000, 0b00001000,
  0b00100000, 0b00000100,
  0b01000000, 0b00000010,
  0b10000000, 0b00000001 };
unsigned char logo16_ada[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };




// void translate() {

// }

// void bitmap_read();
// void bitmap_write();

// void rotate_and_scale() {

// }

// void calculate_vector() {

// }
typedef struct {
    double x;
    double y;
} vector;


vector vector_add(vector a, vector b) {
    vector res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;

    return res;
}

vector vector_sub(vector a, vector b) {
    vector res;
    res.x = a.x - b.x;
    res.y = a.y - b.y;

    return res;
}
#define PI 3.14159265
vector vector_rotate(int angle, vector v) {
printf("rot ini: x: %f  y: %f \r\n", v.x, v.y);
    double sa = sin(PI*angle / 180.0);
    double ca = cos(PI*angle / 180.0);
    vector res = {ca * v.x - sa * v.y,  sa * v.x + ca * v.y};
printf("rot res: x: %f  y: %f \r\n", res.x, res.y);
    return res;
}
void vectors_rotate(vector *vectors_bfr, vector *vectors_afr, int angle, int num_of_vectors) {
    for (int i = 0; i < num_of_vectors; i++) {
        vectors_afr[i] = vector_rotate(angle, vectors_bfr[i]);
    }
}


int initilize_vector_list(const unsigned char *bitmap, int h, int w, vector *vectors) {
    uint8_t byte = 0;
    uint16_t byteWidth = (w + 7) / 8;

    int cntr = 0;

    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++){

            if(i & 7) byte <<= 1;
            else byte = bitmap[i / 8 + j * byteWidth ];
            if (byte & 0x80) {
                // translate relative x,y (i, j) to absolute x,y
                vector *ptr = (vector *)malloc(sizeof(vector));
                ptr->x = i;
                ptr->y = j;
                vectors[cntr++] = *ptr;
            }
        }
    }
    return cntr;

}
void setup() {
    vector vectors[16*16];


    int num_of_vectors = initilize_vector_list(logo16, 16, 16, vectors);

    vector vectors_afr[num_of_vectors];

    vectors_rotate(vectors, vectors_afr, -10, num_of_vectors);

    printf("vectors bfr\n");
    for (int i = 0; i < num_of_vectors; i++) {
        printf("x: %f y:%f\n", vectors[i].x, vectors[i].y);
    }

    printf("vectors after\n");
    for (int i = 0; i < num_of_vectors; i++) {
        printf("x: %f y:%f\n", vectors_afr[i].x, vectors_afr[i].y);
    }
}


int main() {
    setup();
}
