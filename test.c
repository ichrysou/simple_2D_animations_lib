#include <math.h>
#include <stdio.h>

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;



uint32_t counter;

static const unsigned char logo16[] =
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
    float x;
    float y;
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
    float sa = sin(PI*angle / 180.0);
    float ca = cos(PI*angle / 180.0);
    vector res = {ca * v.x - sa * v.y,  sa * v.x + ca * v.y};
    printf("rot res: x: %f  y: %f \n", res.x, res.y);
    return res;
}

void bmp_rotate(const unsigned char *bitmap, vector bitmap_position, vector rotation_center, int angle, int w, int h) {
    uint8_t byte = 0;
    printf("===========\n");
    // final bitmap position
    vector init_rel_bitmap_pos_v = vector_sub(bitmap_position, rotation_center);
    vector final_rel_bitmap_pos_v = vector_rotate(angle, init_rel_bitmap_pos_v);
    vector final_abs_bmp_pos_v = vector_add(rotation_center, final_rel_bitmap_pos_v);


    /* printf("position: x: %f y: %f\n", bitmap_position.x, bitmap_position.y); */
    /* printf("rotation: x: %f y: %f\n", rotation_center.x, rotation_center.y); */
    /* printf("final bmp pos for angle: %d\r\n", angle); */
    /* printf("x: %f y: %f\n", final_abs_bmp_pos_v.x, final_abs_bmp_pos_v.y); */
    /* printf("===========\n"); */
    // uint8_t final_bmp[w/8 * h];

    // for (int i = 0; i < w; i++){
    //     for (int j = 0; j < h; j++) {
    //         if(i & 7) byte <<= 1;
    //         else byte = bimtap[i / 8 + j * w ];
    //         if (byte & 0x80) {
    //             // translate relative x,y (i, j) to absolute x,y
    //             vector abs_v;
    //             vector rel_v = {i, j};
    //             abs_v = vector_add(bitmap_position, rel_v);
    //             // find the vector rotation_center -> pixel
    //             vector rot_v = vector_sub(abs_v, rotation_center);
    //             // multiply with rotation matrix
    //             vector final_v = vector_rotate(angle, rot_v);
    //             vector final_rel = vector_sub(final_v, final_abs_bmp_pos_v);
    //             final_bmp[final_rel.x / 8 + final_rel.y * w] = 1 << (7 - final_rel.x);
    //         }
    //     }
    // }
    // display.clearDisplay();
    // display.drawBitmap(final_abs_bmp_pos_v.x, final_abs_bmp_pos_v.y, final_bmp, w, h, WHITE);

}


void setup() {

    counter = 0;

}

int angles[] = {0, 45, 90 , 135, 180};
vector position = {10, 10};
vector rotations[] = {{10, 10},
                      {20, 20},
                      {0, 0}
};

#define GET_SIZE_OF_ARRAY(x, y) (x / 8 * y)

uint8_t empty_bmp[] = {
};

#define ROTATIONS_SIZE (sizeof(rotations) / sizeof(rotations[0]))
#define ANGLES_SIZE (sizeof(angles) / sizeof(angles[0]))
int main() {


    /* for (int i = 0; i < ROTATIONS_SIZE; i++) */
    /*     for(int j = 0; j < ANGLES_SIZE; j++) */

    bmp_rotate(empty_bmp, (vector){10, 10}, (vector){0, 0}, 90, 16, 16);

}
