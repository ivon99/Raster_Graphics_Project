# Raster_Graphics_Project
Project_2 for OOP course

Raster Graphics is a photo editor working with Netpbm images.

The program supports sessions to which the user can add photos of any of the supported image formats (.pbm, .pgm, .ppm). The user can choose to modify the images in the currently opened session by inputting commands corresponding to supported transformations. The images are only modified if the user chooses **save**, which modifies all the images in the current session. The user can add unlimited amount of images, as well as can undo any of the applied transformations before the loaded images are saved. The user can add new sessions and switch between already created ones. Every session is identified with a unique session ID.

Supported image modifications are:

= grayscale
= monochrome
= negative
= rotate (left/right)
= collage of two images (horizontal/vertical)
