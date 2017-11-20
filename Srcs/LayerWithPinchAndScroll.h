#ifndef LAYERWITHPIPNCHANDSCROLL_H
#define LAYERWITHPIPNCHANDSCROLL_H

// defines for double tap state
#define double_tap_not_started 0
#define double_tap_started_calculation 1
#define double_tap_detected 2
#define original_zooming_speed 0.005

//here we'll skip the first, second, locations and start from third, we'll use the first locations for the previous location or previous distance, but we'll neglate them, as they won't be accurate, you'll find it compared with touchNum value, this removes some flick with pinch to zoom and scrolling
#define laps_until_processing   3

//saves the maximum speed even if the user is fast will not go up for smoother look
#define maxScalingSpeed 0.03
#define maxScrollingSpeed 4.0

// this is the extra range that will be useful with bounce on edge
//#define extraRangeX (winSize.width())
//#define extraRangeY (winSize.height())
#define extraRangeX (10)
#define extraRangeY (10)


#include "layer.h"

class LayerWithPinchAndScroll : public Layer {
    
public:

    LayerWithPinchAndScroll();
    virtual void touchBegin(const QPointF &touchPoint);
    virtual void touchMove(const QPointF &touchPoint);
    virtual void touchEnd(const QPointF &touchPoint);
    virtual void update(double delta);
    void scrollSchedualUpdate();
    void scrollUnSchedualUpdate();
    void scrollsetScale(float p_scaleVal);
    QPointF check_point_with_extra_range(QPointF &p_point);
    QPointF check_point_with_no_extra_range(QPointF &p_point);
    QPointF move_point(QPointF p_point,float *vX, float *vY);

    float layerWidth;       //this is to hold the layer max width
    float layerHeight;       //this is to hold the layer max height
    float min_scale;        // hold minimum scale value
    float max_scale;        // hold maximum scale value
    //these can be controlled outside the class to disable features
    bool pich_to_zoom;
    bool scrolling;
    bool doubletap;
    
    //these are to help the related operations
    bool pinching;
    short int doubletap_state;
    bool zoomin;            //if true and double tap zoomin or zoom out if false and double tap
    float zooomingSpeed;
    
    QRect winSize;         //save window size here
    QTime timer;            //save the time
    float CurrDistance;         //save current distance for multi touch
    float PrevDistance;         //save prev distance
    float LastX;        // hold prev x if scrolling
    float LastY;        // hold prev y if scrolling
    float firsTapX;     //hold first tap x
    float firsTapY;     //hold first tap y
    float minX;         // saves minum x point
    float maxX;         //saves max x point
    float minY;         // saves minum y point
    float maxY;         //saves max y point
    short int touchNum;      //saves touch numbers, so after some small number of touches we start calculating, so not to make mistakes
    
    //these veriables are used for kintic scrolling along with their timer for speed calculation
    float velocity_x;
    float velocity_y;
    bool fingerDown;
    
    //these values are used when we get out of range for bounce on edge features
    
    bool outOfRange;
    
    
    float total;            //handle the exceptions that's if our update methode took more than some seconds we'll stop it
    
};

#endif //#define LAYERWITHPIPNCHANDSCROLL_H
