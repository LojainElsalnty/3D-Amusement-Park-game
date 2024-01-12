//
//  main.cpp
//  3D game
//
//  Created by Login Elsalnty on 17/11/2023.
//
#define GL_SILENCE_DEPRECATION
#include <math.h>
#include <stdio.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <cstdlib>
#include <iostream>

// for Sound
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)
float angle = 0.0f;


class Vector3f {
public:
    float x, y, z;

    Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
        x = _x;
        y = _y;
        z = _z;
    }

    Vector3f operator+(const Vector3f &v) const {
        return Vector3f(x + v.x, y + v.y, z + v.z);
    }

    Vector3f operator-(const Vector3f &v) const {
        return Vector3f(x - v.x, y - v.y, z - v.z);
    }

    Vector3f operator*(float n) const {
        return Vector3f(x * n, y * n, z * n);
    }

    Vector3f operator/(float n) const {
        return Vector3f(x / n, y / n, z / n);
    }

    Vector3f unit() {
        return *this / sqrt(x * x + y * y + z * z);
    }

    Vector3f cross(Vector3f v) {
        return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }
};

class Camera {
public:
    Vector3f eye, center, up;

    Camera(float eyeX = 5.0f, float eyeY = 5.0f, float eyeZ = 15.0f, float centerX = 5.0f, float centerY = 1.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
        eye = Vector3f(eyeX, eyeY, eyeZ);
        center = Vector3f(centerX, centerY, centerZ);
        up = Vector3f(upX, upY, upZ);
    }

    void moveX(float d) {
        Vector3f right = up.cross(center - eye).unit();
        eye = eye + right * d;
        center = center + right * d;
//        std::cout << "eye, " << eye.x << std::endl;
//        std::cout <<"center,"<< center.x << std::endl;
    }
    

    void moveY(float d) {
        eye = eye + up.unit() * d;
        center = center + up.unit() * d;
    }

    void moveZ(float d) {
        Vector3f view = (center - eye).unit();
        eye = eye + view * d;
        center = center + view * d;
    }

    void rotateX(float a) {
        Vector3f view = (center - eye).unit();
        Vector3f right = up.cross(view).unit();
        view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
        up = view.cross(right);
        center = eye + view;
    }

    void rotateY(float a) {
        Vector3f view = (center - eye).unit();
        Vector3f right = up.cross(view).unit();
        view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
        right = view.cross(up);
        center = eye + view;
    }
    void frontView(){
//        std::cout << "eyeX, " << eye.x << std::endl;
//        std::cout <<"centerX,"<< center.x << std::endl;
//        
//        std::cout << "eyeY, " << eye.y << std::endl;
//        std::cout <<"centerY,"<< center.y << std::endl;
//        
//        std::cout << "eyeZ, " << eye.z << std::endl;
//        std::cout <<"centerZ,"<< center.z << std::endl;
//        eye.x=5;
//        center.x=5;
//        eye.y=5.62883;
//        center.y=1.62883;
//        eye.z=15.4831;
//        center.z=0.483117;
        eye.x=5;
        center.x=5;
        up.x=0;
        eye.y=3.01356;
        center.y=3.01417;
        up.y=1;
        eye.z=16.7082;
        center.z=15.7082;
        up.z=0;
        
        
    }
    void topView(){
//        std::cout << "eyeX, " << eye.x << std::endl;
//        std::cout <<"centerX,"<< center.x << std::endl;
//        std::cout <<"upX,"<< up.x << std::endl;
//        
//        std::cout << "eyeY, " << eye.y << std::endl;
//        std::cout <<"centerY,"<< center.y << std::endl;
//        std::cout <<"upY,"<< up.y << std::endl;
//        
//        std::cout << "eyeZ, " << eye.z << std::endl;
//        std::cout <<"centerZ,"<< center.z << std::endl;
//        std::cout <<"upZ,"<< up.z << std::endl;
        
        eye.x=4.5;
        center.x=4.5;
        up.x=0;
        eye.y=14.944;
        center.y=13.9627;
        up.y=0.19256;
        eye.z=4.91331;
        center.z=4.72075;
        up.z=-0.981285;
        
    }
    void sideView(){
//        std::cout << "eyeX, " << eye.x << std::endl;
//        std::cout <<"centerX,"<< center.x << std::endl;
//        std::cout <<"upX,"<< up.x << std::endl;
//        
//        std::cout << "eyeY, " << eye.y << std::endl;
//        std::cout <<"centerY,"<< center.y << std::endl;
//        std::cout <<"upY,"<< up.y << std::endl;
//        
//        std::cout << "eyeZ, " << eye.z << std::endl;
//        std::cout <<"centerZ,"<< center.z << std::endl;
//        std::cout <<"upZ,"<< up.z << std::endl;
        
        eye.x=20.4252;
        center.x=19.4425;
        up.x=-0.184966;
        eye.y=8.24166;
        center.y=8.05683;
        up.y=0.982722;
        eye.z=4.71984;
        center.z=4.73652;
        up.z= -0.00671857;
        
    }

    void look() {
        gluLookAt(
            eye.x, eye.y, eye.z,
            center.x, center.y, center.z,
            up.x, up.y, up.z
        );
        
    }
    
};

Camera camera;
bool upPressed = false;
bool downPressed = false;
bool leftPressed = false;
bool rightPressed = false;
float babyX =1.0f;
float babyY = 0.0f;
float babyZ =3.0f;
float movementSpeed = 0.1f;
int babyDirection=4;  // spaceship face is directed to up at first of the game
float babyROT = 0.0f;
bool objectsAnim= false;
float angleObjectsAnim = 0.0f;
float goalAnim=0.0f;
int timeAnim=1;
bool goalCollision=false;
float scaleValue1=0.0f;
float scaleValue2=0.0f;
bool scaleValue = false;
char* p0s[20];
int playerScore=0;
int lives= 5;
int gameTime = 60; // for now game time is just 60 seconds
int secondsInt=0;
int secondsDayNight=0;
std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
enum GameState { GAME_PLAYING, GAME_OVER };
GameState gameState;


