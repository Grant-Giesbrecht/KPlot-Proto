//
//  kpgraphics.cpp
//  SFML Test 1
//
//  Created by Grant Giesbrecht on 9/11/17.
//  Copyright © 2017 IEGA Software. All rights reserved.
//


#include "kpgraphics.hpp"

#include <iostream>
#include <stdio.h>
#include <sstream>
#include <iomanip>

using namespace std;

/*
 Converts a single KTrace into a vector of KTraces so all traces are contained within the bound area. TODO: Won't yet register when trace passes through region without having any points land in it.
 
 KTrace - ktrace to trim
 xMin - x lower bound
 xMax - x upper bound
 yMin - y lower bound
 yMax - y upper bound
 
 Returns vector of ktraces
 */
std::vector<KTrace> trim_ktrace(KTrace kt, double xMin, double xMax, double yMin, double yMax){ //watch the divide by zeros! When x = 0, b calc goes to hell. Probably other divide by zero bugs too. May also be root of issue with tessellation b/c error occured at y-axis! Divide by zero like a wrecking crew - well that crew just wrecked the hell out of kpgraphics.
    
    std::vector<KTrace> traces;
    vector<KTrace> returned_traces;
    KTrace temp_trace;
    bool in_area = false;
    KPoint temp_pt;
    double m, b; //slope, y-intercept
    for (int i = 0 ; i < kt.points.size() ; i++){
        cout << i << "\t " << kt.points[i].x  << " " << kt.points[i].y << endl;
        
        if (in_area){
            if (kt.points[i].x > xMax || kt.points[i].x < xMin || kt.points[i].y < yMin || kt.points[i].y > yMax){ //outside area
                //moved from in to outside area, calculate edge point and push back
                
                //calculate edge point
                if (kt.points[i].x > xMax){
                    temp_pt.x = xMax;
                    m = ((kt.points[i].y-kt.points[i-1].y)/(kt.points[i].x-kt.points[i-1].x));
                    if ((kt.points[i].x-kt.points[i-1].x) == 0){ //Case: ∆X = 0
                        temp_pt.x = kt.points[i].x;
                    }else{ //default
                        if (kt.points[i-1].x == 0){ //Case: X_last = 0
                            b = kt.points[i-1].y;
                        }else{ //default
                            b = (kt.points[i-1].y - (m*kt.points[i-1].x));
                        }
                        cout << "m: " << m << " xMax: " << xMax <<" b: " << b << endl;
                        temp_pt.y = m*xMax + b; /*just y=mx+b*/
                    }
                }else if(kt.points[i].x < xMin){
                    temp_pt.x = xMin;
                    m = ((kt.points[i].y-kt.points[i-1].y)/(kt.points[i].x-kt.points[i-1].x));
                    if ((kt.points[i].x-kt.points[i-1].x) == 0){ //Case: ∆X = 0
                        temp_pt.x = kt.points[i].x;
                    }else{ //default
                        if (kt.points[i-1].x == 0){ //Case: X_last = 0
                            b = kt.points[i-1].y;
                        }else{ //default
                            b = (kt.points[i-1].y - (m*kt.points[i-1].x));
                        }
                        cout << "m: " << m << " xMax: " << xMax <<" b: " << b << endl;
                        temp_pt.y = m*xMin + b; /*just y=mx+b*/
                    }
                }else if(kt.points[i].y < yMin){
                    temp_pt.y = yMin;
                    m = ((kt.points[i].y-kt.points[i-1].y)/(kt.points[i].x-kt.points[i-1].x));
                    if ((kt.points[i].x-kt.points[i-1].x) == 0){ //Case: ∆X = 0
                        temp_pt.x = kt.points[i].x;
                    }else{ //default
                        if (kt.points[i-1].x == 0){ //Case: X_last = 0
                            b = kt.points[i-1].y;
                        }else{ //default
                            b = (kt.points[i-1].y - (m*kt.points[i-1].x));
                        }
                        cout << "m: " << m << " yMin: " << xMax <<" b: " << b << endl;
                        temp_pt.x = (yMin - b)/m; /*just y=mx+b -> x = (y-b)/m*/
                    }
                }else{ //(kt.points[i].y > yMax) must be true
                    temp_pt.y = yMax;
                    m = ((kt.points[i].y-kt.points[i-1].y)/(kt.points[i].x-kt.points[i-1].x));
                    if ((kt.points[i].x-kt.points[i-1].x) == 0){ //Case: ∆X = 0
                        temp_pt.x = kt.points[i].x;
                    }else{ //default
                        if (kt.points[i-1].x == 0){ //Case: X_last = 0
                            b = kt.points[i-1].y;
                        }else{ //default
                            b = (kt.points[i-1].y - (m*kt.points[i-1].x));
                        }
                        cout << "m: " << m << " yMin: " << xMax <<" b: " << b << endl;
                        temp_pt.x = (yMax - b)/m; /*just y=mx+b -> x = (y-b)/m*/
                    }
                }
                
                in_area = false;
                
                //add calculated point to trace via standard procedure
                cout << "\t\t" << temp_pt.x << " " << temp_pt.y << " " << m <<endl;
                temp_trace.points.push_back(temp_pt);
                
                //If a line enters or exits the graph are by violating two boundaries (exceeds x&y max, for example),
                //only one of the violations will be fixed. We loop through the new trace again to ensure all is well
                //and that any multi-bound violations are fully corrected.
                returned_traces = trim_ktrace(temp_trace, xMin, xMax, yMin, yMax);
                for (int a = 0 ; a < returned_traces.size() ; a++){
                    traces.push_back(returned_traces[a]);
                }
                
                
            }else{
                //Was and still is in area, record point
                temp_trace.points.push_back(kt.points[i]);
            }
        }else{
            if (kt.points[i].x > xMax || kt.points[i].x < xMin || kt.points[i].y < yMin || kt.points[i].y > yMax){ //outside area
                //do nothing
            }else{
                //moved from outside to inside, calculate edge point and start new trace
                
                temp_trace.points.clear();
                in_area = true;
                
                if (i > 0){
                    
                    //calculate edge point
                    if (kt.points[i-1].x > xMax){
                        temp_pt.x = xMax;
                        m = ((kt.points[i].y-kt.points[i-1].y)/(kt.points[i].x-kt.points[i-1].x));
                        if ((kt.points[i].x-kt.points[i-1].x) == 0){ //Case: ∆X = 0
                            temp_pt.x = kt.points[i].x;
                        }else{ //default
                            if (kt.points[i-1].x == 0){ //Case: X_last = 0
                                b = kt.points[i-1].y;
                            }else{ //default
                                b = (kt.points[i-1].y - (m*kt.points[i-1].x));
                            }
                            cout << "m: " << m << " xMax: " << xMax <<" b: " << b << endl;
                            temp_pt.y = m*xMax + b; /*just y=mx+b*/
                        }
                    }else if(kt.points[i-1].x < xMin){
                        temp_pt.x = xMin;
                        m = ((kt.points[i].y-kt.points[i-1].y)/(kt.points[i].x-kt.points[i-1].x));
                        if ((kt.points[i].x-kt.points[i-1].x) == 0){ //Case: ∆X = 0
                            temp_pt.x = kt.points[i].x;
                        }else{ //default
                            if (kt.points[i-1].x == 0){ //Case: X_last = 0
                                b = kt.points[i-1].y;
                            }else{ //default
                                b = (kt.points[i-1].y - (m*kt.points[i-1].x));
                            }
                            cout << "m: " << m << " xMax: " << xMax <<" b: " << b << endl;
                            temp_pt.y = m*xMin + b; /*just y=mx+b*/
                        }
                    }else if(kt.points[i-1].y < yMin){
                        temp_pt.y = yMin;
                        m = ((kt.points[i].y-kt.points[i-1].y)/(kt.points[i].x-kt.points[i-1].x));
                        if ((kt.points[i].x-kt.points[i-1].x) == 0){ //Case: ∆X = 0
                            temp_pt.x = kt.points[i].x;
                        }else{ //default
                            if (kt.points[i-1].x == 0){ //Case: X_last = 0
                                b = kt.points[i-1].y;
                            }else{ //default
                                b = (kt.points[i-1].y - (m*kt.points[i-1].x));
                            }
                            cout << "m: " << m << " yMin: " << xMax <<" b: " << b << endl;
                            temp_pt.x = (yMin - b)/m; /*just y=mx+b -> x = (y-b)/m*/
                        }
                    }else{ //(kt.points[i-1].y > yMax) must be true
                        temp_pt.y = yMax;
                        m = ((kt.points[i].y-kt.points[i-1].y)/(kt.points[i].x-kt.points[i-1].x));
                        if ((kt.points[i].x-kt.points[i-1].x) == 0){ //Case: ∆X = 0
                            temp_pt.x = kt.points[i].x;
                        }else{ //default
                            if (kt.points[i-1].x == 0){ //Case: X_last = 0
                                b = kt.points[i-1].y;
                            }else{ //default
                                b = (kt.points[i-1].y - (m*kt.points[i-1].x));
                            }
                            cout << "m: " << m << " yMin: " << xMax <<" b: " << b << endl;
                            temp_pt.x = (yMax - b)/m; /*just y=mx+b -> x = (y-b)/m*/
                        }
                    }
                    
                    //add calculated and actual point to trace
                    cout << "\t\t" << temp_pt.x << " " << temp_pt.y << " " << m << endl;
                    temp_trace.points.push_back(temp_pt);
                    temp_trace.points.push_back(kt.points[i]);
                }else{ //Is first point - started inside region - no point calculation required
                    temp_trace.points.push_back(kt.points[i]);
                }
            }// end if( OUTSIDE AREA LOGIC ) statement
        }//end if(in_area) statement
    }//end for loop (iterating through all trace points)
    
    if (traces.size() == 0){
        traces.push_back(temp_trace);
    }
    
    return traces;
}

