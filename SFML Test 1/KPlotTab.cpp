//
//  KPlotTab.cpp
//  SFML Test 1
//
//  Created by Grant Giesbrecht on 9/10/17.
//  Copyright © 2017 IEGA Software. All rights reserved.
//

#include "KPlotTab.hpp"

#include <iostream>
#include <stdio.h>

/*
 Constructor
 */
KPlotTab::KPlotTab(){
    int rows = -1;
    int cols = -1;
}

/*
 Add a graph to the tab
 
 ng - new graph to add
 
 Void return
 */
void KPlotTab::add_graph(KGraph ng){
    graphs.push_back(ng);
}

/*
 Deletes the graph specified by 'idx'.
 
 idx - index of graph to delete
 
 Returns true if the graph was found and deleted
 */
bool KPlotTab::deleteGraph(int idx){
    
    if (idx >= graphs.size() || idx < 0){
        return false;
    }
    
    graphs.erase(graphs.begin() + idx);
    return true;
}

/*
 Deletes the graph specified by title
 
 title - name of title (saved in KGraph object) of graph to delete
 
 Returns true if graph found and deleted
 */
bool KPlotTab::deleteGraph(std::string title){
    
    int idx = get_index_form_title(title);
    
    return deleteGraph(idx);
}

/*
 Returns a referece to the graph specified by idx.
 
 idx - index of graph
 success - bool reference in which success state is saved. (True: Graph found and returned, False: Graph not found)
 
 Returns a reference to the graph if found, else it returns an arbitrary KGraph reference.
 */
KGraph& KPlotTab::getGraph(int idx, bool& success){
        
    if (idx >= graphs.size() || idx < 0){
        success = false;
        return null_graph;
    }
    
    success = true;
    
    return graphs[idx];
}

/*
 Returns a referece to the graph specified by title.
 
 title - title of graph
 success - bool reference in which success state is saved. (True: Graph found and returned, False: Graph not found)
 
 Returns a reference to the graph if found, else it returns an arbitrary KGraph reference.
 */
KGraph& KPlotTab::getGraph(std::string title, bool& success){
    
    int idx = get_index_form_title(title);
    
    return getGraph(idx, success);
}

/*
 Specify the dimensions of the tab's grid layout
 
 nrows - new number of rows
 ncols - new number of columns
 
 Void return
 */
void KPlotTab::layout_dimensions(int nrows, int ncols){
    
    rows = nrows;
    cols = ncols;
}

/*
 Specify the location of the specified graph
 
 idx - index of graph
 r - row of location of graph (in terms of the grid-layout, not pixel dimensions)
 c - col of location of graph (in terms of the grid-layout, not pixel dimensions)
 
 Void return
 */
void KPlotTab::graph_location(int idx, int r, int c){
    
    if (idx >= graphs.size() || idx < 0){
        return;
    }
    
    graphs[idx].r_tl = r;
    graphs[idx].c_tl = c;
    graphs[idx].r_br = r;
    graphs[idx].c_br = c;
}

/*
 Specify the location of the specified graph
 
 idx - index of graph
 r_tl - row of location of graph's top left corner (in terms of the grid-layout, not pixel dimensions)
 c_tl - col of location of graph's top left corner (in terms of the grid-layout, not pixel dimensions)
 r_br - row of location of graph's bottom right corner (in terms of the grid-layout, not pixel dimensions)
 c_br - col of location of graph's bottom right corner (in terms of the grid-layout, not pixel dimensions)
 
 Void return
 */
void KPlotTab::graph_location(int idx, int r_tl, int c_tl, int r_br, int c_br){
    
    if (idx >= graphs.size() || idx < 0){
        return;
    }
    
    graphs[idx].r_tl = r_tl;
    graphs[idx].c_tl = c_tl;
    graphs[idx].r_br = r_br;
    graphs[idx].c_br = c_br;
}

/*
 Specify the location of the specified graph
 
 title - title of graph
 r - row of location of graph (in terms of the grid-layout, not pixel dimensions)
 c - col of location of graph (in terms of the grid-layout, not pixel dimensions)
 
 Void return
 */
