/*   Greg Francis/Gfranci
     Cpsc102 Section 1
     10/05/15
     MPA#1
*/  
#include "vector.h"

/* Compute the sum of two vectors */

void vec_sum(vec_t *v1, vec_t *v2, vec_t *v3){  

        v3->x = v1->x + v2->x;
        v3->y = v1->y + v2->y;
        v3->z = v1->z + v2->z;
}   

/* Compute the difference of two vectors */

void vec_diff(vec_t *v1, vec_t *v2, vec_t *v3){

        v3->x = v2->x - v1->x;
        v3->y = v2->y - v1->y;
        v3->z = v2->z - v1->z;
}

/* Compute the componentwise product of two vectors */

void vec_mult(vec_t *v1, vec_t *v2, vec_t *v3){   
   
        v3->x = v2->x * v1->x;
        v3->y = v2->y * v1->y;
        v3->z = v2->z * v1->z;
}

void vec_reflect(vec_t *unitin, vec_t *unitnorm, vec_t *unitout){
        //Does unitin need to be negative?
        vec_scale(-1, unitin, unitin);
        
        double UdotN = vec_dot(unitin, unitnorm);
        
        unitout->x = 2 * unitnorm->x * UdotN - unitin->x;
        unitout->y = 2 * unitnorm->y * UdotN - unitin->y;
        unitout->z = 2 * unitnorm->z * UdotN - unitin->z;
        



}

/* Return the (dot) inner product of two input vectors     */

double vec_dot(vec_t *v1, vec_t *v2){   

        return (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
}

/* Return length of a 3d vector */

double vec_len(vec_t *v1){  

        return sqrt(vec_dot(v1, v1));
}

/* Scale a 3d vector by multiplying each element by scale factor */

void vec_scale( double fact, vec_t *v1, vec_t *v2){

        v2->x = v1->x * fact;
        v2->y = v1->y * fact;
        v2->z = v1->z * fact;
}

/* Construct a unit vector v2 in direction of input vector v1 */

void vec_unit(vec_t *v1, vec_t *v2){
    
        vec_scale((1.0 / vec_len(v1)), v1, v2);
}

/* Copy vector v1 to v2 another */

void vec_copy(vec_t *v1, vec_t *v2){   

        v2->x = v1->x;
        v2->y = v1->y;
        v2->z = v1->z;
}

void vec_cross(
vec_t *v1,         /* Left input vector  */
vec_t *v2,         /* Right input vector */
vec_t *v3)         /* Output vector      */
{
        vec_t t;

        t.x = v1->y * v2->z - v1->z * v2->y;
        t.y = v1->z * v2->x - v1->x * v2->z;
        t.z = v1->x * v2->y - v1->y * v2->x;

        vec_copy(&t, v3);
}

void vec_project(vec_t *n, vec_t *v, vec_t *p){

        double ndotv;
        vec_t temp;
        ndotv = vec_dot(n,v);
        vec_scale(ndotv,n, &temp);
        vec_diff(&temp,v,p);
        
}

void vec_xform(mtx_t *m,vec_t *v1, vec_t *v2){

        vec_t temp;
        temp.x = vec_dot(&m->row[0],v1);
        temp.y = vec_dot(&m->row[1],v1);
        temp.z = vec_dot(&m->row[2],v1);
        vec_copy(&temp,v2);
        
}


/* Read in values of vector from file */
/* Return the # of items read	*/

int vec_read(FILE *in, vec_t *v1){
    
        return fscanf(in, "%lf %lf %lf \n", &v1->x, &v1->y, &v1->z);
}


/* Print values of vector to file */

void vec_print(FILE *out, char *label, vec_t *v1){    
    
        fprintf(out, "%s %8.3lf %8.3lf %8.3lf \n", label, v1->x, v1->y, v1->z);
}