/*
 Converts a line with no thickness to a vector of tessellated points from which a thick line can be rendered.
 
 t - trace to tesselate
 thickness - thickness of the line (in pixels)
 
 Returns a vector of KPoints constituting the tessellated trace.
 */
std::vector<KPoint> tessellate_line(KTrace t, int thickness){ //TODO: Accomodate repeated points (by deleting copy)
    
    vector<KPoint> pts;
    
    //Ensure t contains at least 2 points
    if (t.size() < 2){
        return pts;
    }
    
    //Determine vector components for each line segment
    KPoint A;
    vector<KPoint> m; //x & y not being used for position, rather ∆x & ∆y for slope
    for (int i = 1 ; i < t.size() ; i++){
        KPoint kpt = {t(i).x - t(i-1).x, t(i).y - t(i-1).y};
        m.push_back(kpt);
    }
    
    // ======== Calculate tessellation vertices for first point ==========
    
    //Calculate A-vector & scale
    A.x = -1*m[0].y;
    A.y = m[0].x;
    double mag = vec_mag(A);
    if (mag != 0){ //TODO: enable points to overlap
        A = vec_mult(A, thickness/2.0/mag);
    }

    //Calculate verticies
    pts.push_back(vec_add(t(0), A));
    pts.push_back(vec_sub(t(0), A));
    
    KPoint p1 = vec_sub(t(0), A);
    KPoint p2 = vec_add(t(0), A);
    
    // ======= Calculate tessellation verticies for middle points ==========
    
    bool swap_order = false;
    for (int i = 1 ; i < m.size() ; i++){
        
        //Check magnitudes not zero
        if (vec_mag(m[i]) == 0 || vec_mag(m[i-1]) == 0) continue;
        
        //Calculate A-vector & A magnitude
        double T;
        A = vec_sub( vec_mult(m[i], 1/vec_mag(m[i])), vec_mult(m[i-1], 1/vec_mag(m[i-1])) );
        if ((abs(A.x) <= 1e-14 && A.y <= 1e-14) || (isnan(A.x) && isnan(A.y))){
            A.x = -1*m[i].y;
            A.y = m[i].x;
            T = thickness;
        }else{
            T = thickness/sin(( 3.1415926535 - acos( vec_dot(m[i], m[i-1])/vec_mag(m[i])/vec_mag(m[i-1]) ) )/2);
        }
        KPoint save = A;
        A = vec_mult(A, .5);
        
        //check magnitude not zero
        if (vec_mag(A) == 0) continue;
        
        //Scale A
//        double T = thickness/sin(( 3.1415926535 - acos( vec_dot(m[i], m[i-1])/vec_mag(m[i])/vec_mag(m[i-1]) ) )/2);
        A = vec_mult(A, T/2.0/vec_mag(A));

        //Calculate verticies
        p1 = vec_add(t(i), A);
        p2 = vec_sub(t(i), A);
        
//        if (isnan(p1.x) || isnan(p1.y) || isnan(p2.x) || isnan(p2.y)){
//            //c out << "NAN, OH FUCK!: " << p1.x << " " << p1.y  << " " << p2.x << " " << p2.y << std::endl;
//            //c out << "\tMag: " << vec_mag(A) << endl;
//            //c out << "\tA: " << A.x << ", " << A.y << endl;
//            //c out << "\tm[i], m[i-1]:"  << m[i].x << ", " << m[i].y << " | " << m[i-1].x << " " << m[i-1].y << endl;
//            //c out << "vec_mag(m[i]), vec_mag(m[i-1]): " << vec_mag(m[i]) << " " << vec_mag(m[i-1]) << endl;
//            //c out << vec_mult(m[i], 1/vec_mag(m[i])).x << " " << vec_mult(m[i], 1/vec_mag(m[i])).y << endl;
//            //c out << "\t\t\t" << A.x << " " << A.y << endl;
//            //c out << "\t\t\t" << save.x << " " << save.y << endl;
//            //c out << T << endl;
//        }
        
        //Order verticies correctly
        if ((pts[i*2-2].y != pts[i*2-1].y) && (p1.y != p2.y)){
            if ((pts[i*2-2].y > pts[i*2-1].y && p1.y > p2.y) || (pts[i*2-2].y < pts[i*2-1].y && p1.y < p2.y)){
                pts.push_back(p1);
                pts.push_back(p2);
            }else{
                pts.push_back(p2);
                pts.push_back(p1);
            }
        }else{
            if ((pts[i*2-2].x > pts[i*2-1].x && p1.x > p2.x) || (pts[i*2-2].x < pts[i*2-1].x && p1.x < p2.x)){
                pts.push_back(p1);
                pts.push_back(p2);
            }else{
                pts.push_back(p2);
                pts.push_back(p1);
            }
        }
        
    }
    if (m.size() <= 1) swap_order = !swap_order;
    
    // ======== Calculate tessellation verticies for final point
    
    //Calculate A-vector & scale
    A.x = -1*m[m.size()-1].y;
    A.y = m[m.size()-1].x;
    mag = vec_mag(A);
    A = vec_mult(A, thickness/2.0/mag);
    
    //Calculate verticies
    p1 = vec_sub(t(t.size()-1), A);
    p2 = vec_add(t(t.size()-1), A);
    
    //Order verticies correctly
    if ((pts[pts.size()-2].y != pts[pts.size()-1].y) && (p1.y != p2.y)){
        if ((pts[pts.size()-2].y > pts[pts.size()-1].y && p1.y > p2.y) || (pts[pts.size()-2].y < pts[pts.size()-1].y && p1.y < p2.y)){
            pts.push_back(p1);
            pts.push_back(p2);
        }else{
            pts.push_back(p2);
            pts.push_back(p1);
        }
    }else{
        if ((pts[pts.size()-2].x > pts[pts.size()-1].x && p1.x > p2.x) || (pts[pts.size()-2].x < pts[pts.size()-1].x && p1.x < p2.x)){
            pts.push_back(p1);
            pts.push_back(p2);
        }else{
            pts.push_back(p2);
            pts.push_back(p1);
        }
    }

    //Return tessellation verticies
    return pts;
}



