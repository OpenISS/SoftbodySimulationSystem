#include "ViewSpace.h"
#include "global.h"



void ViewSpace::Draw(void)    // Draw the view space
{
    int j;

	glPushMatrix();
    glBegin(GL_QUADS);  	  

		// floor
		j = 0;
		{
			glColor4f(1, 0.5, 0.1, 0.5);  
			glNormal3f(0, 1, 0);
			glVertex3f(spaceVertex[j]->x, spaceVertex[j]->y, spaceVertex[j]->z);
			glVertex3f(spaceVertex[j+1]->x, spaceVertex[j+1]->y, spaceVertex[j+1]->z);
			glVertex3f(spaceVertex[j+2]->x, spaceVertex[j+2]->y, spaceVertex[j+2]->z);
			glVertex3f(spaceVertex[j+3]->x, spaceVertex[j+3]->y, spaceVertex[j+3]->z);	
		}

		// ceiling
		j += 4;
		{
			glColor4f(1, 0.5, 0.1, 0.5);  
			glNormal3f(0, -1, 0);
			glVertex3f(spaceVertex[j]->x, spaceVertex[j]->y, spaceVertex[j]->z);
			glVertex3f(spaceVertex[j+1]->x, spaceVertex[j+1]->y, spaceVertex[j+1]->z);
			glVertex3f(spaceVertex[j+2]->x, spaceVertex[j+2]->y, spaceVertex[j+2]->z);
			glVertex3f(spaceVertex[j+3]->x, spaceVertex[j+3]->y, spaceVertex[j+3]->z);	
		}

		// back wall
		j = 1;
		{
			glColor4f(0, 0, 1, 0.5);  
			glNormal3f(0, 0, 1);
			glVertex3f(spaceVertex[j]->x, spaceVertex[j]->y, spaceVertex[j]->z);
			glVertex3f(spaceVertex[j+1]->x, spaceVertex[j+1]->y, spaceVertex[j+1]->z);         
			glVertex3f(spaceVertex[j+5]->x, spaceVertex[j+5]->y, spaceVertex[j+5]->z);
			glVertex3f(spaceVertex[j+4]->x, spaceVertex[j+4]->y, spaceVertex[j+4]->z);
		}

		// right wall
		j = 0;
		{
			glColor4f(0.5, 0.9, 0.1, 0.5); 
			glNormal3f(-1, 0, 0);
			glVertex3f(spaceVertex[j]->x, spaceVertex[j]->y, spaceVertex[j]->z);
			glVertex3f(spaceVertex[j+1]->x, spaceVertex[j+1]->y, spaceVertex[j+1]->z);
			glVertex3f(spaceVertex[j+5]->x, spaceVertex[j+5]->y, spaceVertex[j+5]->z);
			glVertex3f(spaceVertex[j+4]->x, spaceVertex[j+4]->y, spaceVertex[j+4]->z);	
		}   

		// left wall 
		j += 2;
		{
			glNormal3f(1, 0, 0);
			glColor4f(0.5, 0.9, 0.1, 0.5); 
			glVertex3f(spaceVertex[j]->x, spaceVertex[j]->y, spaceVertex[j]->z);
			glVertex3f(spaceVertex[j+1]->x, spaceVertex[j+1]->y, spaceVertex[j+1]->z);
			glVertex3f(spaceVertex[j+5]->x, spaceVertex[j+5]->y, spaceVertex[j+5]->z);
			glVertex3f(spaceVertex[j+4]->x, spaceVertex[j+4]->y, spaceVertex[j+4]->z);	
		}

	glEnd();	 

	glPopMatrix();

}
