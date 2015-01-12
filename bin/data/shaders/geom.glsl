
#version 120
#extension GL_EXT_geometry_shader4 : enable

uniform float thickness;
uniform vec3 lightDir;
uniform float rotateMount;

vec3 vert[8] = vec3[8](
                       vec3(-1.0,-1.0,1.0),
                       vec3(-1.0,1.0,1.0),
                       vec3(1.0,1.0,1.0),
                       vec3(1.0,-1.0,1.0),
                       vec3(-1.0,-1.0,-1.0),
                       vec3(-1.0,1.0,-1.0),
                       vec3(1.0,1.0,-1.0),
                       vec3(1.0,-1.0,-1.0));


void quad(int a,int b,int c,int d,vec3 p0){
    
    float timer =  0;
    
    mat4 RotationMatrix =  mat4(
                                vec4(1.0,         0.0,         0.0, 0.0),
                                vec4(0.0,  cos(timer),  sin(timer), 0.0),
                                vec4(0.0, -sin(timer),  cos(timer), 0.0),
                                vec4(0.0,         0.0,         0.0, 1.0)
                                );
    
    

    //RotationMatrix *= gl_ModelViewProjectionMatrix;
    
//    mat4 matrix;
//    vec3 direction;
    //    vec3 transformed_direction = vec3(matrix * vec4(direction, 0.0));
    //mat4 dd = RotationMatrix * gl_ModelViewProjectionMatrix;
    // RotationMatrix = dd;
    //mat2 rotX = mat2(cosA, sinA, -sinA, cosA);
    //a_pos.xy = rotZ * a_position.xy;
    
    //   gl_Position = gl_ModelViewProjectionMatrix * vec4(0,1,0,1.0);
    
    gl_Position =  gl_ModelViewProjectionMatrix * (vec4(vert[a]+p0,1.0)*RotationMatrix);
    gl_FrontColor = gl_FrontColorIn[0] ;
	EmitVertex();
    
    gl_Position =  gl_ModelViewProjectionMatrix * (vec4(vert[b]+p0,1.0)*RotationMatrix);
    gl_FrontColor = gl_FrontColorIn[0] ;
	EmitVertex();
    
    gl_Position =  gl_ModelViewProjectionMatrix * (vec4(vert[c]+p0,1.0)*RotationMatrix);
    gl_FrontColor = gl_FrontColorIn[0] ;
	EmitVertex();
    gl_Position =  gl_ModelViewProjectionMatrix * (vec4(vert[d]+p0,1.0)*RotationMatrix);
    gl_FrontColor = gl_FrontColorIn[0] ;
	EmitVertex();
    
    
    /*
    glBegin(GL_QUADS);
    glColor3fv(color[a]);
    glVertex3fv(ver[a]);
    
    glColor3fv(color[b]);
    glVertex3fv(ver[b]);
    
    glColor3fv(color[c]);
    glVertex3fv(ver[c]);
    
    glColor3fv(color[d]);
    glVertex3fv(ver[d]);
    glEnd();
     */
}


//float a[5] = float[](3.4, 4.2, 5.0, 5.2, 1.1);  // same thing

void main() {
    
    

 //vec3 mmmmm = vec3(vert[0]);
    
    // vec3 mmmmm = vec3(vert[2]);
    //ver[0] = vec2(30,30);
	vec3 p0 = gl_PositionIn[0].xyz;
	vec3 p1 = gl_PositionIn[1].xyz;
    //float sf = a[1];
   
  //  vec3 vera[8] = ver;
    
//uniform vec4 myVar = {0.5, 0.2, 0.7, 1.0};
	
	vec3 up = vec3(0, 0, 1);	// arbitrary up vector
//	
	vec3 dir = normalize( p0);			// normalized direction vector from p0 to p1
 vec3 right = normalize(cross(dir, up));	// right vector
//	vec3 norm = cross(right, dir);
//	float fColMult = abs(dot(norm, lightDir));
//	vec4 colMult = vec4(fColMult, fColMult, fColMult, 1.0);
////	
	right *= thickness;
    
    /*
    float ver[8][3] = array ){
        (-1.0,-1.0,1.0),
        (-1.0,1.0,1.0),
        (1.0,1.0,1.0),
        (1.0,-1.0,1.0),
        (-1.0,-1.0,-1.0),
        (-1.0,1.0,-1.0),
        (1.0,1.0,-1.0),
        (1.0,-1.0,-1.0));
    
    float color[8][3] =
    {
        {0.0,0.0,0.0},
        {1.0,0.0,0.0},
        {1.0,1.0,0.0},
        {0.0,1.0,0.0},
        {0.0,0.0,1.0},
        {1.0,0.0,1.0},
        {1.0,1.0,1.0},
        {0.0,1.0,1.0},
    };
    */
    
//    p0.z = z;
//    p1.z = zq;
    quad(0,3,2,1,p0);
    quad(2,3,7,6,p0);
    quad(0,4,7,3,p0);
    quad(1,2,6,5,p0);
    quad(4,5,6,7,p0);
    quad(0,1,5,4,p0);
    
    
//	gl_Position = gl_ModelViewProjectionMatrix * vec4(p0 - right, 1.0);
//	gl_FrontColor = gl_FrontColorIn[0] ;
//	EmitVertex();
//	
//	gl_Position = gl_ModelViewProjectionMatrix * vec4(p0 + right, 1.0);
//	gl_FrontColor = gl_FrontColorIn[0] ;
//	EmitVertex();
//    
//    
//    gl_Position = gl_ModelViewProjectionMatrix * vec4((p0+thickness) - right, 1.0);
//	gl_FrontColor = gl_FrontColorIn[0] ;
//	EmitVertex();
//	
//	gl_Position = gl_ModelViewProjectionMatrix * vec4((p0+thickness) + right, 1.0);
//	gl_FrontColor = gl_FrontColorIn[0];
//	EmitVertex();
    
   /*
    float z = vec4(p0 - right, 1.0).z;
    float z1 = vec4(p0 + right, 1.0).z;
    float z2 = vec4((p0+thickness) - right, 1.0).z;
      float z3 =vec4((p0+thickness) + right, 1.0).z;
    
    
    vec4 a = vec4(p0 - right, 1.0);
   vec4 a1 = vec4(p0 + right, 1.0);
   vec4 a2 = vec4((p0+thickness) - right, 1.0);
    vec4 a3 =vec4((p0+thickness) + right, 1.0);
    float depth = 10;
    a.z = a.z + depth;
       a1.z = a1.z + depth;
         a2.z = a2.z + depth;
    a3.z = a3.z + depth;
    
    
    gl_Position = gl_ModelViewProjectionMatrix * a3;
	gl_FrontColor = gl_FrontColorIn[0];
	EmitVertex();
    
    gl_Position = gl_ModelViewProjectionMatrix * a ;
	gl_FrontColor = gl_FrontColorIn[0] ;
	EmitVertex();
    
    gl_Position = gl_ModelViewProjectionMatrix * a2;
	gl_FrontColor = gl_FrontColorIn[0] ;
	EmitVertex();
    
    gl_Position = gl_ModelViewProjectionMatrix * a1;
	gl_FrontColor = gl_FrontColorIn[0] ;
	EmitVertex();
    */
//	gl_Position = gl_ModelViewProjectionMatrix * vec4(p1 - right, 1.0);
//	gl_FrontColor = gl_FrontColorIn[1] * colMult;
//	EmitVertex();
//
//	gl_Position = gl_ModelViewProjectionMatrix * vec4(p1 + right, 1.0);
//	gl_FrontColor = gl_FrontColorIn[1] * colMult;
//	EmitVertex();

}