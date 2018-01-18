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
 Returns the number of graphs in the tab
 
 No arguments
 
 Return number of graphs
 */
int KPlotTab::numGraphs(){
    return graphs.size();
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
 Draws the tab, including all of the graphs inside the tab.
 
 window -
 left_bound -
 right_bound -
 top_bound -
 low_bound -
 window_style -
 drawings -
 
 Void return
 */
// ?? Window unneccesary?

/*
 What to do...
 currently the program technically works, but not really. The new options system i am implementing is not yet fully supported. I am going through and finding in the graphics software where style decisions are made and having them reference the new options bank. draw_tab is a mess - it can not draw multiple graphs, it references old hardcoded styles, and other crap. Shouldn't be too hard to fix, but do it. Then look for other hard-coded styles or just clean up graphics system in KPlotTab.
 
    I also need to update the main objects for correct programming style, update KPlot to access the options, and then go through and correct all of the then outdated code accessing now private variables.
 
 */

void KPlotTab::draw_tab(sf::RenderWindow& window, int left_bound, int right_bound, int top_bound, int low_bound, int window_style, std::vector<std::shared_ptr<sf::Drawable> >& drawings){
    
    //Calculate width & height
    int width = right_bound - left_bound;
    int height = low_bound - top_bound;
    
    //Draw graphs -
    if (graphs.size() > 0){ //TODO: Currently only plots first graph - allow multiple graphs to be drawn
        int g = 0; //Will replace with for loop when I no longer ain't nobody got time for that
        
        //Room to leave for X&Y labels (will need to add more margins if secondary axes are displayed. Need to add to list of configurable options
//        int x_label_margin = 35;
//        int y_label_margin = 35;
        
//        sf::Color xy_label_color = sf::Color::Black;
//        int xy_label_font_size = 25;
        
        //=====================================================================
        //======================= DRAW GRAPH BACKGROUND =======================
        
        //Calculate background size
        float background_width = width;
        float background_height = height;
        if (graphs[g].options.draw_exterior_x_numerals){ //If primary exterior X-axis enabled, trim graph accordingly
            height -= graphs[g].options.x_label_margin;
        }
        if (width -= graphs[g].options.draw_exterior_y_numerals){ //If primary exterior Y-axis enabled, trim graph accordingly
            width -= graphs[g].options.y_label_margin;
        }
        if (graphs[g].options.draw_secondary_exterior_y_numerals){ //If secondary axes enabled (and drawing y-axis), trim graph area appropriately
            background_width -= graphs[g].options.y_sec_label_margin;
        }
        if (graphs[g].options.draw_secondary_exterior_x_numerals){ //If secondary axes enabled (and drawing X-axis), trim graph area appropriately
            background_height -= graphs[g].options.x_sec_label_margin;
        }
        
        //Calculate background boundaries
        int left_graph_bound = left_bound;
        int right_graph_bound = right_bound;
        int top_graph_bound = top_bound;
        int low_graph_bound = low_bound;
        if (graphs[g].options.draw_exterior_x_numerals){
            low_graph_bound -= graphs[g].options.x_label_margin;
        }
        if (graphs[g].options.draw_exterior_y_numerals){
            left_graph_bound += graphs[g].options.y_label_margin;
        }
        if (graphs[g].options.draw_secondary_exterior_x_numerals){
            top_graph_bound += graphs[g].options.x_sec_label_margin;
        }
        if (graphs[g].options.draw_secondary_exterior_y_numerals){
            right_bound -= graphs[g].options.y_sec_label_margin;
        }
        
        //Create & position background rectangle
        drawptr background = std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(background_width, background_height)));
        ref_RectangleShape(background)->setFillColor(graphs[g].options.background_color);
        if (graphs[g].options.draw_secondary_exterior_x_numerals){ //If secondary axis X-numerals being drawn on top, move graph down accordingly
            ref_RectangleShape(background)->setPosition(left_bound+graphs[g].options.y_label_margin, top_bound+graphs[g].options.x_sec_label_margin);
        }else{
            ref_RectangleShape(background)->setPosition(left_bound+graphs[g].options.y_label_margin, top_bound);
        }
    
        //Draw graph
        draw_graph(window, left_graph_bound, right_graph_bound, top_graph_bound, low_graph_bound, window_style, drawings, graphs[g]);
        
        //=====================================================================
        //========================= DRAW GRAPH LABELS =========================
        
        //Define axes_conversion object
        axes_conversion ac = {left_graph_bound, right_graph_bound, top_graph_bound, low_graph_bound, graphs[g].x_min, graphs[g].x_max, graphs[g].y_max, graphs[g].y_min};
        
        //Label axes of each graph
        sf::FloatRect centering_rect;
        
        //Create X-Axis label
        drawptr x_label = std::shared_ptr<sf::Text>(new sf::Text);
        ref_Text(x_label)->setFont(graphs[g].options.main_font);
        ref_Text(x_label)->setString(graphs[g].x_label);
        ref_Text(x_label)->setFillColor(graphs[g].options.label_color);
        ref_Text(x_label)->setCharacterSize(graphs[g].options.label_font_size);
        centering_rect = ref_Text(x_label)->getLocalBounds();
        ref_Text(x_label)->setOrigin(centering_rect.width*.5, 0);
        if (graphs[g].options.draw_exterior_x_numerals){
            ref_Text(x_label)->setPosition((right_graph_bound+left_graph_bound)*.5, low_bound-graphs[g].options.x_label_margin+2+graphs[g].options.x_numeral_height_exterior);
        }else{
            ref_Text(x_label)->setPosition((right_graph_bound+left_graph_bound)*.5, low_bound-graphs[g].options.x_label_margin+2);
        }
        
        drawings.push_back(x_label);
        
        //Create Y-Axis label
        drawptr y_label = std::shared_ptr<sf::Text>(new sf::Text);
        ref_Text(y_label)->setFont(graphs[0].options.main_font);
        ref_Text(y_label)->setString(graphs[0].y_label);
        ref_Text(y_label)->setFillColor(graphs[g].options.label_color);
        ref_Text(y_label)->setCharacterSize(graphs[g].options.label_font_size);
        centering_rect = ref_Text(y_label)->getLocalBounds();
        ref_Text(y_label)->setOrigin(centering_rect.left + centering_rect.width/2.0f, centering_rect.top + centering_rect.height/2.0f);
        ref_Text(y_label)->setRotation(270);
        if (graphs[g].options.draw_exterior_x_numerals){
            ref_Text(y_label)->setPosition(left_bound-14+graphs[g].options.y_label_margin - graphs[g].options.y_numeral_height_exterior, (top_graph_bound + low_graph_bound)*.5);
        }else{
            ref_Text(y_label)->setPosition(left_bound-14+graphs[g].options.y_label_margin, (top_graph_bound + low_graph_bound)*.5);
        }
        drawings.push_back(y_label);
        
        //=====================================================================
        //========================== DRAW GRAPH TITLE =========================
        
        //Create Title
        drawptr title_label = std::shared_ptr<sf::Text>(new sf::Text);
        ref_Text(title_label)->setFont(graphs[g].options.main_font);
        ref_Text(title_label)->setString(graphs[g].title);
        ref_Text(title_label)->setFillColor(graphs[g].options.label_color);
        ref_Text(title_label)->setCharacterSize(graphs[g].options.title_font_size);
        centering_rect = ref_Text(title_label)->getLocalBounds();
        ref_Text(title_label)->setOrigin(centering_rect.width*.5, centering_rect.top + centering_rect.height);
        if (graphs[g].options.draw_secondary_exterior_x_numerals){
            ref_Text(title_label)->setPosition((right_graph_bound+left_graph_bound)*.5, top_graph_bound - graphs[g].options.title_offset  - graphs[g].options.x_numeral_height_exterior);
        }else{
            ref_Text(title_label)->setPosition((right_graph_bound+left_graph_bound)*.5, top_graph_bound - graphs[g].options.title_offset);
        }
        drawings.push_back(title_label);
        
        //=====================================================================
        //====================== DRAW EXTERIOR NUMERALS =======================
        
        if (graphs[g].options.draw_exterior_x_numerals){
            
            //Neg X exterior numerals (and zero)
            double x_val = fmin(0, graphs[g].x_max);
            double remainder = (x_val / graphs[g].xtick_num);
            if ( remainder != floor(remainder)){ //Ensure that numerals are spaced at integer multiples of numeral relative to zero, not x_max.
                x_val = graphs[g].xtick_num*floor(remainder);
            }
            while (x_val >= graphs[g].x_min){
                
                //Add label
                drawptr temp_label = std::shared_ptr<sf::Text>(new sf::Text);
                ref_Text(temp_label)->setFont(graphs[g].options.main_font);
                ref_Text(temp_label)->setString(kurt_string(x_val));
                ref_Text(temp_label)->setFillColor(graphs[g].options.label_color);
                ref_Text(temp_label)->setCharacterSize(graphs[g].options.label_font_size);
                centering_rect = ref_Text(temp_label)->getLocalBounds();
                ref_Text(temp_label)->setOrigin(centering_rect.width*.5, 0);
                ref_Text(temp_label)->setPosition(x_pixel(x_val, ac), low_graph_bound-graphs[g].options.x_label_offset+2);
                drawings.push_back(temp_label);
                
                //Shift x value
                x_val -= graphs[g].xtick_num;
            }

            
            //Pos X exterior numerals
            x_val = fmax(graphs[g].xtick_num, graphs[g].x_min);
            remainder = (x_val / graphs[g].xtick_num);
            if ( remainder != floor(remainder)){ //Ensure that numerals are spaced at integer multiples of numeral relative to zero, not x_max.
                x_val = graphs[g].xtick_num*ceil(remainder);
            }
            while (x_val <= graphs[g].x_max){
                
                //Add label
                drawptr temp_label = std::shared_ptr<sf::Text>(new sf::Text);
                ref_Text(temp_label)->setFont(graphs[g].options.main_font);
                ref_Text(temp_label)->setString(kurt_string(x_val));
                ref_Text(temp_label)->setFillColor(graphs[g].options.label_color);
                ref_Text(temp_label)->setCharacterSize(graphs[g].options.label_font_size);
                centering_rect = ref_Text(temp_label)->getLocalBounds();
                ref_Text(temp_label)->setOrigin(centering_rect.width*.5, 0);
                ref_Text(temp_label)->setPosition(x_pixel(x_val, ac), low_graph_bound-graphs[g].options.x_label_offset+2);
                drawings.push_back(temp_label);
                
                //Shift x value
                x_val += graphs[g].xtick_num;
            }
        }
        if (graphs[g].options.draw_exterior_y_numerals){
            
            //Neg Y exterior numerals (and zero)
            double x_val = fmin(0, graphs[g].y_max);
            double remainder = (x_val / graphs[g].ytick_num);
            if ( remainder != floor(remainder)){ //Ensure that numerals are spaced at integer multiples of numeral relative to zero, not x_max.
                x_val = graphs[g].ytick_num*floor(remainder);
            }
            while (x_val >= graphs[g].y_min){
                
                //Add label
                drawptr temp_label = std::shared_ptr<sf::Text>(new sf::Text);
                ref_Text(temp_label)->setFont(graphs[g].options.main_font);
                ref_Text(temp_label)->setString(kurt_string(x_val));
                ref_Text(temp_label)->setFillColor(graphs[g].options.label_color);
                ref_Text(temp_label)->setCharacterSize(graphs[g].options.label_font_size);
                centering_rect = ref_Text(temp_label)->getLocalBounds();
                ref_Text(temp_label)->setOrigin(centering_rect.left + centering_rect.width, centering_rect.top + centering_rect.height/2.0f);
//                ref_Text(temp_label)->setRotation(270);
                ref_Text(temp_label)->setPosition(left_graph_bound - graphs[g].options.y_label_offset+2, y_pixel(x_val, ac));
                drawings.push_back(temp_label);
                
                //Shift x value
                x_val -= graphs[g].ytick_num;
            }
            
            
            //Pos Y exterior numerals
            x_val = fmax(graphs[g].ytick_num, graphs[g].y_min);
            remainder = (x_val / graphs[g].ytick_num);
            if ( remainder != floor(remainder)){ //Ensure that numerals are spaced at integer multiples of numeral relative to zero, not x_max.
                x_val = graphs[g].ytick_num*ceil(remainder);
            }
            while (x_val <= graphs[g].y_max){
                
                //Add label
                drawptr temp_label = std::shared_ptr<sf::Text>(new sf::Text);
                ref_Text(temp_label)->setFont(graphs[g].options.main_font);
                ref_Text(temp_label)->setString(kurt_string(x_val));
                ref_Text(temp_label)->setFillColor(graphs[g].options.label_color);
                ref_Text(temp_label)->setCharacterSize(graphs[g].options.label_font_size);
                centering_rect = ref_Text(temp_label)->getLocalBounds();
                ref_Text(temp_label)->setOrigin(centering_rect.left + centering_rect.width, centering_rect.top + centering_rect.height/2.0f);
                //                ref_Text(temp_label)->setRotation(270);
                ref_Text(temp_label)->setPosition(left_graph_bound - graphs[g].options.y_label_offset+2, y_pixel(x_val, ac));
                drawings.push_back(temp_label);
                
                //Shift x value
                x_val += graphs[g].ytick_num;
            }
        }
        if (graphs[g].options.draw_secondary_exterior_x_numerals){
            
        }
        if (graphs[g].options.draw_secondary_exterior_y_numerals){
            
        }
        
    }
}


