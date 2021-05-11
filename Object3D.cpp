#include "Object3D.h"

#include <assert.h>

//##ModelId=45F4D79700EE
Object3D::Object3D()
{    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/*    pa = new Particle(new Vector(0,0,0), MASS);
    pb = new Particle(new Vector(0,0,0), MASS);
    pc = new Particle(new Vector(0,0,0), MASS);
*/
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


    // It is *IMPORTANT* to realize that most of the time
    // the number of particles and springs are not the same
    // in 3D (unlike 2D) so these have to be updated to the
    // actual number of particles and springs when the geometry
    // is initially constructed or altered
    numParticles = NUMPOINTS;
    numSprings = NUMSPRINGS;

    iterations = 1;
    SetObject();

    dim = DIM3D;
}



//##ModelId=45F4D79700FB
Object3D::~Object3D()
{
/*    delete pa;
    delete pb;
    delete pc;
*/
}

void Object3D::createVertexArray(){
    total = 0;
    // blue outer points
    total += outer_points.size();   // for drawing outer points
    total += inner_points.size();   // for drawing inner points
    
    // TODO: can add (outer_spring), (inner_spring), (radium_spring), (shear_left), (shear_right) these springs here.
    // but also need to change (drawing type enum, update data function, and drawing function to correctly draw these)
    
    total += inner_faces.size() * 3;// for drawing inner faces
    total += outer_faces.size() * 3;// for drawing outer faces
    
    // TODO: can add inner face normals here
    
    total += outer_faces.size() * 12;   // for drawing outer faces normals
    total += 2;                     // for drawing integrator line
    
    // dynamically allocate the vertexArrayData size by counting how many vertercies in total
    vertexArrayData = new glm::vec3[total];
    
    // generate VAO and VBO, upload the data, reserve memory in buffer
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(*vertexArrayData) * total, (void*)vertexArrayData, GL_DYNAMIC_DRAW);
    
    // set attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
//        cout<<"3D: " << VAO << " " << VBO << endl;
}

void Object3D::updateVertexArray(){
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    vector<glm::vec3> tempVertices;
    
    // push in data for outer points
    for(int i = 0; i < outer_points.size(); ++i){
        tempVertices.push_back(glm::vec3(outer_points[i]->r->x, outer_points[i]->r->y, outer_points[i]->r->z));
    }
    
    // push in data for inner points
    for(int i = 0; i < inner_points.size(); ++i){
        tempVertices.push_back(glm::vec3(inner_points[i]->r->x, inner_points[i]->r->y, inner_points[i]->r->z));
    }
    
    // push in data for inner faces
    for(int i = 0; i < inner_faces.size(); ++i){
        tempVertices.push_back(glm::vec3(inner_faces[i]->fp1->r->x, inner_faces[i]->fp1->r->y, inner_faces[i]->fp1->r->z));
        tempVertices.push_back(glm::vec3(inner_faces[i]->fp2->r->x, inner_faces[i]->fp2->r->y, inner_faces[i]->fp2->r->z));
        tempVertices.push_back(glm::vec3(inner_faces[i]->fp3->r->x, inner_faces[i]->fp3->r->y, inner_faces[i]->fp3->r->z));
    }
    
    // push in data for outer faces
    for(int i = 0; i < outer_faces.size(); ++i){
        tempVertices.push_back(glm::vec3(outer_faces[i]->fp1->r->x, outer_faces[i]->fp1->r->y, outer_faces[i]->fp1->r->z));
        tempVertices.push_back(glm::vec3(outer_faces[i]->fp2->r->x, outer_faces[i]->fp2->r->y, outer_faces[i]->fp2->r->z));
        tempVertices.push_back(glm::vec3(outer_faces[i]->fp3->r->x, outer_faces[i]->fp3->r->y, outer_faces[i]->fp3->r->z));
    }
    
    // push in data for outer face normals
    for(int i = 0; i < outer_faces.size(); ++i){
        tempVertices.push_back(glm::vec3(outer_faces[i]->fp1->r->x, outer_faces[i]->fp1->r->y, outer_faces[i]->fp1->r->z));
        tempVertices.push_back(glm::vec3(outer_faces[i]->fp2->r->x, outer_faces[i]->fp2->r->y, outer_faces[i]->fp2->r->z));
        
        tempVertices.push_back(glm::vec3(outer_faces[i]->fp2->r->x, outer_faces[i]->fp2->r->y, outer_faces[i]->fp2->r->z));
        tempVertices.push_back(glm::vec3(outer_faces[i]->fp3->r->x, outer_faces[i]->fp3->r->y, outer_faces[i]->fp3->r->z));
        
        tempVertices.push_back(glm::vec3(outer_faces[i]->fp3->r->x, outer_faces[i]->fp3->r->y, outer_faces[i]->fp3->r->z));
        tempVertices.push_back(glm::vec3(outer_faces[i]->fp1->r->x, outer_faces[i]->fp1->r->y, outer_faces[i]->fp1->r->z));
        
        tempVertices.push_back(glm::vec3(inner_faces[i]->fp1->r->x, inner_faces[i]->fp1->r->y, inner_faces[i]->fp1->r->z));
        tempVertices.push_back(glm::vec3(inner_faces[i]->fp2->r->x, inner_faces[i]->fp2->r->y, inner_faces[i]->fp2->r->z));
        
        tempVertices.push_back(glm::vec3(inner_faces[i]->fp2->r->x, inner_faces[i]->fp2->r->y, inner_faces[i]->fp2->r->z));
        tempVertices.push_back(glm::vec3(inner_faces[i]->fp3->r->x, inner_faces[i]->fp3->r->y, inner_faces[i]->fp3->r->z));
        
        tempVertices.push_back(glm::vec3(inner_faces[i]->fp3->r->x, inner_faces[i]->fp3->r->y, inner_faces[i]->fp3->r->z));
        tempVertices.push_back(glm::vec3(inner_faces[i]->fp1->r->x, inner_faces[i]->fp1->r->y, inner_faces[i]->fp1->r->z));
    }
    
    // push in integrator line data
    if(integrator != nullptr){
        tempVertices.push_back(glm::vec3(integrator->mDragX, integrator->mDragY, 0.0f));
    tempVertices.push_back(glm::vec3(outer_points[closest_i]->r->x,outer_points[closest_i]->r->y,outer_points[closest_i]->r->z));
    }
    
    // copy the vector to vertexArrayData
    for(unsigned int i = 0; i < total; ++i)
    {
        // this if statement is to make sure the vertexArrayData's size is unchanged and every vertex is initialized
        // (in case integrator is null)
        if(i < tempVertices.size())
            vertexArrayData[i] = tempVertices.at(i);
        else
            vertexArrayData[i] = glm::vec3(0);
    }
    
    // update the buffer data
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(*vertexArrayData) * total, (void*)vertexArrayData);
    
}

