import math

def generate_circle_points(center, radius, num_points, tilt_angle_degrees=0):
    tilt_angle_radians = math.radians(tilt_angle_degrees)
    circle_points = []
    for i in range(num_points):
        angle = 2 * math.pi * i / num_points
        x = center[0] + radius * math.cos(angle)
        y = center[1] + radius * math.sin(tilt_angle_radians) * math.sin(angle)
        z = center[2] + radius * math.cos(tilt_angle_radians) * math.sin(angle)
        
        temp = x
        x = z
        z = temp
        circle_points.append((x, y, z))
    
    return circle_points

# Define the radius and center of the circle
radius = 5  # You can alter this
center = (0, 0, 0.1)  # You can alter this

# Generate circle points with tilt angle of 45 degrees
circle_points = generate_circle_points(center, radius, 9, tilt_angle_degrees=2)

# Output the circle points
for point in circle_points:
    print(f"<point x=\"{point[0]}\" y=\"{point[1]}\" z=\"{point[2]}\" />")

while(True):
    pass