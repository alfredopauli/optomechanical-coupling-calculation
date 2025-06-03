#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <raylib.h>

#include "Vec3.hpp"
#include "Triangle.hpp"
#include "Surface.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mode.hpp"


void DrawSystemBoundary(const System *system)
{
    DrawCubeWires(
        system->GetBoundaryCenter().ToVector3(),
        system->GetBoundaryWidth(), 
        system->GetBoundaryHeight(),
        system->GetBoundaryLength(),
        RED
    );
}

void DrawObject(const Object *object)
{
    for (const Surface *surface : object->GetSurfaces())
    {
        for (const Triangle &triangle : surface->GetTriangles())
        {
            DrawLine3D(
                (Vector3){ (float)triangle.GetPoint(0).x, (float)triangle.GetPoint(0).y, (float)triangle.GetPoint(0).z }, 
                (Vector3){ (float)triangle.GetPoint(1).x, (float)triangle.GetPoint(1).y, (float)triangle.GetPoint(1).z },
                WHITE
                );
            DrawLine3D(
                (Vector3){ (float)triangle.GetPoint(1).x, (float)triangle.GetPoint(1).y, (float)triangle.GetPoint(1).z }, 
                (Vector3){ (float)triangle.GetPoint(2).x, (float)triangle.GetPoint(2).y, (float)triangle.GetPoint(2).z },
                WHITE
                );
            DrawLine3D(
                (Vector3){ (float)triangle.GetPoint(2).x, (float)triangle.GetPoint(2).y, (float)triangle.GetPoint(2).z }, 
                (Vector3){ (float)triangle.GetPoint(0).x, (float)triangle.GetPoint(0).y, (float)triangle.GetPoint(0).z },
                WHITE
                );
        }
        
        Vec3 midpoint = surface->GetMidpoint();
        Vec3 endpoint = midpoint + surface->GetNormal() * 0.5f;
        
        DrawLine3D(
            (Vector3){ (float)midpoint.x, (float)midpoint.y, (float)midpoint.z },
            (Vector3){ (float)endpoint.x, (float)endpoint.y, (float)endpoint.z },
            MAGENTA
        );
    }
}

void DrawMechanicalEmitter(const PlaneMechanicalMode *mode)
{
    Vec3 propagation = mode->GetPropagation();
    Vec3 perturbation = mode->GetPerturbation();
    Vec3 center = mode->GetCenter();
    
    Vec3 propagation_end = center + propagation * 0.5f;
    Vec3 perturbation_end = center + perturbation * 0.5f / perturbation.Magnitude();
    
    float offset = 0.0f;
    if (propagation_end == perturbation_end)
        offset = 0.05f;
    
    DrawSphere(
        (Vector3){ (float)center.x, (float)center.y, (float)center.z },
        0.03f,
        GREEN
    );
    
    DrawLine3D(
        (Vector3){ (float)center.x, (float)center.y - offset, (float)center.z },
        (Vector3){ (float)propagation_end.x, (float)propagation_end.y - offset, (float)propagation_end.z },
        BLUE
    );
    
    DrawLine3D(
        (Vector3){ (float)center.x, (float)center.y + offset, (float)center.z },
        (Vector3){ (float)perturbation_end.x, (float)perturbation_end.y + offset, (float)perturbation_end.z },
        RED
    );
}

void DrawLightEmitter(const PlaneLightMode *mode)
{
    Vec3 propagation = mode->GetPropagation();
    Vec3 perturbation = mode->GetPerturbation();
    Vec3 center = mode->GetCenter();
    
    Vec3 propagation_end = center + propagation * 0.5f;
    Vec3 perturbation_end = center + perturbation * 0.5f / perturbation.Magnitude();
    
    float offset = 0.0f;
    if (propagation_end == perturbation_end)
        offset = 0.05f;
    
    DrawSphere(
        (Vector3){ (float)center.x, (float)center.y, (float)center.z },
        0.03f,
        GREEN
    );
    
    DrawLine3D(
        (Vector3){ (float)center.x, (float)center.y - offset, (float)center.z },
        (Vector3){ (float)propagation_end.x, (float)propagation_end.y - offset, (float)propagation_end.z },
        BLUE
    );

    DrawLine3D(
        (Vector3){ (float)center.x, (float)center.y + offset, (float)center.z },
        (Vector3){ (float)perturbation_end.x, (float)perturbation_end.y + offset, (float)perturbation_end.z },
        RED
    );
    
    for (int i=0; i < 20; i++)
    {
        Vec3 node = mode->GetNode(i/20.0); 
        DrawSphere(node.ToVector3(), 0.02f, YELLOW);
        Vec3 field = mode->GetField(node);
        DrawLine3D(node.ToVector3(), (node + field).ToVector3(), YELLOW);
    }
}

