#include "LayerWithPinchAndScroll.h"

const int douple_tap_milliseconds = 350;

LayerWithPinchAndScroll::LayerWithPinchAndScroll() {
    // Make sure the layer accepts touches

    setTouchEnabled(true);

    winSize = Director::sharedDirector()->winSizeInPixels();                //save window size inside the variable

    // Set up the starting variables
    max_scale = 1;
    pich_to_zoom = 1;
    scrolling = 1;
    doubletap = 1;
    pinching = 0;
    minY = 0;
    minX = 0;
    maxY = 0;
    maxX = 0;
    outOfRange = 0;
    zooomingSpeed = original_zooming_speed;
    doubletap_state = double_tap_not_started;
}

void LayerWithPinchAndScroll::touchBegin(const QPointF &touchPoint){

    velocity_x = 0;
    velocity_y = 0;

    if (doubletap) {
        if (doubletap_state == double_tap_not_started || timer.elapsed() > douple_tap_milliseconds) {
            timer.restart();
            doubletap_state = double_tap_not_started;
        }
    }

    //fixed as engine does not support multi touch now
    int touches_count = 1;

    if (touches_count == 1) {
        pinching = 0;
    }
    else {
        pinching = 1;
    }
    outOfRange = 0;
    fingerDown = true;
    touchNum = 0;



    if (touches_count == 1) {
        LastX = touchPoint.x();
        LastY = touchPoint.y();

    } else if (touches_count == 2) {

        //        doubletap_state = double_tap_not_started;
        //        doubletap = 0;
        //        touchNum = 0;
        //        NSArray *touchesArray = [touches allObjects];
        //        UITouch *touch1 = [touchesArray objectAtIndex:0];
        //        CGPoint TouchLoc1 = [touch1 locationInView: [touch1 view]];
        //        TouchLoc1 = [[CCDirector sharedDirector] convertToGL:TouchLoc1];

        //        UITouch *touch2 = [touchesArray objectAtIndex:1];
        //        CGPoint TouchLoc2 = [touch2 locationInView: [touch2 view]];
        //        TouchLoc2 = [[CCDirector sharedDirector] convertToGL:TouchLoc2];
        //        PrevDistance = ccpDistance(TouchLoc1, TouchLoc2);
    }
}

void LayerWithPinchAndScroll::touchMove(const QPointF &touchPoint) {

    int touches_count = 1;
    //we'll do pinching or scrolling if it's not a double tap and we are moving our fingers

    if(touches_count == 2)
    {
        //            if (pich_to_zoom) {
        //                // setting pinching
        //                pinching = 1;

        //                //taking the two points from the finger
        //                NSArray *touchesArray = [touches allObjects];
        //                UITouch *touch1 = [touchesArray objectAtIndex:0];
        //                CGPoint TouchLoc1 = [touch1 locationInView: [touch1 view]];
        //                TouchLoc1 = [[CCDirector sharedDirector] convertToGL:TouchLoc1];

        //                UITouch *touch2 = [touchesArray objectAtIndex:1];
        //                CGPoint TouchLoc2 = [touch2 locationInView: [touch2 view]];
        //                TouchLoc2 = [[CCDirector sharedDirector] convertToGL:TouchLoc2];
        //                CurrDistance = ccpDistance(TouchLoc1, TouchLoc2);
        //                float currScale = [self scale];
        //                float addedScale = ( CurrDistance - PrevDistance ) / 200;

        //                // we don't have to exceed the max scale speed for more smoother operation
        //                if (addedScale > maxScalingSpeed) {
        //                    addedScale = maxScalingSpeed;
        //                }

        //                if (addedScale < -1*maxScalingSpeed) {
        //                    addedScale = -1*maxScalingSpeed;
        //                }

        //                bool outOfRangeScale = false;

        //                //applying the new scale and making sure it's not above the max or min scale

        //                currScale += addedScale;
        //                if (currScale > max_scale) {
        //                    currScale = max_scale;
        //                    outOfRangeScale = true;
        //                }
        //                if (currScale < min_scale) {
        //                    currScale = min_scale;
        //                    outOfRangeScale = true;
        //                }

        //                // we need to exceed the number of laps, so that our processing will be much more accurate
        //                if (    touchNum < laps_until_processing) {
        //                    touchNum++;
        //                }
        //                else
        //                {
        //                    doubletap = 0;
        //                    [self setScale:currScale];

        //                    //after we already scaled we will position our self not outside the range if we are out the range

        //                    CGPoint tempPoint = self.position;

        //                    //we'll try to move to the user location where his finger is while scrolling using vector addtion with screen center as center point

        //                    //defining our first vector x and y
        //                    float diffrenceInX = TouchLoc1.x-(winSize.width/2);
        //                    float diffrenceInY = TouchLoc1.y-(winSize.height/2);

        //                    //adding our second vector to the previous

        //                    diffrenceInX += TouchLoc2.x-(winSize.width/2);
        //                    diffrenceInY += TouchLoc2.y-(winSize.height/2);

        //                    //moving our point excatly in the opposite of that new vector/100 (just calculation)
        //                    tempPoint.x-=diffrenceInX/50;
        //                    tempPoint.y-=diffrenceInY/50;

        //                    //making sure our calculation is not outside our range

        //                    tempPoint = [self check_point_with_extra_range:tempPoint];
        //                    //applying the new position to our selves if we haven't exceded the scale range
        //                    if (!outOfRangeScale) {
        //                        self.position = tempPoint;
        //                    }

        //                }


        //                PrevDistance = CurrDistance;

        //            }
    }
    else if(touches_count == 1 && !pinching && doubletap_state != double_tap_detected)
    {
        if (scrolling) {

            //recording finger location

            // taking our point and getting the distance vector
            QPointF tempPoint = pos();
            velocity_x = touchPoint.x() - LastX;
            velocity_y = touchPoint.y() - LastY;

            tempPoint = move_point(tempPoint,&velocity_x,&velocity_y);
            tempPoint = check_point_with_extra_range(tempPoint);


            if ( touchNum < laps_until_processing) {
                touchNum++;
            } else {

                doubletap_state = double_tap_not_started;
                setPos(tempPoint);
            }

            //we're calculating the speed here, so we use this for kinitec scrolling


            // here we are checking whether we are going to reset the time, cause it's also used by the double time for few milliseconds
            if (doubletap_state == double_tap_not_started || timer.elapsed() > douple_tap_milliseconds ) {
                timer.restart();
                doubletap = 0;
                doubletap_state = double_tap_not_started;
            }

            //saving old values for next round use

            LastX = touchPoint.x();
            LastY = touchPoint.y();
        }
    }
}