bool day=true;
int countDayNight=0;
std::chrono::high_resolution_clock::time_point lastSwitchTime;

// Music
Mix_Music* bgm ;
Mix_Chunk* soundEffect;
int channel;
std::chrono::high_resolution_clock::time_point soundTime;




void drawFilledCylinder(GLfloat radius, GLfloat height, GLint slices, GLint stacks);
void playBackgroundSound(){
    // Initialize SDL
     if (SDL_Init(SDL_INIT_AUDIO) < 0) {
         printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
         return;
     }

     // Initialize SDL_mixer
     if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
         printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
         return;
     }

     // Load music
     Mix_Music* bgm = Mix_LoadMUS("/Users/loginelsalnty/Desktop/Semester 7 guc/Graphics/Assignments/3D game/audio/background.mp3");
     if (bgm == NULL) {
         printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
         return;
     }

     // Play music
     Mix_PlayMusic(bgm, -1);
    
}
void  resumeBackgroundSound(){

    Mix_HaltChannel(channel);
    
}
void playAnimationSound(){
    // Initialize SDL
     if (SDL_Init(SDL_INIT_AUDIO) < 0) {
         printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
         return;
     }

     // Initialize SDL_mixer
     if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
         printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
         return;
     }

     // Load music
     Mix_Music* bgm = Mix_LoadMUS("/Users/loginelsalnty/Desktop/Semester 7 guc/Graphics/Assignments/3D game/audio/babyShark.mp3");
     if (bgm == NULL) {
         printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
         return;
     }

     // Play music
     Mix_PlayMusic(bgm, -1);
    
}
void playGoalCollisionSound(){
    // Initialize SDL
     if (SDL_Init(SDL_INIT_AUDIO) < 0) {
         printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
         return;
     }

     // Initialize SDL_mixer
     if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
         printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
         return;
     }

     // Load music
     Mix_Music* bgm = Mix_LoadMUS("/Users/loginelsalnty/Desktop/Semester 7 guc/Graphics/Assignments/3D game/audio/babyLaughing.mp3");
     if (bgm == NULL) {
         printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
         return;
     }

     // Play music
     Mix_PlayMusic(bgm, -1);
    
}

