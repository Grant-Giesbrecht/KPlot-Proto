//
//  kpgraphics.hpp
//  SFML Test 1
//
//  Created by Grant Giesbrecht on 9/11/17.
//  Copyright © 2017 IEGA Software. All rights reserved.
//
//
//  Includes functions to help KPlot with graphics.
//
//

#ifndef kpgraphics_hpp
#define kpgraphics_hpp

#include <stdio.h>
#include <vector>
#include <memory>

#include "KTrace.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#define ref_RectangleShape(x) (std::dynamic_pointer_cast<sf::RectangleShape>(x))
#define ref_VertexArray(x) (std::dynamic_pointer_cast<sf::VertexArray>(x))
#define ref_Text(x) (std::dynamic_pointer_cast<sf::Text>(x))
#define ref_CircleShape(x) (std::dynamic_pointer_cast<sf::CircleShape>(x))

typedef std::shared_ptr<sf::Drawable> drawptr;

typedef struct{ //Used to contain data required to convert numeric values to pixel values
    int left_bound;
    int right_bound;
    int top_bound;
    int low_bound;
    double left_val;
    double right_val;
    double top_val;
    double low_val;
}axes_conversion;

void trim_kplot(KTrace& kt, double xMin, double xMax, double yMin, double yMax);

std::vector<KPoint> tessellate_line(KTrace t, int thickness);

std::vector<KPoint> tessellate_line(KTrace t, int thickness, double xMin, double xMax, double yMin, double yMax);

std::vector<std::vector<KPoint> > tessellate_pattern_line(KTrace t, int thickness, int c1, int c2, int c3, int c4, int c5);

void tes_to_vertexarray(std::vector<KPoint> tp, sf::VertexArray* va, sf::Color c);

void tes_to_vertexarray(std::vector<KPoint> tp, drawptr va, sf::Color c);

KPoint numeric_to_pixel(KPoint kp, int left_bound, int right_bound, double left_val, double right_val, int top_bound, int low_bound, double top_val, double low_val);

std::vector<KPoint> numeric_to_pixel(std::vector<KPoint> kp, int left_bound, int right_bound, double left_val, double right_val, int top_bound, int low_bound, double top_val, double low_val);

int x_pixel(double x, axes_conversion ac);

int y_pixel(double y, axes_conversion ac);

KTrace scale_trace(KTrace kt, axes_conversion ac);

//template <typename T>
//std::string to_string_with_precision(const T a_value, const int n = 6);

std::string kurt_string(double a_value, const int max_outsize = 32);

#endif /* kpgraphics_hpp */













