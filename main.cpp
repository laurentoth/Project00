////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Contains main function to create a window and run engine
///
/// Basic support for directional light, depth buffer, setting up 3d projection,
/// setting up a 3d camera, drawing a cube model, and running a set fixed frame
/// rate.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes

// STL
#include <cmath>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// GL
#if   defined(OSX)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <GLUT/glut.h>
#elif defined(LINUX)
#include <GL/glut.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#endif
////////////////////////////////////////////////////////////////////////////////
// Global variables - avoid these

// Window
int g_width{1360};
int g_height{768};
int g_window{0};

// Camera
float g_theta{0.f};

// Frame rate
const unsigned int FPS = 60;
float g_frameRate{0.f};
std::chrono::high_resolution_clock::time_point g_frameTime{
  std::chrono::high_resolution_clock::now()};
  float g_delay{0.f};
  float g_framesPerSecond{0.f};




  static GLfloat vertex[1000];
  int currentIndexVertex=0;
  static GLfloat normals[10000];
  int currentIndexNormals=1;
  static GLfloat faces[10000];
  int currentIndexFaces=1;
  static GLfloat textures[10000];
  int currentIndexTextures=1;
  int numVertex=0;
  int numIndicies=0;
  bool wireFrame=false; 
  bool pointModel=false;
  bool solidModel=true;


////////////////////////////////////////////////////////////////////////////////
// Functions

////////////////////////////////////////////////////////////////////////////////
/// @brief Initialize GL settings
  void
  initialize() {
    glClearColor(0.f, 0.f, 0.4f, 0.f);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
  }

////////////////////////////////////////////////////////////////////////////////
/// @brief Callback for resize of window
///
/// Responsible for setting window size (viewport) and projection matrix.
  void
  resize(GLint _w, GLint _h) {
    g_width = _w;
    g_height = _h;

  // Viewport
    glViewport(0, 0, g_width, g_height);

  // Projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.f, GLfloat(g_width)/g_height, 0.01f, 100.f);
  }

////////////////////////////////////////////////////////////////////////////////
/// @brief Timer function to fix framerate in a GLUT application
/// @param _v Value (not used here)
///
/// Note, this is rudametary and fragile.
  void
  timer(int _v) {
    if(g_window != 0) {
      glutPostRedisplay();

      g_delay = std::max(0.f, 1.f/FPS - g_frameRate);
      glutTimerFunc((unsigned int)(1000.f*g_delay), timer, 0);
    }
    else
      exit(0);
  }