/*
 Converts a line with no thickness to a set of vectors of tessellated points. Each set of points can be used to make a small line segment, all of these segments (in the outermost vector) constitue the origional line broken up into the pattern described by c1-5.
 
 t - trace to segment and tesselate
 thickness - thickness of line in pixels
 c1-5 - (pattern description terms) size (in pixels) of each component of the repeating pattern to use in segmenting 't'. If one is set to -1, it and the following pattern description terms will be ignored and the repeat will begin.
 
 Returns a vector of vectors of KPoints constituting the tesselated and segmented trace.
 */
std::vector<std::vector<KPoint> > tessellate_pattern_line(KTrace t, int thickness, int c1, int c2, int c3, int c4, int c5){
    
}

/*
 Converts a series of points indicating the verticies of a trianglestrip vertex array to the vertexarray it represents.
 
 tp - tessellated points (aka vertex points)
 va - vertexarray to modify
 c - color to make 'va'
 
 Void return
 */
void tes_to_vertexarray(std::vector<KPoint> tp, sf::VertexArray* va, sf::Color c){
    
    //Set VA settings
    va->clear();
    va->resize(tp.size());
    va->setPrimitiveType(sf::TriangleStrip);
    
    //Add points
    for (int i = 0 ; i < tp.size() ; i++){
        va->append(sf::Vertex(sf::Vector2f(tp[i].x, tp[i].y), c));
    }
    
}

