//
//  KPlot.cpp
//  SFML Test 1
//
//  Created by Grant Giesbrecht on 10/7/17.
//  Copyright © 2017 IEGA Software. All rights reserved.
//

#include "KPlot.hpp"

using namespace std;

KPlot::KPlot(){
    default_construct();
}

KPlot::KPlot(unsigned int x_size, unsigned int y_size){
    
    //Call default constructor code
    default_construct();
    
    //Set window size
    mainWindow.setWindowSize(x_size, y_size);
}

KPlot::KPlot(std::string name, KMatrix km){
    
    //Call default constructor code
    default_construct();
    
    //Add trace to graph
    addTrace(name, km);
    
}

KPlot::KPlot(std::string name, KMatrix x_km, KMatrix y_km){
    
    //Call default constructor code
    default_construct();
    
    //Add trace to graph
    addTrace(name, x_km, y_km);
    
}

void KPlot::addTrace(string name, KMatrix km){

    bool success;
    
    if (km.rows() >= 2 && km.cols() >= 1){
        
        vector<double> temp_x = km.get_rowv(0);
        vector<double> temp_y = km.get_rowv(1);
        
        if (temp_x.size() != temp_y.size()) return;
        
        shared_ptr<KTrace> trace = shared_ptr<KTrace>(new KTrace());
        for (int i = 0 ; i < temp_x.size() ; i++){
            trace->addPoint(temp_x[i], temp_y[i]);
        }
        
        mainWindow.getTab(0).getGraph(0, success).addTrace(name, *trace);
        
    }
}

void KPlot::addTrace(string name, KMatrix x_km, KMatrix y_km){
    
    bool success;
    
    if (y_km.rows() >= 1 && y_km.cols() >= 1 && x_km.rows() >= 1 && y_km.cols() == x_km.cols()){
        
        vector<double> temp_x = x_km.get_rowv(0);
        vector<double> temp_y = y_km.get_rowv(0);
        
        if (temp_x.size() != temp_y.size()) return;
        
        shared_ptr<KTrace> trace = shared_ptr<KTrace>(new KTrace());
        for (int i = 0 ; i < temp_x.size() ; i++){
            trace->addPoint(temp_x[i], temp_y[i]);
        }
        
        mainWindow.getTab(0).getGraph(0, success).addTrace(name, *trace);
    }
}

void KPlot::addTrace(KTrace t){
    
}

void KPlot::addGraph(KGraph g){
    
}

KGraph& KPlot::get_graph(bool& success){
    return mainTab.getGraph(0, success);
}

void KPlot::setWindowSize(unsigned int x_size, unsigned int y_size){
    mainWindow.setWindowSize(x_size, y_size);
}

void KPlot::setBounds(double x_min, double x_max, double y_min, double y_max){
    bool success;
    mainWindow.getTab(0).getGraph(0, success).setBounds(x_min, x_max, y_min, y_max);
}

void KPlot::setXTicks(double small, double big, double num){
    bool success;
    mainWindow.getTab(0).getGraph(0, success).xtick_small = small;
    mainWindow.getTab(0).getGraph(0, success).xtick_big = big;
    mainWindow.getTab(0).getGraph(0, success).xtick_num = num;
}

void KPlot::setYTicks(double small, double big, double num){
    bool success;
    mainWindow.getTab(0).getGraph(0, success).ytick_small = small;
    mainWindow.getTab(0).getGraph(0, success).ytick_big = big;
    mainWindow.getTab(0).getGraph(0, success).ytick_num = num;
}

void KPlot::setGraphTitle(std::string title){
    bool success;
    mainWindow.getTab(0).getGraph(0, success).title = title;
    
}

void KPlot::setXLabel(std::string label){
    bool success;
    mainWindow.getTab(0).getGraph(0, success).x_label = label;
    
}

void KPlot::setYLabel(std::string label){
    bool success;
    mainWindow.getTab(0).getGraph(0, success).y_label = label;
}

void KPlot::set(int property, int val){
    
}

void KPlot::setWindowStyle(int style){
    mainWindow.set(KP_SET_WSTYLE, style);
}

bool KPlot::setTraceType(std::string trace, int nt){
    bool success;
    
    mainWindow.getTab(0).getGraph(0, success);
    if (success){
        mainWindow.getTab(0).getGraph(0, success).getTrace(trace, success);
        if (success){
            mainWindow.getTab(0).getGraph(0, success).getTrace(trace, success).setType(nt);
            return true;
        }
    }
    
    return false;
}

bool KPlot::setTraceThickness(std::string trace, int nt){
    bool success;
    
    mainWindow.getTab(0).getGraph(0, success);
    if (success){
        mainWindow.getTab(0).getGraph(0, success).getTrace(trace, success);
        if (success){
            mainWindow.getTab(0).getGraph(0, success).getTrace(trace, success).setThickness(nt);
            return true;
        }
    }
    
    return false;
}

bool KPlot::setTraceStyle(std::string trace, int ns){
    
    bool success;
    
    mainWindow.getTab(0).getGraph(0, success);
    if (success){
        mainWindow.getTab(0).getGraph(0, success).getTrace(trace, success);
        if (success){
            mainWindow.getTab(0).getGraph(0, success).getTrace(trace, success).setStyle(ns);
            return true;
        }
    }
    
    return false;
}

bool KPlot::setTraceColor(std::string trace, sf::Color nc){
    
    bool success;
    
    mainWindow.getTab(0).getGraph(0, success);
    if (success){
        mainWindow.getTab(0).getGraph(0, success).getTrace(trace, success);
        if (success){
            mainWindow.getTab(0).getGraph(0, success).getTrace(trace, success).setColor(nc);
            return true;
        }
    }
    
    return false;
}

bool KPlot::setCols(std::string trace, int nc){
    bool success;
    
    KGraph& g = mainTab.getGraph(0, success);
    if (success){
        KTrace& t = g.getTrace(trace, success);
        if (success){
            t.setCols(nc);
            return true;
        }
    }
    
    return false;
}

void KPlot::event_loop(){
    mainWindow.event_loop();
}

void KPlot::event_loop(bool* halt){
    mainWindow.event_loop(halt);
}

void KPlot::default_construct(){
    //Set title of main graph
    mainGraph.title = "Main Graph Title";
    
    //Add tab to window
    mainWindow.add_tab(mainTab, "Tab 1");
    
    //Add graph to main tab
    mainWindow.getTab(0).add_graph(mainGraph);
}
