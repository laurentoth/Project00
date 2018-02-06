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
#include <sstream>
#include <string>
#include <vector>
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


struct vertex_t{
  float xcoor;
  float ycoor;
  float zcoor;
};




struct normals_t{
  float xcoor;
  float ycoor;
  float zcoor;
};

struct textures_t{
  float coorOne;
  float coorTwo;
};


struct faces_t{
  vertex_t one;
  vertex_t two;
  vertex_t three;
  normals_t normal;
  textures_t texture1;
  textures_t texture2;
  textures_t texture3;
};


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

//Menu Ints
  int menuID;
  int submenuLineStyleID;
  int submenuColorID;
  int submenuLineWidthID;
  int submenuPointSizeID;
  int submenuBackgroundColorID;
  int submenuModelID;


//Model Color Coordinates
GLfloat red=0.5;
GLfloat green=0.5;
GLfloat blue=0.5;

//Background Color Coordinates
GLfloat backgroudRed=0.0;
GLfloat backgroundBlue=0.0;
GLfloat backgroundGreen=0.0;
GLfloat backgroundAplha=0.0;

//Point Size
GLfloat pointSize=1.0;

//Line Size
GLfloat lineSize =1.0;

//Line Style
GLshort lineStyle=0xFFFF;


  vector <vertex_t> vertex;
  int currentIndexVertex=0;
  vector <normals_t> normals;
  int currentIndexNormals=0;
  vector<faces_t> faces;
  int currentIndexFaces=0;
  vector<textures_t >textures;
  int currentIndexTextures=0;
  int numVertex=0;
  int numIndicies=0;
  bool wireFrame=false; 
  bool pointModel=false;
  bool solidModel=true;
  bool textureHere=true;


////////////////////////////////////////////////////////////////////////////////
// Functions

////////////////////////////////////////////////////////////////////////////////
/// @brief Initialize GL settings
  void
  initialize() {
    glClearColor(0.f, 0.4f, 0.6f, 0.f);
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
    glClearColor(backgroudRed,backgroundGreen,backgroundBlue,backgroundAplha);

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
    glColor3f(red, green, blue);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glEnable(GL_LINE_SMOOTH);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1,lineStyle);
    glLineWidth(lineSize);
    glPointSize(pointSize);


   

    if(wireFrame){
       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glBegin(GL_LINES);
      for(int i=0; i<currentIndexFaces; i+=1){
        if(currentIndexNormals==0){
          calculateNormal(faces[i].normal.xcoor, faces[i].normal.ycoor,faces[i].normal.zcoor);
        }
        else{
        glNormal3f(faces[i].normal.xcoor, faces[i].normal.ycoor,faces[i].normal.zcoor);
        }
        if(textureHere){
        glTexCoord2f(faces[i].texture1.coorOne,faces[i].texture1.coorTwo);
        }
        glVertex3f(faces[i].one.xcoor,faces[i].one.ycoor,faces[i].one.zcoor);
        if(textureHere){
         glTexCoord2f(faces[i].texture2.coorOne,faces[i].texture2.coorTwo);
         }
        glVertex3f(faces[i].two.xcoor,faces[i].two.ycoor,faces[i].two.zcoor);
        if(textuureHere){
         glTexCoord2f(faces[i].texture3.coorOne,faces[i].texture3.coorTwo);
         }
        glVertex3f(faces[i].three.xcoor,faces[i].three.ycoor,faces[i].three.zcoor);

        
        
      }
       glEnd();
     
    }

    if(pointModel){
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
       glBegin(GL_POINTS);
      for(int i=0; i<currentIndexFaces; i++){
       
           glNormal3f(faces[i].normal.xcoor, faces[i].normal.ycoor,faces[i].normal.zcoor);
        glTexCoord2f(faces[i].texture1.coorOne,faces[i].texture1.coorTwo);
        glVertex3f(faces[i].one.xcoor,faces[i].one.ycoor,faces[i].one.zcoor);
         glTexCoord2f(faces[i].texture2.coorOne,faces[i].texture2.coorTwo);
        glVertex3f(faces[i].two.xcoor,faces[i].two.ycoor,faces[i].two.zcoor);
         glTexCoord2f(faces[i].texture3.coorOne,faces[i].texture3.coorTwo);
        glVertex3f(faces[i].three.xcoor,faces[i].three.ycoor,faces[i].three.zcoor);
          
      }
      glEnd();
    }

      if(solidModel){
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         glBegin(GL_TRIANGLES);
        for(int i=0; i<currentIndexFaces; i++){
         
            glNormal3f(faces[i].normal.xcoor, faces[i].normal.ycoor,faces[i].normal.zcoor);
          glTexCoord2f(faces[i].texture1.coorOne,faces[i].texture1.coorTwo);
         glVertex3f(faces[i].one.xcoor,faces[i].one.ycoor,faces[i].one.zcoor);
          glTexCoord2f(faces[i].texture2.coorOne,faces[i].texture2.coorTwo);
         glVertex3f(faces[i].two.xcoor,faces[i].two.ycoor,faces[i].two.zcoor);
           glTexCoord2f(faces[i].texture3.coorOne,faces[i].texture3.coorTwo);
          glVertex3f(faces[i].three.xcoor,faces[i].three.ycoor,faces[i].three.zcoor);

        }
        glEnd();

      }

      glDisable(GL_LINE_STIPPLE);
      glDisable(GL_LINE_SMOOTH);
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



 void changeToPoints(){
      wireFrame=false; 
      pointModel=true;
      solidModel=false;
    }

    void changeToWire(){
      wireFrame=true; 
      pointModel=false;
      solidModel=false;
    }

    void changeToSolid(){
      wireFrame=false; 
      pointModel=false;
      solidModel=true;
    }


