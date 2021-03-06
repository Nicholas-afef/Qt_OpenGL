#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNorms;
layout(location = 2) in vec2 texCoord;

out vec2 v_TexCoord;
out vec3 normal;
out vec3 fragPosition;

uniform mat4 normalMatrix = mat4(1.0, 0.0, 0.0, 0.0,
                                    0.0, 1.0, 0.0, 0.0,
                                    0.0, 0.0, 1.0, 0.0,
                                    0.0, 0.0, 0.0, 1.0);

uniform mat4 modelViewMatrix = mat4(1.0, 0.0, 0.0, 0.0,
                                0.0, 1.0, 0.0, 0.0,
                                0.0, 0.0, 1.0, 0.0,
                                0.0, 0.0, 0.0, 1.0);

uniform mat4 perspectiveMatrix = mat4(1.0, 0.0, 0.0, 0.0,
                                      0.0, 1.0, 0.0, 0.0,
                                      0.0, 0.0, 1.0, 0.0,
                                      0.0, 0.0, 0.0, 1.0);

void main(){
    //modelMatrix: moves vertex from local to world space
    //viewMatrix: moves vertex from world space to camera view
    //  [ux, uy, uz, -u.x]
    //  [vx, vy, vz, -v.y]
    //  [nx, ny, nz, -n.z]
    //  [ 0,  0,  0,  1  ]
    //so modelView is the combo of model and view
    //projectionMatrix: moves the vertex to clip space screen co-ords

    gl_Position = perspectiveMatrix * modelViewMatrix * vec4(aPos,1.0);
    v_TexCoord = texCoord;
    fragPosition = vec3(normalMatrix * vec4(aPos,1.0));
    normal = aNorms;
};
