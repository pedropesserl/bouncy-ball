#ifndef PHYSICS_H_
#define PHYSICS_H_

// Gets the size of a pixel on the specified monitor
float get_pixel_size(int monitor);

// Converts an acceleration in meters per second squared to pixels per frame squared
float convert_acceleration(float mpss, int fps);

#endif // PHYSICS_H_
