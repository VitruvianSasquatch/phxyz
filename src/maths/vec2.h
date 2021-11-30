#ifndef VEC2_H
#define VEC2_H


typedef struct {
	double x, y;
} Vec2_t;

#define VEC2_ZERO ((Vec2_t){0, 0})

/**
 * @brief Sums the two passed vectors together. 
 * 
 * @param v1 The first vector to be summed. 
 * @param v2 The second vector to be summed. 
 * @return Vec2_t A new vector equal to @p v1 + @p v2. 
 */
Vec2_t vec2_sum(Vec2_t v1, Vec2_t v2);


/**
 * @brief Finds the difference between the two passed vectors
 * 
 * @param v1 The vector to be subtracted from. 
 * @param v2 The vector to be subtracted. 
 * @return Vec2_t A new vector equal to @p v1 - @p v2. 
 */
Vec2_t vec2_diff(Vec2_t v1, Vec2_t v2);


/**
 * @brief Scales the vector @p v by @p a. 
 * 
 * @param v The vector to be scaled. 
 * @param a The scalar to be multiplied by, 
 * @return Vec2_t A new vector equal to @p a . @p v
 */
Vec2_t vec2_scale(Vec2_t v, double a);


/**
 * @brief Finds the length of the vector @p v. 
 * 
 * @param v The vector to find the length of. 
 * @return double The length of @p v. 
 */
double vec2_mag(Vec2_t v);


/**
 * @brief Normalises the vector @p v. 
 * 
 * @param v The vector to be normalised. 
 * @return Vec2_t A new vector equal to @p v / | @p v |. 
 */
Vec2_t vec2_norm(Vec2_t v);


/**
 * @brief Finds the dot product of the two passed vectors. 
 * 
 * @param v1 The first vector to be dotted. 
 * @param v2 The second vector to be dotted. 
 * @return double The dot product @p v1 . @p v2 . 
 */
double vec2_dot(Vec2_t v1, Vec2_t v2);


/**
 * @brief Finds the squared distance between two vectors. 
 * 
 * @param v1 The first vector on the line. 
 * @param v2 The second vector on the line. 
 * @return double The squared length of the line between @p v1 and @p v2. 
 */
double vec2_squareDist(Vec2_t v1, Vec2_t v2);


/**
 * @brief Prints the vector @p v in parentheses, no newline. 
 * 
 * @param v The vector to be printed
 */
void vec2_print(Vec2_t v);








#endif //VEC2_H