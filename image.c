/*   Greg Francis/Gfranci
     Cpsc102 Section 1
     10/05/15
     MPA#1
*/  

#include "ray.h"

//=============================================================================
// ******* ray_trace( ) *******
// 
// 
//=============================================================================


void ray_trace (
        model_t *model,
        vec_t *base,                // view point
        vec_t *dir,                 // unit direction vector
        drgb_t *pix,                // pixel return location
        double total_dist,          // distance ray has travelled so far
        object_t *last_hit)         // most recently hit object
{
        double mindist;
        drgb_t thispix = {0.0, 0.0, 0.0};
        object_t *closest;
        //double specref = 0.0;
        //vec_t *ref_dir = NULL;
        //vec_t *last_hitpoint;
        //closest->getlast_hitpt(&last_hitpoint);
        
        
        /* Get the object (plane or sphere).        */
        
        
        closest = find_closest_object(model,base,dir,last_hit,&mindist);
        
        if(total_dist > MAX_DIST){
            return;
        } 
         
              
        if(closest == NULL)
        {
               return;
        }
        

        pix->r += thispix.r;
        pix->g += thispix.g;
        pix->b += thispix.b;
        
        total_dist += mindist;
        closest->getambient(&thispix);   
        add_illumination(model, base, closest, &thispix);   
        
        pix_scale((1/total_dist),&thispix, &thispix);

    /*    
        closest->getspecular(&specref);
        if(specref != 0){
            drgb_t specint = {0.0,0.0,0.0};
            vec_reflect(base, dir, ref_dir); 
            ray_trace(model, &last_hitpoint, ref_dir, &specint, total_dist, closest);
            pix_scale(specref,&specint, &specint);
            pix_sum(&specint, &thispix, 0);
        }
        */
        pix_sum(&thispix, pix, pix);
        
        return;
        
}


//=============================================================================
// ******* make_pixel( ) *******
// 
// 
//=============================================================================
void make_pixel(model_t  *model, int  x, int  y) {
   
        vec_t raydir;
        vec_t viewpoint;
        drgb_t d_pix = {0.0, 0.0, 0.0};
        camera_t *cam = model->cam;
        cam->getviewpt(&viewpoint);
        cam->getdir(x, y, &raydir);
        #ifdef DBG_PIX
           fprintf(stderr, "\nPIX %4d %4d - ", x,y);
        #endif
        /*  The ray_trace function determines the pixel color in */
        /*  d_rgb units.   The last two parameters are used ONLY */
        /*  in the case of specular (bouncing) rays              */
        ray_trace(model, &viewpoint, &raydir, &d_pix, 0.0, NULL);
        cam->store_pixel(x, y, &d_pix);

        return;
}


//=============================================================================
// ******* make_row( ) *******
// 
// 
//=============================================================================
void make_row(model_t  *model, int  y) 
{
        int x;
        int temp;
        camera_t *cam = model->cam;
        
        /*  for each pixel in the row, invoke make_pixel() */
        /*  to paint the pixel.                            */
	temp = cam->getxdim(); 
        for(x = 0; x < temp; x++){
     
                make_pixel(model, x, y);
        }
}


//=============================================================================
// ******* image_create( ) *******
// 
// 
//=============================================================================
void image_create(model_t  *model, FILE  *out){ 

        int y;
        int temp;
        camera_t *cam = model->cam;
        
        /*  fire rays through each pixel in the window; */
        /*  for each row, invoke make_row() to paint    */
        /*  the row of pixels.                          */
        temp = cam->getydim();
        for(y = 0; y < temp; y++){
   
                make_row(model, y);
        }
        /*  write the image                           */
        cam->camera_write_image(out);
}