void KPlotTab::graph_location(std::string title, int r, int c){
    
    int idx = get_index_form_title(title);
    
    graph_location(idx, r, c);
}

/*
 Specify the location of the specified graph
 
 idx - index of graph
 r_tl - row of location of graph's top left corner (in terms of the grid-layout, not pixel dimensions)
 c_tl - col of location of graph's top left corner (in terms of the grid-layout, not pixel dimensions)
 r_br - row of location of graph's bottom right corner (in terms of the grid-layout, not pixel dimensions)
 c_br - col of location of graph's bottom right corner (in terms of the grid-layout, not pixel dimensions)
 
 Void return
 */
void KPlotTab::graph_location(std::string title, int r_tl, int c_tl, int r_br, int c_br){
    
    int idx = get_index_form_title(title);
    
    graph_location(idx, r_tl, c_tl, r_br, c_br);
}

/*
 Draw the tab, including all of the graphs inside the tab.
 */
// ?? Window unneccesary?
void KPlotTab::draw_tab(sf::RenderWindow& window, int left_bound, int right_bound, int top_bound, int low_bound, int window_style, std::vector<std::shared_ptr<sf::Drawable> >& drawings){
    
    //Calculate width & height
    int width = right_bound - left_bound;
    int height = low_bound - top_bound;
    
    int x_label_margin = 35;
    int y_label_margin = 35;
    
    sf::Color xy_label_color = sf::Color::Black;
    int xy_label_font_size = 25;
    
    if (window_style == KP_WSTYLE_BLUEWAVE){
        //Draw background
        drawptr background = std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(width-y_label_margin, height-x_label_margin)));
        ref_RectangleShape(background)->setFillColor(sf::Color(165, 170, 200));
        ref_RectangleShape(background)->setPosition(left_bound+y_label_margin, top_bound);
        drawings.push_back(background);
    }else{ //KP_WINDOW_CLASSIC
        //Draw background
        drawptr background = std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(width-y_label_margin, height-x_label_margin)));
        ref_RectangleShape(background)->setFillColor(sf::Color(255, 255, 255));
        ref_RectangleShape(background)->setPosition(left_bound+y_label_margin, top_bound);
        drawings.push_back(background);
    }
    
    //std::c out << "graphs.size(): " << graphs.size() << std::endl;
    
    //Draw graphs
    if (graphs.size() > 0){ //TODO: Currently only plots first graph - split this up
        
        //std::c out << "about to call draw_graph for first graph. (Graphs size: " << graphs.size() << " )" << std::endl;
        //std::c out << "\tP.S. graphs.traces.size(): " << graphs[0].traces.size() << std::endl;
        draw_graph(window, left_bound+y_label_margin, right_bound, top_bound, low_bound-x_label_margin, window_style, drawings, graphs[0]);
        
        //Label axes of each graph
        drawptr y_label = std::shared_ptr<sf::Text>(new sf::Text);
        ref_Text(y_label)->setFont(graphs[0].tick_font);
        ref_Text(y_label)->setString(graphs[0].y_label);
        ref_Text(y_label)->setFillColor(xy_label_color);
        ref_Text(y_label)->setCharacterSize(xy_label_font_size);
        sf::FloatRect centering_rect = ref_Text(y_label)->getLocalBounds();
        ref_Text(y_label)->setOrigin(centering_rect.left + centering_rect.width/2.0f, centering_rect.top + centering_rect.height/2.0f);
        ref_Text(y_label)->setRotation(270);
        ref_Text(y_label)->setPosition(left_bound-14+y_label_margin, low_bound-(height+x_label_margin)*.5);
        drawings.push_back(y_label);
        
        //Label axes of each graph
        drawptr x_label = std::shared_ptr<sf::Text>(new sf::Text);
        ref_Text(x_label)->setFont(graphs[0].tick_font);
        ref_Text(x_label)->setString(graphs[0].x_label);
        ref_Text(x_label)->setFillColor(xy_label_color);
        ref_Text(x_label)->setCharacterSize(xy_label_font_size);
        centering_rect = ref_Text(x_label)->getLocalBounds();
        ref_Text(x_label)->setOrigin(centering_rect.left + centering_rect.width/2.0f, centering_rect.top);
        ref_Text(x_label)->setPosition(left_bound+(width+y_label_margin)*.5, low_bound-x_label_margin+2);
        drawings.push_back(x_label);
    }
}


