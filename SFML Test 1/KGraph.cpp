//
//  KGraph.cpp
//  SFML Test 1
//
//  Created by Grant Giesbrecht on 9/9/17.
//  Copyright © 2017 IEGA Software. All rights reserved.
//

#include "KGraph.hpp"
#include <iostream> //for debugging only

#include "resourcePath.hpp"

/*
 Constructor
 */
KGraph::KGraph(){ //NO initializer list required for void_trace because no arguments requrired
    
    //Default bounds
    x_min = -10;
    x_max = 10;
    y_min = -10;
    y_max = 10;
    
    //Default ticks
    xtick_small = 1;
    xtick_big = 5;
    xtick_num = 5;
    ytick_small = 1;
    ytick_big = 5;
    ytick_num = 5;
    
    //Default legend position (upper-right corner)
    legend_x = 1;
    legend_y = 0;
    
    //Default labels
    x_label = "X-Axis";
    y_label = "Y-Axis";
    title = "Title";
    
    //Initialize options
    implement_style(KP_WSTYLE_CLASSIC, options);
    
    r_tl = -1;
    c_tl = -1;
    r_br = -1;
    c_br = -1;
}

/*
 Destructor
 */
KGraph::~KGraph(){
    
}

/*
 Add trace to graph
 
 nt - trace to add
 
 Void return
 */
void KGraph::addTrace(KTrace nt){
    
    traces.push_back(nt);
    
}

/*
 Add trace to graph & set its name
 
 name - name to assign to trace
 nt - trace to add
 
 Void return
 */
void KGraph::addTrace(std::string name, KTrace nt){
    
    nt.setName(name);
    traces.push_back(nt);
    //std::c out << "Traces.size() reads '" << traces.size() << "' after adding the trace and inside 'addTrace'" << std::endl;
}

/*
 Access trace reference via trace name.
 
 search_name - name of trace for which to search
 
 Returns reference to trace (if found)
 */
KTrace& KGraph::getTrace(std::string search_name, bool& success){
    
    for (int i = 0 ; i < traces.size() ; i++){
        if (traces[i].name() == search_name){
            success = true;
            //std::c out << "Found it!" << std::endl;
            return traces[i];
        }else{
            //std::c out << "Looking for '" << search_name << "', found '" << traces[i].name() << "'." << std::endl;
        }
    }
    
    success = false;
    return void_trace;
}

/*
 Set font of graph
 
 nf - new font for graph
 
 Void return
 */
void KGraph::setFont(sf::Font nf){ //For axes and title and legend
    
    options.main_font = nf;
    
}

/*
 Set bounds of graph
 
 x_min - x min
 x_max - x max
 y_min - y min
 y_max - y max
 
 Void return
 */
void KGraph::setBounds(double x_min, double x_max, double y_min, double y_max){ //Set plot bounds
    
    KGraph::x_min = x_min;
    KGraph::x_max = x_max;
    KGraph::y_min = y_min;
    KGraph::y_max = y_max;
    
}

/*
 Set KGraph property
 
 prop - property to adjust
 val - new property value
 
 Void return
 */
void KGraph::set(int prop, bool val){ //Set specified property
    
    switch (prop) {
        case KG_PROP_LEGEND_ON:
            options.show_legend = val;
            break;
        default:
            break;
    }
    
}

/*
 Set position of legend
 
 x - x position in percent/100 of graph size (not pixel coordinates)
 y - y position in percent/100 of graph size (not pixel coordinates)
 
 Void return
 */
void KGraph::setLegendPosition(double x, double y){ //Set position of legend, in %/100 of graph size, NOT PIXELS
    legend_x = x;
    legend_y = y;
}

/*
 Return the title of the graph
 */
std::string KGraph::getTitle(){
    return title;
}

/*
 Overwrites 'options' with the preferences associated with 'style'.
 
 options - struct containing graph style options to be overwritten
 style - new style to write into 'options'
 
 Void return
 */
