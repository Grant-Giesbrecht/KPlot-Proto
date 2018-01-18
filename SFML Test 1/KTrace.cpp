//
//  KTrace.cpp
//  SFML Test 1
//
//  Created by Grant Giesbrecht on 9/9/17.
//  Copyright © 2017 IEGA Software. All rights reserved.
//
//
//  This class is only a wrapper for info about a trace in a KGraph. It doesn't do any plotting
//  because it is only used to make the code more organized.
//
//

#include "KTrace.hpp"

#include <iostream>

using namespace std;

/*
 KTrace default contructor
 */
KTrace::KTrace(){
//    KTrace::trace_color = sf::Color::Black;
    KTrace::trace_color = sf::Color::Blue;
    
    null_pt = {-1, -1};
    trace_type  = KT_TYPE_LINE;
    trace_style = KT_STYLE_STD;
    
    KTrace::trace_thickness = 3;
    
    use_secondary_axis = false;
    
    trace_name = "Trace";
}

/*
 Constructor
 
 new_vals - vector of KPoints with which to initialze trace.
 */
KTrace::KTrace(std::vector<KPoint> new_vals){
    KTrace::points = new_vals;
    KTrace::trace_color = sf::Color::Black;
    
    null_pt = {-1, -1};
    trace_type  = KT_TYPE_LINE;
    trace_style = KT_STYLE_STD;
    
    KTrace::trace_thickness = 3;
    
    use_secondary_axis = false;
    
    trace_name = "Trace";
}

/*
 Constructor
 
 new_vals - vector of KPoints with which to initialze trace.
 nc - color of trace
 */
KTrace::KTrace(std::vector<KPoint> new_vals, sf::Color nc){
    KTrace::points = new_vals;
    KTrace::trace_color = nc;
    
    null_pt = {-1, -1};
    trace_type  = KT_TYPE_LINE;
    trace_style = KT_STYLE_STD;
    
    KTrace::trace_thickness = 3;
    
    use_secondary_axis = false;
    
    trace_name = "Trace";
}

/*
 Constructor for field type
 
 new_vals - vector of KPoints at which colors are defined
 new_colors - vector of colors at above points
 */
KTrace::KTrace(std::vector<KPoint> new_vals, std::vector<sf::Color> new_colors, int cols){
    KTrace::points = new_vals;
    KTrace::field_color = new_colors;
    KTrace::num_cols = cols;
    
    null_pt = {-1, -1};
    trace_type = KT_TYPE_FIELD;
    trace_style = KT_STYLE_STD;
    
    KTrace::trace_thickness = 3;
    
    use_secondary_axis = false;
    
    trace_name = "Trace";
}

/*
 Constructor for field type
 
 new_vals - vector of KPoints at which values are defined
 new_field_vales - vector of doubles at above points. Automatically converted to a color specturm
 */
KTrace::KTrace(std::vector<KPoint> new_vals, std::vector<double> new_field_vals, int cols){
    KTrace::points = new_vals;
    KTrace::field_value = new_field_vals;
    KTrace::num_cols = cols;
    
    null_pt = {-1, -1};
    trace_type = KT_TYPE_FIELD;
    trace_style = KT_STYLE_STD;
    
    KTrace::trace_thickness = 3;
    
    use_secondary_axis = false;
    
    trace_name = "Trace";
}

/*
 Destructor
 */
KTrace::~KTrace(){
    
}

/*
 Specify the points for the KTrace object (overrides any old points)
 
 new_vals - vector of KPoints with which to intialize trace
 
 Void return
 */
void KTrace::setPoints(std::vector<KPoint> new_vals){
    KTrace::points = new_vals;
}

/*
 Set num_cols
 
 nc - new value
 */
void KTrace::setCols(int nc){
    num_cols = nc;
    trace_type = KT_TYPE_FIELD;
}

/*
 Add a point to the trace
 
 x - x component
 y - y component
 
 Void return
 */
