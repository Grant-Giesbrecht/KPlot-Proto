//
//  KPlot.hpp
//  SFML Test 1
//
//  Created by Grant Giesbrecht on 10/7/17.
//  Copyright © 2017 IEGA Software. All rights reserved.
//
//  KPlot adds no new functionality to the KPlot system - everything that can be done with KPlot can be done with KPlotWindow + KPlotTab
//  + KGraph + KTrace + KPoint. Its just tiresome to deal with 4 types of objects if you only want to plot something simple. Thats
//  Where KPlot comes in. KPlot lets you do plot quickly by assuming that you will only have one graph (with as many traces as you like).
//  If you need more complex operations, the other files will only add a few more lines of code - probably less than a dozen. Together,
//  this code can run the gamut of complex and capable to simple and quick. Whatever speed you need, KPlot (and its affiliates) can support.
//
//

#ifndef KPlot_hpp
#define KPlot_hpp

#include <stdio.h>
#include <string>

#include "KPlotWindow.hpp"
#include "KPlotTab.hpp"
#include "KGraph.hpp"
#include "KTrace.hpp"

#include "KMatrix.hpp"
#include "string_manip.hpp"
//#include "KVar.hpp"

class KPlot{
public:
    
    //Initialization functions
    KPlot();
    KPlot(unsigned int x_size, unsigned int y_size);
    KPlot(std::string name, KMatrix km);
    KPlot(std::string name, KMatrix x_km, KMatrix y_km);
//    KPlot(std::string name, KMatrix x_km, KMatrix y_km);
    
    //Add/get trace functions
    void addTrace(std::string name, KMatrix km);
    void addTrace(std::string name, KMatrix x_km, KMatrix y_km);
    void addTrace(KTrace t);
    void addGraph(KGraph g);
    KGraph& get_graph(bool& success);
    
    //General settings
    void set(int property, int val);
    
    //Window settings
    void setWindowStyle(int style);
    void setWindowSize(unsigned int x_size, unsigned int y_size);

    //Graph settings
    void setBounds(double x_min, double x_max, double y_min, double y_max);
    void setXTicks(double small, double big, double num);
    void setYTicks(double small, double big, double num);
    void setGraphTitle(std::string label);
    void setXLabel(std::string label);
    void setYLabel(std::string title);
    
    //Trace settings
    bool setTraceType(std::string trace, int nt);
    bool setTraceThickness(std::string trace, int nt);
    bool setTraceStyle(std::string trace, int ns);
    bool setTraceColor(std::string trace, sf::Color nc);
    bool setCols(std::string trace, int nc);
    
    //Loop functions
    void event_loop();
    void event_loop(bool* halt);
    
private:
    KPlotWindow mainWindow;
    KPlotTab mainTab;
    KGraph mainGraph;
    
    void default_construct();
};

#endif /* KPlot_hpp */

