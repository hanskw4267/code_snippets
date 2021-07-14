from threading import Thread
import cv2

class load_cams:
  def __init__(self, sources=[0, 2], width=224, height=224, rez_width=640, rez_height=640):
    # Store camera parameters
    self.width = width
    self.height = height
    self.rez_width = rez_width
    self.rez_height = rez_height

    # Initialise image and thread arrays
    n = len(sources)
    self.imgs, self.threads = [None] * n, [None] * n
    
    # Start image capture threads
    for i, src in enumerate(sources):
      cap = cv2.VideoCapture(src)
      assert cap.isOpened(), f"failed to open {src}" # Make sure capture can be opened
      _, self.imgs[i] = cap.read()
      self.threads[i] = Thread(target=self.update, args=([i, cap]), daemon=True)
      self.threads[i].start()
      print(f"Success in opening camera {src}")

  def update(self, i, cap):
    # Update image in array accordingly
    while cap.isOpened():
      cap.grab() # Get image frame
      success, im = cap.retrieve() # Retrieve frame
      # Store image if retrieval was successful
      self.imgs[i] = cv2.resize(im, self.width, self.height) if success else self.imgs[i] * 0
  
  def getFrames(self):
    return self.imgs.copy()