void drawRightWall(double thickness) {
    glPushMatrix();
    if(day){
        glColor3f(0.1f, 0.55f, 1.0f);  // Set baby blue color
    }else{
        glColor3f(0.0f, 0.2f, 0.6f); // Night
    }
    glTranslated(5, 5 * thickness, 5);     // x
    glScaled(1.0, thickness, 1.0);
    glutSolidCube(10);                     // 2x
    glPopMatrix();
    
    glPushMatrix();
//    glScaled(0.5, 1, 1);
   // glScaled(1, 0.5, 1);
    glScaled(1, 1, 0.5);
    // clouds
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    //    x,-z,y
    glTranslated(7.3, -0.05, 7.5+8);     // x
    glScaled(1.0, 5*thickness, 1.0);
    glutSolidSphere(1, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    //    x,-z,y
    glTranslated(6.0, -0.05,  7.5+8);     // x
    glScaled(1.0, 5*thickness, 1.0);
    glutSolidSphere(0.8, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    //    x,-z,y
    glTranslated(8.5, -0.05,  7.5+8);     // x
    glScaled(1.0, 5*thickness, 1.0);
    glutSolidSphere(0.8, 32, 32);
    glPopMatrix();
    
    glPopMatrix();
    
    glPushMatrix();
//    glScaled(0.5, 1, 1);
   // glScaled(1, 0.5, 1);
    glScaled(1, 1, 0.5);
    // clouds
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    //    x,-z,y
    glTranslated(7.3-3, -0.05, 7.5+7);     // x
    glScaled(1.0, 5*thickness, 1.0);
    glutSolidSphere(1, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    //    x,-z,y
    glTranslated(6.0-3, -0.05,  7.5+7);     // x
    glScaled(1.0, 5*thickness, 1.0);
    glutSolidSphere(0.8, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    //    x,-z,y
    glTranslated(8.5-3, -0.05,  7.5+7);     // x
    glScaled(1.0, 5*thickness, 1.0);
    glutSolidSphere(0.8, 32, 32);
    glPopMatrix();
    
    glPopMatrix();
    
    
}
void drawLeftWall(double thickness) {
    glPushMatrix();
    if(day){
        glColor3f(0.1f, 0.55f, 1.0f);  // Set baby blue color
    }else{
        glColor3f(0.0f, 0.2f, 0.6f); // Night
    }
    glTranslated(5, 5 * thickness, 5);     // x
    glScaled(1.0, thickness, 1.0);
    glutSolidCube(10);                     // 2x
    glPopMatrix();
    
    glPushMatrix();
    glScaled(0.5, 1, 1);
    
    // clouds
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); // white
    //    y,-z,x
    glTranslated(8+7, -0.05, 8.0);
    glScaled(1.0, 5*thickness, 1.0);
    glutSolidSphere(0.8, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); // white
    //    y,-z,x
    glTranslated(8+7, -0.05, 6.7);
    glScaled(1.0, 5*thickness, 1.0);
    glutSolidSphere(1, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); // white
    //    y,-z,x
    glTranslated(8+7, -0.05, 6.0);
    glScaled(1.0, 5*thickness, 1.0);
    glutSolidSphere(0.8, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); // white
    //    y,-z,x
    glTranslated(8+6, -0.05, 8.0-3);
    glScaled(1.0, 5*thickness, 1.0);
    glutSolidSphere(0.8, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); // white
    //    y,-z,x
    glTranslated(8+6, -0.05, 6.7-3);
    glScaled(1.0, 5*thickness, 1.0);
    glutSolidSphere(1, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); // white
    //    y,-z,x
    glTranslated(8+6, -0.05, 6.0-3);
    glScaled(1.0, 5*thickness, 1.0);
    glutSolidSphere(0.8, 32, 32);
    glPopMatrix();
    
    glPopMatrix();
    
    
}
void drawGround(double thickness) {
    glPushMatrix();
    // Set green color for the grass
    glColor3f(0.4f, 0.8f, 0.3f);
    glTranslated(5, 5 * thickness, 5);     // x
    glScaled(1.0, thickness, 1.0);
    glutSolidCube(10);                     // 2x
    glPopMatrix();
}



void drawFrontWall(double thickness) {
   
    glPushMatrix();
    glRotated(-90, 1.0, 0.0, 0.0);
    
    glPushMatrix();
    if(day){
        glColor3f(0.1f, 0.55f, 1.0f);  // Set baby blue color
    }else{
        glColor3f(0.0f, 0.2f, 0.6f); // Night
    }
    
    glTranslated(5, 5 * thickness, 5);     // x
    glScaled(1.0, thickness, 1.0);
    glutSolidCube(10);                     // 2x
    glPopMatrix();
    
    
    glPushMatrix();
    
    if(day){
        glColor3f(1.0f, 0.8f, 0.2f); // Bright yellow-orange
    }else{
        glColor3f(0.8f, 0.8f, 0.8f); // Pale gray
    }
    //    x,-z,y
    glTranslated(8, -0.05, 8.0);     // x
    glScaled(1.0, 5*thickness, 1.0);
   // glutSolidS(10); // 2x
    glutSolidSphere(1, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(9, 0, 1);
    glRotated(-90, 0, 1, 0);
   
    glScaled(0.5, 1, 1);
    
    // clouds
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); // white
    //    y,-z,x
    glTranslated(8+7, -0.05, 8.0);
    glScaled(1.0, 5*thickness, 1.0);
    glutSolidSphere(0.8, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); // white
    //    y,-z,x
    glTranslated(8+7, -0.05, 6.7);
    glScaled(1.0, 5*thickness, 1.0);
    glutSolidSphere(1, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); // white
    //    y,-z,x
    glTranslated(8+7, -0.05, 6.0);
    glScaled(1.0, 5*thickness, 1.0);
    glutSolidSphere(0.8, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); // white
    //    y,-z,x
    glTranslated(8+6, -0.05, 8.0-3);
    glScaled(1.0, 5*thickness, 1.0);
    glutSolidSphere(0.8, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); // white
    //    y,-z,x
    glTranslated(8+6, -0.05, 6.7-3);
    glScaled(1.0, 5*thickness, 1.0);
    glutSolidSphere(1, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); // white
    //    y,-z,x
    glTranslated(8+6, -0.05, 6.0-3);
    glScaled(1.0, 5*thickness, 1.0);
    glutSolidSphere(0.8, 32, 32);
    glPopMatrix();
    
    glPopMatrix();
    
    glPopMatrix();
}
void drawBoundaries(){
    
    drawGround(0.02);

    

    // front wall
    drawFrontWall(0.02);
    

    //// Set baby blue color
    glColor3f(0.2f, 0.6f, 1.0f);
    glPushMatrix();
    glRotated(90, 0, 0, 1.0);
    drawLeftWall(0.02);
    glPopMatrix();
    
    glPushMatrix();
    // Set baby blue color
    glColor3f(0.2f, 0.6f, 1.0f);
    glRotated(-90, 1.0, 0.0, 0.0);
    glTranslated(10, 0, 0);     //2x
    glRotated(-90, 0.0, 0.0, 1.0);
    drawRightWall(0.02);
    glPopMatrix();
    
}
void drawTableLeg(double thick, double len) {
    glPushMatrix();
    glTranslated(0, len / 2, 0);
    glScaled(thick, len, thick);
    glutSolidCube(1.0);
    glPopMatrix();
}
void drawJackPart() {
    glPushMatrix();
    glColor3f(1.0f, 0.5f, 0.6f);
    glColor3f(0.2f, 0.2f, 0.7f);
    glScaled(0.2, 0.2, 1.5);
    glutSolidSphere(1, 15, 15);
    glPopMatrix();
    glPushMatrix();
    glColor4f(0.7f, 0.7f, 1.0f, 0.5f);
    glTranslated(0, 0, 1.5);
    glutSolidSphere(0.5, 15, 15);
    glTranslated(0, 0, -2.7);
    glutSolidSphere(0.5, 15, 15);
    glPopMatrix();
}
void drawJack() {
    // Lower Part
    glPushMatrix();
//    glColor3f(0.8f, 0.4f, 0.9f);
    glColor3f(0.9f, 0.9f, 0.9f);
    glTranslatef(8.0, 0.0, 2.0);
    glRotated(-90, 1.0, 0.0, 0.0);
    drawFilledCylinder(0.75, 0.5, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    if(objectsAnim){
//        std::cout << "(objectsAnim) " <<  objectsAnim << std::endl;
        glTranslatef(8.0, 2.0, 2.0);  // Translate to the center of rotation
//        std::cout << "(angleObjectsAnim) " <<  angleObjectsAnim << std::endl;
        glRotatef(angleObjectsAnim, 0, 1, 0);
        glTranslatef(-8.0, -2.0, -2.0);
    }
    glPushMatrix();
    glTranslated(8.0, 2.0 , 2.0);
    glRotated(90, 0, 0, 1);
    glScaled(1.0, 1.0, 1.0);
    
    
    glPushMatrix();
    drawJackPart();
    glRotated(90.0, 0, 1, 0);
    drawJackPart();
    glRotated(90.0, 1, 0, 0);
    drawJackPart();
    glPopMatrix();
    
    glPopMatrix();
    glPopMatrix();
}
void drawBench(double topWid, double topThick, double legThick, double legLen){
    glPushMatrix();
    glTranslated(1.0, 0.0, 6.0);
    glColor3f(0.65f, 0.27f, 0.07f);
    
    glPushMatrix();
    glTranslated(0, legLen, 0);
    glScaled(topWid, topThick, topWid*2);
    glutSolidCube(1.0);
    glPopMatrix();

    double dist = 0.95*topWid / 2.0 - legThick / 2.0;
    glPushMatrix();
    glTranslated(dist, 0, dist);
    drawTableLeg(legThick, legLen);
    glTranslated(0, 0, -2 * dist);
    drawTableLeg(legThick, legLen);
    glTranslated(-2 * dist, 0, 2 * dist);
    drawTableLeg(legThick, legLen);
    glTranslated(0, 0, -2 * dist);
    drawTableLeg(legThick, legLen);
    glPopMatrix();
    
    glPopMatrix();
}
void drawFilledCylinder(GLfloat radius, GLfloat height, GLint slices, GLint stacks) {
    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    
    gluCylinder(quadric, radius, radius, height, slices, stacks);
    
    glPushMatrix();
    glTranslatef(0.0, 0.0, height);
    gluDisk(quadric, 0.0, radius, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    gluDisk(quadric, 0.0, radius, slices, stacks);
    glPopMatrix();

    gluDeleteQuadric(quadric);
}
void drawSwingRide() {

    // Central Pole
    // Lower Part
    glColor3f(0.8f, 0.4f, 0.9f);
    glPushMatrix();
    glTranslatef(2.0, 0.0, 2.0);
    glRotated(-90, 1.0, 0.0, 0.0);
    drawFilledCylinder(0.5, 4, 32, 32);
    glPopMatrix();
    glPushMatrix();
    if(objectsAnim){
//        std::cout << "(objectsAnim) " <<  objectsAnim << std::endl;
        glTranslatef(2.0, 0.0, 2.0);  // Translate to the center of rotation
//        std::cout << "(angleObjectsAnim) " <<  angleObjectsAnim << std::endl;
        glRotatef(angleObjectsAnim, 0, 1, 0);
        glTranslatef(-2.0, 0.0, -2.0);
    }

    // Upper Part
    glColor3f(0.8f, 0.4f, 0.9f);
    glPushMatrix();
    glTranslatef(2.0, 4.0, 2.0);
    glRotated(-90, 1.0, 0.0, 0.0);
    drawFilledCylinder(2, 0.5, 32, 32);
    glPopMatrix();
    
    // Draw the chains and seats
    
    // Draw the chains
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        // Calculate the position of the chain
        float xPosition = 1 + 2 * i;
        float zPosition = 1 + 2 * j;
        
          if(i==0){
              xPosition+=0.2;
              
          }else{
              xPosition+=0.2;
              
          }
          
        // Draw the chain
        glPushMatrix();
        glColor3f(1.0f, 0.9f, 1.0f);
        glTranslated(xPosition, 4, zPosition);
        glRotatef(90, 1, 0, 0);

        if (i == 0) {
          glRotatef(-10, 0, 1, 0); // Rotate the chain slightly to the left
        } else {
          glRotatef(10, 0, 1, 0); // Rotate the chain slightly to the right
        }

        drawFilledCylinder(0.05, 2, 10, 10);
        glPopMatrix();
          if(i==1){
              xPosition+=0.8;
          }
//          if(j==0){
//              zPosition+=0.15;
//          }else{
//              zPosition+=0.05;
//          }

        // Draw the seat
        glPushMatrix();
        glTranslated(xPosition - 0.4, 2, zPosition + 0.2);
        glScaled(0.5, 0.2, 0.5);
        glutSolidCube(1);
        glPopMatrix();

        // Draw the seat back
        glPushMatrix();
        glTranslated(xPosition - 0.4, 2.2, zPosition );
        glScaled(0.5, 0.2, 0.1);
        glutSolidCube(1);
        glPopMatrix();

        // Draw the seat left arm
        glPushMatrix();
        glTranslated(xPosition -0.6, 2.2, zPosition + 0.2);
        glScaled(0.1, 0.2, 0.5);
        glutSolidCube(1);
        glPopMatrix();

        // Draw the seat right arm
        glPushMatrix();
        glTranslated(xPosition - 0.2, 2.2, zPosition + 0.2);
        glScaled(0.1, 0.2, 0.5);
        glutSolidCube(1);
        glPopMatrix();
      }
    }
    
    for (int j = 0; j < 2; ++j) {
      // Calculate the position of the chain
      float xPosition =2;
      float zPosition = 1 + 2 * j;
        
        if(j==0){
            zPosition-=0.2;
        }else{
            zPosition+=0.2;
        }

      // Draw the chain
      glPushMatrix();
      glColor3f(1.0f, 0.9f, 1.0f);
      glTranslated(xPosition, 4, zPosition);
      glRotatef(90, 1, 0, 0);

      if (j == 0) {
        glRotatef(10, 0, 0, 0); // Rotate the chain slightly to the left
      } else {
        glRotatef(-10, 0, 0, 0); // Rotate the chain slightly to the right
      }

      drawFilledCylinder(0.05, 2, 10, 10);
      glPopMatrix();
//        if(i==1){
//            xPosition+=0.8;
//        }
        if(j==1){
            zPosition+=0.35;
        }else{
            zPosition-=0.35;
        }
        xPosition+=0.3;

      // Draw the seat
      glPushMatrix();
      glTranslated(xPosition - 0.2, 2, zPosition + 0.2);
      glScaled(0.5, 0.2, 0.5);
      glutSolidCube(1);
      glPopMatrix();

      // Draw the seat back
      glPushMatrix();
      glTranslated(xPosition - 0.2, 2.2, zPosition );
      glScaled(0.5, 0.2, 0.1);
      glutSolidCube(1);
      glPopMatrix();

      // Draw the seat left arm
      glPushMatrix();
      glTranslated(xPosition -0.4, 2.2, zPosition + 0.2);
      glScaled(0.1, 0.2, 0.5);
      glutSolidCube(1);
      glPopMatrix();

      // Draw the seat right arm
      glPushMatrix();
      glTranslated(xPosition , 2.2, zPosition + 0.2);
      glScaled(0.1, 0.2, 0.5);
      glutSolidCube(1);
      glPopMatrix();
    }
    
    // Draw the chains
    for (int i = 0; i < 2; ++i) {
//      for (int j = 0; j < 2; ++j) {
        // Calculate the position of the chain
        float xPosition = 1 + 2 * i;
       // float zPosition = 1 + 2 * j;
          float zPosition = 2;
          
        if(i==0){
            xPosition-=0.2;
        }else{
            xPosition+=0.2;
        }
  
        // The chains in between
        glPushMatrix();
        glColor3f(1.0f, 0.9f, 1.0f);
        glTranslated(xPosition, 4, zPosition);
        glRotatef(90, 1, 0, 0);

        if (i == 0) {
          glRotatef(-10, 0, 1, 0); // Rotate the chain slightly to the left
        } else {
          glRotatef(10, 0, 1, 0); // Rotate the chain slightly to the right
        }

        drawFilledCylinder(0.05, 2, 10, 10);
        glPopMatrix();
          if(i==1){
              xPosition+=0.8;
          }

        // Draw the seat
        glPushMatrix();
        glTranslated(xPosition - 0.4, 2, zPosition + 0.2);
        glScaled(0.5, 0.2, 0.5);
        glutSolidCube(1);
        glPopMatrix();

        // Draw the seat back
        glPushMatrix();
        glTranslated(xPosition - 0.4, 2.2, zPosition );
        glScaled(0.5, 0.2, 0.1);
        glutSolidCube(1);
        glPopMatrix();

        // Draw the seat left arm
        glPushMatrix();
        glTranslated(xPosition -0.6, 2.2, zPosition + 0.2);
        glScaled(0.1, 0.2, 0.5);
        glutSolidCube(1);
        glPopMatrix();

        // Draw the seat right arm
        glPushMatrix();
        glTranslated(xPosition - 0.2, 2.2, zPosition + 0.2);
        glScaled(0.1, 0.2, 0.5);
        glutSolidCube(1);
        glPopMatrix();
//      }
    }
 
    glPopMatrix();
  
}
void drawHorseCarousel() {
 
    // Draw carousel base
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(5.0, 0.2, 5.0);
    glRotatef(-90, 1, 0, 0);
    drawFilledCylinder(1, 0.2, 32, 32);
    glPopMatrix();
    
    glColor3f(1.0f, 0.84f, 0.0f);
    glPushMatrix();
    glTranslatef(5.0, 0.4, 5.0);
    glRotatef(-90, 1, 0, 0);
    drawFilledCylinder(0.5, 0.2, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    if(objectsAnim){
//        std::cout << "(objectsAnim) " <<  objectsAnim << std::endl;
        glTranslatef(5.0, 0.0, 5.0);  // Translate to the center of rotation
//        std::cout << "(angleObjectsAnim) " <<  angleObjectsAnim << std::endl;
        glRotatef(angleObjectsAnim, 0, 1, 0);
        glTranslatef(-5.0, 0.0, -5.0);
    }
    
    // Draw central pole
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(5.0, 0.0, 5.0);
    glRotatef(-90, 1, 0, 0);
    drawFilledCylinder(0.1, 3, 32, 32);
    glPopMatrix();

    // Draw one horse
    // Body
    glColor3f(0.9, 1, 1);
    glPushMatrix();
    glTranslatef(5.0, 1.75, 5.0);       // Position above the base
    glRotatef(-90, 1, 0, 0);
    glRotatef(-90, 0, 0, 1);
    glScalef(0.5, 1.0, 0.5);           // Scale down to horse size
    glutSolidCube(1.0);
    glPopMatrix();

    // Head
    glPushMatrix();
    glColor3f(0.9, 1, 1);
    glTranslatef(5.4, 2.2, 5.0);
    glScalef(0.5, 0.4, 0.35);
    glutSolidCube(1);
    glColor3f(1.0, 0.8, 1.0);
    glTranslatef(0.2, 0.0, 0.0);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(0.25, 1.5, 32, 32);
    glPopMatrix();

    // Legs
    glPushMatrix();
    glColor3f(0.9, 1, 1);
    glTranslatef(4.6, 1.25, 4.85);
    glScalef(0.15, 0.5, 0.15);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.9, 1, 1);
    glTranslatef(4.6, 1.25, 5.15);
    glScalef(0.15, 0.5, 0.15);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.9, 1, 1);
    glTranslatef(5.4, 1.25, 4.85);
    glScalef(0.15, 0.5, 0.15);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.9, 1, 1);
    glTranslatef(5.4, 1.25, 5.15);
    glScalef(0.15, 0.5, 0.15);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(5.0, 3, 5.0);
    glRotatef(-90, 1, 0, 0);
    drawFilledCylinder(1.5, 0.3, 32, 32);
    glPopMatrix();
    
    glColor3f(1.0f, 0.84f, 0.0f);
    glPushMatrix();
    glTranslatef(5.0, 3.3, 5.0);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(1.0, 1, 32, 32);
    glPopMatrix();

    glPopMatrix();
}
void adjustBabyDirection(){
    if(downPressed){  // down =4
        if(babyDirection==1){
            babyROT+= 270;
        } else if(babyDirection==3){
            babyROT+= 90;
        } else if(babyDirection==2){
            babyROT+= 180;
        }
        babyDirection=4;
    }
    else if( upPressed){ // up=2
        if(babyDirection==1){
            babyROT+= 90;
        } else if(babyDirection==3){
            babyROT+= 270;
        } else if(babyDirection==4){
            babyROT+= 180;
            
        }
        babyDirection=2;
    }
     else if(rightPressed){ //right=1
        
        if(babyDirection==3){     // face of spaceship was left
            babyROT+= -180;
        } else if(babyDirection==4){
            babyROT+= 90;
        } else if(babyDirection==2){
            babyROT+= 270;
            
        }
         babyDirection=1;
    }
    else if(leftPressed){ //left=3
        if(babyDirection==1){   // face of spaceship was right
            babyROT+= 180;
        } else if(babyDirection==4){
           babyROT+= 270;
        } else if(babyDirection==2){
           babyROT+= 90;
        }
        babyDirection=3;
    }
}
void drawBaby(){
    adjustBabyDirection();

    glPushMatrix();
//    std::cout << "(babyX) " <<  babyX << std::endl;
//    std::cout << "(babyZ) " <<  babyZ << std::endl;
    glTranslatef(babyX, 0.0, babyZ);
    glRotatef(babyROT, 0.0f, 1.0f, 0.0f);
    glTranslatef(-babyX , 0.0, -babyZ);
    
    glPushMatrix();
    glTranslated(babyX-0.07, 0.25, babyZ+0.0);
    glColor3f(0.96f, 0.8f, 0.69f);
    glScaled( 0.1,0.15, 0.15);
    glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(babyX+0.08, 0.25, babyZ+0.0);
    glColor3f(0.96f, 0.8f, 0.69f);
    glScaled( 0.1,0.15, 0.15);
    glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(babyX+0.0, 0.4, babyZ+0.0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glScaled( 0.25,0.2, 0.15);
    glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(babyX+0.0, 0.65,babyZ+ 0.0);
    glColor3f(0.96f, 0.8f, 0.69f);
    glScaled( 0.25,0.3, 0.15);
    glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(babyX+0.0, 0.95, babyZ+0.0);
    glColor3f(0.96f, 0.8f, 0.69f);
    glutSolidSphere(0.125, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(babyX-0.2, 0.65,babyZ+ 0.0);
    glColor3f(0.96f, 0.8f, 0.69f);
    glScaled( 0.1,0.2, 0.09);
    glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(babyX+0.2, 0.65,babyZ+ 0.0);
    glColor3f(0.96f, 0.8f, 0.69f);
    glScaled( 0.1,0.2, 0.09);
    glutSolidCube(1);
    glPopMatrix();
    
    // Draw baby's eyes
    glPushMatrix();
    glTranslatef(babyX-0.06,0.955,babyZ+0.1);
    glColor3f(0.0f, 0.0f, 0.0f);  // Black for eyes
    glutSolidSphere(0.04, 20, 20);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(babyX-0.06,0.955,babyZ+0.13);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidSphere(0.02, 20, 20);
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslatef(babyX+0.06,0.955,babyZ+0.1);
    glColor3f(0.0f, 0.0f, 0.0f);  // Black for eyes
    glutSolidSphere(0.04, 20, 20);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(babyX+0.06,0.955,babyZ+0.13);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidSphere(0.02, 20, 20);
    glPopMatrix();
    
    

        // Draw baby's mouth (a simple smile)
        glColor3f(1.0f, 0.0f, 0.0f);  // Red for mouth
        glPushMatrix();
        glTranslatef(babyX,0.9,babyZ+0.1);
        glutSolidCone(0.02, 0.03, 20, 20);
        glPopMatrix();
    
    glPopMatrix();
    
    
}
void drawIceCream(){
    if(!goalCollision){
        glPushMatrix();
        glTranslatef(9.0, 0.7, 9.0);
        glRotatef(goalAnim, 0, 1, 0);
        glTranslatef(-9.0, -0.7, -9.0);
        
        
        // Draw ice cream cone
        glPushMatrix();
        glColor3f(0.87f, 0.72f, 0.53f);  // Light brown for the cone
        glTranslatef(9.0, 0.7, 9.0);
        glRotatef(90, 1, 0, 0);
        glRotatef(-45, 0, 1, 0);
        glutSolidCone(0.2, 0.5, 32, 32);
        glPopMatrix();
        
        // Draw ice cream scopes
        glPushMatrix();
        glColor3f(0.36f, 0.20f, 0.12f);
        glTranslatef(9.0, 0.8, 8.9);
        glRotatef(90, 1, 0, 0);
        glRotatef(-45, 0, 1, 0);
        glutSolidSphere(0.15, 32, 32);
        glPopMatrix();
        
        glPushMatrix();
        glColor3f(1.0f, 0.0f, 0.5f);  // Strawberry color
        glTranslatef(9.0, 0.75, 9.1);
        glRotatef(90, 1, 0, 0);
        glRotatef(-45, 0, 1, 0);
        glutSolidSphere(0.15, 32, 32);
        glPopMatrix();
        
        glPushMatrix();
        glColor3f(1.0f, 1.0f, 0.8f);  // Vanilla color
        glTranslatef(9.1, 0.7, 9.0);
        glRotatef(90, 1, 0, 0);
        glRotatef(-45, 0, 1, 0);
        glutSolidSphere(0.15, 32, 32);
        glPopMatrix();
        
        glPopMatrix();
    }
}
void drawTree(){
    glPushMatrix();
    glColor3f(0.55f, 0.27f, 0.07f); // Standard Brown
    glTranslatef(1.0, 0.0, 9.0);
    glRotatef(-90, 1, 0, 0);
    drawFilledCylinder(0.1, 2, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.0f, 0.5f, 0.0f); // Standard Green
    glTranslatef(1.0, 2, 9.25);
    if (objectsAnim) {
        glScalef(scaleValue1, scaleValue1, scaleValue1);
    } else {
        glScalef(0.5, 0.5, 0.5);
    }
    glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.0f, 0.5f, 0.0f); // Standard Green
    glTranslatef(1.0, 2, 8.75);
    if (objectsAnim) {
        glScalef(scaleValue2, scaleValue2, scaleValue2);
    } else {
        glScalef(0.75, 0.75, 0.75);
    }
    glutSolidCube(1);
    glPopMatrix();
  

}
void drawCup(float x, float y, float z) {
    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_LINE);
    const float cupRadius = 0.5;
    const float cupHeight = 1.0;

    glPushMatrix();
    glTranslatef(x, y, z);
    glRotated(90, 1, 0, 0);
    glScaled(0.25, 0.25, 0.25);

    // Draw the cup (approximated with a cylinder and a cone)
    drawFilledCylinder(cupRadius, cupHeight, 16, 8);
    gluCylinder(quadric, cupRadius, cupRadius, cupHeight, 32, 32);
    glTranslatef(0.0, 0.0, cupHeight);
    glutSolidCone(cupRadius * 1.5, cupRadius * 2.0, 16, 8);

    glPopMatrix();
}
void drawTeapotGame(){
    // Lower Part
    glPushMatrix();
    glColor3f(0.9f, 0.9f, 0.9f);
    glTranslatef(8.0, 0.0, 6.0);
    glRotated(-90, 1.0, 0.0, 0.0);
    drawFilledCylinder(1.5, 0.5, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    if(objectsAnim){
//        std::cout << "(objectsAnim) " <<  objectsAnim << std::endl;
        glTranslatef(8.0, 0.0, 6.0);  // Translate to the center of rotation
//        std::cout << "(angleObjectsAnim) " <<  angleObjectsAnim << std::endl;
        glRotatef(angleObjectsAnim, 0, 1, 0);
        glTranslatef(-8.0, 0.0, -6.0);
    }
    
    glPushMatrix();
    glTranslated(8.0, 0.75, 6.0);
    
    glColor3f(1.0f, 0.6f, 0.5f);
    drawCup(-1, 0, 0);
    glColor3f(1.0f, 0.8f, 1.0f);
    drawCup(1, 0, 0);
    glColor3f(1.0f, 0.5f, 0.6f);
    drawCup(-0.15, 0, -1);
    glColor3f(1.0f, 0.8f, 0.4f);
    drawCup(0.15, 0, 1);
    

    // Draw teapot in the center
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.7f);
    glTranslatef(0,0,0);
    glutSolidTeapot(0.5);
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();
}


void setupLights() {
    GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
    GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
    GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
    GLfloat shininess[] = { 50 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    GLfloat lightIntensity[] = { 1.0f, 1.0f, 1, 1.0f };
    GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
    //GLfloat lightPosition[] = { 0.0f, 5.0f, 3.0f, 0.0f };
    // GLfloat lightPosition[] = { 30.0f, 600.0f, 300.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
   // glEnable(GL_COLOR_MATERIAL);
}

void setupCamera() {
    // Set the current matrix mode to GL_PROJECTION
    glMatrixMode(GL_PROJECTION);

    // Load the identity matrix into the projection matrix stack
    glLoadIdentity();

    // Set up the perspective projection matrix using gluPerspective
//    gluPerspective(60, 640 / 480, 0.001, 100);
    gluPerspective(60, 1000/800, 0.001, 800);

    // Set the current matrix mode to GL_MODELVIEW
    glMatrixMode(GL_MODELVIEW);

    // Load the identity matrix into the modelview matrix stack
    glLoadIdentity();

    // Call the look method of the camera object
    camera.look();
}


void startObjectsAnim(){
    objectsAnim= true;
    playAnimationSound();
    
}
void stopObjectsAnim(){
    objectsAnim= false;

    if(goalCollision){
        playGoalCollisionSound();
    }else{
        playBackgroundSound();
    }
}
void checkCollision(){
//        std::cout << "(babyX) " <<  babyX << std::endl;
//        std::cout << "(babyZ) " <<  babyZ << std::endl;
//    if(babyX==9.0 && babyZ==8.9){
//        goalCollision=true;
//    }
    const float epsilon = 0.5;  // Adjust this threshold based on your precision requirements

    if (std::abs(babyX - 9.0) < epsilon && std::abs(babyZ - 9.0) < epsilon) {
        goalCollision = true;
        playGoalCollisionSound();
    }
}

void Keyboard(unsigned char key, int x, int y) {
    
    float d = 0.5;
    float a = 1.0;
    
        switch (key) {
            case 'w':
                camera.moveY(d);
                break;
            case 's':
                camera.moveY(-d);
                break;
            case 'a':
                camera.moveX(d);
                break;
            case 'd':
                camera.moveX(-d);
                break;
            case 'q':
                camera.moveZ(d);
                break;
            case 'e':
                camera.moveZ(-d);
                break;
            case 'm':
                startObjectsAnim();
                break;
            case 'n':
                stopObjectsAnim();
                break;
            case 'i':
                camera.rotateX(a);
                break;
            case 'k':
                camera.rotateX(-a);
                break;
            case 'j':
                camera.rotateY(a);
                break;
            case 'l':
                camera.rotateY(-a);
                break;
            case 'f':
                camera.frontView();
                break;
            case 't':
                camera.topView();
                break;
            case 'g':
                camera.sideView();
                break;
            case GLUT_KEY_ESCAPE:
                exit(EXIT_SUCCESS);
        }
       
    
}

void specialKeys(int key, int x, int y) {
    
    switch (key) {
            case GLUT_KEY_UP:
                upPressed = true;
                break;
            case GLUT_KEY_DOWN:
                downPressed = true;
                break;
            case GLUT_KEY_LEFT:
                leftPressed = true;
                break;
            case GLUT_KEY_RIGHT:
                rightPressed = true;
                break;
        }
    
}
void specialKeysUp(int key, int x, int y) {
    if(gameState==GAME_PLAYING){
        switch (key) {
            case GLUT_KEY_UP:
                upPressed = false;
                break;
            case GLUT_KEY_DOWN:
                downPressed = false;
                break;
            case GLUT_KEY_LEFT:
                leftPressed = false;
                break;
            case GLUT_KEY_RIGHT:
                rightPressed = false;
                break;
        }
        glutPostRedisplay();
    }
}
void idle(){
    
    
    if(gameState==GAME_PLAYING){
//        std::cout << "(gameState) " <<  gameState << std::endl;
        
        if (upPressed && (babyZ  )>0.0999994) {
            babyZ -= movementSpeed;
            
        } else if( upPressed &&(babyZ  )<0.0999994){
            
            babyZ += movementSpeed;
            
        }
        else if (downPressed && (babyZ  )<9.9 ) {
            babyZ += movementSpeed;
            
        }else if(downPressed && (babyZ  )>9.9){
            
            babyZ -= movementSpeed;
        }
        else if (leftPressed&& (babyX  )>0.25 ) {
            babyX -= movementSpeed;
        }else if (leftPressed && (babyX  )<0.25) {
            
            babyX += movementSpeed;
        }
        else if (rightPressed && (babyX  )<9.9 ) {
            babyX += movementSpeed;
        }else if (rightPressed  && (babyX  )>9.9) {
            
            babyX -= movementSpeed;
        }
        
        if (objectsAnim) {
            angleObjectsAnim += 0.5f;  // Increment the angle for the next frame

        }
        if( timeAnim%2==0){
            scaleValue1=0.75f;
            scaleValue2=0.5f;
        }else if( timeAnim%5==0){
            scaleValue1=0.5f;
            scaleValue2=0.75f;
        }
        
        
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = currentTime - lastSwitchTime;
        float seconds = duration.count();

        if(seconds >= 10){
            day = !day; // Switch the day flag
            lastSwitchTime = currentTime; // Update the time of the last switch
            
        }
        //std::cout << "(day) " <<  day << std::endl;
        timeAnim++;
        goalAnim+=0.5f;
        checkCollision();
        glutPostRedisplay();
    }
}
void print(int x, int y, char* string){
    int len, i;
    glColor3f(1.0f, 1.0f, 1.0f);
    //set the position of the text in the window using the x and y coordinates
    glRasterPos2f(x, y);

    //get the length of the string to display
    len = (int)strlen(string);

    //loop to display character by character
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
}
void toPrint(){
    //Displayed throught the game
    
    // Time
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = currentTime - startTime;
    float seconds = duration.count();
    secondsInt = static_cast<int>(seconds);
    sprintf((char*)p0s, "Time: %d s",gameTime- secondsInt);
    print(5, 11, (char*)p0s);
}
void renderEndScene(){

    //glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(goalCollision){
       // playAlienSound();
        sprintf((char*)p0s, "You won! :)");
    }
    else{
        
        //playLoseSound();
        sprintf((char*)p0s, "You lose :(");
    }
    print(5, 5, (char*)p0s);
    glutSwapBuffers();
    glFlush();
   
}
void Display() {
    
    setupCamera();
    setupLights();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    drawJack();
    
    drawBench(1.0, 0.2, 0.09, 1.0);
    
    drawSwingRide();
    drawHorseCarousel();
    drawBaby();
    drawIceCream();
    drawTree();
    drawTeapotGame();
    drawBoundaries();
    
    
    toPrint();
    
    if(gameTime - secondsInt==0 ){
        gameState=GAME_OVER;
        renderEndScene();
    }
    
    glutSwapBuffers();
    
    glFlush();
    
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitWindowSize(1000, 800);
    glutInitWindowPosition(50, 50);

    glutCreateWindow("Lost Baby!");
    
    srand(time(0));  // stars generated but not randomly after each rub
    secondsInt=0;
    startTime = std::chrono::high_resolution_clock::now();
    gameState = GAME_PLAYING; // Set the initial state to playing.
    
    
    lastSwitchTime = std::chrono::high_resolution_clock::now();
    
    playBackgroundSound();
    glutDisplayFunc(Display);
    glutKeyboardFunc(Keyboard);
    glutSpecialUpFunc(specialKeysUp);
    glutSpecialFunc(specialKeys);
    glutIdleFunc(idle);

    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB | GLUT_DEPTH);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glShadeModel(GL_SMOOTH);

    glutMainLoop();
    
    return 0;
}