int main(void)
{
    InitWindow(0,0, "Optomechanical Coupling Calculator");
    
    // TODO: Redo triangle code, i dont like the way im am handling
    // translations, maybe its better just update all triangles position
    // instead of storing the templates
    // TODO: How do I calculate the frequency of the mechanical mode
    // TODO: make so that the system has only one mechanical and optical mode
    
    // Define the camera to look into our 3d world (position, target, up vector)
    Camera camera;
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 10.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_ORTHOGRAPHIC;             // Camera projection type
    int camera_mode = CAMERA_ORBITAL;
    
    DisableCursor();
    
    System system;

    double L = 0.1;
    const double delta = 0.1;
    const double L_offset = 0.01;
    const int points = 1000;
    
    system.DefineBoundary(Vec3(-L/2.0,-1.0,-1.0), L, 2, 2); 
    
    std::stringstream file_name;
    file_name << "optm loff=" << L_offset << " delta=" << delta << " points=" << points;

    std::ofstream outfile;
    outfile.open(file_name.str());
    
    // Add light emitter
    PlaneLightMode *le = system.CreateLightMode<PlaneLightMode>();
    le->SetCenter(Vec3(-L/2.0, 0.0, 0.0));
    le->SetPerturbation(Vec3(0.0, 1.0, 0.0));
    le->SetPropagation(Vec3(1.0, 0.0, 0.0));
    le->SetFrequency(LIGHT_SPEED/(2.0 * (L + delta)));
    
    PlaneMechanicalMode *me = system.CreateMechanicalMode<PlaneMechanicalMode>();
    me->SetCenter(Vec3(L/2.0, 0.0, 0.0));
    me->SetPerturbation(Vec3(1.0, 0.0, 0.0));
    me->SetPropagation(Vec3(1.0, 0.0, 0.0));
    me->SetFrequency(LIGHT_SPEED/(2.0 * (L + delta)));
    
    Object *fabry_perot = system.CreateObject();
    fabry_perot->SetDielectricConstant(5.0);

    Surface *fabry_perot_mirror = fabry_perot->CreateSurface();
    fabry_perot_mirror->SetNormal(Vec3(-1.0f, 0.0f, 0.0f));

    fabry_perot_mirror->CreateTriangle(
        Vec3(0.0, -1.0, 1.0),
        Vec3(0.0, -1.0, -1.0),
        Vec3(0.0, 1.0, -1.0)
    );

    fabry_perot_mirror->CreateTriangle(
        Vec3(0.0, 1.0, -1.0),
        Vec3(0.0, 1.0, 1.0),
        Vec3(0.0, -1.0, 1.0)
    );
    
    fabry_perot_mirror->Translate(Vec3(L/2.0, 0.0, 0.0));
    fabry_perot_mirror->CreateMesh(0.01);
    
    outfile << L << "," << system.CalculateOptomechanicalCoupling() << std::endl;
    
    for (int i=0; i < points; i++)
    {
        L += L_offset;

        le->SetCenter(Vec3(-L/2.0, 0.0, 0.0));
        le->SetFrequency(LIGHT_SPEED/(2.0 * (L + delta)));
        me->SetCenter(Vec3(L/2.0, 0.0, 0.0));
        me->SetFrequency(LIGHT_SPEED/(2.0 * (L + delta)));
        fabry_perot_mirror->Translate(Vec3(L/2.0, 0.0, 0.0));
        system.DefineBoundary(Vec3(-L/2.0, -1.0, -1.0), L, 2, 2); 

        // std::cout << "Optomechanical coupling: " << system.CalculateOptomechanicalCoupling() << std::endl;
        //std::cout << L << "," << system.CalculateOptomechanicalCoupling() << std::endl;
        outfile << L << "," << system.CalculateOptomechanicalCoupling() << std::endl;
    }
    
    outfile.close();
    
    while(!WindowShouldClose())
    {
        if (IsKeyPressed('Z'))
        {
            if (camera_mode == CAMERA_ORBITAL)
            {
                camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
                camera.projection = CAMERA_PERSPECTIVE; 
                camera_mode = CAMERA_FREE;
                camera.fovy = 45.0;
            } else if (camera_mode == CAMERA_FREE)
            {
                camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
                camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };    
                camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
                camera.fovy = 10.0f;
                camera.projection = CAMERA_ORTHOGRAPHIC;
                camera_mode = CAMERA_ORBITAL;
            }
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            L += L_offset;
            
            le->SetCenter(Vec3(-L/2.0, 0.0, 0.0));
            le->SetFrequency(LIGHT_SPEED/(2.0 * (L + delta)));
            me->SetCenter(Vec3(L/2.0, 0.0, 0.0));
            me->SetFrequency(LIGHT_SPEED/(2.0 * (L + delta)));
            fabry_perot_mirror->Translate(Vec3(L/2.0, 0.0, 0.0));

            // std::cout << "Optomechanical coupling: " << system.CalculateOptomechanicalCoupling() << std::endl;
            std::cout << L << "," << system.CalculateOptomechanicalCoupling() << std::endl;
        }
        
        UpdateCamera(&camera, camera_mode);

        BeginDrawing(); 
        ClearBackground(BLACK);
        
        BeginMode3D(camera);
            DrawGrid(10, 1.0f);
            
            DrawSystemBoundary(&system);
            DrawLightEmitter(le);
            DrawMechanicalEmitter(me);
            DrawObject(fabry_perot);
        EndMode3D();

        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}

