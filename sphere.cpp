/*   Greg Francis/Gfranci
     Cpsc102 Section 1
     10/05/15
     MPA#1
*/  

#include "ray.h"
#include <math.h>

#define NUM_ATTRS (sizeof(sphere_parse) / sizeof(pparm_t))

static pparm_t sphere_parse[] = 
{
        {"center", 3, 8, "%lf", 0},
        {"radius", 1, 8, "%lf", 0}
};

sphere_t::sphere_t(FILE *in, model_t *model, int attrmax) : object_t(in,model)
{
        int mask;
        
        strcpy(obj_type, "sphere");
        
        sphere_parse[0].loc = &center;
        sphere_parse[1].loc = &radius;
        mask = parser(in,sphere_parse, NUM_ATTRS,attrmax);
        assert(mask ==3);
        
}

double sphere_t::hits(vec_t *base, vec_t *dir)
{
        vec_t hit, temp, unitnorm ,newbase;
        
        double a,b,c,discrim,distance;
        
        vec_diff(&center,base,&newbase);
        a = vec_dot(dir,dir);
        b = 2.0 * vec_dot(&newbase,dir);
	c = vec_dot(&newbase, &newbase) -(radius * radius);
	discrim = (b * b) - (4 * a * c);
	
	if(discrim > 0.0){
	
	        distance = ((b * (-1.0)) - sqrt(discrim))/(a*2);
	        
	}
	
	else{
	
	        return(-1);        
	}
	

	vec_scale(distance,dir,&temp);
	vec_sum(base, &temp , &hit);
	
	if(hit.z < 0.0)
	{
	        vec_copy(&hit,&last_hitpt);
	        vec_diff(&center,&hit,&unitnorm);
	        vec_unit(&unitnorm,&last_normal);
	        return(distance);
	}
	else
	{
	        return(-1);
	}        
}

void sphere_t::printer(FILE *out)
{
        
        object_t::printer(out);
        fprintf(out,"%-12s %5.1f%5.1f%5.1f\n","center",center.x, 
	                               center.y, center.z);
	fprintf(out,"%-12s %5.1lf\n","radius",radius);




}	        
        
        
        
        
        
        
        
        
        
             
