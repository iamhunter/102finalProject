/*   Greg Francis/Gfranci
     Cpsc102 Section 1
     10/05/15
     MPA#1
*/  
#include "ray.h"

#define NUM_ATTRS (sizeof(plane_parse) / sizeof(pparm_t))



double plane_t::hits(vec_t *base, vec_t *dir)
{
        double ndotd,t,ndotb;
        vec_t temp;
        ndotd = vec_dot(&normal, dir);
        
        if(ndotd == 0)
            return(-1.0);
        
        ndotq = vec_dot(&normal,&point);
        ndotb = vec_dot(&normal,base);
        
        t = (ndotq - ndotb) / ndotd;
        
        if(t <= 0)
            return(-1);
        
        
        vec_scale(t,dir,&temp);
        vec_sum(&temp,base,&last_hitpt);
        
        if((last_hitpt.z > 0.01) && (strcmp(obj_type,"projector")))
            return(-1);
               
            
               
        return(t);
}

void plane_t::printer(FILE *out)
{
        
        object_t::printer(out);
        fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf\n", "normal", normal.x,
                                                    normal.y, normal.z);
        fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf\n", "point", point.x, 
                                                      point.y, point.z); 
}               
              
        
static pparm_t plane_parse[] =
{
        {"point", 3, 8, "%lf",0},
        {"normal", 3, 8, "%lf",0}
};

plane_t::plane_t(FILE *in, model_t *model, int attrmax) : object_t(in,model)
{
        int mask;
        cookie = OBJ_COOKIE;
        strcpy(obj_type,"plane");
        
        plane_parse[0].loc = &point;
        plane_parse[1].loc = &normal;
        mask = parser(in,plane_parse,NUM_ATTRS, attrmax);
        assert(mask == 3);
        
        
        vec_copy(&normal, &last_normal);
        vec_unit(&normal,&normal);
        ndotq = vec_dot(&point,&normal);
}       
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
                
