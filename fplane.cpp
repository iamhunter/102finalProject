#include "ray.h"

#define NUM_ATTRS (sizeof(fplane_parse) / sizeof(pparm_t))
 

 
 
 
void fplane_t::printer(FILE *out)
{
       vec_t projxdir;
       vec_unit(&normal, &normal); 
       vec_project(&normal, &xdir, &projxdir);

       plane_t::printer(out); 
 
       fprintf(out, "%-12s %5.1lf %5.1lf\n", "dimensions",
                                  dims[0], dims[1]);
 
       fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf\n", "xdir",
                                   xdir.x, xdir.y, xdir.z);
 
       fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf\n", "projected",
                           projxdir.x, projxdir.y, projxdir.z);
 
       fprintf(out, "%-12s", "rotation matrix\n");
       
       fprintf(out, "%18.1lf %5.3f %5.3f\n",
                       rot.row[0].x, rot.row[0].y, rot.row[0].z);
 
       fprintf(out, "%18.1f %5.3f %5.3f\n",
                       rot.row[1].x, rot.row[1].y, rot.row[1].z);
 
       fprintf(out, "%18.1f %5.3f %5.3f\n",
                       rot.row[2].x, rot.row[2].y, rot.row[2].z);
 
}
 

 
double fplane_t::hits(vec_t *base, vec_t *dir)       
{
        vec_t newloc;
 
        double t;
 
        t = plane_t::hits(base, dir);
 
        if(t == -1)
        {
                return(-1);
        }        
 
        vec_diff(&point, &last_hitpt, &newloc);
 
        vec_xform(&rot, &newloc, &newloc);
 
        if(0 <= newloc.x && newloc.x <= dims[0])
        {
 
                if(0 <= newloc.y && newloc.y <= dims[1])
                {
 
                        vec_copy(&newloc, &rothit);
 
                        return(t);
 
                }
 
        }
 
        return(-1);
 
}

static pparm_t fplane_parse[] =
 
{
 
   {"xdir",    3, 8, "%lf", 0},
 
   {"dimensions", 2, 8, "%lf", 0}
 
};
 

 
fplane_t::fplane_t(FILE *in, model_t *model,
int attrmax) : plane_t(in, model, 2)
 
{
 
        int mask;
        vec_t projxdir;
        cookie = OBJ_COOKIE;
        strcpy(obj_type, "fplane");
        vec_t tempunit;
        
 
        fplane_parse[0].loc = &xdir; 
        fplane_parse[1].loc = &dims;
 
        mask = parser(in, fplane_parse, NUM_ATTRS, attrmax); 
        assert(mask == 3);
 
        vec_unit(&normal, &tempunit); 
        vec_project(&tempunit, &xdir, &projxdir);
 
        if(((projxdir.x == projxdir.y) == projxdir.z))
        {
                assert(projxdir.x != 0.0);
        }
 
        vec_unit(&projxdir, &projxdir);
        vec_copy (&projxdir, &rot.row[0]); 
        vec_copy (&normal, &rot.row[2]); 
        vec_cross(&rot.row[2], &rot.row[0], &rot.row[1]);
 
}  
