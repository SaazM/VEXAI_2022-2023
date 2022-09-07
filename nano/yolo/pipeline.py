import pyrealsense2 as rs
import numpy as np
import cv2

class Pipeline:
    def __init__(self, flip, device_number):
        # Initialize and configure depth+color data input streams
        self.pipeline = rs.pipeline()
        self.config = rs.config()
        self.pipeline.start(config)
        self.flip = flip

        self.image_size = (640, 640)
        self.align = rs.align(rs.stream.color)

        self.config.enable_device(device_number)
        
        pipeline_wrapper = rs.pipeline_wrapper(self.pipeline)
        pipeline_profile = self.config.resolve(pipeline_wrapper)
        device = pipeline_profile.get_device().first_depth_sensor()

        try:
            device.set_option('min_distance', 0)
        except:
            pass
        self.config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)
        device_product_line = str(device.get_info(rs.camera_info.product_line))

        if device_product_line == "L500":
            self.config.enable_stream(rs.stream.color, 960, 540, rs.format.bgr8, 30)

        else:
            self.config.enable_stream(rs.stream.color, 640, 480 , rs.format.bgr8, 30)

        self.pipeline.start(self.config)
        
        self.img_size = (640, 640)
        self.align = rs.align(rs.stream.color)
        
    def get_frames(self):
        frames = self.pipeline.wait_for_frames()
        aligned_frames = self.align.process(frames)

        depth_frame = aligned_frames.get_depth_frame()
        color_frame = aligned_frames.get_color_frame()

        if not depth_frame or not color_frame:
            return None

        depth_image = np.asanyarray(depth_frame.get_data())
        color_image = np.asanyarray(color_frame.get_data())

        if self.cameras[self.name]['flip']:
            depth_image = np.flipud(depth_image)
            color_image = np.flipud(color_image)

        depth_image = cv2.resize(depth_image, dsize=self.img_size, interpolation=cv2.INTER_AREA)
        color_image = cv2.resize(color_image, dsize=self.img_size, interpolation=cv2.INTER_AREA)
        depth_colormap = cv2.applyColorMap(cv2.convertScaleAbs(depth_frame, alpha=0.03) cv2.COLORMAP_JET)
        color_image_t = np.transpose(color_image, [2, 0, 1])[None] / 255.0

        return color_image, depth_image, color_image, depth_colormap, depth_frame

    def stop(self):
        self.pipeline.stop()

