#version 400 core
out vec4 FragColor;
uniform int SCR_WIDTH;
uniform int SCR_HEIGHT;
uniform vec2 Center;
uniform float Scale;
uniform float time;
uniform vec2 c;

void main()
{   
    double size = (SCR_HEIGHT + SCR_HEIGHT) / 2;
    double x = gl_FragCoord.x - 0.5 * SCR_WIDTH ;
    double y = gl_FragCoord.y - 0.5 * SCR_HEIGHT;
    x = x * Scale / size;
    y = y * Scale / size;
    x += Center.x;
    y += Center.y;

    vec2 org_pos = vec2(x, y);

    float time = 0;
    
    while (time < 255){
        double next_x = pow(float(x), 2) - pow(float(y), 2) + org_pos.x;
        double next_y = 2 * x * y + org_pos.y;

        x = next_x;
        y = next_y;

        double dis = length(org_pos - vec2(x, y));
        if (dis > 100) break;
        time += 1;
    }

    float color_out = time / 255;
    FragColor = vec4(vec3(color_out), 1.0f);
    // if (length(org_pos - c) < 0.05)FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    
}
    