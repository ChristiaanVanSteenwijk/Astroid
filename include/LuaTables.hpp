#ifndef Tables
#define Tables

struct Ships
{
    std::string name, image;
    float x, y, angle;
} ships[] =
{
    {"Enemy", "img/alien4.png", 500, 500, 0},
    {"Cruiser", "img/alien4.png", 800, 400, 0},
    {NULL, NULL, 0, 0, 0}  //sentinel
};

#endif // Tables
