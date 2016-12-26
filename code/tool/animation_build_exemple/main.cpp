#include <iostream>
#include <fstream>

#include "BSON/Document.hh"
 
int main()
{
    bson::Document animations;
    bson::Document animation;
    bson::Document frames;
    bson::Document frame;

    frame << "x" << 10;
    frame << "y" << 20;
    frame << "width" << 30;
    frame << "height" << 40;

    frames << "1" << frame;

    animation << "frequency" << 0.5;
    animation << "frames" << frames;

    animations << "animationTest" << animation;

    std::ofstream out("c++test.anim", std::ios::out | std::ios::binary);
    out.write((const char *)&animations.getBuffer()[0], animations.getBuffer().size());
}
