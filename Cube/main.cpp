#define _USE_MATH_DEFINES
#include<cmath>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

struct vector3
{
    float x,y,z;

};
struct connection
{
    int a;
    int b;
};
VertexArray build_cube(vector<vector3>& points, vector<connection>& connections, int w, int h, float focus_len)
{
    int lenlist = connections.size();
    VertexArray line(Lines, lenlist * 2);
    int i = 0;
    for (auto& conn : connections)
    {
        /*
        float x1 = w/2 + (focus_len * points[conn.a].x)/(focus_len + points[conn.a].z) * 100;
        float y1 = h / 2 + (focus_len * points[conn.a].y) / (focus_len + points[conn.a].z) * 100;
        float x2 = w / 2 + (focus_len * points[conn.b].x) / (focus_len + points[conn.b].z) * 100;
        float y2 = h / 2 + (focus_len * points[conn.b].y) / (focus_len + points[conn.b].z) * 100; */
        float x1 = w / 2 + (points[conn.a].x) * 100;
        float y1 = h / 2 + (points[conn.a].y)* 100;
        float x2 = w / 2 + (points[conn.b].x)* 100;
        float y2 = h / 2 + (points[conn.b].y)* 100;
        line[i].position = Vector2f(x1, y1);
        line[i + 1].position = Vector2f(x2, y2);
        i += 2;
    }
    return line;
}



void rotate(vector3& point, float x = 0, float y = 0, float z = 0)
{
    float rad = 0;
    rad = x * M_PI/180;// yz rotation
    point.y = cos(rad) * point.y - sin(rad) * point.z;
    point.z = sin(rad) * point.y + cos(rad) * point.z;

    rad = y * M_PI / 180;// xz rotation
    point.x = cos(rad) * point.x - sin(rad) * point.z;
    point.z = sin(rad) * point.x + cos(rad) * point.z;

    rad = z * M_PI / 180; //xy rotation
    point.x = cos(rad) * point.x - sin(rad) * point.y;
    point.y = sin(rad) * point.x + cos(rad) * point.y;
}


void rotate_all(vector<vector3>& points, double a, double b, double c)
{

    for (auto& p : points)
    {

        rotate(p, a, b, c);

    }
}



int main()
{
    int resw = 1024;
    int resh = 1024;
    float focus_len = 10000;
    vector<vector3> points{


        {-1,-1,-1},
        {1,-1,-1},
        {1,1,-1},
        {-1,1,-1},

        {-1,-1,1},
        {1,-1,1},
        {1,1,1},
        {-1,1,1}
    };
    vector<connection> connections
    {
        {0,4},
        {1,5},
        {2,6},
        {3,7},

        {0,1},
        {1,2},
        {2,3},
        {3,0},

        {4,5},
        {5,6},
        {6,7},
        {7,4}

    };




    RenderWindow window(VideoMode(resw, resh), L"Новый проект", Style::Default);

    window.setVerticalSyncEnabled(true);
    

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();

            case sf::Event::KeyPressed:
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    rotate_all(points, 0.0, 0.0, 0.7);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    rotate_all(points, 0.0, 0.0, -0.7);
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    rotate_all(points, 0.0, 0.7, 0.0);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    rotate_all(points, 0.0, -0.7, 0.0);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    rotate_all(points, 0.7, 0.0, 0.0);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    rotate_all(points, -0.7, 0.0, 0.0);

                break;
            }


            }
            VertexArray vertexes = build_cube(points, connections, resw, resh, focus_len);
            window.clear(Color::Black);
            window.draw(vertexes);
            window.display();
            vertexes.clear();
        }
    }
    return 0;
}