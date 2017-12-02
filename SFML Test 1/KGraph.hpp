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
    std::string x_label; //Label on y axis
    std::string y_label; //Label on x axis
    std::string title; //Title of graph
    double legend_x, legend_y; //Legend x-y position (of upper-right corner), in percent/100 NOT pixels
    
    //Graph positioning in window
    int r_tl;
    int c_tl;
    int r_br;
    int c_br;
    
    std::vector<KTrace> traces; //Vector of all traces in graph
    
    sf::Font main_font; //Font used in all text in KGraph
    sf::Font tick_font; //Font used for labeling tick numbers on axes
    
private:
    
    sf::Color background_color; //Color of background
    sf::Color axes_color; //Color of axes and axes label
    sf::Color title_color; //Color of title at top of graph
    sf::Color grid_color; //Color of in-graph grid
    sf::Color legend_background; //Color of legend_background
    
    KTrace void_trace; //An empty and unused ktrace to return if no KTrace meets search criteria
    
    bool show_legend; //Show the legend
    
};

#endif /* KGraph_hpp */