int Object3D::getOffset(drawingInstances instance){
    int offset = 0;
    
    switch(instance){
        case outer_inner_points:
            offset = 0;
            break;
        case outer_face:
            offset = getCount(outer_inner_points);
            break;
        case inner_face:
            offset = getOffset(outer_face) + getCount(outer_face);
            break;
        case outer_face_normal:
            offset = getOffset(inner_face) + getCount(inner_face);
            break;
        case integrator_line:
            offset = getOffset(outer_face_normal) + getCount(outer_face_normal);
            break;
        default:
            offset = 0;
            break;
    }
    return offset;
}

int Object3D::getCount(drawingInstances instance){
    int vertexCount = 0;
    
    switch(instance){
        case outer_inner_points:
            vertexCount = (int) outer_points.size() + (int)inner_points.size();
            break;
        case outer_face:
            vertexCount = (int) outer_faces.size() * 3;
            break;
        case inner_face:
            vertexCount = (int) inner_faces.size() * 3;
            break;
        case outer_face_normal:
            vertexCount = (int) outer_faces.size() * 12;
            break;
        case integrator_line:
            vertexCount = 2;
            break;
        default:
            vertexCount = 0;
            break;
            
    }
    return vertexCount;
}

//##ModelId=45F4D797010B
void Object3D::Add_Structural_Spring(int index, int h, int t)
{
    // making sure nobody actuall calls it
/*    assert(false);

      inner_springs.push_back( new Spring(inner_points[h],inner_points[t]));
    outer_springs.push_back( new Spring(outer_points[h],outer_points[t]));
 
*/
    
/*        inner_springs.push_back( new Spring());
    outer_springs.push_back( new Spring());
*/
/*    inner_springs[index]->setRestLen();                    //set the inner spring's length
    outer_springs[index]->setRestLen();                    //set the outer spring's length
*/
}


////////////////////////////////////////////////////



//##ModelId=45F4D797010F
void Object3D::Add_Radium_Spring(int index)
{
    radium_springs.push_back( new Spring(inner_springs[index]->sp1,outer_springs[index]->sp1, 5*KS, 2*KD));
    radium_springs[index]->setRestLen();                        //set the radium spring's length
}


//##ModelId=45F4D797011B
void Object3D::Add_Shear_Spring(int index )
{
    shear_springs_left.push_back(new Spring(inner_springs[index]->sp1,outer_springs[index]->sp2, 5*KS, 2*KD));
    shear_springs_right.push_back(new Spring(inner_springs[index]->sp2, outer_springs[index]->sp1,5*KS, 2*KD));

    shear_springs_left[index]->setRestLen();                    //set the shear left spring's length
    shear_springs_right[index]->setRestLen();                //set the shear right spring's length
}