// ?? Window unneccesary?
void KPlotTab::draw_graph(sf::RenderWindow& window, int left_bound, int right_bound, int top_bound, int low_bound, int window_style, std::vector<std::shared_ptr<sf::Drawable> >& drawings, KGraph& kg){
    
    //Settings initialized here to KP_WSTYLE_CLASSIC parameters
    
    //Font properties for labels on x & y axes
    int label_font_size = 25;
    int x_label_offset = 3;
    int y_label_offset = 3;
    sf::Color label_color = sf::Color::Black;
    
    //properties for small tick grid
    int small_grid_thickness = 1;
    sf::Color small_grid_color = sf::Color(60, 60, 60);
    
    //Properties for big tick grid
    int grid_thickness = 2;
    sf::Color grid_color = sf::Color(30, 30, 30);
    
    //Properties for axes (x & y axes)
    int axis_thickness = 3;
    sf::Color axis_color = sf::Color::Black;
    
    //Thickness for traces
    int trace_thickness = 3;
    
    if (window_style == KP_WSTYLE_BLUEWAVE){
        //Font properties for labels on x & y axes
        label_font_size = 25;
        x_label_offset = 3;
        y_label_offset = 3;
        label_color = sf::Color::Black;

        //properties for small tick grid
        small_grid_thickness = 1;
        small_grid_color = sf::Color(30, 35, 120);

        //Properties for big tick grid
        grid_thickness = 2;
        grid_color = sf::Color(50, 55, 150);

        //Properties for axes (x & y axes)
        axis_thickness = 3;
        axis_color = sf::Color(80, 85, 220);

        trace_thickness = 4;
    }
    
    //Calculate width & height
    int width = right_bound - left_bound;
    int height = low_bound - top_bound;
    
    //==================== Draw small grid ===========================
    
    axes_conversion ac = {left_bound, right_bound, top_bound, low_bound, kg.x_min, kg.x_max, kg.y_max, kg.y_min};
    
    //X grid
    double x_val = kg.x_max;
    while (x_val >= kg.x_min){
        
        //Add grid line
        KTrace temp;
        temp.addPoint(x_pixel(x_val, ac), y_pixel(kg.y_min, ac));
        temp.addPoint(x_pixel(x_val, ac), y_pixel(kg.y_max, ac));
        drawptr grid_temp = std::shared_ptr<sf::VertexArray>(new sf::VertexArray);
        tes_to_vertexarray( tessellate_line(temp, small_grid_thickness), grid_temp, small_grid_color);
        drawings.push_back(grid_temp);
        
        //Shift x value
        x_val -= kg.xtick_small;
    }
    
//    //Pos X grid
//    x_val = 0;
//    while (x_val <= kg.x_max){
//
//        //Add grid line
//        KTrace temp;
//        temp.addPoint(x_pixel(x_val, ac), y_pixel(kg.y_min, ac));
//        temp.addPoint(x_pixel(x_val, ac), y_pixel(kg.y_max, ac));
//        drawptr grid_temp = std::shared_ptr<sf::VertexArray>(new sf::VertexArray);
//        tes_to_vertexarray( tessellate_line(temp, small_grid_thickness), grid_temp, small_grid_color);
//        drawings.push_back(grid_temp);
//
//        //Shift x value
//        x_val += kg.xtick_small;
//    }
    
    //Y grid
    x_val = kg.y_max;
    while (x_val >= kg.y_min){
        
        //Add grid line
        KTrace temp;
        temp.addPoint(x_pixel(kg.x_min, ac), y_pixel(x_val, ac));
        temp.addPoint(x_pixel(kg.x_max, ac), y_pixel(x_val, ac));
        drawptr grid_temp = std::shared_ptr<sf::VertexArray>(new sf::VertexArray);
        tes_to_vertexarray( tessellate_line(temp, small_grid_thickness), grid_temp, small_grid_color);
        drawings.push_back(grid_temp);
        
        //Shift x value
        x_val -= kg.ytick_small;
    }
    
    //Pos Y grid
//    x_val = 0;
//    while (x_val <= kg.y_max){
//
//        //Add grid line
//        KTrace temp;
//        temp.addPoint(x_pixel(kg.x_min, ac), y_pixel(x_val, ac));
//        temp.addPoint(x_pixel(kg.x_max, ac), y_pixel(x_val, ac));
//        drawptr grid_temp = std::shared_ptr<sf::VertexArray>(new sf::VertexArray);
//        tes_to_vertexarray( tessellate_line(temp, small_grid_thickness), grid_temp, small_grid_color);
//        drawings.push_back(grid_temp);
//
//        //Shift x value
//        x_val += kg.ytick_small;
//    }
    
    //==================== Draw big grid ===========================
    
    
    //X grid
    x_val = kg.x_max;
    while (x_val >= kg.x_min){
        
        //Add grid line
        KTrace temp;
        temp.addPoint(x_pixel(x_val, ac), y_pixel(kg.y_min, ac));
        temp.addPoint(x_pixel(x_val, ac), y_pixel(kg.y_max, ac));
        drawptr grid_temp = std::shared_ptr<sf::VertexArray>(new sf::VertexArray);
        tes_to_vertexarray( tessellate_line(temp, grid_thickness), grid_temp, grid_color);
        drawings.push_back(grid_temp);
        
        //Shift x value
        x_val -= kg.xtick_big;
    }
    
    //Pos X grid
//    x_val = 0;
//    while (x_val <= kg.x_max){
//
//        //Add grid line
//        KTrace temp;
//        temp.addPoint(x_pixel(x_val, ac), y_pixel(kg.y_min, ac));
//        temp.addPoint(x_pixel(x_val, ac), y_pixel(kg.y_max, ac));
//        drawptr grid_temp = std::shared_ptr<sf::VertexArray>(new sf::VertexArray);
//        tes_to_vertexarray( tessellate_line(temp, grid_thickness), grid_temp, grid_color);
//        drawings.push_back(grid_temp);
//
//        //Shift x value
//        x_val += kg.xtick_big;
//    }
    
    //Y grid
    x_val = kg.y_max;
    while (x_val >= kg.y_min){
        
        //Add grid line
        KTrace temp;
        temp.addPoint(x_pixel(kg.x_min, ac), y_pixel(x_val, ac));
        temp.addPoint(x_pixel(kg.x_max, ac), y_pixel(x_val, ac));
        drawptr grid_temp = std::shared_ptr<sf::VertexArray>(new sf::VertexArray);
        tes_to_vertexarray( tessellate_line(temp, grid_thickness), grid_temp, grid_color);
        drawings.push_back(grid_temp);
        
        //Shift x value
        x_val -= kg.ytick_big;
    }
    
    //Pos Y grid
//    x_val = 0;
//    while (x_val <= kg.y_max){
//
//        //Add grid line
//        KTrace temp;
//        temp.addPoint(x_pixel(kg.x_min, ac), y_pixel(x_val, ac));
//        temp.addPoint(x_pixel(kg.x_max, ac), y_pixel(x_val, ac));
//        drawptr grid_temp = std::shared_ptr<sf::VertexArray>(new sf::VertexArray);
//        tes_to_vertexarray( tessellate_line(temp, grid_thickness), grid_temp, grid_color);
//        drawings.push_back(grid_temp);
//
//        //Shift x value
//        x_val += kg.ytick_big;
//    }
    
    
    //========================================= Draw Axes =======================================================
    
    //Y axis
    if (0 >= kg.x_min && 0 <= kg.x_max){
        KTrace y_axis_trace; //Create KTrace ; add points
        y_axis_trace.addPoint(x_pixel(0, ac), y_pixel(kg.y_min, ac));
        y_axis_trace.addPoint(x_pixel(0, ac), y_pixel(kg.y_max, ac));
        drawptr y_axis = std::shared_ptr<sf::VertexArray>(new sf::VertexArray); //Create vertex array
        tes_to_vertexarray(tessellate_line(y_axis_trace, axis_thickness), y_axis, axis_color); //Populate vertex array
        drawings.push_back(y_axis);
    }
    
    //X Axis
    if (0 >= kg.y_min && 0 <= kg.y_max){
        KTrace x_axis_trace; //Create KTrace ; add points
        x_axis_trace.addPoint(x_pixel(kg.x_min, ac), y_pixel(0, ac));
        x_axis_trace.addPoint(x_pixel(kg.x_max, ac), y_pixel(0, ac));
        drawptr x_axis = std::shared_ptr<sf::VertexArray>(new sf::VertexArray); //Create vertex array
        tes_to_vertexarray(tessellate_line(x_axis_trace, axis_thickness), x_axis, axis_color); //Populate vertex array
        drawings.push_back(x_axis);
    }
    
    //======================================== Draw Traces =========================================================
    
//    axes_conversion, drawings, trace, , 
    //std::c out << "This is when I SHOULD draw the traces (size: " << kg.traces.size() << " )" << std::endl;
    for (int i = 0 ; i < kg.traces.size() ; i++){
        draw_trace(kg.traces[i], ac, drawings);
    }
    
    //======================================== Draw Labels =========================================================
    
//    std::cout << "Xmin: " << kg.x_min << " Xmax: " << kg.x_max << " tick_size: " << kg.xtick_num << std::endl;
    
    
    //Neg X axes
    x_val = -1*fmin(kg.xtick_num, kg.x_max);
    while (x_val >= kg.x_min){
        
        //Add label
        drawptr temp_label = std::shared_ptr<sf::Text>(new sf::Text);
        ref_Text(temp_label)->setFont(kg.tick_font);
        ref_Text(temp_label)->setString(kurt_string(x_val));
        ref_Text(temp_label)->setFillColor(label_color);
        ref_Text(temp_label)->setCharacterSize(label_font_size);
        ref_Text(temp_label)->setPosition(x_pixel(x_val, ac), y_pixel(0, ac)+x_label_offset);
        drawings.push_back(temp_label);
        
        //Shift x value
        x_val -= kg.xtick_num;
    }
    
    //Pos X grid
    x_val = fmax(kg.xtick_num, kg.x_min);
    while (x_val <= kg.x_max){
        
        //Add label
        drawptr temp_label = std::shared_ptr<sf::Text>(new sf::Text);
        ref_Text(temp_label)->setFont(kg.tick_font);
        ref_Text(temp_label)->setString(kurt_string(x_val));
        ref_Text(temp_label)->setFillColor(label_color);
        ref_Text(temp_label)->setCharacterSize(label_font_size);
        ref_Text(temp_label)->setPosition(x_pixel(x_val, ac), y_pixel(0, ac)+x_label_offset);
        drawings.push_back(temp_label);
        
        //Shift x value
        x_val += kg.xtick_num;
    }
    
    //Neg Y grid
    x_val = -1*fmin(kg.ytick_num, kg.y_max);
    while (x_val >= kg.y_min){
        
        //Add label
        drawptr temp_label = std::shared_ptr<sf::Text>(new sf::Text);
        ref_Text(temp_label)->setFont(kg.tick_font);
        ref_Text(temp_label)->setString(kurt_string(x_val));
        ref_Text(temp_label)->setFillColor(label_color);
        ref_Text(temp_label)->setCharacterSize(label_font_size);
        ref_Text(temp_label)->setPosition(x_pixel(0, ac)+y_label_offset, y_pixel(x_val, ac));
        drawings.push_back(temp_label);
        
        //Shift x value
        x_val -= kg.ytick_num;
    }
    
    //Pos Y grid
    x_val = fmax(kg.ytick_num, kg.y_min);
    while (x_val <= kg.y_max){
        
        //Add label
        drawptr temp_label = std::shared_ptr<sf::Text>(new sf::Text);
        ref_Text(temp_label)->setFont(kg.tick_font);
        ref_Text(temp_label)->setString(kurt_string(x_val));
        ref_Text(temp_label)->setFillColor(label_color);
        ref_Text(temp_label)->setCharacterSize(label_font_size);
        ref_Text(temp_label)->setPosition(x_pixel(0, ac)+y_label_offset, y_pixel(x_val, ac));
        drawings.push_back(temp_label);
        
        //Shift x value
        x_val += kg.ytick_num;
    }
        
    //Draw ticks
    
    //    std::vector<KPoint> numeric_to_pixel(std::vector<KPoint> kp, int left_bound, int right_bound, double left_val, double right_val, int top_bound, int low_bound, double top_val, double low_val)
    
}

