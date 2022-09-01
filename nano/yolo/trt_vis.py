import numpy as np
import cv2
import time
import argparse
import math

import torch
from utils.yolo.plots import Annotator, colors
from utils.serial import Coms
from utils.data import return_data, determine_depth, degree, sort_distance, quicksort
from utils.camera import Camera
from utils.models import Model
from sklearn.cluster import DBSCAN

# TODO: Camera setup

cam = Camera(cameras, args.camera)
comm = Coms()
obj = "disc"
# model = Model(<>)
conf_thres = 0.4
whole_str = ""

try:
    while True:
        start = time.time()
        try:
            data = cam.poll_frames()
        except Exception as e:
            print(str(e))
            continue
        
        if data is None:
            continue

        color_image, depth_image, color_image_t, depth_colormap, depth_frame = data

        pred = model.predict(color_image_t, color_image.shape, conf_thres=conf_thres)
        pred = torch.column_stack((pred, torch.ones(len(pred))))

        for i, det in enumerate(pred):
            pred[i, 6] = determine_depth(det, depth_image) * depth_frame.get_units()

        try:
            pred = torch.stack(quicksort(pred))
            
        except:
            pass

        print("--------------")
        print("Time elapsed: {}".format(time.time() - start))

        color_annotator = Annotator(color_image, line_width=2, pil=not ascii)
        depth_annotator = Annotator(depth_colormap, line_width=2, pil=not ascii)

        contains_disc = False

        if args.display:
            for det in pred:
                color_annotator.box_label(det[:4], f'{obj} {det[4]:.2f}', color=colors(int(det[5]), True))
                depth_annotator.box_label(det[:4], f'{obj} {det[4]:.2f}', color=colors(int(det[5]), True))
            color_image, depth_colormap = color_annotator.result(), depth_annotator.result()
            images = np.hstack((color_image, depth_colormap))
            cv2.namedWindow('RealSense', cv2.WINDOW_AUTOSIZE)
            cv2.imshow('RealSense', images)
            cv2.waitKey(1)
        print("wholestr: " + whole_str)

finally:
    cam.stop()