//new draw_graph
void KPlotTab::draw_graph(sf::RenderWindow& window, int left_bound, int right_bound, int top_bound, int low_bound, int window_style, std::vector<std::shared_ptr<sf::Drawable> >& drawings, KGraph& kg){

    
    //Calculate width & height
    int width = right_bound - left_bound;
    int height = low_bound - top_bound;
    
    //==================== Draw small grid ===========================
    
    double x_val;
    double remainder;
    axes_conversion ac = {left_bound, right_bound, top_bound, low_bound, kg.x_min, kg.x_max, kg.y_max, kg.y_min};
    if (kg.options.draw_small_grid){
        
        //X grid
        x_val = kg.x_max;
        remainder = (x_val / kg.xtick_small);
        if ( remainder != floor(remainder)){ //Ensure that grid lines are spaced at integer multiples of xtick relative to zero, not x_max.
            x_val = kg.xtick_small*floor(remainder);
        }
        while (x_val >= kg.x_min){
            
            //Add grid line
            KTrace temp;
            temp.addPoint(x_pixel(x_val, ac), y_pixel(kg.y_min, ac));
            temp.addPoint(x_pixel(x_val, ac), y_pixel(kg.y_max, ac));
            drawptr grid_temp = std::shared_ptr<sf::VertexArray>(new sf::VertexArray);
            tes_to_vertexarray( tessellate_line(temp, kg.options.small_grid_thickness), grid_temp, kg.options.small_grid_color);
            drawings.push_back(grid_temp);
            
            //Shift x value
            x_val -= kg.xtick_small;
        }
        
        //Y grid
        x_val = kg.y_max;
        remainder = (x_val / kg.ytick_small);
        if ( remainder != floor(remainder)){ //Ensure that grid lines are spaced at integer multiples of ytick relative to zero, not y_max.
            x_val = kg.ytick_small*floor(remainder);
        }
        while (x_val >= kg.y_min){
            
            //Add grid line
            KTrace temp;
            temp.addPoint(x_pixel(kg.x_min, ac), y_pixel(x_val, ac));
            temp.addPoint(x_pixel(kg.x_max, ac), y_pixel(x_val, ac));
            drawptr grid_temp = std::shared_ptr<sf::VertexArray>(new sf::VertexArray);
            tes_to_vertexarray( tessellate_line(temp, kg.options.small_grid_thickness), grid_temp, kg.options.small_grid_color);
            drawings.push_back(grid_temp);
            
            //Shift x value
            x_val -= kg.ytick_small;
        }
    }
    
    //==================== Draw big grid ===========================
    
    if (kg.options.draw_big_grid){
        
        //X grid
        x_val = kg.x_max;
        remainder = (x_val / kg.xtick_big);
        if ( remainder != floor(remainder)){ //Ensure that grid lines are spaced at integer multiples of xtick relative to zero, not x_max.
            x_val = kg.xtick_big*floor(remainder);
        }
        while (x_val >= kg.x_min){
            
            //Add grid line
            KTrace temp;
            temp.addPoint(x_pixel(x_val, ac), y_pixel(kg.y_min, ac));
            temp.addPoint(x_pixel(x_val, ac), y_pixel(kg.y_max, ac));
            drawptr grid_temp = std::shared_ptr<sf::VertexArray>(new sf::VertexArray);
            tes_to_vertexarray( tessellate_line(temp, kg.options.big_grid_thickness), grid_temp, kg.options.big_grid_color);
            drawings.push_back(grid_temp);
            
            //Shift x value
            x_val -= kg.xtick_big;
        }
        
        //Y grid
        x_val = kg.y_max;
        remainder = (x_val / kg.ytick_big);
        if ( remainder != floor(remainder)){ //Ensure that grid lines are spaced at integer multiples of ytick relative to zero, not y_max.
            x_val = kg.ytick_big*floor(remainder);
        }
        while (x_val >= kg.y_min){
            
            //Add grid line
            KTrace temp;
            temp.addPoint(x_pixel(kg.x_min, ac), y_pixel(x_val, ac));
            temp.addPoint(x_pixel(kg.x_max, ac), y_pixel(x_val, ac));
            drawptr grid_temp = std::shared_ptr<sf::VertexArray>(new sf::VertexArray);
            tes_to_vertexarray( tessellate_line(temp, kg.options.big_grid_thickness), grid_temp, kg.options.big_grid_color);
            drawings.push_back(grid_temp);
            
            //Shift x value
            x_val -= kg.ytick_big;
        }
    }
    
   
    
    
    //========================================= Draw Axes =======================================================
    
    //Y axis
    if (0 >= kg.x_min && 0 <= kg.x_max){
        KTrace y_axis_trace; //Create KTrace ; add points
        y_axis_trace.addPoint(x_pixel(0, ac), y_pixel(kg.y_min, ac));
        y_axis_trace.addPoint(x_pixel(0, ac), y_pixel(kg.y_max, ac));
        drawptr y_axis = std::shared_ptr<sf::VertexArray>(new sf::VertexArray); //Create vertex array
        tes_to_vertexarray(tessellate_line(y_axis_trace, kg.options.axes_thickness), y_axis, kg.options.axes_color); //Populate vertex array
        drawings.push_back(y_axis);
    }
    
    //X Axis
    if (0 >= kg.y_min && 0 <= kg.y_max){
        KTrace x_axis_trace; //Create KTrace ; add points
        x_axis_trace.addPoint(x_pixel(kg.x_min, ac), y_pixel(0, ac));
        x_axis_trace.addPoint(x_pixel(kg.x_max, ac), y_pixel(0, ac));
        drawptr x_axis = std::shared_ptr<sf::VertexArray>(new sf::VertexArray); //Create vertex array
        tes_to_vertexarray(tessellate_line(x_axis_trace, kg.options.axes_thickness), x_axis, kg.options.axes_color); //Populate vertex array
        drawings.push_back(x_axis);
    }
    
    //======================================== Draw Traces =========================================================
    
    //    axes_conversion, drawings, trace, ,
    //std::c out << "This is when I SHOULD draw the traces (size: " << kg.traces.size() << " )" << std::endl;
    for (int i = 0 ; i < kg.traces.size() ; i++){
        draw_trace(kg.traces[i], ac, drawings);
    }
    
    //======================================== Draw In-Graph Numerals =========================================================
    
    //Draw x in-graph numerals
    if (kg.options.draw_in_graph_numerals_x){
        
        //Neg X in graph numerals
        x_val = -1*fmin(kg.xtick_num, kg.x_max);
        while (x_val >= kg.x_min){
            
            //Add label
            drawptr temp_label = std::shared_ptr<sf::Text>(new sf::Text);
            ref_Text(temp_label)->setFont(kg.options.tick_font);
            ref_Text(temp_label)->setString(kurt_string(x_val));
            ref_Text(temp_label)->setFillColor(kg.options.label_color);
            ref_Text(temp_label)->setCharacterSize(kg.options.label_font_size);
            ref_Text(temp_label)->setPosition(x_pixel(x_val, ac), y_pixel(0, ac)+kg.options.x_label_offset);
            drawings.push_back(temp_label);
            
            //Shift x value
            x_val -= kg.xtick_num;
        }
        
        //Pos X in graph numerals
        x_val = fmax(kg.xtick_num, kg.x_min);
        while (x_val <= kg.x_max){
            
            //Add label
            drawptr temp_label = std::shared_ptr<sf::Text>(new sf::Text);
            ref_Text(temp_label)->setFont(kg.options.tick_font);
            ref_Text(temp_label)->setString(kurt_string(x_val));
            ref_Text(temp_label)->setFillColor(kg.options.label_color);
            ref_Text(temp_label)->setCharacterSize(kg.options.label_font_size);
            ref_Text(temp_label)->setPosition(x_pixel(x_val, ac), y_pixel(0, ac)+kg.options.x_label_offset);
            drawings.push_back(temp_label);
            
            //Shift x value
            x_val += kg.xtick_num;
        }
    }
    
    //Draw y in-graph numerals
    if (kg.options.draw_in_graph_numerals_y){
        
        //Neg Y in graph numerals
        x_val = -1*fmin(kg.ytick_num, kg.y_max);
        while (x_val >= kg.y_min){
            
            //Add label
            drawptr temp_label = std::shared_ptr<sf::Text>(new sf::Text);
            ref_Text(temp_label)->setFont(kg.options.tick_font);
            ref_Text(temp_label)->setString(kurt_string(x_val));
            ref_Text(temp_label)->setFillColor(kg.options.label_color);
            ref_Text(temp_label)->setCharacterSize(kg.options.label_font_size);
            ref_Text(temp_label)->setPosition(x_pixel(0, ac)+kg.options.y_label_offset, y_pixel(x_val, ac));
            drawings.push_back(temp_label);
            
            //Shift x value
            x_val -= kg.ytick_num;
        }
        
        //Pos Y in graph numerals
        x_val = fmax(kg.ytick_num, kg.y_min);
        while (x_val <= kg.y_max){
            
            //Add label
            drawptr temp_label = std::shared_ptr<sf::Text>(new sf::Text);
            ref_Text(temp_label)->setFont(kg.options.tick_font);
            ref_Text(temp_label)->setString(kurt_string(x_val));
            ref_Text(temp_label)->setFillColor(kg.options.label_color);
            ref_Text(temp_label)->setCharacterSize(kg.options.label_font_size);
            ref_Text(temp_label)->setPosition(x_pixel(0, ac)+kg.options.y_label_offset, y_pixel(x_val, ac));
            drawings.push_back(temp_label);
            
            //Shift x value
            x_val += kg.ytick_num;
        }
    }
    
    //Draw ticks
    
    //    std::vector<KPoint> numeric_to_pixel(std::vector<KPoint> kp, int left_bound, int right_bound, double left_val, double right_val, int top_bound, int low_bound, double top_val, double low_val)
    
}

