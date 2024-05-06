import numpy as np
import math

def generate_oval_sphere_points(num_stacks, divisions_per_stack, a, b, c, file_path):
    points = []
    
    def oval_point(theta, phi, a, b, c):
        x = a * math.cos(theta) * math.sin(phi)
        y = b * math.sin(theta) * math.sin(phi)
        z = c * math.cos(phi)
        return (x, y, z)
    
    def createPatches():
        patchCounter = 0
        lenpatch = 0
        string = ''
        for index in range(len(points)):
            string += f'{index} '
            lenpatch += 1
            if lenpatch == 16:
                string += f'\n'
                lenpatch = 0
                patchCounter += 1
        return patchCounter, string

    for stack_index in range(num_stacks):
        for div_index in range(divisions_per_stack):
            theta0 = 2 * math.pi * div_index / divisions_per_stack
            theta1 = 2 * math.pi * (div_index + 1) / divisions_per_stack
            phi0 = math.pi * stack_index / num_stacks
            phi1 = math.pi * (stack_index + 1) / num_stacks

            points.append(oval_point(theta0, phi0, a, b, c))
            points.append(oval_point(theta1, phi0, a, b, c))
            points.append(oval_point(theta1, phi1, a, b, c))
            points.append(oval_point(theta0, phi1, a, b, c))

    with open(f'../patches/{file_path}', 'w') as f:
        patchCounter, string = createPatches()
        f.write(f'{patchCounter}\n{string}')
        f.write(f'{len(points)}\n')
        for point in points:
            f.write(f' {point[0]:.7f},{point[1]:.7f},{point[2]:.7f}\n')

generate_oval_sphere_points(10, 30, 1.0, 0.7, 0.5, "comet.patch")
print("Done!")
