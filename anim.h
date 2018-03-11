#ifndef _ANIM_H_
#define _ANIM_H_

typedef struct {
    float x;
    float y;
} vector;

// basic math
vector vector_add(vector a, vector b);
vector vector_sub(vector a, vector b);
// translations
vector vector_rotate(vector vec, int angle, vector center_of_rotation);
vector vector_scale(vector vec, float factor, vector center_of_scaling);
vector vector_rotate_and_scale(vector vec, int angle, float factor, vector center_of_rotation, vector center_of_scaling);
vector vector_translate(vector vec, vector dir);
// batch translations
void vectors_rotate(vector *vectors_buffer, int num_of_vectors, int angle, vector center_of_rotation);
void vectors_scale(vector *vectors_buffer, int num_of_vectors, float factor, vector center_of_scaling);
void vectors_rotate_and_scale(vector *vectors_buffer, int num_of_vectors, int angle, float factor, vector center_of_rotation, vector center_of_scaling);
void vectors_translate(vector *vectors_buffer, int num_of_vectors, vector dir);
// create vectors from bitmap
int initilize_vector_list(const unsigned char *bitmap, int h, int w, vector *vectors, vector offset);

#endif