////////////////////////////////////////////////////////////////////////////////
/// @brief Draw function for single frame
  void
  draw() {
    using namespace std::chrono;

  //////////////////////////////////////////////////////////////////////////////
  // Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //////////////////////////////////////////////////////////////////////////////
  // Draw

  // Single directional light
    static GLfloat lightPosition[] = { 0.5f, 1.0f, 1.5f, 0.0f };
    static GLfloat whiteLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    static GLfloat darkLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, darkLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);

  // Camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(10*std::sin(g_theta), 0.f, 10*std::cos(g_theta),
      0.f, 0.f, 0.f, 0.f, 1.f, 0.f);

  // Model of cube
    glColor3f(0.9f, 0.f, 0.f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


//     //Making the Voa
//     GLuint vao;
//     glGenVertexArrays(1,&vao);
//     glBindVertexArray(vao);
    

// //Vertex Buffer Object
//     GLuint vertexBuffer;
//     glGenBuffers(1,&vertexBuffer);
//     glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
//     cout << " numVertex: " << numVertex << endl;
//     glBufferData(GL_ARRAY_BUFFER,numVertex*sizeof(float),vertex, GL_STATIC_DRAW);
//       glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
//     glEnableVertexAttribArray(1);
//     glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);

//     glDrawArrays(GL_TRIANGLES,1,3);
//     glDisableVertexAttribArray(0);

//     // glBindVertexArray(vao);
    


    // GLuint indexBufferObject;
    // glGenBuffers(1,&indexBufferObject);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndicies*sizeof(float),&faces,GL_STATIC_DRAW);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBufferObject);
    // glBindVertexArray(vao);
    // glDrawElements(GL_TRIANGLES,numIndicies,GL_UNSIGNED_INT,(void*)0);
   if(wireFrame){
    glBegin(GL_LINES);
   }
   
   if(pointModel){
    glBegin(GL_POINTS);
    for(int i=1; i<numIndicies; i+=26){
      glNormal3f(vertex[i+1],vertex[],vertex[]);
      glVertex3f(vertex[i],vertex[i+3],vertex[i+6]);
       glVertex3f(vertex[i+9],vertex[i+12],vertex[i+15]);
       glVertex3f(vertex[i+18],vertex[i+21],vertex[i+24]);

   }
   if(solidModel){
    glBegin(GL_TRIANGLES);
     for(int i=1; i<numIndicies; i+=26){
      
      glVertex3f(vertex[i],vertex[i+3],vertex[i+6]);
       glVertex3f(vertex[i+9],vertex[i+12],vertex[i+15]);
       glVertex3f(vertex[i+18],vertex[i+21],vertex[i+24]);


      cout << "vertex: " << vertex[i-2]<< " " <<vertex[i-1]<<" " <<vertex[i] << endl;
         glEnd();
       }
   }
   
   
 

 



  //////////////////////////////////////////////////////////////////////////////
  // Show
    glutSwapBuffers();

  //////////////////////////////////////////////////////////////////////////////
  // Record frame time
    high_resolution_clock::time_point time = high_resolution_clock::now();
    g_frameRate = duration_cast<duration<float>>(time - g_frameTime).count();
    g_frameTime = time;
    g_framesPerSecond = 1.f/(g_delay + g_frameRate);
  //printf("FPS: %6.2f\n", g_framesPerSecond);

  }



////////////////////////////////////////////////////////////////////////////////
/// @brief Callback function for keyboard presses
/// @param _key Key
/// @param _x X position of mouse
/// @param _y Y position of mouse
  void
  keyPressed(GLubyte _key, GLint _x, GLint _y) {
    switch(_key) {
    // Escape key : quit application
      case 27:
      std::cout << "Destroying window: " << g_window << std::endl;
      glutDestroyWindow(g_window);
      g_window = 0;
      break;
      case 80:
      std::cout << "Changing to point model" << endl;
      changeToPoints();
      break;
      
      case 87:
      std::cout<<"Changing to WireModel" << endl;
      changeToWire();
      break;
      
      case 83:
      std::cout << "Changing to Solid Modle" << endl;
      changeToSolid();
      break;
    // Unhandled
      default:
      std::cout << "Unhandled key: " << (int)(_key) << std::endl;
      break;
    }
  }

void changeToPoints(){
    wireFrame=false; 
   pointModel=true;
   solidModel=false;
}

void changeToWire(){
    wireFrame=ture; 
   pointModel=false;
   solidModel=false;
}

void changeToSolid(){
    wireFrame=false; 
   pointModel=false;
   solidModel=true;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Callback function for keyboard presses of special keys
/// @param _key Key
/// @param _x X position of mouse
/// @param _y Y position of mouse
  void
  specialKeyPressed(GLint _key, GLint _x, GLint _y) {
    switch(_key) {
    // Arrow keys
      case GLUT_KEY_LEFT:
      g_theta -= 0.2;
      break;
      case GLUT_KEY_RIGHT:
      g_theta += 0.2;
      break;
    // Unhandled
      default:
      std::cout << "Unhandled special key: " << _key << std::endl;
      break;
    }
  }



//Read File

  void readFile(std::string filename){
    ifstream inFile;
    faces[0]=0;
    currentIndexFaces++;
    if(filename.find("obj") == std::string::npos){
      cout << "File is not supported please provide an obj file" << endl;

    }
    else{

      inFile.open(filename.c_str());
      string line;
      float point;

      while (getline(inFile,line))
      {
    //If it is a comment

        if(line.substr(0,1).compare("#")==0){

        }




        if(line.substr(0,1).compare("f")==0){

          int vertex1;
          int texture1;
          int normal1;
          line = line.substr(2);

          for(int x=0; x<2; x++){
           vertex1 = std::stoi(line.substr(0,line.find("/")));

           line = line.substr(line.find("/")+1);

           texture1 = std::stoi(line.substr(0,line.find("/")));

           line = line.substr(line.find("/")+1);

           normal1 =std::stoi(line.substr(0,line.find(" ")));

           line = line.substr(line.find(" ")+1);

           faces[currentIndexFaces] = vertex[vertex1];
           currentIndexFaces++;
           faces[currentIndexFaces] = textures[texture1];
           currentIndexFaces++;
           faces[currentIndexFaces]= normals[normal1];
           currentIndexFaces++;

         }
         vertex1 = std::stoi(line.substr(0,line.find("/")));
         line = line.substr(line.find("/")+1);
         texture1 = std::stoi(line.substr(0,line.find("/")));
         normal1 =std::stoi(line.substr(line.find("/")+1));
         faces[currentIndexFaces] = vertex[vertex1];
         currentIndexFaces++;
         faces[currentIndexFaces] = textures[texture1];
         currentIndexFaces++;
         faces[currentIndexFaces]= normals[normal1];
         currentIndexFaces++;
         numIndicies++;

       }

      //Case for texture
       else if (line.substr(0,2).compare("vt")==0){
        line = line.substr(3);

        point =  std::stof(line.substr(0,line.find(" ")));
        textures[currentIndexTextures] = point;
        currentIndexTextures++;
        line.substr(line.find(" ")+1);

        point = std::stof(line);
        vertex[currentIndexTextures] = point;
        currentIndexTextures++;
       

      }

       //Case for normals
      else if (line.substr(0,2).compare("vn")==0){

        line = line.substr(3);
        for(int x=0; x<2; x++){
          point =  std::stof(line.substr(0,line.find(" ")));
          normals[currentIndexNormals] = point;
          currentIndexNormals++;
          line.substr(line.find(" ")+1);
        }
        point = std::stof(line);
        vertex[currentIndexNormals] = point;
        currentIndexNormals++;

      }

        //Case for the vertex
      else if(line.substr(0,1).compare("v")==0){

        line = line.substr(2);
        for(int x=0; x< 2; x++){
          point =  std::stof(line.substr(0,line.find(" ")));
          vertex[currentIndexVertex] = point;
          currentIndexVertex++;
          line.substr(line.find(" ")+1);

        }
        point = std::stof(line);
        vertex[currentIndexVertex] = point;
        currentIndexVertex++;
        numVertex++;
      }

      else{
        cout << "not a case" << endl;
      }



      

    }

    inFile.close();
  }
}


////////////////////////////////////////////////////////////////////////////////
// Main

////////////////////////////////////////////////////////////////////////////////
/// @brief main
/// @param _argc Count of command line arguments
/// @param _argv Command line arguments
/// @return Application success status
int
main(int _argc, char** _argv) {
  //////////////////////////////////////////////////////////////////////////////
  // Initialize GLUT Window
  std::cout << "Initializing GLUTWindow" << std::endl;
  // GLUT
  glutInit(&_argc, _argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50, 100);
  glutInitWindowSize(g_width, g_height); // HD size
  g_window = glutCreateWindow("Spiderling: A Rudamentary Game Engine");
  readFile("theBench.obj");

  // GL
  initialize();

  //////////////////////////////////////////////////////////////////////////////
  // Assign callback functions
  std::cout << "Assigning Callback functions" << std::endl;
  glutReshapeFunc(resize);
  glutDisplayFunc(draw);
  glutKeyboardFunc(keyPressed);
  glutSpecialFunc(specialKeyPressed);
  glutTimerFunc(1000/FPS, timer, 0);

  // Start application
  std::cout << "Starting Application" << std::endl;
  glutMainLoop();


  return 0;
}

#if   defined(OSX)
#pragma clang diagnostic pop
#endif