void LayerWithPinchAndScroll::touchEnd(const QPointF &touchPoint) {

    int touches_count = 1;

    scrollUnSchedualUpdate();

    if (pinching) {
        velocity_y = 0;
        velocity_x = 0;
    }

    if (touches_count <= 1) {
        touchNum = 0;
    }
    fingerDown = false;
    total = 0.0;
    LastX = 0;
    LastY = 0;



    //code segment to detect if it's a double tap

    if (doubletap) {
        if (!pinching && touchNum < 3 && doubletap_state != double_tap_detected ) {
            if (touches_count == 1) {
                if (doubletap_state == double_tap_not_started) {
                    firsTapX = touchPoint.x();
                    firsTapY = touchPoint.y();
                    doubletap_state = double_tap_started_calculation;
                }
                else
                {
                    if (timer.elapsed() < douple_tap_milliseconds ) {
                        if ( touchPoint.x() < (LastX + 10) || touchPoint.x() > (LastX - 10) ) {
                            if ( touchPoint.y() < (LastY + 10) || touchPoint.y() > (LastY - 10) ) {
                                // It's a double tap
                                doubletap = 0;
                                doubletap_state = double_tap_detected;
                                setTouchEnabled(false);
                                if (scale() > ((max_scale+min_scale)/2)) {
                                    zoomin = 0;
                                }
                                else {
                                    zoomin = 1;
                                }
                                zooomingSpeed = original_zooming_speed;
                            }
                        }
                    }
                }
            }
        }
    }

    //end of detecting a double tap

    scrollSchedualUpdate();
}

