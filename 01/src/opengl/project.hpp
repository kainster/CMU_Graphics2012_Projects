/**
 * @file project.hpp
 * @brief OpenGL project
 *
 * @author H. Q. Bovik (hqbovik)
 * @bug Unimplemented
 */

#ifndef _462_OPENGL_PROJECT_HPP_
#define _462_OPENGL_PROJECT_HPP_

#include "math/camera.hpp"
#include "math/vector.hpp"
#include "math/quaternion.hpp"
#include "math/color.hpp"

/*
   A namespace declaration. All project files use this namespace.
   Add this declaration (and its closing) to all source/headers you create.
   Note that all #includes should be BEFORE the namespace declaration.
 */
namespace _462 {

/*
    All scene structures are in this file, except:
    - real_t is a typedef in math/math.hpp
    - Camera is defined in math/camera.hpp
    - Vector3 is defined in math/vector.hpp
    - Quaternion is defined in math/quaternion.hpp
    - Color3 is defined in math/color.hpp
*/

struct Triangle
{
    // index into vertex list of the 3 vertices of this triangle
    unsigned int vertices[3];
};

struct MeshData
{
    // array of vertices
    Vector3* vertices;
    // size of vertex array
    size_t num_vertices;
    // array of triangles
    Triangle* triangles;
    // size of triangle array
    size_t num_triangles;

	Vector3* normals;

	size_t num_normals;

	void CalculateNormals();
};

class Heightmap
{
public:
    virtual ~Heightmap() { }
    /**
     * Returns the height at the given position, where the position runs anywhere
     * in the square from (-1,-1) to (1,1).
     */
    virtual real_t compute_height( const Vector2& pos ) const = 0;
    virtual void update( real_t dt ) = 0;
};

struct PositionData
{
    /*
     * Transformations should be applied in the following order:
     * 1. scale
     * 2. rotation
     * 3. translation
     */
    Vector3 position;
    Quaternion orientation;
    Vector3 scale;
};

struct Scene
{
    // note: data is allocated/freed by starter code.
    MeshData mesh;
    PositionData mesh_position;
    // note: is allocated/freed by starter code.
    Heightmap* heightmap;
    PositionData heightmap_position;
};

/**
 * A C++ class. This contains declarations of functions and data for the class.
 * The definitions (implementation) of functions go in a source file.
 *
 * This class is where the majority of the implementation for your project will
 * go. Declare all class functions and members here, and implement functions in
 * project.cpp.
 */
class OpenglProject
{
public:
    // more detailed specifications for each function are in project.cpp.

    // constructor, invoked when object is created
    OpenglProject();
    // destructor, invoked when object is destroyed
    ~OpenglProject();

    // Initialize the project, loading the mesh from the given filename.
    // Returns true on success.
    bool initialize( Camera* camera, Scene* scene );
    // Clean up the project, free any memory, etc.
    void destroy();
    // perform any updates
    void update( real_t dt );
    // Renderg the mesh using the given camera.
    void render( const Camera* camera );

private:

    // a copy of the scene data, as passed in by initialize
    Scene scene;

	void CalculateNormals(Vector3 normals[160][160], int xResolution, int yResolution, float* vertex_array);

    void RenderMesh();

	void RenderHeightMap();

	Vector3 ComputeNormal(Vector3 v1, Vector3 v2, Vector3 v3);
	bool GetNormalFromIDs(int idx1, int idz1, int idx2, int idz2, int idx3, int idz3,
		int xResolution, int zResolution, Vector3& normal, float* vertex_array);
    // since this has no meaningful or usefule assignment/copy, prevent the
    // compiler from automatically generating those functions
    OpenglProject( const OpenglProject& );
    OpenglProject& operator=( const OpenglProject& );
};

} /* _462 */

#endif /* _462_OPENGL_PROJECT_HPP_ */