void KTrace::addPoint(double x, double y){
    KPoint kpt = {x, y};
    KTrace::points.push_back(kpt);
}

void KTrace::addPoint(double x, double y, sf::Color c){
    KPoint kpt = {x, y};
    KTrace::points.push_back(kpt);
    KTrace::field_color.push_back(c);
}

/*
 Get a copy of the KPoint specified by 'idx'. (Same as operator())
 
 idx - index of point
 
 Returns the
 */
KPoint& KTrace::getPoint(int idx, bool& success){

    //Protect bounds
    if (idx >= KTrace::points.size() || idx < 0){
        success = false;
        return null_pt;
    }
    
    success = true;
    return KTrace::points[idx];
}

/*
 Returns the thicnkess of the trace
 */
double KTrace::thickness(){
    return (double)trace_thickness;
}

/*
 Returns the type of the trace
 */
int KTrace::type(){
    return trace_type;
}

/*
 Returns the style of the trace
 */
int KTrace::style(){
    return trace_style;
}

/*
 Returns the number of columns
 */
int KTrace::cols(){
    return num_cols;
}

/*
 Get a copy of the KPoint specified by 'idx'. (Same as getPoint())
 
 idx - index of point
 
 Returns the
 */
KPoint& KTrace::operator()(int idx){
    
    //Protect bounds
    if (idx >= KTrace::points.size() || idx < 0){
        return null_pt;
    }
    
    return KTrace::points[idx];
}


/*
 Return number of points in trace
 */
int KTrace::size(){
    return KTrace::points.size();
}

/*
 Return the name of the trace
 */
std::string KTrace::name(){
    return KTrace::trace_name;
}

/*
 Set trace color
 
 nc - new color
 
 Void return
 */
void KTrace::setColor(sf::Color nc){
    KTrace::trace_color = nc;
}

/*
 Set trace type
 
 nt - new trace type
 
 Void return
 */
void KTrace::setType(int nt){
    KTrace::trace_type = nt;
}

/*
 Set trace style
 
 ns - new style
 
 Void return
 */
void KTrace::setStyle(int ns){
    KTrace::trace_style = ns;
}

/*
 Set thickness
 
 nt - new thickness
 
 Void return
 */
void KTrace::setThickness(int nt){
    KTrace::trace_thickness = nt;
}

/*
 Set name
 
 nt - new name
 
 Void return
 */
void KTrace::setName(std::string name){
    KTrace::trace_name = name;
}

/*
 Get magnitude of KPoint (as a vector)
 
 kp - KPoint to measure
 
 Returns magnitude
 */
double vec_mag(KPoint kp){
    return sqrt( kp.x*kp.x + kp.y*kp.y );
}

/*
 Return vector addition of KPoints a & b. Operation: ret a+b
 
 a - vector 1
 b - vector 2
 
 Returns a+b KPoint
 */
KPoint vec_add(KPoint a, KPoint b){
    KPoint kp = {a.x + b.x, a.y + b.y};
    return kp;
}

/*
 Return vector subtraction of KPoints a & b. Operation: ret a-b
 
 a - vector 1
 b - vector 2
 
 Returns a-b KPoint
 */
KPoint vec_sub(KPoint a, KPoint b){
    KPoint kp = {a.x - b.x, a.y - b.y};
    return kp;
}

/*
 Return vector multiplication of KPoint a & double b. Operation: ret a*b
 
 a - vector
 b - scalar multiple
 
 Returns KPoint a*b
 */
KPoint vec_mult(KPoint a, double b){
    KPoint kp = {a.x*b, a.y*b};
    return kp;
}

/*
 Return dot product of KPoint a & KPoint b. Operation: ret a dot b
 
 a - vector
 b - vector
 
 Returns KPoint a dot b
 */
double vec_dot(KPoint a, KPoint b){
//    //std::c out << "a.x: " << a.x << " a.y" << a.y << " b.x " << b.x << " b.y " << b.y << endl;
    return a.x * b.x + a.y * b.y;
}