////////////////////////////////////////////////////////////////////////////////
/// @brief Callback function for keyboard presses
/// @param _key Key
/// @param _x X position of mouse
/// @param _y Y position of mouse
    void keyPressed(GLubyte _key, GLint _x, GLint _y) {
      switch(_key) {
    // Escape key : quit application
        case 27:
        std::cout << "Destroying window: " << g_window << std::endl;
        glutDestroyWindow(g_window);
        g_window = 0;
        break;
        case 112:
        std::cout << "Changing to point model" << endl;
        changeToPoints();
        break;

        case 119:
        std::cout<<"Changing to WireModel" << endl;
        changeToWire();
        break;

        case 115:
        std::cout << "Changing to Solid Modle" << endl;
        changeToSolid();
        break;
    // Unhandled
        default:
        std::cout << "Unhandled key: " << (int)(_key) << std::endl;
        break;
      }
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
     
      if(filename.find("obj") == std::string::npos){
        cout << "File is not supported please provide an obj file" << endl;

      }
      else{

        inFile.open(filename.c_str());
        string line;
        GLfloat point;

        while (getline(inFile,line))
        {
    //If it is a comment
          cout << line << endl;

          if(line.substr(0,1).compare("#")==0){

          }




          if(line.substr(0,1).compare("f")==0){

            int vertex1;
            int texture1;
            int normal1;
            line = line.substr(2);
            faces_t newFace;
           
            for(int x=0; x<2; x++){
             vertex1 = std::stoi(line.substr(0,line.find("/")));
              line = line.substr(line.find("/")+1);
            
            if(textureHere){
             texture1 = std::stoi(line.substr(0,line.find("/")));
            
             }
              line = line.substr(line.find("/")+1);

             normal1 =std::stoi(line.substr(0,line.find(" ")));

             line = line.substr(line.find(" ")+1);
           

             if(x==0){
               newFace.one = vertex[vertex1-1];
               if(textureHere){
               newFace.texture1=textures[texture1-1];
               }
               newFace.normal=normals[normal1-1];
             }
             if(x==1){
              newFace.two=vertex[vertex1-1];
              if(textureHere){
              newFace.texture2=textures[texture1-1];
              }
            }



          }
          vertex1 = std::stoi(line.substr(0,line.find("/")));
          line = line.substr(line.find("/")+1);
          if(textureHere){
          texture1 = std::stoi(line.substr(0,line.find("/")));
            newFace.texture3=textures[texture1-1];
          }
          normal1 =std::stoi(line.substr(line.find("/")+1));
         

         
          newFace.three = vertex[vertex1-1];
        


          faces.push_back(newFace);
          currentIndexFaces++;
          numIndicies++;
          

          
        }

      //Case for texture
        else if (line.substr(0,2).compare("vt")==0){
          textureHere=true;
          textures_t newText;
          line = line.substr(3);
          std::istringstream in(line);       
          in>>newText.coorOne;   
          in>>newText.coorTwo;
          textures.push_back(newText);
          currentIndexTextures++;

        }

       //Case for normals
        else if (line.substr(0,2).compare("vn")==0){
          normals_t newNormal;
          line = line.substr(3);
          std::istringstream in(line);
          for(int x=0; x<2; x++){
          
            if(x==0){
              in >>newNormal.xcoor;
            }
            if(x==1){
              in >>newNormal.ycoor;
            }

           
          }
       
         
          in>>newNormal.zcoor;
          normals.push_back(newNormal);
          currentIndexNormals++;

        }

        //Case for the vertex
        else if(line.substr(0,1).compare("v")==0){
          vertex_t newVertex;
          line = line.substr(2);
          std::istringstream in(line);
          for(int x=0; x< 2; x++){
            if(x==0){
              in>>newVertex.xcoor;
            }
            if(x==1){
              in>>newVertex.ycoor;

          }
        }
         
          in>>newVertex.zcoor;
          vertex.push_back(newVertex);
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

  void mainMenuHandler(int choice){
    switch (choice){
      case 0:
      cout << "Color Menu" << endl;
      break;

      case 1:
      cout<< "Line Width" <<endl;
      break;

      case 2:
      cout << "Changing Line Style"<< endl;
      break;


      default:
      cout << "Le default " << endl;
      break;
    }
  }
  
void submenuColor(int choice){

  switch(choice){
    case 0: 
      cout << "Red" << endl;
      red =1.0;
      blue =0.0;
      green =0.0;
      break;
      case 1: 
      cout << "Orange" << endl;
      red =1.0;
      green =0.5;
      blue =0.0;
      break;
      case 2: 
      cout << "Yellow" << endl;
      green = 1.0;
      blue = 0.0;
      red =1.0;
      break;
      case 3: 
      cout << "Green" << endl;
      red=0.0;
      blue=0.0;
      green =1.0;
      break;
      case 4: 
      cout << "Blue" << endl;
      red =0.0;
      blue=1.0;
      green=0.0;
      break;
      case 5: 
      cout << "Purple" << endl;
      red=1.0;
      blue=1.0;
      green=0.0;
      break;
    case 6:
      cout << "Grey" << endl;
      red=0.5;
      green =0.5;
      blue =0.5;
      break;
}
}
  
 void submenuPointSize(int choice){
   
   switch(choice){
     case 0:
       cout << "point size 1.0" << endl;
       pointSize=1.0;
       break;
       
     case 1:
       cout << "Point Size 2.0"<< endl;
       pointSize=2.0;
       break;
       
     case 2:
cout << "Point Size 3.0" << endl;
       pointSize=3.0;
       break;
       
     case 3:
       cout << "Point Size 4.0" << endl;
       pointSize=4.0;
       break;
       
     case 4:
      cout << "Point Size 5.0" << endl;
       pointSize=5.0;
       break;
       
     case 5:
cout << "Point Size 6.0" << endl;
       pointSize=6.0;
       break;
    case 6:
    cout << "Point Size 0.1 " << endl;
    pointSize=0.1;
    break;

    case 7:
    cout << "Point Size 0.5" << endl;
    pointSize=0.5;
    break;
       
     default:
       cout << "Point Size 2.0" << endl;
       pointSize=2.0;
       break;
    
       
   }
   
 }


void submenuLineWidth(int choice){
   
   switch(choice){
     case 0:
       cout << "Line size 1.0" << endl;
       lineSize=1.0;
       break;
       
     case 1:
       cout << "Line Size 2.0"<< endl;
       lineSize=2.0;
       break;
       
     case 2:
cout << "Line Size 3.0" << endl;
       lineSize=3.0;
       break;
       
     case 3:
       cout << "Line Size 4.0" << endl;
       lineSize=4.0;
       break;
       
     case 4:
      cout << "Line Size 5.0" << endl;
       lineSize=5.0;
       break;
       
     case 5:
cout << "Line Size 6.0" << endl;
       lineSize=6.0;
       break;
    case 6:
    cout << "Line Size 0.1 " << endl;
    lineSize=0.1;
    break;

    case 7:
    cout << "Line Size 0.5" << endl;
    lineSize=0.5;
    break;
       
     default:
       cout << "Line Size 2.0" << endl;
       lineSize=2.0;
       break;
    
       
   }
   
 }





 void submenuLineStyle(int choice){
   

switch(choice){
  case 0:
  cout << "Line Style changed to Dash-Dot" << endl;
  lineStyle = 0x1C47;
  break;

  case 1:
  cout << "Line Style changed to Dashed" << endl;
  lineStyle = 0x00FF;
  break;

  case 2:
  cout << "Line Style Changed to Dotted" << endl;
  lineStyle = 0x0101;
  break;

  case 3:
  cout << "Line Style changed to solid"<< endl;
  lineStyle=0xFFFF;
  break;
}

 }


void submenuBackgroundColor(int choice){

  switch(choice){
    case 0: 
      cout << "Red" << endl;
      backgroudRed =1.0;
      backgroundBlue =0.0;
      backgroundGreen =0.0;
      break;
      case 1: 
      cout << "Orange" << endl;
      backgroudRed =1.0;
      backgroundGreen =0.5;
      backgroundBlue =0.0;
      break;
      case 2: 
      cout << "Yellow" << endl;
      backgroundGreen = 1.0;
      backgroundBlue = 0.0;
      backgroudRed =1.0;
      break;
      case 3: 
      cout << "Green" << endl;
      backgroudRed=0.0;
      backgroundBlue=0.0;
      backgroundGreen =1.0;
      break;
      case 4: 
      cout << "Blue" << endl;
      backgroudRed =0.0;
      backgroundBlue=1.0;
      backgroundGreen=1.0;
      break;
      case 5: 
      cout << "Purple" << endl;
      backgroudRed=1.0;
      backgroundBlue=1.0;
      backgroundGreen=0.0;
      break;
    case 6:
      cout << "Black" << endl;
      backgroudRed=0.0;
      backgroundGreen =0.0;
      backgroundBlue =0.0;
      break;
}
}

void submenuModel(int choice){

  switch(choice){
    case 0:
    cout << "Skull Model" << endl;
     vertex.clear();
  currentIndexVertex=0;
   normals.clear();
  currentIndexNormals=0;
  faces.clear();
  currentIndexFaces=0;
  textures.clear();
   currentIndexTextures=0;
   numVertex=0;
   numIndicies=0;
      textureHere=false;
  
    readFile("skull.obj");
    break;

    case 1:
    cout << "Cube Model" << endl;
     vertex.clear();
  currentIndexVertex=0;
  normals.clear();
  currentIndexNormals=0;
  faces.clear();
  currentIndexFaces=0;
  textures.clear();
   currentIndexTextures=0;
   numVertex=0;
   numIndicies=0;
      textureHere=false;
    readFile("cube.obj");
    break;

    case 2:
    cout << "Bench Model" << endl;
     vertex.clear();
  currentIndexVertex=0;
  normals.clear();
  currentIndexNormals=0;
  faces.clear();
  currentIndexFaces=0;
  textures.clear();
   currentIndexTextures=0;
   numVertex=0;
   numIndicies=0;
      textureHere=false;
    readFile("theBench.obj");
      break;

       case 3:
    cout << "Tree Model" << endl;
     vertex.clear();
  currentIndexVertex=0;
  normals.clear();
  currentIndexNormals=0;
  faces.clear();
  currentIndexFaces=0;
  textures.clear();
   currentIndexTextures=0;
   numVertex=0;
   numIndicies=0;
      textureHere=false;
    readFile("tree.obj");
      break;
  }
}

Vector<GLfloat>  calculateNormal(Vertex_t one, Vertex_t two, Vertex_t three){
  Vector<GLfloat> normal;
  Vector<Glfloat> U;
  Vector<Glfloat> V;
  U.push_back(two.xcoor-one.xcoor);
  U.push_back(two.ycoor-one.ycoor);
  U.push_back(two.zcoor-one.zcoor);
  V.push_back(three.xcoor-one.xcoor);
  V.push_back(three.ycoor-one.ycoor);
  V.push_back(three.zcoor-one.zcoor);
  
  normal.push_back((U[1]*V[2])-(U[2]*V[2]));
  normal.push_back((U[2]*V[0])-(U[0]*V[2]));
  normal.push_back((U[0]*V[1])-(U[1]*V[0]));
  
  return normal;
  
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

  readFile("skull.obj");


  // GL
  initialize();

  
    submenuColorID = glutCreateMenu(submenuColor);
   glutAddMenuEntry("Red",0);
    glutAddMenuEntry("Orange",1);
    glutAddMenuEntry("Yellow",2);
     glutAddMenuEntry("Green",3);
     glutAddMenuEntry("Blue",4);
      glutAddMenuEntry("Purple",5);
      glutAddMenuEntry("Grey",6);

      submenuBackgroundColorID = glutCreateMenu(submenuBackgroundColor);
   glutAddMenuEntry("Red",0);
    glutAddMenuEntry("Orange",1);
    glutAddMenuEntry("Yellow",2);
     glutAddMenuEntry("Green",3);
     glutAddMenuEntry("Blue",4);
      glutAddMenuEntry("Purple",5);
      glutAddMenuEntry("Black",6);


    submenuLineWidthID= glutCreateMenu(submenuLineWidth);
    glutAddMenuEntry("0.1",6);
    glutAddMenuEntry("0.5",7);
   glutAddMenuEntry("1.0",0);
    glutAddMenuEntry("2.0",1);
    glutAddMenuEntry("3.0",2);
     glutAddMenuEntry("4.0",3);
     glutAddMenuEntry("5.0",4);
      glutAddMenuEntry("6.0",5);


       submenuPointSizeID= glutCreateMenu(submenuPointSize);
    glutAddMenuEntry("0.1",6);
    glutAddMenuEntry("0.5",7);
   glutAddMenuEntry("1.0",0);
    glutAddMenuEntry("2.0",1);
    glutAddMenuEntry("3.0",2);
     glutAddMenuEntry("4.0",3);
     glutAddMenuEntry("5.0",4);
      glutAddMenuEntry("6.0",5);

    submenuLineStyleID = glutCreateMenu(submenuLineStyle);
     glutAddMenuEntry("Dash-dot",0);
    glutAddMenuEntry("Dashed",1);
    glutAddMenuEntry("Dotted",2);
    glutAddMenuEntry("Solid",3);

 submenuModelID = glutCreateMenu(submenuModel);
     glutAddMenuEntry("Skull",0);
    glutAddMenuEntry("Cube",1);
    glutAddMenuEntry("Bench",2);
    glutAddMenuEntry("Tree",3);
   

 
 menuID =glutCreateMenu(mainMenuHandler);
   
  glutAddSubMenu("Change Color",submenuColorID);
  glutAddSubMenu("Change Background Color",submenuBackgroundColorID);
  glutAddSubMenu("Line Width",submenuLineWidthID);
  glutAddSubMenu("Change Line Style",submenuLineStyleID);
  glutAddSubMenu("Change Point Size",submenuPointSizeID);
  glutAddSubMenu("Change Model",submenuModelID);
  
  
 
  glutAttachMenu(GLUT_RIGHT_BUTTON);



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