void LayerWithPinchAndScroll::update(double delta) {
    //here we'll do kintitic scrolling for the user after he lefts up his finger
    total += delta;
    if (total > 5){
        // if there's something wrong or too long, stop it
        scrollUnSchedualUpdate();
    }
    if (fingerDown) {
        total = 0;
        scrollUnSchedualUpdate();
    }

    if (doubletap_state == double_tap_detected) {

        //double tap detected, zoom a little little for smooth operation
        delta*=1000;
        float newScale;
        if (zoomin) {
            newScale = scale()+(zooomingSpeed*delta);
        }

        else {
            newScale = scale()-(zooomingSpeed*delta);
        }
        if (newScale < min_scale) {

            //our job has reached the end
            velocity_x = 0;
            velocity_y = 0;
            newScale = min_scale;
            doubletap_state = double_tap_not_started;
            zooomingSpeed = original_zooming_speed;
        }
        if (newScale > max_scale) {

            //our job has reached the end
            velocity_x = 0;
            velocity_y = 0;
            newScale = max_scale;
            doubletap_state = double_tap_not_started;
            zooomingSpeed = original_zooming_speed;
        }

        scrollsetScale(newScale);

        //we'll try to move to tap location

        if (doubletap_state != double_tap_not_started) {
            zooomingSpeed-= (zooomingSpeed/10);
            if (zooomingSpeed < 0.001) {
                zooomingSpeed = 0.001;
            }

            QPointF tempPoint = pos();
            if (zoomin) {
                tempPoint.setX( tempPoint.x() - ((firsTapX-(winSize.width()/2))/(0.025/zooomingSpeed)) );
                tempPoint.setY( tempPoint.y() - ((firsTapY-(winSize.height()/2))/(0.025/zooomingSpeed)) );
            }
            tempPoint = check_point_with_no_extra_range(tempPoint);
            setPos(tempPoint);
        }

    }
    else {
        if (!outOfRange) {

            //CCLOG(@"we'll be moving at the speed of  vx %f and vy %f", velocity_x, velocity_y);
            delta *= 1000;
            bool stopthisx = false;
            bool stopthisy = false;
            QPointF tempPoint = pos();
            tempPoint.setX( tempPoint.x() + (velocity_x * delta) );
            tempPoint.setY( tempPoint.y() + (velocity_y * delta) );
            if (tempPoint.x()+(winSize.width()/10) > maxX || tempPoint.x()-(winSize.width()/10) < minY) {
                velocity_x  -=  (velocity_x/4);
            }
            else {
                velocity_x  -=  (velocity_x/15);
            }
            if (tempPoint.y()+(winSize.width()/10) > maxY || tempPoint.y()-(winSize.width()/10) < minY) {
                velocity_y  -=  (velocity_y/4);
            }
            else {
                velocity_y  -=  (velocity_y/15);
            }
            if (tempPoint.x() < minX) {
                tempPoint.setX( tempPoint.x() - ((velocity_x*delta)/2) );
            }
            else
                if (tempPoint.x()  > maxX) {
                    tempPoint.setX( tempPoint.x() - ((velocity_x*delta)/2) );
                }

            if (tempPoint.y() < minY) {
                tempPoint.setY( tempPoint.y() + ((velocity_y*delta)/2) );
            }
            else
                if (tempPoint.y()  > maxY) {
                    tempPoint.setY( tempPoint.y() + ((velocity_y*delta)/2) );
                }


            if (tempPoint.x() < minX - (extraRangeX/10) ) {
                tempPoint.setX(minX - (extraRangeX/10));
                stopthisx = true;
            }
            else
                if (tempPoint.x()  > maxX + (extraRangeX/10)) {
                    tempPoint.setX(maxX + (extraRangeX/10));
                    stopthisx = true;
                }

            if (tempPoint.y() < minY - (extraRangeY/10)) {
                tempPoint.setY(minY - (extraRangeY/10));
                stopthisy = true;
            }
            else
                if (tempPoint.y()  > maxY +(extraRangeY/10)) {
                    tempPoint.setY(maxY + (extraRangeY/10));
                    stopthisy = true;
                }

            setPos(tempPoint);
            if ( ( ( velocity_x<0.05 && velocity_x>-0.05 ) && (velocity_y<0.05 && velocity_y>-0.05) ) || (stopthisx && stopthisy) ) {
                tempPoint = pos();
                if (tempPoint.x() < minX) {
                    outOfRange = 1;
                }
                else
                    if (tempPoint.x()  > maxX) {
                        outOfRange = 1;
                    }

                if (tempPoint.y() < minY) {
                    outOfRange = 1;
                }
                else
                    if (tempPoint.y()  > maxY) {
                        outOfRange = 1;
                    }
                if (!outOfRange) {
                    scrollUnSchedualUpdate();
                }
            }
        }
        else
        {

            //CCLOG(@"out of range");
            bool x_done = true;
            bool y_done = true;
            delta *= 100;
            const float divideBy = 20;
            const float minSpeed = 0.1;
            QPointF tempPoint = pos();


            if (tempPoint.x() < minX) {
                x_done = false;
                velocity_x = (tempPoint.x()-minX) /divideBy;
                if (-1*minSpeed < velocity_x) {
                    velocity_x = minSpeed ;
                    velocity_x *= -1;
                }
                tempPoint.setX(tempPoint.x() - ((velocity_x*delta)) );
                if (tempPoint.x() > minX)
                    tempPoint.setX(minX);
            }
            else
                if (tempPoint.x()  > maxX) {
                    velocity_x = (tempPoint.x()-maxX) / divideBy;
                    x_done = false;
                    if (minSpeed > velocity_x) {
                        velocity_x = minSpeed ;
                    }
                    tempPoint.setX( tempPoint.x() - ((velocity_x*delta)) );
                    if (tempPoint.x() < maxX)
                        tempPoint.setX(maxX);
                }

            if (tempPoint.y() < minY) {
                velocity_y = (tempPoint.y()-minY) / divideBy;
                y_done = false;
                if (-1* minSpeed < velocity_y) {
                    velocity_y = minSpeed ;
                    velocity_y *= -1;
                }
                tempPoint.setY( tempPoint.y() - ((velocity_y*delta)) );
                if (tempPoint.y() > minY)
                    tempPoint.setY(minY);
            }
            else
                if (tempPoint.y()  > maxY) {
                    velocity_y = (tempPoint.y()-maxY) / divideBy;
                    y_done = false;
                    if ( minSpeed > velocity_y) {
                        velocity_y = minSpeed ;
                    }
                    tempPoint.setY( tempPoint.y() - ((velocity_y*delta)) );
                    if (tempPoint.y() < maxY)
                        tempPoint.setY(maxY);
                }
            setPos(tempPoint);
            if ( x_done && y_done ) {
                scrollUnSchedualUpdate();
            }

        }

    }

}

