#version 400 core
out vec4 FragColor;
uniform int SCR_WIDTH;
uniform int SCR_HEIGHT;
// uniform vec2 Center;
uniform double Center_x;
uniform double Center_y;
uniform double Scale;
uniform float time_len;
uniform vec2 c;
uniform int loop_time;
uniform float Gamma;
uniform int Show_loop;
uniform int Ctrl;

in vec2 pos;

void main()
{   
    double rate = float(SCR_HEIGHT) / float(SCR_WIDTH);

    double x = pos.x;
    double y = pos.y;
  

    x = x * Scale;
    y = y * Scale;
    x += Center_x;
    y += Center_y;

    vec2 org_pos = vec2(x, y);

    float time = 0;
    
    while (time < loop_time){
        double next_x = x * x - y * y + org_pos.x;
        double next_y = 2 * x * y + org_pos.y;

        x = next_x;
        y = next_y;

        double dis = length(org_pos - vec2(x, y));
        if (dis > 100) break;
        time += 1;
    }

    float color_out = float(time) / loop_time;
    color_out = pow(color_out, Gamma);
    FragColor = vec4(vec3(color_out), 1.0f);
    if (Show_loop == 1)
        if (time >= loop_time) FragColor = vec4(1.0, 1.0, 1.0, 1.0);
        else FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    // if (length(org_pos - c) < 0.05)FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    
}
    