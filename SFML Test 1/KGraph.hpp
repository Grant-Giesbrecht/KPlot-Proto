//
//  KGraph.hpp
//  SFML Test 1
//
//  Created by Grant Giesbrecht on 9/9/17.
//  Copyright © 2017 IEGA Software. All rights reserved.
//
//
//  This class doesn't perform any actual drawing/plotting, rather it is only used as a wrapper
//  for the information a KPlotTab will require for displaying the user's graph.
//
//
//

#ifndef KGraph_hpp
#define KGraph_hpp

#include <stdio.h>
#include <string>
#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "KTrace.hpp"
#include "ResourcePath.hpp"

//Properties
#define KG_PROP_LEGEND_ON 1

//Struct containing the style options for a graph. Can be defined by a preset style or overridden by the user
typedef struct{    
    bool draw_small_grid; //Draw grid throughout entire graph at small_tick spacing (aka small_grid)
    bool draw_big_grid; //Draw grid throughout entire graph at big_tick spacing (aka big_grid)
    bool draw_axis_small_ticks; //Draw tick marks on the axes at small_tick spacing
    bool draw_axis_big_ticks; //Draw tick marks on the axes at big_tick spacing
    bool draw_x_axis; //Draw x-axis
    bool draw_y_axis; //Draw y-axis
    bool draw_graph_border; //Draw a border around the graph
    bool draw_buttons; //Draw buttons at top of graph
    bool draw_in_graph_numerals_x; //Draw x labels inside the graph, not just on the axes
    bool draw_in_graph_numerals_y; //Draw y labels inside the graph, not just on the axes
    bool draw_exterior_x_numerals; //Draw x labels below the graph
    bool draw_exterior_y_numerals; //Draw y labels to the left of the graph
    bool draw_secondary_in_graph_numerals_x; //Draw x labels inside the graph, not just on the axes for the secondary axis (note: making any of the draw_secondary_..._numerals_(x/y) true will enable the secondary axes).
    bool draw_secondary_in_graph_numerals_y; //Draw y labels inside the graph, not just on the axes for the secondary axis
    bool draw_secondary_exterior_x_numerals; //Draw x labels above the graph for the secondary axis
    bool draw_secondary_exterior_y_numerals; //Draw y labels to the right of the graph for the secondary axis
    bool show_legend; //Show the legend !!
    
    sf::Color small_grid_color; //Define the color of the small_grid
    sf::Color big_grid_color; //Define the color of the big_grid
    sf::Color axes_color; //Define the color of the x&y axes
    sf::Color border_color; //Define the color of the border
    sf::Color background_color; //Define the color of the graph's background
    sf::Color label_color; //Define the color fo the X&Y label
    sf::Color title_color; //Color of title at top of graph !!
    sf::Color grid_color; //Color of in-graph grid !!
    sf::Color legend_background; //Color of legend_background !!
    
    int small_grid_thickness; //Define the thickness of the small_grid
    int big_grid_thickness;  //Define the thickness of the big_grid
    int small_tick_thickness;  //Define the thickness of the small_ticks
    int small_tick_length; //Define the length of the small_ticks
    int big_tick_thickness; //Define the thickness of the small_ticks
    int big_tick_length; //Define the length of the small_ticks
    int axes_thickness; //Define the thickness of the X&Y axes
    int border_thickness; //Define the thickness of the border
    int label_font_size; //Size of label font
    int title_font_size; //Size of label font
    int x_label_offset; //Offset of x_label from x-axis (for in-graph numerals)
    int y_label_offset; //Offset of y_label from y-axis (for in-graph numerals)
    int x_numeral_height_exterior; //Height by which x-label is pushed down in order to make room for exterior x-numerals
    int y_numeral_height_exterior; //Height by which y-label is pushed left in order to make room for exterior y-numerals
    int x_sec_label_offset; //Offset of secondary x_label from x-axis
    int y_sec_label_offset; //Offset of secondary y_label from y-axis
    int title_offset; //Offset of title from top of graph
    int x_label_margin; //How much room to leave at bottom of graph's allocated area in tab for labels
    int y_label_margin; //How much room to leave at left of graph's allocated area in tab for labels
    int x_sec_label_margin; //How much room to leave at top of graph's allocated area in tab for labels
    int y_sec_label_margin; //How much room to leave at right of graph's allocated area in tab for labels
    
    sf::Font main_font; //Font used in all text in KGraph !!
    sf::Font tick_font; //Font used for labeling tick numbers on axes !!
    
}graph_style_options;

class KGraph{
    
public:
    //Constructor/destructors
    KGraph();
    ~KGraph();
    
    //Add/edit/delete traces
    void addTrace(KTrace nt);
    void addTrace(std::string name, KTrace nt);
    KTrace& getTrace(std::string, bool& success);
    //TODO: Implement delete trace
    
    //Set Properties
    void setFont(sf::Font); //For axes and title and legend
    void setBounds(double x_min, double x_max, double y_min, double y_max); //Set plot bounds
    void set(int prop, bool val); //Set specified property
    void setLegendPosition(double x, double y); //Set position of legend
    
    //Get Properties
    std::string getTitle();
    
    // Fields //TODO make private and add functions
    double x_min, x_max, y_min, y_max; //Axes bounds
    double xtick_small, xtick_big, xtick_num; //Tick spacing
    double ytick_small, ytick_big, ytick_num; //Tick spacing
    double x_min_sec, x_max_sec, y_min_sec, y_max_sec; //Secondary axes bounds
    std::string x_label; //Label on x axis
    std::string y_label; //Label on y axis
    std::string x_label_sec; //Label on seconadry x axis
    std::string y_label_sec; //Label on secondary y axis
    std::string title; //Title of graph
    double legend_x, legend_y; //Legend x-y position (of upper-right corner), in percent/100 NOT pixels
    graph_style_options options;
    
    //Graph positioning in window
    int r_tl;
    int c_tl;
    int r_br;
    int c_br;
    
    std::vector<KTrace> traces; //Vector of all traces in graph
    
//    sf::Font main_font;
//    sf::Font tick_font;
    
private:
    
    KTrace void_trace; //An empty and unused ktrace to return if no KTrace meets search criteria
    
    
    
};

void implement_style(int style, graph_style_options& options); //Overwrite graph_style_option struct with selected style's options

#endif /* KGraph_hpp */
