#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "anim.h"
#include <stdint.h>

#define PI 3.14159265
#define VECTORS_EQ(u, v) ((u.x == v.x) && (u.y == v.y))

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

vector vector_rotate(vector vec, int angle, vector center_of_rotation) {
    vector v = vector_sub(vec, center_of_rotation);
    float sa = sin(PI*angle / 180.0);
    float ca = cos(PI*angle / 180.0);
    vector res_rel = {ca * v.x - sa * v.y,  sa * v.x + ca * v.y};
    vector res = vector_add(res_rel, center_of_rotation);
    return res;
}

vector vector_scale(vector vec, float factor, vector center_of_scaling) {
    vector v = vector_sub(vec, center_of_scaling);
    vector res_rel = {v.x * factor, v.y * factor};
    vector res = vector_add(res_rel, center_of_scaling);
    return res;
}

vector vector_translate(vector vec, vector dir) {
    return vector_add(vec, dir);
}


vector vector_rotate_and_scale(vector vec, int angle, float factor, vector center_of_rotation, vector center_of_scaling) {
    if (VECTORS_EQ(center_of_scaling, center_of_rotation)) {
        vector v = vector_sub(vec, center_of_rotation);
        float sa = sin(PI * angle / 180.0);
        float ca = cos(PI * angle / 180.0);
        vector res_rel = {(ca * v.x - sa * v.y) * factor,  (sa * v.x + ca * v.y) * factor};
        vector res = vector_add(res_rel, center_of_rotation);
        return res;
    } else {
        return vector_scale(vector_rotate(vec, angle, center_of_rotation), factor, center_of_scaling);
    }
}

void vectors_translate(vector *vectors_buffer, int num_of_vectors, vector dir) {
    vector tmp[num_of_vectors];

    for (int i = 0; i < num_of_vectors; i++) {
        tmp[i] = vector_translate(vectors_buffer[i], dir);
    }
    memcpy(vectors_buffer, &tmp[0], sizeof(vector) * num_of_vectors);
}

void vectors_rotate(vector *vectors_buffer, int num_of_vectors, int angle, vector center_of_rotation) {
    vector tmp[num_of_vectors];

    for (int i = 0; i < num_of_vectors; i++) {
        tmp[i] = vector_rotate(vectors_buffer[i], angle, center_of_rotation);
    }
    memcpy(vectors_buffer, tmp, num_of_vectors * sizeof(vector));
}


void vectors_scale(vector *vectors_buffer, int num_of_vectors, float factor, vector center_of_scaling) {
    vector tmp[num_of_vectors];

    for (int i = 0; i < num_of_vectors; i++) {
        tmp[i] = vector_scale(vectors_buffer[i], factor, center_of_scaling);
    }
    memcpy(vectors_buffer, tmp, num_of_vectors * sizeof(vector));
}

void vectors_rotate_and_scale(vector *vectors_buffer, int num_of_vectors, int angle, float factor, vector center_of_rotation, vector center_of_scaling) {
    vector tmp[num_of_vectors];

    for (int i = 0; i < num_of_vectors; i++) {
        tmp[i] = vector_rotate_and_scale(vectors_buffer[i], angle, factor, center_of_rotation, center_of_scaling);
    }
    memcpy(vectors_buffer, tmp, num_of_vectors * sizeof(vector));
}


int initilize_vector_list(unsigned char *bitmap, int h, int w, vector *vectors, vector offset) {
    uint8_t byte = 0;
    uint16_t byteWidth = (w + 7) / 8;

    int cntr = 0;

    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++){
            if(i & 7) byte <<= 1;
            else byte = bitmap[i / 8 + j * byteWidth ];
            if (byte & 0x80) {
                // translate relative x,y (i, j) to absolute x,y
                vectors[cntr].x = i + offset.x;
                vectors[cntr].y = j + offset.y;
                cntr++;
            }
        }
    }
    return cntr;
}

