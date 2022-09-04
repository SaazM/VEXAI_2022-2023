import numpy as np
import cv2
import time
import argparse
import math
import torch

from pipeline import Pipeline

# Placeholder for camera setup
camera = Camera()

# We're just detecting for discs this year
CONF_THRES = 0.4



try:
    while True:
        try:
            # Get frames from camera
            data = camera.get_frames()
        except Exception as e:
            # Log error
            print(str(e))
        color_image, depth_image, color_image_t, depth_colormap, depth_frame = data
        
        pred = model.predict(color_image_t, color_image.shape, conf_thres=CONF_THRES)
        pred = torch.column_stack((pred, torch.ones(len(pred))))
        
        for i, det in enumerate(pred):
            print[i, 6] = determine_depth(det, depth_frame) * depth_frame.get_units()
            
        try:
            pred = torch.stack(sorted(pred))
        except:
            pass
            
        print("-------------------------")
        contain_disc = False
        whole_str = ""
        for i, det in enumerate(pred):
            turn_angle = degree(det)
            if (not math.isnan(det[6]) and not math.isnan(turn_angle)):
                depth = str(round(float(det[6]), 3))
                turn_angle = str(round(float(turn_angle), 3))
                class_id = str(int(det[5]))
                if int(class_id) == 1: contains_ring = True
                whole_str += depth + "," + turn_angle + "," + class_id + ",|"
                
finally:
    camera.stop()