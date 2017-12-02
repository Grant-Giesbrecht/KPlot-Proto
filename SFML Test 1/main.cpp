
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

#include <iostream>
#include <stdio.h>

#include "kpgraphics.hpp"
#include "KPlotWindow.hpp"
#include "KPlotTab.hpp"
#include "KGraph.hpp"
#include "KTrace.hpp"

#include "KMatrix.hpp"
#include "KPlot.hpp"

#include <cmath>
#include <ctgmath>

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 600

/*
 
 #define KT_TYPE_LINE 0
 #define KT_TYPE_POINT 1
 #define KT_TYPE_FIELD 2
 
 //Line
 #define KT_STYLE_STD 0
 #define KT_STYLE_DASH 1
 #define KT_STYLE_DOT 2
 #define KT_STYLE_DASHDOT 3
 
 //Point
 #define KT_STYLE_CIRCLE 0 //(Equivilent to STD)
 //#define KT_STYLE_STAR 4
 #define KT_STYLE_TRIANGLE 5
 //#define KT_STYLE_O 6
 #define KT_STYLE_CROSSHAIR 7
 #define KT_STYLE_SQUARE 8
 #define KT_STYLE_OCTOGON 9
 */

using namespace std;

int main(int, char const**){
    
    //Get system resolution
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    //std::c out << desktop.width << " " << desktop.height << endl;
    //std::c out << desktop.height*2/3 << " " << desktop.height*.5 << endl;
    
    //Create KTrace
    KTrace trace;
    trace.addPoint(1, 2);
    trace.addPoint(2, 3);
    trace.addPoint(3, 3.5);
    trace.addPoint(4, 6);
    trace.addPoint(5, 2);
    trace.addPoint(6, 4);
    trace.setColor(sf::Color::Red);
    trace.setType(KT_TYPE_POINT);
    trace.setStyle(KT_STYLE_OCTOGON);
    trace.setThickness(25);
    
    KTrace trace2;
    trace2.addPoint(-3, -2);
    trace2.addPoint(-2, -1);
    trace2.addPoint(-1, 0);
    trace2.addPoint(0, 1);
    trace2.addPoint(1, 2);
    trace2.addPoint(2, 2.5);
    trace2.addPoint(3, 2.8);
    trace2.addPoint(4, 3);
    trace2.addPoint(5, 2.8);
    trace2.addPoint(6, 2.3);
    trace2.addPoint(7, 1.5);
    trace2.addPoint(8, 0);
    trace2.addPoint(9, -2);
    trace2.setType(KT_TYPE_POINT);
    trace2.setStyle(KT_STYLE_TRIANGLE);
    trace2.setThickness(25);
//    trace2.setColor(sf::Color::Red);
    
    KTrace trace3;
    trace3.addPoint(-1, 0);
    trace3.addPoint(0, 2);
    trace3.addPoint(1, 4);
    trace3.addPoint(2, 7.5);
    trace3.addPoint(3, 2.8);
    trace3.addPoint(4, 3);
    trace3.addPoint(5, 2.8);
    trace3.addPoint(6, 2.3);
    trace3.addPoint(7, 1.5);
    trace3.addPoint(8, 0);
    trace3.addPoint(9, -2);
    trace3.setColor(sf::Color::Blue);
    trace3.setType(KT_TYPE_POINT);
    trace3.setStyle(KT_STYLE_CROSSHAIR);
    trace3.setThickness(25);
    
    KTrace trace4;
    for (double i = -10 ; i < 10 ; i += .1){
        trace4.addPoint(i, sin(i)*5*sin(i/4));
    }
    trace4.setColor(KP_COLOR_ORANGE);
    
    KTrace trace5;
    trace5.setType(KT_TYPE_FIELD);
    trace5.setCols(21);
    for (int i = -10 ; i <= 10 ; i++){//Row
        for (int j = 10 ; j >= -10 ; j--){ //Column
            trace5.addPoint(j, i, sf::Color(255-(i+10)*10, 0, i*10+100));
        }
    }
    
    /*
    //Create KGraph
    KGraph kg;
    kg.addTrace("Trace 1", trace);
    kg.addTrace("Trace 2", trace2);
    kg.addTrace("Trace 3", trace3);
    kg.setBounds(-6, 10, -5, 10);
    kg.xtick_num = 5;
    kg.ytick_num = 5;
    kg.xtick_big = 5;
    kg.ytick_big = 5;
    kg.xtick_small = 1;
    kg.ytick_small = 1;
    
    KGraph kg2;
    kg2.addTrace("Trace 1", trace4);
    kg2.setBounds(-10, 10, -6, 6);
    kg2.x_label = "Time elapsed (s)";
    kg2.y_label = "Drain voltage (V)";
    
    KGraph kg3;
    kg3.addTrace("Trace 1", trace5);
    kg3.setBounds(-10, 10, -10, 10);
    kg3.x_label = "Time elapsed (s)";
    kg3.y_label = "Position (m)";
    
//    kg.setBounds(-25, 25, -25, 25);
//    kg.setBounds(0, 10, 0, 7);
    
    //Create Tab
    KPlotTab kpt;
    kpt.add_graph(kg);
    
    KPlotTab kpt2;
    kpt2.add_graph(kg2);
    
    KPlotTab kpt3;
    kpt3.add_graph(kg3);
    
    //Create KPWindow
    KPlotWindow kpw(desktop.height*2/3, desktop.height*.5, "IEGA! Plot Test 1");
    kpw.add_tab(kpt, "Tab 1");
    kpw.set(KP_SET_WSTYLE, KP_WSTYLE_CLASSIC);
//
    KPlotWindow kpw2(desktop.height*2/3, desktop.height*.5, "IEGA! Plot Test BLUEWAVE");
    kpw2.add_tab(kpt, "Tab 1");
    kpw2.set(KP_SET_WSTYLE, KP_WSTYLE_BLUEWAVE);
    
    KPlotWindow kpw3(desktop.height*2/3, desktop.height*.5, "IEGA! Plot Test - Sine");
    kpw3.add_tab(kpt, "Tab 0");
    kpw3.add_tab(kpt2, "Tab 1");
    kpw3.set(KP_SET_WSTYLE, KP_WSTYLE_CLASSIC);
    
    KPlotWindow kpw4(desktop.height*2/3, desktop.height*.5, "IEGA! Plot Test - Field");
    kpw4.add_tab(kpt3, "Tab 0");
    //    kpw3.add_tab(kpt2, "Tab 1");
    kpw4.set(KP_SET_WSTYLE, KP_WSTYLE_CLASSIC);*/
    
    KMatrix km("0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 10");
    KPlot kp("Trace1", km);
    if (!kp.setTraceColor("Trace1", sf::Color::Red));
//    kp.setWindowSize(desktop.height, desktop.height*.75);
//    kp.setTraceColor("Trace1", KP_COLOR_ORANGE);
//    kp.setWindowStyle(KP_WSTYLE_CLASSIC);
//    kp.event_loop();
    
    KMatrix xkm("0, 1, 2, 3, 4, 5, 6, 7, 8");
    KMatrix ykm("0, 1, 4, 5, 6, 5, 3, 2.5, 4");
    KPlot kp2("Trace 1", xkm, ykm);
    kp2.setWindowStyle(KP_WSTYLE_CLASSIC);
//    kp2.addTrace("Trace 2", xkm, ykm);
    if (!kp2.setTraceType("Trace 1", KT_TYPE_POINT)){ cout << "\n\nFAIL 1 TYPE\n\n" << endl; }else{ cout << "\n\nGO 1 TYPE\n\n" << endl; }
    if (!kp2.setTraceStyle("Trace 1", KT_STYLE_CROSSHAIR)){ cout << "\n\nFAIL 1 STYLE\n\n" << endl; }else{ cout << "\n\nGO 1 STYLE\n\n" << endl; }
    if (!kp2.setTraceColor("Trace 1", sf::Color::Blue)){ cout << "\n\nFAIL 1 COLOR\n\n" << endl; }else{ cout << "\n\nGO 1 COLOR\n\n" << endl; } //KP_COLOR_ORANGE);
    kp2.setTraceThickness("Trace 1", 25);
    kp2.setXLabel("Temperature (K)");
    kp2.setYLabel("Voltage (V)");
    kp2.setBounds(-1, 10, 0, 10);
    kp2.setXTicks(1, 3, 3);
    kp2.setYTicks(2, 5, 2);
//    kp2.setTraceType("Trace 2", KT_TYPE_POINT);
//    kp2.setTraceStyle("Trace 2", KT_STYLE_CROSSHAIR);
//    kp2.setTraceColor("Trace 2", sf::Color::Red);
    
    KPlotWindow::event_loop();

    return EXIT_SUCCESS;
}
