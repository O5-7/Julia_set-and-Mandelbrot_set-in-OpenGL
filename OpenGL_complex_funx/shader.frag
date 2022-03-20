#version 330 core
out vec4 FragColor;
uniform int SCR_WIDTH;
uniform int SCR_HEIGHT;

uniform vec2 c;

void main()
{   
    float x = gl_FragCoord.x / SCR_WIDTH - 0.5;
    float y = gl_FragCoord.y / SCR_HEIGHT - 0.5;
    x = x * 3;
    y = y * 3;

    vec2 org_pos = vec2(x, y);

    float time = 0;
    
    while (time < 255){
        float next_x = pow(x, 2) - pow(y, 2) + org_pos.x;
        float next_y = 2 * x * y + org_pos.y;

        x = next_x;
        y = next_y;

        float dis = length(org_pos - vec2(x, y));
        if (dis > 10) break;
        time += 1;
    }

    float color_out = time / 255;
    color_out = pow(color_out, 0.3);

    FragColor = vec4(vec3(color_out), 1.0f);
}
    