void KPlotTab::draw_trace(KTrace& kt, axes_conversion& ac, std::vector<std::shared_ptr<sf::Drawable> >& drawings){
    
    //std::c out << "drawing trace now" << std::endl;
    
    if (kt.type() == KT_TYPE_LINE){
        std::vector<KTrace> trace_segments = trim_ktrace(kt, ac.left_val, ac.right_val, ac.low_val, ac.top_val);
        for(int i = 0 ; i < trace_segments.size() ; i++){
            drawptr tr = std::shared_ptr<sf::VertexArray>(new sf::VertexArray);
            tes_to_vertexarray(tessellate_line(scale_trace(trace_segments[i], ac), kt.thickness())/*pts_temp*/, tr, kt.trace_color);
            drawings.push_back(tr);
        }
    }else if(kt.type() == KT_TYPE_POINT){
        switch (kt.style()) {
            case KT_STYLE_STD:{
                for (int i = 0 ; i < kt.points.size() ; i++){
                    drawptr pt = std::shared_ptr<sf::CircleShape>(new sf::CircleShape(kt.thickness()/2.0f));
                    ref_CircleShape(pt)->setFillColor(kt.trace_color);
                    ref_CircleShape(pt)->setOrigin(kt.thickness()/2.0f, kt.thickness()/2.0f);
                    ref_CircleShape(pt)->setPosition(x_pixel(kt.points[i].x, ac), y_pixel(kt.points[i].y, ac));
                    drawings.push_back(pt);
                }
                break;
                }
            case KT_STYLE_SQUARE:{
                for (int i = 0 ; i < kt.points.size() ; i++){
                    drawptr pt = std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(kt.thickness(), kt.thickness())));
                    ref_RectangleShape(pt)->setFillColor(kt.trace_color);
                    ref_RectangleShape(pt)->setOrigin(kt.thickness()/2.0f, kt.thickness()/2.0f);
                    ref_RectangleShape(pt)->setPosition(x_pixel(kt.points[i].x, ac), y_pixel(kt.points[i].y, ac));
                    drawings.push_back(pt);
                }
                break;
                }
            case KT_STYLE_TRIANGLE:{
                for (int i = 0 ; i < kt.points.size() ; i++){
                    drawptr pt = std::shared_ptr<sf::CircleShape>(new sf::CircleShape(kt.thickness()/2.0f, 3));
                    ref_CircleShape(pt)->setFillColor(kt.trace_color);
                    ref_CircleShape(pt)->setOrigin(kt.thickness()/2.0f, kt.thickness()/2.0f);
                    ref_CircleShape(pt)->setPosition(x_pixel(kt.points[i].x, ac), y_pixel(kt.points[i].y, ac));
                    drawings.push_back(pt);
                }
                break;
                }
            case KT_STYLE_OCTOGON:{
                for (int i = 0 ; i < kt.points.size() ; i++){
                    drawptr pt = std::shared_ptr<sf::CircleShape>(new sf::CircleShape(kt.thickness()/2.0f, 8));
                    ref_CircleShape(pt)->setFillColor(kt.trace_color);
                    ref_CircleShape(pt)->setOrigin(kt.thickness()/2.0f, kt.thickness()/2.0f);
                    ref_CircleShape(pt)->setPosition(x_pixel(kt.points[i].x, ac), y_pixel(kt.points[i].y, ac));
                    drawings.push_back(pt);
                }
                break;
                }
            case KT_STYLE_CROSSHAIR:{
                for (int i = 0 ; i < kt.points.size() ; i++){
                    drawptr pt = std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(kt.thickness(), kt.thickness()*.25f)));
                    ref_RectangleShape(pt)->setFillColor(kt.trace_color);
                    ref_RectangleShape(pt)->setOrigin(kt.thickness()/2.0f, kt.thickness()*.125f);
                    ref_RectangleShape(pt)->setPosition(x_pixel(kt.points[i].x, ac), y_pixel(kt.points[i].y, ac));
                    drawings.push_back(pt);
                    drawptr pt2 = std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(kt.thickness()*.25f, kt.thickness())));
                    ref_RectangleShape(pt2)->setFillColor(kt.trace_color);
                    ref_RectangleShape(pt2)->setOrigin(kt.thickness()*.125f, kt.thickness()*.5f);
                    ref_RectangleShape(pt2)->setPosition(x_pixel(kt.points[i].x, ac), y_pixel(kt.points[i].y, ac));
                    drawings.push_back(pt2);
                }
                break;
                }
            default:{ //Use STD as default
                for (int i = 0 ; i < kt.points.size() ; i++){
                    drawptr pt = std::shared_ptr<sf::CircleShape>(new sf::CircleShape(kt.thickness()/2.0f));
                    ref_CircleShape(pt)->setFillColor(kt.trace_color);
                    ref_CircleShape(pt)->setOrigin(kt.thickness()/2.0f, kt.thickness()/2.0f);
                    ref_CircleShape(pt)->setPosition(x_pixel(kt.points[i].x, ac), y_pixel(kt.points[i].y, ac));
                    drawings.push_back(pt);
                }
                break;
                }
        }
    }else if(kt.type() == KT_TYPE_FIELD){
        if (kt.points.size() != kt.field_color.size()) {std::cout << "1 " << std::endl; return;} //Ensure color for each point
        if (kt.points.size() % kt.cols() != 0 ) {std::cout << "2: " << kt.points.size() << " @ " <<kt.cols() << std::endl; return;} //Ensure # points goes evenly into cols
        
        drawptr pt = std::shared_ptr<sf::VertexArray>(new sf::VertexArray(sf::Quads));
        
        for (int i = 0 ; i < kt.points.size()-1-kt.cols() ; i++){
            ref_VertexArray(pt)->append(sf::Vertex(sf::Vector2f( x_pixel(kt.points[i].x, ac), y_pixel(kt.points[i].y, ac)  ), kt.field_color[i] ));
            ref_VertexArray(pt)->append(sf::Vertex(sf::Vector2f( x_pixel(kt.points[i+1].x, ac), y_pixel(kt.points[i+1].y, ac)  ), kt.field_color[i+1] ));
            ref_VertexArray(pt)->append(sf::Vertex(sf::Vector2f( x_pixel(kt.points[i+kt.cols()+1].x, ac), y_pixel(kt.points[i+kt.cols()+1].y, ac)  ), kt.field_color[i+kt.cols()+1] ));
            ref_VertexArray(pt)->append(sf::Vertex(sf::Vector2f( x_pixel(kt.points[i+kt.cols()].x, ac), y_pixel(kt.points[i+kt.cols()].y, ac)), kt.field_color[i+kt.cols()] ));
            
//            ref_VertexArray(pt)->setFillColor(kt.trace_color);
//            ref_VertexArray(pt)->setOrigin(kt.thickness()/2.0f, kt.thickness()/2.0f);
//            ref_VertexArray(pt)->setPosition(x_pixel(kt.points[i].x, ac), y_pixel(kt.points[i].y, ac));
        }
        
        drawings.push_back(pt);
        
    }
}

// ================================== Private Functions =================================

/*
 Returns the index of the first graph with the title 'title'.
 
 title - title to search for
 
 Returns index if found, if not title match, returns -1
 */
int KPlotTab::get_index_form_title(std::string title){
    
    for (int i = 0 ; i < graphs.size() ; i++){
        if (graphs[i].getTitle() == title){
            return i;
        }
    }
    
    return -1;
}


