//==============================================================================
//##ModelId=45F4D79700FF
void Object3D::Iteration()
{
    // Spring triplets counter for older springs particle replacements
//    static int j = 0;

    for (int it=0; it<iterations;it++)
    {
        int initialFacesCount = (int)outer_faces.size();
        int i;

        for(i=0;i<initialFacesCount;i++)
        {

            // Here we subdivide the initial face into four faces by
            pa = new Particle();
            pb = new Particle();
            pc = new Particle();


            // first getting the midpoints on each edge of the original face

            pa->r->x=(outer_faces[i]->fp1->r->x + outer_faces[i]->fp2->r->x)/2;
            pa->r->y=(outer_faces[i]->fp1->r->y + outer_faces[i]->fp2->r->y)/2;
            pa->r->z=(outer_faces[i]->fp1->r->z + outer_faces[i]->fp2->r->z)/2;

            pb->r->x=(outer_faces[i]->fp2->r->x + outer_faces[i]->fp3->r->x)/2;
            pb->r->y=(outer_faces[i]->fp2->r->y + outer_faces[i]->fp3->r->y)/2;
            pb->r->z=(outer_faces[i]->fp2->r->z + outer_faces[i]->fp3->r->z)/2;

            pc->r->x=(outer_faces[i]->fp1->r->x + outer_faces[i]->fp3->r->x)/2;
            pc->r->y=(outer_faces[i]->fp1->r->y + outer_faces[i]->fp3->r->y)/2;
            pc->r->z=(outer_faces[i]->fp1->r->z + outer_faces[i]->fp3->r->z)/2;
            //

    /*         cout<<"before normalization: "<<endl;
              cout<<"pa->x="<<pa->r->x<<"; pa->y="<<pa->r->y<<"; pa->z="<<pa->r->z<<endl;
           cout<<"pb->x="<<pb->r->x<<"; pb->y="<<pb->r->y<<"; pb->z="<<pb->r->z<<endl;
           cout<<"pc->x="<<pc->r->x<<"; pc->y="<<pc->r->y<<"; pc->z="<<pc->r->z<<endl;
           //

*/
         

          

            // Each new point's coordinates are normalized
            pa->r->Normalize();
            pb->r->Normalize();
            pc->r->Normalize();

    /*         cout<<"after normalization: "<<endl;

           cout<<"pa->x="<<pa->r->x<<"; pa->y="<<pa->r->y<<"; pa->z="<<pa->r->z<<endl;
           cout<<"pb->x="<<pb->r->x<<"; pb->y="<<pb->r->y<<"; pb->z="<<pb->r->z<<endl;
           cout<<"pc->x="<<pc->r->x<<"; pc->y="<<pc->r->y<<"; pc->z="<<pc->r->z<<endl;

*/

            bool a = false, b = false, c = false;
            for(int o = 0; o < outer_points.size(); o++)
            {
                if
                (
                       outer_points[o]->r->x == pa->r->x
                    && outer_points[o]->r->y == pa->r->y
                    && outer_points[o]->r->z == pa->r->z
                )
                {
                    delete pa;
                    pa = outer_points[o];
                    a = true;
                }

                if
                (
                       outer_points[o]->r->x == pb->r->x
                    && outer_points[o]->r->y == pb->r->y
                    && outer_points[o]->r->z == pb->r->z
                )
                {
                    delete pb;
                    pb = outer_points[o];
                    b = true;
                }

                if
                (
                       outer_points[o]->r->x == pc->r->x
                    && outer_points[o]->r->y == pc->r->y
                    && outer_points[o]->r->z == pc->r->z
                )
                {
                    delete pc;
                    pc = outer_points[o];
                    c = true;
                }
            }

            // The new points are added to the general collection of points
            if(!a) outer_points.push_back(pa);
            if(!b) outer_points.push_back(pb);
            if(!c) outer_points.push_back(pc);


            // Create three new faces; these represent the three outer triangles
            outer_faces.push_back(new Face(outer_faces[i]->fp1, pa, pc, outer_springs)); // Top
            outer_faces.push_back(new Face(pa, outer_faces[i]->fp2, pb, outer_springs)); // Bottom-left
//            outer_faces.push_back(new Face(pb, outer_faces[i]->fp3, pc, outer_springs)); // Bottom-right
            outer_faces.push_back(new Face(pc, pb, outer_faces[i]->fp3, outer_springs)); // Bottom-right


            // Replace the original face's points with its new one in the middle

            outer_faces[i]->fp1 = pa;
            outer_faces[i]->fp2 = pb;
            outer_faces[i]->fp3 = pc;


            outer_faces[i]->fs1->sp1 = pa;
            outer_faces[i]->fs1->sp2 = pb;

            outer_faces[i]->fs2->sp1 = pb;
            outer_faces[i]->fs2->sp2 = pc;

            outer_faces[i]->fs3->sp1 = pc;
            outer_faces[i]->fs3->sp2 = pa;
        }

        initialFacesCount = (int)inner_faces.size();

     for(i=0;i<initialFacesCount;i++)
        {

            // Here we subdivide the initial face into four faces by
            pa = new Particle();
            pb = new Particle();
            pc = new Particle();


            // first getting the midpoints on each edge of the original face

            pa->r->x=(inner_faces[i]->fp1->r->x + inner_faces[i]->fp2->r->x)/2;
            pa->r->y=(inner_faces[i]->fp1->r->y + inner_faces[i]->fp2->r->y)/2;
            pa->r->z=(inner_faces[i]->fp1->r->z + inner_faces[i]->fp2->r->z)/2;

            pb->r->x=(inner_faces[i]->fp2->r->x + inner_faces[i]->fp3->r->x)/2;
            pb->r->y=(inner_faces[i]->fp2->r->y + inner_faces[i]->fp3->r->y)/2;
            pb->r->z=(inner_faces[i]->fp2->r->z + inner_faces[i]->fp3->r->z)/2;

            pc->r->x=(inner_faces[i]->fp1->r->x + inner_faces[i]->fp3->r->x)/2;
            pc->r->y=(inner_faces[i]->fp1->r->y + inner_faces[i]->fp3->r->y)/2;
            pc->r->z=(inner_faces[i]->fp1->r->z + inner_faces[i]->fp3->r->z)/2;
            //

    /*         cout<<"inner iteration before normalization: "<<endl;
              cout<<"pa->x="<<pa->r->x<<"; pa->y="<<pa->r->y<<"; pa->z="<<pa->r->z<<endl;
           cout<<"pb->x="<<pb->r->x<<"; pb->y="<<pb->r->y<<"; pb->z="<<pb->r->z<<endl;
           cout<<"pc->x="<<pc->r->x<<"; pc->y="<<pc->r->y<<"; pc->z="<<pc->r->z<<endl;
    */       //


         

          

            // Each new point's coordinates are normalized
            pa->r->Normalize();
            pb->r->Normalize();
            pc->r->Normalize();

/*             cout<<"inner iteration after normalization: "<<endl;

           cout<<"pa->x="<<pa->r->x<<"; pa->y="<<pa->r->y<<"; pa->z="<<pa->r->z<<endl;
           cout<<"pb->x="<<pb->r->x<<"; pb->y="<<pb->r->y<<"; pb->z="<<pb->r->z<<endl;
           cout<<"pc->x="<<pc->r->x<<"; pc->y="<<pc->r->y<<"; pc->z="<<pc->r->z<<endl;
*/


            bool a = false, b = false, c = false;
            for(int o = 0; o < inner_points.size(); o++)
            {
                if
                (
                       inner_points[o]->r->x == pa->r->x
                    && inner_points[o]->r->y == pa->r->y
                    && inner_points[o]->r->z == pa->r->z
                )
                {
                    delete pa;
                    pa = inner_points[o];
                    a = true;
                }

                if
                (
                       inner_points[o]->r->x == pb->r->x
                    && inner_points[o]->r->y == pb->r->y
                    && inner_points[o]->r->z == pb->r->z
                )
                {
                    delete pb;
                    pb = inner_points[o];
                    b = true;
                }

                if
                (
                       inner_points[o]->r->x == pc->r->x
                    && inner_points[o]->r->y == pc->r->y
                    && inner_points[o]->r->z == pc->r->z
                )
                {
                    delete pc;
                    pc = inner_points[o];
                    c = true;
                }
            }

            // The new points are added to the general collection of points
            if(!a) inner_points.push_back(pa);
            if(!b) inner_points.push_back(pb);
            if(!c) inner_points.push_back(pc);


            // Create three new faces; these represent the three inner triangles
            inner_faces.push_back(new Face(inner_faces[i]->fp1, pa, pc, inner_springs)); // Top
            inner_faces.push_back(new Face(pa, inner_faces[i]->fp2, pb, inner_springs)); // Bottom-left
//            inner_faces.push_back(new Face(pb, inner_faces[i]->fp3, pc, inner_springs)); // Bottom-right
            inner_faces.push_back(new Face(pc, pb, inner_faces[i]->fp3, inner_springs)); // Bottom-right


            // Replace the original face's points with its new one in the middle

            inner_faces[i]->fp1 = pa;
            inner_faces[i]->fp2 = pb;
            inner_faces[i]->fp3 = pc;


            inner_faces[i]->fs1->sp1 = pa;
            inner_faces[i]->fs1->sp2 = pb;

            inner_faces[i]->fs2->sp1 = pb;
            inner_faces[i]->fs2->sp2 = pc;

            inner_faces[i]->fs3->sp1 = pc;
            inner_faces[i]->fs3->sp2 = pa;
        }





    }


    int i;
for(i=0; i<inner_points.size();i++)
//cout<<"inner_points"<<i<<"----="<<inner_points[i]->r->x<<";"<<inner_points[i]->r->y<<";"<<inner_points[i]->r->z<<endl;

for(i=0; i<inner_faces.size();i++)
{
/*cout<<"inner_faces fp1: "<<i<<"----="<<inner_faces[i]->fp1->r->x<<";"<<inner_faces[i]->fp1->r->y<<";"<<inner_faces[i]->fp1->r->z<<endl;
cout<<"inner_faces fp2: "<<i<<"----="<<inner_faces[i]->fp2->r->x<<";"<<inner_faces[i]->fp2->r->y<<";"<<inner_faces[i]->fp2->r->z<<endl;
cout<<"inner_faces fp3: "<<i<<"----="<<inner_faces[i]->fp3->r->x<<";"<<inner_faces[i]->fp3->r->y<<";"<<inner_faces[i]->fp3->r->z<<endl;
*/}

}



