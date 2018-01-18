//
//  KPlotTab.hpp
//  SFML Test 1
//
//  Created by Grant Giesbrecht on 9/10/17.
//  Copyright © 2017 IEGA Software. All rights reserved.
//
//
//  This file contains the sourcecode for the KPlotTab object. This object will contain 1+
//  KGraph objects each containing 1+ KTrace objects. The KPlotTab will be given drawing
//  powers from the KPlotWindow in which it is contained. The KPlotTab will (only when made
//  active) draw the KGraph(s) inside.
//
//


#ifndef KPlotTab_hpp
#define KPlotTab_hpp

#include <stdio.h>
#include <string>
#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "KGraph.hpp"
#include "kpgraphics.hpp"

class KPlotTab{
public:
    //Constructors
    KPlotTab();
    
    //Add/edit/delete graphs
    void add_graph(KGraph ng);
    bool deleteGraph(int idx);
    bool deleteGraph(std::string title);
    KGraph& getGraph(int idx, bool& success);
    KGraph& getGraph(std::string title, bool& success);
    
    //Get property
    int numGraphs();
    
    //Set layout
    void layout_dimensions(int nrows, int ncols);
    void graph_location(int idx, int r, int c);
    void graph_location(int idx, int r_tl, int c_tl, int r_br, int c_br);
    void graph_location(std::string title, int r, int c);
    void graph_location(std::string title, int r_tl, int c_tl, int r_br, int c_br);
    
    //Draw tab & graph
    void draw_tab(sf::RenderWindow& window, int left_bound, int right_bound, int top_bound, int low_bound, int window_style, std::vector<std::shared_ptr<sf::Drawable> >& drawings);
    void draw_graph(sf::RenderWindow& window, int left_bound, int right_bound, int top_bound, int low_bound, int window_style, std::vector<std::shared_ptr<sf::Drawable> >& drawings, KGraph& kg);
    void draw_trace(KTrace& kt, axes_conversion& ac, std::vector<std::shared_ptr<sf::Drawable> >& drawings);
    
    std::vector<KGraph> graphs;
    std::string tab_title;
    
    //Update functions
    void zoom();
private:
    
    // ===================== FIELDS ============================
    
    //Graphs
//    std::vector<located_graph> graphs;
    
    //Layout
    int rows;
    int cols;
    
    //Null fields
    KGraph null_graph;
    
    // ===================== FUNCTIONS =========================
    
    int get_index_form_title(std::string title);
    
};

#endif /* KPlotTab_hpp */


