/*
 Converts a series of points indicating the verticies of a trianglestrip vertex array to the vertexarray (containted in a drawptr) it represents.
 
 tp - tessellated points (aka vertex points)
 va - drawptr to modify
 c - color to make 'va'
 
 Void return
 */
void tes_to_vertexarray(std::vector<KPoint> tp, drawptr va, sf::Color c){
    
    //Set VA settings
    ref_VertexArray(va)->clear();
    ref_VertexArray(va)->resize(tp.size());
    ref_VertexArray(va)->setPrimitiveType(sf::TriangleStrip);
    
    //Add points
    for (int i = 0 ; i < tp.size() ; i++){
        (*ref_VertexArray(va))[i] = sf::Vertex(sf::Vector2f(tp[i].x, tp[i].y), c);
//        //c out << "Added - x: " << tp[i].x << " y: " << tp[i].y << endl;
    }
    
}

/*
 Scales a single kpoint so numeric values are translated to pixel values
 
 kp - kpoint
 left_bound - left bound (pixels)
 right_bound - right bound (pixels)
 left_val - left axis value
 right_val - right axis value
 top_bound - top bound (pixels)
 low_bound - lower bound (pixels)
 top_val - top axis value
 low_val - lower axis value
 
 Returns the translated point
 */
KPoint numeric_to_pixel(KPoint kp, int left_bound, int right_bound, double left_val, double right_val, int top_bound, int low_bound, double top_val, double low_val){
    
//    kp.x *= abs((right_bound - left_bound)/(right_val - left_val));
//    kp.y *= abs((low_bound - top_bound)/(top_val - low_val));
    
    kp.x = (kp.x - left_val) * abs((right_bound - left_bound)/(right_val - left_val)) + left_bound;
    kp.y = (kp.y - low_val) * -1*abs((low_bound - top_bound)/(top_val - low_val)) + low_bound;
    
    return kp;
}