//##ModelId=45F4D7970100
void Object3D::nonunitsphere()
{

    float tix, tiy, tiz, tox,toy, toz;
    float theta, phi;


float dtheta = 180/3;
float dphi = 360/3;
      for(theta=-90; theta<=90-dtheta; theta+=dtheta)
    {
//    for(i=0; i<numParticles ;i++)
  // create NUMP points into 2D circle
        for(phi=0;phi<=360-dphi; phi+=dphi)
//    for(j=0; j<numParticles ;j++)
      {
    


        tix = 1*RING_RADIUS*cos(theta)*cos(phi);    // outer point X coordiation
        tiy = 1*RING_RADIUS*cos(theta)*sin(phi);    // outer point Y coordiation
        tiz = 1*RING_RADIUS*sin(theta);    // outer point Y coordiation

        tox = 1*RING_RADIUS*cos(theta)*cos(phi);
        toy = 1*RING_RADIUS*cos(theta)*sin(phi);    // outer point Y coordiation
        toz = 1*RING_RADIUS*sin(theta);    // outer point Y coordiation

        outer_points.push_back( new Particle(new Vector(tox, toy, toz), MASS));
                
        inner_points.push_back( new Particle(new Vector(tix, tiy, tiz), MASS));
    

        tix = 1*RING_RADIUS*cos(theta+dtheta)*cos(phi);    // outer point X coordiation
        tiy = 1*RING_RADIUS*cos(theta+dtheta)*sin(phi);    // outer point Y coordiation
        tiz = 1*RING_RADIUS*sin(theta+dtheta);    // outer point Y coordiation

        tox = 1*RING_RADIUS*cos(theta+dtheta)*cos(phi);
        toy = 1*RING_RADIUS*cos(theta+dtheta)*sin(phi);    // outer point Y coordiation
        toz = 1*RING_RADIUS*sin(theta+dtheta);    // outer point Y coordiation

        outer_points.push_back( new Particle(new Vector(tox, toy, toz), MASS));
                
        inner_points.push_back( new Particle(new Vector(tix, tiy, tiz), MASS));

    
        tix = 1*RING_RADIUS*cos(theta+dtheta)*cos(phi+dphi);    // outer point X coordiation
        tiy = 1*RING_RADIUS*cos(theta+dtheta)*sin(phi+dphi);    // outer point Y coordiation
        tiz = 1*RING_RADIUS*sin(theta+dtheta);    // outer point Y coordiation

        tox = 1*RING_RADIUS*cos(theta+dtheta)*cos(phi+dphi);
        toy = 1*RING_RADIUS*cos(theta+dtheta)*sin(phi+dphi);    // outer point Y coordiation
        toz = 1*RING_RADIUS*sin(theta+dtheta);    // outer point Y coordiation

        outer_points.push_back( new Particle(new Vector(tox, toy, toz), MASS));
                
        inner_points.push_back( new Particle(new Vector(tix, tiy, tiz), MASS));


        if(theta>-90 && theta<90)
        {
        tix = 1*RING_RADIUS*cos(theta)*cos(phi+dphi);    // outer point X coordiation
        tiy = 1*RING_RADIUS*cos(theta)*sin(phi+dphi);    // outer point Y coordiation
        tiz = 1*RING_RADIUS*sin(theta);    // outer point Y coordiation

        tox = 1*RING_RADIUS*cos(theta)*cos(phi+dphi);
        toy = 1*RING_RADIUS*cos(theta)*sin(phi+dphi);    // outer point Y coordiation
        toz = 1*RING_RADIUS*sin(theta);    // outer point Y coordiation

        outer_points.push_back( new Particle(new Vector(tox, toy, toz), MASS));
                
        inner_points.push_back( new Particle(new Vector(tix, tiy, tiz), MASS));
        }

        //    cout<<"tox=="<<tox<<"==toy=="<<toy<<"==toz=="<<toz<<endl;
        }
        
    
    }



    /* float M=4;
  float N=4;
    for(i=0; i<M ; i++)
//    for(i=0; i<numParticles ;i++)
  {// create NUMP points into 2D circle
        for(j=0;j<N; j++)
//    for(j=0; j<numParticles ;j++)
      {
    


        tix = 1*RING_RADIUS*cos(((i-M/2)*2.0*PI)/N)*cos(j*(2.0*PI)/N);    // outer point X coordiation
        tiy = 1*RING_RADIUS*cos(((i-M/2)*2.0*PI)/N)*sin(j*(2.0*PI)/N);    // outer point Y coordiation
        tiz = 1*RING_RADIUS*sin(((i-M/2)*2.0*PI)/N);    // outer point Y coordiation

        tox = 1*RING_RADIUS*cos(((i-M/2)*2.0*PI)/N)*cos(j*(2.0*PI)/N);    // outer point X coordiation
        toy = 1*RING_RADIUS*cos(((i-M/2)*2.0*PI)/N)*sin(j*(2.0*PI)/N);    // outer point Y coordiation
        toz = 1*RING_RADIUS*sin(((i-M/2)*2.0*PI)/N);    // outer point Y coordiation


        cout<<"i---"<<i<<"tox=="<<tox<<"==toy=="<<toy<<"==toz=="<<toz<<endl;
            outer_points.push_back( new Particle(new Vector(tox, toy, toz), MASS));
                
        inner_points.push_back( new Particle(new Vector(tix, tiy, tiz), MASS));
    
    //    cout<<"tox=="<<tox<<"==toy=="<<toy<<"==toz=="<<toz<<endl;
        }
        
    
    }*/


}

