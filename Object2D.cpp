#include "Object2D.h"

//##ModelId=45F4D797016E
Object2D::Object2D() : pressure(PRESSURE)
{
    numParticles = NUMPOINTS;
    numSprings =  NUMSPRINGS;
    SetObject();
    dim = DIM2D;
}


//##ModelId=45F4D7970178
Object2D::~Object2D()
{
}

void Object2D::createVertexArray(){
    total = 0;
    // here's how the number of vertercies are counted
    total += outer_faces.size() * 2;        // for drawing outer lines
    total += outer_points.size();           // for drawing outer polygon
    total += inner_points.size();           // for drawing inner polygon
    total += outer_springs.size() * 2;      // for drawing outer springs
    total += inner_springs.size() * 2;      // for drawing inner springs
    total += radium_springs.size() * 2;     // for drawing radium springs
    total += shear_springs_left.size() * 2; // for drawing shear_springs_left
    total += shear_springs_right.size() * 2;// for drawing shear_springs_right
    total += 2;                             // for drawing the integrator line between mouse and object
    
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
}

void Object2D::updateVertexArray(){
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // use a temp vector to update all the information and then copy the vector to vertexArrayData
    vector<glm::vec3> tempVertices;
    // push in the outer circle lines data
    for(int i = 0; i < outer_faces.size(); ++i){
        tempVertices.push_back(glm::vec3(outer_faces[i]->fp1->r->x, outer_faces[i]->fp1->r->y, outer_faces[i]->fp1->r->z));
        tempVertices.push_back(glm::vec3((outer_faces[i]->normal->x + outer_faces[i]->fp1->r->x),
                                         (outer_faces[i]->normal->y + outer_faces[i]->fp1->r->y),
                                         (outer_faces[i]->normal->z + outer_faces[i]->fp1->r->z)));
    }
    
    // push in the outer polygon data
    for(int i = 0; i < outer_points.size(); i++)
    {
        tempVertices.push_back(glm::vec3(outer_points[i]->r->x, outer_points[i]->r->y, 0.0f));
    }
    
    // push in inner polygon data
    for(int i = 0; i < inner_points.size(); ++i)
    {
        tempVertices.push_back(glm::vec3(inner_points[i]->r->x, inner_points[i]->r->y, 0.0f));
    }
    
    // push in outer spring data
    for(int i = 0; i < outer_springs.size(); ++i){
        tempVertices.push_back(glm::vec3(outer_springs[i]->sp1->r->x,outer_springs[i]->sp1->r->y, 0.0f));
        tempVertices.push_back(glm::vec3(outer_springs[i]->sp2->r->x,outer_springs[i]->sp2->r->y, 0.0f));
    }
    
    // push in inner spring data
    for(int i = 0; i < inner_springs.size(); ++i){
        tempVertices.push_back(glm::vec3(inner_springs[i]->sp1->r->x,inner_springs[i]->sp1->r->y, 0.0f));
        tempVertices.push_back(glm::vec3(inner_springs[i]->sp2->r->x,inner_springs[i]->sp2->r->y, 0.0f));
    }
    
    // push in radium spring data
    for(int i = 0; i < radium_springs.size(); ++i){
        tempVertices.push_back(glm::vec3(radium_springs[i]->sp1->r->x,radium_springs[i]->sp1->r->y, 0.0f));
        tempVertices.push_back(glm::vec3(radium_springs[i]->sp2->r->x,radium_springs[i]->sp2->r->y, 0.0f));
    }
    
    // push in shear spring left data
    for(int i = 0; i < shear_springs_left.size(); ++i){
        tempVertices.push_back(glm::vec3(shear_springs_left[i]->sp1->r->x,shear_springs_left[i]->sp1->r->y, 0.0f));
        tempVertices.push_back(glm::vec3(shear_springs_left[i]->sp2->r->x,shear_springs_left[i]->sp2->r->y, 0.0f));
    }
    
    // push in shear spring right data
    for(int i = 0; i < shear_springs_right.size(); ++i){
        tempVertices.push_back(glm::vec3(shear_springs_right[i]->sp1->r->x,shear_springs_right[i]->sp1->r->y, 0.0f));
        tempVertices.push_back(glm::vec3(shear_springs_right[i]->sp2->r->x,shear_springs_right[i]->sp2->r->y, 0.0f));
    }
    
    // push in integrator line data
    if(integrator != nullptr){
        tempVertices.push_back(glm::vec3(integrator->mDragX, integrator->mDragY, 0.0f));
        tempVertices.push_back(glm::vec3(outer_points[closest_i]->r->x, outer_points[closest_i]->r->y, 0.0f));
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

int Object2D::getOffset(drawing_instances instance){
    int offset = 0;
    
    switch(instance){
        case outer_line:
            offset = 0;
            break;
        case outer_polygon:
            offset = (int) outer_faces.size() * 2;
            break;
        case inner_polygon:
            offset = getOffset(outer_polygon) + getCount(outer_polygon);
            break;
        case outer_spring:
            offset = getOffset(inner_polygon) + getCount(inner_polygon);
            break;
        case inner_spring:
            offset = getOffset(outer_spring) + getCount(outer_spring);
            break;
        case radium_spring:
            offset = getOffset(inner_spring) + getCount(inner_spring);
            break;
        case shear_left:
            offset = getOffset(radium_spring) + getCount(radium_spring);
            break;
        case shear_right:
            offset = getOffset(shear_left) + getCount(shear_left);
            break;
        case integrator_line:
            offset = getOffset(shear_right) + getCount(shear_right);
            break;
        default:
            offset = 0;
            break;
            
    }
    return offset;
}

int Object2D::getCount(drawing_instances instance){
    int vertexCount = 0;
    
    switch(instance){
        case outer_line:
            vertexCount = (int) outer_faces.size()*2;
            break;
        case outer_polygon:
            vertexCount = (int) outer_points.size();
            break;
        case inner_polygon:
            vertexCount = (int) inner_points.size();
            break;
        case outer_spring:
            vertexCount = (int) outer_springs.size() * 2;
            break;
        case inner_spring:
            vertexCount = (int) inner_springs.size() * 2;
            break;
        case radium_spring:
            vertexCount = (int) radium_springs.size() * 2;
            break;
        case shear_left:
            vertexCount = (int) shear_springs_left.size() * 2;
            break;
        case shear_right:
            vertexCount = (int) shear_springs_right.size() * 2;
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

//##ModelId=45F4D797017A
void Object2D::Draw(int shaderID, glm::mat4 worldMatrix)
{
    static bool findOnce = false;
    
    //  ===============  basic settings for ogl3 drawing
    updateVertexArray();
    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // set world matrix
    glUniformMatrix4fv(glGetUniformLocation(shaderID, "worldMatrix"), 1, GL_FALSE, &worldMatrix[0][0]);
    // get color location
    GLuint ColorLocation = glGetUniformLocation(shaderID, "colorChoice");
    glEnableClientState(GL_VERTEX_ARRAY);
    glPointSize(10);
    // ====================================================

    // drawing outer lines
    glUniform4f(ColorLocation, 0.5f, 0.2f, 0.5f, 0.7f);
    glDrawArrays(GL_LINES, getOffset(outer_line), getCount(outer_line));
    
    // drawing outer polygon
    glDrawArrays(GL_TRIANGLE_FAN, getOffset(outer_polygon), getCount(outer_polygon));
    
    // drawing inner polygon
    glUniform4f(ColorLocation, 0.0f, 1.0f, 0.0f, 0.5f);
    glDrawArrays(GL_TRIANGLE_FAN, getOffset(inner_polygon), getCount(inner_polygon));
    
    // drawing outer springs
    // (line)
    glUniform4f(ColorLocation, 0.2f, 0.2f, 1.0f, 1.0f);
    glDrawArrays(GL_LINES, getOffset(outer_spring), getCount(outer_spring));
    // (point) - need to be drawn using a loop to draw only one point, also the first point need to be red, other yellow
    for(int i = 0; i < outer_springs.size(); ++i)
    {
        if(i == 0)
            glUniform4f(ColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
        else
            glUniform4f(ColorLocation, 1.0f, 1.0f, 0.0f, 1.0f);
        
        glDrawArrays(GL_POINTS, getOffset(outer_spring) + i*2, 1);
    }
    
    // drawing inner springs
    // (line)
    glUniform4f(ColorLocation, 0.2f, 0.2f, 1.0f, 1.0f);
    glDrawArrays(GL_LINES, getOffset(inner_spring), getCount(inner_spring));
    // (point)
    glUniform4f(ColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
    glDrawArrays(GL_POINTS, getOffset(inner_spring), getCount(inner_spring));
    
    // drawing radium springs
    glUniform4f(ColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);
    glDrawArrays(GL_LINES, getOffset(radium_spring), getCount(radium_spring));
    
    // drawing shear spring left
    glUniform4f(ColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
    glDrawArrays(GL_LINES, getOffset(shear_left), getCount(shear_left));
    
    // drawing shear spring right
    glUniform4f(ColorLocation, 0.0f, 0.0f, 1.0f, 1.0f);
    glDrawArrays(GL_LINES, getOffset(shear_right), getCount(shear_right));
    
    
    
    if(integrator != nullptr){
        if(integrator->dragExists)
        {
            if(findOnce == true)
            {
                FindClosestPoint();
                findOnce = false;
            }
            // draw integrator
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
    
    glBindVertexArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/* Function of adding a new spring on the inner rings*/

//##ModelId=45F4D797018A
void Object2D::Add_Structural_Spring(int index, int h, int t)
{

       inner_springs.push_back( new Spring(inner_points[h],inner_points[t]));
    outer_springs.push_back( new Spring(outer_points[h],outer_points[t]));

    inner_springs[index]->setRestLen();                    //set the inner spring's length
    outer_springs[index]->setRestLen();                    //set the outer spring's length
}


//##ModelId=45F4D7970198
void Object2D::Add_Radium_Spring(int index)
{
       
    radium_springs.push_back( new Spring(inner_points[index],outer_points[index]));
    radium_springs[index]->setRestLen();                        //set the radium spring's length
}


//##ModelId=45F4D797019A
void Object2D::Add_Shear_Spring(int index, int h, int t )
{
      
    
    shear_springs_left.push_back(new Spring(inner_points[h],outer_points[t]));
    shear_springs_right.push_back(new Spring(inner_points[t],outer_points[h]));


    shear_springs_left[index]->setRestLen();                    //set the shear left spring's length
    shear_springs_right[index]->setRestLen();                //set the shear right spring's length
 
}

/* Create 2 2D-rings (points + springs) */
//##ModelId=45F4D797017F
void Object2D::SetObject(void)
{
    float tix, tiy, tiz, tox,toy, toz;
    
    tix=tiy=tiz=tox=toy=toz=0;
    outer_points.clear();
    inner_points.clear();
    outer_springs.clear();
    inner_springs.clear();
    outer_faces.clear();
    inner_faces.clear();
    int i;
    for(i=0; i<numParticles ; i++)                            // create NUMP points into 2D circle
    {
    


        tix = 1*RING_RADIUS*cos(i*(2.0*PI)/numParticles);    // outer point X coordiation
        tiy = 1*RING_RADIUS*sin(i*(2.0*PI)/numParticles);    // outer point Y coordiation
        tiz = 0;//2*RING_RADIUS*sin(i*(2.0*PI)/numParticles);    // outer point Y coordiation

        tox = 2*RING_RADIUS*cos(i*(2.0*PI)/numParticles);    // outer point X coordiation
        toy = 2*RING_RADIUS*sin(i*(2.0*PI)/numParticles);    // outer point Y coordiation
        toz = 0;//2*RING_RADIUS*sin(i*(2.0*PI)/numParticles);    // outer point Y coordiation


    //    cout<<"tox=="<<tox<<"==toy=="<<toy<<"==toz=="<<toz<<endl;
        outer_points.push_back( new Particle(new Vector(tox, toy, toz), MASS));
        inner_points.push_back( new Particle(new Vector(tix, tiy, tiz), MASS));
    }

    

    for(i=0; i<numParticles ;i++)                        //add the springs for outer & inner
    {
        Add_Structural_Spring(i,i,(i+1) % numParticles);
        Add_Radium_Spring(i) ;
        Add_Shear_Spring(i,i,(i+1) % numParticles);
        Add_Faces(i, (i+1) % numParticles, (numParticles/2 + i) % numParticles) ;

    }


    for(i=0;i<inner_faces.size();i++)
    {
    
        inner_faces[i]->CalNormalNField();

    outer_faces[i]->CalNormalNField();
//        cout<<"outer_faces[i]->normal->x==="<<outer_faces[i]->normal->x<<"=== outer_faces[i]->normal->y==="<<outer_faces[i]->normal->y<<"===outer_faces[i]->normal->z===="<<outer_faces[i]->normal->z<<endl;

    
    }

/*    cout<<"outer_faces[0]->fp1->r->x=="<<outer_faces[0]->fp1->r->x<<"==outer_faces[0]->fp1->r->y=="<<outer_faces[0]->fp1->r->y<<"==outer_faces[0]->fp1->r->z=="<<outer_faces[0]->fp1->r->z<<endl;
        cout<<"outer_faces[0]->fp2->r->x=="<<outer_faces[0]->fp2->r->x<<"==outer_faces[0]->fp2->r->y=="<<outer_faces[0]->fp2->r->y<<"==outer_faces[0]->fp2->r->z=="<<outer_faces[0]->fp2->r->z<<endl;
        cout<<"outer_faces[0]->fp3->r->x=="<<outer_faces[0]->fp3->r->x<<"==outer_faces[0]->fp3->r->y=="<<outer_faces[0]->fp3->r->y<<"==outer_faces[0]->fp3->r->z=="<<outer_faces[0]->fp3->r->z<<endl;

    outer_faces[0]->CalNormalNField();
    cout<<"outer_faces[0]->normal->x==="<<outer_faces[0]->normal->x<<"=== outer_faces[0]->normal->y==="<<outer_faces[0]->normal->y<<"===outer_faces[0]->normal->z===="<<outer_faces[0]->normal->z<<endl;
*/
    
    createVertexArray();

}


//##ModelId=45F4D79701A7
void Object2D::Add_Faces(int f1, int f2, int f3)
{
    inner_faces.push_back(new Face(inner_points[f1], inner_points[f2], inner_points[f3]));
    outer_faces.push_back(new Face(outer_points[f1], outer_points[f2], outer_points[f3]));
}