void implement_style(int style, graph_style_options& options){
    
    switch(style){
        case(KP_WSTYLE_CLASSIC):
            options.draw_small_grid = true;
            options.draw_big_grid = true;
            options.draw_axis_small_ticks = false;
            options.draw_axis_big_ticks = false;
            options.draw_x_axis = true;
            options.draw_y_axis = true;
            options.draw_graph_border = true;
            options.draw_in_graph_numerals_x = false;
            options.draw_in_graph_numerals_y = false;
            options.draw_exterior_x_numerals = true;
            options.draw_exterior_y_numerals = true;
            options.draw_secondary_in_graph_numerals_x = false;
            options.draw_secondary_in_graph_numerals_y = false;
            options.draw_secondary_exterior_x_numerals = false;
            options.draw_secondary_exterior_y_numerals = false;
            options.show_legend = false;
            
            options.small_grid_color = sf::Color(60, 60, 60);
            options.big_grid_color = sf::Color(30, 30, 30);
            options.axes_color = sf::Color::Black;
            options.border_color = sf::Color::Black;
            options.background_color = sf::Color(255, 255, 255);
            options.label_color = sf::Color::Black;
            options.title_color = sf::Color::Black;
            options.grid_color = sf::Color(150, 150, 150);
            options.legend_background = sf::Color::White;
            
            options.small_grid_thickness = 1;
            options.big_grid_thickness = 2;
            options.small_tick_thickness = 1;
            options.small_tick_length = 2;
            options.big_tick_thickness = 1;
            options.big_tick_length = 5;
            options.axes_thickness = 3;
            options.border_thickness = 2;
            options.label_font_size = 25;
            options.title_font_size = 32;
            options.x_label_offset = 3;
            options.y_label_offset = 6;
            options.x_numeral_height_exterior = 20;
            options.y_numeral_height_exterior = 20;
            options.x_sec_label_offset = 3;
            options.y_sec_label_offset = 3;
            options.title_offset = 3;
            options.x_label_margin = 35;
            options.y_label_margin = 35;
            options.x_sec_label_margin = 35;
            options.y_sec_label_margin = 35;
            
            if (!options.main_font.loadFromFile(std::string(FONT_PATH) + std::string("sansation.ttf"))) {
                //        return EXIT_FAILURE;
            }
            
            if (!options.main_font.loadFromFile(std::string(FONT_PATH) + std::string("Aileron-Regular.otf"))) {
                //        return EXIT_FAILURE;
            }
            
//            if (!options.main_font.loadFromFile(std::string(SYSTEM_FONT_PATH) + std::string("Arial.ttf"))) {
//                //        return EXIT_FAILURE;
//            }
            
            if (!options.tick_font.loadFromFile(std::string(FONT_PATH) + "sansation.ttf")) {
                //        return EXIT_FAILURE;
            }
            
            break;
        case(KP_WSTYLE_CLASSIC_SIMPLEX): //same as classic for now
            options.draw_small_grid = true;
            options.draw_big_grid = true;
            options.draw_axis_small_ticks = false;
            options.draw_axis_big_ticks = false;
            options.draw_x_axis = true;
            options.draw_y_axis = true;
            options.draw_graph_border = true;
            options.draw_in_graph_numerals_x = false;
            options.draw_in_graph_numerals_y = false;
            options.draw_exterior_x_numerals = true;
            options.draw_exterior_y_numerals = true;
            options.draw_secondary_in_graph_numerals_x = false;
            options.draw_secondary_in_graph_numerals_y = false;
            options.draw_secondary_exterior_x_numerals = false;
            options.draw_secondary_exterior_y_numerals = false;
            options.show_legend = false;
            
            options.small_grid_color = sf::Color(60, 60, 60);
            options.big_grid_color = sf::Color(30, 30, 30);
            options.axes_color = sf::Color::Black;
            options.border_color = sf::Color::Black;
            options.background_color = sf::Color(255, 255, 255);
            options.label_color = sf::Color::Black;
            options.title_color = sf::Color::Black;
            options.grid_color = sf::Color(150, 150, 150);
            options.legend_background = sf::Color::White;
            
            options.small_grid_thickness = 1;
            options.big_grid_thickness = 2;
            options.small_tick_thickness = 1;
            options.small_tick_length = 2;
            options.big_tick_thickness = 1;
            options.big_tick_length = 5;
            options.axes_thickness = 3;
            options.border_thickness = 2;
            options.label_font_size = 25;
            options.title_font_size = 32;
            options.x_label_offset = 3;
            options.y_label_offset = 3;
            options.x_numeral_height_exterior = 20;
            options.y_numeral_height_exterior = 20;
            options.x_sec_label_offset = 3;
            options.y_sec_label_offset = 3;
            options.title_offset = 3;
            options.x_label_margin = 35;
            options.y_label_margin = 35;
            options.x_sec_label_margin = 35;
            options.y_sec_label_margin = 35;
            
            if (!options.main_font.loadFromFile(std::string(FONT_PATH) + std::string("sansation.ttf"))) {
                //        return EXIT_FAILURE;
            }
            
            if (!options.tick_font.loadFromFile(std::string(FONT_PATH) + "sansation.ttf")) {
                //        return EXIT_FAILURE;
            }
            
            break;
        case(KP_WSTYLE_LIGHT): //Classic without the grid
            options.draw_small_grid = false;
            options.draw_big_grid = false;
            options.draw_axis_small_ticks = true;
            options.draw_axis_big_ticks = true;
            options.draw_x_axis = true;
            options.draw_y_axis = true;
            options.draw_graph_border = true;
            options.draw_in_graph_numerals_x = false;
            options.draw_in_graph_numerals_y = false;
            options.draw_exterior_x_numerals = true;
            options.draw_exterior_y_numerals = true;
            options.draw_secondary_in_graph_numerals_x = false;
            options.draw_secondary_in_graph_numerals_y = false;
            options.draw_secondary_exterior_x_numerals = false;
            options.draw_secondary_exterior_y_numerals = false;
            options.show_legend = false;
            
            options.small_grid_color = sf::Color(60, 60, 60);
            options.big_grid_color = sf::Color(30, 30, 30);
            options.axes_color = sf::Color::Black;
            options.border_color = sf::Color::Black;
            options.background_color = sf::Color(255, 255, 255);
            options.label_color = sf::Color::Black;
            options.title_color = sf::Color::Black;
            options.grid_color = sf::Color(150, 150, 150);
            options.legend_background = sf::Color::White;
            
            options.small_grid_thickness = 1;
            options.big_grid_thickness = 2;
            options.small_tick_thickness = 1;
            options.small_tick_length = 2;
            options.big_tick_thickness = 1;
            options.big_tick_length = 5;
            options.axes_thickness = 3;
            options.border_thickness = 2;
            options.label_font_size = 25;
            options.title_font_size = 32;
            options.x_label_offset = 3;
            options.y_label_offset = 3;
            options.x_numeral_height_exterior = 20;
            options.y_numeral_height_exterior = 20;
            options.x_sec_label_offset = 3;
            options.y_sec_label_offset = 3;
            options.title_offset = 3;
            options.x_label_margin = 35;
            options.y_label_margin = 35;
            options.x_sec_label_margin = 35;
            options.y_sec_label_margin = 35;
            
            if (!options.main_font.loadFromFile(std::string(FONT_PATH) + std::string("sansation.ttf"))) {
                //        return EXIT_FAILURE;
            }
            
            if (!options.tick_font.loadFromFile(std::string(FONT_PATH) + "sansation.ttf")) {
                //        return EXIT_FAILURE;
            }
            
            break;
        case(KP_WSTYLE_BLUEWAVE):
            options.draw_small_grid = true;
            options.draw_big_grid = true;
            options.draw_axis_small_ticks = false;
            options.draw_axis_big_ticks = false;
            options.draw_x_axis = true;
            options.draw_y_axis = true;
            options.draw_graph_border = true;
            options.draw_in_graph_numerals_x = false;
            options.draw_in_graph_numerals_y = false;
            options.draw_exterior_x_numerals = true;
            options.draw_exterior_y_numerals = true;
            options.draw_secondary_in_graph_numerals_x = false;
            options.draw_secondary_in_graph_numerals_y = false;
            options.draw_secondary_exterior_x_numerals = false;
            options.draw_secondary_exterior_y_numerals = false;
            options.show_legend = false;
            
            options.small_grid_color = sf::Color(30, 35, 120);
            options.big_grid_color = sf::Color(50, 55, 150);
            options.axes_color = sf::Color(80, 85, 220);
            options.border_color = sf::Color(80, 85, 220);
            options.background_color = sf::Color(165, 170, 200);
            options.label_color = sf::Color::Black;
            options.title_color = sf::Color::Black;
            options.grid_color = sf::Color(150, 150, 150);
            options.legend_background = sf::Color::White;
            
            options.small_grid_thickness = 1;
            options.big_grid_thickness = 2;
            options.small_tick_thickness = 1;
            options.small_tick_length = 2;
            options.big_tick_thickness = 1;
            options.big_tick_length = 5;
            options.axes_thickness = 3;
            options.border_thickness = 2;
            options.label_font_size = 25;
            options.title_font_size = 32;
            options.x_label_offset = 3;
            options.y_label_offset = 3;
            options.x_numeral_height_exterior = 20;
            options.y_numeral_height_exterior = 20;
            options.x_sec_label_offset = 3;
            options.y_sec_label_offset = 3;
            options.title_offset = 3;
            options.x_label_margin = 35;
            options.y_label_margin = 35;
            options.x_sec_label_margin = 35;
            options.y_sec_label_margin = 35;
            
            if (!options.main_font.loadFromFile(std::string(FONT_PATH) + std::string("sansation.ttf"))) {
                //        return EXIT_FAILURE;
            }
            
            if (!options.tick_font.loadFromFile(std::string(FONT_PATH) + "sansation.ttf")) {
                //        return EXIT_FAILURE;
            }
            
            break;
        case(KP_WSTYLE_OKUDAGRAM): //same as classic for now
            options.draw_small_grid = true;
            options.draw_big_grid = true;
            options.draw_axis_small_ticks = false;
            options.draw_axis_big_ticks = false;
            options.draw_x_axis = true;
            options.draw_y_axis = true;
            options.draw_graph_border = true;
            options.draw_in_graph_numerals_x = false;
            options.draw_in_graph_numerals_y = false;
            options.draw_exterior_x_numerals = true;
            options.draw_exterior_y_numerals = true;
            options.draw_secondary_in_graph_numerals_x = false;
            options.draw_secondary_in_graph_numerals_y = false;
            options.draw_secondary_exterior_x_numerals = false;
            options.draw_secondary_exterior_y_numerals = false;
            options.show_legend = false;
            
            options.small_grid_color = sf::Color(60, 60, 60);
            options.big_grid_color = sf::Color(30, 30, 30);
            options.axes_color = sf::Color::Black;
            options.border_color = sf::Color::Black;
            options.background_color = sf::Color(255, 255, 255);
            options.label_color = sf::Color::Black;
            options.title_color = sf::Color::Black;
            options.grid_color = sf::Color(150, 150, 150);
            options.legend_background = sf::Color::White;
            
            options.small_grid_thickness = 1;
            options.big_grid_thickness = 2;
            options.small_tick_thickness = 1;
            options.small_tick_length = 2;
            options.big_tick_thickness = 1;
            options.big_tick_length = 5;
            options.axes_thickness = 3;
            options.border_thickness = 2;
            options.label_font_size = 25;
            options.title_font_size = 32;
            options.x_label_offset = 3;
            options.y_label_offset = 3;
            options.x_numeral_height_exterior = 20;
            options.y_numeral_height_exterior = 20;
            options.x_sec_label_offset = 3;
            options.y_sec_label_offset = 3;
            options.title_offset = 3;
            options.x_label_margin = 35;
            options.y_label_margin = 35;
            options.x_sec_label_margin = 35;
            options.y_sec_label_margin = 35;
            
            if (!options.main_font.loadFromFile(std::string(FONT_PATH) + std::string("sansation.ttf"))) {
                //        return EXIT_FAILURE;
            }
            
            if (!options.tick_font.loadFromFile(std::string(FONT_PATH) + "sansation.ttf")) {
                //        return EXIT_FAILURE;
            }
            
            break;
    }
    
}
//#define KP_WSTYLE_CLASSIC_SIMPLEX 4
//#define KP_WSTYLE_CLASSIC 0
//#define KP_WSTYLE_LIGHT 1
//#define KP_WSTYLE_BLUEWAVE 2
//#define KP_WSTYLE_OKUDAGRAM 3