////old draw_graph
//void KPlotTab::draw_graph(sf::RenderWindow& window, int left_bound, int right_bound, int top_bound, int low_bound, int window_style, std::vector<std::shared_ptr<sf::Drawable> >& drawings, KGraph& kg){
//
//    //Settings initialized here to KP_WSTYLE_CLASSIC parameters
//
//    //Font properties for labels on x & y axes
//    int label_font_size = 25;
//    int x_label_offset = 3;
//    int y_label_offset = 3;
//    sf::Color label_color = sf::Color::Black;
//
//    //properties for small tick grid
//    int small_grid_thickness = 1;
//    sf::Color small_grid_color = sf::Color(60, 60, 60);
//
//    //Properties for big tick grid
//    int grid_thickness = 2;
//    sf::Color grid_color = sf::Color(30, 30, 30);
//
//    //Properties for axes (x & y axes)
//    int axis_thickness = 3;
//    sf::Color axis_color = sf::Color::Black;
//
//    //Thickness for traces
//    int trace_thickness = 3;
//
//    if (window_style == KP_WSTYLE_BLUEWAVE){
//        //Font properties for labels on x & y axes
//        label_font_size = 25;
//        x_label_offset = 3;
//        y_label_offset = 3;
//        label_color = sf::Color::Black;
//
//        //properties for small tick grid
//        small_grid_thickness = 1;
//        small_grid_color = sf::Color(30, 35, 120);
//
//        //Properties for big tick grid
//        grid_thickness = 2;
//        grid_color = sf::Color(50, 55, 150);
//
//        //Properties for axes (x & y axes)
//        axis_thickness = 3;
//        axis_color = sf::Color(80, 85, 220);
//
//        trace_thickness = 4;
//    }
//
//    //Calculate width & height
//    int width = right_bound - left_bound;
//    int height = low_bound - top_bound;
//
//    //==================== Draw small grid ===========================
//
//    axes_conversion ac = {left_bound, right_bound, top_bound, low_bound, kg.x_min, kg.x_max, kg.y_max, kg.y_min};
//
//    //X grid
//    double x_val = kg.x_max;
//    while (x_val >= kg.x_min){
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
//        x_val -= kg.xtick_small;
//    }
//
////    //Pos X grid
////    x_val = 0;
////    while (x_val <= kg.x_max){
////
////        //Add grid line
////        KTrace temp;
////        temp.addPoint(x_pixel(x_val, ac), y_pixel(kg.y_min, ac));
////        temp.addPoint(x_pixel(x_val, ac), y_pixel(kg.y_max, ac));
////        drawptr grid_temp = std::shared_ptr<sf::VertexArray>(new sf::VertexArray);
////        tes_to_vertexarray( tessellate_line(temp, small_grid_thickness), grid_temp, small_grid_color);
////        drawings.push_back(grid_temp);
////
////        //Shift x value
////        x_val += kg.xtick_small;
////    }
//
//    //Y grid
//    x_val = kg.y_max;
//    while (x_val >= kg.y_min){
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
//        x_val -= kg.ytick_small;
//    }
//
//    //Pos Y grid
////    x_val = 0;
////    while (x_val <= kg.y_max){
////
////        //Add grid line
////        KTrace temp;
////        temp.addPoint(x_pixel(kg.x_min, ac), y_pixel(x_val, ac));
////        temp.addPoint(x_pixel(kg.x_max, ac), y_pixel(x_val, ac));
////        drawptr grid_temp = std::shared_ptr<sf::VertexArray>(new sf::VertexArray);
////        tes_to_vertexarray( tessellate_line(temp, small_grid_thickness), grid_temp, small_grid_color);
////        drawings.push_back(grid_temp);
////
////        //Shift x value
////        x_val += kg.ytick_small;
////    }
//
//    //==================== Draw big grid ===========================
//
//
//    //X grid
//    x_val = kg.x_max;
//    while (x_val >= kg.x_min){
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
//        x_val -= kg.xtick_big;
//    }
//
//    //Pos X grid
////    x_val = 0;
////    while (x_val <= kg.x_max){
////
////        //Add grid line
////        KTrace temp;
////        temp.addPoint(x_pixel(x_val, ac), y_pixel(kg.y_min, ac));
////        temp.addPoint(x_pixel(x_val, ac), y_pixel(kg.y_max, ac));
////        drawptr grid_temp = std::shared_ptr<sf::VertexArray>(new sf::VertexArray);
////        tes_to_vertexarray( tessellate_line(temp, grid_thickness), grid_temp, grid_color);
////        drawings.push_back(grid_temp);
////
////        //Shift x value
////        x_val += kg.xtick_big;
////    }
//
//    //Y grid
//    x_val = kg.y_max;
//    while (x_val >= kg.y_min){
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
//        x_val -= kg.ytick_big;
//    }
//
//    //Pos Y grid
////    x_val = 0;
////    while (x_val <= kg.y_max){
////
////        //Add grid line
////        KTrace temp;
////        temp.addPoint(x_pixel(kg.x_min, ac), y_pixel(x_val, ac));
////        temp.addPoint(x_pixel(kg.x_max, ac), y_pixel(x_val, ac));
////        drawptr grid_temp = std::shared_ptr<sf::VertexArray>(new sf::VertexArray);
////        tes_to_vertexarray( tessellate_line(temp, grid_thickness), grid_temp, grid_color);
////        drawings.push_back(grid_temp);
////
////        //Shift x value
////        x_val += kg.ytick_big;
////    }
//
//
//    //========================================= Draw Axes =======================================================
//
//    //Y axis
//    if (0 >= kg.x_min && 0 <= kg.x_max){
//        KTrace y_axis_trace; //Create KTrace ; add points
//        y_axis_trace.addPoint(x_pixel(0, ac), y_pixel(kg.y_min, ac));
//        y_axis_trace.addPoint(x_pixel(0, ac), y_pixel(kg.y_max, ac));
//        drawptr y_axis = std::shared_ptr<sf::VertexArray>(new sf::VertexArray); //Create vertex array
//        tes_to_vertexarray(tessellate_line(y_axis_trace, axis_thickness), y_axis, axis_color); //Populate vertex array
//        drawings.push_back(y_axis);
//    }
//
//    //X Axis
//    if (0 >= kg.y_min && 0 <= kg.y_max){
//        KTrace x_axis_trace; //Create KTrace ; add points
//        x_axis_trace.addPoint(x_pixel(kg.x_min, ac), y_pixel(0, ac));
//        x_axis_trace.addPoint(x_pixel(kg.x_max, ac), y_pixel(0, ac));
//        drawptr x_axis = std::shared_ptr<sf::VertexArray>(new sf::VertexArray); //Create vertex array
//        tes_to_vertexarray(tessellate_line(x_axis_trace, axis_thickness), x_axis, axis_color); //Populate vertex array
//        drawings.push_back(x_axis);
//    }
//
//    //======================================== Draw Traces =========================================================
//
////    axes_conversion, drawings, trace, ,
//    //std::c out << "This is when I SHOULD draw the traces (size: " << kg.traces.size() << " )" << std::endl;
//    for (int i = 0 ; i < kg.traces.size() ; i++){
//        draw_trace(kg.traces[i], ac, drawings);
//    }
//
//    //======================================== Draw Labels =========================================================
//
////    std::cout << "Xmin: " << kg.x_min << " Xmax: " << kg.x_max << " tick_size: " << kg.xtick_num << std::endl;
//
//
//    //Neg X axes
//    x_val = -1*fmin(kg.xtick_num, kg.x_max);
//    while (x_val >= kg.x_min){
//
//        //Add label
//        drawptr temp_label = std::shared_ptr<sf::Text>(new sf::Text);
//        ref_Text(temp_label)->setFont(kg.tick_font);
//        ref_Text(temp_label)->setString(kurt_string(x_val));
//        ref_Text(temp_label)->setFillColor(label_color);
//        ref_Text(temp_label)->setCharacterSize(label_font_size);
//        ref_Text(temp_label)->setPosition(x_pixel(x_val, ac), y_pixel(0, ac)+x_label_offset);
//        drawings.push_back(temp_label);
//
//        //Shift x value
//        x_val -= kg.xtick_num;
//    }
//
//    //Pos X grid
//    x_val = fmax(kg.xtick_num, kg.x_min);
//    while (x_val <= kg.x_max){
//
//        //Add label
//        drawptr temp_label = std::shared_ptr<sf::Text>(new sf::Text);
//        ref_Text(temp_label)->setFont(kg.tick_font);
//        ref_Text(temp_label)->setString(kurt_string(x_val));
//        ref_Text(temp_label)->setFillColor(label_color);
//        ref_Text(temp_label)->setCharacterSize(label_font_size);
//        ref_Text(temp_label)->setPosition(x_pixel(x_val, ac), y_pixel(0, ac)+x_label_offset);
//        drawings.push_back(temp_label);
//
//        //Shift x value
//        x_val += kg.xtick_num;
//    }
//
//    //Neg Y grid
//    x_val = -1*fmin(kg.ytick_num, kg.y_max);
//    while (x_val >= kg.y_min){
//
//        //Add label
//        drawptr temp_label = std::shared_ptr<sf::Text>(new sf::Text);
//        ref_Text(temp_label)->setFont(kg.tick_font);
//        ref_Text(temp_label)->setString(kurt_string(x_val));
//        ref_Text(temp_label)->setFillColor(label_color);
//        ref_Text(temp_label)->setCharacterSize(label_font_size);
//        ref_Text(temp_label)->setPosition(x_pixel(0, ac)+y_label_offset, y_pixel(x_val, ac));
//        drawings.push_back(temp_label);
//
//        //Shift x value
//        x_val -= kg.ytick_num;
//    }
//
//    //Pos Y grid
//    x_val = fmax(kg.ytick_num, kg.y_min);
//    while (x_val <= kg.y_max){
//
//        //Add label
//        drawptr temp_label = std::shared_ptr<sf::Text>(new sf::Text);
//        ref_Text(temp_label)->setFont(kg.tick_font);
//        ref_Text(temp_label)->setString(kurt_string(x_val));
//        ref_Text(temp_label)->setFillColor(label_color);
//        ref_Text(temp_label)->setCharacterSize(label_font_size);
//        ref_Text(temp_label)->setPosition(x_pixel(0, ac)+y_label_offset, y_pixel(x_val, ac));
//        drawings.push_back(temp_label);
//
//        //Shift x value
//        x_val += kg.ytick_num;
//    }
//
//    //Draw ticks
//
//    //    std::vector<KPoint> numeric_to_pixel(std::vector<KPoint> kp, int left_bound, int right_bound, double left_val, double right_val, int top_bound, int low_bound, double top_val, double low_val)
//
//}

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


























