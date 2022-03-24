#version 330 core
out vec4 FragColor;
uniform int SCR_WIDTH;
uniform int SCR_HEIGHT;
uniform float PI;
uniform vec2 Center;
uniform float Scale;
uniform vec2 c;

void main()
{   
    float x = gl_FragCoord.x / SCR_WIDTH - 0.5;
    float y = gl_FragCoord.y / SCR_HEIGHT - 0.5;
    x = x * Scale;
    y = y * Scale;
    x += Center.x;
    y += Center.y;

    float angle;
    if (y == 0){
        if (x == 0) angle = -1;
        if (x > 0) angle = 0;
        if (x < 0) angle = PI;
    }
    else {
        if (y > 0) angle = atan(x / y);
        else angle = atan(x / y) + PI;
    }

    vec3 color;

    if (angle != -1){
        color = vec3(sin(angle) + 1, sin(angle + PI * 2 / 3) + 1, sin(angle + PI * 4 / 3) + 1);
        color = color / 2;
    } 
    else (color = vec3(1.0f));
    FragColor = vec4(color, 1.0f);

}
    