/*
 Scales a vector of kpoints so numeric values are translated to pixel values
 
 kp - kpoint vector
 left_bound - left bound (pixels)
 right_bound - right bound (pixels)
 left_val - left axis value
 right_val - right axis value
 top_bound - top bound (pixels)
 low_bound - lower bound (pixels)
 top_val - top axis value
 low_val - lower axis value
 
 Returns the translated point
 */
std::vector<KPoint> numeric_to_pixel(std::vector<KPoint> kp, int left_bound, int right_bound, double left_val, double right_val, int top_bound, int low_bound, double top_val, double low_val){

    double m_width = abs((right_bound - left_bound)/(right_val - left_val));
    double m_height = -1*abs((low_bound - top_bound)/(top_val - low_val));
    
    for (int i = 0 ; i < kp.size() ; i++){
        kp[i].x = (kp[i].x - left_val) * m_width + left_bound;
        kp[i].y = (kp[i].y - low_val) * m_height + low_bound;
    }
    
    return kp;
}

/*
 Scales a vector of kpoints so numeric values are translated to pixel values
 
 kp - kpoint vector
 ac - axes_conversion struct containing conversion data
 
 Returns the translated point
 */
KPoint numeric_to_pixel(KPoint kp, axes_conversion ac){
    return numeric_to_pixel(kp, ac.left_bound, ac.right_bound, ac.left_val, ac.right_val, ac.top_bound, ac.low_bound, ac.top_val, ac.low_val);
}

/*
 Scales a kpoint so numeric values are translated to pixel values
 
 kp - kpoint
 ac - axes_conversion struct containing conversion data
 
 Returns the translated point
 */
std::vector<KPoint> numeric_to_pixel(std::vector<KPoint> kp, axes_conversion ac){
    return numeric_to_pixel(kp,ac.left_bound, ac.right_bound, ac.left_val, ac.right_val, ac.top_bound, ac.low_bound, ac.top_val, ac.low_val);
}

int x_pixel(double x, axes_conversion ac){
    
    KPoint temp = {x, 0};
    return numeric_to_pixel(temp, ac).x;
    
}

int y_pixel(double y, axes_conversion ac){
    
    KPoint temp = {0, y};
    return numeric_to_pixel(temp, ac).y;
    
}

KTrace scale_trace(KTrace kt, axes_conversion ac){
    
    KTrace n = kt;
    n.points = numeric_to_pixel(kt.points, ac);
    
    return n;
    
}

//template <typename T>
//std::string to_string_with_precision(const T a_value, const int n){
//    std::ostringstream out;
//    out << std::setprecision(n) << a_value;
//    return out.str();
//}

std::string kurt_string(double a_value, const int max_outsize){
    char buffer[max_outsize];
    snprintf(buffer, sizeof(buffer), "%g", a_value);
    return string(buffer);
//    std::ostringstream out;
//    out << std::setprecision(n) << a_value;
//    return out.str();
}






