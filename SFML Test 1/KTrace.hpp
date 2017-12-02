//
//  KTrace.hpp
//  SFML Test 1
//
//  Created by Grant Giesbrecht on 9/9/17.
//  Copyright © 2017 IEGA Software. All rights reserved.
//

#ifndef KTrace_hpp
#define KTrace_hpp

#include <stdio.h>
#include <vector>
#include <cmath>
#include <ctgmath>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#define KT_TYPE_LINE 0
#define KT_TYPE_POINT 1
#define KT_TYPE_FIELD 2

//Line
#define KT_STYLE_STD 0
#define KT_STYLE_DASH 1
#define KT_STYLE_DOT 2
#define KT_STYLE_DASHDOT 3

//Point
#define KT_STYLE_CIRCLE 0 //(Equivilent to STD)
//#define KT_STYLE_STAR 4
#define KT_STYLE_TRIANGLE 5
//#define KT_STYLE_O 6
#define KT_STYLE_CROSSHAIR 7
#define KT_STYLE_SQUARE 8
#define KT_STYLE_OCTOGON 9

typedef struct{
    double x;
    double y;
}KPoint;

class KTrace{
    
public:
    
    KTrace();
    KTrace(std::vector<KPoint> new_vals);
    KTrace(std::vector<KPoint> new_vals, sf::Color nc);
    KTrace(std::vector<KPoint> new_vals, std::vector<sf::Color> new_colors, int cols); //Only for FIELD
    KTrace(std::vector<KPoint> new_vals, std::vector<double> new_field_vals, int cols); //Only for FIELD
    ~KTrace();
    
    void setPoints(std::vector<KPoint> new_vals);
    void addPoint(double x, double y);
    void addPoint(double x, double y, sf::Color c); //Only for FIELD
    
    KPoint& getPoint(int idx, bool& success);
    KPoint& operator()(int idx);
    int size();
    
    void setType(int nt);
    void setThickness(int nt);
    void setStyle(int ns);
    void setColor(sf::Color nc);
    void setCols(int nc);
    void setName(std::string name);
    
    double thickness();
    int type();
    int style();
    int cols(); //Only for FIELD
    std::string name();
    
    sf::Color trace_color;
    
    std::vector<KPoint> points;
    std::vector<sf::Color> field_color; //Only for FIELD
    std::vector<double> field_value; //Only for FIELD - alternative to color
    
private:
  
    int trace_type;
    int trace_style;
    
    int trace_thickness;
    
    int num_cols; //Only for FIELD

    std::string trace_name;
    
    KPoint null_pt;
    
};

double vec_mag(KPoint kp);
KPoint vec_add(KPoint a, KPoint b);
KPoint vec_sub(KPoint a, KPoint b);
KPoint vec_mult(KPoint a, double b);
double vec_dot(KPoint a, KPoint b);

#endif /* KTrace_hpp */
