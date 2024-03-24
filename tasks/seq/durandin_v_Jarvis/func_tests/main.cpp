// Copyright 2024 Durandin Vladimir
#include <gtest/gtest.h>

#include "seq/durandin_v_Jarvis/include/ops_seq.hpp"

TEST(VladimirD_Sequential, Convex_Hull_5_Different_Points)
{
    std::vector<Jarvis::Point2d> points = 
    {
        {0,0},
        {2,0},
        {2,2},
        {0,2},
        {1,1}
    };
    std::vector<Jarvis::Point2d> hull = Jarvis::JarvisAlg(points);
    for(int i = 0; i < hull.size(); ++i)
    {
        std::cout << hull[i].x << " " << hull[i].y << std::endl;
    }
}