///////////////==================================================================
//##ModelId=45F4D7970101
void Object3D::SetObject(void) // [M+2][N] array for M*N+2 Points
{
        
//    int tempsp1, tempsp2;
    
    outer_points.clear();
    inner_points.clear();
    
    outer_faces.clear();
    inner_faces.clear();

    outer_springs.clear();
    inner_springs.clear();

    radium_springs.clear();
    shear_springs_left.clear();
    shear_springs_right.clear();

//    double a;
//    int nt=0/*, ntold*/;
    int i, j;
 
    /////////////////////////////////////////////////////////

//    Pyramid3();

//    Pyramid4();

    Tetrahedron();

//    cout<<"outer_spring size ======="<<outer_springs.size()<<endl;
    Iteration();
//        cout<<"interation after outer_spring size ======="<<outer_springs.size()<<endl;

    this->numParticles = (int) this->outer_points.size();
    this->numSprings = (int) this->outer_springs.size();

//    cout<<"this->numParticles ==="<<this->numParticles<<"-----this->numSprings===="<<this->numSprings<<"-------this->numFaces===="<<this->outer_faces.size()<<endl;
    //    assert(false);
    for(i=0; i<numSprings ;i++)                        //add the springs for outer & inner
    {
        //Add_Structural_Spring(i,i,(i+1) % numParticles);
    
        Add_Radium_Spring(i) ;
        Add_Shear_Spring(i);
        //Add_Faces(i, (i+1) % numParticles, (numParticles/2 + i) % numParticles) ;

    }

    
    
    for(i=0;i<inner_faces.size();i++)
    {
        inner_faces[i]->CalNormalNField();
        outer_faces[i]->CalNormalNField();
//        cout<<"outer_faces[i]->normal->x==="<<outer_faces[i]->normal->x<<"=== outer_faces[i]->normal->y==="<<outer_faces[i]->normal->y<<"===outer_faces[i]->normal->z===="<<outer_faces[i]->normal->z<<endl;
    }
    
    createVertexArray();
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//##ModelId=45F4D797011D
void Object3D::Tetrahedron()
{

    double a;
    int i;

    outer_points.push_back( new Particle(new Vector(0,0,1.5*RING_RADIUS), MASS));
    outer_points.push_back( new Particle(new Vector(0,0,-1.5*RING_RADIUS), MASS));
    outer_points.push_back( new Particle(new Vector(-1.5*RING_RADIUS,-1.5*RING_RADIUS,0), MASS));
    outer_points.push_back( new Particle(new Vector(1.5*RING_RADIUS,-1.5*RING_RADIUS,0), MASS));
    outer_points.push_back( new Particle(new Vector(1.5*RING_RADIUS,1.5*RING_RADIUS,0), MASS));
    outer_points.push_back( new Particle(new Vector(-1.5*RING_RADIUS,1.5*RING_RADIUS,0), MASS));

    inner_points.push_back( new Particle(new Vector(0,0,1.3*RING_RADIUS), MASS));
    inner_points.push_back( new Particle(new Vector(0,0,-1.3*RING_RADIUS), MASS));
    inner_points.push_back( new Particle(new Vector(-1.3*RING_RADIUS,-1.3*RING_RADIUS,0), MASS));
    inner_points.push_back( new Particle(new Vector(1.3*RING_RADIUS,-1.3*RING_RADIUS,0), MASS));
    inner_points.push_back( new Particle(new Vector(1.3*RING_RADIUS,1.3*RING_RADIUS,0), MASS));
    inner_points.push_back( new Particle(new Vector(-1.3*RING_RADIUS,1.3*RING_RADIUS,0), MASS));

    

    this->numParticles = (int) outer_points.size();


    a = 1 / sqrt(2.0);

    for (i=0;i<outer_points.size();i++)
    {
        outer_points[i]->r->x *= a;
        outer_points[i]->r->y *= a;
    //    outer_points[i]->r->z *= a;
        
        inner_points[i]->r->x *= a;
        inner_points[i]->r->y *= a;
    //    inner_points[i]->r->z *= a;
    }


    outer_faces.push_back(new Face(outer_points[0], outer_points[3], outer_points[4], outer_springs));
    outer_faces.push_back(new Face(outer_points[0], outer_points[4], outer_points[5], outer_springs));
    outer_faces.push_back(new Face(outer_points[0], outer_points[5], outer_points[2], outer_springs));
    outer_faces.push_back(new Face(outer_points[0], outer_points[2], outer_points[3], outer_springs));
    outer_faces.push_back(new Face(outer_points[1], outer_points[4], outer_points[3], outer_springs));
    outer_faces.push_back(new Face(outer_points[1], outer_points[5], outer_points[4], outer_springs));
    outer_faces.push_back(new Face(outer_points[1], outer_points[2], outer_points[5], outer_springs));
    outer_faces.push_back(new Face(outer_points[1], outer_points[3], outer_points[2], outer_springs));


    inner_faces.push_back(new Face(inner_points[0], inner_points[3], inner_points[4], inner_springs));
    inner_faces.push_back(new Face(inner_points[0], inner_points[4], inner_points[5], inner_springs));
    inner_faces.push_back(new Face(inner_points[0], inner_points[5], inner_points[2], inner_springs));
    inner_faces.push_back(new Face(inner_points[0], inner_points[2], inner_points[3], inner_springs));
    inner_faces.push_back(new Face(inner_points[1], inner_points[4], inner_points[3], inner_springs));
    inner_faces.push_back(new Face(inner_points[1], inner_points[5], inner_points[4], inner_springs));
    inner_faces.push_back(new Face(inner_points[1], inner_points[2], inner_points[5], inner_springs));
    inner_faces.push_back(new Face(inner_points[1], inner_points[3], inner_points[2], inner_springs));


    this->numSprings = (int) this->outer_springs.size();

}


//##ModelId=45F4D797011E
void Object3D::Pyramid3()
{

    double a;

    int i;


    outer_points.push_back( new Particle(new Vector(-2 * RING_RADIUS, 0,  2 * RING_RADIUS), MASS));
    outer_points.push_back( new Particle(new Vector(-2 * RING_RADIUS, 0, -2 * RING_RADIUS), MASS));
    outer_points.push_back( new Particle(new Vector( 2 * RING_RADIUS, 0, 0), MASS));
    outer_points.push_back( new Particle(new Vector( 0, 2 * RING_RADIUS,0), MASS));

    // XXX: must match above
    inner_points.push_back( new Particle(new Vector(0,0,RING_RADIUS), MASS));
    inner_points.push_back( new Particle(new Vector(0,0,-RING_RADIUS), MASS));
    inner_points.push_back( new Particle(new Vector(-RING_RADIUS,-RING_RADIUS,0), MASS));
    inner_points.push_back( new Particle(new Vector(RING_RADIUS,-RING_RADIUS,0), MASS));


    this->numParticles = (int)outer_points.size();


    a = 1 / sqrt(2.0);



    for (i=0;i<outer_points.size();i++)
    {
        outer_points[i]->r->x *= a;
        outer_points[i]->r->y *= a;
        outer_points[i]->r->z *= a;


        inner_points[i]->r->x *= a;
        inner_points[i]->r->y *= a;
        inner_points[i]->r->z *= a;
    }


    // Bottom face
    outer_faces.push_back(new Face(outer_points[0], outer_points[1], outer_points[2], outer_springs));

    // Left face
    outer_faces.push_back(new Face(outer_points[0], outer_points[1], outer_points[3], outer_springs));


    // Front face
    outer_faces.push_back(new Face(outer_points[0], outer_points[2], outer_points[3], outer_springs));

    // Back face
    outer_faces.push_back(new Face(outer_points[1], outer_points[2], outer_points[3], outer_springs));


    //-----------------------------

///*

    inner_faces.push_back(new Face(inner_points[0], inner_points[1], inner_points[2], inner_springs));

    // Left face
    inner_faces.push_back(new Face(inner_points[0], inner_points[1], inner_points[3], inner_springs));

    // Front face
    inner_faces.push_back(new Face(inner_points[0], inner_points[2], inner_points[3], inner_springs));

    // Back face
    inner_faces.push_back(new Face(inner_points[1], inner_points[2], inner_points[3], inner_springs));

//*/



    this->numSprings = (int) this->outer_springs.size();
}


//================================================================================

//##ModelId=45F4D79700FD
void Object3D::Draw(int shaderID, glm::mat4 worldMatrix)
{
    

    static bool findOnce = false;
//    glDisable(GL_DEPTH_TEST);
//    glDisable(GL_CULL_FACE);

//     int i;
 //===============================================================================
//    glPushMatrix();
//    glColor4f(0,0,1,1);   // Blue color point distribution
//    glBegin(GL_POINTS); // Draw points which built the Object3D
//        glPointSize(10);
//        for(i=0; i<outer_points.size(); i++)
//        {
//        glVertex3f(outer_points[i]->r->x, outer_points[i]->r->y, outer_points[i]->r->z);
//        }
//
//     glEnd();
//
//    glColor4f(0,0,1,1);
//
//    glBegin(GL_POINTS); // Draw inner points which built the Object3D
//        glPointSize(10);
//        for(i=0; i<inner_points.size(); i++)
//        {
//        glVertex3f(inner_points[i]->r->x, inner_points[i]->r->y, inner_points[i]->r->z);
//        }
//     glEnd();
//
//    glPopMatrix();
//===================================================================================
    
    //  ===============  basic settings for ogl3 drawing
    updateVertexArray();
    glBindVertexArray(VAO);
    // set world matrix
    glUniformMatrix4fv(glGetUniformLocation(shaderID, "worldMatrix"), 1, GL_FALSE, &glm::mat4(1.0f)[0][0]);
    // get color location
    GLuint ColorLocation = glGetUniformLocation(shaderID, "colorChoice");
    glEnableClientState(GL_VERTEX_ARRAY);
    glPointSize(10);
    // ====================================================

    // drawing outer and inner points (blue)
    glUniform4f(ColorLocation, 0.0f, 0.0f, 1.0f, 1.0f);
    glDrawArrays(GL_POINTS, getOffset(outer_inner_points), getCount(outer_inner_points));
    
    // drawing inner faces
    glUniform4f(ColorLocation, 1.0f, 0.0f, 1.0f, 0.6f);
    glDrawArrays(GL_TRIANGLES, getOffset(inner_face), getCount(inner_face));
    
    // drawing outer faces
    glUniform4f(ColorLocation, 1.0f, 1.0f, 1.0f, 0.6f);
    glDrawArrays(GL_TRIANGLES, getOffset(outer_face), getCount(outer_face));
    
    // drawing outer faces normals
    glUniform4f(ColorLocation, 0.0f, 0.0f, 1.0f, 1.0f);
    glDrawArrays(GL_LINES, getOffset(outer_face_normal), getCount(outer_face_normal));

    
//    cout<<"Object3D spring size is : "<<outer_springs.size()<<endl;
/*
    glPushMatrix();
    glColor4f(1,0,0,1);
    glBegin(GL_LINES);
    for(i = 0; i<outer_springs.size();i++)
    {
         glVertex3f(outer_springs[i]->sp1->r->x, outer_springs[i]->sp1->r->y, outer_springs[i]->sp1->r->z);
         glVertex3f(outer_springs[i]->sp2->r->x, outer_springs[i]->sp2->r->y, outer_springs[i]->sp2->r->z);
        
    
    }
    glEnd();
    glPopMatrix();
    //*/
///========================================draw inner structural springs==========================================
    
/*    glPushMatrix();
    glColor4f(1,0,0,1);
    glBegin(GL_LINES);
    for(i = 0; i<inner_springs.size();i++)
    {
         glVertex3f(inner_springs[i]->sp1->r->x, inner_springs[i]->sp1->r->y, inner_springs[i]->sp1->r->z);
         glVertex3f(inner_springs[i]->sp2->r->x, inner_springs[i]->sp2->r->y, inner_springs[i]->sp2->r->z);
    }
    glEnd();
    glPopMatrix();
*/
///========================================draw radium springs==========================================
/*    glPushMatrix();
        glBegin(GL_LINES);                // the draw of radium lines from inner to outer
            glLineWidth(10);
            for(i=0 ; i<radium_springs.size(); i++)
            {
                glColor3f(0.0,1.0,0.0);
                glVertex3f(radium_springs[i]->sp1->r->x, radium_springs[i]->sp1->r->y, radium_springs[i]->sp1->r->z);
                glVertex3f(radium_springs[i]->sp2->r->x, radium_springs[i]->sp2->r->y, radium_springs[i]->sp2->r->z);
            }
        glEnd();
    glPopMatrix();*/
    
///========================================draw shear left springs==========================================
/*    glPushMatrix();
        glBegin(GL_LINES);                // the left shear lines from inner to outer
            for(i=0 ; i<shear_springs_left.size(); i++)
            {
                glColor3f(1.0,1.0,0.0);
                glVertex3f(shear_springs_left[i]->sp1->r->x,shear_springs_left[i]->sp1->r->y, shear_springs_left[i]->sp1->r->z);
                glVertex3f(shear_springs_left[i]->sp2->r->x,shear_springs_left[i]->sp2->r->y, shear_springs_left[i]->sp2->r->z);
            }
        glEnd();
    glPopMatrix();*/

///========================================draw shear right springs==========================================

/*    glPushMatrix();
        glBegin(GL_LINES);                // the right shear lines from inner to outer
            for(i=0 ; i<shear_springs_right.size(); i++)
            {
                glColor3f(0.0,0.0,1.0);
                glVertex3f(shear_springs_right[i]->sp1->r->x,shear_springs_right[i]->sp1->r->y, shear_springs_right[i]->sp1->r->z);
                glVertex3f(shear_springs_right[i]->sp2->r->x,shear_springs_right[i]->sp2->r->y, shear_springs_right[i]->sp2->r->z);
            }
        glEnd();
    glPopMatrix();*/



//=======================================================================================
/////----------------------------------------- Draw inner faces ----------------------------------------------
//    cout<<"inner_faces.size()???????????????"<<inner_faces.size()<<endl;
//    glPushMatrix();
//    glBegin(GL_TRIANGLES);
//            for(i=0; i<inner_faces.size(); i++)
//            {
//                glColor4f(1.0,0.0,0.0,.6);             // Yellow color face distribution
//         //     glNormal3f(inner_faces[i]->normal->x,inner_faces[i]->normal->y,inner_faces[i]->normal->z);
//                glVertex3f(inner_faces[i]->fp1->r->x, inner_faces[i]->fp1->r->y, inner_faces[i]->fp1->r->z);
//                glVertex3f(inner_faces[i]->fp2->r->x, inner_faces[i]->fp2->r->y, inner_faces[i]->fp2->r->z);
//                glVertex3f(inner_faces[i]->fp3->r->x, inner_faces[i]->fp3->r->y, inner_faces[i]->fp3->r->z);
//
//            }
//        glEnd();
/////----------------------------------------- Draw inner faces normals----------------------------------------------

/*        glBegin(GL_LINES);
            for(i=0 ; i<inner_faces.size(); i++)
            {
                glVertex3f(inner_faces[i]->fp1->r->x, inner_faces[i]->fp1->r->y, inner_faces[i]->fp1->r->z);
            
                glVertex3f((inner_faces[i]->normal->x + inner_faces[i]->fp1->r->x),
                           (inner_faces[i]->normal->y + inner_faces[i]->fp1->r->y),
                           (inner_faces[i]->normal->z + inner_faces[i]->fp1->r->z));
            }
        glEnd();*/

//    glPopMatrix();


/////----------------------------------------- Draw outer faces ----------------------------------------------
 
//    glPushMatrix();
//        glBegin(GL_TRIANGLES);
//            for(i=0; i<outer_faces.size(); i++)
//            {
//            //    break;
//                glColor4f(1.0,1.0,1.0,.2);             // Yellow color face distribution
//                //     glNormal3f(outer_faces[i]->normal->x,outer_faces[i]->normal->y,outer_faces[i]->normal->z);
//                glVertex3f(outer_faces[i]->fp1->r->x, outer_faces[i]->fp1->r->y, outer_faces[i]->fp1->r->z);
//                glVertex3f(outer_faces[i]->fp2->r->x, outer_faces[i]->fp2->r->y, outer_faces[i]->fp2->r->z);
//                glVertex3f(outer_faces[i]->fp3->r->x, outer_faces[i]->fp3->r->y, outer_faces[i]->fp3->r->z);
//
//            }
//        glEnd();
/////----------------------------------------- Draw outer faces normals----------------------------------------------


//        glColor3f(0,0,1);
//        glBegin(GL_LINES);
//            for(i=0 ; i<outer_faces.size(); i++)
//            {
//                glVertex3f(outer_faces[i]->fp1->r->x, outer_faces[i]->fp1->r->y, outer_faces[i]->fp1->r->z);
//                glVertex3f(outer_faces[i]->fp2->r->x, outer_faces[i]->fp2->r->y, outer_faces[i]->fp2->r->z);
//
//                glVertex3f(outer_faces[i]->fp2->r->x, outer_faces[i]->fp2->r->y, outer_faces[i]->fp2->r->z);
//                glVertex3f(outer_faces[i]->fp3->r->x, outer_faces[i]->fp3->r->y, outer_faces[i]->fp3->r->z);
//
//                glVertex3f(outer_faces[i]->fp3->r->x, outer_faces[i]->fp3->r->y, outer_faces[i]->fp3->r->z);
//                glVertex3f(outer_faces[i]->fp1->r->x, outer_faces[i]->fp1->r->y, outer_faces[i]->fp1->r->z);
//
////                glVertex3f((outer_faces[i]->normal->x + outer_faces[i]->fp1->r->x),
////                           (outer_faces[i]->normal->y + outer_faces[i]->fp1->r->y),
////                           (outer_faces[i]->normal->z + outer_faces[i]->fp1->r->z));
//
//
//                glVertex3f(inner_faces[i]->fp1->r->x, inner_faces[i]->fp1->r->y, inner_faces[i]->fp1->r->z);
//                glVertex3f(inner_faces[i]->fp2->r->x, inner_faces[i]->fp2->r->y, inner_faces[i]->fp2->r->z);
//
//                glVertex3f(inner_faces[i]->fp2->r->x, inner_faces[i]->fp2->r->y, inner_faces[i]->fp2->r->z);
//                glVertex3f(inner_faces[i]->fp3->r->x, inner_faces[i]->fp3->r->y, inner_faces[i]->fp3->r->z);
//
//                glVertex3f(inner_faces[i]->fp3->r->x, inner_faces[i]->fp3->r->y, inner_faces[i]->fp3->r->z);
//                glVertex3f(inner_faces[i]->fp1->r->x, inner_faces[i]->fp1->r->y, inner_faces[i]->fp1->r->z);
//            }
//        glEnd();
//
//    glPopMatrix();
//---------------------------------------------------------------------------------------
    if(integrator != nullptr){
        if(integrator->dragExists)
        {
            if(findOnce == true)
            {
                FindClosestPoint();
                findOnce = false;
            }
            // drawing integrator line
            glUniform4f(ColorLocation, 1.0f, 1.0f, 0.0f, 1.0f);
            glDrawArrays(GL_LINES, getOffset(integrator_line), getCount(integrator_line));
            
        }
        else
        {
            FindClosestPoint();
            findOnce = true;
        }
    }
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
}

