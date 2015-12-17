/* tri.c */

#include "ray.h"


#define NUM_ATTRS (sizeof(tri_parse) / sizeof(pparm_t))

/***/
void tri_t::printer(
FILE *out)
{
   object_t::printer(out);
   fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf \n",
                 "normal", normal.x, normal.y,
                 normal.z);
   fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf \n",
                 "point1", v[0].x, v[0].y,
                 v[0].z);
   fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf \n",
                 "point2", v[1].x, v[1].y,
                 v[1].z);
   fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf \n",
                 "point3", v[2].x, v[2].y,
                 v[2].z);
}

/***/
/* Determine if a vector projected from location *base  */
/* in direction *dir hits the tri.. If so the return */
/* value is the distance from the base to the point of  */
/* contact.                                             */

double tri_t::hits(
vec_t    *base,      /* ray base              */
vec_t    *dir)       /* unit direction vector */
{
   double   ndotd;
   double   t, slope;
   double   ndotb, loc;
   int i;
   int count = 0;

   ndotq = vec_dot(&normal, &v[0]);
   ndotd = vec_dot(dir, &normal);

   //ndotd = 0 -> ray is parallel to the plane

   if (ndotd == 0)
       return(-1);

   ndotb = vec_dot(&normal, base);

   t = (ndotq - ndotb) / ndotd;

   if (t <= 0)
      return(-1);

   vec_scale(t, dir, &last_hitpt);
   vec_sum(&last_hitpt, base, &last_hitpt);

   if (last_hitpt.z > 0.0)
      return(-1);

        vec_t vt[3];

        // transpose point and last_hitpt so that last_hitpt is at the origin
        for(i = 0; i < 3; i++)
                vec_diff(&last_hitpt, &v[i], &vt[i]);

        // project tri and last_hitpt to 2d
        if(fabs(normal.x) > fabs(normal.y) && fabs(normal.x) > fabs(normal.z)) {
                for(i = 0; i < 3; i++) {
                        v_simp[i].x = vt[i].y;
                        v_simp[i].y= vt[i].z;
                }
        }
        if(fabs(normal.y) > fabs(normal.x) && fabs(normal.y) > fabs(normal.z)) {
                for(i = 0; i < 3; i++) {
                        v_simp[i].x = vt[i].x;
                        v_simp[i].y= vt[i].z;
                }
        }
        if(fabs(normal.z) > fabs(normal.x) && fabs(normal.z) > fabs(normal.y)) {
                for(i = 0; i < 3; i++) {
                        v_simp[i].x = vt[i].x;
                        v_simp[i].y= vt[i].y;
                }
        }

        /**************************************************************/
        /*  preform the even/odd test between the hitloc on the plane */
        /*  and polygon edges to determine if the hitloc is inside    */
        /*  or outside the polygon                                    */
        /**************************************************************/

        /* determine how many times a vector shot from the origin to the right
         * on the x axis intersects with the polygon edges */
        for(i = 0; i < 3; i++) {
                slope = (v_simp[i].y - v_simp[(i+1)%3].y) / (v_simp[i].x - v_simp[(i+1)%3].x);
                loc = (0 - v_simp[i].y)/slope + v_simp[i].x;
                if(loc >= 0 && ((v_simp[i].y >= 0 && v_simp[(i+1)%3].y <= 0) || (v_simp[(i+1)%3].y >= 0 && v_simp[i].y <= 0))) {
                        count++;
                }
        }

        if(count % 2 == 0)
                return(-1);

   //fprintf(stderr, "distance: %lf\n", t);
   return(t);
}

/* Parser parameter array for tri attributes */

static pparm_t tri_parse[] =
{
   {"vertex1",   3, 8, "%lf", 0},
   {"vertex2",   3, 8, "%lf", 0},
   {"vertex3",   3, 8, "%lf", 0},
};

/***/
/* Create a new tri object and initialize it */

tri_t::tri_t(FILE *in, model_t *model, int attrmax) : object_t(in, model)
{
   int  temp;
   vec_t tv1, tv2;

   strcpy(obj_type, "tri");

/* The parser is fairly generic but the address of where to */
/* put the data must be updated for each new object         */

   tri_parse[0].loc = &v[0];
   tri_parse[1].loc = &v[1];
   tri_parse[2].loc = &v[2];
   temp = parser(in, tri_parse, NUM_ATTRS, attrmax);
   assert(temp == 7);



   // finds the normal
   vec_diff(&v[0], &v[1], &tv1);
   vec_diff(&v[1], &v[2], &tv2);
   vec_cross(&tv1, &tv2, &normal);
   vec_unit(&normal, &normal);

   vec_copy(&normal, &last_normal);
   ndotq = vec_dot(&v[0], &normal);
}
