//
//  KPlotWindow.hpp
//  SFML Test 1
//
//  Created by Grant Giesbrecht on 9/10/17.
//  Copyright © 2017 IEGA Software. All rights reserved.
//
//
//  The KPlot window object contains one or more KPlotTab objects. The KPlotWindow only has 4
//  jobs: 1. Draw the toolbar 2. Draw the tab-bar (if 2+ tabs or requested for always draw)
//  3. Organize the KPlotTab(s) by selecting which one is active (and all others are inactive)
//  and specifying the coordinates of the area in which the KPlotTabs may plot and 4. Listening
//  for mouse and keyboard events. These could be changing the KPlotTab's graph, changing the
//  active KPlotTab, or a miriad of other things. It does this by spawning an event listener thread
//
//

#ifndef KPlotWindow_hpp
#define KPlotWindow_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <mutex>
#include <atomic>
#include <thread>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "KPlotTab.hpp"

#define KP_COLOR_ORANGE sf::Color(255, 161, 0)

#define KP_SET_SHOW_TOOLBAR 0
#define KP_SET_SHOW_TABBAR 1
#define KP_SET_ACTIV_TAB 2
#define KP_SET_WSTYLE 3

class KPlotWindow{
public:
    
    //Constructors
    KPlotWindow();
    KPlotWindow(int width, int height, std::string title);
    ~KPlotWindow();
    
    bool isOpen();
    sf::RenderWindow& getWindow();
    void close();
    
    //Add/edit/delete tabs
    void add_tab(KPlotTab tab); //Add tab (default title applied)
    void add_tab(KPlotTab tab, std::string tab_title); //Add tab (with title for reference)
//    void add_tab(KPlotTab tab, std::string tab_title); //Add tab (with title for reference)
    bool delete_tab(std::string tab_title); //Delete tab by title
    bool delete_tab(int idx); //Delte tab specified by index
    KPlotTab& tab(std::string tab_title, bool& success); //Access tab for editting
    KPlotTab& tab(int idx, bool& success); //Access tab for editing
    
    //Control window operation
    void setWindowSize(unsigned int x_size, unsigned int y_size);
    void set(int prop, bool val);
    void set(int prop, int val);
    void set(int prop, std::string val);
    
    int getActiveTab();
    
    //Updates the window
    void draw_window();
    
    //Read/write
    bool savePlot(std::string filename);
    bool savePlot(std::string filename, std::string header);
    bool readPlot(std::string);
    
    //Access functions
    KPlotTab& getTab(int idx);
    size_t numTabs();
    
    //Event function
    static void event_loop();
    static void event_loop(bool* run);
    
private:
    
    //Main window
    sf::RenderWindow window;
    
    //Tabs
    std::vector<KPlotTab> tabs;
    
    //Mutex Protected Window Settings
    bool show_toolbar;
    bool show_tabbar;
    int active_tab;
    int window_style;
    int height;
    int width;
    
    //Automatically Protected Variables
    std::atomic<bool> scan_events;
    
    //SFML Window settings variable
//    sf::ContextSettings sfml_window_settings;
    
    //Blank OBJs for References
//    KPlotTab unused_tab;
    
    std::mutex mtx; //Mutex to protect window settings
    std::mutex window_mtx; //Mutex to protect window functions
    
//    std::thread event_thread;
    
    //Functions
//    void init_event_listener(sf::RenderWindow* window, std::mutex* mtx, std::mutex* window_mutex, int* nwidth, int* nheight, std::string* title);
    static std::mutex all_windows_mutex;
    static bool lshift_pressed;
    static bool rshift_pressed;
    int univ_id;
    static std::vector<KPlotWindow*> all_windows;
    
    //Null objects for references
    KPlotTab null_tab;
};

#endif /* KPlotWindow_hpp */












