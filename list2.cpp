/* list.c */

#include "list.h"
#include <stdlib.h>
#include <stdio.h>
link_t::link_t(void)
{

        next = NULL;
        entity = NULL;

}

link_t::link_t(void *newentity)
{
        next = NULL;
        entity = newentity;

}

link_t::~link_t(void)
{
   fprintf(stderr, "destroying link_t \n");
}

void link_t::set_next(link_t *new_next)
{

        next = new_next;

}

link_t * link_t::get_next()
{

        return(next);

}

void * link_t::get_entity()
{
        
        
        return(entity);

}


list_t::list_t()
{

        first = NULL;
        current = NULL;
        last = NULL;

}


void list_t::add(void *entity)
{

/* Create a new link passing it the entity pointer */

        link_t *link;
        link = new link_t(entity);
        
/* Now add the link to the list using generally the */
/* same approach as the C version                   */
        if(first == NULL)
        {
                first = link;
                current = link;
                last = link;
        }
        
        else
        {
                last->set_next(link);
                last = link;
                current = link;
                
        }               

}

void list_t::reset(void)
{
        if (first != NULL)
        {
                current = first;
        }
        else if (first == NULL)
        {
                current = NULL ;
        }
        
}

int list_t::not_end(void)
{
        
        if((current == NULL))
        {
                return(0);
        }
        else
        {
                return(1);
        }



}

void list_t::next_link(void)
{
   
   assert(current != NULL);
   current = current->get_next();
   

}

void * list_t::get_entity(void)
{
   assert(current != NULL);
   return(current->get_entity() );

}

list_t::~list_t()
{
        current = first;
        link_t *kill;
        fprintf(stderr, "destroying list_t \n");
   
        while(current != NULL)
        {
                kill = current;
                current = current->get_next();
                delete kill;
           
        }

}

void list_t::insert(void *entity)
{
        link_t *temp;
        link_t *traverse;
        
        if(first == NULL)
        {
                
                 add(entity);
        }
        else if(current == first)
        {
                
                 temp = new link_t(entity);
                 current = temp;
                 temp->set_next(first);
                 first = temp;
        }
        else
        {
                temp = new link_t(entity);
                temp->set_next(current);
                traverse = first;
                while(traverse->get_next() != current)
                {
                        traverse = traverse->get_next();
                }
                traverse->set_next(temp);
                current = temp;
        }
}                
      
void list_t::remove(void)
{
        link_t *traverse;
        
        if(first == NULL)
        {
        }
        else if(first->get_next() == NULL)
        {
                delete first;
                first = NULL;
                last = NULL;
                current = NULL;
        }
        else if(current == first)
        {
                first = current->get_next();
                delete current;
                current = first;
        }
        else
        {
                traverse = first;
                while(traverse->get_next() != current)
                {
                        traverse = traverse->get_next();
                }
                if(current == last)
                {
                        last = traverse;
                }
                traverse->set_next(current->get_next());
                delete current;
                current = traverse;
        }
}








