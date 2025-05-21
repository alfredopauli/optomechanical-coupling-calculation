#include <iostream>
#include <cmath>
#include "Vec3.hpp"
#include <vector>

#include <raylib.h>

class Triangle
{
    public:
        Triangle() = default;    

        Triangle(const Vec3 &a, const Vec3 &b, const Vec3 &c)
        {
            m_points[0] = a;
            m_points[1] = b;
            m_points[2] = c;
        }
    
        Vec3 GetPoint(short index) const
        {
            return m_points[index];
        }
        
        double GetArea() const 
        {
            return 1.0/2.0 * (Vec3::Cross(m_points[0], m_points[1])).Magnitude();
        }
        
        static void Subdivide(Triangle triangle, Triangle new_triangles[4])
        {
            new_triangles[0] = Triangle(
                triangle.GetPoint(0),
                (triangle.GetPoint(0) + triangle.GetPoint(1)) / 2,
                (triangle.GetPoint(0) + triangle.GetPoint(2)) / 2
            );
            
            new_triangles[1] = Triangle(
                triangle.GetPoint(1),
                (triangle.GetPoint(1) + triangle.GetPoint(0)) / 2,
                (triangle.GetPoint(1) + triangle.GetPoint(2)) / 2
            );
            
            new_triangles[2] = Triangle(
                triangle.GetPoint(2),
                (triangle.GetPoint(2) + triangle.GetPoint(0)) / 2,
                (triangle.GetPoint(2) + triangle.GetPoint(1)) / 2
            );
        }

    private:
        Vec3 m_points[3];
};



class Surface
{
    public:
        Surface() = default;
        
        void AddTriangle(Triangle triangle)
        {
            m_triangles.push_back(triangle);
        }
        
        std::vector<Triangle> GetTriangles() const
        {
            return m_triangles;
        }
        
        void CreateMesh(double threshold)
        {
            m_triangles = RecursiveCreateMesh(m_triangles, threshold);
        }
        

    private:
        std::vector<Triangle> m_triangles;
        
        std::vector<Triangle> RecursiveCreateMesh(const std::vector<Triangle> &previous, double threshold)
        {
            std::vector<Triangle> next_triangles;
            Triangle new_triangles[4];
            
            for (auto &triangle : previous)
            {
                if (triangle.GetArea() < threshold)
                {
                    next_triangles.push_back(triangle);
                    continue;
                }
                
                Triangle::Subdivide(triangle, new_triangles);

                next_triangles.push_back(new_triangles[0]);
                next_triangles.push_back(new_triangles[1]);
                next_triangles.push_back(new_triangles[2]);
                next_triangles.push_back(new_triangles[3]);
            }
            
            return RecursiveCreateMesh(next_triangles, threshold);
        }
};


void DrawSurface(Surface surface)
{
    for (auto &triangle : surface.GetTriangles())
    {
        DrawLine3D(
    }
}


class StandingLightEmitter
{
    public:
        StandingLightEmitter():
            m_center(Vec3(0, 0, 0)),
            m_propagation(Vec3(1, 0, 0)),
            m_perturbation(Vec3(0, 1, 0)),
            m_frequency(1)
        {}
        
        void SetCenter(const Vec3 &center)
        {
            m_center = center;
        }

        void SetPropagation(const Vec3 &propagation)
        {
            m_propagation = Vec3::Normalize(propagation);
        }
        
        void SetPerturbation(const Vec3 &perturbation)
        {
            m_perturbation = perturbation;
        }

        Vec3 GetField(Vec3 point) const
        {
            double x = (point - m_center) * m_propagation;
            return cos(2.0 * M_PI * m_frequency * x) * m_perturbation;
        }

    private:
        Vec3 m_center;
        Vec3 m_propagation;
        Vec3 m_perturbation;
        double m_frequency;
};

int main(void)
{
    InitWindow(0,0, "Optomechanical Coupling Calculator");
    
    // Define the camera to look into our 3d world (position, target, up vector)
    Camera camera = { 0 };
    camera.position = (Vector3){ 2.0f, 2.0f, 2.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
    
    Surface surface;
    surface.AddTriangle(Triangle(
        Vec3(0.0, -1.0, 1.0),
        Vec3(0.0, -1.0, -1.0),
        Vec3(0.0, 1.0, -1.0)
    ));

    surface.AddTriangle(Triangle(
        Vec3(0.0, 1.0, -1.0),
        Vec3(0.0, 1.0, 1.0),
        Vec3(0.0, -1.0, 1.0)
    ));

    while(!WindowShouldClose())
    {
        BeginDrawing(); 
        ClearBackground(BLACK);
        
        BeginMode3D(camera);
        EndMode3D();

        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}