void LayerWithPinchAndScroll::scrollSchedualUpdate() {
    schedualUpdate();
}

void LayerWithPinchAndScroll::scrollUnSchedualUpdate() {
    unSchedualUpdate();
    doubletap = 1;
    setTouchEnabled(true);
}

void LayerWithPinchAndScroll::scrollsetScale(float p_scaleVal) {
    setScale(p_scaleVal);
    maxX =  ((p_scaleVal*layerWidth)/2) - (winSize.width()/2) ;
    minX = -maxX;
    maxY = ((p_scaleVal*layerHeight)/2) - (winSize.height()/2) ;
    minY = -maxY;
}

QPointF LayerWithPinchAndScroll::check_point_with_extra_range(QPointF &p_point) {
    if (p_point.x() < minX - extraRangeX) {
        p_point.setX(minX - extraRangeX);
    }
    else
        if (p_point.x()  > maxX + extraRangeX) {
            p_point.setX(maxX + extraRangeX);
        }

    if (p_point.y() < minY - extraRangeY) {
        p_point.setY(minY - extraRangeY);
    }
    else
        if (p_point.y()  > maxY + extraRangeY) {
            p_point.setY(maxY + extraRangeY);
        }
    return p_point;
}

QPointF LayerWithPinchAndScroll::check_point_with_no_extra_range(QPointF &p_point) {

    if (p_point.x() < minX) {
        p_point.setX(minX);
    } else if (p_point.x()  > maxX) {
        p_point.setX(maxX);
    }

    if (p_point.y() < minY) {
        p_point.setY(minY);
    } else if (p_point.y()  > maxY) {
        p_point.setY(maxY);
    }

    return p_point;
}

QPointF LayerWithPinchAndScroll::move_point(QPointF p_point, float *vX, float *vY) {

    p_point.setX(p_point.x() + *vX);
    p_point.setY(p_point.y() + *vY);


    if ( ( p_point.x() < minX || p_point.x()  > maxX ) && ( p_point.y() < minY || p_point.y()  > maxY )) {
        outOfRange = 1;
    }
    else {
        outOfRange = 0;
    }
    // if it's out of range, we'll remove half of it

    if (p_point.x() < minX) {
        p_point.setX(p_point.x() - (*vX/2));
    }
    else
        if (p_point.x()  > maxX) {
            p_point.setX(p_point.x() - (*vX/2) );
        }

    if (p_point.y() < minY) {
        p_point.setY( p_point.y() - (*vY/2) );
    } else if (p_point.y()  > maxY) {
        p_point.setY( p_point.y() - (*vY/2) );
    }

    if (timer.elapsed() == 0) {
        //CCLOG(@"velocity_x is nan");
        *vX = maxScrollingSpeed;
        *vY = maxScrollingSpeed;
    } else {
        *vX /= timer.elapsed();
        *vY /= timer.elapsed();
    }


    // if we are dividing by zero, again, we'll set it to a max, cause we don't want infinity

    //making sure our distance vector doesn't exceed the max scrolling speed
    if (*vX > maxScrollingSpeed) {
        *vX = maxScrollingSpeed;
    }
    if (*vY > maxScrollingSpeed) {
        *vY = maxScrollingSpeed;
    }


    if (*vX < -1*maxScrollingSpeed) {
        *vX = -1*maxScrollingSpeed;
    }
    if (*vY < -1*maxScrollingSpeed) {
        *vY = -1*maxScrollingSpeed;
    }


    return p_point;
}
