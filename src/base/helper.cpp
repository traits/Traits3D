#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "traits3d/helper.h"


#ifndef TRAITS3D_NOT_FOR_DOXYGEN

namespace
{
// convex hull

typedef double coordinate_type;

int ccw(coordinate_type **P, int i, int j, int k)
{
    coordinate_type a = P[i][0] - P[j][0],
                    b = P[i][1] - P[j][1],
                    c = P[k][0] - P[j][0],
                    d = P[k][1] - P[j][1];
    return a * d - b * c <= 0; /* true if points i, j, k counterclockwise */
}


#define CMPM(c,A,B) \
    v = (*(coordinate_type**)A)[c] - (*(coordinate_type**)B)[c];\
    if (v>0) return 1;\
    if (v<0) return -1;

int cmpl(const void *a, const void *b)
{
    double v;
    CMPM(0, a, b);
    CMPM(1, b, a);
    return 0;
}

int cmph(const void *a, const void *b)
{
    return cmpl(b, a);
}


int make_chain(coordinate_type **V, int n, int(*cmp)(const void *, const void *))
{
    int i, j, s = 1;
    coordinate_type *t;
    qsort(V, n, sizeof(coordinate_type *), cmp);

    for (i = 2; i < n; i++)
    {
        for (j = s; j >= 1 && ccw(V, i, j, j - 1); j--) {}

        s = j + 1;
        t = V[s];
        V[s] = V[i];
        V[i] = t;
    }

    return s;
}

int _ch2d(coordinate_type **P, int n)
{
    int u = make_chain(P, n, cmpl);   /* make lower hull */

    if (!n) return 0;

    P[n] = P[0];
    return u + make_chain(P + u, n - u + 1, cmph);  /* make upper hull */
}


} // ns anon

namespace traits3d
{

void convexhull2d(std::vector<size_t> &idx, const std::vector<Tuple> &src)
{
    idx.clear();

    if (src.empty())
        return;

    if (src.size() == 1)
    {
        idx.push_back(0);
        return;
    }

    coordinate_type **points = new coordinate_type*[src.size() + 1];
    coordinate_type *P = new coordinate_type[src.size() * 2];
    int i;

    for (i = 0; i < (int)src.size(); ++i)
    {
        points[i] = &P[2 * i];
        points[i][0] = src[i].x;
        points[i][1] = src[i].y;
    }

    coordinate_type *start = points[0];
    int m = _ch2d(points, static_cast<int>(src.size()));
    idx.resize(m);

    for (i = 0; i < m; ++i)
        idx[i] = (points[i] - start) / 2;

    delete[] points;
    delete[] P;
}

size_t tesselationSize(CellVector const &t)
{
    size_t ret = 0;

    for (unsigned i = 0; i != t.size(); ++i)
        ret += t[i].size();

    return ret;
}

#endif // TRAITS3D_NOT_FOR_DOXYGEN

float excess(TripleVector const &val)
{
    float ret = 0;

    for (auto v : val)
        ret = std::max(ret, excess(v));

    return ret;
}


std::vector<TripleF> scale(double &exc, TripleVector const &val)
{
    exc = excess(val);

    if (exc > 1)
        return scale(val, exc);
    else
        return convert(val);
}

std::vector<TripleF> scale(TripleVector const &val, double excess)
{
    std::vector<TripleF> ret(val.size());

    for (size_t i = 0; i != val.size(); ++i)
        ret[i] = (val[i] / excess);

    return ret;
}

std::vector<TripleF> convert(TripleVector const &val)
{
    std::vector<TripleF> ret(val.size());

    for (size_t i = 0; i != val.size(); ++i)
        ret[i] = static_cast<TripleF>(val[i]);

    return ret;
}

TripleF calculateUpVector(const TripleF &position, const TripleF &target)
{
    TripleF up;
    const float eps = 0.03f;
    // compute the forward vector
    TripleF forward = glm::normalize(position - target);
    forward = glm::normalize(forward);

    // compute temporal up vector based on the forward vector
    // watch out when look up/down at 90 degree
    // for example, forward vector is on the Z axis
    if (std::abs(forward.x) < eps && std::abs(forward.y) < eps)
    {
        // forward vector is pointing +Z axis
        if (forward.z > 0)
            up = TripleF(0, -1, 0);
        // forward vector is pointing -Z axis
        else
            up = TripleF(0, 1, 0);
    }
    // in general, up vector is straight up
    else
        up = TripleF(0, 0, 1);

    // compute the left vector
    TripleF left = glm::normalize(glm::cross(up, forward));
    // re-calculate the orthonormal up vector
    up = glm::normalize(glm::cross(forward, left));
    return up;
}


namespace
{
// Returns a quaternion such that q*start = dest
glm::quat RotationBetweenVectors(glm::vec3 start, glm::vec3 dest)
{
    start = glm::normalize(start);
    dest = glm::normalize(dest);
    float cosTheta = glm::dot(start, dest);
    glm::vec3 rotationAxis;

    if (cosTheta < -1 + 0.001f)
    {
        // special case when vectors in opposite directions :
        // there is no "ideal" rotation axis
        // So guess one; any will do as long as it's perpendicular to start
        // This implementation favors a rotation around the Up axis,
        // since it's often what you want to do.
        rotationAxis = glm::cross(glm::vec3(0.0f, 0.1f, 0.0f), start);

        if (length2(rotationAxis) < 0.01) // bad luck, they were parallel, try again!
            rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);

        rotationAxis = glm::normalize(rotationAxis);
        return glm::angleAxis(3.1415926f, rotationAxis);
    }

    // Implementation from Stan Melax's Game Programming Gems 1 article
    rotationAxis = glm::cross(start, dest);
    rotationAxis = glm::normalize(rotationAxis);
    float s = sqrt((1 + cosTheta) * 2);
    float invs = 1 / s;
    //float invs = sqrt(1 - cosTheta);// 1 / s;
    //invs = std::acos(cosTheta) / 2;
    //invs = std::sin(invs);
    return glm::quat(
               s * 0.5f,
               rotationAxis.x * invs,
               rotationAxis.y * invs,
               rotationAxis.z * invs
           );
}

// Returns a quaternion that will make your object looking towards 'direction'.
// Similar to RotationBetweenVectors, but also controls the vertical orientation.
// This assumes that at rest, the object faces +Z.
// Beware, the first parameter is a direction, not the target point !
glm::quat LookAt(glm::vec3 direction, glm::vec3 desiredUp)
{
    // Recompute desiredUp so that it's perpendicular to the direction
    // You can skip that part if you really want to force desiredUp
    glm::vec3 right = glm::cross(direction, desiredUp);
    desiredUp = glm::cross(right, direction);
    // Find the rotation between the front of the object (that we assume towards +Z,
    // but this depends on your model) and the desired direction
    glm::quat rot1 = RotationBetweenVectors(glm::vec3(0.0f, 0.0f, 1.0f), direction);
    // Because of the 1rst rotation, the up is probably completely screwed up.
    // Find the rotation between the "up" of the rotated object, and the desired up
    glm::vec3 newUp = rot1 * glm::vec3(0.0f, 1.0f, 0.0f);
    glm::quat rot2 = RotationBetweenVectors(newUp, desiredUp);
    // Apply them
    return rot2 * rot1; // remember, in reverse order.
}

} // private

glm::mat4 rotMatrix(const TripleF &direction)
{
    glm::quat q = LookAt(direction, glm::vec3(0, 1, 0));
    return glm::toMat4(q);
}

} // ns