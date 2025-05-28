#include <iostream>
#include <cmath>
#include <vector>
#include <raylib.h>

#include "Vec3.hpp"
#include "Triangle.hpp"
#include "Surface.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Emitter.hpp"


void DrawObject(const Object &object)
{
    for (const Surface &surface : object.GetSurface())
    {
        for (const Triangle &triangle : surface.GetTriangles())
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
        
        Vec3 midpoint = surface.GetMidpoint();
        Vec3 endpoint = midpoint + surface.GetNormal() * 0.5f;
        
        DrawLine3D(
            (Vector3){ (float)midpoint.x, (float)midpoint.y, (float)midpoint.z },
            (Vector3){ (float)endpoint.x, (float)endpoint.y, (float)endpoint.z },
            MAGENTA
        );
    }
}

void DrawMechanicalEmitter(const StandingMechanicalEmitter &emitter)
{
    Vec3 propagation = emitter.GetPropagation();
    Vec3 perturbation = emitter.GetPerturbation();
    Vec3 center = emitter.GetCenter();
    
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

void DrawLightEmitter(const StandingLightEmitter &emitter)
{
    Vec3 propagation = emitter.GetPropagation();
    Vec3 perturbation = emitter.GetPerturbation();
    Vec3 center = emitter.GetCenter();
    
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
        Vec3 node = emitter.GetNode(i/5.0); 
        DrawSphere(node.ToVector3(), 0.02f, YELLOW);
        Vec3 field = emitter.GetElectricalField(node);
        DrawLine3D(node.ToVector3(), (node + field).ToVector3(), YELLOW);
    }
}


int main(void)
{
    InitWindow(0,0, "Optomechanical Coupling Calculator");
    
    // TODO: Emitter is a Base Class
    // TODO: use unique pointers
    // TODO: check it calculation is Correct
    // TODO: handle e0
    // TODO: refactor code, see if it is the best approach
    
    // Define the camera to look into our 3d world (position, target, up vector)
    Camera camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 10.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_ORTHOGRAPHIC;             // Camera projection type
    int camera_mode = CAMERA_ORBITAL;
    
    DisableCursor();
    
    System system;
    
    // Add light emitter
    StandingLightEmitter *le = new StandingLightEmitter();
    le->SetCenter(Vec3(-1.0, 0.0, 0.0));
    le->SetPerturbation(Vec3(0.0, 1.0, 0.0));
    le->SetPropagation(Vec3(1.0, 0.0, 0.0));
    le->SetFrequency(0.9);
    
    StandingMechanicalEmitter *me = new StandingMechanicalEmitter();
    me->SetCenter(Vec3(1.0, 0.0, 0.0));
    me->SetPerturbation(Vec3(1.0, 0.0, 0.0));
    me->SetPropagation(Vec3(1.0, 0.0, 0.0));
    
    system.AddLightEmitter(le);
    system.AddMechanicalEmitter(me);

    Object &fabry_perot = system.CreateObject();
    Surface &fabry_perot_mirror = fabry_perot.CreateSurface();
    fabry_perot_mirror.DefineNormal(Vec3(-1.0f, 0.0f, 0.0f));

    fabry_perot_mirror.AddTriangle(Triangle(
        Vec3(1.0, -1.0, 1.0),
        Vec3(1.0, -1.0, -1.0),
        Vec3(1.0, 1.0, -1.0)
    ));

    fabry_perot_mirror.AddTriangle(Triangle(
        Vec3(1.0, 1.0, -1.0),
        Vec3(1.0, 1.0, 1.0),
        Vec3(1.0, -1.0, 1.0)
    ));
    
    std::cout << "Optomechanical coupling: " << system.CalculateOptomechanicalCoupling() << std::endl;
    
    fabry_perot_mirror.CreateMesh(0.1);
    
    while(!WindowShouldClose())
    {
        if (IsKeyPressed('Z'))
        {
            camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
            camera.projection = CAMERA_PERSPECTIVE; 
            camera_mode = CAMERA_FREE;
            camera.fovy = 45.0f;                                // Camera field-of-view Y
        }
        
        UpdateCamera(&camera, camera_mode);

        BeginDrawing(); 
        ClearBackground(BLACK);
        
        BeginMode3D(camera);
            DrawGrid(10, 1.0f);
            
            DrawLightEmitter(*le);
            DrawMechanicalEmitter(*me);

            DrawObject(fabry_perot);
        EndMode3D();

        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}

