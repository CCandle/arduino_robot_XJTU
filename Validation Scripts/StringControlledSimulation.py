import numpy as np
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d.axes3d as axes3d

def vec_add(v1, v2):
    return (v1[0]+v2[0], v1[1]+v2[1], v1[2]+v2[2])

def vec_minus(v1, v2):
    return (v1[0]+v2[0], v1[1]+v2[1], v1[2]+v2[2])

def polar_to_orthogonal(rho, theta, phi):
    return (
        rho * np.sin(phi) * np.cos(theta),  # x
        rho * np.sin(phi) * np.sin(theta),  # y
        rho * np.cos(phi)                   # z
    )

def draw_sphere(ax, R):
    theta, phi = np.linspace(0, 2 * np.pi, 100), np.linspace(0, np.pi, 100)
    THETA, PHI = np.meshgrid(theta, phi)
    (X, Y, Z) = polar_to_orthogonal(R, THETA, PHI)
    ax.plot_surface(X, Y, Z, alpha=0.2)

def draw_line(ax, p1, p2):
    vec = vec_minus(p1, p2)
    

# structrual parameters
R_0 = 1         # radius of the sphere
r_0 = .5        # inner length of the tetrahedron points to center

fig = plt.figure()
ax = axes3d.Axes3D(fig)
ax.set_xlim3d(xmin=-2, xmax=2)
ax.set_ylim3d(ymin=-2, ymax=2)
ax.set_zlim3d(zmin=-2, zmax=2)

draw_sphere(ax, 1)

fix_points = [(0,0,R_0), (2/3*2**.5*R_0,0,-1/3*R_0), (-2**.5/3*R_0,6**.5/3*R_0,-R_0/3), (-2**.5/3*R_0,-6**.5/3*R_0,-R_0/3)]

ax.scatter3D([p[0] for p in fix_points], [p[1] for p in fix_points], [p[2] for p in fix_points])

plt.show()